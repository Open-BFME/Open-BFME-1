#!/usr/bin/env python3
"""Refuse changes that run the conversion direction backward: asm -> C++ only.

Usage:  conversion_gate.py OLD NEW
        OLD/NEW are git revisions; NEW may be ":" for the staged index.

Rule A: added lines under game/ (outside game/gen_small/) may not contain
        __declspec(naked) or _emit/__emit. game/gen_small/ is exempt only
        because it is the frozen output of the retired generators, never
        because a new dump is welcome there; a proven codegen blocker
        (x87, SEH) belongs in game/masm_dumps/*.asm. Eighteen fleet commits
        titled "convert ... to exact C++" deleted real C++ bodies and added
        __emit thunks — byte-verification passes on those, so this is the
        only gate that can see them.

Rule B: a matched RVA that had at least one clean-C++ source in OLD must
        still have one in NEW. Retracting a wrong claim (row deleted or
        status changed) is legal and must be its own commit; repointing a
        live clean claim at a dump is never legal.

Rule C: game/gen_asm/ is machine output and stays that way. C1 every added
        line there must match the grammar the retired generator emitted, so a
        lift of a NAMED function cannot be expressed in the directory at all,
        unless the whole new file is exactly what tools/dump_apply.py writes
        from the old one (symbolic relocations, re-derived here, not trusted); C2 every added
        ledger row pointing there is anonymous (?d_<rva>@@YAXXZ, notes
        gen-dump), so a dump can never squat an identity byte-verification
        cannot falsify; C3 a wave commit may not touch any other file under
        game/, so a deleted C++ body cannot ride inside a diff of 33,000
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
import layout_history

LIFT_RE = re.compile(r"\b__?emit\b")
# A comment is prose, not a lift. The gate fired on a merge whose only `__emit`
# was in a line explaining why a dump was being LEFT ALONE, which reads as
# "you added a naked body" and sends the author hunting one that is not there.
# Only whole `//` tails and complete `/* */` pairs are removed: a line inside an
# unterminated block comment keeps its text and is still scanned, so the scan
# fails closed rather than being talked out of a real lift by an open comment.
COMMENT_RE = re.compile(r"/\*.*?\*/|//.*$")


def is_lift_line(line):
    """True when `line` ADDS a naked body or an __emit, ignoring its comments.

    The scanner must go through here rather than matching the raw line, or a
    comment mentioning __emit is reported as a lift.
    """
    scanned = COMMENT_RE.sub(" ", line)
    return bool(NAKED_RE.search(scanned) or LIFT_RE.search(scanned))
LEDGER = "targets/game/reverse/functions.csv"


def run(*argv):
    proc = subprocess.run(argv, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")
    if proc.returncode != 0:
        raise SystemExit("conversion_gate: %s failed: %s" % (" ".join(argv), proc.stderr.strip()))
    return proc.stdout


def added_lift_lines(old, new, lines=None):
    if lines is None:
        lines = diff_lines(old, new, "Code/", "game/", ":(exclude)game/gen_small/")
    # Authored code only. A ledger row may name a file in the vendored
    # inputs/reference/ tree, and those rows sit outside this scan on purpose: nobody
    # authors that tree, nine of its files already contain __emit upstream, and
    # scanning it would fire on the next re-vendor rather than on a regression.
    # Rule B below reads whatever path a row names, so it covers them.
    bad, path = {}, None
    for line in lines:
        if line.startswith("+++ b/"):
            path = line[6:]
        elif line.startswith("+") and not line.startswith("+++"):
            if path is None or not path.startswith("game/") \
                    or path.startswith("game/gen_small/"):
                continue
            if is_lift_line(line):
                first, count = bad.get(path, (line[1:].strip()[:80], 0))
                bad[path] = (first, count + 1)
    return [(p, "%s  (%d such lines)" % (first, count)) for p, (first, count) in bad.items()]


def added_asm_only_bodies(old, new, lines=None):
    """Rule A2: a function whose whole body is mnemonic __asm is a lift too.

    It needs no __emit, so Rule A cannot see it, and progress.py scored it as
    C++ until it learned asm_only_bodies. Compare per file, by signature, so an
    edit elsewhere in a file that already holds one is not charged for it."""
    from progress import asm_only_bodies
    if lines is None:
        lines = collect_diff_lines(old, new)
    # Reuse the one game/ diff Rules A and C read: only files with added lines.
    paths = sorted({line[6:] for line in lines if line.startswith("+++ b/")
                    and line[6:].startswith("game/") and line[6:].endswith(tuple(CPP_SUFFIXES))
                    and not line[6:].startswith("game/gen_small/")})
    bad = []
    for path in paths:
        def body_signatures(rev):
            proc = subprocess.run(["git", "show", f"{rev}:{path}"], capture_output=True)
            if proc.returncode != 0:
                return set()
            text = proc.stdout.decode("utf-8", errors="replace")
            return {b["signature"] for b in asm_only_bodies(text)} if "_asm" in text else set()
        added = body_signatures("" if new == ":" else new) - body_signatures(old)
        bad += [(path, signature) for signature in sorted(added)]
    return bad


GEN_ASM = "game/gen_asm/"
# The generator's whole vocabulary. Anything else in a dump file is a hand edit.
GEN_ASM_LINE_RE = re.compile(
    r"^(?:\.386|\.model flat|_TEXT SEGMENT|_TEXT ENDS|END|;.*|"
    r"public \?d_[0-9a-f]{8}@@YAXXZ|"
    r"\?d_[0-9a-f]{8}@@YAXXZ (?:PROC|ENDP)|"
    r"    db (?:0?[0-9A-F]{2}h)(?:, 0?[0-9A-F]{2}h)*|)$")


def diff_lines(old, new, *paths):
    cmd = ["git", "diff", "--unified=0", "--find-renames=1%"]
    cmd += ["--cached", old] if new == ":" else [old, new]
    return run(*cmd, "--", *paths).splitlines()


def collect_diff_lines(old, new):
    """Collect the shared game/ledger diff used by Rules A and C."""
    return diff_lines(old, new, "Code/", "game/", layout_history.OLD_LEDGER, LEDGER)


def gen_asm_offences(old, new, lines=None):
    """Rule C. Returns a list of human-readable offences, empty when clean."""
    offences = []
    path = None
    dump_rows, other_code_edits, c1 = [], set(), {}
    old_ledger = layout_history.path_at(old, LEDGER, layout_history.OLD_LEDGER,
                                         root=Path.cwd())
    existing = {(r["name"], r["target_rva"], r["target_size"],
                 layout_history.canonical_source(r["source"]), r["status"])
                for r in csv.DictReader(io.StringIO(show(old, old_ledger)))}
    if lines is None:
        lines = diff_lines(old, new, "Code/", "game/", layout_history.OLD_LEDGER, LEDGER)
    for line in lines:
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
                c1.setdefault(path, []).append("C1 %s: not generator output: %s"
                                               % (path, body.strip()[:80]))
        elif path == LEDGER:
            if not added:
                continue
            fields = next(csv.reader([body]), [])
            if len(fields) >= 5 and fields[4].startswith(GEN_ASM):
                if len(fields) >= 6 and (fields[0], fields[2], fields[3],
                                          fields[4], fields[5]) in existing:
                    continue
                dump_rows.append(fields)
        elif path.startswith("game/"):
            other_code_edits.add(path)

    for path, found in c1.items():
        if not tool_reproduced(old, new, path):
            offences.extend(found)
    for fields in dump_rows:
        name, rva, notes = fields[0], fields[2], fields[6] if len(fields) > 6 else ""
        expected = "?d_%08x@@YAXXZ" % int(rva, 16)
        if name != expected:
            offences.append("C2 %s claims identity %s; a dump proves bytes and "
                            "an extent, never what the function is (expected %s)"
                            % (rva, name, expected))
        if not notes.lstrip().startswith("gen-dump"):
            offences.append("C2 %s: a game/gen_asm/ row must carry gen-dump "
                            "notes, or is_scaffold_row cannot see it" % rva)
    if dump_rows and other_code_edits:
        offences.append("C3 wave commit also edits %s — dumps-and-ledger only, "
                        "so a deleted C++ body cannot ride inside an unreadable "
                        "diff" % ", ".join(sorted(other_code_edits)))
    return offences


_DUMP_APPLY = []


def tool_reproduced(old, new, path):
    """C1's one exception: the new blob is byte-for-byte what tools/dump_apply.py
    writes when re-run on the OLD blob of the same path (reproduce(), which
    reads only that text, the ledger and the retail tables). Anything else --
    a hand edit, tool output from another base, one changed byte -- is refused."""
    base, staged = blob(old, path), blob(new, path)
    if base is None or staged is None:
        return False
    try:
        import dump_apply
        if not _DUMP_APPLY:
            _DUMP_APPLY.append(dump_apply.Context())
        text, _ = dump_apply.reproduce(path, base.decode("utf-8"), _DUMP_APPLY[0])
    except Exception as exc:  # any failure to reproduce is a refusal
        print("conversion gate: %s: dump_apply could not reproduce it (%s)" % (path, exc), file=sys.stderr)
        return False
    if text is None:
        return False
    if b"\r\n" in base:
        text = text.replace("\n", "\r\n")
    return text.encode("utf-8") == staged


def blob(rev, path):
    """Raw bytes of path at rev (":" = the index), or None."""
    spec = (":%s" if rev == ":" else rev + ":%s") % path
    proc = subprocess.run(["git", "show", spec], capture_output=True)
    return proc.stdout if proc.returncode == 0 else None


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


def ledger_text(rev):
    path = layout_history.path_at("" if rev == ":" else rev, LEDGER,
                                  layout_history.OLD_LEDGER, root=Path.cwd())
    return show(rev, path)


def matched_by_rva(text):
    rows = {}
    for row in csv.DictReader(io.StringIO(text)):
        if row.get("status") == "matched":
            row["source"] = layout_history.canonical_source(row["source"])
            rows.setdefault(row["target_rva"], []).append(row)
    return rows


def _rva_field(line):
    if '"' in line:
        fields = next(csv.reader([line]), [])
    else:
        fields = line.split(",", 3)
    return fields[2] if len(fields) > 2 else None


def scoped_rows(old_text, new_text):
    """matched_by_rva for both revisions, restricted to what can matter.

    An address's source set can only differ between revisions if one of its
    ledger lines differs, so only those addresses are parsed in full, plus
    (lazily, via the returned callable) every row of the sources they involve
    for the naked-body proof. Parsing both whole 170k-row ledgers was ~9 s of
    every push. Line-scoping is exact while each record is one line; a line
    with an odd number of quotes (a record that may span lines) keeps the full
    parse. Returns (old_rows, new_rows, rows_for_sources) or None to fall back.
    """
    lines = []
    for text in (old_text, new_text):
        split = re.findall(r"[^\n]*\n|[^\n]+$", text)
        if any(line.count('"') % 2 for line in split):
            return None
        lines.append(split)
    old_lines, new_lines = lines
    if not old_lines or not new_lines or old_lines[0] != new_lines[0]:
        return None
    header = old_lines[0]
    changed_lines = set(old_lines[1:]) ^ set(new_lines[1:])
    candidates = {_rva_field(line) for line in changed_lines}

    def parse(selected):
        return matched_by_rva(header + "".join(selected))

    old_rows = parse([l for l in old_lines[1:] if _rva_field(l) in candidates])
    new_rows = parse([l for l in new_lines[1:] if _rva_field(l) in candidates])

    def rows_for_sources(which, sources):
        names = {Path(s).name for s in sources}
        body = old_lines if which == "old" else new_lines
        return parse([l for l in body[1:] if any(n in l for n in names)])

    return old_rows, new_rows, rows_for_sources


def ledger_blob(rev):
    path = layout_history.path_at("" if rev == ":" else rev, LEDGER,
                                  layout_history.OLD_LEDGER, root=Path.cwd())
    spec = (":%s" if rev == ":" else rev + ":%s") % path
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
    old_text, new_text = ledger_text(old), ledger_text(new)
    scoped = scoped_rows(old_text, new_text)
    if scoped is None:
        old_rows, new_rows = matched_by_rva(old_text), matched_by_rva(new_text)
        rows_for_sources = lambda which, _sources: old_rows if which == "old" else new_rows
    else:
        old_rows, new_rows, rows_for_sources = scoped
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

    old_sources = {r["source"] for rva in changed for r in old_rows[rva]}
    new_sources = {r["source"] for rva in changed for r in new_rows[rva]}
    old_naked, old_missing = naked_keys(old, rows_for_sources("old", old_sources), old_sources)
    new_naked, new_missing = naked_keys(new, rows_for_sources("new", new_sources), new_sources)
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
    # Rule A and Rule C consume the same game/ledger diff. Keep the complete
    # diff in memory once, then let each rule apply its own path filter. Rule B
    # independently uses ledger_blob so its authoritative ledger-state check
    # remains valid for binary, rename, or otherwise unusual Git diffs.
    collected = collect_diff_lines(old, new)
    failed = False
    for path, line in added_lift_lines(old, new, collected):
        failed = True
        print("conversion gate: %s adds a naked/__emit body outside game/gen_small/:\n"
              "    %s" % (path, line), file=sys.stderr)
    if failed:
        print("A lift is not a conversion: it deletes the C++ this project exists to\n"
              "produce and moves progress.py C++ exact by +0. Convert to real C++, or\n"
              "leave the .asm dump alone (codegen blockers: game/masm_dumps/*.asm).",
              file=sys.stderr)
    for path, signature in added_asm_only_bodies(old, new, collected):
        failed = True
        print("conversion gate: %s adds a function whose whole body is __asm:\n"
              "    %s\nMnemonic inline asm is a lift like __emit; convert it to C++, or put a "
              "proven codegen blocker in game/masm_dumps/*.asm." % (path, signature),
              file=sys.stderr)
    for offence in gen_asm_offences(old, new, collected):
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
