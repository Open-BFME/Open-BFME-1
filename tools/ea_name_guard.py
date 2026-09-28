#!/usr/bin/env python3
"""Refuse naming an address against EA's own name for it.

targets/game/reverse/ea_evidence.csv (tools/ea_evidence.py) records EA's Class::method for
addresses whose WorldBuilder partner names itself. When a row gets its first real name (it is
new, or its old name kept its address token) at an address whose EA name has strong pairing, the
name must be EA's, keep the address token, be the retail export there, be a Class::method Zero
Hour declares, or say in the row's notes why EA's name is wrong for BFME1:
`ea-name-disputed=<evidence>`. Labels are evidence, not proof:
BFME2 renamed some members, and a body that inlined a labelled callee carries the callee's label
(a destructor labelled with the clear() it inlined). Renaming an already-real name is left to
the identity tools; only the step from unknown to named is guarded.

  python3 tools/ea_name_guard.py --staged
  python3 tools/ea_name_guard.py --range OLD NEW
"""
import argparse
import collections
import csv
import io
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from ea_evidence import ZH, plain  # noqa: E402

LEDGER = "targets/game/reverse/functions.csv"
FIELDS = ["name", "export_rva", "target_rva", "target_size", "source", "status", "notes"]


def changed_rows(diff_args):
    """(rows added, {rva: name} of rows removed) in the ledger diff."""
    diff = subprocess.run(["git", "diff", "-U0", "--no-color", "--no-renames", *diff_args, "--", LEDGER],
                          cwd=ROOT, capture_output=True, text=True, check=True).stdout
    side = {"+": [], "-": []}
    for l in diff.splitlines():
        if l[:1] in side and not l.startswith(("+++", "---")):
            side[l[0]].append(l[1:].rstrip("\r"))
    parse = lambda lines: list(csv.DictReader(io.StringIO("\n".join(lines)), fieldnames=FIELDS))
    old = {}
    for r in parse(side["-"]):
        try:
            old.setdefault(int(r["target_rva"], 16), set()).add(r["name"] or "")
        except (TypeError, ValueError):
            pass
    return parse(side["+"]), old


def load():
    ea = {}
    with open(ROOT / "targets/game/reverse/ea_evidence.csv", encoding="utf-8", newline="") as f:
        for r in csv.DictReader(f):
            if r["kind"] == "name":
                ea[int(r["rva"], 16)] = (r["value"], r["route"], r["basis"])
    exports = {}
    with open(ROOT / "targets/game/reverse/exports.csv", encoding="utf-8", newline="") as f:
        for e in csv.DictReader(f):
            if e["kind"] == "code":
                exports.setdefault(int(e["target_rva"] or e["rva"], 16), set()).add(e["name"])
    return ea, exports


def zh_methods():
    """class -> call-shaped tokens Zero Hour pairs with it. A superset on purpose: any token in a
    header that declares the class counts, which can only let a name through, never block one."""
    known = collections.defaultdict(set)
    for path in ZH.rglob("*"):
        suffix = path.suffix.lower()
        if suffix not in (".h", ".cpp", ".inl") or path.relative_to(ZH).parts[0] == "Tools":
            continue
        text = path.read_text(encoding="latin1")
        for m in re.finditer(r"\b([A-Za-z_]\w*)::(~?\w+)\s*\(", text):
            known[m.group(1).lower()].add(m.group(2).lower())
        if suffix != ".cpp":
            tokens = {t.lower() for t in re.findall(r"(~?\b[A-Za-z_]\w*)\s*\(", text)}
            for c in re.findall(r"^\s*(?:class|struct)\s+(?:\w+\s+)?([A-Za-z_]\w*)\s*[:{]", text, re.M):
                known[c.lower()] |= tokens
    return known


def problems(rows, old, ea, exports, zh=None):
    bad = []
    for r in rows:
        try:
            rva = int(r["target_rva"], 16)
        except (TypeError, ValueError):
            continue
        if rva not in ea or ea[rva][2] != "strong" or "vendored=" in (r["notes"] or ""):
            continue                          # a vendored row carries its upstream's identity
        name, (want, route, basis) = r["name"] or "", ea[rva]
        token = f"{rva:08x}"
        if any(n == name or token not in n.lower() for n in old.get(rva, ())):
            continue                          # unchanged, or renaming a name that was already real
        have = plain(name)
        if ((have and have.lower() == want.lower()) or token in name.lower()
                or name in exports.get(rva, ()) or "ea-name-disputed=" in (r["notes"] or "")):
            continue
        if have:
            zh = zh if zh is not None else zh_methods()
            cls, method = have.lower().split("::")
            if method in zh.get(cls, ()):
                continue
        bad.append(f"  0x{rva:08X}: {name} contradicts EA's {want} ({route}, {basis})")
    return bad


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--staged", action="store_true")
    g.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    args = ap.parse_args()
    rows, old = changed_rows(["--cached", "HEAD"] if args.staged else args.range)
    if not rows:
        return 0
    bad = problems(rows, old, *load())
    if bad:
        print("ea_name_guard: these names contradict EA's own name for the address "
              "(targets/game/reverse/ea_evidence.csv):", file=sys.stderr)
        print("\n".join(bad), file=sys.stderr)
        print("Use EA's name, keep the row's address token, or add ea-name-disputed=<evidence> "
              "to the row's notes when a matched caller, vtable slot or BFME1 witness says otherwise "
              "(a body that inlined a labelled callee carries that callee's label).",
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
