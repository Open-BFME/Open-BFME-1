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
      --keep ports on top of the unstaged batch the worktree already holds,
      re-verifies the whole batch and stops before committing, leaving it
      unstaged, so several reviewed jobs become one batch commit.
      --dry-run ports and verifies in a throwaway worktree at the base and
      leaves the destination untouched.
      --link-debt accepts a job that lands no row because it only replaces
      hard-coded image addresses with named externs (AGENTS.md lane 6): it
      must change nothing under targets/ and only game/ sources or headers,
      every touched source's gate must pass, and tools/link_debt.py's literal
      count must fall in total and rise in no file.
      Checks read a private copy of the index with the port staged; the
      worktree's own index is only written by the final commit.

Workspaces are never modified or deleted.
"""
import argparse, hashlib, json, os, re, shutil, subprocess, sys, tempfile
from contextlib import contextmanager
from functools import wraps
from portable_lock import lock, unlock
import link_debt
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
SOURCE_SUFFIXES = ('.c', '.cc', '.cpp', '.cxx', '.asm')
GUTTED_INDEX = 200  # staged deletions of files still on disk: a worker emptied its index


def sh(cmd, cwd, check=False, timeout=None, env=None):
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, errors='surrogateescape', timeout=timeout,
                       env=env)
    if check and r.returncode:
        raise SystemExit(f'{" ".join(map(str, cmd))} failed:\n{r.stdout}{r.stderr}')
    return r


def git(cwd, *args, check=False, env=None):
    return sh(['git', *args], cwd, check=check, env=env)


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


def path_digests(ws):
    """HEAD and one digest per changed path (status, mode, bytes or link target)."""
    paths = {}
    for path, status in changes(ws):
        digest = hashlib.sha256(status.encode() + b'\0')
        file = Path(ws) / path
        if file.is_symlink():
            digest.update(b'link\0' + os.fsencode(os.readlink(file)))
        elif file.is_file():
            digest.update(str(file.stat().st_mode).encode() + b'\0' + file.read_bytes())
        paths[path] = digest.hexdigest()
    return git(ws, 'rev-parse', 'HEAD', check=True).stdout.strip(), paths


def workspace_fingerprint(ws):
    head, paths = path_digests(ws)
    digest = hashlib.sha256(head.encode())
    for path, value in paths.items():
        digest.update(os.fsencode(path) + b'\0' + value.encode() + b'\0')
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
    """'port', 'scratch' (an untracked top-level file such as aim.cod, or a compilable
    copy a worker left in attempt_history, which holds evidence, never sources) or 'refuse'."""
    if (path.startswith(BANKED[1]) and
            path.lower().endswith((*SOURCE_SUFFIXES, '.h', '.hpp', '.hh', '.hxx', '.inl', '.inc'))):
        return 'scratch'
    if path.startswith(BANKED[0]) and not re.fullmatch(r'0x[0-9a-f]{8}\.cpp', path[len(BANKED[0]):]):
        return 'scratch'  # check_csv accepts only attempts/<rva>.cpp; anything else is a worker's scratch
    if path.startswith(PORTED):
        return 'port'
    return 'scratch' if '/' not in path else 'refuse'


def added_naked(ws, path):
    """Inline asm/naked code on lines the worker added to a tracked file (comments ignored)."""
    d = git(ws, 'diff', '-U0', 'HEAD', '--', path, check=True).stdout
    return bool(NAKED.search(code_only('\n'.join(l[1:] for l in d.splitlines()
                                                 if l.startswith('+') and not l.startswith('+++')))))


def rva_of(row):
    f = row.split(',')
    return f[2].lower() if len(f) > 3 and f[2].lower().startswith('0x') else None


def ledger_delta(ws, path):
    d = git(ws, 'diff', '-U0', 'HEAD', '--', path, check=True).stdout
    add = [l[1:].rstrip('\r') for l in d.splitlines() if l.startswith('+') and not l.startswith('+++')]
    rem = [l[1:].rstrip('\r') for l in d.splitlines() if l.startswith('-') and not l.startswith('---')]
    return add, rem


def head_matched(ws, key):
    """True when HEAD's ledger already holds a matched row for this RVA (lower-case key)."""
    text = git(ws, 'show', 'HEAD:' + LEDGERS[0], check=True).stdout
    for line in text.splitlines():
        f = line.rstrip('\r').split(',')
        if len(f) > 5 and f[2].lower() == key and f[5] == 'matched':
            return True
    return False


