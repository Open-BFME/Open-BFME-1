#!/usr/bin/env python3
"""Print the source files whose functions.csv claims change between two states.

New and edited claims need byte-proof. Removing or reordering a callable name
can also remove a resolver candidate, so untouched callers of lost candidates
need verification. Used by the git hooks instead of running the full gate.

  --staged        HEAD vs the git index (pre-commit)
  --range A B     committed state A vs committed state B (pre-push)
  --pins          print instead the sources a targets/game/reverse/symbols.csv PIN DELETION
                  can redden (see pin_deletion_sources)

Default output: one repo-relative source path per line for legacy callers.
With --selectors, output typed ``source:<path>`` checks and exact
``row:<rva>:<size>:<name>`` byte-verification selectors.
"""
import argparse
import bisect
import csv
import io
import json
import os
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
import layout_history

ROOT = Path(__file__).resolve().parents[1]
LEDGER = "targets/game/reverse/functions.csv"
PINS = "targets/game/reverse/symbols.csv"
REL32 = 0x0014
LIB_SUFFIX = ".lib"


def text_at(spec):
    """File content at a git object spec, or "" where the path does not exist."""
    ref, path = spec.split(":", 1)
    old_path = {LEDGER: layout_history.OLD_LEDGER,
                PINS: layout_history.OLD_PINS}.get(path)
    if old_path:
        path = layout_history.path_at(ref, path, old_path, allow_missing=True, root=ROOT)
        if path is None:
            return ""
        spec = f"{ref}:{path}"
    out = subprocess.run(["git", "-C", str(ROOT), "show", spec], capture_output=True)
    return out.stdout.decode("utf-8", errors="replace") if out.returncode == 0 else ""


def rows_at(spec):
    """Ledger rows at a git object spec (e.g. 'HEAD:targets/game/reverse/...', ':targets/game/reverse/...').
    Returns an empty set when the ledger does not exist there (new repo)."""
    return {tuple(r) for r in csv.reader(io.StringIO(text_at(spec))) if r and r[0] != "name"}


def dict_rows_at(spec):
    rows = [r for r in csv.DictReader(io.StringIO(text_at(spec))) if r.get("name")]
    for row in rows:
        row["source"] = layout_history.canonical_source(row["source"])
    return rows


def row_candidates(rows):
    """Match load_symbol_map: the last function row supplies a name's body.

    All statuses provide candidates; object-symbol only locates emitted code.
    """
    return {row["name"]: int(row["target_rva"], 16) for row in rows}


def pins_at(spec):
    """{(name, address)} pinned by targets/game/reverse/symbols.csv at a git object spec."""
    pairs = set()
    for row in csv.DictReader(io.StringIO(text_at(spec))):
        name = row.get("name")
        address = (row.get("address") or "").strip()
        # A union merge can land a second copy of the header mid-file, and int()
        # on the literal "address" used to abort the whole run. The callers pipe
        # this through mapfile, so the abort became an EMPTY source list and the
        # pin-deletion half of the push gate passed by producing nothing.
        if name == "name" and address == "address":
            continue
        if name and address:
            pairs.add((name, int(address, 16)))
    return pairs


def lost_candidates(deleted, kept_pins, rows, thunks):
    """{address: {name}} — resolutions a row or pin deletion removes.

    load_symbol_map uses the last function row per name plus every symbols.csv
    pin, each expanded with its incremental-link thunks. A removed candidate
    matters only when no surviving provider supplies that same name/address.
    """
    def expand(addresses):
        out = set()
        for address in addresses:
            out.add(address)
            out.update(thunks.get(address, ()))
        return out

    affected = {name for name, _ in deleted}
    survives = {name: set() for name in affected}
    for name, address in row_candidates(rows).items():
        if name in affected:
            survives[name].add(address)
    for name, address in kept_pins:
        if name in affected:
            survives[name].add(address)
    survives = {name: expand(addresses) for name, addresses in survives.items()}

    lost = {}
    for name, address in deleted:
        for candidate in expand({address}) - survives[name]:
            lost.setdefault(candidate, set()).add(name)
    return lost


def call_sites(lost):
    """[(site rva, callee)] for every .text call/jmp encoding a lost address.

    Read out of the RETAIL image, never out of our objects: the displacement a
    row has to reproduce is retail's, so this is exactly the set of sites whose
    resolution the deletion can break, and computing it needs no build state.
    """
    data, sections = build.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    low, size, raw = text["rva"], text["size"], text["raw_pointer"]
    sites = []
    for opcode in (b"\xe8", b"\xe9"):
        position, end = raw, raw + size - 5
        while True:
            position = data.find(opcode, position, end)
            if position == -1:
                break
            site = (position - raw) + low
            callee = site + 5 + struct.unpack_from("<i", data, position + 1)[0]
            if callee in lost:
                sites.append((site, callee))
            position += 1
    return sites


