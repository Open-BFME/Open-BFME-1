#!/usr/bin/env python3
"""Verify and integrate the work an OpenCode router job left in its workspace.

The router (tools/opencode_router.py) runs workers in retained worktrees and
leaves review, verification and commits to the parent. This is that parent
step, and it trusts nothing the worker reported:

  python3 tools/router_integrate.py review JOB_ID
      Independent verdict on the job's workspace: which target rows changed,
      whether every touched source passes its scoped byte gate there, which
      verdicts were recorded, and rule problems (git used, inline asm or naked
      code added, a renamed row, a lift left behind). Exit 0 only when at least
      one target landed and nothing needs a human.

  python3 tools/router_integrate.py integrate JOB_ID [--push] [--measure]
      Ports the job's changes onto a clean detached worktree at origin/master
      (build/wt/integrate by default): source edits as a 3-way patch against
      the job's base, new files copied, deletions applied, ledger rows moved
      line by line (CRLF preserved) so concurrent upstream rows survive. Then
      check_csv, the scoped gate for every touched source, and a normal commit,
      so the repository's commit hooks run the full verification.
      If the hook asks for tools/adopt_header.py --fix-staged it is applied
      once. A name regression is NEVER documented automatically: it stops and
      prints what a reviewer must decide (docs/naming_evidence.md).
      --push rebases and pushes with retries; --measure then records the
      parent-verified result on the job's last attempt.

Workspaces are never modified or deleted.
"""
import argparse, json, os, re, shutil, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGERS = ('targets/game/reverse/functions.csv', 'targets/game/reverse/symbols.csv',
           'targets/game/reverse/deleted_rows.csv', 'targets/game/reverse/re_attempts.log')
CORRECTIONS = 'targets/game/reverse/name_corrections.json'
RVA_LINE = re.compile(r'^- (0x[0-9A-Fa-f]{8})\b', re.M)
NAKED = re.compile(r'__declspec\s*\(\s*naked\s*\)|\b__emit\b|\b__asm\b')
GIT_VERBS = re.compile(r'(?m)^\$ git (add|commit|push|stash|checkout|reset|rebase|rm|mv)\b')


def sh(cmd, cwd, check=False, timeout=None):
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, errors='replace', timeout=timeout)
    if check and r.returncode:
        raise SystemExit(f'{" ".join(map(str, cmd))} failed:\n{r.stdout}{r.stderr}')
    return r


def git(cwd, *args, check=False):
    return sh(['git', *args], cwd, check=check)


def job_info(job):
    r = sh([sys.executable, 'tools/opencode_router.py', 'show', job], ROOT, check=True)
    data = json.loads(r.stdout)
    j = data['jobs'][0]
    attempts = sorted(data['attempts'], key=lambda a: a['started'] or 0)
    rvas = []
    if re.fullmatch(r'0x[0-9A-Fa-f]{1,8}', str(j['target'] or '')):
        rvas.append('0x%08X' % int(j['target'], 16))
    log = ''
    for a in attempts:
        d = Path(a['directory'] or '')
        p = d / 'prompt.txt'
        if p.exists():
            for m in RVA_LINE.findall(p.read_text(errors='replace')):
                if m.upper().replace('0X', '0x') not in rvas:
                    rvas.append(m.upper().replace('0X', '0x'))
        for name in ('events.jsonl', 'stderr.txt'):
            if (d / name).exists():
                log += (d / name).read_text(errors='replace')
    return j, attempts, rvas, log


def changes(ws):
    """(path, status) for every changed path against the workspace base, staged or not."""
    out = []
    for line in git(ws, 'status', '--porcelain', '--untracked-files=all').stdout.splitlines():
        path = line[3:]
        if ' -> ' in path:
            path = path.split(' -> ')[1]
        if path.startswith('build/'):
            continue
        tracked = bool(git(ws, 'ls-tree', 'HEAD', '--', path).stdout.strip())
        exists = (Path(ws) / path).exists()
        out.append((path, 'deleted' if not exists else ('modified' if tracked else 'added')))
    return out


def ledger_delta(ws, path):
    d = git(ws, 'diff', '-U0', 'HEAD', '--', path).stdout
    add = [l[1:].rstrip('\r') for l in d.splitlines() if l.startswith('+') and not l.startswith('+++')]
    rem = [l[1:].rstrip('\r') for l in d.splitlines() if l.startswith('-') and not l.startswith('---')]
    return add, rem


