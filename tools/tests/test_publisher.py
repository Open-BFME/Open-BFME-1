"""The publisher: pinned checker, isolated builder, receipted fast-forwards,
crash recovery, bisect and blame, fairness and the submission path."""
import json
import os
import subprocess
import sys
import threading
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import landing_service as ls  # noqa: E402
import publisher as pub  # noqa: E402
import publisher_load as load  # noqa: E402

TOOLS = Path(__file__).resolve().parents[1]
GATE_SH = """#!/bin/bash
# red when the change adds a file named bad*; names it for the publisher
bad=$(git diff --name-only "$LANDING_BASE" "$LANDING_TIP" | grep '^bad' || true)
if [ -n "$bad" ]; then echo "$bad" | sed 's/^/PUBLISHER-BLAME: /'; exit 1; fi
exit 0
"""


def git(cwd, *args, input=None, env=None, check=True):
    got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True, input=input,
                         env=env)
    if check and got.returncode:
        raise RuntimeError(got.stderr)
    return got.stdout.strip() if check else got


class World:
    def __init__(self, tmp, builders=2, **cfg):
        self.tmp = tmp
        self.origin = tmp / "origin.git"
        git(tmp, "init", "-q", "--bare", str(self.origin))
        self.seat = tmp / "seat"
        git(tmp, "init", "-q", str(self.seat))
        for k, v in (("user.name", "seat"), ("user.email", ""), ("core.hooksPath", "no-hooks")):
            git(self.seat, "config", k, v)
        (self.seat / "checker").mkdir()
        (self.seat / "checker" / "gate.sh").write_text(GATE_SH, newline="\n")
        (self.seat / "a.txt").write_text("base\n")
        git(self.seat, "add", "-A")
        git(self.seat, "commit", "-q", "-m", "base")
        git(self.seat, "push", "-q", str(self.origin), "HEAD:refs/heads/master")
        self.base = git(self.seat, "rev-parse", "HEAD")
        self.state = tmp / "state"
        self.inbox = tmp / "inbox"
        settings = dict(checker_paths=["checker"], gate="bash checker/gate.sh",
                        inbox=str(self.inbox), poll_seconds=0.2, builders=builders, clean_keep=[])
        settings.update(cfg)
        pub.main(["init", "--state", str(self.state), "--target", str(self.origin),
                  *[a for k, v in settings.items() for a in ("--set", f"{k}={json.dumps(v)}")]])
        for name in ("opA", "opB"):
            pub.main(["operator", "--state", str(self.state), name])
        ok, report = pub.promote(self.state, self.base)
        assert ok, report

    def key(self, op):
        return self.state / "operators" / f"{op}.key"

    def commit(self, files, message="unit"):
        """A commit on the current origin master (the operator's clone)."""
        git(self.seat, "fetch", "-q", str(self.origin), "master")
        git(self.seat, "reset", "-q", "--hard", "FETCH_HEAD")
        for path, text in files.items():
            (self.seat / path).parent.mkdir(parents=True, exist_ok=True)
            (self.seat / path).write_text(text, newline="\n")
        git(self.seat, "add", "-A")
        git(self.seat, "commit", "-q", "-m", message)
        return git(self.seat, "rev-parse", "HEAD")

    def submit(self, files, op="opA", **kw):
        kw.setdefault("scope", list(files))
        self.commit(files)
        return pub.submit(self.seat, op, self.key(op), "HEAD~1..HEAD", inbox=self.inbox, **kw)

    def publisher(self, **kw):
        return pub.Publisher(pub.State(self.state), **kw)

    def master(self):
        return git(self.origin, "rev-parse", "master")

    def files(self):
        return sorted(git(self.origin, "ls-tree", "-r", "--name-only", "master").split())


def settle(publisher, limit=180):
    stop = threading.Event()
    timer = threading.Timer(limit, stop.set)
    timer.start()
    try:
        return pub.drain(publisher, once=True, stop=stop)
    finally:
        timer.cancel()


def where(world, unit):
    for state in ("landed", "rejected", "queue"):
        path = world.state / state / f"{unit}.json"
        if path.exists():
            return state, json.loads(path.read_text())
    return None, None


@pytest.fixture
def world(tmp_path):
    return World(tmp_path)


