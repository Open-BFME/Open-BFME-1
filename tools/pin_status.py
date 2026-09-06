#!/usr/bin/env python3
"""Say which definitions in a .cpp are backed by a byte-verified ledger row.

Most sources under Code/ mix bodies this project verified against retail with
bodies copied verbatim from the ZH reference, which are not verified and are not
necessarily even BFME's. Nothing in the file distinguishes them, and the harm is
live: GameLogic.cpp defines `setGamePaused( Bool, Bool )` -- ZH's two-argument
signature -- while PopupSaveLoad.cpp's matched row records that BFME's takes
three, and a shipped mod README names that symbol.

Per definition this prints one of:

  matched        a matched row claims this symbol AND names this source
  row-elsewhere  a matched row claims it, but from another source file
  unmatched      a row exists whose status is not `matched`
  no-row         no row claims it -- the body is unverified
  ambiguous      overloads this file cannot be told apart by mangled name

Definitions the shared parser cannot read are counted, never guessed at: see
`unparsed` in the summary.
"""
import argparse
import collections
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import ledger_io
from find_declared_unmatched import iter_definitions, mangle_method

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
MARKERS = ("present-unmatched", "absent-from-retail")

# A definition at brace depth 0 that is not `Class::method(`. The shared parser
# reads member definitions only, so these are counted and reported as `unparsed`
# rather than classified: a free function's decorated name depends on linkage and
# on any enclosing anonymous namespace, and guessing it wrong would print
# `matched` over an unverified body -- the exact defect this tool exists to find.
NONMEMBER = re.compile(r"^(?!#)[A-Za-z_][\w:<>,&*\s\[\]]*?\b\w+\s*\(")
MEMBER = re.compile(r"^[\w:&*~\s]*?(?:\w+::)*\w+::")


class Definition:
    def __init__(self, line, cls, method, annotation):
        self.line = line
        self.display = f"{cls}::{method}"
        self.needle = mangle_method(cls, method)[:-1]
        # A bare mangled name, or one followed by a present-unmatched /
        # absent-from-retail marker, is the definition's own decorated name and
        # outranks the needle -- it distinguishes overloads the needle merges.
        self.annotation = None
        self.marker = None
        if annotation:
            parts = annotation.split()
            self.annotation = parts[0]
            if len(parts) > 1 and parts[1] in MARKERS:
                self.marker = parts[1]
        self.state = None
        self.symbol = None


def definitions(text):
    return [Definition(*d) for d in iter_definitions(text)]


def count_nonmember(text):
    """Definition-shaped lines at depth 0 that `iter_definitions` does not read."""
    lines = text.replace("\r\n", "\n").replace("\r", "\n").split("\n")
    depth = total = 0
    for index, line in enumerate(lines):
        outer = depth == 0
        depth += line.count("{") - line.count("}")
        stripped = line.strip()
        if not outer or MEMBER.match(line) or not NONMEMBER.match(stripped):
            continue
        if stripped.endswith((";", ",")):
            continue
        follower = next((l.strip() for l in lines[index + 1:index + 4]
                         if l.strip() and not l.strip().startswith("//")), "")
        if stripped.endswith("{") or follower.startswith("{"):
            total += 1
    return total


def screen(defs):
    """(exact names, ^-anchored prefixes, substrings) that could name these defs."""
    exact, prefixes, subs = set(), set(), set()
    for definition in defs:
        if definition.annotation:
            exact.add(definition.annotation)
            if definition.annotation.endswith("@@"):
                prefixes.add(definition.annotation[:-2] + "@")
            continue
        # Constructors and destructors share `??0Class@` with every overload, so
        # they anchor; an ordinary method's needle can sit inside a longer name.
        (prefixes if definition.needle[:3] in ("??0", "??1") else subs).add(
            definition.needle)
    return exact, prefixes, subs


def alternation(needles, anchor):
    if not needles:
        return None
    body = "|".join(re.escape(n) for n in sorted(needles, key=len, reverse=True))
    return re.compile(f"{anchor}(?:{body})")


def read_rows(exact, prefixes, subs, path=FUNCTIONS_CSV):
    """{name: [(source, status)]} for ledger rows any needle could name.

    Streams the ledger a record at a time -- AGENTS.md forbids loading it
    wholesale, and it is 23 MB. Terminators are mixed (\\r\\r\\n, \\r\\n, \\n),
    so each record is parsed through ledger_io rather than split by hand.
    """
    prefix_re = alternation(prefixes, "^")
    sub_re = alternation(subs, "")
    rows = {}
    with open(path, "rb") as handle:
        first = next(handle, None)
        if first is None:
            raise SystemExit(f"{path}: empty ledger")
        header = ledger_io.fields(ledger_io.TERM.sub(b"", first))
        if header[:6] != ["name", "export_rva", "target_rva", "target_size",
                          "source", "status"]:
            raise SystemExit(f"{path}: unexpected header {header}")
        for number, raw in enumerate(handle, 2):
            record = ledger_io.fields(ledger_io.TERM.sub(b"", raw))
            if len(record) != len(header):
                raise SystemExit(f"{path} line {number}: expected "
                                 f"{len(header)} fields, read {len(record)}")
            name = record[0]
            if not (name in exact
                    or (prefix_re and prefix_re.match(name))
                    or (sub_re and sub_re.search(name))):
                continue
            rows.setdefault(name, []).append((record[4], record[5]))
    return rows


