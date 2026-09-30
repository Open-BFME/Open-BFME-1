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
    print("  brief       build/provider_repair/0x00000100/brief.json"); sys.exit(0)
if cmd == "apply":
    (ROOT / "game/legacy.cpp").write_text("// Retail f is implemented in owner.cpp.\n"); sys.exit(0)
if cmd == "check":
    if mode == "fail":
        print("FAIL: byte gate: Functions: FAIL 1/2"); sys.exit(1)
    (d / "receipt.json").write_text(json.dumps({"pass": True, "steps": {"gate": {"result": "Functions: OK 2/2"}}}))
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
    (wt / ".gitignore").write_text("build/\nabandoned.txt\n")
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
    got = claims.claim([0x100], root=wt)                  # what provider_repair next does
    assert got.claimed == [0x100]
    assert ps.once(wt) == ps.LANDED
    head = git(origin, "rev-parse", "master")
    assert git(wt, "merge-base", "--is-ancestor", git(wt, "rev-parse", "HEAD"), head) == ""
    changed = git(origin, "diff-tree", "--no-commit-id", "--name-only", "-r", head)
    assert changed.split() == ["game/legacy.cpp"]         # exactly the competitor source
    message = git(origin, "log", "-1", "--format=%B", head)
    assert "check PASS; Functions: OK 2/2" in message
    assert "Model: script/provider_repair" in message
    assert f"Claim-Lease: 0x00000100={got.leases[0x100]}" in message
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