# ---- the pinned checker ------------------------------------------------
def test_candidate_weakening_its_own_checker_is_not_published(world, tmp_path):
    weak = {"checker/gate.sh": "#!/bin/bash\nexit 0\n", "bad_exploit.txt": "x\n"}
    good = world.submit({"good1.txt": "1\n"})
    exploit = world.submit(weak)
    settle(world.publisher())
    assert where(world, good)[0] == "landed"
    state, record = where(world, exploit)
    assert state == "rejected" and record["reason"] == "gate"
    assert "bad_exploit.txt" not in world.files()
    assert (world.state / "landed" / f"{good}.json").exists()
    # positive control: the legacy service runs the candidate's own gate and lands it
    legacy_origin = tmp_path / "legacy.git"
    git(tmp_path, "clone", "-q", "--bare", str(world.origin), str(legacy_origin))
    svc = tmp_path / "svc"
    git(tmp_path, "init", "-q", str(svc))
    for k, v in (("user.name", "svc"), ("user.email", ""), ("core.hooksPath", "no-hooks")):
        git(svc, "config", k, v)
    git(svc, "remote", "add", "origin", str(legacy_origin))
    service = ls.Service(repo=svc, state=tmp_path / "legacy", gate="bash checker/gate.sh",
                         fence=lambda record: True)
    patch = tmp_path / "exploit.patch"
    patch.write_bytes(subprocess.run(["git", "format-patch", "-1", "--stdout"], cwd=world.seat,
                                     capture_output=True, check=True).stdout)
    unit = service.enqueue(patch)
    assert service.run_once()["landed"] == [unit]
    assert "bad_exploit.txt" in git(legacy_origin, "ls-tree", "--name-only", "master")


def test_builder_is_scrubbed_remoteless_and_ignores_unit_commands(world, monkeypatch):
    cfg = json.loads((world.state / "config.json").read_text())
    cfg["gate"] = ('env; echo "REMOTES:$(git remote)"; echo "HELPER:$(git config credential.helper)"; '
                   'bash checker/gate.sh')
    (world.state / "config.json").write_text(json.dumps(cfg))
    monkeypatch.setenv("GITHUB_TOKEN", "secret-token-xyz")
    monkeypatch.setenv("GIT_ASKPASS", "secret-askpass")
    unit = world.submit({"ok.txt": "1\n"}, extra={"verify": "touch PWNED", "attach": {"x": "y"}})
    settle(world.publisher())
    state, record = where(world, unit)
    assert state == "landed" and "verify" not in record and "attach" not in record
    receipt = json.loads(Path(record["receipt"]).read_text())
    assert pub.verify_mac(pub.State(world.state).receipt_key, receipt)
    assert receipt["tip"] == world.master() == record["tip"]
    assert receipt["base"] == world.base and receipt["verdict"] == "green"
    assert receipt["checker"] == pub.Checkers(pub.State(world.state)).current()
    assert len(receipt["toolchain"]["python"]) == 64
    log = (world.state / "logs" / f"{receipt['tip']}.{receipt['checker'][:12]}.log").read_text()
    assert "secret-token-xyz" not in log and "secret-askpass" not in log
    assert "REMOTES:\n" in log.replace("\r", "") and "HELPER:\n" in log.replace("\r", "")
    assert not list(world.state.rglob("PWNED"))


def test_receipts_are_bound_to_tip_base_checker_and_key(world):
    unit = world.submit({"ok.txt": "1\n"})
    p = world.publisher()
    settle(p)
    record = where(world, unit)[1]
    receipt = json.loads(Path(record["receipt"]).read_text())
    head = world.master()
    batch = pub.Batch([[unit]], receipt["base"], receipt["tip"])
    # it was valid for its base; now the head moved on, so it is not
    assert p.verify_receipt(receipt, batch, receipt["base"]) is None
    assert p.verify_receipt(receipt, batch, head) == "base-is-not-head"
    assert p.verify_receipt(dict(receipt, verdict="red"), batch, receipt["base"]) == "bad-mac"
    forged = pub.signed(os.urandom(32), dict(receipt))
    assert p.verify_receipt(forged, batch, receipt["base"]) == "bad-mac"
    other = pub.Batch([[unit]], receipt["base"], receipt["base"])
    assert p.verify_receipt(receipt, other, receipt["base"]) == "wrong-tip-or-base"


