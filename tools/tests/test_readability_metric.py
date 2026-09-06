"""The seven readability axes, the per-blob cache, and the --staged commit trailer.

The tree here is small enough to count by hand, and every expected number below
is written as the arithmetic that produced it rather than as a magic constant, so
a changed axis definition fails with a readable diff instead of an opaque one.

Two properties get their own tests because nothing else would catch them:

  * the cache is keyed by git blob hash and an entry found under any other hash
    is recomputed, never served -- a metric that silently reports last week's
    counters for an edited file is worse than no metric;
  * --staged measures the INDEX against HEAD, not the worktree. It is the number
    that goes into a commit message, so a worktree edit the commit does not carry
    must not move it;
  * --staged names only the axes whose delta survives the rounding it prints at.
    Dropping one file shifts every denominator, and axes rendered "-0.00 pp"
    make a commit that moved one axis read as one that moved four.

The fixture ledger deliberately mixes \\r\\r\\n, \\r\\n and bare \\n terminators.
functions.csv does the same (tools/ledger_io.py:1-14) and every naive split has
silently dropped or invented rows there; here a naive split would move Ident and
Local off their hand-computed values.
"""
import builtins
import importlib.util
import json
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


metric = _load("readability_metric")

AREA = "Code/GameEngine/Source/Common"

# 7 lines. One pad member, one named member, two virtual slots of which v12 is
# anonymous, and one class body that does NOT count against SSoT: it is in a
# header, which is where a shared type belongs.
ALPHA_H = """class Alpha {
        virtual void Draw();
        virtual void v12();

        char pad[8];
        int m_count;
};
"""

# The same 7 lines with the 8-byte pad split into two named 4-byte fields. Line
# count is deliberately unchanged -- the blank line the pad was separated by is
# what the second field takes -- so this edit moves Types and nothing else.
SPLIT_H = """class Alpha {
        virtual void Draw();
        virtual void v12();
        int m_left;
        int m_right;
        int m_count;
};
"""

# 12 lines, two of them raw assembly, one pad member, one named member, and one
# class body opened inside a TU -- the shim shape the SSoT axis counts.
ALPHA_CPP = """#include "alpha.h"

struct LocalPatch {
        char pad[8];
        int m_flag;
};

void Alpha::Draw()
{
        __asm { nop }
        __emit 0x90
}
"""

# 6 lines and nothing any axis counts except its line total and its .cpp-ness.
GAMMA_CPP = """#include "alpha.h"

void Alpha::Reset()
{
        m_flag = 0;
}
"""

# 5 lines that no axis counts but every denominator does -- padding for the one
# test that needs a tree big enough for a dropped file to shift the denominators
# by less than the trailer's printed precision.
FILLER = """#include "alpha.h"

void filler{n}(void)
{{
}}
"""

LEDGER_PATH = "reverse/functions.csv"


def ledger(reset_lives_in=f"{AREA}/gamma.cpp"):
    """The fixture ledger, with Reset's owning file as the one knob. Repointing
    it at alpha.cpp is a merge: gamma.cpp stops being a one-function file."""
    return b"".join(payload + terminator for payload, terminator in (
        (b"name,export_rva,target_rva,target_size,source,status,notes", b"\r\n"),
        (f"?d_00401000@@YAXXZ,,0x00401000,16,{AREA}/alpha.cpp,matched,".encode(), b"\r\r\n"),
        (f"?Draw@Alpha@@UAEXXZ,,0x00401020,16,{AREA}/alpha.cpp,matched,".encode(), b"\n"),
        (f"?Init@Alpha@@QAEXXZ,,0x00401040,16,{AREA}/alpha.cpp,matched,".encode(), b"\r\n"),
        (f"?Reset@Alpha@@QAEXXZ,,0x00401060,16,{reset_lives_in},matched,".encode(), b"\r\r\n"),
    ))


LEDGER = ledger()

