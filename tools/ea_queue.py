#!/usr/bin/env python3
"""Rename work whose target EA's own name fixes (targets/game/reverse/ea_evidence.csv).

A matched C++ row is a candidate when EA's name for its address is strongly paired, one row
claims the address, and the row's name is not EA's, the export, a Zero Hour name or vendored.
Items, each with a fixed target:
  method  same class, another method name: rename the method (one row)
  move    the row's class is a real Zero Hour class but EA puts the body in another class:
          re-home that one body (one row)
  class   the class is a stand-in or invented (Rva000C97C0Player, BfmeThingBE): rename the
          class to EA's, with every member. Served only when the members' labels agree, and a
          class of more than two rows also needs a second label or its own name to contain EA's
          (BfmeAptScreenInGameChat -> AptInGameChat): one inherited label would rename them all
Never queued: a method name other classes also use (`xfer` is in 510 files; renaming it by word
renames them all); a virtual method outside a whole-class rename (renaming one override detaches it
from its base's slot, and the byte gate compares code, not vtables); a free function EA names as
a member (the calling convention changes); a structor EA labels as a method (usually a label the
body inherited from a callee it inlined). Dumps take EA's name when converted. Folding strays
into their EA file waits for header adoption: 95% redeclare a type their target already has.

    python3 tools/ea_queue.py              # the whole queue
    python3 tools/ea_queue.py next         # one unclaimed item, with every file to edit

An item that cannot land goes in targets/game/reverse/ea_rename_blocked.tsv (0xRVA<TAB>reason),
and the queue then skips it.
"""
import argparse
import collections
import csv
import random
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
from ea_evidence import plain  # noqa: E402
from ea_name_guard import zh_methods  # noqa: E402

REVERSE = ROOT / "targets/game/reverse"
BLOCKED = REVERSE / "ea_rename_blocked.tsv"
EVIDENCE_FILE = "targets/game/reverse/identity_evidence/ea-worldbuilder-labels.md"
MEMBER = re.compile(r"\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@(.)")
STRUCTOR = re.compile(r"\?\?(?:([01])|_[EG])([A-Za-z_]\w*)@@(.)")


def shape(name):
    """(class, method or None for a structor, virtual?) of a simple member symbol, else None."""
    m = STRUCTOR.match(name)
    if m:
        return m.group(2), None, m.group(3) in "UME"
    m = MEMBER.match(name)
    return (m.group(2), m.group(1), m.group(3) in "UME") if m else None


def items(ea, rows_at, exports, zh, blocked):
    """Fixed-target items: dicts with kind, rows [(rva, name, new_name, want)], old, new."""
    single, stand_in = [], collections.defaultdict(list)
    classes_of = collections.defaultdict(set)
    for rs in rows_at.values():
        for r in rs:
            s = shape(r["name"])
            if s and s[1]:
                classes_of[s[1]].add(s[0])
    for rva, (want, route, basis) in sorted(ea.items()):
        rows = rows_at.get(rva, [])
        if basis != "strong" or len(rows) != 1 or rva in blocked:
            continue
        r = rows[0]
        name, source = r["name"], r["source"]
        if ("vendored=" in (r["notes"] or "") or name in exports.get(rva, ()) or build.is_scaffold_row(r)
                or not source.endswith((".cpp", ".h")) or source.startswith("game/gen_")):
            continue
        have, s = plain(name), shape(name)
        if not have or not s or have.lower() == want.lower():
            continue
        cls, method, virtual = s
        if method and method.lower() in zh.get(cls.lower(), ()):
            continue                              # a Zero Hour name: a dispute, not a rename
        want_cls, want_method = want.split("::")
        if (method is None) != (want_method.lstrip("~") == want_cls):
            continue                              # structor versus method
        real_class = cls.lower() in zh
        if cls.lower() == want_cls.lower() or real_class:
            if not virtual and classes_of[method] == {cls}:
                kind = "method" if cls.lower() == want_cls.lower() else "move"
                single.append(dict(kind=kind, old=method if kind == "method" else cls,
                                   new=want_method if kind == "method" else want_cls,
                                   rows=[(rva, name, want)], source=source))
        else:
            stand_in[cls].append((rva, name, want, source))
    out = [dict(i, rows=[(rva, n, rename(n, i["kind"], i["old"], i["new"], w), w) for rva, n, w in i["rows"]])
           for i in single]
    for cls, labelled in stand_in.items():
        targets = {w.split("::")[0] for _, _, w, _ in labelled}
        if len(targets) != 1:
            continue
        new = targets.pop()
        want_at = {rva: w for rva, _, w, _ in labelled}
        members = sorted((rva, r["name"]) for rva, rs in rows_at.items() for r in rs
                         if (shape(r["name"]) or ("",))[0] == cls)
        if any(rva in blocked or len(rows_at[rva]) != 1 for rva, _ in members):
            continue
        corroborated = len(labelled) >= 2 or new.lower().removeprefix("apt") in cls.lower()
        if len(members) > 2 and not corroborated:
            continue
        out.append(dict(kind="class", old=cls, new=new, source=labelled[0][3],
                        rows=[(rva, n, rename(n, "class", cls, new, want_at.get(rva)), want_at.get(rva))
                              for rva, n in members]))
    return out


