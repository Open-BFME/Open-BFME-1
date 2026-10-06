#!/usr/bin/env python3
"""Quality components per source file. Published one by one; never summed into a score.

A composite ratchet invites Goodhart (dummy functions raise functions-per-TU,
cosmetic names raise the name share, a helper hides an offset cast), so each
component is reported on its own, and a commit that makes one of them worse on
a file it touched becomes a queue item, not a refusal:

  rows               ledger rows whose source is this file (functions per TU)
  address_named      rows whose name is an address (Rva00401000, sub_..., FUN_...)
  offset_casts       raw pointer arithmetic: *(T*)((char*)p + 0x1C) and kin
  private_copies     class/struct bodies defined here whose name is also defined
                     in a header or in another unit (a private view of a shared type)
  escape_hatches     selectany, /alternatename, #pragma optimize, __emit,
                     present-unmatched, class-gate: allow, address-named globals
  tier_*             rows by name evidence tier: vendored / retail (export, RTTI,
                     string, vtable, BFME1/ZH donor cited) / address / unevidenced
  linked             link census status of the file (yes / no / absent)

Regressions on a touched file (any of address_named, offset_casts,
private_copies, escape_hatches, tier_unevidenced up; a new one-row file; linked
yes -> no) become `quality-regression` findings whose acceptance command is
`components.py check FILE --max COMPONENT=VALUE`.

  python3 tools/audit/components.py file PATH [--rev REV]
  python3 tools/audit/components.py commit SHA
  python3 tools/audit/components.py check PATH --max offset_casts=3 [--max ...]
  python3 tools/audit/components.py totals          # repo-wide, at the work tree
"""
import argparse
import collections
import functools
import json
import re
import sys

import common

OFFSET_CAST = re.compile(
    r"\(\s*(?:const\s+)?(?:unsigned\s+|signed\s+)?(?:char|BYTE|uint8_t|byte|int8_t)\s*\*\s*\)\s*"
    r"\(?\s*[\w>.\-]+\s*\)?\s*[+-]\s*(?:0x[0-9A-Fa-f]+|\d+)"
    r"|reinterpret_cast\s*<\s*(?:const\s+)?(?:unsigned\s+)?(?:char|BYTE|uint8_t)\s*\*\s*>\s*\([^)]*\)\s*[+-]\s*(?:0x[0-9A-Fa-f]+|\d+)")
CLASS_DEF = re.compile(
    r"^[ \t]*(?:template\s*<[^>]*>\s*)?(?:class|struct|union)\s+(?:__declspec\([^)]*\)\s+)?(\w+)\s*(?::[^;{()]*)?\{",
    re.MULTILINE)
HATCHES = re.compile(
    r"__declspec\s*\(\s*selectany\s*\)|/alternatename|#\s*pragma\s+optimize|\b__emit\b|present-unmatched"
    r"|class-gate:\s*allow|\bg_?[Rr]va[0-9A-Fa-f]{6,8}\b|\bg_[0-9A-Fa-f]{6,8}\b|\bDAT_[0-9A-Fa-f]{6,8}\b")
RETAIL_EVIDENCE = re.compile(r"(?i)\b(?:rtti|export|string|vtable|vftable|ea[_-]?evidence|bfme1|zh|donor|retail|"
                             r"exe-string|typeinfo|assert|ini)\b")
COMPONENTS = ("rows", "address_named", "offset_casts", "private_copies", "escape_hatches",
              "tier_vendored", "tier_retail", "tier_address", "tier_unevidenced", "linked")
WORSE_IF_UP = ("address_named", "offset_casts", "private_copies", "escape_hatches", "tier_unevidenced")


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.DOTALL)
    return re.sub(r"//[^\n]*", "", text)


def tier(row):
    notes = row.get("notes") or ""
    if "vendored=" in notes:
        return "vendored"
    if common.ADDRESS_NAME.search(row.get("name") or ""):
        return "address"
    if RETAIL_EVIDENCE.search(notes):
        return "retail"
    return "unevidenced"


@functools.lru_cache(maxsize=1)
def class_index():
    """class name -> set of files defining a body for it, over the work tree (cached by HEAD)."""
    head = common.git("rev-parse", "HEAD").strip()
    cache = common.STATE / "cache" / f"classes-{head}.json"
    data = common.load_json(cache, None)
    if data is None:
        data = collections.defaultdict(list)
        for path in common.git("ls-files", common.SOURCE_PREFIX).splitlines():
            if not common.is_source(path):
                continue
            try:
                text = (common.ROOT / path).read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            for name in set(CLASS_DEF.findall(strip_comments(text))):
                data[name].append(path)
        common.save_json(cache, data)
    canonical = set()
    for row in common.read_rows(common.show("HEAD", common.CANONICAL)):
        canonical.add(row.get("class") or row.get("name") or "")
    return {k: set(v) for k, v in data.items()}, canonical


def private_copies(path, text):
    index, canonical = class_index()
    count = 0
    for name in set(CLASS_DEF.findall(text)):
        others = index.get(name, set()) - {path}
        if name in canonical or any(o.lower().endswith((".h", ".hpp")) for o in others) or (
                others and not path.lower().endswith((".h", ".hpp"))):
            count += 1
    return count


@functools.lru_cache(maxsize=8)
def tracked_text(rev, path):
    if rev is None:
        full = common.ROOT / path
        return full.read_text(encoding="utf-8", errors="replace") if full.exists() else ""
    return common.show(rev, path) or ""