# Hand-computed over the three sources above. `lines` counts split("\n") pieces,
# so a file of N newline-terminated lines contributes N + 1: 8 + 13 + 7 = 28.
BODY = 100.0 * (1 - 2 / 28)     # 2 __asm/__emit lines out of 28
IDENT = 100.0 * (1 - 1 / 4)     # 1 of 4 ledger names is address-derived
TYPES = 100.0 * (1 - 2 / 4)     # 2 char pad[N] against 2 m_ fields
IFACE = 100.0 * (1 - 1 / 2)     # v12 of {Draw, v12} is an anonymous slot
LOCAL = 100.0 * (1 - 1 / 2)     # gamma.cpp holds 1 of the 2 files' only function
SSOT = 100.0 * (1 - 1 / 3)      # 1 TU-local class body against 2 .cpp files
SRCIDENT = 100.0                # neither .cpp invents an address-derived token
EXPECTED = (BODY, IDENT, TYPES, IFACE, LOCAL, SSOT, SRCIDENT)

SPLIT_TYPES = 100.0 * (1 - 1 / 5)   # 1 char pad[N] against 4 m_ fields
TRAILER = "readability: Types 50.0 -> 80.0 (+30.00 pp), files +0\n"


def world(tmp_path, header=ALPHA_H, fillers=0):
    """A tracked fixture tree. git ls-files/hash-object drive the tool, so the
    sources have to be in an index, not merely on disk."""
    root = (tmp_path / "repo").resolve()
    (root / AREA).mkdir(parents=True)
    (root / "reverse").mkdir()
    (root / AREA / "alpha.h").write_text(header)
    (root / AREA / "alpha.cpp").write_text(ALPHA_CPP)
    (root / AREA / "gamma.cpp").write_text(GAMMA_CPP)
    for n in range(fillers):
        (root / AREA / f"filler{n}.cpp").write_text(FILLER.format(n=n))
    (root / LEDGER_PATH).write_bytes(LEDGER)
    subprocess.run(["git", "init", "-q", str(root)], check=True)
    stage(root, "Code", "reverse")
    return root


def stage(root, *paths):
    subprocess.run(["git", "-C", str(root), "add", "--", *paths], check=True)


def commit(root):
    subprocess.run(["git", "-C", str(root), "-c", "user.email=fixture@example.com",
                    "-c", "user.name=Fixture", "commit", "-q", "-m", "fixture"],
                   check=True)


def blob_of(root, path):
    return subprocess.run(["git", "-C", str(root), "hash-object", "--", path],
                          capture_output=True, text=True, check=True).stdout.strip()


def measure(root):
    """The seven whole-tree axes, leaving the cache on disk as a real run would."""
    cache = metric.Cache(root)
    areas, _tracked = metric.measure_worktree(root, cache)
    cache.save()
    return metric.axes(metric.totals(areas))


def cli(root, *args):
    return subprocess.run([sys.executable, str(TOOLS / "readability_metric.py"),
                           "--root", str(root), *args], capture_output=True, text=True)


def test_every_axis_over_a_hand_computed_tree(tmp_path):
    assert measure(world(tmp_path)) == pytest.approx(EXPECTED)


def test_a_cache_entry_under_another_hash_is_recomputed_never_served(tmp_path):
    root = world(tmp_path)
    assert measure(root) == pytest.approx(EXPECTED)

    counts = root / "build" / "readability" / "counts.json"
    header_blob = blob_of(root, f"{AREA}/alpha.h")
    stored = json.loads(counts.read_text())
    assert header_blob in stored["files"]
    # Re-file the header's counters under a hash that is not the header's, and
    # make them absurd: a lookup that ignores the hash would report them.
    stored["files"].pop(header_blob)
    stored["files"]["0" * 40] = dict.fromkeys(metric.scan(ALPHA_H), 999)
    counts.write_text(json.dumps(stored))
    assert measure(root) == pytest.approx(EXPECTED)

    # Same rule the other way round: the entry for the pre-edit content survives
    # in the cache and must not be served for the edited file.
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    assert measure(root)[2] == pytest.approx(SPLIT_TYPES)
    assert header_blob in json.loads(counts.read_text())["files"]


