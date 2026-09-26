"""WorldBuilder mutations must be atomic and cannot consume game state."""

import hashlib
import json
from pathlib import Path
import subprocess
import sys
from types import MappingProxyType, SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import target_verify
from targets import CompilerProfile, Export, Section, Target
import worldbuilder as wb


@pytest.fixture
def target(tmp_path):
    image = tmp_path / "worldbuilder.exe"
    image.write_bytes(b"\xc3\xcc" * 32)
    ledger = tmp_path / "reverse/worldbuilder"
    ledger.mkdir(parents=True)
    (ledger / "functions.csv").write_bytes(wb.serialize([]))
    (tmp_path / "reverse/functions.csv").write_bytes(b"GAME LEDGER MUST NOT CHANGE\r\n")
    source = tmp_path / "Code/Tools/WorldBuilder/src/Editor.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("void Body() {}\n")
    subprocess.run(["git", "init", "--quiet", str(tmp_path)], check=True)
    subprocess.run(["git", "add", "Code/Tools/WorldBuilder/src/Editor.cpp"], cwd=tmp_path, check=True)
    return Target("worldbuilder", tmp_path, tmp_path / "target.json", image,
                  hashlib.sha256(image.read_bytes()).hexdigest(), ledger,
                  tmp_path / "build/worldbuilder", {"editor-size": CompilerProfile(("-O1",), ())},
                  0x400000, (Section(".text", 0x1000, 64, 64, 0, 0x60000020),),
                  image.read_bytes(), (Export("?Body@@YAXXZ", 1, 0x1000, None),), (), (), MappingProxyType({}))


def row(**changes):
    result = dict(name="?Body@@YAXXZ", target_rva="0x00001000", target_size="1",
                  status="matched", source="Code/Tools/WorldBuilder/src/Editor.cpp",
                  profile="editor-size", evidence="export", model="test-model")
    result.update(changes)
    return result


def candidate(target):
    result = row()
    result["bytes_sha256"] = hashlib.sha256(target.read_rva(0x1000, 1)).hexdigest()
    result["id"] = "Editor::Body"
    result["packet_sha256"] = wb.packet_hash(result)
    (target.ledger_root / "candidates.json").write_text(json.dumps(dict(
        schema_version=1, target_id=target.target_id, binary_sha256=target.expected_sha256,
        candidates=[result])))
    return result


def queue_candidates(target, identities):
    target.ledger_path.write_bytes(wb.serialize([row()]))
    candidates = []
    for index, identity in enumerate(identities):
        family = identity.split("::")[0]
        rva = 0x1002 + index * 2
        packet = row(name=identity, target_rva=rva, source=f"Code/Tools/WorldBuilder/src/{family}.cpp")
        packet.update(id=identity, bytes_sha256=hashlib.sha256(target.read_rva(rva, 1)).hexdigest())
        packet["packet_sha256"] = wb.packet_hash(packet)
        candidates.append(packet)
    (target.ledger_root / "candidates.json").write_text(json.dumps(dict(
        schema_version=1, target_id=target.target_id, binary_sha256=target.expected_sha256,
        candidates=candidates)))
    return candidates


def blocked(target, selector):
    return wb.record(target, SimpleNamespace(selector=selector, status="blocked", model="test-model",
        evidence="complete RET boundary; unsupported dependency", blocker="dependency", stash=None, score=None))


def test_fresh_family_precedes_earlier_blocked_family(target):
    queue_candidates(target, ["Frame::Retry", "Doc::Fresh", "View::Fresh"])
    blocked(target, "Frame::Retry")
    assert [packet["id"] for packet in wb.open_candidates(target)] == [
        "Doc::Fresh", "View::Fresh", "Frame::Retry"]


def test_next_fresh_sibling_keeps_attempted_members_of_same_file(target, monkeypatch, capsys):
    queue_candidates(target, ["Frame::Retry", "Frame::Fresh", "Doc::Fresh"])
    blocked(target, "Frame::Retry")
    monkeypatch.setattr(wb, "load_target", lambda name: target)
    monkeypatch.setattr(wb.worldbuilder_donors, "lookup", lambda *args, **kwargs: [])
    assert wb.main(["next"]) == 0
    packets = json.loads(capsys.readouterr().out)["candidates"]
    assert [packet["id"] for packet in packets] == ["Frame::Fresh", "Frame::Retry"]
    assert len(packets[1]["previous_attempts"]) == 1


