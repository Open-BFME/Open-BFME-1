"""The landing-service prototype: idempotent queue, batch bisection, receipts, recovery."""
import json
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import landing_service as ls  # noqa: E402

GATE = "! ls | grep -q bad"            # red when the tree holds a file named bad*


def git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout.strip()


def test_bisect_keeps_good_units_around_bad_ones():
    calls = []

    def verify(prefix):
        calls.append(list(prefix))
        return not any(u.startswith("bad") for u in prefix)
    units = ["g1", "g2", "bad3", "g4", "g5", "g6", "bad7", "g8"]
    good, bad = ls.bisect(units, verify)
    assert good == ["g1", "g2", "g4", "g5", "g6", "g8"] and bad == ["bad3", "bad7"]
    assert len(calls) <= 2 * 2 * 3 + 1                   # ~2 log2(n) per bad unit
    assert ls.bisect(["g1", "g2"], verify) == (["g1", "g2"], [])


@pytest.fixture
def world(tmp_path):
    origin = tmp_path / "origin.git"
    git(tmp_path, "init", "-q", "--bare", str(origin))
    repos = {}
    for name in ("svc", "seat"):
        repo = tmp_path / name
        git(tmp_path, "init", "-q", str(repo))
        git(repo, "config", "user.name", name)
        git(repo, "config", "user.email", f"{name}@example.com")
        git(repo, "config", "core.hooksPath", "no-hooks")
        git(repo, "remote", "add", "origin", str(origin))
        repos[name] = repo
    seat = repos["seat"]
    (seat / "a.txt").write_text("base\n")
    git(seat, "add", "a.txt")
    git(seat, "commit", "-q", "-m", "base")
    git(seat, "push", "-q", "origin", "HEAD:refs/heads/master")
    patches = tmp_path / "patches"
    patches.mkdir()

    def unit(name, content="x\n", path=None):
        git(seat, "fetch", "-q", "origin", "master")
        git(seat, "reset", "-q", "--hard", "FETCH_HEAD")
        (seat / (path or f"{name}.txt")).write_text(content)
        git(seat, "add", "-A")
        git(seat, "commit", "-q", "-m", f"{name}\n\nVerifier-Change: none, fixture")
        target = patches / f"{name}.patch"
        target.write_bytes(subprocess.run(["git", "format-patch", "-1", "--stdout"], cwd=seat,
                                          check=True, capture_output=True).stdout)
        return target
    service = ls.Service(repo=repos["svc"], state=tmp_path / "state", gate=GATE,
                         fence=lambda record: True)
    return service, unit, origin


def origin_files(origin):
    return sorted(git(origin, "ls-tree", "--name-only", "master").split())


def test_a_batch_lands_the_good_units_once_and_rejects_the_bad(world):
    service, unit, origin = world
    ids = [service.enqueue(unit(n)) for n in ("good1", "bad2", "good3")]
    result = service.run_once()
    assert result["landed"] == [ids[0], ids[2]] and result["rejected"] == [ids[1]]
    assert origin_files(origin) == ["a.txt", "good1.txt", "good3.txt"]
    receipt = json.loads((service.state / "receipts" / f"{ids[0]}.json").read_text())
    master = git(origin, "rev-parse", "master")
    assert receipt["batch_tip"] == master and receipt["gate_exit"] == 0
    assert git(origin, "merge-base", "--is-ancestor", receipt["commit"], master) == ""
    rejected = json.loads((service.state / "rejected" / f"{ids[1]}.json").read_text())
    assert rejected["reason"] == "gate"
    # idempotent: a landed unit enqueued again stays landed; nothing reruns
    landed_patch = service.state / "landed_copy.patch"
    landed_patch.write_bytes((service.state / "queue" / f"{ids[0]}.patch").read_bytes())
    assert service.enqueue(landed_patch) == ids[0]
    assert service.queued() == []
    assert service.run_once() == {"landed": [], "rejected": []}


def test_enqueue_is_idempotent_by_content(world):
    service, unit, _ = world
    patch = unit("same")
    first = service.enqueue(patch)
    assert service.enqueue(patch) == first
    assert len(service.queued()) == 1


def test_a_conflicting_unit_is_rejected_and_the_rest_land(world):
    service, unit, origin = world
    one = service.enqueue(unit("edit1", "one\n", path="a.txt"))
    two = service.enqueue(unit("edit2", "two\n", path="a.txt"))     # same base line: conflicts after one
    result = service.run_once()
    assert result == {"landed": [one], "rejected": [two]}
    assert json.loads((service.state / "rejected" / f"{two}.json").read_text())["reason"] == "conflict"


def test_a_lost_claim_is_fenced_out(world):
    service, unit, origin = world
    service.fence = lambda record: not record.get("claims")
    kept = service.enqueue(unit("mine"))
    lost = service.enqueue(unit("stale"), {"claims": {"0x00000100": "deadbeef"}})
    result = service.run_once()
    assert result == {"landed": [kept], "rejected": [lost]}


def test_a_crash_after_the_push_is_recorded_as_landed(world):
    service, unit, origin = world
    unit_id = service.enqueue(unit("crash"))
    base = service.snapshot()
    tip, _ = service._apply(base, [unit_id])
    git(service.work, "push", "-q", "origin", f"{tip}:refs/heads/master")   # pushed, then "crashed"
    service._phase(phase="publishing", base=base, tip=tip, units=[unit_id], gate_exit=0)
    assert service.run_once() == {"landed": [], "rejected": []}
    assert (service.state / "landed" / f"{unit_id}.json").exists()
    assert json.loads((service.state / "receipts" / f"{unit_id}.json").read_text())["note"]
