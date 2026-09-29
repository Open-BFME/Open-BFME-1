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
        # a worker's scratch variants beside the stash are not banked evidence
        (self.ws / 'targets/game/reverse/attempts/0x00000020_v2.cpp').write_text('int f2;\n')
        hist = self.ws / 'targets/game/reverse/attempt_history/0x00000020'
        hist.mkdir(parents=True); (hist / 'retired-landing.cpp').write_text('int f3;\n')
        ri.bank(args); ri.bank(args)  # idempotent
        self.assertFalse((self.dest / 'targets/game/reverse/attempts/0x00000020_v2.cpp').exists())
        self.assertFalse((self.dest / 'targets/game/reverse/attempt_history/0x00000020/retired-landing.cpp').exists())
        self.assertEqual((self.dest / log).read_bytes(),
                         b'old\t0x00000001\r\n?f\t0x00000020\t9\tpartial\tnear miss\r\n')
        self.assertTrue((self.dest / 'targets/game/reverse/attempts/0x00000020.cpp').exists())
        self.assertFalse((self.dest / 'targets/game/reverse/attempts/0x00000030.cpp').exists())

    def test_bank_keeps_the_better_measured_stash_and_always_ports_verdicts(self):
        # re_log keeps the better measured stash in attempts/<rva>.cpp (header line 2),
        # so a worker's stash conflicts with origin's whenever either side re-banked.
        # Before: bank refused every such job and its verdict rows never reached origin.
        log = 'targets/game/reverse/re_attempts.log'
        stash = 'targets/game/reverse/attempts/0x00000020.cpp'
        body = lambda score: f'// ?f\n// partial score={score} date=2026-09-28\nint f;\n'
        (self.base / log).write_bytes(b'old\t0x00000001\r\n')
        (self.base / stash).parent.mkdir(parents=True)
        (self.base / stash).write_text(body('0.8'))
        git(self.base, 'add', '-A'); git(self.base, 'commit', '-q', '-m', 'bank')
        for tree in (self.ws, self.dest):
            git(tree, 'checkout', '-q', '--detach', 'master')
        args = type('A', (), dict(job=None, workspace=str(self.ws), rva=['0x20'], worktree=str(self.dest),
                                  base='master', force=False))()
        row = b'?f\t0x00000020\t9\tpartial\tworse\r\n'
        (self.ws / log).write_bytes(b'old\t0x00000001\r\n' + row)
        (self.ws / stash).write_text(body('0.5'))
        ri.bank(args)
        self.assertEqual((self.dest / stash).read_text(), body('0.8'))  # origin's better bank kept
        self.assertTrue((self.dest / log).read_bytes().endswith(row))
        better = b'?f\t0x00000020\t9\tpartial\tbetter\r\n'
        (self.ws / log).write_bytes(b'old\t0x00000001\r\n' + row + better)
        (self.ws / stash).write_text(body('0.97'))
        ri.bank(args)
        self.assertEqual((self.dest / stash).read_text(), body('0.97'))  # worker's better bank taken
        self.assertTrue((self.dest / log).read_bytes().endswith(row + better))
        (self.ws / stash).write_text('int f; // no score header\n')
        with self.assertRaises(SystemExit):  # an unranked body is never chosen by guess
            ri.bank(args)
        self.assertEqual((self.dest / stash).read_text(), body('0.97'))

    def test_route(self):
        # attempt_history is evidence (JSON, notes), never a source: a worker's compilable
        # copy there was gated as a touched source and stopped job 0bbbe3cc's landing
        self.assertEqual(ri.route('targets/game/reverse/attempt_history/0x00927360/winning-landing.cpp'), 'scratch')
        # attempts/ holds exactly one stash per target, named by its RVA (check_csv refuses others):
        # a worker's sweep files there (job cd56dcbf left eight _rotsweep_*.cpp) are scratch
        self.assertEqual(ri.route('targets/game/reverse/attempts/_rotsweep_170344cfe2.cpp'), 'scratch')
        self.assertEqual(ri.route('targets/game/reverse/attempts/0x0036a570.cpp'), 'port')
        self.assertEqual(ri.route('targets/game/reverse/attempt_history/0x00927360/' + 'a' * 64 + '.json'), 'port')
        self.assertEqual(ri.route('targets/game/reverse/attempt_history/0x0019bf40/20260922-review.md'), 'port')
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
    def fake_gate(ws, selector, env=None, rows=()):
        # one build.py run over several selectors passes only when each would
        calls.extend((selector, *rows))
        results = [gates.get(s, (False, 'fixture: unknown selector ' + s)) for s in (selector, *rows)]
        return all(ok for ok, _ in results), ' | '.join(text for _, text in results)
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