# ---- promotion -----------------------------------------------------------
def test_promotion_runs_exploit_fixtures_and_ledger_comparison(world, tmp_path):
    state = pub.State(world.state)
    first = pub.Checkers(state).current()
    fixtures = tmp_path / "fixtures"
    fixtures.mkdir()

    def fixture(name, files, expect):
        world.commit(files)
        (fixtures / f"{name}.patch").write_bytes(subprocess.run(
            ["git", "format-patch", "-1", "--stdout"], cwd=world.seat, capture_output=True,
            check=True).stdout)
        git(world.seat, "reset", "-q", "--hard", "HEAD~1")
        return dict(patch=f"{name}.patch", expect=expect)
    manifest = [fixture("self_weakening", {"checker/gate.sh": "exit 0\n", "bad1.txt": "x"}, "reject"),
                fixture("plain_bad", {"bad2.txt": "x"}, "reject"),
                fixture("control", {"fine.txt": "x"}, "pass")]
    (fixtures / "fixtures.json").write_text(json.dumps(manifest))
    # a weakened checker version misses the exploit fixtures: never promoted
    weak = world.commit({"checker/gate.sh": "#!/bin/bash\nexit 0\n"})
    git(world.seat, "push", "-q", str(world.origin), "HEAD:refs/heads/checker-weak")
    ok, report = pub.promote(world.state, weak, fixtures)
    assert not ok and pub.Checkers(state).current() == first
    assert [f["ok"] for f in report["fixtures"]] == [False, False, True]
    # a stronger version that also reports one more ledger line: needs the line accepted
    cfg = json.loads((world.state / "config.json").read_text())
    cfg["ledger_cmd"] = "[ ! -f checker/ledger.sh ] || bash checker/ledger.sh"
    (world.state / "config.json").write_text(json.dumps(cfg))
    git(world.seat, "reset", "-q", "--hard", world.base)
    strong = world.commit({"checker/ledger.sh": "echo row-1\necho row-2-newly-flagged\n"})
    git(world.seat, "push", "-q", str(world.origin), "HEAD:refs/heads/checker-strong")
    ok, report = pub.promote(world.state, strong, fixtures)
    assert not ok and report["ledger"]["unaccepted"] == ["+ row-1", "+ row-2-newly-flagged"]
    accept = tmp_path / "accept.txt"
    accept.write_text("+ row-1\n+ row-2-newly-flagged\n")
    ok, report = pub.promote(world.state, strong, fixtures, accept_diff=accept)
    assert ok and all(f["ok"] for f in report["fixtures"])
    digest = pub.Checkers(state).current()
    assert digest != first and len(pub.Checkers(state).index()["history"]) == 2
    # a tampered bundle is refused before it runs
    (world.state / "checkers" / digest / "checker" / "gate.sh").write_text("exit 0\n")
    with pytest.raises(RuntimeError, match="modified"):
        pub.Checkers(state).path(digest)


# ---- direct pushes --------------------------------------------------------
RULESET = """#!/bin/bash
# emulates the admin ruleset: master accepts only the publisher bot
while read -r old new ref; do
    [ "$ref" = refs/heads/master ] || continue
    ok=0
    for ((i = 0; i < ${GIT_PUSH_OPTION_COUNT:-0}; i++)); do
        v="GIT_PUSH_OPTION_$i"; [ "${!v}" = "publisher-bot=s3cret" ] && ok=1
    done
    [ $ok = 1 ] || { echo "master is restricted to the publisher bot"; exit 1; }
done
"""


def test_no_verify_direct_push_is_only_stopped_by_the_admin_ruleset(world):
    """Documents the dependency: without a server-side rule a --no-verify push
    lands (the publisher can only detect it); with the rule it is refused."""
    p = world.publisher()
    settle(p)
    world.commit({"bad_direct.txt": "x"})
    git(world.seat, "push", "-q", "--no-verify", str(world.origin), "HEAD:refs/heads/master")
    assert "bad_direct.txt" in world.files()                 # nothing client-side stops it
    unit = world.submit({"after.txt": "1\n"})
    settle(p)
    events = [json.loads(line) for line in (world.state / "events.jsonl").read_text().splitlines()]
    assert any(e["ev"] == "foreign_push" for e in events)
    assert where(world, unit)[0] == "landed"                  # re-based onto the foreign head
    # with the ruleset: the direct push is refused, the bot's push is accepted
    hook = world.origin / "hooks" / "pre-receive"
    hook.write_text(RULESET, newline="\n")
    git(world.origin, "config", "receive.advertisePushOptions", "true")
    cfg = json.loads((world.state / "config.json").read_text())
    cfg["push_options"] = ["publisher-bot=s3cret"]
    (world.state / "config.json").write_text(json.dumps(cfg))
    world.commit({"bad_direct2.txt": "x"})
    refused = git(world.seat, "push", "--no-verify", str(world.origin), "HEAD:refs/heads/master",
                  check=False)
    assert refused.returncode != 0 and "restricted to the publisher bot" in refused.stderr
    unit = world.submit({"after2.txt": "1\n"})
    settle(world.publisher())
    assert where(world, unit)[0] == "landed" and "bad_direct2.txt" not in world.files()


