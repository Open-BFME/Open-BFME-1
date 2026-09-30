"""The provider fleet lane: one scripted pass serves, checks, hands off or abandons.

tools/provider_repair.py is replaced by a fake with the same CLI, so these
tests pin the seat's decisions (nothing served -> idle; FAIL -> restored and
abandoned; PASS -> committed and handed to the landing queue with its lease,
never pushed) and the drainer's (rebase, re-check on the published tree,
land, release the claim only once on master).
"""
import json
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "fleet"))

import claims  # noqa: E402
import provider_seat as ps  # noqa: E402

FAKE = r'''
import json, os, subprocess, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
mode = os.environ.get("FAKE_MODE", "pass")
cmd = sys.argv[1]
d = ROOT / "build/provider_repair/0x00000100"
if cmd == "next":
    if mode == "nothing":
        print("provider_repair: nothing to serve; serve 0"); sys.exit(1)
    d.mkdir(parents=True, exist_ok=True)
    facts = {"symbol": "?f@Legacy@@QAEXXZ", "rva": "0x00000100", "size": 16,
             "competitors": [{"source": "game/legacy.cpp", "object": "legacy.obj"}],
             "owner": {"source": "game/owner.cpp"}, "other_copies": []}
    (d / "brief.json").write_text(json.dumps(facts))
    if mode != "noclaim":                      # the real `next` claims what it serves
        sys.path.insert(0, str(ROOT / "tools"))
        import claims
        assert claims.claim([0x100], root=ROOT).claimed == [0x100]
    print("  brief       build/provider_repair/0x00000100/brief.json"); sys.exit(0)
if cmd == "apply":
    (ROOT / "game/legacy.cpp").write_text("// Retail f is implemented in owner.cpp.\n"); sys.exit(0)
if cmd == "check":
    import hashlib
    with (ROOT / "checks.txt").open("a") as h:
        h.write("check\n")
    owner = (ROOT / "game/owner.cpp").read_text()
    if mode == "fail" or "wrong" in owner:        # the real check judges the owner's body
        print("FAIL: harness: owner body differs from retail"); sys.exit(1)
    inputs = {p: hashlib.sha256((ROOT / p).read_bytes()).hexdigest()
              for p in ("game/legacy.cpp", "game/owner.cpp")}
    (d / "receipt.json").write_text(json.dumps({"pass": True, "inputs": inputs,
                                                "steps": {"gate": {"result": "Functions: OK 2/2"}}}))
    print("PASS"); sys.exit(0)
if cmd == "abandon":
    subprocess.run(["git", "checkout", "--", "game/legacy.cpp"], cwd=ROOT, check=True)
    with (ROOT / "abandoned.txt").open("a") as h:
        h.write(" ".join(sys.argv[2:]) + "\n")
    sys.exit(0)
'''


def git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout.strip()


@pytest.fixture
def seat(tmp_path, monkeypatch):
    origin = tmp_path / "origin.git"
    git(tmp_path, "init", "-q", "--bare", str(origin))
    wt = tmp_path / "wt_provider_seat1"
    git(tmp_path, "init", "-q", str(wt))
    for key, value in (("user.name", "seat"), ("user.email", "seat@example.com"),
                       ("core.hooksPath", "no-hooks")):
        git(wt, "config", key, value)
    git(wt, "remote", "add", "origin", str(origin))
    (wt / "tools").mkdir()
    (wt / "tools/provider_repair.py").write_text(FAKE, encoding="utf-8")
    for name in ("claims.py", "portable_lock.py"):
        shutil.copy(TOOLS / name, wt / "tools" / name)
    (wt / "game").mkdir()
    (wt / "game/legacy.cpp").write_text("void Legacy::f() {}\nvoid Legacy::g() {}\n")
    (wt / "game/owner.cpp").write_text("void Legacy::f() { /* retail */ }\n")
    (wt / ".gitignore").write_text("build/\nabandoned.txt\nchecks.txt\n__pycache__/\n")
    git(wt, "add", ".")
    git(wt, "commit", "-q", "-m", "base")
    git(wt, "push", "-q", "origin", "HEAD:refs/heads/master")
    monkeypatch.setenv("BFME_CLAIM_OWNER", "provider-seat-1")
    monkeypatch.setenv("BFME_MODEL", "script/provider_repair")
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    claims.active.cache_clear()
    return ps.worktree(wt), origin


