"""What a Zero Hour work packet is allowed to assert about its own address.

A packet's address and size are not observations, they are the sweep's guess:
the address is wherever a masked needle aligned, and the size is the length of
the Zero Hour body, not of the retail one. Both were printed as fact. A
contributor who trusts them writes a ledger row at an address the function does
not start at, or for an extent it does not have, and the row byte-matches
anyway -- build.py copies DIR32 relocation bytes out of retail rather than
proving them -- so the gate cannot catch what the packet manufactured.

Every path here runs over a synthetic image and a scratch ledger under tmp_path.
The real packet directory is derived and rewritten wholesale, so a test that
pointed at it would delete the live queue.
"""
import csv
import importlib.util
import json
import re
import struct
import sys
import types
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
csv.field_size_limit(10_000_000)

import build  # noqa: E402


def _load(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / "tools" / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


zh_sweep = _load("zh_sweep")

TEXT_RVA = 0x1000
LEDGER_HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
# One 32-byte function the inventory knows, its int3 padding, and a 16-byte one
# after it. Everything else is nop, so nothing but these bounds a body.
KNOWN = {0x2000: 32, 0x3000: 16}
PAD = 0x2020
SOURCE = "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/T.cpp"


def image():
    text = bytearray(b"\x90" * 0x4000)
    text[PAD - TEXT_RVA : PAD - TEXT_RVA + 16] = b"\xcc" * 16
    return bytes(text)


def near(rva, size, sym="?candidate@Thing@@QAEXXZ", align=0.9, relocs=3):
    return {"sym": sym, "obj": "T.obj", "source": SOURCE, "size": size, "relocs": relocs,
            "rva": rva, "bucket": "near", "align": align, "claimed": False}


def run_packets(tmp_path, monkeypatch, records, ledger_rows=(), relocs=(), pins=(),
                patches=()):
    """do_packets over a synthetic image; returns {rva: packet text}.

    `patches` writes retail bytes at an rva, which is how a call site is given a
    displacement to decode; `pins` is the scratch targets/game/reverse/symbols.csv.
    """
    text = bytearray(image())
    for rva, raw in patches:
        text[rva - TEXT_RVA : rva - TEXT_RVA + len(raw)] = raw
    text = bytes(text)
    ledger = tmp_path / "functions.csv"
    ledger.write_text(LEDGER_HEADER + "\r\n" + "".join(r + "\r\n" for r in ledger_rows),
                      encoding="utf-8")
    inventory = tmp_path / "ghidra_functions.csv"
    inventory.write_text("rva,size,name\n"
                         + "".join(f"0x{rva:x},{size},FUN_{rva:08x}\n"
                                   for rva, size in KNOWN.items()), encoding="utf-8")
    symbols = tmp_path / "symbols.csv"
    symbols.write_text("name,address,notes\n" + "".join(p + "\n" for p in pins),
                       encoding="utf-8")
    (tmp_path / "match.json").write_text(json.dumps(list(records)))
    packets = tmp_path / "packets"
    monkeypatch.setattr(zh_sweep, "MATCH_JSON", tmp_path / "match.json")
    monkeypatch.setattr(zh_sweep, "PACKET_DIR", packets)
    monkeypatch.setattr(zh_sweep, "OUT_DIR", tmp_path)
    monkeypatch.setattr(zh_sweep, "ROOT", tmp_path)
    monkeypatch.setattr(zh_sweep, "retail_text", lambda: (TEXT_RVA, text))
    monkeypatch.setattr(zh_sweep, "packet_relocs",
                        lambda objects: {("T.obj", r["sym"]): list(relocs) for r in records})
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    monkeypatch.setattr(build, "SYMBOLS", symbols)
    monkeypatch.setattr(build, "GHIDRA_FUNCTIONS", inventory)
    # The synthetic image carries no incremental-link thunk table. Left alone,
    # load_symbol_map() re-reads the real 4MB exe on every call and folds its
    # thunks into these addresses.
    monkeypatch.setattr(build, "build_call_thunks", lambda: {})
    monkeypatch.setattr(build, "read_target_bytes",
                        lambda rva, size: text[rva - TEXT_RVA : rva - TEXT_RVA + size])

    zh_sweep.do_packets(types.SimpleNamespace())

    return {int(p.stem, 16): p.read_text() for p in packets.glob("*.md")}


def served_size(packet):
    """The size tools/next_work.py parses out of a packet to serve it."""
    return int(re.search(r"- (\d+) bytes", packet).group(1))


def flat(packet):
    """The packet as one line: its prose is wrapped, its claims are not."""
    return " ".join(packet.split())


def test_an_interior_address_is_corrected_to_the_body_it_landed_in(tmp_path, monkeypatch):
    """0x2010 is 16 bytes inside a body the inventory knows. The sweep placed a
    candidate there anyway, which is how 25 of 335 live packets were addressed.
    Printing that as a warning still hands over the wrong address; the inventory
    names the right one, so the packet is addressed there and its extent read
    there too -- 32 bytes of the enclosing body, not 24 of the candidate."""
    written = run_packets(tmp_path, monkeypatch, [near(0x2010, 24)])

    assert list(written) == [0x2000]
    packet = flat(written[0x2000])
    assert "not a function start" not in packet
    assert "address is a confirmed function start (targets/game/reverse/ghidra_functions.csv)" in packet
    assert served_size(written[0x2000]) == 32


def test_an_address_in_padding_is_corrected_forward_to_the_next_body(tmp_path, monkeypatch):
    """The same error pointing the other way: 0x2020 is int3 between the two
    bodies, so the body it names is the one the padding runs up to. Back-snapping
    recovers none of these, which is why the correction reads `containing()`."""
    written = run_packets(tmp_path, monkeypatch, [near(PAD, 24)])

    assert list(written) == [0x3000]
    packet = flat(written[0x3000])
    assert "not a function start" not in packet
    assert "address is a confirmed function start (targets/game/reverse/ghidra_functions.csv)" in packet
    assert served_size(written[0x3000]) == 16


def test_an_address_the_inventory_does_not_cover_is_not_moved(tmp_path, monkeypatch):
    """0x2100 has no row at or covering it and is not padding. That is unknown,
    not wrong: it sits before a known start, so a rule keying off `containing()
    is None` snaps it forward to 0x3000, past its own end -- over the live queue
    that moves every one of the 32 such addresses, two of them onto each other."""
    written = run_packets(tmp_path, monkeypatch, [near(0x2100, 24)])

    assert list(written) == [0x2100]
    assert "treat the start as unverified" in flat(written[0x2100])


def test_a_confirmed_start_says_so_and_says_where_from(tmp_path, monkeypatch):
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 16)])

    packet = flat(written[0x3000])
    assert "address is a confirmed function start (targets/game/reverse/ghidra_functions.csv)" in packet
    assert "not a function start" not in packet


