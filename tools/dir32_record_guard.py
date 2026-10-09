#!/usr/bin/env python3
"""dir32_addresses.csv is evidence the gate reads, so a commit may not write it freely.

verify_dir32_addresses trusts a recorded (name, va) pair: every reference must
give the name that address. A hand-added line was therefore a free pass for a
new decorated name at any address (the red team's "wrong global" exploit), and
a hand-edited address moved every reference's expectation at once.

  * An address already recorded for a name may not change. A wrong record is
    retired (below), never rewritten in a commit that also moves the references.
  * A deleted line must be retired by tools/dir32_record.py, which writes a
    `Dir32-Retire: OLD 0x<VA> for NEW` trailer. Only commit-msg sees the
    message, so .githooks/commit-msg runs `--commit-msg FILE` with this file AS
    OF HEAD (an edit cannot approve itself) and re-checks, against the staged
    tree, the owner's two conditions (ruling 2026-10-09): NEW is ledger-owned
    at OLD's address (a data_rows.csv row at that VA, or a `?j_` row in
    functions.csv at that RVA) and recorded nowhere else, and OLD (decorated
    and bare) occurs nowhere under game/ or inputs/reference/shims/. Every
    deletion needs a trailer and every trailer a matching deletion.
  * An added line must be one the tool would accept for an unrecorded name:
    build.unrecorded_dir32_problem against the record as of the base
    revision, so the added lines cannot vouch for each other.

Usage: python3 tools/dir32_record_guard.py --staged [BASE]     (BASE defaults to HEAD)
       python3 tools/dir32_record_guard.py --commit-msg FILE     (deletions vs HEAD)

The --commit-msg path imports nothing from the tree: the hook pipes it from HEAD.
"""
import csv
import re
import subprocess
import sys
from pathlib import Path

if "__file__" in globals() and not __file__.startswith("<"):
    sys.path.insert(0, str(Path(__file__).resolve().parent))

REL = "targets/game/reverse/dir32_addresses.csv"
DATA_ROWS = "targets/game/reverse/data_rows.csv"
FUNCTIONS = "targets/game/reverse/functions.csv"
IMAGE_BASE = 0x400000
SOURCE_ROOTS = ("game/", "inputs/reference/shims/")
RETIRE_RE = re.compile(r"^Dir32-Retire:[ \t]*(\S+)[ \t]+0x([0-9A-Fa-f]{1,8})[ \t]+for[ \t]+(\S+)[ \t]*$",
                       re.MULTILINE)
TOOL = "python3 tools/dir32_record.py retire OLD --for NEW --msg <message file>"


def root():
    top = subprocess.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True)
    return top.stdout.strip() or "."


def git_show_text(spec):
    shown = subprocess.run(["git", "show", spec], cwd=root(), capture_output=True)
    return shown.stdout.decode("utf-8", "replace") if shown.returncode == 0 else None


def read_at(spec):
    text = git_show_text(spec)
    if text is None:
        return None
    return {row["name"]: int(row["va"], 16) for row in csv.DictReader(text.splitlines())}


def trailer(old, va, new):
    return f"Dir32-Retire: {old} 0x{va:08X} for {new}"


def parse_trailers(message):
    return [(m.group(1), int(m.group(2), 16), m.group(3)) for m in RETIRE_RE.finditer(message)]


def bare_identifier(name):
    """The identifier a decorated name spells: ?Foo@Bar@@3HA -> Foo, _g_x -> g_x."""
    if name.startswith("?"):
        head = name[1:].split("@", 1)[0]
    elif name.startswith("_"):
        head = name[1:]
    else:
        head = name
    return head if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", head) else None


