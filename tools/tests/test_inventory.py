"""Guards for targets/game/reverse/ghidra_functions.csv, which nothing else validates.

check_csv covers functions.csv and symbols.csv only, so the inventory every
queue tool reads for sizes and anonymity has had no shape check at all. These
assert it directly, and that the call-derived starts landed in it stayed
derivable from the retail image rather than becoming a hand-maintained list.

The game-end closure baseline lives here too: `callers_of.py --closure` walks
that same inventory, and its per-tier figures may only move toward source and
identity.
"""
import csv
import importlib.util
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
ROOT = TOOLS.parent
INVENTORY = ROOT / "targets/game/reverse" / "ghidra_functions.csv"
IMAGE_BASE = 0x400000


def _load(name):
    # Reuse a module another test file already imported. Re-executing build.py
    # into sys.modules split its identity: next_work kept the old object while
    # test_next_work_finish patched the new one, so its fixture ledger was
    # ignored and the real ledger leaked in whenever this file ran first.
    if name in sys.modules:
        return sys.modules[name]
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")


def test_inventory_rows_are_well_formed():
    with INVENTORY.open("r", encoding="utf-8", newline="") as handle:
        reader = csv.DictReader(handle)
        assert reader.fieldnames == ["rva", "size", "name"], reader.fieldnames
        rows = list(reader)
    sections = build.pe_sections(build.EXE.read_bytes())
    text = next(section for section in sections if section["name"] == ".text")
    low, high = text["rva"], text["rva"] + text["size"]

    previous = -1
    seen = set()
    for row in rows:
        rva = int(row["rva"], 16)
        size = int(row["size"])
        assert row["rva"] == f"0x{rva:X}", f"non-canonical rva {row['rva']!r}"
        assert size > 0, f"0x{rva:X}: {size}-byte function"
        assert low <= rva and rva + size <= high, f"0x{rva:X}+{size} leaves .text"
        assert rva not in seen, f"0x{rva:X} appears twice"
        assert rva > previous, f"0x{rva:X} is out of order"
        assert row["name"], f"0x{rva:X}: empty name"
        if row["name"].startswith("FUN_"):
            assert row["name"] == f"FUN_{rva + IMAGE_BASE:08x}", (
                f"0x{rva:X}: anonymous name {row['name']} does not spell its own "
                f"address, so it is not the placeholder it claims to be")
        seen.add(rva)
        previous = rva
    print(f"PASS inventory: {len(rows):,} rows well-formed, sorted and unique")


def test_a_jmp_leaving_text_is_not_an_incremental_link_thunk():
    """The bound on the displacement is what tells a thunk from a coincidence.

    0xA5E88E begins with 0xE9 and is not a thunk: it is the tail of a `mov`
    immediate inside a d3dx9 body, reached only because the linear decode read
    the 0xE8 of `89 65 e8` (mov [ebp-0x18], esp) as a call opcode. Following it
    unbounded yields RVA -0x2AD9506D, which is in no section at all, and that
    address passed every unknown/unclaimed filter and crashed the boundary scan.
    Junk targets are the decode working as designed; each one has to reach
    is_boundary to be rejected, so resolving one must never raise.
    """
    data, sections = build.exe_image()
    text = next(section for section in sections if section["name"] == ".text")
    low, high = text["rva"], text["rva"] + text["size"]

    assert data[build.rva_to_file_offset(sections, 0xA5E88E)] == 0xE9
    assert build.follow_thunk(data, sections, 0xA5E88E, low, high) == 0xA5E88E
    body, thunks = next(iter(build.build_call_thunks().items()))
    assert build.follow_thunk(data, sections, thunks[0], low, high) == body
    print("PASS a jmp whose displacement leaves .text stays its own address")


def test_call_derived_starts_stay_derivable():
    """Re-deriving must find nothing new: every start it can prove is landed.

    This is what stops the inventory drifting into a hand-edited list. A row
    deleted from it, or a predicate loosened into inventing starts, both show up
    here as a non-zero count.

    Ledger growth does not decay this. New byte-verified bodies contribute call
    sites, and the derivation is over the retail image, so a body landing can
    only ever prove a start that genuinely belongs in the inventory -- in which
    case the fix is to land it, not to relax the assertion.
    """
    proc = subprocess.run(
        [sys.executable, str(TOOLS / "new_starts.py")],
        cwd=ROOT, capture_output=True, text=True, check=False)
    assert proc.returncode == 0, (
        f"new_starts.py failed (rc {proc.returncode}) -- the derivation has to "
        f"survive every ledger state, junk call targets included:\n{proc.stderr}")
    assert "landing 0 row(s)" in proc.stdout, (
        "the retail image proves a function start the inventory does not have; "
        "run `python3 tools/new_starts.py --apply` and commit the inventory\n"
        + proc.stdout)
    print("PASS call-derived starts: re-derivation is idempotent")


