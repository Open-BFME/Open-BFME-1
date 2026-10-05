"""An opt-in snapshot must preserve native diagnostics and every object proof."""
import copy
import gc
import sys
import weakref
from collections.abc import Mapping
from pathlib import Path
from types import MappingProxyType
from unittest.mock import patch

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C
import link_census as L
from test_link_check import make_case, PREDICTION, INVALID_RECEIPTS, VALID_RECEIPTS, MALFORMED
from test_link_check_common import coff, ix, NoTruth
from test_alias_guard import coff as alias_coff, judge as alias_judge, row


def observe(obj, index, truth, **kwargs):
    if hasattr(truth, "_cache"):
        truth._cache.clear()
    original, facts = L.object_facts, []
    def record(*args, **kw):
        fact = original(*args, **kw)
        facts.append((tuple(fact), {name: getattr(fact, name) for name in
                      ("data", "common", "independent", "truth", "policy")}))
        return fact
    with patch.object(C, "_prediction_tables_valid", wraps=C._prediction_tables_valid) as validator:
        with patch.object(C, "weak_context", wraps=C.weak_context) as context:
            with patch.object(L, "object_facts", side_effect=record):
                try:
                    result = ("result", C.check_object(obj, index, truth, **kwargs))
                except (Exception, SystemExit) as exc:
                    result = ("exception", type(exc), str(exc))
    return result, facts, validator.call_count, context.call_count


def prediction_case(tmp_path, monkeypatch, mode="prediction"):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj, index, truth = make_case(C, tmp_path, mode)
    # Native fixture refreshes; construct a separate prediction-only snapshot.
    index.pop("_weak_token", None)
    index.pop("_weak_current_objects", None)
    return obj, index, truth


@pytest.mark.parametrize("mode", PREDICTION)
def test_prediction_preserves_all_diagnostics_and_attached_facts(tmp_path, monkeypatch, mode):
    obj, index, truth = prediction_case(tmp_path, monkeypatch, mode)
    with patch.object(C, "_prediction_tables_valid", wraps=C._prediction_tables_valid) as validate:
        frozen = C.freeze_prediction_index(index)
    assert type(frozen) is C.FrozenPredictionIndex and validate.call_count == 1
    native = observe(obj, index, truth)
    for _ in range(2):
        prepared = observe(obj, frozen, copy.deepcopy(truth))
        assert native[:2] == prepared[:2]
        assert native[2:] == (1, 0) and prepared[2:] == (0, 0)
    assert next(f[3] for f in prepared[1][0][0][0] if f[0] == "table") == "unknown"


@pytest.mark.parametrize("mode", INVALID_RECEIPTS + VALID_RECEIPTS + MALFORMED)
@pytest.mark.parametrize("refreshed", (False, True))
def test_native_rejection_and_actual_map_paths_are_unchanged(tmp_path, monkeypatch, mode, refreshed):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj, index, truth = make_case(C, tmp_path, mode)
    if mode in MALFORMED or not refreshed:
        index.pop("_weak_token", None)
        index.pop("_weak_current_objects", None)
    with patch.object(C, "_prediction_tables_valid", wraps=C._prediction_tables_valid) as validate:
        prepared = C.freeze_prediction_index(index)
    assert prepared is index
    if mode in INVALID_RECEIPTS + VALID_RECEIPTS:
        assert validate.call_count == 0
    native = observe(obj, index, truth)
    for _ in range(2):
        assert observe(obj, prepared, copy.deepcopy(truth)) == native
    assert native[2] == 1
    if mode in VALID_RECEIPTS:
        assert native[3] == 1


@pytest.mark.parametrize("field", ("weak_kept", "weak_addresses", "weak_locations", "weak_ambiguous"))
@pytest.mark.parametrize("value", (None, {}, [], "invalid"))
def test_any_actual_map_field_is_ineligible(tmp_path, field, value):
    index = ix([coff(tmp_path / "a.obj", [])])
    index["selection"][field] = value
    assert C.freeze_prediction_index(index) is index


@pytest.mark.parametrize("field", ("_weak_token", "_weak_current_objects"))
def test_any_refresh_state_is_ineligible(tmp_path, field):
    index = ix([coff(tmp_path / "a.obj", [])])
    index[field] = None
    assert C.freeze_prediction_index(index) is index


