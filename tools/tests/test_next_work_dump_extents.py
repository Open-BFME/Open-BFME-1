"""A compiled drift size must not truncate a current byte-true dump."""
import csv
from pathlib import Path
import sys
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import next_work


def ledger(tmp_path, monkeypatch, rows):
    (tmp_path / "reverse").mkdir()
    with (tmp_path / "reverse/functions.csv").open("w", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=[
            "target_rva", "target_size", "source", "status", "notes"])
        writer.writeheader()
        for changes in rows:
            row = dict(target_rva="0x00001400", target_size=534,
                       source="Code/gen_asm/d_00001400.asm", status="matched",
                       notes="gen-dump;bounds=high")
            row.update(changes)
            writer.writerow(row)
    monkeypatch.setattr(next_work, "ROOT", tmp_path)


def candidate():
    return dict(function="?f@C@@QAEXH@Z", candidate_rva="0x00001400",
                size=494, source="Code/fixture.cpp", aligned_pct=55, hint="old drift")


def test_missing_inventory_uses_current_dump_without_reweighting(tmp_path, monkeypatch):
    ledger(tmp_path, monkeypatch, [{}])
    monkeypatch.setattr(next_work, "_ghidra_sizes", lambda: {})
    body = b"\x90" * 531 + b"\xc2\x04\x00"
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: body[:size])
    original = candidate()
    items, meta = next_work.collapse_and_validate([original])
    assert meta["served"] == 1
    item = items[0]
    assert item["size"] == 494 and item["extent"] == 534
    assert "--size 534 " in item["command"]
    assert next_work.candidate_weight(item) == next_work.candidate_weight(original)
    assert any("dump confirms 534B" in w for w in item["warnings"])


@pytest.mark.parametrize("changes", [
    {"status": "pending"}, {"notes": "gen-dump;bounds=medium"},
    {"notes": "gen-alias;bounds=high"}, {"source": "Code/real.cpp"},
    {"source": "Code/gen_small/uw.cpp"}, {"target_rva": "0x00001500"},
])
def test_only_requested_matched_high_confidence_dumps(tmp_path, monkeypatch, changes):
    ledger(tmp_path, monkeypatch, [changes])
    assert next_work.proven_dump_extents({0x1400}) == {}


def test_conflicting_dump_extents_fail_explicitly(tmp_path, monkeypatch):
    ledger(tmp_path, monkeypatch, [{}, {"target_size": 535}])
    with pytest.raises(SystemExit, match="conflicting/invalid dump extent"):
        next_work.proven_dump_extents({0x1400})


def test_inventory_disagreement_is_not_silently_overwritten(tmp_path, monkeypatch):
    ledger(tmp_path, monkeypatch, [{}])
    monkeypatch.setattr(next_work, "_ghidra_sizes", lambda: {0x1400: 540})
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\x90" * size)
    items, _ = next_work.collapse_and_validate([candidate()])
    assert items[0]["extent"] == 540
    assert any("inventory 540B vs current dump 534B" in w for w in items[0]["warnings"])


@pytest.mark.parametrize("sizes,fill,reason", [
    ({0x13f0: 600}, b"\x90", "interior-of-function"),
    ({}, b"\xcc", "in-int3-padding"),
])
def test_dump_does_not_override_positive_start_refutation(
        tmp_path, monkeypatch, sizes, fill, reason):
    ledger(tmp_path, monkeypatch, [{}])
    monkeypatch.setattr(next_work, "_ghidra_sizes", lambda: sizes)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: fill * size)
    items, meta = next_work.collapse_and_validate([candidate()])
    assert not items
    assert meta["reasons"] == {"C1 " + reason: 1}


@pytest.mark.parametrize("ranked", [False, True])
def test_both_human_views_show_sizes_and_warnings(capsys, ranked):
    item = dict(candidate(), extent=534, warnings=["dump extent evidence"],
                command="verify", functions=[candidate()["function"]])
    if ranked:
        next_work.print_ranked(SimpleNamespace(tier="structural", limit=1),
                               "ok", [], [item], "", [])
    else:
        next_work.print_candidate("structural reconciliation", item, {"pool": 1})
    output = capsys.readouterr().out
    assert "494B source / 534B retail" in output
    assert "warning: dump extent evidence" in output


def test_unknown_extent_is_labeled_unknown():
    assert "retail size unknown" in next_work.structural_size_label(candidate())


@pytest.mark.parametrize("label", ["Unwind@00401400", "Catch@00401400"])
def test_exception_funclet_inventory_label_rejects_structural_alias(label):
    body = b"\x55\x8b\xec\xc3"
    validator = next_work.boundary_validator.BoundaryValidator(
        lambda rva, size: body[:size], {0x1400: len(body)})
    validator.inventory_names = {0x1400: label}

    items, meta = next_work.collapse_and_validate([candidate()], validator)

    assert items == []
    assert meta["refuted"] == 1
    assert meta["reasons"] == {"C4 exception-funclet": 1}
