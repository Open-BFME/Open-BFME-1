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
    r"|bfme[0-9A-Fa-f]{2,}$"                      # m_bfme0C
    r"|[a-z]+[0-9A-Fa-f]{2,}$"                    # m_hash20, m_slot1c
    r"|at[0-9A-Fa-f]+$)", re.I)

DECL = re.compile(r"\b(?:class|struct)\s+([A-Za-z_][A-Za-z_0-9]*)\s*(?::[^{;]*)?\{")
# `Real m_offsetZ;  // +0x18`, `BfmeShape *m_shapes;  // this+0x2C`
MEMBER = re.compile(
    r"^\s*(?:[A-Za-z_][\w:<>*&\s]*?)\s+(m_[A-Za-z_0-9]+)\s*(?:\[[^\]]*\])?\s*;"
    r"\s*//\s*(?:this)?\s*\+?(0x[0-9A-Fa-f]+)\b"
)


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


def outer_members(text, brace):
    """Members of THIS type only, never a nested one.

    A nested struct's offsets are relative to the NESTED type. Folding them into the
    outer class's offset space invents contradictions that are not there -- it scored
    GeometryInfo's inner BfmeShape::m_height against GeometryInfo+0x04 and called a
    correct file a defect. Depth tracking is the whole point of this function.
    """
    depth = 0
    i = brace
    out = []
    while i < len(text):
        ch = text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                return out
        elif ch == "\n" and depth == 1:
            end = text.find("\n", i + 1)
            hit = MEMBER.match(text[i + 1 : end if end > 0 else len(text)])
            if hit:
                out.append((hit.group(1), int(hit.group(2), 16), text.count("\n", 0, i) + 2))
        i += 1
    return out


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
            for member, off, line in outer_members(text, decl.end() - 1):
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
                    todo.append(rec)
                else:
                    conflicts.append(rec)
    return tally, todo, conflicts


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
    ap.add_argument("--write-baseline", action="store_true", help="record today's findings as the debt register")
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

    if not (args.check or args.todo or args.write_baseline):
        ap.error("give --class, --check, --todo or --write-baseline")

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
        if new - old and old:
            # Same rule pin_consistency_baseline lives by: a debt register that can
            # grow is not a register, it is a rubber stamp.
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
