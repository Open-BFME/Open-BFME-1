"""gen_uw.land() as a transaction, with the same guarantees land_batch has.

land() does not append: it REWRITES every row and pin it owns from a fresh
compile. That makes it the one ledger writer that can lose a row without
anybody noticing -- a row that drops out of the fresh set simply stops being
written, and functions.csv merges with git's union driver, which has no way to
express a deletion. Without a tombstone the next rebase from a branch that
forked earlier puts the dropped row straight back.

Four guarantees are asserted here, each one absent before this file existed:

  * one exclusive reverse/.add_match.lock held across derive -> write -> verify;
  * a byte snapshot opened at the FIRST write, not at the gate -- a guard that
    opens at the gate strands whatever the earlier writes left behind, and
    deleted_rows.csv is append-only, so a stranded tombstone outlives the
    functions.csv it was written against;
  * a superseded gen-dump row retracted AND tombstoned, through
    gen_small.retract_dump_rows rather than a second implementation;
  * a FULL ./build.sh + check_csv before land() returns, with every ledger and
    every owned source reverted on anything short of green;
  * the rewritten block put back where it was, so a row another session appended
    after the last land is not relocated into a union-merge duplicate.
"""
import importlib.util
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
FUNCTIONS_HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
DELETED_HEADER = "name,target_rva,reason"
SYMBOLS_HEADER = "name,address,notes"


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


gen_uw = _load("gen_uw")
from portable_lock import lock as take_lock  # noqa: E402

TARGET = 0x00001234
RVA = 0x00BF0000
OWNED_SOURCE = "Code/gen_small/uw_gen_000.cpp"
DUMP = (f"?d_00bf0000@@YAXXZ,,0x{RVA:08X},8,Code/gen_asm/d_00bf0000.asm,matched,"
        "gen-dump;ghidra=Unwind@00bf0000")


class World:
    """A tiny tree with the three ledgers, an owned source dir, and a gate knob."""

    def __init__(self, tmp_path, monkeypatch, *, rows=(), owned=(), symbols_eol="\r\n",
                 gate=0, funclets=((RVA, 8, -16, TARGET),)):
        self.root = tmp_path
        self.functions = tmp_path / "functions.csv"
        self.symbols = tmp_path / "symbols.csv"
        self.deleted = tmp_path / "deleted_rows.csv"
        self.source_dir = tmp_path / "Code" / "gen_small"
        self.source_dir.mkdir(parents=True)
        self.functions.write_bytes(
            (FUNCTIONS_HEADER + "\r\n").encode()
            + b"".join(row.encode() + b"\r\n" for row in (*rows, *owned)))
        self.symbols.write_bytes(
            (SYMBOLS_HEADER + symbols_eol).encode()
            + f"??1Other@@QAE@XZ,0x00009999,{symbols_eol}".encode())
        self.deleted.write_text(DELETED_HEADER + "\n", encoding="utf-8")
        for name in {row.split(",")[4] for row in owned}:
            (tmp_path / name).write_text("// stale\n", encoding="utf-8")
        # check_csv rejects a row whose source is untracked, so land() puts the
        # sources it writes in the index: the tree it runs in has to be a repo.
        subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
        for name in {row.split(",")[4] for row in owned}:
            subprocess.run(["git", "-C", str(tmp_path), "add", "--", name], check=True)

        monkeypatch.setattr(gen_uw, "ROOT", tmp_path)
        monkeypatch.setattr(gen_uw, "FUNCTIONS", self.functions)
        monkeypatch.setattr(gen_uw, "SYMBOLS", self.symbols)
        monkeypatch.setattr(gen_uw, "DELETED", self.deleted)
        monkeypatch.setattr(gen_uw, "SOURCE_DIR", self.source_dir)
        monkeypatch.setattr(gen_uw, "LOCK_FILE", tmp_path / ".add_match.lock",
                            raising=False)
        # gen_uw delegates the double-claim decision, the dump retraction and the
        # tombstone append to gen_small, which reaches for its own module paths.
        monkeypatch.setattr(gen_uw.gen_small.B, "FUNCTIONS", self.functions)
        monkeypatch.setattr(gen_uw.gen_small, "DELETED", self.deleted)
        self.gate_calls = []
        monkeypatch.setattr(gen_uw, "run", self._gate, raising=False)
        self.gate = gate

        made = [gen_uw.Funclet("A" if disp < 0 else "B", rva, size, disp, target, 0)
                for rva, size, disp, target in funclets]
        monkeypatch.setattr(gen_uw, "read_funclets",
                            lambda ledger: (made, [], {}, {}))
        monkeypatch.setattr(gen_uw, "compiled_slots", self._slots)

    def _gate(self, command, label):
        self.gate_calls.append(label)
        return self.gate

    def _slots(self, source):
        return {gen_uw.key_of(funclet): f"$L{700 + index}"
                for index, funclet in enumerate(gen_uw.read_funclets(None)[0])}

    def snapshot(self):
        # The index is part of the state land() changes: it `git add`s the
        # sources it writes, so a revert that leaves them staged hands the next
        # commit a file with no rows.
        tracked = subprocess.run(["git", "-C", str(self.root), "ls-files"],
                                 capture_output=True, text=True, check=True).stdout
        return (self.functions.read_bytes(), self.symbols.read_bytes(),
                self.deleted.read_bytes(),
                {p.name: p.read_bytes() for p in sorted(self.source_dir.glob("*.cpp"))},
                tracked)

    @property
    def rows(self):
        return self.functions.read_text(encoding="utf-8")

    @property
    def tombstones(self):
        return self.deleted.read_text(encoding="utf-8")


