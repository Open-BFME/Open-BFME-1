#!/usr/bin/env python3
"""What is the member at <class>+<offset> actually called, and does the tree agree?

WHY THIS EXISTS. An agent invents `m_unk20` because finding the real name costs it
four minutes and inventing one costs nothing. The repository already holds the real
name -- 9,539 (class, member) pairs sit in reverse/zh_offsets.json and 2,063 more in
reverse/field_names.csv -- but nothing puts them in front of the agent at the moment
it is choosing, so the evidence is re-derived by hand or, more often, skipped. The
ASK mode is the fix for that: one command, one answer, no judgement.

WHY IT ALSO CHECKS. A machine-generated name advertises its own ignorance and greps
out in a second; a plausible wrong name does neither, and the byte gate cannot see
it -- `m_pitchShift` compiles to the same bytes as `m_priority`. That is the one
defect class with no detector, because the five identity detectors are all keyed on
an ADDRESS and a member name has none. Comparing the offsets a source asserts against
the offsets the ZH<->retail alignment witnesses is the missing question.

    python3 tools/name_oracle.py --class GameWindow
    python3 tools/name_oracle.py --class GameWindow --offset 0x2c
    python3 tools/name_oracle.py --check [PATH ...] [--staged]
    python3 tools/name_oracle.py --write-baseline

A disagreement is NOT proof the source is wrong. The witness is itself inferred --
instruction alignment, weighted votes -- and BFME forked the ZH layout, so a field
BFME added can land on an offset ZH used for something else. Two independent claims
conflicting is a question for a human, which is why this carries a shrink-only
baseline like pin_consistency rather than failing a commit outright.
"""
import argparse
import collections
import csv
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LAYOUTS = ROOT / "reverse/bfme_layouts.json"
FIELDS = ROOT / "reverse/field_names.csv"
BASELINE = ROOT / "reverse/name_oracle_baseline.csv"
AREAS = ("Code/GameEngine", "Code/GameEngineDevice", "Code/Libraries")

# The confidence floor below which layout_witness's own aggregation says the
# alignment was too poor to name a member. Quoting a 0.4-confidence witness at an
# agent as though it were an answer is how this tool would start manufacturing the
# very defect it exists to catch.
MIN_CONFIDENCE = 0.8

# A name whose SHAPE announces "I do not know what this is". The distinction is the
# whole point of the tool: such a name disagreeing with the witness is free work with
# the answer already attached, whereas two plausible names disagreeing is a question
# somebody has to settle. Lumping them together buries 100 easy wins under 30 hard ones.
PLACEHOLDER = re.compile(
    r"^m_(?:[a-z]{1,2}\d*$"                       # m_a, m_b, m_x1
    r"|(?:unk|unmodelled|field|pad|slack|slot|reserved|unused)"
    r"|(?:bfme)?(?:dword|word|byte|bool|int|float|short|ptr|hash|string|str|val|value)\d*$"
    r"|[A-Za-z]+\d[0-9A-Fa-f]+$"                  # m_hash20, m_slot1c, m_bfme0C, m_flag40
    r"|at\d[0-9A-Fa-f]*$)")

DECL = re.compile(r"\b(?:class|struct)\s+([A-Za-z_][A-Za-z_0-9]*)\s*(?P<base>:[^{;]*)?\{")
# `Real m_offsetZ;  // +0x18`, `BfmeShape *m_shapes;  // this+0x2C`, `int m_x;`
MEMBER = re.compile(
    r"^\s*((?:const\s+)?[A-Za-z_][\w:<> ]*?)\s+(\*?\s*)(m_[A-Za-z_0-9]+)\s*(\[[^\]]*\])?\s*;"
    r"(?:\s*//\s*(?:this)?\s*\+?(0x[0-9A-Fa-f]+)\b)?"
)

