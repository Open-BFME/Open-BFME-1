"""Native COFF SEARCH_LIBRARY fallback truth, without aliases or name heuristics."""
import collections
import copy
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as L
import link_check as C
from test_link_census import truth, symbol, jmp

_TEST_INPUTS = L.truth_inputs_fingerprint()


def coff(default="default", search=2, tag=3, aux=1, storage=2, section=0, type_=0x20):
    """One actual DIR32 fixup to storage105 with an actual auxiliary record."""
    strings = bytearray(b"\0" * 4)
    def record(name, value, sec, type__, cls, count):
        raw = name.encode()
        if len(raw) > 8:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(raw + b"\0")
        else:
            field = raw.ljust(8, b"\0")
        return field + struct.pack("<IhHBB", value, sec, type__, cls, count)
    records = [record("table", 0, 1, 0, 2, 0), record("primary", 0, 0, 0x20, 105, aux),
               struct.pack("<II", tag, search) + b"\0" * 10,
               record(default, 0, section, type_, storage, 0)]
    strings[:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 74, 4, 0, 0)
    sec = b".rdata\0\0" + struct.pack("<IIIIIIHHI", 0, 0, 4, 60, 64, 0, 1, 0, 0x40001040)
    return header + sec + b"\0" * 4 + struct.pack("<IIH", 0, 1, 6) + b"".join(records) + strings


def fixture(default="default", pointer=0x1040, **kwargs):
    raw = coff(default, **kwargs)
    image = bytearray(0x80)
    image[:4] = struct.pack("<I", L.BASE + pointer)
    image[0x40] = image[0x60] = 0xC3
    t = truth(image, {"table": {0x1000}, "default": {0x1040}, "other": {0x1060}})
    t._weak_inputs = _TEST_INPUTS
    parts = next(L._comdat_sections(raw))
    return raw, t, parts


def context(default="default", verdict="retail", owners=True, primary=False, common=(), multiple=False,
            selected=True):
    definers = {default: {"owner.obj"}}
    copies = {default: {"owner.obj": ("independent-default", verdict)}}
    owner = {default: {"owner.obj"}} if owners else {}
    kept = {default: "owner.obj"} if selected else {}
    if primary:
        definers["primary"] = {"wrong-primary.obj"}
        copies["primary"] = {"wrong-primary.obj": ("wrong", "wrong")}
        kept["primary"] = "wrong-primary.obj"
    if multiple:
        definers[default].add("other.obj")
        copies[default]["other.obj"] = ("same", "retail")
    return L.weak_selection_context(definers, copies, owner, kept, set(common))


def judge(t, parts, ctx):
    sym, body, relocs, digest, size = parts
    return t.verdict(sym, body, L.bind_weak_relocations(relocs, ctx, t), digest, size)


def test_actual_aux_tag_and_search_library_without_name_prefix():
    raw, t, parts = fixture()
    weak = next(s for s in L._coff_symbols(raw) if s["storage"] == 105)
    assert weak["weak_default"] == "default" and weak["weak_identity"][:2] == (2, "default")
    assert judge(t, parts, None) == "unknown"
    assert judge(t, parts, context()) == "retail"
    assert parts[2][0][2]["name"] == "primary"  # no callee rename or alias pin


@pytest.mark.parametrize("kwargs", [{"search": 0}, {"search": 1}, {"search": 3}, {"search": 4},
                                     {"tag": 1}, {"tag": 2}, {"tag": 999}, {"tag": 0},
                                     {"storage": 105}, {"storage": 3}, {"section": -1},
                                     {"type_": 0}, {"type_": 0x30}, {"aux": 2}])
def test_unsupported_invalid_self_cyclic_or_auxiliary_target_not_promoted(kwargs):
    _, t, parts = fixture(**kwargs)
    assert judge(t, parts, context()) == "unknown"


@pytest.mark.parametrize("mutate", ["symbol_table", "aux_count", "aux_payload"])
def test_truncated_auxiliary_is_rejected(mutate):
    raw = bytearray(coff())
    if mutate == "symbol_table":
        raw = raw[:74 + 2 * 18]
    elif mutate == "aux_count":
        raw[74 + 18 + 17] = 255
    else:
        struct.pack_into("<I", raw, 12, 2)  # weak record's auxiliary falls outside declared count
    with pytest.raises((ValueError, struct.error)):
        list(L._comdat_sections(bytes(raw)))


