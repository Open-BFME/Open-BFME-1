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
  * BUSY means a live fleet lease (tools/fleet_run claims, pid-checked) or,
    until a stopped-fleet cutover, an old seat log assignment. New selections
    are advisory and never create a log assignment.

Library use only; nothing here writes.
"""
import csv
import bisect
import hashlib
import json
import datetime
import re
import time
from pathlib import Path

import build
import re_log

ROOT = Path(__file__).resolve().parents[1]
ANON_RE = re.compile(r"^\?(d|dup|j)_[0-9a-fA-F]{8}@@")


class LedgerUnreadable(RuntimeError):
    """functions.csv could not be read whole; an empty ledger is not an answer."""


def load_rows(path=None, tries=4, wait=1):
    """functions.csv rows, retrying a torn read while another lane writes."""
    path = path or ROOT / "reverse/functions.csv"
    reason = "no read was tried"
    for _ in range(tries):
        try:
            with open(path, newline="", encoding="utf-8", errors="replace") as fh:
                reader = csv.DictReader(fh)
                rows, short = [], None
                for row in reader:
                    if short is None and (row.get("source") is None
                                          or row.get("target_rva") is None):
                        short = reader.line_num
                    rows.append(row)
            if short is None:
                return rows
            reason = f"line {short} has fewer columns than the header"
        except OSError as exc:
            reason = f"{type(exc).__name__}: {exc}"
        time.sleep(wait)
    raise LedgerUnreadable(f"{path}: {reason} (after {tries} reads)")


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


# Verdicts after which a body leaves the anonymous and mid lanes unless it is
# unlocked. Measured 2026-09-17 over 3,000 verdicts: 5+ prior verdicts land at
# 1-2% per session, fresh bodies at ~7%. Same number as next_work's finish cap.
ATTEMPT_CAP = 5


QUICK_LOOK_MINUTES = 10
_MINUTES = re.compile(r"(?:^|\s)t=(\d+)")


def quick_look(status, evidence):
    """A `blocked` row with no banked body from a session that spent at most
    QUICK_LOOK_MINUTES on it and no recorded blocker: somebody looked, nobody
    tried. A blocker records a concrete failed lever, even in a short session.
    4,954 bodies got
    one of these (median 2 minutes, "no named caller") mostly before opaque
    names were allowed. Where a real session came back later, 45% landed; 1,812
    (403 KB) were never revisited because the look counted as an attempt."""
    if status != "blocked" or "stash=" in evidence or "blocker=" in evidence:
        return False
    minutes = _MINUTES.search(evidence)
    return bool(minutes) and int(minutes.group(1)) <= QUICK_LOOK_MINUTES


def attempt_counts(path=None):
    """{rva:int -> number of five-field verdict rows}. A quick look is not an
    attempt (see quick_look); every other status counts."""
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
            if quick_look(f[3], f[4]):
                continue
            counts[rva] = counts.get(rva, 0) + 1
    return counts


CARVED = ROOT / "reverse" / "carved.csv"


def carved_rows(path=None, rows=None):
    """Return live carved candidates shaped like ``functions.csv`` rows.

    Filtering against the current ledger makes shrink-on-land immediate even
    if a seat reads the old carved file between regeneration runs.
    """
    path = Path(path or CARVED)
    if not path.exists():
        return []
    rows = load_rows() if rows is None else rows
    claimed = []
    for row in rows:
        rva = rva_of(row)
        try:
            size = int(row.get("target_size") or 0)
        except (TypeError, ValueError):
            continue
        if rva is not None and size > 0:
            claimed.append((rva, rva + size))
    claimed.sort()
    merged = []
    for start, end in claimed:
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(merged[-1][1], end))
        else:
            merged.append((start, end))
    claimed_starts = [start for start, _ in merged]
    out = []
    with path.open(newline="", encoding="utf-8", errors="replace") as fh:
        for row in csv.DictReader(fh):
            # Ghidra's Unwind@ entries are EH cleanup fragments that borrow
            # their parent's frame, not independently callable C++ bodies.
            if (row.get("ghidra") or "").startswith("Unwind@"):
                continue
            raw_rva = row.get("target_rva") or row.get("rva") or ""
            rva = rva_of({"target_rva": raw_rva})
            try:
                size = int(row.get("target_size") or row.get("size") or 0)
            except (TypeError, ValueError):
                continue
            if rva is None or size <= 0:
                continue
            index = bisect.bisect_right(claimed_starts, rva) - 1
            overlap = any(0 <= candidate < len(merged) and
                          rva < merged[candidate][1] and
                          merged[candidate][0] < rva + size
                          for candidate in (index, index + 1))
            if overlap:
                continue
            out.append({
                "name": row.get("name") or f"?d_{rva:08x}@@YAXXZ",
                "export_rva": "",
                "target_rva": f"0x{rva:08X}",
                "target_size": str(size),
                "source": "reverse/carved.csv",
                "status": "carved",
                "notes": ";".join(filter(None, (
                    f"start={row.get('start_evidence', '')}",
                    f"callers={row.get('callers', '0')}",
                    f"end={row.get('end_evidence', '')}",
                    f"ghidra={row.get('ghidra', '')}"))),
                "start_evidence": row.get("start_evidence", ""),
                "callers": row.get("callers", "0"),
                "end_evidence": row.get("end_evidence", ""),
                "ghidra": row.get("ghidra", ""),
            })
    return out


def is_carved_row(row):
    return row.get("status") == "carved" and row.get("source") == "reverse/carved.csv"


def open_dumps(rows=None, latest=None, min_size=0, max_size=None, anonymous=None,
               include_carved=False, carved_path=None):
    """Dump rows that are not retired, in a size window. anonymous=True keeps
    only ?d_/?dup_/?j_ names; False keeps only named rows; None keeps both."""
    rows = load_rows() if rows is None else rows
    if include_carved:
        rows = list(rows) + carved_rows(path=carved_path, rows=rows)
    latest = latest_verdicts() if latest is None else latest
    out = []
    for row in rows:
        rva = rva_of(row)
        if rva is None or not (is_dump_row(row) or
                               (include_carved and is_carved_row(row))):
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


def stash_date(path):
    """The ISO date on a stash header's second line, else None."""
    try:
        lines = Path(path).read_text(encoding="utf-8", errors="replace").splitlines()
    except OSError:
        return None
    m = re.search(r"date=(\d{4}-\d{2}-\d{2})", lines[1]) if len(lines) > 1 else None
    if not m:
        return None
    try:
        return datetime.date.fromisoformat(m.group(1))
    except ValueError:
        return None


