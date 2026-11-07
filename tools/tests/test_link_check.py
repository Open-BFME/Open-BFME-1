"""link_check: the per-file LINKED preview agrees with link.exe's rules."""
import collections
import copy
import pickle
import subprocess
import sys
from unittest.mock import patch
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C  # noqa: E402
import link_census as L
import pytest
from test_weak_fallback_truth import fixture, provider_coff, add_symbol


def index(strong=None, comdat=None, blockers=None, sizes=None):
    return {"meta": {"date": "d", "commit": "c"}, "objects": ["a.obj", "b.obj", "c.obj"],
            "strong": strong or {}, "comdat": comdat or {}, "blockers": blockers or {}, "bytes": sizes or {},
            "common_schema": C.COMMON_SCHEMA, "common": {}}


@pytest.mark.parametrize("download_status", [0, 1])
def test_fetch_index_replaces_existing_only_after_success(tmp_path, monkeypatch, download_status):
    current = tmp_path / "link_index.pkl"
    old = {"meta": {"date": "previous", "commit": "old"}}
    new = {"meta": {"date": "latest", "commit": "new"}}
    current.write_bytes(pickle.dumps(old))
    monkeypatch.setattr(C, "ROOT", tmp_path)
    monkeypatch.setattr(C, "INDEX", current)

    def gh(args, **kwargs):
        if args[2] == "list":
            return subprocess.CompletedProcess(args, 0, '[{"databaseId": 1, "createdAt": "today"}]', "")
        destination = Path(args[-1]) / current.name
        assert not destination.exists()
        destination.write_bytes(pickle.dumps(new))
        assert C.load_index() == old
        return subprocess.CompletedProcess(args, download_status, "", "download interrupted")

    monkeypatch.setattr(C.subprocess, "run", gh)
    if download_status:
        with pytest.raises(SystemExit, match="download interrupted"):
            C.fetch_index()
    else:
        assert C.fetch_index() == 0
    assert C.load_index() == (old if download_status else new)
    assert list(tmp_path.iterdir()) == [current]


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
    obj.write_bytes(provider_coff())
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
    monkeypatch.setattr(C, "linked_since", lambda census: (frozenset(), "", "no tracked link census"))
    C.publish(index(blockers=blockers, sizes=sizes), queue)
    monkeypatch.setattr(claims, "_fetch_master", lambda: "tip")
    monkeypatch.setattr(C, "_git", lambda *a, **k: "changed.cpp\n" if a[0] == "diff"
                        else f"Claim-Lease: 0x{C.claim_key('landed'):08X}=abcdef12\n")
    monkeypatch.setattr(claims, "owner", lambda: "me")
    monkeypatch.setattr(claims, "active", lambda: {})
    assert C.main(["next", "--no-claim", "--queue", str(queue)]) == 0
    out = capsys.readouterr().out
    assert "link queue #4 (census c; no tracked link census): open" in out and "1 family strings" in out
    assert "1 every file linked or changed since the census" in out
    assert C.main(["next", "--no-claim", "--family", "strings", "--queue", str(queue)]) == 0
    assert "??1AsciiString@@QAE@XZ" in capsys.readouterr().out


def test_refresh_replaces_a_passed_objects_census_definitions(monkeypatch):
    """A duplicate removed from b.obj since the census no longer charges a.obj."""
    import link_census
    from types import SimpleNamespace
    ix = index(strong={"f": [0, 1], "g": [1]}, comdat={"h": [(1, "x", None)]})
    assert C.duplicate("f", 0, True, 0, ix)
    monkeypatch.setattr(link_census, "object_facts", lambda obj, truth, **kwargs: ([], ["g"], [], []))
    monkeypatch.setattr(link_census, "common_definitions", lambda obj, **kwargs: {})
    C.refresh(ix, [SimpleNamespace(name="b.obj", read_bytes=lambda: b"frozen"), SimpleNamespace(name="new.obj")], None)
    assert ix["strong"] == {"f": [0], "g": [1]} and ix["comdat"] == {"h": []}
    assert not C.duplicate("f", 0, True, 0, ix)


class _Obj:
    """A census object stand-in: a name, and a path-like for messages."""
    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return self.name

    def __hash__(self):
        return hash(self.name)

    def __eq__(self, other):
        return getattr(other, "name", None) == self.name


tmp_receipts = Path(__import__("tempfile").mkdtemp()) / "refresh_inputs.json"


def _refreshable(monkeypatch, objects, facts, *, stale=(), missing=(), after=None, dirty=(), compiled=None):
    """Patch link_census so refresh_current sees `objects` (current ledger,
    link order) with `facts`; returns the census index it refreshes."""
    import alias_guard
    import build
    import link_census
    objs = [_Obj(n) for n in objects]
    sources = {o: Path(f"game/{o.name.replace('.obj', '.cpp')}") for o in objs + [_Obj(n) for n in missing]}
    state = {"present": objs, "missing": [_Obj(n) for n in missing], "stale": [_Obj(n) for n in stale]}

    def compile_rows(rows, need, input_proof=None):
        assert input_proof is not None          # the refresh's own receipts prove the inputs
        (compiled if compiled is not None else []).append(sorted(str(n) for n in need))
        if after is not None:
            state.update(after)
        return {}
    monkeypatch.setattr(link_census, "ledger", lambda: [])
    monkeypatch.setattr(link_census, "_object_sources", lambda rows: sources)
    monkeypatch.setattr(link_census, "objects", lambda rows: (state["present"], state["missing"]))
    monkeypatch.setattr(link_census, "stale_objects", lambda present, srcs, why=None: state["stale"])
    monkeypatch.setattr(link_census, "verify_data_objects", lambda: None)
    monkeypatch.setattr(link_census, "read_facts", lambda present, rows: [facts[o.name] for o in present])
    monkeypatch.setattr(link_census, "ledger_owners", lambda rows: {})
    monkeypatch.setattr(link_census, "rejudge_weak_facts",
                        lambda present, facts, rows, kept, owners: pytest.fail("no verified /MAP receipt"))
    monkeypatch.setattr(link_census, "common_definitions", lambda obj, **kw: {})
    monkeypatch.setattr(alias_guard, "object_aliases", lambda obj: [])
    monkeypatch.setattr(build, "compile_rows", compile_rows)
    monkeypatch.setattr(C, "refresh_dirty", lambda paths: list(dirty))
    monkeypatch.setattr(link_census, "_refresh_missing_search_root_receipts", lambda rows, out, receipts: None)
    monkeypatch.setattr(link_census, "_INPUT_RECEIPTS", None)
    monkeypatch.setattr(C, "REFRESH_RECEIPTS", tmp_receipts)
    ix = index(strong={"f": [0, 1]})
    ix["selection"] = {"exceptions": {}, "owners": {}}
    return ix


def test_refresh_rejudges_every_current_object_without_mtimes(monkeypatch):
    """Review 2026-10-15 round 1 (A, B, coverage): every current ledger object
    is re-read and re-judged with current truth -- not only stale or recently
    rebuilt ones -- so a frozen object's COMDAT verdict the census left None is
    judged now; a source the ledger dropped (c.obj) leaves no definitions and a
    source added since the census (d.obj) is in the tables."""
    facts = {"a.obj": ([("g", "dGEN", 4, "wrong")], [], [], []),
             "b.obj": ([("g", "dMINE", 4, "retail")], [], [], []),
             "d.obj": ([], ["h"], [], [])}
    ix = _refreshable(monkeypatch, ["a.obj", "b.obj", "d.obj"], facts)
    C.refresh_current(ix)
    assert ix["objects"] == ["a.obj", "b.obj", "d.obj"]
    assert ix["strong"] == {"h": [2]} and ix["comdat"]["g"] == [(0, "dGEN", "wrong"), (1, "dMINE", "retail")]
    assert ix["refreshed"] and "weak_inventory" not in ix          # census receipts never rewritten


def test_refreshed_index_blocks_the_kept_copy_current_truth_rejects(monkeypatch):
    """Review B: keep_rule kept the first copy dGEN; the census verdict was None
    (judge_selected 'unknown' -> LINKS). Re-judged it is 'wrong' -> selected."""
    facts = {"gen.obj": ([("g", "dGEN", 4, "wrong")], [], [], []),
             "mine.obj": ([("g", "dMINE", 4, "retail")], [], [], [])}
    ix = _refreshable(monkeypatch, ["gen.obj", "mine.obj"], facts)
    C.refresh_current(ix)
    fact = ([("g", "dMINE", 4, "retail")], [], [], [])
    assert C.wrong_selected(_Obj("mine.obj"), fact, 1, 1, ix) == ["g"]


def test_an_unprovable_kept_definition_is_preview_unknown_only_where_its_definers_changed(monkeypatch):
    """Review round 2 (1) + the 2026-10-16 LINKED rule: 5,084 names judge
    'unknown' in today's census; one whose definers did not change keeps the
    census's non-blocking result (no false loss); a changed one is LINKED
    PREVIEW UNKNOWN, never a pass and never a proven loss."""
    fact = ([("g", "dB", 4, None)], [], [], [])
    census = index(comdat={"g": [(0, "dA", None), (1, "dB", None)]})
    census["selection"] = {"exceptions": {}, "owners": {}}
    unknown = []
    assert C.wrong_selected(_Obj("b.obj"), fact, 1, 1, census, unknown=unknown) == [] and unknown == []
    census["selection"]["changed"] = {"g"}
    assert C.wrong_selected(_Obj("b.obj"), fact, 1, 1, census, unknown=unknown) == [] and unknown == ["g"]


def test_changed_definers_compares_object_kind_and_digest():
    old = index(strong={"s": [0]}, comdat={"g": [(0, "dA", None), (1, "dB", None)], "k": [(2, "dK", None)]})
    new = {"objects": ["a.obj", "b.obj", "c.obj"], "strong": {"s": [0]},
           "comdat": {"g": [(0, "dA", "wrong"), (1, "dB2", None)], "k": [(2, "dK", "retail")]}}
    assert C.changed_definers(old, new) == {"g"}       # a verdict alone is no change


