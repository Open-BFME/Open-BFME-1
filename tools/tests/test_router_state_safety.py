"""Pure router state regressions: temporary Git repositories, no workers."""
import json
from pathlib import Path
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import opencode_router as r


def git(repo, *args):
    return subprocess.check_output(['git', '-C', str(repo), *args], text=True).strip()


@pytest.fixture
def repo(tmp_path):
    git(tmp_path, 'init', '-q')
    git(tmp_path, 'config', 'user.name', 'fixture')
    git(tmp_path, 'config', 'user.email', 'fixture@example.invalid')
    (tmp_path / 'evidence').write_text('submission')
    git(tmp_path, 'add', 'evidence')
    git(tmp_path, 'commit', '-qm', 'submission')
    return tmp_path


def test_delayed_dispatch_uses_submission_snapshot(repo, tmp_path, monkeypatch):
    monkeypatch.setattr(r, 'ROOT', repo)
    state = tmp_path / 'state'
    job_id = r.enqueue(state, 'bulk', 'task evidence from submission')
    base = git(repo, 'rev-parse', 'HEAD')
    (repo / 'evidence').write_text('later scheduler HEAD')
    git(repo, 'commit', '-qam', 'later')
    with r.database(state) as db:
        job = dict(db.execute('SELECT * FROM jobs WHERE id=?', (job_id,)).fetchone())
    cwd = r.prepare_workspace(repo, state, job)
    assert git(cwd, 'rev-parse', 'HEAD') == base
    (cwd / 'retained').write_text('retry work')
    # Also recover a crash between worktree creation and cwd persistence.
    assert r.prepare_workspace(repo, state, job) == cwd
    assert (cwd / 'retained').read_text() == 'retry work'


def test_legacy_delayed_job_does_not_invent_base(repo, tmp_path):
    with pytest.raises(ValueError, match='legacy|snapshot'):
        r.prepare_workspace(repo, tmp_path / 'state', {'id': 'old', 'cwd': None})


def test_quota_does_not_override_forced_interruption(tmp_path):
    state = tmp_path / 'state'
    job = r.enqueue(state, 'bulk', 'task')
    c = r.config(r.DEFAULT_CONFIG)
    model = c['models'][0]['id']
    with r.database(state) as db:
        db.execute('INSERT INTO models(id) VALUES (?)', (model,))
        db.execute("INSERT INTO attempts(id,job,model,tier,status,started) VALUES ('a',?,?,'bulk','running',0)", (job, model))
    events = r.Events()
    events.feed(json.dumps({'type': 'error', 'error': {'status': 429}}))
    result = events.result(None, r.INTERRUPTED)
    assert result['kind'] == r.INTERRUPTED
    assert result['quota_observed'] is True
    r.finish(state, c, 'a', result, now=100)
    with r.database(state) as db:
        job = db.execute('SELECT * FROM jobs').fetchone()
        assert (job['status'], job['tier'], job['failures'], job['availability_failures']) == ('queued', 'bulk', 0, 0)
        assert db.execute('SELECT cooldown FROM models').fetchone()[0] >= 100 + c['cooldown']
        assert r.ramp_caps(db, c, 101)[model] == 1
    assert r.go_budget.snapshot(state, c, now=101)['exhausted']


def test_show_does_not_scan_fleet(tmp_path, monkeypatch):
    state = tmp_path / 'state'
    wanted = r.enqueue(state, 'bulk', 'wanted')
    r.enqueue(state, 'bulk', 'unrelated')
    monkeypatch.setattr(r, 'status', lambda *a: pytest.fail('full fleet status called'))
    monkeypatch.setattr(r.fleet_run, 'cgroup_state', lambda *a: pytest.fail('cgroup probe called'))
    monkeypatch.setattr(r, 'budget_snapshot', lambda *a: pytest.fail('budget query called'))
    data = r.show(state, wanted)
    assert [j['id'] for j in data['jobs']] == [wanted]
    assert data['attempts'] == []


def test_delayed_dispatch_rejects_different_repository(repo, tmp_path, monkeypatch):
    monkeypatch.setattr(r, 'ROOT', repo)
    state = tmp_path / 'state'
    job = r.enqueue(state, 'bulk', 'task')
    other = tmp_path / 'other'
    other.mkdir()
    git(other, 'init', '-q')
    with r.database(state) as db:
        row = dict(db.execute('SELECT * FROM jobs WHERE id=?', (job,)).fetchone())
    with pytest.raises(ValueError, match='repository differs'):
        r.prepare_workspace(other, state, row)
