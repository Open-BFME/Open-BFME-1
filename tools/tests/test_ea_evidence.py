#!/usr/bin/env python3
"""ea_evidence: alignment, label/route combination, BSim seeds and file precedence."""
import sys
from pathlib import Path
from types import SimpleNamespace as NS

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import ea_evidence as E  # noqa: E402


def test_escaped_worldbuilder_strings_yield_code_relative_paths_and_labels():
    raw = r"Z:\\LOTR\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp(412)"
    path = E.PATH.search(E.unescape(raw))
    assert path.group(1).replace("\\", "/") == "GameEngine/Source/GameLogic/AI/AIStates.cpp"
    assert E.LABEL.fullmatch("Pathfinder::IsCliffCell") and E.LABEL.fullmatch("A::~A()")
    assert not E.LABEL.fullmatch("ControlBar::populateObserverList trying to populate")
    assert E.plain("?IsCliffCell@Pathfinder@@QAE_NH@Z") == "Pathfinder::IsCliffCell"
    assert E.plain("??1Team@@UAE@XZ") == "Team::~Team"


def test_alignment_keeps_order_and_skips_functions_only_one_build_has():
    same = {("a1", "b1"), ("a2", "b2"), ("a3", "b3")}
    got = E.align(["a1", "a2", "a3"], ["b1", "extra", "b2", "b3"], lambda x, y: 0.9 if (x, y) in same else 0.1)
    assert got == [("a1", "b1"), ("a2", "b2"), ("a3", "b3")]
    crossed = {("a1", "b2"), ("a2", "b1")}
    assert len(E.align(["a1", "a2"], ["b1", "b2"], lambda x, y: 0.9 if (x, y) in crossed else 0.0)) == 1


def pairing(pairs, why):
    return NS(pairs=pairs, why={a: why for a in pairs})


def test_names_join_agreeing_routes_and_drop_disagreeing_ones():
    p1 = pairing({1: 10, 2: 20, 3: 30}, "string")
    p12 = pairing({10: 100, 20: 200, 30: 300}, "aligned")
    p2 = pairing({1: 100, 2: 999}, "bsim")
    labels2 = {100: "A::f", 200: "B::g", 300: "C::h", 999: "Z::z"}
    got = E.names(p1, p12, p2, {}, labels2)
    assert got[1] == ("A::f", "chain+direct", "aligned")
    assert 2 not in got                       # chain says B::g, direct says Z::z
    assert got[3] == ("C::h", "chain", "aligned")
    strong = E.names(p1, pairing({10: 100}, "export"), p2, {10: "A::f"}, labels2)
    assert strong[1] == ("A::f", "chain+direct+wb1", "strong")


def test_bsim_seeds_need_a_margin_a_single_claim_and_size(tmp_path):
    tsv = tmp_path / "q.tsv"
    tsv.write_text("game_rva\tmatch_md5\tmatch_va\tsimilarity\tsignificance\n"
                   "0x10\tm\t0x401000\t0.90\t9\n0x10\tm\t0x402000\t0.70\t9\n"   # clear winner
                   "0x20\tm\t0x403000\t0.90\t9\n0x20\tm\t0x404000\t0.88\t9\n"   # no margin
                   "0x30\tm\t0x405000\t0.95\t9\n0x40\tm\t0x405000\t0.95\t9\n"   # claimed twice
                   "0x50\tm\t0x406000\t0.99\t9\n")                              # too small
    A = NS(size={0x10: 64, 0x20: 64, 0x30: 64, 0x40: 64, 0x50: 8})
    assert E.bsim_seeds(tsv, A, NS(base=0x400000)) == {0x10: 0x1000}


