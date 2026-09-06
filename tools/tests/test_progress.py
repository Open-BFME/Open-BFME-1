#!/usr/bin/env python3
"""Focused tests for tools/progress.py; stdlib only."""
import importlib.util
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "progress.py"
COMMIT = "b08e5e856efced6d08c539153f5e229912f23b4f"

sys.path.insert(0, str(ROOT / "tools"))
spec = importlib.util.spec_from_file_location("progress", TOOL)
progress = importlib.util.module_from_spec(spec)
spec.loader.exec_module(progress)


def row(name, rva, size, source):
    return {(name, f"0x{rva:X}"): (size, source)}


def test_union_and_cpp_precedence():
    matched = {}
    matched.update(row("cpp-a", 0x1000, 10, "Code/a.cpp"))
    matched.update(row("cpp-b", 0x1005, 10, "Code/b.cpp"))
    matched.update(row("asm-overlap", 0x1008, 12, "Code/masm_dumps/a.asm"))
    matched.update(row("asm-only", 0x1030, 10, "Code/masm_dumps/b.asm"))
    stats = progress.coverage(matched, 0x1000, 100)
    assert stats == {
        "cpp": 15,
        "asm_only": 15,
        "unmatched": 70,
        "exact": 30,
        "text": 100,
    }, stats
    print("PASS interval union and C++ precedence")


def test_text_clipping():
    matched = {}
    matched.update(row("before", 0x0FF8, 12, "Code/a.cpp"))
    matched.update(row("after", 0x105E, 12, "Code/masm_dumps/a.asm"))
    stats = progress.coverage(matched, 0x1000, 100)
    assert stats["cpp"] == 4 and stats["asm_only"] == 6, stats
    assert stats["exact"] == 10 and stats["unmatched"] == 90, stats
    print("PASS .text boundary clipping")


def test_unknown_source_suffix_fails():
    matched = row("unknown", 0x1000, 10, "Code/generated/object.bin")
    try:
        progress.coverage(matched, 0x1000, 100)
    except SystemExit as exc:
        message = str(exc)
        assert "unsupported suffix .bin" in message and "object.bin" in message, message
    else:
        raise AssertionError("unknown matched-source suffix was counted as C++")
    print("PASS unknown matched-source suffix fails loudly")


def test_naked_cpp_to_clean_cpp_shifts_category_only():
    matched = row("?convert@Widget@@QAEXXZ", 0x1000, 3, "Code/convert.cpp")
    naked_text = """\
// ?convert@Widget@@QAEXXZ
__declspec(naked) void Widget::convert()
{
    __asm { __emit 0x8b __emit 0xc1 __emit 0xc3 }
}
"""
    naked_rows = progress.naked_cpp_rows(
        matched, {"Code/convert.cpp": naked_text},
        target_reader=lambda rva, size: bytes.fromhex("8b c1 c3"))
    assert naked_rows == set(matched), naked_rows

    before = progress.coverage(matched, 0x1000, 100, naked_rows)
    after = progress.coverage(matched, 0x1000, 100)
    assert before["asm_only"] == 3 and before["cpp"] == 0, before
    assert after["asm_only"] == 0 and after["cpp"] == 3, after
    assert before["exact"] == after["exact"] == 3
    assert before["unmatched"] == after["unmatched"] == 97
    print("PASS naked .cpp -> clean C++ shifts category but not exact coverage")


