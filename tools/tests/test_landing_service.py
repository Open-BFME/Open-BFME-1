"""The landing-service prototype: idempotent queue, batch bisection, receipts, recovery."""
import json
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import landing_service as ls  # noqa: E402

GATE = "! ls | grep -q bad"            # red when the tree holds a file named bad*


def git(cwd, *args, input=None):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True,
                          input=input).stdout.strip()


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
    assert service.run_once() == {"landed": [unit_id], "rejected": []}
    assert (service.state / "landed" / f"{unit_id}.json").exists()
    assert json.loads((service.state / "receipts" / f"{unit_id}.json").read_text())["note"]


# ---- 2026-09-29 audit reproductions (gpt-6.1-sol, BFME_LINKING_AUDIT.md) ----

def test_the_verified_tip_itself_is_published(world):
    # audit: a second `git am` after the gate made a different commit (new
    # committer time) and THAT was pushed, so the receipt named an unverified tip.
    import time
    service, unit, origin = world
    uid = service.enqueue(unit("tip"))
    gated = []
    real_gate = service._gate

    def gate(base, tip):
        gated.append(tip)
        time.sleep(1.1)                    # a re-application would get a new timestamp
        return real_gate(base, tip)
    service._gate = gate
    assert service.run_once()["landed"] == [uid]
    receipt = json.loads((service.state / "receipts" / f"{uid}.json").read_text())
    assert receipt["batch_tip"] == gated[-1] == git(origin, "rev-parse", "master")


def test_a_claim_lost_during_the_gate_does_not_publish(world):
    # audit: the fence ran once before the gate; a takeover during a long gate
    # still published.
    service, unit, origin = world
    held, checks = [True], []
    service.fence = lambda record: checks.append(held[0]) or held[0]
    before = git(origin, "rev-parse", "master")
    uid = service.enqueue(unit("takeover"), {"claims": {"0x100": "lease"}})
    real_gate = service._gate

    def gate(base, tip):
        held[0] = False
        return real_gate(base, tip)
    service._gate = gate
    service.leases = lambda record: {}
    result = service.run_once()
    assert result == {"landed": [], "rejected": [uid]}
    assert checks[-1] is False and git(origin, "rev-parse", "master") == before


@pytest.fixture
def claimed(world, monkeypatch):
    import claims
    service, unit, origin = world
    monkeypatch.setenv("BFME_CLAIM_OWNER", "worker")
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    service.fence = service.claims_fence
    got = claims.claim([0x100], root=service.repo)
    assert got.claimed == [0x100]
    return service, unit, origin, claims, got


def test_a_heartbeat_rotation_during_the_gate_still_lands(claimed):
    # audit: renewal replaced the token that immutable queued metadata named.
    service, unit, origin, claims, got = claimed
    uid = service.enqueue(unit("renewed"), {"claims": {"0x100": got.leases[0x100]}})
    real_gate = service._gate

    def gate(base, tip):
        renewed, lost = claims.renew(got.tokens, root=service.repo)
        assert lost == [] and renewed[0x100] != got.tokens[0x100]
        return real_gate(base, tip)
    service._gate = gate
    assert service.run_once()["landed"] == [uid]


def test_a_takeover_racing_the_push_is_refused_atomically(claimed):
    service, unit, origin, claims, got = claimed
    before = git(origin, "rev-parse", "master")
    uid = service.enqueue(unit("raced"), {"claims": {"0x100": got.leases[0x100]}})
    real_leases = service.claim_leases

    def leases_then_race(record):
        held = real_leases(record)          # read the current token ...
        rival = git(service.repo, "commit-tree", git(service.repo, "mktree", input="") or
                    "4b825dc642cb6eb9a060e54bf8d69288fbee4904", "-m", "rival")
        git(service.repo, "push", "-q", "-f", "origin", f"{rival}:refs/claims/0x00000100")
        return held                         # ... and lose it before the push
    service.leases = leases_then_race
    result = service.run_once()
    assert result == {"landed": [], "rejected": [uid]}
    assert git(origin, "rev-parse", "master") == before


