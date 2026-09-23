#!/usr/bin/env python3
"""Check each commit in a pushed range for descriptive-name regressions.

Usage: python3 tools/name_history.py OLD NEW

The endpoint check in name_regression.py protects source moves across a push.
This check also catches a regression hidden by a later restoration in the same
push, and can run in CI when a contributor has not installed the local hooks.
"""
import argparse
import subprocess
from pathlib import Path

import name_regression


ROOT = Path(__file__).resolve().parents[1]


def git(root, *args):
    return subprocess.run(
        ['git', *args], cwd=root, check=True, capture_output=True, text=True
    ).stdout.strip()


def check(root, old, new):
    base = git(root, 'merge-base', old, new)
    commits = git(root, 'rev-list', '--reverse', '--topo-order', f'{base}..{new}').splitlines()
    findings = []
    accepted = 0
    for commit in commits:
        parent = git(root, 'rev-parse', f'{commit}^')
        current, count = name_regression.check(root, parent, commit)
        findings.extend((commit, finding) for finding in current)
        accepted += count
    return commits, findings, accepted


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('old', help='remote/base commit')
    parser.add_argument('new', help='new head commit')
    args = parser.parse_args(argv)
    try:
        commits, findings, accepted = check(ROOT, args.old, args.new)
    except (ValueError, subprocess.CalledProcessError) as exc:
        print(f'name_history: {exc}')
        return 1
    for commit, finding in findings:
        print(f'  {commit[:12]} {finding.old_path} -> {finding.new_path}: '
              f'{finding.old_name} -> {finding.new_name}')
    print(f'name_history: {len(findings)} regression(s) across '
          f'{len(commits)} commit(s), {accepted} documented correction(s)')
    return bool(findings)


if __name__ == '__main__':
    raise SystemExit(main())