def test_bare_asm_emit_spray_is_asm_but_partial_emit_is_cpp():
    """A plain function whose __asm block emits the row's full retail bytes is
    a lift, not C++ (18 fleet commits smuggled these past the naked-only scan);
    a real body using the period _emit idiom for a few opcodes stays C++."""
    spray = row("?showBox@@YAXXZ", 0x1000, 8, "Code/spray.cpp")
    spray_text = """\
void showBox()
{
    __asm {
        __emit 0x8b;
        __emit 0xc1;
        call helper
        __emit 0x59;
        __emit 0xc3;
    }
}
"""
    found = progress.naked_cpp_rows(
        spray, {"Code/spray.cpp": spray_text},
        target_reader=lambda rva, size: bytes.fromhex("8bc1e800000000" + "59c3")[:size])
    assert found == set(spray), found

    idiom = row("?Init_CPU@@YAXXZ", 0x2000, 200, "Code/cpu.cpp")
    idiom_text = """\
void Init_CPU()
{
    int regs;
    __asm {
        mov eax, 1
        _emit 0x0f
        _emit 0xa2
        mov regs, eax
    }
}
"""
    found = progress.naked_cpp_rows(
        idiom, {"Code/cpu.cpp": idiom_text},
        target_reader=lambda rva, size: b"\x0f\xa2" + bytes(size - 2))
    assert found == set(), found
    print("PASS bare __asm emit spray is ASM; partial _emit idiom stays C++")


def test_mixed_file_marks_only_proven_naked_row():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/mixed.cpp"))
    matched.update(row("?clean@Widget@@QAEXXZ", 0x1010, 1, "Code/mixed.cpp"))
    text = """\
__declspec(naked) void Widget::raw() { __asm { ret } }
void Widget::clean() {}
"""
    found = progress.naked_cpp_rows(matched, {"Code/mixed.cpp": text})
    assert found == {("?raw@Widget@@QAEXXZ", "0x1000")}, found
    print("PASS mixed source classifies only signature-proven naked row")


def test_naked_body_callee_is_not_signature_evidence():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/wrapper.cpp"))
    matched.update(row("?clean@Widget@@QAEXXZ", 0x1010, 1, "Code/wrapper.cpp"))
    text = """\
__declspec(naked) void Widget::raw()
{
    __asm { call Widget::clean ret }
}
void Widget::clean() {}
"""
    found = progress.naked_cpp_rows(matched, {"Code/wrapper.cpp": text})
    assert found == {("?raw@Widget@@QAEXXZ", "0x1000")}, found
    print("PASS naked callee text cannot reclassify a clean row")


def test_naked_declaration_is_not_a_body():
    text = """\
__declspec(naked) void Widget::declared();
__declspec(naked) void Widget::defined() { __asm { ret } }
"""
    bodies = progress.scan_naked_bodies(text)
    assert len(bodies) == 1 and "Widget::defined" in bodies[0]["signature"], bodies
    print("PASS naked declarations are not counted as ASM bodies")


def test_signature_prefix_does_not_match_another_method():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/prefix.cpp"))
    matched.update(row("?rawHelper@Widget@@QAEXXZ", 0x1010, 1, "Code/prefix.cpp"))
    text = """\
void Widget::raw() {}
__declspec(naked) void Widget::rawHelper() { __asm { ret } }
"""
    found = progress.naked_cpp_rows(matched, {"Code/prefix.cpp": text})
    assert found == {("?rawHelper@Widget@@QAEXXZ", "0x1010")}, found
    print("PASS naked signature matching respects method boundaries")


def test_c_naked_signature_matches_decorated_row():
    matched = row("_GetPreviewFromMap", 0x1000, 1, "Code/free.cpp")
    text = "__declspec(naked) void *GetPreviewFromMap(void *, void *) { __asm { ret } }\n"
    found = progress.naked_cpp_rows(matched, {"Code/free.cpp": text})
    assert found == set(matched), found
    print("PASS C-linkage naked signature maps to its decorated row")


def test_live_naked_and_clean_rows_are_distinguished():
    """Every naked classification must point at a source that really contains a
    naked body, and clean rows must dominate.

    This used to pin two symbols by name, which rots by design: the project's
    goal is to convert every naked row, so any pinned naked symbol eventually
    becomes clean and the test breaks on progress (it died when the fleet
    converted ?construct@BFMENetworkBackend). Self-consistency over whatever
    is naked right now cannot rot, and an empty naked set is success."""
    matched = progress.matched_at("HEAD")
    naked = progress.naked_cpp_rows_at(matched, "HEAD")
    texts = progress.naked_source_texts(matched, "HEAD")
    for key in naked:
        source = matched[key][1]
        assert source in texts and (
            progress.NAKED_RE.search(texts[source])
            or progress.EMIT_RE.search(texts[source])), (
            f"{key} classified asm but {source} carries no naked or emit marker")
    clean = {key for key, (_, src) in matched.items()
             if src.endswith(".cpp")} - set(naked)
    assert len(clean) > len(naked), (len(clean), len(naked))
    print(f"PASS live ledger: {len(naked)} naked rows all self-consistent, "
          f"{len(clean)} clean")