# MSVC 7.1 on x86: natural alignment, capped at 8 (/Zp8, what this tree compiles
# with). A type absent from this table makes the struct UNCOMPUTABLE and the whole
# struct is refused -- a guessed size shifts every offset after it, which would turn
# this checker into a generator of false findings against other people's commits.
# (size, alignment). They differ for aggregates: Coord3D is 12 bytes but aligns to 4,
# and treating its size as its alignment would push every following member.
#
# Every entry beyond the built-ins is READ FROM THE HEADER, never guessed, and then
# confirmed by --selfcheck against the offsets the tree already states:
#   StringBase/AsciiString/UnicodeString -- string_base.h:80 is one `Header *m_data`
#   Coord3D / Coord2D / ICoord2D         -- basetype.h: three Reals / two Reals / two Ints
# AsciiString alone blocked 739 structs and Coord3D another 272, and a blocked struct
# is one this checker cannot see into at all -- which is how three deliberately bogus
# names walked past it during the promotion probe.
SIZES = {
    "char": (1, 1), "signed char": (1, 1), "unsigned char": (1, 1), "bool": (1, 1),
    "Bool": (1, 1), "Byte": (1, 1), "UnsignedByte": (1, 1),
    "short": (2, 2), "unsigned short": (2, 2), "wchar_t": (2, 2), "Short": (2, 2),
    "UnsignedShort": (2, 2), "WideChar": (2, 2),
    "int": (4, 4), "unsigned int": (4, 4), "unsigned": (4, 4), "long": (4, 4),
    "unsigned long": (4, 4), "float": (4, 4), "Int": (4, 4), "UnsignedInt": (4, 4),
    "UnsignedInt32": (4, 4), "Real": (4, 4), "Color": (4, 4), "ObjectID": (4, 4),
    "DrawableID": (4, 4),
    "double": (8, 8), "__int64": (8, 8), "unsigned __int64": (8, 8),
    "Int64": (8, 8), "UnsignedInt64": (8, 8),
    "AsciiString": (4, 4), "UnicodeString": (4, 4), "StringBase<char>": (4, 4),
    "BFMERetailAsciiString": (4, 4),
    "Coord3D": (12, 4), "Coord2D": (8, 4), "ICoord2D": (8, 4),
}


def size_of(decl_type, pointer, array):
    """(total bytes, alignment) for one declaration, or None when unsizeable."""
    name = " ".join(decl_type.replace("const", "").replace("volatile", "").split())
    if pointer.strip() == "*":
        unit, align = 4, 4
    elif name in SIZES:
        unit, align = SIZES[name]
    else:
        return None
    count = 1
    if array:
        inner = array[1:-1].strip()
        try:
            count = int(inner, 0)
        except ValueError:
            # `[0x18 - 0x0C]` is how the tree spells a gap between two known offsets.
            span = re.fullmatch(r"(0x[0-9A-Fa-f]+|\d+)\s*-\s*(0x[0-9A-Fa-f]+|\d+)", inner)
            if not span:
                return None
            count = int(span.group(1), 0) - int(span.group(2), 0)
    return unit * count, align


def load_witness():
    """(class, offset) -> (member, confidence, source). Two independent oracles;
    where both speak, bfme_layouts wins because its offset came from the retail
    body itself rather than from an upstream offsetof."""
    out = {}
    for row in json.load(open(FIELDS.parent / "bfme_layouts.json")):
        owner, member, off = row.get("owner"), row.get("member"), row.get("bfme")
        conf = row.get("confidence") or 0.0
        if not owner or not member or off is None:
            continue
        if str(member).startswith("+0x") or conf < MIN_CONFIDENCE:
            continue
        out.setdefault((owner, int(off)), (member, conf, "layout_witness"))
    for row in csv.DictReader(open(FIELDS, newline="")):
        owner, member, off = row.get("upstream_class"), row.get("upstream_member"), row.get("bfme_offset")
        votes = row.get("votes") or "0"
        if not owner or not member or not off or not votes.isdigit() or int(votes) < 2:
            continue
        if (row.get("notes") or "").startswith("ambiguous"):
            continue
        out.setdefault((owner, int(off, 16)), (member, 1.0, "field_names"))
    return out


