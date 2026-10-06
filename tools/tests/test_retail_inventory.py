"""retail_inventory.py: the committed inventories are exactly what the tool regenerates
(deterministic, tool-owned), and an ICF twin needs equal RESOLVED branch targets, not
just equal bytes with address-like dwords masked."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import retail_inventory as ri  # noqa: E402

pytest.importorskip("capstone")


class FakeImage:
    base = 0x400000

    def __init__(self):
        self.img = bytearray(0x3000)
        self.sec = {".text": (0x1000, 0x1000, 0x1000), ".rdata": (0x2000, 0x100, 0x100)}
        self.text = (self.base + 0x1000, self.base + 0x2000)

    def d(self, va):
        return struct.unpack_from("<I", self.img, va - self.base)[0]

    def istext(self, va):
        return self.text[0] <= va < self.text[1]

    def sec_of(self, va):
        r = va - self.base
        return next((n for n, (v, vs, _) in self.sec.items() if v <= r < v + vs), None)

    def call(self, rva, target_rva):
        self.img[rva] = 0xE8
        struct.pack_into("<i", self.img, rva + 1, target_rva - (rva + 5))
        self.img[rva + 5] = 0xC3


def test_fold_list_needs_resolved_targets(monkeypatch):
    im = FakeImage()
    im.call(0x1000, 0x1100)          # A: call X; ret
    im.call(0x1010, 0x1100)          # B: call X; ret  -> twin of A (rel32 bytes differ, target equal)
    im.call(0x1020, 0x1110)          # C: call Y; ret  -> equal when masked, NOT a twin
    im.img[0x1100:0x1103] = b"\x33\xc0\xc3"
    im.img[0x1110:0x1113] = b"\xb0\x01\xc3"
    funcs = [(0x1000, 6, "A"), (0x1010, 6, "B"), (0x1020, 6, "C"), (0x1100, 3, "X"), (0x1110, 3, "Y")]
    monkeypatch.setattr(ri, "ghidra_functions", lambda: funcs)
    rows = [line.split(",") for line in ri.fold_list(im).splitlines()[1:]]
    assert [(r[0], r[2], r[3], r[4]) for r in rows] == [("0x00001000", "0x00001000", "2", "3"),
                                                         ("0x00001010", "0x00001000", "2", "3")]


def test_fold_list_follows_jump_thunks(monkeypatch):
    im = FakeImage()
    im.call(0x1000, 0x1100)          # A calls X directly
    im.call(0x1010, 0x1200)          # B calls a jmp thunk to X: the same resolved target
    im.img[0x1200] = 0xE9
    struct.pack_into("<i", im.img, 0x1201, 0x1100 - 0x1205)
    im.img[0x1100:0x1103] = b"\x33\xc0\xc3"
    monkeypatch.setattr(ri, "ghidra_functions", lambda: [(0x1000, 6, "A"), (0x1010, 6, "B"), (0x1100, 3, "X")])
    assert [line.split(",")[0] for line in ri.fold_list(im).splitlines()[1:]] == ["0x00001000", "0x00001010"]


needs_image = pytest.mark.skipif(not ri.EXE.exists() or not ri.GHIDRA.exists(), reason="retail image not present")


@needs_image
def test_committed_inventories_are_regenerated_byte_for_byte():
    """Determinism across processes and runs: the files were written by an earlier run."""
    pytest.importorskip("pefile")
    fresh = ri.generate()
    for name, text in fresh.items():
        path = ri.ROOT / ri.INVENTORY_DIR / name
        assert path.exists(), "%s missing: run python3 tools/retail_inventory.py" % path
        assert path.read_text(encoding="utf-8").replace("\r\n", "\n") == text, name


@needs_image
def test_generation_is_deterministic_in_process():
    pytest.importorskip("pefile")
    im = ri.Image()
    assert ri.flag_regions(im) == ri.flag_regions(ri.Image())
