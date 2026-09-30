"""fleet_run starts no worker on a body whose shared claim was refused or
unconfirmed, and keeps a claim whose landing is not yet on origin/master."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402
import fleet_run  # noqa: E402


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout


@pytest.fixture
def repo(tmp_path, monkeypatch):
    origin = tmp_path / "origin.git"
    _git(tmp_path, "init", "-q", "--bare", str(origin))
    clone = tmp_path / "seat"
    _git(tmp_path, "init", "-q", str(clone))
    _git(clone, "remote", "add", "origin", str(origin))
    _git(clone, "config", "user.name", "seat")
    _git(clone, "config", "user.email", "seat@example.com")
    monkeypatch.delenv("BFME_CLAIM_OWNER", raising=False)
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    claims.active.cache_clear()
    return clone


TARGETS = [("0x00000100", 16), ("0x00000200", 8)]


def test_granted_claims_are_recorded_with_tokens_and_a_heartbeat(repo):
    record = {}
    beat = fleet_run.claim_shared(repo, "run1", TARGETS, "test", "1", record)
    try:
        assert record["shared_claims"] == ["0x00000100", "0x00000200"]
        assert set(record["shared_claim_tokens"]) == {"0x00000100", "0x00000200"}
        assert record["shared_claim_worker"] == "fleet:run1"
        assert set(claims.active(repo)) == {0x100, 0x200}
        # one heartbeat renews every claim under a fresh token
        old = dict(record["shared_claim_tokens"])
        beat.beat()
        assert record["shared_claim_tokens"].keys() == old.keys()
        assert all(record["shared_claim_tokens"][k] != old[k] for k in old)
        assert claims.holds(0x100, record["shared_claim_tokens"]["0x00000100"], root=repo)
    finally:
        beat.stop()


def test_a_body_held_by_another_worker_stops_the_run(repo):
    claims.claim([0x200], who="fleet:other", root=repo)
    record = {}
    with pytest.raises(fleet_run.ClaimConflict, match="held by another worker"):
        fleet_run.claim_shared(repo, "run2", TARGETS, "test", "1", record)
    # the part that was granted is recorded so the run's cleanup releases it
    assert record["shared_claims"] == ["0x00000100"]
    assert record["shared_claims_refused"] == ["0x00000200"]


def test_an_unreachable_origin_stops_the_run_distinctly(repo):
    _git(repo, "remote", "set-url", "origin", str(repo.parent / "gone.git"))
    record = {}
    with pytest.raises(fleet_run.SharedClaimsUnavailable):
        fleet_run.claim_shared(repo, "run3", TARGETS, "test", "1", record)
    assert "shared_claims_error" in record
    assert not issubclass(fleet_run.SharedClaimsUnavailable, fleet_run.ClaimConflict)
    assert fleet_run.EXIT_CLAIMS_UNAVAILABLE not in (0, 75)


def test_opt_out_and_fixture_roots_skip_shared_claims(repo, tmp_path, monkeypatch):
    lonely = tmp_path / "lonely"
    lonely.mkdir()
    record = {}
    assert fleet_run.claim_shared(lonely, "run4", TARGETS, "test", "1", record) is None
    assert "shared_claims_skipped" in record
    monkeypatch.setenv("BFME_CLAIMS", "off")
    record = {}
    assert fleet_run.claim_shared(repo, "run4", TARGETS, "test", "1", record) is None
    assert claims.active(repo) == {}


def _commit_ledger(clone, rows, message):
    ledger = clone / claims.LEDGER
    ledger.parent.mkdir(parents=True, exist_ok=True)
    ledger.write_text("name,export_rva,target_rva,target_size,source,status,notes\n"
                      + "".join(r + "\n" for r in rows), encoding="utf-8")
    _git(clone, "add", claims.LEDGER)
    _git(clone, "commit", "-q", "-m", message)


def test_settle_keeps_an_unpublished_landing_and_frees_the_rest(repo, monkeypatch):
    _commit_ledger(repo, [], "base")
    _git(repo, "push", "-q", "origin", "HEAD:refs/heads/master")
    record = {}
    fleet_run.claim_shared(repo, "run5", TARGETS, "test", "1", record).stop()
    row = "?f@@YAXXZ,,0x00000100,16,game/x.cpp,matched,model=m"
    _commit_ledger(repo, [row], "land 0x100 locally")
    claims.queue_landed(0x100, row, who="fleet:run5", root=repo)
    fleet_run.settle_shared(repo, "run5", record)
    assert record["shared_claims_released"] == ["0x00000200"]
    assert record["shared_claims_kept"] == ["0x00000100"]
    assert set(claims.active(repo)) == {0x100}
    # the push lands it; the next settle (any run in this checkout) frees it
    _git(repo, "push", "-q", "origin", "HEAD:refs/heads/master")
    assert claims.release_landed(root=repo) == ([0x100], [])
    claims.active.cache_clear()
    assert claims.active(repo) == {}
