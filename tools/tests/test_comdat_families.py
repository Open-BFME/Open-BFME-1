"""Read-only COMDAT family diagnostics keep BFME1 selection/identity policy."""
import copy
import hashlib
import json
from pathlib import Path
import pickle
import sys
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import comdat_families as C
import claims

NAME = "?reserve@?$Vector@H@@QAEXI@Z"
OTHER = "?clear@?$Vector@H@@QAEXXZ"
STL = "?reserve@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXI@Z"


def entry(obj, names=(), linked=False):
    return {"object": obj, "linked": linked, "losers": list(names), "wrong_selected": [],
            "unresolved": [], "duplicates": [], "addresses": 0}


def census(name=NAME):
    return {"meta": {"commit": "census"}, "objects": ["wrong.obj", "provider.obj", "consumer.obj"],
            "comdat": {name: [(0, "bad", "wrong"), (1, "good", "retail")]}, "strong": {},
            "selection": {"exceptions": {}, "owners": {name: {"provider.obj"}}},
            "blockers": {"wrong.cpp": entry("wrong.obj", [name]),
                         "provider.cpp": entry("provider.obj", [], True),
                         "consumer.cpp": {**entry("consumer.obj"), "wrong_selected": [name]}}}


def analyze(index=None, **kwargs):
    return C.analyze(index or census(), {"wrong.cpp": [(100, 180)], "consumer.cpp": [(150, 200)]}, **kwargs)


def test_provider_wrong_emitters_link_order_and_bfme1_judgments():
    ix = census()
    before = copy.deepcopy(ix)
    family = analyze(ix)["families"][0]
    assert family["canonical_provider"]["object"] == "provider.obj"
    assert family["canonical_provider"]["ledger_owner"]
    assert "relocations" in family["canonical_provider"]["evidence"]
    assert family["wrong_emitters"][0]["sources"] == ["wrong.cpp"]
    assert family["selected_object"] == "wrong.obj"
    assert family["selected_verdict"] == "wrong"
    assert family["keep_rule"] == "retail"
    assert family["losing_objects"] == ["wrong.obj"]
    assert family["consumer_units"] == ["consumer.cpp", "wrong.cpp"]
    assert family["bytes_blocked"] == 100
    assert family["servable"]
    assert family["suggested_model_tier"] == "Sol High"
    assert ix == before  # no in-place index/table reordering


@pytest.mark.parametrize("verdict", [None, "unknown", "wrong"])
def test_no_proven_provider_never_established_or_served(verdict):
    ix = census()
    ix["comdat"][NAME][1] = (1, "bad", verdict)  # even a byte twin cannot supply proof
    family = analyze(ix, patterns={NAME: [{"file": "x.cpp", "line": 3}]})["families"][0]
    assert family["canonical_provider"] is None
    assert family["status"] == family["confidence"] == "needs provider analysis"
    assert family["suggested_model_tier"] == "Sol High"
    assert not family["servable"]


@pytest.mark.parametrize("name,owner", [(STL, "stlport"), ("??1AsciiString@@QAE@XZ", "strings"),
                                        ("?TheScriptEngine@@3PAVScriptEngine@@A", "globals")])
def test_owner_held_families_excluded(name, owner):
    family = analyze(census(name))["families"][0]
    assert family["status"] == "owner-held"
    assert family["owner_family"] == owner
    assert not family["servable"]


def test_overlapping_families_and_multiple_blockers_are_nonadditive():
    ix = census()
    ix["comdat"][OTHER] = list(ix["comdat"][NAME])
    ix["blockers"]["consumer.cpp"]["wrong_selected"].append(OTHER)
    report = analyze(ix)
    assert len(report["families"]) == 2
    assert sum(f["bytes_blocked"] for f in report["families"]) == 150
    assert report["bytes_blocked_unique"] == 100
    first = next(f for f in report["families"] if f["family"] == NAME)
    assert first["conditional_single_family_bytes"] == 80


def test_ledger_owner_and_equal_digest_never_override_retail_truth():
    ix = census()
    ix["comdat"][NAME] = [(0, "same", "wrong"), (1, "same", "retail")]
    ix["selection"]["owners"][NAME] = {"wrong.obj"}
    f = analyze(ix)["families"][0]
    assert f["canonical_provider"]["object"] == "provider.obj"
    assert f["selected_verdict"] == "wrong"
    assert len(f["wrong_emitters"]) == 1