# ---- crashes ----------------------------------------------------------------
def test_crash_after_the_gate_republishes_the_exact_tip_without_regating(world):
    units = [world.submit({f"c{i}.txt": f"{i}\n"}) for i in range(3)]
    with pytest.raises(pub.Crash):
        settle(world.publisher(crash_at={"before_push"}))
    journal = json.loads((world.state / "journal.json").read_text())
    assert world.master() == world.base and sorted(journal["units"]) == sorted(units)
    p = world.publisher()                                    # restart: recover() runs
    assert not (world.state / "journal.json").exists()
    assert all(where(world, u)[0] == "queue" for u in units)
    settle(p)
    assert p.stats["gates"] == 0 and p.stats["reused"] == 1   # the receipt was for this exact tip
    assert world.master() == journal["tip"]
    assert all(where(world, u)[0] == "landed" for u in units)


def test_crash_after_the_push_settles_once(world):
    units = [world.submit({f"d{i}.txt": f"{i}\n"}) for i in range(2)]
    with pytest.raises(pub.Crash):
        settle(world.publisher(crash_at={"after_push"}))
    journal = json.loads((world.state / "journal.json").read_text())
    assert world.master() == journal["tip"]
    assert all(where(world, u)[0] == "queue" for u in units)
    p = world.publisher()
    assert all(where(world, u)[0] == "landed" for u in units)
    assert all(where(world, u)[1]["tip"] == journal["tip"] for u in units)
    settle(p)
    assert p.stats["gates"] == 0 and world.master() == journal["tip"]


# ---- red units --------------------------------------------------------------
def test_red_unit_is_bisected_out_without_blame(tmp_path):
    w = World(tmp_path, builders=2,
              gate='bash checker/gate.sh | grep -v PUBLISHER-BLAME; exit "${PIPESTATUS[0]}"')
    units = [w.submit({f"{'bad' if i == 3 else 'g'}{i}.txt": f"{i}\n"}) for i in range(6)]
    p = w.publisher()
    settle(p)
    states = [where(w, u)[0] for u in units]
    assert states == ["landed"] * 3 + ["rejected"] + ["landed"] * 2
    assert "bad3.txt" not in w.files() and len(w.files()) == 1 + 1 + 5
    assert p.stats["gates"] <= 12                          # incl. cancelled speculative gates


def test_blamed_unit_is_probed_alone_and_the_rest_lands():
    with_blame = _virtual_red(blame=1.0)
    without = _virtual_red(blame=0.0)
    assert with_blame["landed"] == without["landed"] == 15
    assert with_blame["rejected"] == without["rejected"] == 1
    assert with_blame["gates"] < without["gates"]


def _virtual_red(blame, tmp=None):
    import tempfile
    world = load.VirtualWorld(tempfile.mkdtemp(prefix="pubtest-"), builders=2, blame=blame,
                              jitter=0.0, max_batch=16, target_red_batch=0.99)
    arrivals = [(0.0, "opA", i == 9, {}) for i in range(16)]
    world.run(arrivals, 4 * 3600)
    events = world.events()
    return dict(landed=sum(e["ev"] == "landed" for e in events),
                rejected=sum(e["ev"] == "rejected" for e in events), gates=world.p.stats["gates"])


# ---- fairness -----------------------------------------------------------------
def _flood(tmp_path, rate_a, fair=True):
    world = load.VirtualWorld(tmp_path, builders=2, jitter=0.0, max_batch=10, fair=fair,
                              operators={"opA": dict(rate=rate_a, burst=5), "opB": dict(rate=60)})
    arrivals = [(0.0, "opA", False, {}) for _ in range(200)]
    arrivals += [(60.0 + 300 * k, "opB", False, {}) for k in range(12)]
    world.run(sorted(arrivals, key=lambda a: a[0]), 3 * 3600)
    waits = {}
    for e in world.events():
        if e["ev"] == "landed":
            waits.setdefault(e["operator"], []).append(e["wait"])
    return waits


def test_operator_flood_does_not_starve_another_operator(tmp_path):
    fair = _flood(tmp_path / "fair", rate_a=30)
    fifo = _flood(tmp_path / "fifo", rate_a=30, fair=False)   # positive control: arrival order
    assert len(fair["opB"]) == len(fifo["opB"]) == 12
    assert max(fair["opB"]) < 15 * 60                        # minutes, not the flood's hours
    assert max(fifo["opB"]) > 3 * max(fair["opB"])
    assert len(fair["opA"]) > 100                            # work-conserving: the flood still drains