def owners_at(va, tree=":"):
    """Ledger names that own retail VA in TREE (':' is the index): data rows at
    that VA and `?j_` function rows at that RVA."""
    out = set()
    for row in csv.DictReader((git_show_text(f"{tree}{DATA_ROWS}") or "").splitlines()):
        try:
            at = int(row["address"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        if row.get("address_kind") == "rva":
            at += IMAGE_BASE
        if at == va:
            out.add(row["name"])
    rva = va - IMAGE_BASE
    for line in (git_show_text(f"{tree}{FUNCTIONS}") or "").splitlines():
        if not line.startswith("?j_"):
            continue
        cols = line.split(",")
        try:
            if int(cols[2], 16) == rva:
                out.add(cols[0])
        except (IndexError, ValueError):
            continue
    return out


def source_mentions(name):
    """Indexed paths under game/ or the shims that spell NAME, decorated or bare."""
    hits = set()
    for needle, word in ((name, False), (bare_identifier(name), True)):
        if not needle:
            continue
        cmd = ["git", "grep", "--cached", "-l", "-F"] + (["-w"] if word else []) + ["-e", needle]
        got = subprocess.run(cmd + ["--", *SOURCE_ROOTS], cwd=root(), capture_output=True, text=True)
        hits.update(p for p in got.stdout.splitlines() if p)
    return sorted(hits)


def retire_problem(old_name, va, new_name, old, new):
    """None when OLD_NAME, recorded at VA in OLD, may be retired for NEW_NAME given
    the record NEW after the change, else why not. Ledgers and sources: the index."""
    if old.get(old_name) != va:
        where = f"0x{old[old_name]:08X}" if old_name in old else "nowhere"
        return f"{old_name} is recorded at {where}, not 0x{va:08X}"
    if new_name == old_name:
        return "NEW must differ from OLD"
    if new_name not in owners_at(va):
        return (f"{new_name} is not ledger-owned at 0x{va:08X}: it needs a data_rows.csv row "
                "at that VA (tools/add_data_match.py) or a ?j_ functions.csv row at that RVA")
    if new_name in new and new[new_name] != va:
        return f"{new_name} is recorded at 0x{new[new_name]:08X}, not 0x{va:08X}"
    mentions = source_mentions(old_name)
    if mentions:
        return (f"{old_name} (or {bare_identifier(old_name)}) still appears in "
                + ", ".join(mentions[:3]) + (f" (+{len(mentions) - 3} more)" if len(mentions) > 3 else ""))
    return None


def retire_problems(old, new, message):
    """Every deleted line needs a matching Dir32-Retire trailer whose conditions hold,
    and every trailer a deleted line."""
    deleted = {name: old[name] for name in old.keys() - new.keys()}
    claims = parse_trailers(message)
    out, named = [], set()
    for name, va, for_name in claims:
        named.add(name)
        if name not in deleted:
            out.append(f"trailer retires {name} but this commit does not delete its line")
        elif va != deleted[name]:
            out.append(f"trailer gives {name} 0x{va:08X}; the deleted line recorded 0x{deleted[name]:08X}")
        else:
            problem = retire_problem(name, va, for_name, old, new)
            if problem:
                out.append(f"{name} for {for_name}: {problem}")
    for name in sorted(deleted.keys() - named):
        out.append(f"{name},0x{deleted[name]:08X} deleted without a Dir32-Retire trailer; use {TOOL}")
    return out


def check_commit_msg(message_file):
    if subprocess.run(["git", "rev-parse", "-q", "--verify", "MERGE_HEAD"], cwd=root(),
                      capture_output=True).returncode == 0:
        return 0
    old, new = read_at(f"HEAD:{REL}"), read_at(f":{REL}")
    with open(message_file, encoding="utf-8", errors="replace") as handle:
        message = handle.read()
    old, new = old or {}, new or {}
    if not (old.keys() - new.keys()) and not parse_trailers(message):
        return 0
    found = retire_problems(old, new, message)
    if found:
        print(f"dir32_record_guard: FAIL {len(found)} retirement problem(s) in {REL}", file=sys.stderr)
        for line in found[:20]:
            print("    " + line, file=sys.stderr)
        return 1
    print(f"dir32_record_guard: OK ({len(old.keys() - new.keys())} line(s) retired)")
    return 0


def problems(old, new, symbol_map=None):
    import build
    out = []
    for name in sorted(old.keys() & new.keys()):
        if old[name] != new[name]:
            out.append(f"{name}: recorded 0x{old[name]:08X} rewritten to 0x{new[name]:08X}; "
                       f"retire the line instead ({TOOL})")
    added = sorted(new.keys() - old.keys())
    if added:
        identities = build.dir32_identities(old)
        if symbol_map is None:
            symbol_map = build.load_symbol_map()
        for name in added:
            problem = build.unrecorded_dir32_problem(name, new[name], identities, symbol_map)
            if problem:
                out.append(f"{name},0x{new[name]:08X} added: {problem}")
    return out


def main(argv):
    if len(argv) == 2 and argv[0] == "--commit-msg":
        return check_commit_msg(argv[1])
    if not argv or argv[0] != "--staged":
        sys.exit(__doc__)
    base = argv[1] if len(argv) > 1 else "HEAD"
    old, new = read_at(f"{base}:{REL}"), read_at(f":{REL}")
    if new is None:
        sys.exit(f"dir32_record_guard: {REL} is not in the index")
    found = problems(old or {}, new)
    if found:
        print(f"dir32_record_guard: FAIL {len(found)} change(s) to {REL} the gate did not make")
        for line in found[:20]:
            print("    " + line)
        return 1
    print(f"dir32_record_guard: OK ({len(old or {})} -> {len(new)} recorded names)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