def rename(name, kind, old, new, want):
    """The row's symbol with EA's names, spelled as the row spells it; the compiler has the last word."""
    if kind == "method":
        return name.replace(f"?{old}@", f"?{new}@", 1)
    renamed = re.sub(rf"(\?\?_[GE]|\?\?[01]|[@?VU]){re.escape(old)}@", rf"\g<1>{new}@", name)
    m = MEMBER.match(renamed)
    if want and m and not STRUCTOR.match(renamed):
        renamed = f"?{want.split('::')[1]}@" + renamed[len(m.group(1)) + 2:]
    return renamed


def load():
    ea = {}
    with open(REVERSE / "ea_evidence.csv", encoding="utf-8", newline="") as f:
        for r in csv.DictReader(f):
            if r["kind"] == "name":
                ea[int(r["rva"], 16)] = (r["value"], r["route"], r["basis"])
    rows_at = collections.defaultdict(list)
    with open(REVERSE / "functions.csv", encoding="utf-8", errors="replace", newline="") as f:
        for r in csv.DictReader(f):
            if r["status"] == "matched" and r["target_rva"].startswith("0x"):
                rows_at[int(r["target_rva"], 16)].append(r)
    exports = collections.defaultdict(set)
    with open(REVERSE / "exports.csv", encoding="utf-8", newline="") as f:
        for e in csv.DictReader(f):
            if e["kind"] == "code":
                exports[int(e["target_rva"] or e["rva"], 16)].add(e["name"])
    blocked = set()
    if BLOCKED.exists():
        blocked = {int(l.split("\t")[0], 16) for l in BLOCKED.read_text(encoding="utf-8").splitlines() if l.strip()}
    return ea, rows_at, exports, zh_methods(), blocked


def mentions(identifier):
    if not shutil.which("rg"):
        sys.exit("ea_queue: ripgrep (rg) is required to find every file naming the old symbol")
    out = subprocess.run(["rg", "-lw", "--no-messages", identifier, "game"], cwd=ROOT,
                         capture_output=True, text=True)
    if out.returncode not in (0, 1):
        sys.exit(f"ea_queue: rg failed: {out.stderr}")
    return sorted(out.stdout.split())


def show(item, rows_at):
    files = mentions(item["old"])
    rvas = " ".join(f"0x{rva:08X}" for rva, *_ in item["rows"])
    print(f"EA rename ({item['kind']}): {item['old']} -> {item['new']}, {len(item['rows'])} row(s)")
    for rva, name, new_name, want in item["rows"]:
        print(f"  0x{rva:08X} {name}\n             -> {new_name}{'  (EA: ' + want + ')' if want else ''}")
    print(f"  rename {item['old']} -> {item['new']} in every file below. Callers declare the old symbol\n"
          f"  too, and a caller left behind goes byte-red the next time it builds:")
    for f in files:
        print(f"    {f}")
    if item["kind"] != "method":
        print(f"  if the hook says a TU now redeclares {item['new']}, run python3 tools/adopt_header.py --fix-staged")
    print(f"  steps:\n    python3 tools/claims.py claim {rvas}\n    edit every file above, then land each row"
          f" (add_match rewrites the ledger row, then byte-verifies its source):")
    for rva, name, new_name, _ in item["rows"]:
        r = rows_at[rva][0]
        print(f"    python3 tools/add_match.py '{new_name}' 0x{rva:08X} {r['target_size']} {r['source']} "
              f"--model $BFME_MODEL --replace-rva 0x{rva:08X} --correct-identity '{name}' "
              f"--identity-evidence {EVIDENCE_FILE}")
    sources = {rows_at[rva][0]["source"] for rva, *_ in item["rows"]}
    rest = [f for f in files if f not in sources]
    if rest:
        print(f"    ./build.sh {' '.join(rest)}")
    print(f"    (use the spelling the compiler emits where it differs), rename the symbols in\n"
          f"    targets/game/reverse/symbols.csv, python3 tools/pin_consistency.py --check, commit together\n"
          f"  cannot land? append 0xRVA<TAB>reason to {BLOCKED.relative_to(ROOT)} and release the claim")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("command", nargs="?", choices=("list", "next"), default="list")
    args = ap.parse_args()
    ea, rows_at, *rest = load()
    queue = items(ea, rows_at, *rest)
    if args.command == "list":
        for i in queue:
            rva, name, _, want = i["rows"][0]
            print(f"{i['kind']:6} {len(i['rows']):2} row(s)  0x{rva:08X} {name[:52]:52} -> {i['new']}")
        print(f"{len(queue)} items, {sum(len(i['rows']) for i in queue)} rows: "
              f"{dict(collections.Counter(i['kind'] for i in queue))}")
        return 0
    import eligibility
    busy = eligibility.busy_rvas()
    free = [i for i in queue if not any(f"0x{rva:08x}" in busy for rva, *_ in i["rows"])]
    if not free:
        print(f"No EA renames left ({len(queue)} queued, all claimed).")
        return 0
    show(random.choice(free), rows_at)
    return 0


if __name__ == "__main__":
    sys.exit(main())