def test_refresh_runs_the_census_weak_rejudge_on_its_map_holders(monkeypatch):
    import link_census
    facts = {"a.obj": ([], [], [], []), "b.obj": ([], [], [], [])}
    ix = _refreshable(monkeypatch, ["a.obj", "b.obj"], facts)
    seen = []
    monkeypatch.setattr(C, "census_kept", lambda selection: {"w": "a.obj"})
    monkeypatch.setattr(link_census, "rejudge_weak_facts",
                        lambda present, f, rows, kept, owners: seen.append(kept) or f)
    C.refresh_current(ix)
    assert seen == [{"w": "a.obj"}]


def test_refresh_refuses_a_big_compile_without_the_flag(monkeypatch):
    many = [f"s{i}.obj" for i in range(C.REFRESH_COMPILE_LIMIT + 1)]
    compiled = []
    ix = _refreshable(monkeypatch, many, {n: ([], [], [], []) for n in many}, stale=many, compiled=compiled)
    with pytest.raises(SystemExit, match="--refresh-compile"):
        C.refresh_current(ix)
    assert compiled == []
    ix = _refreshable(monkeypatch, many, {n: ([], [], [], []) for n in many}, stale=many, compiled=compiled,
                      after={"stale": []})
    C.refresh_current(ix, allow_compile=True)
    assert len(compiled) == 1 and len(compiled[0]) == len(many)


def test_refresh_refuses_objects_still_stale(monkeypatch):
    ix = _refreshable(monkeypatch, ["a.obj"], {"a.obj": ([], [], [], [])}, stale=["a.obj"],
                      after={"stale": [_Obj("a.obj")]})
    with pytest.raises(SystemExit, match="still stale"):
        C.refresh_current(ix)


def test_refresh_previews_without_objects_still_missing_as_the_census_does(monkeypatch, capsys):
    """Review round 2 (3): one failed ledger compile must not make --refresh always refuse."""
    import build
    ix = _refreshable(monkeypatch, ["a.obj"], {"a.obj": ([], ["h"], [], [])}, missing=["gone.obj"],
                      after={"missing": [_Obj("gone.obj")]})

    def failing(rows, need, input_proof=None):
        raise SystemExit("cl.exe failed on game/gone.cpp")
    monkeypatch.setattr(build, "compile_rows", failing)
    C.refresh_current(ix)
    assert ix["objects"] == ["a.obj"] and "1 ledger object(s) missing" in capsys.readouterr().err


def test_refresh_refuses_a_dirty_tree_outside_the_checked_files(monkeypatch):
    ix = _refreshable(monkeypatch, ["a.obj"], {"a.obj": ([], [], [], [])}, dirty=["game/other.cpp"])
    with pytest.raises(SystemExit, match="differ from HEAD"):
        C.refresh_current(ix, checked=["game/a.cpp"])


def test_refresh_dirty_ignores_only_the_checked_files(monkeypatch):
    out = " M game/a.cpp\0?? game/new.cpp\0R  game/to.cpp\0game/from.cpp\0 R game/wt.cpp\0game/wfrom.cpp\0"
    calls = []
    monkeypatch.setattr(C, "_git", lambda *a, **k: calls.append(a) or out)
    assert C.refresh_dirty({str(C.ROOT / "game/a.cpp")}) == ["game/new.cpp", "game/to.cpp", "game/wt.cpp"]
    assert C.refresh_dirty({"./game/a.cpp", "game/new.cpp"}) == ["game/to.cpp", "game/wt.cpp"]
    # the ledgers are not part of the check: add_match/re_log edit them between previews
    assert "targets/game/reverse" not in calls[0]


def test_refresh_drops_build_recompile_only(monkeypatch):
    monkeypatch.setenv("BUILD_RECOMPILE_ONLY", "x.cpp")
    ix = _refreshable(monkeypatch, ["a.obj"], {"a.obj": ([], [], [], [])})
    C.refresh_current(ix)
    import os
    assert "BUILD_RECOMPILE_ONLY" not in os.environ


def test_refresh_keeps_measured_holders_and_blocks_unmeasured_ones(monkeypatch):
    facts = {"a.obj": ([("g", "d1", 4, None)], [], [], []), "b.obj": ([("g", "d2", 4, None)], [], [], [])}
    ix = _refreshable(monkeypatch, ["a.obj", "b.obj"], facts)
    ix["strong"], ix["comdat"] = {}, {"g": [(0, "d1", None), (1, "d2-old", None)]}
    ix["selection"]["exceptions"] = {"g": 1}
    C.refresh_current(ix)
    assert ix["selection"]["exceptions"] == {} and ix["selection"]["stale"] == {"g"}
    unknown = []
    assert C.wrong_selected(_Obj("a.obj"), facts["a.obj"], 0, 0, ix, unknown=unknown) == [] and unknown == ["g"]


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
    monkeypatch.setattr(C, "apply_selection_rule", lambda *a, **k: (set(), set()))
    monkeypatch.setattr(C, "source_bytes", lambda sources: {s: 100 for s in sources})
    monkeypatch.setattr(C, "check_object", lambda *a: {k: [] for k in
                        ("unresolved", "duplicates", "comdat", "addresses", "selected")})
    return C.main(names)


def test_a_file_named_twice_counts_once(monkeypatch, tmp_path, capsys):
    assert _preview(monkeypatch, tmp_path, ["a.obj", "a.obj"]) == 0
    assert "1 of 1 link cleanly; LINKED 0 -> 100 bytes" in capsys.readouterr().out


def _coff(defines=(), refers=()):
    import struct
    body = b"\xc3"
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 60 + len(body), len(defines) + len(refers), 0, 0)
    sec = b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x60500020)
    symbols = b"".join(name.encode().ljust(8, b"\0") + struct.pack("<IhHBB", 0, 1 if name in defines else 0, 0x20, 2, 0)
                       for name in (*defines, *refers))
    return header + sec + body + symbols + struct.pack("<I", 4)


