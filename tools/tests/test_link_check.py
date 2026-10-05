"""link_check: the per-file LINKED preview agrees with link.exe's rules."""
import copy
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
    monkeypatch.setattr(link_census, "object_facts", lambda obj, truth, **kwargs: ([], ["g"], [], []))
    monkeypatch.setattr(link_census, "common_definitions", lambda obj, **kwargs: {})
    C.refresh(ix, [SimpleNamespace(name="b.obj", read_bytes=lambda: b"frozen"), SimpleNamespace(name="new.obj")], None)
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
