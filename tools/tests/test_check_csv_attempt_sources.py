"""Immutable-ref attempt checks batch source evidence without changing its state."""
import subprocess
import sys
from pathlib import Path
from unittest.mock import Mock

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_csv


@pytest.fixture
def attempt_repo(tmp_path, monkeypatch):
    def git(*args):
        return subprocess.run(['git', '-C', str(tmp_path), *args],
                              check=True, capture_output=True).stdout
    git('init')
    git('config', 'core.autocrlf', 'false')
    git('config', 'user.name', 'Attempt source test')
    git('config', 'user.email', 'attempt@example.invalid')
    monkeypatch.setattr(check_csv, 'ROOT', tmp_path)
    ledger = tmp_path / 'reverse/functions.csv'
    monkeypatch.setattr(check_csv, 'FUNCTIONS', ledger)

    def populate(source_body=b'__declspec(naked) void fn() {}', count=3,
                 source='Code/shared source.cpp', bank_body=None, commit_source=True):
        bank_dir = tmp_path / 'reverse/attempts'
        bank_dir.mkdir(parents=True)
        body = bank_body if bank_body is not None else b'// fn\n// partial score=0.9 date=2026-09-04\n'
        for i in range(count):
            (bank_dir / f'0x{0x1000+i:08x}.cpp').write_bytes(body)
        ledger.write_bytes((check_csv.FUNCTIONS_HEADER + '\r\n' + ''.join(
            f'fn{i},,0x{0x1000+i:08x},1,{source},matched,\r\n'
            for i in range(count))).encode())
        code = tmp_path / source
        code.parent.mkdir(parents=True, exist_ok=True)
        code.write_bytes(source_body)
        git('add', '--', 'reverse')
        if commit_source:
            git('add', '--', source)
        git('commit', '-m', 'attempt snapshot')
        return git('rev-parse', 'HEAD').decode().strip(), code, bank_dir
    return tmp_path, git, populate


def test_immutable_ref_keeps_committed_banks_and_sources_and_batches_once(attempt_repo, monkeypatch):
    root, git, populate = attempt_repo
    sha, code, banks = populate(count=12)
    # Both index and worktree now disagree with the immutable evidence.
    code.write_bytes(b'void fn() {}')
    git('add', '--', code.relative_to(root).as_posix())
    code.write_bytes(b'working tree differs again')
    for bank in banks.iterdir():
        bank.write_bytes(b'bad working-tree metadata')
    original = check_csv.subprocess.run
    calls = Mock(wraps=original)
    monkeypatch.setattr(check_csv.subprocess, 'run', calls)
    problems = []
    assert check_csv.check_attempts(sha, problems) == 12
    assert problems == []
    batches = [call for call in calls.call_args_list if 'cat-file' in call.args[0]]
    assert len(batches) == 2  # Existing bank batch plus one unique-source batch.
    assert batches[1].kwargs['input'] == f'{sha}:Code/shared source.cpp\n'.encode()
    assert not any('show' in call.args[0] and
                   call.args[0][-1].endswith(':Code/shared source.cpp')
                   for call in calls.call_args_list)


def test_committed_clean_source_is_still_an_orphan_despite_naked_disk_copy(attempt_repo):
    root, git, populate = attempt_repo
    sha, code, banks = populate(source_body=b'void fn() {}', count=2)
    code.write_bytes(b'__declspec(naked) void fn() {}')
    problems = []
    assert check_csv.check_attempts(sha, problems) == 2
    assert len(problems) == 2
    assert all('already has real C++' in problem for problem in problems)


@pytest.mark.parametrize('spec', [None, '', 'HEAD'], ids=['worktree', 'index', 'symbolic-ref'])
def test_mutable_modes_keep_original_source_reads(attempt_repo, monkeypatch, spec):
    root, git, populate = attempt_repo
    sha, code, banks = populate(count=1)
    code.write_bytes(b'void fn() {}')
    if spec == '':
        git('add', '--', code.relative_to(root).as_posix())
    read = Mock(wraps=check_csv.read_ledger)
    monkeypatch.setattr(check_csv, 'read_ledger', read)
    problems = []
    check_csv.check_attempts(spec, problems)
    assert bool(problems) == (spec != 'HEAD')
    read.assert_any_call(code, spec)
    # A later working/index edit is observed on the next invocation.
    code.write_bytes(b'__declspec(naked) void fn() {}')
    if spec == '':
        git('add', '--', code.relative_to(root).as_posix())
    problems = []
    check_csv.check_attempts(spec, problems)
    assert problems == []


def test_missing_committed_source_fails_without_reading_disk(attempt_repo):
    root, git, populate = attempt_repo
    sha, code, banks = populate(commit_source=False, count=1)
    assert code.exists()
    with pytest.raises(SystemExit, match='cannot read'):
        check_csv.check_attempts(sha, [])


def test_bad_score_does_not_trigger_unreachable_source_read(attempt_repo):
    root, git, populate = attempt_repo
    sha, code, banks = populate(commit_source=False, count=1,
                               bank_body=b'// fn\n// bad score\n')
    problems = []
    assert check_csv.check_attempts(sha, problems) == 1
    assert len(problems) == 1 and 'line 2' in problems[0]


@pytest.mark.parametrize('suffix', ['.asm', '.s', '.lib'])
def test_binary_placeholders_need_no_cpp_source_evidence(attempt_repo, suffix):
    root, git, populate = attempt_repo
    sha, code, banks = populate(commit_source=False, count=1,
                               source='Code/binary'+suffix)
    problems = []
    assert check_csv.check_attempts(sha, problems) == 1
    assert problems == []
