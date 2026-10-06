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
    # an unrecorded name must also be owned by the ledger (test_gate_exploits.py);
    # these tests are about agreement, so the data ledger owns the one they use
    monkeypatch.setattr(build, "dir32_identities", lambda recorded: ({}, {"?g_new@@3HA": 0x01300000}))
    monkeypatch.setattr(build, "load_symbol_map", lambda: {})
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


def test_the_full_gate_proposes_new_names_and_never_rewrites_the_record(monkeypatch, tmp_path, capsys):
    """The full gate runs in other agents' commit hooks; a tracked file it rewrote would sit
    uncommitted in their trees."""
    recorded, proposal = tmp_path / "dir32_addresses.csv", tmp_path / "build" / "dir32_addresses.csv"
    recorded.write_text("name,va\n?one@@3HA,0x012B9200\n")
    monkeypatch.setattr(build, "DIR32_ADDRESSES", recorded)
    monkeypatch.setattr(build, "DIR32_PROPOSAL", proposal)
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "retail_va_span", lambda: (0x400000, 0x1416000))
    build.propose_dir32_addresses({"?one@@3HA": {0x012B9200}, "?wl@@3HA": {0x012B9300}}, {"?wl@@3HA"})
    assert not proposal.exists()
    build.propose_dir32_addresses({"?one@@3HA": {0x012B9200}, "?two@@3HA": {0x1000, 0x402000},
                                   "?null@@3HA": {0}, "?new@@3HA": {0x012B9400}}, set())
    assert proposal.read_text() == "name,va\n?new@@3HA,0x012B9400\n?one@@3HA,0x012B9200\n"
    assert recorded.read_text() == "name,va\n?one@@3HA,0x012B9200\n"
    assert "1 symbol(s) not yet recorded, 0 no longer referenced" in capsys.readouterr().out


def test_the_full_gate_fails_a_symbol_every_reference_moved_together(monkeypatch, tmp_path, capsys):
    """A header edit can move all of a symbol's references at once; they agree with each other."""
    whitelist = tmp_path / "whitelist.txt"
    whitelist.write_text("")
    monkeypatch.setattr(build, "DIR32_WHITELIST", whitelist)
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "dir32_references", lambda rows: iter(
        [(ROW, 0x1F3, "?GameSpyColor@@3PAHA", 0x012B9208), (ROW, 0x2A0, "?GameSpyColor@@3PAHA", 0x012B9208)]))
    monkeypatch.setattr(build, "read_dir32_addresses", lambda: {"?GameSpyColor@@3PAHA": 0x012B9200})
    with pytest.raises(SystemExit):
        build.verify_dir32_consistency([ROW])
    assert "(0x012B9200 is the one dir32_addresses.csv records)" in capsys.readouterr().out


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