def test_gate_passes_exact_rows_to_the_same_build_run(monkeypatch):
    seen = []
    monkeypatch.setattr(ri, 'sh', lambda cmd, *a, **k: seen.append(cmd) or subprocess.CompletedProcess(
        cmd, 0, 'Functions: OK 3/3 matched\n', ''))
    assert ri.gate('.', 'game/a.cpp', rows=['row:0x00000010:4:?f@@YAXXZ'])[0]
    assert seen == [['./build.sh', 'game/a.cpp', 'row:0x00000010:4:?f@@YAXXZ']]


def _counting_review(tmp_path, monkeypatch, rows, gates, changed=(('game/shared.cpp', 'modified'),)):
    """review() whose fake build records each build.py invocation as a tuple of selectors."""
    from types import SimpleNamespace
    (tmp_path / 'game').mkdir(exist_ok=True)
    for path, _ in changed:
        (tmp_path / path).write_text('void f() {}')
    (tmp_path / 'game/shared.cpp').write_text('void f() {}')
    rvas = ['0x%08X' % int(r.split(',')[2], 16) for r in rows]
    monkeypatch.setattr(ri, 'info', lambda _: ({'cwd': str(tmp_path), 'status': 'completed'}, [], rvas, ''))
    monkeypatch.setattr(ri, 'changes', lambda _: list(changed))
    monkeypatch.setattr(ri, 'ledger_delta', lambda ws, path: (rows, []) if path == LED else ([], []))
    monkeypatch.setattr(ri, 'git', lambda *a, **k: subprocess.CompletedProcess([], 0, '', ''))
    runs = []
    def fake_gate(ws, selector, env=None, rows=()):
        runs.append((selector, *rows))
        results = [gates.get(s, (False, 'fixture: unknown selector ' + s)) for s in (selector, *rows)]
        return all(ok for ok, _ in results), ' | '.join(text for _, text in results)
    monkeypatch.setattr(ri, 'gate', fake_gate)
    return ri.review(SimpleNamespace(job='fixture')), runs


def test_review_verifies_the_target_selector_inside_its_source_gate(tmp_path, monkeypatch):
    # Reuse only within one build run on one snapshot: the source's rows and the
    # exact selector (with its exactly-one-row check) are both still verified.
    rows = ['?t@@YAXXZ,,0x00000020,5,game/shared.cpp,matched,proof',
            '?u@@YAXXZ,,0x00000030,7,game/shared.cpp,matched,proof']
    sel = ['row:0x00000020:5:?t@@YAXXZ', 'row:0x00000030:7:?u@@YAXXZ']
    result, runs = _counting_review(tmp_path, monkeypatch, rows,
                                    {'game/shared.cpp': (True, 'ok'), sel[0]: (True, 'ok'), sel[1]: (True, 'ok')})
    assert runs == [('game/shared.cpp', *sel)]
    assert result['landed'] == ['0x00000020', '0x00000030']
    assert result['problems'] == []
    # a target whose row source the worker did not touch is gated with its selector too
    result, runs = _counting_review(tmp_path, monkeypatch, rows[:1],
                                    {'game/shared.cpp': (True, 'ok'), sel[0]: (True, 'ok')}, changed=())
    assert runs == [('game/shared.cpp', sel[0])]
    assert result['landed'] == ['0x00000020']


