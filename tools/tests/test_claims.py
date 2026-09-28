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

    def act(name):
        monkeypatch.setattr(claims, "ROOT", clones[name])
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
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


def test_an_unreachable_origin_blocks_nothing(hosts, monkeypatch):
    hosts("a")
    monkeypatch.setattr(claims, "REMOTE", "no-such-remote")
    assert claims.active() == {}
    assert claims.claim([0x100]) == ([], [])


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