def test_file_precedence_and_retail_runs():
    G = NS(funcs=[1, 2, 3, 4, 5, 6, 7], vendored={6},
           name={1: "?f@A@@QAEXXZ", 2: "", 3: "", 4: "?g@B@@QAEXXZ", 5: "uw_00000005", 6: "", 7: "?f@A@@QAEXXZ"},
           names={1: {"?f@A@@QAEXXZ"}, 4: {"?g@B@@QAEXXZ"}, 7: {"?f@A@@QAEXXZ", "?h@C@@QAEXXZ"}})
    p1 = NS(pairs={1: 11, 3: 33})
    p2 = NS(pairs={4: 44})
    f1 = {11: ("X/A.cpp", "direct"), 33: ("X/A.cpp", "filled")}
    f2 = {44: ("Y/B2.cpp", "direct")}
    got = E.files(G, p1, p2, f1, f2, {"a::f": "Z/ZhA.cpp", "b::g": "Z/ZhB.cpp"})
    assert got[1] == ("X/A.cpp", "wb1")       # BFME1's own path beats Zero Hour
    assert got[2] == ("X/A.cpp", "retail-run")
    assert got[3] == ("X/A.cpp", "wb1-run")       # run-filled inside WorldBuilder
    assert 4 not in got                       # Zero Hour and BFME2 disagree
    assert 5 not in got and 6 not in got      # funclets and vendored code have no EA file
    assert 7 not in got                       # two ledger names: the zh route cannot choose


def test_worldbuilder_runs_fill_only_between_the_same_file():
    w = NS(size={1: 9, 2: 9, 3: 9, 4: 9, 5: 9}, paths={1: {"A.cpp"}, 3: {"A.cpp"}, 5: {"B.cpp", "C.cpp"}})
    got = E.wb_files(w)
    assert got == {1: ("A.cpp", "direct"), 2: ("A.cpp", "filled"), 3: ("A.cpp", "direct")}


def test_name_guard_checks_every_rename_at_a_strongly_paired_address():
    import ea_name_guard as guard
    ea = {0x3D9430: ("Pathfinder::IsCliffCell", "chain", "strong"), 0x10: ("A::f", "chain", "aligned")}
    exports = {0x3D9430: {"?exported@Pathfinder@@QAE_NH@Z"}}
    row = lambda name, notes="", rva="0x003D9430": {"name": name, "target_rva": rva, "notes": notes}
    was_dump = {0x3D9430: {"?d_003d9430@@YAXXZ"}}
    ok = [row("?IsCliffCell@Pathfinder@@QAE_NH@Z"), row("?iscliffcell@Pathfinder@@QAE_NH@Z"),
          row("?Rva003D9430@Pathfinder@@QAE_NH@Z"), row("?exported@Pathfinder@@QAE_NH@Z"),
          row("?isCliff@Pathfinder@@QAE_NH@Z", "ea-name-disputed=matched caller 0x00401000 calls isCliff")]
    assert guard.problems(ok, was_dump, ea, exports, zh={}) == []
    bad = guard.problems([row("?bfmeCellTypeTwo@Pathfinder@@QAE_NH@Z")], was_dump, ea, exports, zh={})
    assert len(bad) == 1 and "IsCliffCell" in bad[0]
    assert guard.problems([row("?bfmeCellTypeTwo@Pathfinder@@QAE_NH@Z")], {}, ea, exports, zh={})  # a new row
    zh = {"pathfinder": {"cellistypetwo"}}                                                  # Zero Hour declares it
    assert guard.problems([row("?cellIsTypeTwo@Pathfinder@@QAE_NH@Z")], was_dump, ea, exports, zh=zh) == []
    real_before = {0x3D9430: {"?cellTypeTwo@Pathfinder@@QAE_NH@Z"}}                        # real -> real
    assert guard.problems([row("?bfmeCellTypeTwo@Pathfinder@@QAE_NH@Z")], real_before, ea, exports, zh={})
    assert guard.problems([row("?IsCliffCell@Pathfinder@@QAE_NH@Z")], real_before, ea, exports, zh={}) == []
    moved = {0x3D9430: {"?bfmeCellTypeTwo@Pathfinder@@QAE_NH@Z"}}                          # source repoint only
    assert guard.problems([row("?bfmeCellTypeTwo@Pathfinder@@QAE_NH@Z")], moved, ea, exports) == []
    assert guard.problems([row("?g@B@@QAEXXZ", rva="0x00000010")], {}, ea, exports) == []      # aligned basis
    assert guard.problems([row("?Token@CParse@D3DXShader@@IAEHXZ", "vendored=d3dx9-9.0c")], {}, ea, exports, zh={}) == []


