#!/usr/bin/env python3
"""Structural tests for the code cave; stdlib + pytest + capstone.

Every assertion here corresponds to a bug that actually shipped into a build
and was only caught by disassembling the result. All three were invisible in
the source and silent at build time:

  * the new section's Characteristics were packed at +0x28 instead of +0x24,
    so the cave came out neither readable nor executable;
  * yasm's `-f bin` aligns its output section, so an `org` at a non-4-aligned
    address emitted three leading pad bytes and the trampoline landed three
    bytes short of the payload's first instruction;
  * the payload's exit ran off the end of its own code and fell through into
    the helper functions emitted after it, because the relocated prologue is
    appended after the WHOLE blob, helpers included.

They are asserted against the real retail image rather than a synthetic PE:
the alignment bug in particular only appears at a cave offset that is not a
multiple of four, which is a property of real allocation, not of a fixture.
"""
import struct
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from cave import CHARACTERISTICS, PE, CaveError  # noqa: E402

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
UPDATE = 0x0035F920  # VictoryConditions::update; prologue is push -1 / push imm32

pytestmark = pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")

capstone = pytest.importorskip("capstone")


@pytest.fixture
def pe():
    p = PE(EXE)
    p.add_cave(0x10000)
    return p


def _disasm(pe, rva, n):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return list(md.disasm(pe.read(rva, n), pe.image_base + rva))


def test_new_section_is_readable_and_executable(pe):
    """Characteristics must land at +0x24. Packed one field late they read 0,
    which is a section the loader will fault on the moment it is entered."""
    sect = [s for s in pe.sections() if s["name"] == ".bfmemod"]
    assert len(sect) == 1, "the cave section should be present exactly once"
    assert sect[0]["chars"] == CHARACTERISTICS
    assert sect[0]["chars"] & 0x20000000, "cave must be executable"
    assert sect[0]["chars"] & 0x40000000, "cave must be readable"


def test_size_of_image_covers_the_cave(pe):
    """A SizeOfImage that stops short of the new section is a load failure."""
    size_of_image = struct.unpack_from("<I", pe.data, pe.opt + 56)[0]
    assert size_of_image >= pe.cave_rva + pe.cave_size


def test_appending_twice_is_refused(pe):
    with pytest.raises(CaveError):
        pe.add_cave(0x1000)


def test_allocation_is_aligned(pe):
    """yasm pads a section whose org is unaligned, which silently moves the
    entry point away from the address the trampoline was built to jump to."""
    pe.alloc(b"\x01" * 3)          # deliberately leaves cave_used at 3
    rva = pe.alloc(b"\x02" * 4)
    assert rva % 16 == 0, "allocations must be aligned, not merely sequential"
    assert pe.next_rva() % 16 == 0


def test_next_rva_predicts_where_alloc_lands(pe):
    """The builder assembles against next_rva() before it has bytes to place;
    if that prediction is wrong the payload is assembled for the wrong address."""
    pe.alloc(b"\x00" * 5)
    predicted = pe.next_rva()
    assert pe.alloc(b"\x90" * 8) == predicted


def test_trampoline_lands_on_the_first_payload_instruction(pe):
    """The end-to-end version of the alignment bug: follow the installed jmp and
    require the very first byte to be the payload, not padding."""
    # Allocate an UNALIGNED amount first. modbuild always places the feature's
    # data before its code, so a detour that resolves its landing address from
    # a raw cave_used rather than next_rva() only diverges once something has
    # been allocated -- detouring an empty cave hides the bug entirely.
    pe.alloc(b"\xAA" * 313)
    assert pe.cave_used % 16 != 0, "the fixture must leave the cursor unaligned"
    payload = bytes([0x60, 0x9C, 0x90, 0x61, 0x9D])   # pushad/pushfd/nop/popad/popfd
    pe.detour(UPDATE, payload=payload)

    assert pe.read(UPDATE, 1) == b"\xE9", "a jmp rel32 must be installed at the target"
    disp = struct.unpack_from("<i", pe.read(UPDATE + 1, 4))[0]
    landing = UPDATE + 5 + disp
    assert pe.read(landing, len(payload)) == payload


def test_exit_reaches_the_relocated_prologue_not_the_bytes_after_the_payload(pe):
    """The payload's own last byte is NOT where control should resume. The
    relocated prologue is appended after the entire blob, so a payload that
    simply ends -- or that has helpers after its exit -- must still arrive there."""
    pe.alloc(b"\xAA" * 313)                      # same unaligned precondition
    stolen, n, _ = pe._steal(UPDATE, 5)
    payload = bytes([0x90])                      # a one-byte payload
    start = pe.detour(UPDATE, payload=payload)

    after = start + len(payload)
    ins = _disasm(pe, after, 16)
    assert [i.mnemonic for i in ins][:2] == ["push", "push"], \
        "the stolen prologue should be replayed immediately after the payload"
    assert ins[0].bytes + ins[1].bytes == stolen[: ins[0].size + ins[1].size]

    tail = ins[2]
    assert tail.mnemonic == "jmp"
    assert int(tail.op_str, 16) - pe.image_base == UPDATE + n, \
        "control must resume just past the bytes the trampoline overwrote"


def test_displaced_bytes_are_fully_replaced_or_padded(pe):
    """Whatever the trampoline does not use of the stolen run must be NOPs, or
    the tail of a half-overwritten instruction executes as garbage."""
    _, n, _ = pe._steal(UPDATE, 5)
    pe.detour(UPDATE)
    assert pe.read(UPDATE + 5, n - 5) == b"\x90" * (n - 5)


def test_relative_call_is_rewritten_when_relocated(pe):
    """A stolen `call rel32` moved into the cave still has to reach its original
    target; leaving the displacement alone silently redirects it."""
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    site = None
    for rva in range(0x00360000, 0x00362000):
        if pe.read(rva, 1) == b"\xE8":
            ins = list(md.disasm(pe.read(rva, 16), pe.image_base + rva))
            if ins and ins[0].mnemonic == "call" and ins[0].size == 5:
                site = rva
                break
    if site is None:
        pytest.skip("no 5-byte rel32 call found in the scanned window")

    original_target = site + 5 + struct.unpack_from("<i", pe.read(site + 1, 4))[0]
    start = pe.detour(site)
    moved = _disasm(pe, start, 16)[0]
    assert moved.mnemonic == "call"
    assert int(moved.op_str, 16) - pe.image_base == original_target


def test_short_branch_in_the_prologue_is_refused_not_mangled(pe):
    """A relative jump too short to survive relocation must fail the build.
    Silently copying it would land somewhere arbitrary inside the cave."""
    scratch = pe.next_rva()
    pe.alloc(bytes([0xEB, 0x02, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90]))
    with pytest.raises(CaveError, match="short relative branch"):
        pe.detour(scratch)


def test_cave_exhaustion_raises(pe):
    with pytest.raises(CaveError, match="cave exhausted"):
        pe.alloc(b"\x00" * (pe.cave_size + 1))


def test_baseline_image_is_untouched_until_saved(pe):
    """add_cave/detour mutate an in-memory copy; the file on disk is the
    byte-exact retail image the whole decomp is verified against."""
    assert PE(EXE).data == bytearray(EXE.read_bytes())
