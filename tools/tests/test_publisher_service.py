"""Publisher rollout: the pre-push step in each mode against a local bare
remote, shadow submission failure never blocking a push, and the service
draining a queue end to end into the local mirror (shadow) or origin (enforce)."""
import json
import os
import subprocess
import sys
import time
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import publisher_hook as hook  # noqa: E402
import publisher_service as svc  # noqa: E402

ROOT = TOOLS.parent
MODE_FILE = next(m for m in hook.MODE_FILES if (ROOT / m).exists())
HOOK_LINE = next(line for line in (ROOT / ".githooks" / "pre-push").read_text().splitlines()
                 if "publisher_hook.py pre-push" in line)
# the repository's pre-push reduced to a local check (red on a bad* file), then
# the publisher line exactly as the real hook carries it
FAKE_HOOK = """#!/usr/bin/env bash
set -euo pipefail
refs="$(cat || true)"
while read -r _l local_sha _r remote_sha; do
    [ -z "${local_sha:-}" ] && continue
    case "$_r" in refs/submit/*) continue ;; esac
    if git diff --name-only "$remote_sha" "$local_sha" | grep -q '^bad'; then
        echo "PRE-PUSH FAILED: bad file"; exit 1
    fi
done <<< "$refs"
""" + HOOK_LINE + "\n"


def git(cwd, *args, check=True):
    got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True)
    if check and got.returncode:
        raise RuntimeError(got.stderr)
    return got.stdout.strip() if check else got


class World:
    def __init__(self, tmp, mode):
        self.tmp = tmp
        self.origin = tmp / "origin.git"
        git(tmp, "init", "-q", "--bare", "-b", "master", str(self.origin))
        self.seat = tmp / "seat"
        git(tmp, "init", "-q", "-b", "master", str(self.seat))
        for k, v in (("user.name", "Seat One"), ("user.email", ""),
                     ("core.hooksPath", ".githooks")):
            git(self.seat, "config", k, v)
        git(self.seat, "remote", "add", "origin", str(self.origin))
        (self.seat / "tools").mkdir()
        for tool in ("publisher.py", "publisher_hook.py", "publisher_gate.py", "publisher_service.py"):
            (self.seat / "tools" / tool).write_bytes((TOOLS / tool).read_bytes())
        (self.seat / ".githooks").mkdir()
        (self.seat / ".githooks" / "pre-push").write_text(FAKE_HOOK, newline="\n")
        (self.seat / MODE_FILE).parent.mkdir(parents=True, exist_ok=True)
        (self.seat / MODE_FILE).write_text(mode + "\n")
        (self.seat / "a.txt").write_text("base\n")
        git(self.seat, "add", "-A")
        git(self.seat, "commit", "-q", "-m", "base")
        git(self.seat, "push", "-q", "--no-verify", "origin", "HEAD:refs/heads/master")
        git(self.seat, "fetch", "-q", "origin")

    def commit(self, name, text="x\n"):
        (self.seat / name).write_text(text)
        git(self.seat, "add", "-A")
        git(self.seat, "commit", "-q", "-m", f"add {name}")
        return git(self.seat, "rev-parse", "HEAD")

    def push(self):
        started = time.time()
        got = git(self.seat, "push", "origin", "HEAD:master", check=False)
        return got, time.time() - started

    def master(self):
        return git(self.origin, "rev-parse", "refs/heads/master")

    def submit_refs(self, wait=0.0, at_least=1):
        deadline = time.time() + wait
        while True:
            refs = git(self.origin, "for-each-ref", "--format=%(refname)", "refs/submit/").split()
            if len(refs) >= at_least or time.time() >= deadline:
                return refs
            time.sleep(0.25)

    def service(self, builders=2):
        state = svc.setup(self.tmp / "pstate", "t", str(self.origin), str(self.seat),
                          "origin/master", builders, checker_paths=["tools", ".githooks"],
                          host_lock=self.tmp / "host.lock")
        return svc.Service(state)


def queued_unit(stderr):
    return stderr.split("PUBLISHER-QUEUED ")[1].split()[0]


def test_off_mode_is_a_plain_push(tmp_path):
    w = World(tmp_path, "off")
    tip = w.commit("b.txt")
    got, _ = w.push()
    assert got.returncode == 0 and w.master() == tip
    assert w.submit_refs(wait=2) == []


def test_shadow_push_lands_then_the_range_is_submitted(tmp_path):
    w = World(tmp_path, "shadow")
    base = w.master()
    tip = w.commit("b.txt")
    got, _ = w.push()
    assert got.returncode == 0 and w.master() == tip
    refs = w.submit_refs(wait=20)
    assert len(refs) == 1 and refs[0].startswith("refs/submit/seat-one/")
    env = json.loads(git(w.origin, "show", f"{refs[0]}:envelope.json"))
    assert env["auth"] == hook.AUTH and env["base"] == base and env["tip"] == tip
    import publisher
    assert publisher.verify_mac(bytes.fromhex(hook.unauth_key("seat-one")), env)


def test_shadow_local_gate_failure_submits_nothing(tmp_path):
    w = World(tmp_path, "shadow")
    w.commit("bad.txt")
    got, _ = w.push()
    assert got.returncode != 0 and "PRE-PUSH FAILED" in got.stdout + got.stderr
    assert w.submit_refs(wait=3) == []


