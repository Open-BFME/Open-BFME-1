"""Shared claims as refs on origin (tools/claims.py), two hosts against a bare repo."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout


@pytest.fixture
def hosts(tmp_path, monkeypatch):
    origin = tmp_path / "origin.git"
    _git(tmp_path, "init", "-q", "--bare", str(origin))
    clones = {}
    for name in ("a", "b"):
        clone = tmp_path / name
        _git(tmp_path, "init", "-q", str(clone))
        _git(clone, "remote", "add", "origin", str(origin))
        _git(clone, "config", "user.name", name)
        _git(clone, "config", "user.email", f"{name}@example.com")
        clones[name] = clone

    monkeypatch.delenv("BFME_RUN_ID", raising=False)

    def act(name):
        monkeypatch.setattr(claims, "ROOT", clones[name])
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
        # never the real origin: every claim these tests push lands in the fixture
        assert Path(claims._git("remote", "get-url", "origin").stdout.strip()) == origin
        return clones[name]
    act.origin = origin
    return act


def test_a_claim_is_exclusive_across_hosts(hosts):
    hosts("a")
    assert claims.claim([0x100, 0x200]) == ([0x100, 0x200], [])
    hosts("b")
    assert set(claims.active()) == {0x100, 0x200}
    assert claims.claim([0x200, 0x300]) == ([0x300], [0x200])     # partial batch
    assert claims.active()[0x300]["owner"] == "b"


def test_only_the_owner_releases(hosts):
    hosts("a")
    claims.claim([0x100])
    hosts("b")
    assert claims.release([0x100]) == []
    assert 0x100 in claims.active()
    hosts("a")
    assert claims.release([0x100]) == [0x100]
    assert claims.active() == {}


def test_an_expired_claim_can_be_taken_over(hosts):
    hosts("a")
    claims.claim([0x100], ttl_hours=-1)                            # already expired
    hosts("b")
    assert claims.active() == {}
    assert claims.claim([0x100]) == ([0x100], [])
    assert claims.active()[0x100]["owner"] == "b"


def test_renewing_your_own_claim_succeeds(hosts):
    hosts("a")
    claims.claim([0x100])
    assert claims.claim([0x100]) == ([0x100], [])


def test_an_unreachable_origin_fails_closed(hosts, monkeypatch):
    # Readers still serve (a picker only proposes), but claim() may no longer
    # answer ([], []) -- "nothing claimed" and "nothing to claim" looked alike.
    hosts("a")
    monkeypatch.setattr(claims, "REMOTE", "no-such-remote")
    assert claims.active() == {}
    with pytest.raises(claims.ClaimsUnavailable):
        claims.claim([0x100])
    assert claims.main(["claim", "0x100"]) == 2


def test_active_reads_the_origin_of_the_given_root_not_this_checkout(hosts, tmp_path):
    # tools/tests/test_fleet_lifecycle_regressions.py failed on every host with
    # live claims on the real origin: busy_rvas(fixture_root) merged claims.active(),
    # which always fetched from THIS checkout. A root is now fetched through
    # its own origin, so a fixture repository without a remote sees none.
    hosts("a")
    assert claims.claim([0x300]) == ([0x300], [])
    hosts("b")
    assert set(claims.active(claims.ROOT)) == {0x300}
    lonely = tmp_path / "lonely"
    _git(tmp_path, "init", "-q", str(lonely))
    assert claims.active(lonely) == {}
    import eligibility
    (lonely / "build").mkdir()
    assert "0x00000300" not in eligibility.busy_rvas(lonely)


def test_a_claim_result_carries_tokens_and_still_unpacks(hosts):
    hosts("a")
    result = claims.claim([0x100, 0x200])
    got, refused = result
    assert (got, refused) == ([0x100, 0x200], [])
    assert result.worker == "a" and result.unconfirmed == []
    token = result.tokens[0x100]
    assert claims.holds(0x100, token)
    assert result.tokens[0x200] == token          # one claim commit per call


def test_a_push_origin_refuses_without_a_holder_is_unconfirmed(hosts, monkeypatch):
    hosts("a")
    real = claims._git

    def flaky(*args, **kw):
        if args[:1] == ("push",):
            return claims.subprocess.CompletedProcess(args, 1, "", "connection reset")
        return real(*args, **kw)
    monkeypatch.setattr(claims, "_git", flaky)
    with pytest.raises(claims.ClaimsUnavailable):
        claims.claim([0x100])


def test_a_race_lost_after_fetch_is_refused_not_unconfirmed(hosts, monkeypatch):
    hosts("a")
    real_fetch = claims.fetch
    calls = []

    def fetch_then_race(root=None):
        ok = real_fetch(root)
        if not calls:                  # b claims between a's fetch and a's push
            calls.append(1)
            monkeypatch.setenv("BFME_CLAIM_OWNER", "b")
            claims.claim([0x100], root=hosts.b_root)
            monkeypatch.setenv("BFME_CLAIM_OWNER", "a")
        return ok
    hosts.b_root = hosts("b")
    hosts("a")
    monkeypatch.setattr(claims, "fetch", fetch_then_race)
    result = claims.claim([0x100])
    assert result == ([], [0x100]) and result.unconfirmed == []


def test_the_default_owner_is_per_checkout_not_per_host(hosts, monkeypatch, tmp_path):
    a = hosts("a")
    b = hosts("b")
    monkeypatch.delenv("BFME_CLAIM_OWNER")
    assert claims.owner(a) != claims.owner(b)
    assert claims.owner(a) == claims.owner(a)
    monkeypatch.setenv("BFME_RUN_ID", "20260929T000000Z-abc")
    assert claims.owner(a) == "fleet:20260929T000000Z-abc"


def test_heartbeat_renews_and_fencing_detects_a_takeover(hosts):
    hosts("a")
    result = claims.claim([0x100, 0x200], ttl_hours=-1)            # both already expired
    renewed, lost = claims.renew({0x100: result.tokens[0x100]})
    assert lost == [] and claims.holds(0x100, renewed[0x100])
    assert not claims.holds(0x100, result.tokens[0x100])           # old token is dead
    hosts("b")
    taken = claims.claim([0x200])                                  # expired: b takes it over
    assert taken.claimed == [0x200]
    hosts("a")
    renewed, lost = claims.renew({0x200: result.tokens[0x200]})
    assert renewed == {} and lost == [0x200]
    # a stale release (even forced) never deletes the successor's claim
    assert claims.release([0x200], force=True, tokens={0x200: result.tokens[0x200]}) == []
    assert claims.active()[0x200]["owner"] == "b"


def _commit_ledger(clone, rows, message, files=None):
    ledger = clone / claims.LEDGER
    ledger.parent.mkdir(parents=True, exist_ok=True)
    ledger.write_text("name,export_rva,target_rva,target_size,source,status,notes\n"
                      + "".join(r + "\n" for r in rows), encoding="utf-8")
    for path, text in (files or {}).items():
        (clone / path).parent.mkdir(parents=True, exist_ok=True)
        (clone / path).write_text(text, encoding="utf-8")
        _git(clone, "add", path)
    _git(clone, "add", claims.LEDGER)
    _git(clone, "commit", "-q", "-m", message)
    return _git(clone, "rev-parse", "HEAD").strip()


def test_a_landing_releases_only_once_origin_master_holds_the_row(hosts):
    a = hosts("a")
    base = _commit_ledger(a, ["?d_00000100@@YAXXZ,,0x00000100,16,game/gen_asm/x.asm,matched,gen-dump"], "base")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    sha = _commit_ledger(a, [row], "land", {"game/x.cpp": "void f() {}\n"})
    claims.queue_landed(0x100, row)
    # verified and committed locally, not pushed: the claim must hold
    assert claims.release_landed() == ([], [0x100])
    assert 0x100 in claims.active()
    with pytest.raises(ValueError):
        claims.landed_rvas(sha)
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([0x100], [])
    assert claims.active() == {} and claims.pending() == []
    assert base != sha


def test_release_landed_sha_releases_the_leases_the_commit_names(hosts):
    a = hosts("a")
    _commit_ledger(a, [], "base")
    got = claims.claim([0x300, 0x400])
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,game/y.cpp,matched,",
                             "?h@@YAXXZ,,0x00000400,8,game/y.cpp,matched,"],
                         f"land\n\nClaim-Lease: 0x00000300={got.leases[0x300]}\n")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.landed_rvas(sha) == [0x300, 0x400]
    assert claims.lease_trailers(sha) == {0x300: got.leases[0x300]}
    assert claims.main(["release", "--landed", sha]) == 0
    assert set(claims.active()) == {0x400}          # no trailer, no evidence: untouched


def test_an_old_published_row_does_not_release_an_unpublished_source_change(hosts):
    # review 2026-09-29: the same row key was already on origin (an earlier
    # lift); the new source existed only locally, and release_landed released.
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,gen-dump"
    _commit_ledger(a, [row], "existing lift", {"game/x.cpp": "__asm { emit }\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    (a / "game/x.cpp").write_text("void f() { real(); }\n", encoding="utf-8")
    (a / "game/x.h").write_text("struct X;\n", encoding="utf-8")          # a new dependency
    claims.queue_landed(0x100, row.replace("gen-dump", "model=m"))
    entry = claims.pending()[0]
    assert set(entry["deps"]) == {"game/x.cpp", "game/x.h"}
    assert claims.release_landed() == ([], [0x100])
    _commit_ledger(a, [row.replace("gen-dump", "model=m")], "real body",
                   {"game/x.cpp": "void f() { real(); }\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([], [0x100])        # the header is still local
    _commit_ledger(a, [row.replace("gen-dump", "model=m")], "header",
                   {"game/x.h": "struct X;\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed() == ([0x100], [])


def test_a_missing_source_never_releases(hosts):
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "row only")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    claims.queue_landed(0x100, row)
    assert claims.release_landed() == ([], [0x100])


def test_concurrent_queue_appends_all_survive(tmp_path):
    import threading
    jobs = [threading.Thread(target=claims.queue_landed,
                             args=(r, f"f,,0x{r:08X},1,game/x.cpp,matched,"),
                             kwargs={"who": "t", "root": tmp_path, "deps": {"game/x.cpp": "b"}})
            for r in range(0x100, 0x100 + 24)]
    for job in jobs:
        job.start()
    for job in jobs:
        job.join(timeout=30)
    assert sorted(int(e["rva"], 16) for e in claims.pending(tmp_path)) == list(range(0x100, 0x118))


def test_a_directory_inside_a_checkout_never_inherits_its_origin(hosts, monkeypatch):
    # review 2026-09-29: pytest's basetemp under a real checkout let a
    # "no origin" fixture discover the enclosing repo and push real claims.
    a = hosts("a")
    inner = a / "build" / "fixture"
    inner.mkdir(parents=True)
    assert not claims.configured(inner)
    with pytest.raises(claims.ClaimsUnavailable):
        claims.claim([0x500], root=inner)
    assert _git(hosts.origin, "for-each-ref", "refs/claims/") == ""


def test_release_landed_sha_cannot_override_a_pending_landing(hosts):
    # review 2026-09-29 (reproduction test_release_bypass.py): settlement kept
    # the claim, but `release --landed <old published sha>` released it while
    # the replacement source was still local.
    a = hosts("a")
    _commit_ledger(a, [], "base")
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    sha = _commit_ledger(a, [row], "old published body", {"game/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    (a / "game/x.cpp").write_text("void f() { different(); }\n", encoding="utf-8")
    claims.queue_landed(0x100, row)
    assert claims.release_landed() == ([], [0x100])
    assert claims.release_landed(sha) == ([], [0x100])
    assert 0x100 in claims.active()
    assert claims.main(["release", "--landed", sha]) == 0 and 0x100 in claims.active()


def test_an_earlier_settled_landing_does_not_release_a_newer_pending_one(hosts):
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"game/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    claims.queue_landed(0x100, row)                          # matches origin: settled
    (a / "game/x.cpp").write_text("void f() { again(); }\n", encoding="utf-8")
    claims.queue_landed(0x100, row)                          # a second, local-only pass
    assert claims.release_landed() == ([], [0x100])
    assert 0x100 in claims.active()


def test_a_committed_but_unpushed_repair_is_not_released(hosts):
    # 2026-09-29 audit fixture: the row was on origin, the repaired source was
    # committed locally but never pushed, and release_landed released.
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=old"
    _commit_ledger(a, [row], "old landing", {"game/x.cpp": "old source\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    _git(a, "fetch", "-q", "origin")
    claims.claim([0x100])
    _commit_ledger(a, [row], "unpublished repair", {"game/x.cpp": "repaired source\n"})
    claims.queue_landed(0x100, row.replace("model=old", "model=new"))
    assert claims.release_landed() == ([], [0x100])
    assert 0x100 in claims.active()


def test_a_lease_survives_renewal_and_dies_with_a_takeover(hosts):
    a = hosts("a")
    got = claims.claim([0x100], ttl_hours=-1)                       # expired at once
    lease = got.leases[0x100]
    assert claims.lease_holder(0x100, lease) is None                # expired: not held
    renewed, _ = claims.renew(got.tokens)
    assert claims.lease_holder(0x100, lease) == renewed[0x100]      # same lease, new token
    assert claims.lease_holder(0x100, got.tokens[0x100]) is None    # the old token alone is dead
    hosts("b")
    claims.release([0x100], force=True)
    claims.claim([0x100])
    hosts("a")
    assert claims.lease_holder(0x100, lease) is None


def test_a_landing_queued_during_settlement_keeps_its_claim(hosts, monkeypatch):
    # review 2026-09-30: the queue was snapshotted before the fetch, so a
    # repair queued meanwhile was never evaluated and its claim was released.
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"game/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    claims.queue_landed(0x100, row)                    # settled on origin
    real_fetch = claims._fetch_master

    def queue_while_on_network(root=None):
        (a / "game/x.cpp").write_text("void f() { local_repair(); }\n", encoding="utf-8")
        claims.queue_landed(0x100, row)
        return real_fetch(root)
    monkeypatch.setattr(claims, "_fetch_master", queue_while_on_network)
    released, waiting = claims.release_landed()
    assert released == [] and 0x100 in waiting
    assert len(claims.pending()) == 1 and 0x100 in claims.active()


def test_settlement_releases_only_the_claim_generation_it_evaluated(hosts, monkeypatch):
    a = hosts("a")
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"game/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    claims.claim([0x100])
    claims.queue_landed(0x100, row)
    real_release = claims.release

    def reclaimed_first(rvas, **kwargs):
        # the claim is re-taken (a new generation) between evaluation and release
        claims.claim([0x100], who="a")
        return real_release(rvas, **kwargs)
    monkeypatch.setattr(claims, "release", reclaimed_first)
    assert claims.release_landed()[0] == []
    assert 0x100 in claims.active()


def _published_and_queued(a):
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    _commit_ledger(a, [row], "published", {"game/x.cpp": "void f() {}\n"})
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    old = claims.claim([0x100])
    claims.queue_landed(0x100, row)
    assert claims.pending()[0]["lease"] == old.leases[0x100]
    return old


def test_a_fresh_claim_during_settlement_survives_the_old_landing(hosts, monkeypatch):
    # review 2026-09-30 (test_review_probes.py): the body was re-claimed by the
    # same owner while settlement fetched; the old landing deleted the NEW claim.
    a = hosts("a")
    old = _published_and_queued(a)
    real_fetch = claims._fetch_master
    fresh = []

    def replace_before_evaluation(root=None):
        fresh.append(claims.claim([0x100], who="a"))
        return real_fetch(root)
    monkeypatch.setattr(claims, "_fetch_master", replace_before_evaluation)
    released, _ = claims.release_landed()
    assert fresh[0].leases[0x100] != old.leases[0x100]
    assert released == [] and 0x100 in claims.active()
    assert claims.holds(0x100, fresh[0].tokens[0x100])


def test_a_renewal_keeps_the_lease_so_the_landing_still_releases(hosts):
    a = hosts("a")
    old = _published_and_queued(a)
    renewed, lost = claims.renew(old.tokens)
    assert lost == [] and renewed[0x100] != old.tokens[0x100]
    assert claims.release_landed() == ([0x100], [])
    assert claims.active() == {}


def test_release_landed_sha_never_releases_on_timing(hosts, monkeypatch):
    # review 2026-09-30 (test_ca142ff_review.py): a claim taken 0.9 s AFTER the
    # commit passed the whole-second `since <= commit time` test and was freed.
    a = hosts("a")
    _commit_ledger(a, [], "base")
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,game/y.cpp,matched,"], "land")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    committed = int(_git(a, "log", "-1", "--format=%ct", sha))
    monkeypatch.setattr(claims.time, "time", lambda: committed + 0.9)
    fresh = claims.claim([0x300])
    released, _ = claims.release_landed(sha)
    assert released == [] and claims.holds(0x300, fresh.tokens[0x300])


def test_a_trailer_naming_an_old_lease_does_not_release_a_fresh_claim(hosts):
    a = hosts("a")
    _commit_ledger(a, [], "base")
    old = claims.claim([0x300])
    sha = _commit_ledger(a, ["?g@@YAXXZ,,0x00000300,8,game/y.cpp,matched,"],
                         f"land\n\nClaim-Lease: 0x00000300={old.leases[0x300]}\n")
    _git(a, "push", "-q", "origin", "HEAD:refs/heads/master")
    fresh = claims.claim([0x300])                    # same owner, new lease
    assert fresh.leases[0x300] != old.leases[0x300]
    assert claims.release_landed(sha)[0] == []
    assert claims.holds(0x300, fresh.tokens[0x300])


@pytest.mark.parametrize("failure", [None, "fetch", "head", "head_error_with_output", "empty", "timeout"])
def test_fetch_master_preserves_commands_and_reports_failed_step(
        tmp_path, monkeypatch, capsys, failure):
    # Exercise the real _fetch_master and _git with a mocked subprocess only:
    # no fixture or production Git/network operation is launched.
    import os

    monkeypatch.setattr(claims, "REMOTE", "fixture-origin")
    inherited_env = dict(os.environ)
    calls = []

    def run(command, **kwargs):
        step = "fetch" if len(calls) == 0 else "head"
        calls.append(command)
        assert kwargs == {
            "cwd": tmp_path, "capture_output": True, "text": True,
            "input": None, "timeout": 300 if step == "fetch" else 60,
            "env": dict(inherited_env, GIT_CEILING_DIRECTORIES=str(tmp_path.parent)),
        }
        if step == "fetch":
            assert command == ["git", "fetch", "-q", "--no-tags", "fixture-origin", "master"]
            if failure == "timeout":
                raise subprocess.TimeoutExpired(command, 300)
            if failure == "fetch":
                return subprocess.CompletedProcess(command, 128, "", "fatal: fixture fetch failed\n")
            return subprocess.CompletedProcess(command, 0, "", "")
        assert command == ["git", "rev-parse", "FETCH_HEAD"]
        if failure == "head":
            return subprocess.CompletedProcess(command, 128, "", "fatal: fixture FETCH_HEAD failed\n")
        if failure == "head_error_with_output":
            return subprocess.CompletedProcess(command, 128, "abc123\n", "fatal: fixture FETCH_HEAD failed\n")
        if failure == "empty":
            return subprocess.CompletedProcess(command, 0, " \n", "")
        return subprocess.CompletedProcess(command, 0, "abc123\n", "")

    monkeypatch.setattr(claims.subprocess, "run", run)
    result = claims._fetch_master(tmp_path)
    captured = capsys.readouterr()
    assert captured.out == ""
    assert len(calls) == (1 if failure in ("fetch", "timeout") else 2)
    if failure is None:
        assert result == "abc123"
        assert captured.err == ""
    else:
        assert result is None
        expected = {
            "fetch": "claims: git fetch fixture-origin master failed (exit 128): fatal: fixture fetch failed\n",
            "head": "claims: git rev-parse FETCH_HEAD failed (exit 128, empty stdout): fatal: fixture FETCH_HEAD failed\n",
            "head_error_with_output": "claims: git rev-parse FETCH_HEAD failed (exit 128): fatal: fixture FETCH_HEAD failed\n",
            "empty": "claims: git rev-parse FETCH_HEAD failed (exit 0, empty stdout): (no stderr)\n",
            "timeout": "claims: git fetch fixture-origin master failed (exit 124): timed out after 300s\n",
        }
        assert captured.err == expected[failure]
