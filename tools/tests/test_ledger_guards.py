"""Guards against the two ways a union-merged ledger corrupts itself silently.

Both of these actually happened while merging PR #67, and neither was caught by
anything: dedup_csv picked a source that no longer defined the symbol, and a
merge from a stale branch put a proven-wrong row back on master.
"""
import csv
import importlib.util
import io
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
HEADER = "name,export_rva,target_rva,target_size,source,status,notes"


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


dedup_csv = _load("dedup_csv")
check_csv = _load("check_csv")


def _write(path, *rows):
    path.write_text(HEADER + "\r\n" + "".join(r + "\r\n" for r in rows), encoding="utf-8")


FIND_FIELD_PARSE = "?findFieldParse@@YAP6AXPAVINI@@PAX1PBX@ZPBUFieldParse@@PBDAAHAAPBX@Z"


def test_dedup_refuses_when_one_row_is_claimed_by_two_sources(tmp_path):
    """The findFieldParse bug: lexical tiebreak picked ini.cpp, which no longer
    defines it, and the full gate died with 'symbol not found in object'."""
    ledger = tmp_path / "functions.csv"
    _write(ledger,
           f"{FIND_FIELD_PARSE},,0x00850880,128,Code/GameEngine/Source/Common/INI/ini.cpp,matched,",
           f"{FIND_FIELD_PARSE},,0x00850880,128,Code/GameEngine/Source/Common/INI/ini_parsers.cpp,matched,moved to the parser TU")
    before = ledger.read_bytes()

    with pytest.raises(SystemExit) as exc:
        dedup_csv.dedup_functions(ledger)

    assert exc.value.code == 1
    assert ledger.read_bytes() == before, "must not rewrite the ledger when it cannot decide"


def test_dedup_still_collapses_true_duplicates(tmp_path):
    """Same source twice is the ordinary union-merge case and must still collapse."""
    ledger = tmp_path / "functions.csv"
    src = "Code/GameEngine/Source/Common/INI/ini_parsers.cpp"
    _write(ledger,
           f"{FIND_FIELD_PARSE},,0x00850880,128,{src},matched,",
           f"{FIND_FIELD_PARSE},,0x00850880,128,{src},matched,moved to the parser TU")

    before, after = dedup_csv.dedup_functions(ledger)

    assert (before, after) == (2, 1)
    kept = list(csv.DictReader(io.StringIO(ledger.read_text(encoding="utf-8"))))
    assert kept[0]["source"] == src
    assert kept[0]["notes"] == "moved to the parser TU", "keep the more informative row"


def test_icf_alias_group_survives_dedup(tmp_path):
    """Distinct names at one address are folded COMDATs, not a conflict."""
    ledger = tmp_path / "functions.csv"
    src = "Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp"
    _write(ledger,
           f"?removeAllTerrainBibs@BaseHeightMapRenderObjClass@@QAEXXZ,,0x006CB050,31,{src},matched,",
           f"?setShoreLineDetail@BaseHeightMapRenderObjClass@@QAEXXZ,,0x006CB050,31,{src},matched,")

    before, after = dedup_csv.dedup_functions(ledger)

    assert (before, after) == (2, 2)


def test_check_csv_flags_a_resurrected_row(tmp_path, monkeypatch):
    """A branch that forked before a delete re-adds the row with no conflict,
    because git's union driver cannot express a deletion."""
    monkeypatch.setattr(check_csv, "DELETED", tmp_path / "deleted_rows.csv")
    check_csv.DELETED.write_text(
        "name,target_rva,reason\n"
        "# comment line must be ignored\n"
        "??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,0x00121F60,vtable base disagrees with ten other TUs\n",
        encoding="utf-8")
    src = "Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp"
    raw = (HEADER + "\r\n"
           + f"??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,,0x00121F60,46,{src},matched,\r\n"
           ).encode("utf-8")

    problems = []
    check_csv.check_functions(raw, problems, {src})

    assert any("come back" in p for p in problems), problems
    assert any("vtable base disagrees" in p for p in problems), "must say why it was deleted"


def test_check_csv_allows_rows_that_are_not_tombstoned(tmp_path, monkeypatch):
    monkeypatch.setattr(check_csv, "DELETED", tmp_path / "deleted_rows.csv")
    check_csv.DELETED.write_text(
        "name,target_rva,reason\n"
        "??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,0x00121F60,proven wrong\n",
        encoding="utf-8")
    src = "Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp"
    # same name, DIFFERENT address -> not the tombstoned row
    raw = (HEADER + "\r\n"
           + f"??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,,0x00999000,46,{src},matched,\r\n"
           ).encode("utf-8")

    problems = []
    check_csv.check_functions(raw, problems, {src})

    assert not any("come back" in p for p in problems), problems


def test_shipped_tombstone_file_parses():
    """The real reverse/deleted_rows.csv must load, or the guard is silently off."""
    entries = check_csv.tombstones()
    assert entries, "reverse/deleted_rows.csv produced no entries"
    assert all(isinstance(rva, int) and reason for (_, rva), reason in entries.items()), entries


