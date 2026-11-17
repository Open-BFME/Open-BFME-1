"""Only complete CodeView definitions can vote on a class layout."""
import collections
import copy
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract


def complete(size=8):
    return {
        "fwd": False, "key": "class", "size": size,
        "bases": [], "fields": [[0, "value", "float", 4]],
        "statics": [], "methods": [], "virtual": [], "vslots": {}, "vfptr": False,
    }


@pytest.fixture
def evidence(monkeypatch):
    monkeypatch.setattr(contract.class_layouts, "build_module", lambda: object())
    monkeypatch.setattr(contract, "ledger_rows", lambda: [])
    monkeypatch.setattr(contract, "zh_layout", lambda *args: None)
    monkeypatch.setattr(contract, "retail_access", lambda *args: {})
    monkeypatch.setattr(contract, "witnesses", lambda *args: {})
    monkeypatch.setattr(contract, "retail_vtable", lambda *args: {})
    monkeypatch.setattr(contract, "ledger_key", lambda *args: collections.Counter())

    def decide(layouts):
        got = {f"game/view{i}.cpp": copy.deepcopy(layout) for i, layout in enumerate(layouts)}
        every = {source: {"Example": layout} for source, layout in got.items()}
        monkeypatch.setattr(contract, "views", lambda *args: (got, every))
        monkeypatch.setattr(contract, "census", lambda *args: list(got))
        return contract.decide("Example", sources=list(got))

    return decide


def test_complete_view_is_unchanged(evidence):
    result = evidence([complete()])
    assert result["size"] == 8 and result["size_by"] == "majority"
    assert result["key"] == "class" and result["bases"] == []
    assert result["fields"][0]["name"] == "value"
    assert result["fields"][0]["offset"] == 0
    assert result["fields"][0]["size"] == 4
    assert result["evidence"]["views"] == 1
    assert result["evidence"]["view_errors"] == 0
    assert result["queue"] == []


@pytest.mark.parametrize("forward", [
    {"fwd": True},
    {"fwd": True, "size": 4096, "key": "struct", "fields": [[1024, "bogus", "int", 4]],
     "bases": [["BogusBase", 0]], "vslots": {"9": "bogus()"}},
])
def test_forward_reference_cannot_change_complete_layout(evidence, forward):
    expected = evidence([complete()])
    result = evidence([complete(), forward])
    assert {k: v for k, v in result.items() if k != "evidence"} == {
        k: v for k, v in expected.items() if k != "evidence"
    }
    assert result["evidence"]["views"] == 1
    assert result["evidence"]["view_errors"] == 1
    assert result["evidence"]["census"] == 2
    assert result["evidence"]["view_sizes"] == {8: 1}


def test_only_forward_references_remain_unresolved(evidence, capsys):
    result = evidence([{"fwd": True}, {"fwd": True}])
    assert result["evidence"]["views"] == 0
    assert result["evidence"]["view_errors"] == 2
    assert result["evidence"]["view_sizes"] == {}
    assert result["sources"] == [] and result["fields"] == []
    assert result["size_by"] == "tie"
    assert any(item["attribute"] == "size" for item in result["queue"])
    assert contract.main(["--class", "Example"]) == 1
    assert "QUEUE size" in capsys.readouterr().out


def test_forward_references_cannot_resolve_conflicting_complete_sizes(evidence):
    result = evidence([complete(8), complete(16), {"fwd": True}])
    assert result["size_by"] == "tie"
    assert result["evidence"]["view_sizes"] == {8: 1, 16: 1}
    assert any(item["attribute"] == "size" for item in result["queue"])


def test_failed_compile_remains_excluded(evidence):
    result = evidence([complete(), {"error": "compile failed"}])
    assert result["evidence"]["views"] == 1
    assert result["evidence"]["view_errors"] == 1
    assert result["sources"] == ["game/view0.cpp"]
    assert result["queue"] == []
