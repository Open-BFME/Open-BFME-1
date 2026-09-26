#!/usr/bin/env python3
"""Git merge driver for append-mostly JSON list ledgers (name_corrections.json).

functions.csv, symbols.csv, deleted_rows.csv and re_attempts.log union-merge
(.gitattributes), so parallel appends never conflict. name_corrections.json
is a JSON array, which union merge would corrupt, and every agent that lands a
bank->source rename appends to its tail: on 2026-09-26 three landings pushed
within minutes of each other all stopped their rebases on the same `},` line.

This merges as a set of entries: the result is OURS, minus entries THEIRS
removed from BASE, plus entries THEIRS added, in THEIRS' order. Anything that is
not a JSON list on all three sides exits 1, and git leaves an ordinary conflict.

Registered per clone by tools/setup_hooks.sh and tools/setup_local_fleet.py:
  git config merge.jsonlist.driver "python3 tools/merge_json_list.py %O %A %B"
"""
import json
import re
import sys


def key(entry):
    return json.dumps(entry, sort_keys=True, ensure_ascii=False)


def load(path):
    raw = open(path, "rb").read()
    data = json.loads(raw.decode("utf-8-sig")) if raw.strip() else []
    if not isinstance(data, list):
        raise ValueError(f"{path} is not a JSON list")
    return raw, data


def merge(base, ours, theirs):
    old = {key(e) for e in base}
    removed = old - {key(e) for e in theirs}
    have = {key(e) for e in ours}
    kept = [e for e in ours if key(e) not in removed]
    return kept + [e for e in theirs if key(e) not in have and key(e) not in old]


def render(entries, like):
    """Serialise in the layout of `like` (the OURS bytes): indent and newline."""
    text = like.decode("utf-8-sig", errors="replace")
    m = re.search(r"\n( +)\S", text)
    indent = len(m.group(1)) if m else 1
    newline = "\r\n" if "\r\n" in text else "\n"
    out = json.dumps(entries, indent=indent, ensure_ascii=False).replace("\n", newline)
    return (out + newline).encode("utf-8")


def main(argv):
    if len(argv) != 3:
        print("usage: merge_json_list.py BASE OURS THEIRS", file=sys.stderr)
        return 2
    try:
        _, base = load(argv[0])
        ours_raw, ours = load(argv[1])
        _, theirs = load(argv[2])
    except (OSError, ValueError) as error:
        print(f"merge_json_list: {error}; leaving a conflict", file=sys.stderr)
        return 1
    with open(argv[1], "wb") as handle:
        handle.write(render(merge(base, ours, theirs), ours_raw))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