CLOSURE_SEEDS = "targets/game/reverse/game_end/seeds.json"
# `callers_of.py --closure` per (group, tier), regenerated for every cell in
# Phase 2 when the E_leave vcall seed moved from 0x012F76F0 to the live
# TheNetwork global 0x012F7714 (the old global matched no call site) and again
# in Phase 3 when the A/B/C/D tier 0-1 identity pack landed:
# (functions, bytes) in each ledger state and on each side of identity. The
# regressing columns may only fall and the improving ones only rise, so landing
# a conversion or a pin inside the game-end region is what moves a figure here,
# and a lost row or a broken thunk walk is what turns one red.
#
# REBASED 2026-08-29 after ~250 conversions landed inside the game-end closure.
# 56 figures moved: 55 the right way, 1 the wrong way, and the one is recorded
# here rather than swallowed by the rebase --
#
#     ("A_victory", 2) UNCLAIMED (42, 30585) -> (41, 30847)
#
# The COUNT fell by one and the BYTES rose by 262. The closure grew to 1005
# functions over the same period, so converting callers pulled newly-reachable
# unclaimed ground into the tier faster than the tier retired it. Every other
# UNCLAIMED cell fell, ASM fell everywhere, and CPP and identified rose
# everywhere. Re-arming from the better position is right; leaving the suite red
# for a fortnight, which is what actually happened, is not.
#
# If that cell rises again WITHOUT the closure growing, that is a real
# regression and not this.
#
# REBASED 2026-09-26 after the layout reorganisation (904cff16ec) and admiraly's
# two gen_asm carving commits (8c9b7ea723: 239 carved bodies, 290cb61bb2: 71
# int3-delimited bodies) gave the census proven starts it used to skip. Over the
# whole closure identified rose 1,923 -> 2,496 functions and anonymous fell
# 763 -> 206; UNCLAIMED fell 92 -> 5. Three figures moved the wrong way and are
# recorded rather than swallowed --
#
#     ("C_results", 0) anonymous  (0, 0)      -> (1, 2868)    0x00578160 newly bounded
#     ("C_results", 0) identified (25, 33106) -> (24, 30314)  one identified body moved to tier 1
#     ("C_results", 1) anonymous  (0, 0)      -> (3, 3970)    0x0055B200 / 0x0055A240 / an STL helper
#
# No name was lost: none of the three bodies ever carried a real pin (only
# ?b_ gen-thunk pins); they were outside the census until their starts were
# proven. Every other cell is re-armed at its current, better, figure.
CLOSURE_BASELINE = {
    ("A_victory", 0): {
        "UNCLAIMED": (0, 0), "ASM": (2, 1349), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (6, 1383), "identified": (8, 2732), "anonymous": (0, 0)},
    ("A_victory", 1): {
        "UNCLAIMED": (1, 4125), "ASM": (13, 19431), "SMALL": (1, 8), "LIB": (7, 595),
        "CPP": (46, 5583), "identified": (67, 29737), "anonymous": (1, 5)},
    ("A_victory", 2): {
        "UNCLAIMED": (2, 425), "ASM": (129, 109856), "SMALL": (44, 3984), "LIB": (71, 11394),
        "CPP": (760, 114122), "identified": (891, 183928), "anonymous": (115, 55853)},
    ("B_script", 0): {
        "UNCLAIMED": (0, 0), "ASM": (0, 0), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (5, 19920), "identified": (5, 19920), "anonymous": (0, 0)},
    ("B_script", 1): {
        "UNCLAIMED": (0, 0), "ASM": (2, 39766), "SMALL": (0, 0), "LIB": (1, 59),
        "CPP": (3, 194), "identified": (5, 39853), "anonymous": (1, 166)},
    ("B_script", 2): {
        "UNCLAIMED": (0, 0), "ASM": (1, 320), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (10, 489), "identified": (10, 489), "anonymous": (1, 320)},
    ("C_results", 0): {
        "UNCLAIMED": (0, 0), "ASM": (4, 8147), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (21, 25035), "identified": (24, 30314), "anonymous": (1, 2868)},
    ("C_results", 1): {
        "UNCLAIMED": (0, 0), "ASM": (20, 24502), "SMALL": (5, 338), "LIB": (17, 1968),
        "CPP": (138, 37741), "identified": (177, 60579), "anonymous": (3, 3970)},
    ("C_results", 2): {
        "UNCLAIMED": (0, 0), "ASM": (34, 44696), "SMALL": (26, 3360), "LIB": (56, 7673),
        "CPP": (254, 45236), "identified": (341, 81426), "anonymous": (29, 19539)},
    ("D_desync", 0): {
        "UNCLAIMED": (0, 0), "ASM": (0, 0), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (2, 861), "identified": (2, 861), "anonymous": (0, 0)},
    ("D_desync", 1): {
        "UNCLAIMED": (0, 0), "ASM": (1, 1473), "SMALL": (1, 8), "LIB": (0, 0),
        "CPP": (10, 1223), "identified": (10, 2683), "anonymous": (2, 21)},
    ("D_desync", 2): {
        "UNCLAIMED": (0, 0), "ASM": (2, 269), "SMALL": (10, 1074), "LIB": (1, 31),
        "CPP": (26, 2424), "identified": (33, 3108), "anonymous": (6, 690)},
    ("E_leave", 0): {
        "UNCLAIMED": (0, 0), "ASM": (6, 3310), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (37, 9208), "identified": (43, 12518), "anonymous": (0, 0)},
    ("E_leave", 1): {
        "UNCLAIMED": (0, 0), "ASM": (12, 7088), "SMALL": (1, 4), "LIB": (1, 58),
        "CPP": (196, 23116), "identified": (210, 30266), "anonymous": (0, 0)},
    ("E_leave", 2): {
        "UNCLAIMED": (2, 1495), "ASM": (28, 31761), "SMALL": (22, 3243), "LIB": (24, 5973),
        "CPP": (467, 72075), "identified": (509, 95113), "anonymous": (34, 19434)},
    ("F_engine_quit", 0): {
        "UNCLAIMED": (0, 0), "ASM": (2, 11837), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (4, 1633), "identified": (6, 13470), "anonymous": (0, 0)},
    ("F_engine_quit", 1): {
        "UNCLAIMED": (0, 0), "ASM": (16, 10640), "SMALL": (1, 3), "LIB": (5, 214),
        "CPP": (146, 22952), "identified": (155, 25640), "anonymous": (13, 8169)},
}