def gate(cwd, src, env=None, rows=()):
    """Scoped byte gate of `src`, plus any exact `rows` selectors in the same build.py run."""
    r = sh(['./build.sh', src, *rows], cwd, timeout=1800, env=env)
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
        if not args.rva and not getattr(args, 'link_debt', False):
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
    # A matched target row's exact selector rides in its own source's gate: one
    # build.py run on the same snapshot verifies every row of the source and the
    # selector, including its exactly-one-matched-row check (the row is one of the
    # source's rows, so nothing is added or dropped). A second run for the selector
    # alone cost ~2 s of fixed ledger/symbol-map loading per review. A combined
    # failure is re-run split, so which of the two failed is still reported.
    exact_rows, exact = {}, {}
    for rva in rvas:
        new = [r for r in fadd if f',{rva.lower()},' in r.lower()]
        row = new[-1].split(',') if new else []
        if len(row) > 5 and row[5] == 'matched':
            exact_rows.setdefault(row[4], []).append(f'row:{row[2]}:{row[3]}:{row[0]}')

    def source_gate(src):
        selectors = list(dict.fromkeys(exact_rows.get(src, ())))
        if selectors:
            combined = gate(ws, src, rows=selectors)
            if combined[0]:
                exact.update((selector, combined) for selector in selectors)
                return combined
        return gate(ws, src)

    for path, st in ch:
        if route(path) == 'refuse':
            res['problems'].append(f'{path}: changed outside {", ".join(PORTED)}; the port does not carry it')
        if st != 'deleted' and path.lower().endswith(SOURCE_SUFFIXES) and path.startswith('game/'):
            res['gates'][path] = source_gate(path)
            if not res['gates'][path][0]:
                res['problems'].append(f'{path}: touched source gate fails ({res["gates"][path][1]})')
            if st == 'added' and NAKED.search(code_only((Path(ws) / path).read_text(errors='replace'))):
                res['problems'].append(f'{path}: new source contains inline asm/__emit/naked code')
            elif st == 'modified' and not path.lower().endswith('.asm') and added_naked(ws, path):
                res['problems'].append(f'{path}: the worker added inline asm/__emit/naked code')
    gutted = [l for l in git(ws, 'diff', '--cached', '--name-only', '-z', '--diff-filter=D', check=True).stdout.split('\0')
              if l and (Path(ws) / l).exists()]
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
            status = row[5] if len(row) > 5 else ''
            if src not in res['gates']:
                res['gates'][src] = source_gate(src) if (Path(ws) / src).exists() else (False, 'source missing')
            ok = res['gates'][src]
            t.update(name=row[0], size=row[3], source=src, status=status, gate=ok[1])
            if old and old[-1].split(',')[0] != row[0]:
                t['renamed_from'] = old[-1].split(',')[0]
                res['problems'].append(f'{rva}: row renamed from {t["renamed_from"]} -- check the identity evidence')
            if not ok[0]:
                res['problems'].append(f'{rva}: row changed but its gate fails ({ok[1]})')
            # A green source-wide gate proves the SIBLINGS still match. The target
            # itself lands only when its row says matched AND its exact row selector
            # verifies: an `unmatched` row is a legitimate investigation, not a landing.
            if status != 'matched':
                t['outcome'] = 'unmatched investigation retained'
            elif not ok[0]:
                t['outcome'] = 'matched row but its source gate fails'
            else:
                selector = f'row:{row[2]}:{row[3]}:{row[0]}'
                row_gate = exact.get(selector) or gate(ws, selector)
                t['row_gate'] = row_gate[1]
                t['landed'] = row_gate[0]
                t['outcome'] = 'target newly matched' if row_gate[0] else 'matched row but its exact row selector fails'
                if not row_gate[0]:
                    res['problems'].append(f'{rva}: row says matched but {selector} fails ({row_gate[1]})')
        else:
            t['outcome'] = ('existing match preserved' if head_matched(ws, key)
                            else 'no row change for the target')
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
        # a --keep batch or an editor may hold a change to a file the worker deleted: never unlink it
        if status == 'deleted' and p not in ledgers and os.path.lexists(Path(dest) / p) and git(
                dest, 'status', '--porcelain=v1', '-z', '--', p, check=True).stdout:
            raise SystemExit(f'worker deleted {p}, which holds a retained change in {dest}; nothing ported')
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
        # exactly attempts/0x0012abcd.cpp or attempt_history/0x0012abcd/...: not another
        # target's evidence, nor a worker's scratch variant such as attempts/0x0012abcd_v2.cpp
        if not any(p.lower() == f'{BANKED[0]}{k}.cpp' or p.lower().startswith(f'{BANKED[1]}{k}/') for k in keys):
            continue
        if route(p) == 'scratch':  # a compilable copy left in attempt_history is not evidence
            continue
        safe_port_path(ws, p)
        safe_port_path(dest, p)
        src, dst = Path(ws) / p, dest / p
        if os.path.lexists(dst) and (dst.is_symlink() or not dst.is_file()
                                    or src.is_symlink() or src.read_bytes() != dst.read_bytes()):
            if not p.startswith(BANKED[0]):
                raise SystemExit(f'retained bank evidence conflicts at {p}')
            # Both sides re-banked this target: re_log keeps the better MEASURED body,
            # so keep whichever header ranks higher (the destination on a tie).
            ours, theirs = stash_score(dst), stash_score(src)
            if ours is None or theirs is None:
                raise SystemExit(f'retained bank evidence conflicts at {p}; a side has no score header')
            if theirs <= ours:
                print(f'{p}: kept the destination bank (score {ours} >= worker {theirs})')
                continue
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


