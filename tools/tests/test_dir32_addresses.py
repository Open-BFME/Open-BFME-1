import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402

ROW = {"name": "?PopulateLobbyPlayerListbox@@YAXXZ"}


def _check(monkeypatch, refs, recorded, whitelist=()):
    monkeypatch.setattr(build, "dir32_references", lambda rows: iter(refs))
    monkeypatch.setattr(build, "read_dir32_addresses", lambda: dict(recorded))
    monkeypatch.setattr(build, "read_dir32_whitelist", lambda: set(whitelist))
    monkeypatch.setattr(build, "retail_va_span", lambda: (0x400000, 0x1416000))
    build.verify_dir32_addresses([ROW])


def test_the_recorded_address_passes(monkeypatch, capsys):
    _check(monkeypatch, [(ROW, 0x1F3, "?GameSpyColor@@3PAHA", 0x012B9200)],
           {"?GameSpyColor@@3PAHA": 0x012B9200})
    assert "DIR32 addresses: OK (1 reference(s)" in capsys.readouterr().out


def test_a_wrong_array_slot_fails_with_both_addresses(monkeypatch, capsys):
    """The lobby colour bug: slot 9 where retail reads slot 11 puts the table 8 bytes late."""
    with pytest.raises(SystemExit):
        _check(monkeypatch, [(ROW, 0x1F3, "?GameSpyColor@@3PAHA", 0x012B9208)],
               {"?GameSpyColor@@3PAHA": 0x012B9200})
    out = capsys.readouterr().out
    assert "+0x1f3: ?GameSpyColor@@3PAHA -> 0x012B9208" in out
    assert "records 0x012B9200" in out


def test_unrecorded_symbols_must_agree_within_the_build(monkeypatch, capsys):
    refs = [(ROW, 0x10, "?g_new@@3HA", 0x01300000), (ROW, 0x20, "?g_new@@3HA", 0x01300004)]
    with pytest.raises(SystemExit):
        _check(monkeypatch, refs, {})
    assert "another reference in this build gives 0x01300000" in capsys.readouterr().out
    _check(monkeypatch, refs[:1] * 2, {})


def test_whitelisted_and_out_of_image_bases_are_not_this_checks_business(monkeypatch):
    refs = [(ROW, 0x10, "__imp__memmove", 0x0135945C),   # two IAT slots in retail
            (ROW, 0x20, "??_7PolyRemover@@6B@", 0x0)]    # null_reloc.py's finding
    _check(monkeypatch, refs, {"__imp__memmove": 0x01359000, "??_7PolyRemover@@6B@": 0x0113D01C},
           whitelist={"__imp__memmove"})


def test_the_recorder_keeps_only_single_in_image_addresses(monkeypatch, tmp_path):
    out = tmp_path / "dir32_addresses.csv"
    monkeypatch.setattr(build, "DIR32_ADDRESSES", out)
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "retail_va_span", lambda: (0x400000, 0x1416000))
    build.write_dir32_addresses({"?one@@3HA": {0x012B9200}, "?two@@3HA": {0x1000, 0x2000 + 0x400000},
                                 "?wl@@3HA": {0x012B9300}, "?null@@3HA": {0}}, {"?wl@@3HA"})
    assert out.read_text() == "name,va\n?one@@3HA,0x012B9200\n"
    mtime = out.stat().st_mtime_ns
    build.write_dir32_addresses({"?one@@3HA": {0x012B9200}}, set())
    assert out.stat().st_mtime_ns == mtime
