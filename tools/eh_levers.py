#!/usr/bin/env python3
"""Generate shape_search choices for the mechanical exception-handling levers.

57% of the dump bytes still open (973 KB of 1.70 MB, 2026-09-15) sit in bodies
with a C++ exception frame, and the blocker tags seats write most often are
EH codegen (ehThisSpillTemp, PREFMAP_KEYTEMP_EH_ORDER, seh_frame_not_modeled).
The levers that landed the 6,338 authored EH bodies already in the tree are
documented in docs/shape_levers.md, and four of them are pure text edits a
program can try faster than a seat can rediscover them:

  throw     add `throw()` to one callee declaration at a time -- MSVC 7.1
            drops the unwind state around a call it knows cannot throw
            (shape_levers: the getPreferredMap trio, 377 B each)
  ehsc      toggle the `// cl:` line between /EHsc and /EHsc- (Render_Line,
            1763 B, needed /EHsc; the default emitted extra states)
  stlp      `#define _STLP_NO_EXCEPTIONS 1` before the first include (the
            _M_insert family; retail built STLport with exceptions off)
  nodelete  `void __cdecl operator delete[](void *) throw();` before the
            includes (VectorClass::Resize family: no EH reset before delete[])

Each lever is one shape_search choice, so the search tries their finite
combinations under the usual trial/plateau budget and keeps the best masked
score. The output is a choices.json; nothing here compiles or claims.

  python3 tools/eh_levers.py SOURCE.cpp [--levers throw,ehsc,stlp,nodelete]
      [--max-throw N] > choices.json
  python3 tools/shape_search.py SOURCE.cpp "MANGLED" 0xRVA --size N --choices choices.json
"""
import argparse
import json
import re
import sys
from pathlib import Path

# A free or member function declaration ending in `);` on one line, without
# a body, that does not already carry an exception specification.
DECL_RE = re.compile(r"^[ \t]*(?!#|//|return\b|if\b|for\b|while\b|switch\b|public:|private:|protected:)"
                     r"[A-Za-z_][\w:<>, \t\*&~]*?\b[\w:~]+[ \t]*\([^;{}\n]*\)[ \t]*(?:const[ \t]*)?;[ \t]*$",
                     re.M)
CL_RE = re.compile(r"^// cl:.*$", re.M)
FIRST_INCLUDE_RE = re.compile(r"^[ \t]*#\s*include\b.*$", re.M)


def throw_choices(text, limit):
    out = []
    for match in DECL_RE.finditer(text):
        line = match.group(0)
        if "throw" in line or text.count(line) != 1 or "operator" in line:
            continue
        stripped = line.rstrip()
        if stripped.endswith("const;"):
            after = stripped[:-1] + " throw();"
        else:
            after = stripped[:-1] + " throw();"
        out.append({"before": line, "after": [after], "lever": "throw"})
        if len(out) >= limit:
            break
    return out


def ehsc_choice(text):
    match = CL_RE.search(text)
    if not match:
        return None
    line = match.group(0)
    if "/EHsc-" in line:
        after = line.replace("/EHsc-", "/EHsc")
    elif "/EHsc" in line:
        after = line.replace("/EHsc", "/EHsc-")
    else:
        after = line + " /EHsc"
    return {"before": line, "after": [after], "lever": "ehsc"}


def prefix_choice(text, insert, lever):
    match = FIRST_INCLUDE_RE.search(text)
    if not match or insert in text:
        return None
    line = match.group(0)
    if text.count(line) != 1:
        return None
    return {"before": line, "after": [insert + "\n" + line], "lever": lever}


def choices_for(text, levers=("throw", "ehsc", "stlp", "nodelete"), max_throw=4):
    out = []
    if "throw" in levers:
        out += throw_choices(text, max_throw)
    if "ehsc" in levers:
        c = ehsc_choice(text)
        if c:
            out.append(c)
    if "stlp" in levers:
        c = prefix_choice(text, "#define _STLP_NO_EXCEPTIONS 1", "stlp")
        if c:
            out.append(c)
    if "nodelete" in levers:
        c = prefix_choice(text, "void __cdecl operator delete[](void *) throw();", "nodelete")
        if c:
            out.append(c)
    # shape_search rejects overlapping edits; the prefix levers both anchor on
    # the first include, so fold them into one choice with both alternatives
    prefixes = [c for c in out if c["lever"] in ("stlp", "nodelete")]
    if len(prefixes) == 2:
        merged = {"before": prefixes[0]["before"],
                  "after": prefixes[0]["after"] + prefixes[1]["after"]
                  + [prefixes[1]["after"][0].split("\n")[0] + "\n" + prefixes[0]["after"][0]],
                  "lever": "stlp+nodelete"}
        out = [c for c in out if c["lever"] not in ("stlp", "nodelete")] + [merged]
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source", type=Path)
    ap.add_argument("--levers", default="throw,ehsc,stlp,nodelete")
    ap.add_argument("--max-throw", type=int, default=4,
                    help="callee declarations to try throw() on (each doubles the trial count)")
    a = ap.parse_args()
    text = a.source.read_text(encoding="utf-8-sig")
    choices = choices_for(text, tuple(a.levers.split(",")), a.max_throw)
    for c in choices:
        c.pop("lever", None)
    if not choices:
        sys.exit("eh_levers: no applicable lever found (no bare declarations, cl: line or #include)")
    json.dump(choices, sys.stdout, indent=2)
    print(file=sys.stdout)
    trials = 1
    for c in choices:
        trials *= 1 + len(c["after"])
    print(f"[eh_levers: {len(choices)} choice(s), {trials} combinations; "
          f"shape_search caps at --max-trials]", file=sys.stderr)


if __name__ == "__main__":
    main()
