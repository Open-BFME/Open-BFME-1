"""Donor provenance stays pinned across index lookup and source delivery."""
import hashlib
import io
import json
from pathlib import Path
import sys
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import worldbuilder_donors as donors


def fixture(tmp_path):
    target = SimpleNamespace(root=tmp_path, target_id="worldbuilder",
        manifest_path=tmp_path / "inputs/baselines/bfme1/workshop-vanilla-1.03/manifest.json",
        ledger_root=tmp_path / "targets/worldbuilder/reverse", build_root=tmp_path / "build/worldbuilder",
        expected_sha256="a" * 64,
        exports=[SimpleNamespace(name="?method@Owner@@QAEXXZ", rva=0x1234, forwarder=None)],
        section_for_rva=lambda _: SimpleNamespace(characteristics=0x60000020))
    body = b"void Owner::method() {}\n"
    config = {"schema_version": 1, "references": {
        name: {"repository": repo, "revision": character * 40, "ledger_git_blob_sha1": "c" * 40}
        for (name, repo), character in zip(donors.REPOSITORIES.items(), "12")}}
    raw = donors._json_bytes(config)
    index = {"schema_version": 1, "target_id": target.target_id, "binary_sha256": target.expected_sha256,
        "references_sha256": hashlib.sha256(raw).hexdigest(), "target_evidence": "PE export name; source hypothesis",
        "donors": [{"reference": "bfme2", "symbol": "?method@Owner@@QAEXXZ",
            "worldbuilder_export_rva": 0x1234, "donor_rva": 0x2345, "donor_size": 1,
            "source": "Code/GameEngine/Owner.cpp", "source_git_blob_sha1": donors.git_blob_hash(body)}]}
    (target.root / "targets/worldbuilder").mkdir(parents=True)
    target.ledger_root.mkdir(parents=True)
    (target.root / "targets/worldbuilder" / "references.json").write_bytes(raw)
    (target.ledger_root / "donors.json").write_bytes(donors._json_bytes(index))
    return target, body, config, index


def test_lookup_is_offline_and_supplies_revision_hash_and_source(tmp_path, monkeypatch):
    target, body, _, _ = fixture(tmp_path)
    monkeypatch.setattr(donors, "urlopen", lambda *_a, **_k: pytest.fail("offline lookup used network"))
    record, = donors.lookup(target, "Owner.cpp")
    assert record["revision"] == "2" * 40
    assert record["source_git_blob_sha1"] == donors.git_blob_hash(body)
    assert record["repository"] == donors.REPOSITORIES["bfme2"]
    assert donors.lookup(target, record["symbol"], exact=True) == [record]
    assert donors.lookup(target, "Owner", exact=True) == []
    assert donors.lookup(target, reference="bfme1") == []


def test_changing_pin_invalidates_existing_index(tmp_path):
    target, _, config, _ = fixture(tmp_path)
    config["references"]["bfme2"]["revision"] = "3" * 40
    (target.root / "targets/worldbuilder" / "references.json").write_bytes(donors._json_bytes(config))
    with pytest.raises(donors.DonorError, match="index/reference/target mismatch"):
        donors.lookup(target)


@pytest.mark.parametrize("field,value", [("binary_sha256", "f" * 64), ("target_id", "bfme1")])
def test_other_target_index_rejected(tmp_path, field, value):
    target, _, _, index = fixture(tmp_path)
    index[field] = value
    (target.ledger_root / "donors.json").write_bytes(donors._json_bytes(index))
    with pytest.raises(donors.DonorError, match="mismatch"):
        donors.lookup(target)


def test_fetch_uses_exact_pin_and_reuses_hash_valid_cache(tmp_path, monkeypatch):
    target, body, _, _ = fixture(tmp_path)
    record, = donors.lookup(target)
    calls = []
    def remote(reference, source):
        calls.append((reference["revision"], source))
        return body
    monkeypatch.setattr(donors, "_remote_bytes", remote)
    path = donors.fetch_source(target, record)
    assert path.read_bytes() == body
    assert path == target.build_root / "donors/bfme2" / ("2" * 40) / record["source"]
    assert donors.fetch_source(target, record) == path
    assert calls == [("2" * 40, "Code/GameEngine/Owner.cpp")]


