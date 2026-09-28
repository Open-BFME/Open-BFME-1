#!/usr/bin/env python3
"""router_integrate.port: moves a router workspace's work onto a newer base.

Covers the failure modes met while integrating router/Zen workers by hand:
staged-only edits (a worker that ran `git add`), deletions of lift files and
banked attempts, CRLF ledgers where upstream appended rows concurrently, and
name_corrections.json entries.
"""
import json, subprocess, sys, tempfile, unittest
import pytest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import router_integrate as ri

LED = 'targets/game/reverse/functions.csv'


def git(cwd, *a):
    subprocess.run(['git', *a], cwd=cwd, check=True, capture_output=True)


class PortFixture(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        base = Path(self.tmp.name) / 'repo'
        base.mkdir()
        git(base, 'init', '-q', '-b', 'master')
        git(base, 'config', 'user.email', 't@t'); git(base, 'config', 'user.name', 't')
        git(base, 'config', 'core.autocrlf', 'false')
        (base / 'targets/game/reverse').mkdir(parents=True)
        (base / 'game').mkdir()
        (base / LED).write_bytes(b'name,export_rva,target_rva\r\n?a@@YAXXZ,,0x00000010\r\n?lift@@YAXXZ,,0x00000020\r\n')
        (base / ri.CORRECTIONS).write_bytes(b'[\r\n {\r\n  "old_name": "x"\r\n }\r\n]\r\n')
        (base / 'game/keep.cpp').write_text('int keep() { return 1; }\n')
        (base / 'game/lift.cpp').write_text('__declspec(naked) void lift() {}\n')
        git(base, 'add', '-A'); git(base, 'commit', '-q', '-m', 'base')
        self.base = base
        self.ws = Path(self.tmp.name) / 'ws'
        self.dest = Path(self.tmp.name) / 'dest'
        git(base, 'worktree', 'add', '-q', '--detach', str(self.ws), 'HEAD')
        git(base, 'worktree', 'add', '-q', '--detach', str(self.dest), 'HEAD')

    def tearDown(self):
        self.tmp.cleanup()


class PortTest(PortFixture):
    def test_port_staged_deleted_and_ledger(self):
        ws, dest = self.ws, self.dest
        # worker: edit keep.cpp (unstaged), add clean source (staged via git add),
        # delete the lift (git rm), move the row, append a correction entry
        (ws / 'game/keep.cpp').write_text('int keep() { return 2; }\n')
        (ws / 'game/clean.cpp').write_text('void lift() {}\n')
        git(ws, 'add', 'game/clean.cpp')
        git(ws, 'rm', '-q', 'game/lift.cpp')
        led = (ws / LED).read_bytes().replace(b'?lift@@YAXXZ,,0x00000020', b'?lift@@YAXXZ,,0x00000020,game/clean.cpp')
        (ws / LED).write_bytes(led)
        corr = json.loads((ws / ri.CORRECTIONS).read_text())
        corr.append({'old_name': 'lift', 'new_name': 'Rva20'})
        (ws / ri.CORRECTIONS).write_text(json.dumps(corr, indent=1))
        # upstream meanwhile appends its own row in the integration worktree
        with open(dest / LED, 'ab') as f:
            f.write(b'?up@@YAXXZ,,0x00000030\r\n')
        ri.port({'cwd': str(ws)}, str(dest))
        self.assertEqual((dest / 'game/keep.cpp').read_text(), 'int keep() { return 2; }\n')
        self.assertTrue((dest / 'game/clean.cpp').exists())
        self.assertFalse((dest / 'game/lift.cpp').exists())
        raw = (dest / LED).read_bytes()
        self.assertIn(b'?up@@YAXXZ,,0x00000030\r\n', raw)
        self.assertIn(b'?lift@@YAXXZ,,0x00000020,game/clean.cpp\r\n', raw)
        self.assertNotIn(b'?lift@@YAXXZ,,0x00000020\r\n', raw)
        self.assertNotIn(b'\n\n', raw.replace(b'\r\n', b'\n'))
        self.assertEqual(raw.count(b'\n'), raw.count(b'\r\n'))
        corr = json.loads((dest / ri.CORRECTIONS).read_text())
        self.assertEqual(corr[-1]['new_name'], 'Rva20')
        self.assertTrue((dest / ri.CORRECTIONS).read_bytes().endswith(b'\r\n]\r\n'))

    def test_changes_sees_staged_only_work(self):
        (self.ws / 'game/new.cpp').write_text('x\n')
        git(self.ws, 'add', 'game/new.cpp')
        self.assertIn(('game/new.cpp', 'added'), ri.changes(str(self.ws)))

    def test_port_carries_shim_header_edit(self):
        # batch 5: the worker's new source needed its shim-header edit, and a
        # port that carried only game/ and targets/ produced a tree that the
        # hook passed (working tree) but the commit could not compile
        shim = 'inputs/reference/shims/x/X.h'
        for tree in (self.base,):
            (tree / shim).parent.mkdir(parents=True)
            (tree / shim).write_text('int a;\n')
        git(self.base, 'add', '-A'); git(self.base, 'commit', '-q', '-m', 'shim')
        for tree in (self.ws, self.dest):
            git(tree, 'checkout', '-q', '--detach', 'master')
        (self.ws / shim).write_text('int a, b;\n')
        (self.ws / 'aim.cod').write_text('scratch\n')
        ri.port({'cwd': str(self.ws)}, str(self.dest))
        self.assertEqual((self.dest / shim).read_text(), 'int a, b;\n')
        self.assertFalse((self.dest / 'aim.cod').exists())

    def test_port_refuses_vendored_reference_edit(self):
        ref = 'inputs/reference/Vendor/Y.h'
        (self.base / ref).parent.mkdir(parents=True)
        (self.base / ref).write_text('int y;\n')
        git(self.base, 'add', '-A'); git(self.base, 'commit', '-q', '-m', 'ref')
        for tree in (self.ws, self.dest):
            git(tree, 'checkout', '-q', '--detach', 'master')
        (self.ws / ref).write_text('int y, z;\n')
        with self.assertRaises(SystemExit):
            ri.port({'cwd': str(self.ws)}, str(self.dest))
        self.assertEqual((self.dest / ref).read_text(), 'int y;\n')

    def test_port_crlf_source(self):
        crlf = 'game/crlf.cpp'
        (self.base / crlf).write_bytes(b'int a;\r\nint b;\r\n')
        git(self.base, 'add', '-A'); git(self.base, 'commit', '-q', '-m', 'crlf')
        for tree in (self.ws, self.dest):
            git(tree, 'checkout', '-q', '--detach', 'master')
        (self.ws / crlf).write_bytes(b'int a;\r\nint c;\r\n')
        (self.ws / 'game/keep.cpp').unlink()
        ri.port({'cwd': str(self.ws)}, str(self.dest))
        self.assertEqual((self.dest / crlf).read_bytes(), b'int a;\r\nint c;\r\n')

    def test_port_keeps_ledger_order(self):
        # a worker ledger rewrite that re-adds an untouched row must not move it,
        # and a changed row keeps its predecessor's position
        led = (self.ws / LED).read_bytes()
        led = led.replace(b'?a@@YAXXZ,,0x00000010\r\n', b'') + b'?a@@YAXXZ,,0x00000010\r\n'
        led = led.replace(b'?lift@@YAXXZ,,0x00000020', b'?clean@@YAXXZ,,0x00000020')
        (self.ws / LED).write_bytes(led)
        with open(self.dest / LED, 'ab') as f:
            f.write(b'?up@@YAXXZ,,0x00000030\r\n')
        ri.port({'cwd': str(self.ws)}, str(self.dest))
        self.assertEqual((self.dest / LED).read_bytes(),
                         b'name,export_rva,target_rva\r\n?a@@YAXXZ,,0x00000010\r\n?clean@@YAXXZ,,0x00000020\r\n'
                         b'?up@@YAXXZ,,0x00000030\r\n')

    def test_bank_carries_only_the_targets_evidence(self):
        log = 'targets/game/reverse/re_attempts.log'
        (self.base / log).write_bytes(b'old\t0x00000001\r\n')
        git(self.base, 'add', '-A'); git(self.base, 'commit', '-q', '-m', 'log')
        for tree in (self.ws, self.dest):
            git(tree, 'checkout', '-q', '--detach', 'master')
        (self.ws / log).write_bytes(b'old\t0x00000001\r\n?f\t0x00000020\t9\tpartial\tnear miss\r\n'
                                    b'?g\t0x00000030\t9\tpartial\tother target\r\n')
        stash = self.ws / 'targets/game/reverse/attempts/0x00000020.cpp'
        stash.parent.mkdir(parents=True); stash.write_text('int f;\n')
        (self.ws / 'targets/game/reverse/attempts/0x00000030.cpp').write_text('int g;\n')
        args = type('A', (), dict(job=None, workspace=str(self.ws), rva=['0x20'], worktree=str(self.dest),
                                  base='master', force=False))()
        ri.bank(args); ri.bank(args)  # idempotent
        self.assertEqual((self.dest / log).read_bytes(),
                         b'old\t0x00000001\r\n?f\t0x00000020\t9\tpartial\tnear miss\r\n')
        self.assertTrue((self.dest / 'targets/game/reverse/attempts/0x00000020.cpp').exists())
        self.assertFalse((self.dest / 'targets/game/reverse/attempts/0x00000030.cpp').exists())

    def test_route(self):
        self.assertEqual(ri.route('inputs/reference/shims/a/b.h'), 'port')
        self.assertEqual(ri.route('inputs/reference/CnC_Generals_Zero_Hour/x.h'), 'refuse')
        self.assertEqual(ri.route('tools/opencode_router.py'), 'refuse')
        self.assertEqual(ri.route('aim.cod'), 'scratch')

    def test_code_only_ignores_comments(self):
        self.assertIsNone(ri.NAKED.search(ri.code_only('// was a __declspec(naked) copy\nvoid f() {}\n')))
        self.assertIsNotNone(ri.NAKED.search(ri.code_only('__declspec(naked) void f() {}\n')))


if __name__ == '__main__':
    unittest.main()


def test_gate_rejects_late_nonzero_exit(monkeypatch):
    monkeypatch.setattr(ri, 'sh', lambda *a, **k: subprocess.CompletedProcess([], 1, 'Functions: OK\n', 'late error'))
    assert ri.gate('.', 'game/a.cpp')[0] is False


@pytest.mark.parametrize('bad_suffix', ['cpp', 'c', 'cc', 'cxx', 'asm'])
def test_review_checks_each_source_once_and_blocks_other_failure(tmp_path, monkeypatch, bad_suffix):
    from types import SimpleNamespace
    (tmp_path / 'game').mkdir()
    bad = 'game/bad.' + bad_suffix
    for name in ('game/good.cpp', bad):
        (tmp_path / name).write_text('void f() {}')
    monkeypatch.setattr(ri, 'info', lambda _: ({'cwd': str(tmp_path), 'status': 'completed'}, [], ['0x00000010'], ''))
    monkeypatch.setattr(ri, 'changes', lambda _: [('game/good.cpp', 'modified'), (bad, 'modified')])
    monkeypatch.setattr(ri, 'ledger_delta', lambda ws, path: (['?f,,0x00000010,1,game/good.cpp'], []) if path == LED else ([], []))
    monkeypatch.setattr(ri, 'git', lambda *a, **k: subprocess.CompletedProcess([], 0, '', ''))
    calls = []
    def fake_gate(ws, src):
        calls.append(src)
        return (src.endswith('good.cpp'), 'fixture')
    monkeypatch.setattr(ri, 'gate', fake_gate)
    result = ri.review(SimpleNamespace(job='fixture'))
    assert calls == ['game/good.cpp', bad]
    assert any(bad in p for p in result['problems'])


def _review_fixture(tmp_path, monkeypatch, new_rows, gates, head_ledger=''):
    """review() over a workspace whose functions.csv delta adds `new_rows`;
    `gates` maps a build.sh selector (source path or row: selector) to (ok, text)."""
    from types import SimpleNamespace
    (tmp_path / 'game').mkdir(exist_ok=True)
    (tmp_path / 'game/shared.cpp').write_text('void f() {}')
    monkeypatch.setattr(ri, 'info', lambda _: ({'cwd': str(tmp_path), 'status': 'completed'}, [], ['0x00000020'], ''))
    monkeypatch.setattr(ri, 'changes', lambda _: [('game/shared.cpp', 'modified')])
    monkeypatch.setattr(ri, 'ledger_delta', lambda ws, path: (new_rows, []) if path == LED else ([], []))
    monkeypatch.setattr(ri, 'git', lambda *a, **k: subprocess.CompletedProcess([], 0, head_ledger, ''))
    calls = []
    def fake_gate(ws, selector):
        calls.append(selector)
        return gates.get(selector, (False, 'fixture: unknown selector ' + selector))
    monkeypatch.setattr(ri, 'gate', fake_gate)
    return ri.review(SimpleNamespace(job='fixture')), calls


def test_review_does_not_land_an_unmatched_row_behind_a_green_source_gate(tmp_path, monkeypatch):
    # The audited defect: a source with an already-matched sibling and a NEW
    # unmatched row for the target passed its source-wide gate, and review
    # reported the target as landed.
    row = '?t@@YAXXZ,,0x00000020,5,game/shared.cpp,unmatched,investigation'
    result, calls = _review_fixture(tmp_path, monkeypatch, [row], {'game/shared.cpp': (True, 'siblings ok')})
    assert result['landed'] == []
    assert result['targets']['0x00000020']['outcome'] == 'unmatched investigation retained'
    assert result['problems'] == []
    assert not any(c.startswith('row:') for c in calls)


def test_review_lands_only_a_matched_row_whose_exact_selector_verifies(tmp_path, monkeypatch):
    row = '?t@@YAXXZ,,0x00000020,5,game/shared.cpp,matched,proof'
    selector = 'row:0x00000020:5:?t@@YAXXZ'
    result, calls = _review_fixture(tmp_path, monkeypatch, [row],
                                    {'game/shared.cpp': (True, 'ok'), selector: (True, 'exact')})
    assert result['landed'] == ['0x00000020']
    assert result['targets']['0x00000020']['outcome'] == 'target newly matched'
    assert selector in calls
    # the same row whose exact selector FAILS is not a landing, and it is a problem
    result, _ = _review_fixture(tmp_path, monkeypatch, [row],
                                {'game/shared.cpp': (True, 'ok'), selector: (False, 'byte mismatch')})
    assert result['landed'] == []
    assert any(selector in p for p in result['problems'])


def test_review_distinguishes_a_preserved_existing_match(tmp_path, monkeypatch):
    head = 'name,export_rva,target_rva,size,source,status,notes\n?t@@YAXXZ,,0x00000020,5,game/shared.cpp,matched,\n'
    result, _ = _review_fixture(tmp_path, monkeypatch, [], {'game/shared.cpp': (True, 'ok')}, head_ledger=head)
    assert result['landed'] == []
    assert result['targets']['0x00000020']['outcome'] == 'existing match preserved'


class PublishFixture(unittest.TestCase):
    """A bare origin, a clone playing the integration worktree, and a second
    clone that can race it."""
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = Path(self.tmp.name)
        self.origin = root / 'origin.git'
        subprocess.run(['git', 'init', '-q', '--bare', '-b', 'master', str(self.origin)], check=True)
        self.dest, self.racer = root / 'dest', root / 'racer'
        for clone in (self.dest, self.racer):
            subprocess.run(['git', 'clone', '-q', str(self.origin), str(clone)], check=True, capture_output=True)
            git(clone, 'config', 'user.email', 't@t'); git(clone, 'config', 'user.name', 't')
        (self.dest / 'a').write_text('base\n')
        git(self.dest, 'add', 'a'); git(self.dest, 'commit', '-qm', 'base'); git(self.dest, 'push', '-q', 'origin', 'master')
        git(self.racer, 'pull', '-q', 'origin', 'master')
        (self.dest / 'a').write_text('integration\n')
        git(self.dest, 'commit', '-qam', 'integration')
        self.counter = root / 'pushes'
        self.counter.write_text('')

    def tearDown(self):
        self.tmp.cleanup()

    def hook(self, body):
        hooks = self.dest / '.git/hooks'
        script = hooks / 'pre-push'
        script.write_text('#!/bin/sh\nprintf x >> "%s"\n%s\n' % (self.counter, body))
        script.chmod(0o755)

    def attempts(self):
        return len(self.counter.read_text())


class PublishTest(PublishFixture):
    def test_hook_rejection_is_reported_once_not_retried_as_a_race(self):
        self.hook('echo "byte verification failed for game/x.cpp" >&2\nexit 1')
        with self.assertRaises(SystemExit) as cm:
            ri.publish(self.dest, 8)
        message = str(cm.exception)
        self.assertIn('byte verification failed for game/x.cpp', message)
        self.assertIn('not a stale-base race', message)
        self.assertNotIn('losing the race', message)
        self.assertEqual(self.attempts(), 1)
        # the local commit is preserved and origin did not move
        self.assertEqual((self.dest / 'a').read_text(), 'integration\n')
        self.assertEqual(git_out(self.origin, 'rev-parse', 'master'), git_out(self.dest, 'rev-parse', 'HEAD~1'))

    def test_stale_base_race_is_rebased_and_retried(self):
        # the first push loses to the racer, which lands its commit from inside
        # the hook; the retry rebases onto it and succeeds
        flag = Path(self.tmp.name) / 'raced'
        self.hook('if [ ! -f "%s" ]; then touch "%s"; git -C "%s" commit -q --allow-empty -m race; '
                  'git -C "%s" push -q origin HEAD:master; fi\nexit 0' % (flag, flag, self.racer, self.racer))
        self.assertEqual(ri.publish(self.dest, 8), 2)
        self.assertEqual(self.attempts(), 2)
        log = git_out(self.dest, 'log', '--format=%s', 'origin/master')
        self.assertEqual(log.split('\n'), ['integration', 'race', 'base'])

    def test_transport_failure_is_not_retried(self):
        git(self.dest, 'remote', 'set-url', 'origin', str(Path(self.tmp.name) / 'missing.git'))
        with self.assertRaises(SystemExit) as cm:
            ri.publish(self.dest, 8)
        self.assertIn('not a stale-base race', str(cm.exception))


def git_out(cwd, *a):
    return subprocess.run(['git', *a], cwd=cwd, check=True, capture_output=True, text=True).stdout.strip()


class ConflictTest(PortFixture):
    def test_new_file_conflicts_with_upstream_addition(self):
        for tree, content in ((self.ws, 'worker'), (self.dest, 'upstream')):
            (tree / 'game/new.cpp').write_text(content)
        git(self.dest, 'add', 'game/new.cpp'); git(self.dest, 'commit', '-qm', 'upstream')
        with self.assertRaises(SystemExit):
            ri.port({'cwd': str(self.ws)}, self.dest)
        self.assertEqual((self.dest / 'game/new.cpp').read_text(), 'upstream')

    def test_rename_with_edit_and_quoted_path(self):
        name = 'game/a "quoted" name.cpp'
        git(self.ws, 'mv', 'game/keep.cpp', name)
        (self.ws / name).write_text('int keep() { return 3; }\n')
        changed = ri.changes(self.ws)
        self.assertIn(('game/keep.cpp', 'deleted'), changed)
        self.assertIn((name, 'added'), changed)
        ri.port({'cwd': str(self.ws)}, self.dest)
        self.assertFalse((self.dest / 'game/keep.cpp').exists())
        self.assertEqual((self.dest / name).read_text(), 'int keep() { return 3; }\n')


class DestinationTest(PortFixture):
    def test_retained_dirty_and_unpushed_work_is_refused(self):
        with self.assertRaisesRegex(SystemExit, 'retained changes'):
            (self.dest / 'game/keep.cpp').write_text('retained')
            ri.safe_destination(self.dest, 'master')
        self.assertEqual((self.dest / 'game/keep.cpp').read_text(), 'retained')
        git(self.dest, 'add', 'game/keep.cpp')
        with self.assertRaisesRegex(SystemExit, 'staged work'):
            ri.safe_destination(self.dest, 'master', keep=True)
        git(self.dest, 'commit', '-qm', 'retained commit')
        with self.assertRaisesRegex(SystemExit, 'unintegrated commits'):
            ri.safe_destination(self.dest, 'master')

    def test_clean_detached_destination_and_explicit_keep(self):
        ri.safe_destination(self.dest, 'master')
        (self.dest / 'game/keep.cpp').write_text('retained')
        ri.safe_destination(self.dest, 'master', keep=True)


def test_check_csv_failure_blocks_integration(tmp_path, monkeypatch):
    from types import SimpleNamespace
    dest = tmp_path / 'destination'
    dest.mkdir()
    monkeypatch.setattr(ri, 'review', lambda _: {'landed': ['x'], 'problems': [], 'gates': {}, 'fingerprint': 'stable'})
    monkeypatch.setattr(ri, 'info', lambda _: ({'cwd': 'worker'}, [], [], ''))
    monkeypatch.setattr(ri, 'safe_destination', lambda *a: None)
    monkeypatch.setattr(ri, 'port', lambda *a: None)
    monkeypatch.setattr(ri, 'workspace_fingerprint', lambda *a: 'stable')
    monkeypatch.setattr(ri, 'git', lambda *a, **k: subprocess.CompletedProcess([], 0, '', ''))
    def run(cmd, cwd, check=False):
        assert cmd[-1] == 'tools/check_csv.py'
        if check:
            raise SystemExit('fixture invalid ledger')
        return subprocess.CompletedProcess(cmd, 1, '', '')
    monkeypatch.setattr(ri, 'sh', run)
    import pytest
    with pytest.raises(SystemExit, match='invalid ledger'):
        ri.integrate(SimpleNamespace(worktree=str(dest), force=False, keep=False, base='master'))


def test_destination_mutations_are_serialized(tmp_path):
    from concurrent.futures import ThreadPoolExecutor
    from threading import Event
    from types import SimpleNamespace
    first_entered, release, second_entered = Event(), Event(), Event()
    @ri.serialized_destination
    def mutate(args):
        if args.first:
            first_entered.set()
            assert release.wait(3)
        else:
            second_entered.set()
    with ThreadPoolExecutor(max_workers=2) as pool:
        first = pool.submit(mutate, SimpleNamespace(worktree=str(tmp_path / 'dest'), first=True))
        assert first_entered.wait(3)
        second = pool.submit(mutate, SimpleNamespace(worktree=str(tmp_path / 'dest'), first=False))
        try:
            assert not second_entered.wait(.1)
        finally:
            release.set()
        first.result()
        second.result()
    assert second_entered.is_set()


def test_symlink_parent_cannot_redirect_port(tmp_path):
    import pytest
    outside = tmp_path / 'outside'
    outside.mkdir()
    dest = tmp_path / 'dest'
    dest.mkdir()
    (dest / 'game').symlink_to(outside, target_is_directory=True)
    with pytest.raises(SystemExit, match='symlink'):
        ri.safe_port_path(dest, 'game/new.cpp')


def test_review_rejects_concurrent_workspace_edit(tmp_path, monkeypatch):
    from types import SimpleNamespace
    monkeypatch.setattr(ri, 'info', lambda _: ({'cwd': str(tmp_path), 'status': 'completed'}, [], [], ''))
    monkeypatch.setattr(ri, 'changes', lambda _: [])
    monkeypatch.setattr(ri, 'ledger_delta', lambda *a: ([], []))
    monkeypatch.setattr(ri, 'git', lambda *a, **k: subprocess.CompletedProcess([], 0, '', ''))
    fingerprints = iter(['before', 'after'])
    monkeypatch.setattr(ri, 'workspace_fingerprint', lambda _: next(fingerprints))
    result = ri.review(SimpleNamespace(job='fixture'))
    assert any('changed during review' in p for p in result['problems'])


def test_rejected_push_preserves_commit_and_refuses_reset(tmp_path, monkeypatch):
    import pytest
    from types import SimpleNamespace
    fixture = PortTest()
    fixture.setUp()
    try:
        remote = tmp_path / 'remote.git'
        git(fixture.base, 'init', '--bare', '-q', str(remote))
        git(fixture.base, 'remote', 'add', 'origin', str(remote))
        git(fixture.base, 'push', '-q', 'origin', 'master')
        hook = remote / 'hooks/pre-receive'
        hook.write_text('#!/bin/sh\nexit 1\n')
        hook.chmod(0o755)
        ws, dest = fixture.ws, fixture.dest
        raw = (ws / LED).read_bytes().replace(b'?a@@YAXXZ,,0x00000010',
                                              b'?a@@YAXXZ,,0x00000010,8,game/keep.cpp,matched,')
        (ws / LED).write_bytes(raw)
        (ws / 'game/keep.cpp').write_text('int keep() { return 2; }\n')
        monkeypatch.setattr(ri, 'ROOT', fixture.base)
        monkeypatch.setattr(ri, 'gate', lambda *a: (True, 'fixture gate'))
        original_sh = ri.sh
        def fake_check(cmd, cwd, **kwargs):
            if cmd[-1] == 'tools/check_csv.py':
                return subprocess.CompletedProcess(cmd, 0, 'fixture ledger OK', '')
            return original_sh(cmd, cwd, **kwargs)
        monkeypatch.setattr(ri, 'sh', fake_check)
        args = SimpleNamespace(job=None, workspace=str(ws), rva=['0x10'], worktree=str(dest),
                               base='origin/master', force=False, keep=False, dry_run=False,
                               push=True, push_retries=1, title='fixture integration', trailer='', measure=False)
        with pytest.raises(SystemExit, match='commit kept locally'):
            ri.integrate(args)
        retained = ri.git(dest, 'rev-parse', 'HEAD', check=True).stdout
        assert retained != ri.git(dest, 'rev-parse', 'origin/master', check=True).stdout
        assert (dest / 'game/keep.cpp').read_text() == 'int keep() { return 2; }\n'
        with pytest.raises(SystemExit, match='unintegrated commits'):
            ri.integrate(args)
        assert ri.git(dest, 'rev-parse', 'HEAD', check=True).stdout == retained
        # A cooperating integrator is locked out, but an external editor may
        # still change the destination during a gate. Never stage that edit.
        fresh = tmp_path / 'fresh'
        git(fixture.base, 'worktree', 'add', '-q', '--detach', str(fresh), 'origin/master')
        args.worktree, args.push = str(fresh), False
        def changing_gate(cwd, src):
            if Path(cwd) == fresh:
                (fresh / src).write_text('concurrent editor work\n')
            return True, 'fixture gate'
        monkeypatch.setattr(ri, 'gate', changing_gate)
        with pytest.raises(SystemExit, match='destination changed during verification'):
            ri.integrate(args)
        assert (fresh / 'game/keep.cpp').read_text() == 'concurrent editor work\n'
        assert ri.git(fresh, 'diff', '--cached', '--quiet').returncode == 0
    finally:
        fixture.tearDown()