@pytest.mark.parametrize("ctx", [None, context(verdict="wrong"), context(verdict="unknown"),
                                 context(owners=False), context(selected=False), context(primary=True),
                                 context(common=("primary",)), context(common=("default",)),
                                 context(multiple=True)])
def test_missing_wrong_unowned_ambiguous_or_primary_context_not_promoted(ctx):
    _, t, parts = fixture()
    assert judge(t, parts, ctx) == "unknown"


def test_selected_context_keeper_must_be_actual_definer():
    result = L.weak_selection_context({"default": {"a.obj"}},
                                     {"default": {"a.obj": ("d", "retail")}},
                                     {"default": {"a.obj"}}, {"default": "missing.obj"}, set())
    assert not result["defaults"]


def test_wrong_aux_default_address_is_not_masked_by_same_opcodes():
    _, t, parts = fixture(default="other")
    assert judge(t, parts, context(default="other")) == "wrong"


@pytest.mark.parametrize("state", ["pinned-only", "shared", "ambiguous-home"])
def test_default_must_have_independent_unshared_ledger_identity(state):
    _, t, parts = fixture()
    if state == "pinned-only":
        t.pinned["default"] = t.ledger.pop("default")
    elif state == "shared":
        t.shared.add(0x1040)
    else:
        t.ledger["default"].add(0x1060)
    assert judge(t, parts, context()) == "unknown"


def test_actual_retial_operand_ilt_route_is_followed():
    _, t, parts = fixture(pointer=0x1020)
    image = bytearray(t.image)
    image[0x1b:0x20] = jmp(0x101b, 0x1060)
    image[0x20:0x25] = jmp(0x1020, 0x1040)
    t.image = bytes(image)
    assert judge(t, parts, context()) == "retail"
    image[0x20:0x25] = jmp(0x1020, 0x1060)
    t.image = bytes(image)
    t._cache.clear()
    assert judge(t, parts, context()) == "wrong"


def test_cache_fingerprint_tracks_aux_default_and_selected_context_drift():
    _, t, parts = fixture()
    assert judge(t, parts, context()) == "retail"
    assert judge(t, parts, context(primary=True)) == "unknown"
    assert judge(t, parts, context(verdict="wrong")) == "unknown"
    raw2 = coff(default="other")
    sym, body, relocs, _, size = next(L._comdat_sections(raw2))
    # A legacy coarse digest cannot make the new auxiliary reuse a positive verdict.
    same_digest_parts = sym, body, relocs, parts[3], size
    assert judge(t, same_digest_parts, context(default="other")) == "wrong"


def test_digest_includes_auxiliary_fallback_semantics():
    digest = lambda raw: next(L._comdat_sections(raw))[3]
    assert digest(coff()) != digest(coff(default="other"))
    assert digest(coff()) != digest(coff(search=3))


def test_historical_index_cannot_authorize_new_fallback_without_current_provider(tmp_path, monkeypatch):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    _, t, _ = fixture()
    obj = tmp_path / "owner.obj"
    obj.write_bytes(b"frozen-provider")
    ix = {"objects": [obj.name], "strong": {},
          "comdat": {"default": [(0, "d", "retail")]}, "common": {},
          "selection": {"owners": {"default": {obj.name}}, "exceptions": {}, "weak_kept": {"default": obj.name}, "weak_locations": {"default": obj.name}, "weak_addresses": {"default": 0x401040}, "weak_ambiguous": set()}}
    assert not C.weak_context(ix, t)["defaults"]
    ix["weak_schema"] = C.WEAK_SCHEMA
    ix["weak_root"] = str(C.ROOT.resolve())
    ix["weak_truth"] = L.truth_fingerprint(t)
    ix["weak_inventory"] = {obj.name: (str(obj), __import__("hashlib").sha256(obj.read_bytes()).hexdigest())}
    ix["selection"]["weak_receipt"] = C.selected_receipt_digest(ix["selection"])
    assert not C.weak_context(ix, t)["defaults"]
    ix["_weak_current_objects"] = {obj.name: (L.truth_fingerprint(t),
        __import__("hashlib").sha256(obj.read_bytes()).hexdigest(), L.policy_fingerprint(), obj, {"default": "d"})}
    assert not C.weak_context(ix, t)["defaults"]  # persisted marker is not evidence
    ix["_weak_token"] = C._WEAK_PREVIEW_TOKEN
    assert "default" in C.weak_context(ix, t)["defaults"]
    obj.write_bytes(b"changed-provider")
    assert not C.weak_context(ix, t)["defaults"]
    ix["common"] = {"primary": [(0, 4)]}
    assert "primary" in C.weak_context(ix, t)["defined"]
    ix["common"] = {"primary": []}
    assert "primary" not in C.weak_context(ix, t)["defined"]