def test_prerequisites_inherit_priority_and_waiting_ages(tmp_path):
    world = load.VirtualWorld(tmp_path, builders=1, aging_minutes=10)
    sched, now = world.p.sched, world.now
    pre = world.submit("opA", priority=0)
    now[0] = 1.0
    busy = [world.submit("opC", priority=5) for _ in range(4)]
    dep = world.submit("opB", priority=5, after=[pre])
    items, _ = sched.pick(world.p.queue, set(), set(), 2, now[0])
    assert items[0] == [pre]                                   # inherits dep's priority, older
    assert [dep] in items or busy[0] in items[1]
    # aging: a priority-0 unit waiting 60 min outranks fresh priority-5 work
    now[0] = 3600.0
    fresh = [world.submit("opC", priority=5) for _ in range(3)]
    items, _ = sched.pick(world.p.queue, set(busy), set(), 1, now[0])
    assert items == [[pre]]
    assert fresh


def test_bundles_land_or_fail_together_and_dependents_of_rejects_are_rejected(tmp_path):
    world = load.VirtualWorld(tmp_path, builders=2, jitter=0.0)
    b1 = world.submit("opA", bundle="layout")
    b2 = world.submit("opA", bad=True, bundle="layout")
    child = world.submit("opB", after=[b2])
    ok = world.submit("opB")
    world.run([], 3 * 3600)
    done = {e["unit"]: (e["ev"], e.get("reason")) for e in world.events()
            if e["ev"] in ("landed", "rejected")}
    assert done[b1] == done[b2] == ("rejected", "gate")
    assert done[child] == ("rejected", "dependency-rejected")
    assert done[ok] == ("landed", None)


def test_infra_reserve_and_authenticated_operators(tmp_path):
    world = load.VirtualWorld(tmp_path, builders=1, infra_slots=1,
                              operators={"opA": {}, "infra": dict(infra=True)})
    flood = [world.submit("opA", priority=10) for _ in range(30)]
    infra = world.submit("infra", kind="infra")
    sneaky = world.submit("opA", kind="infra")                # not an infra operator
    assert world.p.queue[sneaky]["kind"] == "normal"
    items, _ = world.p.sched.pick(world.p.queue, set(), set(), 4, 1.0)
    assert items[0] == [infra] and [sneaky] not in items and flood
    # identity is the signing key: a forged or unknown signer is not queued
    patch = b"From 0 Mon Sep 17 00:00:00 2001\nx\n"
    digest = __import__("hashlib").sha256(patch).hexdigest()
    forged = pub.signed(b"not-the-key", dict(operator="opA", patch_sha256=digest))
    assert world.p.accept(forged, patch) == (None, "bad-signature")
    stranger = pub.signed(b"k", dict(operator="mallory", patch_sha256=digest))
    assert world.p.accept(stranger, patch) == (None, "unknown-operator")


# ---- submission ---------------------------------------------------------------
def test_submit_over_a_git_remote_and_continuous_drain(world, tmp_path):
    submissions = tmp_path / "submit.git"
    git(tmp_path, "init", "-q", "--bare", str(submissions))
    cfg = json.loads((world.state / "config.json").read_text())
    cfg["submit_remote"] = str(submissions)
    (world.state / "config.json").write_text(json.dumps(cfg))
    p = world.publisher()
    stop = threading.Event()
    drainer = threading.Thread(target=pub.drain, args=(p,), kwargs=dict(stop=stop), daemon=True)
    drainer.start()
    try:
        landed = []
        for i in range(2):                                    # each lands in seconds, not minutes
            git(world.seat, "config", "user.name", "opB")     # the author says opB; the key says opA
            world.commit({f"r{i}.txt": "1\n"})
            unit = pub.submit(world.seat, "opA", world.key("opA"), "HEAD~1..HEAD",
                              remote=str(submissions), scope=[f"r{i}.txt"])
            for _ in range(300):
                if where(world, unit)[0] == "landed":
                    break
                threading.Event().wait(0.1)
            landed.append(where(world, unit))
    finally:
        stop.set()
        drainer.join(timeout=60)
    assert all(state == "landed" and record["operator"] == "opA" for state, record in landed)
    assert git(submissions, "for-each-ref", "refs/submit") == ""   # consumed


def test_pre_push_shim_turns_a_master_push_into_a_submission(world):
    sha = world.commit({"shim.txt": "1\n"})
    env = dict(os.environ, PUBLISHER_OPERATOR="opA", PUBLISHER_KEY_FILE=str(world.key("opA")),
               PUBLISHER_INBOX=str(world.inbox), PUBLISHER_PY=str(TOOLS / "publisher.py"))
    line = f"refs/heads/master {sha} refs/heads/master {world.base}\n"
    got = subprocess.run(["bash", str(TOOLS / "publisher_pre_push.sh"), "origin", "x"],
                         cwd=world.seat, input=line.encode(), capture_output=True, env=env)
    got.stderr = got.stderr.decode()
    assert got.returncode == 1 and "PUBLISHER-SUBMITTED" in got.stderr
    assert len(list(world.inbox.glob("*.env.json"))) == 1
    other = subprocess.run(["bash", str(TOOLS / "publisher_pre_push.sh"), "origin", "x"],
                           cwd=world.seat, input=f"refs/heads/x {sha} refs/heads/topic {'0' * 40}\n",
                           capture_output=True, text=True, env=env)
    assert other.returncode == 0
    settle(world.publisher())
    assert "shim.txt" in world.files()


