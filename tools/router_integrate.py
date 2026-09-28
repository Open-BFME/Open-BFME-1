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
      --keep ports on top of whatever the worktree already holds and stops
      before committing, so several reviewed jobs become one batch commit.

Workspaces are never modified or deleted.
"""
import argparse, hashlib, json, os, re, shutil, subprocess, sys
from functools import wraps
from portable_lock import lock, unlock
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGERS = ('targets/game/reverse/functions.csv', 'targets/game/reverse/symbols.csv',
           'targets/game/reverse/deleted_rows.csv', 'targets/game/reverse/re_attempts.log')
CORRECTIONS = 'targets/game/reverse/name_corrections.json'
RVA_LINE = re.compile(r'^- (0x[0-9A-Fa-f]{8})\b', re.M)
NAKED = re.compile(r'__declspec\s*\(\s*naked\s*\)|\b__emit\b|\b__asm\b')
GIT_VERBS = re.compile(r'(?m)^\$ git (add|commit|push|stash|checkout|reset|rebase|rm|mv)\b')
# Every changed path is routed explicitly; nothing is dropped in silence. A
# worker's shim-header edit that the port left behind let the hook pass on
# the working tree while the commit could not compile (2026-09-27, batch 5).
PORTED = ('game/', 'worldbuilder/', 'targets/', 'inputs/reference/shims/')
GUTTED_INDEX = 200  # staged deletions of files still on disk: a worker emptied its index


def sh(cmd, cwd, check=False, timeout=None):
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, errors='surrogateescape', timeout=timeout)
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
    # a follow-up job is keyed fu-0xRVA (one target per job, so the RVA is unambiguous)
    m = re.fullmatch(r'(?:fu-)?(0x[0-9A-Fa-f]{1,8})', str(j['target'] or ''))
    if m:
        rvas.append('0x%08X' % int(m.group(1), 16))
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
    # Porcelain -z emits destination then origin for renames/copies. Never
    # split on lines or decode Git's quoted display format.
    fields = iter(git(ws, 'status', '--porcelain=v1', '-z',
                      '--untracked-files=all', check=True).stdout.split('\0'))
    paths = []
    for entry in fields:
        if not entry:
            continue
        status, path = entry[:2], entry[3:]
        paths.append(path)
        if 'R' in status or 'C' in status:
            origin = next(fields)
            if 'R' in status:
                paths.append(origin)
    out = []
    for path in dict.fromkeys(paths):
        if path.startswith('build/'):
            continue
        tracked = bool(git(ws, 'ls-tree', '-z', 'HEAD', '--', path, check=True).stdout)
        exists = os.path.lexists(Path(ws) / path)
        out.append((path, 'deleted' if not exists else ('modified' if tracked else 'added')))
    return out


def workspace_fingerprint(ws):
    digest = hashlib.sha256(git(ws, 'rev-parse', 'HEAD', check=True).stdout.encode())
    for path, status in changes(ws):
        digest.update(os.fsencode(path) + b'\0' + status.encode() + b'\0')
        file = Path(ws) / path
        if file.is_symlink():
            digest.update(b'link\0' + os.fsencode(os.readlink(file)))
        elif file.is_file():
            digest.update(str(file.stat().st_mode).encode() + b'\0' + file.read_bytes())
    return digest.hexdigest()


def safe_port_path(root, path):
    # Git pathnames are relative, but a symlinked parent can escape the tree.
    relative = Path(path)
    if relative.is_absolute() or '..' in relative.parts:
        raise SystemExit(f'unsafe worker path: {path}')
    current = Path(root)
    for part in relative.parts:
        current /= part
        if current.is_symlink():
            raise SystemExit(f'symlink in port path: {path}; review manually')


def route(path):
    """'port', 'scratch' (an untracked top-level file such as aim.cod) or 'refuse'."""
    if path.startswith(PORTED):
        return 'port'
    return 'scratch' if '/' not in path else 'refuse'


def added_naked(ws, path):
    """Inline asm/naked code on lines the worker added to a tracked file (comments ignored)."""
    d = git(ws, 'diff', '-U0', 'HEAD', '--', path).stdout
    return bool(NAKED.search(code_only('\n'.join(l[1:] for l in d.splitlines()
                                                 if l.startswith('+') and not l.startswith('+++')))))


def rva_of(row):
    f = row.split(',')
    return f[2].lower() if len(f) > 3 and f[2].lower().startswith('0x') else None


def ledger_delta(ws, path):
    d = git(ws, 'diff', '-U0', 'HEAD', '--', path).stdout
    add = [l[1:].rstrip('\r') for l in d.splitlines() if l.startswith('+') and not l.startswith('+++')]
    rem = [l[1:].rstrip('\r') for l in d.splitlines() if l.startswith('-') and not l.startswith('---')]
    return add, rem


def gate(cwd, src):
    r = sh(['./build.sh', src], cwd, timeout=1800)
    lines = [l for l in (r.stdout + r.stderr).splitlines() if 'fixme' not in l and ('Functions:' in l or 'FAIL' in l)]
    return (r.returncode == 0 and not any('FAIL' in l for l in lines)
            and any('Functions: OK' in l for l in lines)), f'exit={r.returncode}: ' + ' | '.join(lines)[:300]


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
    fingerprint = workspace_fingerprint(ws)
    ch = changes(ws)
    fadd, frem = ledger_delta(ws, LEDGERS[0])
    radd, _ = ledger_delta(ws, LEDGERS[3])
    res = {'job': job, 'workspace': ws, 'status': j['status'], 'targets': {}, 'problems': [], 'gates': {}}
    for path, st in ch:
        if route(path) == 'refuse':
            res['problems'].append(f'{path}: changed outside {", ".join(PORTED)}; the port does not carry it')
        if st != 'deleted' and path.endswith(('.cpp', '.asm')) and path.startswith('game/'):
            res['gates'][path] = gate(ws, path)
            if not res['gates'][path][0]:
                res['problems'].append(f'{path}: touched source gate fails ({res["gates"][path][1]})')
            if st == 'added' and NAKED.search(code_only((Path(ws) / path).read_text(errors='replace'))):
                res['problems'].append(f'{path}: new source contains inline asm/__emit/naked code')
            elif st == 'modified' and path.endswith('.cpp') and added_naked(ws, path):
                res['problems'].append(f'{path}: the worker added inline asm/__emit/naked code')
    gutted = [l for l in git(ws, 'diff', '--cached', '--name-only', '--diff-filter=D').stdout.splitlines()
              if (Path(ws) / l).exists()]
    if len(gutted) > GUTTED_INDEX:
        res['problems'].append(f'index gutted: {len(gutted)} staged deletions of files still on disk')
    for rva in rvas:
        key = rva.lower()
        new = [r for r in fadd if f',{key},' in r.lower()]
        old = [r for r in frem if f',{key},' in r.lower()]
        t = {'landed': False}
        if new:
            row = new[-1].split(',')
            src = row[4]
            if src not in res['gates']:
                res['gates'][src] = gate(ws, src) if (Path(ws) / src).exists() else (False, 'source missing')
            ok = res['gates'][src]
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
    if fingerprint != workspace_fingerprint(ws):
        res['problems'].append('workspace changed during review; rerun on a stable snapshot')
    res['fingerprint'] = fingerprint
    res['landed'] = sorted(r for r, t in res['targets'].items() if t.get('landed'))
    return res


def port(j, dest):
    ws = j['cwd']
    ch = changes(ws)
    refused = [p for p, s in ch if route(p) == 'refuse']
    if refused:
        raise SystemExit('workspace changed paths the port does not carry:\n  ' + '\n  '.join(refused))
    for p, s in ch:
        if route(p) == 'scratch':
            print(f'skipping top-level scratch file {p}')
    ch = [(p, s) for p, s in ch if route(p) == 'port']
    for path, _status in ch:
        safe_port_path(ws, path)
        safe_port_path(dest, path)
    ledgers = set(LEDGERS) | {CORRECTIONS}
    # Check every addition before applying any part of the worker patch.
    for p, status in ch:
        if status == 'added' and p not in ledgers and os.path.lexists(Path(dest) / p):
            src, dst = Path(ws) / p, Path(dest) / p
            if (src.is_symlink() or dst.is_symlink() or not src.is_file() or not dst.is_file()
                    or src.read_bytes() != dst.read_bytes()
                    or (src.stat().st_mode & 0o111) != (dst.stat().st_mode & 0o111)):
                raise SystemExit(f'upstream addition conflicts with worker path: {p}')
    tracked = [p for p, s in ch if s != 'added' and p not in ledgers]
    if tracked:
        # bytes, never text: universal-newline decoding strips the CRs of a CRLF
        # source, and the patch then no longer applies to the identical blob
        patch = subprocess.run(['git', 'diff', '--binary', 'HEAD', '--', *tracked], cwd=ws,
                               capture_output=True, check=True).stdout
        if patch.strip():
            r = subprocess.run(['git', 'apply', '-3', '--whitespace=nowarn'], cwd=dest, input=patch,
                               capture_output=True)
            if r.returncode:
                raise SystemExit(f'patch does not apply on origin/master:\n{r.stderr.decode(errors="replace")}')
            git(dest, 'reset', '-q', '--', *tracked, check=True)
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
        raw = f.read_bytes().decode('utf-8', 'surrogateescape') if f.exists() else ''
        nl = '\r\n' if raw.count('\r\n') > raw.count('\n') / 2 else '\n'
        rows = raw.split(nl)
        trail = rows and rows[-1] == ''
        if trail:
            rows = rows[:-1]
        # A row the worker removed and re-added unchanged is no change: porting
        # it as delete+append moved ~160 untouched rows to the end (batch 8).
        rem, add = [r for r in rem if r not in add], [a for a in add if a not in rem]
        remset = set(rem)
        # A changed functions.csv row takes its predecessor's place (same RVA).
        by_rva = {}
        if led.endswith('functions.csv'):
            for a in add:
                by_rva.setdefault(rva_of(a), []).append(a)
        out, placed = [], set()
        for r in rows:
            if r in remset:
                for a in by_rva.pop(rva_of(r), []):
                    out.append(a); placed.add(a)
                continue
            out.append(r)
        have = set(out)
        rows = out + [a for a in add if a not in have and a not in placed]
        f.write_text(nl.join(rows) + (nl if trail else ''), encoding='utf-8', errors='surrogateescape', newline='')
    # name_corrections.json: append entries the worker added, keeping the file's format
    old = git(ws, 'show', f'HEAD:{CORRECTIONS}').stdout
    new_path = Path(ws) / CORRECTIONS
    if old and new_path.exists():
        before, after = json.loads(old), json.loads(new_path.read_text(encoding='utf-8'))
        added = [e for e in after if e not in before]
        if added:
            f = Path(dest) / CORRECTIONS
            raw = f.read_bytes().decode('utf-8')
            end = '\r\n]\r\n' if raw.endswith('\r\n]\r\n') else '\n]\n'
            nl = '\r\n' if end.startswith('\r') else '\n'
            ents = [nl.join(' ' + l for l in json.dumps(e, indent=1, ensure_ascii=False).split('\n')) for e in added]
            raw = raw[:-len(end)] + ',' + nl + (',' + nl).join(ents) + end
            json.loads(raw)
            f.write_text(raw, encoding='utf-8', newline='')


BANKED = ('targets/game/reverse/attempts/', 'targets/game/reverse/attempt_history/')
TERMINAL_JOB = ('completed', 'failed', 'cancelled')


def bank(args):
    """Carry a finished job's near-miss evidence to origin: its new re_attempts.log
    verdict rows, its banked stash (attempts/<rva>.cpp) and attempt history. The
    integrate path only takes jobs that LANDED a row, so before this every fleet
    near-miss stayed in its worker worktree and the next seat started cold."""
    j, attempts, rvas, _ = info(args)
    if args.job and j['status'] not in TERMINAL_JOB and not args.force:
        raise SystemExit(f'job is {j["status"]}: it may still land; bank only a finished job')
    ws = j['cwd']
    dest = Path(args.worktree).resolve()
    if not dest.exists():
        git(ROOT, 'fetch', '-q', 'origin', 'master', check=True)
        git(ROOT, 'worktree', 'add', '-q', '--detach', str(dest), args.base, check=True)
    safe_destination(dest, args.base, keep=True)
    keys = {r.lower() for r in rvas}
    moved = []
    for p, st in changes(ws):
        if not p.startswith(BANKED) or st == 'deleted':
            continue
        if not any(f'/{k}' in p.lower() for k in keys):  # attempts/0x0012abcd.cpp, attempt_history/0x0012abcd/
            continue  # another target's evidence
        src, dst = Path(ws) / p, dest / p
        if os.path.lexists(dst) and (dst.is_symlink() or not dst.is_file()
                                    or src.is_symlink() or src.read_bytes() != dst.read_bytes()):
            raise SystemExit(f'retained bank evidence conflicts at {p}')
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        moved.append(p)
    add, _ = ledger_delta(ws, LEDGERS[3])
    add = [a for a in add if any(k in a.lower() for k in keys)]
    f = dest / LEDGERS[3]
    raw = f.read_bytes()
    have = set(raw.replace(b'\r\n', b'\n').split(b'\n'))
    nl = b'\r\n' if raw.count(b'\r\n') * 2 > raw.count(b'\n') else b'\n'
    new = [a.encode('utf-8', 'surrogateescape') for a in add]
    new = [a for a in new if a not in have]
    if new:
        f.write_bytes((raw if raw.endswith(b'\n') else raw + nl) + b''.join(a + nl for a in new))
    print(json.dumps({'job': args.job, 'status': j['status'], 'files': moved, 'verdict_rows': len(new)}))


def serialized_destination(function):
    @wraps(function)
    def wrapped(args):
        dest = Path(args.worktree).resolve()
        dest.parent.mkdir(parents=True, exist_ok=True)
        # A sibling lock survives checkout and is shared by bank/integrate.
        with (dest.parent / ('.' + dest.name + '.integration.lock')).open('a+b') as handle:
            lock(handle, exclusive=True)
            try:
                return function(args)
            finally:
                unlock(handle)
    return wrapped


def safe_destination(dest, base, keep=False):
    if git(dest, 'rev-parse', '--show-toplevel', check=True).stdout.strip() != str(dest):
        raise SystemExit('destination is not a worktree root')
    if git(dest, 'diff', '--cached', '--quiet').returncode:
        raise SystemExit('destination has staged work; retained for inspection')
    for name in ('MERGE_HEAD', 'rebase-merge', 'rebase-apply', 'CHERRY_PICK_HEAD'):
        path = git(dest, 'rev-parse', '--git-path', name, check=True).stdout.strip()
        if (dest / path).exists():
            raise SystemExit('destination has an unfinished Git operation')
    if keep:
        return
    if changes(dest):
        raise SystemExit('destination has retained changes; use --keep to explicitly combine them')
    if git(dest, 'symbolic-ref', '-q', 'HEAD').returncode == 0:
        raise SystemExit('destination must be detached; refusing to move a retained branch')
    if git(dest, 'merge-base', '--is-ancestor', 'HEAD', base).returncode:
        raise SystemExit('destination has unintegrated commits; retained for recovery')


bank = serialized_destination(bank)


@serialized_destination
def integrate(args):
    rev = review(args)
    print(json.dumps(rev, indent=1))
    if not rev['landed']:
        raise SystemExit('nothing landed in this workspace; nothing to integrate')
    if any(not result[0] for result in rev['gates'].values()):
        raise SystemExit('source verification failed; cannot integrate')
    blocking = [p for p in rev['problems'] if 'renamed' not in p and 'mutating git' not in p]
    if blocking and not args.force:
        raise SystemExit('review found problems (rerun with --force after checking them):\n  ' + '\n  '.join(blocking))
    j, attempts, rvas, _ = info(args)
    dest = Path(args.worktree).resolve()
    git(ROOT, 'fetch', '-q', 'origin', 'master', check=True)
    base = args.base
    if not dest.exists():
        git(ROOT, 'worktree', 'add', '-q', '--detach', str(dest), base, check=True)
    safe_destination(dest, base, args.keep)
    if not args.keep:
        git(dest, 'checkout', '-q', '--detach', base, check=True)
    if rev.get('fingerprint') != workspace_fingerprint(j['cwd']):
        raise SystemExit('workspace changed since review; review again before porting')
    port(j, dest)
    if rev['fingerprint'] != workspace_fingerprint(j['cwd']):
        raise SystemExit('workspace changed during port; destination retained for inspection')
    r = sh([sys.executable, 'tools/check_csv.py'], dest, check=True)
    print(r.stdout[-600:])
    status = [path for path, _ in changes(dest)]
    stray = [p for p in status if not p.startswith('build/') and route(p) != 'port']
    if stray:
        raise SystemExit('integration worktree has changes outside the ported set:\n  ' + '\n  '.join(stray))
    touched = [p for p in status
               if p.endswith(('.cpp', '.asm')) and (dest / p).exists() and not p.startswith('build/')]
    for src in touched:
        ok, text = gate(str(dest), src)
        print(f'gate {src}: {text}')
        if not ok:
            raise SystemExit(f'scoped gate fails on origin/master for {src}; not committing')
    if args.dry_run or args.keep:
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
    git(dest, 'add', '-A', '--', *status, check=True)
    c = git(dest, 'commit', '-q', '-m', msg)
    out = c.stdout + c.stderr
    if c.returncode and 'adopt_header.py --fix-staged' in out:
        print('commit hook asks for header adoption; running tools/adopt_header.py --fix-staged once')
        sh([sys.executable, 'tools/adopt_header.py', '--fix-staged'], dest, check=True)
        git(dest, 'add', '-A', '--', *status, check=True)
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
        sh([sys.executable, 'tools/check_csv.py'], dest, check=True)
        if git(dest, 'push', '-q', 'origin', 'HEAD:master').returncode == 0:
            break
    else:
        raise SystemExit('push kept losing the race; integration commit kept locally in ' + str(dest))
    sha = git(dest, 'rev-parse', 'HEAD').stdout.strip()
    print('pushed', sha)
    git(dest, 'pull', '-q', '--rebase', 'origin', 'master', check=True)
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
    bk = sub.add_parser('bank', help="port a finished job's verdict rows, stash and attempt history only")
    bk.add_argument('job', nargs='?')
    bk.add_argument('--workspace'); bk.add_argument('--rva', action='append', default=[])
    bk.add_argument('--worktree', default=str(ROOT / 'build' / 'wt' / 'bank'))
    bk.add_argument('--base', default='origin/master')
    bk.add_argument('--force', action='store_true', help='bank a job that is not finished')
    for x in (r, i):
        x.add_argument('job', nargs='?')
        x.add_argument('--workspace', help='a prepared worktree instead of a router job')
        x.add_argument('--rva', action='append', default=[], help='target RVA (with --workspace; repeatable)')
    i.add_argument('--title', default='', help='commit title (default: generic)')
    i.add_argument('--base', default='origin/master', help='integration base (default origin/master)')
    i.add_argument('--worktree', default=str(ROOT / 'build' / 'wt' / 'integrate'))
    i.add_argument('--dry-run', action='store_true')
    i.add_argument('--keep', action='store_true',
                   help='port on top of the worktree as it is (batch several jobs; implies --dry-run)')
    i.add_argument('--push', action='store_true')
    i.add_argument('--push-retries', type=int, default=8)
    i.add_argument('--measure', action='store_true', help='after --push, record the verified result on the job')
    i.add_argument('--force', action='store_true', help='integrate despite review problems you have checked')
    i.add_argument('--trailer', default='', help='extra commit message trailer lines (\\n separated)')
    a = ap.parse_args(argv)
    if a.cmd == 'bank':
        bank(a)
        return 0
    if a.cmd == 'review':
        res = review(a)
        print(json.dumps(res, indent=1))
        return 0 if res['landed'] and not res['problems'] else 1
    integrate(a)
    return 0


if __name__ == '__main__':
    sys.exit(main())