def stash_score(path):
    """A banked stash's measured score from its header (tools/re_log.py), else None."""
    from re_log import _STASH_SCORE
    lines = Path(path).read_text(encoding='utf-8-sig', errors='replace').splitlines()
    m = _STASH_SCORE.match(lines[1]) if len(lines) > 1 else None
    return float(m.group(1)) if m else None


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


@contextmanager
def staged_view(dest):
    """An environment whose GIT_INDEX_FILE is a private copy of dest's index with the
    ported directories staged. check_csv lists tracked files, so a lift or stash the worker
    deleted (unlinked by port() but still indexed) crashed it with FileNotFoundError, and a
    new source must count as tracked (ada39cafc9). Staging in the real index instead left
    every --keep batch, dry run and aborted integration staged, which the next run refused."""
    index = Path(dest) / git(dest, 'rev-parse', '--git-path', 'index', check=True).stdout.strip()
    fd, private = tempfile.mkstemp(prefix='router-integrate-index.', dir=index.parent)
    os.close(fd)
    try:
        shutil.copyfile(index, private)
        env = dict(os.environ, GIT_INDEX_FILE=private)
        git(dest, 'add', '-A', '--', *(d.rstrip('/') for d in PORTED if (Path(dest) / d).exists()),
            check=True, env=env)
        yield env
    finally:
        for leftover in (private, private + '.lock'):
            if os.path.lexists(leftover):
                os.unlink(leftover)