def test_shadow_submission_failure_never_blocks_the_push(tmp_path):
    w = World(tmp_path, "shadow")
    (w.origin / "hooks" / "pre-receive").write_text(
        "#!/bin/sh\nwhile read o n r; do case $r in refs/submit/*) "
        "echo no submissions here; exit 1;; esac; done\nexit 0\n", newline="\n")
    tip = w.commit("b.txt")
    got, _ = w.push()
    assert got.returncode == 0 and w.master() == tip
    log = Path(git(w.seat, "rev-parse", "--absolute-git-dir")) / "publisher-hook.log"
    deadline = time.time() + 20
    while time.time() < deadline and "failed" not in (log.read_text() if log.exists() else ""):
        time.sleep(0.25)
    assert "submission of" in log.read_text() and "failed" in log.read_text()
    assert w.submit_refs() == []


def test_shadow_step_returns_within_two_seconds(tmp_path):
    w = World(tmp_path, "shadow")
    base = w.master()
    tip = w.commit("b.txt")
    started = time.time()
    got = subprocess.run([sys.executable, "tools/publisher_hook.py", "pre-push", "origin"],
                         cwd=w.seat, input=f"refs/heads/master {tip} refs/heads/master {base}\n",
                         capture_output=True, text=True)
    assert got.returncode == 0 and time.time() - started < 2.0


def test_enforce_queues_refuses_and_orders_the_next_push_after(tmp_path):
    w = World(tmp_path, "enforce")
    before = w.master()
    first = w.commit("b.txt")
    got, _ = w.push()
    assert got.returncode != 0 and w.master() == before
    assert "PUBLISHER-QUEUED" in got.stderr and "status" in got.stderr
    unit1 = queued_unit(got.stderr)
    second = w.commit("c.txt")
    got, _ = w.push()
    assert got.returncode != 0 and "PUBLISHER-QUEUED" in got.stderr
    unit2 = queued_unit(got.stderr)
    env2 = json.loads(git(w.origin, "show", f"refs/submit/seat-one/{unit2}:envelope.json"))
    assert env2["after"] == [unit1] and env2["base"] == first and env2["tip"] == second
    patch2 = git(w.origin, "show", f"refs/submit/seat-one/{unit2}:unit.patch")
    assert "c.txt" in patch2 and "b.txt" not in patch2
    got, _ = w.push()                       # nothing new: refused, nothing submitted
    assert got.returncode != 0 and "already queued" in got.stderr
    assert len(w.submit_refs()) == 2


def test_service_drains_shadow_queue_into_the_local_mirror_only(tmp_path):
    w = World(tmp_path, "shadow")
    service = w.service()                   # running before the seats push, as deployed
    for name in ("b.txt", "c.txt", "d.txt"):
        w.commit(name)
        assert w.push()[0].returncode == 0
        w.submit_refs(wait=20, at_least=len(w.submit_refs()) + 1)
    base = w.master()
    tip = w.commit("bad.txt")               # never pushed: a unit the gate must refuse
    cwd = Path.cwd()
    os.chdir(w.seat)
    try:
        hook.submit("origin", "seat-one", base, tip)
    finally:
        os.chdir(cwd)
    assert len(w.submit_refs()) == 4
    origin_refs = git(w.origin, "for-each-ref")
    service.run(until_drained=True, max_seconds=180)
    assert git(w.origin, "for-each-ref") == origin_refs      # nothing written to origin
    files = git(service.mirror, "ls-tree", "--name-only", f"refs/heads/{svc.SHADOW_BRANCH}").split()
    assert {"b.txt", "c.txt", "d.txt"} <= set(files) and "bad.txt" not in files
    rows = svc.read_csv(service.dir / "metrics.csv")
    assert sorted(r["outcome"] for r in rows) == ["landed"] * 3 + ["rejected"]
    assert [r["reason"] for r in rows if r["outcome"] == "rejected"] == ["gate"]
    assert len(git(service.mirror, "show", f"{hook.RESULTS_REF}:results.jsonl").splitlines()) == 4
    assert "seat-one" in json.loads((service.dir / "config.json").read_text())["operators"]


def test_service_in_enforce_lands_on_origin_and_reports(tmp_path):
    w = World(tmp_path, "enforce")
    w.commit("b.txt")
    got, _ = w.push()
    unit = queued_unit(got.stderr)
    service = w.service()
    service.run(until_drained=True, max_seconds=180)
    assert "b.txt" in git(w.origin, "ls-tree", "--name-only", "refs/heads/master").split()
    assert w.submit_refs() == []                              # ingested refs deleted
    got = subprocess.run([sys.executable, "tools/publisher_hook.py", "status", unit],
                         cwd=w.seat, capture_output=True, text=True)
    assert json.loads(got.stdout)["state"] == "landed", got.stdout + got.stderr


def test_health_go_and_no_go(tmp_path):
    now = time.time()
    rows = [dict(time=svc.now_iso(now - 3600 + i * 30), unit=f"u{i}", operator="a",
                 outcome="landed", reason="", latency_s=300, queue_depth=1, inflight=1,
                 builders_busy=1, red_rate_100=0, target="shadow") for i in range(119)]
    svc.append_csv(tmp_path / "metrics.csv", svc.METRIC_FIELDS, rows)
    ticks = [dict(time=svc.now_iso(now - 3599 + m * 60), target="shadow", queue=2, inflight=1,
                  builders_busy=1, enqueued_total=0, finished_total=0, submit_refs_pending=0)
             for m in range(60)]
    svc.append_csv(tmp_path / "queue.csv", svc.QUEUE_FIELDS, ticks)
    report = svc.health(tmp_path, hours=1, now=now)
    assert report["go"], report
    slow = [dict(r, unit=r["unit"] + "s", latency_s=7200) for r in rows]
    svc.append_csv(tmp_path / "metrics.csv", svc.METRIC_FIELDS, slow)
    report = svc.health(tmp_path, hours=1, now=now)
    assert not report["go"] and not report["checks"]["p95_latency"]["ok"]
