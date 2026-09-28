"""The pre-push hook must select EVERY edited claimed source for byte verification.

The unchanged-ledger source-edit path used to ask Git for `game/*.cpp` and
`game/*.c` only, so a `.cc`, `.cxx` or `.asm` edit whose ledger row did not
change went out unverified. The ledger owns the set of claimed sources; the
hook intersects changed `game/` paths with it and keeps no suffix list of its
own. This runs the hook's actual inline selector script in a temporary
repository.
"""
import re
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
LEDGER = 'targets/game/reverse/functions.csv'
SUFFIXES = ('cpp', 'c', 'cc', 'cxx', 'asm')


def selector_script():
    text = (ROOT / '.githooks' / 'pre-push').read_text(encoding='utf-8')
    # the heredoc opener is continued by one shell line (`|| { ...; }`) before the script starts
    m = re.search(r'python3 - "\$base" "\$local_sha" > "\$edited_out" <<\'PY\' \\\n[^\n]*\n(.*?)\nPY\n', text, re.S)
    assert m, 'the edited-claimed-sources selector script was not found in .githooks/pre-push'
    return m.group(1)


def git(repo, *args):
    return subprocess.run(['git', '-C', str(repo), *args], check=True, capture_output=True, text=True).stdout.strip()


@pytest.fixture
def repo(tmp_path):
    git(tmp_path, 'init', '-q', '-b', 'master')
    git(tmp_path, 'config', 'user.name', 'fixture')
    git(tmp_path, 'config', 'user.email', 'fixture@example.invalid')
    (tmp_path / 'game').mkdir()
    (tmp_path / 'targets/game/reverse').mkdir(parents=True)
    rows = ['name,export_rva,target_rva,size,source,status,notes']
    for i, suffix in enumerate(SUFFIXES):
        (tmp_path / f'game/{suffix}_body.{suffix}').write_text(f'// {suffix} v1\n')
        rows.append(f'?f{i}@@YAXXZ,,0x{0x10 * (i + 1):08X},5,game/{suffix}_body.{suffix},matched,')
    (tmp_path / 'game/unclaimed.cc').write_text('// v1\n')
    (tmp_path / 'game/investigation.cxx').write_text('// v1\n')
    rows.append('?u@@YAXXZ,,0x00000100,5,game/investigation.cxx,unmatched,')
    (tmp_path / LEDGER).write_text('\n'.join(rows) + '\n')
    git(tmp_path, 'add', '-A')
    git(tmp_path, 'commit', '-qm', 'base')
    return tmp_path


def selected(repo, base, rev):
    r = subprocess.run([sys.executable, '-', base, rev], input=selector_script(), cwd=repo,
                       capture_output=True, text=True, check=True)
    return r.stdout.split()


def test_every_edited_claimed_source_is_selected_whatever_its_suffix(repo):
    base = git(repo, 'rev-parse', 'HEAD')
    for suffix in SUFFIXES:
        (repo / f'game/{suffix}_body.{suffix}').write_text(f'// {suffix} v2\n')
    (repo / 'game/unclaimed.cc').write_text('// v2\n')
    (repo / 'game/investigation.cxx').write_text('// v2\n')
    git(repo, 'commit', '-qam', 'edit every source, no ledger change')
    rev = git(repo, 'rev-parse', 'HEAD')
    assert selected(repo, base, rev) == sorted(f'game/{s}_body.{s}' for s in SUFFIXES)


def test_untouched_sources_are_not_selected(repo):
    base = git(repo, 'rev-parse', 'HEAD')
    (repo / 'game/cxx_body.cxx').write_text('// v2\n')
    git(repo, 'commit', '-qam', 'one edit')
    assert selected(repo, base, git(repo, 'rev-parse', 'HEAD')) == ['game/cxx_body.cxx']


def test_the_hook_keeps_no_suffix_list_of_its_own():
    text = (ROOT / '.githooks' / 'pre-push').read_text(encoding='utf-8')
    assert '"game/*.cpp"' not in text and '"game/*.c"' not in text