def test_refresh_second_pass_failure_preserves_all_tables_and_proof_markers(tmp_path, monkeypatch):
    obj = tmp_path / "a.obj"
    obj.write_bytes(coff())
    ix = {"objects": [obj.name], "strong": {}, "comdat": {}, "common": {},
          "common_schema": C.COMMON_SCHEMA, "selection": {"owners": {}, "exceptions": {}}}
    before = copy.deepcopy(ix)
    original = L.object_facts
    calls = 0
    def fails_second(obj_, t, **kwargs):
        nonlocal calls
        calls += 1
        if calls == 2:
            raise L.MissingObject("second-pass changed or unreadable provider")
        return original(obj_, t, **kwargs)
    class NoTruth:
        def verdict(self, *args):
            return None
    monkeypatch.setattr(L, "object_facts", fails_second)
    with pytest.raises(L.MissingObject):
        C.refresh(ix, [obj], NoTruth())
    assert ix == before and calls == 2


def test_freeze_reads_replacement_once_for_both_passes(tmp_path):
    class Object:
        name = "a.obj"
        reads = 0
        def read_bytes(self):
            self.reads += 1
            return coff()
    obj = Object()
    ix = {"objects": [obj.name], "strong": {}, "comdat": {}, "common": {},
          "common_schema": C.COMMON_SCHEMA, "selection": {"owners": {}, "exceptions": {}}}
    class NoTruth:
        def verdict(self, *args):
            return None
    C.refresh(ix, [obj], NoTruth())
    assert obj.reads == 1


def test_census_currency_guard_includes_changed_proof_policy():
    assert "tools/link_census.py" in L.CENSUS_INPUTS
    assert "tools/link_check.py" in L.CENSUS_INPUTS


def add_symbol(raw, name, value=0, section=1, storage=2):
    table, count = struct.unpack_from("<II", raw, 8)
    at = table + count * 18
    record = name.encode().ljust(8, b"\0") + struct.pack("<IhHBB", value, section, 0x20, storage, 0)
    result = bytearray(raw[:at] + record + raw[at:])
    struct.pack_into("<I", result, 12, count + 1)
    return bytes(result)


@pytest.mark.parametrize("common", [False, True])
def test_current_payload_primary_or_common_always_suppresses_fallback(tmp_path, common):
    raw, t, _ = fixture()
    raw = add_symbol(raw, "primary", 4 if common else 0, 0 if common else 1)
    obj = tmp_path / "table.obj"
    obj.write_bytes(raw)
    fact = L.object_facts(obj, t, weak_context=context())
    assert next(verdict for name, _, _, verdict in fact[0] if name == "table") != "retail"


def test_prebound_route_is_withdrawn_without_current_context():
    _, t, parts = fixture()
    bound = L.bind_weak_relocations(parts[2], context(), t)
    assert "weak_route" in bound[0][2]
    assert "weak_route" not in L.bind_weak_relocations(bound, None, t)[0][2]


def test_frozen_facts_pickle_preserves_snapshot_and_currency_rejects_mutation(tmp_path):
    import pickle
    raw, t, _ = fixture()
    obj = tmp_path / "table.obj"
    obj.write_bytes(raw)
    fact = pickle.loads(pickle.dumps(L.object_facts(obj, t)))
    assert fact.data == raw and len(fact) == 4 and fact.common == {}
    L.validate_fact_snapshots([obj], [fact])
    obj.write_bytes(add_symbol(raw, "primary"))
    with pytest.raises(L.MissingObject, match="changed during census"):
        L.validate_fact_snapshots([obj], [fact])


