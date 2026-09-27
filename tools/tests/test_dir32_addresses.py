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


class _Image:
    """resolve() as pin_consistency.Image does: follow a jump stub to its body."""
    def __init__(self, stubs):
        self.stubs = stubs

    def resolve(self, rva):
        return self.stubs.get(rva, rva), [rva]


class _Scanner:
    def __init__(self, stubs):
        self.image = _Image(stubs)


def _pins(monkeypatch, pins, recorded, stubs=None):
    import pin_consistency
    # Patch the build module pin_consistency holds: another suite may have re-imported build.
    monkeypatch.setattr(pin_consistency.build, "read_dir32_addresses", lambda: dict(recorded))
    monkeypatch.setattr(pin_consistency.build, "read_dir32_whitelist", lambda: set())
    monkeypatch.setattr(pin_consistency, "load_pins", lambda: pins)
    pin_consistency.verify_dir32_pins(_Scanner(stubs or {}))


def test_pins_agree_in_rva_or_va_form_or_through_a_stub(monkeypatch, capsys):
    _pins(monkeypatch,
          {"?GameSpyColor@@3PAHA": [0x00EB9200, 0x012B9200],     # RVA and VA forms
           "??1Thing@@QAE@XZ": [0x00887940]},                     # the body its ILT reaches
          {"?GameSpyColor@@3PAHA": 0x012B9200, "??1Thing@@QAE@XZ": 0x0040D828},
          stubs={0x0000D828: 0x00887940})
    assert "DIR32 pins: OK (3 pin(s)" in capsys.readouterr().out


def test_a_pin_on_another_import_slot_fails(monkeypatch, capsys):
    """The GetClientRect pin sat on GetWindowRect's IAT slot to force a wrong call."""
    with pytest.raises(SystemExit):
        _pins(monkeypatch, {"__imp__GetClientRect@8": [0x0135901C]},
              {"__imp__GetClientRect@8": 0x01358FEC})
    assert "pinned 0x0135901C, matched references use 0x01358FEC" in capsys.readouterr().out