REGRESSING = ("UNCLAIMED", "ASM", "SMALL", "anonymous")
IMPROVING = ("CPP", "identified")


def _closure_table(stdout):
    lines = stdout.splitlines()
    columns = lines[0].split()[4:]
    table = {}
    for line in lines[1:]:
        fields = line.split()
        if fields[0] != "TOTAL":
            table[(fields[0], int(fields[1]))] = {
                column: tuple(int(v) for v in cell.split("/"))
                for column, cell in zip(columns, fields[4:])}
    return table


def test_game_end_closure_coverage_never_regresses():
    proc = subprocess.run(
        [sys.executable, str(TOOLS / "callers_of.py"), "--closure", CLOSURE_SEEDS],
        cwd=ROOT, capture_output=True, text=True, check=False)
    assert proc.returncode == 0, (
        f"callers_of.py --closure failed (rc {proc.returncode}):\n{proc.stderr}")
    table = _closure_table(proc.stdout)
    zero = {column: (0, 0) for column in REGRESSING + IMPROVING}
    moved = []
    for key in sorted(set(CLOSURE_BASELINE) | set(table)):
        base = CLOSURE_BASELINE.get(key, zero)
        now = table.get(key, zero)
        for column in REGRESSING:
            if now[column][0] > base[column][0] or now[column][1] > base[column][1]:
                moved.append(f"{key}: {column} rose to {now[column]} from {base[column]}")
        for column in IMPROVING:
            if now[column][0] < base[column][0] or now[column][1] < base[column][1]:
                moved.append(f"{key}: {column} fell to {now[column]} from {base[column]}")
    assert not moved, "\n".join(moved) + "\n\n" + proc.stdout
    print("PASS game-end closure: no state or identity figure moved the wrong way")


CLAIMS = ROOT / "targets/game/reverse" / "game_end" / "claims.csv"
# Address facts the game-end identity packs rest on, each checked against the
# retail image. Address/expected per kind: bytes 0xRVA/hex; insn 0xRVA/capstone
# text; vslot 0xVTABLEVA+0xOFF/body RVA after the thunk chain; jt
# 0xTABLEVA[idx]/the entry RVA; thunk ILT RVA/body RVA; global VA/RVA of an
# instruction whose immediate or displacement carries that VA; string VA/the
# exact C string NUL-terminated at that VA (the one kind compared case-sensitively);
# patch 0xRVA/`<original hex>-><replacement hex>|<post-patch capstone text>`, a
# byte-patch candidate: this test checks retail still holds the original bytes,
# test_game_end_patch_rows_apply_to_a_copy applies the replacement to a copy.


