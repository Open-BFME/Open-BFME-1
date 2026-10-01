"""link_check: the per-file LINKED preview agrees with link.exe's rules."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C  # noqa: E402


def index(strong=None, comdat=None, blockers=None, sizes=None):
    return {"meta": {"date": "d", "commit": "c"}, "objects": ["a.obj", "b.obj", "c.obj"],
            "strong": strong or {}, "comdat": comdat or {}, "blockers": blockers or {}, "bytes": sizes or {},
            "common_schema": C.COMMON_SCHEMA, "common": {}}


def test_two_inline_copies_fold_silently():
    ix = index(comdat={"f": [(0, "x", None), (1, "y", None)]})
    assert not C.duplicate("f", 2, False, None, ix)


def test_exclusive_definition_collides_with_the_first_definition():
    ix = index(strong={"f": [0]}, comdat={"f": [(0, "x", None)]})
    assert C.duplicate("f", 2, False, None, ix)   # an inline copy after an exclusive first one
    assert C.duplicate("f", 2, True, None, ix)
    ix = index(comdat={"f": [(0, "x", None)]})
    assert C.duplicate("f", 2, True, None, ix)    # an exclusive definition after an inline first one
    assert not C.duplicate("f", 0, False, 0, ix)  # its own old copy is not a second definition


def test_first_definition_is_charged_when_a_later_one_is_exclusive():
    ix = index(strong={"f": [2]}, comdat={"f": [(2, "x", None)]})
    assert C.duplicate("f", 0, False, None, ix)


def test_next_counts_only_files_with_a_single_blocker(capsys):
    blockers = {
        "one.cpp": {"object": "a.obj", "linked": False, "unresolved": ["_htons@4"], "duplicates": [], "losers": [],
                    "addresses": 0},
        "two.cpp": {"object": "b.obj", "linked": False, "unresolved": ["_htons@4", "_x"], "duplicates": [],
                    "losers": [], "addresses": 0},
        "lit.cpp": {"object": "c.obj", "linked": False, "unresolved": [], "duplicates": [], "losers": [],
                    "addresses": 3},
    }
    C.next_names(index(blockers=blockers, sizes={"one.cpp": 100, "two.cpp": 500, "lit.cpp": 40}), 10)
    out = capsys.readouterr().out
    assert "100     1  unresolved  _htons@4" in out
    assert C.ADDRESSES in out and "_x" not in out


def test_stale_object_is_never_evidence(tmp_path, monkeypatch):
    """A source edited after its object was compiled: link_census.object_current
    says no (with or without a dependency record) and link_check refuses it."""
    import json
    import os
    import link_census
    source, obj = tmp_path / "f.cpp", tmp_path / "f.obj"
    obj.write_bytes(b"old object")
    source.write_text("int f() { return 2; }\n")
    os.utime(obj, (1_000_000, 1_000_000))
    assert not link_census.object_current(source, obj)  # no sidecar: older than its source
    os.utime(obj, None)
    os.utime(source, (1_000_000, 1_000_000))
    assert not link_census.object_current(source, obj)  # timestamps do not replace a receipt
    monkeypatch.setattr(link_census.build, "compiler_command", lambda s, o: (["cl"], {}))
    monkeypatch.setattr(link_census.build, "_cmd_fingerprint", lambda command, env: "cmd")
    sidecar = link_census.build._deps_sidecar(obj)
    sidecar.write_text(json.dumps({"source": link_census.build._hash_file(str(source)), "deps": {}, "cmd": "cmd"}))
    assert link_census.object_current(source, obj)
    source.write_text("int f() { return 3; }\n")  # edited after the compile
    assert not link_census.object_current(source, obj)
    monkeypatch.setattr(C, "ROOT", tmp_path)
    ix = index(blockers={"f.cpp": {"object": "f.obj", "linked": True, "unresolved": [], "duplicates": [],
                                   "losers": [], "addresses": 0}})
    import pytest
    with pytest.raises(SystemExit, match="not current"):
        C.resolve(str(obj), ix)


def test_a_missing_object_is_never_an_empty_clean_one(tmp_path):
    # falsifier from the 2026-09-29 linking audit: object_facts turned a read failure into empty
    # facts, and link_check reported LINKS for an object that does not exist
    import pytest
    import link_census
    missing = tmp_path / "does_not_exist.obj"
    with pytest.raises(link_census.MissingObject):
        link_census.object_facts(missing)
    ix = {**index(), "objects": [], "selection": {"exceptions": {}, "owners": {}},
          "excuses": {"runtime": set(), "imported": {}, "stubs": {}}}
    with pytest.raises(link_census.MissingObject):
        C.check_object(missing, ix, None)
    with pytest.raises(SystemExit):
        C.resolve(str(missing), ix)


def test_families_follow_the_name_scope_not_its_arguments():
    assert C.family_of("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z") == "stlport"
    assert C.family_of("??1facet@locale@_STL@@MAE@XZ") == "stlport"
    assert C.family_of("?_Stl_atod@_STL@@YANPADHH@Z") == "stlport"
    assert C.family_of("?bfmeBitVectorEqual@@YA_NABV?$vector@_NV?$allocator@_N@_STL@@@_STL@@0@Z") == ""
    assert C.family_of("??1AsciiString@@QAE@XZ") == "strings"
    assert C.family_of("?compareNoCase@?$StringBase@D@@QBEHABV1@@Z") == "strings"
    assert C.family_of("?getPingValue@GameSpyInfo@@UAEHABVAsciiString@@@Z") == ""
    assert C.family_of("?TheScriptEngine@@3PAVScriptEngine@@A") == "globals"
    assert C.claim_key("x") >= 0xF0000000


def test_publish_and_serve_skip_changed_landed_and_family_rows(tmp_path, monkeypatch, capsys):
    import claims
    blockers = {name + ".cpp": {"object": "a.obj", "linked": False, "unresolved": [name], "duplicates": [],
                                "losers": [], "addresses": 0}
                for name in ("changed", "landed", "open", "??1AsciiString@@QAE@XZ")}
    sizes = {"changed.cpp": 400, "landed.cpp": 300, "??1AsciiString@@QAE@XZ.cpp": 250, "open.cpp": 100}
    queue = tmp_path / "q.csv"
    C.publish(index(blockers=blockers, sizes=sizes), queue)
    monkeypatch.setattr(claims, "_fetch_master", lambda: "tip")
    monkeypatch.setattr(C, "_git", lambda *a, **k: "changed.cpp\n" if a[0] == "diff"
                        else f"Claim-Lease: 0x{C.claim_key('landed'):08X}=abcdef12\n")
    monkeypatch.setattr(claims, "owner", lambda: "me")
    monkeypatch.setattr(claims, "active", lambda: {})
    assert C.main(["next", "--no-claim", "--queue", str(queue)]) == 0
    out = capsys.readouterr().out
    assert "link queue #4 (census c): open" in out and "1 family strings" in out
    assert C.main(["next", "--no-claim", "--family", "strings", "--queue", str(queue)]) == 0
    assert "??1AsciiString@@QAE@XZ" in capsys.readouterr().out


def test_refresh_replaces_a_passed_objects_census_definitions(monkeypatch):
    """A duplicate removed from b.obj since the census no longer charges a.obj."""
    import link_census
    from types import SimpleNamespace
    ix = index(strong={"f": [0, 1], "g": [1]}, comdat={"h": [(1, "x", None)]})
    assert C.duplicate("f", 0, True, 0, ix)
    monkeypatch.setattr(link_census, "object_facts", lambda obj, truth: ([], ["g"], [], []))
    monkeypatch.setattr(link_census, "common_definitions", lambda obj: {})
    C.refresh(ix, [SimpleNamespace(name="b.obj"), SimpleNamespace(name="new.obj")], None)
    assert ix["strong"] == {"f": [0], "g": [1]} and ix["comdat"] == {"h": []}
    assert not C.duplicate("f", 0, True, 0, ix)


def test_serve_fails_closed_when_freshness_cannot_be_read(tmp_path, monkeypatch):
    """No origin/master, or a census commit git cannot find: exit, never claim."""
    import claims
    import pytest
    queue = tmp_path / "q.csv"
    C.publish(index(blockers={"a.cpp": {"object": "a.obj", "linked": False, "unresolved": ["x"], "duplicates": [],
                                        "losers": [], "addresses": 0}}, sizes={"a.cpp": 1}), queue)
    monkeypatch.setattr(claims, "claim", lambda *a, **k: pytest.fail("claimed a stale queue"))
    monkeypatch.setattr(claims, "_fetch_master", lambda: None)
    with pytest.raises(SystemExit):
        C.main(["next", "--queue", str(queue)])
    monkeypatch.setattr(claims, "_fetch_master", lambda: "HEAD")   # census "c" is not a commit
    with pytest.raises(SystemExit, match="nothing claimed"):
        C.main(["next", "--queue", str(queue)])


def _preview(monkeypatch, tmp_path, names):
    import link_census
    ix = index(blockers={"a.cpp": {"object": "a.obj", "linked": False, "unresolved": [], "duplicates": [],
                                   "losers": [], "addresses": 0}}, sizes={"a.cpp": 100})
    monkeypatch.setattr(C, "load_index", lambda: ix)
    monkeypatch.setattr(C, "resolve", lambda path, _: (path.replace(".obj", ".cpp"), tmp_path / path))
    monkeypatch.setattr(link_census, "ledger", lambda: None)
    monkeypatch.setattr(link_census, "RetailTruth", lambda _: None)
    monkeypatch.setattr(C, "refresh", lambda *a: None)
    monkeypatch.setattr(C, "source_bytes", lambda sources: {s: 100 for s in sources})
    monkeypatch.setattr(C, "check_object", lambda *a: {k: [] for k in
                        ("unresolved", "duplicates", "comdat", "addresses", "selected")})
    return C.main(names)


def test_a_file_named_twice_counts_once(monkeypatch, tmp_path, capsys):
    assert _preview(monkeypatch, tmp_path, ["a.obj", "a.obj"]) == 0
    assert "1 of 1 link cleanly; LINKED 0 -> 100 bytes" in capsys.readouterr().out


def test_an_object_outside_the_census_is_refused(monkeypatch, tmp_path):
    import pytest
    with pytest.raises(SystemExit, match="not in census c.*new.cpp"):
        _preview(monkeypatch, tmp_path, ["a.obj", "new.obj"])
