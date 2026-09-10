"""Regression tests for gap-thunk candidate retirement."""

import sys
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import gen_small


def test_gap_thunks_do_not_resurrect_a_deleted_claim():
    retired = (0x000094F3, 0x00289800)
    available = (0x0000B41F, 0x00439150)
    tombstones = {(gen_small.thunk_symbol("j", retired[0]), retired[0])}

    picked, subsumed = gen_small.select_gap_thunks(
        [retired, available], {}, "Code/gen_small/gthunks_087.cpp", 20,
        gen_small.overlap_index([]), tombstones)

    assert picked == [available]
    assert subsumed == []