@pytest.mark.skipif(os.geteuid() == 0, reason="root reads through chmod 000")
def test_an_unreadable_source_aborts_instead_of_totalling_the_rest(tmp_path):
    root = world(tmp_path)
    blocked = root / AREA / "alpha.cpp"
    blocked.chmod(0o000)
    done = cli(root)
    assert done.returncode != 0
    assert str(blocked) in done.stderr
    assert "ALL Code/" not in done.stdout


def test_a_warm_run_opens_no_file_it_already_has_counters_for(tmp_path, capsys,
                                                              monkeypatch):
    root = world(tmp_path)
    metric.main(["--root", str(root)])
    first = capsys.readouterr().out

    real_open = builtins.open

    def guarded(file, *args, **kwargs):
        target = Path(file).resolve()
        if target.is_relative_to(root) and not target.is_relative_to(root / "build"):
            raise AssertionError(f"warm run opened {target}")
        return real_open(file, *args, **kwargs)

    monkeypatch.setattr(builtins, "open", guarded)
    metric.main(["--root", str(root)])
    assert capsys.readouterr().out == first


def test_splitting_a_pad_moves_types_and_leaves_the_other_five(tmp_path):
    root = world(tmp_path)
    before = measure(root)
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    after = measure(root)
    assert after[2] == pytest.approx(SPLIT_TYPES)
    assert before[2] == pytest.approx(TYPES)
    assert after[:2] + after[3:] == pytest.approx(before[:2] + before[3:])


def test_staged_trailer_names_only_the_axis_that_moved(tmp_path):
    root = world(tmp_path)
    commit(root)
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    stage(root, f"{AREA}/alpha.h")
    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stdout == TRAILER


def test_staged_measures_the_index_not_the_worktree(tmp_path):
    root = world(tmp_path)
    commit(root)
    (root / AREA / "alpha.h").write_text(SPLIT_H)
    stage(root, f"{AREA}/alpha.h")
    (root / AREA / "alpha.h").write_text(
        SPLIT_H.replace("        int m_count;\n",
                        "        int m_count;\n        int m_extra;\n"))

    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stdout == TRAILER
    # ...and the edit really would have moved the number, had the tool read it.
    assert measure(root)[2] == pytest.approx(100.0 * (1 - 1 / 6))


# SSoT is the tightest of the six against a dropped .cpp: its shift is
# 100 / ((F + 2)(F + 3)) points, so F = 200 puts it at 0.0024 -- real, and half
# an order of magnitude under the 0.005 the trailer's 2 decimals can show.
FILLERS = 200


def merged(tmp_path):
    """A merge commit in miniature, staged: Reset's ledger row repointed onto
    alpha.cpp so gamma.cpp stops being a one-function file, and a donor dropped.
    Local moves by 50 points; every other denominator only wobbles."""
    root = world(tmp_path, fillers=FILLERS)
    commit(root)
    (root / LEDGER_PATH).write_bytes(ledger(f"{AREA}/alpha.cpp"))
    subprocess.run(["git", "-C", str(root), "rm", "-q", "--", f"{AREA}/filler0.cpp"],
                   check=True)
    stage(root, LEDGER_PATH)
    return root


def staged_sides(root):
    """The two axis tuples --staged compares: HEAD, then the staged index."""
    cache = metric.Cache(root)
    return (metric.axes(metric.totals(metric.measure_blobs(root, "HEAD", cache))),
            metric.axes(metric.totals(metric.measure_blobs(root, None, cache))))


def test_a_denominator_shift_below_the_printed_precision_is_not_named(tmp_path):
    root = merged(tmp_path)
    head, index = staged_sides(root)
    for axis in (0, 5):   # Body and SSoT really moved -- just below 0.005 points
        assert 0 < abs(index[axis] - head[axis]) < 0.005
    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stdout == "readability: Local 50.0 -> 100.0 (+50.00 pp), files -1\n"


