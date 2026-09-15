"""Target lookup delegates thunk and table bounds to the existing image reader."""
from pathlib import Path
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import vtable_lookup


class Image:
    def __init__(self, tables):
        self.tables = tables
        self.starts = sorted(tables)

    def slots(self, va, cap):
        return self.tables[va][:cap]


def test_returns_head_and_interior_slot_not_an_invented_head():
    image = Image({0x10B5C70: [0x1000] * 15 + [0x260180]})
    assert vtable_lookup.target_tables(image, 0x260180) == [(0x10B5C70, 15)]


def test_preserves_distinct_tables_and_repeated_slots():
    image = Image({0x1000010: [0x2000, 0x2000], 0x1000000: [0x2000]})
    assert vtable_lookup.target_tables(image, 0x2000) == [
        (0x1000000, 0), (0x1000010, 0), (0x1000010, 1)]


def test_respects_existing_table_boundaries_and_user_cap():
    image = Image({0x1000000: [0x1000], 0x1000004: [0x2000, 0x3000]})
    assert vtable_lookup.target_tables(image, 0x2000) == [(0x1000004, 0)]
    assert vtable_lookup.target_tables(image, 0x3000, 1) == []


def test_unknown_target_is_not_assigned_an_owner():
    assert vtable_lookup.target_tables(Image({0x1000000: [0x1000]}), 0x2000) == []


def test_real_image_follows_thunk_and_does_not_cross_adjacent_table():
    from ctor_vtable import Image as RetailImage
    data = bytearray(0x200)
    sections = [dict(name='.text', rva=0x1000, size=0x100, raw_pointer=0),
                dict(name='.rdata', rva=0x2000, size=0x100, raw_pointer=0x100)]
    # Two installed one-slot tables, directly adjacent without a separator.
    data[0:6] = b'\xc7\x06' + struct.pack('<I', 0x402000)
    data[8:14] = b'\xc7\x06' + struct.pack('<I', 0x402004)
    data[0x40:0x45] = b'\xe9' + struct.pack('<i', 0x1080 - 0x1045)
    data[0x80] = data[0x90] = 0xc3
    struct.pack_into('<II', data, 0x100, 0x401040, 0x401090)
    image = RetailImage(data=bytes(data), sections=sections)
    assert vtable_lookup.target_tables(image, 0x1080) == [(0x402000, 0)]
    assert vtable_lookup.target_tables(image, 0x1090) == [(0x402004, 0)]
