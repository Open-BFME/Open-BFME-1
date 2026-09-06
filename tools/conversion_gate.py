#!/usr/bin/env python3
"""Refuse changes that run the conversion direction backward: asm -> C++ only.

Usage:  conversion_gate.py OLD NEW
        OLD/NEW are git revisions; NEW may be ":" for the staged index.

Rule A: added lines under Code/ (outside Code/gen_small/) may not contain
        __declspec(naked) or _emit/__emit. Machine byte-dumps belong to
        tools/gen_dump.py in Code/gen_small/; a proven codegen blocker
        (x87, SEH) belongs in Code/masm_dumps/*.asm. Eighteen fleet commits
        titled "convert ... to exact C++" deleted real C++ bodies and added
        __emit thunks — byte-verification passes on those, so this is the
        only gate that can see them.

Rule B: a matched RVA that had at least one clean-C++ source in OLD must
        still have one in NEW. Retracting a wrong claim (row deleted or
        status changed) is legal and must be its own commit; repointing a
        live clean claim at a dump is never legal.

Rule C: Code/gen_asm/ is machine output and stays that way. C1 every added
        line there must match the generator's grammar, so a lift of a NAMED
        function cannot be expressed in the directory at all; C2 every added
        ledger row pointing there is anonymous (?d_<rva>@@YAXXZ, notes
        gen-dump), so a dump can never squat an identity byte-verification
        cannot falsify; C3 a wave commit may not touch any other file under
        Code/, so a deleted C++ body cannot ride inside a diff of 33,000
        unreadable `db` lines. Rule A needs no exemption here and gets none:
        a `db` dump matches neither NAKED_RE nor LIFT_RE, and source_kind
        scores a .asm file as assembly unconditionally, so the offence Rule A
        polices -- inflating the C++ lane with re-encoded binary -- is not
        expressible in this directory.
"""

import csv
import io
import re
import subprocess
import sys
from pathlib import Path

from list_naked_candidates import NAKED_RE
from progress import CPP_SUFFIXES, naked_cpp_rows

LIFT_RE = re.compile(r"\b__?emit\b")
LEDGER = "reverse/functions.csv"