# --- banked near-miss attempts (reverse/attempts/) -------------------------
# check_attempts reads the state being gated through known_sources/read_ledger,
# so these drive it with both stubbed rather than writing into the real repo.

def _attempts_harness(monkeypatch, tmp_path, stash_body, ledger_rows=(),
                      sources=()):
    """Point check_attempts at one synthetic stash plus a synthetic ledger."""
    rel = "reverse/attempts/0x000c8220.cpp"
    files = {rel: stash_body}
    files.update(sources)
    for path, text in files.items():
        target = tmp_path / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text, encoding="utf-8")

    ledger = (HEADER + "\r\n" + "".join(ledger_rows)).encode("utf-8")
    monkeypatch.setattr(check_csv, "ROOT", tmp_path)
    monkeypatch.setattr(check_csv, "known_sources", lambda spec: set(files))
    monkeypatch.setattr(check_csv, "read_ledger",
                        lambda path, spec: ledger if str(path).endswith("functions.csv")
                        else Path(path).read_bytes())
    problems = []
    check_csv.check_attempts(None, problems)
    return problems


GOOD_HEADER = ("// ?readFromDict@Handicap@@QAEXPBVDict@@@Z\n"
               "// partial score=0.99 date=2026-08-24\n")


def test_attempts_accepts_a_well_formed_stash(tmp_path, monkeypatch):
    problems = _attempts_harness(monkeypatch, tmp_path,
                                 GOOD_HEADER + "void f() {}\n")
    assert problems == [], problems


def test_attempts_rejects_an_unparsable_header(tmp_path, monkeypatch):
    problems = _attempts_harness(monkeypatch, tmp_path,
                                 "// sym\n// no score\nvoid f() {}\n")
    assert any("line 2 must read" in p for p in problems), problems


def test_attempts_rejects_an_oversize_body(tmp_path, monkeypatch):
    problems = _attempts_harness(monkeypatch, tmp_path,
                                 GOOD_HEADER + "x" * (64 * 1024 + 1))
    assert any("over 65536" in p for p in problems), problems


def test_attempts_rejects_a_stash_whose_rva_has_real_cpp(tmp_path, monkeypatch):
    """It landed: the body the stash was for now exists as authored C++."""
    src = "Code/GameEngine/Source/Common/Handicap.cpp"
    problems = _attempts_harness(
        monkeypatch, tmp_path, GOOD_HEADER + "void f() {}\n",
        ledger_rows=[f"?readFromDict@Handicap@@QAEXPBVDict@@@Z,,0x000C8220,362,{src},matched,\r\n"],
        sources={src: "void Handicap::readFromDict(const Dict *d) { real(); }\n"})
    assert any("already has real C++" in p for p in problems), problems


def test_attempts_exempts_a_dump_backed_rva(tmp_path, monkeypatch):
    """THE dump-lane regression guard, shaped on the real Handicap row.

    Every candidate list_naked_candidates serves is already status=matched --
    a naked transcription lands byte-verified -- so a bare matched-check would
    reject exactly the stashes this feature exists to serve.
    """
    src = "Code/GameEngine/Source/Common/Handicap_readFromDict_Thunk.cpp"
    problems = _attempts_harness(
        monkeypatch, tmp_path, GOOD_HEADER + "void f() {}\n",
        ledger_rows=[f"?readFromDict@Handicap@@QAEXPBVDict@@@Z,,0x000C8220,362,{src},matched,string-anchor Open-BFME4+Grok BUILDCOST\r\n"],
        sources={src: "__declspec(naked) void Handicap::readFromDict(Dict const *)\n"
                      "{ __asm { __emit 0x6a } }\n"})
    assert problems == [], problems


def test_attempts_rejects_a_misnamed_file(tmp_path, monkeypatch):
    rel = "reverse/attempts/handicap.cpp"
    target = tmp_path / rel
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(GOOD_HEADER + "void f() {}\n", encoding="utf-8")
    monkeypatch.setattr(check_csv, "ROOT", tmp_path)
    monkeypatch.setattr(check_csv, "known_sources", lambda spec: {rel})
    monkeypatch.setattr(check_csv, "read_ledger",
                        lambda path, spec: (HEADER + "\r\n").encode("utf-8"))
    problems = []
    check_csv.check_attempts(None, problems)
    assert any("must be the lowercase rva" in p for p in problems), problems


def test_attempts_exempts_an_asm_backed_rva(tmp_path, monkeypatch):
    """A Code/gen_asm/*.asm row is retail re-encoded by extension alone: it
    carries no __declspec(naked)/__emit token, so a body-text-only test reads
    it as real C++ and rejects the stash. Caught by the pre-commit hook on the
    first real seeding, not by review."""
    src = "Code/gen_asm/d_00435170.asm"
    problems = _attempts_harness(
        monkeypatch, tmp_path, GOOD_HEADER + "void f() {}\n",
        ledger_rows=[f"?d_00439280@@YAXXZ,,0x000C8220,82,{src},matched,gen-dump\r\n"],
        sources={src: "d_00439280 PROC\n  db 0x55\nd_00439280 ENDP\n"})
    assert problems == [], problems
