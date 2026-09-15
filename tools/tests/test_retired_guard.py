#!/usr/bin/env python3
"""retired_guard refuses re-adding a deliberately deleted path."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import retired_guard as rg  # noqa: E402


def test_offenders_match_listed_paths_only(tmp_path):
    listing = tmp_path / "retired.txt"
    listing.write_text("# retired\ntools/gen_uw.py\ntools/tests/test_gen_uw_shapes.py\n", encoding="utf-8")
    retired = rg.retired_paths(listing)
    assert rg.offenders(["tools/gen_uw.py", "tools/next_work.py"], retired) == ["tools/gen_uw.py"]
    assert rg.offenders(["tools\\tests\\test_gen_uw_shapes.py"], retired) == ["tools\\tests\\test_gen_uw_shapes.py"]
    assert rg.offenders([], retired) == []


def test_tracked_listing_covers_the_generators_and_none_exist():
    retired = rg.retired_paths()
    for name in ("tools/gen_uw.py", "tools/gen_small.py", "tools/gen_dump.py",
                 "tools/land_wave.py", "tools/obj_sweep.py", "tools/wave_accounting.py"):
        assert name in retired
        assert not (ROOT / name).exists(), f"{name} is retired but present"