def struct_body(text, brace):
    """The text between this declaration's braces, nested braces included."""
    depth = 0
    i = brace
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return text[brace + 1 : i]
        i += 1
    return None


def outer_members(text, brace, has_base):
    """Offsets for THIS type's own members, computed from declaration order.

    Only 11.1% of member declarations state their offset in a comment, so requiring
    one confined this checker to ~1% of the surface. Computing it instead reaches
    43,332 members -- but only while every case the model cannot account for is
    REFUSED rather than approximated. Each `return [], reason` below is one of those.

    A nested struct's offsets are relative to the NESTED type, so only depth-1 lines
    count; folding the inner ones in scored GeometryInfo's BfmeShape::m_height
    against GeometryInfo+0x04 and reported a correct file as a defect.

    Returns (members, refusal_reason). Measured against the 5,285 members that state
    their own offset, this model agrees 99.5% of the time; `--selfcheck` is that test.
    """
    if has_base:
        return [], "base class of unknown size"
    body = struct_body(text, brace)
    if body is None:
        return [], "unterminated declaration"
    if re.search(r"\bunion\b", body):
        # Union members OVERLAY; this model sums them, so it would push every later
        # offset. PathfindCellInfo hid behind the unsizeable-type refusal until
        # ICoord2D became sizeable, then produced nine wrong offsets at once.
        return [], "contains a union"
    # A polymorphic class puts a 4-byte vptr at +0, so its first member starts at +4.
    # Missing this was the entire off-by-four cluster: 90.5% agreement became 99.5%.
    off = 4 if re.search(r"\bvirtual\b", body) else 0
    first_line = text.count("\n", 0, brace) + 1
    out = []
    depth = 0
    for n, line in enumerate(body.splitlines()):
        # Depth is tested BEFORE the line's own braces are counted, so a nested
        # declaration's members are skipped while its closing `};` still returns here.
        nested, depth = depth > 0, depth + line.count("{") - line.count("}")
        if nested:
            continue
        if re.match(r"^\s*(?:public|private|protected)\s*:", line):
            continue
        if re.match(r"^\s*(?://|/\*|\*|$|\}|#)", line) or "(" in line:
            continue
        hit = MEMBER.match(line)
        if not hit:
            if re.search(r"\bm_[A-Za-z_0-9]+\s*;", line):
                return [], "unparsed member declaration"
            continue
        sized = size_of(hit.group(1), hit.group(2), hit.group(4))
        if sized is None:
            return [], f"unsizeable type {hit.group(1).strip()!r}"
        span, align = sized
        step = min(align, 8)
        off = (off + step - 1) // step * step
        stated = int(hit.group(5), 16) if hit.group(5) else None
        if stated is not None and stated != off:
            if not out or all(m[3] is None for m in out):
                # The first member states an offset the model does not put it at, so
                # this declaration windows into the middle of a larger class and every
                # offset in it is relative to something we do not know.
                return [], "declaration windows into a larger class"
            # The struct's own annotation contradicts the model. Trust the file, not
            # the model, and disqualify the struct: asserting offsets from a layout
            # this very declaration has already refuted is how a checker starts
            # blocking correct commits.
            return [], "annotation contradicts the computed layout"
        out.append((hit.group(3), off, first_line + n + 1, stated, span))
        off += span
    return out, None


def sources(paths, staged):
    if paths:
        # Callers pass repo-relative paths (that is what every other tool here
        # prints), so anchor them; an unanchored Path breaks relative_to(ROOT) later.
        return [Path(p) if Path(p).is_absolute() else ROOT / p for p in paths]
    if staged:
        out = subprocess.run(
            ["git", "diff", "--cached", "--name-only", "--diff-filter=ACMRT"],
            cwd=ROOT, capture_output=True, text=True, check=True).stdout.split()
        return [ROOT / p for p in out if p.endswith(".cpp") and p.startswith(AREAS)]
    return [p for area in AREAS for p in (ROOT / area).rglob("*.cpp")]


