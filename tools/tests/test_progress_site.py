"""progress_site: the map's layout and the exact per-file byte split."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import progress_site as site  # noqa: E402


@pytest.mark.parametrize("sizes", [[5], [6, 6, 4, 3, 2, 2, 1], [100, 1, 1, 1], [3, 3, 3, 3, 3, 3, 3, 3, 3]])
def test_squarify_tiles_the_whole_area_without_overlap(sizes):
    rects = site.squarify([(i, s) for i, s in enumerate(sizes)], 0, 0, 1100, 560)
    assert len(rects) == len(sizes)
    assert sum(w * h for _, _, _, w, h in rects) == pytest.approx(1100 * 560)
    for (i, x, y, w, h) in rects:
        assert w * h == pytest.approx(1100 * 560 * sizes[i] / sum(sizes))
        assert x >= -1e-6 and y >= -1e-6 and x + w <= 1100 + 1e-6 and y + h <= 560 + 1e-6
    for a in rects:
        for b in rects:
            if a is not b:
                overlap_w = min(a[1] + a[3], b[1] + b[3]) - max(a[1], b[1])
                overlap_h = min(a[2] + a[4], b[2] + b[4]) - max(a[2], b[2])
                assert overlap_w <= 1e-6 or overlap_h <= 1e-6


def test_subtract_leaves_only_the_uncovered_pieces():
    claimed = [(10, 20), (30, 40), (50, 60)]
    starts = [lo for lo, _ in claimed]
    assert site._subtract(0, 70, claimed, starts) == [(0, 10), (20, 30), (40, 50), (60, 70)]
    assert site._subtract(12, 18, claimed, starts) == []
    assert site._subtract(15, 35, claimed, starts) == [(20, 30)]
    assert site._subtract(60, 65, claimed, starts) == [(60, 65)]


@pytest.mark.parametrize("source,expected", [
    ("game/GameEngine/Source/GameLogic/Object/Foo.cpp", "engine"),
    ("game/GameEngineDevice/Source/W3DDevice/X.cpp", "device"),
    ("inputs/vendor/d3dx9/d3dx9.lib", "libraries"),
    ("game/gen_small/eh_anchor.cpp", "generated"),
    ("game/gen_asm/d_002e22f0.asm", "dumps"),
])
def test_categories_follow_the_tree(source, expected):
    assert site.category(source) == expected
    assert site.category(site.block_of(source) + "/") == expected