def test_the_packet_quotes_retails_extent_not_the_candidates_length(tmp_path, monkeypatch):
    """The size bug: `size` was the Zero Hour body's length. Retail's body at
    0x3000 is 16 bytes; a 24-byte candidate must not widen the claim to 24."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 24)])

    packet = written[0x3000]
    assert served_size(packet) == 16
    assert "the candidate body is 24 bytes long" in flat(packet)
    assert "Retail disassembly (16 bytes from this address)" in packet


def test_an_unmeasurable_extent_is_labelled_unverified_not_guessed(tmp_path, monkeypatch):
    """No inventory row and no int3 run in range: the candidate's length is all
    there is, so it is served with that said out loud rather than as an extent."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3200, 24)])

    packet = written[0x3200]
    assert served_size(packet) == 24
    assert "an UNVERIFIED size" in flat(packet)
    assert "no inventory row confirms a function starts at this address" in flat(packet)


def test_agreement_is_measured_over_compared_bytes_not_blanked_ones(tmp_path, monkeypatch):
    """match.json's `align` scores a blanked relocation byte as agreeing, so the
    sentence "outside relocation sites" was never the number it printed. Here 8
    of 24 bytes are relocation slots: 0.9 over the whole body is 22 matching, of
    which 8 were never compared, so 14 of 16 -- 87.5%, not 90.0%."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 24, align=0.9)],
                          relocs=[(4, zh_sweep.DIR32, "?g@@3HA"),
                                  (12, zh_sweep.REL32, "?callee@@YAXXZ")])

    packet = flat(written[0x3000])
    assert "agrees on 87.5% of the bytes outside relocation sites: 14 of 16" in packet
    assert "the other 8 byte(s) of its 24-byte body are relocation slots" in packet
    assert "the sweep's own 90.0% counts every blanked byte as agreeing" in packet


def test_tied_candidates_are_not_offered_as_an_identity(tmp_path, monkeypatch):
    """Masking hides which global and which callee a body uses, so equally
    aligned candidates are indistinguishable -- 0x002EFAF0 landed under the
    wrong one of three."""
    written = run_packets(tmp_path, monkeypatch, [
        near(0x3000, 16, sym="?first@Thing@@QAEXXZ"),
        near(0x3000, 16, sym="?second@Thing@@QAEXXZ")])

    assert "2 of the candidates below align equally well" in flat(written[0x3000])


def test_no_packet_for_ground_the_ledger_already_claims(tmp_path, monkeypatch):
    """The claim is re-asked against the live ledger and against the extent the
    packet would quote, not against the snapshot taken when the match ran."""
    claimed = "?owner@Thing@@QAEXXZ,,0x00003000,16,game/Thing.cpp,matched,"
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 16)], ledger_rows=[claimed])

    assert written == {}


CALLEE = "?callee@Thing@@QAEXXZ"
CALLEE_ROW = f"{CALLEE},,0x00002000,32,{SOURCE},matched,"


def calls(target, site=0x3004):
    """A REL32 site at `site` whose retail displacement decodes to `target`."""
    return {"relocs": [(site - 0x3000, zh_sweep.REL32, CALLEE)],
            "patches": [(site, struct.pack("<i", target - (site + 4)))]}


def pins_of(packet):
    return packet.split("## Callee pins")[1].split("```")[1].strip()


def test_a_pin_is_marked_when_the_ledger_holds_the_address_this_site_calls(
        tmp_path, monkeypatch):
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 16)],
                          ledger_rows=[CALLEE_ROW], **calls(0x2000))

    assert pins_of(written[0x3000]) == f"{CALLEE},0x00002000 (already in the ledger)"


def test_a_pin_naming_a_copy_the_ledger_does_not_hold_is_not_marked(tmp_path, monkeypatch):
    """The name is in the ledger and the address is not, which is what a name
    test cannot see: retail folds and duplicates bodies, so this site reaches a
    copy no row covers. Saying "already in the ledger" over it tells a converter
    the callee is landed at an address the ledger has never claimed."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 16)],
                          ledger_rows=[CALLEE_ROW], **calls(0x3800))

    assert pins_of(written[0x3000]) == (f"{CALLEE},0x00003800 (unpinned: this is the address "
                                        "retail calls; the ledger holds this name at "
                                        "0x00002000)")


def test_a_pin_only_symbols_csv_holds_names_symbols_csv_and_not_the_ledger(
        tmp_path, monkeypatch):
    """load_symbol_map() is not a subset of the ledger's names. An address it
    resolves only because symbols.csv pins it is resolvable, but it is not a
    ledger row and there is no source behind it."""
    written = run_packets(tmp_path, monkeypatch, [near(0x3000, 16)],
                          pins=[f"{CALLEE},0x00002400,per-TU copy"], **calls(0x2400))

    assert pins_of(written[0x3000]) == (f"{CALLEE},0x00002400 "
                                        "(already pinned in targets/game/reverse/symbols.csv)")
