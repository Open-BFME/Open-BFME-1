#!/usr/bin/env python3
"""Orchestrator harvest. Workers never run git; this is the only VCS path.

Under the ledger lock: stage ledgers + cited sources, verify, commit. Then
rebase+push in a SEPARATE worktree (build/wt) so in-flight worker edits to
tracked Code/ files never block the pull, and finally move the main
checkout's HEAD to the pushed commit, refreshing only files whose working copy
still equals the old commit (untouched by anyone in flight). If workers advance
the ledgers during network work, preserve their edits and defer local sync.
"""
import csv, os, subprocess, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2 if Path(__file__).resolve().parent.name == "fleet" else 1]
sys.path.insert(0, str(ROOT / "tools"))
import portable_lock

def run(*cmd, cwd=ROOT, check=True, cap=False):
    print("$", " ".join(cmd), flush=True)
    return subprocess.run(cmd, cwd=cwd, check=check, capture_output=cap, text=cap)

def out(*cmd, cwd=ROOT):
    return subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, check=True).stdout.strip()

def show(rev, f):
    return subprocess.run(["git", "show", f"{rev}:{f}"], cwd=ROOT, capture_output=True).stdout

def lines(b):
    return [x.rstrip(b"\r") for x in b.split(b"\n")]

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
        sys.exit("harvest: existing staged work belongs to another writer; leaving it untouched")
    dependencies = out("git", "diff", "--name-only", "--", "*.h", "*.hpp", "reference", "tools", ".githooks", "AGENTS.md")
    untracked_headers = out("git", "ls-files", "--others", "--exclude-standard", "--", "Code/*.h", "Code/*.hpp", "reference")
    if dependencies or untracked_headers:
        sys.exit("harvest: changed shared dependencies need a separate verified commit; not sweeping them into fleet work")
    subprocess.run([sys.executable, "tools/fleet/ledger_prep.py"], cwd=ROOT,
                   env=dict(os.environ, HARVEST_HAS_LOCK="1"), check=True)
    # Only fleet-owned evidence and ledger-cited sources belong in this commit.
    # Never sweep unrelated docs/tools/headers or every dirty Code source.
    evidence = [p for p in ("reverse/functions.csv", "reverse/symbols.csv",
                "reverse/re_attempts.log", "reverse/attempts", "reverse/attempt_history")
                if (ROOT / p).exists()]
    run("git", "add", "-A", "--", *evidence)
    cited = set()
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as ledger:
        cited = {r["source"] for r in csv.DictReader(ledger) if r["status"] == "matched"
                 and r["source"].startswith("Code/") and r["source"].endswith((".cpp", ".c"))}
    changed_sources = out("git", "diff", "--name-only", "--", "Code").splitlines()
    for source in changed_sources:
        if source in cited:
            run("git", "add", "--", source)
    unt = out("git", "ls-files", "--others", "--exclude-standard", "Code").split()
    keep = [u for u in unt if u in cited]
    if keep:
        run("git", "add", "--", *keep)
    print(f"harvest: staged {len(keep)} new cited sources, skipped {len(unt)-len(keep)} in-flight")
    r = subprocess.run([sys.executable, "tools/check_csv.py"], cwd=ROOT, capture_output=True, text=True, errors="replace")
    if r.returncode:
        import re
        # stashes whose body landed by another route: retire them (git rm)
        stale = re.findall(r"(reverse/attempts/0x[0-9a-f]{8}\.cpp): 0x[0-9a-f]+ already has real C\+\+", r.stdout + r.stderr)
        if stale:
            run("git", "rm", "-q", "-f", "--ignore-unmatch", "--", *stale)
            print(f"harvest: retired {len(stale)} landed stash(es)")
        env = dict(os.environ, HARVEST_HAS_LOCK="1")
        subprocess.run([sys.executable, "tools/dedup_csv.py"], cwd=ROOT, env=env)
        subprocess.run([sys.executable, "tools/fleet/dedup_keepfirst.py"], cwd=ROOT, env=env)
        run("git", "add", "-A", "--", *evidence)
        if subprocess.run([sys.executable, "tools/check_csv.py"], cwd=ROOT).returncode:
            run("git", "reset", "-q")
            sys.exit("harvest: check_csv failing; hands needed")
    if subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=ROOT).returncode:
        run("git", "commit", "-q", "-m", msg + "\n\nCo-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>")
    old = out("git", "rev-parse", "HEAD")
    portable_lock.unlock(h)

    # rebase + push in a clean worktree
    if not WT.exists():
        run("git", "worktree", "add", "-q", "--detach", str(WT), old)
    run("git", "checkout", "-q", "--detach", old, cwd=WT)
    run("git", "fetch", "-q", "origin", "master", cwd=WT)
    rc = run("git", "rebase", "origin/master", cwd=WT, check=False).returncode
    if rc:
        run("git", "rebase", "--abort", cwd=WT, check=False)
        sys.exit("harvest: rebase conflict in build/wt; hands needed")
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
            sys.exit("harvest: rebased ledgers fail check_csv; hands needed")
    rc = run("git", "push", "origin", f"{new}:master", cwd=WT, check=False).returncode
    if rc:
        sys.exit("harvest: push rejected (raced another lane); rerun")

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
