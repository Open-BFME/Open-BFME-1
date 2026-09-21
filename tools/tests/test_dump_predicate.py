"""One answer to "is this address still open work?", and a guard that keeps it.

A gen-dump row is retail's own bytes under a synthetic name: it fixes a boundary
and holds no source, so a work finder must treat the ground under it as open
while an over-claim guard must treat it as taken. Three tools decided that for
themselves and all three got it wrong; two of the fixes then keyed on the source
path, which still hides the 349 gen-dump rows that live in
Code/gen_small/dumps_000.cpp rather than Code/gen_asm/.

build.is_scaffold_row is the predicate and build.load_claim_rows serves the two
answers. The guard at the bottom is the point of the exercise: it fails the next
tool that decides dumpness from a path instead.
"""
import csv
import importlib.util
import re
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
GEN_ASM_DUMP = ("?d_00abcd00@@YAXXZ,,0x00ABCD00,32,Code/gen_asm/d_00abcd00.asm,"
                "matched,gen-dump;ghidra=FUN_00eacd00")
# The row both of this week's path-based fixes get wrong: a dump outside gen_asm.
GEN_SMALL_DUMP = ("?d_00abce00@@YAXXZ,,0x00ABCE00,48,Code/gen_small/dumps_000.cpp,"
                  "matched,gen-dump;ghidra=FUN_00eace00")
REAL = ("?realBody@Thing@@QAEXXZ,,0x00ABCF00,64,"
        "Code/GameEngine/Source/Common/Thing.cpp,matched,")
UNMATCHED = ("?hypothesis@Thing@@QAEXXZ,,0x00ABD000,16,"
             "Code/GameEngine/Source/Common/Thing.cpp,unmatched,")

DUMP_RVA = 0x00ABCE00
REAL_RVA = 0x00ABCF00


def _module(name):
    """The live module under `name`, importing it only if nobody loaded it yet.

    Resolved through sys.modules rather than captured at import time on purpose:
    sibling test files re-exec build and next_work under these same names, so a
    module object bound at collection is not the one next_work's own
    `import build` will find at call time, and monkeypatching the wrong copy
    passes vacuously.
    """
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


@pytest.fixture
def build(tmp_path, monkeypatch):
    """build.py reading a scratch ledger: gen_asm dump, gen_small dump, real, unmatched."""
    module = _module("build")
    ledger = tmp_path / "functions.csv"
    ledger.write_text(
        HEADER + "\r\n" + "".join(row + "\r\n" for row in
                                  (GEN_ASM_DUMP, GEN_SMALL_DUMP, REAL, UNMATCHED)),
        encoding="utf-8")
    monkeypatch.setattr(module, "FUNCTIONS", ledger)
    return module


def rvas(rows):
    return {int(row["target_rva"], 16) for row in rows}


def test_the_over_claim_answer_counts_every_dump(build):
    """"Is this ground spoken for?" — a dump holds the boundary, so yes."""
    rows = build.load_claim_rows(counting_dumps=True, matched_only=True)
    assert rvas(rows) == {0x00ABCD00, DUMP_RVA, REAL_RVA}


def test_the_work_finder_answer_counts_no_dump_wherever_it_lives(build):
    """"Do we have source for this?" — neither dump does, including the gen_small one."""
    rows = build.load_claim_rows(counting_dumps=False, matched_only=True)
    assert rvas(rows) == {REAL_RVA}


def test_matched_only_decides_the_hypothesis_row_separately(build):
    """An unmatched row is a guess about an address, not proof it is spoken for."""
    assert 0x00ABD000 in rvas(build.load_claim_rows(counting_dumps=True, matched_only=False))
    assert 0x00ABD000 not in rvas(build.load_claim_rows(counting_dumps=True, matched_only=True))


def test_a_gen_small_dump_is_a_dump_by_note_not_by_directory(build):
    rows = {row["name"]: row for row in build.load_all_function_rows()}
    assert build.is_scaffold_row(rows["?d_00abce00@@YAXXZ"])
    assert not build.is_scaffold_row(rows["?realBody@Thing@@QAEXXZ"])


def test_neither_question_may_be_answered_by_default():
    """A default is how the wrong answer reached tool number four in silence."""
    import inspect
    parameters = inspect.signature(_module("build").load_claim_rows).parameters
    assert set(parameters) == {"counting_dumps", "matched_only"}
    for parameter in parameters.values():
        assert parameter.default is inspect.Parameter.empty, parameter.name
        assert parameter.kind is inspect.Parameter.KEYWORD_ONLY, parameter.name


