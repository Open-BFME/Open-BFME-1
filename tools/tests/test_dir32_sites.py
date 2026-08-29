"""The base arithmetic is the whole claim this diagnostic makes."""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import dir32_sites  # noqa: E402


def _at(value):
    return struct.pack("<I", value)


def test_base_removes_the_compiled_addend():
    """final = base + addend, so base = final - addend."""
    target, body = _at(0x012ED5BC + 0x10), _at(0x10)
    assert dir32_sites.base_of(target, body, 0) == 0x012ED5BC


def test_zero_addend_is_the_address_itself():
    assert dir32_sites.base_of(_at(0x012EF0E4), _at(0), 0) == 0x012EF0E4


def test_subtraction_wraps_like_the_gate_does():
    """An addend above the final value must wrap to 32 bits, not go negative."""
    assert dir32_sites.base_of(_at(4), _at(8), 0) == 0xFFFFFFFC
