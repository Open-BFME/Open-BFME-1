"""The provider fleet lane: one scripted pass serves, checks, lands or abandons.

tools/provider_repair.py is replaced by a fake with the same CLI, so these
tests pin the seat's own decisions: nothing served -> idle; FAIL -> sources
restored and abandoned; PASS -> exactly the competitor sources committed,
pushed, confirmed on origin/master by ancestry, the claim released through
its Claim-Lease trailer; unpushable -> patch kept inside the seat worktree.
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


def test_nothing_to_serve_idles(seat, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "nothing")
    before = git(origin, "rev-parse", "master")
    assert ps.once(wt) == ps.NOTHING
    assert git(origin, "rev-parse", "master") == before


def test_a_failed_check_is_abandoned_and_restored(seat, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "fail")
    before = git(origin, "rev-parse", "master")
    assert ps.once(wt) == ps.FAILED
    assert (wt / "game/legacy.cpp").read_text().startswith("void Legacy::f()")
    assert "?f@Legacy@@QAEXXZ --model script/provider_repair" in (wt / "abandoned.txt").read_text()
    assert git(origin, "rev-parse", "master") == before


def test_a_pass_lands_on_master_with_receipt_and_releases_the_claim(seat, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    assert ps.once(wt) == ps.LANDED
    head = git(origin, "rev-parse", "master")
    assert git(wt, "merge-base", "--is-ancestor", git(wt, "rev-parse", "HEAD"), head) == ""
    changed = git(origin, "diff-tree", "--no-commit-id", "--name-only", "-r", head)
    assert changed.split() == ["game/legacy.cpp"]         # exactly the competitor source
    message = git(origin, "log", "-1", "--format=%B", head)
    assert "check PASS; Functions: OK 2/2" in message
    assert "Model: script/provider_repair" in message
    assert "Claim-Lease: 0x00000100=" in message
    claims.active.cache_clear()
    assert claims.active(wt) == {}                        # released by its lease


def test_a_pass_that_cannot_be_pushed_keeps_its_patch_in_the_worktree(seat, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    monkeypatch.setattr(ps, "PUSH_ATTEMPTS", 1)
    real_git = ps.git

    def refusing(cwd, *args, check=False):
        if args[:1] == ("push",):
            return subprocess.CompletedProcess(args, 1, "", "rejected")
        return real_git(cwd, *args, check=check)
    monkeypatch.setattr(ps, "git", refusing)
    before = git(origin, "rev-parse", "master")
    assert ps.once(wt) == ps.UNPUSHED
    assert (wt / "build/provider_seat/unpushed/0x00000100.patch").read_bytes()
    assert git(origin, "rev-parse", "master") == before
    assert git(wt, "status", "--porcelain") == ""


def test_the_lane_exists_and_is_off_by_default():
    launch = (TOOLS / "fleet" / "launch_fleet.sh").read_text(encoding="utf-8")
    seat_sh = (TOOLS / "fleet" / "seat.sh").read_text(encoding="utf-8")
    assert "P=${10:-0}" in launch and 'launch provider "$i"' in launch
    assert 'if [ "$ENGINE" = provider ]; then' in seat_sh
    assert "tools/fleet/provider_seat.py" in seat_sh and "FLEET_DRY_PAUSE" in seat_sh


def _peer(origin, tmp_path):
    peer = tmp_path / "peer"
    git(tmp_path, "clone", "-q", str(origin), str(peer))
    for key, value in (("user.name", "peer"), ("user.email", "peer@example.com"),
                       ("core.hooksPath", "no-hooks")):
        git(peer, "config", key, value)
    return peer


def _after_first_check(monkeypatch, action):
    real = ps.tool
    done = []

    def tool(wt, *args):
        got = real(wt, *args)
        if args[0] == "check" and got.returncode == 0 and not done:
            done.append(1)
            action()
        return got
    monkeypatch.setattr(ps, "tool", tool)


def test_a_rebase_that_changes_the_owner_is_checked_again_and_refused(seat, tmp_path, monkeypatch):
    # review 2026-09-30 (test_adversarial.py): an owner-source change arrived in
    # the rebase after `check`, and the seat pushed on the stale receipt.
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    peer = _peer(origin, tmp_path)

    def concurrent_owner_change():
        (peer / "game/owner.cpp").write_text("void Legacy::f() { /* wrong linked provider */ }\n")
        git(peer, "commit", "-q", "-am", "concurrent owner change")
        git(peer, "push", "-q", "origin", "HEAD:master")
    _after_first_check(monkeypatch, concurrent_owner_change)
    assert ps.once(wt) == ps.FAILED
    assert (wt / "checks.txt").read_text().count("check") == 2          # checked again
    head = git(origin, "rev-parse", "master")
    assert git(origin, "log", "-1", "--format=%s", head) == "concurrent owner change"
    assert "check FAIL after rebase" in (wt / "abandoned.txt").read_text()
    assert git(wt, "status", "--porcelain") == ""
    assert (wt / "game/legacy.cpp").read_text().startswith("void Legacy::f()")


def test_an_unrelated_upstream_change_needs_no_second_check(seat, tmp_path, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    peer = _peer(origin, tmp_path)

    def unrelated():
        (peer / "notes.txt").write_text("unrelated\n")
        git(peer, "add", "notes.txt")
        git(peer, "commit", "-q", "-m", "unrelated")
        git(peer, "push", "-q", "origin", "HEAD:master")
    _after_first_check(monkeypatch, unrelated)
    assert ps.once(wt) == ps.LANDED
    assert (wt / "checks.txt").read_text().count("check") == 1


def test_an_upstream_header_change_forces_a_second_check(seat, tmp_path, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    peer = _peer(origin, tmp_path)

    def header():
        (peer / "game/legacy.h").write_text("struct Legacy;\n")
        git(peer, "add", "game/legacy.h")
        git(peer, "commit", "-q", "-m", "header")
        git(peer, "push", "-q", "origin", "HEAD:master")
    _after_first_check(monkeypatch, header)
    assert ps.once(wt) == ps.LANDED
    assert (wt / "checks.txt").read_text().count("check") == 2


def test_a_claim_lost_before_the_push_publishes_nothing(seat, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "pass")
    before = git(origin, "rev-parse", "master")

    def taken_over():
        claims.release([0x100], force=True, root=wt)
        monkeypatch.setenv("BFME_CLAIM_OWNER", "rival")
        claims.claim([0x100], root=wt)
        monkeypatch.setenv("BFME_CLAIM_OWNER", "provider-seat-1")
    _after_first_check(monkeypatch, taken_over)
    assert ps.once(wt) == ps.FAILED
    assert git(origin, "rev-parse", "master") == before
    assert git(wt, "status", "--porcelain") == ""
    assert not (wt / "abandoned.txt").exists()          # not a verdict: someone else owns it


def test_no_lease_means_no_landing(seat, monkeypatch):
    wt, origin = seat
    monkeypatch.setenv("FAKE_MODE", "noclaim")
    before = git(origin, "rev-parse", "master")
    assert ps.once(wt) == ps.FAILED
    assert git(origin, "rev-parse", "master") == before