def finish_bodies(min_score=0.9, rows=None, latest=None, max_attempts=0,
                  counts=None, cooldown_days=0, today=None):
    """[(row, stash_path, score)] for dumps with a banked body >= min_score,
    best score first then largest. A later deferral does not hide the stash;
    a later dead end retires it.

    Two guards keep the tier from becoming a treadmill. Measured 2026-09-16
    over the last 800 verdict rows: 10 were first attempts, 259 were on bodies
    already tried eight or more times, and 550 of the 800 landed on bodies
    with six or more prior verdicts -- every default seat drew the same 270
    near misses by score. `max_attempts` > 0 hides a body with that many
    verdict rows (the hard set; serve it to a stronger lane on purpose, see
    hard_bodies). `cooldown_days` > 0 hides a stash re-banked that recently,
    which is the only cross-host signal in git: the date on the stash header.
    """
    from conversion_gate import is_lift_line

    out = []
    counts = counts if counts is not None else (attempt_counts() if max_attempts else {})
    today = today or datetime.date.today()
    for row in open_dumps(rows, latest):
        rva = rva_of(row)
        found = stash(rva)
        if not found or found[1] < min_score:
            continue
        # A saved naked/__emit transcription can probe exact by construction,
        # but the conversion gate cannot accept it as C++. Keep it in the
        # attempt bank without advertising it as one lever from landing.
        if any(is_lift_line(line) for line in
               found[0].read_text(encoding="utf-8", errors="replace").splitlines()):
            continue
        if max_attempts and counts.get(rva, 0) >= max_attempts:
            continue
        if cooldown_days:
            banked = stash_date(found[0])
            if banked and (today - banked).days < cooldown_days:
                continue
        out.append((row, found[0], found[1]))
    out.sort(key=lambda t: (-t[2], -int(t[0].get("target_size") or 0)))
    return out


