"""How many gate failures are "retail inlined a forwarder we call out of line"?

The Buffer family is this shape. Our source calls `~Buffer` out of line; retail
calls `Buffer::Reset` directly, because `~Buffer`'s entire body is `{ Reset(); }`
and retail inlined it. The candidate list is irrelevant -- no pin can fix it,
because the two are different functions and retail simply never calls ours.

The signature, read straight out of the gate log and the ledger:

  * the failure says `retail calls 0xA (ledger: <name B>)`
  * the symbol WE emit at that site is a different name, and it has a matched row
  * so both are real, distinct, byte-matched functions

That last point is what separates this from an identity problem: nothing is
misnamed, our source is calling the wrong one of two functions that both exist.
"""
import collections
import csv
import re
import sys
from pathlib import Path

G = sys.argv[1] if len(sys.argv) > 1 else (
    "/tmp/claude-1000/-home-wacket-Projects-Open-BFME/"
    "5b41fcb8-7e71-4cc6-a3ea-e8a58497c1bb/scratchpad/gateB.log")

CALLS = re.compile(r"\+0x[0-9a-f]+ (\S+): retail calls (0x[0-9A-Fa-f]+)"
                   r"(?: -> body (0x[0-9A-Fa-f]+))? \(ledger: ([^;)]+)")

by_name, by_rva = {}, collections.defaultdict(list)
with open("targets/game/reverse/functions.csv", newline="") as fh:
    for row in csv.DictReader(fh):
        if row.get("status") != "matched":
            continue
        by_name.setdefault(row["name"], row)
        by_rva[row["target_rva"].upper()].append(row)

lines = Path(G).read_text(errors="replace").splitlines()
shapes = collections.Counter()
examples = collections.defaultdict(list)
current = None
for line in lines:
    if line.startswith("  FAIL") and "(" in line:
        current = line[line.index("(") + 1:line.rindex(")")]
        continue
    hit = CALLS.search(line)
    if not (hit and current):
        continue
    ours, target, body, ledger = hit.groups()
    # build.py prints "(ledger: <mangled name>, <free-text note>)". The note is
    # NOT part of the name, and treating it as one makes every annotated row look
    # unconverted: that reported 54 failures as blocked on the conversion lane
    # when the true number is zero, and hid 49 that are fixable in source.
    ledger = ledger.split(", ")[0].strip()
    mine = by_name.get(ours)
    theirs = by_name.get(ledger)
    if mine and theirs:
        # both sides are real, byte-matched functions: our source picked the
        # wrong one of two that exist.
        shapes["both functions exist and are matched -- source calls the wrong one"] += 1
        examples["both"].append((current, ours, ledger))
    elif mine and not theirs:
        shapes["we call a matched function; retail's target is not a matched row"] += 1
        examples["ours-only"].append((current, ours, ledger))
    elif theirs and not mine:
        shapes["retail's target is matched; the symbol we emit is not a row"] += 1
        examples["theirs-only"].append((current, ours, ledger))
    else:
        shapes["neither side is a matched row"] += 1
        examples["neither"].append((current, ours, ledger))

total = sum(shapes.values())
print(f"call-target failures examined: {total}")
for why, n in shapes.most_common():
    print(f"  {n:>4}  {why}")
for key, label in (("both", "SOURCE CALLS THE WRONG FUNCTION (fixable in source)"),):
    print(f"\n--- {label} ---")
    seen = set()
    for src, ours, ledger in examples[key]:
        k = (src, ours, ledger)
        if k in seen:
            continue
        seen.add(k)
        print(f"  {Path(src).name:<42} calls {ours[:44]}")
        print(f"  {'':<42} retail {ledger[:44]}")