@pytest.mark.parametrize("receipt", (None, "absent", "", "invalid", 0, {}, []))
def test_only_absent_or_none_receipt_is_eligible(tmp_path, receipt):
    index = ix([coff(tmp_path / "a.obj", [])])
    if receipt == "absent":
        del index["selection"]["weak_receipt"]
    else:
        index["selection"]["weak_receipt"] = receipt
    frozen = C.freeze_prediction_index(index)
    assert (type(frozen) is C.FrozenPredictionIndex) == (receipt in (None, "absent"))


def invalid_shape(index, mode):
    mutations = {
        "common_schema": lambda: index.pop("common_schema"),
        "common_mapping": lambda: index.update(common=[]),
        "common_entry_short": lambda: index["common"].update(primary=[(0,)]),
        "common_entry_long": lambda: index["common"].update(primary=[(0, 4, 5)]),
        "common_entry_scalar": lambda: index["common"].update(primary=[1]),
        "common_negative": lambda: index["common"].update(primary=[(-1, 4)]),
        "common_oob": lambda: index["common"].update(primary=[(99, 4)]),
        "common_bool": lambda: index["common"].update(primary=[(True, 4)]),
        "common_bad_size": lambda: index["common"].update(primary=[(0, "4")]),
        "common_zero_size": lambda: index["common"].update(primary=[(0, 0)]),
        "common_big_size": lambda: index["common"].update(primary=[(0, 2**32)]),
        "alias_table": lambda: index.update(aliases=[]),
        "alias_name": lambda: index["aliases"].update({1: [(0, "default")]}),
        "alias_entries": lambda: index["aliases"].update(primary=None),
        "alias_entry": lambda: index["aliases"].update(primary=[(0,)]),
        "alias_holder": lambda: index["aliases"].update(primary=[([], "default")]),
        "alias_oob": lambda: index["aliases"].update(primary=[(99, "default")]),
        "alias_target": lambda: index["aliases"].update(primary=[(0, [])]),
        "owner_missing": lambda: index["selection"].pop("owners"),
        "exceptions_missing": lambda: index["selection"].pop("exceptions"),
        "exception_oob": lambda: index["selection"]["exceptions"].update(default=99),
        "excuses_missing": lambda: index.pop("excuses"),
        "runtime_scalar": lambda: index["excuses"].update(runtime="default"),
        "runtime_members": lambda: index["excuses"].update(runtime=[[]]),
        "imports_table": lambda: index["excuses"].update(imported=[]),
        "imports_members": lambda: index["excuses"]["imported"].update(default=[1]),
        "stubs_table": lambda: index["excuses"].update(stubs=[]),
        "stubs_entry": lambda: index["excuses"]["stubs"].update(primary=[("dll",)]),
        "stubs_type": lambda: index["excuses"]["stubs"].update(primary=[("dll", 1)]),
    }
    mutations[mode]()


@pytest.mark.parametrize("mode", (
    "common_schema", "common_mapping", "common_entry_short", "common_entry_long", "common_entry_scalar",
    "common_negative", "common_oob", "common_bool", "common_bad_size", "common_zero_size", "common_big_size",
    "alias_table", "alias_name", "alias_entries", "alias_entry", "alias_holder", "alias_oob", "alias_target",
    "owner_missing", "exceptions_missing", "exception_oob", "excuses_missing", "runtime_scalar",
    "runtime_members", "imports_table", "imports_members", "stubs_table", "stubs_entry", "stubs_type"))
def test_malformed_consumer_shapes_keep_exact_native_behavior(tmp_path, monkeypatch, mode):
    obj, index, truth = prediction_case(tmp_path, monkeypatch)
    invalid_shape(index, mode)
    prepared = C.freeze_prediction_index(index)
    assert prepared is index
    assert observe(obj, prepared, copy.deepcopy(truth)) == observe(obj, index, truth)


