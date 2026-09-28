#!/usr/bin/env python3
"""router_integrate.port: moves a router workspace's work onto a newer base.

Covers the failure modes met while integrating router/Zen workers by hand:
staged-only edits (a worker that ran `git add`), deletions of lift files and
banked attempts, CRLF ledgers where upstream appended rows concurrently, and
name_corrections.json entries.
"""
import json, subprocess, sys, tempfile, unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import router_integrate as ri

LED = 'targets/game/reverse/functions.csv'


def git(cwd, *a):
    subprocess.run(['git', *a], cwd=cwd, check=True, capture_output=True)


class PortTest(unittest.TestCase):
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