def run(*argv):
    proc = subprocess.run(argv, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")
    if proc.returncode != 0:
        raise SystemExit("conversion_gate: %s failed: %s" % (" ".join(argv), proc.stderr.strip()))
    return proc.stdout


def added_lift_lines(old, new):
    diff_cmd = ["git", "diff", "--unified=0"]
    diff_cmd += ["--cached", old] if new == ":" else [old, new]
    # Authored code only. A ledger row may name a file in the vendored
    # reference/ tree, and those rows sit outside this scan on purpose: nobody
    # authors that tree, nine of its files already contain __emit upstream, and
    # scanning it would fire on the next re-vendor rather than on a regression.
    # Rule B below reads whatever path a row names, so it covers them.
    diff_cmd += ["--", "Code/", ":(exclude)Code/gen_small/"]
    bad, path = {}, None
    for line in run(*diff_cmd).splitlines():
        if line.startswith("+++ b/"):
            path = line[6:]
        elif line.startswith("+") and not line.startswith("+++"):
            if NAKED_RE.search(line) or LIFT_RE.search(line):
                first, count = bad.get(path, (line[1:].strip()[:80], 0))
                bad[path] = (first, count + 1)
    return [(p, "%s  (%d such lines)" % (first, count)) for p, (first, count) in bad.items()]


GEN_ASM = "Code/gen_asm/"
# The generator's whole vocabulary. Anything else in a dump file is a hand edit.
GEN_ASM_LINE_RE = re.compile(
    r"^(?:\.386|\.model flat|_TEXT SEGMENT|_TEXT ENDS|END|;.*|"
    r"public \?d_[0-9a-f]{8}@@YAXXZ|"
    r"\?d_[0-9a-f]{8}@@YAXXZ (?:PROC|ENDP)|"
    r"    db (?:0?[0-9A-F]{2}h)(?:, 0?[0-9A-F]{2}h)*|)$")


def diff_lines(old, new, *paths):
    cmd = ["git", "diff", "--unified=0"]
    cmd += ["--cached", old] if new == ":" else [old, new]
    return run(*cmd, "--", *paths).splitlines()


def gen_asm_offences(old, new):
    """Rule C. Returns a list of human-readable offences, empty when clean."""
    offences = []
    path = None
    dump_rows, other_code_edits = [], set()
    for line in diff_lines(old, new, "Code/", LEDGER):
        if line.startswith("+++ b/"):
            path = line[6:]
            continue
        if path is None or line.startswith("---") or line.startswith("+++"):
            continue
        added = line.startswith("+")
        if not added and not line.startswith("-"):
            continue
        body = line[1:]
        if path.startswith(GEN_ASM):
            if added and not GEN_ASM_LINE_RE.match(body):
                offences.append("C1 %s: not generator output: %s"
                                % (path, body.strip()[:80]))
        elif path == LEDGER:
            if not added:
                continue
            fields = next(csv.reader([body]), [])
            if len(fields) >= 5 and fields[4].startswith(GEN_ASM):
                dump_rows.append(fields)
        elif path.startswith("Code/"):
            other_code_edits.add(path)

    for fields in dump_rows:
        name, rva, notes = fields[0], fields[2], fields[6] if len(fields) > 6 else ""
        expected = "?d_%08x@@YAXXZ" % int(rva, 16)
        if name != expected:
            offences.append("C2 %s claims identity %s; a dump proves bytes and "
                            "an extent, never what the function is (expected %s)"
                            % (rva, name, expected))
        if not notes.lstrip().startswith("gen-dump"):
            offences.append("C2 %s: a Code/gen_asm/ row must carry gen-dump "
                            "notes, or is_scaffold_row cannot see it" % rva)
    if dump_rows and other_code_edits:
        offences.append("C3 wave commit also edits %s — dumps-and-ledger only, "
                        "so a deleted C++ body cannot ride inside an unreadable "
                        "diff" % ", ".join(sorted(other_code_edits)))
    return offences


class _MissingSource(Exception):
    """A ledger row's source is unreadable at the revision being judged.

    Raised instead of exiting: HEAD itself can carry such rows (a commit that
    added rows without adding the file), and crashing on them blocks the very
    repair commit that retracts them. Callers treat a missing source as
    proving nothing -- neither clean nor naked -- and check_csv (which runs
    beside this gate in the hook) still rejects any NEW row in that state.
    """


def show(rev, path, allow_missing=False):
    spec = (":%s" if rev == ":" else rev + ":%s") % path
    proc = subprocess.run(["git", "show", spec], capture_output=True, text=True)
    if proc.returncode != 0:
        if allow_missing:
            raise _MissingSource(spec)
        raise SystemExit("conversion_gate: cannot read %s — a matched row's source "
                         "must exist at its revision (ledger corruption?)" % spec)
    return proc.stdout


def matched_by_rva(rev):
    rows = {}
    for row in csv.DictReader(io.StringIO(show(rev, LEDGER))):
        if row.get("status") == "matched":
            rows.setdefault(row["target_rva"], []).append(row)
    return rows


def ledger_blob(rev):
    spec = (":%s" if rev == ":" else rev + ":%s") % LEDGER
    return run("git", "rev-parse", spec).strip()


def naked_keys(rev, all_rows, sources):
    """(Row keys naked at `rev`, sources unreadable at `rev`).

    Judged by progress.py's per-row machinery. Feeds naked_cpp_rows every
    matched row of each affected source, not just the changed rows: its
    sole-row-sole-body proof is only valid on whole files. A source missing
    at `rev` proves nothing either way, so its rows are withheld from the
    proof and reported beside it for clean_sources to exclude as well.
    """
    matched = {(r["name"], r["target_rva"]): (int(r["target_size"]), r["source"])
               for rows in all_rows.values() for r in rows if r["source"] in sources}
    texts, missing = {}, set()
    for s in sources:
        if Path(s).suffix.lower() not in CPP_SUFFIXES:
            continue
        try:
            texts[s] = show(rev, s, allow_missing=True)
        except _MissingSource:
            missing.add(s)
    matched = {k: v for k, v in matched.items() if v[1] not in missing}
    return naked_cpp_rows(matched, texts), missing


def clean_coverage_lost(old, new):
    if ledger_blob(old) == ledger_blob(new):
        return []
    old_rows, new_rows = matched_by_rva(old), matched_by_rva(new)
    changed = [rva for rva, rows in new_rows.items()
               if rva in old_rows and
               {r["source"] for r in old_rows[rva]} != {r["source"] for r in rows}]
    if not changed:
        return []

    def clean_sources(rva, rows_by_rva, naked, missing):
        return sorted({r["source"] for r in rows_by_rva[rva]
                       if not r["source"].endswith(".asm")
                       and r["source"] not in missing
                       and (r["name"], r["target_rva"]) not in naked})

    old_naked, old_missing = naked_keys(old, old_rows, {r["source"] for rva in changed for r in old_rows[rva]})
    new_naked, new_missing = naked_keys(new, new_rows, {r["source"] for rva in changed for r in new_rows[rva]})
    lost = []
    for rva in changed:
        before = clean_sources(rva, old_rows, old_naked, old_missing)
        if before and not clean_sources(rva, new_rows, new_naked, new_missing):
            lost.append((rva, old_rows[rva][0]["name"], ", ".join(before),
                         ", ".join(sorted({r["source"] for r in new_rows[rva]}))))
    return lost


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__.strip().splitlines()[2].strip())
    old, new = sys.argv[1], sys.argv[2]
    failed = False
    for path, line in added_lift_lines(old, new):
        failed = True
        print("conversion gate: %s adds a naked/__emit body outside Code/gen_small/:\n"
              "    %s" % (path, line), file=sys.stderr)
    if failed:
        print("A lift is not a conversion: it deletes the C++ this project exists to\n"
              "produce and moves progress.py C++ exact by +0. Convert to real C++, or\n"
              "leave the .asm dump alone (codegen blockers: Code/masm_dumps/*.asm).",
              file=sys.stderr)
    for offence in gen_asm_offences(old, new):
        failed = True
        print("conversion gate: " + offence, file=sys.stderr)
    for rva, name, old_src, new_src in clean_coverage_lost(old, new):
        failed = True
        print("conversion gate: %s (%s) was clean C++ at %s, repointed to %s.\n"
              "C++ exact never goes backward: retract the row in its own commit if the\n"
              "claim is wrong; never swap a dump under a live claim."
              % (rva, name, old_src, new_src), file=sys.stderr)
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
