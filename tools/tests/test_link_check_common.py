"""COMMON provider extraction and scoped resolution, without a compiler/linker."""
import copy
import struct
import sys
from pathlib import Path

import pytest
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C
import link_census as L


def coff(path, records):
    strings = bytearray(b"\0" * 4)
    symbols = bytearray()
    for name, value, section, storage in records:
        raw = name.encode()
        if len(raw) > 8:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(raw + b"\0")
        else:
            field = raw.ljust(8, b"\0")
        symbols.extend(field + struct.pack("<IhHBB", value, section, 0, storage, 0))
    strings[:4] = struct.pack("<I", len(strings))
    section = b".data".ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, 0, 0, 0, 0, 0, 0, 0xC0000040)
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, 1, 0, 60, len(records), 0, 0) + section + symbols + strings)
    return path


class NoTruth:
    def verdict(self, *args):
        return None


def ix(objects):
    facts = [L.object_facts(o, NoTruth()) for o in objects]
    result = C.index_tables(objects, facts, {"exceptions": {}, "owners": {}})
    result["excuses"] = {"runtime": set(), "imported": {}, "stubs": {}}
    return result


def test_extract_common_and_exclude_undefined_static_absolute(tmp_path):
    obj = coff(tmp_path / "a.obj", [("common_long_name", 4, 0, 2), ("u", 0, 0, 2),
                                  ("absolute", 8, -1, 2), ("static", 8, 0, 3)])
    assert L.common_definitions(obj) == {"common_long_name": 4}
    facts = L.object_facts(obj, NoTruth())
    assert len(facts) == 4 and facts[2] == ["u"] and "common_long_name" not in facts[1]


@pytest.mark.parametrize("sizes", [(4, 8), (8, 4)])
def test_common_merges_and_resolves_reference(tmp_path, sizes):
    a = coff(tmp_path / "a.obj", [("x", sizes[0], 0, 2)])
    b = coff(tmp_path / "b.obj", [("x", sizes[1], 0, 2)])
    user = coff(tmp_path / "user.obj", [("x", 0, 0, 2)])
    index = ix([a, b, user])
    assert index["common"] == {"x": [(0, sizes[0]), (1, sizes[1])]}
    for obj in (a, b, user):
        assert not any(C.check_object(obj, index, NoTruth()).values())
    index["common"] = {}
    assert C.check_object(user, index, NoTruth())["unresolved"] == ["x"]


def test_own_common_is_a_provider_even_outside_index(tmp_path):
    obj = coff(tmp_path / "own.obj", [("x", 4, 0, 2), ("x", 0, 0, 2)])
    assert not any(C.check_object(obj, ix([]), NoTruth()).values())


@pytest.mark.parametrize("reverse", [False, True])
def test_strong_overrides_common_without_duplicate(tmp_path, reverse):
    common = coff(tmp_path / "common.obj", [("x", 4, 0, 2)])
    strong = coff(tmp_path / "strong.obj", [("x", 0, 1, 2)])
    objs = [common, strong] if not reverse else [strong, common]
    index = ix(objs)
    for obj in objs:
        assert not any(C.check_object(obj, index, NoTruth()).values())
    second = coff(tmp_path / "second.obj", [("x", 0, 1, 2)])
    assert C.check_object(second, index, NoTruth())["duplicates"] == ["x"]


def test_own_common_does_not_hide_wrong_comdat_override(tmp_path):
    own = coff(tmp_path / "own.obj", [("x", 4, 0, 2)])
    index = ix([own])
    index["objects"].append("wrong.obj")
    index["comdat"] = {"x": [(1, "bad", "wrong")]}
    assert C.check_object(own, index, NoTruth())["selected"] == ["x"]


def test_own_common_does_not_hide_wrong_strong_owner(tmp_path):
    own = coff(tmp_path / "own.obj", [("x", 4, 0, 2)])
    index = ix([own])
    index["objects"].extend(["wrong.obj", "retail.obj"])
    index["strong"] = {"x": [1, 2]}
    index["selection"] = {"exceptions": {}, "owners": {"x": {"retail.obj"}}}
    assert C.check_object(own, index, NoTruth())["selected"] == ["x"]


def test_refresh_removes_last_provider_and_preserves_other_owner(tmp_path):
    a = coff(tmp_path / "a.obj", [("x", 4, 0, 2)])
    b = coff(tmp_path / "b.obj", [("x", 8, 0, 2)])
    user = coff(tmp_path / "user.obj", [("x", 0, 0, 2)])
    index = ix([a, b, user])
    coff(a, [])
    C.refresh(index, [a], NoTruth())
    assert index["common"]["x"] == [(1, 8)]
    assert not C.check_object(user, index, NoTruth())["unresolved"]
    coff(b, [])
    C.refresh(index, [b], NoTruth())
    assert C.check_object(user, index, NoTruth())["unresolved"] == ["x"]