def test_a_commit_that_only_drops_files_still_reports_them(tmp_path):
    root = world(tmp_path, fillers=FILLERS)
    commit(root)
    subprocess.run(["git", "-C", str(root), "rm", "-q", "--", f"{AREA}/filler0.cpp"],
                   check=True)
    assert cli(root, "--staged").stdout == "readability: files -1\n"


def test_a_commit_that_moves_nothing_says_so(tmp_path):
    root = world(tmp_path)
    commit(root)
    assert cli(root, "--staged").stdout == "readability: no measurable change\n"


def test_a_cold_scan_says_so_on_stderr_and_a_warm_one_is_silent(tmp_path):
    """A cold cache scans every source, which is minutes of no output and reads
    as a hang -- a fresh worktree's first run was mistaken for a blocked build
    lock. It gets one stderr line, and only stderr: stdout carries the trailer
    into commit messages and is asserted on elsewhere, so it must not move."""
    root = world(tmp_path, fillers=metric.SCAN_NOTICE_MIN + 5)

    cold = cli(root)
    assert cold.returncode == 0, cold.stderr
    assert "cold cache" in cold.stderr
    assert cold.stderr.count("\n") == 1, f"expected one line, got {cold.stderr!r}"

    warm = cli(root)
    assert warm.returncode == 0, warm.stderr
    assert warm.stderr == ""
    assert warm.stdout == cold.stdout


def test_a_handful_of_changed_files_scans_quietly(tmp_path):
    """The per-commit case must stay silent, or the notice becomes noise on every
    commit and stops meaning anything."""
    root = world(tmp_path, fillers=metric.SCAN_NOTICE_MIN + 5)
    commit(root)
    cli(root)                                   # warm the cache
    (root / AREA / "filler0.cpp").write_text(FILLER.format(n=0) + "\nvoid extra(void)\n{\n}\n")
    stage(root, f"{AREA}/filler0.cpp")

    done = cli(root, "--staged")
    assert done.returncode == 0, done.stderr
    assert done.stderr == ""


def test_a_member_declaration_is_counted_on_its_own_line_only(tmp_path):
    """NAMED_MEMBER's character class used to contain \\s, which matches a newline,
    so the pattern ran from one line across every line below it hunting for an
    `m_`. Two defects fell out of that, and only this test sees either:

      * it counted members the intervening lines had already disqualified -- the
        real case was a blank line, then `private:`, then a member whose trailing
        comment said "pad", which the negative lookahead exists to reject;
      * it made the scan quadratic in file size. One 42 KB source cost 2.3 s, a
        full 12,860-source run never finished inside any timeout anyone gave it,
        and build/readability/ therefore stayed empty -- so every --staged run
        paid a cold scan and the per-commit trailer the plan is built on was
        unusable.
    """
    disqualified = "\nprivate:\n\tchar             m_head[ 0x08 ];\t\t// +0x04 pad\n"
    assert metric.scan(disqualified)["named_members"] == 0

    plain = "\nprivate:\n\tchar m_raw[ 0x14 ];\n"
    assert metric.scan(plain)["named_members"] == 1

    across_lines = "SomeType\n\tm_member;\n"
    assert metric.scan(across_lines)["named_members"] == 0


def test_scanning_stays_linear_in_file_size(tmp_path):
    """The guard for the half of the defect above that is not a wrong number. The
    shape that blew up is many lines whose every character is inside the class
    and which never reach an `m_`, so the star ran to end-of-file and backtracked
    from each of them in turn. The `// readable body of ...` markers this tree is
    full of are exactly that shape. Measured on this fixture: 3.72 s before,
    0.008 s after, and 3x the lines cost the old pattern 10.7x the time."""
    import time

    text = ("readable body of ZZ1AssaultTransportAIUpdate ZZ Code GameEngine "
            "Source path\n") * 900
    start = time.monotonic()
    assert metric.scan(text)["named_members"] == 0
    assert time.monotonic() - start < 1.0


