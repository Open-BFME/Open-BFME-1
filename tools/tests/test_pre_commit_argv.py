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
    (root / 'targets/game/reverse').mkdir(parents=True)
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
        'config --get merge.union.driver') printf '%s\n' 'python3 tools/merge_rows.py %O %A %B %P' ;;
        'rev-parse --show-toplevel') printf '%s\n' "$PWD" ;;
        'rev-parse --git-path bfme-ledger-verified-tree') printf '%s\n' ledger-verified-tree ;;
        'write-tree') if [ -f index-tree ]; then cat index-tree; else printf '%s\n' 0123456789abcdef0123456789abcdef01234567; fi ;;
        'diff --quiet -- tools/check_csv.py tools/b_pin_check.py') return "${DIRTY_CHECKER:-0}" ;;
        'diff --cached --name-only --diff-filter=ACMRT')
            printf '%s\n' targets/game/reverse/functions.csv
            [ -z "${STAGED_SOURCE:-}" ] || printf '%s\n' "$STAGED_SOURCE"
            ;;
        'diff --cached --name-only --diff-filter=ACMR') return 0 ;;
        'cat-file -e :tools/target_hooks.py'|'cat-file -e :tools/name_regression.py'|'cat-file -e :tools/name_oracle.py') return 0 ;;
        'diff --quiet -- tools/name_regression.py'|'diff --quiet -- tools/name_oracle.py') return 0 ;;
        'diff --cached --quiet -- targets/game/reverse/functions.csv') return 1 ;;
        'diff --cached --quiet -- targets/game/reverse/symbols.csv'|'diff --cached --quiet -- targets/game/reverse/pin_consistency_baseline.csv') return 0 ;;
        'diff --cached --quiet -- targets/game/reverse/full_gate_baseline.txt') return 0 ;;
        'diff --quiet -- targets/game/reverse/functions.csv') return 0 ;;
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
        tools/b_pin_check.py) [ -z "${LATE_STAGE:-}" ] || printf '%s\n' feedfacefeedfacefeedfacefeedfacefeedface > index-tree; return 0 ;;
        tools/target_hooks.py|tools/eol_guard.py|tools/doc_budget.py|tools/link_debt.py|tools/ea_name_guard.py|tools/name_lane.py) return 0 ;;
        tools/header_dependents.py) if [ -f header_deps ]; then cat header_deps; fi; return "${HEADER_RC:-0}" ;;
        *) printf 'unexpected Python test invocation: %s\n' "$*" >&2; return 93 ;;
    esac
}
source ./hook
''', encoding='utf-8', newline='\n')

    def run(paths, claimed=None, fail_chunk=0, broken_csv=False, build_pool=None,
            raw_selectors=False, staged_source=None, header_deps=None, header_rc=0,
            late_stage=False, dirty_checker=False, stale_receipt=False):
        claimed = paths if claimed is None else claimed
        if raw_selectors:
            selectors = paths
        else:
            selected_paths = list(dict.fromkeys(p for p in paths if p in claimed))
            selectors = [f'row:0x{i + 0x1000:08X}:16:{p}'
                         for i, p in enumerate(selected_paths)]
        (root / 'deltas').write_text(''.join(p + '\n' for p in selectors), encoding='utf-8', newline='\n')
        with (root / 'targets/game/reverse/functions.csv').open('w', encoding='utf-8', newline='') as stream:
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
        if header_deps is not None:
            (root / 'header_deps').write_text(''.join(p + '\n' for p in header_deps),
                                              encoding='utf-8', newline='\n')
        env['HEADER_RC'] = str(header_rc)
        if late_stage:
            env['LATE_STAGE'] = '1'
        env['DIRTY_CHECKER'] = '1' if dirty_checker else '0'
        if stale_receipt:
            (root / 'ledger-verified-tree').write_text('0123456789abcdef0123456789abcdef01234567\n')
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
    return [f"game/GameEngine/Folder with spaces {i:04}/" + 'long segment/' * (8 + i % 9)
            + "Unicode \u00e9\U0001f30d/[brackets]/quote's file.cpp" for i in range(count)]


def test_many_long_spaced_paths_are_verified_once_in_bounded_chunks(hook_runner):
    paths = long_paths()
    parked = 'game/GameEngine/parked reconstruction.cpp'
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
    assert not (root / 'ledger-verified-tree').exists()  # a failed hook never records


def test_filter_error_fails_closed_without_build(hook_runner):
    result, chunks, _ = hook_runner(['game/GameEngine/claimed.cpp'], broken_csv=True)
    assert result.returncode != 0
    assert not chunks
    assert 'filtering claimed sources' in result.stderr
    assert 'PRE-COMMIT OK' not in result.stdout


def test_unclaimed_staged_sources_are_removed_without_empty_build(hook_runner):
    source = 'game/GameEngine/parked reconstruction.cpp'
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
    result, chunks, _ = hook_runner(['game/GameEngine/' + 'x' * 12000 + '.cpp'])
    assert result.returncode != 0
    assert not chunks
    assert 'byte-verify selector exceeds argument limit' in result.stderr


def test_small_delta_remains_one_build(hook_runner):
    paths = ['game/GameEngine/a.cpp', 'game/GameEngine/folder with spaces/b.cpp']
    result, chunks, root = hook_runner(paths)
    assert result.returncode == 0, result.stderr
    assert len(chunks) == 1
    # both ledger checks ran on this tree: post-commit may skip its re-check
    assert (root / 'ledger-verified-tree').read_text().strip() == '0123456789abcdef0123456789abcdef01234567'
    assert set(chunks[0]) == {f'row:0x{i + 0x1000:08X}:16:{p}'
                              for i, p in enumerate(paths)}


def test_changed_staged_source_still_uses_full_source_selector(hook_runner):
    source = 'game/GameEngine/Edited.cpp'
    result, chunks, _ = hook_runner(['game/GameEngine/claim.cpp'],
                                   claimed=['game/GameEngine/claim.cpp', source],
                                   staged_source=source)
    assert result.returncode == 0, result.stderr
    assert len(chunks) == 1
    assert source in chunks[0]
    assert any(selector.startswith('row:') for selector in chunks[0])


def test_bounded_header_change_verifies_only_its_dependents(hook_runner):
    deps = ['game/A.cpp', 'game/B.cpp']
    result, chunks, root = hook_runner([], staged_source='game/Inc/Low.h', header_deps=deps)
    assert result.returncode == 0, result.stderr
    assert 'scoped gate over 2 dependent source(s)' in result.stderr
    assert deps in chunks
    assert 'tools/gate_baseline.py --check' not in (root / 'guards').read_text()


def test_unbounded_included_source_runs_the_full_gate(hook_runner):
    result, chunks, root = hook_runner([], staged_source='game/Inc/Included.cpp', header_rc=2)
    assert result.returncode == 0, result.stderr
    assert 'running FULL gate' in result.stderr
    assert 'tools/gate_baseline.py --check' in (root / 'guards').read_text()


def test_unbounded_header_change_runs_the_full_gate(hook_runner):
    result, chunks, root = hook_runner([], staged_source='game/Inc/Low.h', header_rc=2)
    assert result.returncode == 0, result.stderr
    assert 'running FULL gate' in result.stderr
    assert 'tools/gate_baseline.py --check' in (root / 'guards').read_text()


RECEIPT_TREE = '0123456789abcdef0123456789abcdef01234567'
PATHS = ['game/GameEngine/a.cpp']


def test_receipt_records_the_tree_the_checks_read(hook_runner):
    result, _, root = hook_runner(PATHS)
    assert result.returncode == 0, result.stderr
    assert (root / 'ledger-verified-tree').read_text().strip() == RECEIPT_TREE
    assert not list(root.glob('ledger-verified-tree.tmp.*'))  # written atomically, nothing left over


def test_index_changed_after_the_checks_leaves_no_receipt(hook_runner):
    # review 2026-09-29: a pin deletion staged after b_pin_check passed was committed
    # as tree B while the receipt named B, and post-commit skipped its re-check
    result, _, root = hook_runner(PATHS, late_stage=True)
    assert result.returncode == 0, result.stderr
    assert not (root / 'ledger-verified-tree').exists()


def test_checker_with_unstaged_edits_leaves_no_receipt(hook_runner):
    result, _, root = hook_runner(PATHS, dirty_checker=True)
    assert result.returncode == 0, result.stderr
    assert not (root / 'ledger-verified-tree').exists()


def test_stale_receipt_is_cleared_even_when_the_hook_fails(hook_runner):
    result, _, root = hook_runner(long_paths(), fail_chunk=2, stale_receipt=True)
    assert result.returncode != 0
    assert not (root / 'ledger-verified-tree').exists()