def _new_files(monkeypatch, tmp_path, objects, order):
    """A census of a.obj and b.obj (a.obj defines _g); `objects` {name: coff}
    are new files whose current link order is `order`. Nothing but compiling
    is stubbed: refresh and check_object run for real."""
    import link_census
    ix = {**index(strong={"_g": [0]}), "objects": ["a.obj", "b.obj"], "aliases": {},
          "selection": {"exceptions": {}, "owners": {}},
          "excuses": {"runtime": set(), "imported": {}, "stubs": {}}}
    for name, raw in objects.items():
        (tmp_path / name).write_bytes(raw)
    monkeypatch.setattr(C, "load_index", lambda: ix)
    monkeypatch.setattr(C, "resolve", lambda path, _: (path, tmp_path / path.replace(".cpp", ".obj")))
    monkeypatch.setattr(C, "note_evaluated", lambda *a: None)
    monkeypatch.setattr(link_census, "ledger", lambda: [])
    monkeypatch.setattr(link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(link_census, "link_order", lambda rows, data: [Path(name) for name in order])
    monkeypatch.setattr(C, "source_bytes", lambda sources: {s: 100 for s in sources})
    # the census objects' inputs are known and unchanged since the census
    monkeypatch.setattr(C, "changed_since", lambda commit: _since(()))
    monkeypatch.setattr(C, "MOVED_CACHE", tmp_path / "moved_cache.json")
    monkeypatch.setattr(C, "object_inputs", lambda obj, sources, receipts: {obj.name})
    return ix


def test_two_new_files_defining_one_exclusive_symbol_both_collide(monkeypatch, tmp_path, capsys):
    """Every new object is placed and refreshed in a normal check, so two new
    files defining one symbol both fail as link.exe fails them (LNK2005), and
    a new file's reference resolves against a census definition."""
    ix = _new_files(monkeypatch, tmp_path, {"n1.obj": _coff(["_f"], ["_g"]), "n2.obj": _coff(["_f"])},
                    ["a.obj", "n1.obj", "b.obj", "n2.obj"])
    assert C.main(["n1.cpp", "n2.cpp"]) == 1
    out = capsys.readouterr().out
    assert "new since census c, previewed at its link-order place: n1.cpp, n2.cpp" in out
    assert out.count("duplicate   _f") == 2 and "unresolved" not in out
    assert ix["objects"] == ["a.obj", "n1.obj", "b.obj", "n2.obj"]


def test_a_new_file_links_when_its_references_resolve_in_the_census(monkeypatch, tmp_path, capsys):
    _new_files(monkeypatch, tmp_path, {"n1.obj": _coff(["_f"], ["_g"])}, ["n1.obj", "a.obj", "b.obj"])
    assert C.main(["n1.cpp"]) == 0
    assert "n1.cpp: LINKS  LINKED 0 -> 100 bytes" in capsys.readouterr().out


def test_census_only_still_reads_a_new_file_s_own_object(monkeypatch, tmp_path, capsys):
    _new_files(monkeypatch, tmp_path, {"n1.obj": _coff(["_g"])}, ["a.obj", "b.obj", "n1.obj"])
    assert C.main(["--census-only", "n1.cpp"]) == 1
    assert "duplicate   _g" in capsys.readouterr().out


def test_a_new_file_no_matched_row_places_is_refused(monkeypatch, tmp_path):
    _new_files(monkeypatch, tmp_path, {"n1.obj": _coff(["_f"])}, ["a.obj", "b.obj"])
    with pytest.raises(SystemExit, match="no matched ledger or data row places it.*n1.cpp"):
        C.main(["n1.cpp"])


def test_a_new_object_goes_to_its_link_order_place_not_last():
    """Which definition is first decides a duplicate: a new SELECT_ANY copy
    linked before an ANY copy that precedes an exclusive one collides, the
    same copy linked last folds silently (??4AsciiString@@QAEAAV0@PBD@Z)."""
    ix = {**index(strong={"x": [1]}, comdat={"x": [(0, "d", None)]}), "objects": ["a.obj", "b.obj"],
          "aliases": {"y": [(1, "x")]}, "common": {"z": [(1, 4)]},
          "selection": {"exceptions": {"x": 1, "w": None}, "owners": {}}}
    C.place_new(ix, ["n.obj"], ["n.obj", "a.obj", "b.obj"])
    assert ix["objects"] == ["n.obj", "a.obj", "b.obj"]
    assert ix["strong"] == {"x": [2]} and ix["comdat"] == {"x": [(1, "d", None)]}
    assert ix["aliases"] == {"y": [(2, "x")]} and ix["common"] == {"z": [(2, 4)]}
    assert ix["selection"]["exceptions"] == {"x": 2, "w": None}
    assert C.duplicate("x", 0, False, 0, ix)
    last = {**index(strong={"x": [1]}, comdat={"x": [(0, "d", None)]}), "objects": ["a.obj", "b.obj"]}
    C.place_new(last, ["n.obj"], ["a.obj", "b.obj", "n.obj"])
    assert last["objects"][2] == "n.obj" and not C.duplicate("x", 2, False, 2, last)


def test_an_object_with_no_known_source_outside_the_census_is_refused(tmp_path):
    obj = tmp_path / "handmade.obj"
    obj.write_bytes(_coff(["_f"]))
    with pytest.raises(SystemExit, match="no source is known"):
        C.resolve(str(obj), index())


# Prediction-only previews avoid building global weak-provider contexts.

PREDICTION = ("prediction", "wrong_comdat", "strong_duplicate", "common_primary", "local_primary")
INVALID_RECEIPTS = ("missing_addresses", "missing_locations", "missing_ambiguous", "inconsistent_keys",
                    "wrong_address_type", "wrong_raw_holder", "mismatched_receipt", "missing_receipt")
VALID_RECEIPTS = ("actual", "alias_same", "foreign_primary", "stale_inventory", "stale_truth",
                  "stale_inputs", "stale_schema", "stale_root", "stale_token")
MALFORMED = ("strong_oob", "strong_negative_oob", "strong_position_type", "strong_rows_type",
             "comdat_oob", "comdat_position_type", "comdat_entry_short", "comdat_entries_type",
             "object_unhashable", "owners_type", "owner_members_type", "exceptions_type",
             "exception_unhashable", "selection_none", "compound_selection", "compound_missing_comdat")


def make_case(module, root, mode):
    """Real COFF and independent RetailTruth; no compiler or production writes."""
    raw, truth, _ = fixture()
    owner, table = root / "owner.obj", root / "table.obj"
    owner.write_bytes(provider_coff())
    table.write_bytes(raw)
    selection = {"owners": {"default": {owner.name}}, "exceptions": {}}
    if mode in INVALID_RECEIPTS + VALID_RECEIPTS:
        selection.update(weak_kept={"default": owner.name}, weak_locations={"default": owner.name},
                         weak_addresses={"default": 0x401040}, weak_ambiguous=set())
        if mode in ("alias_same", "foreign_primary"):
            holder = owner.name if mode == "alias_same" else "foreign.obj"
            selection["weak_kept"]["primary"] = holder
            selection["weak_locations"]["primary"] = holder
            selection["weak_addresses"]["primary"] = 0x401040 if mode == "alias_same" else 0x402000
    objects = [owner, table]
    index = module.index_tables(objects, [L.object_facts(obj, truth) for obj in objects], selection)
    index["excuses"] = {"runtime": set(), "imported": {}, "stubs": {}}
    module.refresh(index, objects, truth)
    selection = index["selection"]
    if mode == "wrong_comdat":
        index["objects"].append("foreign.obj")
        index["comdat"]["table"].append((2, "other-retail-copy", "retail"))
    elif mode == "strong_duplicate":
        index["objects"].append("foreign.obj")
        index["strong"]["table"] = [2]
    elif mode == "common_primary":
        index["common"]["primary"] = [(0, 4)]
    elif mode == "local_primary":
        table.write_bytes(add_symbol(raw, "primary"))
    elif mode.startswith("missing_"):
        selection.pop("weak_" + mode[len("missing_"):])
    elif mode == "inconsistent_keys":
        selection["weak_addresses"]["foreign"] = 0x402000
    elif mode == "wrong_address_type":
        selection["weak_addresses"]["default"] = "00401040"
    elif mode == "wrong_raw_holder":
        selection["weak_locations"]["default"] = "foreign.obj"
    elif mode == "mismatched_receipt":
        selection["weak_receipt"] = "wrong"
    elif mode == "stale_inventory":
        owner.write_bytes(provider_coff(b"\x90"))
    elif mode == "stale_truth":
        index["weak_truth"] = "previous-truth"
    elif mode == "stale_inputs":
        truth._weak_inputs = "previous-inputs"
    elif mode == "stale_schema":
        index["weak_schema"] = module.WEAK_SCHEMA - 1
    elif mode == "stale_root":
        index["weak_root"] = str(root / "other")
    elif mode == "stale_token":
        index["_weak_token"] = object()
    elif mode == "strong_oob":
        index["strong"]["unrelated"] = [99]
    elif mode == "strong_negative_oob":
        index["strong"]["unrelated"] = [-99]
    elif mode == "strong_position_type":
        index["strong"]["unrelated"] = ["0"]
    elif mode == "strong_rows_type":
        index["strong"]["unrelated"] = 1
    elif mode == "comdat_oob":
        index["comdat"]["unrelated"] = [(99, "d", "retail")]
    elif mode == "comdat_position_type":
        index["comdat"]["unrelated"] = [("0", "d", "retail")]
    elif mode == "comdat_entry_short":
        index["comdat"]["unrelated"] = [(0, "d")]
    elif mode == "comdat_entries_type":
        index["comdat"]["unrelated"] = None
    elif mode == "object_unhashable":
        index["objects"].append([])
    elif mode == "owners_type":
        selection["owners"] = []
    elif mode == "owner_members_type":
        selection["owners"]["default"] = 1
    elif mode == "exceptions_type":
        selection["exceptions"] = []
    elif mode == "exception_unhashable":
        selection["exceptions"]["default"] = []
    elif mode == "selection_none":
        index["selection"] = None
    elif mode == "compound_selection":
        index["strong"]["unrelated"] = [99]
        index["selection"] = None
    elif mode == "compound_missing_comdat":
        index["strong"]["unrelated"] = [99]
        del index["comdat"]
    truth._cache.clear()
    return table, index, truth


def observe(module, obj, index, truth, *, force_full_context=False):
    """Capture the complete preview and actual fact verdicts with empty cache."""
    truth._cache.clear()
    original_facts = L.object_facts
    facts = []
    def record(*args, **kwargs):
        if force_full_context:
            kwargs["weak_context"] = module.weak_context(index, truth)
        result = original_facts(*args, **kwargs)
        facts.append(tuple(result))
        return result
    with patch.object(module, "weak_context", wraps=module.weak_context) as full:
        with patch.object(L, "object_facts", side_effect=record):
            try:
                output = {"result": module.check_object(obj, index, truth)}
            except (IndexError, TypeError, ValueError, AttributeError) as exc:
                output = {"exception": type(exc).__name__, "message": str(exc)}
    return output, facts, full.call_count


@pytest.mark.parametrize("mode", PREDICTION + INVALID_RECEIPTS)
def test_prediction_result_equals_full_context_without_weak_promotion(tmp_path, monkeypatch, mode):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj, index, truth = make_case(C, tmp_path, mode)
    # Independent truth state ensures neither branch reuses the other's verdict.
    reference_truth = copy.deepcopy(truth)
    optimized, facts, calls = observe(C, obj, index, truth)
    reference, original_facts, _ = observe(C, obj, index, reference_truth, force_full_context=True)
    assert optimized == reference and facts == original_facts
    assert calls == 0
    assert next(copy_[3] for copy_ in facts[0][0] if copy_[0] == "table") == "unknown"
    if mode == "wrong_comdat":
        assert optimized["result"]["comdat"]
    if mode == "strong_duplicate":
        assert optimized["result"]["duplicates"] == ["table"]


@pytest.mark.parametrize("mode", VALID_RECEIPTS)
def test_actual_receipt_keeps_full_validation_and_stale_proofs_fail(tmp_path, monkeypatch, mode):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj, index, truth = make_case(C, tmp_path, mode)
    reference_truth = copy.deepcopy(truth)
    result, facts, calls = observe(C, obj, index, truth)
    reference, original_facts, _ = observe(C, obj, index, reference_truth, force_full_context=True)
    assert result == reference and facts == original_facts and calls == 1
    expected = "retail" if mode in ("actual", "alias_same") else "unknown"
    assert next(copy_[3] for copy_ in facts[0][0] if copy_[0] == "table") == expected


@pytest.mark.parametrize("mode", MALFORMED)
def test_malformed_global_tables_keep_original_failure(tmp_path, monkeypatch, mode):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj, index, truth = make_case(C, tmp_path, mode)
    reference_truth = copy.deepcopy(truth)
    result, _, calls = observe(C, obj, index, truth)
    reference, _, _ = observe(C, obj, index, reference_truth, force_full_context=True)
    assert "exception" in result and result == reference and calls == 1


def test_mapping_subclass_preserves_original_access_pattern(tmp_path, monkeypatch):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj, index, truth = make_case(C, tmp_path, "prediction")
    class CustomIndex(dict):
        def get(self, key, *args):
            if key == "objects":
                raise AssertionError("new get access on noncanonical index")
            return super().get(key, *args)
    index = CustomIndex(index)
    result, facts, calls = observe(C, obj, index, truth)
    reference, original_facts, _ = observe(C, obj, index, copy.deepcopy(truth), force_full_context=True)
    assert result == reference and facts == original_facts and calls == 1


def _status(tmp_path, monkeypatch, status_commit, linked):
    """A tracked link_status.csv measured at `status_commit` with `linked` files linked."""
    import link_census
    path = tmp_path / "link_status.csv"
    path.write_text("source,linked\n" + "".join(f"{s},{'yes' if s in linked else 'no'}\n"
                                                for s in ("a.cpp", "b.cpp", "c.cpp")), encoding="utf-8")
    monkeypatch.setattr(link_census, "STATUS", path)
    monkeypatch.setattr(link_census, "read_history", lambda: [{"commit": status_commit}] if status_commit else [])


def test_linked_since_trusts_only_a_status_at_or_after_the_census(tmp_path, monkeypatch):
    _status(tmp_path, monkeypatch, "bbbbbbbbbb", {"a.cpp"})
    order = {("aaaaaaaaaa", "bbbbbbbbbb"): True, ("cccccccccc", "bbbbbbbbbb"): False}
    monkeypatch.setattr(C, "_is_ancestor", lambda old, new: order.get((old, new)))
    assert C.linked_since("bbbbbbbbbbbbbbbb")[0] == {"a.cpp"}            # the same census, abbreviated
    assert C.linked_since("aaaaaaaaaa") == ({"a.cpp"}, "bbbbbbbbbb", "")   # a later census
    linked, status, note = C.linked_since("cccccccccc")                   # an older one
    assert linked == frozenset() and "not after census cccccccccc" in note
    linked, _, note = C.linked_since("dddddddddd")                        # one git cannot order
    assert linked == frozenset() and "cannot order" in note
    _status(tmp_path, monkeypatch, "", set())
    assert C.linked_since("aaaaaaaaaa")[0] == frozenset()


def test_queue_and_serve_drop_files_a_later_census_saw_link(tmp_path, monkeypatch, capsys):
    import claims
    blockers = {s: {"object": "a.obj", "linked": False, "unresolved": [name], "duplicates": [], "losers": [],
                    "addresses": 0}
                for s, name in (("a.cpp", "gone"), ("b.cpp", "shared"), ("c.cpp", "shared"))}
    sizes = {"a.cpp": 900, "b.cpp": 300, "c.cpp": 200}
    queue = tmp_path / "q.csv"
    monkeypatch.setattr(C, "linked_since", lambda census: (frozenset(), "", "no tracked link census"))
    C.publish(index(blockers=blockers, sizes=sizes), queue)        # the census's own queue: both rows
    monkeypatch.setattr(C, "linked_since", lambda census: (frozenset({"a.cpp"}), "later", ""))
    assert [r["name"] for r in C.queue_rows(index(blockers=blockers, sizes=sizes), {"a.cpp"})] == ["shared"]
    monkeypatch.setattr(claims, "_fetch_master", lambda: "tip")
    monkeypatch.setattr(C, "_git", lambda *a, **k: "b.cpp\n" if a[0] == "diff" else "")
    monkeypatch.setattr(claims, "owner", lambda: "me")
    monkeypatch.setattr(claims, "active", lambda: {})
    assert C.main(["next", "--no-claim", "--queue", str(queue)]) == 0
    out = capsys.readouterr().out
    # a.cpp linked at a later census; b.cpp changed, but c.cpp still stands on the census's evidence
    assert "#2 (census c; files linked at census later dropped): shared" in out
    assert "files: 1 open; 1 other(s) linked or changed since the census: c.cpp" in out
    assert "1 linked at census later" in out
    monkeypatch.setattr(C, "_git", lambda *a, **k: "b.cpp\nc.cpp\n" if a[0] == "diff" else "")
    assert C.main(["next", "--no-claim", "--queue", str(queue)]) == 1
    assert "every file linked or changed since the census" in capsys.readouterr().out


def _near_index():
    blank = {"duplicates": [], "losers": [], "wrong_selected": [], "alias_target": [], "addresses": 0,
             "linked": False}
    return {"blockers": {s: {**blank, "unresolved": ["?d_00000500@@YAXXZ"]}
                         for s in ("game/T/a.cpp", "game/T/b.cpp", "game/T/c.cpp")},
            "bytes": {"game/T/a.cpp": 30, "game/T/b.cpp": 20, "game/T/c.cpp": 10}}


class _Judge:
    def __init__(self, target="?one@@YAXXZ", note="", address=0x500):
        self.target, self.note, self.address = target, note, address

    def respell(self, name, caller=None):
        return self.target, self.note, ""

    def pinned(self, name):
        return self.address

    def normal(self, address):
        return address


def test_near_drops_files_linked_later_or_blocked_at_this_census():
    skipped = collections.Counter()
    rows = C.near_rows(_near_index(), _Judge(), skipped=skipped, linked={"game/T/a.cpp"},
                       blocked={"game/T/b.cpp": "blocked 0x00000700 at census c"})
    assert [r["source"] for r in rows] == ["game/T/c.cpp"]
    assert skipped == {C.LINKED_LATER: 1, C.BLOCKED_NOW: 1}


def _records(*verdicts):
    """re_log.latest_link_records() of these verdict rows, in log order."""
    import re_log
    return {(int(fields[1], 16), fields[0], re_log.census_source_of(fields[4])): (index, list(fields))
            for index, fields in enumerate(verdicts)}


def test_a_blocked_verdict_stands_only_at_its_own_census():
    import re_log
    callers = {"game/T/b.cpp": [_row("?b@@YAXXZ", 0x700, "game/T/b.cpp")],
               "game/T/c.cpp": [_row("?c@@YAXXZ", 0x800, "game/T/c.cpp")],
               "game/T/d.cpp": [_row("?d@@YAXXZ", 0x900, "game/T/d.cpp")]}
    latest = _records(["?b@@YAXXZ", "0x00000700", "9", "blocked", "link_check t=2 census=5f10bce6ba"],
                      ["?c@@YAXXZ", "0x00000800", "9", "blocked", "link_check t=2 census=7d308168db"],
                      ["?d@@YAXXZ", "0x00000900", "9", "landed", "link_check LINKS census=5f10bce6ba"])
    assert set(C.blocked_files(callers, latest, "5f10bce6ba0123")) == {"game/T/b.cpp"}
    assert set(C.blocked_files(callers, latest, "7d308168db")) == {"game/T/c.cpp"}
    assert C.blocked_files(callers, latest, "") == {}
    assert "blocked" in re_log.DEFERRED_STATUSES


def test_a_blocked_verdict_blocks_only_the_row_and_file_it_was_judged_in():
    """385 RVAs carry rows of several sources (0x0013A450: W3DBufferManager.cpp
    and wwmemlog.cpp); a verdict on one never suppresses the other (GPT-6.1-Sol, round 3)."""
    w3d, log = "game/W/W3DBufferManager.cpp", "game/L/wwmemlog.cpp"
    callers = {w3d: [_row("?alloc@W3DBufferManager@@QAEXXZ", 0x13A450, w3d)],
               log: [_row("?alloc@WWMemLog@@QAEXXZ", 0x13A450, log)]}
    blocked = ["?alloc@W3DBufferManager@@QAEXXZ", "0x0013A450", "9", "blocked",
               f"link_check t=2 census=5f10bce6ba census-source={w3d}"]
    assert set(C.blocked_files(callers, _records(blocked), "5f10bce6ba")) == {w3d}
    # a verdict judged in a file the row has since left blocks neither
    moved = blocked[:4] + ["link_check t=2 census=5f10bce6ba census-source=game/W/Old.cpp"]
    assert C.blocked_files(callers, _records(moved), "5f10bce6ba") == {}
    # a later resolution naming no file releases it
    landed = blocked[:3] + ["landed", "link_check LINKS 0 -> 9"]
    assert C.blocked_files(callers, _records(blocked, landed), "5f10bce6ba") == {}
    # one name at one RVA in two sources: a verdict naming no file is unsure, so it blocks nothing
    twins = {source: [_row("?alloc@Shared@@QAEXXZ", 0x13A450, source)] for source in callers}
    unnamed = ["?alloc@Shared@@QAEXXZ", "0x0013A450", "9", "blocked", "link_check t=2 census=5f10bce6ba"]
    assert C.blocked_files(twins, _records(unnamed), "5f10bce6ba", shared={(0x13A450, "?alloc@Shared@@QAEXXZ")}) == {}
    assert len(C.blocked_files(twins, _records(unnamed), "5f10bce6ba")) == 2   # the same pair, not shared
    # GPT-6.1-Sol, round 4: blocks judged in two files at one RVA both stand
    one = unnamed[:4] + [f"link_check t=2 census=5f10bce6ba census-source={w3d}"]
    two = unnamed[:4] + [f"link_check t=2 census=5f10bce6ba census-source={log}"]
    shared = {(0x13A450, "?alloc@Shared@@QAEXXZ")}
    assert set(C.blocked_files(twins, _records(one, two), "5f10bce6ba", shared)) == {w3d, log}


def test_latest_link_records_keeps_each_file_s_verdict_and_voids_the_row(tmp_path):
    import re_log
    log = tmp_path / "re_attempts.log"
    log.write_text("\r\n".join([
        "?a@@YAXXZ\t0x00000700\t9\tblocked\tlink_check census=5f10bce6ba census-source=game/A.cpp",
        "?a@@YAXXZ\t0x00000700\t9\tblocked\tlink_check census=5f10bce6ba census-source=game/B.cpp",
        "?a@@YAXXZ\t0x00000700\t9\tnote\tan annotation never votes"]) + "\r\n", encoding="utf-8")
    records = re_log.latest_link_records(log)
    assert set(records) == {(0x700, "?a@@YAXXZ", "game/A.cpp"), (0x700, "?a@@YAXXZ", "game/B.cpp")}
    with log.open("a", encoding="utf-8", newline="") as handle:
        handle.write("?a@@YAXXZ\t0x00000700\t9\tvoid\tboth rows were typed wrong\r\n")
    assert re_log.latest_link_records(log) == {}


def test_convention_reads_the_letter_after_the_scope():
    assert C.convention("??1QueuedDownload@@QAE@XZ") == "thiscall"
    assert C.convention("?getFoo@Bar@@QBEHXZ") == "thiscall"
    assert C.convention("?update@Module@@UAEXXZ") == "thiscall"
    assert C.convention("?parse@Store@@SAXPAVINI@@@Z") == "cdecl"     # static member
    assert C.convention("?releaseCodecState@@YAXPAPAUCodecState@@@Z") == "cdecl"
    assert C.convention("?Init@@YGXXZ") == "stdcall"
    assert C.convention("?f@C@@QAIXXZ") == "fastcall"
    assert C.convention("_memcpy") == "cdecl" and C.convention("_Sleep@4") == "stdcall"
    # a template scope is read by name_regression's full reader (GPT-6.1-Sol, round 5)
    assert C.convention("??A?$hash_map@VAsciiString@@H@_STL@@QAEAAHABVAsciiString@@@Z") == "thiscall"
    assert C.convention("?f@?$Box@H@@QAEXH@Z") == "thiscall" and C.convention("?g@?$Crate@H@@QAAXH@Z") == "cdecl"
    assert C.convention("?TheGlobalData@@3PAVGlobalData@@A") == ""                              # data
    # adjustor thunks encode an adjustment before the cv letter: unknown, never a wrong guess
    assert C.convention("?f@C@@W3AEXXZ") == "" and C.convention("?f@C@@W3AGXXZ") == ""
    assert C.convention("?f@C@@G7AEXXZ") == "" and C.convention("?f@C@@O3AEXXZ") == ""


def _ctx(rows_at, changed=(), refused=(), latest=None, census="5f10bce6ba"):
    by_rva, by_source = collections.defaultdict(list), collections.defaultdict(list)
    for row in rows_at:
        by_rva[int(row["target_rva"], 16)].append(row)
        by_source[row["source"]].append(row)
    return {"by_rva": by_rva, "by_source": by_source, "latest": latest or {}, "census": census,
            "changed": set(changed), "refused": set(refused)}


def _row(name, rva, source, notes=""):
    return {"name": name, "target_rva": f"0x{rva:08X}", "target_size": "128", "source": source, "notes": notes}


def test_packet_serves_a_plain_respelling_and_says_why_it_will_not_serve_the_rest():
    caller = _row("?queue@DownloadManager@@QAEXXZ", 0x627810, "game/D/Q.cpp")
    target = _row("??1QueuedDownload@@QAE@XZ", 0x500, "game/D/DownloadManager.cpp")
    near = {"source": "game/D/Q.cpp", "bytes": 334,
            "fixes": [("??1BfmeErasedValue_00627200@@QAE@XZ", "??1QueuedDownload@@QAE@XZ", "")]}
    judge = _Judge("??1QueuedDownload@@QAE@XZ")
    item = C.packet(near, judge, _ctx([caller, target]))
    assert item["verdict"] == "serve" and item["reasons"] == []
    assert item["callers"] == [caller] and item["packet_fixes"][0]["row"] == target
    assert item["packet_fixes"][0]["kind"] == "authored"
    assert item["packet_fixes"][0]["conventions"] == ("thiscall", "thiscall")
    # changed since the census, or in a family: another lane's (skip)
    assert C.packet(near, judge, _ctx([caller, target], changed={"game/D/Q.cpp"}))["verdict"] == "skip"
    family = {**near, "fixes": [("?d_00000500@@YAXXZ", "??1AsciiString@@QAE@XZ", "")]}
    item = C.packet(family, _Judge("??1AsciiString@@QAE@XZ"), _ctx([caller, target]))
    assert item["verdict"] == "skip" and "family strings" in item["reasons"][0]
    # a generated row, a convention change, a refused rename: more than a respelling (escalate)
    generated = _row("??1QueuedDownload@@QAE@XZ", 0x500, "game/gen_small/thunks_001.cpp")
    item = C.packet(near, judge, _ctx([caller, generated]))
    assert item["verdict"] == "escalate" and "gen_small" in item["reasons"][0]
    alias = _row("??1QueuedDownload@@QAE@XZ", 0x500, "game/D/DownloadManager.cpp",
                 "gen-alias;object-symbol=??1QueuedDownload@@QAE@XZ")
    assert "gen-alias" in C.packet(near, judge, _ctx([caller, alias]))["reasons"][0]
    cdecl = {**near, "fixes": [("?f@@YAXXZ", "??1QueuedDownload@@QAE@XZ", "")]}
    assert any("cdecl call to a thiscall row" in r for r in C.packet(cdecl, judge, _ctx([caller, target]))["reasons"])
    # a rename the hook refuses, whether the owner, an operator's owner or an argument type carries it
    for call, target in (("?release@CodecState@@QAEXXZ", "?release@BfmeThingJT@@QAEXXZ"),
                         ("??RCodecState@@QBE_NH@Z", "??RBfmeThingJT@@QBE_NH@Z"),
                         ("?releaseCodecState@@YAXPAPAUCodecState@@@Z", "?releaseCodecState@@YAXPAPAUBfmeThingJT@@@Z")):
        item = C.packet({**near, "fixes": [(call, target, "")]}, _Judge(target),
                        _ctx([caller, _row(target, 0x500, "game/D/D.cpp")], refused={("CodecState", "BfmeThingJT")}))
        assert item["verdict"] == "escalate", call
        assert "name_regression refuses CodecState -> BfmeThingJT" in item["reasons"], call
    # a call of another shape (here one class argument fewer) is a declaration change, not a respelling
    item = C.packet({**near, "fixes": [("?run@Display@@QAEXPBVImage@@H@Z", "?run@Bfme5Host@@QAEXHH@Z", "")]},
                    _Judge("?run@Bfme5Host@@QAEXHH@Z"), _ctx([caller, _row("?run@Bfme5Host@@QAEXHH@Z", 0x500, "D.cpp")]))
    assert item["verdict"] == "escalate" and "differ in shape" in item["reasons"][0]
    # same identifier counts, another declaration (GPT-6.1-Sol, round 2): a free function called
    # as a class's operator delete with one argument fewer, and a void(Class*) called as Class()
    for call, target in (("?bfmeDeleteVMP@@YAXPAXI@Z", "??3Gen007F0170@@SAXPAX@Z"),
                         ("?f@?$Box@H@@QAEXPAU1@@Z", "?g@?$Crate@M@@QAEXPAU1@@Z"),     # <int> against <float>, round 3
                         ("?bfmeCallDQF@BfmeSubDQF@@QAEXPAVBfmeOtherDQF@@@Z",
                          "?Get_Texture@ParticleBufferClass@@QBE?AVTextureHandleClass@1@XZ")):
        item = C.packet({**near, "fixes": [(call, target, "")]}, _Judge(target),
                        _ctx([caller, _row(target, 0x500, "D.cpp")]))
        assert item["verdict"] == "escalate" and any("differ in shape" in r for r in item["reasons"]), call
    # and a name the reader cannot parse (a function-pointer argument) is left to the hook
    pointer = "?run@Host@@QAEXP6AXXZ@Z"
    item = C.packet({**near, "fixes": [("?run@Shim@@QAEXP6AXXZ@Z", pointer, "")]}, _Judge(pointer),
                    _ctx([caller, _row(pointer, 0x500, "D.cpp")]))
    assert item["verdict"] == "escalate" and "cannot read" in item["reasons"][0]


def test_packet_marks_prior_verdicts_current_or_stale():
    caller = _row("?queue@DownloadManager@@QAEXXZ", 0x627810, "game/D/Q.cpp")
    target = _row("??1QueuedDownload@@QAE@XZ", 0x500, "game/D/DownloadManager.cpp")
    near = {"source": "game/D/Q.cpp", "bytes": 334,
            "fixes": [("??1BfmeErasedValue_00627200@@QAE@XZ", "??1QueuedDownload@@QAE@XZ", "")]}
    verdict = [caller["name"], "0x00627810", "334", "blocked", "link_check t=3 census=7d308168db"]
    item = C.packet(near, _Judge("??1QueuedDownload@@QAE@XZ"), _ctx([caller, target], latest=_records(verdict)))
    assert item["prior"][0]["when"] == "stale: census 7d308168db" and item["verdict"] == "serve"
    verdict[4] = "link_check t=3"
    assert C.packet(near, _Judge(), _ctx([caller, target], latest=_records(verdict)))["prior"][0]["when"] == "no census"


def test_near_lists_served_files_and_prints_a_packet(monkeypatch, capsys, tmp_path):
    ix = {**_near_index(), "meta": {"date": "d", "commit": "5f10bce6ba"}, "alias_schema": C.ALIAS_SCHEMA}
    monkeypatch.setattr(C, "INDEX", tmp_path / "link_census" / "link_index.pkl")   # its receipts land here
    rows = [_row("?a@@YAXXZ", 0x600, "game/T/a.cpp"), _row("?b@@YAXXZ", 0x700, "game/T/b.cpp"),
            _row("?c@@YAXXZ", 0x800, "game/T/c.cpp"), _row("?one@@YAXXZ", 0x500, "game/T/one.cpp")]
    monkeypatch.setattr(C, "load_index", lambda: ix)
    monkeypatch.setattr(C, "_git", lambda *a, **k: "game/T/c.cpp\n")
    monkeypatch.setattr(C, "linked_since", lambda census: (frozenset({"game/T/a.cpp"}), census, ""))
    monkeypatch.setattr(C, "alias_judge", lambda: _Judge())
    monkeypatch.setattr(C.link_census, "ledger", lambda: rows)
    import name_regression
    import re_log
    monkeypatch.setattr(re_log, "latest_link_records", lambda path=None: {})
    monkeypatch.setattr(name_regression, "refused_respellings", lambda pairs, root=None, ref="HEAD": set())
    assert C.main(["near"]) == 0
    out = capsys.readouterr().out
    assert "2 files, 30 bytes; 1 serve, 1 skip, 0 escalate; 1 skipped: linked at a later census" in out
    assert "game/T/b.cpp  [serve]" in out and "game/T/c.cpp" not in out.split("\n", 1)[1]
    assert C.main(["near", "--verdict", "skip"]) == 0
    assert "game/T/c.cpp  [skip (changed since the index's census" in capsys.readouterr().out
    assert C.main(["near", "--packet", "game/T/b.cpp"]) == 0
    out = capsys.readouterr().out
    assert "verdict: serve" in out and "caller  ?b@@YAXXZ 0x00000700 128 B" in out
    assert "row 0x00000500 128 B authored game/T/one.cpp; convention cdecl -> cdecl" in out
    assert "python3 tools/re_log.py record '?b@@YAXXZ' 0x00000700 128 blocked" in out
    assert "census=5f10bce6ba" in out
    receipt = tmp_path / "link_census" / C.RECEIPTS / C.receipt_name(0x700, "?b@@YAXXZ", "game/T/b.cpp")
    assert receipt.exists()                                                         # the packet judged it
    assert C.main(["near", "--packet", "game/T/a.cpp"]) == 1
    assert "game/T/a.cpp is not a near file at census 5f10bce6ba: linked at census 5f10bce6ba" in (
        capsys.readouterr().out)
    monkeypatch.setattr(re_log, "latest_link_records", lambda path=None: _records(
        ["?b@@YAXXZ", "0x00000700", "128", "blocked", "link_check t=2 census=5f10bce6ba"]))
    assert C.main(["near", "--packet", "game/T/b.cpp"]) == 1
    assert "blocked: blocked 0x00000700 at census 5f10bce6ba" in capsys.readouterr().out
    # a verdict judged against an older index blocks nothing once near serves from a newer one,
    # even when link_status.csv is newer still (GPT-6.1-Sol, review round 1)
    monkeypatch.setattr(re_log, "latest_link_records", lambda path=None: _records(
        ["?b@@YAXXZ", "0x00000700", "128", "blocked", "link_check t=2 census=7d308168db"]))
    monkeypatch.setattr(C, "linked_since", lambda census: (frozenset({"game/T/a.cpp"}), "9999999999", ""))
    assert C.main(["near", "--packet", "game/T/b.cpp"]) == 0
    assert "prior   blocked 0x00000700 (stale: census 7d308168db)" in capsys.readouterr().out


def test_a_check_leaves_per_row_receipts_re_log_tags_from(tmp_path, monkeypatch):
    """The census comes from the index that judged the row's file, per row:
    a later check of another file at another census does not retag it."""
    import re_log
    monkeypatch.setattr(C, "INDEX", tmp_path / "link_census" / "link_index.pkl")
    monkeypatch.setattr(re_log, "EVALUATED", tmp_path / "link_census" / C.RECEIPTS)
    b = ("7d308168db", "game/T/b.cpp")
    C.note_evaluated([_row("?b@@YAXXZ", 0x700, "game/T/b.cpp"), _row("?b2@@YAXXZ", 0x704, "game/T/b.cpp")],
                     "7d308168db")
    C.note_evaluated([_row("?c@@YAXXZ", 0x800, "game/T/c.cpp")], "5f10bce6ba")
    assert re_log.evaluated_census("0x00000700", "?b@@YAXXZ") == re_log.evaluated_census("0x704", "?b2@@YAXXZ") == b
    assert re_log.evaluated_census("0x00000800", "?c@@YAXXZ") == ("5f10bce6ba", "game/T/c.cpp")
    assert re_log.evaluated_census("0x00000900", "?d@@YAXXZ") == ("", "")     # never judged here: no tag
    assert re_log.evaluated_census("0x00000700", "?other@@YAXXZ") == ("", "")  # another row at that RVA
    # another source's row at the same RVA has its own receipt and never retags this one
    C.note_evaluated([_row("?x@@YAXXZ", 0x700, "game/T/x.cpp")], "5f10bce6ba")
    assert re_log.evaluated_census("0x00000700", "?b@@YAXXZ") == b
    C.note_evaluated([_row("?b@@YAXXZ", 0x700, "game/T/b.cpp")], "5f10bce6ba")   # re-judged
    assert re_log.evaluated_census("0x00000700", "?b@@YAXXZ") == ("5f10bce6ba", "game/T/b.cpp")
    # the same row judged in a second file (rehomed, or a twin): unsure, so no tag
    C.note_evaluated([_row("?b@@YAXXZ", 0x700, "game/T/moved.cpp")], "5f10bce6ba")
    assert re_log.evaluated_census("0x00000700", "?b@@YAXXZ") == ("", "")
    C.note_evaluated([_row("?d@@YAXXZ", 0x900, "game/T/d.cpp")], "")             # no census: no receipt
    assert re_log.evaluated_census("0x00000900", "?d@@YAXXZ") == ("", "")


def test_the_printed_record_command_records_a_census_bound_block(tmp_path, monkeypatch):
    """Filled in as printed, the packet's command passes re_log's tag rules and
    carries the census near served from, whatever words its evidence uses."""
    import shlex
    import re_log
    log = tmp_path / "re_attempts.log"
    log.write_text("", encoding="utf-8")
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    monkeypatch.setattr(re_log, "EVALUATED", tmp_path / "absent.json")
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    re_log._reset()
    try:
        command = C.record_command(_row("?b@@YAXXZ", 0x700, "game/T/b.cpp"), "7d308168db")
        filled = (command.replace("<what stopped it>", "ABI mismatch").replace("<family>/<detail>", "identity/abi")
                  .replace("<min>", "20").replace("<model>", "test-model"))
        argv = shlex.split(filled)
        assert argv[:4] == ["python3", "tools/re_log.py", "record", "?b@@YAXXZ"]
        re_log._record(argv[3:])
        fields = log.read_text(encoding="utf-8").splitlines()[-1].split("\t")
        assert fields[3] == "blocked" and re_log.census_of(fields[4]) == "7d308168db"
        assert re_log.census_source_of(fields[4]) == "game/T/b.cpp"
        assert C.blocked_files({"game/T/b.cpp": [_row("?b@@YAXXZ", 0x700, "game/T/b.cpp")]}, re_log.latest_link_records(log),
                               "7d308168db") == {"game/T/b.cpp": "blocked 0x00000700 at census 7d308168db"}
    finally:
        re_log._reset()


def test_census_only_refreshes_every_new_file_so_new_files_see_each_other(monkeypatch, tmp_path, capsys):
    """owner verdict 2026-10-13 (adversarial review round 2: test gaps): under
    --census-only the census holds nothing for new files, so each one is
    refreshed from its own object; a reference between two new files resolves."""
    _new_files(monkeypatch, tmp_path, {"n1.obj": _coff(["_f"], ["_h"]), "n2.obj": _coff(["_h"])},
               ["a.obj", "b.obj", "n1.obj", "n2.obj"])
    assert C.main(["--census-only", "n1.cpp", "n2.cpp"]) == 0
    out = capsys.readouterr().out
    assert "unresolved" not in out and "2 of 2 link cleanly" in out


# The LINKED-claim rule (project lead 2026-10-16): apply_selection_rule.

class _Path(_Obj):
    pass


def _rule_fixture(monkeypatch, census_objects, census_facts, current_facts, *, ledger=None, built=None,
                  owners=None, census_owners=None, stale_objects=(), since=frozenset(), inputs=None):
    """A census of `census_objects` with `census_facts` ({obj: (copies, strong)},
    copies [(name, digest, verdict)]); `current_facts` is what each object
    holds now ({obj: (copies, strong[, references])}), judged with current
    truth. `ledger` is the current ledger's link order (default: the census's
    objects, then the new ones in current_facts), `built` the objects that
    exist here (default all), `since` the files changed since the census and
    `inputs` {obj: set of input files | None} (default {obj.cpp}). refresh()
    is replaced by a table rewrite from current_facts; the rest is real."""
    import build
    import link_census
    strong, comdat = collections.defaultdict(list), collections.defaultdict(list)
    for i, name in enumerate(census_objects):
        copies, defined = census_facts.get(name, ([], []))[:2]
        for sym in defined:
            strong[sym].append(i)
        for sym, digest, verdict in copies:
            comdat[sym].append((i, digest, verdict))
    ix = {"meta": {"date": "d", "commit": "c"}, "objects": list(census_objects), "strong": dict(strong),
          "comdat": dict(comdat), "blockers": {}, "bytes": {}, "common": {}, "common_schema": C.COMMON_SCHEMA,
          "selection": {"exceptions": {}, "owners": census_owners or {}}}

    class _Seen(list):
        pass
    refreshed = _Seen()

    def fake_refresh(index, objects, truth):
        for obj in objects:
            refreshed.append(obj.name)
            if obj.name not in index["objects"]:
                index["objects"].append(obj.name)
            at = index["objects"].index(obj.name)
            for table in ("strong", "comdat"):
                for sym in list(index[table]):
                    index[table][sym] = [e for e in index[table][sym] if (e if table == "strong" else e[0]) != at]
            copies, defined = current_facts[obj.name][:2]
            for sym in defined:
                index["strong"].setdefault(sym, []).append(at)
            for sym, digest, verdict in copies:
                index["comdat"].setdefault(sym, []).append((at, digest, verdict))

    def facts_of(obj, truth=None, **kw):
        entry = current_facts[obj.name]
        copies, defined = entry[:2]
        refs = list(entry[2]) if len(entry) > 2 else []
        return ([(s, d, 4, v) for s, d, v in copies], list(defined), refs, [])
    ledger = list(ledger if ledger is not None
                  else list(census_objects) + [n for n in current_facts if n not in census_objects])
    built = set(ledger if built is None else built)
    order = [_Path(n) for n in ledger]
    present = [o for o in order if o.name in built]
    missing = [o for o in order if o.name not in built]
    inputs = inputs or {}
    compiled = []
    monkeypatch.setattr(C, "refresh", fake_refresh)
    monkeypatch.setattr(link_census, "object_facts", facts_of)
    monkeypatch.setattr(link_census, "ledger_owners", lambda rows: owners or {})
    monkeypatch.setattr(link_census, "_object_sources", lambda rows: {o: Path(o.name + ".cpp") for o in order})
    monkeypatch.setattr(link_census, "objects", lambda rows: (present, missing))
    monkeypatch.setattr(link_census, "link_order", lambda rows, data=(): order)
    monkeypatch.setattr(link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(C, "changed_since", lambda commit: _since(since))
    monkeypatch.setattr(C, "_TRUTH_MEMO", {}, raising=False)
    monkeypatch.setattr(C, "MOVED_CACHE", Path(__import__("tempfile").mkdtemp()) / "moved_cache.json")
    monkeypatch.setattr(C, "object_inputs",
                        lambda obj, sources, receipts: inputs.get(obj.name, {obj.name + ".cpp"}))
    monkeypatch.setattr(C, "_refresh_receipts", lambda: type("R", (), {"save": lambda self: None})())
    monkeypatch.setattr(C, "_object_is_current",
                        lambda obj, sources, receipts: obj.name in built and obj.name not in stale_objects)
    monkeypatch.setattr(build, "compile_rows", lambda rows, need, input_proof=None: compiled.extend(need) or {})
    monkeypatch.setattr(link_census, "_refresh_missing_search_root_receipts", lambda *a: None)
    refreshed.compiled = compiled
    return ix, refreshed, facts_of


class _Everything(frozenset):
    def __contains__(self, item):
        return True


def _since(paths, tracked=_Everything()):
    """A changed_since answer for fixtures: every input is tracked by git."""
    changed = C.Changed(paths)
    changed.tracked = tracked
    return changed


ROWS = [{"name": "fixture"}]       # a non-empty ledger: the rule reads link order only then


def _judge(ix, obj, facts_of):
    fact = facts_of(obj)
    own = ix["objects"].index(obj.name)
    unknown = []
    return C.wrong_selected(obj, fact, own, own, ix, unknown=unknown), unknown


def test_rule_c4c23b4869_renamed_stlport_names_meet_frozen_gen_copies(monkeypatch):
    """c4c23b4869: BfmeConv14xx renamed to real STLport names that
    game/gen_small/tgrid_004.cpp and zhstl_005.cpp already define (frozen
    copies the census left unjudged). Every definer is refreshed with current
    truth: the kept first copy (tgrid's) is not retail's -> a loss, never LINKS."""
    S = "??$find_if@V?$reverse_iterator@PBD@_STL@@U?$_Neq_char_bound@U?$char_traits@D@_STL@@@2@@_STL@@YA@Z"
    census = {"tgrid_004.obj": ([(S, "dT", None)], []), "zhstl_005.obj": ([(S, "dZ", None)], []),
              "bfmeconv1472.obj": ([("?old_asm_lift@@YAXXZ", "dL", None)], [])}
    now = {"tgrid_004.obj": ([(S, "dT", "wrong")], []), "zhstl_005.obj": ([(S, "dZ", "wrong")], []),
           "bfmeconv1472.obj": ([(S, "dM", "retail")], [])}
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now)
    mine = _Path("bfmeconv1472.obj")
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
    assert S in changed and stale == set()
    assert sorted(refreshed) == ["bfmeconv1472.obj", "tgrid_004.obj", "zhstl_005.obj"]
    selected, unknown = _judge(ix, mine, facts_of)
    assert selected == [S] and unknown == []


def test_rule_c4c23b4869_gen_objects_not_built_here_are_preview_unknown(monkeypatch):
    """Round 3 F1: the same case in a worktree that never BUILT the gen
    objects (still in the current ledger, so missing, not gone): their copies
    stay and the name is LINKED PREVIEW UNKNOWN -- with no compile budget, or
    when compiling them does not produce them. Never LINKS."""
    S = "??$find_if@stl@@YAXXZ"
    census = {"tgrid_004.obj": ([(S, "dT", None)], []), "zhstl_005.obj": ([(S, "dZ", None)], []),
              "bfmeconv1472.obj": ([], [])}
    now = {"tgrid_004.obj": ([(S, "dT", "wrong")], []), "zhstl_005.obj": ([(S, "dZ", "wrong")], []),
           "bfmeconv1472.obj": ([(S, "dM", "retail")], [])}
    for limit in (0, 50):
        ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now, built={"bfmeconv1472.obj"})
        mine = _Path("bfmeconv1472.obj")
        changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS, compile_limit=limit)
        assert S in changed and stale == {S}
        assert len(ix["comdat"][S]) == 3                         # nothing dropped
        assert _judge(ix, mine, facts_of) == ([], [S])
        assert len(refreshed.compiled) == (2 if limit else 0)    # compiled within the budget first