def port_and_verify(rev, j, dest):
    """Port the reviewed workspace into dest and verify it there; returns dest's changed paths.
    dest's own index and HEAD are never written, so on any refusal the port (and anything a
    concurrent editor did) is left exactly as it is in the worktree, unstaged."""
    if rev.get('fingerprint') != workspace_fingerprint(j['cwd']):
        raise SystemExit('workspace changed since review; review again before porting')
    port(j, dest)
    if rev['fingerprint'] != workspace_fingerprint(j['cwd']):
        raise SystemExit('workspace changed during port; destination retained for inspection')
    with staged_view(dest) as env:
        ported = path_digests(dest)
        r = sh([sys.executable, 'tools/check_csv.py'], dest, check=True, env=env)
        print(r.stdout[-600:])
        status = list(ported[1])
        stray = [p for p in status if not p.startswith('build/') and route(p) != 'port']
        if stray:
            raise SystemExit('integration worktree has changes outside the ported set:\n  ' + '\n  '.join(stray))
        touched = [p for p in status
                   if p.lower().endswith(SOURCE_SUFFIXES) and (Path(dest) / p).exists() and not p.startswith('build/')]
        for src in touched:
            ok, text = gate(str(dest), src, env)
            print(f'gate {src}: {text}')
            if not ok:
                raise SystemExit(f'scoped gate fails on origin/master for {src}; not committing')
    after = path_digests(dest)
    if after != ported:
        moved = sorted(p for p in set(ported[1]) | set(after[1]) if ported[1].get(p) != after[1].get(p))
        raise SystemExit(f'destination changed during verification; the integrator staged and committed nothing. Retained '
                         f'unstaged in {dest} as the editor left them:\n  ' + '\n  '.join(moved or ['HEAD'])
                         + '\nthe rest of the port is unstaged there too:\n  '
                         + '\n  '.join(p for p in status if p not in moved))
    return status


def link_debt_delta(ws, rev):
    """(path, before, after) literal counts for a --link-debt job, HEAD blob against the
    workspace file, or SystemExit naming every reason it is not a pure literal cut."""
    problems, counts = [], []
    for path, status in changes(ws):
        where = route(path)
        if where == 'scratch':
            continue
        if path.startswith('targets/'):
            problems.append(f'{path}: a link-debt job changes no file under targets/')
        elif where != 'port' or not link_debt.watched(path):
            problems.append(f'{path}: a link-debt job changes only game/ sources and headers')
        elif status == 'deleted':
            problems.append(f'{path}: a link-debt job deletes no file (a deletion is not a named extern)')
        else:
            if path.lower().endswith(SOURCE_SUFFIXES) and not rev['gates'].get(path, (False,))[0]:
                problems.append(f'{path}: its gate did not pass in review '
                                f'({rev["gates"].get(path, (False, "not gated"))[1]})')
            old = git(ws, 'show', f'HEAD:{path}').stdout if status == 'modified' else ''
            new = (Path(ws) / path).read_text(encoding='utf-8', errors='replace')
            counts.append((path, len(link_debt.literals(old)), len(link_debt.literals(new))))
    problems += [f'{p}: {b} -> {a} literals; no file may gain one' for p, b, a in counts if a > b]
    before, after = sum(c[1] for c in counts), sum(c[2] for c in counts)
    if not counts:
        problems.append('no game/ source or header changed')
    elif after >= before:
        problems.append(f'link debt does not fall ({before} -> {after} literals)')
    tolerated = ('renamed', 'mutating git', 'no target RVA found')
    problems += [p for p in rev['problems'] if not any(t in p for t in tolerated)]
    if problems:
        raise SystemExit('not a link-debt integration; nothing ported:\n  ' + '\n  '.join(dict.fromkeys(problems)))
    return counts