def rows_for(rev, path):
    """Ledger rows of one source at a revision, without parsing the whole ledger."""
    text = tracked_text(rev, common.LEDGER)
    header = text.split("\n", 1)[0]
    needle = f",{path},"
    lines = [line for line in text.splitlines() if needle in line]
    return [r for r in common.read_rows("\n".join([header, *lines])) if r.get("source") == path]


def linked_for(rev, path):
    text = tracked_text(rev, common.LINK_STATUS)
    for line in text.splitlines():
        if line.startswith(path + ","):
            return line.split(",")[1]
    return "absent"


def measure(path, text, rows, linked):
    code = strip_comments(text or "")
    mine = [r for r in rows if r.get("source") == path and r.get("status") == "matched"]
    tiers = collections.Counter(tier(r) for r in mine)
    return {
        "rows": len(mine),
        "address_named": sum(1 for r in mine if common.ADDRESS_NAME.search(r.get("name") or "")),
        "offset_casts": len(OFFSET_CAST.findall(code)),
        "private_copies": private_copies(path, code) if text else 0,
        "escape_hatches": len(HATCHES.findall(text or "")),
        **{f"tier_{t}": tiers.get(t, 0) for t in ("vendored", "retail", "address", "unevidenced")},
        "linked": linked,
    }


def file_components(path, rev=None):
    text = common.show(rev, path) if rev else tracked_text(None, path)
    return measure(path, text, rows_for(rev, path), linked_for(rev, path))


def regressions(before, after, existed):
    out = []
    for key in WORSE_IF_UP:
        if after[key] > before[key]:
            out.append((key, before[key], after[key]))
    if not existed and after["rows"] == 1 and not after["tier_vendored"]:
        out.append(("one_row_file", 0, 1))
    if before["linked"] == "yes" and after["linked"] == "no":
        out.append(("linked", "yes", "no"))
    return out


def commit_regressions(sha):
    """[(path, component, before, after)] for the source files one commit touched."""
    # the parent by id, so a newest-first walk reuses the ledger text it read as the previous child
    parent = common.git("rev-parse", f"{sha}^").strip()
    paths = [p for p in common.git("diff", "--name-only", "--no-renames", parent, sha).splitlines()
             if common.is_source(p)]
    out = []
    for path in paths:
        old, new = common.show(parent, path), common.show(sha, path)
        if new is None:
            continue
        before = measure(path, old, rows_for(parent, path), linked_for(parent, path))
        after = measure(path, new, rows_for(sha, path), linked_for(sha, path))
        out += [(path, key, b, a) for key, b, a in regressions(before, after, old is not None)]
    return out


def totals():
    rows = common.ledger_at()
    by_source = collections.defaultdict(list)
    for row in rows:
        by_source[row.get("source")].append(row)
    linked = {r["source"]: r.get("linked", "") for r in common.read_rows(tracked_text(None, common.LINK_STATUS))}
    agg = collections.Counter()
    files = 0
    for path in common.git("ls-files", common.SOURCE_PREFIX).splitlines():
        if not common.is_source(path):
            continue
        files += 1
        text = (common.ROOT / path).read_text(encoding="utf-8", errors="replace")
        values = measure(path, text, by_source.get(path, []), linked.get(path, "absent"))
        for key, value in values.items():
            if key == "linked":
                agg[f"linked_{value}"] += 1
            else:
                agg[key] += value
        agg["one_row_files"] += values["rows"] == 1
    agg["files"] = files
    agg["address_named_share_pct"] = round(100.0 * agg["address_named"] / max(agg["rows"], 1), 2)
    with_rows = len({r["source"] for r in rows if r.get("status") == "matched"})
    agg["rows_per_file_with_rows"] = round(agg["rows"] / max(with_rows, 1), 2)
    return dict(agg)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    f = sub.add_parser("file")
    f.add_argument("path")
    f.add_argument("--rev")
    sub.add_parser("commit").add_argument("sha")
    c = sub.add_parser("check")
    c.add_argument("path")
    c.add_argument("--max", action="append", default=[], help="COMPONENT=VALUE")
    sub.add_parser("totals")
    args = ap.parse_args(argv)
    if args.cmd == "file":
        print(json.dumps(file_components(args.path, args.rev), indent=1))
    elif args.cmd == "commit":
        for item in commit_regressions(args.sha):
            print("\t".join(map(str, item)))
    elif args.cmd == "totals":
        print(json.dumps(totals(), indent=1, sort_keys=True))
    else:
        values = file_components(args.path) if (common.ROOT / args.path).exists() else None
        if values is None:
            print(f"{args.path}: gone (accepted: the regression left with the file)")
            return 0
        bad = []
        for spec in args.max:
            key, _, limit = spec.partition("=")
            value = values.get(key)
            if key == "linked":
                if value != limit:
                    bad.append(f"linked={value} (want {limit})")
            elif key == "one_row_file":
                if values["rows"] == 1:
                    bad.append("still a one-row file")
            elif value is not None and value > int(limit):
                bad.append(f"{key}={value} > {limit}")
        print(f"{args.path}: " + ("; ".join(bad) if bad else "OK"))
        return 1 if bad else 0
    return 0


if __name__ == "__main__":
    sys.exit(main())