def object_rel32(path):
    """({defined symbol: (section, value)}, {(section, offset): REL32 symbol}).

    One parse per object, through build.py's own cached COFF reader, because a
    gen_small TU carries tens of thousands of symbols and a per-row scan of them
    is quadratic over the thousand-plus rows such a TU owns.
    """
    stat = path.stat()
    data, sections, symbols = build._object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    defined = {}
    for symbol in symbols:
        if symbol["section"] > 0:
            defined.setdefault(symbol["name"], (symbol["section"], symbol["value"]))
    sites = {}
    for index, section in enumerate(sections, start=1):
        for r in range(section["reloc_count"]):
            offset = section["reloc_pointer"] + r * 10
            if build.u16(data, offset + 8) == REL32:
                sites[(index, build.u32(data, offset))] = symbols[build.u32(data, offset + 4)]["name"]
    return defined, sites


def object_is_current(source, obj):
    """True iff obj was compiled from exactly this source text and headers.

    build.compile_is_current's test minus its compile-command arm, which calls
    winepath per source to rebuild the command line: 2 wine subprocesses per TU
    is not something a commit hook may do, and a stale wineserver hangs it
    outright. Everything that decides which SYMBOL a relocation names — the
    source and every header it pulled — is still hashed, and a `False` here only
    ever KEEPS a source in the verify set.
    """
    sidecar = build._deps_sidecar(obj)
    if not obj.exists() or not sidecar.exists():
        return False
    try:
        meta = json.loads(sidecar.read_text())
    except (OSError, ValueError):
        return False
    if meta.get("source") != build._hash_file(str(source)):
        return False
    return all(build._hash_file(dep if os.path.isabs(dep) else str(ROOT / dep)) == digest
               for dep, digest in meta.get("deps", {}).items())


def row_selector(row):
    """Exact build selector for one ledger claim, independent of its source TU."""
    return (f"row:0x{int(row['target_rva'], 16):08X}:"
            f"{int(row['target_size'])}:{row['name']}")


def affected_row_indices(deleted, kept_pins, rows, reason):
    """Matched ledger rows whose byte-truth can change after candidate loss.

    Two filters, in this order, and neither is allowed to guess:

      1. RETAIL, exact. Only a site that literally encodes a lost address can
         change, so the .text scan bounds the blast radius with no build state.
      2. OUR OBJECT, narrowing. That site is only affected if the row's own
         relocation there names the symbol whose candidate disappeared; the
         50 call sites of operator delete[] at 0x00881EF0 resolve through the
         matched ??_V@YAXPAX@Z row and do not care that ??3@YAXPAX@Z lost it.
         An object that is absent or provably stale is not evidence, so its row
         stays in the set rather than being dropped on a guess. Return the
         exact row owners, so callers can verify those rows without requiring
         every unrelated sibling in a large generated TU to be green.
    """
    if not deleted:
        print(f"{reason}: none — no caller row to verify", file=sys.stderr)
        return []
    lost = lost_candidates(deleted, kept_pins, rows, build.build_call_thunks())
    log = (f"{reason}: {len(deleted)} candidate(s) over "
           f"{len({n for n, _ in deleted})} name(s); {len(lost)} resolution(s) lost")
    if not lost:
        print(log + " that nothing else supplies — no row to verify", file=sys.stderr)
        return []

    # Folded aliases can have different emitted symbols at the same range;
    # every overlapping owner needs its own object evidence before exclusion.
    owners = sorted((int(r["target_rva"], 16), int(r["target_size"]), i)
                    for i, r in enumerate(rows) if r["status"] == "matched")
    starts = [o[0] for o in owners]
    ends = []
    for start, size, _ in owners:
        ends.append(max(ends[-1] if ends else 0, start + size))
    hits = {}
    for site, callee in call_sites(lost):
        index = bisect.bisect_right(starts, site) - 1
        while index >= 0 and ends[index] > site:
            if site < owners[index][0] + owners[index][1]:
                hits.setdefault(owners[index][2], []).append((site, callee))
            index -= 1

    # Grouped by object, so a TU that owns a thousand claimed rows is parsed
    # once and released before the next -- the pathological case here is 18,799
    # rows over 1,812 files, and holding every parse would be gigabytes.
    by_object = {}
    for index, sited in hits.items():
        row = rows[index]
        # A .lib row's every relocation site is masked out of the comparison
        # (compile_function: pre-link addends, library-internal callees), so the
        # symbol map is never consulted for it, so candidate loss cannot move it.
        if (ROOT / row["source"]).suffix.lower() == LIB_SUFFIX:
            continue
        by_object.setdefault(build.row_object(row), []).append((index, row, sited))

    affected, stale = set(), set()
    for obj, claims in by_object.items():
        source = ROOT / claims[0][1]["source"]
        if not object_is_current(source, obj):
            stale.update(index for index, _, _ in claims)
            affected.update(index for index, _, _ in claims)
            continue
        defined, rel32 = object_rel32(obj)
        for index, row, sited in claims:
            placed = defined.get(build.ledger_object_symbol(row))
            if placed is None:
                # The row's own symbol is not in the object this ledger row
                # names. Whatever that is, it is not evidence of safety.
                stale.add(index)
                affected.add(index)
                continue
            section, value = placed
            body = int(row["target_rva"], 16)
            # The relocation covers the 4-byte displacement, one byte past the
            # call/jmp opcode the retail scan found.
            if any(rel32.get((section, value + site - body + 1)) in lost[callee]
                   for site, callee in sited):
                affected.add(index)

    print(f"{log}; {sum(len(v) for v in hits.values())} retail call site(s) in "
          f"{len(hits)} claimed row(s) -> {len(affected)} row(s) to verify "
          f"({len(stale)} kept because their object is missing or stale)", file=sys.stderr)
    return sorted(affected)


