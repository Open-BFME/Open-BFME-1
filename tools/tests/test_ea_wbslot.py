#!/usr/bin/env python3
"""ea_wbslot: the slot mapping, label reading, table ownership and the CSV merge."""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import ea_wbslot as W  # noqa: E402

ANCHORS = dict(zip((12, 15, 10, 9), (11, 13, 9, 8)))   # WorldBuilder -> game, UpgradeMux


def test_slot_mapping_uses_an_anchor_or_the_slot_just_below_one():
    assert W.map_slot(10, ANCHORS) == 9          # upgradeImplementation
    assert W.map_slot(8, ANCHORS) == 7           # removeUpgrade: below the contiguous run WB 9,10 = game 8,9
    assert W.map_slot(11, ANCHORS) == 10         # anchors 10 and 12 are 2 apart in both builds
    assert W.map_slot(7, ANCHORS) is None        # no anchor at or just above it
    assert W.map_slot(13, ANCHORS) is None


def test_one_below_an_anchor_needs_equal_spacing_on_both_sides():
    # WB 15 = game 13 but WB 12 = game 11: WorldBuilder has an extra virtual between them,
    # so WB 14 (one below 15) cannot be placed.
    assert W.map_slot(14, ANCHORS) is None
    # with no lower anchor, the anchor above must start a run that is contiguous in both builds
    assert W.map_slot(4, {5: 4, 7: 5}) is None
    assert W.map_slot(4, {5: 4, 6: 5}) == 3


class Fake(W.Image):
    def __init__(self, mem, base=0x400000, text=(0x1000, 0x2000), data=((0x2000, 0x3000),)):
        self.base, self.mem, self.text, self.data = base, bytearray(mem), text, list(data)


def test_labels_reads_pushed_class_method_strings_only():
    mem = bytearray(0x3000)
    mem[0x2100:0x2100 + 27] = b"RadarUpgrade::removeUpgrade"
    mem[0x2200:0x2200 + 6] = b"FALSE\0"
    # push 0x402200; push 0x402100; ret
    mem[0x1000:0x100B] = bytes.fromhex("6800224000" "6800214000" "c3")
    assert W.labels(Fake(mem), 0x1000) == {("RadarUpgrade", "removeUpgrade")}


def test_a_class_labelled_in_two_tables_or_a_shared_body_names_nothing(monkeypatch):
    img = Fake(bytearray(0x3000))
    img.sha = "x"
    monkeypatch.setitem(W.WB_IMAGES, "x", ("test", {"UpgradeMux": 0}))
    tables = {0x10: [0xA, 0xB], 0x20: [0xA, 0xC], 0x30: [0xD]}
    monkeypatch.setattr(W, "family_tables", lambda *a: set(tables))
    monkeypatch.setattr(W.Image, "slots", lambda self, t: [v + self.base for v in tables[t]])
    found = {0xA: {("Shared", "f")}, 0xB: {("Radar", "removeUpgrade")}, 0xC: {("Radar", "removeUpgrade")},
             0xD: {("Armor", "removeUpgrade")}}
    monkeypatch.setattr(W, "labels", lambda img, rva: found[rva])
    got = W.wb_labels(img, "UpgradeMux")
    assert got == {"Armor": [("Armor", "removeUpgrade", 0, 0xD)]}   # Radar sits on two tables; Shared is shared


def row(rva, kind, value, route, basis=""):
    return dict(rva=rva, kind=kind, value=value, route=route, basis=basis)


def test_merge_replaces_wbslot_rows_and_keeps_an_agreeing_label_name():
    existing = [row("0x00000010", "file", "A.cpp", "zh"), row("0x00000010", "name", "A::f", "direct", "aligned"),
                row("0x00000020", "name", "B::old", "wbslot", "strong")]
    got = W.merge(existing, [(0x10, "A::f", "ev"), (0x30, "C::g", "ev")])
    assert got == [row("0x00000010", "file", "A.cpp", "zh"), row("0x00000010", "name", "A::f", "direct", "aligned"),
                   row("0x00000030", "name", "C::g", "wbslot", "strong")]


def test_merge_refuses_a_disagreeing_label_name():
    with pytest.raises(SystemExit):
        W.merge([row("0x00000010", "name", "A::g", "chain", "aligned")], [(0x10, "A::f", "ev")])