def test_b08_is_zero_byte_progress():
    start, size = progress.retail_text()
    before_rows = progress.matched_at(f"{COMMIT}^")
    after_rows = progress.matched_at(COMMIT)
    before = progress.coverage(
        before_rows, start, size, progress.naked_cpp_rows_at(before_rows, f"{COMMIT}^"))
    after = progress.coverage(
        after_rows, start, size, progress.naked_cpp_rows_at(after_rows, COMMIT))
    assert before == after, (before, after)

    proc = subprocess.run(
        [sys.executable, str(TOOL), f"{COMMIT}^..{COMMIT}"],
        cwd=ROOT, capture_output=True, text=True, check=True)
    # Every delta the scorecard prints must be zero, on whichever views exist.
    # Pinning the line count instead broke the moment the real-code view added
    # six more of them, which is a report gaining detail, not progress moving.
    deltas = proc.stdout.count("delta ")
    assert deltas and proc.stdout.count("delta +0 bytes, +0.00 pp") == deltas, proc.stdout
    assert "matched rows" not in proc.stdout, proc.stdout
    print(f"PASS b08 reports zero byte progress on all {deltas} reported lanes")


def test_details_are_opt_in():
    plain = subprocess.run(
        [sys.executable, str(TOOL), f"{COMMIT}^..{COMMIT}"],
        cwd=ROOT, capture_output=True, text=True, check=True).stdout
    detailed = subprocess.run(
        [sys.executable, str(TOOL), "--details", f"{COMMIT}^..{COMMIT}"],
        cwd=ROOT, capture_output=True, text=True, check=True).stdout
    assert "ledger details" not in plain
    assert "ledger details" in detailed and "distinct RVAs" in detailed
    assert "ASM-backed rows:" in detailed and "ASM-bearing files:" in detailed
    print("PASS ledger diagnostics require --details")


def test_source_lanes_partition_claims_and_exclude_dumps():
    """Provenance lanes must cover every claimed byte exactly once, and only
    human-written source may land in the recovered lane."""
    matched, notes = {}, {}
    for name, rva, size, source, note in (
        ("authored", 0x1000, 10, "Code/GameEngine/Source/a.cpp", ""),
        ("vendored", 0x1010, 10, "Code/Libraries/Source/Lua/l.c", ""),
        ("gen-noted", 0x1020, 10, "Code/GameEngine/Source/b.cpp", "gen-thunk;"),
        ("gen-path", 0x1030, 10, "Code/gen_small/uw_gen_001.cpp", ""),
        ("lib", 0x1040, 10, "vendor/d3dx9/d3dx9.lib", ""),
        ("dump", 0x1050, 10, "Code/gen_asm/d_001050.asm", "gen-dump;"),
        ("emit", 0x1060, 10, "Code/GameEngine/Source/c.cpp", ""),
        # An ICF alias of the authored row, claimed again as a dump: the byte
        # is credited once, to the claim that says the most about it.
        ("alias", 0x1000, 10, "Code/gen_asm/d_001000.asm", "gen-dump;"),
    ):
        matched.update(row(name, rva, size, source))
        notes[(name, f"0x{rva:X}")] = note

    split = progress.source_split(matched, notes, 0x1000, 200,
                                  naked_rows={("emit", "0x1060")})
    assert split == {"authored": 10, "vendored": 10, "generated": 20,
                     "library": 10, "dump": 20, "recovered": 20}, split
    stats = progress.coverage(matched, 0x1000, 200, {("emit", "0x1060")})
    assert sum(split[lane] for lane in progress.SOURCE_LANES) == stats["exact"]
    print("PASS provenance lanes partition claimed bytes; dumps excluded")