def test_review_splits_a_failed_combined_gate_to_attribute_it(tmp_path, monkeypatch):
    rows = ['?t@@YAXXZ,,0x00000020,5,game/shared.cpp,matched,proof']
    sel = 'row:0x00000020:5:?t@@YAXXZ'
    # the exact selector fails, the siblings pass: the old verdict and problem text
    result, runs = _counting_review(tmp_path, monkeypatch, rows,
                                    {'game/shared.cpp': (True, 'ok'), sel: (False, 'byte mismatch')})
    assert runs == [('game/shared.cpp', sel), ('game/shared.cpp',), (sel,)]
    assert result['landed'] == []
    assert result['gates']['game/shared.cpp'][0] is True
    assert result['targets']['0x00000020']['outcome'] == 'matched row but its exact row selector fails'
    assert any(sel in p and 'byte mismatch' in p for p in result['problems'])
    # a sibling fails: the source gate is red, the target never lands
    result, runs = _counting_review(tmp_path, monkeypatch, rows,
                                    {'game/shared.cpp': (False, 'sibling red'), sel: (True, 'ok')})
    assert runs == [('game/shared.cpp', sel), ('game/shared.cpp',)]
    assert result['landed'] == []
    assert result['targets']['0x00000020']['outcome'] == 'matched row but its source gate fails'
    assert any('touched source gate fails' in p for p in result['problems'])


def test_review_detects_a_workspace_edit_during_the_combined_gate(tmp_path, monkeypatch):
    from types import SimpleNamespace
    ws = tmp_path / 'ws'
    (ws / 'game').mkdir(parents=True)
    git(tmp_path, 'init', '-q', str(ws))
    git(ws, 'config', 'user.email', 't@t'); git(ws, 'config', 'user.name', 't')
    (ws / 'game/shared.cpp').write_text('void f() {}\n')
    git(ws, 'add', '-A'); git(ws, 'commit', '-q', '-m', 'base')
    (ws / 'game/shared.cpp').write_text('void f() { }\n')
    row = '?t@@YAXXZ,,0x00000020,5,game/shared.cpp,matched,proof'
    monkeypatch.setattr(ri, 'info', lambda _: ({'cwd': str(ws), 'status': 'completed'}, [], ['0x00000020'], ''))
    monkeypatch.setattr(ri, 'ledger_delta', lambda w, path: ([row], []) if path == LED else ([], []))
    monkeypatch.setattr(ri, 'added_naked', lambda *a: False)
    def editing_gate(cwd, selector, env=None, rows=()):
        (ws / 'game/shared.cpp').write_text('void f() { /* concurrent editor */ }\n')
        return True, 'fixture gate'
    monkeypatch.setattr(ri, 'gate', editing_gate)
    result = ri.review(SimpleNamespace(job='fixture'))
    assert any('changed during review' in p for p in result['problems'])


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


REAL_HOOK = Path(__file__).resolve().parents[2] / '.githooks/pre-push'


def real_race_guard():
    """The real pre-push hook up to and including its advertised-tip ancestry
    guard; the expensive validators after it are omitted."""
    lines = REAL_HOOK.read_text().splitlines(keepends=True)
    end = next(i for i, l in enumerate(lines) if l.strip() == 'base="$remote_sha"')
    assert lines[end + 1].strip() == 'fi'
    return ''.join(lines[:end + 2]) + '    echo "PRE-PUSH OK"\ndone <<< "$refs"\n'


