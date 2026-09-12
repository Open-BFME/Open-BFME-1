"""Batch reads preserve the exact committed/staged evidence and fail closed."""
import subprocess
import sys
from pathlib import Path
from unittest.mock import Mock

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_csv


@pytest.fixture
def repo(tmp_path, monkeypatch):
    def git(*args):
        return subprocess.run(['git', '-C', str(tmp_path), *args],
                              check=True, capture_output=True).stdout
    git('init')
    git('config', 'core.autocrlf', 'false')
    git('config', 'user.name', 'Blob test')
    git('config', 'user.email', 'blob@example.invalid')
    monkeypatch.setattr(check_csv, 'ROOT', tmp_path)
    return tmp_path, git


def test_batch_preserves_ref_index_and_worktree(repo):
    root, git = repo
    first, second = root / 'file with spaces.cpp', root / 'empty.cpp'
    original = b'// header\r\nembedded\x00bytes\n'
    first.write_bytes(original)
    second.write_bytes(b'')
    git('add', '--', first.name, second.name)
    git('-c', 'core.hooksPath=/dev/null', 'commit', '-m', 'fixture')
    first.write_bytes(b'staged\r\n')
    git('add', '--', first.name)
    first.write_bytes(b'working tree\n')
    assert check_csv.read_blobs([first, second], 'HEAD') == {first: original, second: b''}
    assert check_csv.read_blobs([first], '') == {first: b'staged\r\n'}
    assert check_csv.read_blobs([first], None) == {first: b'working tree\n'}


def test_missing_committed_blob_never_uses_disk(repo):
    root, git = repo
    path = root / 'only-local.cpp'
    path.write_bytes(b'present only on disk')
    with pytest.raises(SystemExit, match='cannot read'):
        check_csv.read_blobs([path], '')


@pytest.mark.parametrize('output', [b'abc blob 8\nshort\n', b'abc tree 0\n\n',
                                   b'abc blob 0\n\ntrailing', b'abc blob 1\nx!'])
def test_malformed_batch_fails_closed(tmp_path, monkeypatch, output):
    monkeypatch.setattr(check_csv, 'ROOT', tmp_path)
    run = Mock(return_value=subprocess.CompletedProcess([], 0, output, b''))
    monkeypatch.setattr(check_csv.subprocess, 'run', run)
    with pytest.raises(SystemExit):
        check_csv.read_blobs([tmp_path / 'body.cpp'], 'HEAD')


def test_many_blobs_use_one_process(tmp_path, monkeypatch):
    monkeypatch.setattr(check_csv, 'ROOT', tmp_path)
    paths = [tmp_path / f'{n}.cpp' for n in range(30)]
    run = Mock(return_value=subprocess.CompletedProcess([], 0, b'abc blob 1\nx\n' * 30, b''))
    monkeypatch.setattr(check_csv.subprocess, 'run', run)
    assert check_csv.read_blobs(paths, 'HEAD') == dict.fromkeys(paths, b'x')
    run.assert_called_once()


@pytest.mark.parametrize('body,claim,naked,expected', [
    (b'// fn\n// broken score\n', False, False, 'line 2'),
    (b'// fn\n// partial score=0.9 date=2026-09-04\n' + b'x' * 65536,
     False, False, 'over 65536'),
    (b'// fn\n// partial score=0.9 date=2026-09-04\n', True, False,
     'already has real C++'),
    (b'// fn\n// partial score=0.9 date=2026-09-04\n', True, True, None),
], ids=['bad-score', 'oversized', 'landed-orphan', 'naked-placeholder'])
def test_attempt_validation_still_checks_committed_evidence(repo, monkeypatch,
                                                          body, claim, naked, expected):
    root, git = repo
    bank = root / 'reverse/attempts/0x00001000.cpp'
    bank.parent.mkdir(parents=True)
    bank.write_bytes(body)
    ledger = root / 'reverse/functions.csv'
    ledger.write_bytes((check_csv.FUNCTIONS_HEADER + '\r\n' +
                       ('fn,,0x00001000,1,Code/body.cpp,matched,\r\n' if claim else '')).encode())
    source = root / 'Code/body.cpp'
    source.parent.mkdir()
    source.write_text('__declspec(naked) void fn() {}' if naked else 'void fn() {}')
    git('add', '--', 'reverse', 'Code/body.cpp')
    # Staged gate must read the staged bank even if the disk copy is replaced.
    bank.write_bytes(b'unrelated unstaged text')
    monkeypatch.setattr(check_csv, 'FUNCTIONS', ledger)
    problems = []
    assert check_csv.check_attempts('', problems) == 1
    if expected:
        assert any(expected in problem for problem in problems), problems
    else:
        assert problems == []


@pytest.mark.parametrize('staged_naked', [True, False],
                         ids=['naked-index-real-worktree',
                              'real-index-naked-worktree'])
def test_attempt_sources_use_index_and_deduplicate_shared_source(repo, monkeypatch,
                                                                staged_naked):
    root, git = repo
    attempts = root / 'reverse/attempts'
    attempts.mkdir(parents=True)
    bank_body = b'// fn\n// partial score=0.9 date=2026-09-04\n'
    for rva in ('0x00001000', '0x00002000'):
        (attempts / f'{rva}.cpp').write_bytes(bank_body)

    ledger = root / 'reverse/functions.csv'
    ledger.write_bytes((check_csv.FUNCTIONS_HEADER + '\r\n' +
                        'first,,0x00001000,1,Code/shared.cpp,matched,\r\n' +
                        'second,,0x00002000,1,Code/shared.cpp,matched,\r\n').encode())
    source = root / 'Code/shared.cpp'
    source.parent.mkdir()
    naked = '__declspec(naked) void fn() {}'
    real = 'void fn() {}'
    source.write_text(naked if staged_naked else real)
    git('add', '--', 'reverse', 'Code/shared.cpp')
    source.write_text(real if staged_naked else naked)

    monkeypatch.setattr(check_csv, 'FUNCTIONS', ledger)
    original = check_csv.read_blobs
    batches = []

    def recording_read_blobs(paths, spec):
        paths = list(paths)
        batches.append(paths)
        return original(paths, spec)

    monkeypatch.setattr(check_csv, 'read_blobs', recording_read_blobs)
    problems = []
    assert check_csv.check_attempts('', problems) == 2
    orphan_problems = [problem for problem in problems
                       if 'already has real C++' in problem]
    assert len(orphan_problems) == (0 if staged_naked else 2), problems
    assert len(batches) == 2
    assert batches[1] == [source]