@pytest.mark.parametrize("kind", (list, tuple, set, frozenset))
@pytest.mark.parametrize("has_owner", (False, True))
def test_owner_intersection_preserves_native_exception_or_set_behavior(tmp_path, kind, has_owner):
    first = coff(tmp_path / "first.obj", [("shared", 0, 1, 2)])
    second = coff(tmp_path / "second.obj", [("shared", 0, 1, 2)])
    index = ix([first, second])
    index["selection"]["owners"]["shared"] = kind([first.name] if has_owner else [])
    # Native shape validation allows string lists/tuples, but judge_selected
    # intersects owners with the competing exclusive definers as a set.
    assert C._prediction_tables_valid(index)
    prepared = C.freeze_prediction_index(index)
    native = observe(first, index, NoTruth())
    if kind in (list, tuple):
        assert prepared is index
        assert native[0] == ("exception", TypeError,
                             f"unsupported operand type(s) for &: '{kind.__name__}' and 'set'")
        assert observe(first, prepared, NoTruth()) == native
        assert native[2:] == (1, 0)
    else:
        assert type(prepared) is C.FrozenPredictionIndex
        frozen = observe(first, prepared, NoTruth())
        assert native[0][0] == "result" and frozen[:2] == native[:2]
        assert native[2:] == (1, 0) and frozen[2:] == (0, 0)


@pytest.mark.parametrize("kind", (dict, list, tuple, set, frozenset, str, int, float, bytes))
def test_subclasses_are_rejected_without_hooks(tmp_path, kind):
    class Custom(kind):
        def __iter__(self):
            pytest.fail("called a subclass iteration hook")
        def __copy__(self):
            pytest.fail("called a copy hook")
        def __deepcopy__(self, memo):
            pytest.fail("called a deepcopy hook")
    index = ix([coff(tmp_path / "a.obj", [])])
    index["metadata"] = Custom()
    assert C.freeze_prediction_index(index) is index
    if kind is dict:
        assert type(C.freeze_prediction_index(Custom(index))) is Custom


@pytest.mark.parametrize("extra", (bytearray(b"x"), object(), MappingProxyType({}), range(2)))
def test_unsupported_values_are_ineligible(tmp_path, extra):
    index = ix([coff(tmp_path / "a.obj", [])])
    index["extra"] = extra
    assert C.freeze_prediction_index(index) is index


def test_cycles_and_noncanonical_mappings_are_not_traversed(tmp_path):
    index = ix([coff(tmp_path / "a.obj", [])])
    index["cycle"] = [index]
    assert C.freeze_prediction_index(index) is index
    class Custom(dict):
        def get(self, *args):
            pytest.fail("accessed a noncanonical mapping")
    custom = Custom(index)
    assert C.freeze_prediction_index(custom) is custom


def mutable_containers(value):
    if type(value) is dict:
        yield value
        for item in value.values():
            yield from mutable_containers(item)
    elif type(value) in (list, tuple, set, frozenset):
        if type(value) in (list, set):
            yield value
        for item in value:
            yield from mutable_containers(item)


def assert_sealed(value):
    if isinstance(value, Mapping):
        assert type(value) in (C.FrozenPredictionIndex, MappingProxyType)
        with pytest.raises(TypeError):
            value["mutation"] = []
        for key, item in value.items():
            assert_sealed(key)
            assert_sealed(item)
    elif type(value) in (tuple, frozenset):
        if value:
            if type(value) is tuple:
                with pytest.raises(TypeError):
                    value[0] = None
            else:
                with pytest.raises(AttributeError):
                    value.add("mutation")
        for item in value:
            assert_sealed(item)
    else:
        assert type(value) in (type(None), bool, int, float, str, bytes)


