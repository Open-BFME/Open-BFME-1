"""obj_sweep must never name an address after a symbol the ledger already places.

17 rows shipped claiming a real mangled name at an address whose symbol was
already proven somewhere else, because the ledger records that proof in a row's
`object-symbol=` note rather than in its `name` column. Both spellings are
identity; only one was being read.
"""
import collections
import sys
import types
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import obj_sweep


def universe(rows):
    """A stand-in carrying only what wave_name reads, built the way Universe does."""
    import build as B
    uni = types.SimpleNamespace(tombstoned=set(), placements=collections.Counter())
    for row in rows:
        uni.placements[B.ledger_object_symbol(row)] += 1
    return uni


def name_for(uni, symbol, rva, extra_matches=0, taken=()):
    record = {"owners": [obj_sweep.Owner("Code/x.cpp", symbol, "rf", 0, ())]}
    folds = collections.Counter({symbol: 1 + extra_matches})
    folds.update(uni.placements)
    return obj_sweep.wave_name(uni, record, rva, folds, set(taken), collections.Counter())


REAL = "?get_value@RvaA3160Offset1088Getter@@QAEIXZ"


class WaveName(unittest.TestCase):
    def test_unplaced_symbol_matching_one_address_keeps_its_real_name(self):
        self.assertEqual(name_for(universe([]), REAL, 0x0015A2C0), REAL)

    def test_symbol_placed_under_a_synthetic_name_is_not_reused(self):
        # The ledger's row is named ?d_000a3160; only its note says which
        # compiled symbol those bytes are. That note is the placement.
        uni = universe([{"name": "?d_000a3160@@YAXXZ",
                         "notes": f"object-symbol={REAL};Open-BFME5 clean C++"}])
        self.assertEqual(name_for(uni, REAL, 0x0015A2C0), "?dup_0015a2c0@@YAXXZ")

    def test_symbol_placed_under_its_own_name_is_not_reused(self):
        uni = universe([{"name": REAL, "notes": "Open-BFME5 clean C++"}])
        self.assertEqual(name_for(uni, REAL, 0x0015A2C0), "?dup_0015a2c0@@YAXXZ")

    def test_icf_class_wider_than_one_address_gets_an_alias(self):
        self.assertEqual(name_for(universe([]), REAL, 0x0015A2C0, extra_matches=3),
                         "?dup_0015a2c0@@YAXXZ")

    def test_splitting_a_wave_does_not_erode_the_icf_guard(self):
        # Wave 1 landed three of the four addresses as aliases; to wave 2 the
        # fourth is the only unheld member and would look unique on its own.
        uni = universe([{"name": f"?dup_{rva:08x}@@YAXXZ",
                         "notes": f"gen-alias;object-symbol={REAL};C++ alias"}
                        for rva in (0x68BF0, 0xA0AB0, 0x1337F0)])
        self.assertEqual(name_for(uni, REAL, 0x0015A2C0), "?dup_0015a2c0@@YAXXZ")


if __name__ == "__main__":
    unittest.main()
