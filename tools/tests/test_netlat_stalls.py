#!/usr/bin/env python3
"""Check the freeze analysis on data whose answer is known by construction.

The retry-timer spike is decided on this file's output, and its riskiest
behaviours all fail silently on real captures:

  * the match-start gap is dropped by POSITION, not by size. Dropping by size
    would also discard the genuine multi-second freezes the whole spike is
    about -- and the result would look like a fix that eliminated them;
  * that gap is excluded from the DENOMINATOR too. Match loads measured 11 s to
    23 s between runs for reasons unrelated to the arm, which is enough to move
    a per-minute rate by 5% on its own;
  * the guest is the headline and the router is reported separately. Pooling
    them would roughly halve the freeze rate, which reads as an improvement.

Checked against synthetic captures, so the expected answer is arithmetic rather
than another run of the same code.
"""
import json
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from netlat_stalls import STALL_MS, stalls, summarise  # noqa: E402

FREQ = 1_000_000        # 1 MHz, so a microsecond is a tick and ms are exact


def _seat(path, gaps_ms, router):
    """A capture whose frame events sit exactly `gaps_ms` apart."""
    lines = [json.dumps({"ev": "open", "qfreqlo": FREQ, "qfreqhi": 0})]
    t = 0.0
    for n, gap in enumerate([0.0] + list(gaps_ms)):
        t += gap
        q = int(t * 1000)
        lines.append(json.dumps({
            "ev": "frame", "qlo": q & 0xFFFFFFFF, "qhi": q >> 32,
            "f": n, "c": n + 1, "slot": 0 if router else 1,
            "router": 1 if router else 0, "exec": 1, "desync": 0, "stalls": 0}))
    path.write_text("\n".join(lines) + "\n")


@pytest.fixture
def run(tmp_path):
    def build(guest_gaps, router_gaps=None):
        d = tmp_path / "run"
        d.mkdir(exist_ok=True)
        _seat(d / "P1.jsonl",
              router_gaps if router_gaps is not None else [200.0] * 20, router=True)
        _seat(d / "P3.jsonl", guest_gaps, router=False)
        return d
    return build


def test_the_match_start_gap_is_dropped_by_position_not_size(run):
    """A 9 s load followed by a genuine 2 s freeze: the load goes, the freeze
    stays. Dropping by size would take both and report a match with no freezes."""
    d = run([9000.0] + [200.0] * 10 + [2000.0] + [200.0] * 10)
    out = summarise(d)
    assert len(out["lost"]) == 1, "the real freeze was discarded with the load"
    assert out["lost"][0] == pytest.approx(2000.0)


def test_a_long_freeze_late_in_the_match_is_never_discarded(run):
    """The load gap is not the largest gap here. Position, not rank."""
    d = run([1000.0] + [200.0] * 5 + [8000.0] + [200.0] * 5)
    assert [round(x) for x in summarise(d)["lost"]] == [8000]


def test_the_load_gap_is_out_of_the_denominator_too(run):
    """Two identical matches whose loads differ by 20 s must report the same
    per-minute rate; otherwise startup variance masquerades as an arm effect."""
    body = [200.0] * 50 + [2000.0] + [200.0] * 50
    quick = summarise(run([2000.0] + body))
    slow = summarise(run([22000.0] + body))
    assert quick["per_min"] == pytest.approx(slow["per_min"], rel=1e-6)
    assert quick["behind_pct"] == pytest.approx(slow["behind_pct"], rel=1e-6)


def test_the_router_is_reported_separately_not_pooled(run):
    """A change that helped the guest by hurting the router must be visible."""
    d = run([500.0] + [200.0] * 8 + [2000.0] * 3 + [200.0] * 8,
            router_gaps=[500.0] + [200.0] * 8 + [2000.0] + [200.0] * 8)
    out = summarise(d)
    assert len(out["lost"]) == 3, "the guest's freezes are the headline"
    assert out["router_lost"] == 1, "the router's are counted, and counted apart"


def test_sub_threshold_jitter_is_not_a_freeze(run):
    assert summarise(run([1000.0] + [STALL_MS - 1] * 10))["lost"] == []


def test_net_and_wall_are_different_quantities(run):
    """A guest that freezes and then catches up has spent wall time frozen and
    lost little game time. Reporting one as the other would overstate a fix."""
    d = run([1000.0] + [200.0] * 9 + [2000.0] + [100.0] * 18)
    out = summarise(d)
    assert out["share"] > out["behind_pct"], \
        "catch-up must show up as net game time recovered"


def test_overall_speed_counts_the_frozen_time(run):
    d = run([1000.0] + [200.0] * 9 + [2000.0] + [200.0] * 9)
    out = summarise(d)
    assert out["overall"] < 5.0, "freezing cannot leave the overall rate at 5"
    assert out["rate"] == pytest.approx(5.0, abs=0.01), \
        "between freezes the game still runs at 5 Hz"


def test_a_capture_with_no_match_refuses_rather_than_reporting_zero(tmp_path):
    d = tmp_path / "empty"
    d.mkdir()
    _seat(d / "P1.jsonl", [], router=True)
    _seat(d / "P3.jsonl", [], router=False)
    with pytest.raises(SystemExit):
        summarise(d)


def test_stalls_needs_two_frames_to_say_anything(tmp_path):
    p = tmp_path / "one.jsonl"
    _seat(p, [], router=False)
    from netlat import load  # noqa: E402
    with pytest.raises(SystemExit):
        stalls(load(p))