def test_next_work_offers_the_address_a_dump_covers(build, tmp_path, monkeypatch):
    """The bug that started this: the queue skipped every dump-covered candidate.

    Before the migration this pool was built over every ledger row, so the dump
    at DUMP_RVA counted as claimed and the candidate vanished -- which is the
    over-claim answer, asserted here so the two cannot silently converge again.
    """
    assert DUMP_RVA in rvas(build.load_claim_rows(counting_dumps=True, matched_only=False))

    next_work = _module("next_work")
    drift = tmp_path / "drift_report.csv"
    with drift.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["function", "source", "size", "candidate_rva",
                                         "aligned_pct", "class", "first_diff", "hint",
                                         "votes"], lineterminator="\n")
        writer.writeheader()
        for name, rva in (("?underADump@@YAXXZ", DUMP_RVA), ("?realBody@Thing@@QAEXXZ", REAL_RVA)):
            writer.writerow({"function": name, "source": "Thing.cpp", "size": "48",
                             "candidate_rva": f"0x{rva:08X}", "aligned_pct": "90",
                             "class": "immediate-only", "first_diff": "4",
                             "hint": "one immediate drifted", "votes": "3"})
    monkeypatch.setattr(next_work, "DRIFT", drift)
    monkeypatch.setattr(next_work, "resolve_drift_source",
                        lambda source, name: "Code/GameEngine/Source/Common/Thing.cpp")

    served = {item["candidate_rva"] for item in next_work.drift_quick_wins()}
    assert served == {f"0x{DUMP_RVA:08X}"}, "a dump-covered candidate is open work"


# Every way a tool has spelled "this row is a dump" from its source path: the
# Code/gen_asm/ literal, gen_small's DUMP_DIR_PREFIX bare or module-qualified,
# and conversion_gate's GEN_ASM. Written escaped so the guard does not flag its
# own definition.
BY_PATH = re.compile(
    r"""startswith\(\s*(?:["']Code/gen_asm/|(?:\w+\.)?(?:DUMP_DIR_PREFIX|GEN_ASM)\b)""")

# Placement questions, not claim questions: each of these asks WHERE a dump was
# written, and is allowed to read the directory to answer it.
ALLOWED = {
    "gen_dump.py": "retracts the rows it wrote into that directory: its own bookkeeping",
    "conversion_gate.py": "enforces that a gen_asm row carries gen-dump notes, which is "
                          "the invariant is_scaffold_row rests on",
    "wave_accounting.py": "splits an already-classified dump lane into genasm and naked",
    "family_scan.py": "scopes its family search to the gen_asm lane on purpose -- the 312 "
                      "gen-dump rows under Code/gen_small/ are owned by gen_small and "
                      "gen_uw, which AGENTS.md forbids hand-editing. The note cannot say "
                      "this: both lanes spell it `gen-dump`, so the lane is the path",
    "struct_match.py": "same lane restriction as family_scan.py, for the same reason",
}


def test_no_tool_decides_dumpness_by_source_path():
    """The fourth instance of this bug fails here instead of in the ledger.

    Phrased over the predicate rather than the bare string: `Code/gen_asm/`
    appears all over tools/ as prose and fixtures, and build.py never contains
    it at all, so a guard over the literal could only ever pass vacuously.
    """
    offences = []
    for path in sorted(TOOLS.rglob("*.py")):
        if "__pycache__" in path.parts or path.name in ALLOWED:
            continue
        for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
            if BY_PATH.search(line):
                offences.append(f"{path.relative_to(TOOLS.parent)}:{number}: {line.strip()}")
    assert not offences, (
        "a dump is a gen-dump note, never a directory -- 349 of them live in "
        "Code/gen_small/dumps_000.cpp. Ask build.is_scaffold_row or "
        "build.load_claim_rows instead:\n  " + "\n  ".join(offences))


def test_the_marker_is_a_whole_token_not_a_prefix_of_free_text(build):
    # Ten rows of real C++ carried notes such as "gen-dump conversion; ..." and
    # were served as open dumps by every picker, because the test was a prefix.
    assert build.is_scaffold_row({"notes": "gen-dump"})
    assert build.is_scaffold_row({"notes": "gen-dump;size=40"})
    assert build.is_scaffold_row({"notes": " gen-dump , carved"})
    assert not build.is_scaffold_row({"notes": "gen-dump conversion; 64-slot refcounted table"})
    assert not build.is_scaffold_row({"notes": "gen-dump converted to address-derived name"})
    assert not build.is_scaffold_row({"notes": "gen-dumped"})
    assert not build.is_scaffold_row({"notes": None})
    assert not build.is_scaffold_row({})


def test_no_row_of_real_source_passes_as_a_dump(build):
    with (build.ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8", errors="replace") as fh:
        wrong = [row["target_rva"] for row in csv.DictReader(fh)
                 if build.is_scaffold_row(row) and not row["source"].startswith("Code/gen_")]
    assert not wrong, f"{len(wrong)} rows outside Code/gen_ read as dumps: {wrong[:5]}"
