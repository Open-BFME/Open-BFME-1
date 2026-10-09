#!/usr/bin/env python3
"""Ledger facts the gate reads may change only through the tool that writes them.

Two kinds of fact, each with one writer:

  imp_pin   targets/game/reverse/symbols.csv: an `__imp_` pin (name, address). Writer:
            tools/import_binding.py pin / retire-pin.
  data_row  targets/game/reverse/data_rows.csv: an added or changed row (name,
            address, kind, size, section, source, status). Writer:
            tools/add_data_match.py. Deleting a row, or editing only its
            evidence/model text, is not refused.
  eh_label  targets/game/reverse/functions.csv: the funclet label (`$L1234`, the row
            name or its `object-symbol=`) of a row present before and after, keyed
            by target_rva. Writers: tools/eh_state_pins.py --fix and add_match.py
            --replace-existing/--replace-rva. SHADOW: an unstamped relabel prints a
            note and is never refused (kinds in SHADOW; drop it from that set to enforce).

A writer calls `stamp(kind, before, after)` with the file's bytes before and after
its write; the facts that differ go to a stamp file in this worktree's own git dir
(`git rev-parse --git-path bfme-gate-writers`). The pre-commit hook runs
`--staged` with this file AS OF HEAD (an edit cannot approve itself): every fact
the staged change makes against HEAD must be in the stamp, else the commit is
refused with the tool command to use. Merges (MERGE_HEAD) are skipped.
post-commit runs `--consume`: the stamps of each kind whose file the commit
touched are dropped, so an old stamp cannot cover a later hand edit.

  python3 tools/gate_writers.py --staged
  python3 tools/gate_writers.py --consume
"""
import csv
import json
import re
import subprocess
import sys

FILES = {
    "imp_pin": "targets/game/reverse/symbols.csv",
    "data_row": "targets/game/reverse/data_rows.csv",
    "eh_label": "targets/game/reverse/functions.csv",
}
# Kinds that only report. Enforcing one is deleting it here (one line).
SHADOW = {"eh_label"}
LABEL = re.compile(r"^\$L\d+$")
OBJECT_SYMBOL = re.compile(r"(?:^|;)object-symbol=([^;]+)")
TOOLS = {
    "eh_label": "python3 tools/eh_state_pins.py --source <file> --fix --model <you>",
    "imp_pin": "python3 tools/import_binding.py pin NAME ADDR (retail's IAT slot for it) or "
               "retire-pin NAME (nothing built still references it)",
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


def _label(f):
    if len(f) < 7:
        return None
    m = OBJECT_SYMBOL.search(f[6])
    name = m.group(1) if m else f[0]
    return name if LABEL.match(name) else None


def facts(kind, before, after):
    """The gate-read facts AFTER changes against BEFORE (bytes or text)."""
    removed, added = _changed(before, after)
    if kind == "eh_label":
        removed = [line for line in removed if "$L" in line]
        if not removed:
            return set()
        olds, news = {}, {}
        for side, lines in ((olds, removed), (news, added)):
            for f in _rows(lines):
                if len(f) > 2 and f[2].startswith("0x"):
                    side.setdefault(f"0x{int(f[2], 16):08X}", set()).add(_label(f))
        out = set()
        for rva in olds.keys() & news.keys():
            a, b = olds[rva] - {None}, news[rva] - {None}
            if a != b:
                out.add(f"{rva} {','.join(sorted(a)) or '-'} -> {','.join(sorted(b)) or '-'}")
        return out
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


def consume():
    """After a commit: drop the stamps of every kind whose file the commit
    touched, so an old stamp cannot cover a later hand edit."""
    path = stamp_path()
    names = set(_git("diff-tree", "--no-commit-id", "--name-only", "-r", "HEAD").stdout.decode().split())
    kinds = {kind for kind, rel in FILES.items() if rel in names}
    try:
        with open(path, encoding="utf-8") as handle:
            lines = handle.readlines()
    except (OSError, TypeError):
        return
    kept = []
    for line in lines:
        try:
            if json.loads(line)["kind"] in kinds:
                continue
        except (ValueError, KeyError, TypeError):
            continue
        kept.append(line)
    with open(path, "w", encoding="utf-8") as handle:
        handle.writelines(kept)


def main(argv):
    if argv[1:] == ["--consume"]:
        consume()
        return 0
    if argv[1:] != ["--staged"]:
        print(__doc__, file=sys.stderr)
        return 2
    if _git("rev-parse", "-q", "--verify", "MERGE_HEAD").returncode == 0:
        return 0
    found = staged_problems()
    for kind in sorted(SHADOW & found.keys()):
        for fact in found.pop(kind):
            print(f"gate_writers: shadow: {kind} {fact} in {FILES[kind]} would be refused; "
                  f"use {TOOLS[kind]}", file=sys.stderr)
    for kind, missing in found.items():
        print(f"gate_writers: FAIL {len(missing)} {kind} change(s) in {FILES[kind]} no tool wrote "
              f"in this worktree. Use: {TOOLS[kind]}", file=sys.stderr)
        for fact in missing[:12]:
            print(f"    {fact}", file=sys.stderr)
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
