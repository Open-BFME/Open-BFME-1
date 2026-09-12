#!/usr/bin/env python3
"""Place vendored Zero Hour code in BFME retail .text by masked-byte search.

BFME 1 and Generals: Zero Hour are both SAGE/W3D games built with the same
compiler, so a ZH translation unit frequently emits function bodies that are
byte-identical to BFME's. This sweep compiles the vendored tree, carves each
function COMDAT out of the objects, blanks every relocation slot -- those four
bytes hold link-time addresses two different executables cannot be expected to
agree on -- and searches .text for a placement of what is left.

  compile     build ZH translation units into the sweep object cache
  match       carve and place every COMDAT          -> build/zh_sweep/match.json
  land        append ledger rows for placements that survive filtering
  land-multi  report which gen-dump rows an exact-MULTI placement could supersede
  packets     write conversion work packets for near misses at unclaimed addresses

A placement is evidence of identical CODE, which is not the same as evidence of
identity: `land` drops every placement that overlaps ground another row already
claims, that carries a compiler-local label instead of a name, or whose name the
ledger already spends at another address. Search is uncapped on purpose -- a
capped needle scan can miss the second placement of a body and report an
ambiguous match as a unique one.
"""
import argparse
import bisect
import csv
import hashlib
import json
import re
import struct
import subprocess
import sys
import textwrap
from collections import Counter, defaultdict, namedtuple
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import boundary_validator
import build

ROOT = build.ROOT
ZH = build.ZH_REFERENCE_ROOT
OBJ_DIR = ROOT / "build" / "spike_zh"
OUT_DIR = ROOT / "build" / "zh_sweep"
MATCH_JSON = OUT_DIR / "match.json"
PACKET_DIR = ROOT / "reverse" / "zh_sweep" / "packets"

MIN_FUNC = 24           # under this, a body is a stub that places all over .text
SEARCHABLE = 10         # a body whose longest reloc-free run is shorter has no needle
MIN_NEEDLE = 4          # under this a run matches so much of .text it is pure noise
NEAR_ALIGN = 0.85       # near miss worth a work packet
PAD_SCAN = 0x2000       # how far past an address to look for the int3 run that ends it
DIR32, REL32 = 0x0006, 0x0014
CODE_SECTION = 0x00000020       # IMAGE_SCN_CNT_CODE

# The subtrees the sweep compiles, in the order it compiles them. Their split is
# what build.source_needs_stlport keys on: the WWVegas libraries build against
# MSVC's own STL, the GameEngine trees need STLport.
SUBTREES = [
    "Libraries/Source/WWVegas/WW3D2",
    "Libraries/Source/WWVegas/WWMath",
    "Libraries/Source/WWVegas/WWLib",
    "GameEngine/Source/GameLogic",
    "GameEngine/Source/Common",
    "GameEngine/Source/GameClient",
    # BFME links all four of these too, so their bodies are in retail .text the
    # same way GameLogic's are; leaving them out was costing the sweep a quarter
    # of its reach for nothing.
    "GameEngineDevice/Source",
    "GameEngine/Source/GameNetwork",
    "Libraries/Source/WWVegas/wwshade",
    "Libraries/Source/WWVegas/WWAudio",
]


def object_stem(source):
    """Sweep cache name for a ZH source: its last three path parts.

    Objects built by the original spike are named this way and are expensive to
    reproduce (a 400-TU wine sweep), so the naming stays as they left it.
    zh_sources() proves it stays one-to-one over the tree.
    """
    return "_".join(Path(source).with_suffix("").parts[-3:])


def zh_sources():
    """Sweep cache name -> repo-relative ZH source, proven unambiguous."""
    table = {}
    for path in sorted(ZH.rglob("*.cpp")):
        relative = path.relative_to(ROOT)
        stem = object_stem(relative)
        if stem in table:
            raise SystemExit(
                f"zh_sweep: object stem {stem!r} names two sources ({table[stem]} and "
                f"{relative}); the cache cannot say which object came from which")
        table[stem] = relative.as_posix()
    return table


def object_source(obj, sources):
    stem = obj.name[: -len(".obj")].removesuffix(".stl")
    source = sources.get(stem)
    if source is None:
        raise SystemExit(f"zh_sweep: {obj.name} has no source in the ZH tree — the object "
                         "cache holds something this sweep did not build")
    return source


