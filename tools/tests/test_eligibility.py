#!/usr/bin/env python3
"""The one eligibility predicate every picker and brief must share."""
import json
import sys
import time
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import eligibility  # noqa: E402
import re_log  # noqa: E402

RVA = 0x00354C10
SYM = "?d_00354c10@@YAXXZ"


def row(**kw):
    base = {"name": SYM, "target_rva": f"0x{RVA:08X}", "target_size": "400",
            "source": "Code/gen_asm/d_003492a0.asm", "status": "matched",
            "notes": "gen-dump"}
    base.update(kw)
    return base


@pytest.fixture
def world(tmp_path, monkeypatch):
    log = tmp_path / "re_attempts.log"
    log.write_text("", encoding="utf-8")
    (tmp_path / "attempts").mkdir()
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    re_log._reset()
    try:
        yield tmp_path, log
    finally:
        re_log._reset()


def verdict(log, status):
    with log.open("a", encoding="utf-8") as fh:
        fh.write(f"{SYM}\t0x{RVA:08X}\t400\t{status}\tevidence t=5min\n")
    re_log._reset()


def bank(tmp_path, score):
    (tmp_path / "attempts" / f"0x{RVA:08x}.cpp").write_text(
        f"// {SYM}\n// partial score={score} date=2026-09-01\nint x;\n", encoding="utf-8")


def test_dump_row_predicate_covers_note_and_suffix():
    assert eligibility.is_dump_row(row())
    assert eligibility.is_dump_row(row(notes="", source="Code/masm_dumps/x.asm"))
    assert not eligibility.is_dump_row(row(notes="", source="Code/GameEngine/X.cpp"))
    assert not eligibility.is_dump_row(row(status="unmatched"))


def test_anonymous_names():
    assert eligibility.is_anonymous("?d_00354c10@@YAXXZ")
    assert eligibility.is_anonymous("?dup_00354c10@@YAXXZ")
    assert not eligibility.is_anonymous("?init@PartitionManager@@UAEXXZ")


def test_dead_end_retires_but_deferral_does_not(world):
    _, log = world
    verdict(log, "blocked")
    latest = eligibility.latest_verdicts()
    assert eligibility.deferred(RVA, latest) and not eligibility.retired(RVA, latest)
    assert eligibility.open_dumps([row()], latest)
    verdict(log, "no-match")
    latest = eligibility.latest_verdicts()
    assert eligibility.retired(RVA, latest)
    assert eligibility.open_dumps([row()], latest) == []


def test_stash_outlives_a_later_deferral(world):
    tmp_path, log = world
    bank(tmp_path, "0.95")
    verdict(log, "partial")
    verdict(log, "blocked")
    got = eligibility.finish_bodies(0.9, [row()], eligibility.latest_verdicts())
    assert len(got) == 1 and got[0][2] == 0.95


def test_size_window_and_anonymous_filter():
    rows = [row(), row(name="?init@PartitionManager@@UAEXXZ", target_rva="0x00001000",
                      target_size="50")]
    assert len(eligibility.open_dumps(rows, {}, min_size=300)) == 1
    assert len(eligibility.open_dumps(rows, {}, anonymous=False)) == 1
    assert len(eligibility.open_dumps(rows, {}, anonymous=True)) == 1


def test_recent_runs_and_attempt_counts(tmp_path, world):
    world_path, log = world
    runs = tmp_path / "build" / "fleet_runs" / "r1"
    runs.mkdir(parents=True)
    (runs / "record.json").write_text(json.dumps(
        {"start": time.time() - 60, "targets": [["0x00354C10", 400]]}), encoding="utf-8")
    assert eligibility.recent_run_rvas(1, tmp_path) == {"0x00354c10"}
    assert eligibility.recent_run_rvas(0, tmp_path) == set()
    verdict(log, "blocked")
    verdict(log, "partial")
    assert eligibility.attempt_counts()[RVA] == 2


def test_hard_bodies_are_the_capped_complement(world):
    world_path, log = world
    bank(world_path, "0.95")
    for _ in range(3):
        verdict(log, "blocked")
    rows, latest = [row()], eligibility.latest_verdicts()
    served = eligibility.finish_bodies(0.9, rows, latest, max_attempts=3, cooldown_days=0)
    hard = eligibility.hard_bodies(0.9, 3, rows, latest)
    assert served == [] and [eligibility.rva_of(r) for r, _, _ in hard] == [RVA]
    assert len(eligibility.finish_bodies(0.9, rows, latest, max_attempts=4, cooldown_days=0)) == 1
    assert eligibility.hard_bodies(0.9, 4, rows, latest) == []