@pytest.mark.parametrize("change", ["primary", "common", "default", "missing"])
def test_changed_unchecked_context_object_disables_promotion(tmp_path, monkeypatch, change):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    _, t, _ = fixture()
    owner = tmp_path / "owner.obj"
    other = tmp_path / "other.obj"
    owner.write_bytes(b"owned-default")
    other.write_bytes(coff())
    sha = lambda p: __import__("hashlib").sha256(p.read_bytes()).hexdigest()
    ix = {"objects": [owner.name, other.name], "strong": {},
          "comdat": {"default": [(0, "d", "retail")]}, "common": {},
          "selection": {"owners": {"default": {owner.name}}, "exceptions": {}, "weak_kept": {"default": owner.name}, "weak_locations": {"default": owner.name}, "weak_addresses": {"default": 0x401040}, "weak_ambiguous": set()},
          "weak_schema": C.WEAK_SCHEMA, "weak_root": str(C.ROOT.resolve()), "weak_truth": L.truth_fingerprint(t),
          "weak_inventory": {p.name: (str(p), sha(p)) for p in (owner, other)},
          "_weak_token": C._WEAK_PREVIEW_TOKEN,
          "_weak_current_objects": {owner.name: (L.truth_fingerprint(t), sha(owner), L.policy_fingerprint(), owner, {"default": "d"})}}
    ix["selection"]["weak_receipt"] = C.selected_receipt_digest(ix["selection"])
    assert "default" in C.weak_context(ix, t)["defaults"]
    if change == "missing":
        other.unlink()
    else:
        other.write_bytes(add_symbol(coff(), "primary" if change != "default" else "default",
                                     4 if change == "common" else 0, 0 if change == "common" else 1))
    assert not C.weak_context(ix, t)["defaults"]


def test_census_second_pass_uses_frozen_default_and_referrer(tmp_path, monkeypatch):
    raw, t, _ = fixture()
    obj = tmp_path / "table.obj"
    obj.write_bytes(raw)
    fact = L.object_facts(obj, t)
    # Mutating disk cannot inject a primary into the second pass's frozen view.
    obj.write_bytes(add_symbol(raw, "primary"))
    class BorrowedTruth(L.RetailTruth):
        def __new__(cls, rows):
            return t
        def __init__(self, rows):
            pass
    t.__class__ = BorrowedTruth
    monkeypatch.setattr(L, "RetailTruth", BorrowedTruth)
    monkeypatch.setattr(L, "truth_fingerprint", lambda actual: fact.truth)
    # A complete frozen input lacking the provider simply remains unproven.
    result = L.rejudge_weak_facts([obj], [fact], [], {}, {})
    assert result[0].data == raw
    with pytest.raises(L.MissingObject):
        L.validate_fact_snapshots([obj], result)


def provider_coff(body=b"\xc3"):
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 60 + len(body), 1, 0, 0)
    sec = b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x60001020)
    symbol_ = b"default\0" + struct.pack("<IhHBB", 0, 1, 0x20, 2, 0)
    return header + sec + body + symbol_ + struct.pack("<I", 4)


def test_cross_pass_changed_default_cannot_replace_frozen_proof_or_be_accepted(tmp_path, monkeypatch):
    raw, t, _ = fixture()
    owner, table = tmp_path / "owner.obj", tmp_path / "table.obj"
    owner.write_bytes(provider_coff())
    table.write_bytes(raw)
    facts = [L.object_facts(p, t) for p in (owner, table)]
    assert facts[0][0][0][3] == "retail" and facts[1][0][0][3] == "unknown"
    fingerprint = facts[0].truth
    owner.write_bytes(provider_coff(b"\x90"))
    assert L.object_facts(owner, t)[0][0][3] == "wrong"
    class BorrowedTruth(L.RetailTruth):
        def __new__(cls, rows):
            return t
        def __init__(self, rows):
            pass
    t.__class__ = BorrowedTruth
    monkeypatch.setattr(L, "RetailTruth", BorrowedTruth)
    monkeypatch.setattr(L, "truth_fingerprint", lambda actual: fingerprint)
    frozen = L.rejudge_weak_facts([owner, table], facts, [], {"default": owner.name}, {"default": {owner.name}})
    assert frozen[1][0][0][3] == "retail"  # same immutable context, not new wrong bytes
    with pytest.raises(L.MissingObject):
        L.validate_fact_snapshots([owner, table], frozen)


