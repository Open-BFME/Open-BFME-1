"""Retail import identities can replace aliases without a naming vote."""
import sys
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census
import name_lane


def test_import_identifiers_use_exact_export_or_stdcall_spelling(monkeypatch):
    monkeypatch.setattr(link_census, "_retail_import_entries", lambda: [
        ("mss32.dll", "_AIL_3D_sample_status@4", 0xF5958C),
        ("kernel32.dll", "EnterCriticalSection", 0xF58D18),
        ("msvcr71.dll", "_vsnprintf", 0xF59360),
        ("example.dll", "?Method@Class@@QAEXXZ", 1),
    ])
    assert name_lane.retail_import_names() == {
        "AIL_3D_sample_status", "EnterCriticalSection", "_vsnprintf",
    }


def test_real_retail_table_witnesses_miles_api():
    names = name_lane.retail_import_names()
    assert "AIL_3D_sample_status" in names
    assert "AIL_3D_sample_statusInvented" not in names


def test_staged_guard_allows_only_witnessed_import_rename(monkeypatch, tmp_path, capsys):
    source = "game/ImportFixture.cpp"
    old = 'extern "C" int bfmeStatusDXD(void *); int test(void *p) { return bfmeStatusDXD(p); }'
    renamed = {"name": "AIL_3D_sample_status"}
    ea = tmp_path / "ea.csv"
    ea.write_text("kind,value\n")
    monkeypatch.setattr(name_lane, "EA", ea)
    monkeypatch.setattr(name_lane, "agreed_state", lambda: {})
    monkeypatch.setattr(link_census, "_retail_import_entries", lambda: [
        ("mss32.dll", "_AIL_3D_sample_status@4", 0xF5958C),
    ])

    def git(*args, **kwargs):
        if args[0] == "diff":
            return source + "\n"
        if args == ("show", "HEAD:" + source):
            return old
        if args == ("show", ":" + source):
            return old.replace("bfmeStatusDXD", renamed["name"])
        # A proposed decorated pin does not establish its undecorated API.
        return "name,va\n__imp__AIL_3D_sample_statusInvented@4,0x0135958C\n"

    monkeypatch.setattr(name_lane, "git", git)
    monkeypatch.setattr(name_lane.subprocess, "run", lambda *a, **k: SimpleNamespace(returncode=1))
    assert name_lane.cmd_check(SimpleNamespace(staged=True)) == 0
    renamed["name"] = "AIL_3D_sample_statusInvented"
    assert name_lane.cmd_check(SimpleNamespace(staged=True)) == 1
    assert "bfmeStatusDXD -> AIL_3D_sample_statusInvented" in capsys.readouterr().err