def gate(cwd, src):
    r = sh(['./build.sh', src], cwd, timeout=1800)
    lines = [l for l in (r.stdout + r.stderr).splitlines() if 'fixme' not in l and ('Functions:' in l or 'FAIL' in l)]
    return (not any('FAIL' in l for l in lines)) and any('Functions: OK' in l for l in lines), ' | '.join(lines)[:300]


def code_only(text):
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    return re.sub(r'//[^\n]*', '', text)


def workspace_info(ws, rvas):
    """A prepared worktree that is not a router job (manual or legacy seat work)."""
    return ({'id': None, 'cwd': str(Path(ws).resolve()), 'status': 'workspace', 'target': None}, [],
            ['0x%08X' % int(r, 16) for r in rvas], '')


def info(args):
    if args.workspace:
        if not args.rva:
            raise SystemExit('--workspace needs at least one --rva')
        return workspace_info(args.workspace, args.rva)
    if not args.job:
        raise SystemExit('give a JOB_ID or --workspace PATH --rva 0x...')
    return job_info(args.job)


def review(args):
    j, attempts, rvas, log = info(args)
    job = args.job or j['cwd']
    ws = j['cwd']
    ch = changes(ws)
    fadd, frem = ledger_delta(ws, LEDGERS[0])
    radd, _ = ledger_delta(ws, LEDGERS[3])
    res = {'job': job, 'workspace': ws, 'status': j['status'], 'targets': {}, 'problems': [], 'gates': {}}
    for path, st in ch:
        if st != 'deleted' and path.endswith(('.cpp', '.asm')) and path.startswith('game/'):
            res['gates'][path] = gate(ws, path)
            if st == 'added' and NAKED.search(code_only((Path(ws) / path).read_text(errors='replace'))):
                res['problems'].append(f'{path}: new source contains inline asm/__emit/naked code')
    for rva in rvas:
        key = rva.lower()
        new = [r for r in fadd if f',{key},' in r.lower()]
        old = [r for r in frem if f',{key},' in r.lower()]
        t = {'landed': False}
        if new:
            row = new[-1].split(',')
            src = row[4]
            ok = res['gates'].get(src, gate(ws, src) if (Path(ws) / src).exists() else (False, 'source missing'))
            t.update(landed=ok[0], name=row[0], size=row[3], source=src, gate=ok[1])
            if old and old[-1].split(',')[0] != row[0]:
                t['renamed_from'] = old[-1].split(',')[0]
                res['problems'].append(f'{rva}: row renamed from {t["renamed_from"]} -- check the identity evidence')
            if not ok[0]:
                res['problems'].append(f'{rva}: row changed but its gate fails ({ok[1]})')
        v = [r for r in radd if key in r.lower()]
        if v:
            f = v[-1].split('\t')
            t['verdict'] = f[3] if len(f) > 3 else '?'
            m = re.search(r'score=([0-9.]+)', v[-1])
            if m:
                t['score'] = float(m.group(1))
        res['targets'][rva] = t
    # rows now owned by nothing: a lift left behind or a moved body
    for path, st in ch:
        if st == 'modified' and path.startswith('game/') and path.endswith('.cpp'):
            if NAKED.search(code_only((Path(ws) / path).read_text(errors='replace'))) and any(
                    r.split(',')[4] != path and any(path in o for o in frem) for r in fadd):
                res['problems'].append(f'{path}: still holds naked code after its row moved out')
    if GIT_VERBS.search(log):
        res['problems'].append('worker ran a mutating git command')
    if not rvas:
        res['problems'].append('no target RVA found in the job target or prompt')
    res['landed'] = sorted(r for r, t in res['targets'].items() if t.get('landed'))
    return res


