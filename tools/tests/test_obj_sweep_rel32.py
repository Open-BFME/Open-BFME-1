"""When a call displacement may be re-encoded at a second address, and when not.

`compile_function` does not COMPARE a REL32 site, it WRITES one: it seeds from
`symbol_map[sym][0]`, stops at the first candidate whose displacement reproduces
retail, and writes whatever it stopped on — the last candidate, unchecked, when
none of them matched. At an alias address it therefore emits retail's own four
bytes exactly when the callee retail's displacement points at is one of that
symbol's candidates. `rel32_callees` runs that arithmetic forwards, so the sweep
never offers a span at an address where the gate would write a different call.

`classify` is the other half: the REL32 branch of `compile_function` raises
SystemExit — killing a whole wave's gate, not one row — when a site runs past the
row's end, so such a span must never reach a wave at all.
"""
import collections
import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import obj_sweep

ALIAS = 0x00C41000          # the dump address the span would be claimed at
CALLEE = "?tick@Clock@@QAEXXZ"
CALLEE_RVA = 0x00401200
THUNK_RVA = 0x00402500      # the incremental-link thunk for the same callee
SITE = 6                    # the displacement occupies bytes 6..9 of the body

# push ebp / mov ebp,esp / xor eax,eax / call <site> / pop ebp / ret
BODY = bytes.fromhex("558bec33c0e8") + b"\0\0\0\0" + bytes.fromhex("5dc3")
RELOCS = [(SITE, obj_sweep.REL32, CALLEE)]


class Retail:
    """Just enough of obj_sweep.Image: retail's own bytes at an rva."""

    def __init__(self, data, base=ALIAS):
        self.data, self.base = data, base

    def body(self, rva, size):
        start = rva - self.base
        assert 0 <= start and start + size <= len(self.data), "read outside the fixture"
        return self.data[start:start + size]


def retail_calling(address):
    """Retail at ALIAS: this body with the displacement the linker wrote there."""
    return Retail(BODY[:SITE] + struct.pack("<i", address - (ALIAS + SITE + 4))
                  + BODY[SITE + 4:])


def callees(symbol_map, image, relocs=RELOCS):
    stats = collections.Counter()
    return obj_sweep.rel32_callees(BODY, relocs, image, ALIAS, symbol_map, stats), stats


class Rel32Callees(unittest.TestCase):
    def test_a_call_reaching_the_address_the_ledger_holds_is_aliasable(self):
        found, _ = callees({CALLEE: {CALLEE_RVA}}, retail_calling(CALLEE_RVA))
        self.assertEqual(found, [(CALLEE, CALLEE_RVA)])

    def test_an_incremental_link_thunk_is_a_candidate_like_any_other(self):
        """symbol_map carries [thunk, body]; the site encodes whichever it used."""
        found, _ = callees({CALLEE: {CALLEE_RVA, THUNK_RVA}}, retail_calling(THUNK_RVA))
        self.assertEqual(found, [(CALLEE, THUNK_RVA)])

    def test_a_callee_the_ledger_cannot_place_is_refused(self):
        found, stats = callees({}, retail_calling(CALLEE_RVA))
        self.assertIsNone(found)
        self.assertEqual(stats["skip_rel32_callee_unplaced"], 1)

    def test_a_call_reaching_somewhere_else_is_refused(self):
        """The one case that would land a wrong body: same symbol, other target."""
        found, stats = callees({CALLEE: {CALLEE_RVA}}, retail_calling(CALLEE_RVA + 0x40))
        self.assertIsNone(found)
        self.assertEqual(stats["skip_rel32_callee_elsewhere"], 1)

    def test_a_dir32_site_is_not_this_functions_business(self):
        """Those four bytes are copied from retail, not re-derived; dir32_sites
        proves them. An empty list here is acceptance, not a missed check."""
        found, _ = callees({}, retail_calling(CALLEE_RVA),
                           relocs=[(2, obj_sweep.DIR32, "?theGlobal@@3HA")])
        self.assertEqual(found, [])


def classify(length, relocs):
    stats = collections.Counter()
    return obj_sweep.classify(bytes(length), relocs, stats), stats


class Classify(unittest.TestCase):
    def test_a_span_with_no_relocation_is_reloc_free(self):
        self.assertEqual(classify(20, [])[0], ("rf", []))

    def test_pointer_sites_alone_are_dir32(self):
        self.assertEqual(classify(20, [(4, obj_sweep.DIR32, "?g@@3HA")])[0], ("dir32", [4]))

    def test_a_call_among_the_pointers_makes_it_rel32(self):
        got, _ = classify(20, [(4, obj_sweep.DIR32, "?g@@3HA"),
                               (10, obj_sweep.REL32, CALLEE)])
        self.assertEqual(got, ("rel32", [4, 10]))

    def test_a_call_running_past_the_span_end_is_never_offered(self):
        """compile_function raises on this, which is the gate dead for the whole
        wave; and it is right to, because the boundary is what is wrong."""
        got, stats = classify(12, [(10, obj_sweep.REL32, CALLEE)])
        self.assertIsNone(got)
        self.assertEqual(stats["skip_rel32_straddles_end"], 1)

    def test_a_call_ending_exactly_on_the_span_end_still_counts(self):
        """Negative control: refusing every site at the tail would pass the above."""
        self.assertEqual(classify(14, [(10, obj_sweep.REL32, CALLEE)])[0], ("rel32", [10]))

    def test_a_span_that_is_mostly_holes_proves_nothing(self):
        got, stats = classify(12, [(0, obj_sweep.REL32, CALLEE),
                                   (4, obj_sweep.REL32, CALLEE)])
        self.assertIsNone(got)
        self.assertEqual(stats["skip_rel32_thin"], 1)

    def test_a_relocation_the_gate_does_not_re_encode_is_refused(self):
        """SECREL and friends: compile_function leaves those bytes as the object
        holds them, so the span is not the same code at a second address."""
        got, stats = classify(20, [(4, 0x000B, "?g@@3HA")])
        self.assertIsNone(got)
        self.assertEqual(stats["skip_other_reloc"], 1)


if __name__ == "__main__":
    unittest.main()