def test_promoted_copy_cannot_become_an_independent_default(tmp_path):
    raw, t, _ = fixture()
    obj = tmp_path / "table.obj"
    obj.write_bytes(raw)
    fact = L.object_facts(obj, t, weak_context=context())
    assert fact[0][0][3] == "retail" and "table" not in fact.independent


def test_live_truth_input_drift_disables_previous_preview_proof(tmp_path, monkeypatch):
    monkeypatch.setattr(C, "ROOT", tmp_path)
    _, t, _ = fixture()
    obj = tmp_path / "owner.obj"
    obj.write_bytes(b"owned-default")
    sha = __import__("hashlib").sha256(obj.read_bytes()).hexdigest()
    ix = {"objects": [obj.name], "strong": {}, "comdat": {"default": [(0, "d", "retail")]},
          "common": {}, "selection": {"owners": {"default": {obj.name}}, "exceptions": {}, "weak_kept": {"default": obj.name}, "weak_locations": {"default": obj.name}, "weak_addresses": {"default": 0x401040}, "weak_ambiguous": set()},
          "weak_schema": C.WEAK_SCHEMA, "weak_root": str(C.ROOT.resolve()), "weak_truth": L.truth_fingerprint(t),
          "weak_inventory": {obj.name: (str(obj), sha)}, "_weak_token": C._WEAK_PREVIEW_TOKEN,
          "_weak_current_objects": {obj.name: (L.truth_fingerprint(t), sha, L.policy_fingerprint(), obj, {"default": "d"})}}
    ix["selection"]["weak_receipt"] = C.selected_receipt_digest(ix["selection"])
    assert "default" in C.weak_context(ix, t)["defaults"]
    monkeypatch.setattr(L, "truth_inputs_fingerprint", lambda: "changed-baseline-ledger-pin-import-inputs")
    assert not C.weak_context(ix, t)["defaults"]


