"""A Ghidra owned-address count is not a verified contiguous code span."""
import shlex
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import build
import next_work


def candidate(monkeypatch):
    row = {"name": "?affectedByUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z",
           "target_rva": "0x001C5A30", "target_size": "267",
           "source": "game/Caller.cpp",
           "notes": "reloc-derived;call-sites=2;identity=real"}
    monkeypatch.setattr(next_work, "read_csv", lambda *_: ([], [row]))
    rows, _ = next_work.reloc_named_candidates(set(), [])
    return rows[0]


def test_json_distinguishes_inventory_count_from_extent(monkeypatch):
    item = candidate(monkeypatch)
    assert item["size"] == 267  # retain the actual input, not a guessed correction
    assert item["size_basis"] == (
        "inventory-address-count; contiguous extent unverified")


def test_named_display_warns_before_work_starts(monkeypatch, capsys):
    item = candidate(monkeypatch)
    next_work.print_candidate("reloc-named unclaimed function", item, {"pool": 1})
    output = capsys.readouterr().out
    assert "267B inventory count; contiguous extent unverified" in output
    assert "Verify the complete retail boundary" in output


def test_starter_command_is_accepted_by_its_real_parser(monkeypatch):
    item = candidate(monkeypatch)
    args = shlex.split(item["command"])
    assert args[1:] == ["tools/callees.py", "0x001C5A30", "267"]
    # The old decode_calls.py --rva ... --size ... command had no positional
    # source/symbol and an unsupported --size option. Actually run this one.
    result = subprocess.run([sys.executable, *args[1:]], cwd=TOOLS.parent,
                            capture_output=True, text=True)
    assert result.returncode == 0, result.stdout + result.stderr
    assert "call target(s)" in result.stdout


@pytest.mark.parametrize("rva,count,span,tail", [
    (0x000EF340, 96, 99, bytes.fromhex("015bc3")),  # mov al,1 immediate; pop ebx; ret
    (0x001C5A30, 267, 270, bytes.fromhex("c20400")),
    (0x0088A3A0, 132, 135, bytes.fromhex("5e5dc3")),
])
def test_known_inventory_counts_cut_retail_epilogues(rva, count, span, tail):
    body = build.read_target_bytes(rva, span + 2)
    assert body[count:span] == tail
    assert body[span:span + 2] == b"\xcc\xcc"


def test_exporter_still_documents_and_preserves_address_count():
    source = (TOOLS / "ghidra/list_functions.java").read_text()
    assert "f.getBody().getNumAddresses()" in source
    assert "NOT a contiguous byte extent" in source