def affected_sources(deleted, kept_pins, rows, reason):
    """Source-granularity view retained for diagnostics and compatibility."""
    return sorted({rows[index]["source"] for index in
                   affected_row_indices(deleted, kept_pins, rows, reason)})


def pin_deletion_sources(old_spec, new_spec):
    kept = pins_at(f"{new_spec}:{PINS}")
    deleted = pins_at(f"{old_spec}:{PINS}") - kept
    return affected_sources(deleted, kept, dict_rows_at(f"{new_spec}:{LEDGER}"),
                            "pin deletions")


def function_delta_sources(old_spec, new_spec):
    old = dict_rows_at(f"{old_spec}:{LEDGER}")
    new = dict_rows_at(f"{new_spec}:{LEDGER}")
    old_rows = {tuple(row.items()) for row in old}
    sources = {row["source"] for row in new
               if row.get("source") and tuple(row.items()) not in old_rows}
    deleted = set(row_candidates(old).items()) - set(row_candidates(new).items())
    if deleted:
        sources.update(affected_sources(deleted, pins_at(f"{new_spec}:{PINS}"), new,
                                        "function candidate losses"))
    return sorted(sources)


def function_delta_selectors(old_spec, new_spec):
    """Typed source checks plus exact matched-row build selectors for hook use."""
    old = dict_rows_at(f"{old_spec}:{LEDGER}")
    new = dict_rows_at(f"{new_spec}:{LEDGER}")
    old_rows = {tuple(row.items()) for row in old}
    selected = [row for row in new
                if row.get("status") == "matched" and tuple(row.items()) not in old_rows]
    deleted = set(row_candidates(old).items()) - set(row_candidates(new).items())
    if deleted:
        selected.extend(new[index] for index in affected_row_indices(
            deleted, pins_at(f"{new_spec}:{PINS}"), new, "function candidate losses"))
    return typed_selectors(selected)


def pin_deletion_selectors(old_spec, new_spec):
    kept = pins_at(f"{new_spec}:{PINS}")
    deleted = pins_at(f"{old_spec}:{PINS}") - kept
    rows = dict_rows_at(f"{new_spec}:{LEDGER}")
    selected = [rows[index] for index in affected_row_indices(
        deleted, kept, rows, "pin deletions")]
    return typed_selectors(selected)


def typed_selectors(rows):
    """Emit each selected row's source for cleanliness checks and exact row for build."""
    selectors = set()
    for row in rows:
        if row.get("source"):
            selectors.add(f"source:{row['source']}")
        selectors.add(row_selector(row))
    return sorted(selectors)


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true",
                      help="delta between HEAD and the staged ledger")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"),
                      help="delta between two committed refs/SHAs")
    parser.add_argument("--pins", action="store_true",
                        help="analyze symbols.csv pin deletions")
    parser.add_argument("--selectors", action="store_true",
                        help="emit source:<path> and exact row:<rva>:<size>:<name> selectors")
    args = parser.parse_args()

    old_spec, new_spec = ("HEAD", "") if args.staged else args.range

    if args.selectors and args.pins:
        selectors = pin_deletion_selectors(old_spec, new_spec)
    elif args.selectors:
        selectors = function_delta_selectors(old_spec, new_spec)
    elif args.pins:
        selectors = pin_deletion_sources(old_spec, new_spec)
    else:
        selectors = function_delta_sources(old_spec, new_spec)

    # Hooks read paths line by line: force LF-only output or
    # Windows text-mode stdout appends CR to every path and -f "$s" fails.
    sys.stdout.reconfigure(newline="\n")
    for s in selectors:
        print(s)


if __name__ == "__main__":
    main()
