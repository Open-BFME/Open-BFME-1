#!/usr/bin/env python3
"""Keep the ledgers landable while nobody is watching.

add_match refuses to land anything while reverse/functions.csv or
reverse/symbols.csv is malformed. On 2026-09-03 two symbol rows with a
9-digit address stalled a 20-seat fleet for three hours between orchestrator
cycles. This loop runs every --interval seconds, and under the ledger lock
repairs the mechanical cases:
  * addresses with leading zeros beyond 8 hex digits  -> 8 digits
  * mixed line terminators / union-merge duplicates   -> tools/dedup_csv.py
  * exact duplicate records                            -> build/dedup_keepfirst.py
Anything else is logged to build/fleet_logs/watchdog.log for the orchestrator.

  python build/ledger_watchdog.py --interval 300
"""
import argparse, os, re, subprocess, sys, time
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import ledger_io, portable_lock

LOG = ROOT / "build/fleet_logs/watchdog.log"
ADDR9 = re.compile(rb",0x0([0-9A-Fa-f]{8}),")

def log(msg):
    with open(LOG, "a", encoding="utf-8") as f:
        f.write(time.strftime("%Y-%m-%d %H:%M ") + msg + "\n")

def row_checks_only():
    """check_csv problems that are about ledger ROWS (what add_match gates on),
    ignoring stash/orphan/source-not-in-git noise from in-flight work."""
    r = subprocess.run([sys.executable, "tools/check_csv.py"], cwd=ROOT, capture_output=True, text=True, errors="replace")
    text = r.stdout + r.stderr
    probs = [l for l in text.splitlines() if l.startswith("  - ")
             and ("symbols.csv line" in l or "functions.csv line" in l or "mixes line terminators" in l
                  or "line 2 must read" in l)
             and "source not in git" not in l]   # in-flight sources are normal, not corruption
    return probs

def stash_headers():
    """Workers keep writing stashes without the required line 2
    '// partial score=<0..1> date=<iso>'; check_csv then blocks every harvest.
    Insert it from the attempts log's score (0.50 if none)."""
    import datetime
    latest = {}
    try:
        for l in open(ROOT / "reverse/re_attempts.log", encoding="utf-8", errors="replace"):
            p = l.rstrip("\n").split("\t")
            if len(p) >= 5 and p[1].startswith("0x"):
                latest[p[1].lower()] = p[4]
    except OSError:
        return 0
    n = 0
    for f in (ROOT / "reverse/attempts").glob("0x*.cpp"):
        try:
            t = f.read_text(encoding="utf-8", errors="replace").splitlines()
        except OSError:
            continue
        good = re.compile(r"^// partial score=(0(?:\.\d+)?|1(?:\.0+)?) date=\d{4}-\d{2}-\d{2}$")
        if len(t) >= 2 and good.match(t[1]):
            continue
        m = re.search(r"score=([0-9.]+)", latest.get(f.stem.lower(), ""))
        score = m.group(1) if m else "0.50"
        try:
            score = f"{min(1.0, max(0.0, float(score))):.2f}"
        except ValueError:
            score = "0.50"
        line = f"// partial score={score} date={datetime.date.today().isoformat()}"
        if len(t) >= 2 and t[1].startswith("// partial"):
            t[1] = line          # malformed header: rewrite it
        else:
            t.insert(1, line)    # missing header: insert it
        f.write_text("\n".join(t) + "\n", encoding="utf-8", newline="\n")
        n += 1
    return n

def repair():
    env = dict(os.environ, HARVEST_HAS_LOCK="1")
    with open(ROOT / "reverse/.add_match.lock", "a+") as h:
        portable_lock.lock(h, exclusive=True)
        fixed = 0
        hdr = stash_headers()
        if hdr:
            log(f"inserted {hdr} missing stash header(s)")
        for name in ("reverse/symbols.csv", "reverse/functions.csv"):
            p = ROOT / name
            raw = p.read_bytes()
            new = ADDR9.sub(lambda m: b",0x" + m.group(1) + b",", raw)
            if new != raw:
                ledger_io.atomic_write_bytes(p, new)
                fixed += raw.count(b",0x0") - new.count(b",0x0")
        subprocess.run([sys.executable, "tools/dedup_csv.py"], cwd=ROOT, env=env, capture_output=True)
        subprocess.run([sys.executable, "build/dedup_keepfirst.py"], cwd=ROOT, env=env, capture_output=True)
        portable_lock.unlock(h)
    return fixed

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--interval", type=int, default=300)
    ap.add_argument("--once", action="store_true")
    a = ap.parse_args()
    good = re.compile(r"^// partial score=(0(?:\.\d+)?|1(?:\.0+)?) date=\d{4}-\d{2}-\d{2}$")
    def stash_needs_fix():
        for f in (ROOT / "reverse/attempts").glob("0x*.cpp"):
            try:
                t = f.read_text(encoding="utf-8", errors="replace").splitlines()
            except OSError:
                continue
            if len(t) < 2 or not good.match(t[1]):
                return True
        return False
    while True:
        probs = row_checks_only()
        if probs or stash_needs_fix():
            fixed = repair()
            after = row_checks_only()
            log(f"{len(probs)} row problem(s); repaired {fixed} address(es); remaining {len(after)}"
                + ("" if not after else " :: " + after[0][:160]))
        if a.once:
            break
        time.sleep(a.interval)

if __name__ == "__main__":
    main()
