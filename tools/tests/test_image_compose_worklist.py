"""image_compose worklist: single-fix unlocks per file, and the negative cases that must rank 0."""
import json
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


def published_row(name, rva, size, site, family="data", verdict="unresolved", rule="unresolved data name"):
    return {"rank": 0, "family": family, "rule": rule, "verdict": verdict, "blocker": name, "claim_rva": rva,
            "unlock_files": 1, "unlock_authored_bytes": size, "unlock_function_bytes": 5, "_files": ["game/a.cpp"],
            "fix_site": site, "reason": "r", "census": "abc1234",
            "command": C.exact_command(family, rule, verdict, name, rva, "", "game/a.cpp")}


def test_next_serves_the_first_open_claimable_row(tmp_path, monkeypatch, capsys):
    import eligibility
    path = tmp_path / "linking_worklist.csv"
    work = [published_row(*spec) for spec in (("_nowhere", "", 90, "name:_nowhere"),
                                              ("_retired", "0x00000010", 80, "name:_retired"),
                                              ("_changed", "0x00000030", 75, "source:game/b.cpp"),
                                              ("_served", "0x00000020", 70, "name:_served"),
                                              ("_no_file", "0x00000040", 0, "name:_no_file"))]
    assert C.write_published(path, work, {"commit": "abc1234", "date": "d"}, 0) == 4  # 0 authored bytes: not published
    text = path.read_text(encoding="utf-8")
    assert text.startswith("# linking worklist, census abc1234") and C.SINGLE_FIX in text
    monkeypatch.setattr(eligibility, "latest_verdicts", lambda: {0x10: "no-match"})
    monkeypatch.setattr(eligibility, "retired", lambda rva, latest: rva in latest)
    fresh = object.__new__(C.Freshness)
    fresh.root, fresh.changed, fresh.lines = tmp_path, {"game/b.cpp"}, []
    monkeypatch.setattr(C, "Freshness", lambda census: fresh)
    args = type("Args", (), {"worklist": path, "family": None, "no_claim": True})()
    assert C.cmd_next(args) == 0
    out = capsys.readouterr().out
    assert "rank 4" in out and "_served" in out and "NOT claimed" in out
    assert "its source changed since the census 1" in out and "dead-end verdict 1" in out
    assert "provider_repair.py data-next --symbol '_served'" in out  # this blocker, not another picker


def test_published_schema_feeds_provider_repair_data_next(tmp_path):
    import provider_repair
    path = tmp_path / "linking_worklist.csv"
    work = [published_row("_g_unresolved", "0x00000020", 70, "name:_g_unresolved"),
            published_row("?t@@3PAGA", "0x00000030", 60, "source:game/t.cpp", verdict="unknown",
                          rule=C.TYPED + ": scalar or pointer"),
            published_row("?f@@YAXXZ", "0x00000040", 50, "source:game/f.cpp", family="body", verdict="wrong",
                          rule="wrong body")]
    C.write_published(path, work, {"commit": "abc1234", "date": "d"}, 0)
    tally = {}
    served = provider_repair.data_candidates(path, tally)
    assert [row["name"] for row in served] == ["_g_unresolved"] and tally == {"typed-evidence-lane": 1}


def test_exact_commands_name_the_blocker():
    assert C.exact_command("provider", "no single retail home", "unknown", "?f@@YAXXZ", "0x1", "game/a.cpp", "")         == "python3 tools/provider_repair.py next --symbol '?f@@YAXXZ'"
    assert "import_binding.py apply 'game/r.cpp'" in C.exact_command("import", "unresolved import", "unresolved",
                                                                        "__imp__X@4", "0x2", "", "game/r.cpp")
    assert C.exact_command("bridge", "dump body", "wrong", "?d_1", "0x00001000", "", "") ==         "python3 tools/brief.py --rvas 0x00001000"
    assert "link_check.py 'game/r.cpp'" in C.exact_command("provider", "alias", "unresolved", "?g", "", "",
                                                           "game/r.cpp")