def test_rule_an_object_dropped_from_the_ledger_loses_its_definitions(monkeypatch):
    """Only an object absent from the current ledger's link order is gone."""
    S = "??$find_if@stl@@YAXXZ"
    census = {"tgrid_004.obj": ([(S, "dT", None)], []), "zhstl_005.obj": ([(S, "dZ", None)], []),
              "bfmeconv1472.obj": ([], [])}
    now = {"zhstl_005.obj": ([(S, "dZ", "retail")], []), "bfmeconv1472.obj": ([(S, "dZ", "retail")], [])}
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now,
                                            ledger=["zhstl_005.obj", "bfmeconv1472.obj"])
    mine = _Path("bfmeconv1472.obj")
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
    assert stale == set() and sorted(ix["objects"][i] for i, _, _ in ix["comdat"][S]) == [
        "bfmeconv1472.obj", "zhstl_005.obj"]                                   # tgrid's copy dropped
    assert _judge(ix, mine, facts_of) == ([], [])


def test_rule_another_definer_changed_since_the_census(monkeypatch):
    """Round 3 F2: a.obj (not checked) changed its copy of S since the census
    (a header inline edit, a // cl: flag, another commit). Its inputs changed
    since the census commit, so S is changed, a.obj is refreshed and its now
    wrong kept copy is a loss -- and with its inputs unknown, S changes too."""
    S = "?s@@YAXXZ"
    census = {"a.obj": ([(S, "dA", "retail")], []), "mine.obj": ([(S, "dA", "retail")], [])}
    now = {"a.obj": ([(S, "dX", "wrong")], []), "mine.obj": ([(S, "dA", "retail")], [])}
    for kwargs in ({"since": {"game/inline.h"}, "inputs": {"a.obj": {"a.cpp", "game/inline.h"}}},
                   {"inputs": {"a.obj": None}}):
        ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now, **kwargs)
        mine = _Path("mine.obj")
        changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
        assert changed == {S} and "a.obj" in refreshed
        assert _judge(ix, mine, facts_of) == ([S], [])
    # inputs that did not change: the census verdict stands, nothing re-read
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now, since={"game/other.h"})
    changed, stale = C.apply_selection_rule(ix, [_Path("mine.obj")], None, ROWS)
    assert changed == set() and refreshed == ["mine.obj"]


