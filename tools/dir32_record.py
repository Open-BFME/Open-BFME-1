#!/usr/bin/env python3
"""The one sanctioned writer of targets/game/reverse/dir32_addresses.csv.

  retire OLD --for NEW [--msg FILE]
      Delete OLD's line when the owner's two conditions hold (ruling 2026-10-09):
      NEW is ledger-owned at OLD's recorded address (a data_rows.csv row at that
      VA, or a `?j_` functions.csv row at that RVA) and recorded nowhere else,
      and OLD, decorated or as its bare identifier, occurs nowhere under game/ or
      inputs/reference/shims/ in the index. Prints the trailer
      `Dir32-Retire: OLD 0x<VA> for NEW`; --msg appends it to that message file.
      The commit-msg hook (tools/dir32_record_guard.py --commit-msg, as of HEAD)
      refuses a deletion without a matching trailer and re-checks both conditions.

  record [--msg FILE]
      Adopt the full gate's proposal (build/dir32_addresses.csv, written by
      build.propose_dir32_addresses): add the names it proposes that the record
      lacks. Recorded lines are kept as they are (a rewrite is refused by the
      pre-commit guard; a name the proposal drops is retired only through
      `retire`). Each addition must pass build.unrecorded_dir32_problem, the same
      check the pre-commit guard applies. Prints `Dir32-Record: +N from the full
      gate's proposal` for the message (audit only; the guard judges the lines).

Stage the record yourself: git add targets/game/reverse/dir32_addresses.csv
"""
import argparse
import csv
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
sys.path.insert(0, str(TOOLS))
import dir32_record_guard as guard  # noqa: E402

ROOT = Path(guard.root())
RECORD = ROOT / guard.REL
PROPOSAL = ROOT / "build" / "dir32_addresses.csv"


def read(path):
    with open(path, newline="") as handle:
        return {row["name"]: int(row["va"], 16) for row in csv.DictReader(handle)}


def write_adding(path, added):
    """Append ADDED lines, leaving every recorded byte as it is."""
    text = Path(path).read_text(newline="")
    if text and not text.endswith("\n"):
        text += "\n"
    text += "".join(f"{name},0x{va:08X}\n" for name, va in sorted(added.items()))
    Path(path).write_text(text, newline="")


def write_dropping(path, name):
    """Delete one line, leaving every other byte as it is."""
    lines = Path(path).read_text(newline="").splitlines(keepends=True)
    kept = [line for line in lines if line.split(",", 1)[0] != name]
    Path(path).write_text("".join(kept), newline="")


def append_trailer(msg, line):
    if not msg:
        return
    text = Path(msg).read_text() if Path(msg).exists() else ""
    if line in text.splitlines():
        return
    Path(msg).write_text(text.rstrip("\n") + ("\n\n" if text.strip() else "") + line + "\n")


def retire(args):
    recorded = read(RECORD)
    if args.old not in recorded:
        print(f"dir32_record: {args.old} is not recorded", file=sys.stderr)
        return 1
    va = recorded[args.old]
    after = {k: v for k, v in recorded.items() if k != args.old}
    problem = guard.retire_problem(args.old, va, args.new, recorded, after)
    if problem:
        print(f"dir32_record: refused: {problem}", file=sys.stderr)
        return 1
    write_dropping(RECORD, args.old)
    line = guard.trailer(args.old, va, args.new)
    append_trailer(args.msg, line)
    print(line)
    return 0


def record(args):
    import build
    if not PROPOSAL.exists():
        print(f"dir32_record: no proposal at {PROPOSAL.relative_to(ROOT)}; run the full gate", file=sys.stderr)
        return 1
    recorded, proposed = read(RECORD), read(PROPOSAL)
    identities = build.dir32_identities(recorded)
    symbol_map = build.load_symbol_map()
    added, refused = {}, []
    for name in sorted(proposed.keys() - recorded.keys()):
        problem = build.unrecorded_dir32_problem(name, proposed[name], identities, symbol_map)
        (refused.append(f"{name},0x{proposed[name]:08X}: {problem}") if problem
         else added.__setitem__(name, proposed[name]))
    moved = sorted(n for n in proposed.keys() & recorded.keys() if proposed[n] != recorded[n])
    dropped = sorted(recorded.keys() - proposed.keys())
    for line in refused:
        print("  not added: " + line, file=sys.stderr)
    if moved:
        print(f"  {len(moved)} recorded name(s) proposed at a new address, kept; retire them first: "
              + ", ".join(moved[:5]), file=sys.stderr)
    if dropped:
        print(f"  {len(dropped)} recorded name(s) no longer referenced, kept "
              "(retire one only with `retire OLD --for NEW`)", file=sys.stderr)
    if not added:
        print("dir32_record: nothing to add")
        return 1 if refused else 0
    write_adding(RECORD, added)
    line = f"Dir32-Record: +{len(added)} from the full gate's proposal"
    append_trailer(args.msg, line)
    print(line)
    return 1 if refused else 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("retire")
    r.add_argument("old")
    r.add_argument("--for", dest="new", required=True)
    r.add_argument("--msg")
    a = sub.add_parser("record")
    a.add_argument("--msg")
    args = ap.parse_args(argv)
    return retire(args) if args.cmd == "retire" else record(args)


if __name__ == "__main__":
    sys.exit(main())
