#!/usr/bin/env python3
"""Narrow structure invariants: who owns a retail address, and which file it belongs in.

Rules (each finding carries its rule id):

  A1  second row     a commit adds a ledger row for an address whose matched row
                     is owned by another source file, and does not remove that row.
  A2  wrong TU       a commit moves a row (its `source` changes) to a file other
                     than the address's APPROVED TU in tu_map.csv.
  A3  new row        a commit adds a row for an address with an approved TU in a
                     file other than that TU. Separate id so it can be promoted on
                     its own measurements; a moved row is A2, not A3.
  A4  second body    a staged source gains an out-of-line `Class::method(`
                     definition while every matched ledger row of that symbol is
                     owned by another file (two definitions of one retail function;
                     the link sees both). `inline` and template bodies are exempt.
  B1  private copy   a staged source gains a body for a class registered with a
                     canonical header (reverse/canonical_classes.csv in Open-BFME-2,
                     adopt_header.headers() in Open-BFME-1) without
                     `// class-gate: allow NAME reason`. The registry entry is the
                     ABI contract; the name is the key.
  B2  fingerprint    DIAGNOSTIC ONLY, never blocks: a new private class whose base
                     list and data-member types equal a registered class's. A
                     fingerprint is a similarity, not an identity, so it may only
                     raise a queue item.

Only what the commit introduces is checked, so existing debt never blocks an
unrelated edit. Everything runs on `git diff -U0` plus `git grep` lookups of the
few addresses a commit touches: about a second per commit in the hook, most of it
parsing tu_map.csv, which is skipped when the ledger did not change.

Usage:
  python3 tools/tu_ownership.py --staged [--shadow]   the commit hook
  python3 tools/tu_ownership.py --commit REV          check one commit against its parent
  python3 tools/tu_ownership.py --replay SINCE [--ref origin/master] [--rules A1,A2]
        replay first-parent history (no fetch) and print the would-reject rate
"""
import argparse
import collections
import csv
import io
import re
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_map  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
LAYOUT = tu_map.Layout(ROOT)
BLOCKING = {"A1", "A2", "A3", "A4", "B1"}
DEF = re.compile(r"^(?!\s)(?!.*\binline\b)(?!template\b)(?!#)(?!//)[^;{}=()]*?\b([A-Za-z_]\w*)\s*::\s*(~?[A-Za-z_]\w*)\s*\([^;]*$")
CLASS = re.compile(r"^\s*(?:class|struct)\s+(?:__declspec\([^)]*\)\s*)?([A-Za-z_]\w*)\s*(:[^{;]*)?\{?\s*$")
ALLOW = re.compile(r"//\s*class-gate:\s*allow\s+(\w+)\s+\S")


def ledger():
    return f"{LAYOUT.reverse}/functions.csv"


def git(*args, check=False):
    r = subprocess.run(["git", *args], cwd=ROOT, capture_output=True)
    return r.stdout.decode("utf-8", errors="replace") if (r.returncode == 0 or not check) else ""


def row_of(line):
    try:
        f = next(csv.reader([line]))
    except (StopIteration, csv.Error):
        return None
    if len(f) < 7 or not f[2].startswith("0x"):
        return None
    return {"name": f[0], "rva": int(f[2], 16), "source": f[4], "status": f[5], "notes": f[6]}


def diff(base, new, paths):
    """{path: (added lines, removed lines)} between two trees; new=None is the index."""
    args = ["diff", "-U0", "--no-color", "--no-ext-diff", "--no-renames"]
    args += ["--cached", base] if new is None else [base, new]
    out = collections.defaultdict(lambda: ([], []))
    path = None
    for line in git(*args, "--", *paths).splitlines():
        if line.startswith("+++ "):
            path = line[6:] if line.startswith("+++ b/") else None
        elif line.startswith("--- "):
            continue
        elif path and line.startswith("+"):
            out[path][0].append(line[1:])
        elif path and line.startswith("-"):
            out[path][1].append(line[1:])
    return out


def grep(rev, pattern, path):
    spec = ["--cached"] if rev is None else [rev]
    return git("grep", "-h", "-F", "-e", pattern, *spec, "--", path).splitlines()


def ledger_rows_at(rev, needle):
    return [r for r in map(row_of, grep(rev, needle, ledger())) if r]