def test_a_red_gate_reverts_every_ledger_and_every_owned_source(tmp_path, monkeypatch):
    """The gate is the point of the transaction: without it land() `returns` on
    rows nothing ever compiled."""
    world = World(tmp_path, monkeypatch, gate=1)
    before = world.snapshot()

    with pytest.raises(SystemExit):
        gen_uw.land()

    assert world.gate_calls, "land() must prove its rows with ./build.sh before returning"
    assert world.snapshot() == before, "a red gate must leave nothing behind"


def test_a_green_gate_lands_the_rows_stages_the_source_and_runs_check_csv(
        tmp_path, monkeypatch):
    world = World(tmp_path, monkeypatch)

    gen_uw.land()

    assert f"uw_{RVA:08x}" in world.rows
    assert any("build.sh" in call for call in world.gate_calls)
    assert any("check_csv" in call for call in world.gate_calls)
    assert OWNED_SOURCE in world.snapshot()[-1], (
        "check_csv rejects a row whose source is untracked, so the gate can only "
        "prove a generated file that is already in the index")


def test_landing_twice_rewrites_the_same_pins_instead_of_appending(tmp_path, monkeypatch):
    """The generator's own regression check: a second run reports nothing new.

    It did not hold. rewrite_lines splits on b"\\n", so every CRLF pin reaches the
    ownership predicate with a trailing b"\\r" and `endswith(PIN_NOTE)` was false
    for all of them -- each run appended a fresh copy of all 511 pins it believed
    it had removed. With no gate in land(), the duplicate only surfaced on some
    later contributor's check_csv.
    """
    world = World(tmp_path, monkeypatch)

    gen_uw.land()
    once = world.snapshot()
    gen_uw.land()

    assert world.snapshot() == once, "a second land must be a byte-for-byte no-op"
    assert world.symbols.read_bytes().count(gen_uw.PIN_NOTE_BYTES) == 1


CONCURRENT = ("_luaK_number,,0x0099EE10,349,Code/Libraries/Source/Lua/lcode.c,"
              "matched,")
# Two funclets, because one is not enough to show the damage: git's union driver
# resolves a single relocated line cleanly and only starts keeping both copies
# once the block it moved across is two lines or more. The repo's block is 18,689.
TWO = ((RVA, 8, -16, TARGET), (RVA + 0x100, 8, -24, TARGET))


def test_a_row_appended_after_the_landed_block_keeps_its_position(tmp_path, monkeypatch):
    """The rewrite must put the fresh block back where the old one was.

    The no-op test above passed while this was broken, because its fixture puts
    the owned rows last -- exactly where an append-at-end rewrite would leave
    them. In the repo they are not last: nine rows other sessions appended after
    the previous land sat behind 18,689 owned rows, and re-landing hoisted every
    one of them to the top of the block.
    """
    world = World(tmp_path, monkeypatch, funclets=TWO)
    gen_uw.land()
    with world.functions.open("ab") as handle:      # a concurrent single-row append
        handle.write(CONCURRENT.encode() + b"\r\n")
    once = world.snapshot()

    gen_uw.land()

    assert world.rows.splitlines()[-1] == CONCURRENT, (
        "a row this generator does not own must not be relocated by the rewrite")
    assert world.snapshot() == once, "a re-land of an unchanged population is a no-op"


def test_a_relocated_row_is_duplicated_by_the_union_merge_driver(tmp_path, monkeypatch):
    """Why the position matters, through the driver that actually runs.

    reverse/functions.csv is `merge=union` in .gitattributes. A rewrite that
    relocates a line is, to that driver, a deletion on one side with no
    corresponding change on the other -- so it keeps both copies and check_csv
    reports an exact duplicate row on somebody else's rebase.
    """
    world = World(tmp_path, monkeypatch, funclets=TWO)
    gen_uw.land()
    with world.functions.open("ab") as handle:
        handle.write(CONCURRENT.encode() + b"\r\n")
    base = world.functions.read_bytes()

    gen_uw.land()                                   # "ours": a fresh land on top
    ours = world.functions.read_bytes()
    theirs = base + b"?other@@YAXXZ,,0x00AB0000,16,Code/other.cpp,matched,\r\n"

    paths = {}
    for name, raw in (("base", base), ("ours", ours), ("theirs", theirs)):
        paths[name] = tmp_path / f"merge_{name}.csv"
        paths[name].write_bytes(raw)
    merged = subprocess.run(
        ["git", "merge-file", "--union", "-p",
         str(paths["ours"]), str(paths["base"]), str(paths["theirs"])],
        capture_output=True, check=True).stdout.decode()
    lines = [line for line in merged.splitlines() if line.strip()]
    duplicates = {line for line in lines if lines.count(line) > 1}

    assert not duplicates, (
        "the union driver kept two copies of %d row(s) the rewrite relocated: %s"
        % (len(duplicates), sorted(duplicates)[:3]))