class PublishRealHookTest(PublishFixture):
    """publish() against the real hook's PUSH RACE guard, with a racer landing
    a commit after publish()'s pull and before its push."""
    def setUp(self):
        super().setUp()
        shebang, rest = real_race_guard().split('\n', 1)
        script = self.dest / '.git/hooks/pre-push'
        script.write_text('%s\nprintf x >> "%s"\n%s' % (shebang, self.counter, rest))
        script.chmod(0o755)

    def racer_lands(self, times):
        """A publish() check that advances origin on its first `times` calls."""
        left = Path(self.tmp.name) / 'left'
        left.write_text('x' * times)
        return [['sh', '-c', 'if [ -s "%s" ]; then printf %%s "$(tail -c +2 "%s")" > "%s"; '
                 'git -C "%s" pull -q --rebase origin master && '
                 'git -C "%s" commit -q --allow-empty -m race && git -C "%s" push -q origin HEAD:master; fi'
                 % (left, left, left, self.racer, self.racer, self.racer)]]

    def assert_integration_kept_locally(self):
        self.assertEqual((self.dest / 'a').read_text(), 'integration\n')
        self.assertEqual(git_out(self.dest, 'log', '-1', '--format=%s'), 'integration')
        self.assertEqual(git_out(self.dest, 'show', 'HEAD:a'), 'integration')

    def test_advertised_tip_race_is_rebased_and_retried(self):
        self.assertEqual(ri.publish(self.dest, 8, checks=self.racer_lands(1)), 2)
        self.assertEqual(self.attempts(), 2)
        log = git_out(self.origin, 'log', '--format=%s', 'master')
        self.assertEqual(log.split('\n'), ['integration', 'race', 'base'])
        self.assertEqual(git_out(self.origin, 'show', 'master:a'), 'integration')
        self.assert_integration_kept_locally()

    def test_consecutive_races_stop_at_the_bound(self):
        with self.assertRaises(SystemExit) as cm:
            ri.publish(self.dest, 3, checks=self.racer_lands(5))
        message = str(cm.exception)
        self.assertIn('kept losing the race over 3 attempt(s)', message)
        self.assertIn('integration commit kept locally', message)
        self.assertIn('PUSH RACE', message)
        self.assertEqual(self.attempts(), 3)
        self.assert_integration_kept_locally()
        self.assertNotIn('integration', git_out(self.origin, 'log', '--format=%s', 'master'))

    def test_validation_failure_after_the_guard_stops_once(self):
        script = self.dest / '.git/hooks/pre-push'
        script.write_text(script.read_text().replace(
            'echo "PRE-PUSH OK"', 'fail "byte verification failed for game/x.cpp"'))
        with self.assertRaises(SystemExit) as cm:
            ri.publish(self.dest, 8)
        message = str(cm.exception)
        self.assertIn('PRE-PUSH FAILED: byte verification failed for game/x.cpp', message)
        self.assertIn('not a stale-base race', message)
        self.assertEqual(self.attempts(), 1)
        self.assert_integration_kept_locally()


@pytest.mark.parametrize('output', [
    ' ! [rejected]        HEAD -> master (fetch first)\nerror: failed to push some refs\n'
    'hint: Updates were rejected because the remote contains work that you do not\n',
    ' ! [rejected]        HEAD -> master (non-fast-forward)\nerror: failed to push some refs\n'
    'hint: Updates were rejected because the tip of your current branch is behind\n',
    ' ! [rejected]        HEAD -> master (stale info)\nerror: failed to push some refs\n',
    " ! [remote rejected] HEAD -> master (cannot lock ref 'refs/heads/master': is at "
    "1111111111111111111111111111111111111111 but expected 2222222222222222222222222222222222222222)\n",
    'PRE-PUSH FAILED: PUSH RACE: destination refs/heads/master at 1111111 is not an ancestor of 2222222; '
    'rebase and retry (validation not run)\nerror: failed to push some refs\n',
    'PRE-PUSH FAILED: PUSH RACE: destination refs/heads/master advanced before verification; retry\n',
])
def test_proven_stale_base_output_is_a_race(output):
    assert ri.is_push_race(output)