def scan(paths, staged):
    """Every (file, class, offset) a source asserts that the witness also names."""
    wit = load_witness()
    tally = collections.Counter()
    todo, conflicts = [], []
    for path in sources(paths, staged):
        if not path.exists():
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        for decl in DECL.finditer(text):
            owner = decl.group(1)
            members, refused = outer_members(text, decl.end() - 1, bool(decl.group("base")))
            if refused:
                # Counted, never silent: refusals are the safety property, so a drop
                # in this number is the signal that the model started guessing.
                tally["refused: " + refused.split(" '")[0]] += 1
            for member, off, line, stated, span in members:
                tally["members computed"] += 1
                if stated is not None:
                    tally["  ...offset stated in the file too"] += 1
                known = wit.get((owner, off))
                if known is None:
                    continue
                name, conf, src = known
                rec = (str(path.relative_to(ROOT)), line, owner, off, member, name, conf, src)
                if name == member:
                    tally["agree"] += 1
                elif "+0x" in name:
                    # The witness resolved this offset to a field inside an embedded
                    # struct; the source naming that inner field directly is a finer
                    # answer, not a conflicting one.
                    tally["embedded"] += 1
                elif member.lower().replace("bfme", "") == name.lower().replace("bfme", ""):
                    tally["variant"] += 1
                elif PLACEHOLDER.match(member):
                    # `char m_unknown[0x54]` starting where s_GlobalDataFieldParseTable
                    # starts is not that field -- it is unknown SPACE that happens to
                    # begin there, and naming it after the first field inside it is
                    # simply false. Offer a name only when the member does not swallow
                    # another witnessed offset.
                    if any((owner, o) in wit for o in range(off + 1, off + span)):
                        tally["placeholder spans other witnessed fields"] += 1
                    else:
                        todo.append(rec)
                else:
                    conflicts.append(rec)
    return tally, todo, conflicts


def selfcheck(paths):
    """Score the offset model against the offsets the tree already states.

    7,154 member declarations carry a `// +0xNN` comment. That is free ground truth
    for the one thing this tool cannot otherwise prove about itself, it needs no new
    evidence, and it runs in seconds -- so every change to SIZES or to the alignment
    model is answerable here before it reaches anybody's commit.

    Unlike the scan, this does NOT disqualify a struct on the first contradiction:
    the point is to count them.
    """
    agree, mismatch, structs = 0, [], collections.Counter()
    for path in sources(paths, False):
        if not path.exists():
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        for decl in DECL.finditer(text):
            if decl.group("base"):
                structs["skipped: base class"] += 1
                continue
            body = struct_body(text, decl.end() - 1)
            if body is None:
                continue
            if re.search(r"\bunion\b", body):
                structs["skipped: contains a union"] += 1
                continue
            off = 4 if re.search(r"\bvirtual\b", body) else 0
            rows, bad = [], None
            for line in body.splitlines():
                if re.match(r"^\s*(?:public|private|protected)\s*:", line):
                    continue
                if re.match(r"^\s*(?://|/\*|\*|$|\}|#)", line) or "(" in line:
                    continue
                hit = MEMBER.match(line)
                if not hit:
                    if re.search(r"\bm_[A-Za-z_0-9]+\s*;", line):
                        bad = "unparsed member"
                        break
                    continue
                sized = size_of(hit.group(1), hit.group(2), hit.group(4))
                if sized is None:
                    bad = "unsizeable type"
                    break
                span, align = sized
                step = min(align, 8)
                off = (off + step - 1) // step * step
                rows.append((hit.group(3), off, int(hit.group(5), 16) if hit.group(5) else None))
                off += span
            if bad:
                structs["skipped: " + bad] += 1
                continue
            stated = [r for r in rows if r[2] is not None]
            if stated and stated[0][2] != stated[0][1]:
                structs["skipped: windows into a larger class"] += 1
                continue
            structs["scored"] += 1
            for name, computed, said in rows:
                if said is None:
                    continue
                if said == computed:
                    agree += 1
                else:
                    mismatch.append(f"{path.relative_to(ROOT)}: {decl.group(1)}::{name} "
                                    f"states {said:#x}, model computes {computed:#x}")
    return agree, mismatch, structs