def test_the_receipt_names_what_was_verified(world):
    service, unit, origin = world
    service.gate = "mkdir -p out && printf obj > out/body.obj && " + GATE
    uid = service.enqueue(unit("inputs"))
    assert service.run_once()["landed"] == [uid]
    receipt = json.loads((service.state / "receipts" / f"{uid}.json").read_text())
    tip = receipt["batch_tip"]
    assert receipt["tree"] == git(origin, "rev-parse", "master^{tree}")
    assert receipt["artifacts"] == 1 and receipt["gate_log_sha256"]
    manifest = json.loads((service.state / "receipts" / f"{tip}.artifacts.json").read_text())
    import hashlib
    assert manifest == {"out/body.obj": hashlib.sha256(b"obj").hexdigest()}
    assert receipt["artifacts_sha256"] == hashlib.sha256(
        json.dumps(manifest, sort_keys=True).encode()).hexdigest()
    assert receipt["versions"]["python"] and receipt["versions"]["git"].startswith("git version")


# ---- 2026-09-30 review (gpt-6.1-sol, review_20260930_0006.md) ----

def test_the_journal_survives_a_receipt_failure_and_recovery_writes_it(world):
    service, unit, origin = world
    uid = service.enqueue(unit("receipt_crash"))
    real = service._receipts

    def fail(*args, **kwargs):
        raise RuntimeError("simulated disk failure after a successful push")
    service._receipts = fail
    with pytest.raises(RuntimeError, match="simulated disk"):
        service.run_once()
    assert "receipt_crash.txt" in origin_files(origin)
    assert (service.state / "state.json").exists()           # the journal survived
    service._receipts = real
    assert service.run_once()["landed"] == [uid]
    assert (service.state / "receipts" / f"{uid}.json").exists()
    assert not (service.state / "state.json").exists()


def test_a_takeover_after_ref_advertisement_blocks_publication(claimed):
    # The push's own pre-push hook moves the claim ref after the refs were
    # advertised; only a real expected-token update catches that.
    service, unit, origin, claims, got = claimed
    before = git(origin, "rev-parse", "master")
    uid = service.enqueue(unit("post_advertisement"), {"claims": {"0x100": got.leases[0x100]}})
    tree = git(service.repo, "mktree", input="")
    rival = git(service.repo, "commit-tree", tree, "-m", "rival")
    git(service.repo, "push", "-q", "origin", f"{rival}:refs/test/rival")
    hooks = service.state / "hooks"
    hooks.mkdir()
    (hooks / "pre-push").write_text(
        "#!/bin/sh\n" + f'git --git-dir="{origin.as_posix()}" update-ref refs/claims/0x00000100 {rival}\n',
        encoding="utf-8")
    git(service.repo, "config", "core.hooksPath", hooks.as_posix())
    result = service.run_once()
    assert result == {"landed": [], "rejected": [uid]}
    assert git(origin, "rev-parse", "master") == before
    assert git(origin, "rev-parse", "refs/claims/0x00000100") == rival


def test_publication_rewrites_the_claim_and_releases_it_once_landed(claimed):
    service, unit, origin, claims, got = claimed
    uid = service.enqueue(unit("published"), {"claims": {"0x100": got.leases[0x100]}})
    pushed = []
    real_git = ls.git

    def spy(*args, **kwargs):
        if args[:1] == ("push",) and any(a.endswith(":refs/claims/0x00000100") and not a.startswith(":")
                                         for a in args):
            pushed.append(args)
        return real_git(*args, **kwargs)
    ls.git = spy
    try:
        assert service.run_once()["landed"] == [uid]
    finally:
        ls.git = real_git
    # the atomic publication rewrote the claim (lease kept, publication recorded) ...
    assert pushed and any("refs/heads/master" in " ".join(a) for a in pushed)
    # ... and the claim is released only after the landing is on the branch
    assert git(origin, "for-each-ref", "refs/claims/") == ""