@pytest.mark.parametrize('output', [
    'PRE-PUSH FAILED: byte verification failed\nerror: failed to push some refs\n',
    'PRE-PUSH FAILED: ledger integrity at 2222222 (see above)\n',
    "remote: Permission to o/r.git denied to u.\n"
    "fatal: unable to access 'https://x/': The requested URL returned error: 403\n",
    'git@host: Permission denied (publickey).\nfatal: Could not read from remote repository.\n',
    "fatal: could not read Username for 'https://github.com': terminal prompts disabled\n",
    "fatal: unable to access 'https://x/': Could not resolve host: x\n",
    'error: RPC failed; curl 56 Recv failure: Connection reset by peer\nfatal: early EOF\n',
    # the hook could not fetch the advertised tip: a transport failure, not proof it moved
    "fatal: unable to access 'https://x/': Could not resolve host: x\n"
    'PRE-PUSH FAILED: PUSH RACE: cannot inspect destination refs/heads/master at 1111111; retry\n',
    'PRE-PUSH FAILED: PUSH RACE: destination tip 1111111 is unavailable; retry\n',
    # a lock error without "is at X but expected Y" does not show the ref moved
    " ! [remote rejected] HEAD -> master (cannot lock ref 'refs/heads/master': "
    "Unable to create '/srv/o.git/refs/heads/master.lock': File exists.)\n",
    "fatal: Unable to create '/w/.git/index.lock': File exists.\n",
    'error: failed to lock refs/heads/master\n',
    # a validator failure alongside a race-looking line is still a validation failure
    ' ! [rejected]        HEAD -> master (non-fast-forward)\nPRE-PUSH FAILED: byte verification failed\n',
])
def test_other_push_failures_are_not_races(output):
    assert not ri.is_push_race(output)


@pytest.mark.parametrize('text, diagnosis', [
    ("fatal: could not read Username for 'https://github.com': terminal prompts disabled", 'could not read Username'),
    ('fatal: unable to access: Could not resolve host: example.invalid', 'Could not resolve host'),
    ('error: RPC failed; curl 56 Connection reset by peer', 'Connection reset by peer'),
    ('PRE-PUSH FAILED: PUSH RACE: cannot inspect destination refs/heads/master at 1111111; retry', 'cannot inspect'),
    ("fatal: Unable to create '/w/.git/index.lock': File exists.", 'index.lock'),
])
def test_auth_transport_and_lock_failures_stop_once_with_diagnosis(text, diagnosis):
    fixture = PublishFixture()
    fixture.setUp()
    try:
        fixture.hook('cat >/dev/null\necho "%s" >&2\nexit 1' % text.replace('"', '\\"'))
        with pytest.raises(SystemExit) as cm:
            ri.publish(fixture.dest, 8)
        message = str(cm.value)
        assert diagnosis in message
        assert 'not a stale-base race' in message
        assert fixture.attempts() == 1
        assert git_out(fixture.dest, 'show', 'HEAD:a') == 'integration'
        assert git_out(fixture.dest, 'log', '-1', '--format=%s') == 'integration'
    finally:
        fixture.tearDown()


def git_out(cwd, *a):
    return subprocess.run(['git', *a], cwd=cwd, check=True, capture_output=True, text=True).stdout.strip()