def port(j, dest):
    ws = j['cwd']
    ch = changes(ws)
    ledgers = set(LEDGERS) | {CORRECTIONS}
    tracked = [p for p, s in ch if s != 'added' and p not in ledgers]
    if tracked:
        patch = git(ws, 'diff', '--binary', 'HEAD', '--', *tracked).stdout
        if patch.strip():
            r = subprocess.run(['git', 'apply', '-3', '--whitespace=nowarn'], cwd=dest, input=patch,
                               capture_output=True, text=True)
            if r.returncode:
                raise SystemExit(f'patch does not apply on origin/master:\n{r.stderr}')
            git(dest, 'reset', '-q')
    for p, s in ch:
        if p in ledgers:
            continue
        if s == 'added':
            (Path(dest) / p).parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(Path(ws) / p, Path(dest) / p)
        elif s == 'deleted' and (Path(dest) / p).exists():
            (Path(dest) / p).unlink()
    for led in LEDGERS:
        add, rem = ledger_delta(ws, led)
        if not add and not rem:
            continue
        f = Path(dest) / led
        raw = f.read_text(encoding='utf-8', errors='surrogateescape', newline='') if f.exists() else ''
        nl = '\r\n' if raw.count('\r\n') > raw.count('\n') / 2 else '\n'
        rows = raw.split(nl)
        trail = rows and rows[-1] == ''
        if trail:
            rows = rows[:-1]
        remset = set(rem)
        rows = [r for r in rows if r not in remset]
        have = set(rows)
        rows += [a for a in add if a not in have]
        f.write_text(nl.join(rows) + (nl if trail else ''), encoding='utf-8', errors='surrogateescape', newline='')
    # name_corrections.json: append entries the worker added, keeping the file's format
    old = git(ws, 'show', f'HEAD:{CORRECTIONS}').stdout
    new_path = Path(ws) / CORRECTIONS
    if old and new_path.exists():
        before, after = json.loads(old), json.loads(new_path.read_text(encoding='utf-8'))
        added = [e for e in after if e not in before]
        if added:
            f = Path(dest) / CORRECTIONS
            raw = f.read_text(encoding='utf-8', newline='')
            end = '\r\n]\r\n' if raw.endswith('\r\n]\r\n') else '\n]\n'
            nl = '\r\n' if end.startswith('\r') else '\n'
            ents = [nl.join(' ' + l for l in json.dumps(e, indent=1, ensure_ascii=False).split('\n')) for e in added]
            raw = raw[:-len(end)] + ',' + nl + (',' + nl).join(ents) + end
            json.loads(raw)
            f.write_text(raw, encoding='utf-8', newline='')


