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
    assert pw.read(root=clones["service"])[1]["nonce"] == token


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
    gate_evidence.record("HEAD", "scoped", root=seat, selectors=["game/a.cpp"], base=first)
    assert not gate_evidence.reusable("HEAD", "full", root=seat)[0]        # scoped never covers full
    assert gate_evidence.reusable("HEAD", "scoped", root=seat, selectors=["game/a.cpp"])[0]
    assert not gate_evidence.reusable("HEAD", "scoped", root=seat,
                                      selectors=["game/a.cpp", "game/b.cpp"])[0]
    assert not gate_evidence.reusable("HEAD", "scoped", root=seat)[0]       # scope must be named


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


# ---- 2026-09-30 review (review_20260930_0251.md) ----

def test_a_narrow_scoped_record_never_skips_a_wider_gate(tmp_path):
    # review_five_probes.py: the same tip pushed onto an older base changes two
    # headers instead of one; the narrow record from the first push let the
    # wider gate (which fails on b.cpp) be skipped.
    repo = tmp_path / "repo"
    _git(tmp_path, "init", "-q", str(repo))
    for key, value in (("user.name", "t"), ("user.email", "t@example.com"), ("core.hooksPath", "no-hooks")):
        _git(repo, "config", key, value)
    for sub_dir in ("tools", ".githooks", "game", "targets/game/reverse"):
        (repo / sub_dir).mkdir(parents=True)
    (repo / "targets/game/reverse/functions.csv").write_text("name,source,status\n")
    shutil.copy(REPO / ".githooks" / "pre-push", repo / ".githooks" / "pre-push")
    shutil.copy(TOOLS / "gate_evidence.py", repo / "tools" / "gate_evidence.py")
    for name in ("check_csv", "one_identity", "target_hooks", "conversion_gate", "name_regression",
                 "name_history", "name_oracle", "retired_guard", "doc_budget", "ea_name_guard",
                 "pin_consistency", "b_pin_check", "delta_sources", "protected_paths"):
        (repo / f"tools/{name}.py").write_text("import sys\nsys.exit(0)\n")
    (repo / "tools/layout_migration.py").write_text("import sys\nsys.exit(1)\n")
    (repo / "tools/header_dependents.py").write_text(
        "import subprocess,sys\n"
        "paths=subprocess.check_output(['git','diff','--name-only',sys.argv[2],sys.argv[3],'--','game'])"
        ".decode().splitlines()\n"
        "for p in paths:\n if p.endswith('.h'): print(p[:-2]+'.cpp')\n")
    (repo / "build.sh").write_text('#!/usr/bin/env bash\nprintf "%s\\n" "$@" >> gate_calls.txt\n'
                                   'case "$*" in *b.cpp*) exit 1;; esac\n')
    (repo / "game/a.h").write_text("old\n")
    (repo / "game/b.h").write_text("old\n")
    _git(repo, "add", "--", ".githooks", "tools", "build.sh", "game", "targets")
    _git(repo, "update-index", "--chmod=+x", "build.sh")
    _git(repo, "commit", "-q", "-m", "initial")
    older = _git(repo, "rev-parse", "HEAD")
    (repo / "game/b.h").write_text("bad b\n")
    _git(repo, "commit", "-q", "-am", "header b")
    newer = _git(repo, "rev-parse", "HEAD")
    (repo / "game/a.h").write_text("new a\n")
    _git(repo, "commit", "-q", "-am", "header a")
    tip = _git(repo, "rev-parse", "HEAD")

    def hook(base, reuse=True):
        env = {k: v for k, v in os.environ.items() if k != gate_evidence.ENABLE}
        if reuse:
            env[gate_evidence.ENABLE] = "1"
        return subprocess.run(["bash", ".githooks/pre-push", "origin", "unused"], cwd=repo, env=env,
                              input=f"refs/heads/topic {tip} refs/heads/topic {base}\n",
                              capture_output=True, text=True)
    assert hook(newer).returncode == 0                  # narrow: only a.cpp, green, recorded
    assert hook(older).returncode != 0                  # wider: b.cpp is red, reuse must not hide it
    assert hook(older, reuse=False).returncode != 0
    again = hook(newer)                                  # no reuse any more: it gates again
    assert again.returncode == 0 and "REUSING" not in again.stderr


def test_closing_someone_elses_window_needs_the_token_or_an_explicit_force(clones):
    token = pw.open_window(30, owner="holder", purpose="stack", root=clones["service"])
    assert not pw.close_window(root=clones["seat"])                     # tokenless: refused
    assert not pw.close_window("wrong", root=clones["seat"])
    assert pw.read(root=clones["service"])[1]["nonce"] == token
    assert pw.close_window(force=True, root=clones["seat"])             # explicit, logged
    log = Path(_git(clones["seat"], "rev-parse", "--absolute-git-dir")) / "bfme-window-forced.log"
    assert "forced close" in log.read_text() and "holder" in log.read_text()
    assert pw.read(root=clones["service"]) == (None, None)


# ---- short renewable lease (owner request 2026-09-30) ----

def test_a_window_is_a_short_lease_its_holder_renews(clones, monkeypatch):
    assert pw.LEASE_MINUTES <= 10
    nonce = pw.open_window(owner="drainer", root=clones["service"])
    token, info = pw.read(root=clones["service"])
    assert info["expires"] - info["opened"] <= pw.LEASE_MINUTES * 60
    expires = pw.renew_window(nonce, 5, root=clones["service"])
    new_token, info = pw.read(root=clones["service"])
    assert expires and new_token != token and info["nonce"] == nonce
    monkeypatch.setenv(pw.TOKEN_ENV, nonce)                  # the holder's pushes still pass
    assert pw.check(root=clones["seat"])[0]
    monkeypatch.delenv(pw.TOKEN_ENV)
    assert pw.renew_window("not-ours", 5, root=clones["seat"]) is None
    assert pw.close_window(nonce, root=clones["service"])


