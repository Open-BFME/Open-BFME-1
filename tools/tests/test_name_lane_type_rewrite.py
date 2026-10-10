import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane as n


def test_type_rewrite_keeps_vtable_addresses_and_unrelated_alias_names(monkeypatch, tmp_path):
    ledger = tmp_path / "functions.csv"
    addresses = tmp_path / "dir32_addresses.csv"
    tombstones = tmp_path / "deleted_rows.csv"
    ledger.write_text("name,export_rva,target_rva\n??0OpaqueOwner@@QAE@XZ,,0x00100000\n")
    before = ("name,address\n"
              "??_7OpaqueOwner@@6BBaseA@@@,0x01100000\n"
              "??_7OpaqueOwner@@6BBaseB@@@,0x01100004\n"
              "??_7OpaqueOwnerSuffix@@6BBaseA@@@,0x01100008\n"
              "?OpaqueOwnerVftable@@3PAPBXA,0x01100000\n")
    addresses.write_text(before)
    tombstones.write_text("name,rva,reason\n")
    monkeypatch.setattr(n, "LEDGER", ledger)
    monkeypatch.setattr(n, "TOMBSTONES", tombstones)
    monkeypatch.setattr(n, "STORED", [ledger, addresses])
    n.rewrite_stored([("type", "", "OpaqueOwner", "KnownOwner")], why="fixture identity proof")
    assert "??0KnownOwner@@QAE@XZ" in ledger.read_text()
    assert addresses.read_text() == before.replace("??_7OpaqueOwner@@", "??_7KnownOwner@@")
    assert "??0OpaqueOwner@@QAE@XZ,0x00100000" in tombstones.read_text()


def test_type_and_method_rename_rewrites_the_method_before_its_owner(monkeypatch, tmp_path):
    ledger = tmp_path / "functions.csv"
    tombstones = tmp_path / "deleted_rows.csv"
    ledger.write_text("name,export_rva,target_rva\n?bfmeHasBit@Gen_000D5930@@QBE_NPBVBfmeThingEL@@@Z,,0x000D5930\n")
    tombstones.write_text("name,rva,reason\n")
    monkeypatch.setattr(n, "LEDGER", ledger)
    monkeypatch.setattr(n, "TOMBSTONES", tombstones)
    monkeypatch.setattr(n, "STORED", [ledger])
    n.rewrite_stored([("type", "", "Gen_000D5930", "Player"),
                      ("function", "Gen_000D5930@", "bfmeHasBit", "hasUpgradeComplete")], why="fixture")
    assert "?hasUpgradeComplete@Player@@QBE_NPBVBfmeThingEL@@@Z" in ledger.read_text()