def integrate(args):
    rev = review(args)
    print(json.dumps(rev, indent=1))
    if not rev['landed']:
        raise SystemExit('nothing landed in this workspace; nothing to integrate')
    blocking = [p for p in rev['problems'] if 'renamed' not in p and 'mutating git' not in p]
    if blocking and not args.force:
        raise SystemExit('review found problems (rerun with --force after checking them):\n  ' + '\n  '.join(blocking))
    j, attempts, rvas, _ = info(args)
    dest = Path(args.worktree).resolve()
    git(ROOT, 'fetch', '-q', 'origin', 'master', check=True)
    base = args.base
    if not dest.exists():
        git(ROOT, 'worktree', 'add', '-q', '--detach', str(dest), base, check=True)
    git(dest, 'checkout', '-q', '--detach', base, check=True)
    git(dest, 'reset', '-q', '--hard', base, check=True)
    git(dest, 'clean', '-qfd', '-e', 'build/')
    port(j, dest)
    r = sh([sys.executable, 'tools/check_csv.py'], dest)
    print(r.stdout[-600:])
    touched = [l[3:] for l in git(dest, 'status', '--porcelain', '--untracked-files=all').stdout.splitlines()
               if l[3:].endswith(('.cpp', '.asm')) and (dest / l[3:]).exists() and not l[3:].startswith('build/')]
    for src in touched:
        ok, text = gate(str(dest), src)
        print(f'gate {src}: {text}')
        if not ok:
            raise SystemExit(f'scoped gate fails on origin/master for {src}; not committing')
    if args.dry_run:
        print('dry run: ported and gated, not committed')
        return
    landed = rev['landed']
    names = '; '.join(f'{rev["targets"][r]["name"]} at {r} ({rev["targets"][r]["size"]} bytes)' for r in landed)
    models = sorted({a['model'] for a in attempts if a.get('model')})
    origin = f'router job {args.job}' if args.job else 'prepared workspace'
    title = args.title or f'Integrate {origin}: {len(landed)} byte-exact conversion(s)'
    msg = (f'{title}\n\n{names}\n\n'
           + (f'Worker model(s): {", ".join(models)}. ' if models else '')
           + 'Verified independently with tools/router_integrate.py (scoped gates on '
           'origin/master) and the commit hooks.\n')
    if args.trailer:
        msg += '\n' + args.trailer.replace('\\n', '\n') + '\n'
    git(dest, 'add', '-A', '--', 'game', 'targets', check=True)
    c = git(dest, 'commit', '-q', '-m', msg)
    out = c.stdout + c.stderr
    if c.returncode and 'adopt_header.py --fix-staged' in out:
        print('commit hook asks for header adoption; running tools/adopt_header.py --fix-staged once')
        sh([sys.executable, 'tools/adopt_header.py', '--fix-staged'], dest, check=True)
        git(dest, 'add', '-A', '--', 'game', 'targets', check=True)
        c = git(dest, 'commit', '-q', '-m', msg)
        out = c.stdout + c.stderr
    if c.returncode:
        print(out[-3000:])
        if 'descriptive names regressed' in out:
            print('\nA row was renamed to a placeholder. Read the worker\'s identity evidence; if it holds, '
                  'document the correction in targets/game/reverse/name_corrections.json (see '
                  'docs/naming_evidence.md) in this worktree and commit by hand.')
        raise SystemExit('commit hook rejected the integration; worktree left as ported for inspection')
    sha = git(dest, 'rev-parse', 'HEAD').stdout.strip()
    print('committed', sha)
    if not args.push:
        return
    if args.base != 'origin/master':
        raise SystemExit('--push only integrates onto origin/master')
    for _ in range(args.push_retries):
        p = git(dest, 'pull', '-q', '--rebase', 'origin', 'master')
        if p.returncode:
            git(dest, 'rebase', '--abort')
            raise SystemExit('rebase conflict; integration commit kept locally in ' + str(dest))
        if git(dest, 'push', '-q', 'origin', 'HEAD:master').returncode == 0:
            break
    else:
        raise SystemExit('push kept losing the race; integration commit kept locally in ' + str(dest))
    sha = git(dest, 'rev-parse', 'HEAD').stdout.strip()
    print('pushed', sha)
    if args.measure and attempts and args.job:
        delta = sh([sys.executable, 'tools/progress.py', f'{sha}^..{sha}'], dest).stdout
        m = re.search(r'REBUILDS FROM.*?delta ([+-][\d,]+) bytes', delta)
        cmd = [sys.executable, 'tools/opencode_router.py', 'measure', attempts[-1]['id'], '--exact-match', 'yes',
               '--evidence', f'tools/router_integrate.py integrate {args.job}: scoped gates + commit hooks, pushed {sha[:10]}']
        if m:
            cmd += ['--bytes-gained', m.group(1).replace(',', '').lstrip('+')]
        print(sh(cmd, ROOT).stdout)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    r = sub.add_parser('review')
    i = sub.add_parser('integrate')
    for x in (r, i):
        x.add_argument('job', nargs='?')
        x.add_argument('--workspace', help='a prepared worktree instead of a router job')
        x.add_argument('--rva', action='append', default=[], help='target RVA (with --workspace; repeatable)')
    i.add_argument('--title', default='', help='commit title (default: generic)')
    i.add_argument('--base', default='origin/master', help='integration base (default origin/master)')
    i.add_argument('--worktree', default=str(ROOT / 'build' / 'wt' / 'integrate'))
    i.add_argument('--dry-run', action='store_true')
    i.add_argument('--push', action='store_true')
    i.add_argument('--push-retries', type=int, default=8)
    i.add_argument('--measure', action='store_true', help='after --push, record the verified result on the job')
    i.add_argument('--force', action='store_true', help='integrate despite review problems you have checked')
    i.add_argument('--trailer', default='', help='extra commit message trailer lines (\\n separated)')
    a = ap.parse_args(argv)
    if a.cmd == 'review':
        res = review(a)
        print(json.dumps(res, indent=1))
        return 0 if res['landed'] and not res['problems'] else 1
    integrate(a)
    return 0


if __name__ == '__main__':
    sys.exit(main())