# ---- scope, diff-vs-scope, retry accounting ------------------------------------
def test_scopes_overlap_on_shared_ledgers_headers_and_globs():
    unit = lambda allow, paths, forbid=(): dict(scope=dict(allow=allow, forbid=list(forbid)),  # noqa: E731
                                                paths=paths)
    ledger = "targets/game/reverse/functions.csv"
    a = unit(["game/a.cpp", ledger], ["game/a.cpp", ledger])
    b = unit(["game/b.cpp", ledger], ["game/b.cpp", ledger])
    c = unit(["game/c.cpp"], ["game/c.cpp"])
    header = unit(["game/include/**"], ["game/include/x.h"])
    user = unit(["game/d.cpp", "game/include/x.h"], ["game/d.cpp", "game/include/x.h"])
    tools = unit(["tools/**", ".githooks/*"], ["tools/build.py"])
    builder = unit(["game/e.cpp", "tools/build.py"], ["game/e.cpp", "tools/build.py"])
    assert pub.scopes_overlap(a, b)                    # the shared ledger is scope
    assert pub.scopes_overlap(header, user) and pub.scopes_overlap(tools, builder)
    assert not pub.scopes_overlap(a, c) and not pub.scopes_overlap(c, header)
    assert pub.in_scope("game/include/y/z.h", header["scope"])
    assert not pub.in_scope("tools/x.py", dict(allow=["**"], forbid=["tools/**"]))


FUNCTIONS = "targets/game/reverse/functions.csv"
HEADER = "name,export_rva,target_rva,target_size,source,status,notes"


def _concurrency(tmp_path, serialize, same_row=True, graph=None):
    world = load.VirtualWorld(tmp_path, builders=3, jitter=0.0, serialize_scopes=serialize)
    world.repo.headers[FUNCTIONS] = HEADER
    if graph:
        world.repo.graph = graph
    seen = []
    original = world.p._dispatch

    def dispatch(batch, digest):
        original(batch, digest)
        seen.append([u for b in world.p.inflight for u in b.units])
    world.p._dispatch = dispatch
    shared = [world.submit("opA", paths=[f"x{i}.cpp", FUNCTIONS],
                           rows={FUNCTIONS: ["0x00401000" if same_row else f"0x0040{i}000"]})
              for i in range(3)]
    loose = [world.submit("opB", paths=[f"y{i}.cpp"]) for i in range(3)]
    world.run([], 3 * 3600)
    done = {e["unit"]: e["ev"] for e in world.events() if e["ev"] in ("landed", "rejected")}
    together = max(len(set(shared) & set(units)) for units in seen)
    loose_together = max(len(set(loose) & set(units)) for units in seen)
    return done, shared + loose, together, loose_together


def test_overlapping_scopes_are_serialized_not_rejected(tmp_path):
    done, units, together, loose_together = _concurrency(tmp_path / "on", serialize=True)
    assert all(done[u] == "landed" for u in units)        # serialized, never rejected
    assert together == 1 and loose_together == 3          # disjoint units still share a batch
    # positive control: without the rule the three ledger units are in flight together
    _, _, together_off, _ = _concurrency(tmp_path / "off", serialize=False)
    assert together_off == 3


def test_rebased_diff_outside_the_declared_scope_is_rejected(world):
    sneaky = world.submit({"ok1.txt": "1\n", "tools/extra.py": "x = 1\n"}, scope=["ok1.txt"])
    forbidden = world.submit({"ok2.txt": "1\n", "checker/gate.sh": "exit 0\n"},
                             scope=["**"], forbid=["checker/**"])
    good = world.submit({"ok3.txt": "1\n", "sub/ok4.txt": "1\n"}, scope=["ok3.txt", "sub/**"])
    settle(world.publisher())
    state, record = where(world, sneaky)
    assert state == "rejected" and record["reason"] == "out-of-scope"
    assert record["paths"] == ["tools/extra.py"]
    state, record = where(world, forbidden)
    assert state == "rejected" and record["paths"] == ["checker/gate.sh"]
    assert where(world, good)[0] == "landed"              # negative control
    assert "tools/extra.py" not in world.files() and "sub/ok4.txt" in world.files()
    # a unit that declares no scope is not queued at all
    world.commit({"noscope.txt": "1\n"})
    pub.submit(world.seat, "opA", world.key("opA"), "HEAD~1..HEAD", inbox=world.inbox)
    world.publisher().ingest()
    reasons = [json.loads(p.read_text())["reason"] for p in (world.state / "inbox-rejected").glob("*.json")]
    assert reasons == ["no-scope"]