def test_exhausted_fresh_queue_preserves_attempted_candidates_in_inventory_order(target):
    queue_candidates(target, ["Frame::Retry", "Doc::Retry"])
    blocked(target, "Doc::Retry")
    blocked(target, "Frame::Retry")
    assert [packet["id"] for packet in wb.open_candidates(target)] == ["Frame::Retry", "Doc::Retry"]


def test_explicit_show_retry_remains_available_with_fresh_work(target, monkeypatch, capsys):
    queue_candidates(target, ["Frame::Retry", "Doc::Fresh"])
    blocked(target, "Frame::Retry")
    monkeypatch.setattr(wb, "load_target", lambda name: target)
    monkeypatch.setattr(wb.worldbuilder_donors, "lookup", lambda *args, **kwargs: [])
    assert wb.main(["show", "Frame::Retry"]) == 0
    assert [packet["id"] for packet in json.loads(capsys.readouterr().out)["candidates"]] == ["Frame::Retry"]


def test_land_verifies_before_append_and_preserves_game(target, monkeypatch):
    before = target.ledger_path.read_bytes()
    calls = []

    def verify(actual, rows, selectors):
        assert target.ledger_path.read_bytes() == before
        calls.append((actual, rows, selectors))
        return {"rows": rows}

    monkeypatch.setattr(target_verify, "verify", verify)
    wb.land(target, row())
    assert len(target_verify.read_rows(target)) == 1
    assert calls[0][2] == [row()["source"]]
    assert b"\r" not in target.ledger_path.read_bytes()
    assert (target.root / "reverse/functions.csv").read_bytes() == b"GAME LEDGER MUST NOT CHANGE\r\n"


def test_failed_verify_leaves_ledger_unchanged(target, monkeypatch):
    before = target.ledger_path.read_bytes()

    def fail(*args, **kwargs):
        raise ValueError("byte mismatch")

    monkeypatch.setattr(target_verify, "verify", fail)
    with pytest.raises(ValueError, match="byte mismatch"):
        wb.land(target, row())
    assert target.ledger_path.read_bytes() == before


def test_duplicate_land_fails_before_compiler(target, monkeypatch):
    target.ledger_path.write_bytes(wb.serialize([row()]))
    before = target.ledger_path.read_bytes()
    monkeypatch.setattr(target_verify, "verify", lambda *args, **kwargs: pytest.fail("must not compile"))
    with pytest.raises(ValueError, match="duplicate"):
        wb.land(target, row())
    assert target.ledger_path.read_bytes() == before


def test_source_edit_during_verify_aborts_land(target, monkeypatch):
    before = target.ledger_path.read_bytes()

    def edit(*args, **kwargs):
        (target.root / row()["source"]).write_text("void Body() { changed(); }\n")
        return {}

    monkeypatch.setattr(target_verify, "verify", edit)
    with pytest.raises(ValueError, match="source changed"):
        wb.land(target, row())
    assert target.ledger_path.read_bytes() == before


def test_external_ledger_edit_is_not_overwritten(target, monkeypatch):
    changed = wb.serialize([row(model="another-worker")])

    def edit(*args, **kwargs):
        target.ledger_path.write_bytes(changed)
        return {}

    monkeypatch.setattr(target_verify, "verify", edit)
    with pytest.raises(ValueError, match="ledger changed outside its lock"):
        wb.land(target, row())
    assert target.ledger_path.read_bytes() == changed


def test_changed_binary_cannot_land(target, monkeypatch):
    target.image_path.write_bytes(b"other binary")
    before = target.ledger_path.read_bytes()
    monkeypatch.setattr(target_verify, "verify", lambda *args, **kwargs: pytest.fail("must not compile"))
    with pytest.raises(ValueError, match="SHA-256 mismatch"):
        wb.land(target, row())
    assert target.ledger_path.read_bytes() == before


@pytest.mark.parametrize("source", ["../other.cpp", "/tmp/other.cpp", "Code/../../other.cpp"])
def test_land_rejects_path_traversal(target, source):
    with pytest.raises(ValueError, match="repository-relative"):
        wb.land(target, row(source=source))


def test_game_ledger_schema_cannot_be_used(target):
    target.ledger_path.write_text("name,export_rva,target_rva,target_size,source,status,notes\n")
    with pytest.raises(ValueError, match="expected header"):
        target_verify.read_rows(target)


