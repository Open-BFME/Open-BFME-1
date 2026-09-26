#!/usr/bin/env python3
"""Which of a type's competing headers is the real one, decided mechanically.

WHY. `adopt_header.py` can only touch a type when exactly ONE header defines it,
so 62 types are frozen out for having two or more. Asked to rank them by taste, a
reader reaches for includer counts and directory convention -- and those are not
evidence. `INI` is the proof: `Include/Common/INI/INI.h` has ZERO includers and
`fx_particle_system.h` has seven, so both signals point the wrong way. Reading the
two definitions settles it in one second:

    fx_particle_system.h   class INI { initFromINI; parseFXList; };
    Include/Common/INI/INI.h   class INI { load; loadFile; loadDirectory; ... }

The seven-includer one is a TU-local shim that happens to live in a .h. It is not
a rival definition, it is the same problem one directory up.

THE RULE. Candidates that agree on data layout are the same type, and the one
declaring the widest interface is the real one; a candidate declaring a strict
subset is a shim. Candidates that disagree STRUCTURALLY -- a base class one has
and another does not -- are different types wearing one name, and no amount of
counting resolves that. Those are reported UNSETTLED and left alone.

WHAT IT WAS WORTH, MEASURED. Not much, and that is the useful part. Of the 62
types "defined by two or more headers", 23 are vendored upstream (libjpeg ships
`struct jpeg_d_coef_controller { long dummy; }` in jpeglib.h as an opaque handle
and the real fields in jpegint.h -- eight types were that one idiom). Of the 39
that are ours, 18 settle mechanically, 8 are one missing method away, and 13 are
genuinely different types wearing one name -- ten of those because one candidate
gives the type a base class another does not, five from `game_engine_subsystems.h`
alone. Then the payoff: those 39 types have THIRTEEN TU-local copies between
them. AsciiString alone has 418. The types are ambiguous BECAUSE they are rare,
so resolving the ambiguity unlocks nothing -- `adopt_header.py` was never being
held back by it. Run this to settle a question, not to find work.

This decides nothing about bytes. It says which header is worth ASKING the gate
about; `adopt_header.py` still proves every file one at a time.

    python3 tools/canonical_header.py             # every multi-header type
    python3 tools/canonical_header.py --type INI
"""
import argparse
import collections
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# The class head, captured so the base clause is visible: `class X : public Y {`.
HEAD = re.compile(r"^[ \t]*(?:class|struct)[ \t]+(\w+)\b([^{;]*)\{", re.M)
MEMBER = re.compile(r"^\s*[A-Za-z_][\w:<>*&\s]*?\b(m_\w+|[a-z]\w*)\s*(\[[^\]]*\])?\s*;", re.M)
METHOD = re.compile(r"^\s*[^/\n]*?\b(\w+)\s*\([^;{]*\)\s*(?:const)?\s*[;{]", re.M)
# Upstream libraries vendored in whole. Their headers are already right, and
# their "disagreements" are upstream idiom -- libjpeg publishes
# `struct jpeg_d_coef_controller { long dummy; }` in jpeglib.h as an opaque
# handle and the real fields in jpegint.h. Eight of the 62 were that one trick.
# `return (x);` inside an inline body looks exactly like a declaration of a
# method named `return`. A tool that reports a C++ keyword as a missing method
# cannot be trusted on the methods it does report.
KEYWORDS = frozenset("return if while for switch sizeof catch else do new delete "
                     "throw typedef union struct class enum operator".split())
VENDORED = ("/JPEG/", "/LibPNG/", "/Lua/", "/STLport/", "/D3DX9/", "/Compression/")


def body(text, name):
    """The brace-balanced body of `name`'s definition, and its base clause."""
    for head in HEAD.finditer(text):
        if head.group(1) != name:
            continue
        depth, i = 0, head.end() - 1
        while i < len(text):
            depth += (text[i] == "{") - (text[i] == "}")
            if depth == 0:
                return text[head.end():i], head.group(2).strip()
            i += 1
        raise SystemExit(f"unbalanced braces in {name}")
    return None, None


def shape(path, name):
    """(data members, method names, base clause) as the header declares them."""
    inner, base = body(path.read_text(encoding="utf-8", errors="replace"), name)
    if inner is None:
        return None
    # Nested classes carry their own members; strip them so a type's layout is
    # what IT declares, not what it contains.
    flat, depth = [], 0
    for line in inner.splitlines():
        if depth == 0:
            flat.append(line)
        depth += line.count("{") - line.count("}")
    flat = "\n".join(flat)
    members = [(m, bool(a)) for m, a in MEMBER.findall(flat)]
    methods = set(METHOD.findall(flat)) - KEYWORDS - {name, f"~{name}"}
    return members, methods, base


def verdict(name, paths):
    shapes = {p: shape(p, name) for p in paths}
    shapes = {p: s for p, s in shapes.items() if s}
    if len(shapes) < 2:
        return None
    bases = {s[2] for s in shapes.values()}
    if len(bases) > 1:
        # A base class one candidate has and another does not is not a spelling
        # difference. These are different types and counting cannot merge them.
        return "UNSETTLED", None, f"base clause disagrees: {sorted(bases)!r}"
    # A candidate declaring NO data members makes no claim about layout, so it
    # cannot disagree with one that does -- same reason an array member is a span
    # and not a field. Only candidates that name fields get a vote on layout.
    layouts = {tuple(m for m, a in s[0] if not a) for s in shapes.values() if s[0]}
    layouts.discard(())
    if len(layouts) > 1:
        return "UNSETTLED", None, f"data members disagree: {sorted(layouts)!r}"
    widest = max(shapes, key=lambda p: (len(shapes[p][1]), len(shapes[p][0])))
    others = [p for p in shapes if p != widest]
    missing = sorted(set().union(*(shapes[p][1] for p in others)) - shapes[widest][1])
    thin = ", ".join(f"{p.name}({len(shapes[p][1])})" for p in others)
    if missing:
        # The layout agrees and no base class is in dispute, so this IS one type
        # -- but adopting the header would break every TU that calls a method it
        # does not declare. That is a header to finish, not a judgement to make.
        return ("INCOMPLETE", widest,
                f"{widest.name} lacks {len(missing)}: {', '.join(missing[:6])}")
    return ("CANONICAL", widest,
            f"{widest.name} declares {len(shapes[widest][1])} methods; shims: {thin}")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--type", help="settle one type instead of all")
    args = ap.parse_args()

    defining = {}
    for path in (ROOT / "game").rglob("*.h"):
        if any(v in path.as_posix() for v in VENDORED):
            continue
        for head in HEAD.finditer(path.read_text(encoding="utf-8", errors="replace")):
            defining.setdefault(head.group(1), []).append(path)

    rows = []
    for name, paths in sorted(defining.items()):
        if args.type and name != args.type:
            continue
        if len(paths) < 2:
            continue
        got = verdict(name, sorted(set(paths)))
        if got:
            rows.append((name, *got))
    tally = collections.Counter(r[1] for r in rows)
    print(f"types defined by two or more headers: {len(rows)}")
    for status in ("CANONICAL", "INCOMPLETE", "UNSETTLED"):
        print(f"  {status:<11} {tally[status]:>3}")
    for name, status, path, why in sorted(rows, key=lambda r: (r[1], r[0])):
        where = path.relative_to(ROOT).as_posix() if path else "-"
        print(f"\n  {name:<28} {status}")
        print(f"      {where}")
        print(f"      {why}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