def test_freshness_skips_what_changed_since_the_census(tmp_path):
    fresh = object.__new__(C.Freshness)
    fresh.root, fresh.changed = tmp_path, {"game/a.cpp"}
    fresh.lines = ["?f@@YAXXZ,,0x00401000,12,game/c.cpp,matched,", "_g_x,0x00500000,,"]
    assert C.Freshness.stale(fresh, {"fix_site": "source:game/a.cpp"}).startswith("its source")
    assert C.Freshness.stale(fresh, {"claim_rva": "0x00401000"}).startswith("a ledger line")
    assert C.Freshness.stale(fresh, {"blocker": "_g_x"}).startswith("a row, pin")
    assert C.Freshness.stale(fresh, {"blocker": "_g", "claim_rva": "0x00600000",
                                     "fix_site": "source:game/b.cpp"}) is None
    receipt = tmp_path / "build" / "provider_repair" / "0x00600000" / "receipt.json"
    receipt.parent.mkdir(parents=True)
    source = tmp_path / "game" / "b.cpp"
    source.parent.mkdir()
    source.write_text("int x;")
    row = {"claim_rva": "0x00600000"}
    receipt.write_text(json.dumps({"pass": False, "inputs": {"game/b.cpp": C.sha_file(source)}}))
    assert C.Freshness.stale(fresh, row) is None  # a FAIL receipt suppresses nothing
    receipt.write_text(json.dumps({"pass": True, "inputs": {"game/b.cpp": "0" * 64}}))
    assert C.Freshness.stale(fresh, row) is None  # a PASS on another tree neither
    receipt.write_text(json.dumps({"pass": True, "inputs": {"game/b.cpp": C.sha_file(source)}}))
    assert C.Freshness.stale(fresh, row).startswith("a PASS provider_repair receipt")


def test_receipt_validity_is_one_predicate(tmp_path):
    import provider_repair
    source = tmp_path / "game" / "b.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("int x;")
    digest = C.sha_file(source)
    receipt = tmp_path / "receipt.json"
    for text, valid in (("{not json", False), ("[]", False), (json.dumps({"pass": True}), False),
                        (json.dumps({"pass": False, "inputs": {"game/b.cpp": digest}}), False),
                        (json.dumps({"pass": True, "inputs": {"game/b.cpp": "0" * 64}}), False),
                        (json.dumps({"pass": True, "inputs": {"game/gone.cpp": digest}}), False),
                        (json.dumps({"pass": True, "inputs": {"game/b.cpp": digest}}), True)):
        receipt.write_text(text)
        assert provider_repair.receipt_valid(receipt, tmp_path) is valid, text


def test_generated_destinations_are_not_published(tmp_path):
    assert C.exact_command("import", "unresolved import", "unresolved", "__imp__X@4", "0x2", "",
                           "game/gen_small/imports_000.cpp") == ""
    assert C.exact_command("body", "wrong body", "wrong", "?f", "0x1", "game/gen_asm/x.asm", "") == ""
    path = tmp_path / "linking_worklist.csv"
    work = [published_row("__imp__X@4", "0x00000020", 70, "name:__imp__X@4", family="import",
                          rule="unresolved import")]
    work[0]["command"] = C.exact_command("import", "unresolved import", "unresolved", "__imp__X@4", "0x00000020", "",
                                         "game/gen_small/imports_000.cpp")
    assert C.write_published(path, work, {"commit": "abc1234", "date": "d"}, 0) == 0
    assert "less 1 whose fix would edit" in path.read_text(encoding="utf-8")


def test_daily_census_publishes_the_link_queue_under_its_lock():
    """The census, not image_compose, publishes the queue now (36288d9ff6): after
    the lock is taken, from this census's index, committed with the census."""
    script = (Path(__file__).resolve().parents[1] / "fleet" / "daily_census.sh").read_text(encoding="utf-8")
    assert script.count('rmdir "$lock"') == 1 and "trap 'rmdir \"$lock\"' EXIT" in script
    lock, census = script.index('mkdir "$lock"'), script.index("tools/link_census.py --build --history")
    publish = script.index("python3 tools/link_check.py --publish")
    assert lock < census < publish < script.index("targets/game/reverse/link_queue.csv", publish)
    assert "image_check.py" not in script and "linking_worklist.csv" not in script
