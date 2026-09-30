"""image_compose worklist: single-fix unlocks per file, and the negative cases that must rank 0."""
import random
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import image_check as I  # noqa: E402
import image_compose as C  # noqa: E402


def sets_for(succ, keys, cap=2):
    return C.reach_keys(succ, I.Image._scc(succ), keys, cap)


def test_second_blocker_in_the_file_unlocks_nothing():
    # file F: a -> x (bad), b -> y (bad); file G: c -> x
    a, b, c, x, y = range(5)
    succ = [(x,), (y,), (x,), (), ()]
    keys = [None, None, None, x, y]
    sets = sets_for(succ, keys)
    files, fns, closed = C.single_fix([a, b, c], {a: "F", b: "F", c: "G"}, sets)
    assert files[x] == ["G"] and y not in files  # F keeps y: fixing x ranks F at 0
    assert sorted(fns[x]) == [a, c] and fns[y] == [b]  # per function, each still closes alone
    assert closed == []
    # one fix site owning both x and y closes F too
    group = sets_for(succ, [None, None, None, "site", "site"])
    files, _, _ = C.single_fix([a, b, c], {a: "F", b: "F", c: "G"}, group)
    assert sorted(files["site"]) == ["F", "G"]


def test_more_bad_nodes_than_the_cap_unlock_nobody():
    # a reaches three bad nodes through a chain; cap 2 -> None, never a single-fix unlock
    a, m, x, y, z = range(5)
    succ = [(m, x), (y, z), (), (), ()]
    sets = sets_for(succ, [None, None, x, y, z])
    assert sets[a] is None and sets[m] == frozenset({y, z})
    files, fns, closed = C.single_fix([a], {a: "F"}, sets)
    assert not files and not fns and not closed


def test_closed_file_and_bad_function_itself():
    a, b, g = range(3)
    succ = [(g,), (), ()]
    sets = sets_for(succ, [None, b, None])  # b is itself bad, a reaches only good g
    files, fns, closed = C.single_fix([a, b], {a: "F", b: "H"}, sets)
    assert closed == ["F"] and files[b] == ["H"] and fns[b] == [b]


def test_cycles_share_one_set():
    a, b, x = range(3)
    succ = [(b,), (a, x), ()]
    sets = sets_for(succ, [None, None, x])
    assert sets[a] == sets[b] == frozenset({x})


def test_node_keys_reproduce_image_check_badsets():
    rng = random.Random(7)
    count = 300
    succ = [tuple(rng.sample(range(count), rng.randint(0, 3))) for _ in range(count)]
    good = [rng.random() > 0.1 for _ in range(count)]
    comp = I.Image._scc(succ)
    assert C.reach_keys(succ, comp, [None if ok else n for n, ok in enumerate(good)], 2) == \
        I.Image._badsets(succ, comp, good)


def leaf(name, kind, reason):
    return ("leaf", name, kind, False, reason, None, None, None, (), None)


def item(name, reason, verdict="wrong", lane="authored", obj="a.obj"):
    return ("item", name, obj, False, reason, verdict, 0x1000, lane, (name,), verdict)


def test_families():
    assert C.family_of(leaf("__imp__Foo@4", "unresolved", "nothing defines it (import)"), "")[0] == "import"
    assert C.family_of(leaf("_g_x", "unresolved", "nothing defines it (data)"), "")[0] == "data"
    assert C.family_of(leaf("?f@@YAXXZ", "unresolved", "nothing defines it (dump)"), "")[0] == "bridge"
    assert C.family_of(leaf("?f@@YAXXZ", "unresolved", "nothing defines it (alias)"), "")[0] == "provider"
    assert C.family_of(leaf("?f@@YAXXZ", "selection-unknown", "2 definitions and no /MAP holder"), "")[0] == \
        "provider"
    assert C.family_of(leaf("??_7Foo@@6B@", "unresolved", "nothing defines it (unpinned)"), "")[0] == "class-copy"
    assert C.family_of(item("$T123", "no retail address"), ".xdata$x")[0] == "eh"
    assert C.family_of(item("?d_00401000@@YAXXZ", "x", lane="dump"), ".text")[0] == "bridge"
    assert C.family_of(item("?f@@YAXXZ", "bytes differ at +0x5 (0x00401005)"), ".text")[0] == "body"
    assert C.family_of(item("?f@@YAXXZ", "+0x3 ?g@@YAXXZ (b.obj) lands at 0x1, its retail address is 0x2"),
                       ".text")[0] == "provider"
    assert C.family_of(item("?t@@3PAGA", "61 unrelocated in-image dword(s), first 0x0043003D at +0x22",
                            verdict="unknown"), ".data")[0] == "data"
    assert C.class_of("??_7Foo@@6B@") == "Foo" and C.class_of("??_R0?AVBar@@@8") == "Bar"
    assert C.fix_site(leaf("??_R4Foo@@6B@", "unresolved", ""), "class-copy", {}) == "class:Foo"
    assert C.fix_site(item("?f@@YAXXZ", ""), "body", {"a.obj": "game/a.cpp"}) == "source:game/a.cpp"


def test_next_serves_the_first_claimable_row(tmp_path, monkeypatch, capsys):
    import eligibility
    path = tmp_path / "worklist.csv"
    header = ",".join(C.WORKLIST_FIELDS)
    blank = {field: "" for field in C.WORKLIST_FIELDS}

    def line(**values):
        row = {**blank, "unlock_files": "0", "unlock_authored_bytes": "0", "unlock_vendored_bytes": "0",
               "unlock_census_linked_files": "0", "unlock_functions": "0", "unlock_function_bytes": "0",
               "group_unlock_files": "0", "group_unlock_authored_bytes": "0", **values}
        return ",".join(str(row[f]) for f in C.WORKLIST_FIELDS)
    path.write_text("\n".join([f"# {C.SINGLE_FIX}", header,
                               line(rank=1, blocker="_nowhere", family="data", unlock_authored_bytes=90),
                               line(rank=2, blocker="_retired", family="data", claim_rva="0x00000010",
                                    unlock_authored_bytes=80),
                               line(rank=3, blocker="_served", family="data", claim_rva="0x00000020",
                                    unlock_authored_bytes=70)]) + "\n", encoding="utf-8")
    monkeypatch.setattr(eligibility, "latest_verdicts", lambda: {0x10: "no-match"})
    monkeypatch.setattr(eligibility, "retired", lambda rva, latest: rva in latest)
    args = type("Args", (), {"worklist": path, "family": None, "no_claim": True})()
    assert C.cmd_next(args) == 0
    out = capsys.readouterr().out
    assert "rank 3" in out and "_served" in out and "NOT claimed" in out
