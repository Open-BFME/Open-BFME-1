import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eh_info


def image():
    data = bytearray(0x1000)
    data[0x100:0x107] = b"\x6a\xff\x68" + struct.pack("<I", 0x400200)
    data[0x200:0x20a] = b"\xb8" + struct.pack("<I", 0x400300) + b"\xe9\x00\x00\x00\x00"
    data[0x300:0x30c] = struct.pack("<IiI", eh_info.MAGIC, 3, 0x400400)
    data[0x400:0x418] = struct.pack("<iIiIiI", -1, 0x400500, 0, 0, 1, 0x400600)
    return data


def test_states_and_null_action():
    data = image()
    assert eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100) == (
        0x200, 0x300, [(0, -1, 0x500), (1, 0, None), (2, 1, 0x600)])


def test_registration_load_before_state_push():
    data = image()
    data[0x100:0x10d] = b"\x64\xa1\x00\x00\x00\x00" + data[0x100:0x107]
    assert eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100) == (
        0x200, 0x300, [(0, -1, 0x500), (1, 0, None), (2, 1, 0x600)])


def test_state_push_before_registration_load():
    data = image()
    data[0x100:0x115] = (
        b"\x6a\xff\x64\xa1\x00\x00\x00\x00\x68"
        + struct.pack("<I", 0x400200)
        + b"\x50\x64\x89\x25\x00\x00\x00\x00"
    )
    assert eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100) == (
        0x200, 0x300, [(0, -1, 0x500), (1, 0, None), (2, 1, 0x600)])


def test_alternate_prologue_requires_full_registration_store():
    data = image()
    data[0x100:0x115] = (
        b"\x6a\xff\x64\xa1\x00\x00\x00\x00\x68"
        + struct.pack("<I", 0x400200)
        + b"\x50\x64\x89\x25\x00\x00\x00\x00"
    )
    data[0x10d] = 0x51
    with pytest.raises(ValueError, match="unsupported EH prologue"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


@pytest.mark.parametrize("prefix", [b"\x64\xa1\x04\x00\x00\x00", b"\x90" * 6])
def test_unrecognized_prefix_is_not_scanned(prefix):
    data = image()
    data[0x100:0x10d] = prefix + data[0x100:0x107]
    with pytest.raises(ValueError, match="unsupported EH prologue"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


def test_truncated_prefixed_prologue_rejected():
    data = image()
    data[0x100:0x10d] = b"\x64\xa1\x00\x00\x00\x00" + data[0x100:0x107]
    data = data[:0x10b]
    with pytest.raises(ValueError, match="unsupported EH prologue"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


@pytest.mark.parametrize("offset,value", [(0x100, 0x90), (0x200, 0x90), (0x300, 0), (0x400, 1)])
def test_bad_metadata_rejected(offset, value):
    data = image()
    data[offset] = value
    with pytest.raises(ValueError):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


def test_truncated_map_rejected():
    data = image()[:0x410]
    with pytest.raises(ValueError, match="truncated unwind map"):
        eh_info.unwind_info(lambda r, n: data[r:r+n], 0x100)


def test_cleanup_adjustment_and_ilt_resolution():
    pytest.importorskip("capstone")
    data = image()
    data[0x500:0x50b] = b"\x8b\x4d\xe4\x83\xc1\x08\xe9" + struct.pack("<i", 0x700 - 0x50b)
    data[0x700:0x705] = b"\xe9" + struct.pack("<i", 0x800 - 0x705)
    lines = list(eh_info.action_instructions(lambda r, n: data[r:r+n], 0x500))
    assert len(lines) == 3
    assert "add ecx, 8" in lines[1]
    assert "ILT -> RVA 0x00000800" in lines[2]