def snapshot(tree):
    """Exact HEAD, index entries, status and file bytes of a worktree."""
    tree = Path(tree)
    status = subprocess.run(['git', 'status', '--porcelain=v1', '-z', '--untracked-files=all'], cwd=tree,
                            check=True, capture_output=True, text=True).stdout
    return {'head': git_out(tree, 'rev-parse', 'HEAD'),
            'index': git_out(tree, 'ls-files', '-s'),
            'status': sorted(e for e in status.split('\0') if e),
            'files': {p.relative_to(tree).as_posix(): p.read_bytes() for p in sorted(tree.rglob('*'))
                      if p.is_file() and p.name != '.git'}}


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
    from contextlib import nullcontext
    monkeypatch.setattr(ri, 'staged_view', lambda *a: nullcontext())
    def run(cmd, cwd, check=False, **_):
        assert cmd[-1] == 'tools/check_csv.py'
        if check:
            raise SystemExit('fixture invalid ledger')
        return subprocess.CompletedProcess(cmd, 1, '', '')
    monkeypatch.setattr(ri, 'sh', run)
    import pytest
    with pytest.raises(SystemExit, match='invalid ledger'):
        ri.integrate(SimpleNamespace(worktree=str(dest), force=False, keep=False, dry_run=False, base='master'))


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
        monkeypatch.setattr(ri, 'gate', lambda *a, **k: (True, 'fixture gate'))
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
        before = snapshot(fresh)
        args.worktree, args.push = str(fresh), False
        def changing_gate(cwd, src, env=None, rows=()):
            if Path(cwd) == fresh:
                (fresh / src).write_text('concurrent editor work\n')
            return True, 'fixture gate'
        monkeypatch.setattr(ri, 'gate', changing_gate)
        with pytest.raises(SystemExit, match='destination changed during verification') as aborted:
            ri.integrate(args)
        # the message names what the editor changed and where it is retained
        assert f'Retained unstaged in {fresh}' in str(aborted.value)
        assert '\n  game/keep.cpp\n' in str(aborted.value)
        # HEAD and the index are exactly as before: nothing of the port or the
        # editor's work was staged or committed ...
        after = snapshot(fresh)
        assert after['head'] == before['head'] == git_out(fixture.base, 'rev-parse', 'origin/master')
        assert after['index'] == before['index']
        assert git_out(fresh, 'diff', '--cached', '--name-status') == ''
        # ... and the worktree holds the editor's bytes plus the rest of the port, unstaged
        assert after['status'] == [' M game/keep.cpp', ' M ' + LED]
        assert after['files'] == dict(before['files'], **{
            'game/keep.cpp': b'concurrent editor work\n',
            # the fixture's 3-field rows carry no size (rva_of), so the changed row is appended
            LED: b'name,export_rva,target_rva\r\n?lift@@YAXXZ,,0x00000020\r\n'
                 b'?a@@YAXXZ,,0x00000010,8,game/keep.cpp,matched,\r\n'})
        # no private index was left behind in the worktree's git dir
        gitdir = Path(git_out(fresh, 'rev-parse', '--absolute-git-dir'))
        assert not list(gitdir.glob('router-integrate-index.*'))
    finally:
        fixture.tearDown()