@serialized_destination
def integrate(args):
    rev = review(args)
    print(json.dumps(rev, indent=1))
    debt = None
    if getattr(args, 'link_debt', False):
        # A job without a row: every other check below still runs on it.
        debt = link_debt_delta(info(args)[0]['cwd'], rev)
        print('link debt: ' + '; '.join(f'{p} {b} -> {a}' for p, b, a in debt))
    elif not rev['landed']:
        raise SystemExit('nothing landed in this workspace; nothing to integrate')
    if any(not result[0] for result in rev['gates'].values()):
        raise SystemExit('source verification failed; cannot integrate')
    blocking = [p for p in rev['problems'] if 'renamed' not in p and 'mutating git' not in p
                and not (debt is not None and 'no target RVA found' in p)]
    if blocking and not args.force:
        raise SystemExit('review found problems (rerun with --force after checking them):\n  ' + '\n  '.join(blocking))
    j, attempts, rvas, _ = info(args)
    dest = Path(args.worktree).resolve()
    git(ROOT, 'fetch', '-q', 'origin', 'master', check=True)
    base = args.base
    if args.dry_run:
        if args.keep:
            raise SystemExit('--dry-run never touches the destination, so it cannot combine with --keep')
        # A throwaway checkout at the base: the destination's HEAD, index and files stay as they are.
        scratch = Path(tempfile.mkdtemp(prefix='.' + dest.name + '.dry-run.', dir=dest.parent))
        try:
            git(ROOT, 'worktree', 'add', '-q', '--detach', str(scratch), base, check=True)
            port_and_verify(rev, j, scratch)
        finally:
            git(ROOT, 'worktree', 'remove', '--force', str(scratch))  # only ever this call's own scratch
            shutil.rmtree(scratch, ignore_errors=True)
        print(f'dry run: ported and gated in a scratch worktree on {base}; {dest} untouched, nothing committed')
        return
    if not dest.exists():
        git(ROOT, 'worktree', 'add', '-q', '--detach', str(dest), base, check=True)
    safe_destination(dest, base, args.keep)
    if args.keep:
        retained = [p for p, _ in changes(dest)]
        stray = [p for p in retained if route(p) != 'port']
        if stray:
            raise SystemExit(f'{dest} holds changes outside the ported set; nothing ported, all retained '
                             'unstaged as found:\n  ' + '\n  '.join(stray))
        if retained:
            print(f'--keep: combining with the unstaged batch in {dest}:\n  ' + '\n  '.join(retained))
    else:
        git(dest, 'checkout', '-q', '--detach', base, check=True)
    status = port_and_verify(rev, j, dest)
    if args.keep:
        print(f'--keep: batch ported and gated, left unstaged in {dest}; not committed')
        return
    landed = rev['landed']
    names = '; '.join(f'{rev["targets"][r]["name"]} at {r} ({rev["targets"][r]["size"]} bytes)' for r in landed)
    models = sorted({a['model'] for a in attempts if a.get('model')})
    origin = f'router job {args.job}' if args.job else 'prepared workspace'
    title = args.title or f'Integrate {origin}: {len(landed)} byte-exact conversion(s)'
    if debt is not None:
        title = args.title or f'link-debt: name the globals in {len(debt)} files'
        names = '\n'.join(f'{p}: {b} -> {a} literals' for p, b, a in debt)
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
    sha = git(dest, 'rev-parse', 'HEAD', check=True).stdout.strip()
    print('committed', sha)
    if not args.push:
        return
    if args.base != 'origin/master':
        raise SystemExit('--push only integrates onto origin/master')
    publish(dest, args.push_retries, checks=[[sys.executable, 'tools/check_csv.py']])
    sha = git(dest, 'rev-parse', 'HEAD', check=True).stdout.strip()
    print('pushed', sha)
    git(dest, 'pull', '-q', '--rebase', 'origin', 'master', check=True)
    if args.measure and attempts and args.job and debt is not None:
        # no row changes, so no byte is gained and no target matched
        cmd = [sys.executable, 'tools/opencode_router.py', 'measure', attempts[-1]['id'], '--exact-match', 'no',
               '--bytes-gained', '0', '--evidence',
               f'tools/router_integrate.py integrate {args.job} --link-debt: link debt '
               f'{sum(d[1] for d in debt)} -> {sum(d[2] for d in debt)} literals in {len(debt)} files, '
               f'scoped gates + commit hooks, pushed {sha[:10]}']
        print(sh(cmd, ROOT, check=True).stdout)
    elif args.measure and attempts and args.job:
        delta = sh([sys.executable, 'tools/progress.py', f'{sha}^..{sha}'], dest, check=True).stdout
        m = re.search(r'REBUILDS FROM.*?delta ([+-][\d,]+) bytes', delta)
        # exact-match is the TARGET's verdict (review's landed list), never the
        # fact that the batch was accepted: a pushed unmatched investigation is
        # useful work but not an exact match.
        exact = 'yes' if any(rva in rev['landed'] for rva in rvas) else 'no'
        cmd = [sys.executable, 'tools/opencode_router.py', 'measure', attempts[-1]['id'], '--exact-match', exact,
               '--evidence', f'tools/router_integrate.py integrate {args.job}: scoped gates + commit hooks, pushed {sha[:10]}']
        if m:
            cmd += ['--bytes-gained', m.group(1).replace(',', '').lstrip('+')]
        print(sh(cmd, ROOT, check=True).stdout)


