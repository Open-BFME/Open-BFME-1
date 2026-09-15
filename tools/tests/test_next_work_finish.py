#!/usr/bin/env python3
"""The finish tier serves a banked stash while its address is still a dump,
survives a later deferral, and retires on a later dead-end verdict."""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import next_work  # noqa: E402
import re_log  # noqa: E402

RVA = 0x00354C10
SYM = "??0Rva0035D2B0Node@@QAE@XZ"


@pytest.fixture
def world(tmp_path, monkeypatch):
    log = tmp_path / "re_attempts.log"
    log.write_text("", encoding="utf-8")
    (tmp_path / "attempts").mkdir()
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    re_log._reset()
    rows = [{"name": SYM, "target_rva": f"0x{RVA:08X}", "target_size": "76",
             "source": "Code/gen_asm/d_003492a0.asm", "status": "matched",
             "notes": "gen-dump"}]
    monkeypatch.setattr(build, "load_all_function_rows", lambda: rows)
    try:
        yield tmp_path, log, rows
    finally:
        re_log._reset()


def bank(tmp_path, score):
    (tmp_path / "attempts" / f"0x{RVA:08x}.cpp").write_text(
        f"// {SYM}\n// partial score={score} date=2026-09-15\nint x;\n", encoding="utf-8")


def verdict(log, status):
    with log.open("a", encoding="utf-8") as fh:
        fh.write(f"{SYM}\t0x{RVA:08X}\t76\t{status}\tevidence t=5min\n")
    re_log._reset()


def test_served_from_stash_with_score(world):
    tmp_path, log, _ = world
    bank(tmp_path, "0.95")
    verdict(log, "partial")
    got = next_work.finish_candidates(0.9)
    assert [c["target_rva"] for c in got] == [f"0x{RVA:08X}"]
    assert got[0]["score"] == 0.95 and got[0]["function"] == SYM
    assert got[0]["latest_verdict"] == "partial"
    assert "probe.py" in got[0]["command"]


def test_later_deferral_does_not_hide_the_stash(world):
    tmp_path, log, _ = world
    bank(tmp_path, "0.95")
    verdict(log, "partial")
    verdict(log, "blocked")
    got = next_work.finish_candidates(0.9)
    assert len(got) == 1 and got[0]["latest_verdict"] == "blocked"


def test_later_dead_end_retires_the_address(world):
    tmp_path, log, _ = world
    bank(tmp_path, "0.95")
    verdict(log, "partial")
    verdict(log, "no-match")
    assert next_work.finish_candidates(0.9) == []


def test_below_threshold_and_landed_rows_are_not_served(world):
    tmp_path, log, rows = world
    bank(tmp_path, "0.80")
    assert next_work.finish_candidates(0.9) == []
    bank(tmp_path, "0.99")
    rows[0]["source"] = "Code/GameEngine/Source/Common/Node.cpp"
    rows[0]["notes"] = "clean C++"
    assert next_work.finish_candidates(0.9) == []


def test_finish_choice_prefers_closer_bodies():
    cands = [{"score": 0.99}, {"score": 0.90}]
    draws = [next_work.finish_choice(cands)["score"] for _ in range(300)]
    assert draws.count(0.99) > draws.count(0.90) * 3
