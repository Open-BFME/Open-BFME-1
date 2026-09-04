"""Terminator-preserving ledger rewrite. The ONLY safe way to drop/edit rows.

reverse/functions.csv is not uniformly CRLF: at fa05aaa4b it holds 93,713 rows
ending \r\r\n, 11,140 ending \r\n and 309 ending with a bare \n. Every rewrite
that has split on "\r\n" or used str.splitlines() has silently dropped or
duplicated rows (twice this session):

    text.split("\r\n")   -> 104,854 pieces  (loses 306 rows)
    text.splitlines()    -> 198,875 pieces  (invents 93,713 rows)
    csv.reader(StringIO) -> 105,162 records (correct)

So: parse records with csv.reader for *identity*, but rewrite by operating on
the raw bytes record-by-record, keeping each record's own terminator.
"""
import collections
import csv
import io
import re

TERM = re.compile(rb"\r*\n")


def split_records(raw):
    """[(payload_bytes, terminator_bytes)] over the whole file, order preserved."""
    out, pos = [], 0
    for m in TERM.finditer(raw):
        out.append((raw[pos:m.start()], m.group(0)))
        pos = m.end()
    if pos != len(raw):
        raise ValueError("ledger does not end with a newline (truncated last row?)")
    return out


def fields(payload):
    return next(csv.reader(io.StringIO(payload.decode("utf-8"))), [])


def terminator_census(raw):
    """{terminator_bytes: [1-based line numbers]}, in file order.

    Matches the terminators only rather than reusing split_records: this runs in
    the commit hook over a 4 MB symbols.csv, and slicing out 70,000 payloads it
    never reads took the walk from 109ms to 145ms.
    """
    census = collections.defaultdict(list)
    end = 0
    for number, match in enumerate(TERM.finditer(raw), 1):
        census[match.group(0)].append(number)
        end = match.end()
    if end != len(raw):
        raise ValueError("ledger does not end with a newline (truncated last row?)")
    return census


def uniform_terminator(raw, label):
    """The one line ending `raw` uses; a file mixing two is not appendable.

    reverse/symbols.csv is `merge=union`. A pin differing from its twin only by a
    `\\r` is a DISTINCT line to the merge driver, so the same pin lands twice and
    every later rebase compounds it -- that is how 4,172 pins became 8,784.
    Matching the file keeps each batch a pure append.

    functions.csv legitimately mixes all three terminators, so this is asked of
    symbols.csv only; there a duplicate pin is legal and nothing downstream
    catches it, while a duplicated function row trips check_csv's name rule.
    """
    census = terminator_census(raw)
    if len(census) > 1:
        spelling = {b"\n": "LF", b"\r\n": "CRLF", b"\r\r\n": "CRCRLF"}
        detail = "; ".join(
            f"{spelling.get(term, repr(term))} on {len(lines)} line(s) "
            f"(first {lines[0]})" for term, lines in sorted(census.items()))
        raise SystemExit(f"{label} mixes line terminators -- {detail}. Union-merging it "
                         "duplicates every pin whose terminator differs. Repair it with "
                         "python3 tools/dedup_csv.py before appending.")
    return next(iter(census), b"\r\n")


def rewrite(raw, keep):
    """keep(fields) -> True to retain the record. Terminators are preserved."""
    kept, dropped = [], 0
    for payload, term in split_records(raw):
        if keep(fields(payload)):
            kept.append(payload + term)
        else:
            dropped += 1
    return b"".join(kept), dropped


def atomic_write_bytes(path, data, retries=240, delay=0.25):
    """Replace `path` with `data` so no reader ever sees a torn file.

    A plain write_bytes truncates first and fills 30 MB afterwards; a reader
    (check_csv, git, another lane) or a kill in that window sees a short file
    -- that is how symbols.csv lost 14,858 rows on 2026-09-02. Write beside
    the target, fsync, then rename over it. On Windows the rename fails with
    PermissionError while a reader still holds the old file open, so retry
    for up to a minute: with 40 fleet seats each re-reading the 30 MB ledger,
    ten seconds of retries was not enough on 2026-09-04.
    """
    import os
    import time
    from pathlib import Path as _P
    path = _P(path)
    tmp = path.with_name(path.name + ".tmp-%d" % os.getpid())
    with open(tmp, "wb") as f:
        f.write(data)
        f.flush()
        os.fsync(f.fileno())
    last = None
    for _ in range(retries):
        try:
            os.replace(tmp, path)
            return
        except PermissionError as e:
            last = e
            time.sleep(delay)
    try:
        tmp.unlink()
    except OSError:
        pass
    raise last