# Push outputs that prove "the destination moved under you": a rebase fixes
# these and nothing else.  Git's own non-fast-forward / lease rejections, a
# remote ref update that found the ref at a different tip, and the pre-push
# hook's advertised-tip guard (.githooks/pre-push) when it asserts the tip
# moved or is not an ancestor.  Not races, reported as is: validator failures,
# auth and transport failures, a bare lock error (a stale .lock file does not
# show the ref moved), and the hook's "cannot inspect destination" (its fetch
# failed: transport) and "tip ... is unavailable" (fetched but unreadable).
RACE = re.compile(r'\[rejected\].*\((?:fetch first|non-fast-forward|stale info)\)|'
                  r'is at [0-9a-f]+ but expected [0-9a-f]+|'
                  r'Updates were rejected because the (?:remote contains work|tip of your current branch is behind)|'
                  r'PRE-PUSH FAILED: PUSH RACE: destination \S+ (?:advanced before verification|'
                  r'at [0-9a-f]+ is not an ancestor of)', re.I)
HOOK_FAIL = re.compile(r'^PRE-PUSH FAILED: (.*)$', re.M)


def is_push_race(output):
    """True only when the push output proves a stale base; any other hook
    failure in the same output (a validator) wins, so it is never retried."""
    if any(not RACE.search('PRE-PUSH FAILED: ' + f) for f in HOOK_FAIL.findall(output)):
        return False
    return bool(RACE.search(output))


def publish(dest, retries, checks=()):
    """Rebase onto origin/master and push; retry only on evidence of a stale-base race.

    The original push output is kept and reported: a byte-verification hook
    rejection used to be retried eight times and then reported as a lost race.
    Returns the attempt number that succeeded.
    """
    last = ''
    for attempt in range(1, retries + 1):
        p = git(dest, 'pull', '-q', '--rebase', 'origin', 'master')
        if p.returncode:
            out = (p.stdout + p.stderr).strip()
            if re.search(r'CONFLICT|could not apply|Resolve all conflicts', out):
                git(dest, 'rebase', '--abort')
                raise SystemExit('rebase conflict; integration commit kept locally in ' + str(dest)
                                 + '\n' + out[-3000:])
            raise SystemExit(f'pull --rebase origin master failed before the push; this is not a stale-base '
                             f'race. Integration commit kept locally in {dest}. Output:\n' + out[-3000:])
        for cmd in checks:
            sh(cmd, dest, check=True)
        p = git(dest, 'push', '-q', 'origin', 'HEAD:master')
        if p.returncode == 0:
            return attempt
        last = (p.stdout + p.stderr).strip()
        if not is_push_race(last):
            raise SystemExit(f'push rejected on attempt {attempt}; this is not a stale-base race, so retrying '
                             f'cannot fix it. Integration commit kept locally in {dest}. Push output:\n'
                             + last[-3000:])
    raise SystemExit(f'push kept losing the race over {retries} attempt(s); integration commit kept locally '
                     f'in {dest}. Last push output:\n' + last[-3000:])


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
    i.add_argument('--dry-run', action='store_true',
                   help='port and gate in a throwaway worktree; the destination is left untouched')
    i.add_argument('--keep', action='store_true',
                   help='port on top of the unstaged batch in the worktree and stop before committing '
                        '(batch several jobs; the batch stays unstaged)')
    i.add_argument('--push', action='store_true')
    i.add_argument('--push-retries', type=int, default=8)
    i.add_argument('--measure', action='store_true', help='after --push, record the verified result on the job')
    i.add_argument('--force', action='store_true', help='integrate despite review problems you have checked')
    i.add_argument('--trailer', default='', help='extra commit message trailer lines (\\n separated)')
    i.add_argument('--link-debt', action='store_true',
                   help='accept a job that lands no row because it only replaces hard-coded image addresses '
                        'with named externs: nothing under targets/ may change, only game/ sources and headers, '
                        'every touched gate must pass and the link_debt.py literal count must fall in total '
                        'and rise in no file (--force does not waive these)')
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