def test_input_and_every_nested_container_can_mutate_without_changing_snapshot(tmp_path, monkeypatch):
    obj, index, truth = prediction_case(tmp_path, monkeypatch)
    index["extra"] = {("tuple-key", frozenset({1})): [({"deep": [{1, 2}, [3]]},)],
                      "scalars": [None, True, 1.5, b"bytes"]}
    frozen = C.freeze_prediction_index(index)
    assert type(frozen) is C.FrozenPredictionIndex
    before = observe(obj, frozen, truth)
    containers = list(mutable_containers(index))
    assert len(containers) > 20
    for value in reversed(containers):
        value.clear()
        assert observe(obj, frozen, truth) == before
    assert_sealed(frozen)
    assert not hasattr(frozen, "__dict__")
    with pytest.raises(TypeError):
        dict.__setitem__(frozen, "strong", {})
    with pytest.raises(TypeError):
        frozen._FrozenPredictionIndex__tables = {}
    with pytest.raises(TypeError):
        del frozen._FrozenPredictionIndex__tables
    with pytest.raises(AttributeError):
        object.__setattr__(frozen, "_FrozenPredictionIndex__tables", {})
    # The read accessor exposes only a recursively sealed proxy.
    assert_sealed(frozen._tables())
    with pytest.raises(TypeError, match="freeze_prediction_index"):
        C.FrozenPredictionIndex(index)
    with pytest.raises(TypeError, match="subclassed"):
        type("Child", (C.FrozenPredictionIndex,), {})


def test_refresh_fails_before_reads_or_iteration_and_rebuild_is_fresh(tmp_path, monkeypatch):
    obj = coff(tmp_path / "a.obj", [("x", 4, 0, 2)])
    index = ix([obj])
    frozen = C.freeze_prediction_index(index)
    class Unreadable:
        def __iter__(self):
            pytest.fail("iterated refresh inputs")
    with pytest.raises(TypeError, match="rebuild"):
        C.refresh(frozen, Unreadable(), NoTruth())
    with pytest.raises(TypeError, match="rebuild"):
        C.refresh(frozen, [], NoTruth())
    assert frozen["common"]["x"] == ((0, 4),)
    index["common"]["x"][0] = (0, 8)
    with patch.object(C, "_prediction_tables_valid", wraps=C._prediction_tables_valid) as validator:
        rebuilt = C.freeze_prediction_index(index)
        assert C.freeze_prediction_index(frozen) is frozen
    assert validator.call_count == 1 and rebuilt is not frozen
    assert rebuilt["common"]["x"] == ((0, 8),) and frozen["common"]["x"] == ((0, 4),)


@pytest.mark.parametrize("mode", ("strong_oob", "comdat_oob", "object_unhashable", "owner_members_type"))
def test_ordinary_mutable_indices_are_revalidated_after_mutation(tmp_path, monkeypatch, mode):
    obj, index, truth = prediction_case(tmp_path, monkeypatch)
    frozen = C.freeze_prediction_index(index)
    assert observe(obj, index, truth)[2:] == (1, 0)
    reference = observe(obj, frozen, truth)
    _, malformed, _ = prediction_case(tmp_path, monkeypatch, mode)
    index.clear()
    index.update(malformed)
    failed = observe(obj, index, truth)
    assert failed[0][0] == "exception" and failed[2:] == (1, 1)
    assert observe(obj, frozen, truth) == reference


@pytest.mark.parametrize("verdict", ("wrong", "unknown", "ok"))
def test_alias_common_excuses_selected_and_source_address_diagnostics(tmp_path, monkeypatch, verdict):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    pin = {"call": 0x500} if verdict != "unknown" else {}
    target_rva = 0x500 if verdict == "ok" else 0x600
    judge = alias_judge(monkeypatch, pin, [row("target", target_rva)])
    provider = alias_coff(tmp_path / "provider.obj", [("target", 0, 1, 2), ("common", 4, 0, 2)])
    obj = alias_coff(tmp_path / "user.obj", [(name, 0, 0, 2) for name in
                     ("call", "common", "__imp_imported", "runtime", "stub", "missing")],
                     "/alternatename:call=target")
    index = ix([provider, obj])
    index["excuses"] = {"runtime": {"runtime"}, "imported": {"imported": {"dll"}},
                        "stubs": {"stub": {("dll", "imported")}}}
    source = tmp_path / "user.cpp"
    source.write_text("void *f() { return (void *)0x00812345; }\n")
    frozen = C.freeze_prediction_index(index)
    assert type(frozen) is C.FrozenPredictionIndex
    native = observe(obj, index, NoTruth(), source=source.name, judge=judge)
    assert observe(obj, frozen, NoTruth(), source=source.name, judge=judge)[:2] == native[:2]
    result = native[0][1]
    assert result["unresolved"] == ["missing"] and result["addresses"]
    assert bool(result["alias_target"]) == (verdict == "wrong")
    assert bool(result["alias_unknown"]) == (verdict == "unknown")


