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
    # a seat that lands a real name with plain add_match (no --replace-rva) leaves
    # the gen-* placeholder row on the same range; check_csv says the placeholder
    # yields, so retract it and tombstone it in deleted_rows.csv
    import ledger_io
    raw = p.read_bytes()
    def norm(x): return x.decode("utf-8", "replace") if isinstance(x, bytes) else x
    real = {}
    for payload, _ in ledger_io.split_records(raw):
        f = [norm(x) for x in ledger_io.fields(payload)]
        if len(f) >= 6 and f[5] == "matched" and not f[4].startswith("Code/gen_") and not f[0].startswith(("?d_", "?j_", "?b_", "?dup_")):
            real.setdefault(f[2].upper(), f[0])
    victims = []
    def keep(f):
        f = [norm(x) for x in f]
        if len(f) >= 6 and f[0].startswith("?d_") and f[4].startswith("Code/gen_asm/") and f[2].upper() in real:
            victims.append((f[0], f[2])); return False
        return True
    new, dropped = ledger_io.rewrite(raw, keep)
    if dropped:
        ledger_io.atomic_write_bytes(p, new)
        d = ROOT / "reverse/deleted_rows.csv"; b = d.read_bytes()
        term = b"\r\n" if b"\r\n" in b[:2000] else b"\n"
        if not b.endswith(term): b += term
        for name, rva in victims:
            b += f"{name},{rva},gen-dump placeholder retracted: range owned by real C++ {real[rva.upper()]} landed by the fleet".encode() + term
        ledger_io.atomic_write_bytes(d, b)
        print(f"ledger_prep: retracted {dropped} gen placeholder row(s) shadowed by real C++")
    # seats append LF rows into a CRLF ledger; normalize before the check
    subprocess.run([sys.executable, str(ROOT / "tools/dedup_csv.py")], cwd=ROOT, env=dict(os.environ, HARVEST_HAS_LOCK="1"))
    if not os.environ.get("HARVEST_HAS_LOCK"):
        portable_lock.unlock(h)