class BatchFixture(PortFixture):
    """The real integrate() over two prepared workspaces and a bare origin, with
    the byte gates and check_csv faked. Both fakes record what they saw through
    the environment integrate() gives them."""
    ROW1 = b'?a@@YAXXZ,,0x00000010,8,game/keep.cpp,matched,'
    ROW2 = b'?lift@@YAXXZ,,0x00000020,8,game/two.cpp,matched,'

    def setUp(self):
        super().setUp()
        from unittest import mock
        root = Path(self.tmp.name)
        remote = root / 'remote.git'
        git(self.base, 'init', '--bare', '-q', str(remote))
        git(self.base, 'remote', 'add', 'origin', str(remote))
        git(self.base, 'push', '-q', 'origin', 'master')
        git(self.base, 'fetch', '-q', 'origin')
        self.origin_head = git_out(self.base, 'rev-parse', 'origin/master')
        self.base_led = (self.base / LED).read_bytes()
        # job 1 improves keep.cpp and matches its row
        (self.ws / 'game/keep.cpp').write_text('int keep() { return 2; }\n')
        (self.ws / LED).write_bytes(self.base_led.replace(b'?a@@YAXXZ,,0x00000010', self.ROW1))
        # job 2 replaces the lift with clean source and matches the lift's row
        self.ws2 = root / 'ws2'
        git(self.base, 'worktree', 'add', '-q', '--detach', str(self.ws2), 'HEAD')
        (self.ws2 / 'game/two.cpp').write_text('void lift() {}\n')
        (self.ws2 / 'game/lift.cpp').unlink()
        (self.ws2 / LED).write_bytes(self.base_led.replace(b'?lift@@YAXXZ,,0x00000020', self.ROW2))
        self.gates, self.tracked = [], []
        dest = self.dest
        def fake_gate(cwd, src, env=None, rows=()):
            if Path(cwd) != Path(self.ws) and Path(cwd) != self.ws2:
                self.gates.append((Path(cwd), src, (Path(cwd) / src).read_bytes(),
                                   bool(env and env.get('GIT_INDEX_FILE'))))
            return True, 'fixture gate'
        original_sh = ri.sh
        def fake_sh(cmd, cwd, **kwargs):
            if cmd[-1] == 'tools/check_csv.py':
                # check_csv lists tracked files: it must see the port staged
                self.tracked.append(subprocess.run(['git', 'ls-files', 'game'], cwd=cwd, check=True, text=True,
                                                   capture_output=True, env=kwargs.get('env')).stdout.split())
                return subprocess.CompletedProcess(cmd, 0, 'fixture ledger OK', '')
            return original_sh(cmd, cwd, **kwargs)
        for name, value in (('ROOT', self.base), ('gate', fake_gate), ('sh', fake_sh)):
            patcher = mock.patch.object(ri, name, value)
            patcher.start()
            self.addCleanup(patcher.stop)

    def args(self, ws, rva, **kw):
        from types import SimpleNamespace
        a = dict(job=None, workspace=str(ws), rva=[rva], worktree=str(self.dest), base='origin/master',
                 force=False, keep=True, dry_run=False, push=False, push_retries=1, title='batch',
                 trailer='', measure=False)
        a.update(kw)
        return SimpleNamespace(**a)

    def assert_clean_index(self, snap):
        self.assertEqual(snap['head'], self.origin_head)
        self.assertEqual(snap['index'], git_out(self.base, 'ls-files', '-s'))  # the base commit's index
        self.assertEqual(git_out(self.dest, 'diff', '--cached', '--name-status'), '')


