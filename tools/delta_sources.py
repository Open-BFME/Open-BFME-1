#!/usr/bin/env python3
"""Print the source files whose functions.csv claims change between two states.

Row-set semantics: a row counts as delta only if its exact tuple is absent from
the old state — new claims and edited claims need byte-proof; deletions and
reorders (dedup_csv re-sorts the whole file) cannot break byte-truth and are
ignored. Used by the git hooks to byte-verify exactly what a commit or push
adds, instead of running the full multi-minute gate.

  --staged        HEAD vs the git index (pre-commit)
  --range A B     committed state A vs committed state B (pre-push)
  --pins          print instead the sources a reverse/symbols.csv PIN DELETION
                  can redden (see pin_deletion_sources)

Output: one repo-relative source path per line (empty output = no new claims).
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

ROOT = Path(__file__).resolve().parents[1]
LEDGER = "reverse/functions.csv"
PINS = "reverse/symbols.csv"
REL32 = 0x0014
LIB_SUFFIX = ".lib"


def text_at(spec):
    """File content at a git object spec, or "" where the path does not exist."""
    out = subprocess.run(["git", "-C", str(ROOT), "show", spec], capture_output=True)
    return out.stdout.decode("utf-8", errors="replace") if out.returncode == 0 else ""


def rows_at(spec):
    """Ledger rows at a git object spec (e.g. 'HEAD:reverse/...', ':reverse/...').
    Returns an empty set when the ledger does not exist there (new repo)."""
    return {tuple(r) for r in csv.reader(io.StringIO(text_at(spec))) if r and r[0] != "name"}


def dict_rows_at(spec):
    return [r for r in csv.DictReader(io.StringIO(text_at(spec))) if r.get("name")]


def pins_at(spec):
    """{(name, address)} pinned by reverse/symbols.csv at a git object spec."""
    pairs = set()
    for row in csv.DictReader(io.StringIO(text_at(spec))):
        address = (row.get("address") or "").strip()
        if row.get("name") and address:
            pairs.add((row["name"], int(address, 16)))
    return pairs


def lost_candidates(deleted, kept_pins, rows, thunks):
    """{address: {name}} — the name->address resolutions a pin deletion removes.

    load_symbol_map hands a name every address the ledger and symbols.csv pin
    for it, each expanded with its incremental-link thunks. A deleted pin only
    costs the name a candidate when nothing else still supplies that address: it
    can also arrive from a functions.csv row of the same name, from another pin,
    or as a thunk of either. Those survivors are subtracted here, so a deletion
    that changes no resolution scopes to nothing at all.
    """
    def expand(addresses):
        out = set()
        for address in addresses:
            out.add(address)
            out.update(thunks.get(address, ()))
        return out

    affected = {name for name, _ in deleted}
    survives = {name: set() for name in affected}
    for row in rows:
        if row["name"] in affected:
            survives[row["name"]].add(int(row["target_rva"], 16))
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


def pin_deletion_sources(old_spec, new_spec):
    """Sources whose byte-truth a reverse/symbols.csv pin deletion can break.

    The ordinary delta above reads functions.csv and nothing else, so a commit
    that only deletes pins presents an empty verify set — d27ae4b7b deleted
    1,599 pins, byte-verified two files, and reddened 612 rows. symbols.csv is
    an ADDITIVE candidate list and retail holds many ICF copies of one name, so
    removing a routing address does not remove a claim: it makes the REL32
    resolver walk to a different copy and emit the wrong displacement.

    Two filters, in this order, and neither is allowed to guess:

      1. RETAIL, exact. Only a site that literally encodes a lost address can
         change, so the .text scan bounds the blast radius with no build state.
      2. OUR OBJECT, narrowing. That site is only resolved through the deleted
         pin if the row's own relocation there names the deleted SYMBOL; the
         50 call sites of operator delete[] at 0x00881EF0 resolve through the
         matched ??_V@YAXPAX@Z row and do not care that ??3@YAXPAX@Z lost it.
         An object that is absent or provably stale is not evidence, so its row
         stays in the set rather than being dropped on a guess.
    """
    deleted = pins_at(f"{old_spec}:{PINS}") - pins_at(f"{new_spec}:{PINS}")
    if not deleted:
        # Said out loud so a green hook distinguishes "the question was asked
        # and the answer was none" from "this check never ran".
        print("pin deletions: none — no pin-derived source to verify", file=sys.stderr)
        return []
    rows = dict_rows_at(f"{new_spec}:{LEDGER}")
    lost = lost_candidates(deleted, pins_at(f"{new_spec}:{PINS}"), rows, build.build_call_thunks())
    log = (f"pin deletions: {len(deleted)} pin(s) over "
           f"{len({n for n, _ in deleted})} name(s); {len(lost)} resolution(s) lost")
    if not lost:
        print(log + " that nothing else supplies — no source to verify", file=sys.stderr)
        return []

    # Bucket every affected call site into the matched row that owns it. A site
    # outside every matched row is retail we do not claim yet: nothing to verify.
    owners = sorted((int(r["target_rva"], 16), int(r["target_size"]), i)
                    for i, r in enumerate(rows) if r["status"] == "matched")
    starts = [o[0] for o in owners]
    hits = {}
    for site, callee in call_sites(lost):
        index = bisect.bisect_right(starts, site) - 1
        if index >= 0 and site < owners[index][0] + owners[index][1]:
            hits.setdefault(owners[index][2], []).append((site, callee))

    # Grouped by object, so a TU that owns a thousand claimed rows is parsed
    # once and released before the next -- the pathological case here is 18,799
    # rows over 1,812 files, and holding every parse would be gigabytes.
    by_object = {}
    for index, sited in hits.items():
        row = rows[index]
        # A .lib row's every relocation site is masked out of the comparison
        # (compile_function: pre-link addends, library-internal callees), so the
        # symbol map is never consulted for it and no pin can move its bytes.
        if (ROOT / row["source"]).suffix.lower() == LIB_SUFFIX:
            continue
        by_object.setdefault(build.row_object(row), []).append((row, sited))

    sources, stale = set(), set()
    for obj, claims in by_object.items():
        source = ROOT / claims[0][0]["source"]
        if not object_is_current(source, obj):
            stale.update(row["source"] for row, _ in claims)
            sources.update(row["source"] for row, _ in claims)
            continue
        defined, rel32 = object_rel32(obj)
        for row, sited in claims:
            placed = defined.get(build.ledger_object_symbol(row))
            if placed is None:
                # The row's own symbol is not in the object this ledger row
                # names. Whatever that is, it is not evidence of safety.
                stale.add(row["source"])
                sources.add(row["source"])
                continue
            section, value = placed
            body = int(row["target_rva"], 16)
            # The relocation covers the 4-byte displacement, one byte past the
            # call/jmp opcode the retail scan found.
            if any(rel32.get((section, value + site - body + 1)) in lost[callee]
                   for site, callee in sited):
                sources.add(row["source"])

    print(f"{log}; {sum(len(v) for v in hits.values())} retail call site(s) in "
          f"{len(hits)} claimed row(s) -> {len(sources)} source(s) to verify "
          f"({len(stale)} kept because their object is missing or stale)", file=sys.stderr)
    return sorted(sources)


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true",
                      help="delta between HEAD and the staged ledger")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"),
                      help="delta between two committed refs/SHAs")
    parser.add_argument("--pins", action="store_true",
                        help="print the sources a symbols.csv pin deletion can redden")
    args = parser.parse_args()

    old_spec, new_spec = ("HEAD", "") if args.staged else args.range

    if args.pins:
        sources = pin_deletion_sources(old_spec, new_spec)
    else:
        old, new = rows_at(f"{old_spec}:{LEDGER}"), rows_at(f"{new_spec}:{LEDGER}")
        sources = sorted({r[4] for r in (new - old) if len(r) >= 5 and r[4]})

    # Hooks consume this via mapfile/<(...) - force LF-only output or
    # Windows text-mode stdout appends CR to every path and -f "$s" fails.
    sys.stdout.reconfigure(newline="\n")
    for s in sources:
        print(s)


if __name__ == "__main__":
    main()
