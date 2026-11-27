"""Rule B protects readable C/C++ ownership, not prebuilt binary coverage.

These fixtures run the actual gate over historical Git blobs and the staged
index. Other native gates remain responsible for byte and archive validity.
"""
import contextlib
import io
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import conversion_gate as gate

HEADER = 'name,export_rva,target_rva,target_size,source,status,notes\n'
NAME = '?f@@YAHXZ'
CPP = b'int f() { return 1; }\n'
# Binary contents are deliberately not UTF-8 source text. Rule B should never
# treat the prebuilt archive as readable C++ or try to parse it as such.
ARCHIVE = b'!<arch>\n\x00\x80\xff\x00\x00'
ASM = b'.386\n.model flat\n_TEXT SEGMENT\nf PROC\n    ret\nf ENDP\n_TEXT ENDS\nEND\n'
NAKED = b'// ?f@@YAHXZ\n__declspec(naked) int f() { __asm { ret } }\n'
LEDGER = 'targets/game/reverse/functions.csv'


def row(source, *, status='matched'):
    return f'{NAME},,0x00401000,4,{source},{status},\n'


def git(repo, *args):
    return subprocess.run(['git', '-C', str(repo), *args], check=True,
                          capture_output=True, text=True).stdout.strip()


@pytest.fixture
def change(tmp_path, monkeypatch):
    repo = tmp_path / 'repo'
    repo.mkdir()
    git(repo, 'init', '-q')
    git(repo, 'config', 'core.autocrlf', 'false')
    monkeypatch.chdir(repo)

    def write(path, data):
        target = repo / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data.encode() if isinstance(data, str) else data)

    def commit():
        git(repo, 'add', '-A')
        git(repo, '-c', 'user.name=gate fixture', '-c',
            'user.email=gate@example.invalid', 'commit', '-qm', 'fixture')
        return git(repo, 'rev-parse', 'HEAD')

    def prepare(old_source, old_data, new_source, new_data, *, staged,
                new_status='matched'):
        write(old_source, old_data)
        write(LEDGER, HEADER + row(old_source))
        before = commit()
        write(new_source, new_data)
        write(LEDGER, HEADER + row(new_source, status=new_status))
        git(repo, 'add', '-A')
        return before, ':' if staged else commit()

    return prepare


def verdict(monkeypatch, before, after):
    monkeypatch.setattr(sys, 'argv', ['conversion_gate.py', before, after])
    error = io.StringIO()
    with contextlib.redirect_stderr(error):
        code = gate.main()
    return code, error.getvalue()


@pytest.mark.parametrize('staged', [False, True])
@pytest.mark.parametrize('archive', ['inputs/vendor/runtime.lib',
                                     'inputs/vendor/runtime.LIB'])
def test_binary_archive_to_assembly_does_not_lose_readable_cpp(change, monkeypatch,
                                                             staged, archive):
    before, after = change(archive, ARCHIVE, 'game/masm_dumps/CompilerHelper.asm',
                           ASM, staged=staged)
    assert gate.clean_coverage_lost(before, after) == []
    code, error = verdict(monkeypatch, before, after)
    assert code == 0, error


@pytest.mark.parametrize('staged', [False, True])
def test_binary_archive_to_real_cpp_is_a_conversion(change, monkeypatch, staged):
    before, after = change('inputs/vendor/runtime.lib', ARCHIVE,
                           'game/Libraries/Source/Runtime.cpp', CPP, staged=staged)
    assert gate.clean_coverage_lost(before, after) == []
    code, error = verdict(monkeypatch, before, after)
    assert code == 0, error


@pytest.mark.parametrize('staged', [False, True])
@pytest.mark.parametrize('source', ['game/Game.cpp',
                                    'game/Libraries/Source/Runtime.c',
                                    'inputs/reference/runtime/Runtime.CXX'])
def test_real_cpp_in_game_or_library_source_cannot_be_replaced_by_assembly(
        change, monkeypatch, staged, source):
    before, after = change(source, CPP, 'game/masm_dumps/Replacement.asm', ASM,
                           staged=staged)
    assert gate.clean_coverage_lost(before, after)
    code, error = verdict(monkeypatch, before, after)
    assert code == 1 and 'was clean C++' in error, error


@pytest.mark.parametrize('staged', [False, True])
@pytest.mark.parametrize('replacement', ['inputs/vendor/replacement.lib',
                                        'inputs/vendor/replacement.LIB',
                                        'game/masm_dumps/Replacement.s',
                                        'game/masm_dumps/Replacement.S',
                                        'game/masm_dumps/Replacement.ASM'])
def test_archive_or_assembly_suffix_cannot_keep_lost_cpp_coverage(
        change, monkeypatch, staged, replacement):
    data = ARCHIVE if replacement.lower().endswith('.lib') else ASM
    before, after = change('game/Game.cpp', CPP, replacement, data, staged=staged)
    assert gate.clean_coverage_lost(before, after)
    code, error = verdict(monkeypatch, before, after)
    assert code == 1 and 'was clean C++' in error, error


@pytest.mark.parametrize('staged', [False, True])
def test_naked_cpp_suffix_does_not_keep_readable_cpp_coverage(change, monkeypatch,
                                                           staged):
    before, after = change('game/Game.cpp', CPP, 'game/Replacement.cpp', NAKED,
                           staged=staged)
    assert gate.clean_coverage_lost(before, after)
    code, error = verdict(monkeypatch, before, after)
    assert code == 1 and 'was clean C++' in error, error
    assert 'adds a naked' in error, error


@pytest.mark.parametrize('staged', [False, True])
def test_a_retracted_cpp_claim_is_not_a_live_reversal(change, monkeypatch, staged):
    before, after = change('game/Game.cpp', CPP, 'game/masm_dumps/Replacement.asm',
                           ASM, staged=staged, new_status='unmatched')
    assert gate.clean_coverage_lost(before, after) == []
    code, error = verdict(monkeypatch, before, after)
    assert code == 0, error