def test_rule_an_object_added_since_the_census_is_a_definer(monkeypatch):
    """Round 3 F3: n.obj, added by another commit since the census and first in
    link order, defines a wrong copy of S: it is placed, read and kept -> a
    loss. Not readable here: every touched name is PREVIEW UNKNOWN."""
    S = "?resize@?$vector@PAX@@QAEXI@Z"
    census = {"a.obj": ([(S, "dA", "retail")], []), "mine.obj": ([], [], [S])}
    now = {"n.obj": ([(S, "dN", "wrong")], []), "a.obj": ([(S, "dA", "retail")], []),
           "mine.obj": ([], [], [S])}
    ledger = ["n.obj", "a.obj", "mine.obj"]
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now, ledger=ledger)
    mine = _Path("mine.obj")
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
    assert ix["objects"][0] == "n.obj" and S in changed
    assert _judge(ix, mine, facts_of) == ([S], [])
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now, ledger=ledger,
                                            built={"a.obj", "mine.obj"})
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS, compile_limit=0)
    assert ix["selection"]["unknown_definers"]
    assert _judge(ix, mine, facts_of) == ([], [S])


def test_rule_a_changed_name_with_a_census_map_exception_is_stale(monkeypatch):
    """Round 3 F4: the census /MAP holder was measured on other definers."""
    S = "?s@@YAXXZ"
    census = {"a.obj": ([(S, "dA", "wrong")], []), "b.obj": ([(S, "dB", "retail")], []), "mine.obj": ([], [])}
    now = {**census, "mine.obj": ([(S, "dM", "wrong")], [])}
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now)
    ix["selection"]["exceptions"] = {S: 1}
    mine = _Path("mine.obj")
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
    assert S in changed and S in stale
    assert _judge(ix, mine, facts_of) == ([], [S])