def test_name_contradiction_vetoes_even_a_byte_proven_ledger_owner():
    checks = [{"rva": "0x00106670", "verdict": "CONTRADICTED"}]
    family = analyze(homes={NAME: {0x00106670}}, identities={NAME: checks})["families"][0]
    assert family["identity_contradicted"]
    assert family["identity_oracle"] == checks
    assert family["canonical_provider"] is None
    assert family["proven_copies"][0]["object"] == "provider.obj"
    assert not family["servable"]
    assert "identity contradicted" in family["status"]
    assert "Resolve" in family["hypothesis"]


@pytest.mark.parametrize("verdict", ["CONFIRMED", "UNTESTABLE", "UNAVAILABLE"])
def test_noncontradicting_oracle_result_is_reported_without_becoming_identity_proof(verdict):
    checks = [{"rva": "0x1000", "verdict": verdict}]
    family = analyze(homes={NAME: {0x1000}}, identities={NAME: checks})["families"][0]
    assert not family["identity_contradicted"]
    assert family["identity_oracle"] == checks
    assert family["canonical_provider"] is not None
    assert "independent evidence" in family["canonical_provider"]["evidence"]


def test_identity_oracle_reads_only_supplied_root_and_claimed_homes(tmp_path, monkeypatch):
    import ilt_oracle
    path = tmp_path / "targets/game/reverse/ilt_windows.tsv"
    path.parent.mkdir(parents=True)
    path.write_text("fixture")
    seen = []

    class Oracle:
        def __init__(self, windows):
            assert windows == path

        def check(self, name, rva):
            seen.append((name, rva))
            return "CONTRADICTED", 0.001, "outside window"

    monkeypatch.setattr(ilt_oracle, "Oracle", Oracle)
    result = C.identity_checks(tmp_path, {NAME: {0x2000, 0x1000}})
    assert seen == [(NAME, 0x1000), (NAME, 0x2000)]
    assert result[NAME][0]["rva"] == "0x00001000"
    assert result[NAME][1]["verdict"] == "CONTRADICTED"


def test_missing_identity_windows_are_explicit(tmp_path):
    result = C.identity_checks(tmp_path, {NAME: {0x1000}})
    assert result[NAME][0]["verdict"] == "UNAVAILABLE"
    assert result[NAME][0]["p_false"] is None


@pytest.mark.parametrize("name", ["?get@Rva0009FEF0Dword@@QBEIXZ", "?get@BfmeOwner@@QBEIXZ"])
def test_opaque_names_do_not_claim_the_retail_spelling(tmp_path, name):
    result = C.identity_checks(tmp_path, {name: {0x9FEF0}})
    assert result[name][0]["verdict"] == "NOT_APPLICABLE"


def test_unknown_map_holder_is_not_first_copy_fallback():
    ix = census()
    ix["selection"]["exceptions"][NAME] = None
    f = analyze(ix)["families"][0]
    assert f["selected_object"] is None
    assert f["selected_verdict"] == "unknown"
    assert not f["servable"]


def test_strong_definers_are_reported_and_not_served():
    ix = census()
    ix["strong"][NAME] = [2]
    f = analyze(ix)["families"][0]
    assert len(f["definers"]) == 3
    assert f["definers"][-1]["retail_verdict"] == "strong"
    assert f["suggested_model_tier"] == "Astra High"
    assert not f["servable"]


def test_bfme2_exact_comment_and_marker_signature_lookup(tmp_path, monkeypatch):
    code = tmp_path / "Code"
    code.mkdir()
    source = code / "sample.cpp"
    source.write_text(f"// bfme link decl-only begin\n"
                      "namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }\n"
                      "// bfme link decl-only end\n"
                      f"// Suppress this TU's non-retail copy of {NAME}:\n"
                      "template <> void Vector<int>::reserve(unsigned int);\n"
                      f"// Suppress this TU's non-retail copy of {OTHER[:-2]}:\n"
                      "template <> void Vector<int>::clear();\n")
    dtor = "??1?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ"
    monkeypatch.setattr(C.shutil, "which", lambda _: "/native/llvm-undname")
    monkeypatch.setattr(C.subprocess, "run", lambda *a, **k: SimpleNamespace(returncode=1, stderr="error: Invalid mangled name\n", stdout=dtor + "\n"
                        "public: __thiscall _STL::vector<void *, class _STL::allocator<void *>>::~vector<void *, class _STL::allocator<void *>>(void)\n"))
    result, scan = C.bfme2_patterns(tmp_path, {NAME, OTHER, dtor})
    assert result[NAME][0]["line"] == 4
    assert result[dtor][0]["line"] == 2
    assert result[dtor][0]["file"] == "Code/sample.cpp"
    assert OTHER not in result  # never complete a truncated decorated name by prefix
    assert scan["marker_files"] == 1
    assert scan["demangle_errors"] == 1


