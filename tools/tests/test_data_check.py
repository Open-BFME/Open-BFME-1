import struct
import sys
from collections import defaultdict
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import component_link  # noqa: E402
import data_check  # noqa: E402


def fixture(initializer=b"ABCD", retail=b"ABCD", reloc=None, target=None, anchors=None):
    relocs = [] if reloc is None else [(0, 1, component_link.DIR32)]
    section = {"number": 1, "name": ".data", "size": len(initializer), "flags": 0x40,
               "body": initializer, "relocs": relocs}
    symbols = {0: {"index": 0, "name": "_value", "section": 1, "storage": 2, "value": 0}}
    if target is not None:
        symbols[1] = {"index": 1, "name": target, "section": 0, "storage": 2, "value": 0}
    p = SimpleNamespace(
        objs={"one.obj": ([section], symbols)}, base={("one.obj", 1): 0x2000},
        defined={"_value": ("one.obj", 1, 0)}, anchors=defaultdict(set, anchors or {}),
        slots=defaultdict(set), ledger_rows=defaultdict(list), conflicts=[],
        pe=[],
        read=lambda rva, size: retail[:size] if rva == 0x2000 else None,
        masked_diff=component_link.Placement.masked_diff,
    )
    return p


def test_exact_initializer_is_verified():
    good, bad, unknown = data_check.audit(fixture())
    assert len(good) == 1
    assert bad == unknown == []


def test_wrong_initializer_is_a_contradiction():
    good, bad, unknown = data_check.audit(fixture(retail=b"ABCE"))
    assert good == unknown == []
    assert "initializer differs" in bad[0]


def test_relocation_target_is_checked_not_masked():
    ours = struct.pack("<I", 0)
    retail = struct.pack("<I", component_link.BASE + 0x3333)
    good, bad, unknown = data_check.audit(
        fixture(ours, retail, reloc=True, target="_other", anchors={"_other": {0x4444}}))
    assert good == unknown == []
    assert "retail 0x00403333" in bad[0]
    assert "0x00404444" in bad[0]


def test_missing_relocation_target_is_unverified():
    ours = struct.pack("<I", 0)
    retail = struct.pack("<I", component_link.BASE + 0x3333)
    good, bad, unknown = data_check.audit(fixture(ours, retail, reloc=True, target="_missing"))
    assert good == bad == []
    assert "no retail anchor" in unknown[0]


def test_absolute_symbol_uses_va_for_dir32_and_rva_for_dir32nb():
    for kind, encoded in ((component_link.DIR32, component_link.BASE + 0x3333),
                          (component_link.DIR32NB, 0x3333)):
        p = fixture(struct.pack("<I", 0), struct.pack("<I", encoded),
                    reloc=True, target="_absolute")
        p.objs["one.obj"][0][0]["relocs"] = [(0, 1, kind)]
        p.objs["one.obj"][1][1]["section"] = -1
        p.objs["one.obj"][1][1]["value"] = component_link.BASE + 0x3333
        good, bad, unknown = data_check.audit(p)
        assert len(good) == 1
        assert bad == unknown == []


def test_absolute_symbol_rel32_is_relative_to_site():
    encoded = 0x3333 - (0x2000 + 4)
    p = fixture(struct.pack("<I", 0), struct.pack("<I", encoded),
                reloc=True, target="_absolute")
    p.objs["one.obj"][0][0]["relocs"] = [(0, 1, component_link.REL32)]
    p.objs["one.obj"][1][1]["section"] = -1
    p.objs["one.obj"][1][1]["value"] = component_link.BASE + 0x3333
    good, bad, unknown = data_check.audit(p)
    assert len(good) == 1
    assert bad == unknown == []


def test_out_of_bounds_relocation_is_a_contradiction_before_masking():
    p = fixture(b"ABCD", b"ABCD", reloc=True, target="_other", anchors={"_other": {0x4444}})
    p.objs["one.obj"][0][0]["relocs"] = [(3, 1, component_link.DIR32)]
    good, bad, unknown = data_check.audit(p)
    assert good == unknown == []
    assert "malformed relocation" in bad[0]


def test_packed_incremental_link_stub_may_point_at_known_body():
    ours = struct.pack("<I", 0)
    retail = struct.pack("<I", component_link.BASE + 0x1234)
    p = fixture(ours, retail, reloc=True, target="_method", anchors={"_method": {0x5678}})
    p.pe = [{"name": ".text", "rva": 0x1000, "size": 0x5000}]
    around = bytearray(15)
    around[0] = around[5] = 0xE9
    struct.pack_into("<i", around, 6, 0x5678 - (0x1234 + 5))
    p.read = lambda rva, size: retail if (rva, size) == (0x2000, 4) else \
        bytes(around) if (rva, size) == (0x122F, 15) else None
    good, bad, unknown = data_check.audit(p)
    assert len(good) == 1
    assert bad == unknown == []


def test_jump_looking_bytes_in_data_are_not_an_ilt():
    ours = struct.pack("<I", 0)
    retail = struct.pack("<I", component_link.BASE + 0x1234)
    p = fixture(ours, retail, reloc=True, target="_data", anchors={"_data": {0x5678}})
    p.pe = [{"name": ".data", "rva": 0x1000, "size": 0x5000}]
    around = bytearray(15)
    around[0] = around[5] = 0xE9
    struct.pack_into("<i", around, 6, 0x5678 - (0x1234 + 5))
    p.read = lambda rva, size: retail if (rva, size) == (0x2000, 4) else \
        bytes(around) if (rva, size) == (0x122F, 15) else None
    good, bad, unknown = data_check.audit(p)
    assert good == unknown == []
    assert "retail 0x00401234" in bad[0]


def test_lone_tail_jump_in_text_is_not_a_packed_ilt():
    ours = struct.pack("<I", 0)
    retail = struct.pack("<I", component_link.BASE + 0x1234)
    p = fixture(ours, retail, reloc=True, target="_method", anchors={"_method": {0x5678}})
    p.pe = [{"name": ".text", "rva": 0x1000, "size": 0x5000}]
    around = bytearray(15)
    around[5] = 0xE9
    struct.pack_into("<i", around, 6, 0x5678 - (0x1234 + 5))
    p.read = lambda rva, size: retail if (rva, size) == (0x2000, 4) else \
        bytes(around) if (rva, size) == (0x122F, 15) else None
    good, bad, unknown = data_check.audit(p)
    assert good == unknown == []
    assert bad


def test_unplaced_data_is_never_reported_as_verified():
    p = fixture()
    p.base.clear()
    good, bad, unknown = data_check.audit(p)
    assert good == bad == []
    assert "section is unplaced" in unknown[0]