def test_an_address_derived_name_counts_however_it_ends(tmp_path):
    """PLACEHOLDER's `\\b` after the hex run meant an address-derived name counted
    only when nothing followed the digits. `Rva001EFF60` did; `Rva0026C320Owner`
    -- the shape the file names actually use -- did not, so 4,278 rows of
    reverse/functions.csv were scored as semantic names and Ident read 2.65 pp
    higher than the tree deserved. That is the wrong direction for a scoreboard
    to be wrong in: it hid the single largest rename lane from the axis meant to
    measure it.

    The capital is load bearing. re.I is on for the whole pattern, so an
    unqualified [A-Z] would accept any letter and `GenCab` -- three hex digits
    and a letter -- would score a real word as a placeholder. Hence (?-i:[A-Z]),
    and six hex digits before a capital for Gen where Rva needs four.
    """
    for name in ("Rva0026C320Owner", "?Get_Fade@Rva0095B260Anim@@QAEMHM@Z",
                 "?rva00061150Set@@YAHXZ", "Gen0060CBB0Pair", "Rva001EFF60"):
        assert metric.PLACEHOLDER.search(name), name

    for name in ("GenCabbageStore", "Generals", "RvaSomething", "MoveToState",
                 "AttackNugget", "GameLogic"):
        assert not metric.PLACEHOLDER.search(name), name


def test_a_mangling_prefix_does_not_hide_an_address(tmp_path):
    """`??0`, `??1`, `??_G`, `??$` and the type tags `@U`/`@PAV`/`$$CBU` all END in
    a word character, so `\\b` never fires in front of the class name that follows
    and `??0Rva006D51B0@@QAE@II@Z` -- a constructor of an address-named class --
    scored as a real name. 2,982 rows of reverse/functions.csv, Ident 20.72 ->
    18.82. Third defect of this family: the two before it were the wrong RIGHT
    edge of the hex run, and both were also worth pp in the wrong direction.

    tools/rename_addressed_sources.py has carried a comment about this exact case
    since it shipped, and its own refusal test names it -- the blind spot was
    documented in one tool while the other kept scoring through it.
    """
    for name in ("??0Rva006D51B0@@QAE@II@Z", "??1BfmeOwnerBU@@QAE@XZ",
                 "??_GGen_004902A0@@UAEPAXI@Z", "??4Gen_005D1E50@@QAEAAV0@ABV0@@Z",
                 "??$_Construct@URva001954D0@@U1@@_STL@@YAXPAURva001954D0@@ABU1@@Z",
                 "?erase@?$vector@URva004262F0Elem@@@_STL@@QAEPAU2@@Z"):
        assert metric.PLACEHOLDER.search(name), name

    # The left edge only gains positions that mangling glue creates; an ordinary
    # word boundary still governs everything else, so the old refusals hold.
    for name in ("GenCabbageStore", "Generals", "RvaSomething", "MoveToState",
                 "?setPosition@Drawable@@QAEXABVCoord3D@@@Z"):
        assert not metric.PLACEHOLDER.search(name), name


def test_a_pattern_change_is_invisible_without_a_cache_version_bump(tmp_path):
    """The cache stores scan()/scan_ledger() OUTPUT under the blob hash, and a
    blob hash cannot see a change to the code that read it. So an entry written by
    an older version must be discarded wholesale rather than served: without that,
    every fix to a pattern here lands, moves nothing on any tree that has ever run
    the tool, and reads as a fix that did not work."""
    root = world(tmp_path)
    assert measure(root) == pytest.approx(EXPECTED)
    counts = root / "build" / "readability" / "counts.json"

    stored = json.loads(counts.read_text())
    assert stored["version"] == metric.CACHE_VERSION
    # Absurd counters for every file, under the CURRENT version: they are served,
    # which is what proves the next assertion is about the version and not luck.
    poisoned = {sha: dict.fromkeys(entry, 999) for sha, entry in stored["files"].items()}
    counts.write_text(json.dumps({"version": metric.CACHE_VERSION,
                                  "files": poisoned, "ledgers": stored["ledgers"]}))
    assert measure(root) != pytest.approx(EXPECTED)

    counts.write_text(json.dumps({"version": metric.CACHE_VERSION - 1,
                                  "files": poisoned, "ledgers": stored["ledgers"]}))
    assert measure(root) == pytest.approx(EXPECTED)