def _claim_observed(kind, address, expected, image, md):
    """What retail holds where a claims.csv row says `expected` is."""
    from capstone.x86 import X86_OP_IMM, X86_OP_MEM
    data, sections, low, high = image

    def offset(rva):
        assert rva != 0, "a claim at RVA 0 is a typo, not a fact: refusing to read address zero"
        return build.rva_to_file_offset(sections, rva)

    def follow(rva):
        for _ in range(4):
            body = build.follow_thunk(data, sections, rva, low, high)
            if body == rva:
                break
            rva = body
        return rva

    def insn(rva):
        decoded = next(md.disasm(data[offset(rva):offset(rva) + 16], IMAGE_BASE + rva), None)
        assert decoded is not None, f"nothing decodes at 0x{rva:08X}"
        return decoded

    if kind == "bytes":
        start = offset(int(address, 16))
        return data[start:start + len(expected) // 2].hex()
    if kind == "insn":
        decoded = insn(int(address, 16))
        return f"{decoded.mnemonic} {decoded.op_str}".strip()
    if kind == "thunk":
        return f"0x{follow(int(address, 16)):08X}"
    if kind in ("vslot", "jt"):
        match = re.fullmatch(r"(0x[0-9A-Fa-f]+)(?:\+(0x[0-9A-Fa-f]+)|\[(\d+)\])", address)
        assert match, f"malformed {kind} address {address!r}"
        table, off, index = match.groups()
        va = int(table, 16) + (int(off, 16) if off else 4 * int(index))
        entry = struct.unpack_from("<I", data, offset(va - IMAGE_BASE))[0] - IMAGE_BASE
        return f"0x{(follow(entry) if kind == 'vslot' else entry):08X}"
    if kind == "global":
        decoded = insn(int(expected, 16))
        carried = {(op.imm if op.type == X86_OP_IMM else op.mem.disp) & 0xFFFFFFFF
                   for op in decoded.operands if op.type in (X86_OP_IMM, X86_OP_MEM)}
        if int(address, 16) in carried:
            return expected
        return f"0x{int(expected, 16):08X} carries " + ",".join(f"0x{v:08X}" for v in sorted(carried))
    if kind == "string":
        # one byte past the expected length: a longer retail string has no NUL there
        start = offset(int(address, 16) - IMAGE_BASE)
        chunk = data[start:start + len(expected) + 1]
        end = chunk.find(b"\0")
        return (chunk if end < 0 else chunk[:end]).decode("latin-1")
    if kind == "patch":
        original = expected.split("->", 1)[0]
        start = offset(int(address, 16))
        held = data[start:start + len(original) // 2].hex()
        if held == original.lower():
            return expected
        return f"original bytes at 0x{int(address, 16):08X} are {held}"
    raise AssertionError(f"unknown claim kind {kind!r}")


def test_game_end_claims_hold_against_retail():
    try:
        import capstone
    except ImportError:
        raise SystemExit("capstone is missing (pip install capstone): the game-end claims "
                         "cannot be checked without a disassembler, and skipping them "
                         "silently would leave every address fact unverified")
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    data, sections = build.exe_image()
    text = next(section for section in sections if section["name"] == ".text")
    image = (data, sections, text["rva"], text["rva"] + text["size"])
    with CLAIMS.open("r", encoding="utf-8", newline="") as handle:
        rows = list(csv.DictReader(handle))
    # 796 rows landed with Phase 2 and 1000+ with Phase 3: a count under the
    # floor means rows were lost, not that the floor is wrong.
    assert len(rows) >= 1800, f"{CLAIMS}: only {len(rows)} rows"
    wrong = []
    for row in rows:
        observed = _claim_observed(row["kind"], row["address"], row["expected"], image, md)
        expected = row["expected"] if row["kind"] == "string" else row["expected"].lower()
        if (observed if row["kind"] == "string" else observed.lower()) != expected:
            wrong.append(f"{row['kind']},{row['address']},{row['expected']} ({row['note']}): "
                         f"observed {observed}")
    assert not wrong, f"{len(wrong)} claim(s) do not hold against retail:\n" + "\n".join(wrong)
    print(f"PASS game-end claims: {len(rows)} rows hold against retail")


FINDINGS = ROOT / "targets/game/reverse" / "game_end" / "FINDINGS.md"
# 6-8 hex digits: RVAs and VAs. Offsets (+0x484) and immediates (0x7530) are
# shorter and are not addresses.
ADDRESS_LITERAL = re.compile(r"\b0x([0-9A-Fa-f]{6,8})\b")


def _ledgered_addresses():
    """Every address some machine-checked file vouches for, as integers: a
    claims.csv address or expected value, a functions.csv target/export RVA, or
    a symbols.csv pin."""
    known = set()
    with CLAIMS.open("r", encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            for field in (row["address"], row["expected"]):
                known.update(int(m.group(1), 16) for m in ADDRESS_LITERAL.finditer(field))
    for path, columns in ((build.FUNCTIONS, ("target_rva", "export_rva")),
                          (build.SYMBOLS, ("address",))):
        with path.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                for column in columns:
                    if row[column].startswith("0x"):
                        known.add(int(row[column], 16))
    return known


def test_game_end_findings_cite_only_ledgered_addresses():
    text = FINDINGS.read_text(encoding="utf-8")
    cited = {}
    for match in ADDRESS_LITERAL.finditer(text):
        cited.setdefault(int(match.group(1), 16), match.group(0))
    assert cited, f"{FINDINGS}: no addresses at all"
    known = _ledgered_addresses()
    unknown = sorted(literal for value, literal in cited.items() if value not in known)
    assert not unknown, (f"{len(unknown)} address(es) in {FINDINGS.name} have no claims/"
                         f"functions/symbols row: " + ", ".join(unknown))
    print(f"PASS game-end findings: {len(cited)} cited addresses are ledgered")


PATCH_SCRATCH = build.PATCH_DIR / "lotrbfme.game_end_patch_check.exe"


def test_game_end_patch_rows_apply_to_a_copy():
    """Each `patch` claim is applied to a fresh copy of the baseline under
    build/: the site must then decode to the expected instruction, the
    instruction must span exactly the patched bytes, and the copy must differ
    from the baseline nowhere else. The baseline is only ever read
    (shutil.copyfile reads it; build.verify_baseline re-hashes it afterwards)."""
    try:
        import capstone
    except ImportError:
        raise SystemExit("capstone is missing (pip install capstone): a patch row cannot be "
                         "proven to decode to its expected instruction without it")
    with CLAIMS.open("r", encoding="utf-8", newline="") as handle:
        rows = [row for row in csv.DictReader(handle) if row["kind"] == "patch"]
    assert rows, "no patch rows in claims.csv: the quit-freeze candidates were lost"
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    baseline, sections = build.exe_image()
    build.PATCH_DIR.mkdir(parents=True, exist_ok=True)
    try:
        for row in rows:
            rva = int(row["address"], 16)
            assert rva != 0, "a patch at RVA 0 is a typo: refusing to touch address zero"
            spec, text = row["expected"].split("|", 1)
            original, replacement = (bytes.fromhex(part) for part in spec.split("->", 1))
            assert len(original) == len(replacement), f"{row['address']}: patch changes the length"
            assert original != replacement, f"{row['address']}: the replacement equals the original"
            start = build.rva_to_file_offset(sections, rva)
            end = start + len(original)
            assert baseline[start:end] == original, (
                f"{row['address']}: retail holds {baseline[start:end].hex()}, not {original.hex()}")
            shutil.copyfile(build.EXE, PATCH_SCRATCH)
            with PATCH_SCRATCH.open("r+b") as handle:
                handle.seek(start)
                handle.write(replacement)
            patched = PATCH_SCRATCH.read_bytes()
            decoded = next(md.disasm(patched[start:start + 16], IMAGE_BASE + rva), None)
            assert decoded is not None, f"{row['address']}: nothing decodes after the patch"
            got = f"{decoded.mnemonic} {decoded.op_str}".strip()
            assert got == text, f"{row['address']}: patched site decodes to {got!r}, expected {text!r}"
            assert decoded.size == len(replacement), (
                f"{row['address']}: the patched instruction is {decoded.size} B, "
                f"the patch {len(replacement)} B")
            assert patched[start:end] == replacement
            assert len(patched) == len(baseline) and patched[:start] == baseline[:start] \
                and patched[end:] == baseline[end:], (
                f"{row['address']}: the copy differs from the baseline outside the patched bytes")
    finally:
        if PATCH_SCRATCH.exists():
            PATCH_SCRATCH.unlink()
    build.verify_baseline()
    print(f"PASS game-end patches: {len(rows)} row(s) apply to a copy and decode as claimed")