def candidates(definition, rows):
    """The ledger names that could be this definition, most precise rule first."""
    if definition.annotation:
        if definition.annotation in rows:
            return [definition.annotation]
        if not definition.annotation.endswith("@@"):
            return []
        # An abbreviated annotation -- `?getAnimationScrubScalar@Drawable@@` with
        # the argument types dropped -- names a real symbol by prefix.
        key = definition.annotation[:-2] + "@"
        return [n for n in rows if n.startswith(key)]
    if definition.needle[:3] in ("??0", "??1"):
        return [n for n in rows if n.startswith(definition.needle)]
    return [n for n in rows if definition.needle in n]


STATES = ("matched", "row-elsewhere", "unmatched", "no-row", "ambiguous")


def classify(defs, rows, source):
    # Overloads share one needle, and 500 of the tree's 13,114 un-annotated
    # definitions sit in such a group. Reporting a sibling's matched row as this
    # body's verification is the defect this tool exists to find, so a group only
    # resolves when it cannot be wrong: every row the needle finds is matched
    # from this source, and there are at least as many rows as bodies.
    siblings = collections.Counter(d.needle for d in defs if not d.annotation)
    for definition in defs:
        names = candidates(definition, rows)
        claims = [(n, src, status) for n in names for src, status in rows[n]]
        mine = [c for c in claims if c[2] == "matched" and c[1] == source]
        overloaded = 0 if definition.annotation else siblings[definition.needle]
        if not claims:
            definition.state = "no-row"
        elif overloaded > 1 and not (len(mine) == len(claims)
                                     and len(names) >= overloaded):
            definition.state = "ambiguous"
        elif mine:
            definition.state = "matched"
        elif any(claim[2] == "matched" for claim in claims):
            definition.state = "row-elsewhere"
        else:
            definition.state = "unmatched"
        if overloaded > 1:
            # Naming one overload here would claim more than the needle knows.
            definition.symbol = (f"{definition.needle}@ "
                                 f"({len(names)} rows, {overloaded} bodies)")
        elif definition.state == "no-row":
            definition.symbol = definition.annotation or definition.needle + "@"
        else:
            definition.symbol = (mine or claims)[0][0]
    return defs


def report(path, defs, unparsed, show_lines, out):
    counts = {state: 0 for state in STATES}
    for definition in defs:
        counts[definition.state] += 1
    print(path, file=out)
    if show_lines:
        for definition in defs:
            marker = f"  [{definition.marker}]" if definition.marker else ""
            print(f"  {definition.line:>6}  {definition.state:<13} "
                  f"{definition.display}{marker}  {definition.symbol or ''}".rstrip(),
                  file=out)
    detail = ", ".join(f"{state} {counts[state]}" for state in counts
                       if state != "matched")
    print(f"  {counts['matched']} of {len(defs)} definitions carry a verified "
          f"row ({detail}); unparsed: {unparsed} definitions", file=out)
    return counts


def run(paths, show_lines=True, out=sys.stdout, ledger=FUNCTIONS_CSV, root=ROOT):
    root = Path(root).resolve()
    texts = {}
    for path in paths:
        resolved = Path(path)
        resolved = (resolved if resolved.is_absolute() else root / resolved).resolve()
        if not resolved.is_relative_to(root):
            # The ledger's `source` column is repo-relative, so a path outside
            # the tree has no row it could ever be compared against.
            raise SystemExit(f"{path}: outside {root}")
        texts[path] = (resolved.read_text(encoding="utf-8"),
                       resolved.relative_to(root).as_posix())
    parsed = {path: definitions(text) for path, (text, _rel) in texts.items()}
    rows = read_rows(*screen([d for ds in parsed.values() for d in ds]),
                     path=ledger)
    totals = {}
    for path, (text, rel) in texts.items():
        defs = classify(parsed[path], rows, rel)
        totals[path] = report(rel, defs, count_nonmember(text), show_lines, out)
    return totals


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("paths", nargs="+", help=".cpp sources to report on")
    parser.add_argument("--summary", action="store_true",
                        help="print only the per-file summary line")
    args = parser.parse_args(argv)
    run(args.paths, show_lines=not args.summary)


if __name__ == "__main__":
    main()
