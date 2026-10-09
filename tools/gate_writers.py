#!/usr/bin/env python3
"""Ledger facts the gate reads may change only through the tool that writes them.

Two kinds of fact, each with one writer:

  imp_pin   targets/game/reverse/symbols.csv: an `__imp_` pin (name, address). No
            tool writes these: the import itself is repaired in source with
            tools/import_binding.py (apply/check), which needs no pin.
  data_row  targets/game/reverse/data_rows.csv: an added or changed row (name,
            address, kind, size, section, source, status). Writer:
            tools/add_data_match.py. Deleting a row, or editing only its
            evidence/model text, is not refused.

A writer calls `stamp(kind, before, after)` with the file's bytes before and after
its write; the facts that differ go to a stamp file in this worktree's own git dir
(`git rev-parse --git-path bfme-gate-writers`). The pre-commit hook runs
`--staged` with this file AS OF HEAD (an edit cannot approve itself): every fact
the staged change makes against HEAD must be in the stamp, else the commit is
refused with the tool command to use. Merges (MERGE_HEAD) are skipped.

  python3 tools/gate_writers.py --staged
"""
import csv
import json
import subprocess
import sys

FILES = {
    "imp_pin": "targets/game/reverse/symbols.csv",
    "data_row": "targets/game/reverse/data_rows.csv",
}
TOOLS = {
    "imp_pin": "no tool writes __imp_ pins: repair the import in source with "
               "python3 tools/import_binding.py apply <source>, then check <source>",
    "data_row": "python3 tools/add_data_match.py NAME ADDR --va|--rva SOURCE --model <you> "
                "--evidence ...  (to move a row: delete it, then add it with the tool)",
}


def _git(*args):
    return subprocess.run(["git", *args], capture_output=True)


def stamp_path():
    got = _git("rev-parse", "--git-path", "bfme-gate-writers")
    return got.stdout.decode().strip() if got.returncode == 0 and got.stdout.strip() else None


def _rows(lines):
    out = []
    for line in lines:
        try:
            out.append(next(csv.reader([line])))
        except (csv.Error, StopIteration):
            continue
    return out


def _changed(before, after):
    if isinstance(before, bytes):
        before = before.decode("utf-8", "replace")
    if isinstance(after, bytes):
        after = after.decode("utf-8", "replace")
    old = set((before or "").replace("\r\n", "\n").split("\n"))
    new = set((after or "").replace("\r\n", "\n").split("\n"))
    return [line for line in old - new if line], [line for line in new - old if line]


def facts(kind, before, after):
    """The gate-read facts AFTER changes against BEFORE (bytes or text)."""
    removed, added = _changed(before, after)
    if kind == "imp_pin":
        def pins(lines):
            got = set()
            for f in _rows(line for line in lines if line.startswith("__imp_")):
                try:
                    got.add(f"{f[0]},0x{int(f[1], 16):08X}")
                except (IndexError, ValueError):
                    got.add(",".join(f[:2]))
            return got
        old, new = pins(removed), pins(added)
        return {"-" + p for p in old - new} | {"+" + p for p in new - old}
    if kind == "data_row":
        def keys(lines):
            return {"|".join(f[:7]) for f in _rows(lines) if f and f[0] != "name"}
        return keys(added) - keys(removed)
    raise ValueError(kind)


def stamp(kind, before, after):
    """Record the facts a tool's own write made, for the pre-commit check."""
    path = stamp_path()
    made = facts(kind, before, after)
    if not path or not made:
        return made
    with open(path, "a", encoding="utf-8") as handle:
        for fact in sorted(made):
            handle.write(json.dumps({"kind": kind, "fact": fact}) + "\n")
    return made


def stamped():
    path = stamp_path()
    out = set()
    try:
        with open(path, encoding="utf-8") as handle:
            for line in handle:
                try:
                    entry = json.loads(line)
                    out.add((entry["kind"], entry["fact"]))
                except (ValueError, KeyError, TypeError):
                    continue
    except (OSError, TypeError):
        pass
    return out


def staged_problems():
    """{kind: [unstamped facts]} for the staged change against HEAD."""
    names = set(_git("diff", "--cached", "--name-only", "HEAD").stdout.decode().split())
    have = stamped()
    out = {}
    for kind, rel in FILES.items():
        if rel not in names:
            continue
        old, new = _git("show", f"HEAD:{rel}"), _git("show", f":{rel}")
        missing = sorted(f for f in facts(kind, old.stdout if old.returncode == 0 else b"",
                                          new.stdout if new.returncode == 0 else b"")
                         if (kind, f) not in have)
        if missing:
            out[kind] = missing
    return out


def main(argv):
    if argv[1:] != ["--staged"]:
        print(__doc__, file=sys.stderr)
        return 2
    if _git("rev-parse", "-q", "--verify", "MERGE_HEAD").returncode == 0:
        return 0
    found = staged_problems()
    for kind, missing in found.items():
        print(f"gate_writers: FAIL {len(missing)} {kind} change(s) in {FILES[kind]} no tool wrote "
              f"in this worktree. Use: {TOOLS[kind]}", file=sys.stderr)
        for fact in missing[:12]:
            print(f"    {fact}", file=sys.stderr)
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