def test_an_anonymous_slot_is_recognised_by_shape_not_by_vocabulary(tmp_path):
    """ANON_SLOT was a closed list, `(?:v|pad|slot|vf|unk)\\d{1,3}`, matched with
    .fullmatch -- so `v37` was anonymous and `vslot37` was a name. Renaming every
    anonymous slot that way is a sed that changes nothing a reader can see and was
    worth Iface +30.46 pp.

    The list was also already wrong without anyone gaming it: `bfmeSlot0`,
    `unused04`, `reserved113`, `s0` and 40 slots already spelled `vslotNN` are
    14,188 slot occurrences in this tree that it did not count, Iface 69.54 ->
    48.55. A stem plus a bare index carries nothing the index does not.
    """
    for name in ("v37", "vslot37", "unused04", "bfmeSlot0", "reserved113", "s0",
                 "_pad68", "dslot42", "vfn12"):
        assert metric.ANON_SLOT.fullmatch(name), name
    for name in ("Draw", "getPlayerCount", "update", "Set_Transform", "v", "isIdle"):
        assert not metric.ANON_SLOT.fullmatch(name), name


def test_renaming_an_anonymous_slot_family_does_not_move_iface(tmp_path):
    """The gaming edit, staged end to end: the axis must not move."""
    root = world(tmp_path)
    before = measure(root)
    (root / AREA / "alpha.h").write_text(ALPHA_H.replace("void v12()", "void vslot12()"))
    assert measure(root) == pytest.approx(before)


def test_a_pad_member_is_not_also_counted_as_a_named_field(tmp_path):
    """NAMED_MEMBER's lookahead needs a word boundary before `pad`, which `m_pad`
    does not give it, so `unsigned char m_pad[0x38];` matched BOTH patterns and was
    counted in both terms of the Types ratio -- 6,609 of this tree's 10,522 pad
    members, Types 81.28 -> 78.78."""
    counts = metric.scan("struct S {\n\tunsigned char m_pad[0x38];\n\tint m_health;\n};\n")
    assert (counts["pad_members"], counts["named_members"]) == (1, 1)

    # ...and the field that only LOOKS like the vocabulary is still a named field:
    # widening the lookahead instead would have thrown `m_chunkSize` away for the
    # `unk` inside `chunk`.
    counts = metric.scan("struct S {\n\tint m_chunkSize;\n};\n")
    assert (counts["pad_members"], counts["named_members"]) == (0, 1)


def test_srcident_counts_bodies_that_invent_an_address_derived_name(tmp_path):
    """The axis the other six could not see. Between 71d0effcb (22 Aug) and this
    tree Ident rose 14.92 -> 18.82 while SrcIdent fell 80.36 -> 63.06: renaming a
    ledger row moves Ident, and writing `Rva0026C320Owner` into a body moves
    neither Ident nor anything else the audit measured. Both figures come out of
    `--at <rev>`, so neither is a number anyone has to take on trust.

    Headers are excluded for the same reason they are excluded from SSoT: an
    address-derived name in a header is one declaration, not a body written around
    it. So the axis is per .cpp/.c, and one occurrence dirties the file."""
    root = world(tmp_path)
    assert measure(root)[6] == pytest.approx(100.0)

    (root / AREA / "gamma.cpp").write_text(
        GAMMA_CPP.replace("void Alpha::Reset()",
                          "static Rva0026C320Owner *owner;\n\nvoid Alpha::Reset()"))
    assert measure(root)[6] == pytest.approx(50.0)   # 1 of the 2 .cpp is dirty

    # A header carrying the same token does not move it.
    (root / AREA / "alpha.h").write_text(ALPHA_H + "struct Rva0071C0E0Thing;\n")
    assert measure(root)[6] == pytest.approx(50.0)