@pytest.mark.parametrize("key,value", [("BFME_TARGET", "game"), ("BFME_TARGET_SHA256", "0" * 64)])
def test_cli_rejects_wrong_fleet_target_before_writing(target, monkeypatch, capsys, key, value):
    before = target.ledger_path.read_bytes()
    monkeypatch.setattr(wb, "load_target", lambda name: target)
    monkeypatch.setenv(key, value)
    assert wb.main(["check"]) == 1
    assert key in capsys.readouterr().err
    assert target.ledger_path.read_bytes() == before


def test_queue_rejects_wrong_image_and_altered_packet(target):
    candidate(target)
    path = target.ledger_root / "candidates.json"
    data = json.loads(path.read_text())
    data["binary_sha256"] = "0" * 64
    path.write_text(json.dumps(data))
    with pytest.raises(ValueError, match="target hash mismatch"):
        wb.load_candidates(target)
    data["binary_sha256"] = target.expected_sha256
    data["candidates"][0]["source"] = "Code/Tools/WorldBuilder/src/Wrong.cpp"
    path.write_text(json.dumps(data))
    with pytest.raises(ValueError, match="packet hash"):
        wb.load_candidates(target)


def test_queue_rejects_candidate_missing_identity(target):
    candidate(target)
    path = target.ledger_root / "candidates.json"
    data = json.loads(path.read_text())
    del data["candidates"][0]["id"]
    path.write_text(json.dumps(data))
    with pytest.raises(ValueError, match="missing its identity"):
        wb.load_candidates(target)


def test_candidate_selectors_support_hex_and_identity(target):
    item = candidate(target)
    for selector in ("0x1000", "4096", "Editor::Body", item["source"], item["name"]):
        assert wb.select([item], [selector]) == [item]
    with pytest.raises(ValueError, match="no WorldBuilder row"):
        wb.select([item], ["missing"])


def test_open_queue_removes_landed_candidates(target):
    candidate(target)
    target.ledger_path.write_bytes(wb.serialize([row()]))
    assert wb.open_candidates(target) == []


def test_partial_banks_hashed_body_and_rejects_modified_bank(target):
    candidate(target)
    args = SimpleNamespace(selector="Editor::Body", status="partial", model="test-model",
                           evidence="complete RET extent; one-byte difference", blocker="codegen",
                           stash=row()["source"], score=0.9)
    item = wb.record(target, args)
    bank = target.root / item["stash"]
    assert bank.read_bytes() == (target.root / args.stash).read_bytes()
    assert wb.read_attempts(target) == [item]
    bank.write_bytes(b"altered")
    with pytest.raises(ValueError, match="attempt hash mismatch"):
        wb.read_attempts(target)


def test_partial_then_land_retains_history_but_retires_open_work(target, monkeypatch):
    candidate(target)
    args = SimpleNamespace(selector="Editor::Body", status="partial", model="test-model",
                           evidence="complete RET extent; one-byte difference", blocker="codegen",
                           stash=row()["source"], score=0.9)
    attempt = wb.record(target, args)
    monkeypatch.setattr(target_verify, "verify", lambda *args, **kwargs: {"rows": [row()]})
    wb.land(target, row())
    assert wb.read_attempts(target) == [attempt]
    assert (target.root / attempt["stash"]).is_file()
    assert wb.open_candidates(target) == []
    before = (target.ledger_root / "attempts.jsonl").read_bytes()
    with pytest.raises(ValueError, match="already landed"):
        wb.record(target, args)
    assert (target.ledger_root / "attempts.jsonl").read_bytes() == before


def test_check_rejects_corrupted_historical_bank(target, monkeypatch, capsys):
    candidate(target)
    args = SimpleNamespace(selector="Editor::Body", status="partial", model="test-model",
                           evidence="complete RET extent", blocker="codegen",
                           stash=row()["source"], score=0.9)
    attempt = wb.record(target, args)
    target.ledger_path.write_bytes(wb.serialize([row()]))
    (target.root / attempt["stash"]).write_bytes(b"changed bank")
    monkeypatch.setattr(wb, "load_target", lambda name: target)
    monkeypatch.setattr(wb.worldbuilder_donors, "lookup", lambda *args, **kwargs: [])
    assert wb.main(["check"]) == 1
    assert "banked attempt hash mismatch" in capsys.readouterr().err


