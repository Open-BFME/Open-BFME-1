"""link_check: the per-file LINKED preview agrees with link.exe's rules."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C  # noqa: E402


def index(strong=None, comdat=None, blockers=None, sizes=None):
    return {"meta": {"date": "d", "commit": "c"}, "objects": ["a.obj", "b.obj", "c.obj"],
            "strong": strong or {}, "comdat": comdat or {}, "blockers": blockers or {}, "bytes": sizes or {}}


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
    assert link_census.object_current(source, obj)
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