@pytest.fixture
def queue(seat, tmp_path, monkeypatch):
    """This host's landing service, pointed at the fixture origin."""
    import landing_service as ls
    wt, origin = seat
    service = ls.Service(repo=wt, state=tmp_path / "landing", gate="true")
    monkeypatch.setattr(ps, "landing", lambda: service)
    return service


def test_nothing_to_serve_idles(seat, queue, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "nothing")
    assert ps.once(wt) == ps.NOTHING
    assert queue.queued() == []


def test_a_failed_check_is_abandoned_and_restored(seat, queue, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "fail")
    assert ps.once(wt) == ps.FAILED
    assert (wt / "game/legacy.cpp").read_text().startswith("void Legacy::f()")
    assert "?f@Legacy@@QAEXXZ --model script/provider_repair" in (wt / "abandoned.txt").read_text()
    assert queue.queued() == []


def test_a_pass_is_handed_to_the_landing_queue_not_pushed(seat, queue, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    before = git(origin, "rev-parse", "master")
    assert ps.once(wt) == ps.QUEUED
    assert git(origin, "rev-parse", "master") == before          # the seat never races master
    [unit] = queue.queued()
    lease = claims.current_lease(0x100, root=wt)
    assert unit["claims"] == {"0x00000100": lease} and unit["model"] == "script/provider_repair"
    assert "provider_repair.py check" in unit["verify"] and "?f@Legacy@@QAEXXZ" in unit["verify"]
    assert list(unit["attach"]) == ["build/provider_repair/0x00000100"]
    patch = (queue.state / "queue" / f"{unit['id']}.patch").read_text()
    assert f"Claim-Lease: 0x00000100={lease}" in patch and "game/legacy.cpp" in patch
    claims.active.cache_clear()
    assert 0x100 in claims.active(wt)                              # kept until it lands
    assert git(wt, "status", "--porcelain") == ""
    assert git(wt, "rev-parse", "HEAD") == git(wt, "rev-parse", ps.MASTER)


def test_no_lease_means_nothing_is_handed_off(seat, queue, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "noclaim")
    assert ps.once(wt) == ps.FAILED
    assert queue.queued() == [] and git(wt, "status", "--porcelain") == ""


def _peer(origin, tmp_path):
    peer = tmp_path / "peer"
    git(tmp_path, "clone", "-q", str(origin), str(peer))
    for key, value in (("user.name", "peer"), ("user.email", "peer@example.com"),
                       ("core.hooksPath", "no-hooks")):
        git(peer, "config", key, value)
    return peer


def test_the_drainer_lands_it_checks_again_and_releases_the_claim(seat, queue, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    assert ps.once(wt) == ps.QUEUED
    result = queue.run_once()
    assert len(result["landed"]) == 1 and result["rejected"] == []
    head = git(origin, "rev-parse", "master")
    assert git(origin, "diff-tree", "--no-commit-id", "--name-only", "-r", head).split() == \
        ["game/legacy.cpp"]
    assert "check" in (queue.work / "checks.txt").read_text()     # re-checked on the landed tree
    assert git(origin, "for-each-ref", "refs/claims/") == ""       # released once on master


def test_an_upstream_change_after_the_seats_check_is_caught_by_the_drainer(
        seat, queue, tmp_path, monkeypatch):
    # The races fixed in f3806f101a..fa8ff653ae (owner source, ledger, an
    # included .cpp changing after the seat's check) are now structural: the
    # drainer rebases first and runs the unit's own check on the exact tree
    # it would publish.
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    assert ps.once(wt) == ps.QUEUED
    peer = _peer(origin, tmp_path)
    (peer / "game/owner.cpp").write_text("void Legacy::f() { /* wrong linked provider */ }\n")
    git(peer, "commit", "-q", "-am", "owner changed after the seat's check")
    git(peer, "push", "-q", "origin", "HEAD:master")
    result = queue.run_once()
    assert result["landed"] == [] and len(result["rejected"]) == 1
    assert git(origin, "log", "-1", "--format=%s", "master") == "owner changed after the seat's check"


def test_the_lane_exists_and_is_off_by_default():
    launch = (TOOLS / "fleet" / "launch_fleet.sh").read_text(encoding="utf-8")
    seat_sh = (TOOLS / "fleet" / "seat.sh").read_text(encoding="utf-8")
    assert "P=${10:-0}" in launch and 'launch provider "$i"' in launch
    assert 'if [ "$ENGINE" = provider ]; then' in seat_sh
    assert "tools/fleet/provider_seat.py" in seat_sh and "FLEET_DRY_PAUSE" in seat_sh