def test_equivalent_failures_are_refused_until_the_target_inputs_change(world):
    target = ["bad_t.txt", "cfg.txt"]
    world.submit({"cfg.txt": "v1\n"}, scope=["cfg.txt"])
    settle(world.publisher())

    def attempt(n, content="same approach\n", ledger=False):
        files = {"bad_t.txt": content}
        if ledger:                                       # ledger edits do not change the approach
            files["functions.csv"] = f"row {n}\n"
        world.commit(files, message=f"attempt {n}")
        scope = target + (["functions.csv"] if ledger else [])
        return pub.submit(world.seat, "opA", world.key("opA"), "HEAD~1..HEAD",
                          inbox=world.inbox, scope=scope)

    def refused():
        return sorted(json.loads(p.read_text())["reason"]
                      for p in (world.state / "inbox-rejected").glob("*.json"))
    for n in range(3):
        unit = attempt(n)
        settle(world.publisher())
        assert where(world, unit)[1]["reason"] == "gate"
    # the shared ledger moving on is not a change of the target's inputs
    world.submit({"functions.csv": "other rows\n"}, scope=["functions.csv"])
    settle(world.publisher())
    assert "functions.csv" in world.files()
    fourth = attempt(3, ledger=True)
    settle(world.publisher())
    assert where(world, fourth)[0] is None and refused() == ["retry-limit"]
    other = attempt(4, content="a different approach\n")      # negative control
    settle(world.publisher())
    assert where(world, other)[1]["reason"] == "gate"
    # the target's inputs change (cfg.txt lands anew): the same approach may run again
    world.submit({"cfg.txt": "v2\n"}, scope=["cfg.txt"])
    settle(world.publisher())
    again = attempt(5)
    settle(world.publisher())
    assert where(world, again)[1]["reason"] == "gate" and refused() == ["retry-limit"]


# ---- row-level ledger scope and header dependencies ------------------------------
def _diff(path, *lines):
    return (f"diff --git a/{path} b/{path}\n--- a/{path}\n+++ b/{path}\n@@ -1 +1 @@\n"
            + "".join(f"{line}\n" for line in lines)).encode()


def test_ledger_rows_and_row_tokens_follow_the_ledger_key_rules():
    ledgers = pub.DEFAULTS["row_ledgers"]
    headers = {FUNCTIONS: HEADER, "targets/game/reverse/symbols.csv": "name,address,notes",
               "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status"}
    diff = (_diff(FUNCTIONS, "-?a@@YAXXZ,,0x401000,10,x.cpp,matched,",
                  '+?b@@YAXXZ,,0x00401000,10,x.cpp,matched,"note, with comma"',
                  "+?c,,0x00402000,4,y.cpp,matched,")
            + _diff("targets/game/reverse/symbols.csv", "+?g_x@@3HA,0x00500000,pin")
            + _diff("reverse/data_rows.csv", "+?d@@3HA,0x00600000,va,4,.data,z.cpp,matched")
            + _diff("targets/game/reverse/re_attempts.log", "+one attempt line")
            + _diff("game/x.cpp", "+int a;"))
    rows = pub.ledger_rows(diff, ledgers, headers.get)
    assert rows[FUNCTIONS] == ["0x00401000", "0x00402000"]       # an edit is one row, RVAs normalised
    assert rows["targets/game/reverse/symbols.csv"] == ["?g_x@@3HA"]
    assert rows["reverse/data_rows.csv"] == ["0x00600000"]
    assert len(rows["targets/game/reverse/re_attempts.log"]) == 1   # a line ledger keys whole lines
    scope = pub.scope_from_diff(diff, ledgers, headers.get)
    assert f"{FUNCTIONS}#0x00402000" in scope and "game/x.cpp" in scope and FUNCTIONS not in scope
    # a header edit is a whole-file change
    assert pub.scope_from_diff(_diff(FUNCTIONS, "-" + HEADER, "+" + HEADER + ",extra"),
                               ledgers, headers.get) == [FUNCTIONS]
    row = lambda key: dict(scope=dict(allow=[f"{FUNCTIONS}#{key}"]), paths=[FUNCTIONS],  # noqa: E731
                           rows={FUNCTIONS: [key]})
    whole = dict(scope=dict(allow=[FUNCTIONS]), paths=[FUNCTIONS], rows={FUNCTIONS: ["0x00409000"]})
    assert not pub.scopes_overlap(row("0x00401000"), row("0x00402000"))   # disjoint rows
    assert pub.scopes_overlap(row("0x00401000"), row("0x00401000"))       # positive control
    assert pub.scopes_overlap(row("0x00401000"), whole)                    # a whole-file scope
    assert not pub.in_scope(FUNCTIONS, dict(allow=[f"{FUNCTIONS}#0x00401000"]), "0x00402000")


