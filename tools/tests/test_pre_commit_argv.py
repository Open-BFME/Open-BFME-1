"""Run the real pre-commit flow with isolated Git/build/guard test doubles."""
import csv
import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest

HOOK = Path(__file__).resolve().parents[2] / '.githooks' / 'pre-commit'


@pytest.fixture
def hook_runner(tmp_path):
    # WindowsApps/bash.exe is a WSL launcher, not the shell Git runs for hooks.
    if os.name == 'nt':
        git = Path(shutil.which('git') or '')
        candidates = [git.parent.parent / 'bin/bash.exe',
                      Path('C:/Program Files/Git/bin/bash.exe')]
        bash = next((str(p) for p in candidates if p.is_file()), None)
    else:
        bash = shutil.which('bash')
    if not bash:
        pytest.skip('Git Bash is required on Windows; Bash is required elsewhere')
    root = tmp_path / 'hook fixture with spaces'
    root.mkdir()
    (root / 'reverse').mkdir()
    (root / 'calls').mkdir()
    (root / 'hook').write_bytes(HOOK.read_bytes())
    (root / 'build.sh').write_text(r'''#!/usr/bin/env bash
set -euo pipefail
n=0
if [ -f calls/count ]; then read -r n < calls/count; fi
n=$((n + 1))
printf '%s\n' "$n" > calls/count
printf '%s\0' "$@" > "calls/$n.args"
printf '%s\n' "${BUILD_POOL-unset}" > "calls/$n.pool"
if [ "$n" -eq "${FAIL_CHUNK:-0}" ]; then exit 23; fi
''', encoding='utf-8', newline='\n')
    (root / 'build.sh').chmod(0o755)
    (root / 'run.sh').write_text(r'''#!/usr/bin/env bash
set -euo pipefail
git() {
        case "$*" in
        'rev-parse --show-toplevel') printf '%s\n' "$PWD" ;;
        'diff --cached --name-only --diff-filter=ACMRT')
            printf '%s\n' reverse/functions.csv
            [ -z "${STAGED_SOURCE:-}" ] || printf '%s\n' "$STAGED_SOURCE"
            ;;
        'diff --cached --name-only --diff-filter=ACMR') return 0 ;;
        'cat-file -e :tools/name_regression.py'|'cat-file -e :tools/name_oracle.py') return 0 ;;
        'diff --quiet -- tools/name_regression.py'|'diff --quiet -- tools/name_oracle.py') return 0 ;;
        'diff --cached --quiet -- reverse/functions.csv') return 1 ;;
        'diff --cached --quiet -- reverse/symbols.csv'|'diff --cached --quiet -- reverse/pin_consistency_baseline.csv') return 0 ;;
        'diff --cached --quiet -- reverse/full_gate_baseline.txt') return 0 ;;
        'diff --quiet -- reverse/functions.csv') return 0 ;;
        'diff --quiet -- '*) return 0 ;;
        'diff --cached --name-only --diff-filter=ACM -- tools/*.py'|'diff --cached --name-only --diff-filter=A') return 0 ;;
        *) printf 'unexpected Git test invocation: %s\n' "$*" >&2; return 92 ;;
    esac
}
python3() {
    if [ "$1" = - ]; then
        printf '%s\n' "$#" >> filter-argc
        "$REAL_PYTHON" "$@"
        return
    fi
    printf '%s\n' "$*" >> guards
    case "$1" in
        tools/delta_sources.py) cat deltas ;;
        tools/find_declared_unmatched.py|tools/adopt_header.py|tools/name_oracle.py|tools/name_regression.py|tools/retired_guard.py) return 0 ;;
        tools/check_case_collisions.py|tools/conversion_gate.py|tools/check_csv.py|tools/pin_consistency.py|tools/identity_guard.py|tools/gate_baseline.py) return 0 ;;
        *) printf 'unexpected Python test invocation: %s\n' "$*" >&2; return 93 ;;
    esac
}
source ./hook
''', encoding='utf-8', newline='\n')

    def run(paths, claimed=None, fail_chunk=0, broken_csv=False, build_pool=None,
            raw_selectors=False, staged_source=None):
        claimed = paths if claimed is None else claimed
        if raw_selectors:
            selectors = paths
        else:
            selected_paths = list(dict.fromkeys(p for p in paths if p in claimed))
            selectors = [f'row:0x{i + 0x1000:08X}:16:{p}'
                         for i, p in enumerate(selected_paths)]
        (root / 'deltas').write_text(''.join(p + '\n' for p in selectors), encoding='utf-8', newline='\n')
        with (root / 'reverse/functions.csv').open('w', encoding='utf-8', newline='') as stream:
            writer = csv.writer(stream)
            writer.writerow(['broken' if broken_csv else 'source', 'status'])
            writer.writerows((path, 'matched') for path in claimed)
        env = os.environ.copy()
        env.update(REAL_PYTHON=Path(sys.executable).as_posix(), FAIL_CHUNK=str(fail_chunk),
                   PYTHONUTF8='1', LC_ALL='C.UTF-8')
        if staged_source:
            path = root / staged_source
            path.parent.mkdir(parents=True, exist_ok=True)
            path.touch()
            env['STAGED_SOURCE'] = staged_source
        env.pop('BUILD_POOL', None)
        if build_pool is not None:
            env['BUILD_POOL'] = build_pool
        result = subprocess.run([bash, 'run.sh'], cwd=root, env=env,
                                capture_output=True, text=True, encoding='utf-8', timeout=60)
        chunks = []
        for file in sorted((root / 'calls').glob('*.args'), key=lambda p: int(p.stem)):
            chunks.append([p.decode('utf-8') for p in file.read_bytes().split(b'\0')[:-1]])
        return result, chunks, root
    return run


