"""The masked pointer site that hides the only difference between two bodies.

`dir32_sites` exempts `??_C@` symbols from the base-agreement rule because a
pooled literal legitimately sits at a different address in every TU. That leaves
a string reference proved by nothing: a body that loads "SaveCameraInReplays"
byte-compares equal, masked, to the body two doors down that loads
"UseSystemMapDir" and is otherwise identical. `build.py:verify_string_refs` is
the stage that catches it, and it runs after the byte comparison — ten such rows
went through `Functions: OK 1227/1227` and then failed the wave at the next
stage, naming no source `land_wave` could route around, so the whole 181-row
transaction reverted. `string_refs_agree` asks the same question at candidate
time, where the answer costs one dropped candidate.
"""
import struct
import sys
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import obj_sweep

STRING_SYMBOL = "??_C@_0BE@KMNOPQRS@SaveCameraInReplays@"
OBJ = Path("build/match/does-not-need-to-exist.obj")
ALIAS = 0x00500000
SITE = 4                     # the pointer occupies bytes 4..7 of the body
POINTER = 0x0089A100         # the address retail's dword at that site holds
AT = 0x300                   # where that address lands in the image


class Retail:
    """Just enough of obj_sweep.Image for this check: the site, and the image."""

    def __init__(self, at_pointer):
        self.data = bytes(AT) + at_pointer
        self.sections = ()

    def body(self, rva, size):
        assert (rva, size) == (ALIAS + SITE, 4), "the only read this check makes"
        return struct.pack("<I", POINTER)


def agree(literal, at_pointer, addend=0, symbol=STRING_SYMBOL, reachable=True):
    body = bytearray(24)
    body[SITE:SITE + 4] = struct.pack("<i", addend)
    locate_pointer = (lambda *_: AT) if reachable else \
        mock.Mock(side_effect=ValueError("RVA is outside all PE sections"))
    with mock.patch.object(obj_sweep.B, "read_object_symbol_bytes",
                           return_value=(literal, [])), \
         mock.patch.object(obj_sweep.B, "rva_to_file_offset", locate_pointer):
        return obj_sweep.string_refs_agree(
            OBJ, bytes(body), [(SITE, obj_sweep.DIR32, symbol)],
            Retail(at_pointer), ALIAS, len(body))


class StringRefs(unittest.TestCase):
    def test_the_literal_the_alias_points_at_is_the_one_compiled(self):
        self.assertTrue(agree(b"SaveCameraInReplays\0", b"SaveCameraInReplays\0"))

    def test_a_different_string_at_the_same_shape_is_refused(self):
        """The exact wave failure: same code, other preference key."""
        self.assertFalse(agree(b"SaveCameraInReplays\0", b"UseSystemMapDir\0\0\0\0"))

    def test_a_prefix_of_the_right_length_is_not_the_right_string(self):
        self.assertFalse(agree(b"MaxPing\0", b"MaxFPS\0\0"))

    def test_a_pooled_literal_is_referenced_at_its_own_addend(self):
        """"DBGHELP.DLL"+4 is "ELP.DLL", and the binary holds that tail there."""
        self.assertTrue(agree(b"DBGHELP.DLL\0", b"ELP.DLL\0", addend=4))

    def test_an_empty_literal_must_point_at_an_empty_string(self):
        self.assertTrue(agree(b"\0", b"\0"))
        self.assertFalse(agree(b"\0", b"x"))

    def test_a_pointer_outside_every_section_is_refused_not_raised(self):
        self.assertFalse(agree(b"SaveCameraInReplays\0", b"", reachable=False))

    def test_a_pointer_site_that_is_not_a_string_is_not_this_checks_business(self):
        """dir32_sites proves those against the bases the ledger already holds."""
        self.assertTrue(agree(b"anything", b"nothing like it", symbol="?theGlobal@@3HA"))


if __name__ == "__main__":
    unittest.main()