def test_disjoint_ledger_rows_run_together_and_the_same_row_serializes(tmp_path):
    done, units, together, _ = _concurrency(tmp_path / "same", serialize=True, same_row=True)
    assert together == 1 and all(done[u] == "landed" for u in units)
    done, units, together, _ = _concurrency(tmp_path / "rows", serialize=True, same_row=False)
    assert together == 3 and all(done[u] == "landed" for u in units)


def test_a_header_overlaps_the_units_whose_sources_include_it(tmp_path):
    graph = ({"a.h": {"game/x.cpp", "game/b.h"}, "b.h": {"game/y.cpp"}}, set())
    world = load.VirtualWorld(tmp_path, builders=3, jitter=0.0)
    world.repo.graph = graph
    header = world.submit("opA", paths=["game/a.h"])
    record = world.p.queue[header]
    assert record["reach"] == ["game/b.h", "game/x.cpp", "game/y.cpp"]    # transitive, by name
    x = world.submit("opB", paths=["game/x.cpp"])
    y = world.submit("opB", paths=["game/y.cpp"])
    z = world.submit("opB", paths=["game/z.cpp"])
    q = world.p.queue
    assert pub.scopes_overlap(q[header], q[x]) and pub.scopes_overlap(q[header], q[y])
    assert not pub.scopes_overlap(q[header], q[z]) and not pub.scopes_overlap(q[x], q[y])
    # macro includes count as including everything, except ignored STLport redirects
    world.repo.graph = (graph[0], {"game/macro.cpp"})
    assert "game/macro.cpp" in world.p._reach(["game/a.h"])
    world.repo.graph = (graph[0], {"inputs/vendor/stlport/ctype.h"})
    assert "inputs/vendor/stlport/ctype.h" not in world.p._reach(["game/a.h"])


def test_rows_outside_the_declared_tokens_are_rejected_and_auto_scope_lands(tmp_path):
    w = World(tmp_path)
    w.commit({".gitattributes": "*.csv merge=union\n",
              FUNCTIONS: HEADER + "\n?a,,0x00401000,4,a.cpp,matched,\n"})
    git(w.seat, "push", "-q", str(w.origin), "HEAD:refs/heads/master")
    w.commit({"g1.cpp": "1\n", FUNCTIONS: HEADER + "\n?a,,0x00401000,4,a.cpp,matched,\n"
              "?b,,0x00402000,4,g1.cpp,matched,\n?c,,0x00403000,4,g1.cpp,matched,\n"})
    sneaky = pub.submit(w.seat, "opA", w.key("opA"), "HEAD~1..HEAD", inbox=w.inbox,
                        scope=["g1.cpp", f"{FUNCTIONS}#0x00402000"])
    w.commit({"g2.cpp": "1\n", FUNCTIONS: HEADER + "\n?a,,0x00401000,4,a.cpp,matched,\n"
              "?d,,0x00404000,4,g2.cpp,matched,\n"})
    auto = pub.submit(w.seat, "opB", w.key("opB"), "HEAD~1..HEAD", inbox=w.inbox, scope="diff")
    w.commit({"g3.cpp": "1\n", FUNCTIONS: HEADER + "\n?a,,0x00401000,4,a.cpp,matched,\n"
              "?e,,0x00405000,4,g3.cpp,matched,\n"})
    auto2 = pub.submit(w.seat, "opA", w.key("opA"), "HEAD~1..HEAD", inbox=w.inbox, scope="diff")
    p = w.publisher()
    settle(p)
    state, record = where(w, sneaky)
    assert state == "rejected" and record["paths"] == [f"{FUNCTIONS}#0x00403000"]
    for unit in (auto, auto2):                                 # disjoint rows: both land
        state, record = where(w, unit)
        assert state == "landed" and f"{FUNCTIONS}#0x0040" in " ".join(record["scope"]["allow"])
    text = git(w.origin, "show", f"master:{FUNCTIONS}")
    assert "0x00404000" in text and "0x00405000" in text and "0x00403000" not in text