@pytest.mark.parametrize("when", ["before_accept", "during_serialization"])
def test_actual_status_acceptance_refuses_mutation_without_replacing_artifacts(tmp_path, monkeypatch, when):
    raw, t, _ = fixture()
    owner, table = tmp_path / "owner.obj", tmp_path / "table.obj"
    owner.write_bytes(provider_coff())
    table.write_bytes(raw)
    facts = [L.object_facts(p, t) for p in (owner, table)]
    status, index, history = [tmp_path / name for name in ("status.csv", "index.pkl", "history.csv")]
    for path in (status, index, history):
        path.write_bytes(b"previous accepted evidence")
    monkeypatch.setattr(L, "STATUS", status)
    monkeypatch.setattr(L, "HISTORY", history)
    monkeypatch.setattr(C, "INDEX", index)
    monkeypatch.setattr(L.build, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(L, "library_symbols", lambda path: set())
    monkeypatch.setattr(L, "import_stubs", lambda: set())
    monkeypatch.setattr(L, "retail_imports", lambda: set())
    monkeypatch.setattr(L, "data_ledger", lambda: [])
    monkeypatch.setattr(L, "ledger_owners", lambda rows: {"default": {owner.name}})
    monkeypatch.setattr(C, "source_bytes", lambda sources: {})
    class BorrowedTruth(L.RetailTruth):
        def __new__(cls, rows):
            return t
        def __init__(self, rows):
            pass
    t.__class__ = BorrowedTruth
    monkeypatch.setattr(L, "RetailTruth", BorrowedTruth)
    prepared = L.write_status("", [], [owner, table], {}, {"default": owner.name}, publish=False, facts=facts)[4]
    if when == "before_accept":
        owner.write_bytes(provider_coff(b"\x90"))
    else:
        import pickle
        dump = pickle.dump
        def mutate_after_dump(*args, **kwargs):
            result = dump(*args, **kwargs)
            owner.write_bytes(provider_coff(b"\x90"))
            return result
        monkeypatch.setattr(pickle, "dump", mutate_after_dump)
    with pytest.raises(L.MissingObject):
        prepared["accept"]()
    assert all(path.read_bytes() == b"previous accepted evidence" for path in (status, index, history))


def test_actual_record_freezes_objects_before_selection_map(tmp_path, monkeypatch):
    _, t, _ = fixture()
    owner = tmp_path / "owner.obj"
    owner.write_bytes(provider_coff())
    monkeypatch.setattr(L, "verify_data_objects", lambda: None)
    monkeypatch.setattr(L.subprocess, "run", lambda *a, **k: __import__("types").SimpleNamespace(stdout="", returncode=0))
    monkeypatch.setattr(L, "objects", lambda rows: ([owner], []))
    monkeypatch.setattr(L, "_object_sources", lambda rows: {})
    monkeypatch.setattr(L, "stale_objects", lambda *args: [])
    monkeypatch.setattr(L, "read_history", lambda: [])
    monkeypatch.setattr(L, "head", lambda: "commit")
    monkeypatch.setattr(L, "final_log", lambda census: "")
    monkeypatch.setattr(L, "read_facts", lambda objs, rows: [L.object_facts(obj, t) for obj in objs])
    def changed_selection(objs, log):
        owner.write_bytes(provider_coff(b"\x90"))
        return ""
    monkeypatch.setattr(L, "selection_link", changed_selection)
    monkeypatch.setattr(L, "write_status", lambda *a, **k: pytest.fail("accepted stale map context"))
    with pytest.raises(L.MissingObject):
        L.record({"missing": 0}, [])


def test_cached_native_image_cannot_be_paired_with_new_native_payload(monkeypatch):
    image, sections = L.build.exe_image()
    stale = image[:-1] + bytes([image[-1] ^ 1])
    monkeypatch.setattr(L.build, "exe_image", lambda: (stale, sections))
    with pytest.raises(L.MissingObject, match="baseline changed"):
        L.RetailTruth([])


def test_official_ledger_snapshot_rejects_changed_file_without_mutation(tmp_path, monkeypatch):
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    path = reverse / "functions.csv"
    path.write_text("name,status,target_rva\nf,matched,0x1000\n")
    monkeypatch.setattr(L, "ROOT", tmp_path)
    rows = L.ledger()
    assert rows[0]["name"] == "f"
    rows.validate()
    path.write_text("name,status,target_rva\ng,matched,0x1000\n")
    with pytest.raises(L.MissingObject, match="ledger changed"):
        rows.validate()


@pytest.mark.parametrize("inventory", [None, {}, {"owner.obj": None}, {"owner.obj": (None, "hash")}])
def test_missing_or_corrupt_full_inventory_cannot_promote(inventory):
    _, t, _ = fixture()
    ix = {"objects": ["owner.obj"], "strong": {}, "comdat": {"default": [(0, "d", "retail")]},
          "common": {}, "selection": {"owners": {"default": {"owner.obj"}}, "exceptions": {}},
          "weak_schema": C.WEAK_SCHEMA, "weak_root": str(C.ROOT.resolve()), "weak_truth": L.truth_fingerprint(t), "weak_inventory": inventory}
    assert not C.weak_context(ix, t)["defaults"]


@pytest.mark.parametrize("local_definition", ["primary", "default"])
@pytest.mark.parametrize("relabel_root", [False, True])
def test_copied_index_donor_absence_cannot_promote_local_fallback(tmp_path, monkeypatch, local_definition, relabel_root):
    raw, t, _ = fixture()
    donor, local = tmp_path / "donor", tmp_path / "local"
    donor.mkdir(); local.mkdir()
    def populate(root, other_name):
        files = [root / name for name in ("owner.obj", "table.obj", "other.obj")]
        files[0].write_bytes(provider_coff())
        files[1].write_bytes(raw)
        files[2].write_bytes(provider_coff().replace(b"default\0", other_name.encode().ljust(8, b"\0")))
        return files
    donor_objects = populate(donor, "other")
    local_objects = populate(local, local_definition)
    monkeypatch.setattr(C, "ROOT", donor)
    ix = C.index_tables(donor_objects, [L.object_facts(p, t) for p in donor_objects],
                        {"owners": {"default": {"owner.obj"}}, "exceptions": {}, "weak_kept": {"default": "owner.obj"}, "weak_locations": {"default": "owner.obj"}, "weak_addresses": {"default": 0x401040}, "weak_ambiguous": set()})
    monkeypatch.setattr(C, "ROOT", local)
    if relabel_root:
        ix["weak_root"] = str(local.resolve())  # paths must remain bound too
    C.refresh(ix, local_objects[:2], t)
    assert ix["weak_inventory"]["other.obj"][0] == str(donor_objects[2])
    assert local_definition in {n for n, *_ in L.object_facts(local_objects[2], t)[0]}
    ctx = C.weak_context(ix, t)
    assert not ctx["defaults"]
    assert L.object_facts(local_objects[1], t, weak_context=ctx)[0][0][3] == "unknown"


def test_inventory_object_name_must_match_current_checkout_path(tmp_path, monkeypatch):
    _, t, _ = fixture()
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj = tmp_path / "owner.obj"
    obj.write_bytes(provider_coff())
    fact = L.object_facts(obj, t)
    ix = C.index_tables([obj], [fact], {"owners": {"default": {obj.name}}, "exceptions": {}, "weak_kept": {"default": obj.name}, "weak_locations": {"default": obj.name}, "weak_addresses": {"default": 0x401040}, "weak_ambiguous": set()})
    C.refresh(ix, [obj], t)
    assert "default" in C.weak_context(ix, t)["defaults"]
    renamed = tmp_path / "different.obj"
    renamed.write_bytes(obj.read_bytes())
    ix["weak_inventory"][obj.name] = (str(renamed), ix["weak_inventory"][obj.name][1])
    assert not C.weak_context(ix, t)["defaults"]


@pytest.mark.parametrize("holder,addresses,expected", [
    ("selected_stubs.obj", {"default": 0x401000, "primary": 0x402000}, "unknown"),
    ("native.lib:member.obj", {"default": 0x401000, "primary": 0x402000}, "unknown"),
    ("owner.obj", {}, "unknown"),
    ("owner.obj", {"default": 0, "primary": 0}, "unknown"),
    ("owner.obj", {"default": 0x401000, "primary": 0x402000}, "unknown"),
    ("owner.obj", {"default": 0x401000, "primary": 0x401000}, "retail"),
])
def test_actual_selected_primary_requires_same_owned_holder_and_address(holder, addresses, expected):
    _, t, parts = fixture()
    kept = L.SelectedDefinitions({"default": "owner.obj", "primary": holder})
    kept.addresses = addresses
    ctx = L.weak_selection_context({"default": {"owner.obj"}},
        {"default": {"owner.obj": ("independent", "retail")}}, {"default": {"owner.obj"}}, kept, set())
    assert judge(t, parts, ctx) == expected


def test_actual_map_retains_legitimate_alias_and_rejects_ambiguous_primary():
    _, t, parts = fixture()
    text = (" 0001:00000000 default 00401000 f i owner.obj\n"
            " 0001:00000000 primary 00401000 f i owner.obj\n")
    kept = L.selected_definitions(text)
    make = lambda k: L.weak_selection_context({"default": {"owner.obj"}},
        {"default": {"owner.obj": ("independent", "retail")}}, {"default": {"owner.obj"}}, k, set())
    assert kept.addresses["primary"] == kept.addresses["default"] == 0x401000
    assert judge(t, parts, make(kept)) == "retail"
    kept = L.selected_definitions(text + " 0001:00000004 primary 00402000 f i foreign.obj\n")
    assert "primary" in kept.ambiguous and judge(t, parts, make(kept)) == "unknown"


@pytest.mark.parametrize("holder,addresses,expected", [
    ("selected_stubs.obj", {"default": 0x401000, "primary": 0x402000}, "unknown"),
    ("owner.obj", {"default": 0x401000, "primary": 0x402000}, "unknown"),
    ("owner.obj", {"default": 0x401000, "primary": 0x401000}, "retail"),
])
def test_foreign_actual_primary_survives_index_and_refresh(tmp_path, monkeypatch, holder, addresses, expected):
    raw, t, _ = fixture()
    monkeypatch.setattr(C, "ROOT", tmp_path)
    owner, table = tmp_path / "owner.obj", tmp_path / "table.obj"
    owner.write_bytes(provider_coff()); table.write_bytes(raw)
    facts = [L.object_facts(o, t) for o in (owner, table)]
    selection = {"owners": {"default": {owner.name}}, "exceptions": {},
                 "weak_kept": {"default": owner.name, "primary": holder}, "weak_addresses": addresses,
                 "weak_locations": {"default": owner.name, "primary": holder}, "weak_ambiguous": set()}
    index = C.index_tables([owner, table], facts, selection)
    C.refresh(index, [owner, table], t)
    ctx = C.weak_context(index, t)
    assert ctx["selected"]["primary"] == holder
    assert L.object_facts(table, t, weak_context=ctx)[0][0][3] == expected


@pytest.mark.parametrize("primary_location,default_location", [
    ("vendor.lib:owner.obj", "owner.obj"),
    ("owner.obj", "vendor.lib:owner.obj"),
    ("vendor.lib:owner.obj", "vendor.lib:owner.obj"),
])
def test_actual_map_library_qualification_cannot_impersonate_source_owner(primary_location, default_location):
    _, t, parts = fixture()
    kept = L.selected_definitions(
        f" 0001:00000000 default 00401000 f i {default_location}\n"
        f" 0001:00000000 primary 00401000 f i {primary_location}\n")
    assert kept["default"] == kept["primary"] == "owner.obj"  # ordinary legacy behavior retained
    assert kept.locations["default"] == default_location
    ctx = L.weak_selection_context({"default": {"owner.obj"}},
        {"default": {"owner.obj": ("independent", "retail")}}, {"default": {"owner.obj"}}, kept, set())
    assert judge(t, parts, ctx) == "unknown"


@pytest.mark.parametrize("drift", ["missing_addresses", "missing_locations", "missing_ambiguous",
                                   "inconsistent_keys", "wrong_address_type", "wrong_raw_holder"])
def test_partial_or_corrupt_selected_receipt_cannot_promote(tmp_path, monkeypatch, drift):
    _, t, _ = fixture()
    monkeypatch.setattr(C, "ROOT", tmp_path)
    obj = tmp_path / "owner.obj"
    obj.write_bytes(provider_coff())
    selection = {"owners": {"default": {obj.name}}, "exceptions": {}, "weak_kept": {"default": obj.name},
                 "weak_locations": {"default": obj.name}, "weak_addresses": {"default": 0x401040},
                 "weak_ambiguous": set()}
    ix = C.index_tables([obj], [L.object_facts(obj, t)], selection)
    C.refresh(ix, [obj], t)
    selection = ix["selection"]
    assert "default" in C.weak_context(ix, t)["defaults"]
    if drift.startswith("missing_"):
        selection.pop("weak_" + drift[len("missing_"):])
    elif drift == "inconsistent_keys":
        selection["weak_addresses"]["foreign"] = 0x402000
    elif drift == "wrong_address_type":
        selection["weak_addresses"]["default"] = "00401040"
    else:
        selection["weak_locations"]["default"] = "another.obj"
    assert not C.weak_context(ix, t)["defaults"]


def test_jointly_dropped_foreign_primary_receipt_is_not_resealed_by_refresh(tmp_path, monkeypatch):
    import pickle
    raw, t, _ = fixture()
    monkeypatch.setattr(C, "ROOT", tmp_path)
    owner, table = tmp_path / "owner.obj", tmp_path / "table.obj"
    owner.write_bytes(provider_coff()); table.write_bytes(raw)
    selection = {"owners": {"default": {owner.name}}, "exceptions": {},
                 "weak_kept": {"default": owner.name, "primary": "selected_stubs.obj"},
                 "weak_locations": {"default": owner.name, "primary": "selected_stubs.obj"},
                 "weak_addresses": {"default": 0x401040, "primary": 0x402000}, "weak_ambiguous": set()}
    ix = C.index_tables([owner, table], [L.object_facts(o, t) for o in (owner, table)], selection)
    ix = pickle.loads(pickle.dumps(ix))
    for key in ("weak_kept", "weak_locations", "weak_addresses"):
        ix["selection"][key].pop("primary")
    assert ix["selection"]["weak_receipt"] != C.selected_receipt_digest(ix["selection"])
    C.refresh(ix, [owner, table], t)
    assert not C.weak_context(ix, t)["defaults"]
    assert L.object_facts(table, t, weak_context=C.weak_context(ix, t))[0][0][3] == "unknown"