def test_rename_queue_serves_fixed_targets_and_refuses_the_risky_shapes():
    import ea_queue as Q
    row = lambda name, source="game/GameEngine/Source/Common/X.cpp", notes="": {
        "name": name, "source": source, "notes": notes, "target_size": "16"}
    rows_at = {
        0x10: [row("?Rva00000010@GameEngine@@QAEXPAX@Z")],                 # method rename
        0x20: [row("?bfmeFoo@BfmeThingBE@@QAEXXZ")],                        # stand-in class
        0x30: [row("?bar@BfmeThingBE@@QAEXXZ")],                            # its unlabelled member
        0x40: [row("?XferEnum@XferSave@@UAEXPAXPBXI@Z")],                   # virtual: never alone
        0x50: [row("?AddBanner@@YAXHABVAsciiString@@0@Z")],                 # free vs member
        0x60: [row("??1AIStateMachine@@MAE@XZ")],                           # structor vs method
        0x70: [row("?getBool@Dict@@QBE_NW4NameKeyType@@PA_N@Z")],           # already EA's name
        0x80: [row("?isCliff@Pathfinder@@QAE_NH@Z")],                       # a Zero Hour name
    }
    ea = {0x10: ("GameEngine::startHeadlessClients", "chain", "strong"), 0x20: ("AptCIH::Go", "chain", "strong"),
          0x40: ("XferSave::XferImpl", "chain", "strong"), 0x50: ("BannerUI::CreateBanner", "chain", "strong"),
          0x60: ("AIStateMachine::clear", "chain", "strong"), 0x70: ("Dict::getBool", "chain", "strong"),
          0x80: ("Pathfinder::IsCliffCell", "chain", "strong")}
    got = {i["kind"]: i for i in Q.items(ea, rows_at, {}, {"pathfinder": {"iscliff"}}, set())}
    assert set(got) == {"method", "class"}
    assert got["method"]["rows"] == [(0x10, "?Rva00000010@GameEngine@@QAEXPAX@Z",
                                      "?startHeadlessClients@GameEngine@@QAEXPAX@Z", "GameEngine::startHeadlessClients")]
    assert [r[2] for r in got["class"]["rows"]] == ["?Go@AptCIH@@QAEXXZ", "?bar@AptCIH@@QAEXXZ"]
    assert Q.items(ea, rows_at, {}, {"pathfinder": {"iscliff"}}, {0x10, 0x20}) == []       # blocked


def test_a_big_stand_in_class_needs_a_second_label_or_a_matching_name():
    import ea_queue as Q
    row = lambda name: {"name": name, "source": "game/X.cpp", "notes": "", "target_size": "16"}
    rows_at = {0x10 * k: [row(f"?m{k}@WindowManager@@QAEXXZ")] for k in range(1, 5)}
    ea = {0x10: ("AptPlayer::HideBackground", "chain", "strong")}
    assert Q.items(ea, rows_at, {}, {}, set()) == []
    ea[0x20] = ("AptPlayer::ShowBackground", "chain", "strong")
    assert len(Q.items(ea, rows_at, {}, {}, set())[0]["rows"]) == 4
    named = {0x10 * k: [row(f"?m{k}@BfmeAptScreenInGameChat@@QAEXXZ")] for k in range(1, 5)}
    assert Q.items({0x10: ("AptInGameChat::InitGadgets", "chain", "strong")}, named, {}, {}, set())
