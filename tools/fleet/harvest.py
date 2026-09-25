#!/usr/bin/env python3
"""Orchestrator harvest. Workers never run git; this is the only VCS path.

Under the ledger lock: stage ledgers + cited sources, verify, commit. Then
rebase+push in a SEPARATE worktree (build/wt) so in-flight worker edits to
tracked Code/ files never block the pull, and finally move the main
checkout's HEAD to the pushed commit, refreshing only files whose working copy
still equals the old commit (untouched by anyone in flight). If workers advance
the ledgers during network work, preserve their edits and defer local sync.
"""
import csv, os, re, subprocess, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2 if Path(__file__).resolve().parent.name == "fleet" else 1]
sys.path.insert(0, str(ROOT / "tools"))
import portable_lock

def run(*cmd, cwd=ROOT, check=True, cap=False):
    print("$", " ".join(cmd), flush=True)
    # seats, the watchdog and ledger_prep run git in this checkout too; a
    # transient .git/index.lock is not a failure of ours, so wait it out
    import time
    for attempt in range(6):
        r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, errors="replace")
        if r.returncode == 0 or "index.lock" not in (r.stderr or ""):
            break
        time.sleep(10)
    if not cap:
        sys.stdout.write(r.stdout); sys.stderr.write(r.stderr)
    if check and r.returncode:
        raise subprocess.CalledProcessError(r.returncode, cmd, r.stdout, r.stderr)
    return r

def out(*cmd, cwd=ROOT):
    return subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, check=True).stdout.strip()

def show(rev, f):
    return subprocess.run(["git", "show", f"{rev}:{f}"], cwd=ROOT, capture_output=True).stdout

def lines(b):
    return [x.rstrip(b"\r") for x in b.split(b"\n")]

def minimal_diff_ledgers(base="HEAD", cwd=ROOT):
    """Rewrite functions.csv / symbols.csv as BASE's byte order plus the real
    row delta. dedup_csv.py sorts, and seats re-sort segments; a reordered
    file is a whole-file diff (6,236 changed lines for 19 landings on
    2026-09-22) that made the pre-commit name_regression scan spawn two git
    processes per changed row (over an hour) and that the union merge driver
    turns into duplicate rows on rebase. Same algorithm as build/ledger_minimal_diff.py."""
    for f in ("reverse/functions.csv", "reverse/symbols.csv"):
        head = subprocess.run(["git", "show", f"{base}:{f}"], cwd=cwd, capture_output=True).stdout.splitlines(True)
        if not head:
            continue
        cur = (cwd / f).read_bytes().splitlines(True)
        key = lambda x: x.rstrip(b"\r\n")
        hs, cs = {key(x) for x in head}, {key(x) for x in cur}
        term = b"\r\n" if head[-1].endswith(b"\r\n") else b"\n"
        merged = [x for x in head if key(x) in cs]
        if merged and not merged[-1].endswith(b"\n"):
            merged[-1] += term
        seen = set()
        for x in cur:
            k = key(x)
            if k and k not in hs and k not in seen:
                seen.add(k); merged.append(k + term)
        (cwd / f).write_bytes(b"".join(merged))
        print(f"{f}: {base} order kept; removed {len(hs - cs)} added {len(seen)}", flush=True)

