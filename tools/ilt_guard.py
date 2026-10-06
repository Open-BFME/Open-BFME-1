#!/usr/bin/env python3
"""Refuse a new real name that retail's incremental-link thunk table contradicts.

Every external function retail defined in a command-line object has a jmp thunk, and the
thunk's position fixes the hash bucket of its decorated name to a narrow window
(tools/ilt_oracle.py, targets/game/reverse/ilt_windows.tsv). A functions.csv row or symbols.csv
pin whose name is new or changed at a thunked address must land in that window. A wrong name
passes by chance with probability ~6e-4; a right one fails only if a neighbouring anchor is
wrong. Exempt: placeholder and Bfme* names (honest stand-ins), untestable addresses (library
region, statics, labels), and keys in targets/game/reverse/ilt_contradicted_baseline.txt, the
contradicted names already in the ledger. That baseline only shrinks: a repair deletes its line
(`--prune-baseline`); nothing adds one.

A name that fits is only *consistent* with retail: a free-text name can be salted until it fits,
so passing this check is never identity evidence. Only tools/ilt_repair.py's searches, whose
expected false counts are stated, mark a row `ilt-verified=`.

  python3 tools/ilt_guard.py --staged           (pre-commit) changed rows in the index
  python3 tools/ilt_guard.py --range OLD NEW
  python3 tools/ilt_guard.py --all              shadow run: every contradicted real row, baseline or not
  python3 tools/ilt_guard.py --prune-baseline   drop baseline keys no longer in the ledger as contradicted
"""
import argparse
import csv
import io
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import ilt_oracle as O  # noqa: E402

BASELINE = O.REVERSE / "ilt_contradicted_baseline.txt"
BASELINE_REL = "targets/game/reverse/ilt_contradicted_baseline.txt"
LEDGERS = {"targets/game/reverse/functions.csv": ("functions", ["name", "export_rva", "target_rva", "target_size",
                                                                "source", "status", "notes"], "target_rva"),
           "targets/game/reverse/symbols.csv": ("pins", ["name", "address", "notes"], "address")}
HEADER = "# ilt_guard baseline: contradicted real names already in the ledger. Shrink-only; one key per line.\n"


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, encoding="utf-8",
                          errors="replace", check=True).stdout


def baseline_keys(text):
    return {l.rstrip("\r") for l in text.splitlines() if l.strip() and not l.startswith("#")}


def key(src, rva, name):
    return f"{src}\t0x{rva:08X}\t{name}"


def changed(diff_args):
    """[(src, rva, name)] of rows whose name is new at their address in the diff."""
    out = []
    for path, (src, fields, col) in LEDGERS.items():
        diff = git("diff", "-U0", "--no-color", "--no-renames", *diff_args, "--", path)
        side = {"+": [], "-": []}
        for l in diff.splitlines():
            if l[:1] in side and not l.startswith(("+++", "---")):
                side[l[0]].append(l[1:].rstrip("\r"))
        rows = lambda lines: csv.DictReader(io.StringIO("\n".join(lines)), fieldnames=fields)
        old = set()
        for r in rows(side["-"]):
            try:
                old.add((int(r[col], 16), r["name"]))
            except (TypeError, ValueError):
                pass
        for r in rows(side["+"]):
            try:
                rva = int(r[col], 16)
            except (TypeError, ValueError):
                continue
            if (rva, r["name"]) not in old:
                out.append((src, rva, r["name"] or ""))
    return out


def problems(rows, oracle, exempt):
    """(rejections, number of new real names merely consistent)."""
    bad, consistent = [], 0
    for src, rva, name in rows:
        if O.tier(name) != "real" or key(src, rva, name) in exempt:
            continue
        verdict, p, why = oracle.check(name, rva)
        if verdict == O.CONTRADICTED:
            bad.append(f"  {src} 0x{rva:08X} {name}\n      {why}")
        elif verdict == O.CONFIRMED:
            consistent += 1
    return bad, consistent


def shadow(oracle):
    for src, name, rva, _ in O.ledger_rows():
        if O.tier(name) == "real" and oracle.check(name, rva)[0] == O.CONTRADICTED:
            yield key(src, rva, name)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--staged", action="store_true")
    g.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    g.add_argument("--all", action="store_true")
    g.add_argument("--prune-baseline", action="store_true")
    g.add_argument("--init-baseline", action="store_true", help=argparse.SUPPRESS)  # once, with the guard
    args = ap.parse_args(argv)
    if args.all or args.prune_baseline or args.init_baseline:
        found = sorted(set(shadow(O.oracle())))
        if args.all:
            print("\n".join(found))
            print(f"{len(found)} contradicted real rows", file=sys.stderr)
            return 0
        keep = found if args.init_baseline else sorted(baseline_keys(BASELINE.read_text("utf-8")) & set(found))
        BASELINE.write_text(HEADER + "".join(k + "\n" for k in keep), encoding="utf-8", newline="\n")
        print(f"{BASELINE_REL}: {len(keep)} keys")
        return 0
    diff_args = ["--cached", "HEAD"] if args.staged else list(args.range)
    rows = changed(diff_args)
    if args.staged:
        try:
            head = baseline_keys(git("show", f"HEAD:{BASELINE_REL}"))
        except subprocess.CalledProcessError:
            head = None
        staged = baseline_keys(git("show", f":{BASELINE_REL}")) if head is not None else set()
        if head is not None and staged - head:
            print("ilt_guard: the contradicted-name baseline may only shrink; this adds:\n  "
                  + "\n  ".join(sorted(staged - head)[:20]), file=sys.stderr)
            return 1
        exempt = staged
    else:
        exempt = baseline_keys(git("show", f"{args.range[1]}:{BASELINE_REL}"))
    if not rows:
        return 0
    bad, consistent = problems(rows, O.oracle(), exempt)
    if bad:
        print("ilt_guard: retail's thunk table contradicts these names (tools/ilt_oracle.py; a wrong name "
              "fits by chance ~6e-4, so these are wrong decorations, classes or identities):", file=sys.stderr)
        print("\n".join(bad[:40]), file=sys.stderr)
        print("Fix the decoration (access, const, calling convention, class), keep the address-derived name, "
              "or test candidates with `python3 tools/ilt_oracle.py check NAME 0xRVA`.", file=sys.stderr)
        return 1
    if consistent:
        print(f"ilt_guard: {consistent} new name(s) consistent with retail's thunk table "
              f"(consistent, not verified)", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
