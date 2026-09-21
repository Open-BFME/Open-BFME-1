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
        fh.write(f"{SYM}\t0x{RVA:08X}\t400\t{status}\tevidence t=35min\n")   # over QUICK_LOOK_MINUTES: a real attempt
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


def test_only_touched_targets_cool_down_and_aborted_runs_cool_nothing(tmp_path):
    def run(name, **record):
        directory = tmp_path / "build" / "fleet_runs" / name
        directory.mkdir(parents=True)
        record.setdefault("start", time.time() - 60)
        (directory / "record.json").write_text(json.dumps(record), encoding="utf-8")
    two = [["0x00000010", 10], ["0x00000020", 10]]
    run("worked", status="finished", exit_code=0, seconds=4000, targets=two, touched=["0x00000010"])
    run("quota", status="finished", exit_code=1, seconds=3, targets=[["0x00000030", 10]], touched=[])
    run("legacy-quota", status="finished", exit_code=1, seconds=3, targets=[["0x00000040", 10]])
    run("live", status="running", targets=[["0x00000050", 10]], touched=[])
    assert eligibility.recent_run_rvas(1, tmp_path) == {"0x00000010", "0x00000050"}


def test_servable_applies_every_lane_rule(tmp_path, world, monkeypatch):
    world_path, log = world
    ok = eligibility.servable(tmp_path)
    assert ok(RVA) and ok(RVA + 0x10)
    directory = tmp_path / "build" / "fleet_runs" / "r1"
    directory.mkdir(parents=True)
    (directory / "record.json").write_text(json.dumps(dict(
        start=time.time() - 60, status="finished", exit_code=0, seconds=4000,
        targets=[[f"0x{RVA:08x}", 400]], touched=[f"0x{RVA:08x}"])), encoding="utf-8")
    assert not eligibility.servable(tmp_path)(RVA)          # a run just worked on it
    assert eligibility.servable(tmp_path, hours=0)(RVA)
    for _ in range(eligibility.ATTEMPT_CAP):
        verdict(log, "blocked")
    assert not eligibility.servable(tmp_path, hours=0)(RVA)  # attempt cap
    monkeypatch.setattr(eligibility, "unlocked_rvas", lambda path=None: {RVA})
    assert eligibility.servable(tmp_path, hours=0)(RVA)      # reopened on purpose


def test_a_quick_look_is_not_an_attempt(world):
    world_path, log = world
    with log.open("a", encoding="utf-8") as fh:
        fh.write(f"{SYM}\t0x{RVA:08X}\t400\tblocked\tno named caller identifies the owner t=2min model=x\n")
    re_log._reset()
    assert eligibility.quick_look("blocked", "no named caller t=2min model=x")
    assert not eligibility.quick_look("blocked", "three shapes tried t=45min model=x")
    assert not eligibility.quick_look("partial", "t=3min stash=reverse/attempts/x.cpp score=0.4")
    assert not eligibility.quick_look("blocked", "no duration given")      # unknown effort still counts
    assert eligibility.attempt_counts().get(RVA, 0) == 0                   # somebody looked, nobody tried
    with log.open("a", encoding="utf-8") as fh:
        fh.write(f"{SYM}\t0x{RVA:08X}\t400\tblocked\tthree shapes tried t=40min model=x\n")
    re_log._reset()
    assert eligibility.attempt_counts()[RVA] == 1


def test_neighbour_density_counts_landed_cpp_around_a_body():
    def row(rva, source, size=200):
        return dict(name=f"?f{rva:x}@@YAXXZ", target_rva=f"0x{rva:08X}", target_size=str(size),
                    source=source, status="matched", notes="")
    rows = [row(0x1000 + 0x100 * i, "Code/GameEngine/Source/a.cpp") for i in range(6)]
    rows += [row(0x2000 + 0x100 * i, "Code/gen_asm/d_00002000.asm") for i in range(6)]
    rows += [row(0x1050, "Code/gen_small/thunks_001.cpp"), row(0x1060, "Code/GameEngine/Source/tiny.cpp", size=8)]
    density = eligibility.neighbour_density(rows, k=3)
    assert density(0x1200) == 1.0            # generated rows and tiny bodies are not neighbours
    assert density(0x2300) == 0.0
    assert 0.0 < density(0x1F00) < 1.0       # between the two regions
    assert eligibility.neighbour_density(rows[:3], k=3)(0x1100) is None   # too few neighbours to say
    assert eligibility.neighbour_prior(1.0) > eligibility.neighbour_prior(0.5) > eligibility.neighbour_prior(0.1)
    dense = eligibility.expected_bytes(2, 600, 0.9)
    sparse = eligibility.expected_bytes(2, 900, 0.1)
    assert dense > sparse                    # a smaller body in a landed neighbourhood outranks a bigger cold one


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


def test_unlocked_rvas_parses_tags_and_ignores_comments(tmp_path):
    f = tmp_path / "unlocked.txt"
    f.write_text("# header" + chr(10) + "0x00354C10 w3d-render  # after DX8State.h" + chr(10)
                 + chr(10) + "bad line" + chr(10) + "0x00001000" + chr(10), encoding="utf-8")
    got = eligibility.unlocked_rvas(f)
    assert got == {0x00354C10: "w3d-render", 0x1000: ""}
    assert eligibility.unlocked_rvas(tmp_path / "missing.txt") == {}


def test_boundary_suspect_reads_latest_deferral_only(world):
    _, log = world
    with log.open("a", encoding="utf-8") as fh:
        fh.write(f"{SYM}\t0x{RVA:08X}\t400\tblocked\tQueued RVA starts in the tail of a live helper and crosses unrelated bodies t=5min\n")
    re_log._reset()
    assert eligibility.boundary_suspect(RVA)
    verdict(log, "partial")
    assert not eligibility.boundary_suspect(RVA)
    with log.open("a", encoding="utf-8") as fh:
        fh.write(f"{SYM}\t0x{RVA:08X}\t400\tno-boundary\tstarts inside another body\n")
    re_log._reset()
    assert not eligibility.boundary_suspect(RVA)
    assert not eligibility.boundary_suspect(0x1234)


def test_expected_bytes_prefers_bytes_then_warmth():
    assert eligibility.expected_bytes(3, 1200) > eligibility.expected_bytes(5, 90)
    assert eligibility.expected_bytes(1, 400) > eligibility.expected_bytes(0, 2400)
    assert eligibility.expected_bytes(2, 800) > eligibility.expected_bytes(1, 800)