# ---------------------------------------------------------------- A rules
def check_ledger(base, new, d, tumap):
    added, removed = d.get(ledger(), ([], []))
    add = [r for r in map(row_of, added) if r]
    rem = [r for r in map(row_of, removed) if r]
    gone = {(r["rva"], r["source"]) for r in rem}
    was = {r["rva"]: r for r in rem}
    out = []
    for r in add:
        if "gen-alias" in r["notes"]:
            continue
        prior = was.get(r["rva"])
        if prior and prior["source"] == r["source"]:
            continue                                   # an edit in place
        if not prior:
            owners = [o for o in ledger_rows_at(base, f",0x{r['rva']:08X},") if o["rva"] == r["rva"]
                      and o["status"] == "matched" and "gen-alias" not in o["notes"]
                      and (o["rva"], o["source"]) not in gone and o["source"] != r["source"]]
            if owners:
                out.append(("A1", f"0x{r['rva']:08X} {r['name']}: second row in {r['source']}; "
                                  f"owned by {owners[0]['source']}"))
                continue
        tus = [t for t in tumap.get(r["rva"], ()) if t["confidence"] == "approved" and t["kind"].startswith("code")]
        if tus and r["source"].lower() != tus[0]["tu"].lower():
            rule = "A2" if prior else "A3"
            out.append((rule, f"0x{r['rva']:08X} {r['name']}: {'moved' if prior else 'added'} to {r['source']}; "
                              f"approved TU is {tus[0]['tu']} ({tus[0]['by']})"))
    return out


def mangled(cls, meth):
    if meth == cls:
        return f"??0{cls}@@"
    if meth == "~" + cls:
        return f"??1{cls}@@"
    return f"?{meth}@{cls}@@"


def check_defs(base, new, d):
    out = []
    for path, (added, removed) in d.items():
        if not path.startswith(LAYOUT.src) or not path.endswith((".cpp", ".c")):
            continue
        gone = {re.sub(r"\s+", "", x) for x in removed}
        for line in added:
            m = DEF.match(line)
            if not m or re.sub(r"\s+", "", line) in gone:
                continue
            sym = mangled(m.group(1), m.group(2))
            rows = [r for r in ledger_rows_at(new, sym) if r["name"].startswith(sym)
                    and r["status"] == "matched" and "gen-alias" not in r["notes"]]
            if rows and all(r["source"] != path for r in rows):
                out.append(("A4", f"{path}: defines {m.group(1)}::{m.group(2)} owned by {rows[0]['source']} "
                                  f"(0x{rows[0]['rva']:08X})"))
    return out


# ---------------------------------------------------------------- B rules
def registry():
    """class -> header path (repo-relative)."""
    reg = {}
    p = LAYOUT.path("canonical_classes.csv")
    if p.exists():
        for r in tu_map.read_csv(p):
            reg[r["class"]] = r["header"]
        return reg
    try:
        import adopt_header
        for name, (inc, d, _) in adopt_header.headers().items():
            reg[name] = f"{d}/{inc}"
    except Exception:   # a registry we cannot read registers nothing
        pass
    return reg


def exempt():
    """path -> classes a recorded decision lets that file keep privately.

    Open-BFME-1's adopt_header.py records every shim the compiler refused to swap
    for its header in header_adopt_blocked.tsv; a recorded refusal is a decision,
    not a new copy, so B1 honours it (measured: 1 of 6 B1 replay findings).
    """
    out = collections.defaultdict(set)
    p = LAYOUT.path("header_adopt_blocked.tsv")
    if p.exists():
        for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
            f = line.split("	")
            if len(f) >= 2:
                out[f[0]].add(f[1])
    return out


MEMBER = re.compile(r"^\s*(?!static\b|typedef\b|friend\b|enum\b|using\b|virtual\b|return\b)([A-Za-z_][\w:<>,\s*&]*?)\s*\b\w+\s*(\[[^\]]*\])?\s*;")


def fingerprint(body, bases):
    depth, members = 0, []
    for line in body.splitlines():
        if depth == 1 and "(" not in line:
            m = MEMBER.match(line)
            if m:
                members.append(re.sub(r"\s+", "", m.group(1)) + (m.group(2) or ""))
        depth += line.count("{") - line.count("}")
    return (re.sub(r"\s+|public|private|protected", "", bases or ""), tuple(members))


def class_bodies(text):
    out = {}
    lines = text.splitlines()
    for i, line in enumerate(lines):
        m = CLASS.match(line)
        if not m:
            continue
        depth, body = 0, []
        for line2 in lines[i:]:
            body.append(line2)
            depth += line2.count("{") - line2.count("}")
            if "{" in "".join(body) and depth <= 0:
                break
        if "{" in "".join(body):
            out.setdefault(m.group(1), fingerprint("\n".join(body), m.group(2)))
    return out


