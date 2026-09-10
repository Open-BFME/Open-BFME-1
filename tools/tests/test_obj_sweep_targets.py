"""Which addresses obj_sweep will aim a wave at, and why those only.

`gen_small.validate_rows` takes over a lone gen-dump row of the exact extent and
refuses everything else, and one refusal aborts the whole wave — so this filter
has to be that rule, spelled the same way. It was spelled two other ways: by
directory, which hides the 349 dumps in Code/gen_small/dumps_000.cpp, and over
the matched rows only, which cannot see an unmatched row sharing the address
(the sibling `uncl` branch already asks about those).
"""
import argparse
import collections
import sys
import types
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import obj_sweep

RVA, SIZE = 0x00ABCD00, 32
ARGS = argparse.Namespace(min_size=8)


def universe(rows, extra_rvas=()):
    """Only what `blocked` reads: rows at an exact extent, and the ledger's rvas."""
    uni = types.SimpleNamespace(rows=collections.defaultdict(list),
                                all_rvas=collections.Counter())
    for row in rows:
        uni.rows[(row["rva"], row["size"])].append(row)
        uni.all_rvas[row["rva"]] += 1
    for rva in extra_rvas:
        uni.all_rvas[rva] += 1
    return uni


def row(name, source, notes, rva=RVA, size=SIZE):
    return {"name": name, "rva": rva, "size": size, "source": source, "notes": notes}


GEN_ASM = row("?d_00abcd00@@YAXXZ", "Code/gen_asm/d_00abcd00.asm",
              "gen-dump;ghidra=FUN_00eacd00")
GEN_SMALL = row("?d_00abcd00@@YAXXZ", "Code/gen_small/dumps_000.cpp",
                "gen-dump;ghidra=FUN_00eacd00")
REAL = row("?realBody@Thing@@QAEXXZ", "Code/GameEngine/Source/Common/Thing.cpp", "")


def blocked(uni):
    skipped = collections.Counter()
    return obj_sweep.blocked(uni, ("dump", RVA, SIZE), {}, ARGS, skipped), skipped


class DumpTargets(unittest.TestCase):
    def test_a_lone_gen_asm_dump_is_landable(self):
        self.assertIsNone(blocked(universe([GEN_ASM]))[0])

    def test_a_dump_outside_gen_asm_is_landable_too(self):
        """land_batch supersedes it by its note; the sweep may aim at it."""
        self.assertIsNone(blocked(universe([GEN_SMALL]))[0])

    def test_a_real_row_is_never_a_dump_target(self):
        self.assertTrue(blocked(universe([REAL]))[0])

    def test_two_rows_at_the_extent_are_a_boundary_dispute(self):
        self.assertTrue(blocked(universe([GEN_ASM, REAL]))[0])

    def test_an_unmatched_row_at_the_address_still_blocks(self):
        """It is absent from `rows` (matched only) and from the matched-range
        index, and validate_rows aborts the wave on it anyway."""
        blocks, skipped = blocked(universe([GEN_ASM], extra_rvas=[RVA]))
        self.assertTrue(blocks)
        self.assertEqual(list(skipped), ["address does not carry a lone gen-dump row"])

    def test_a_span_under_min_size_is_refused_first(self):
        skipped = collections.Counter()
        self.assertTrue(obj_sweep.blocked(universe([GEN_ASM]), ("dump", RVA, 4), {},
                                          ARGS, skipped))


if __name__ == "__main__":
    unittest.main()