def quarantine(source, funcs, status="blocked", why=None):
    """Set aside a landed source the hook refuses (it defines helpers the ledger
    does not declare): move it under build/quarantine, revert the ledger rows
    that cite it and the tombstones of the rows they replaced, restore those
    replaced rows from HEAD, and record one blocked verdict per reverted row so
    the next seat starts from the saved file instead of from scratch."""
    import re_log
    def rows(text):
        return list(csv.reader(text.decode("utf-8", errors="replace").splitlines()))
    fpath, dpath = ROOT / "reverse/functions.csv", ROOT / "reverse/deleted_rows.csv"
    raw = fpath.read_bytes(); term = b"\r\n" if b"\r\n" in raw[:4000] else b"\n"
    cur = raw.splitlines(True)
    mine = [r for r in rows(raw) if len(r) > 5 and r[4] == source]
    rvas = {r[2].upper() for r in mine}
    keepf = [x for x in cur if not (len(f := next(csv.reader([x.decode("utf-8", errors="replace").rstrip("\r\n")]), [])) > 5 and f[4] == source)]
    head = show("HEAD", "reverse/functions.csv")
    have = {x.rstrip(b"\r\n") for x in keepf}
    for x in head.splitlines(True):
        f = next(csv.reader([x.decode("utf-8", errors="replace").rstrip("\r\n")]), [])
        if len(f) > 2 and f[2].upper() in rvas and x.rstrip(b"\r\n") not in have:
            keepf.append(x.rstrip(b"\r\n") + term)   # the dump row this landing replaced
    fpath.write_bytes(b"".join(keepf))
    if dpath.exists():
        draw = dpath.read_bytes(); dhead = {x.rstrip(b"\r\n") for x in show("HEAD", "reverse/deleted_rows.csv").splitlines(True)}
        keepd = [x for x in draw.splitlines(True)
                 if x.rstrip(b"\r\n") in dhead or not (len(f := next(csv.reader([x.decode("utf-8", errors="replace").rstrip("\r\n")]), [])) > 1 and f[1].upper() in rvas)]
        dpath.write_bytes(b"".join(keepd))
    dest = ROOT / "build/quarantine" / source
    dest.parent.mkdir(parents=True, exist_ok=True)
    (ROOT / source).replace(dest)
    subprocess.run(["git", "reset", "-q", "--", source], cwd=ROOT)
    for r in mine:
        reason = why or "source defines helpers the ledger does not declare (%s); declare the helpers or land them as rows, then re-land" % ", ".join(funcs)[:200]
        evidence = ("harvest quarantine: %s; byte-exact file kept at build/quarantine/%s on this host "
                    "blocker=callee/harvest-quarantine model=harvest" % (reason, source))
        subprocess.run([sys.executable, "tools/re_log.py", "record", r[0], r[2], r[3], status, evidence], cwd=ROOT)


def unstage_inflight():
    """A stash whose address a live seat still leases is scratch in flight
    (seats write reverse/attempts directly before banking); judging it wedged
    five harvests on 2026-09-17. It is picked up once the lease ends."""
    import fleet_run
    live = {a.lower() for a in fleet_run.active_rvas(ROOT)}
    # a retired stash (its body landed, git rm above) stays retired even when the
    # seat that landed it still holds the lease: unstaging that deletion put the
    # stash back in the index and check_csv refused the commit (2026-09-23, x3)
    inflight = [p for p in out("git", "diff", "--cached", "--name-only", "--", "reverse/attempts").splitlines()
                if Path(p).stem.lower() in live and (ROOT / p).exists()]
    if inflight:
        run("git", "reset", "-q", "--", *inflight)
        print(f"harvest: left {len(inflight)} in-flight stash(es) unstaged")


# The pre-commit hook's placement rule (.githooks/pre-commit): a NEW source
# outside these trees fails the commit, and a harvest is one commit.
OFFICIAL = ("Code/GameEngine/", "Code/GameEngineDevice/", "Code/Libraries/", "Code/gen_small/",
            "Code/gen_asm/", "Code/masm_dumps/", "reference/shims/", "reference/CnC_Generals_Zero_Hour/",
            "tools/tests/", "build/toolchains/", "mods/", "reverse/attempts/")
# Written while this harvest owns the index. A harvest that dies between
# staging and commit leaves its own staged set behind, and every later pass
# then refused it as "another writer's" (2026-09-18 to 09-21: three days, the
# whole backlog of one host). The marker tells our leftovers from a stranger's.
MARKER = ROOT / "build/.harvest_staged"


def unstage():
    run("git", "reset", "-q")
    MARKER.unlink(missing_ok=True)


def alarm(text):
    """One greppable line for the orchestrator; the harvest log is 5 MB of routine."""
    import time
    log = ROOT / "build/fleet_logs/harvest_alarm.log"
    log.parent.mkdir(parents=True, exist_ok=True)
    with log.open("a", encoding="utf-8") as handle:
        handle.write(time.strftime("%Y-%m-%d %H:%M ") + text.splitlines()[0][:300] + "\n")


def hands(text):
    alarm(text)
    sys.exit(text)


msg = sys.argv[1] if len(sys.argv) > 1 else "Open-BFME5: fleet ledger and source snapshot"
WT = ROOT / "build/wt"