def key(f):
    return f"{f[2]}+{f[3]:#x}|{f[4]}|{f[5]}"


def read_baseline():
    if not BASELINE.exists():
        return set()
    return {r["finding"] for r in csv.DictReader(open(BASELINE, newline=""))}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--class", dest="cls", help="print what the evidence knows about this class")
    ap.add_argument("--offset", help="with --class, answer one offset (hex or decimal)")
    ap.add_argument("--check", action="store_true", help="report sources that CONFLICT with the witness")
    ap.add_argument("--todo", action="store_true", help="list placeholders the evidence can already name")
    ap.add_argument("--apply", action="store_true", help="with --todo, rewrite those placeholders in place")
    ap.add_argument("--staged", action="store_true", help="with --check, only the staged sources")
    ap.add_argument("--selfcheck", action="store_true", help="score the offset model against the offsets the tree states")
    ap.add_argument("--max-mismatch", type=int, default=0,
                    help="with --selfcheck, the residual this model is known to have; exceeding it fails")
    ap.add_argument("--write-baseline", action="store_true", help="record today's findings as the debt register")
    ap.add_argument("--reach-changed", action="store_true",
                    help="with --write-baseline, allow growth because the DETECTOR got wider, not the debt")
    ap.add_argument("paths", nargs="*")
    args = ap.parse_args()

    if args.cls:
        wit = load_witness()
        rows = sorted((off, n, c, s) for (o, off), (n, c, s) in wit.items() if o == args.cls)
        if not rows:
            # Loud, not empty: "no output" reads as "no members", which would send an
            # agent off to invent a name while the evidence simply was not loaded.
            print(f"name_oracle: no witnessed layout for class {args.cls!r} "
                  f"(of {len({o for o, _ in wit})} classes). Evidence may exist but be unaligned: "
                  f"run tools/layout_witness.py --compile, then tools/layout_witness.py", file=sys.stderr)
            return 2
        if args.offset is not None:
            want = int(args.offset, 0)
            for off, n, c, s in rows:
                if off == want:
                    print(f"{args.cls}+{off:#x}  {n}  (confidence {c:.2f}, {s})")
                    return 0
            print(f"name_oracle: {args.cls}+{want:#x} is not witnessed; "
                  f"nearest below is {max((o for o, *_ in rows if o <= want), default=None)}", file=sys.stderr)
            return 2
        print(f"{args.cls}: {len(rows)} witnessed member(s)")
        for off, n, c, s in rows:
            print(f"  +{off:#06x}  {n:<40} conf={c:.2f}  {s}")
        return 0

    if args.selfcheck:
        agree, mismatch, structs = selfcheck(args.paths)
        total = agree + len(mismatch)
        print(f"name_oracle --selfcheck: {agree} of {total} stated offsets reproduced "
              f"({100 * agree / max(total, 1):.1f}%)")
        for k, v in structs.most_common():
            print(f"  {v:>6}  structs {k}")
        for m in mismatch[:40]:
            print(f"  MISMATCH {m}")
        if len(mismatch) > 40:
            print(f"  ... and {len(mismatch) - 40} more")
        # A mismatch is a bug in SIZES or the alignment model, never something to
        # wave through: the scan disqualifies such a struct, so every one of these
        # is coverage this tool is silently giving up. The ceiling exists so a change
        # to the model is answerable as better-or-worse rather than pass-or-fail --
        # today's residual is 25, all packed or gap-modelled Bfme* declarations.
        if len(mismatch) > args.max_mismatch:
            print(f"name_oracle: {len(mismatch)} mismatch(es) exceeds the known "
                  f"residual of {args.max_mismatch}", file=sys.stderr)
            return 1
        return 0

    if not (args.check or args.todo or args.write_baseline):
        ap.error("give --class, --check, --todo, --selfcheck or --write-baseline")

    tally, todo, findings = scan(args.paths, args.staged)

    if args.todo:
        # The work queue, not the bug list: a placeholder the evidence can already
        # name. No judgement in any of these -- the answer is in the right column.
        print(f"name_oracle: {len(todo)} placeholder(s) the evidence can name "
              f"({len({key(t) for t in todo})} distinct)")
        for t in sorted(todo, key=lambda r: (r[2], r[3])):
            print(f"  {t[0]}:{t[1]}: {t[2]}+{t[3]:#x}  {t[4]}  ->  {t[5]}  ({t[7]})")
        if not args.apply:
            return 0
        # Member renames are byte-neutral (nothing in a member name reaches the
        # mangled symbol), so this is a text substitution and the gate is the proof.
        # It stages nothing and commits nothing: build the touched files, then commit.
        done = refused = 0
        for path in sorted({t[0] for t in todo}):
            text = (ROOT / path).read_text(encoding="utf-8")
            for _, _, _, _, old, new, _, _ in [t for t in todo if t[0] == path]:
                if len(re.findall(rf"\b{re.escape(old)}\b\s*(?:\[[^\]]*\])?\s*;", text)) > 1:
                    # The same placeholder spelling declared in two structs of one file
                    # sits at two different offsets; a file-wide substitution would put
                    # one struct's name into the other. Refuse the row, not the file.
                    print(f"  REFUSED {path}: {old!r} is declared more than once here",
                          file=sys.stderr)
                    refused += 1
                    continue
                if re.search(rf"\b{re.escape(new)}\b", text):
                    # Renaming onto a name the file already uses would silently merge
                    # two distinct members. Refuse the row, never the whole file.
                    print(f"  REFUSED {path}: {new!r} already appears in this file", file=sys.stderr)
                    refused += 1
                    continue
                text, n = re.subn(rf"\b{re.escape(old)}\b", new, text)
                done += n
            (ROOT / path).write_text(text, encoding="utf-8")
        print(f"name_oracle: rewrote {done} occurrence(s), refused {refused}. "
              f"Now byte-verify: ./build.sh " + " ".join(sorted({t[0] for t in todo})[:4]) + " ...")
        return 0

    if args.write_baseline:
        old = read_baseline()
        new = {key(f) for f in findings}
        if new - old and old and not args.reach_changed:
            # Same rule pin_consistency_baseline lives by: a debt register that can
            # grow is not a register, it is a rubber stamp. The one honest exception
            # is a detector that started seeing more of the tree -- that is new SIGHT,
            # not new debt -- and it needs saying out loud with --reach-changed, in a
            # commit that changes no source, so the growth is attributable.
            print(f"name_oracle: refusing to grow the baseline by {len(new - old)} finding(s):", file=sys.stderr)
            for k in sorted(new - old)[:10]:
                print(f"    {k}", file=sys.stderr)
            return 1
        with open(BASELINE, "w", newline="") as fh:
            w = csv.writer(fh)
            w.writerow(["finding", "file", "line", "confidence", "source"])
            for f in sorted(findings, key=key):
                w.writerow([key(f), f[0], f[1], f"{f[6]:.2f}", f[7]])
        print(f"name_oracle: baseline written, {len(findings)} finding(s)")
        return 0

    base = read_baseline()
    fresh = [f for f in findings if key(f) not in base]
    print(f"name_oracle: {tally['agree']} agree, {tally['embedded']} resolve inside an embedded struct, "
          f"{tally['variant']} spelling variants, {len(todo)} nameable placeholders (--todo), "
          f"{len(findings)} conflicts ({len({key(f) for f in findings})} distinct), "
          f"{len(fresh)} not in the baseline")
    for f in fresh:
        print(f"  {f[0]}:{f[1]}: {f[2]}+{f[3]:#x} says {f[4]!r}, witness says {f[5]!r} "
              f"(confidence {f[6]:.2f}, {f[7]})")
    if fresh:
        print("\nA disagreement is a question, not a verdict: the witness is inferred and BFME forked "
              "the ZH layout. Settle it, then remove the line -- never add one to go green.", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