def test_check_validates_queue_and_donor_index(target, monkeypatch, capsys):
    candidate(target)
    target.ledger_path.write_bytes(wb.serialize([row()]))
    monkeypatch.setattr(wb, "load_target", lambda name: target)
    calls = []
    monkeypatch.setattr(wb.worldbuilder_donors, "lookup", lambda selected: calls.append(selected) or [])
    assert wb.main(["check"]) == 0
    output = json.loads(capsys.readouterr().out)
    assert output == dict(valid_rows=1, valid_candidates=1, valid_attempts=0, valid_donor_suggestions=0)
    assert calls == [target]
    path = target.ledger_root / "candidates.json"
    broken = json.loads(path.read_text())
    broken["binary_sha256"] = "0" * 64
    path.write_text(json.dumps(broken))
    assert wb.main(["check"]) == 1
    assert "target hash mismatch" in capsys.readouterr().err


def test_show_attaches_offline_donors_without_changing_candidate_hash(target, monkeypatch, capsys):
    item = candidate(target)
    monkeypatch.setattr(wb, "load_target", lambda name: target)
    donor = dict(reference="bfme2", revision="b" * 40, source="Code/GameEngine/Math.cpp")
    calls = []

    def lookup(selected, symbol, exact):
        calls.append((selected, symbol, exact))
        return [donor]

    monkeypatch.setattr(wb.worldbuilder_donors, "lookup", lookup)
    assert wb.main(["show", item["name"]]) == 0
    output = json.loads(capsys.readouterr().out)["candidates"][0]
    assert output["donor_suggestions"] == [donor]
    assert output["packet_sha256"] == item["packet_sha256"]
    assert wb.load_candidates(target) == [item]
    assert calls == [(target, item["name"], True)]


@pytest.mark.parametrize("landed", [False, True])
def test_show_banked_rva_includes_verified_history_even_after_landing(target, monkeypatch, capsys, landed):
    item = candidate(target)
    attempt = wb.record(target, SimpleNamespace(selector="Editor::Body", status="partial", model="test-model",
        evidence="complete RET extent; one-byte difference", blocker="codegen", stash=row()["source"], score=0.9))
    if landed:
        target.ledger_path.write_bytes(wb.serialize([row()]))
    monkeypatch.setattr(wb, "load_target", lambda name: target)
    monkeypatch.setattr(wb.worldbuilder_donors, "lookup", lambda *args, **kwargs: [])
    assert wb.main(["show", "0x1000"]) == 0
    packet = json.loads(capsys.readouterr().out)["candidates"][0]
    assert packet["previous_attempts"] == [attempt]
    assert packet["packet_sha256"] == item["packet_sha256"]
    bank = target.root / packet["previous_attempts"][0]["stash"]
    assert hashlib.sha256(bank.read_bytes()).hexdigest() == attempt["stash_sha256"]
    bank.write_bytes(b"corrupted historical body")
    assert wb.main(["show", "0x1000"]) == 1
    assert "banked attempt hash mismatch" in capsys.readouterr().err


@pytest.mark.parametrize("changes", [dict(model=""), dict(evidence=" "), dict(score=1), dict(packet_sha256="bad")])
def test_attempt_integrity_rejects_invalid_metadata(target, changes):
    candidate(target)
    args = SimpleNamespace(selector="Editor::Body", status="partial", model="test-model",
                           evidence="complete RET extent", blocker="codegen",
                           stash=row()["source"], score=0.9)
    attempt = wb.record(target, args)
    attempt.update(changes)
    (target.ledger_root / "attempts.jsonl").write_text(json.dumps(attempt) + "\n")
    with pytest.raises(ValueError):
        wb.read_attempts(target)


def test_partial_without_source_cannot_claim_useful_attempt(target):
    candidate(target)
    args = SimpleNamespace(selector="Editor::Body", status="partial", model="test-model",
                           evidence="complete extent", blocker="codegen", stash=None, score=0.9)
    with pytest.raises(ValueError, match="both --stash and --score"):
        wb.record(target, args)
    assert not (target.ledger_root / "attempts.jsonl").exists()


def test_progress_separates_editor_and_engine_bytes(target):
    result = wb.progress(target, [row(), row(name="other", source="Code/GameEngine/Math.cpp",
                                          target_size="47")])
    assert result["editor"] == {"functions": 1, "bytes": 1}
    assert result["engine"] == {"functions": 1, "bytes": 47}
    assert result["verified_bytes"] == 48


def test_divergent_engine_source_is_not_labelled_shared(target):
    result = wb.progress(target, [row(source="worldbuilder/Code/GameEngine/Math.cpp")])
    assert result["engine"] == {"functions": 1, "bytes": 1}
    assert "shared_engine" not in result
