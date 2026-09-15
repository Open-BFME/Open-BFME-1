#!/usr/bin/env python3
"""One answer to "is this address still open work, and what has been tried?"

Every picker and brief used to answer this on its own, and they disagreed:
pick_finish.py required the LATEST verdict to be `partial` and so hid 234 of
381 servable near-misses behind a later `blocked`; pick_big.py skipped a body
whose latest record merely carried today's date; brief.py dropped only
SecuROM dead ends. The same class of starvation reappears in every new tool
unless the predicate lives in exactly one place. It lives here.

Rules (Claude/Astra consensus, 2026-09-15; see docs/baseline-2026-09-15.md):

  * a DUMP row is open work: gen-dump note or a .asm/.s source; it fixes a
    boundary and holds no source (build.is_scaffold_row is the canonical
    note test, the suffix test covers MASM rows outside Code/gen_asm/).
  * a DEAD-END verdict retires the address: no-match, refuted, ... are
    findings about the BOUNDARY (tools/re_log.DEAD_END_STATUSES).
  * a DEFERRAL never retires: blocked/attempted/abandoned/partial say a
    session failed, not that the address is wrong.
  * a banked STASH outlives a later deferral: the body is the evidence.
  * BUSY means a live fleet lease (tools/fleet_run claims, pid-checked) or a
    seat currently on it per seats.log; append-only claim files are not
    consulted -- they starved the fleet once every body had been touched.

Library use only; nothing here writes.
"""
import csv
import json
import re
import time
from pathlib import Path

import build
import re_log

ROOT = Path(__file__).resolve().parents[1]
ANON_RE = re.compile(r"^\?(d|dup|j)_[0-9a-fA-F]{8}@@")


def load_rows(path=None, tries=4):
    """functions.csv rows, retrying a torn read while another lane writes."""
    path = path or ROOT / "reverse/functions.csv"
    for _ in range(tries):
        try:
            with open(path, newline="", encoding="utf-8", errors="replace") as fh:
                rows = list(csv.DictReader(fh))
            if all(r.get("source") is not None and r.get("target_rva") is not None
                   for r in rows):
                return rows
        except OSError:
            pass
        time.sleep(1)
    return []


def rva_of(row):
    text = row.get("target_rva") or ""
    try:
        return int(text, 16) if text.startswith("0x") else None
    except ValueError:
        return None


def is_dump_row(row):
    return (row.get("status") == "matched"
            and (build.is_scaffold_row(row)
                 or Path(row.get("source", "")).suffix.lower() in (".asm", ".s")))


def is_anonymous(name):
    return bool(ANON_RE.match(name or ""))


def latest_verdicts(path=None):
    """{rva:int -> latest live status} from the attempt log."""
    return {rva: fields[3] for rva, fields in re_log.latest_records(path).items()}


def retired(rva, latest):
    return latest.get(rva) in re_log.DEAD_END_STATUSES


def deferred(rva, latest):
    return latest.get(rva) in re_log.DEFERRED_STATUSES


def stash(rva):
    """(path, score) for a banked body at rva, else None."""
    return re_log.stash_for(rva)


def attempt_counts(path=None):
    """{rva:int -> number of five-field verdict rows}, any status."""
    path = path or re_log.RE_ATTEMPTS
    counts = {}
    if not path.exists():
        return counts
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        f = line.split("\t")
        if len(f) >= 5 and f[1].startswith("0x"):
            try:
                rva = int(f[1], 16)
            except ValueError:
                continue
            counts[rva] = counts.get(rva, 0) + 1
    return counts


def open_dumps(rows=None, latest=None, min_size=0, max_size=None, anonymous=None):
    """Dump rows that are not retired, in a size window. anonymous=True keeps
    only ?d_/?dup_/?j_ names; False keeps only named rows; None keeps both."""
    rows = load_rows() if rows is None else rows
    latest = latest_verdicts() if latest is None else latest
    out = []
    for row in rows:
        rva = rva_of(row)
        if rva is None or not is_dump_row(row):
            continue
        size = int(row.get("target_size") or 0)
        if size < min_size or (max_size is not None and size > max_size):
            continue
        if retired(rva, latest):
            continue
        if anonymous is not None and is_anonymous(row["name"]) != anonymous:
            continue
        out.append(row)
    return out


def finish_bodies(min_score=0.9, rows=None, latest=None):
    """[(row, stash_path, score)] for dumps with a banked body >= min_score,
    best score first then largest. A later deferral does not hide the stash;
    a later dead end retires it."""
    out = []
    for row in open_dumps(rows, latest):
        found = stash(rva_of(row))
        if found and found[1] >= min_score:
            out.append((row, found[0], found[1]))
    out.sort(key=lambda t: (-t[2], -int(t[0].get("target_size") or 0)))
    return out


def busy_rvas(root=None, seats_log=None):
    """Addresses a live worker owns: fleet_run leases (pid-checked) plus seats
    currently '->' on an RVA in seats.log. Lower-case '0x%08x' strings."""
    root = root or ROOT
    import fleet_run
    busy = set(fleet_run.active_rvas(root))
    seats_log = seats_log or root / "build" / "fleet_logs" / "seats.log"
    if seats_log.exists():
        state = {}
        for line in seats_log.read_text(encoding="utf-8", errors="replace").splitlines():
            m = re.match(r"\S+ (?:vt)?seat (\S+) (->|done) (.+)", line)
            if m:
                for token in m.group(3).split():
                    if token.lower().startswith("0x"):
                        state[token.lower()] = m.group(2) == "->"
        busy |= {rva for rva, on in state.items() if on}
    return busy


def recent_run_rvas(hours=48, root=None):
    """Addresses any immutable fleet run targeted in the last `hours`: the
    honest replacement for append-only claim files. A body a session just
    left is not served again until the window passes or its stash changes."""
    root = root or ROOT
    cutoff = time.time() - hours * 3600
    out = set()
    runs = root / "build" / "fleet_runs"
    if not runs.exists():
        return out
    for record in runs.glob("*/record.json"):
        try:
            data = json.loads(record.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            continue
        if data.get("start", 0) >= cutoff:
            out |= {r.lower() for r, _ in data.get("targets", [])}
    return out