def test_refresh_a_missing_ledger_object_makes_its_census_names_stale(monkeypatch):
    """Round 3 F5 (--refresh): gone.obj is in the ledger, defined S first
    (wrong) in the census and failed to compile here: S is stale -> PREVIEW
    UNKNOWN, never LINKS on a's retail copy."""
    import build
    S = "?s@@YAXXZ"
    ix = _refreshable(monkeypatch, ["a.obj"], {"a.obj": ([(S, "dA", 4, "retail")], [], [], [])},
                      missing=["gone.obj"], after={"missing": [_Obj("gone.obj")]})
    monkeypatch.setattr(build, "compile_rows",
                        lambda rows, need, input_proof=None: (_ for _ in ()).throw(SystemExit("cl failed")))
    ix["objects"] = ["gone.obj", "a.obj"]
    ix["strong"] = {}
    ix["comdat"] = {S: [(0, "dG", "wrong"), (1, "dA", "retail")]}
    C.refresh_current(ix)
    assert S in ix["selection"]["stale"]
    fact = ([(S, "dA", 4, "retail")], [], [], [])
    own = ix["objects"].index("a.obj")
    unknown = []
    assert C.wrong_selected(_Obj("a.obj"), fact, own, own, ix, unknown=unknown) == [] and unknown == [S]