def test_refresh_size_and_common_strong_transitions(tmp_path):
    obj = coff(tmp_path / "a.obj", [("x", 4, 0, 2)])
    index = ix([obj])
    coff(obj, [("x", 8, 0, 2)])
    C.refresh(index, [obj], NoTruth())
    assert index["common"]["x"] == [(0, 8)]
    coff(obj, [("x", 0, 1, 2)])
    C.refresh(index, [obj], NoTruth())
    assert index["common"]["x"] == [] and index["strong"]["x"] == [0]
    coff(obj, [("x", 4, 0, 2)])
    C.refresh(index, [obj], NoTruth())
    assert index["common"]["x"] == [(0, 4)] and index["strong"]["x"] == []


@pytest.mark.parametrize("broken", [b"", b"short", "truncated", "aux", "name", "terminator"])
def test_bad_common_read_refuses_and_refresh_is_atomic(tmp_path, broken):
    a = coff(tmp_path / "a.obj", [("x", 4, 0, 2)])
    b = coff(tmp_path / "b.obj", [("y", 8, 0, 2)])
    index = ix([a, b]); saved = copy.deepcopy(index)
    coff(a, [])
    data = bytearray(b.read_bytes())
    if broken == "truncated":
        data = data[:-1]
    elif broken == "aux":
        data[60 + 17] = 1
    elif broken == "name":
        data[60:68] = struct.pack("<II", 0, 0xFFFFFFFF)
    elif broken == "terminator":
        data = bytearray(coff(b, [("long_common_name", 8, 0, 2)]).read_bytes())
        data[-1] = ord("x")
    else:
        data = broken
    b.write_bytes(data)
    with pytest.raises(L.MissingObject):
        C.refresh(index, [a, b], NoTruth())
    assert index == saved
    with pytest.raises(L.MissingObject):
        C.index_tables([a, b], [([], [], [], [])] * 2, {"exceptions": {}, "owners": {}})


def test_missing_common_provider_never_becomes_empty_clean(tmp_path):
    with pytest.raises(L.MissingObject):
        L.common_definitions(tmp_path / "missing.obj")


def test_old_index_refuses_check_and_refresh(tmp_path):
    obj = coff(tmp_path / "a.obj", [])
    index = ix([obj]); del index["common_schema"]
    with pytest.raises(SystemExit, match="rebuild.*link_census"):
        C.check_object(obj, index, NoTruth())
    with pytest.raises(SystemExit, match="rebuild.*link_census"):
        C.refresh(index, [obj], NoTruth())
    index["common_schema"] = C.COMMON_SCHEMA; del index["common"]
    with pytest.raises(SystemExit, match="COMMON"):
        C.check_object(obj, index, NoTruth())


def test_sdk_common_resolves_while_gp_wrong_body_stays_blocked(tmp_path):
    provider = coff(tmp_path / "available.obj", [("___GSIACResult", 4, 0, 2)])
    user = coff(tmp_path / "gp.obj", [("___GSIACResult", 0, 0, 2)])
    index = ix([provider, user]); index["objects"].append("bad_gp.obj")
    index["comdat"] = {"_gpDisconnect": [(2, "wrong", "wrong")]}
    coff(user, [("___GSIACResult", 0, 0, 2), ("_gpDisconnect", 0, 0, 2)])
    result = C.check_object(user, index, NoTruth())
    assert result["unresolved"] == [] and result["selected"] == ["_gpDisconnect"]


def test_failed_replacement_facts_preserve_all_tables(tmp_path, monkeypatch):
    a = coff(tmp_path / "a.obj", [("x", 4, 0, 2)])
    b = coff(tmp_path / "b.obj", [("y", 0, 1, 2)])
    index = ix([a, b])
    saved = copy.deepcopy(index)
    original = L.object_facts
    coff(a, [])
    def fail_second(obj, truth, **kwargs):
        if obj == b:
            raise L.MissingObject("bad relocation/COMDAT data")
        return original(obj, truth, **kwargs)
    monkeypatch.setattr(L, "object_facts", fail_second)
    with pytest.raises(L.MissingObject):
        C.refresh(index, [a, b], NoTruth())
    assert index == saved


def test_index_requires_facts_for_every_object(tmp_path):
    obj = coff(tmp_path / "a.obj", [])
    with pytest.raises(ValueError, match="every census object"):
        C.index_tables([obj], [], {"exceptions": {}, "owners": {}})


def test_cli_rejects_old_index_before_source_compile(tmp_path, monkeypatch):
    obj = coff(tmp_path / "a.obj", [])
    index = ix([obj]); del index["common_schema"]
    monkeypatch.setattr(C, "load_index", lambda: index)
    monkeypatch.setattr(C, "resolve", lambda *args: pytest.fail("compiled before schema refusal"))
    with pytest.raises(SystemExit, match="COMMON providers.*rebuild"):
        C.main(["game/f.cpp"])
