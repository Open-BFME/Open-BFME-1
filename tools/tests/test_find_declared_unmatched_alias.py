"""A verified object's emitter alias belongs only to its ledger source."""

import csv
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import find_declared_unmatched as claims  # noqa: E402


def _source_claim(tmp_path, monkeypatch, capsys, *, alias=True, same_source=True,
                  status="matched", marker=False):
    source_a = "Code/GameEngine/Source/GameClient/AliasOwner.cpp"
    source_b = "Code/GameEngine/Source/GameClient/OtherOwner.cpp"
    rows = [
        ["?retail@AliasOwner@@QAEXXZ", "", "0x00123400", "12", source_a,
         status, "object-symbol=?emitter@AliasOwner@@QAEXXZ" if alias else ""],
    ]
    if status != "matched":
        # Isolate alias status from the separate zero-matched-source rule.
        rows.append(["?helper@AliasOwner@@QAEXXZ", "", "0x00123410", "12",
                     source_a, "matched", ""])
    if not same_source:
        rows.append(["?other@AliasOwner@@QAEXXZ", "", "0x00123420", "12",
                     source_b, "matched", ""])
    ledger = tmp_path / "reverse/functions.csv"
    ledger.parent.mkdir(parents=True)
    with ledger.open("w", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(["name", "export_rva", "target_rva", "target_size",
                         "source", "status", "notes"])
        writer.writerows(rows)
    inspected = source_a if same_source else source_b
    source = tmp_path / inspected
    source.parent.mkdir(parents=True)
    annotation = "// ?emitter@AliasOwner@@QAEXXZ present-unmatched\n" if marker else ""
    source.write_text(annotation + "void AliasOwner::emitter() {}\n", encoding="utf-8")
    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    subprocess.run(["git", "add", "reverse/functions.csv", inspected],
                   cwd=tmp_path, check=True)
    monkeypatch.setattr(claims, "ROOT", tmp_path)
    monkeypatch.setattr(claims, "FUNCTIONS_CSV", ledger)
    monkeypatch.setattr(claims, "CLAIMS_WHITELIST", tmp_path / "reverse/whitelist.txt")
    monkeypatch.setattr(sys, "argv", ["find_declared_unmatched.py", "--fail",
                                  "--staged", inspected])
    try:
        claims.main()
    except SystemExit as exc:
        return exc.code, capsys.readouterr().out
    return 0, capsys.readouterr().out


def test_staged_emitter_alias_is_declared_in_its_own_source(tmp_path, monkeypatch, capsys):
    code, output = _source_claim(tmp_path, monkeypatch, capsys)
    assert code == 0, output
    assert "All defined functions are already matched." in output


def test_real_ingameui_staged_emitter_alias_is_declared():
    root = Path(__file__).resolve().parents[2]
    source = "Code/GameEngine/Source/GameClient/InGameUISubtitleLabelRva0043E510.cpp"
    result = subprocess.run(
        [sys.executable, str(root / "tools/find_declared_unmatched.py"),
         "--fail", "--staged", source],
        cwd=root, capture_output=True, text=True)
    assert result.returncode == 0, result.stdout + result.stderr


def test_matched_alias_marker_is_stale(tmp_path, monkeypatch, capsys):
    code, output = _source_claim(tmp_path, monkeypatch, capsys, marker=True)
    assert code == 1
    assert "still marked present-unmatched" in output


@pytest.mark.parametrize("change", ["different-source", "missing-alias", "not-matched"])
def test_alias_cannot_excuse_unrelated_definition(tmp_path, monkeypatch, capsys, change):
    code, output = _source_claim(
        tmp_path, monkeypatch, capsys,
        alias=change != "missing-alias", same_source=change != "different-source",
        status="unmatched" if change == "not-matched" else "matched")
    assert code == 1
    assert "AliasOwner::emitter" in output