def test_rule_never_compiles_beyond_its_limit(monkeypatch):
    S = "?s@@YAXXZ"
    census = {"a.obj": ([(S, "dA", None)], []), "mine.obj": ([], [])}
    now = {"a.obj": ([(S, "dA", None)], []), "mine.obj": ([(S, "dM", None)], [])}
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now, stale_objects={"a.obj"})
    changed, stale = C.apply_selection_rule(ix, [_Path("mine.obj")], None, ROWS, compile_limit=0)
    assert stale == {S} and refreshed.compiled == []


def test_rule_e9c390b038_new_identical_copy_still_reports_the_gain(monkeypatch):
    """e9c390b038: the respelled EAStringC TU newly emits ??1EAStringC, a COMDAT
    18 other TUs define with the same body. The name changed (a new definer),
    every definer is refreshed, the copies agree: nothing to choose, so the
    file LINKS and its +587 stands."""
    D = "??1EAStringC@@QAE@XZ"
    others = {f"eastr{i}.obj": ([(D, "dE", None)], []) for i in range(18)}
    census = {**others, "rva008c7950stacksubstring.obj": ([], [])}
    now = {**others, "rva008c7950stacksubstring.obj": ([(D, "dE", None)], [])}
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now)
    mine = _Path("rva008c7950stacksubstring.obj")
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
    assert D in changed and stale == set() and len(refreshed) == 19
    assert _judge(ix, mine, facts_of) == ([], [])