_FP = None


def registered_fingerprints(reg):
    global _FP
    if _FP is None:
        _FP = {}
        for cls, hdr in reg.items():
            p = ROOT / hdr
            if p.exists():
                fp = class_bodies(p.read_text(encoding="utf-8", errors="replace")).get(cls)
                if fp and len(fp[1]) >= 2:
                    _FP.setdefault(fp, cls)
    return _FP


def check_classes(base, new, d, reg):
    out = []
    for path, (added, removed) in d.items():
        if not path.startswith(LAYOUT.src) or not path.endswith((".cpp", ".c", ".h")):
            continue
        new_names = {m.group(1) for m in map(CLASS.match, added) if m}
        new_names -= {m.group(1) for m in map(CLASS.match, removed) if m}
        if not new_names:
            continue
        spec = f":{path}" if new is None else f"{new}:{path}"
        text = git("show", spec)
        allowed = set(ALLOW.findall(text)) | exempt().get(path, set())
        bodies = class_bodies(text)
        for name in sorted(new_names):
            if name in reg and name not in allowed and name in bodies and ROOT / reg[name] != ROOT / path \
                    and reg[name] != path:
                out.append(("B1", f"{path}: private body of registered class {name} (header {reg[name]})"))
            elif name in bodies and name not in reg:
                hit = registered_fingerprints(reg).get(bodies[name])
                if hit:
                    out.append(("B2", f"{path}: class {name} has the layout fingerprint of registered {hit} "
                                      f"(diagnostic only)"))
    return out


# ---------------------------------------------------------------- drivers
def check(base, new, tumap=None, reg=None, rules=None):
    d = diff(base, new, [ledger(), LAYOUT.src.rstrip("/")])
    if tumap is None:
        tumap = tu_map.load(ROOT) if ledger() in d else {}
    reg = registry() if reg is None else reg
    out = check_ledger(base, new, d, tumap) + check_defs(base, new, d) + check_classes(base, new, d, reg)
    return [f for f in out if not rules or f[0] in rules]


def report(found, shadow):
    blocking = [f for f in found if f[0] in BLOCKING]
    for rule, msg in found:
        tag = "shadow" if shadow or rule not in BLOCKING else "refused"
        print(f"tu_ownership [{tag}] {rule} {msg}", file=sys.stderr)
    if blocking and not shadow:
        print("tu_ownership: put the body in its approved TU (tools/tu_skeleton.py --plan TU), "
              "or include the canonical header", file=sys.stderr)
        return 1
    return 0


def replay(since, ref, rules):
    revs = git("rev-list", "--first-parent", "--no-merges", f"--since={since}", ref).split()
    tumap, reg = tu_map.load(ROOT), registry()
    per_rule, flagged, timings, rows = collections.Counter(), [], [], 0
    for rev in reversed(revs):
        t0 = time.time()
        found = check(f"{rev}^", rev, tumap, reg, rules)
        timings.append(time.time() - t0)
        if found:
            subject = git("log", "-1", "--format=%s", rev).strip()
            flagged.append((rev[:10], subject, found))
            for rule in {f[0] for f in found}:
                per_rule[rule] += 1
    for rev, subject, found in flagged:
        print(f"{rev} {subject[:80]}")
        for rule, msg in found:
            print(f"    {rule} {msg}")
    n = len(revs)
    print(f"\ncommits {n}; flagged {len(flagged)}; per rule (commits): "
          + ", ".join(f"{k}={v} ({100 * v / max(n, 1):.1f}%)" for k, v in sorted(per_rule.items())))
    if timings:
        timings.sort()
        print(f"check cost per commit: median {timings[len(timings) // 2]:.2f}s, "
              f"p95 {timings[int(len(timings) * .95)]:.2f}s, max {timings[-1]:.2f}s")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--staged", action="store_true")
    g.add_argument("--commit", metavar="REV")
    g.add_argument("--replay", metavar="SINCE")
    ap.add_argument("--ref", default="origin/master")
    ap.add_argument("--rules", help="comma-separated rule ids to run (default: all)")
    ap.add_argument("--shadow", action="store_true", help="report, never refuse")
    a = ap.parse_args(argv)
    rules = set(a.rules.split(",")) if a.rules else None
    if a.replay:
        return replay(a.replay, a.ref, rules)
    if a.staged:
        return report(check("HEAD", None, rules=rules), a.shadow)
    return report(check(f"{a.commit}^", a.commit, rules=rules), a.shadow)


if __name__ == "__main__":
    sys.exit(main())