class BatchTest(BatchFixture):
    def test_successive_keep_batches_commit_exactly_both_jobs(self):
        ri.integrate(self.args(self.ws, '0x10'))
        snap = snapshot(self.dest)
        self.assert_clean_index(snap)
        self.assertEqual(snap['status'], [' M game/keep.cpp', ' M ' + LED])
        self.assertEqual(snap['files']['game/keep.cpp'], b'int keep() { return 2; }\n')
        # the fixture's 3-field rows carry no size (rva_of), so a changed row is appended
        self.assertEqual(snap['files'][LED], b'name,export_rva,target_rva\r\n?lift@@YAXXZ,,0x00000020\r\n'
                                             + self.ROW1 + b'\r\n')
        self.assertEqual(self.tracked[-1], ['game/keep.cpp', 'game/lift.cpp'])
        # the second batch is accepted on top of the first and re-verifies the whole batch
        self.gates.clear()
        ri.integrate(self.args(self.ws2, '0x20'))
        snap = snapshot(self.dest)
        self.assert_clean_index(snap)
        self.assertEqual(snap['status'], [' D game/lift.cpp', ' M game/keep.cpp', ' M ' + LED, '?? game/two.cpp'])
        both = b'name,export_rva,target_rva\r\n' + self.ROW1 + b'\r\n' + self.ROW2 + b'\r\n'
        self.assertEqual(snap['files'][LED], both)
        self.assertEqual(snap['files']['game/two.cpp'], b'void lift() {}\n')
        self.assertNotIn('game/lift.cpp', snap['files'])
        self.assertEqual(self.tracked[-1], ['game/keep.cpp', 'game/two.cpp'])  # staged view: lift gone, two added
        self.assertEqual(sorted((src, staged) for _, src, _, staged in self.gates),
                         [('game/keep.cpp', True), ('game/two.cpp', True)])
        # the reviewer commits the batch: it holds exactly both jobs
        git(self.dest, 'add', '-A'); git(self.dest, 'commit', '-qm', 'batch')
        self.assertEqual(git_out(self.dest, 'rev-parse', 'HEAD~1'), self.origin_head)
        self.assertEqual(sorted(git_out(self.dest, 'diff-tree', '--no-commit-id', '-r', '--name-status',
                                        'HEAD').splitlines()),
                         ['A\tgame/two.cpp', 'D\tgame/lift.cpp', 'M\tgame/keep.cpp', 'M\t' + LED])
        self.assertEqual(subprocess.run(['git', 'show', 'HEAD:' + LED], cwd=self.dest, check=True,
                                        capture_output=True).stdout, both)
        self.assertEqual(snapshot(self.dest)['status'], [])

    def test_edits_between_keep_batches_are_retained_not_staged(self):
        ri.integrate(self.args(self.ws, '0x10'))
        # an editor touches a ported file and an unrelated file between batches
        (self.dest / 'game/keep.cpp').write_text('editor\n')
        (self.dest / 'docs').mkdir()
        (self.dest / 'docs/notes.md').write_text('editor notes\n')
        before = snapshot(self.dest)
        with self.assertRaisesRegex(SystemExit, 'outside the ported set; nothing ported') as cm:
            ri.integrate(self.args(self.ws2, '0x20'))
        self.assertIn('docs/notes.md', str(cm.exception))
        after = snapshot(self.dest)
        self.assertEqual(after, before)
        self.assert_clean_index(after)
        self.assertEqual(after['status'], [' M game/keep.cpp', ' M ' + LED, '?? docs/notes.md'])
        self.assertEqual(after['files']['game/keep.cpp'], b'editor\n')
        # the editor also changes the lift job 2 deletes: that edit is never unlinked
        (self.dest / 'docs/notes.md').unlink(); (self.dest / 'docs').rmdir()
        (self.dest / 'game/lift.cpp').write_text('editor lift\n')
        before = snapshot(self.dest)
        with self.assertRaisesRegex(SystemExit, 'worker deleted game/lift.cpp, which holds a retained change'):
            ri.integrate(self.args(self.ws2, '0x20'))
        self.assertEqual(snapshot(self.dest), before)
        # with the lift restored, the edited ported file joins the batch and is gated with the editor's bytes
        (self.dest / 'game/lift.cpp').write_bytes((self.base / 'game/lift.cpp').read_bytes())
        self.gates.clear()
        ri.integrate(self.args(self.ws2, '0x20'))
        snap = snapshot(self.dest)
        self.assert_clean_index(snap)
        self.assertEqual(snap['status'], [' D game/lift.cpp', ' M game/keep.cpp', ' M ' + LED, '?? game/two.cpp'])
        self.assertEqual(snap['files']['game/keep.cpp'], b'editor\n')
        self.assertIn((self.dest, 'game/keep.cpp', b'editor\n', True), self.gates)

    def test_dry_run_leaves_the_destination_byte_identical(self):
        # a clean destination, then one holding a --keep batch: neither is touched
        for keep_first in (False, True):
            if keep_first:
                ri.integrate(self.args(self.ws, '0x10'))
            before = snapshot(self.dest)
            worktrees = git_out(self.base, 'worktree', 'list', '--porcelain')
            self.gates.clear()
            ri.integrate(self.args(self.ws2, '0x20', keep=False, dry_run=True))
            self.assertEqual(snapshot(self.dest), before)
            self.assertEqual(git_out(self.base, 'worktree', 'list', '--porcelain'), worktrees)
            self.assertEqual(sorted(p.name for p in self.dest.parent.iterdir() if 'dry-run' in p.name), [])
            # it really ported and gated, elsewhere, on the base
            self.assertEqual([(src, staged) for _, src, _, staged in self.gates], [('game/two.cpp', True)])
            self.assertNotEqual(self.gates[0][0], self.dest)
        with self.assertRaisesRegex(SystemExit, 'cannot combine with --keep'):
            ri.integrate(self.args(self.ws2, '0x20', keep=True, dry_run=True))
        self.assertEqual(snapshot(self.dest), before)
