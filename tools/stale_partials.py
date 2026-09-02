#!/usr/bin/env python3
"""Keep the banked-attempt queue honest. Read-only report + CSV output.

Two things went wrong repeatedly on 2026-09-02 and this catches both:

  * STALE: the attempts log's latest entry for an RVA says `partial`/`blocked`,
    but reverse/functions.csv already points that RVA at real C++ -- someone
    landed it by another route. Agents kept re-working these.
  * RE-QUEUE: a body was banked because a callee/global it needs was unpinned;
    every address its evidence cites is now claimed or pinned, so the blocker
    is gone but nobody went back.

  python3 tools/stale_partials.py                 # summary
  python3 tools/stale_partials.py --requeue out.csv  # write the re-queue list
  python3 tools/stale_partials.py --stale           # list stale entries (+ stash files to delete with git rm)

Never writes to the ledgers or the log; the outputs are a report and an optional
CSV. Retiring a stash is a `git rm` (they are tracked) followed by a commit.
"""
import argparse
import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def load():
    rows = {}
    dump = {}
    claimed = set()
    for r in csv.DictReader(open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace")):
        try:
            rva = int(r["target_rva"], 16)
        except ValueError:
            continue
        rows[rva] = r
        claimed.add(rva)
        if r["source"].endswith((".asm", ".s")):
            dump[rva] = int(r["target_size"] or 0)
    pinned = set()
    for r in csv.reader(open(ROOT / "reverse/symbols.csv", newline="", encoding="utf-8", errors="replace")):
        if len(r) > 1 and r[1].startswith("0x"):
            try:
                pinned.add(int(r[1], 16))
            except ValueError:
                pass
    latest = {}
    for l in open(ROOT / "reverse/re_attempts.log", encoding="utf-8", errors="replace"):
        p = l.rstrip("\n").split("\t")
        if len(p) >= 5:
            try:
                latest[int(p[1], 16)] = p
            except ValueError:
                pass
    return rows, dump, claimed, pinned, latest


def is_naked(src):
    if src.endswith((".asm", ".s", ".lib")):
        return True
    try:
        t = (ROOT / src).read_text(encoding="utf-8", errors="replace")
    except OSError:
        return True
    return "__declspec(naked)" in t or "_emit" in t


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--requeue", help="write re-queue CSV here")
    ap.add_argument("--stale", action="store_true")
    a = ap.parse_args()
    rows, dump, claimed, pinned, latest = load()

    stale, requeue = [], []
    for rva, p in latest.items():
        status = p[3]
        if status not in ("partial", "blocked"):
            continue
        r = rows.get(rva)
        if r and not is_naked(r["source"]):
            stash = ROOT / "reverse/attempts" / f"0x{rva:08x}.cpp"
            stale.append((rva, p[0], r["source"], stash.exists()))
            continue
        if rva not in dump:
            continue
        ev = p[4]
        if not re.search(r"unresolved|unpinned|not pinned|callee|no pin|unidentified callee|needs.*pin|global", ev, re.I):
            continue
        cited = set()
        for h in re.findall(r"0x0*([0-9A-Fa-f]{5,8})", ev):
            v = int(h, 16)
            if v != rva and v < 0x1000000:
                cited.add(v)
        if not cited:
            continue
        if all((c in claimed or c in pinned or (c - 0x400000) in claimed or (c - 0x400000) in pinned) for c in cited):
            requeue.append((dump[rva], rva, p[0], status, len(cited)))

    print(f"banked entries: {sum(1 for p in latest.values() if p[3] in ('partial','blocked'))}")
    print(f"STALE (already real C++): {len(stale)}  -- {sum(1 for s in stale if s[3])} still have a stash file to git rm")
    print(f"RE-QUEUE (blockers resolved): {len(requeue)} bodies, {sum(r[0] for r in requeue)} bytes")
    if a.stale:
        for rva, sym, src, has in sorted(stale):
            print(f"  0x{rva:08X} {sym[:60]:60} -> {Path(src).name}{'  [stash present]' if has else ''}")
    if a.requeue:
        requeue.sort(reverse=True)
        with open(a.requeue, "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["size", "rva", "symbol", "status", "cited_addrs"])
            for size, rva, sym, st, n in requeue:
                w.writerow([size, f"0x{rva:08x}", sym, st, n])
        print(f"wrote {a.requeue}")


if __name__ == "__main__":
    main()