def test_pattern_lookup_without_demangler_is_conservative(tmp_path, monkeypatch):
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/x.cpp").write_text("// bfme link decl-only begin\nnamespace _STL { template <> vector<int>::~vector(); }\n")
    monkeypatch.setattr(C.shutil, "which", lambda _: None)
    result, scan = C.bfme2_patterns(tmp_path, {NAME})
    assert not result
    assert not scan["demangler"]


@pytest.mark.parametrize("name,provider,pattern,verdict,strong,tier", [
    (NAME, {}, [1], "wrong", set(), "Luna Medium"),
    (NAME, None, [1], "wrong", set(), "Sol High"),
    (NAME, {}, [], "unknown", set(), "Astra High"),
    ("??_GThing@@UAEPAXI@Z", {}, [1], "wrong", set(), "Astra XHigh"),
    ("??1Thing@@QAE@XZ", {}, [1], "wrong", set(), "Astra XHigh"),
])
def test_model_tier_metadata(name, provider, pattern, verdict, strong, tier):
    assert C.model_tier(name, provider, pattern, verdict, strong)[0] == tier


def test_coff_consumers_are_hash_bound_and_missing_is_incomplete(tmp_path, monkeypatch):
    payload = b"coff snapshot"
    (tmp_path / "consumer.obj").write_bytes(payload)
    ix = census()
    ix["weak_inventory"] = {"consumer.obj": ("/not/local/consumer.obj", hashlib.sha256(payload).hexdigest()),
                            "wrong.obj": ("/missing", "bad")}
    monkeypatch.setattr(C.link_census, "_coff_symbols", lambda data: [
        {"name": NAME, "storage": 2, "section": 0}])
    refs, scan = C.census_consumers(ix, {NAME}, tmp_path)
    assert refs == {NAME: {"consumer.obj"}}
    assert scan == {"complete": False, "verified_objects": 1, "missing_objects": 1, "missing_inventory": 1}
    (tmp_path / "consumer.obj").write_bytes(b"changed")
    refs, scan = C.census_consumers(ix, {NAME}, tmp_path)
    assert not refs and scan["changed_objects"] == 1


def mock_serving(monkeypatch):
    monkeypatch.setattr(claims, "_fetch_master", lambda: "tip")
    monkeypatch.setattr(claims, "active", lambda: {})
    monkeypatch.setattr(C.link_check, "_git", lambda *args, **kw: "")
    monkeypatch.setattr(C.link_check, "linked_since", lambda _: (frozenset(), "", ""))


def test_next_claims_entire_family_with_existing_link_queue_key(monkeypatch):
    mock_serving(monkeypatch)
    calls = []
    key = C.link_check.claim_key(NAME)

    def claim(keys, **kwargs):
        calls.append((keys, kwargs))
        return SimpleNamespace(claimed=keys, leases={key: "lease"})

    monkeypatch.setattr(claims, "claim", claim)
    result = C.serve(analyze())
    assert calls[0][0] == [key]
    assert "family:" in calls[0][1]["note"]
    assert result["claim_trailer"] == claims.trailer(key, "lease")
    assert len(result["definers"]) == 2
    assert C.serve(analyze(census(STL))) is None


def test_next_excludes_claimed_family_and_dry_run_never_claims(monkeypatch):
    mock_serving(monkeypatch)
    monkeypatch.setattr(claims, "claim", lambda *a, **k: pytest.fail("dry run claimed"))
    assert C.serve(analyze(), no_claim=True)["family"] == NAME
    monkeypatch.setattr(claims, "active", lambda: {C.link_check.claim_key(NAME): {"owner": "other"}})
    assert C.serve(analyze(), no_claim=True) is None