# Serialize harvesters separately; network waits must not own the landing lock.
harvester = open(ROOT / "build/.harvest.lock", "a+")
portable_lock.lock(harvester, exclusive=True)

with open(ROOT / "reverse/.add_match.lock", "a+") as h:
    portable_lock.lock(h, exclusive=True)
    # under the lock no seat can land, so a stash deleted by add_match since the
    # last commit is restored here and retired below without racing a seat
    if subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=ROOT).returncode:
        if not MARKER.exists():
            hands("harvest: existing staged work belongs to another writer; leaving it untouched")
        # both locks are ours, so no harvester and no landing is in progress:
        # this is the index of a harvest that died. The working tree is the
        # source of truth; unstage and stage again from it.
        print("harvest: unstaging the leftovers of a harvest that died mid-commit")
        unstage()
    dependencies = out("git", "diff", "--name-only", "--", "*.h", "*.hpp", "reference", "tools", ".githooks", "AGENTS.md")
    untracked_headers = out("git", "ls-files", "--others", "--exclude-standard", "--", "Code/*.h", "Code/*.hpp", "reference")
    if dependencies or untracked_headers:
        sys.exit("harvest: changed shared dependencies need a separate verified commit; not sweeping them into fleet work")
    subprocess.run([sys.executable, "tools/fleet/ledger_prep.py"], cwd=ROOT,
                   env=dict(os.environ, HARVEST_HAS_LOCK="1"), check=True)
    # ledger_prep runs dedup_csv, which sorts: restore HEAD order before anything
    # is staged (2026-09-22: the sorted file made name_regression pair InGameUI.cpp
    # with Rva0042TinyBodies.cpp and report 14 bogus regressions).
    minimal_diff_ledgers()
    # Only fleet-owned evidence and ledger-cited sources belong in this commit.
    # Never sweep unrelated docs/tools/headers or every dirty Code source.
    evidence = [p for p in ("reverse/functions.csv", "reverse/symbols.csv",
                "reverse/re_attempts.log", "reverse/attempts", "reverse/attempt_history",
                "reverse/deleted_rows.csv",  # tombstones: check_csv rejects a row removal without one
                "reverse/header_adopt_blocked.tsv")  # adopt_header records what the compiler refused
                if (ROOT / p).exists()]
    MARKER.write_text(str(os.getpid()), encoding="ascii")
    run("git", "add", "-A", "--", *evidence); unstage_inflight()
    cited = set()
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as ledger:
        cited = {r["source"] for r in csv.DictReader(ledger) if r["status"] == "matched"
                 and r["source"].startswith("Code/") and r["source"].endswith((".cpp", ".c"))}
    changed_sources = out("git", "diff", "--name-only", "--", "Code").splitlines()
    for source in changed_sources:
        if source in cited:
            # a tracked TU a seat is still editing fails the hook's byte-verify
            # and takes every other landing down with it: stage it only once
            # it verifies on its own (GameLOD.cpp and sortingrenderer.cpp, 2026-09-17)
            v = subprocess.run(["bash", str(ROOT / "build.sh"), source], cwd=ROOT, capture_output=True, text=True, errors="replace")
            if "Functions: OK" in v.stdout + v.stderr and "FAIL" not in v.stdout + v.stderr:
                run("git", "add", "--", source)
            else:
                print(f"harvest: {source} does not byte-verify yet; left in flight")
    # a cited TU may #include a sibling (.c/.inl) a seat edited for the landing;
    # nbench1.cpp includes nbench1.c (2026-09-17): stage the include with the TU
    import re as _re
    staged_code = set(out("git", "diff", "--cached", "--name-only", "--", "Code").splitlines())
    for source in changed_sources:
        if source in staged_code or not (ROOT / source).exists():
            continue
        name = Path(source).name
        for tu in staged_code:
            if (ROOT / tu).exists() and _re.search(r'#include\s*"%s"' % _re.escape(name), (ROOT / tu).read_text(encoding="utf-8", errors="replace")):
                run("git", "add", "--", source); print(f"harvest: staged {source}, included by {tu}"); break
    unt = out("git", "ls-files", "--others", "--exclude-standard", "Code").split()
    keep = [u for u in unt if u in cited]
    # placement first: the hook refuses a new source outside the official tree
    # and takes every other landing down with it (Code/stlport/, 2026-09-18)
    for path in [k for k in keep if not k.startswith(OFFICIAL)]:
        quarantine(path, [], why="placement: %s is outside the official source tree (AGENTS.md 'File placement'); "
                                 "move it under an official Code/ path and re-land" % path)
        keep.remove(path)
        print(f"harvest: quarantined {path} (outside the official tree)")
    if keep:
        run("git", "add", "--", *keep)
    print(f"harvest: staged {len(keep)} new cited sources, skipped {len(unt)-len(keep)} in-flight")
    # A new source that defines helpers the ledger never declares fails the
    # pre-commit hook and, because the harvest is one commit, blocks every other
    # landing behind it (three such files wedged this host for five hours on
    # 2026-09-17). Quarantine it: the file goes to build/quarantine, its rows
    # and tombstones are reverted, and a blocked verdict names the helpers.
    if keep:
        r = subprocess.run([sys.executable, "tools/find_declared_unmatched.py", "--fail", "--staged", *keep],
                           cwd=ROOT, capture_output=True, text=True, errors="replace")
        bad = {}
        for line in (r.stdout + r.stderr).splitlines():
            path, sep, func = line.partition(": ")
            path = path.strip().replace("\\", "/")
            if sep and path in keep:
                bad.setdefault(path, []).append(func.strip())
        for path, funcs in bad.items():
            quarantine(path, funcs)
            keep.remove(path)
        if bad:
            run("git", "add", "-A", "--", *evidence); unstage_inflight()
            print(f"harvest: quarantined {len(bad)} source(s) defining undeclared helpers: {' '.join(bad)}")
    # A new constructor row the vtable detector contradicts fails identity_guard
    # (shrink-only baseline) and wedges the harvest the same way. Quarantine it
    # with an identity-suspect verdict naming the class the vtable belongs to.
    head_names = {r[0] for r in csv.reader(show("HEAD", "reverse/functions.csv").decode("utf-8", errors="replace").splitlines())}
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace") as ledger:
        new_ctors = {r["target_rva"].upper(): r for r in csv.DictReader(ledger)
                     if r["name"].startswith("??0") and r["name"] not in head_names and r["status"] == "matched"}
    if new_ctors:
        import re
        r = subprocess.run([sys.executable, "tools/ctor_vtable.py"], cwd=ROOT, capture_output=True, text=True, errors="replace")
        flagged = {}
        for m in re.finditer(r"^(0x[0-9A-Fa-f]{8}) +\d+B +(\S+)\n\s+claims (\S+); the vtable it leaves installed belongs to (\S+)", r.stdout, re.M):
            flagged[m.group(1).upper()] = m.group(4)
        for rva, row in new_ctors.items():
            if rva in flagged and row["source"] in cited:
                quarantine(row["source"], [], status="identity-suspect",
                           why="ctor_vtable: the vtable this body leaves installed belongs to %s, not %s" % (flagged[rva], row["name"]))
                run("git", "add", "-A", "--", *evidence); unstage_inflight()
                print(f"harvest: quarantined {row['source']} (identity-suspect: vtable belongs to {flagged[rva]})")
    # A new forwarder-sized body named like its family's real method is the
    # other identity_guard detector that wedged a harvest (a 5-byte thunk named
    # `construct`, 2026-09-18). Quarantine what size_outlier indicts among the
    # rows this harvest adds; rows already in HEAD are the baseline's business.
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace") as ledger:
        new_rows = [r for r in csv.DictReader(ledger) if r["status"] == "matched"
                    and r["name"] not in head_names and r["source"] in cited]
    if new_rows:
        import re
        r = subprocess.run([sys.executable, "tools/size_outlier.py"], cwd=ROOT, capture_output=True, text=True, errors="replace")
        for m in re.finditer(r"^\s*(\d+)B vs family median\s+(\d+)B\s+(\S+)\s+(\S+)\s+callers exist, none same-method", r.stdout, re.M):
            size, median, method, klass = m.groups()
            for row in new_rows:
                if row["target_size"] == size and row["name"].startswith(f"?{method}@{klass}") and (ROOT / row["source"]).exists():
                    quarantine(row["source"], [], status="identity-suspect",
                               why="size_outlier: %sB body named %s, family median %sB, no same-method or same-class caller; "
                                   "name it for what it forwards to" % (size, method, median))
                    run("git", "add", "-A", "--", *evidence); unstage_inflight()
                    print(f"harvest: quarantined {row['source']} (identity-suspect: size outlier {method})")
    # A staged source or stash that redeclares a type a header owns fails the
    # hook; adopt_header swaps in the include, byte-gates the file and records
    # what the compiler refuses, so run it on the staged set first
    subprocess.run([sys.executable, "tools/adopt_header.py", "--fix-staged"], cwd=ROOT, capture_output=True)
    run("git", "add", "-A", "--", *evidence); unstage_inflight()
    # A placeholder member the evidence can already name fails the name oracle;
    # its --apply is a byte-neutral rename, so let it settle what it can first
    if keep:
        subprocess.run([sys.executable, "tools/name_oracle.py", "--todo", "--apply", *keep], cwd=ROOT, capture_output=True)
        run("git", "add", "--", *[k for k in keep if (ROOT / k).exists()])
    # A seat that invents a name and pins it with route= over a body the ledger
    # names differently fails pin consistency for the whole harvest (twice on
    # 2026-09-17). Quarantine the source that declares that class and drop its
    # pin rows; the verdict tells the next seat which ledger name to call.
    r = subprocess.run([sys.executable, "tools/pin_consistency.py", "--check"], cwd=ROOT, capture_output=True, text=True, errors="replace")
    if r.returncode and "Route pins: FAIL" in r.stdout + r.stderr:
        import re
        text = r.stdout + r.stderr
        head_syms = {x.rstrip(b"\r\n") for x in show("HEAD", "reverse/symbols.csv").splitlines(True)}
        for m in re.finditer(r"^    (\S+) 0x([0-9A-Fa-f]{8}) \(route=0x[0-9A-Fa-f]+\)\n\s+(.*)$", text, re.M):
            name, why = m.group(1), m.group(3)
            klass = re.search(r"@(Rva[0-9A-Fa-f]{8}\w*|\w+)@@", name)
            owner = None
            for src in keep:
                if klass and (ROOT / src).exists() and klass.group(1) in (ROOT / src).read_text(encoding="utf-8", errors="replace"):
                    owner = src; break
            spath = ROOT / "reverse/symbols.csv"
            rows_ = spath.read_bytes().splitlines(True)
            spath.write_bytes(b"".join(x for x in rows_ if x.rstrip(b"\r\n") in head_syms or not x.startswith(name.encode() + b",")))
            if owner:
                quarantine(owner, [], why="pin gate: %s is an inadmissible route= pin (%s); call the ledger's own name for that body" % (name, why[:160]))
                keep.remove(owner)
            run("git", "add", "-A", "--", *evidence); unstage_inflight()
            print(f"harvest: dropped inadmissible route pin {name}" + (f"; quarantined {owner}" if owner else ""))
    r = subprocess.run([sys.executable, "tools/check_csv.py", "--staged"], cwd=ROOT, capture_output=True, text=True, errors="replace")
    if r.returncode:
        import re
        # stashes whose body landed by another route: retire them (git rm)
        stale = re.findall(r"(reverse/attempts/0x[0-9a-f]{8}\.cpp): 0x[0-9a-f]+ already has real C\+\+", r.stdout + r.stderr)
        if stale:
            run("git", "rm", "-q", "-f", "--ignore-unmatch", "--", *stale)
            print(f"harvest: retired {len(stale)} landed stash(es)")
        # a scratch stash (no score header) whose seat is gone and which HEAD
        # never held is an orphan, not evidence: set it aside for the record
        orphans = [p for p in re.findall(r"(reverse/attempts/0x[0-9a-f]{8}\.cpp): line 2 must read", r.stdout + r.stderr)
                   if subprocess.run(["git", "cat-file", "-e", f"HEAD:{p}"], cwd=ROOT, capture_output=True).returncode]
        for p in orphans:
            dest = ROOT / "build/orphan_stashes" / Path(p).name
            dest.parent.mkdir(parents=True, exist_ok=True)
            subprocess.run(["git", "reset", "-q", "--", p], cwd=ROOT)
            (ROOT / p).replace(dest)
        if orphans:
            print(f"harvest: set aside {len(orphans)} orphan scratch stash(es) under build/orphan_stashes")
        env = dict(os.environ, HARVEST_HAS_LOCK="1")
        subprocess.run([sys.executable, "tools/dedup_csv.py"], cwd=ROOT, env=env)
        subprocess.run([sys.executable, "tools/fleet/dedup_keepfirst.py"], cwd=ROOT, env=env)
        minimal_diff_ledgers()
        run("git", "add", "-A", "--", *evidence); unstage_inflight()
        if subprocess.run([sys.executable, "tools/check_csv.py", "--staged"], cwd=ROOT).returncode:
            unstage()
            hands("harvest: check_csv failing; hands needed")
    # The index may hold entries this harvest never staged (a stale branch, a
    # crashed writer). f43040e9c5 committed 19 deliberately deleted generator
    # files that way. Commit only what a harvest is allowed to own, and never
    # a path the project retired.
    staged = out("git", "diff", "--cached", "--name-only").splitlines()
    allowed = tuple(evidence)
    stray = [p for p in staged if not p.startswith(allowed) and p not in cited]
    if stray:
        unstage()
        hands("harvest: index holds paths a harvest may not commit; hands needed:\n  " + "\n  ".join(stray))
    if subprocess.run([sys.executable, "tools/retired_guard.py", "--staged"], cwd=ROOT).returncode:
        unstage()
        hands("harvest: a retired path is staged; hands needed")
    if subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=ROOT).returncode:
        # seats' add_match and the watchdog run git here too; a transient
        # .git/index.lock is not a hook failure, so wait it out (3 x 20 s)
        import time
        for attempt in range(4):
            r = subprocess.run(["git", "commit", "-q", "-m", msg],
                               cwd=ROOT, capture_output=True, text=True, errors="replace")
            if r.returncode == 0:
                break
            if "index.lock" not in r.stderr or attempt == 3:
                sys.stdout.write(r.stdout); sys.stderr.write(r.stderr)
                # leave nothing staged: the next pass must be able to try again
                # (it quarantines what it can name) instead of refusing our index
                unstage()
                why = [l for l in (r.stdout + r.stderr).splitlines() if "PRE-COMMIT FAILED" in l]
                hands("harvest: commit failed: " + (why[-1] if why else "see hook output above"))
            time.sleep(20)
    MARKER.unlink(missing_ok=True)
    old = out("git", "rev-parse", "HEAD")
    portable_lock.unlock(h)

    # rebase + push in a clean worktree
    if not WT.exists():
        run("git", "worktree", "add", "-q", "--detach", str(WT), old)
    # others push every minute and the push hook takes minutes: retry the whole
    # fetch/rebase/push instead of waiting 15 minutes for the next loop pass
    for attempt in range(5):
        run("git", "checkout", "-q", "--detach", old, cwd=WT)
        run("git", "fetch", "-q", "origin", "master", cwd=WT)
        rc = run("git", "rebase", "origin/master", cwd=WT, check=False).returncode
        while rc:
            # resolve what the fleet's registers always conflict on (the ledgers are
            # rebuilt from origin + delta below anyway): append-only registers by union,
            # reverse/name_corrections.json as a list union, a stash by "our commit is the
            # later word" (deleted if we retired it, else our bank). Anything else: hands.
            conflicts = out("git", "diff", "--name-only", "--diff-filter=U", cwd=WT).split()
            def resolvable(c):
                return c.endswith((".tsv", ".log", ".csv")) or c == "reverse/name_corrections.json" or c.startswith("reverse/attempts/")
            if not conflicts or not all(resolvable(c) for c in conflicts):
                run("git", "rebase", "--abort", cwd=WT, check=False)
                hands("harvest: rebase conflict in build/wt on " + " ".join(conflicts) + "; hands needed")
            for c in conflicts:
                if c == "reverse/name_corrections.json":
                    import json
                    def side(n):
                        raw = subprocess.run(["git", "show", f":{n}:{c}"], cwd=WT, capture_output=True, text=True, errors="replace").stdout
                        return json.loads(raw) if raw.strip() else []
                    seen, merged = set(), []
                    for e in side(2) + side(3):
                        k = json.dumps(e, sort_keys=True)
                        if k not in seen:
                            seen.add(k); merged.append(e)
                    (WT / c).write_text(json.dumps(merged, indent=1) + "\n", encoding="utf-8")
                elif c.startswith("reverse/attempts/"):
                    if subprocess.run(["git", "show", f":3:{c}"], cwd=WT, capture_output=True).returncode:
                        run("git", "rm", "-q", "-f", "--", c, cwd=WT); continue
                    run("git", "checkout", "--theirs", "--", c, cwd=WT)
                else:
                    raw = (WT / c).read_bytes(); keep, seen = [], set()
                    for line in raw.splitlines(True):
                        if line.startswith((b"<<<<<<<", b"=======", b">>>>>>>")):
                            continue
                        k = line.rstrip(b"\r\n")
                        if k in seen:
                            continue
                        seen.add(k); keep.append(line)
                    (WT / c).write_bytes(b"".join(keep))
                run("git", "add", "--", c, cwd=WT)
            rc = subprocess.run(["git", "rebase", "--continue"], cwd=WT, capture_output=True, text=True,
                                env=dict(os.environ, GIT_EDITOR="true")).returncode
        # The union merge driver resurrects rows origin removed and duplicates the
        # tail when both sides append (2026-09-17: 1,958 duplicate rows, harvest
        # wedged for hours). Rebuild the two ledgers as origin's bytes plus this
        # checkout's real row delta instead of trusting the text merge.
        base = out("git", "merge-base", old, "origin/master", cwd=WT)
        for f in ("reverse/functions.csv", "reverse/symbols.csv"):
            key = lambda x: x.rstrip(b"\r\n")
            was = {key(x) for x in show(base, f).splitlines(True)}
            mine = [key(x) for x in show(old, f).splitlines(True)]
            gone = was - set(mine)
            theirs = show("origin/master", f).splitlines(True)
            have = {key(x) for x in theirs}
            term = b"\r\n" if theirs and theirs[-1].endswith(b"\r\n") else b"\n"
            rebuilt = [x for x in theirs if key(x) not in gone]
            if rebuilt and not rebuilt[-1].endswith(b"\n"):
                rebuilt[-1] += term
            for x in dict.fromkeys(mine):
                if x and x not in was and x not in have:
                    rebuilt.append(x + term)
            (WT / f).write_bytes(b"".join(rebuilt))
        if subprocess.run(["git", "diff", "--quiet", "--", "reverse/functions.csv", "reverse/symbols.csv"], cwd=WT).returncode:
            run("git", "add", "reverse/functions.csv", "reverse/symbols.csv", cwd=WT)
            # Rebuilding can erase a harvest whose only change was row order.
            # Keep its checkpoint even when no content delta remains.
            run("git", "commit", "-q", "--amend", "--no-edit", "--allow-empty", cwd=WT)
        new = out("git", "rev-parse", "HEAD", cwd=WT)
        if subprocess.run([sys.executable, str(WT / "tools/check_csv.py")], cwd=WT).returncode:
            # union-merge artifacts of the rebase: exact duplicate records and mixed
            # terminators. Repair in the worktree copy of the tools and amend.
            env = dict(os.environ, HARVEST_HAS_LOCK="1")
            subprocess.run([sys.executable, str(WT / "tools/fleet/dedup_keepfirst.py")], cwd=WT, env=env)
            subprocess.run([sys.executable, str(WT / "tools/dedup_csv.py")], cwd=WT, env=env)
            run("git", "add", "-A", "reverse", cwd=WT)
            run("git", "commit", "-q", "--amend", "--no-edit", cwd=WT, check=False)
            new = out("git", "rev-parse", "HEAD", cwd=WT)
            if subprocess.run([sys.executable, str(WT / "tools/check_csv.py")], cwd=WT).returncode:
                hands("harvest: rebased ledgers fail check_csv; hands needed")
        # The pre-push hook byte-verifies for ~35 s while other hosts push every
        # minute, so a direct push to master lost 6 of 6 races on 2026-09-17.
        # Push the verified commit to a per-host scratch branch (the hook runs
        # there), then fast-forward master on the server in one API call: the
        # race window is a second. Hosts without gh fall back to the direct push.
        import shutil
        # HARVEST_NO_GH: a remote that is not GitHub (the test fixture, a mirror)
        gh = None if os.environ.get("HARVEST_NO_GH") else shutil.which("gh")
        if gh:
            scratch = "fleet-" + re.sub(r"[^A-Za-z0-9]+", "-", os.environ.get("COMPUTERNAME") or os.environ.get("HOSTNAME") or "host").lower()
            # The pre-push hook ranges from the remote's CURRENT sha of the ref
            # being pushed. A scratch branch left from yesterday makes that range
            # span every commit origin took since (15 other hosts' name
            # regressions refused this host's push on 2026-09-22). Delete it
            # first: a deletion is hook-exempt, and the hook then ranges from
            # merge-base with origin/master, i.e. this commit only.
            run("git", "push", "-q", "origin", f":refs/heads/{scratch}", cwd=WT, check=False, cap=True)
            rc = run("git", "push", "-f", "origin", f"{new}:refs/heads/{scratch}", cwd=WT, check=False).returncode
            if rc:
                hands("harvest: push refused by the pre-push hook (see above); hands needed")
            remote = out("git", "remote", "get-url", "origin", cwd=WT)
            repo = re.sub(r"\.git$", "", re.sub(r"^.*github\.com[:/]", "", remote))
            ff = subprocess.run([gh, "api", "-X", "PATCH", f"repos/{repo}/git/refs/heads/master",
                                 "-f", f"sha={new}", "-F", "force=false"], cwd=WT, capture_output=True, text=True)
            rc = ff.returncode
            # Retain the per-host checkpoint so the next harvest updates an
            # existing ref instead of repeating the slow branch-creation push.
        else:
            rc = run("git", "push", "origin", f"{new}:master", cwd=WT, check=False).returncode
        if not rc:
            break
        print(f"harvest: push raced another lane (attempt {attempt + 1}); rebasing again", flush=True)
    else:
        sys.exit("harvest: push rejected 5 times (raced another lane); rerun")

    portable_lock.lock(h, exclusive=True)
    # Workers may land during fetch/rebase/push now. Never union-append complete
    # ledgers over their replacements, or overwrite an unrelated HEAD/index.
    # Preserve those late landings for the next harvest, which rebases them.
    if (out("git", "rev-parse", "HEAD") != old
            or subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=ROOT).returncode
            or subprocess.run(["git", "diff", "--quiet", old, "--", "reverse"], cwd=ROOT).returncode):
        print(f"harvest: pushed {new[:9]}; local synchronization deferred because workers advanced")
        portable_lock.unlock(h)
        sys.exit(0)

    # move main checkout to the pushed commit without touching in-flight files
    changed = out("git", "diff", "--name-only", old, new).split("\n")
    run("git", "update-ref", "refs/heads/master", new, old)
    refreshed, kept = 0, []
    for f in filter(None, changed):
        dirty = subprocess.run(["git", "diff", "--quiet", old, "--", f], cwd=ROOT).returncode
        if not dirty:
            exists = subprocess.run(["git", "cat-file", "-e", f"{new}:{f}"], cwd=ROOT).returncode == 0
            if exists:
                subprocess.run(["git", "checkout", "-q", new, "--", f], cwd=ROOT, check=False)
            elif (ROOT / f).exists():
                (ROOT / f).unlink()   # deleted upstream (e.g. a retired stash)
            refreshed += 1
        elif f.startswith("reverse/"):
            # a worker appended since `old`: origin's version + those lines
            cur = (ROOT / f).read_bytes()
            known = set(lines(show(old, f))) | set(lines(show(new, f)))
            added, seen = [], set()
            for x in lines(cur):
                if x and x not in known and x not in seen:
                    seen.add(x)
                    added.append(x)
            subprocess.run(["git", "checkout", "-q", new, "--", f], cwd=ROOT, check=True)
            base = (ROOT / f).read_bytes()
            term = b"\r\n" if b"\r\n" in base[:4000] else b"\n"
            if not base.endswith(term):
                base += term
            (ROOT / f).write_bytes(base + term.join(added) + (term if added else b""))
            kept.append(f"{f}(+{len(added)} late lines)")
        else:
            kept.append(f + "(in flight, left)")
    run("git", "reset", "-q")  # index = new HEAD; working tree untouched
    print(f"harvest: pushed {new[:9]}; refreshed {refreshed} files from origin; "
          f"in-flight: {' '.join(kept)[:400]}")
    portable_lock.unlock(h)
