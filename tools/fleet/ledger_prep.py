#!/usr/bin/env python3
r"""Pre-harvest repair of the two mechanical states that stalled harvest on 2026-09-04:
  * a stash file deleted from disk while re_attempts.log still cites it -> check_csv crashes
    instead of reporting; restore it from HEAD so harvest can retire it properly
  * a seat wrote a Windows path (Code\...) into functions.csv -> harvest never stages the
    cited source; normalize to forward slashes
Runs under the ledger lock. Safe to run any time."""
import os, subprocess, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import portable_lock
BS = chr(92).encode()
with open(ROOT / "reverse/.add_match.lock", "a+") as h:
    if not os.environ.get("HARVEST_HAS_LOCK"):
        portable_lock.lock(h, exclusive=True)
    gone = subprocess.run(["git", "ls-files", "-d", "reverse/attempts"], cwd=ROOT, capture_output=True, text=True).stdout.split()
    if gone:
        subprocess.run(["git", "checkout", "HEAD", "--", *gone], cwd=ROOT)
        print(f"ledger_prep: restored {len(gone)} deleted stash(es) for retirement")
    p = ROOT / "reverse/functions.csv"
    b = p.read_bytes()
    n = b.count(b"Code" + BS)
    if n:
        # only the source column is a path; notes may legitimately contain backslashes
        out = []
        for line in b.split(b"\n"):
            parts = line.split(b",")
            if len(parts) > 4 and parts[4].startswith(b"Code" + BS):
                parts[4] = parts[4].replace(BS, b"/")
            out.append(b",".join(parts))
        with open(p, "r+b") as f:
            f.seek(0); f.write(b"\n".join(out)); f.truncate()
        print(f"ledger_prep: normalized {n} backslash source path(s)")
    # seats append LF rows into a CRLF ledger; normalize before the check
    subprocess.run([sys.executable, str(ROOT / "tools/dedup_csv.py")], cwd=ROOT, env=dict(os.environ, HARVEST_HAS_LOCK="1"))
    if not os.environ.get("HARVEST_HAS_LOCK"):
        portable_lock.unlock(h)
