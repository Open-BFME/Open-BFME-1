"""The cooperative publish window, reusable gate evidence, and multi-commit
landing units (linking_plan.md workstream G; header-wide landings)."""
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "tests"))

import gate_evidence  # noqa: E402
import publish_window as pw  # noqa: E402
from test_landing_service import world, git, origin_files  # noqa: E402,F401


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True,
                          text=True).stdout.strip()


@pytest.fixture
def clones(tmp_path, monkeypatch):
    monkeypatch.delenv(pw.TOKEN_ENV, raising=False)
    origin = tmp_path / "origin.git"
    _git(tmp_path, "init", "-q", "--bare", str(origin))
    out = {}
    for name in ("service", "seat"):
        clone = tmp_path / name
        _git(tmp_path, "init", "-q", str(clone))
        _git(clone, "remote", "add", "origin", str(origin))
        _git(clone, "config", "user.name", name)
        _git(clone, "config", "user.email", f"{name}@example.com")
        _git(clone, "config", "core.hooksPath", "no-hooks")
        assert Path(_git(clone, "remote", "get-url", "origin")) == origin   # never the real origin
        out[name] = clone
    out["origin"] = origin
    return out


def test_one_holder_at_a_time_and_its_own_pushes_pass(clones, monkeypatch):
    token = pw.open_window(30, purpose="header stack", owner="svc", root=clones["service"])
    with pytest.raises(pw.WindowHeld):
        pw.open_window(30, owner="rival", root=clones["seat"])
    allowed, why = pw.check(root=clones["seat"])
    assert not allowed and "svc" in why and "header stack" in why
    monkeypatch.setenv(pw.TOKEN_ENV, token)
    assert pw.check(root=clones["seat"])[0]
    monkeypatch.delenv(pw.TOKEN_ENV)
    assert not pw.close_window("not-the-token", root=clones["seat"])
    assert pw.close_window(token, root=clones["service"])
    assert pw.check(root=clones["seat"]) == (True, "")


def test_an_expired_window_is_taken_over_and_blocks_nothing(clones):
    pw.open_window(-1, owner="crashed", root=clones["service"])
    assert pw.check(root=clones["seat"]) == (True, "")
    token = pw.open_window(30, owner="next", root=clones["seat"])
    assert pw.read(root=clones["service"])[0] == token


def test_an_unreachable_origin_does_not_block_pushes(clones):
    _git(clones["seat"], "remote", "set-url", "origin", str(clones["origin"].parent / "gone.git"))
    allowed, why = pw.check(root=clones["seat"])
    assert allowed and "not checking" in why


def test_the_pre_push_hook_refuses_master_while_someone_else_holds_the_window(clones, monkeypatch):
    seat = clones["seat"]
    (seat / "tools").mkdir()
    shutil.copy(TOOLS / "publish_window.py", seat / "tools" / "publish_window.py")
    token = pw.open_window(30, purpose="header stack", owner="svc", root=clones["service"])
    hook = REPO / ".githooks" / "pre-push"
    line = "refs/heads/master " + "1" * 40 + " refs/heads/master " + "0" * 40 + "\n"

    def run(env_token=None):
        env = {k: v for k, v in os.environ.items() if k != pw.TOKEN_ENV}
        if env_token:
            env[pw.TOKEN_ENV] = env_token
        return subprocess.run(["bash", str(hook), "origin", str(clones["origin"])], cwd=seat,
                              env=env, input=line, capture_output=True, text=True)
    blocked = run()
    assert blocked.returncode != 0 and "publish window" in blocked.stderr
    held = run(token)               # the holder gets past the window (and fails later, on the fake sha)
    assert "publish window held" not in held.stderr and "unavailable" in held.stderr
    other_ref = subprocess.run(["bash", str(hook), "origin", "x"], cwd=seat, input=line.replace(
        "refs/heads/master", "refs/heads/topic"), capture_output=True, text=True)
    assert "publish window" not in other_ref.stderr
    window_ref = subprocess.run(["bash", str(hook), "origin", "x"], cwd=seat, input=line.replace(
        "refs/heads/master", pw.REF), capture_output=True, text=True)
    assert window_ref.returncode == 0          # the lock marker itself is not gated


def test_gate_evidence_is_opt_in_exact_tree_and_full_covers_scoped(clones, monkeypatch):
    seat = clones["seat"]
    (seat / "a.txt").write_text("a\n")
    _git(seat, "add", "a.txt")
    _git(seat, "commit", "-q", "-m", "a")
    first = _git(seat, "rev-parse", "HEAD")
    gate_evidence.record(first, "full", root=seat)
    monkeypatch.delenv(gate_evidence.ENABLE, raising=False)
    assert not gate_evidence.reusable(first, "full", root=seat)[0]          # opt-in only
    monkeypatch.setenv(gate_evidence.ENABLE, "1")
    assert gate_evidence.reusable(first, "full", root=seat)[0]
    assert gate_evidence.reusable(first, "scoped", root=seat)[0]            # full covers scoped
    (seat / "a.txt").write_text("b\n")
    _git(seat, "commit", "-q", "-am", "b")
    assert not gate_evidence.reusable("HEAD", "full", root=seat)[0]        # a different tree
    _git(seat, "commit", "-q", "--allow-empty", "-m", "same tree")
    gate_evidence.record("HEAD", "scoped", root=seat)
    assert not gate_evidence.reusable("HEAD", "full", root=seat)[0]        # scoped never covers full


def test_a_multi_commit_unit_lands_whole_under_the_window(world, monkeypatch):
    service, unit, origin = world
    monkeypatch.delenv(pw.TOKEN_ENV, raising=False)
    seat = service.repo.parent / "seat"
    git(seat, "fetch", "-q", "origin", "master")
    git(seat, "reset", "-q", "--hard", "FETCH_HEAD")
    base = git(seat, "rev-parse", "HEAD")
    for name in ("header.h", "user.cpp"):
        (seat / name).write_text(name + "\n")
        git(seat, "add", name)
        git(seat, "commit", "-q", "-m", f"{name}\n\nVerifier-Change: none, fixture")
    stack = seat.parent / "stack.patch"
    stack.write_bytes(subprocess.run(["git", "format-patch", "--stdout", f"{base}..HEAD"], cwd=seat,
                                     check=True, capture_output=True).stdout)
    uid = service.enqueue(stack)
    seen = []
    real_gate = service._gate

    def gate(base_sha, tip):
        # while the service gates, anybody else's push to master is refused
        saved = os.environ.pop(pw.TOKEN_ENV)
        seen.append(pw.check(root=seat)[0])
        os.environ[pw.TOKEN_ENV] = saved
        assert os.environ.get(gate_evidence.ENABLE) == "1"
        return real_gate(base_sha, tip)
    service._gate = gate
    result = service.run_once(window=True)
    assert result["landed"] == [uid] and seen == [False]
    assert {"header.h", "user.cpp"} <= set(origin_files(origin))
    receipt = json.loads((service.state / "receipts" / f"{uid}.json").read_text())
    assert len(receipt["commits"]) == 2 and receipt["commit"] == receipt["commits"][-1]
    assert pw.read(root=service.repo) == (None, None)                     # closed afterwards
    assert pw.TOKEN_ENV not in os.environ