def test_remote_wrong_blob_is_not_cached(tmp_path, monkeypatch):
    target, _, _, _ = fixture(tmp_path)
    record, = donors.lookup(target)
    monkeypatch.setattr(donors, "_remote_bytes", lambda *_: b"wrong source revision")
    with pytest.raises(donors.DonorError, match="Git blob hash mismatch"):
        donors.fetch_source(target, record)
    assert not list(target.build_root.rglob("Owner.cpp"))


def test_corrupted_cache_fails_without_silent_refetch(tmp_path, monkeypatch):
    target, body, _, _ = fixture(tmp_path)
    record, = donors.lookup(target)
    monkeypatch.setattr(donors, "_remote_bytes", lambda *_: body)
    path = donors.fetch_source(target, record)
    path.write_bytes(b"changed")
    monkeypatch.setattr(donors, "_remote_bytes", lambda *_: pytest.fail("silently repaired corrupt cache"))
    with pytest.raises(donors.DonorError, match="cached donor Git blob hash mismatch"):
        donors.fetch_source(target, record)


def test_stale_record_and_unbound_export_are_rejected(tmp_path):
    target, _, _, index = fixture(tmp_path)
    record, = donors.lookup(target)
    with pytest.raises(donors.DonorError, match="stale"):
        donors.fetch_source(target, dict(record, revision="4" * 40))
    index["donors"][0]["worldbuilder_export_rva"] += 1
    (target.ledger_root / "donors.json").write_bytes(donors._json_bytes(index))
    with pytest.raises(donors.DonorError, match="no corresponding WorldBuilder export"):
        donors.lookup(target)


def test_refresh_keeps_only_streamed_real_source_candidates(tmp_path, monkeypatch):
    target, body, _, _ = fixture(tmp_path)
    rows = [{"name": "?method@Owner@@QAEXXZ", "status": "matched", "source": "Code/Owner.cpp",
             "target_rva": "0x1234", "target_size": "1"},
            {"name": "?method@Owner@@QAEXXZ", "status": "matched", "source": "Code/Lift.cpp",
             "target_rva": "0x2345", "target_size": "2"}]
    lift = b"__declspec(naked) void f() { __asm _emit 0xc3 }"
    tree = {"reverse/functions.csv": {"sha": "a" * 40, "size": 1},
            "Code/Owner.cpp": {"sha": donors.git_blob_hash(body), "size": len(body)},
            "Code/Lift.cpp": {"sha": donors.git_blob_hash(lift), "size": len(lift)}}
    monkeypatch.setattr(donors, "_tree", lambda *_: tree)
    monkeypatch.setattr(donors, "_ledger_rows", lambda *_: (rows, {"sha256": "b" * 64, "size": 1}))
    monkeypatch.setattr(donors, "_read_source", lambda _t, _n, _r, source, _h: body if "Owner" in source else lift)
    index = donors.refresh(target, {"bfme1": "1" * 40, "bfme2": "2" * 40})
    assert len(index["donors"]) == 2
    assert all(row["source"] == "Code/Owner.cpp" for row in index["donors"])
    assert index["excluded_assembly_sources"] == {name: ["Code/Lift.cpp"] for name in donors.REPOSITORIES}
    assert len(donors.lookup(target)) == 2


def test_truncated_streamed_ledger_fails_its_pinned_blob_hash(tmp_path, monkeypatch):
    data = (b"name,status,source,notes\n"
            b"selected,matched,Code/Owner.cpp,\n")
    monkeypatch.setattr(donors, "urlopen", lambda *_a, **_k: io.BytesIO(data[:-1]))
    reference = {"repository": donors.REPOSITORIES["bfme2"], "revision": "2" * 40}
    with pytest.raises(donors.DonorError, match="differs from the pinned Git tree"):
        donors._ledger_rows(SimpleNamespace(root=tmp_path), "bfme2", reference, {"selected"},
                            {"sha": donors.git_blob_hash(data), "size": len(data)})
