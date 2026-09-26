"""Consolidation candidates that merge_cluster cannot see.

merge_cluster works from `readable body of ...: <dest>` MARKERS, and every one of
its 52 ready clusters has donors that disagree on their `// cl:` line. But the
marker set is not the whole population: grouping by (directory, owning class)
straight off the ledger finds groups whose donors DO agree, because they were
written by the same lane into the same directory with the same flags.

A group qualifies only when every file in it shares one identical `// cl:` line
(that line is the TU's whole compile environment, flags and include search path),
none holds a __declspec(naked)/__emit body, and none declares a type another
member of the group also declares -- concatenating two TU-local shims for the
same type is a redefinition, not a merge.
"""
import collections
import csv
import os
import re
from pathlib import Path

METHOD = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@")
STRUCTOR = re.compile(r"^\?\?[01]([A-Za-z_]\w*)@@")
NAKED = re.compile(r"__declspec\s*\(\s*naked\s*\)|\b__emit\b|\b__asm\b")
CL = re.compile(r"^//\s*cl:(.*)$", re.M)
TYPE = re.compile(r"^[ \t]*(?:class|struct)[ \t]+([A-Za-z_]\w*)\b[^;{]*\{", re.M)

owners = collections.defaultdict(set)
with open("targets/game/reverse/functions.csv", newline="") as fh:
    for row in csv.DictReader(fh):
        if row.get("status") != "matched":
            continue
        src = row.get("source") or ""
        if not src.startswith(("game/GameEngine", "game/Libraries", "game/GameEngineDevice")):
            continue
        m = METHOD.match(row.get("name") or "") or STRUCTOR.match(row.get("name") or "")
        if m:
            owners[src].add(m.group(2) if m.re is METHOD else m.group(1))

single = {s: next(iter(c)) for s, c in owners.items() if len(c) == 1}
groups = collections.defaultdict(list)
for src, cls in single.items():
    groups[(os.path.dirname(src), cls)].append(src)

ok, blocked = [], collections.Counter()
for (directory, cls), files in sorted(groups.items()):
    if len(files) < 2:
        continue
    texts = {}
    for f in files:
        try:
            texts[f] = Path(f).read_text(encoding="utf-8", errors="replace")
        except OSError:
            pass
    if len(texts) < 2:
        continue
    if any(NAKED.search(t) for t in texts.values()):
        blocked["holds a naked/__emit donor"] += 1
        continue
    lines = {(CL.search(t).group(1).strip() if CL.search(t) else None) for t in texts.values()}
    if len(lines) > 1:
        blocked["donors disagree on `// cl:`"] += 1
        continue
    seen = collections.Counter()
    for t in texts.values():
        for name in {m.group(1) for m in TYPE.finditer(t)}:
            seen[name] += 1
    if any(v > 1 for v in seen.values()):
        blocked["two donors declare the same type"] += 1
        continue
    ok.append((len(texts), directory, cls, sorted(texts)))

ok.sort(reverse=True)
print(f"# mergeable groups: {len(ok)}  files: {sum(n for n, _, _, _ in ok)}  "
      f"would remove: {sum(n for n, _, _, _ in ok) - len(ok)}")
for why, n in blocked.most_common():
    print(f"# blocked {n:>5}  {why}")
for n, directory, cls, files in ok:
    print(f"{n}\t{cls}\t{directory}\t{','.join(files)}")