def test_next_fails_closed_for_shared_or_dirty_source_movement(monkeypatch):
    mock_serving(monkeypatch)
    monkeypatch.setattr(C.link_check, "_git", lambda *args, **kw: "game/changed.cpp\n" if args[0] == "diff" else "")
    with pytest.raises(ValueError, match="shared inputs changed"):
        C.serve(analyze(), no_claim=True)


def test_filtered_ledger_real_bytes_and_nonmutation_cli(tmp_path, monkeypatch, capsys):
    ledger = tmp_path / "targets/game/reverse/functions.csv"
    ledger.parent.mkdir(parents=True)
    ledger.write_text("name,target_rva,target_size,source,status,notes\n"
                      "one,0x1000,8,wrong.cpp,matched,\n"
                      "two,0x1004,8,consumer.cpp,matched,\n"
                      "skip,0x1000,12,not-wanted.cpp,matched,\n"
                      "dump,0x1000,99,wrong.cpp,unmatched,\n")
    for name in ("wrong.cpp", "consumer.cpp", "provider.cpp"):
        (tmp_path / name).write_text("// immutable source\n")
    symbols = ledger.with_name("symbols.csv")
    symbols.write_bytes(b"name,address\r\n")
    index = tmp_path / "index.pkl"
    index.write_bytes(pickle.dumps(census()))
    monkeypatch.setattr(C, "ROOT", tmp_path)
    monkeypatch.setattr(C.progress, "naked_cpp_rows", lambda *a: set())
    monkeypatch.setattr(C.progress, "_text_image", lambda: (0x1000, b"a" * 6 + b"\xcc\xcc" + b"b" * 4))
    monkeypatch.setattr(C.subprocess, "run", lambda *a, **k: pytest.fail("no compiler/subprocess expected"))
    before = {p: p.read_bytes() for p in tmp_path.rglob("*") if p.is_file()}
    assert C.main(["ranked", "--index", str(index), "--limit", "0"]) == 0
    result = json.loads(capsys.readouterr().out)
    assert result["bytes_blocked_unique"] == 10  # overlap and padding excluded
    assert result["families"][0]["bytes_blocked"] == 10
    assert {p: p.read_bytes() for p in tmp_path.rglob("*") if p.is_file()} == before


def test_ordinary_comdat_is_reported_but_not_served_as_specialization():
    family = analyze(census("?member@Ordinary@@QAEXXZ"))["families"][0]
    assert family["canonical_provider"] is not None
    assert not family["servable"]
    assert "unestablished" in family["repair_applicability"]
    assert family["bfme2_pattern_status"] == "not established by bounded lookup"


def test_body_after_annotation_is_never_decl_only_evidence(tmp_path, monkeypatch):
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/x.cpp").write_text(
        f"// bfme link decl-only begin\n// Suppress this TU's non-retail copy of {NAME}:\n"
        "template <> void Vector<int>::reserve(unsigned int) {}\n"
        "template <> void Other<int>::reserve(unsigned int);\n// bfme link decl-only end\n")
    monkeypatch.setattr(C.shutil, "which", lambda _: None)
    patterns, _ = C.bfme2_patterns(tmp_path, {NAME})
    assert NAME not in patterns


def test_filtered_intervals_exclude_generated_and_naked_and_clip_text(tmp_path, monkeypatch):
    ledger = tmp_path / "targets/game/reverse/functions.csv"
    ledger.parent.mkdir(parents=True)
    ledger.write_text("name,target_rva,target_size,source,status,notes\n"
                      "one,0x1000,8,one.cpp,matched,\n"
                      "gen,0x1000,8,generated.cpp,matched,gen-tgrid\n"
                      "naked,0x1000,8,naked.cpp,matched,\n"
                      "tail,0x1004,99,tail.cpp,matched,\n")
    for name in ("one.cpp", "generated.cpp", "naked.cpp", "tail.cpp"):
        (tmp_path / name).write_text("// fixture\n")
    monkeypatch.setattr(C.progress, "naked_cpp_rows", lambda *a: {("naked", "0x1000")})
    monkeypatch.setattr(C.progress, "_text_image", lambda: (0x1002, b"abcdef"))
    found = C.source_intervals(tmp_path, {"one.cpp", "generated.cpp", "naked.cpp", "tail.cpp"})
    assert found == {"one.cpp": [(0x1002, 0x1008)], "tail.cpp": [(0x1004, 0x1008)]}