def test_changed_object_bytes_are_read_and_rejudged_each_time(tmp_path):
    obj = coff(tmp_path / "a.obj", [])
    frozen = C.freeze_prediction_index(ix([obj]))
    before = observe(obj, frozen, NoTruth())
    coff(obj, [("new_missing", 0, 0, 2)])
    after = observe(obj, frozen, NoTruth())
    assert before[0][1]["unresolved"] == []
    assert after[0][1]["unresolved"] == ["new_missing"]
    assert before[1][0][1]["data"] != after[1][0][1]["data"]


def test_unbound_tuple_construction_cannot_admit_mutable_tables(tmp_path):
    index = ix([coff(tmp_path / "a.obj", [])])
    # Regression for the rejected v1 tuple carrier: this used to create an
    # exact-type instance whose mutable payload skipped native validation.
    with pytest.raises(TypeError):
        tuple.__new__(C.FrozenPredictionIndex, (index,))


def test_unregistered_exact_handle_fails_before_any_object_io(tmp_path, monkeypatch):
    unregistered = object.__new__(C.FrozenPredictionIndex)
    assert type(unregistered) is C.FrozenPredictionIndex
    monkeypatch.setattr(C, "_object_bytes", lambda *a: pytest.fail("read unregistered object"))
    monkeypatch.setattr(C, "_prediction_tables_valid", lambda *a: pytest.fail("validated unregistered handle"))
    monkeypatch.setattr(C, "weak_context", lambda *a: pytest.fail("accepted unregistered handle"))
    for read in (lambda: unregistered._tables(), lambda: unregistered["objects"],
                 lambda: len(unregistered), lambda: iter(unregistered),
                 lambda: C.require_common_index(unregistered),
                 lambda: C.freeze_prediction_index(unregistered),
                 lambda: C.check_object(tmp_path / "missing.obj", unregistered, NoTruth())):
        with pytest.raises(TypeError, match="unregistered frozen prediction index"):
            read()
    with pytest.raises(TypeError, match="rebuild"):
        C.refresh(unregistered, [tmp_path / "missing.obj"], NoTruth())
    for name in ("_tables", "__dict__", "_FrozenPredictionIndex__tables", "validated"):
        with pytest.raises(AttributeError):
            object.__setattr__(unregistered, name, {})


def test_owned_payload_is_sealed_and_repreparing_mutated_input_is_independent(tmp_path):
    obj = coff(tmp_path / "user.obj", [("missing", 0, 0, 2)])
    index = ix([obj])
    first = C.freeze_prediction_index(index)
    original = observe(obj, first, NoTruth())
    index["objects"].append("provider.obj")
    index["strong"]["missing"] = [1]
    with patch.object(C, "_prediction_tables_valid", wraps=C._prediction_tables_valid) as validator:
        second = C.freeze_prediction_index(index)
    assert validator.call_count == 1 and first is not second
    assert observe(obj, first, NoTruth()) == original
    assert observe(obj, second, NoTruth())[0][1]["unresolved"] == []
    index["strong"]["missing"].append(99)
    assert C.freeze_prediction_index(index) is index
    assert observe(obj, first, NoTruth()) == original
    assert observe(obj, second, NoTruth())[0][1]["unresolved"] == []
    for handle in (first, second):
        assert_sealed(handle._tables())
        with pytest.raises(TypeError):
            handle._tables()["strong"] = index["strong"]
        with pytest.raises(AttributeError):
            object.__setattr__(handle, "_tables", index)


def test_factory_storage_does_not_keep_handles_alive(tmp_path):
    index = ix([coff(tmp_path / "a.obj", [])])
    handle = C.freeze_prediction_index(index)
    reference = weakref.ref(handle)
    assert reference() is handle
    del handle
    gc.collect()
    assert reference() is None
    # A later allocation cannot inherit registration or contents from an
    # expired handle. Every newly allocated but unissued handle is rejected.
    for _ in range(100):
        unregistered = object.__new__(C.FrozenPredictionIndex)
        with pytest.raises(TypeError, match="unregistered"):
            C.require_common_index(unregistered)
