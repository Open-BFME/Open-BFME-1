#!/usr/bin/env python3
"""The comparison tool must lead with the creation-anchored metric.

`netlat_compare.py` reported `to_execution` — send-anchored — as its headline for
an entire campaign. That clock starts when a command LEAVES the machine, which
subtracts a send-side fix's own benefit and, under packet loss, charges the fixed
build for a freeze that the baseline's later timestamp lands inside. It produced
a phantom p95 regression that two sessions reproduced independently, because they
shared the instrument rather than the finding.

The regression is silent: the tool still runs, still prints plausible
milliseconds, and is wrong by ~60 ms in the direction that hides the fix. These
tests fail loudly if the headline reverts.
"""
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
CAPTURES = ROOT / "build/netlat"
BASE, FIX = CAPTURES / "s9-retail-1", CAPTURES / "s9-both-1"

pytestmark = pytest.mark.skipif(
    not (BASE.exists() and FIX.exists()),
    reason="reference captures not present")


@pytest.fixture(scope="module")
def report():
    r = subprocess.run(
        [sys.executable, str(ROOT / "tools/netlat_compare.py"),
         "--baseline", str(BASE), "--fix", str(FIX), "--label", "both400"],
        capture_output=True, text=True, cwd=ROOT)
    assert r.returncode == 0, r.stderr or r.stdout
    return r.stdout


def row(report, label):
    """(baseline median, fix median, change) for one printed row.

    The bracketed [lo-hi] spreads are skipped deliberately: they contain a
    hyphen and would otherwise be parsed as a negative number.
    """
    for line in report.splitlines():
        if not line.startswith(label):
            continue
        out = []
        for tok in line[len(label):].split():
            if tok.startswith("["):
                continue
            try:
                out.append(float(tok.rstrip("ms").rstrip("/s").rstrip("fr")))
            except ValueError:
                pass
        assert len(out) == 3, f"expected 3 numbers in {line!r}, got {out}"
        return out
    raise AssertionError(f"no row {label!r} in:\n{report}")


def test_creation_anchored_row_is_present_and_first(report):
    """The creation-anchored figure leads, and the send-anchored one is marked."""
    body = report[report.index("change"):]
    created = body.index("guest: CREATED -> it runs")
    superseded = body.index("guest: send -> it runs (SUPERSEDED)")
    assert created < superseded


def test_held_is_reported_as_a_result(report):
    """`held` separates the arms and must be visible, not buried as a check.

    It read 86.9-96.1 ms in every retail arm and 0.1 ms in every 031-earlysend
    arm from the first capture onward, and went unread as a result for four
    hours because it was labelled a validity check. It is the quantity a
    send-side fix actually moves.
    """
    values = row(report, "guest: held locally before send")
    assert values, "held row missing"
    baseline, fixed, change = values
    assert 80.0 < baseline < 100.0, f"retail hold should be ~90ms, got {baseline}"
    assert fixed < 5.0, f"earlysend hold should be ~0ms, got {fixed}"


def test_send_anchored_clock_understates_the_fix(report):
    """The reason the headline had to change, asserted rather than described.

    Both rows measure the same two captures. The send-anchored one credits the
    fix with less because it starts its clock after the delay the fix removes.
    """
    _, _, created_change = row(report, "guest: CREATED -> it runs")
    _, _, sent_change = row(report, "guest: send -> it runs (SUPERSEDED)")
    assert created_change < sent_change < 0, (
        f"creation-anchored improvement {created_change} should exceed "
        f"send-anchored {sent_change}; both should be negative")


def test_no_bare_nan_rows(report):
    """A nan reads as a broken measurement.

    The router has no creation-anchored figure for a structural reason — it binds
    its own commands in sendLocalCommand and never relays them to itself, so the
    join has nothing to bind to. That row is omitted rather than printed as nan.
    """
    body = report[report.index("change"):]
    assert "nan" not in body.lower(), f"nan in report body:\n{body}"