def test_zero_hour_reference_source_is_not_authored():
    """A row compiled out of the pristine Zero Hour tree is EA's source, not ours.

    The zh_sweep waves point ledger rows straight at
    reference/CnC_Generals_Zero_Hour/... — a tree this project is forbidden to
    modify — so nobody wrote those bytes from the disassembly. Before the lane
    was added, 34,291 bytes of Zero Hour scored as "C++ we wrote". The headline
    may not move either way: rebuildable() spans authored and vendored alike.
    """
    zh = "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/"
    assert progress.source_lane(zh + "GameClient/GUI/ControlBar/ControlBar.cpp",
                                "", False) == "vendored"
    # ...and only under that root. The shims are ours, and so is Code/.
    assert progress.source_lane("reference/shims/controlbar/x.cpp", "", False) == "authored"
    assert progress.source_lane("Code/GameEngine/Source/Common/x.cpp", "", False) == "authored"

    matched, notes = {}, {}
    for name, rva, size, source in (
        ("zh-twin", 0x1000, 10, zh + "Common/x.cpp"),
        ("ours", 0x1010, 10, "Code/GameEngine/Source/Common/y.cpp"),
    ):
        matched.update(row(name, rva, size, source))
        notes[(name, f"0x{rva:X}")] = ""
    split = progress.source_split(matched, notes, 0x1000, 100)
    assert split["vendored"] == 10 and split["authored"] == 10, split
    assert progress.rebuildable(split) == 20, split
    print("PASS Zero Hour reference source lands in the vendored lane")


def test_gamespy_sdk_c_is_vendored_but_the_cpp_beside_it_is_not():
    """GameSpy's SDK is the one vendored tree that shares a directory with the
    game's own code, so the lane split has to key on extension there.

    Before this was fixed, every GameSpy .c row scored as "C++ we wrote" and
    90,073 bytes of a 2004 third-party SDK inflated the authored figure -- the
    exact defect d57cc1fcf named when it routed LZHCompress. The .cpp assertion
    is the half that keeps the fix from over-reaching: PeerDefs.cpp and the
    thunks beside gp.c ARE this project's.
    """
    root = "Code/GameEngine/Source/GameNetwork/GameSpy/"
    assert progress.source_lane(root + "gp/gp.c", "", False) == "vendored"
    assert progress.source_lane(root + "nonport.c", "", False) == "vendored"
    assert progress.source_lane(root + "PeerDefs.cpp", "", False) == "authored"
    assert progress.source_lane(root + "gp/gp.c", "gen-alias;", False) == "generated"

    # ...and the headline may not move when a byte changes lane, because
    # rebuildable() spans authored and vendored alike.
    matched, notes = {}, {}
    for name, rva, size, source in (
        ("sdk-c", 0x1000, 10, root + "qr2/qr2.c"),
        ("game-cpp", 0x1010, 10, root + "GSConfig.cpp"),
    ):
        matched.update(row(name, rva, size, source))
        notes[(name, f"0x{rva:X}")] = ""
    split = progress.source_split(matched, notes, 0x1000, 100)
    assert split["vendored"] == 10 and split["authored"] == 10, split
    assert progress.rebuildable(split) == 20, split
    print("PASS GameSpy SDK .c routes to the vendored lane; .cpp stays authored")


def test_dump_pass_moved_zero_recovered_bytes():
    """The metric must not be movable by a script.

    The stage 1-4 dump pass claimed 4.57 MB of retail as MASM `db` bodies. If
    that can raise the recovered figure by one byte, the figure is worthless,
    so the whole pass is pinned here as a zero.
    """
    start, size = progress.retail_text()
    before_ref, after_ref = "03b2ecc83", "6fe7ee982"
    figures = []
    for ref in (before_ref, after_ref):
        rows = progress.matched_at(ref)
        figures.append(progress.source_split(
            rows, progress.notes_at(ref), start, size,
            progress.naked_cpp_rows_at(rows, ref)))
    before, after = figures
    assert before["recovered"] == after["recovered"], (before, after)
    assert after["dump"] - before["dump"] > 4_000_000, (before, after)
    print(f"PASS dump pass added {after['dump'] - before['dump']:,} scaffold bytes "
          f"and 0 recovered bytes")