def carve(data):
    """Yield (symbol, body, relocs) per function COMDAT of a COFF object.

    relocs are (offset, type, callee) restricted to the two i386 kinds whose
    bytes are a link-time address. Only symbols at offset zero of a code section
    are taken: those are whole COMDAT bodies, so the section size is the body
    size, with no guessing about where the next function starts.
    """
    machine, section_count, _, symbol_table, symbol_count, optional, _ = \
        struct.unpack_from("<HHIIIHH", data, 0)
    if machine != 0x14C:
        return
    sections = []
    for index in range(section_count):
        offset = 20 + optional + 40 * index
        name, _, _, raw_size, raw_pointer, reloc_pointer, _, reloc_count, _, characteristics = \
            struct.unpack_from("<8sIIIIIIHHI", data, offset)
        sections.append((name.rstrip(b"\0").decode(errors="replace"), raw_size,
                         raw_pointer, reloc_pointer, reloc_count, characteristics))
    strings = symbol_table + symbol_count * 18

    def name_at(offset):
        raw = data[offset : offset + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            return data[start : data.index(b"\0", start)].decode(errors="replace")
        return raw.rstrip(b"\0").decode(errors="replace")

    symbols, names, index = [], [], 0
    while index < symbol_count:
        offset = symbol_table + 18 * index
        value, section, kind, storage, aux = struct.unpack_from("<IhHBB", data, offset + 8)
        symbols.append((name_at(offset), value, section, kind, storage))
        # relocations index the raw table, so the auxiliary records a symbol
        # carries have to keep their slots in the name lookup
        names += [symbols[-1][0]] + [""] * aux
        index += 1 + aux

    for name, value, section, kind, storage in symbols:
        if section <= 0 or value != 0 or kind != 0x20 or storage not in (2, 3):
            continue
        section_name, raw_size, raw_pointer, reloc_pointer, reloc_count, characteristics = \
            sections[section - 1]
        if not section_name.startswith(".text") or not characteristics & CODE_SECTION:
            continue
        relocs = []
        for r in range(reloc_count):
            address, symbol_index, kind = struct.unpack_from("<IIH", data, reloc_pointer + 10 * r)
            if kind in (DIR32, REL32):
                relocs.append((address, kind, names[symbol_index]))
        yield name, data[raw_pointer : raw_pointer + raw_size], sorted(relocs)


def mask(body, relocs):
    """The body with every relocation slot blanked, plus which bytes were blanked."""
    masked, holes = bytearray(body), bytearray(len(body))
    for offset, _, _ in relocs:
        for index in range(offset, min(offset + 4, len(body))):
            masked[index] = 0
            holes[index] = 1
    return bytes(masked), bytes(holes)


def needles(holes, count=2):
    """Offsets and lengths of the longest reloc-free runs — the searchable parts."""
    runs, start = [], None
    for index, hole in enumerate(bytes(holes) + b"\1"):
        if not hole and start is None:
            start = index
        elif hole and start is not None:
            runs.append((index - start, start))
            start = None
    runs.sort(reverse=True)
    return runs[:count]


def placements(text, body, masked, holes):
    """Every offset in .text where the unmasked bytes of `body` appear.

    Uncapped: a limit on hits per needle silently turns a body that appears
    twice into a unique placement, which is exactly the error that would let an
    ICF-folded twin be landed under the wrong address.
    """
    found = set()
    runs = needles(holes)
    if not runs or runs[0][0] < SEARCHABLE:
        return found
    for length, offset in runs:
        if length < MIN_NEEDLE:
            continue
        needle = masked[offset : offset + length]
        position = text.find(needle)
        while position != -1:
            candidate = position - offset
            if 0 <= candidate <= len(text) - len(body):
                found.add(candidate)
            position = text.find(needle, position + 1)
    return found


def alignment(window, masked, holes):
    same = sum(1 for index in range(len(masked)) if holes[index] or window[index] == masked[index])
    return same / len(masked)


def retail_text():
    data = build.EXE.read_bytes()
    section = next(s for s in build.pe_sections(data) if s["name"] == ".text")
    return section["rva"], data[section["raw_pointer"] : section["raw_pointer"] + section["size"]]


def merged_claims():
    """Matched retail ranges, merged, plus a true overlap test over them.

    Containment ("is this whole body inside one claim?") is not the question a
    double-claim check asks: a body that starts inside a claim and runs past its
    end contains bytes another row already owns, and passes a containment test.

    Matched rows only, matching check_csv's overlap rule: an unmatched row is a
    hypothesis about an address, not proof that the ground is spoken for.

    A gen-dump row is not a claim for this purpose. It holds retail's own bytes
    under a synthetic name -- a boundary and no source -- which is exactly the
    code a Zero Hour packet is worth writing for. Counting dumps as claims made
    do_packets blind to 112 of its own best leads and, because it wipes the
    directory before rewriting, silently deleted the packets already written for
    them. build.load_claim_rows owns that rule: filtering on the Code/gen_asm/
    path instead, as this did, still hid the 349 dumps outside that directory.
    """
    spans = []
    for row in build.load_claim_rows(counting_dumps=False, matched_only=True):
        start = int(row["target_rva"], 16)
        spans.append((start, start + int(row["target_size"])))
    spans.sort()
    merged = []
    for start, end in spans:
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    starts = [start for start, _ in merged]

    def overlaps(rva, size):
        index = bisect.bisect_right(starts, rva) - 1
        if index >= 0 and merged[index][1] > rva:
            return True
        index = bisect.bisect_left(starts, rva)
        return index < len(merged) and merged[index][0] < rva + size

    return overlaps


def do_compile(args):
    sources = []
    for subtree in SUBTREES:
        found = sorted((ZH / subtree).rglob("*.cpp"))
        if args.limit and len(found) > args.limit:
            step = len(found) / args.limit
            found = [found[int(i * step)] for i in range(args.limit)]
        sources += found
    OBJ_DIR.mkdir(parents=True, exist_ok=True)
    built = failed = cached = 0
    for source in sources:
        obj = OBJ_DIR / (object_stem(source.relative_to(ROOT))
                         + (".stl" if build.source_needs_stlport(source) else "") + ".obj")
        if obj.exists() and not args.force:
            cached += 1
            continue
        try:
            build.compile_source(source, obj)
            built += 1
        except SystemExit:
            # A ZH TU that will not compile is the expected minority (the sweep
            # runs at ~95%), not a reason to abandon the other 400.
            failed += 1
            print(f"  compile FAILED {source.relative_to(ROOT)}", flush=True)
    print(f"compile: {built} built, {cached} cached, {failed} failed "
          f"of {len(sources)} translation unit(s)")


def do_match(args):
    text_rva, text = retail_text()
    overlaps = merged_claims()
    sources = zh_sources()
    records, seen = [], set()
    for obj in sorted(OBJ_DIR.glob("*.obj")):
        source = object_source(obj, sources)
        for name, body, relocs in carve(obj.read_bytes()):
            if len(body) < MIN_FUNC or name in seen:
                continue
            seen.add(name)
            masked, holes = mask(body, relocs)
            runs = needles(holes)
            record = {"sym": name, "obj": obj.name, "source": source,
                      "size": len(body), "relocs": len(relocs)}
            exact, best, best_align = [], None, 0.0
            for candidate in placements(text, body, masked, holes):
                align = alignment(text[candidate : candidate + len(body)], masked, holes)
                if align == 1.0:
                    exact.append(candidate)
                if align > best_align:
                    best_align, best = align, candidate
            if len(exact) == 1:
                record["rva"] = text_rva + exact[0]
                record["bucket"] = ("exact-unique-claimed"
                                    if overlaps(record["rva"], len(body))
                                    else "exact-unique-unclaimed")
            elif len(exact) > 1:
                record["bucket"] = "exact-multi"
                record["hits"] = len(exact)
            elif best is not None:
                record["rva"] = text_rva + best
                record["bucket"] = "near"
                record["align"] = round(best_align, 3)
                record["claimed"] = overlaps(record["rva"], len(body))
            else:
                record["bucket"] = ("no-placement" if runs and runs[0][0] >= SEARCHABLE
                                    else "no-needle")
            records.append(record)
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    MATCH_JSON.write_text(json.dumps(records, indent=1))
    counts, sizes = Counter(), Counter()
    for record in records:
        counts[record["bucket"]] += 1
        sizes[record["bucket"]] += record["size"]
    print(f"match: {len(records)} function(s) from {len(list(OBJ_DIR.glob('*.obj')))} object(s)")
    for bucket in sorted(counts):
        print(f"  {bucket:24s} {counts[bucket]:5d} funcs {sizes[bucket]:9,} bytes")
    print(f"  -> {MATCH_JSON.relative_to(ROOT)}")


def landable(records):
    """The exact-unique placements that carry a landable identity, and why the
    others do not. Each filter answers a different question, so a placement can
    fail several; the counts below are of placements failing each, not a split."""
    ledger = list(build.load_all_function_rows())
    claimed_names = {row["name"] for row in ledger}
    ledger_sizes = {int(row["target_rva"], 16): int(row["target_size"]) for row in ledger}
    overlaps = merged_claims()
    candidates = [r for r in records if r["bucket"] == "exact-unique-unclaimed"]
    address_use = Counter(r["rva"] for r in candidates)

    reasons, keep = Counter(), []
    for record in candidates:
        why = []
        if overlaps(record["rva"], record["size"]):
            why.append("overlaps-existing-claim")
        if ledger_sizes.get(record["rva"], record["size"]) != record["size"]:
            # even an unmatched row at this address fixes what size the function
            # is; two sizes at one address is a contradiction check_csv rejects
            why.append("address-held-at-another-size")
        if record["sym"].startswith("$L"):
            why.append("compiler-local-label")
        if record["sym"] in claimed_names:
            why.append("name-already-claimed")
        if address_use[record["rva"]] > 1:
            why.append("address-claimed-by-siblings")
        for reason in why:
            reasons[reason] += 1
        if why:
            record["rejected"] = why
        else:
            keep.append(record)
    return keep, reasons


NOTE = "zh-sweep exact-unique placement in unclaimed .text"


def ledger_line(record):
    return (f"{record['sym']},,0x{record['rva']:08X},{record['size']},{record['source']},"
            f"matched,{NOTE}")


def do_land(args):
    records = json.loads(MATCH_JSON.read_text())
    keep, reasons = landable(records)
    print(f"land: {sum(1 for r in records if r['bucket'] == 'exact-unique-unclaimed')} "
          f"exact-unique-unclaimed placement(s)")
    for reason, count in sorted(reasons.items()):
        print(f"  rejected {count:4d}  {reason}")
    print(f"  landable {len(keep):4d}  {sum(r['size'] for r in keep):,} bytes")
    if not args.apply:
        for record in sorted(keep, key=lambda r: r["rva"]):
            print(ledger_line(record))
        return

    # Append everything before verifying anything. These bodies call each other,
    # and a callee only resolves once its own row is in the ledger, so landing
    # source by source would reject a row purely for sorting before its callee.
    write_rows(keep)
    live = {record["sym"]: record for record in keep}
    for attempt in range(5):
        rejected = {}
        for source in sorted({record["source"] for record in live.values()}):
            verify = subprocess.run([sys.executable, str(ROOT / "tools" / "build.py"), source],
                                    cwd=ROOT, capture_output=True, text=True, timeout=900)
            if verify.returncode == 0:
                continue
            for line in verify.stdout.splitlines():
                if line.startswith("  FAIL "):
                    rejected[line[len("  FAIL "):].rsplit(" (", 1)[0]] = verify.stdout
        if not rejected:
            break
        for name, output in rejected.items():
            reason = next((l.strip() for l in output.splitlines()
                           if "unresolved call(s)" in l and name in output), "byte mismatch")
            print(f"  DROP {name}\n       {reason}")
            live.pop(name)
        # A dropped row can be the callee another surviving row needed, so the
        # survivors are only proven once a full pass rejects nothing.
        write_rows(live.values())
    else:
        raise SystemExit("zh_sweep: rows kept failing after 5 rounds; nothing landed")
    by_source = Counter(record["source"] for record in live.values())
    for source, count in sorted(by_source.items()):
        print(f"  +{count:3d} {source}")
    print(f"landed {len(live)} row(s), {sum(r['size'] for r in live.values()):,} bytes")


def write_rows(records):
    """Rewrite the ledger with exactly this sweep's rows appended.

    Binary, with explicit CRLF: the ledger is a CRLF file, and a text-mode
    rewrite silently normalises every line in it to LF — check_csv rejects the
    whole file for that, which reads as ledger corruption rather than as a
    landing bug.
    """
    kept = [line for line in build.FUNCTIONS.read_bytes().splitlines(keepends=True)
            if NOTE.encode() not in line]
    rows = [(ledger_line(record) + "\r\n").encode()
            for record in sorted(records, key=lambda r: r["rva"])]
    build.FUNCTIONS.write_bytes(b"".join(kept + rows))


def ghidra_validator():
    """A boundary validator over the Ghidra inventory.

    Missing inventory is fatal rather than empty. An empty one answers "no
    opinion" to every question, which a packet would faithfully print as "the
    inventory does not cover this address" — a different and worse lie than the
    one this validation exists to stop.
    """
    if not build.GHIDRA_FUNCTIONS.exists():
        raise SystemExit(f"zh_sweep: {build.GHIDRA_FUNCTIONS.relative_to(ROOT)} is missing; "
                         "without it no packet's address or extent can be checked")
    with build.GHIDRA_FUNCTIONS.open(newline="") as handle:
        sizes = {int(row["rva"], 16): int(row["size"]) for row in csv.DictReader(handle)}
    return boundary_validator.BoundaryValidator(build.read_target_bytes, sizes)


def retail_extent(rva, validator, text, text_rva):
    """(bytes, kind, where it came from) for the body at `rva`, or (None, ...).

    The Ghidra inventory answers directly where it covers the address. Where it
    does not, the image still bounds the body: MSVC pads between functions with
    int3, so the first run of them after `rva` ends it — unless a known function
    starts before the run, which makes the run that later body's padding and
    leaves this body's end unknown rather than guessable.
    """
    if rva in validator.sizes:
        return validator.sizes[rva], "the Ghidra inventory", "reverse/ghidra_functions.csv"
    offset = rva - text_rva
    run = text.find(b"\xcc" * boundary_validator.MIN_PAD_RUN, offset, offset + PAD_SCAN)
    if run <= offset:
        return None, "unverified", None
    if validator.starts_inside(rva, text_rva + run):
        return None, "unverified", None
    return run - offset, "int3 padding", f"the int3 padding at 0x{text_rva + run:08X}"


def packet_bounds(rva, zh_size, validator, text, text_rva):
    """What this repo can prove about the body at `rva`, for one packet header.

    The old packet asserted both halves of that header: that the address is a
    function start, and that the Zero Hour candidate's own length is retail's
    extent at it. Neither was ever checked. 25 of 335 addresses are provably not
    a start — one of them four bytes inside a 106-byte body, quoting 164 — and
    35 of the 191 with a known extent disagree with the candidate's size. Both
    errors put a contributor to work reproducing bytes the function they were
    handed does not own, and the byte gate cannot catch the resulting row
    because build.py copies relocation bytes from retail rather than proving
    them.

    `served` is the range the packet quotes: retail's extent where it is known,
    and only otherwise the candidate's length, which the packet then labels
    unverified instead of stating as fact.
    """
    start, why = validator.check_start(rva)
    extent, kind, extent_from = retail_extent(rva, validator, text, text_rva)
    served = extent or zh_size
    enclosing = validator.containing(rva)
    return {"start": start, "start_why": why, "enclosing": enclosing,
            "enclosing_size": validator.sizes.get(enclosing), "extent": extent,
            "extent_kind": kind, "extent_from": extent_from, "zh_size": zh_size,
            "served": served, "spans": validator.check_end(rva, served)}


def do_packets(args):
    records = json.loads(MATCH_JSON.read_text())
    # `claimed` in a record is the ledger as it stood when the match ran, and the
    # ledger moves under it in both directions -- rows land, rows are retracted.
    # It is re-asked live below, so honouring the snapshot here too would only
    # hide leads whose claim has since been withdrawn.
    near = [r for r in records if r["bucket"] == "near" and r["align"] >= NEAR_ALIGN]
    text_rva, text = retail_text()
    overlaps = merged_claims()
    # One packet per retail address, not per candidate body. Retail folds
    # identical code, so one address routinely answers to a dozen Zero Hour
    # template instantiations; they are one function to convert, and a file per
    # candidate would hand the same work out a dozen times.
    #
    # The address itself is a guess too, and for 19 of 144 a refuted one: the
    # needle aligned inside a body or in its padding. Correcting it here, before
    # anything reads it, is what makes the header verdict, the extent, the bytes
    # quoted and the live-claim check below all describe the same one body. An
    # address the inventory merely does not cover is left alone -- it keeps its
    # unverified banner rather than being snapped to a body nobody placed it in.
    validator = ghidra_validator()
    by_rva = {}
    for record in near:
        start = validator.corrected_start(record["rva"])
        by_rva.setdefault(record["rva"] if start is None else start, []).append(record)
    reloc_index = packet_relocs({r["obj"] for r in near})
    # Once: it re-reads the exe and scans .text for the thunk table.
    sources = pin_sources()
    PACKET_DIR.mkdir(parents=True, exist_ok=True)
    # Render every packet BEFORE unlinking anything. The old order deleted the
    # directory first and wrote as it went, so any failure part-way -- a missing
    # objdump was enough -- left the queue empty with nothing to fall back on,
    # and the leads people had hand-annotated into those files went with it.
    rendered = {}
    covered = solved = bodies = inflated = 0
    verdicts, extents, conflicts = Counter(), Counter(), 0
    for rva, group in sorted(by_rva.items()):
        # Ranked on what the packet prints, which is agreement over the bytes
        # actually compared. Ranking on match.json's `align` puts a candidate
        # that is two thirds relocation slots above one with none.
        for record in group:
            record["compared"] = compared_bytes(record, reloc_index[(record["obj"],
                                                                     record["sym"])])
        group.sort(key=lambda r: (-(r["compared"]["agree"] or 0), r["sym"]))
        bounds = packet_bounds(rva, max(r["size"] for r in group), validator, text, text_rva)
        # "unclaimed" is a metadata claim like any other, and match.json's is a
        # snapshot of the ledger as it stood when the match ran. Re-asked here
        # against the live ledger, and against the extent the packet will
        # actually quote rather than the candidate's length.
        if overlaps(rva, bounds["served"]):
            solved += 1
            continue
        body = text[rva - text_rva : rva - text_rva + bounds["served"]]
        relocs = reloc_index[(group[0]["obj"], group[0]["sym"])]
        rendered[rva] = packet_text(rva, bounds, group, body, relocs, sources)
        covered += bounds["served"]
        bodies += len(group)
        verdicts[{True: "function start", False: bounds["start_why"],
                  None: "start unconfirmed"}[bounds["start"]]] += 1
        extents[bounds["extent_kind"]] += 1
        conflicts += bounds["extent"] not in (None, bounds["zh_size"])
        inflated += (group[0]["compared"]["agree"] or 0) < NEAR_ALIGN
    # The directory is derived, so it is rebuilt from scratch -- but it is also
    # tracked, and a regression upstream turns that into silent deletion of
    # leads nobody can regenerate. Say what goes, so a drop is visible in the
    # run that causes it rather than in a diff nobody reads.
    dropped = [p.stem for p in PACKET_DIR.glob("*.md") if int(p.stem, 16) not in rendered]
    for stale in PACKET_DIR.glob("*.md"):
        stale.unlink()
    if dropped:
        print(f"packets: dropping {len(dropped)} packet(s) this run does not "
              f"reproduce: {' '.join(sorted(dropped)[:8])}"
              + (" ..." if len(dropped) > 8 else ""))
    for rva, packet in rendered.items():
        (PACKET_DIR / f"{rva:08x}.md").write_text(packet)
    print(f"packets: {len(rendered)} written to {PACKET_DIR.relative_to(ROOT)}, covering "
          f"{bodies} candidate body/bodies over {covered:,} bytes of unclaimed .text")
    print(f"  {solved} address(es) the ledger has claimed since the match ran: no packet")
    for verdict, count in sorted(verdicts.items()):
        print(f"  address {verdict:24s} {count:4d}")
    for source, count in sorted(extents.items()):
        print(f"  extent from {source:20s} {count:4d}")
    print(f"  {conflicts} packet(s) quote a retail extent the Zero Hour candidate does not have")
    print(f"  {inflated} packet(s) agree on less than {NEAR_ALIGN:.0%} of their COMPARED bytes; "
          f"the threshold is applied upstream to a figure that scores blanked bytes as agreeing")


def packet_relocs(objects):
    """(obj, symbol) -> relocations, for the objects the packets need."""
    index = {}
    for name in sorted(objects):
        for symbol, _, relocs in carve((OBJ_DIR / name).read_bytes()):
            index[(name, symbol)] = relocs
    return index


def hex_listing(body, rva):
    """The retail bytes, sixteen to a line, when there is no disassembler.

    Less convenient than a listing and just as authoritative: the packet's whole
    job is to quote the target exactly, and a reader who needs mnemonics has the
    address to look up.
    """
    lines = []
    for offset in range(0, len(body), 16):
        chunk = body[offset:offset + 16]
        lines.append(f"  {rva + offset:6x}:\t" + " ".join(f"{b:02x}" for b in chunk))
    return "\n".join(lines)


def disassemble(body, rva):
    scratch = OUT_DIR / "disassemble.bin"
    scratch.parent.mkdir(parents=True, exist_ok=True)
    scratch.write_bytes(body)
    try:
        listing = subprocess.run(
            ["objdump", "-b", "binary", "-m", "i386", "-M", "intel",
             f"--adjust-vma=0x{rva:x}", "-D", str(scratch)], capture_output=True)
    except FileNotFoundError:
        # objdump is not part of this repo's toolchain and is absent on a plain
        # Windows checkout. Falling back keeps the queue generatable there.
        return hex_listing(body, rva)
    if listing.returncode != 0:
        raise SystemExit("zh_sweep: objdump failed: " + listing.stderr.decode(errors="replace"))
    lines = listing.stdout.decode(errors="replace").splitlines()
    body_start = next(i for i, line in enumerate(lines) if line.endswith(">:")) + 1
    return "\n".join(lines[body_start:])


Callee = namedtuple("Callee", "ledger_targets csv_targets ledger_rvas csv_rvas")


def pin_sources():
    """{name: Callee} — every address a call to `name` may legitimately encode.

    A name is not an address. `build.load_symbol_map` already folds in the ILT
    thunks a call site encodes in place of the body, but it merges the ledger
    and reverse/symbols.csv into one list, and which of the two holds an address
    is the whole claim a pin makes: symbols.csv routinely pins a per-TU copy of
    a name the ledger holds somewhere else entirely, as
    ?releaseBuffer@UnicodeString@@IAEXXZ is a ledger row at 0x009409F0 and a
    separate BFME body at 0x008881D0. The rvas are carried apart from the
    targets because they are what a reader can look up, and the target sets are
    not: `build_call_thunks` scans for every 0xE9 byte, so one body reaches 171
    "thunks" and printing them would bury the two addresses that matter.
    """
    thunks = build.build_call_thunks()
    ledger_rvas, csv_rvas = defaultdict(list), defaultdict(list)
    for row in build.load_all_function_rows():
        ledger_rvas[row["name"]].append(int(row["target_rva"], 16))
    with build.SYMBOLS.open("r", encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            csv_rvas[row["name"]].append(int(row["address"], 16))
    sources = {}
    for name, candidates in build.load_symbol_map().items():
        owned = {target for rva in ledger_rvas[name] for target in thunks.get(rva, []) + [rva]}
        sources[name] = Callee(owned, set(candidates) - owned,
                               ledger_rvas[name], csv_rvas[name])
    return sources


def elsewhere(callee):
    """Where a name IS known, for a call site that reaches none of it."""
    known = [f"{label} {', '.join(f'0x{rva:08X}' for rva in rvas)}"
             for label, rvas in (("the ledger holds this name at", callee.ledger_rvas),
                                 ("reverse/symbols.csv pins it at", callee.csv_rvas)) if rvas]
    return f" (unpinned: this is the address retail calls; {'; '.join(known)})" if known else ""


def callee_pins(rva, body, relocs, sources):
    """Each REL32 callee with the address THIS call site encodes in retail.

    The displacement is read out of the retail bytes, so the address is the
    binary's own answer rather than a guess: callee = site + 4 + displacement.
    Whether it is pinned is therefore asked of that address and not of the name:
    retail folds and duplicates bodies, so a name the ledger holds is routinely
    called HERE at a copy the ledger does not hold, and a pin that reads the
    name alone asserts a symbol is landed while quoting an address no row
    covers. that is the trap.
    """
    lines = []
    for offset, kind, callee in relocs:
        if kind != REL32 or offset + 4 > len(body):
            continue
        displacement = struct.unpack_from("<i", body, offset)[0]
        target = rva + offset + 4 + displacement
        symbol = sources.get(callee)
        if symbol is None:
            mark = ""
        elif target in symbol.ledger_targets:
            mark = " (already in the ledger)"
        elif target in symbol.csv_targets:
            mark = " (already pinned in reverse/symbols.csv)"
        else:
            mark = elsewhere(symbol)
        lines.append(f"{callee},0x{target:08X}{mark}")
    return "\n".join(lines) or "(no relative calls in this body)"


def wrap(paragraph, indent=""):
    """One paragraph at the width the rest of these files are written to."""
    return textwrap.fill(paragraph, width=88, subsequent_indent=indent,
                         break_long_words=False, break_on_hyphens=False)


NOT_A_START = {
    "in-int3-padding": "the retail byte at this address is int3, which is what MSVC puts "
                       "*between* function bodies, so the placement straddles a boundary",
    "outside-.text": "the address is not in .text at all",
}


def address_banner(rva, bounds):
    """The warning that has to lead a packet whose address is refuted.

    A contributor who trusts the address writes a ledger row at it, and that row
    byte-matches: build.py copies DIR32 relocation bytes out of retail instead
    of proving them, so a claim on bytes the named function does not own still
    goes green. That is how a wrong claim reaches the ledger looking right, and
    the packet is the only place it can be stopped.
    """
    if bounds["start"] is not False:
        return []
    if bounds["enclosing"] is None:
        why = NOT_A_START[bounds["start_why"]] + ", and no known function encloses it"
    else:
        why = (f"the address is {rva - bounds['enclosing']} byte(s) inside the function at "
               f"0x{bounds['enclosing']:08X}, which is {bounds['enclosing_size']} bytes long "
               "and is the body worth converting here")
    return [wrap("**This address is not a function start.** The sweep placed a Zero Hour "
                 f"body here by byte alignment alone, and this repo's own evidence refutes "
                 f"it: {why}. Do not add a ledger row at this address; the bytes below say "
                 "what is here, but the address in this packet's name is not the start of "
                 "it."), ""]


def percent(agreement):
    return "nothing comparable" if agreement is None else f"{agreement * 100:.1f}%"


def compared_bytes(record, relocs):
    """{agree, compared, masked} for one candidate, over the bytes it could compare.

    `align` in match.json is not the number the packet's own sentence claims.
    alignment() scores a blanked byte as agreeing (`holes[index] or ...`), so a
    body that is 65% relocation slots reads 86.8% while agreeing on 66.1% of
    what was actually compared -- and the queue banner says "85%+ aligned" over
    a pool where 25 of 144 do not reach 85% on the measure the words describe.
    The inflated figure stays in the packet, named as the sweep's own, because
    it is what NEAR_ALIGN selected on.
    """
    masked = len({index for offset, _, _ in relocs
                  for index in range(offset, min(offset + 4, record["size"]))})
    compared = record["size"] - masked
    agree = None if not compared else \
        (round(record["align"] * record["size"]) - masked) / compared
    return {"agree": agree, "compared": compared, "masked": masked}


def header_lines(rva, bounds, best):
    """The packet's claims about its own address, extent, and evidence.

    Each is stated with where it came from, or stated unverified. They fail
    independently: an address can be a confirmed start whose extent nothing
    measures, and an unconfirmed address can still have its end read off the
    image. `tools/next_work.py` parses the first of these lines for the size it
    serves, so the extent has to lead.
    """
    extent = (f", an extent measured from {bounds['extent_from']}" if bounds["extent"] else
              ", an UNVERIFIED size — the Zero Hour candidate's own length, which nothing"
              " here measures against retail")
    start = {True: "address is a confirmed function start (reverse/ghidra_functions.csv)",
             None: "no inventory row confirms a function starts at this address; treat the"
                   " start as unverified",
             False: f"address is NOT a function start ({bounds['start_why']}) — see above"
             }[bounds["start"]]
    seen = best["compared"]
    agreement = ("- no byte of the best candidate lies outside a relocation site, so nothing "
                 "about it was compared at all" if seen["agree"] is None else
                 f"- best Zero Hour candidate agrees on {seen['agree'] * 100:.1f}% of the "
                 f"bytes outside relocation sites: {round(seen['agree'] * seen['compared'])} "
                 f"of {seen['compared']} compared byte(s) match")
    lines = [f"- {bounds['served']} bytes, unclaimed by any ledger row{extent}",
             f"- {start}",
             agreement,
             f"- the other {seen['masked']} byte(s) of its {bounds['zh_size']}-byte body are "
             f"relocation slots, blanked before comparing, so which global and which callee "
             f"this body uses never entered that figure — the sweep's own "
             f"{best['align'] * 100:.1f}% counts every blanked byte as agreeing"]
    if bounds["extent"] and bounds["extent"] != bounds["zh_size"]:
        lines.append(f"- the candidate body is {bounds['zh_size']} bytes long, so it does not "
                     "have retail's extent here; the bytes quoted below are retail's")
    if bounds["spans"]:
        lines.append(f"- the quoted range still crosses a boundary ({bounds['spans']}), so "
                     "its end is in dispute")
    return [wrap(line, indent="  ") for line in lines]


def packet_text(rva, bounds, group, body, relocs, sources):
    best = group[0]
    candidates = [f"- `{r['sym']}`\n  in `{r['source']}` "
                  f"({percent(r['compared']['agree'])} of {r['compared']['compared']} "
                  "compared bytes)" for r in group]
    tied = sum(1 for r in group if r["compared"]["agree"] == best["compared"]["agree"])
    ambiguous = [] if tied == 1 else [wrap(
        f"{tied} of the candidates below align equally well, so the sweep cannot tell them "
        "apart: masking the relocation sites hides exactly the bytes that differ between "
        "them — which global the body loads, which callee it tail-jumps to. The first is "
        "not the answer. 0x002EFAF0 was landed under the wrong one of three such ties, and "
        "the call targets below are what separated them."), ""]
    return "\n".join([
        f"# Work packet: retail `0x{rva:08X}`",
        "",
        *address_banner(rva, bounds),
        *header_lines(rva, bounds, best),
        "",
        "## Reference source leads",
        "",
        *ambiguous,
        "\n".join(candidates),
        "",
        "## What this is",
        "",
        "The vendored Zero Hour tree contains a body that nearly reproduces these retail",
        "bytes. Near is not identical, so the names above are leads and not identity: the",
        "two versions differ by something real — a changed constant, an extra member, a",
        "different inlining decision — or they are different functions that share a shape.",
        "Port the reference body into a `Code/` source, then close the remaining gap",
        "against the disassembly below.",
        "",
        f"## Retail disassembly ({bounds['served']} bytes from this address)",
        "",
        "```",
        disassemble(body, rva),
        "```",
        "",
        "## Callee pins (paste unresolved ones into reverse/symbols.csv)",
        "",
        "```",
        callee_pins(rva, body, relocs, sources),
        "```",
        "",
        "## Landing it",
        "",
        "Add a row to `reverse/functions.csv` naming your source and this address, then",
        "run `./build.sh '<your symbol>'`. It passes only when every byte outside a",
        "relocation site is identical to the address above — which is exactly why the",
        "name and the extent above still need checking by hand. The gate copies",
        "relocation bytes from retail rather than proving them, so a row at the wrong",
        "address, the wrong size, or under a tied candidate's name goes green anyway.",
        "",
    ])


# --------------------------------------------------------------------------
# land-multi: the exact-MULTI placements, landed over gen-dump rows
# --------------------------------------------------------------------------
#
# `land` only lands a body that places at exactly ONE address, because a unique
# placement is evidence about identity. The bodies below place at many: retail
# folds identical code, so one Zero Hour body is byte-true at a dozen addresses
# and says nothing about which function any one of them is. That is still worth
# landing -- the ledger stops holding a byte dump and starts holding a real
# source that reproduces those bytes -- but only under a name that admits it:
# ?dup_<rva>@@YAXXZ, with the COMDAT the bytes came from in object-symbol=.
#
# A real name here would need positive proof this address is that function, and
# an ICF twin is exactly the case where nobody has it.

MULTI_JSON = OUT_DIR / "multi_placements.json"
WAVE_CSV = OUT_DIR / "landmulti_wave.csv"
PINS_CSV = OUT_DIR / "landmulti_pins.csv"
REJECT_CSV = OUT_DIR / "landmulti_string_rejects.csv"
CLASS_RANK = {"zero-reloc": 0, "rel32-all-resolve": 1, "dir32-masked": 2,
              "rel32-mismatch": 3, "rel32-unknown": 4}
LOCAL_LABEL_RE = re.compile(r"\$[A-Za-z]+\d+")
IMAGE_BASE = 0x400000
MULTI_NOTE = "zh-landmulti exact-multi ZH twin"
ALT_OWNERS = 4          # alternate bodies per address, for a lander's retry loop


def dump_rows():
    """{rva: size} for every gen-dump row a wave may supersede.

    Dumpness is the NOTE and only the NOTE — the same predicate validate_rows
    supersedes on, and the one 349 dumps outside Code/gen_asm/ are invisible to
    when a tool asks the directory instead.
    """
    rows = {int(row["target_rva"], 16): int(row["target_size"])
            for row in build.load_all_function_rows() if build.is_scaffold_row(row)}
    if not rows:
        raise SystemExit("zh_sweep: the ledger holds no gen-dump rows — land-multi has "
                         "nothing to supersede")
    return rows


def cache_fingerprint(objects):
    """What the placement search actually depends on: the image and every object."""
    digest = hashlib.sha1(build.EXE.read_bytes())
    for obj in objects:
        digest.update(obj.name.encode())
        digest.update(obj.read_bytes())
    return digest.hexdigest()


def multi_placements(objects_dir, sizes, rederive):
    """Cache-cached: every carved body that places exactly at >1 .text address.

    Only body sizes some dump row has are searched -- a body no dump row can
    receive cannot become a candidate, and searching for it costs the same as
    searching for one that can.

    The search is minutes of work over inputs that do not move between waves, so
    it is cached under a fingerprint of the image and the objects it read. Dump
    rows only ever leave the ledger, so a cache derived for a SUPERSET of this
    run's sizes still holds every body this run could use; any other difference
    re-derives rather than filtering a cache blind.
    """
    objects = sorted(Path(objects_dir).glob("*.obj"))
    if not objects:
        raise SystemExit(f"zh_sweep: no .obj files in {objects_dir} — run `zh_sweep compile` "
                         "first, or point --objects at a populated sweep cache")
    fingerprint = cache_fingerprint(objects)
    if MULTI_JSON.exists() and not rederive:
        cached = json.loads(MULTI_JSON.read_text())
        covered = set(sizes) <= set(cached["sizes"])
        if cached["fingerprint"] == fingerprint and covered:
            bodies = [b for b in cached["bodies"] if b["size"] in sizes]
            print(f"land-multi: {len(bodies)} multi-placed body/bodies from "
                  f"{MULTI_JSON.relative_to(ROOT)} ({len(cached['bodies'])} cached over "
                  f"{len(cached['sizes'])} size(s))")
            return bodies
        print(f"land-multi: re-deriving — cached fingerprint "
              f"{'matches' if cached['fingerprint'] == fingerprint else 'DIFFERS'}, cached sizes "
              f"{'cover' if covered else 'do NOT cover'} this run's {len(sizes)}")

    text_rva, text = retail_text()
    sources = zh_sources()
    bodies, seen = [], set()
    for index, obj in enumerate(objects, start=1):
        source = object_source(obj, sources)
        for name, body, relocs in carve(obj.read_bytes()):
            if len(body) < MIN_FUNC or name in seen:
                continue
            seen.add(name)                      # first object wins, as do_match does
            if len(body) not in sizes:
                continue
            masked, holes = mask(body, relocs)
            exact = [text_rva + candidate for candidate in placements(text, body, masked, holes)
                     if alignment(text[candidate:candidate + len(body)], masked, holes) == 1.0]
            if len(exact) < 2:
                continue
            bodies.append({"sym": name, "obj": obj.name, "source": source, "size": len(body),
                           "relocs": [[o, k, s] for o, k, s in relocs], "addresses": exact})
        if index % 200 == 0:
            print(f"  {index}/{len(objects)} objects, {len(bodies)} multi-placed bodies",
                  flush=True)
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    MULTI_JSON.write_text(json.dumps({"fingerprint": fingerprint, "sizes": sorted(sizes),
                                      "bodies": bodies}))
    print(f"land-multi: {len(bodies)} multi-placed body/bodies -> "
          f"{MULTI_JSON.relative_to(ROOT)}")
    return bodies


class Landing:
    """Everything a land-multi run asks of the retail image and the object cache."""

    def __init__(self, objects_dir):
        self.objects = Path(objects_dir)
        self.data, self.sections = build.exe_image()
        self.text_rva, self.text = retail_text()
        section = next(s for s in self.sections if s["name"] == ".text")
        self.low, self.high = section["rva"], section["rva"] + section["size"]
        self.symbols = {name: set(addresses)
                        for name, addresses in build.load_symbol_map().items()}
        self._bodies, self._literals, self._thunks = {}, {}, {}

    def at(self, rva, size):
        offset = build.rva_to_file_offset(self.sections, rva)
        return self.data[offset:offset + size]

    def u32(self, rva):
        return struct.unpack_from("<I", self.at(rva, 4))[0]

    def rel32_target(self, rva, offset):
        site = rva - self.text_rva + offset
        return rva + offset + 4 + struct.unpack_from("<i", self.text, site)[0]

    def follow(self, rva):
        """The body a call lands in, past any incremental-link thunk."""
        if rva not in self._thunks:
            self._thunks[rva] = (build.follow_thunk(self.data, self.sections, rva,
                                                    self.low, self.high)
                                 if self.low <= rva < self.high else rva)
        return self._thunks[rva]

    def compiled(self, body):
        """The candidate's own compiled bytes — where DIR32 addends are read."""
        key = (body["obj"], body["sym"])
        if key not in self._bodies:
            self._bodies[key] = build.read_object_symbol_bytes(
                self.objects / body["obj"], body["sym"], body["size"])[0]
        return self._bodies[key]

    def literal(self, body, sym):
        """The string COMDAT's own bytes, or None when this object does not define it."""
        key = (body["obj"], sym)
        if key not in self._literals:
            try:
                self._literals[key] = build.read_object_symbol_bytes(
                    self.objects / body["obj"], sym)[0]
            except ValueError:
                self._literals[key] = None
        return self._literals[key]

    def cstring(self, rva, limit=96):
        """The retail string at `rva`, for a rejection log — identity intel, not a check."""
        raw = self.at(rva, limit)
        return raw.split(b"\0", 1)[0].decode("ascii", errors="replace")

    def sites(self, body):
        """The relocations that lie inside the claimed extent; nothing else is compared."""
        return [(offset, kind, sym) for offset, kind, sym in body["relocs"]
                if offset + 4 <= body["size"]]

    def classify(self, rva, body):
        """Which verifier decides this placement, once the row is in the ledger."""
        relocs = self.sites(body)
        if not relocs:
            return "zero-reloc"
        mismatch = unknown = False
        for offset, kind, sym in relocs:
            if kind != REL32:
                continue
            if sym not in self.symbols:
                unknown = True
            elif self.rel32_target(rva, offset) not in self.symbols[sym]:
                mismatch = True
        if mismatch:
            return "rel32-mismatch"
        if unknown:
            return "rel32-unknown"
        if any(kind == DIR32 for _, kind, _ in relocs):
            return "dir32-masked"
        return "rel32-all-resolve"

    def string_sites(self, body):
        return [(offset, sym) for offset, kind, sym in self.sites(body)
                if kind == DIR32 and sym.startswith("??_C@")]

    def strings_agree(self, rva, body):
        """verify_string_refs' own rule, asked BEFORE landing instead of after.

        An exact twin reproduces retail with the pointer blanked, so a wrong twin
        places perfectly and then points at a Zero Hour class name where retail
        holds a BFME one. Returns (ok, reason, [retail string]) — the strings are
        the byproduct: they name the BFME-only identity living at that address.
        """
        compiled = self.compiled(body)
        found = []
        for offset, sym in self.string_sites(body):
            content = self.literal(body, sym)
            if content is None:
                return False, f"literal {sym[:40]} is not defined in {body['obj']}", found
            content = content.rstrip(b"\0")
            addend = struct.unpack_from("<i", compiled, offset)[0]
            if 0 < addend <= len(content):
                content = content[addend:]
            try:
                pointer = self.u32(rva + offset) - IMAGE_BASE
                retail = self.at(pointer, max(len(content), 1))
                found.append(self.cstring(pointer))
            except ValueError as exc:
                return False, f"string pointer at +{offset} is not in any section: {exc}", found
            if content and retail != content:
                return False, (f"literal {content[:60].decode('ascii', 'replace')!r} != retail "
                               f"{found[-1][:60]!r}"), found
            if not content and retail[:1] != b"\0":
                return False, f'literal "" but retail holds {found[-1][:60]!r}', found
        return True, "", found

    def dir32_bases(self, rva, body, whitelist):
        """{symbol: base} for the DIR32 sites verify_dir32_consistency gates.

        Same exclusions as build.py: string literals are verified by content,
        compiler-local labels and __ehhandler$ stubs are per-TU by construction,
        and a whitelisted symbol is already known to hold several bases.
        """
        compiled = self.compiled(body)
        bases = {}
        for offset, kind, sym in self.sites(body):
            if kind != DIR32 or sym.startswith("??_C@") or sym in whitelist:
                continue
            if LOCAL_LABEL_RE.fullmatch(sym) or sym.startswith("__ehhandler$"):
                continue
            addend = struct.unpack_from("<I", compiled, offset)[0]
            bases[sym] = (self.u32(rva + offset) - addend) & 0xFFFFFFFF
        return bases

    def unresolved_calls(self, rva, body):
        """(symbol, target) per REL32 site retail encodes somewhere the map does not have."""
        out = []
        for offset, kind, sym in self.sites(body):
            if kind != REL32:
                continue
            target = self.rel32_target(rva, offset)
            if sym in self.symbols and target in self.symbols[sym]:
                continue
            out.append((sym, self.follow(target)))
        return out

    def callee_bodies(self, wanted):
        """{symbol: (bytes, relocs)} carved out of the cache for the pin proof."""
        carved = {}
        for obj in sorted(self.objects.glob("*.obj")):
            for name, body, relocs in carve(obj.read_bytes()):
                if name in wanted and name not in carved:
                    carved[name] = (bytes(body), relocs)
        return carved

    def proves(self, carved, sym, target):
        """The byte-equal precedent (1a6060b38): pin only where the CALLEE's own
        compiled body reproduces retail at the address this call site encodes."""
        entry = carved.get(sym)
        if entry is None:
            return False
        body, relocs = entry
        masked, holes = mask(body, relocs)
        try:
            window = self.at(target, len(body))
        except ValueError:
            return False
        return len(window) == len(body) and all(
            holes[index] or window[index] == masked[index] for index in range(len(body)))


def whitelisted_dir32():
    path = ROOT / "reverse" / "dir32_consistency_whitelist.txt"
    if not path.exists():
        raise SystemExit(f"zh_sweep: {path.relative_to(ROOT)} is missing; without it every "
                         "known-legitimate multi-base symbol reads as a new conflict")
    return {line.strip() for line in path.read_text().splitlines()
            if line.strip() and not line.startswith("#")}


def existing_dir32_bases(wanted):
    """{symbol: {base}} for `wanted` over every matched row already in the ledger.

    verify_dir32_consistency runs only in the FULL gate and a per-source gate is
    scoped, so a wave that disagrees with an existing row about where a symbol
    lives lands green and fails the next full build — which is how 18 whitelist
    entries got added to make a red master pass. Asked here instead, before a
    row is written.
    """
    bases = defaultdict(set)
    rows = build.load_function_rows()
    print(f"land-multi: DIR32 pre-check — scanning {len(rows):,} matched row(s) for "
          f"{len(wanted)} symbol(s)", flush=True)
    for row in rows:
        obj = build.require_row_object(row)
        rva, size = int(row["target_rva"], 16), int(row["target_size"])
        try:
            body, relocs = build.read_object_symbol_bytes(
                obj, build.ledger_object_symbol(row), size)
        except ValueError:
            # The same skip verify_dir32_consistency itself takes: a row whose
            # symbol is not in its object contributes no base to either side.
            continue
        target = None
        for offset, kind, sym in relocs:
            if kind != DIR32 or sym not in wanted or offset + 4 > min(size, len(body)):
                continue
            if target is None:
                target = build.read_target_bytes(rva, size)
            final = struct.unpack_from("<I", target, offset)[0]
            addend = struct.unpack_from("<I", body, offset)[0]
            bases[sym].add((final - addend) & 0xFFFFFFFF)
    return bases


def pick_candidates(bodies, rows, held, landing, limits):
    """Per dump address, the bodies that can be landed on it, best class first.

    A candidate must start EXACTLY at a dump row, agree with it on size, and sit
    on ground no matched row claims. Everything after that is which twin, not
    whether: they are all byte-true, so they are ranked by the class of verifier
    that will judge them and tie-broken on the symbol so a re-run picks the same.
    """
    by_address, rejects = defaultdict(list), []
    for body in bodies:
        for rva in body["addresses"]:
            if rows.get(rva) != body["size"] or held(rva, body["size"]):
                continue
            entry = {"body": body, "rva": rva, "size": body["size"],
                     "class": landing.classify(rva, body)}
            if landing.string_sites(body):
                ok, why, strings = landing.strings_agree(rva, body)
                if not ok:
                    rejects.append({"rva": rva, "size": body["size"], "sym": body["sym"],
                                    "source": body["source"], "reason": why,
                                    "retail": " | ".join(strings)})
                    continue
                entry["strings"] = strings
            by_address[rva].append(entry)
    for entries in by_address.values():
        entries.sort(key=lambda e: (CLASS_RANK[e["class"]], e["body"]["sym"]))
    # `covered` is every address some twin can serve, asked BEFORE the class
    # filter: a rejection only means "no Zero Hour twin has retail's string here"
    # when the address has no surviving candidate at all, and a --classes run
    # that hid the surviving one would otherwise report a solved address as
    # BFME-only intel.
    covered = set(by_address)
    if limits.get("classes"):
        by_address = {rva: entries for rva, entries in by_address.items()
                      if entries[0]["class"] in limits["classes"]}
    return by_address, rejects, covered


def dir32_consistent(chosen, by_address, landing, whitelist):
    """Keep, per address, a twin whose DIR32 symbols land where the ledger has them.

    Two ways a wave breaks verify_dir32_consistency: it disagrees with itself, or
    it disagrees with a row already in the ledger. Both fail the full gate
    identically, and the fix is never a whitelist entry — it is not landing the
    placement that caused it.

    But "the placement" is a whole family: retail folds identical code, and the
    twins at one address differ in exactly the bytes that are blanked — which
    vtable, which pool. So a twin that puts ??_7SomeClass@@6B@ somewhere the
    ledger does not have it is not a reason to abandon the address; its sibling
    that agrees is the one to land. Only twins of the same class are considered,
    because a twin from a worse class needs pins this run harvested for another
    body. What is left is settled greedily to a fixpoint: the base covering the
    most bytes keeps its addresses.
    """
    families = {rva: [(entry, landing.dir32_bases(rva, entry["body"], whitelist))
                      for entry in by_address[rva]
                      if entry["class"] == chosen[rva]["class"]
                      and CLASS_RANK[entry["class"]] < CLASS_RANK["rel32-mismatch"]]
                or [(chosen[rva], landing.dir32_bases(rva, chosen[rva]["body"], whitelist))]
                for rva in chosen}
    wanted = {sym for family in families.values() for _, syms in family for sym in syms}
    if not wanted:
        return chosen, {}
    existing = dict(existing_dir32_bases(wanted))
    live, bases, dropped = {}, {}, {}
    for rva, family in families.items():
        agreeing = [(entry, syms) for entry, syms in family
                    if all(base in existing[sym]
                           for sym, base in syms.items() if sym in existing)]
        if agreeing:
            live[rva], bases[rva] = agreeing[0]
            continue
        entry, syms = family[0]
        sym, base = next((s, b) for s, b in sorted(syms.items())
                         if s in existing and b not in existing[s])
        dropped[rva] = (f"{sym} would resolve to 0x{base:08X} here, but "
                        f"{'/'.join(f'0x{b:08X}' for b in sorted(existing[sym]))} elsewhere, "
                        f"and no twin of this body agrees")
    while True:
        by_symbol = defaultdict(lambda: defaultdict(list))
        for rva in live:
            for sym, base in bases[rva].items():
                by_symbol[sym][base].append(rva)
        drop = {}
        for sym, seen in by_symbol.items():
            options = dict(seen)
            for base in existing.get(sym, ()):
                options.setdefault(base, [])
            if len(options) <= 1:
                continue
            keep = max(options, key=lambda base: (sum(live[r]["size"] for r in options[base])
                                                  + (10 ** 9 if base in existing.get(sym, ()) else 0),
                                                  -base))
            for base, addresses in options.items():
                if base == keep:
                    continue
                for rva in addresses:
                    drop[rva] = (f"{sym} would resolve to 0x{base:08X} here, but "
                                 f"0x{keep:08X} elsewhere")
        if not drop:
            return live, dropped
        for rva, reason in drop.items():
            live.pop(rva)
            dropped[rva] = reason


def harvest_pins(chosen, by_address, landing):
    """Per-site callee pins for the mismatch/unknown classes, byte-equal only.

    A wave row whose REL32 site the symbol map cannot resolve fails the gate, so
    each such site needs the callee pinned at the address retail's own
    displacement points to. The pin is only written where the callee's compiled
    body reproduces retail there — the precedent from 1a6060b38, and the only
    thing separating a pin from a guess.

    Pins split in two by how they can be written. A callee reverse/symbols.csv
    already spends at a DIFFERENT address comes back as `extra`: symbols.csv is
    additive and 512 names in it already hold several addresses, but a wave
    transaction refuses to add a second address for a pinned name, so those have
    to be appended separately.
    """
    needed = {rva: [(entry, landing.unresolved_calls(rva, entry["body"]))
                    for entry in by_address[rva]]
              for rva, entry in chosen.items()
              if landing.unresolved_calls(rva, entry["body"])}
    if not needed:
        return {}, {}, {}
    spent = spent_pins()
    carved = landing.callee_bodies({sym for twins in needed.values()
                                    for _, sites in twins for sym, _ in sites})
    pins, extra, unprovable = defaultdict(set), defaultdict(set), {}
    for rva, twins in needed.items():
        # Every twin at this address is byte-true; they differ in which callee
        # they name at each site, so one can be provable where another is not.
        # Trying only the first is how the spike's 247 pins collapsed to 1.
        failed = set()
        for entry, sites in twins:
            unproven = {sym for sym, target in sites
                        if not landing.proves(carved, sym, target)}
            if unproven:
                failed |= {f"{sym} (not byte-equal at the encoded address)" for sym in unproven}
                continue
            chosen[rva] = entry
            for sym, target in sites:
                (extra if sym in spent and spent[sym] != target else pins)[sym].add(target)
            break
        else:
            unprovable[rva] = "no twin's callees prove out: " + ", ".join(sorted(failed)[:3])
    return pins, extra, unprovable


def spent_pins():
    """{name: address} reverse/symbols.csv already holds."""
    with build.SYMBOLS.open(encoding="utf-8", newline="") as handle:
        return {row["name"]: int(row["address"], 16) for row in csv.DictReader(handle)}


def report_drops(label, dropped, chosen, show=6):
    """Say what left the wave and why, without printing three hundred lines of it."""
    for index, rva in enumerate(sorted(dropped)):
        if index < show:
            print(f"  DROP 0x{rva:08X} ({label}): {dropped[rva]}")
        if chosen is not None:
            chosen.pop(rva, None)
    if len(dropped) > show:
        print(f"  ... {len(dropped) - show} more {label} drop(s)")


def wave_rows(chosen, alternates):
    """The wave CSV: one dup_ row per address, alternates for a retry loop."""
    header = ["name", "rva", "size", "source", "notes"]
    for index in range(1, ALT_OWNERS + 1):
        header += [f"alt{index}_source", f"alt{index}_notes"]
    lines = [header]
    for rva in sorted(chosen):
        entry = chosen[rva]
        record = [f"?dup_{rva:08x}@@YAXXZ", f"0x{rva:08X}", str(entry["size"]),
                  entry["body"]["source"], owner_notes(entry)]
        for other in alternates[rva][:ALT_OWNERS]:
            record += [other["body"]["source"], owner_notes(other)]
        lines.append(record + [""] * (len(header) - len(record)))
    return lines


def interchangeable(rva, chosen, others, landing, whitelist):
    """The twins a lander may retry this address on without changing its proof.

    An alternate owner is only a different translation unit to compile the same
    bytes from — but two twins can carry different DIR32 addends or call
    different callees, and the wave was pre-checked against the chosen one. An
    alternate that would move a DIR32 base or need a pin nobody proved is not an
    alternate, it is a second landing nobody checked.
    """
    keep = []
    reference = (landing.dir32_bases(rva, chosen["body"], whitelist),
                 sorted(landing.unresolved_calls(rva, chosen["body"])))
    for other in others:
        if (landing.dir32_bases(rva, other["body"], whitelist),
                sorted(landing.unresolved_calls(rva, other["body"]))) == reference:
            keep.append(other)
    return keep


def owner_notes(entry):
    return f"{MULTI_NOTE} ({entry['class']});object-symbol={entry['body']['sym']}"


def write_csv(path, rows):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as handle:
        csv.writer(handle, lineterminator="\n").writerows(rows)
    return path


def do_land_multi(args):
    rows = dump_rows()
    sizes = set(rows.values())
    print(f"land-multi: {len(rows):,} gen-dump row(s) at HEAD, "
          f"{sum(rows.values()):,} bytes, {len(sizes)} distinct size(s)")
    bodies = multi_placements(args.objects, sizes, args.rederive)
    landing = Landing(args.objects)
    held = merged_claims()
    limits = {"classes": set(args.classes.split(",")) if args.classes else None}
    by_address, rejects, covered = pick_candidates(bodies, rows, held, landing, limits)
    counts, byte_counts = Counter(), Counter()
    for entries in by_address.values():
        counts[entries[0]["class"]] += 1
        byte_counts[entries[0]["class"]] += entries[0]["size"]
    print(f"\nland-multi: {len(by_address)} dump address(es) an exact-multi twin can be "
          f"landed on, {sum(byte_counts.values()):,} bytes")
    for name in CLASS_RANK:
        print(f"  {name:18s} {counts[name]:5d} addrs {byte_counts[name]:9,d} B")
    print(f"  string rejections  {len(rejects):5d} addr-body pair(s) — "
          f"{REJECT_CSV.relative_to(ROOT)}")
    write_csv(REJECT_CSV, [["rva", "size", "sym", "source", "reason", "retail_strings"]]
              + [[f"0x{r['rva']:08X}", r["size"], r["sym"], r["source"], r["reason"],
                  r["retail"]] for r in sorted(rejects, key=lambda r: r["rva"])])
    # The rejections are a deliverable, not a loss: the retail string a wrong twin
    # points at is the class name living at that address, and these bodies are
    # getModuleNameKey/getClassMemoryPool shapes where the name IS the identity.
    unsolved = {r["rva"]: r for r in rejects if r["rva"] not in covered}
    for rva, reject in sorted(unsolved.items()):
        print(f"  string reject 0x{rva:08X}/{reject['size']}B: retail names "
              f"{reject['retail']!r} — no Zero Hour twin has it")

    chosen = {rva: entries[0] for rva, entries in by_address.items()}
    pins, extra, unprovable = harvest_pins(chosen, by_address, landing)
    report_drops("unproven callee", unprovable, chosen)
    print(f"land-multi: {sum(len(v) for v in pins.values())} proven pin(s) over "
          f"{len(pins)} callee symbol(s) + {sum(len(v) for v in extra.values())} on "
          f"{len(extra)} callee(s) symbols.csv already spends elsewhere; "
          f"{len(unprovable)} address(es) dropped unproven")

    whitelist = whitelisted_dir32()
    chosen, conflicts = dir32_consistent(chosen, by_address, landing, whitelist)
    report_drops("DIR32 consistency", conflicts, None)
    print(f"land-multi: {len(chosen)} address(es) survive the DIR32 pre-check "
          f"({len(conflicts)} dropped)")

    chosen = trim(chosen, args)
    alternates = {rva: interchangeable(rva, chosen[rva], by_address[rva][1:], landing, whitelist)
                  for rva in chosen}
    wave = write_csv(WAVE_CSV, wave_rows(chosen, alternates))
    pinned = pin_rows(pins, chosen, landing)
    pin_csv = write_csv(PINS_CSV, [["name", "address", "notes"]] + pinned)
    print(f"\nland-multi: wave {wave.relative_to(ROOT)} — {len(chosen)} row(s), "
          f"{sum(e['size'] for e in chosen.values()):,} bytes over "
          f"{len({e['body']['source'] for e in chosen.values()})} source(s); "
          f"{len(pinned)} pin(s) -> {pin_csv.relative_to(ROOT)}")
    print("land-multi: the wave and its pins are a REPORT — tools/land_wave.py, the\n"
          "      lander that consumed them, was retired with the generators. Landing a\n"
          "      row now means proving it through ./build.sh by hand.")


def pin_rows(pins, chosen, landing):
    """The pins the surviving rows still need, in reverse/symbols.csv's columns."""
    live = defaultdict(set)
    for rva, entry in chosen.items():
        for sym, target in landing.unresolved_calls(rva, entry["body"]):
            if target in pins.get(sym, ()):
                live[sym].add(target)
    return [[sym, f"0x{target:08X}",
             "zh-landmulti per-site callee copy (body proven byte-equal)"]
            for sym in sorted(live) for target in sorted(live[sym])]


def trim(chosen, args):
    """Cut the wave down to what one gate round should carry.

    Sources are the unit that costs: a lander compiles each one, and a wave
    spanning two hundred Zero Hour translation units is a gate nobody can wait
    out. Sources are taken whole and in address order so a re-run with the same
    limits builds the same wave.
    """
    per_source = defaultdict(list)
    for rva in sorted(chosen):
        per_source[chosen[rva]["body"]["source"]].append(rva)
    kept, sources = {}, 0
    for source in sorted(per_source, key=lambda s: (-sum(chosen[r]["size"]
                                                         for r in per_source[s]), s)):
        if args.max_sources and sources >= args.max_sources:
            break
        addresses = per_source[source][:args.max_per_source or None]
        if args.max_rows and len(kept) + len(addresses) > args.max_rows:
            addresses = addresses[:args.max_rows - len(kept)]
        if not addresses:
            continue
        sources += 1
        for rva in addresses:
            kept[rva] = chosen[rva]
        if args.max_rows and len(kept) >= args.max_rows:
            break
    if not kept:
        raise SystemExit("land-multi: every candidate was filtered out — nothing to land")
    return kept


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    compile_parser = sub.add_parser("compile", help="build ZH TUs into the object cache")
    compile_parser.add_argument("--limit", type=int, default=0,
                                help="sample at most N sources per subtree")
    compile_parser.add_argument("--force", action="store_true", help="rebuild cached objects")
    compile_parser.set_defaults(run=do_compile)
    sub.add_parser("match", help="place every carved COMDAT in .text").set_defaults(run=do_match)
    land_parser = sub.add_parser("land", help="ledger rows for landable placements")
    land_parser.add_argument("--apply", action="store_true",
                             help="append the rows and byte-verify each source")
    land_parser.set_defaults(run=do_land)
    multi_parser = sub.add_parser("land-multi",
                                  help="supersede gen-dump rows with exact-MULTI placements")
    multi_parser.add_argument("--objects", default=str(OBJ_DIR),
                              help=f"sweep object cache (default {OBJ_DIR.relative_to(ROOT)})")
    multi_parser.add_argument("--classes",
                              help="comma-separated subset of " + ",".join(CLASS_RANK))
    multi_parser.add_argument("--max-rows", type=int, default=0, help="cap rows in the wave")
    multi_parser.add_argument("--max-sources", type=int, default=0,
                              help="cap translation units in the wave (each one is a compile)")
    multi_parser.add_argument("--max-per-source", type=int, default=0,
                              help="cap rows taken from any one translation unit")
    multi_parser.add_argument("--rederive", action="store_true",
                              help="ignore the cached placement search")
    multi_parser.set_defaults(run=do_land_multi)
    sub.add_parser("packets", help="work packets for unclaimed near misses").set_defaults(
        run=do_packets)
    args = parser.parse_args()
    args.run(args)


if __name__ == "__main__":
    main()