def test_rule_unchanged_unknown_name_is_no_false_loss(monkeypatch):
    """A name the census already judged 'unknown' (two differing copies, no
    retail address) that the checked file references but whose definers and
    ownership did not change keeps the census verdict: no loss, no unknown."""
    U = "?unknown@@YAXXZ"
    census = {"a.obj": ([(U, "d1", None)], []), "b.obj": ([(U, "d2", None)], []),
              "mine.obj": ([("?mine@@YAXXZ", "dm", None)], [], [U])}
    now = dict(census)
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, now)
    mine = _Path("mine.obj")
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
    assert changed == set() and refreshed == ["mine.obj"]
    assert _judge(ix, mine, facts_of) == ([], [])


def test_rule_an_ownership_change_alone_refreshes_the_definers(monkeypatch):
    G = "?owned@@YAXXZ"
    census = {"a.obj": ([], [G]), "mine.obj": ([], [G])}
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, census,
                                            owners={G: {"mine.obj"}}, census_owners={G: {"a.obj"}})
    changed, stale = C.apply_selection_rule(ix, [_Path("mine.obj")], None, ROWS)
    assert changed == {G} and sorted(refreshed) == ["a.obj", "mine.obj"]
    assert ix["selection"]["owners"][G] == {"mine.obj"}
    # two exclusive definers, the kept (first, a.obj) is not the current owner's -> wrong
    assert _judge(ix, _Path("mine.obj"), facts_of) == ([G], [])


def test_report_preview_unknown_never_claims_a_gain(capsys):
    ix = index(blockers={"x.cpp": {"linked": False}})
    result = {k: [] for k in ("unresolved", "duplicates", "comdat", "addresses", "selected")}
    result["preview_unknown"] = ["?s@@YAXXZ"]
    assert C.report("x.cpp", _Obj("x.obj"), result, ix, 587) is False
    out = capsys.readouterr().out
    assert "LINKED PREVIEW UNKNOWN — selection census stale for: ?s@@YAXXZ" in out
    assert "LINKED 0 -> 0 bytes" in out and result["after_bytes"] == 0


def test_rule_inputs_changed_but_copies_identical_keep_the_census_verdict(monkeypatch):
    """A definer's header changed since the census but it still compiles to
    the census's copy: once re-read, S's definers are exactly the census's,
    so the census verdict (a non-blocking 'unknown') stands -- no PREVIEW
    UNKNOWN for e9c390b038-like files whose shared names only look touched."""
    S = "??1Rva8CD130String@@QAE@XZ"
    census = {"a.obj": ([(S, "d1", None)], []), "b.obj": ([(S, "d2", None)], []),
              "mine.obj": ([], [], [S])}
    ix, refreshed, facts_of = _rule_fixture(monkeypatch, list(census), census, census,
                                            since={"game/str.h"}, inputs={"a.obj": {"a.cpp", "game/str.h"}})
    mine = _Path("mine.obj")
    changed, stale = C.apply_selection_rule(ix, [mine], None, ROWS)
    assert "a.obj" in refreshed and changed == set() and stale == set()
    assert _judge(ix, mine, facts_of) == ([], [])


# The pre-commit environment (project lead, 2026-10-16): a SPARSE worker
# checkout where only the checked object is built, ANOTHER source defining a
# touched name changed since the census, and a NEWLY INTRODUCED definer earlier
# in link order. apply_selection_rule must never claim LINKS (or a positive
# LINKED delta) there: PREVIEW UNKNOWN, or a loss it can prove.

def _precommit_case(monkeypatch, *, sparse, modified, new_definer, limit=0):
    S = "?shared@@YAXXZ"
    census = {"b.obj": ([(S, "dB", "retail")], []), "mine.obj": ([(S, "dB", "retail")], [])}
    now = {"b.obj": ([(S, "dX" if modified else "dB", "wrong" if modified else "retail")], []),
           "mine.obj": ([(S, "dB", "retail")], [])}
    ledger = ["b.obj", "mine.obj"]
    if new_definer:
        now["n.obj"] = ([(S, "dN", "wrong")], [])
        ledger = ["n.obj"] + ledger
    ix, refreshed, facts_of = _rule_fixture(
        monkeypatch, list(census), census, now, ledger=ledger,
        built={"mine.obj"} if sparse else None,
        since={"game/b.cpp"} if modified else set(),
        inputs={"b.obj": {"game/b.cpp"}})
    ix["blockers"] = {"mine.cpp": {"linked": True}}
    ix["bytes"] = {"mine.cpp": 100}
    mine = _Path("mine.obj")
    C.apply_selection_rule(ix, [mine], None, ROWS, compile_limit=limit)
    selected, unknown = _judge(ix, mine, facts_of)
    result = {k: [] for k in ("unresolved", "duplicates", "comdat", "addresses")}
    result.update(selected=selected, preview_unknown=unknown)
    linked = C.report("mine.cpp", mine, result, ix, 100)
    return selected, unknown, linked, result["after_bytes"]


@pytest.mark.parametrize("modified,new_definer", [(True, False), (False, True), (True, True)])
def test_precommit_sparse_checkout_never_claims_links(monkeypatch, capsys, modified, new_definer):
    selected, unknown, linked, after = _precommit_case(monkeypatch, sparse=True, modified=modified,
                                                       new_definer=new_definer)
    assert not linked and after <= 100 and (selected or unknown)
    assert "LINKED PREVIEW UNKNOWN" in capsys.readouterr().out or selected


@pytest.mark.parametrize("modified,new_definer", [(True, False), (False, True), (True, True)])
def test_precommit_built_checkout_proves_the_loss(monkeypatch, modified, new_definer):
    selected, unknown, linked, after = _precommit_case(monkeypatch, sparse=False, modified=modified,
                                                       new_definer=new_definer)
    assert selected == ["?shared@@YAXXZ"] and not linked and after == 0


def test_precommit_sparse_checkout_with_nothing_changed_keeps_the_census_verdict(monkeypatch):
    """Sparse alone: no definer, input or ownership changed since the census,
    so the census verdict (here LINKS, 100 -> 100: no gain) stands."""
    selected, unknown, linked, after = _precommit_case(monkeypatch, sparse=True, modified=False,
                                                       new_definer=False)
    assert (selected, unknown, linked, after) == ([], [], True, 100)


def test_precommit_sparse_checkout_compiling_within_budget_proves_the_loss(monkeypatch):
    """With a compile budget the fixture still cannot build (sparse stays
    sparse): the answer stays PREVIEW UNKNOWN, never LINKS."""
    selected, unknown, linked, after = _precommit_case(monkeypatch, sparse=True, modified=True,
                                                       new_definer=True, limit=50)
    assert not linked and (selected or unknown)


def test_object_inputs_trusts_only_a_sidecar_whose_files_still_match(monkeypatch, tmp_path):
    """Round 4 N2: the sidecar's header list counts only while the source and
    every header still have the digests that build read; no compiler runs."""
    import build
    import hashlib
    src, hdr, obj = tmp_path / "a.cpp", tmp_path / "a.h", tmp_path / "a.obj"
    src.write_text("int a;\n")
    hdr.write_text("#define A 1\n")
    obj.write_bytes(b"obj")
    md5 = lambda p: hashlib.md5(p.read_bytes()).hexdigest()
    sidecar = tmp_path / "a.deps.json"
    sidecar.write_text(__import__("json").dumps({"cmd": "today", "source": md5(src), "deps": {str(hdr): md5(hdr)}}))
    monkeypatch.setattr(build, "_deps_sidecar", lambda o: sidecar)
    monkeypatch.setattr(C, "_current_fingerprint", lambda source, obj: "today")
    got = C.object_inputs(obj, {obj: src}, None)
    assert got == {C.repo_path(src), C.repo_path(hdr)}
    monkeypatch.setattr(C, "_current_fingerprint", lambda source, obj: "another command")   # round 5 F1
    assert C.object_inputs(obj, {obj: src}, None) is None
    monkeypatch.setattr(C, "_current_fingerprint", lambda source, obj: "today")
    hdr.write_text("#define A 2\n")                    # the header moved on since that build
    assert C.object_inputs(obj, {obj: src}, None) is None


def test_hook_mode_reports_unknown_for_unstaged_edits_and_exits_zero(monkeypatch, capsys):
    monkeypatch.setattr(C, "_git", lambda *a, **k: "game/x.cpp\0")
    monkeypatch.setattr(C, "load_index", lambda: pytest.fail("no preview when unstaged edits differ"))
    assert C.main(["--hook", "game/a.cpp"]) == 0
    assert "game/a.cpp: LINKED PREVIEW UNKNOWN (unstaged or untracked inputs differ" in capsys.readouterr().out


def test_hook_mode_never_compiles_and_never_fails(monkeypatch, capsys):
    calls = []
    monkeypatch.setattr(C, "_git", lambda *a, **k: "")

    def fake_main(argv, hook=False):
        calls.append((argv, hook))
        raise SystemExit("link_check: no census index")
    real_main = C.main
    monkeypatch.setattr(C, "main", fake_main)
    args = type("A", (), {"paths": ["game/a.cpp"], "compile_limit": None, "census_only": False,
                          "deadline": 5})()
    assert C.hook_main(args) == 0
    assert calls == [(["game/a.cpp", "--compile-limit", "0"], True)]
    assert "LINKED PREVIEW UNKNOWN" in capsys.readouterr().out
    monkeypatch.setattr(C, "main", real_main)


def test_hook_mode_deadline_says_unknown(monkeypatch, capfd):
    """Past the deadline the hook prints UNKNOWN (timeout) and exits 0."""
    import subprocess
    import sys as _sys
    code = ("import sys, time; sys.path.insert(0, %r); import link_check as C\n"
            "C._git = lambda *a, **k: ''\n"
            "C.main = lambda argv, hook=False: time.sleep(30)\n"
            "args = type('A', (), {'paths': ['game/a.cpp'], 'compile_limit': None, 'census_only': False, "
            "'deadline': 1})()\n"
            "C.hook_main(args)\n") % str(C.ROOT / "tools")
    done = subprocess.run([_sys.executable, "-c", code], capture_output=True, text=True, timeout=60)
    assert done.returncode == 0
    assert "game/a.cpp: LINKED PREVIEW UNKNOWN (timeout after 1s)" in done.stdout
