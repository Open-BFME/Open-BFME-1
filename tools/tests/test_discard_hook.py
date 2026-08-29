#!/usr/bin/env python3
"""Assert the discard hook lands on the instruction it claims, not near it.

`netlat_discard` reads the engine's registers at VA 0x00A620A4 -- eax as the
command's execution frame, esi as the NetCommandRef, edi as the Connection. All
three are true only at that exact address: five bytes earlier eax still holds the
NetCommandMsg, and the detour would report a pointer as a frame number and read
`margin` off the end of the world.

A wrong address here does not fail loudly. It displaces half an instruction, and
the game runs until it doesn't. So the surrounding code is asserted by shape --
the slack read, the add, the compare against TheGameLogic's frame, and the
conditional that skips the delete -- rather than trusting the constant.
"""
import struct
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
pytestmark = pytest.mark.skipif(not EXE.exists(), reason="retail baseline not present")

from modbuild import TARGET_DISCARD  # noqa: E402

# `mov ecx, ds:0x012ED5C8` -- the TheGlobalData load the detour displaces.
DISPLACED = bytes([0x8B, 0x0D, 0xC8, 0xD5, 0x2E, 0x01])


@pytest.fixture(scope="module")
def image():
    return EXE.read_bytes()


def test_hook_sits_on_the_globaldata_load(image):
    """The displaced bytes are a whole 6-byte instruction, so relocation is safe."""
    assert image[TARGET_DISCARD:TARGET_DISCARD + 6] == DISPLACED


def test_the_guard_follows_the_hook(image):
    """slack read, add exec, compare against the logic frame, skip the delete.

    This is the branch 033-retrytime is about. If any of it moves, the feature's
    entire mechanism argument is describing a different binary.
    """
    at = TARGET_DISCARD + 6
    # mov edx, [ecx+0xCB4]   -- NetworkRunAheadSlack, a FRAME COUNT in BFME
    assert image[at:at + 6] == bytes([0x8B, 0x91, 0xB4, 0x0C, 0x00, 0x00])
    # add edx, eax           -- + the command's execution frame
    assert image[at + 6:at + 8] == bytes([0x03, 0xD0])
    # mov eax, ds:0x012F0898 -- TheGameLogic
    assert image[at + 8:at + 13] == bytes([0xA1, 0x98, 0x08, 0x2F, 0x01])
    # cmp edx, [eax+0x3C]    -- vs the current logic frame
    assert image[at + 13:at + 16] == bytes([0x3B, 0x50, 0x3C])
    # jae +0x19              -- keep it; falling through deletes it
    assert image[at + 16:at + 18] == bytes([0x73, 0x19])


def test_the_fallthrough_is_the_delete(image):
    """Falling through the jae reaches removeMessage, not something benign."""
    at = TARGET_DISCARD + 6 + 18
    # mov ecx, [edi+0x18]  -- Connection::m_netCommandList
    assert image[at:at + 3] == bytes([0x8B, 0x4F, 0x18])
    # push esi             -- the NetCommandRef, the same one the hook reports
    assert image[at + 3] == 0x56
    assert image[at + 4] == 0xE8  # call removeMessage


def test_eax_holds_a_frame_not_a_pointer(image):
    """The two loads that put an execution frame in eax, immediately above.

    This is what makes arg0 a frame. Both branches of the command-type test feed
    the same register, and the -1 check below them is why the hook never sees an
    unbound command.
    """
    # mov eax, [eax+0x1C] / jmp / mov eax, [eax+0x08] / cmp eax, -1 / je
    at = TARGET_DISCARD - 13
    assert image[at:at + 3] == bytes([0x8B, 0x40, 0x1C])
    assert image[at + 3:at + 5] == bytes([0xEB, 0x03])
    assert image[at + 5:at + 8] == bytes([0x8B, 0x40, 0x08])
    assert image[at + 8:at + 11] == bytes([0x83, 0xF8, 0xFF])
    assert image[at + 11] == 0x74


def test_slack_default_is_ten_frames(image):
    """GlobalData's defaults, asserted as an ordered run.

    Identity of +0xCB4 rests on consecutive fields matching Zero Hour's
    declaration order, which is what distinguishes RunAheadSlack from
    KeepAliveDelay at +0xCB8. Asserting the run rather than the one value is the
    point: a single 10 proves nothing, the sequence does.

    Note the shape -- +0xCB0 and +0xCB4 are stored from eax after a `mov eax,10`
    rather than as immediates, which is why they are two fields sharing one
    literal and why reading either in isolation is ambiguous.
    """
    at = 0x00085272          # the defaults block, file offset

    def imm_store(off, disp):
        i = at + off
        assert image[i:i + 2] == bytes([0xC7, 0x86]), f"not an imm store at +{off}"
        assert struct.unpack_from("<I", image, i + 2)[0] == disp, f"wrong field at +{off}"
        return struct.unpack_from("<I", image, i + 6)[0]

    def eax_store(off, disp):
        i = at + off
        assert image[i:i + 2] == bytes([0x89, 0x86]), f"not an eax store at +{off}"
        assert struct.unpack_from("<I", image, i + 2)[0] == disp, f"wrong field at +{off}"

    assert imm_store(0, 0xCAC) == 500        # NetworkRunAheadMetricsTime
    assert image[at + 10:at + 15] == bytes([0xB8, 0x0A, 0, 0, 0])   # mov eax,10
    eax_store(15, 0xCB0)                     # NetworkCushionHistoryLength = 10
    eax_store(21, 0xCB4)                     # NetworkRunAheadSlack       = 10
    assert imm_store(27, 0xCB8) == 20        # NetworkKeepAliveDelay
    assert imm_store(37, 0xCBC) == 5000      # NetworkDisconnectTime
    assert imm_store(47, 0xCC0) == 60000     # NetworkPlayerTimeoutTime
    assert imm_store(57, 0xCC4) == 15000     # NetworkDisconnectScreenNotifyTime


def test_slack_is_never_scaled(image):
    """No read of +0xCB4 is followed by a divide.

    Generals/ZH treats NetworkRunAheadSlack as a PERCENTAGE and computes
    `x / 100.0` at both use sites. BFME added an abandonment that adds it
    straight to a frame number. If a future reader ports ZH's semantics here the
    feature's horizon arithmetic silently becomes 100x wrong, so the absence of
    the divide is worth pinning.
    """
    read = bytes([0xB4, 0x0C, 0x00, 0x00])   # the +0xCB4 displacement
    hits = [i for i in range(len(image) - 4) if image[i:i + 4] == read
            and image[i - 2] in (0x8B, 0x89, 0x8D) and image[i - 1] & 0xC0 == 0x80]
    assert len(hits) >= 7, f"expected >=7 references to +0xCB4, found {len(hits)}"
    for i in hits:
        window = image[i + 4:i + 4 + 24]
        assert bytes([0xF7, 0xF9]) not in window, f"idiv near +0xCB4 read at {i:#x}"
        assert bytes([0x99]) + bytes([0xF7]) not in window, f"cdq;idiv at {i:#x}"