def long_paths(count=998):
    return [f"Code/GameEngine/Folder with spaces {i:04}/" + 'long segment/' * (8 + i % 9)
            + "Unicode \u00e9\U0001f30d/[brackets]/quote's file.cpp" for i in range(count)]


def test_many_long_spaced_paths_are_verified_once_in_bounded_chunks(hook_runner):
    paths = long_paths()
    parked = 'Code/GameEngine/parked reconstruction.cpp'
    result, chunks, root = hook_runner(paths + [parked, paths[0]], claimed=paths, build_pool='7')
    expected = [f'row:0x{i + 0x1000:08X}:16:{p}' for i, p in enumerate(paths)]
    assert result.returncode == 0, result.stderr
    assert len(chunks) > 1
    flattened = [p for chunk in chunks for p in chunk]
    assert len(flattened) == len(expected)
    assert set(flattened) == set(expected)
    assert (root / 'filter-argc').read_text().splitlines() == ['2']
    for chunk in chunks:
        assert chunk
        assert sum(2 * len(p.encode('utf-8')) + 3 for p in chunk) <= 24000
        # Check the real Windows quoting rule too, with an oversized launcher prefix.
        command = subprocess.list2cmdline(['p' * 1000, 's' * 1000] + chunk)
        assert len(command.encode('utf-16-le')) // 2 < 32767
    assert all(p.read_text().strip() == '7' for p in (root / 'calls').glob('*.pool'))
    assert '998 verification selector(s) checked' in result.stdout
    assert 'tools/identity_guard.py' in (root / 'guards').read_text()


def test_failed_chunk_stops_without_success_or_later_chunks(hook_runner):
    result, chunks, root = hook_runner(long_paths(), fail_chunk=2)
    assert result.returncode != 0
    assert len(chunks) == 2
    assert sum(map(len, chunks)) < 998
    assert 'byte-verify of changed sources/rows' in result.stderr
    assert 'PRE-COMMIT OK' not in result.stdout
    assert all(p.read_text().strip() == '4' for p in (root / 'calls').glob('*.pool'))


def test_filter_error_fails_closed_without_build(hook_runner):
    result, chunks, _ = hook_runner(['Code/GameEngine/claimed.cpp'], broken_csv=True)
    assert result.returncode != 0
    assert not chunks
    assert 'filtering claimed sources' in result.stderr
    assert 'PRE-COMMIT OK' not in result.stdout


def test_unclaimed_staged_sources_are_removed_without_empty_build(hook_runner):
    source = 'Code/GameEngine/parked reconstruction.cpp'
    result, chunks, root = hook_runner([], claimed=[], staged_source=source)
    assert result.returncode == 0, result.stderr
    assert not chunks
    assert '0 verification selector(s) checked' in result.stdout
    assert 'tools/identity_guard.py' in (root / 'guards').read_text()


def test_no_delta_does_not_invoke_filter_or_build(hook_runner):
    result, chunks, root = hook_runner([])
    assert result.returncode == 0, result.stderr
    assert not chunks
    assert not (root / 'filter-argc').exists()


def test_individually_oversized_path_is_rejected(hook_runner):
    result, chunks, _ = hook_runner(['Code/GameEngine/' + 'x' * 12000 + '.cpp'])
    assert result.returncode != 0
    assert not chunks
    assert 'byte-verify selector exceeds argument limit' in result.stderr


def test_small_delta_remains_one_build(hook_runner):
    paths = ['Code/GameEngine/a.cpp', 'Code/GameEngine/folder with spaces/b.cpp']
    result, chunks, _ = hook_runner(paths)
    assert result.returncode == 0, result.stderr
    assert len(chunks) == 1
    assert set(chunks[0]) == {f'row:0x{i + 0x1000:08X}:16:{p}'
                              for i, p in enumerate(paths)}


def test_changed_staged_source_still_uses_full_source_selector(hook_runner):
    source = 'Code/GameEngine/Edited.cpp'
    result, chunks, _ = hook_runner(['Code/GameEngine/claim.cpp'],
                                   claimed=['Code/GameEngine/claim.cpp', source],
                                   staged_source=source)
    assert result.returncode == 0, result.stderr
    assert len(chunks) == 1
    assert source in chunks[0]
    assert any(selector.startswith('row:') for selector in chunks[0])