def test_a_claim_retaken_after_publication_survives_the_release(claimed, monkeypatch):
    service, unit, origin, claims, got = claimed
    uid = service.enqueue(unit("retaken"), {"claims": {"0x100": got.leases[0x100]}})
    real_release = service._release

    def retake_first(published):
        claims.release([0x100], force=True, root=service.repo)
        monkeypatch.setenv("BFME_CLAIM_OWNER", "next-worker")
        claims.claim([0x100], root=service.repo)
        return real_release(published)
    service._release = retake_first
    assert service.run_once()["landed"] == [uid]
    claims.active.cache_clear()
    assert claims.active(service.repo)[0x100]["owner"] == "next-worker"


def test_a_units_own_check_runs_on_the_rebased_tree_and_can_reject_it(world, tmp_path):
    service, unit, origin = world
    attach = tmp_path / "evidence"
    attach.mkdir()
    (attach / "brief.json").write_text("{}")
    good = service.enqueue(unit("checked_ok"), {
        "verify": "test -f build/provider_repair/X/brief.json && test -f checked_ok.txt",
        "attach": {"build/provider_repair/X": str(attach)}})
    bad = service.enqueue(unit("checked_bad"), {"verify": "exit 7"})
    result = service.run_once()
    assert result == {"landed": [good], "rejected": [bad]}
    assert "checked_ok.txt" in origin_files(origin) and "checked_bad.txt" not in origin_files(origin)


def test_the_drainer_runs_a_windowed_pass_only_when_the_queue_is_non_empty(tmp_path, capsys):
    calls = []

    class Fake:
        work = tmp_path / "wt"

        def __init__(self, queued):
            self._queued = queued

        def recover(self):
            return []

        def queued(self):
            return self._queued

        def run_once(self, max_batch, window):
            calls.append((max_batch, window))
            return {"landed": ["u"], "rejected": []}
    assert ls.drain(Fake([]), once=True) == 0 and calls == []
    assert ls.drain(Fake([{"id": "u"}]), once=True, max_batch=5) == 0
    assert calls == [(5, True)] and '"landed": ["u"]' in capsys.readouterr().out


# ---- review 2026-09-30 cycle 5 (adversarial_checks.py) ----

def test_an_attachment_outside_the_service_build_dir_is_refused(tmp_path):
    service = ls.Service(repo=tmp_path, state=tmp_path / "state", gate="true")
    service.work.mkdir(parents=True, exist_ok=True)
    src = tmp_path / "evidence"
    src.mkdir()
    (src / "brief.json").write_text("{}")
    victim = service.state / "victim"
    victim.mkdir()
    (victim / "other_agent.txt").write_text("keep")
    for dest in ("../victim", "build/../../victim", "build", str(victim)):
        assert service._unit_checks("base", "tip", [{"id": "u", "verify": "true",
                                                     "attach": {dest: str(src)}}]) != 0
    assert (victim / "other_agent.txt").read_text() == "keep" and not (victim / "brief.json").exists()
    assert service._unit_checks("base", "tip", [{"id": "u", "verify": "true",
                                                 "attach": {"build/provider_repair/X": str(src)}}]) == 0


def test_a_one_shot_drain_error_is_not_success():
    class Failure:
        def recover(self):
            return []

        def queued(self):
            return [{"id": "u"}]

        def run_once(self, *args, **kwargs):
            raise RuntimeError("verification failed")
    assert ls.drain(Failure(), once=True) == 1


def test_the_drainer_settles_a_journal_even_with_an_empty_queue():
    calls = []

    class Journal:
        def recover(self):
            calls.append("recover")
            return ["settled-unit"]

        def queued(self):
            return []
    assert ls.drain(Journal(), once=True) == 0 and calls == ["recover"]