def test_readme_headline_is_a_recovered_figure():
    """The first percentage the README's Status section quotes is its headline
    claim, and it may never exceed what the tool calls recovered source.

    Upper bound only, for the same reason as the test below: contributors land
    functions continuously, so a README that lags is fine and a README that
    flatters is not.
    """
    printed = subprocess.run([sys.executable, str(TOOL)],
                             cwd=ROOT, capture_output=True, text=True, check=True).stdout
    line = next(l for l in printed.splitlines()
                if "REBUILDS FROM WHAT WE HOLD" in l)
    rebuilds = float(line.split("(")[1].split("%")[0])

    readme = (ROOT / "README.md").read_text(encoding="utf-8")
    assert readme.index("docs/progress.svg") < readme.index("## Status")
    svg = (ROOT / "docs/progress.svg").read_text(encoding="utf-8")
    headline = float(re.search(r"(\d+\.\d+)%", svg).group(1))
    assert headline <= rebuilds + 0.005, (
        f"README headlines {headline}% where progress.py says {rebuilds}%. "
        f"The README may lag reality; it may never flatter it")
    assert headline >= rebuilds - 5.0, (
        f"README headlines {headline}% where the project is already at "
        f"{rebuilds}% — more than five points stale. Update it")
    print(f"PASS README headlines {headline}% against {rebuilds}%")


def test_readme_never_overstates_coverage():
    """The README quotes ONE headline: what rebuilds from what we hold. No
    figure in it may exceed that, and the headline itself must be the tool's.

    The project reports a single number on purpose. Anything a reader could
    mistake for it — total-claimed, which counts byte-true dumps of retail —
    flatters by ~56 points, so the guard is that nothing quoted goes above the
    headline. Equality with the headline is asserted (it is one pinned number
    now, and a stale headline is the failure this test exists to catch), but
    the other figures are only bounded: they are allowed to lag.
    """
    printed = subprocess.run([sys.executable, str(TOOL)],
                             cwd=ROOT, capture_output=True, text=True, check=True).stdout
    line = next(l for l in printed.splitlines()
                if "REBUILDS FROM WHAT WE HOLD" in l)
    rebuilds = float(line.split("(")[1].split("%")[0])

    readme = (ROOT / "README.md").read_text(encoding="utf-8")
    readme += (ROOT / "docs/progress.svg").read_text(encoding="utf-8")
    quoted = sorted(float(v) for v in re.findall(r"(\d+\.\d+)%", readme))
    assert quoted, "README quotes no coverage figure at all"
    for value in quoted:
        assert value <= rebuilds + 0.005, (
            f"README quotes {value}%, above the {rebuilds}% that rebuilds from "
            f"what we hold. The bigger figures the tool prints -- total claimed, "
            f"the dump share -- are not coverage, and quoting one here reads as "
            f"if it were")
    print(f"PASS all {len(quoted)} README figures stay at or under {rebuilds}%")


def main():
    test_union_and_cpp_precedence()
    test_text_clipping()
    test_unknown_source_suffix_fails()
    test_naked_cpp_to_clean_cpp_shifts_category_only()
    test_bare_asm_emit_spray_is_asm_but_partial_emit_is_cpp()
    test_mixed_file_marks_only_proven_naked_row()
    test_naked_body_callee_is_not_signature_evidence()
    test_naked_declaration_is_not_a_body()
    test_signature_prefix_does_not_match_another_method()
    test_c_naked_signature_matches_decorated_row()
    test_live_naked_and_clean_rows_are_distinguished()
    test_b08_is_zero_byte_progress()
    test_details_are_opt_in()
    test_source_lanes_partition_claims_and_exclude_dumps()
    test_zero_hour_reference_source_is_not_authored()
    test_gamespy_sdk_c_is_vendored_but_the_cpp_beside_it_is_not()
    test_dump_pass_moved_zero_recovered_bytes()
    test_readme_headline_is_a_recovered_figure()
    test_readme_never_overstates_coverage()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