def hard_bodies(min_score=0.9, max_attempts=5, rows=None, latest=None, counts=None):
    """The near misses finish_bodies hides under `max_attempts`: banked at or
    above min_score, still a dump, tried at least max_attempts times. These
    need a different lever or a reviewer, not a sixth luna pass."""
    counts = counts if counts is not None else attempt_counts()
    served = finish_bodies(min_score, rows, latest)
    return [t for t in served if counts.get(rva_of(t[0]), 0) >= max_attempts]


UNLOCKED = ROOT / "reverse" / "unlocked.txt"


def unlocked_rvas(path=None):
    """{rva:int -> tag} from reverse/unlocked.txt: dump bodies whose shared
    blocker (a family shim, a class layout, a set of pins) a stronger session
    has already landed, so a luna seat's context pack now proves their
    callees. Lines are `0x%08x <tag>`; `#` comments. pick_anon adds warmth
    for a listed body; the file is shrink-on-land, hygiene removes rows whose
    address is no longer a dump."""
    path = path or UNLOCKED
    out = {}
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        rva, _, tag = line.partition(" ")
        if not rva.lower().startswith("0x"):
            continue
        try:
            out[int(rva, 16)] = tag.strip()
        except ValueError:
            continue
    return out


BOUNDARY_RE = re.compile(
    r"starts in(side)? (the )?(tail|middle|interior)|starts inside|begins inside|"
    r"tail of (a|another|the) |not a (standalone|function) boundary|no standalone|"
    r"crosses (multiple|unrelated|into)|mid-body|interior of|"
    r"inside (a|another) (live|landed|matched) (helper|body|function)", re.I)


def boundary_suspect(rva, records=None):
    """True when the latest verdict on rva is a deferral whose evidence says the
    queued address is not a function boundary (starts in another body's tail,
    crosses bodies, ...). Seats write those as `blocked` instead of the
    dead-end `no-boundary`, so the address was served again: 301 bodies were
    re-served that way for 559 later sessions (measured 2026-09-16). Pickers
    skip suspects; nothing is retired, an explicit --rvas still serves them."""
    records = re_log.latest_records() if records is None else records
    fields = records.get(rva)
    if not fields or len(fields) < 5:
        return False
    return fields[3] in re_log.DEFERRED_STATUSES and bool(BOUNDARY_RE.search(fields[4]))


def neighbour_density(rows=None, k=6, min_size=60):
    """density(rva:int) -> share of the 2k nearest ledger bodies (by address,
    >= min_size bytes, generated rows ignored) that are landed authored C++,
    or None with fewer than four neighbours. Landed neighbours are what a
    session actually reuses: the class, its layout, the callee declarations."""
    rows = load_rows() if rows is None else rows
    known = []
    for row in rows:
        rva = rva_of(row)
        if rva is None or row.get("status") != "matched" or int(row.get("target_size") or 0) < min_size:
            continue
        source = row["source"]
        if is_dump_row(row):
            known.append((rva, False))
        elif source.endswith((".cpp", ".c")) and not source.startswith("Code/gen_"):
            known.append((rva, True))
    known.sort()
    addresses = [a for a, _ in known]

    def density(rva):
        i = bisect.bisect_left(addresses, rva)
        near = [landed for a, landed in known[max(0, i - k):i] + known[i:i + k + 1] if a != rva][:2 * k]
        return sum(near) / len(near) if len(near) >= 4 else None
    return density


def neighbour_prior(density):
    """Land rate of attempted 300-2,500 B bodies by neighbour density, measured
    2026-09-21 over 2,267 bodies: 7% below a quarter landed, 17%, 20%, and 50%
    where three quarters or more of the neighbours are landed C++."""
    if density is None:
        return 0.15
    return (0.07, 0.17, 0.20, 0.50)[min(int(density * 4), 3)]