def test_a_tombstoned_name_is_renamed_around_never_resurrected(tmp_path, monkeypatch):
    """A tombstone retires a NAME at an address, not the bytes at it.

    0x00BFD6F0's tombstone is a verdict on a GameState.cpp row whose compiler
    label renumbered, which says nothing about a funclet the gate byte-proves
    from a generated TU. Re-using the retired name would leave deleted_rows.csv
    unable to say which row it retired, so the claim takes the next name.
    """
    world = World(tmp_path, monkeypatch)
    world.deleted.write_text(
        DELETED_HEADER + f"\nuw_{RVA:08x},0x{RVA:08X},the earlier row's object symbol "
        "renumbered and no label in that object reproduces retail\n", encoding="utf-8")

    gen_uw.land()

    rows = world.rows
    assert f"uw_{RVA:08x}_r2,,0x{RVA:08X}," in rows
    assert f"\nuw_{RVA:08x},,0x{RVA:08X}," not in rows, "the retired name stays retired"


def test_a_dropped_owned_row_is_tombstoned(tmp_path, monkeypatch):
    """The rewrite silently un-writes any owned row the fresh compile no longer
    produces. functions.csv union-merges, so an un-written row with no tombstone
    comes back on the next rebase from an older fork."""
    gone = (f"uw_00bf9000,,0x00BF9000,8,{OWNED_SOURCE},matched,"
            f"{gen_uw.ROW_NOTES}$L4242")
    world = World(tmp_path, monkeypatch, owned=[gone])

    gen_uw.land()

    assert "uw_00bf9000" not in world.rows, "the stale owned row is rewritten away"
    assert "uw_00bf9000,0x00BF9000," in world.tombstones, (
        "a row this generator stops emitting must be tombstoned, or the union "
        "merge driver resurrects it")


def test_an_exact_gen_dump_row_is_superseded_and_tombstoned(tmp_path, monkeypatch):
    """A dump is retail's bytes under a synthetic name. The funclet body that
    reproduces those bytes supersedes it in the same transaction."""
    world = World(tmp_path, monkeypatch, rows=[DUMP])

    gen_uw.land()

    assert "?d_00bf0000@@YAXXZ" not in world.rows, "the dump row must be retracted"
    assert f"uw_{RVA:08x}" in world.rows
    tombstone = world.tombstones
    assert f"?d_00bf0000@@YAXXZ,0x{RVA:08X}," in tombstone
    assert f"uw_{RVA:08x}" in tombstone, "the tombstone names its successor"


def test_a_red_gate_restores_the_superseded_dump_row_and_its_tombstone(
        tmp_path, monkeypatch):
    world = World(tmp_path, monkeypatch, rows=[DUMP], gate=1)
    before = world.snapshot()

    with pytest.raises(SystemExit):
        gen_uw.land()

    assert world.snapshot() == before, (
        "the tombstone is the dangerous half: deleted_rows.csv is append-only, so "
        "a guard that opens at the gate strands it against a reverted functions.csv")


def test_a_failure_between_the_two_ledger_writes_restores_functions_csv(
        tmp_path, monkeypatch):
    """symbols.csv is asked for its terminator only after functions.csv has been
    rewritten, and a mixed file makes that question fatal. Nothing about the
    funclets is wrong; the guard has to be open already."""
    world = World(tmp_path, monkeypatch)
    world.symbols.write_bytes(world.symbols.read_bytes() + b"??1Mixed@@QAE@XZ,0x0000AAAA,\n")
    before = world.snapshot()

    with pytest.raises(SystemExit):
        gen_uw.land()

    assert world.snapshot() == before, (
        "functions.csv was rewritten before symbols.csv was even asked its "
        "terminator; the snapshot must cover both")


def test_the_ledger_lock_is_held_across_the_whole_transaction(tmp_path, monkeypatch):
    """add_match.py and gen_small.land_batch take reverse/.add_match.lock. Without
    it a concurrent single-row append interleaves with the rewrite, and the revert
    clobbers whatever it landed."""
    fcntl = pytest.importorskip("fcntl")
    world = World(tmp_path, monkeypatch)
    held = []

    def probe(command, label):
        with (tmp_path / ".add_match.lock").open("a") as rival:
            try:
                fcntl.flock(rival, fcntl.LOCK_EX | fcntl.LOCK_NB)
            except OSError:
                held.append(label)
                return 0
        held.append(None)
        return 0

    monkeypatch.setattr(gen_uw, "run", probe, raising=False)
    gen_uw.land()

    assert held and all(call is not None for call in held), (
        "reverse/.add_match.lock must be held while the gate runs")
