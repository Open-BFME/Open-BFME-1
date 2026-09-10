"""Regression tests for the real-identity small-function generator."""

import sys
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import gen_small


def test_named_batch_does_not_reemit_another_landed_batch():
    first = (0x1000, 8, "first", b"first")
    second = (0x2000, 8, "second", b"second")
    unclaimed = (0x3000, 8, "third", b"third")
    claimed = {
        0x1000: "Code/gen_small/named_000.cpp",
        0x2000: "Code/gen_small/named_001.cpp",
    }

    selected = gen_small.named_batch_population(
        [first, second, unclaimed], claimed, "Code/gen_small/named_001.cpp")

    assert selected == [second, unclaimed]