def test_a_dead_holder_blocks_only_until_its_short_lease_expires(clones):
    pw.open_window(-0.01, owner="crashed drainer", root=clones["service"])   # never renewed
    assert pw.check(root=clones["seat"]) == (True, "")


def test_the_drainer_renews_while_working_closes_and_logs_its_hold(world, monkeypatch):
    service, unit, origin = world
    monkeypatch.delenv(pw.TOKEN_ENV, raising=False)
    uid = service.enqueue(unit("renewed_window"))
    real_gate = service._gate
    renewals = []
    real_renew = pw.renew_window

    def counting(*args, **kwargs):
        renewals.append(1)
        return real_renew(*args, **kwargs)
    monkeypatch.setattr(pw, "renew_window", counting)

    def slow_gate(base, tip):
        import time
        time.sleep(4)                                       # longer than a renewal interval
        return real_gate(base, tip)
    service._gate = slow_gate
    result = service.run_once(window=True, window_minutes=0.05)     # 3 s lease, renew each 1 s
    assert result["landed"] == [uid] and renewals and "window_lost" not in result
    assert result["window_held_seconds"] > 0
    assert pw.read(root=service.repo) == (None, None)
    logged = json.loads((service.state / "windows.log").read_text().splitlines()[-1])
    assert logged["held"] == result["window_held_seconds"] and logged["landed"] == 1


def test_the_window_closes_even_when_the_pass_fails(world, monkeypatch):
    service, unit, origin = world
    monkeypatch.delenv(pw.TOKEN_ENV, raising=False)
    service.enqueue(unit("boom"))

    def boom(*args, **kwargs):
        raise RuntimeError("gate host fell over")
    service._gate = boom
    with pytest.raises(RuntimeError):
        service.run_once(window=True)
    assert pw.read(root=service.repo) == (None, None)


def test_no_new_pass_starts_after_the_hold_cap(world, monkeypatch):
    service, unit, origin = world
    monkeypatch.delenv(pw.TOKEN_ENV, raising=False)
    uid = service.enqueue(unit("capped"))
    result = service.run_once(window=True, max_hold=-1)       # cap already reached
    assert result["landed"] == [] and result["deferred"] == [uid]
    assert [r["id"] for r in service.queued()] == [uid]       # stays queued
    assert pw.read(root=service.repo) == (None, None)


def test_an_ignored_included_input_that_changes_is_caught_by_the_next_push(tmp_path):
    # Review cycle 6/7: the reverted ordinary-path reuse (6089f82afc) let a push
    # skip byte verification after an ignored, #included file changed. Kept as
    # a permanent guard: even with BFME_REUSE_GATE_EVIDENCE=1 the ordinary
    # pre-push path byte-verifies every push, so the change fails the gate.
    repo = tmp_path / "repo"
    _git(tmp_path, "init", "-q", str(repo))
    for key, value in (("user.name", "t"), ("user.email", "t@example.com"), ("core.hooksPath", "no-hooks")):
        _git(repo, "config", key, value)
    for sub_dir in ("tools", ".githooks", "game", "targets/game/reverse"):
        (repo / sub_dir).mkdir(parents=True)
    (repo / "targets/game/reverse/functions.csv").write_text("name,source,status\nf,game/a.cpp,matched\n")
    shutil.copy(REPO / ".githooks" / "pre-push", repo / ".githooks" / "pre-push")
    shutil.copy(TOOLS / "gate_evidence.py", repo / "tools" / "gate_evidence.py")
    for name in ("check_csv", "one_identity", "target_hooks", "conversion_gate", "name_regression",
                 "name_history", "name_oracle", "retired_guard", "doc_budget", "ea_name_guard",
                 "pin_consistency", "b_pin_check", "delta_sources", "header_dependents"):
        (repo / f"tools/{name}.py").write_text("import sys\nsys.exit(0)\n")
    (repo / "tools/layout_migration.py").write_text("import sys\nsys.exit(1)\n")
    (repo / "tools/verification_cache.py").write_text(
        "import sys\nargs = sys.argv\n"
        "if 'prepare' in args:\n    print(open(args[args.index('--selectors-file') + 1]).read(), end='')\n")
    (repo / "build.sh").write_text("#!/usr/bin/env bash\ngrep -q bad game/generated.h && exit 1\nexit 0\n")
    (repo / ".gitignore").write_text("game/generated.h\n")
    (repo / "game/generated.h").write_text("good\n")
    (repo / "game/a.cpp").write_text('#include "generated.h"\nint a;\n')
    _git(repo, "add", ".")
    _git(repo, "update-index", "--chmod=+x", "build.sh")
    _git(repo, "commit", "-q", "-m", "base")
    base = _git(repo, "rev-parse", "HEAD")
    (repo / "game/a.cpp").write_text('#include "generated.h"\nint a = 1;\n')
    _git(repo, "commit", "-q", "-am", "change")
    tip = _git(repo, "rev-parse", "HEAD")

    def hook():
        env = dict(os.environ, **{gate_evidence.ENABLE: "1"})
        return subprocess.run(["bash", ".githooks/pre-push", "origin", "unused"], cwd=repo, env=env,
                              input=f"refs/heads/topic {tip} refs/heads/topic {base}\n",
                              capture_output=True, text=True)
    assert hook().returncode == 0
    (repo / "game/generated.h").write_text("bad\n")          # ignored, included, changed
    again = hook()
    assert again.returncode != 0 and "reused" not in again.stdout