def expected_bytes(warmth, size, density=None):
    """Rank key for the anonymous lane: bytes a session is expected to land.
    Measured over 1,500 verdict rows on 2026-09-16: the land rate is flat
    (~7%) from 100 B to 2,500 B, so bytes per attempt scale with size (4 B for
    <100 B bodies, 94 B for 1,000-2,500 B); warmth raises the rate, and so
    does a landed neighbourhood (neighbour_prior). Bodies with no evidence at
    all rank last regardless of size."""
    return (warmth > 0, size * (1 + warmth) * neighbour_prior(density) / 0.15)


def servable(root=None, hours=48):
    """The one predicate every lane should ask before serving a dump body:
    returns ok(rva:int) -> bool. False while a live worker owns the body, for
    `hours` after a run worked on it, once it has ATTEMPT_CAP verdicts (unless
    reverse/unlocked.txt reopens it), after a dead end, and while its boundary
    is suspect. pick_class had its own rules -- a permanent claim file and
    none of the rest -- so a vtable served once was never served again."""
    root = root or ROOT
    taken = {int(a, 16) for a in busy_rvas(root) | recent_run_rvas(hours, root)}
    latest = latest_verdicts()
    records = re_log.latest_records()
    attempts = attempt_counts()
    unlocked = unlocked_rvas()

    def ok(rva):
        if rva in taken:
            return False
        if attempts.get(rva, 0) >= ATTEMPT_CAP and rva not in unlocked:
            return False
        return not (retired(rva, latest) or boundary_suspect(rva, records))
    return ok


def busy_rvas(root=None, seats_log=None):
    """Live run leases plus unreconciled legacy log assignments."""
    root = root or ROOT
    import fleet_run
    busy = set(fleet_run.active_rvas(root))
    seats_log = seats_log or root / "build" / "fleet_logs" / "seats.log"
    for token in legacy_busy_tokens(root, seats_log):
        if token.startswith("0x"):
            try:
                busy.add(f"0x{int(token, 16):08x}")
            except ValueError:
                continue
    return busy


def legacy_busy_tokens(root=None, seats_log=None):
    """Ownerless old-log exclusions, with a conservative stopped-fleet cutover.

    The cutover records the exact closed prefix. If that prefix changes, read
    the whole log again. New old-style assignments after cutover are honored,
    so accidentally restarting an old controller cannot silently bypass them.
    """
    root = root or ROOT
    seats_log = seats_log or root / "build/fleet_logs/seats.log"
    try:
        raw = seats_log.read_bytes()
    except FileNotFoundError:
        raw = b""
    marker = root / "build/fleet_legacy_cutover.json"
    try:
        cut = json.loads(marker.read_text(encoding="utf-8"))
        count = cut["closed_log_bytes"]
        if (isinstance(count, int) and 0 <= count <= len(raw)
                and hashlib.sha256(raw[:count]).hexdigest() == cut["closed_log_sha256"]):
            raw = raw[count:]
    except (OSError, ValueError, KeyError, TypeError):
        pass
    state = {}
    for line in raw.decode("utf-8", errors="replace").splitlines():
        match = re.match(r"\S+ (?:vt)?seat (\S+) (->|done) (.+)", line)
        if match:
            for token in match.group(3).split():
                state[token.lower()] = match.group(2) == "->"
    return {token for token, on in state.items() if on}


def recent_run_rvas(hours=48, root=None):
    """Addresses a fleet run WORKED ON in the last `hours`: the honest
    replacement for append-only claim files. A body a session just left is
    not served again until the window passes or its stash changes.

    Only touched targets cool down (fleet_run.mark_touched, written by probe,
    re_log and add_match). A brief lists up to 14 bodies and a session works
    on one or two; the rest go straight back to the queue. An aborted run
    (quota, network) cools nothing. A record from before touch tracking has
    no `touched` key and keeps the old meaning: every target."""
    root = root or ROOT
    import fleet_run
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
        if data.get("start", 0) < cutoff or fleet_run.aborted(data):
            continue
        targets = {r.lower() for r, _ in data.get("targets", [])}
        if "touched" in data and data.get("status") != "running":
            targets &= {r.lower() for r in data["touched"]}
        out |= targets
    return out
