#!/usr/bin/env python3
"""Generate byte-verifiable C++ for the retail executable's tiny functions.

The 1.03 build carries ~43k ghidra-inventoried functions of 16 bytes or less, and
37,716 of them are a single `jmp rel32`. Those have no recoverable identity, but
their bytes are fully determined by their target, so `void j_<rva>() { b_<tgt>(); }`
reproduces one exactly under MSVC 7.1 /O2 (five bytes, E9 + a REL32 reloc) and the
existing gate proves it against the retail bytes. The gate fills the displacement
from a `?b_<tgt>@@YAXXZ` pin in reverse/symbols.csv, so a wrong target or a wrong
pin fails loudly instead of matching anyway.

Subcommands
  classify    write reverse/ghidra_artifacts_blacklist.txt — the small-function
              RVAs that are ghidra boundary artifacts and must never be claimed.
  gen-thunks  write one Code/gen_small/thunks_<batch>.cpp plus its pending ledger
              rows and symbols.csv pins (build/gen_small/thunks_<batch>.json).
  gen-gap-thunks
              the same emission for the `jmp rel32` thunks that live in the
              .text the ghidra inventory never covered: one
              Code/gen_small/gthunks_<batch>.cpp per batch.
  gen-imports write one Code/gen_small/imports_<batch>.cpp for the six-byte
              `FF 25` import thunks; no pins, the gate copies DIR32 sites.
  gen-ehstubs bind the ten-byte `__ehhandler$` stubs in those same gaps to the
              single Code/gen_small/eh_anchor.cpp obj, one chunk of rows per
              run; refuses to emit unless the compiled anchor masked-matches
              three image exemplars first.
  gen-tgrid   write Code/gen_small/tgrid_<batch>.cpp: STLport templates
              instantiated over a synthetic payload grid, claiming the retail
              container bodies those instantiations reproduce byte for byte.
  gen-tinst   the same instantiation, driven the other way round: the element
              type is read OUT of the body's own STLport-decorated name in
              reverse/reloc_names.csv, so the retail body is identified by name
              rather than placed by shape. Writes Code/gen_small/tinst_<batch>.cpp.
  gen-dtors   write one Code/gen_small/dtors_<batch>.cpp (scalar `??_G`) or
              dtorsv_<batch>.cpp (vector `??_E`) batch of synthetic classes whose
              compiler-generated deleting destructors are the retail bodies.
  probe       compile one instance of every anonymous-body skeleton and record
              which ones reproduce the retail bytes exactly (skeleton library).
  gen-shims   write one Code/gen_small/fun_<batch>.cpp of `gen-shim` struct
              methods for the probed skeletons' instances.
  gen-getters write one numbered Code/gen_small/getters_<batch>.cpp containing
              the exact `B8 imm32 C3` bodies held by live gen-dump scaffolds.
  shim-report account for every anonymous FUN_* body: landed, skipped skeleton,
              or out of scope.
  gen-named   write one Code/gen_small/named_<batch>.cpp of the small functions
              ghidra named, under the decorated names a family rule derives and
              this command byte-verifies before emitting.
  sweep-funclets
              match the SEH funclets in already-matched sources' objects against
              the unclaimed retail `Unwind@*`/`Catch@*` inventory by bytes, and
              write the rows that match exactly one of them each way.
  land        append that batch's rows and pins under the ledger lock and prove
              them with ONE ./build.sh; any failure reverts everything.
  land-funclets
              the same transaction for one funclet batch — rows only, since
              those point at parent sources git already tracks.

Every subcommand is idempotent: rerunning one whose output has already landed
reports `0 new` and writes nothing.

Hex convention: C++ identifiers carry the lowercase 8-digit RVA (ghidra spells its
own names that way, FUN_004874e0); ledger and symbols.csv address columns are
0x%08X, per docs/matching.md.
"""
import argparse
import bisect
import collections
import csv
import hashlib
import io
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import ledger_io
from add_match import parse_ledger
from portable_lock import lock

ROOT = B.ROOT
GHIDRA = ROOT / "reverse" / "ghidra_functions.csv"
BLACKLIST = ROOT / "reverse" / "ghidra_artifacts_blacklist.txt"
GEN_DIR = ROOT / "Code" / "gen_small"
PENDING_DIR = ROOT / "build" / "gen_small"
# WHERE a dump was written, never WHETHER a row is one -- 349 gen-dump rows live
# outside this directory. build.is_scaffold_row answers "is this a dump?"; this
# only tells wave_accounting's genasm lane from its naked one.
DUMP_DIR_PREFIX = "Code/gen_asm/"
# The only record of a functions.csv deletion; see retract_dump_rows().
DELETED = ROOT / "reverse" / "deleted_rows.csv"
LOCK_FILE = ROOT / "reverse" / ".add_match.lock"

# The inventory this generator works over. Bigger ghidra functions carry real
# structure and belong to the ordinary reverse-engineering queue.
SMALL_MAX = 16

# functions.csv is raw comma-joined fields with no quoting, so any of these in a
# generated field silently corrupts the ledger. Same set add_match.py rejects.
CSV_HOSTILE = set(',"\r\n')


class FormatError(Exception):
    """A generated row or pin broke a ledger format rule.

    This is always a generator bug. It must stop the run: a row that reaches
    functions.csv malformed is discovered days later as somebody else's red gate.
    """


# --------------------------------------------------------------------------
# inventory
# --------------------------------------------------------------------------

def load_ghidra():
    """[(rva, size, name)] for every inventoried function, ascending by rva."""
    with GHIDRA.open(encoding="utf-8", newline="") as handle:
        rows = [(int(r["rva"], 16), int(r["size"]), r["name"])
                for r in csv.DictReader(handle)]
    rows.sort()
    return rows


def exe_reader():
    """read(rva, size) -> bytes, over one in-memory copy of the retail image."""
    data = B.EXE.read_bytes()
    sections = B.pe_sections(data)

    def read(rva, size):
        offset = B.rva_to_file_offset(sections, rva)
        return data[offset:offset + size]
    return read


# --------------------------------------------------------------------------
# classification
# --------------------------------------------------------------------------

def jmp_call_rm_length(body, pos):
    """Length of the `jmp`/`call r/m32` at body[pos:], or None if there isn't one.

    FF /4 and FF /2 are how the retail vtable and import trampolines end, and
    their length depends on the ModRM/SIB/displacement encoding, so a small
    function ending in one cannot be recognised from its last byte alone.
    """
    if pos + 1 >= len(body) or body[pos] != 0xFF:
        return None
    modrm = body[pos + 1]
    mod, reg, rm = modrm >> 6, (modrm >> 3) & 7, modrm & 7
    if reg not in (2, 4):  # call r/m32, jmp r/m32
        return None
    length = 2
    if mod != 3 and rm == 4:
        if pos + 2 >= len(body):
            return None
        length += 1
        if mod == 0 and (body[pos + 2] & 7) == 5:
            length += 4
    if mod == 0 and rm == 5:
        length += 4
    elif mod == 1:
        length += 1
    elif mod == 2:
        length += 4
    return length


def terminator(body):
    """Name the instruction the body ends on, or None when its last bytes are not
    a recognizable function ending — which means ghidra cut the boundary inside an
    instruction and the row's size is fiction."""
    n = len(body)
    if body[-1] == 0xC3:
        return "ret"
    if n >= 3 and body[-3] == 0xC2:
        return "ret imm16"
    if n >= 5 and body[-5] == 0xE9:
        return "jmp rel32"
    if n >= 5 and body[-5] == 0xE8:
        return "call rel32"  # tail call into a noreturn (throw helpers, exit)
    if n >= 2 and body[-2] == 0xEB:
        return "jmp rel8"
    for pos in range(max(0, n - 7), n - 1):
        if jmp_call_rm_length(body, pos) == n - pos:
            return "jmp/call r/m32"
    if body[-1] == 0xCC:
        return "int3"
    return None


def jmp_rel32_target(body, rva):
    """Target RVA of a five-byte `jmp rel32` body, or None if it is not one."""
    if len(body) != 5 or body[0] != 0xE9:
        return None
    return rva + 5 + struct.unpack_from("<i", body, 1)[0]


def classify(entries, read, small_max=SMALL_MAX):
    """{rva: reason} for the small functions that are ghidra boundary artifacts.

    A blacklisted RVA is never claimed by any generator here. Being wrong in the
    other direction is the expensive one, so anything whose bytes do not read as a
    complete function is listed, not guessed at.
    """
    starts = {rva for rva, _, _ in entries}
    artifacts = {}
    for rva, size, name in entries:
        if size > small_max:
            continue
        body = read(rva, size)
        if body[-1] == 0xCC:
            reason = "int3-truncated: body ends in padding, not an instruction"
        elif body[0] == 0xE9 and size < 5:
            reason = f"truncated-jmp: {size}-byte body cannot hold a jmp rel32"
        elif terminator(body) is None:
            reason = f"no-terminator: body ends mid-instruction ({body.hex()})"
        else:
            target = jmp_rel32_target(body, rva)
            if target is None or target in starts:
                continue
            reason = (f"mid-instruction-target: jmp rel32 to 0x{target:08X}, "
                      "which is not a function start")
        artifacts[rva] = f"{reason} ({name})"
    return artifacts


BLACKLIST_HEADER = """\
# Ghidra boundary artifacts among the <= {small_max} byte functions: RVAs whose
# retail bytes do not read as a complete function, so no source could ever
# reproduce them. tools/gen_small.py never claims one.
#
# Regenerate (deterministic, from the retail image): python3 tools/gen_small.py classify
# Format: 0x<rva> <reason>
""".format(small_max=SMALL_MAX)


def render_blacklist(artifacts):
    lines = [f"0x{rva:08X} {reason}" for rva, reason in sorted(artifacts.items())]
    return BLACKLIST_HEADER + "\n".join(lines) + "\n"


def read_blacklist():
    """{rva: reason} for the file as it stands, empty when it does not exist."""
    out = {}
    if not BLACKLIST.exists():
        return out
    for line in BLACKLIST.read_text(encoding="utf-8").splitlines():
        if not line.strip() or line.startswith("#"):
            continue
        rva, _, reason = line.partition(" ")
        out[int(rva, 16)] = reason
    return out


def load_blacklist():
    if not BLACKLIST.exists():
        raise SystemExit(f"gen_small: no {BLACKLIST.relative_to(ROOT)} — run "
                         "`python3 tools/gen_small.py classify` first")
    return read_blacklist()


def cmd_classify(_args):
    entries = load_ghidra()
    artifacts = classify(entries, exe_reader())
    # An entry for an RVA outside the inventory came from the gap scan, which
    # classify cannot re-derive; rewriting the file without it would silently
    # re-open a candidate the scan refused.
    inventory = {rva for rva, _, _ in entries}
    artifacts.update({rva: reason for rva, reason in read_blacklist().items()
                      if rva not in inventory})
    text = render_blacklist(artifacts)
    existing = BLACKLIST.read_text(encoding="utf-8") if BLACKLIST.exists() else None
    kinds = {}
    for reason in artifacts.values():
        kinds[reason.split(":")[0]] = kinds.get(reason.split(":")[0], 0) + 1
    detail = ", ".join(f"{count} {kind}" for kind, count in sorted(kinds.items()))
    if text == existing:
        print(f"classify: {len(artifacts)} artifact(s) ({detail}) — 0 new, file unchanged")
        return
    BLACKLIST.write_text(text, encoding="utf-8")
    print(f"classify: wrote {BLACKLIST.relative_to(ROOT)}: "
          f"{len(artifacts)} artifact(s) ({detail})")


# --------------------------------------------------------------------------
# row and pin formatting
# --------------------------------------------------------------------------

def check_field(label, value):
    bad = set(value) & CSV_HOSTILE
    if bad:
        raise FormatError(
            f"{label} contains {sorted(bad)}: {value!r}. functions.csv rows are raw "
            "comma-joined fields with no quoting — use ';' to separate notes.")


def format_row(name, target_rva, target_size, source, notes):
    """One functions.csv line. Every rule the ledger relies on is enforced here."""
    for label, value in [("name", name), ("source", source), ("notes", notes)]:
        check_field(label, value)
    if not name:
        raise FormatError("row name is empty")
    if not isinstance(target_size, int) or target_size <= 0:
        raise FormatError(f"{name}: target_size must be a positive int, got {target_size!r}")
    if not isinstance(target_rva, int) or target_rva < 0:
        raise FormatError(f"{name}: target_rva must be a non-negative int, got {target_rva!r}")
    # export_rva stays empty: a generated identity is not an export.
    return f"{name},,0x{target_rva:08X},{target_size},{source},matched,{notes}"


def format_pin(name, address, notes):
    """One reverse/symbols.csv line (LF-native, name,address,notes)."""
    for label, value in [("name", name), ("notes", notes)]:
        check_field(label, value)
    if not name:
        raise FormatError("pin name is empty")
    if not isinstance(address, int) or address < 0:
        raise FormatError(f"{name}: pin address must be a non-negative int, got {address!r}")
    return f"{name},0x{address:08X},{notes}"


def thunk_symbol(prefix, rva):
    """`?j_00001005@@YAXXZ` — the decorated name MSVC 7.1 gives `void j_00001005()`.

    The row's name column is this exact COFF symbol, so build.py finds the body
    without an `object-symbol=` note.
    """
    return f"?{prefix}_{rva:08x}@@YAXXZ"


# --------------------------------------------------------------------------
# thunk batches
# --------------------------------------------------------------------------

def batch_paths(batch):
    return (GEN_DIR / f"thunks_{batch:03d}.cpp", PENDING_DIR / f"thunks_{batch:03d}.json")


def select_thunks(entries, read, blacklist, claimed, batch_source, limit, index):
    """(picked, subsumed) — the next `limit` claimable `jmp rel32` functions.

    `claimed`: {rva: source} from the ledger. An RVA already claimed by THIS
    batch's source stays selected — that is what makes a rerun after landing
    regenerate the identical file instead of marching on to the next 500.

    `index`: overlap_index over the matched rows. A handful of ghidra "thunks"
    are really the tail `jmp` of a larger function somebody has already matched
    byte-for-byte; the retail bytes belong to that row, so those are returned as
    `subsumed` for the caller to report rather than claimed or silently dropped.
    """
    names = {rva: name for rva, _, name in entries}
    picked, subsumed = [], []
    for rva, size, name in entries:
        if size != 5 or rva in blacklist:
            continue
        target = jmp_rel32_target(read(rva, 5), rva)
        if target is None:
            continue
        owner = claimed.get(rva)
        if owner is not None and owner != batch_source:
            continue
        if owner is None:
            hit = find_overlap(index, rva, 5)
            if hit is not None:
                subsumed.append((rva, name, hit))
                continue
        if target not in names:
            raise FormatError(
                f"thunk {name} at 0x{rva:08X} targets 0x{target:08X}, which has no ghidra "
                "function row — classify should have blacklisted it; rerun classify")
        picked.append((rva, target, names[target]))
        if len(picked) == limit:
            break
    return picked, subsumed


THUNK_HEADER = [
    "// Each j_<rva> reproduces the retail five-byte incremental-link thunk at that",
    "// RVA. Under /O2 a tail call with no arguments is exactly `E9 rel32`, and the",
    "// gate resolves the displacement from the ?b_<target>@@YAXXZ pin in",
    "// reverse/symbols.csv, so the bytes prove the target.",
]


def render_batch(picked, command, header):
    """The thunk TU for `picked` [(rva, target, ...)], under `header`'s rationale."""
    targets = sorted({item[1] for item in picked})
    lines = [f"// Generated by: python3 tools/gen_small.py {command}",
             "// Do not edit by hand; regenerate instead.", "//", *header, ""]
    lines += [f"void b_{target:08x}();" for target in targets]
    lines.append("")
    lines += [f"void j_{rva:08x}() {{ b_{target:08x}(); }}" for rva, target, *_ in picked]
    return "\n".join(lines) + "\n"


def load_claims(skip_dumps=False):
    """{rva: source}, {name: rva} and an overlap index over every ledger row.

    skip_dumps drops gen-dump rows. A dump is retail's own bytes under a
    synthetic name: it fixes a boundary and holds no source, so for the census
    it is a body still to be cracked, not a claim. Every other caller wants the
    dump counted, or it would generate a second body over the same range.
    """
    by_rva, by_name, ranges = {}, {}, []
    for row in B.load_claim_rows(counting_dumps=not skip_dumps, matched_only=False):
        rva = int(row["target_rva"], 16)
        by_rva[rva] = row["source"]
        by_name[row["name"]] = rva
        ranges.append({"rva": rva, "size": int(row["target_size"]),
                       "name": row["name"], "status": row["status"]})
    return by_rva, by_name, overlap_index(ranges)


def dump_boundaries():
    """{rva: (size, name)} for every dump row a generated body may supersede.

    A dump is retail's own bytes under a synthetic name: it fixes a boundary and
    holds no identity, and `validate_rows` already accepts a real body over the
    EXACT same range, retracting and tombstoning the dump in the same
    transaction. Nothing ever reached that path from a recipe engine, because
    the dump row hid its own range from the scan -- and 12,816 of these ranges
    have no ghidra entry at all, so they were never candidates to begin with.

    This set is `validate_rows`' set, spelled the same way: a dump is a gen-dump
    NOTE, never a directory. Keying it on `Code/gen_asm/` withheld the 349 dumps
    in `Code/gen_small/dumps_000.cpp` that land_batch has always superseded
    (tools/tests/test_land_supersede.py), so the scan refused ground the landing
    transaction accepts.

    A boundary is offered only where the dump is the ONLY row at its address.
    `tg_scan` hides a supersedable dump from `owned`, and the overlap index it
    falls back on holds matched ranges only -- so a co-located UNMATCHED row
    would be invisible to both, and validate_rows aborts the whole wave on it.

    Narrower than validate_rows on one point, deliberately: the dump row itself
    has to be `matched`. validate_rows would take over an unmatched scaffold row
    too, but the whole value of a dump boundary here is that its extent is
    PROVEN, and an unmatched row is a hypothesis about an address. Scanning at a
    width nobody verified is the one direction that costs a wave rather than a
    site. (None exist today: the ledger is 100% matched.)
    """
    at_rva = collections.defaultdict(list)
    for row in B.load_claim_rows(counting_dumps=True, matched_only=False):
        at_rva[int(row["target_rva"], 16)].append(row)
    return {rva: (int(rows[0]["target_size"]), rows[0]["name"])
            for rva, rows in at_rva.items()
            if len(rows) == 1 and rows[0]["status"] == "matched"
            and B.is_scaffold_row(rows[0])}


def scan_population(entries, boundaries):
    """`entries` with every dump boundary merged in; the two must agree.

    A dump row's extent is proven -- the bytes it emits ARE the retail bytes over
    that range -- while a ghidra entry is an inference, so where both describe
    one RVA they have to say the same thing, and today they do (29,463 of
    29,463). A disagreement is not a case to route around: it means a range
    whose bytes are already verified is booked at two different widths, and
    picking either silently leaves the loser wrong in every other tool that
    reads it. Reconcile the inventory instead.
    """
    disputed = sorted((rva, size, boundaries[rva][0]) for rva, size, _ in entries
                      if rva in boundaries and boundaries[rva][0] != size)
    if disputed:
        detail = ", ".join(f"0x{rva:08X} ghidra={size}B dump={dumped}B"
                           for rva, size, dumped in disputed[:5])
        raise FormatError(
            f"{len(disputed)} address(es) where the ghidra inventory and a proven dump "
            f"boundary disagree on the extent: {detail}. The dump's bytes are verified "
            "over its range, so the inventory is what needs reconciling.")
    merged = {rva: (rva, size, name) for rva, (size, name) in boundaries.items()}
    for rva, size, name in entries:
        merged.setdefault(rva, (rva, size, name))
    return sorted(merged.values())


def load_pins():
    """{name: address} already pinned in reverse/symbols.csv."""
    with B.SYMBOLS.open(encoding="utf-8", newline="") as handle:
        return {r["name"]: int(r["address"], 16) for r in csv.DictReader(handle)}


def cmd_gen_thunks(args):
    entries = load_ghidra()
    read = exe_reader()
    blacklist = load_blacklist()
    claimed, claimed_names, index = load_claims()
    pinned = load_pins()

    source_path, pending_path = batch_paths(args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    picked, subsumed = select_thunks(entries, read, blacklist, claimed, source_rel,
                                     args.limit, index)
    for rva, name, (owner, start, end) in subsumed:
        print(f"gen-thunks: SKIP 0x{rva:08X} {name}: those bytes are inside matched row "
              f"{owner} [0x{start:08X}, 0x{end:08X}) — ghidra cut a boundary inside a "
              "function somebody already byte-matched", file=sys.stderr)
    if not picked:
        print(f"gen-thunks: batch {args.batch}: 0 new — no claimable jmp rel32 functions left"
              + (f" ({len(subsumed)} subsumed by matched rows, listed above)" if subsumed else ""))
        return

    rows, pins = [], []
    for rva, target, target_name in picked:
        name = thunk_symbol("j", rva)
        existing = claimed_names.get(name)
        if existing is not None and existing != rva:
            raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger, "
                              f"but this batch would claim 0x{rva:08X}")
        rows.append(format_row(name, rva, 5, source_rel, f"gen-thunk;target={target_name}"))
        pin_name = thunk_symbol("b", target)
        if pinned.get(pin_name) not in (None, target):
            raise FormatError(f"{pin_name} is pinned at 0x{pinned[pin_name]:08X} in "
                              f"symbols.csv but names body 0x{target:08X}")
        if pin_name not in pinned:
            pins.append(format_pin(pin_name, target, "gen-thunk body"))
            pinned[pin_name] = target

    new_rows = [row for row in rows if row.split(",")[0] not in claimed_names]
    text = render_batch(picked, f"gen-thunks --batch {args.batch} --limit {args.limit}",
                        THUNK_HEADER)
    unchanged = source_path.exists() and source_path.read_text(encoding="utf-8") == text
    if not unchanged:
        GEN_DIR.mkdir(parents=True, exist_ok=True)
        source_path.write_text(text, encoding="utf-8")
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    pending_path.write_text(json.dumps(
        {"source": source_rel, "rows": rows, "pins": pins}, indent=1) + "\n", encoding="utf-8")

    print(f"gen-thunks: batch {args.batch} -> {source_rel}: {len(picked)} thunk(s), "
          f"{len(new_rows)} new row(s), {len(pins)} new pin(s), "
          f"{len(subsumed)} subsumed by matched rows"
          + (" — file unchanged" if unchanged else ""))


# --------------------------------------------------------------------------
# gap thunks
# --------------------------------------------------------------------------
#
# Ghidra's inventory covers 7.4MB of the 13MB .text. The complement is not all
# padding: another ~43k five-byte `E9 rel32` incremental-link thunks sit there,
# in the same tables as the inventoried ones and identical in shape, so the
# round-1 emission claims them unchanged. All the new work is in the finding,
# and the finding has one thing to prove: that five bytes starting with E9 are a
# whole standalone instruction and not the tail of an undiscovered function.
# Both sides of a run must therefore be delimited — padding, a gap boundary, or
# a neighbour that itself ends on a complete instruction — because a claim on a
# function's tail byte-verifies forever while blocking the real function.

PADDING = frozenset((0xCC, 0x90, 0x00))
GAP_NOTE = "gen-thunk;gap"


def text_section():
    """(bytes, lo) of the retail .text — the only section thunks live in."""
    data, sections = B.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    start = text["raw_pointer"]
    return data[start:start + text["size"]], text["rva"]


def covered_intervals(entries, rows):
    """Merged, ascending [start, end) of everything inventoried or matched.

    Ghidra's boundaries and the ledger's matched rows are two independent
    statements about where a function lives; a byte in neither is a byte nobody
    has looked at, and that complement is where the uninventoried thunks are.
    """
    spans = sorted([(rva, rva + size) for rva, size, _ in entries]
                   + [(int(r["target_rva"], 16),
                       int(r["target_rva"], 16) + int(r["target_size"])) for r in rows])
    merged = []
    for start, end in spans:
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    return merged


def text_gaps(merged, lo, hi):
    """[(start, end, neighbour)] — the complement of `merged` inside [lo, hi).

    `neighbour` is the covered span the gap opens straight out of, or None when
    nothing precedes it, so the caller can ask whether that span ends on a whole
    instruction before treating the first bytes after it as their own function.
    """
    gaps, pos, previous = [], lo, None
    for start, end in merged:
        if end <= lo:
            continue
        if start >= hi:
            break
        if start > pos:
            gaps.append((pos, min(start, hi), previous))
        if end > pos:
            pos, previous = end, (max(start, lo), min(end, hi))
    if pos < hi:
        gaps.append((pos, hi, previous))
    return gaps


# A fixed-width body the gap scan can recognize: `size` bytes each, spelled
# `name` in the refusal reasons, and `at(rva, end)` true where one starts.
GapShape = collections.namedtuple("GapShape", "size name at")


def thunk_shape(text, lo):
    return GapShape(5, "thunk",
                    lambda rva, end: rva + 5 <= end and text[rva - lo] == 0xE9)


def scan_gap_runs(text, lo, merged, shape):
    """([rva], {rva: reason}) for the delimited runs of `shape` bodies in the gaps.

    Every candidate the scan touches ends up in exactly one of the two: picked,
    or refused with the reason it is not a standalone function. A run of
    back-to-back bodies is a table only when nothing runs into it — padding or
    the gap's end has to close it, and whatever the gap opens out of has to end
    on a whole instruction. Claiming a larger function's tail instead
    byte-verifies forever while blocking the function it was cut from.
    """
    hi = lo + len(text)
    picked, refused = [], {}

    def skip_to_padding(pos, end):
        while pos < end and text[pos - lo] not in PADDING:
            pos += 1
        return pos

    for start, end, neighbour in text_gaps(merged, lo, hi):
        pos = start
        tail = None if neighbour is None else text[
            max(neighbour[0], neighbour[1] - 8) - lo:neighbour[1] - lo]
        if tail and shape.at(start, end) and terminator(tail) is None:
            refused[start] = (f"gap-unterminated-neighbour: the code ending at 0x{start:08X} "
                              "does not end on a whole instruction, so these bytes may be "
                              f"its tail rather than a {shape.name}")
            pos = skip_to_padding(start, end)
        while pos < end:
            if text[pos - lo] in PADDING:
                pos += 1
                continue
            run_start, run = pos, []
            while shape.at(pos, end):
                run.append(pos)
                pos += shape.size
            if run and (pos >= end or text[pos - lo] in PADDING):
                picked += run
                continue
            for rva in run:
                refused[rva] = (f"gap-undelimited-run: the {shape.name} run at "
                                f"0x{run_start:08X} runs straight into other code, so it is "
                                f"a function tail, not a standalone {shape.name}")
            pos = skip_to_padding(run_start, end)
    return picked, refused


def scan_gap_thunks(text, lo, merged, starts):
    """([(rva, target)], {rva: reason}) for the standalone `E9 rel32` in the gaps.

    `starts` is every known function start, which is what makes a target
    verifiable — inside a known function but not its start means the
    displacement points mid-instruction.
    """
    hi = lo + len(text)
    starts_index = [span[0] for span in merged]
    picked, refused = scan_gap_runs(text, lo, merged, thunk_shape(text, lo))

    claimable = []
    for rva in picked:
        target = rva + 5 + struct.unpack_from("<i", text, rva - lo + 1)[0]
        position = bisect.bisect_right(starts_index, target) - 1
        if not lo <= target < hi:
            refused[rva] = f"gap-target-outside-text: jmp rel32 to 0x{target:08X}"
        elif (target not in starts and position >= 0
              and merged[position][0] < target < merged[position][1]):
            refused[rva] = (f"mid-instruction-target: jmp rel32 to 0x{target:08X}, which is "
                            "inside a known function and is not one's start")
        elif text[target - lo] in (0xCC, 0x90):
            refused[rva] = (f"gap-target-padding: jmp rel32 to 0x{target:08X}, which is "
                            "int3/nop fill, not a function start")
        else:
            claimable.append((rva, target))
    return claimable, refused


def gap_population(entries, blacklist):
    """([(rva, target)], {rva: reason}) over the whole .text complement.

    Rows this generator wrote are excluded from the coverage, so the population
    is the same before and after a batch lands and a rerun regenerates the
    identical file instead of marching on to the next 500.
    """
    text, lo = text_section()
    rows = [r for r in B.load_all_function_rows()
            if r["status"] == "matched" and not r["notes"].startswith(GAP_NOTE)]
    merged = covered_intervals(entries, rows)
    starts = ({rva for rva, _, _ in entries}
              | {int(r["target_rva"], 16) for r in rows})
    claimable, refused = scan_gap_thunks(text, lo, merged, starts)
    return [(rva, target) for rva, target in claimable if rva not in blacklist], refused


def append_blacklist(refused):
    """Record refused candidates in the blacklist; return what this run added.

    A refusal is a statement about the retail bytes, so it belongs in the file
    every generator here consults before claiming an RVA — not in a log line
    that scrolls away.
    """
    known = read_blacklist()
    added = {rva: reason for rva, reason in refused.items() if rva not in known}
    if added:
        BLACKLIST.write_text(render_blacklist({**known, **added}), encoding="utf-8")
    return added


GAP_HEADER = [
    "// The same five-byte incremental-link thunks Code/gen_small/thunks_NNN.cpp claims,",
    "// found in the .text no ghidra function and no matched row covers. Each j_<rva> is",
    "// a standalone `E9 rel32` that padding delimits on both sides, and the gate",
    "// resolves its displacement from the ?b_<target>@@YAXXZ pin in reverse/symbols.csv,",
    "// so the bytes prove the target.",
]


def gap_paths(batch):
    return (GEN_DIR / f"gthunks_{batch:03d}.cpp", PENDING_DIR / f"gthunks_{batch:03d}.json")


def select_gap_thunks(candidates, claimed, batch_source, limit, index):
    """(picked, subsumed) — the next `limit` claimable gap thunks.

    Same contract as select_thunks: an RVA already claimed by THIS batch's
    source stays selected, and one whose bytes a matched row owns is reported
    rather than claimed or silently dropped.
    """
    picked, subsumed = [], []
    for rva, target in candidates:
        owner = claimed.get(rva)
        if owner is not None and owner != batch_source:
            continue
        if owner is None:
            hit = find_overlap(index, rva, 5)
            if hit is not None:
                subsumed.append((rva, hit))
                continue
        picked.append((rva, target))
        if len(picked) == limit:
            break
    return picked, subsumed


def cmd_gen_gap_thunks(args):
    entries = load_ghidra()
    blacklist = load_blacklist()
    candidates, refused = gap_population(entries, blacklist)
    added = append_blacklist(refused)
    claimed, claimed_names, index = load_claims()
    pinned = load_pins()

    source_path, pending_path = gap_paths(args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    picked, subsumed = select_gap_thunks(candidates, claimed, source_rel, args.limit, index)
    for rva, (owner, start, end) in subsumed:
        print(f"gen-gap-thunks: SKIP 0x{rva:08X}: those bytes are inside matched row "
              f"{owner} [0x{start:08X}, 0x{end:08X})", file=sys.stderr)
    kinds = collections.Counter(reason.split(":")[0] for reason in refused.values())
    print(f"gen-gap-thunks: gap population {len(candidates) + len(refused)} candidate(s) = "
          f"{len(candidates)} claimable + {len(refused)} refused "
          + f"({', '.join(f'{count} {kind}' for kind, count in sorted(kinds.items()))})"
          + f"; {len(added)} newly blacklisted")
    if not picked:
        print(f"gen-gap-thunks: batch {args.batch}: 0 new — no claimable gap thunks left"
              + (f" ({len(subsumed)} subsumed by matched rows, listed above)" if subsumed else ""))
        return

    rows, pins = [], []
    for rva, target in picked:
        name = thunk_symbol("j", rva)
        existing = claimed_names.get(name)
        if existing is not None and existing != rva:
            raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger, "
                              f"but this batch would claim 0x{rva:08X}")
        rows.append(format_row(name, rva, 5, source_rel, f"{GAP_NOTE};target=0x{target:08X}"))
        pin_name = thunk_symbol("b", target)
        if pinned.get(pin_name) not in (None, target):
            raise FormatError(f"{pin_name} is pinned at 0x{pinned[pin_name]:08X} in "
                              f"symbols.csv but names body 0x{target:08X}")
        if pin_name not in pinned:
            pins.append(format_pin(pin_name, target, "gen-thunk body"))
            pinned[pin_name] = target

    new_rows = [row for row in rows if row.split(",")[0] not in claimed_names]
    text = render_batch(picked, f"gen-gap-thunks --batch {args.batch} --limit {args.limit}",
                        GAP_HEADER)
    unchanged = source_path.exists() and source_path.read_text(encoding="utf-8") == text
    if not unchanged:
        GEN_DIR.mkdir(parents=True, exist_ok=True)
        source_path.write_text(text, encoding="utf-8")
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    pending_path.write_text(json.dumps(
        {"source": source_rel, "rows": rows, "pins": pins}, indent=1) + "\n", encoding="utf-8")

    print(f"gen-gap-thunks: batch {args.batch} -> {source_rel}: {len(picked)} thunk(s), "
          f"{len(new_rows)} new row(s), {len(pins)} new pin(s), "
          f"{len(subsumed)} subsumed by matched rows"
          + (" — file unchanged" if unchanged else ""))


# --------------------------------------------------------------------------
# EH handler stubs
# --------------------------------------------------------------------------

EH_NOTE = "gen-ehstub"
EH_SOURCE = "Code/gen_small/eh_anchor.cpp"
EH_STUB_SIZE = 10
# The `jmp` every handler stub ends on. 0x009F6DD6 is the `FF 25` import thunk
# for __CxxFrameHandler (already claimed as ?ji_009f6dd6@@YAXXZ), which is what
# the retail stubs actually reach, so it is also where the anchor obj's REL32 to
# ___CxxFrameHandler has to resolve.
EH_HANDLER_RVA = 0x009F6DD6
# Read back out of the compiled anchor rather than trusted: MSVC's leading
# underscore on a C symbol makes the decorated spelling easy to get wrong.
EH_HANDLER_SYMBOL = "___CxxFrameHandler"
EH_SPIKE_SAMPLES = 3


def eh_stub_shape(text, lo):
    """`B8 <funcinfo> E9 <rel32 to the __CxxFrameHandler thunk>`, ten bytes.

    The jmp target is part of the shape, not a later check: these bytes only
    mean "EH handler stub" because of where the jmp goes, and `B8 imm32` in
    front of some unrelated `E9` is a two-instruction coincidence otherwise.
    """
    def at(rva, end):
        pos = rva - lo
        return (rva + EH_STUB_SIZE <= end and text[pos] == 0xB8 and text[pos + 5] == 0xE9
                and rva + EH_STUB_SIZE
                + struct.unpack_from("<i", text, pos + 6)[0] == EH_HANDLER_RVA)
    return GapShape(EH_STUB_SIZE, "EH handler stub", at)


def eh_population(entries, blacklist):
    """([rva], {rva: reason}) over the whole .text complement.

    Rows this generator wrote are excluded from the coverage, so the population
    is the same before and after a chunk lands; `select_eh_stubs` is what skips
    the ones already claimed and moves on to the next chunk.
    """
    text, lo = text_section()
    rows = [r for r in B.load_all_function_rows()
            if r["status"] == "matched" and not r["notes"].startswith(EH_NOTE)]
    merged = covered_intervals(entries, rows)
    picked, refused = scan_gap_runs(text, lo, merged, eh_stub_shape(text, lo))
    return [rva for rva in picked if rva not in blacklist], refused


def eh_anchor_symbol(data):
    """The one `__ehhandler$` symbol the anchor obj defines."""
    names = sorted({s["name"] for s in B.read_object_symbols(data)
                    if s["section"] > 0 and s["name"].startswith("__ehhandler$")})
    if len(names) != 1:
        raise FormatError(
            f"{EH_SOURCE} compiles to {len(names)} __ehhandler$ symbol(s) ({names}); it must "
            "define exactly one, or the rows cannot name which stub they claim")
    return names[0]


def build_eh_anchor():
    """(symbol, body, relocs) for the anchor's handler stub, refusing any other shape.

    Everything the rows depend on is asserted here rather than assumed: the stub
    is ten bytes, its funcinfo operand is the DIR32 site build.py copies from
    each target, and its jmp is a REL32 to the CRT handler this module pins.
    """
    source = ROOT / EH_SOURCE
    if not source.exists():
        raise SystemExit(f"gen_small: {EH_SOURCE} does not exist — the EH anchor TU is the "
                         "one thing this command cannot generate")
    obj = B.obj_path(source)
    B.compile_source(source, obj)
    data = obj.read_bytes()
    symbol = eh_anchor_symbol(data)
    body, relocs = B.read_object_symbol_bytes(obj, symbol, EH_STUB_SIZE)
    if len(body) != EH_STUB_SIZE:
        raise FormatError(f"{symbol} is {len(body)} bytes in the anchor obj, not {EH_STUB_SIZE} "
                          f"({body.hex(' ')}) — it is not the retail stub shape")
    sites = {offset: (rtype, name) for offset, rtype, name in relocs}
    if sorted(sites) != [1, 6]:
        raise FormatError(f"{symbol} relocates at offsets {sorted(sites)}, expected [1, 6] "
                          "(the funcinfo operand and the jmp displacement)")
    if sites[1][0] != 0x0006:
        raise FormatError(f"{symbol}'s funcinfo operand at +1 is reloc type "
                          f"0x{sites[1][0]:04X}, not DIR32 — build.py only copies DIR32 sites "
                          "from the target, so the per-stub funcinfo would not be wildcarded")
    if sites[6] != (0x0014, EH_HANDLER_SYMBOL):
        raise FormatError(f"{symbol}'s jmp at +6 relocates as {sites[6]}, expected "
                          f"(0x0014, {EH_HANDLER_SYMBOL}) — the pin would resolve the wrong "
                          "symbol")
    return symbol, body, relocs


def spike_eh_anchor(text, lo, body, exemplars):
    """Prove the anchor's bytes ARE the retail stub, against `exemplars`.

    Masked, because two operands are per-site by construction: the funcinfo
    pointer is the DIR32 site the gate copies from each target, and the jmp
    displacement is a function of the stub's own address, so it is checked as
    arithmetic — it has to be exactly the distance from this RVA to the handler.
    Everything outside those two operands has to be equal. One exemplar that
    differs means the anchor is not what the retail compiler emitted, and no row
    may be written on the strength of it.
    """
    if len(exemplars) < EH_SPIKE_SAMPLES:
        raise FormatError(f"only {len(exemplars)} exemplar(s) available, need "
                          f"{EH_SPIKE_SAMPLES} to spike the anchor")
    for rva in exemplars[:EH_SPIKE_SAMPLES]:
        target = text[rva - lo:rva - lo + EH_STUB_SIZE]
        masked = (target[0:1] + body[1:5] + target[5:6] + body[6:10])
        expected = body[0:1] + body[1:5] + body[5:6] + body[6:10]
        if masked != expected:
            raise FormatError(
                f"spike FAILED at 0x{rva:08X}: retail {target.hex(' ')} vs anchor "
                f"{body.hex(' ')} differ outside the funcinfo operand")
        displacement = struct.unpack_from("<i", target, 6)[0]
        reached = rva + EH_STUB_SIZE + displacement
        if reached != EH_HANDLER_RVA:
            raise FormatError(
                f"spike FAILED at 0x{rva:08X}: jmp displacement {displacement:#010x} reaches "
                f"0x{reached:08X}, not the handler at 0x{EH_HANDLER_RVA:08X}")
        print(f"gen-ehstubs: spike 0x{rva:08X} masked-exact ({target.hex(' ')}); "
              f"disp 0x{displacement & 0xFFFFFFFF:08X} == 0x{EH_HANDLER_RVA:08X} - "
              f"(0x{rva:08X} + {EH_STUB_SIZE})")
    print(f"gen-ehstubs: spike {EH_SPIKE_SAMPLES}/{EH_SPIKE_SAMPLES} masked-exact against the "
          f"image — anchor reproduces the retail stub")


def select_eh_stubs(candidates, claimed, limit, index):
    """(picked, subsumed) — the next `limit` unclaimed stubs.

    Unlike the batched thunk engines every chunk here shares one source, so
    "already claimed by this source" cannot mean "keep selecting it" — that
    would pin every rerun to the first chunk forever. Skipping every claimed RVA
    instead is what makes consecutive runs walk forward through the population
    and the run after the last one report nothing left.
    """
    picked, subsumed = [], []
    for rva in candidates:
        if rva in claimed:
            continue
        hit = find_overlap(index, rva, EH_STUB_SIZE)
        if hit is not None:
            subsumed.append((rva, hit))
            continue
        picked.append(rva)
        if len(picked) == limit:
            break
    return picked, subsumed


def cmd_gen_ehstubs(args):
    entries = load_ghidra()
    blacklist = load_blacklist()
    candidates, refused = eh_population(entries, blacklist)
    added = append_blacklist(refused)
    text, lo = text_section()

    # The spike runs before anything is selected, let alone written: the whole
    # claim rests on one compiled stub standing in for thousands of retail ones,
    # so that has to be proved against the image first or not attempted at all.
    symbol, body, _ = build_eh_anchor()
    spike_eh_anchor(text, lo, body, candidates)

    claimed, claimed_names, index = load_claims()
    picked, subsumed = select_eh_stubs(candidates, claimed, args.limit, index)
    for rva, (owner, start, end) in subsumed:
        print(f"gen-ehstubs: SKIP 0x{rva:08X}: those bytes are inside matched row "
              f"{owner} [0x{start:08X}, 0x{end:08X})", file=sys.stderr)
    kinds = collections.Counter(reason.split(":")[0] for reason in refused.values())
    print(f"gen-ehstubs: gap population {len(candidates) + len(refused)} candidate(s) = "
          f"{len(candidates)} claimable + {len(refused)} refused "
          + f"({', '.join(f'{count} {kind}' for kind, count in sorted(kinds.items())) or 'none'})"
          + f"; {len(added)} newly blacklisted")
    if not picked:
        print(f"gen-ehstubs: 0 new — every claimable stub is already in the ledger"
              + (f" ({len(subsumed)} subsumed by matched rows, listed above)" if subsumed else ""))
        return

    note = f"{EH_NOTE};object-symbol={symbol}"
    rows = []
    for rva in picked:
        name = f"eh_{rva:08x}"
        existing = claimed_names.get(name)
        if existing is not None and existing != rva:
            raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger, "
                              f"but this chunk would claim 0x{rva:08X}")
        rows.append(format_row(name, rva, EH_STUB_SIZE, EH_SOURCE, note))

    pins = []
    if load_pins().get(EH_HANDLER_SYMBOL) != EH_HANDLER_RVA:
        pins.append(format_pin(EH_HANDLER_SYMBOL, EH_HANDLER_RVA,
                               "__CxxFrameHandler import thunk; every __ehhandler$ stub jmps here"))

    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    pending_path = PENDING_DIR / (Path(EH_SOURCE).stem + ".json")
    pending_path.write_text(json.dumps(
        {"source": EH_SOURCE, "rows": rows, "pins": pins}, indent=1) + "\n", encoding="utf-8")
    remaining = sum(1 for rva in candidates if rva not in claimed) - len(picked)
    print(f"gen-ehstubs: {len(picked)} stub(s) -> {pending_path.relative_to(ROOT)}: "
          f"{len(rows)} new row(s), {len(pins)} new pin(s), {remaining} still unclaimed, "
          f"{len(subsumed)} subsumed by matched rows")


# --------------------------------------------------------------------------
# deleting destructors
# --------------------------------------------------------------------------
#
# A class with a virtual destructor gets a compiler-generated deleting
# destructor: `??_G` calls the class destructor and then `operator delete`,
# `??_E` does the same over an array through `__ehvec_dtor`. Not one line of the
# game's source is in either, so a synthetic class with a virtual destructor
# reproduces one exactly, and the only bytes that differ between two classes'
# copies are the four-byte relocation slots.
#
# That is what makes the family claimable in bulk and what makes it dangerous:
# every deleting destructor of a shape masked-matches every other one, which is
# how 205 class names once came to be claimed on a single body
# (tools/audit_dtor_aliases.py). So these identities are deliberately anonymous
# -- Gen_dtor_<rva> names an address, never a class -- and every operand is read
# out of the retail bytes rather than assumed: the class destructor each body
# calls becomes that member's own pin, and a body whose operator-delete slot
# reaches anything but the CRT's is refused, because a class that overrides
# operator delete is not the class this recipe writes.

DTOR_NOTE = "gen-dtor"
# The probe class's sizeof, and so the element stride in the vector template.
# Any value works; it is what makes the immediate identifiable in the bytes.
DTOR_PROBE_ELEMENT = 8
DTOR_PROBE_TAG = "probe"

# The CRT helpers a deleting destructor calls, by the COFF symbol the compiled
# template relocates against, with every address the retail image is allowed to
# reach through that slot. Both are checked, never trusted: the symbol names are
# asserted against the compiled probe's relocations, and a member whose slot
# reaches an address that is not listed is refused by name instead of claimed.
# `??3` is one address on purpose -- a scalar `delete this` that lands anywhere
# else belongs to a class with its own operator delete, which this recipe would
# silently misdescribe.
# `??_V` is one address for the same reason: MSVC 7.1 routes `delete[]` to plain
# `operator delete` in a TU that never declares `operator delete[]`, so the
# retail image holds both spellings of the array slot. The emitted TU declares
# it, which fixes the call at `??_V`, and a body that took the other route is
# refused rather than resolved through the `??_V` pin that also sits on
# 0x00881EB0 for unrelated W3D containers.
DTOR_HELPERS = {
    "??3@YAXPAX@Z": ((0x00881EB0,), "op-delete", "scalar operator delete"),
    "??_V@YAXPAX@Z": ((0x00881EF0,), "array-delete", "array operator delete"),
    "??_M@YGXPAXIHP6EX0@Z@Z": ((0x009F6D76,), "ehvec", "__ehvec_dtor"),
}

# key       subcommand's --kind, and the notes marker's suffix
# klass     synthetic class prefix; the row name is its mangled deleting dtor
# stem      Code/gen_small/<stem>_NNN.cpp
# size      the retail body size this template must compile to
# flags     the `// cl:` line the emitted TU needs, if any
# relocs    (role, COFF reloc type) in offset order; "dtor" is the class
#           destructor, anything else is a DTOR_HELPERS symbol
# element   True when the body carries the class's sizeof as an immediate
# preamble  file-scope declarations every class in the TU needs
DtorKind = collections.namedtuple(
    "DtorKind", "key tag klass stem size flags relocs element preamble")

DTOR_KINDS = {
    "scalar": DtorKind(
        "scalar", "??_G", "Gen_dtor", "dtors", 30, (),
        (("dtor", 0x0014), ("??3@YAXPAX@Z", 0x0014)), False, ()),
    "vector": DtorKind(
        "vector", "??_E", "Gen_dtorv", "dtorsv", 84, ("/EHsc",),
        (("dtor", 0x0006), ("??_M@YGXPAXIHP6EX0@Z@Z", 0x0014),
         ("??_V@YAXPAX@Z", 0x0014), ("dtor", 0x0014), ("??3@YAXPAX@Z", 0x0014)), True,
        # Undeclared, `delete[]` compiles to a call to scalar operator delete and
        # the array slot relocates against ??3 instead of ??_V.
        ("void operator delete[](void *);",)),
}

# body/mask: the template and which of its bytes carry meaning; segments: the
# meaningful bytes as (offset, expected) slices, which is what the scan compares
# so a candidate is rejected on one slice compare instead of 84 index reads.
DtorSkeleton = collections.namedtuple(
    "DtorSkeleton", "kind size body mask segments slots element")
DtorMember = collections.namedtuple("DtorMember", "rva ghidra dtor element helpers")


def dtor_symbol(kind, tag):
    """`??_GGen_dtor_0005fa60@@UAEPAXI@Z` — the row's name and the COFF symbol."""
    return f"{kind.tag}{kind.klass}_{tag}@@UAEPAXI@Z"


def dtor_pin_symbol(kind, tag):
    """`??1Gen_dtor_0005fa60@@UAE@XZ` — the class destructor the body calls."""
    return f"??1{kind.klass}_{tag}@@UAE@XZ"


def dtor_class(kind, tag, element):
    """The synthetic class and the uses that force its deleting destructor out.

    The forcers are the whole reason this compiles to anything: a virtual
    destructor alone emits no code, instantiating the class pulls the vtable, and
    the vtable pulls `??_G`. `??_E` needs more -- without a heap `new[]` MSVC
    emits it as a weak alias of `??_G` and there is no body to compare -- and it
    needs the class to be exactly `element` bytes wide, because that width is an
    immediate in the retail bytes.
    """
    name = f"{kind.klass}_{tag}"
    if not kind.element:
        return (f"struct {name} {{ virtual ~{name}(); }};\n"
                f"void gen_force_{tag}() {{ {name} v; }}\n")
    pad = "" if element == 4 else f" int pad[{element // 4 - 1}];"
    return (f"struct {name} {{ virtual ~{name}();{pad} }};\n"
            f"{name} *gen_new_{tag}() {{ return new {name}[2]; }}\n"
            f"void gen_kill_{tag}({name} *p) {{ delete[] p; }}\n")


DTOR_HEADER = {
    "scalar": [
        "// Each ??_GGen_dtor_<rva> reproduces the retail scalar deleting destructor at",
        "// that RVA: call the class destructor, then `operator delete` when the caller",
        "// passed the delete flag. The class is synthetic and anonymous by design -- the",
        "// bytes identify the shape, never which class owned it -- and the gate resolves",
        "// the destructor call from that member's ??1Gen_dtor_<rva> pin in",
        "// reverse/symbols.csv, so the bytes prove the target.",
    ],
    "vector": [
        "// Each ??_EGen_dtorv_<rva> reproduces the retail vector deleting destructor at",
        "// that RVA: run the class destructor over the array through __ehvec_dtor, then",
        "// `operator delete[]`. Each class is padded to the element width the retail body",
        "// hands __ehvec_dtor, and the heap `new[]` is what makes MSVC emit a real ??_E",
        "// body instead of a weak alias of ??_G.",
    ],
}


def render_dtors(kind, members, command):
    """The TU for `members` [(tag, element size)], with its rationale on top."""
    lines = []
    if kind.flags:
        lines.append("// cl: " + " ".join(kind.flags))
    lines += [f"// Generated by: python3 tools/gen_small.py {command}",
              "// Do not edit by hand; regenerate instead.", "//",
              *DTOR_HEADER[kind.key], ""]
    lines += [*kind.preamble, ""] if kind.preamble else []
    lines += [dtor_class(kind, tag, element) for tag, element in members]
    return "\n".join(lines)


def dtor_skeleton(kind, body, relocs, dtor_name):
    """The masked template `kind`'s members must reproduce, from a compiled probe.

    The mask is the relocation slots and nothing else: those four-byte holes are
    all that differs between two classes' deleting destructors, so equality on
    every other byte is what makes a retail body an instance of this recipe
    rather than a coincidence. The element-size immediate is masked as well and
    honoured by construction instead -- the emitted class is given a matching
    sizeof -- because it is a property of the class, not a relocation.
    """
    if len(body) < kind.size:
        raise FormatError(f"the {kind.key} probe compiled to {len(body)} bytes, not "
                          f"{kind.size} ({body.hex(' ')}) — it is not the retail shape")
    body = bytes(body[:kind.size])
    slots = sorted((offset, rtype, "dtor" if name == dtor_name else name)
                   for offset, rtype, name in relocs if offset < kind.size)
    shape = tuple((role, rtype) for _, rtype, role in slots)
    if shape != kind.relocs:
        raise FormatError(
            f"the {kind.key} probe relocates as {list(shape)}, expected "
            f"{list(kind.relocs)} — the template does not call what this engine claims "
            "it calls, so no member's operands could be read from it")
    unknown = {role for role, _ in shape} - {"dtor"} - set(DTOR_HELPERS)
    if unknown:
        raise FormatError(f"the {kind.key} probe calls unlisted helper(s) {sorted(unknown)}")

    mask = bytearray(b"\xff" * kind.size)
    for offset, _, _ in slots:
        mask[offset:offset + 4] = b"\x00" * 4
    element = None
    if kind.element:
        push = bytes((0x6A, DTOR_PROBE_ELEMENT))
        hits = [i for i in range(kind.size - 1) if body[i:i + 2] == push]
        if len(hits) != 1:
            raise FormatError(
                f"the {kind.key} probe holds {len(hits)} `push {DTOR_PROBE_ELEMENT}` "
                "instructions; the element-size operand is not identifiable, so a member's "
                "class could not be given the width the retail body encodes")
        element = hits[0] + 1
        mask[element] = 0

    segments, start = [], None
    for offset in range(kind.size + 1):
        keep = offset < kind.size and mask[offset]
        if keep and start is None:
            start = offset
        elif not keep and start is not None:
            segments.append((start, body[start:offset]))
            start = None
    return DtorSkeleton(kind, kind.size, body, bytes(mask), tuple(segments),
                        tuple((o, t, r) for o, t, r in slots), element)


def dtor_probe(kind):
    """Compile this kind's recipe once and read its template back out.

    Derived rather than transcribed, and derived from the same renderer the
    batches use: a template that came from anywhere else could describe bytes the
    emitted TU never produces, and the mismatch would only surface as a reverted
    land hours later.
    """
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    source = PENDING_DIR / f"probe_{kind.stem}.cpp"
    source.write_text(render_dtors(kind, [(DTOR_PROBE_TAG, DTOR_PROBE_ELEMENT)],
                                   f"gen-dtors --kind {kind.key} (probe)"), encoding="utf-8")
    obj = B.obj_path(source)
    B.compile_source(source, obj)
    symbol = dtor_symbol(kind, DTOR_PROBE_TAG)
    body, relocs = B.read_object_symbol_bytes(obj, symbol, kind.size)
    skeleton = dtor_skeleton(kind, body, relocs, dtor_pin_symbol(kind, DTOR_PROBE_TAG))
    print(f"gen-dtors: {kind.key} template from {source.relative_to(ROOT)}: {skeleton.size}B "
          f"{skeleton.body.hex(' ')}")
    print(f"gen-dtors: {kind.key} slots " + ", ".join(
        f"+{offset}={role}({'DIR32' if rtype == 0x0006 else 'REL32'})"
        for offset, rtype, role in skeleton.slots)
        + ("" if skeleton.element is None else f", element size at +{skeleton.element}"))
    return skeleton


def dtor_matches(skeleton, body):
    """True when `body` differs from the template only in the masked slots."""
    return (len(body) >= skeleton.size
            and all(body[offset:offset + len(want)] == want
                    for offset, want in skeleton.segments))


def dtor_shape(skeleton, text, lo):
    return GapShape(skeleton.size, f"{skeleton.kind.key} deleting destructor",
                    lambda rva, end: rva + skeleton.size <= end
                    and dtor_matches(skeleton, text[rva - lo:rva - lo + skeleton.size]))


def image_base():
    """The VA a DIR32 operand in the retail image is relative to."""
    data, _ = B.exe_image()
    return B.u32(data, B.u32(data, 0x3C) + 4 + 20 + 28)


def call_targets():
    """target address -> the body addresses a call there could mean.

    Intra-module calls go through incremental-link thunks, so the address in a
    REL32 is often a five-byte `jmp body` rather than the body. Reading a slot's
    operand means resolving that, or two slots naming the same destructor look
    like a disagreement.
    """
    resolved = collections.defaultdict(set)
    for body, thunks in B.build_call_thunks().items():
        for thunk in thunks:
            resolved[thunk].add(body)
    return resolved


def dtor_member(skeleton, rva, ghidra, body, resolved, base):
    """(DtorMember, None) for one candidate, or (None, why it is not claimable).

    Every operand the emitted class has to reproduce is read here, out of the
    retail bytes: the class destructor this body calls, which becomes the
    member's pin, and for the vector kind the element stride handed to
    __ehvec_dtor, which is the class's sizeof and is honoured by giving the
    synthetic class that many bytes. A slot that reaches somewhere this recipe
    cannot describe refuses the member by name -- claiming it would byte-verify
    forever on a body whose real class this source does not model.
    """
    dtors, helpers = [], {}
    for offset, rtype, role in skeleton.slots:
        if rtype == 0x0006:
            reached = struct.unpack_from("<I", body, offset)[0] - base
        else:
            reached = rva + offset + 4 + struct.unpack_from("<i", body, offset)[0]
        if role == "dtor":
            dtors.append((offset, rtype, reached))
            continue
        allowed, label, _ = DTOR_HELPERS[role]
        if not ({reached} | resolved.get(reached, set())) & set(allowed):
            return None, (f"{label}-target-mismatch: slot +{offset} reaches 0x{reached:08X}, "
                          f"not {' or '.join(f'0x{a:08X}' for a in allowed)} ({role})")
        helpers[role] = reached

    if not set.intersection(*({reached} | resolved.get(reached, set())
                              for _, _, reached in dtors)):
        return None, ("dtor-slot-disagreement: " + ", ".join(
            f"+{offset} reaches 0x{reached:08X}" for offset, _, reached in dtors)
            + " — the slots name different destructors, so neither can be pinned")

    element = None
    if skeleton.element is not None:
        element = body[skeleton.element]
        if element < 4 or element % 4:
            return None, (f"elem-size-unreachable: the body hands __ehvec_dtor a stride of "
                          f"{element}, which is not a vptr plus whole int fields")
    # The REL32 is what the gate has to reproduce, so that is what gets pinned; a
    # DIR32 slot is copied from the retail bytes and needs no symbol at all.
    target = next(reached for _, rtype, reached in dtors if rtype == 0x0014)
    return DtorMember(rva, ghidra, target, element, helpers), None


def dtor_population(skeleton, entries, blacklist):
    """([(rva, ghidra name, body)], {rva: reason}) — every body of this shape.

    Two sources, one template: the inventory functions ghidra sized exactly like
    it, and the same bodies in the .text no inventory row and no matched row
    covers, found by the shared gap scan. Rows this generator wrote are excluded
    from the coverage, so the population is the same before and after a batch
    lands and a rerun regenerates the identical file instead of marching on.
    """
    read = exe_reader()
    found = []
    for rva, size, name in entries:
        if size != skeleton.size or rva in blacklist:
            continue
        body = read(rva, size)
        if dtor_matches(skeleton, body):
            found.append((rva, name, body))
    rows = [r for r in B.load_all_function_rows()
            if r["status"] == "matched" and not r["notes"].startswith(DTOR_NOTE)]
    text, lo = text_section()
    picked, refused = scan_gap_runs(text, lo, covered_intervals(entries, rows),
                                    dtor_shape(skeleton, text, lo))
    found += [(rva, "gap", bytes(text[rva - lo:rva - lo + skeleton.size]))
              for rva in picked if rva not in blacklist]
    found.sort()
    return found, refused


def dtor_paths(kind, batch):
    return (GEN_DIR / f"{kind.stem}_{batch:03d}.cpp",
            PENDING_DIR / f"{kind.stem}_{batch:03d}.json")


def select_dtors(skeleton, members, claimed, batch_source, limit, index):
    """(picked, subsumed) — the next `limit` claimable members.

    Same contract as select_thunks: an RVA already claimed by THIS batch's source
    stays selected, so a rerun after landing regenerates the identical file, and
    one whose bytes a matched row owns is reported rather than silently dropped.
    """
    picked, subsumed = [], []
    for member in members:
        owner = claimed.get(member.rva)
        if owner is not None and owner != batch_source:
            continue
        if owner is None:
            hit = find_overlap(index, member.rva, skeleton.size)
            if hit is not None:
                subsumed.append((member, hit))
                continue
        picked.append(member)
        if len(picked) == limit:
            break
    return picked, subsumed


def verify_dtors(skeleton, source_path, members):
    """(verified, [(member, reason)]) — compile the batch and prove every emitted
    body IS the template before a row says it reproduces a retail one.

    The scan proved the retail bytes equal the template outside the masked slots;
    this proves the source about to be committed does too, for this member's own
    class width. Without it a class whose sizeof the compiler rounded differently
    would land as a reverted batch instead of a reported refusal.
    """
    obj = B.obj_path(source_path)
    B.compile_source(source_path, obj)
    verified, failed = [], []
    for member in members:
        symbol = dtor_symbol(skeleton.kind, f"{member.rva:08x}")
        try:
            body, _ = B.read_object_symbol_bytes(obj, symbol, skeleton.size)
        except ValueError:
            failed.append((member, f"symbol-absent: {source_path.name} defines no {symbol}"))
        else:
            if not dtor_matches(skeleton, body):
                failed.append((member, "template-deviation: emitted "
                                       f"{bytes(body[:skeleton.size]).hex(' ')}"))
            elif skeleton.element is not None and body[skeleton.element] != member.element:
                failed.append((member, f"elem-size-not-honoured: emitted a stride of "
                                       f"{body[skeleton.element]}, retail encodes {member.element}"))
            else:
                verified.append(member)
    return verified, failed


def load_pin_addresses():
    """{name: {address}} — symbols.csv is additive, so one name may pin several."""
    out = collections.defaultdict(set)
    with B.SYMBOLS.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            out[row["name"]].add(int(row["address"], 16))
    return out


def dtor_anchor_pins(members, pinned):
    """The CRT-helper pins this population needs, for the ones not already pinned."""
    wanted = collections.defaultdict(set)
    for member in members:
        for symbol, address in member.helpers.items():
            wanted[symbol].add(address)
    pins = []
    for symbol, addresses in sorted(wanted.items()):
        for address in sorted(addresses - pinned.get(symbol, set())):
            if symbol in pinned:
                raise FormatError(
                    f"{symbol} is pinned at "
                    f"{', '.join(f'0x{a:08X}' for a in sorted(pinned[symbol]))} but this "
                    f"population also calls 0x{address:08X}; symbols.csv takes several "
                    "addresses per name, but a batch may not add one — append "
                    f"`{format_pin(symbol, address, DTOR_HELPERS[symbol][2])}` by hand first")
            pins.append(format_pin(symbol, address, DTOR_HELPERS[symbol][2]))
    return pins


def cmd_gen_dtors(args):
    kind = DTOR_KINDS[args.kind]
    entries = load_ghidra()
    blacklist = load_blacklist()
    skeleton = dtor_probe(kind)
    candidates, refused = dtor_population(skeleton, entries, blacklist)
    added = append_blacklist(refused)
    kinds = collections.Counter(reason.split(":")[0] for reason in refused.values())
    print(f"gen-dtors: {kind.key} population {len(candidates) + len(refused)} candidate(s) = "
          f"{len(candidates)} of the template + {len(refused)} gap-refused "
          + f"({', '.join(f'{count} {name}' for name, count in sorted(kinds.items())) or 'none'})"
          + f"; {len(added)} newly blacklisted")

    resolved, base = call_targets(), image_base()
    members, unclaimable = [], []
    for rva, ghidra, body in candidates:
        member, reason = dtor_member(skeleton, rva, ghidra, body, resolved, base)
        if member is None:
            unclaimable.append((rva, ghidra, reason))
        else:
            members.append(member)
    for rva, ghidra, reason in unclaimable:
        print(f"gen-dtors: REFUSED 0x{rva:08X} {ghidra}: {reason}", file=sys.stderr)

    claimed, claimed_names, index = load_claims()
    source_path, pending_path = dtor_paths(kind, args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    picked, subsumed = select_dtors(skeleton, members, claimed, source_rel, args.limit, index)
    for member, (owner, start, end) in subsumed:
        print(f"gen-dtors: SKIP 0x{member.rva:08X}: those bytes are inside matched row "
              f"{owner} [0x{start:08X}, 0x{end:08X})", file=sys.stderr)
    if not picked:
        print(f"gen-dtors: {kind.key} batch {args.batch}: 0 new — every claimable "
              f"{kind.tag} body is already in the ledger ({len(members)} of the template, "
              f"{len(unclaimable)} refused, {len(subsumed)} subsumed by matched rows)")
        return

    GEN_DIR.mkdir(parents=True, exist_ok=True)
    text = render_dtors(kind, [(f"{m.rva:08x}", m.element) for m in picked],
                        f"gen-dtors --kind {kind.key} --batch {args.batch} "
                        f"--limit {args.limit}")
    source_path.write_text(text, encoding="utf-8")
    verified, failed = verify_dtors(skeleton, source_path, picked)
    for member, reason in failed:
        print(f"gen-dtors: TEMPLATE-FAILED 0x{member.rva:08X} {member.ghidra}: {reason}",
              file=sys.stderr)
    if failed:
        text = render_dtors(kind, [(f"{m.rva:08x}", m.element) for m in verified],
                            f"gen-dtors --kind {kind.key} --batch {args.batch} "
                            f"--limit {args.limit}")
        source_path.write_text(text, encoding="utf-8")

    pinned = load_pin_addresses()
    rows, pins = [], dtor_anchor_pins(verified, pinned)
    for member in verified:
        tag = f"{member.rva:08x}"
        name = dtor_symbol(kind, tag)
        existing = claimed_names.get(name)
        if existing is not None and existing != member.rva:
            raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger, "
                              f"but this batch would claim 0x{member.rva:08X}")
        rows.append(format_row(name, member.rva, skeleton.size, source_rel,
                               f"{DTOR_NOTE};ghidra={member.ghidra}"))
        pin_name = dtor_pin_symbol(kind, tag)
        if pinned.get(pin_name, {member.dtor}) != {member.dtor}:
            raise FormatError(f"{pin_name} is pinned at "
                              f"{', '.join(f'0x{a:08X}' for a in sorted(pinned[pin_name]))} in "
                              f"symbols.csv but names body 0x{member.dtor:08X}")
        if pin_name not in pinned:
            pins.append(format_pin(pin_name, member.dtor, f"{DTOR_NOTE} class destructor"))
            pinned[pin_name] = {member.dtor}

    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    pending_path.write_text(json.dumps(
        {"source": source_rel, "rows": rows, "pins": pins}, indent=1) + "\n", encoding="utf-8")
    new_rows = [row for row in rows if row.split(",")[0] not in claimed_names]
    # Counted against what this run would newly claim, not against everything it
    # selected: a rerun after landing reselects its own members, and subtracting
    # those a second time reports a negative backlog.
    remaining = sum(1 for m in members if m.rva not in claimed) - sum(
        1 for m in verified if m.rva not in claimed)
    print(f"gen-dtors: {kind.key} batch {args.batch} -> {source_rel}: {len(verified)} "
          f"member(s), {len(new_rows)} new row(s), {len(pins)} new pin(s), {remaining} still "
          f"unclaimed, {len(unclaimable)} refused, {len(failed)} template-failed, "
          f"{len(subsumed)} subsumed by matched rows")
    if len(members) + len(unclaimable) != len(candidates):
        raise FormatError(f"report accounts for {len(members) + len(unclaimable)} of "
                          f"{len(candidates)} candidates")


# --------------------------------------------------------------------------
# import thunks
# --------------------------------------------------------------------------

def import_paths(batch):
    return (GEN_DIR / f"imports_{batch:03d}.cpp", PENDING_DIR / f"imports_{batch:03d}.json")


def iat_slot(body):
    """The IAT address a six-byte `jmp dword ptr [addr]` reads, or None."""
    if len(body) != 6 or body[0] != 0xFF or body[1] != 0x25:
        return None
    return struct.unpack_from("<I", body, 2)[0]


def select_imports(entries, read, blacklist, claimed, batch_source, limit):
    """The next `limit` claimable `FF 25` import thunks, ascending by rva."""
    picked = []
    for rva, size, name in entries:
        if size != 6 or rva in blacklist:
            continue
        slot = iat_slot(read(rva, 6))
        if slot is None:
            continue
        owner = claimed.get(rva)
        if owner is not None and owner != batch_source:
            continue
        picked.append((rva, slot, name))
        if len(picked) == limit:
            break
    return picked


def render_imports(picked, batch, limit):
    lines = [
        f"// Generated by: python3 tools/gen_small.py gen-imports --batch {batch} --limit {limit}",
        "// Do not edit by hand; regenerate instead.",
        "//",
        "// Each ji_<rva> reproduces the retail six-byte import thunk at that RVA. A",
        "// tail call to a __declspec(dllimport) function is exactly `FF 25` plus a DIR32",
        "// reloc on the __imp_ slot, and the gate copies DIR32 sites from the retail",
        "// bytes, so these rows prove the opcode and the length, not the slot: the IAT",
        "// address the retail thunk reads is recorded in each row's notes instead.",
        "",
    ]
    lines += [f"__declspec(dllimport) void i_{rva:08x}();" for rva, _, _ in picked]
    lines.append("")
    lines += [f"void ji_{rva:08x}() {{ i_{rva:08x}(); }}" for rva, _, _ in picked]
    return "\n".join(lines) + "\n"


def cmd_gen_imports(args):
    entries = load_ghidra()
    read = exe_reader()
    blacklist = load_blacklist()
    claimed, claimed_names, _ = load_claims()

    source_path, pending_path = import_paths(args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    picked = select_imports(entries, read, blacklist, claimed, source_rel, args.limit)
    if not picked:
        print(f"gen-imports: batch {args.batch}: 0 new — no claimable import thunks left")
        return

    rows = []
    for rva, slot, target_name in picked:
        name = thunk_symbol("ji", rva)
        existing = claimed_names.get(name)
        if existing is not None and existing != rva:
            raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger, "
                              f"but this batch would claim 0x{rva:08X}")
        rows.append(format_row(name, rva, 6, source_rel,
                               f"gen-import;slot=0x{slot:08X};target={target_name}"))

    new_rows = [row for row in rows if row.split(",")[0] not in claimed_names]
    text = render_imports(picked, args.batch, args.limit)
    unchanged = source_path.exists() and source_path.read_text(encoding="utf-8") == text
    if not unchanged:
        GEN_DIR.mkdir(parents=True, exist_ok=True)
        source_path.write_text(text, encoding="utf-8")
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    pending_path.write_text(json.dumps(
        {"source": source_rel, "rows": rows, "pins": []}, indent=1) + "\n", encoding="utf-8")

    print(f"gen-imports: batch {args.batch} -> {source_rel}: {len(picked)} import thunk(s), "
          f"{len(new_rows)} new row(s)" + (" — file unchanged" if unchanged else ""))


# --------------------------------------------------------------------------
# FUN_* skeleton shims
# --------------------------------------------------------------------------
#
# The anonymous FUN_* bodies have no recoverable identity, but 1,202 of them are
# instances of a few dozen instruction skeletons whose every operand is readable
# from the retail bytes: a getter is `8B 41 <disp>`, a vtable-pointer store is
# `C7 01 <imm32>`. One C++ struct method per body reproduces the skeleton, with
# the operands substituted, and the gate proves the result byte-for-byte.
#
# They are struct methods rather than free functions because the ledger row's
# name is then the method's real decorated name (`?m@Gen_<rva>@@QAEHXZ`), which
# is what find_declared_unmatched's mangled-substring rule pairs with the
# definition at commit time. Every row's notes start with `gen-shim;` so the set
# stays greppable when a real identity turns up later.

FIELD_WIDTH = {"u8": 1, "s8": 1, "u16": 2, "u32": 4, "s32": 4, "rel32": 4}

# key      short name; also the notes marker and the report's row label
# pattern  retail byte template; `{name:kind}` captures an operand
# ret/args/mangle/body  the C++ method and the decorated name it compiles to
# extern   one file-scope declaration the body needs (deduplicated per file)
# pin      symbols.csv name for a call target, so the gate resolves the REL32
# Operand substitution is %-formatting so C++ braces need no escaping.
Skeleton = collections.namedtuple(
    "Skeleton", "key pattern ret args mangle body extern pin")
Skeleton.__new__.__defaults__ = (None, None)

SKELETONS = [
    # empty bodies
    Skeleton("ret-void", "C3", "void", "", "QAEXXZ", ""),
    Skeleton("ret-void-4", "C2 04 00", "void", "int a", "QAEXH@Z", ""),
    Skeleton("ret-void-8", "C2 08 00", "void", "int a, int b", "QAEXHH@Z", ""),
    # constant returns
    Skeleton("ret-zero", "33 C0 C3", "int", "", "QAEHXZ", "return 0;"),
    Skeleton("ret-zero-4", "33 C0 C2 04 00", "int", "int a", "QAEHH@Z", "return 0;"),
    Skeleton("ret-false", "32 C0 C3", "bool", "", "QAE_NXZ", "return false;"),
    Skeleton("ret-false-4", "32 C0 C2 04 00", "bool", "int a", "QAE_NH@Z", "return false;"),
    Skeleton("ret-true", "B0 01 C3", "bool", "", "QAE_NXZ", "return true;"),
    Skeleton("ret-imm", "B8 {imm:u32} C3", "unsigned", "", "QAEIXZ",
             "return 0x%(imm)08Xu;"),
    Skeleton("ret-this", "8B C1 C3", "void *", "", "QAEPAXXZ", "return this;"),
    Skeleton("ret-this-4", "8B C1 C2 04 00", "void *", "int a", "QAEPAXH@Z",
             "return this;"),
    Skeleton("ret-arg1", "8B 44 24 04 C2 04 00", "int", "int a", "QAEHH@Z", "return a;"),
    # field reads
    Skeleton("getter-0", "8B 01 C3", "int", "", "QAEHXZ", "return *(int *)this;"),
    Skeleton("getter-d8", "8B 41 {d:s8} C3", "int", "", "QAEHXZ",
             "return *(int *)((char *)this %(d_)s);"),
    Skeleton("getter-d32", "8B 81 {d:s32} C3", "int", "", "QAEHXZ",
             "return *(int *)((char *)this %(d_)s);"),
    Skeleton("getter8-d8", "8A 41 {d:s8} C3", "char", "", "QAEDXZ",
             "return *((char *)this %(d_)s);"),
    Skeleton("getter16-d8", "66 8B 41 {d:s8} C3", "short", "", "QAEFXZ",
             "return *(short *)((char *)this %(d_)s);"),
    # field writes
    Skeleton("setter-0", "8B 44 24 04 89 01 C2 04 00", "void", "int a", "QAEXH@Z",
             "*(int *)this = a;"),
    Skeleton("setter-d8", "8B 44 24 04 89 41 {d:s8} C2 04 00", "void", "int a", "QAEXH@Z",
             "*(int *)((char *)this %(d_)s) = a;"),
    Skeleton("setter8-d8", "8A 44 24 04 88 41 {d:s8} C2 04 00", "void", "char a",
             "QAEXD@Z", "*((char *)this %(d_)s) = a;"),
    Skeleton("setter-deref", "8B 09 8B 44 24 04 89 08 C2 04 00", "void", "int a",
             "QAEXH@Z", "**(int **)this = a;"),
    Skeleton("zero8-pair", "32 C0 88 41 {a:s8} 88 41 {b:s8} C3", "void", "", "QAEXXZ",
             "char *p = (char *)this; p[%(a)d] = 0; p[%(b)d] = 0;"),
    Skeleton("store-imm-0", "C7 01 {imm:u32} C3", "void", "", "QAEXXZ",
             "*(unsigned *)this = 0x%(imm)08Xu;"),
    Skeleton("store-imm-d8", "C7 41 {d:s8} {imm:u32} C3", "void", "", "QAEXXZ",
             "*(unsigned *)((char *)this %(d_)s) = 0x%(imm)08Xu;"),
    # this-returning initializers
    Skeleton("this-zero-0", "8B C1 C7 00 00 00 00 00 C3", "void *", "", "QAEPAXXZ",
             "*(unsigned *)this = 0; return this;"),
    Skeleton("this-zero2-0", "8B C1 C7 00 00 00 00 00 C7 40 04 00 00 00 00 C3", "void *",
             "", "QAEPAXXZ", "int *p = (int *)this; p[0] = 0; p[1] = 0; return this;"),
    Skeleton("this-store-arg1", "8B C1 8B 4C 24 04 89 08 C2 04 00", "void *", "int a",
             "QAEPAXH@Z", "*(int *)this = a; return this;"),
    Skeleton("this-store-arg2", "8B C1 8B 4C 24 08 89 08 C2 08 00", "void *",
             "int a, int b", "QAEPAXHH@Z", "*(int *)this = b; return this;"),
    Skeleton("this-copy-arg1", "8B C1 8B 4C 24 04 8B 11 89 10 C2 04 00", "void *",
             "void *o", "QAEPAXPAX@Z", "*(int *)this = *(int *)o; return this;"),
    Skeleton("this-zero3", "8B C1 33 C9 89 08 89 48 04 89 48 08 C3", "void *", "",
             "QAEPAXXZ",
             "int *p = (int *)this; p[0] = 0; p[1] = 0; p[2] = 0; return this;"),
    Skeleton("this-zero3-4", "8B C1 33 C9 89 08 89 48 04 89 48 08 C2 04 00", "void *",
             "int a", "QAEPAXH@Z",
             "int *p = (int *)this; p[0] = 0; p[1] = 0; p[2] = 0; return this;"),
    # pointer adjustors: `p = this + a; return p ? this + b : 0`
    Skeleton("adjustor", "8D 41 {a:s8} 85 C0 74 04 8D 41 {b:s8} C3 33 C0 C3",
             "char *", "", "QAEPADXZ",
             "char *p = (char *)this %(a_)s; "
             "return p ? (char *)this %(b_)s : 0;"),
    # tail-call delegates: load a member pointer, jump to its method
    Skeleton("delegate-0", "8B 09 E9 {t:rel32}", "void", "", "QAEXXZ",
             "((T_%(t)08x *)*(void **)this)->m();",
             extern="struct T_%(t)08x { void m(); };",
             pin=("?m@T_%(t)08x@@QAEXXZ", "t")),
    Skeleton("delegate-d8", "8B 49 {d:s8} E9 {t:rel32}", "void", "", "QAEXXZ",
             "((T_%(t)08x *)*(void **)((char *)this %(d_)s))->m();",
             extern="struct T_%(t)08x { void m(); };",
             pin=("?m@T_%(t)08x@@QAEXXZ", "t")),
    # cdecl one-argument forwarders: push a member, call, pop the argument
    Skeleton("forward-0", "8B 01 50 E8 {t:rel32} 59 C3", "void", "", "QAEXXZ",
             "f_%(t)08x(*(void **)this);",
             extern="void f_%(t)08x(void *);",
             pin=("?f_%(t)08x@@YAXPAX@Z", "t")),
    # null-checked virtual call through the first vtable slot
    Skeleton("vcall-null-0", "8B 09 85 C9 74 06 8B 01 6A 01 FF 10 C3", "void", "",
             "QAEXXZ", "V_ *p = *(V_ **)this; if (p) p->v(1);",
             extern="struct V_ { virtual void v(int); };"),
    # The accessor/predicate batch below is intentionally a closed recipe set.
    # These patterns are admitted only through accessor_population(), which
    # checks the live gen-dump row and the retail bytes before rendering.
    Skeleton("access-pred-ne", "8B 51 {d:s8} 33 C0 85 D2 0F 95 C0 C3", "bool", "", "QAE_NXZ",
             "int value = *(int *)((char *)this %(d_)s); return value != 0;"),
    Skeleton("access-pred-eq2", "8B 51 {d:s8} 33 C0 83 FA 02 0F 94 C0 C3", "bool", "", "QAE_NXZ",
             "int value = *(int *)((char *)this %(d_)s); return value == 2;"),
    Skeleton("access-pred-eq0", "8B 51 {d:s8} 33 C0 85 D2 0F 94 C0 C3", "bool", "", "QAE_NXZ",
             "int value = *(int *)((char *)this %(d_)s); return value == 0;"),
    Skeleton("access-pred-pointee", "8B 41 {d:s8} 8B 10 33 C9 3B D0 0F 95 C1 8A C1 C3", "bool", "", "QAE_NXZ",
             "unsigned *value = *(unsigned **)((char *)this %(d_)s); return *(unsigned *)value != (unsigned)value;"),
    Skeleton("access-byte-index", "8B 44 24 04 8A 84 08 {d:s32} C2 04 00", "unsigned char", "int a", "QAEEH@Z",
             "return *((unsigned char *)((char *)a + (int)this %(d_)s));"),
    Skeleton("access-adjustor-if", "8A 41 {flag:s8} 84 C0 74 04 8D 41 {ret:s8} C3 33 C0 C3", "char *", "", "QAEPADXZ",
             "if (*((char *)this %(flag_)s)) return (char *)this %(ret_)s; return 0;"),
    Skeleton("access-float-index", "8B 44 24 04 D9 44 81 {d:s8} C2 04 00", "float", "int a", "QAEMH@Z",
             "return ((float *)this)[a + 0x10];"),
    Skeleton("access-float-indirect", "8B 41 {d:s8} D9 40 {f:s8} C3", "float", "", "QAEMXZ",
             "return *(float *)((char *)*(int **)((char *)this %(d_)s) %(f_)s);"),
    Skeleton("access-aggregate-store", "8B 89 {d:s32} 8B 44 24 04 89 08 C2 04 00", "AccessWord", "", "QAE?AUAccessWord@@XZ",
             "return *(AccessWord *)((char *)this %(d_)s);",
             extern="struct AccessWord { unsigned value; };"),
    Skeleton("access-nested-d32", "8B 81 {d:s32} 8B 80 {f:s32} C3", "int", "", "QAEHXZ",
             "return *(int *)((char *)*(int **)((char *)this %(d_)s) %(f_)s);"),
    Skeleton("access-float-global", "D9 81 {d:s32} D8 0D {g:u32} C3", "float", "", "QAEMXZ",
             "float value = *(float *)((char *)this %(d_)s); return value * g_01075954;",
             extern="extern volatile float g_01075954;"),
    Skeleton("access-arg-nested", "8B 44 24 04 8B 80 {d:s32} C2 08 00", "int", "int a, int b", "QAEHHH@Z",
             "return *(int *)((char *)a %(d_)s);"),
    Skeleton("access-array-index", "8B 41 {d:s8} 8B 4C 24 04 8B 04 88 C2 04 00", "int", "int a", "QAEHH@Z",
             "return ((int *)*(int **)((char *)this %(d_)s))[a];"),
    Skeleton("access-frustum", "56 8B F1 E8 {t:rel32} 8D 86 {d:s32} 5E C3", "char *", "", "QAEPADXZ",
             "((CameraClass *)this)->Update_Frustum(); return (char *)this %(d_)s;",
             extern=("struct Gen_00942f20; struct CameraClass { protected: "
                     "void Update_Frustum() const; friend struct Gen_00942f20; };"),
             pin=("?Update_Frustum@CameraClass@@IBEXXZ", "t")),
    Skeleton("access-virtual-adjust", "83 C1 {d:s8} 8B 01 FF 60 {slot:u8}", "void", "", "QAEXXZ",
             "((AccessVTable *)((char *)this %(d_)s))->v();",
             extern=("struct AccessVTable { virtual void a0(); virtual void a1(); "
                     "virtual void a2(); virtual void a3(); virtual void a4(); "
                     "virtual void a5(); virtual void a6(); virtual void a7(); "
                     "virtual void a8(); virtual void a9(); virtual void aa(); "
                     "virtual void v(); };")),
    Skeleton("access-short-arg", "66 8B 44 24 04 C2 08 00", "unsigned short", "int a, int b", "QAEGHH@Z",
             "return (unsigned short)a;"),
    Skeleton("access-or-imm", "81 49 {d:s8} {imm:u32} C3", "void", "", "QAEXXZ",
             "*(unsigned *)((char *)this %(d_)s) |= %(imm)u;"),
]


def parse_pattern(pattern):
    """Byte template -> [literal byte | (operand name, kind)]."""
    items = []
    for token in pattern.split():
        if token.startswith("{"):
            name, _, kind = token[1:-1].partition(":")
            if kind not in FIELD_WIDTH:
                raise FormatError(f"unknown operand kind {kind!r} in {pattern!r}")
            items.append((name, kind))
        else:
            items.append(int(token, 16))
    return items


PATTERNS = {s.key: parse_pattern(s.pattern) for s in SKELETONS}


def match_pattern(items, body, rva):
    """Operands for `body`, or None when it is not an instance of this skeleton."""
    ops, pos = {}, 0
    for item in items:
        if isinstance(item, int):
            if pos >= len(body) or body[pos] != item:
                return None
            pos += 1
            continue
        name, kind = item
        width = FIELD_WIDTH[kind]
        if pos + width > len(body):
            return None
        raw = body[pos:pos + width]
        if kind == "u8":
            ops[name] = raw[0]
        elif kind == "s8":
            ops[name] = struct.unpack("<b", raw)[0]
        elif kind == "u16":
            ops[name] = struct.unpack("<H", raw)[0]
        elif kind == "u32":
            ops[name] = struct.unpack("<I", raw)[0]
        elif kind == "s32":
            ops[name] = struct.unpack("<i", raw)[0]
        else:  # rel32, relative to the end of its own field
            ops[name] = rva + pos + 4 + struct.unpack("<i", raw)[0]
        pos += width
    return ops if pos == len(body) else None


def match_skeleton(body, rva):
    """(Skeleton, operands) for this body, or (None, None) when none applies."""
    hits = []
    for skeleton in SKELETONS:
        ops = match_pattern(PATTERNS[skeleton.key], body, rva)
        if ops is not None:
            hits.append((skeleton, ops))
    if len(hits) > 1:
        raise FormatError(f"body {body.hex()} matches {len(hits)} skeletons "
                          f"({', '.join(s.key for s, _ in hits)}) — a body must have "
                          "exactly one shape or the generated C++ is a guess")
    return hits[0] if hits else (None, None)


def shim_symbol(rva, skeleton):
    """`?m@Gen_00401000@@QAEHXZ` — the decorated name of the generated method."""
    return f"?m@Gen_{rva:08x}@@{skeleton.mangle}"


def shim_lines(rva, skeleton, ops):
    """(extern declaration or None, [struct line, definition line])."""
    struct_name = f"Gen_{rva:08x}"
    join = "" if skeleton.ret.endswith("*") else " "
    # `%(d_)s` renders a signed operand as ` + 4` / ` - 8`, so a body reads as
    # pointer arithmetic instead of `this + -8`.
    ops = dict(ops, **{f"{name}_": f"+ {value}" if value >= 0 else f"- {-value}"
                       for name, value in ops.items()})
    return (skeleton.extern % ops if skeleton.extern else None,
            [f"struct {struct_name} {{ {skeleton.ret}{join}m({skeleton.args}); }};",
             f"{skeleton.ret}{join}{struct_name}::m({skeleton.args}) "
             f"{{ {(skeleton.body % ops).strip()} }}".replace("{  }", "{ }")])


def shim_pin(skeleton, ops):
    """(pin name, address) for a call target this skeleton jumps to, or None."""
    if skeleton.pin is None:
        return None
    name_format, address_op = skeleton.pin
    return name_format % ops, ops[address_op]


# --------------------------------------------------------------------------
# constant-return getter batch
# --------------------------------------------------------------------------
#
# The ret-imm skeleton is useful for a particularly narrow conversion lane:
# several gen_asm dumps are six-byte `mov eax, imm32; ret` bodies.  The dump row
# proves both the boundary and the bytes, but carries no identity.  This lane
# only takes over a live gen-dump row after reading those exact six bytes from
# the retail image. In particular, it does not scan .text for the byte
# sequence: a coincidental sequence inside another body is not a function.

GETTER_SKELETON = next(s for s in SKELETONS if s.key == "ret-imm")
GETTER_PATTERN = PATTERNS[GETTER_SKELETON.key]
EH_FUNCLET_RE = re.compile(r"(?:^|;)ghidra=(?:Catch|Unwind)@")


def getter_ghidra_name(row):
    """The scaffold's inventory name, for an auditable replacement note."""
    notes = row.get("notes", "")
    match = re.search(r"(?:^|;)ghidra=([^;]+)", notes)
    return match.group(1) if match else row["name"]


def getter_population(rows=None, read=None):
    """Return ``(eligible, excluded)`` exact getter scaffold instances.

    ``eligible`` has the same tuple shape as :func:`select_shims`, so the
    existing shim renderer can be reused.  ``excluded`` contains
    ``(rva, reason, size)`` for exact six-byte scaffolds rejected by policy.
    Rows are sorted by RVA (and then name) regardless of ledger order.  Only
    matched gen-dump scaffold rows are considered regardless of source path;
    non-scaffolds, wrong sizes, arbitrary byte occurrences, and Catch@/Unwind@
    funclets never enter this population.
    """
    if rows is None:
        rows = B.load_all_function_rows()
    if read is None:
        read = exe_reader()

    live = [row for row in rows if row.get("status") == "matched"]
    spans = [(int(row["target_rva"], 16),
              int(row["target_rva"], 16) + int(row["target_size"]), row)
             for row in live]
    exact = []
    for row in live:
        if not B.is_scaffold_row(row) or int(row["target_size"]) != 6:
            continue
        rva = int(row["target_rva"], 16)
        body = bytes(read(rva, 6))
        ops = match_pattern(GETTER_PATTERN, body, rva)
        if ops is None:
            continue
        exact.append((rva, body, row, ops))

    eligible, excluded = [], []
    for rva, body, row, ops in sorted(exact, key=lambda item: (item[0], item[2]["name"])):
        if EH_FUNCLET_RE.search(row.get("notes", "")):
            excluded.append((rva, "eh-funclet", len(body)))
            continue
        end = rva + len(body)
        overlaps = [other for start, other_end, other in spans
                    if other is not row and start < end and rva < other_end]
        if overlaps:
            owner = min(overlaps, key=lambda other: (int(other["target_rva"], 16),
                                                       other["name"]))
            excluded.append((rva, f"overlap={owner['name']}", len(body)))
            continue
        skeleton = GETTER_SKELETON
        eligible.append((rva, body, getter_ghidra_name(row), skeleton, ops))
    return eligible, excluded


def getter_paths(batch):
    """Return the immutable numbered source and pending paths for ``batch``."""
    if batch < 0:
        raise FormatError(f"getter batch must be non-negative, got {batch}")
    return (GEN_DIR / f"getters_{batch:03d}.cpp",
            PENDING_DIR / f"getters_{batch:03d}.json")


def ensure_getter_batch_available(source_rel, ledger_rows, candidate_count, batch):
    """Refuse to reuse a landed batch for a later population.

    Numbered generated TUs are immutable once their rows land.  Reusing one
    after new scaffolds appear would require modifying a tracked source whose
    existing rows still point at its old contents, so direct the caller to the
    next batch instead.
    """
    owners = [row for row in ledger_rows
              if row.get("status") == "matched" and row.get("source") == source_rel]
    if owners and candidate_count:
        raise FormatError(
            f"{source_rel} already owns {len(owners)} live row(s), but {candidate_count} "
            f"new getter candidate(s) remain; refusing to overwrite an immutable batch — "
            f"rerun with --batch {batch + 1}")


def ensure_generated_text(path, text):
    """Refuse to overwrite an existing generated artifact with different bytes."""
    if path.exists() and path.read_text(encoding="utf-8") != text:
        raise FormatError(
            f"{path.relative_to(ROOT)} already exists with different generated bytes; "
            "refusing to overwrite an immutable batch")


def render_getters(picked, batch=0):
    """Render one deterministic TU for all picked constant-return shims."""
    lines = [
        f"// Generated by: python3 tools/gen_small.py gen-getters --batch {batch}",
        "// Do not edit by hand; regenerate instead.",
        "//",
        "// Each Gen_<rva>::m() replaces one exact six-byte gen-dump scaffold",
        "// whose retail body is `B8 imm32 C3`. The source rows are marked gen-shim",
        "// because this synthetic method is a byte-verified shim, not a recovered",
        "// identity. Catch@/Unwind@ funclets are excluded from this lane.",
        "",
    ]
    for rva, _, _, skeleton, ops in picked:
        lines += shim_lines(rva, skeleton, ops)[1]
    return "\n".join(lines) + "\n"


def _write_if_changed(path, text):
    """Write generated text only when its bytes differ; return whether changed."""
    if path.exists() and path.read_text(encoding="utf-8") == text:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    return True


def cmd_gen_getters(args):
    rows, excluded = getter_population()
    exact = len(rows) + len(excluded)
    exact_bytes = sum(item[2] for item in excluded) + 6 * len(rows)
    reasons = collections.Counter(item[1].split("=", 1)[0] for item in excluded)
    detail = ", ".join(f"{count} {reason}" for reason, count in sorted(reasons.items()))
    print(f"gen-getters: {exact} exact scaffold(s) ({exact_bytes} bytes) = "
          f"{len(rows)} eligible ({6 * len(rows)} bytes) + "
          f"{len(excluded)} excluded ({sum(item[2] for item in excluded)} bytes)"
          + (f" [{detail}]" if detail else ""))
    if args.dry_run:
        print("gen-getters: dry-run — no source, pending JSON, or ledger changes")
        return
    if not rows:
        print("gen-getters: 0 new — no eligible ordinary getter scaffolds remain")
        return

    source_path, pending_path = getter_paths(args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    ledger_rows = B.load_all_function_rows()
    ensure_getter_batch_available(source_rel, ledger_rows, len(rows), args.batch)
    text = render_getters(rows, args.batch)
    pending = {
        "source": source_rel,
        "rows": [],
        "pins": [],
    }
    _, claimed_names, _ = load_claims()
    for rva, body, ghidra_name, skeleton, ops in rows:
        name = shim_symbol(rva, skeleton)
        existing = claimed_names.get(name)
        if existing is not None and existing != rva:
            raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger, "
                              f"but this batch would claim 0x{rva:08X}")
        pending["rows"].append(format_row(
            name, rva, len(body), source_rel,
            f"gen-shim;skeleton={skeleton.key};ghidra={ghidra_name}"))
    pending_text = json.dumps(pending, indent=1) + "\n"
    ensure_generated_text(source_path, text)
    ensure_generated_text(pending_path, pending_text)
    changed = _write_if_changed(source_path, text)
    pending_changed = _write_if_changed(pending_path, pending_text)
    print(f"gen-getters: {source_rel}: {len(rows)} row(s), "
          f"{len(rows)} new row(s), 0 new pin(s)"
          + (" — file unchanged" if not changed and not pending_changed else ""))


# --------------------------------------------------------------------------
# closed accessor/predicate batch
# --------------------------------------------------------------------------

ACCESSOR_BATCH = (
    (0x000C9040, "access-pred-ne"), (0x0026E740, "access-pred-ne"),
    (0x002B9E40, "access-pred-ne"), (0x00180380, "access-pred-eq2"),
    (0x00235140, "access-pred-eq0"), (0x0009ED10, "access-pred-pointee"),
    (0x000C9CA0, "access-byte-index"), (0x0018F0B0, "access-adjustor-if"),
    (0x001DE210, "access-float-index"), (0x0020E860, "access-float-indirect"),
    (0x0020FAC0, "access-aggregate-store"), (0x00233F20, "access-nested-d32"),
    (0x002C60C0, "access-nested-d32"), (0x0073A6B0, "access-float-global"),
    (0x007FBBB0, "access-arg-nested"), (0x00928EE0, "access-array-index"),
    (0x00942F20, "access-frustum"), (0x002176C0, "access-virtual-adjust"),
    (0x005241E0, "access-short-arg"), (0x0056B9E0, "access-short-arg"),
    (0x0044F350, "access-or-imm"),
)
ACCESSOR_NOTE = "gen-shim;accessor-batch"


def accessor_paths(batch):
    if batch < 0:
        raise FormatError(f"accessor batch must be non-negative, got {batch}")
    return (GEN_DIR / f"accessors_{batch:03d}.cpp",
            PENDING_DIR / f"accessors_{batch:03d}.json")


def accessor_population(rows=None, read=None):
    """Read the fixed batch's live dump rows and prove every recipe shape.

    This is deliberately not a byte-pattern scan. A candidate remains eligible
    only while its ledger row is a matched gen-dump with the original extent;
    any row, size, or retail-byte drift aborts the run.
    """
    if rows is None:
        rows = B.load_all_function_rows()
    if read is None:
        read = exe_reader()
    by_rva = {int(row["target_rva"], 16): row for row in rows}
    out = []
    for rva, key in ACCESSOR_BATCH:
        row = by_rva.get(rva)
        if row is None:
            raise FormatError(f"accessor batch row 0x{rva:08X} is missing")
        # Dumpness is the gen-dump note, never the source directory: 349 dump
        # rows live in Code/gen_small/dumps_000.cpp, so a path test rejects live
        # dumps that have simply been relocated. B.is_scaffold_row is the rule.
        if row.get("status") != "matched" or not B.is_scaffold_row(row):
            raise FormatError(f"accessor batch row 0x{rva:08X} is not a live gen-dump")
        size = int(row["target_size"])
        body = read(rva, size)
        if len(body) != size:
            raise FormatError(f"accessor batch row 0x{rva:08X} reads {len(body)} bytes, expected {size}")
        skeleton = next(s for s in SKELETONS if s.key == key)
        ops = match_pattern(PATTERNS[key], body, rva)
        if ops is None:
            raise FormatError(f"accessor recipe {key} no longer matches 0x{rva:08X}: {body.hex(' ')}")
        out.append((rva, body, row, skeleton, ops))
    return out


def render_accessors(picked, batch=0, optimized=False):
    lines = [
        *(["// cl: /O1"] if optimized else []),
        f"// Generated by: python3 tools/gen_small.py gen-accessors --batch {batch}",
        "// Do not edit by hand; regenerate instead.",
        "//",
        "// This immutable TU is emitted only from the closed, byte-validated accessor",
        "// batch. Every row remains marked gen-shim: the synthetic recipe proves bytes",
        "// and does not claim a recovered retail identity.",
        "",
    ]
    externs = []
    rendered = []
    for rva, _, _, skeleton, ops in picked:
        extern, body_lines = shim_lines(rva, skeleton, ops)
        if extern is not None and extern not in externs:
            externs.append(extern)
        rendered.extend(body_lines)
    lines += sorted(externs)
    if externs:
        lines.append("")
    lines += rendered
    return "\n".join(lines) + "\n"


def cmd_gen_accessors(args):
    ledger_rows = B.load_all_function_rows()
    source_path, pending_path = accessor_paths(args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    special_rel = (GEN_DIR / "accessor_002176c0.cpp").relative_to(ROOT).as_posix()
    by_rva = {int(row["target_rva"], 16): row for row in ledger_rows}
    if all(by_rva.get(rva, {}).get("source") in (source_rel, special_rel)
           and by_rva.get(rva, {}).get("notes", "").startswith(ACCESSOR_NOTE)
           for rva, _ in ACCESSOR_BATCH):
        print(f"gen-accessors: batch {args.batch}: 0 new — immutable rows already landed")
        return
    picked = accessor_population()
    special_rva = 0x002176C0
    special_path = GEN_DIR / "accessor_002176c0.cpp"
    special_rel = special_path.relative_to(ROOT).as_posix()
    ordinary = [item for item in picked if item[0] != special_rva]
    special = [item for item in picked if item[0] == special_rva]
    text = render_accessors(ordinary, args.batch)
    special_text = render_accessors(special, args.batch, optimized=True)
    _, claimed_names, _ = load_claims()
    rows, pins = [], []
    for rva, body, ledger_row, skeleton, ops in picked:
        name = shim_symbol(rva, skeleton)
        existing = claimed_names.get(name)
        if existing is not None and existing != rva:
            raise FormatError(f"{name} already claims 0x{existing:08X}, not 0x{rva:08X}")
        row_source = special_rel if rva == special_rva else source_rel
        rows.append(format_row(name, rva, len(body), row_source,
                               f"{ACCESSOR_NOTE};skeleton={skeleton.key};source={ledger_row['source']}"))
        pin = shim_pin(skeleton, ops)
        if pin is not None:
            pins.append(format_pin(pin[0], pin[1], "accessor-batch call target"))
        if skeleton.key == "access-float-global":
            pins.append(format_pin("?g_01075954@@3MC", 0x01075954,
                                   "accessor-batch external float"))
    ensure_generated_text(source_path, text)
    ensure_generated_text(special_path, special_text)
    pending = json.dumps({"source": source_rel, "sources": [source_rel, special_rel],
                          "rows": rows, "pins": pins}, indent=1) + "\n"
    ensure_generated_text(pending_path, pending)
    changed = _write_if_changed(source_path, text)
    special_changed = _write_if_changed(special_path, special_text)
    pending_changed = _write_if_changed(pending_path, pending)
    print(f"gen-accessors: {source_rel}: {len(picked)} row(s), "
          f"{sum(len(body) for _, body, _, _, _ in picked)} bytes, {len(pins)} pin(s)"
          + (" — file unchanged" if not changed and not special_changed and not pending_changed else ""))


def population(entries, read, blacklist):
    """[(rva, body, name)] — every anonymous FUN_* body, claimed or not.

    Excludes only what the other generators own (the five-byte `jmp rel32`
    thunks, the six-byte `FF 25` import thunks) and the boundary artifacts, so
    this total does not move as batches land. `claimable` narrows it to the
    bodies no real ledger row has taken.
    """
    out = []
    for rva, size, name in entries:
        if size > SMALL_MAX or not name.startswith("FUN_") or rva in blacklist:
            continue
        body = read(rva, size)
        if len(body) == 5 and body[0] == 0xE9:
            continue
        if len(body) == 6 and body[0] == 0xFF and body[1] == 0x25:
            continue
        out.append((rva, body, name))
    return out


# --------------------------------------------------------------------------
# skeleton probe
# --------------------------------------------------------------------------

PROBE_SOURCE = PENDING_DIR / "probe.cpp"
PROBE_RESULT = PENDING_DIR / "skeletons.json"

PROBE_HEADER = """\
// Scratch (untracked): one instance of every candidate skeleton in
// tools/gen_small.py, compiled and byte-compared against its retail body by
// `python3 tools/gen_small.py probe`. A skeleton may generate claims only after
// its instance here matches exactly.
"""


def foreign_claims(marker="gen-shim;"):
    """({rva: name} claimed by rows this generator did not write, overlap index).

    A body some real reverse-engineering row already owns is not ours to shim.
    A body one of OUR `marker` rows owns still counts as ours, which is what
    keeps `probe` and `shim-report` answering the same thing before and after a
    batch lands.
    """
    rows = [r for r in B.load_all_function_rows()
            if not r["notes"].startswith(marker)]
    by_rva = {int(r["target_rva"], 16): r["name"] for r in rows}
    index = overlap_index([{"rva": int(r["target_rva"], 16), "size": int(r["target_size"]),
                            "name": r["name"], "status": r["status"]} for r in rows])
    return by_rva, index


def claimable(entries, read, blacklist):
    """The population minus the bodies real ledger rows already own."""
    owned, index = foreign_claims()
    return [(rva, body, name) for rva, body, name in population(entries, read, blacklist)
            if rva not in owned and find_overlap(index, rva, len(body)) is None]


def probe_instances(bodies):
    """{key: {rva: (body, ops)}} — what has to byte-verify before a skeleton may
    generate claims: its lowest-addressed instance, plus the instances holding
    the smallest and largest value of every operand.

    The extremes are the difference between a probe that means something and one
    that flatters itself: `8B 41 08` and `8B 41 F8` are the same skeleton, but
    the second is a NEGATIVE displacement, and a decoder that reads it unsigned
    produces C++ the compiler encodes four bytes wider. One well-behaved first
    instance hides that until a whole batch fails its gate.
    """
    by_key = {}
    for rva, body, _ in bodies:
        skeleton, ops = match_skeleton(body, rva)
        if skeleton is not None:
            by_key.setdefault(skeleton.key, []).append((rva, body, ops))
    chosen = {}
    for key, instances in by_key.items():
        picked = {instances[0][0]: instances[0][1:]}
        for name, _ in [i for i in PATTERNS[key] if not isinstance(i, int)]:
            for extreme in (min, max):
                rva, body, ops = extreme(instances, key=lambda i: i[2][name])
                picked[rva] = (body, ops)
        chosen[key] = picked
    return chosen


def render_probe(instances):
    externs, lines = [], []
    for skeleton in SKELETONS:
        for rva, (_, ops) in sorted(instances.get(skeleton.key, {}).items()):
            extern, body_lines = shim_lines(rva, skeleton, ops)
            if extern is not None and extern not in externs:
                externs.append(extern)
            lines += [f"// {skeleton.key}"] + body_lines
    return PROBE_HEADER + "\n" + "\n".join(externs + [""] + lines) + "\n"


def cmd_probe(args):
    entries = load_ghidra()
    read = exe_reader()
    instances = probe_instances(claimable(entries, read, load_blacklist()))
    missing = [s.key for s in SKELETONS if s.key not in instances]
    if missing:
        raise SystemExit("gen_small: no claimable instance for skeleton(s) "
                         + ", ".join(missing) + " — remove them from the library")

    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    PROBE_SOURCE.write_text(render_probe(instances), encoding="utf-8")
    obj = B.obj_path(PROBE_SOURCE)
    B.compile_source(PROBE_SOURCE, obj)
    symbol_map = B.load_symbol_map()
    thunks = B.build_call_thunks()

    def verify(skeleton, rva, body, ops):
        pin = shim_pin(skeleton, ops)
        # The pin is what lets the gate resolve this instance's REL32; it is not
        # in symbols.csv until the batch lands, so supply it for the probe.
        if pin is not None and pin[0] not in symbol_map:
            symbol_map[pin[0]] = thunks.get(pin[1], []) + [pin[1]]
        row = {"name": shim_symbol(rva, skeleton), "target_rva": f"0x{rva:08X}",
               "target_size": str(len(body)), "source": PROBE_SOURCE.name, "notes": ""}
        try:
            patch = B.compile_function(row, symbol_map, obj)
        except ValueError as error:
            return "no-symbol", str(error)
        if patch["unresolved"]:
            return "unresolved", ", ".join(patch["unresolved"])
        if patch["bytes"] != patch["target"]:
            return "mismatch", (f"retail {patch['target'].hex()} != "
                                f"generated {patch['bytes'].hex()}")
        return "verified", patch["target"].hex()

    results = {}
    for skeleton in SKELETONS:
        checked = {rva: verify(skeleton, rva, body, ops)
                   for rva, (body, ops) in sorted(instances[skeleton.key].items())}
        bad = [(rva, status, detail) for rva, (status, detail) in checked.items()
               if status != "verified"]
        results[skeleton.key] = {
            "rva": min(checked),
            "instances": {f"0x{rva:08X}": list(outcome) for rva, outcome in checked.items()},
            "status": "verified" if not bad else bad[0][1],
            "detail": "" if not bad else f"0x{bad[0][0]:08X}: {bad[0][2]}",
        }

    PROBE_RESULT.write_text(json.dumps(results, indent=1, sort_keys=True) + "\n",
                            encoding="utf-8")
    verified = [k for k, r in results.items() if r["status"] == "verified"]
    for key, result in sorted(results.items()):
        if result["status"] != "verified":
            print(f"probe: SKIP {key}: {result['status']}: {result['detail']}",
                  file=sys.stderr)
    print(f"probe: {len(verified)} of {len(SKELETONS)} skeleton(s) byte-verified over "
          f"{sum(len(i) for i in instances.values())} instance(s) -> "
          f"{PROBE_RESULT.relative_to(ROOT)}")


def load_probe():
    """{key: result} for the skeleton library, or a hard stop if never probed."""
    if not PROBE_RESULT.exists():
        raise SystemExit(f"gen_small: no {PROBE_RESULT.relative_to(ROOT)} — run "
                         "`python3 tools/gen_small.py probe` first")
    results = json.loads(PROBE_RESULT.read_text(encoding="utf-8"))
    stale = {s.key for s in SKELETONS} ^ set(results)
    if stale:
        raise SystemExit(f"gen_small: {PROBE_RESULT.relative_to(ROOT)} is stale "
                         f"({', '.join(sorted(stale))}) — rerun `probe`")
    return results


# --------------------------------------------------------------------------
# shim batches
# --------------------------------------------------------------------------

def shim_paths(batch):
    return (GEN_DIR / f"fun_{batch:03d}.cpp", PENDING_DIR / f"fun_{batch:03d}.json")


def select_shims(entries, read, blacklist, claimed, batch_source, limit, index, verified):
    """(picked, subsumed) — the next `limit` claimable instances of verified skeletons."""
    picked, subsumed = [], []
    for rva, body, name in population(entries, read, blacklist):
        skeleton, ops = match_skeleton(body, rva)
        if skeleton is None or skeleton.key not in verified:
            continue
        owner = claimed.get(rva)
        if owner is not None and owner != batch_source:
            continue
        if owner is None:
            hit = find_overlap(index, rva, len(body))
            if hit is not None:
                subsumed.append((rva, name, hit))
                continue
        picked.append((rva, body, name, skeleton, ops))
        if len(picked) == limit:
            break
    return picked, subsumed


def render_shims(picked, batch, limit):
    lines = [
        f"// Generated by: python3 tools/gen_small.py gen-shims --batch {batch} --limit {limit}",
        "// Do not edit by hand; regenerate instead.",
        "//",
        "// Each Gen_<rva>::m() reproduces the anonymous retail body at that RVA: the",
        "// instruction skeleton is one tools/gen_small.py proved byte-exact, and every",
        "// operand comes from the retail bytes. These are shims, not identities — the",
        "// ledger rows are marked gen-shim so a later real name can replace them.",
        "",
    ]
    externs = []
    for rva, _, _, skeleton, ops in picked:
        extern, _ = shim_lines(rva, skeleton, ops)
        if extern is not None and extern not in externs:
            externs.append(extern)
    lines += sorted(externs)
    if externs:
        lines.append("")
    for rva, _, _, skeleton, ops in picked:
        lines += shim_lines(rva, skeleton, ops)[1]
    return "\n".join(lines) + "\n"


def cmd_gen_shims(args):
    entries = load_ghidra()
    read = exe_reader()
    blacklist = load_blacklist()
    claimed, claimed_names, index = load_claims()
    pinned = load_pins()
    verified = {key for key, result in load_probe().items() if result["status"] == "verified"}

    source_path, pending_path = shim_paths(args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    picked, subsumed = select_shims(entries, read, blacklist, claimed, source_rel,
                                    args.limit, index, verified)
    for rva, name, (owner, start, end) in subsumed:
        print(f"gen-shims: SKIP 0x{rva:08X} {name}: those bytes are inside matched row "
              f"{owner} [0x{start:08X}, 0x{end:08X})", file=sys.stderr)
    if not picked:
        print(f"gen-shims: batch {args.batch}: 0 new — no claimable skeleton instances left"
              + (f" ({len(subsumed)} subsumed by matched rows, listed above)" if subsumed else ""))
        return

    rows, pins = [], []
    for rva, body, ghidra_name, skeleton, ops in picked:
        name = shim_symbol(rva, skeleton)
        existing = claimed_names.get(name)
        if existing is not None and existing != rva:
            raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger, "
                              f"but this batch would claim 0x{rva:08X}")
        rows.append(format_row(name, rva, len(body), source_rel,
                               f"gen-shim;skeleton={skeleton.key};ghidra={ghidra_name}"))
        pin = shim_pin(skeleton, ops)
        if pin is None:
            continue
        pin_name, address = pin
        if pinned.get(pin_name) not in (None, address):
            raise FormatError(f"{pin_name} is pinned at 0x{pinned[pin_name]:08X} in "
                              f"symbols.csv but names body 0x{address:08X}")
        if pin_name not in pinned:
            pins.append(format_pin(pin_name, address, "gen-shim call target"))
            pinned[pin_name] = address

    new_rows = [row for row in rows if row.split(",")[0] not in claimed_names]
    text = render_shims(picked, args.batch, args.limit)
    unchanged = source_path.exists() and source_path.read_text(encoding="utf-8") == text
    if not unchanged:
        GEN_DIR.mkdir(parents=True, exist_ok=True)
        source_path.write_text(text, encoding="utf-8")
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    pending_path.write_text(json.dumps(
        {"source": source_rel, "rows": rows, "pins": pins}, indent=1) + "\n", encoding="utf-8")

    kinds = {}
    for _, _, _, skeleton, _ in picked:
        kinds[skeleton.key] = kinds.get(skeleton.key, 0) + 1
    print(f"gen-shims: batch {args.batch} -> {source_rel}: {len(picked)} shim(s), "
          f"{len(new_rows)} new row(s), {len(pins)} new pin(s), "
          f"{len(subsumed)} subsumed by matched rows"
          + (" — file unchanged" if unchanged else ""))
    print("  " + ", ".join(f"{key}={count}" for key, count in sorted(kinds.items())))


def cmd_shim_report(_args):
    """Account for every claimable body: landed, skipped skeleton, or out of scope."""
    entries = load_ghidra()
    read = exe_reader()
    blacklist = load_blacklist()
    claimed, _, _ = load_claims()
    probe = load_probe()
    everything = population(entries, read, blacklist)
    bodies = claimable(entries, read, blacklist)

    shapes = collections.Counter(body.hex() for _, body, _ in bodies)
    landed, pending, skipped = collections.Counter(), collections.Counter(), {}
    other = collections.defaultdict(list)
    for rva, body, _ in bodies:
        skeleton, _ = match_skeleton(body, rva)
        if skeleton is None:
            bucket = "singleton shape" if shapes[body.hex()] == 1 else "recurring shape"
            other[bucket].append(body.hex())
            continue
        result = probe[skeleton.key]
        if result["status"] != "verified":
            entry = skipped.setdefault(skeleton.key, [0, result["status"], result["detail"]])
            entry[0] += 1
        elif rva in claimed:
            landed[skeleton.key] += 1
        else:
            pending[skeleton.key] += 1

    print(f"anonymous FUN_* bodies <= {SMALL_MAX}B (not blacklisted, not a jmp or "
          f"import thunk): {len(everything)}")
    print(f"  {len(everything) - len(bodies)} already claimed by real ledger rows")
    print(f"  {len(bodies)} claimable by this phase\n")
    print(f"landed as gen-shim rows: {sum(landed.values())}")
    for key, count in sorted(landed.items(), key=lambda kv: (-kv[1], kv[0])):
        print(f"  {count:5d}  {key}")
    if pending:
        print(f"\nverified skeleton, batch not landed: {sum(pending.values())}")
        for key, count in sorted(pending.items(), key=lambda kv: (-kv[1], kv[0])):
            print(f"  {count:5d}  {key}")
    print(f"\nskipped — skeleton failed its probe: {sum(v[0] for v in skipped.values())}")
    for key, (count, status, detail) in sorted(skipped.items(), key=lambda kv: -kv[1][0]):
        print(f"  {count:5d}  {key}: {status}: {detail}")
    out_of_scope = sum(len(v) for v in other.values())
    print(f"\nout of scope — no library skeleton: {out_of_scope}")
    for bucket, hits in sorted(other.items()):
        print(f"  {len(hits):5d}  {bucket} ({len(set(hits))} distinct)")
    total = (sum(landed.values()) + sum(pending.values())
             + sum(v[0] for v in skipped.values()) + out_of_scope)
    print(f"\ntotal accounted: {total} of {len(bodies)} claimable")
    if total != len(bodies):
        raise FormatError(f"report accounts for {total} of {len(bodies)} bodies")


# --------------------------------------------------------------------------
# named families
# --------------------------------------------------------------------------
#
# A "named" small function is one ghidra gave a real name (`releaseBuffer`,
# `getClass`, `operator=`) instead of FUN_/thunk_/Unwind@/Catch@. Those names are
# UNDECORATED and carry no class and no signature, so they are not by themselves
# a COFF symbol: `expandBy` could be any of a dozen classes' members. A family
# rule here therefore does not translate a ghidra name — it recognises a specific
# function by name AND by the exact retail byte template it must have, and states
# the decorated name outright. One rule per family, no pattern-guessing: if the
# bytes are not the shape the rule assumes, the function is reported underivable
# rather than claimed on the strength of a name collision.
#
# Every operand the rule needs (a call target, a data slot) is read from the
# retail bytes, so the emitted C++ is determined, not inferred. DIR32 sites are
# copied from retail by the gate, which is why an absolute data address may be
# named by a placeholder extern; a REL32 callee is real and gets a pin.

Family = collections.namedtuple("Family", "key ghidra pattern symbol source pin")
Family.__new__.__defaults__ = (None,)

# Names ghidra assigns when it has NO identity for a function.
ANONYMOUS_PREFIXES = ("FUN_", "thunk_", "Unwind@", "Catch@")

FAMILIES = [
    # `cmp ecx, [__security_cookie]; jne over; ret; over: jmp report_failure`.
    # The cookie arrives in ECX with no prologue, which is __fastcall; extern "C"
    # __fastcall decorates as @name@<bytes of args>.
    # KNOWN FAILING (reported every run, never emitted): retail keeps the `ret` on
    # the fallthrough path and jumps away to fail, MSVC 7.1 emits the two blocks
    # swapped (`74 05 E9 .. C3`) for this source and for the noreturn variant. The
    # name and the operands are right; only the block order is not reachable from
    # straight-line C++, so this body needs inline asm, not another rule guess.
    Family(
        "security-cookie", "__security_check_cookie",
        "3B 0D {cookie:u32} 75 01 C3 E9 {fail:rel32}",
        "@__security_check_cookie@4",
        'extern unsigned long gs_cookie_%(cookie)08x;\n'
        '__declspec(noreturn) void gs_report_%(fail)08x();\n'
        '\n'
        'extern "C" void __fastcall __security_check_cookie(unsigned long cookie)\n'
        '{\n'
        '\tif (cookie != gs_cookie_%(cookie)08x)\n'
        '\t\tgs_report_%(fail)08x();\n'
        '}\n',
        pin=("?gs_report_%(fail)08x@@YAXXZ", "fail")),
    # comdef.h's `void __stdcall _com_issue_error(HRESULT)`, whose whole body is
    # `_com_raise_error(hr, NULL)` through the import table: `mov eax,[esp+4];
    # push 0; push eax; call [__imp]; ret 4`.
    Family(
        "com-issue-error", "_com_issue_error",
        "8B 44 24 04 6A 00 50 FF 15 {slot:u32} C2 04 00",
        "?_com_issue_error@@YGXJ@Z",
        '__declspec(dllimport) void __stdcall _com_raise_error(long hr, void *info);\n'
        '\n'
        'void __stdcall _com_issue_error(long hr)\n'
        '{\n'
        '\t_com_raise_error(hr, 0);\n'
        '}\n'),
]

FAMILY_PATTERNS = {f.key: parse_pattern(f.pattern) for f in FAMILIES}


def named_paths(batch):
    return (GEN_DIR / f"named_{batch:03d}.cpp", PENDING_DIR / f"named_{batch:03d}.json")


def named_population(entries, read, blacklist):
    """[(rva, size, name, body)] — every named small function no ledger row owns.

    Rows this generator wrote are excluded from the "owned" set, so the
    population is the same number before and after a batch lands and a rerun
    regenerates the identical file.
    """
    owned, index = foreign_claims("gen-named;")
    out = []
    for rva, size, name in entries:
        if size > SMALL_MAX or rva in blacklist:
            continue
        if name.startswith(ANONYMOUS_PREFIXES):
            continue
        if rva in owned or find_overlap(index, rva, size) is not None:
            continue
        out.append((rva, size, name, read(rva, size)))
    return out


def named_batch_population(entries, claimed, source_rel):
    """Keep unclaimed functions plus rows already owned by this exact batch.

    ``named_population`` deliberately ignores every ``gen-named`` row so a
    landed batch can regenerate byte-for-byte.  Without the source check here,
    asking for the next batch emits the previous batch's rows again under a
    second source file.
    """
    return [entry for entry in entries
            if claimed.get(entry[0]) in (None, source_rel)]


def match_family(rva, name, body):
    """(Family, operands) for this function, or (None, why no rule applies)."""
    for family in FAMILIES:
        if family.ghidra != name:
            continue
        ops = match_pattern(FAMILY_PATTERNS[family.key], body, rva)
        if ops is None:
            return None, (f"family {family.key} expects `{family.pattern}`, but the "
                          f"retail body is {body.hex()}")
        return family, ops
    return None, "no derivation rule: an undecorated ghidra name is not a COFF symbol"


NAMED_HEADER = """\
// Generated by: python3 tools/gen_small.py gen-named --batch {batch}
// Do not edit by hand; regenerate instead.
//
// Real identities, not shims: each definition below carries the decorated name
// the retail function actually has, derived by tools/gen_small.py's family rules
// and byte-verified before this file was written. Operands come from the retail
// bytes. Rows are marked gen-named in reverse/functions.csv.
"""


def render_named(picked, batch):
    lines = [NAMED_HEADER.format(batch=batch)]
    for rva, family, ops in picked:
        lines.append(f"// 0x{rva:08X} {family.ghidra} ({family.key}) -> {family.symbol}\n"
                     + family.source % ops)
    return "\n".join(lines)


def cmd_gen_named(args):
    entries = load_ghidra()
    read = exe_reader()
    claimed, claimed_names, _ = load_claims()
    pinned = load_pins()

    source_path, pending_path = named_paths(args.batch)
    source_rel = source_path.relative_to(ROOT).as_posix()
    scanned = named_population(entries, read, load_blacklist())
    scanned = named_batch_population(scanned, claimed, source_rel)

    candidates, underivable = [], []
    for rva, _size, name, body in scanned:
        family, ops = match_family(rva, name, body)
        if family is None:
            underivable.append((rva, name, ops))
            continue
        existing = claimed_names.get(family.symbol)
        if existing is not None and existing != rva:
            raise FormatError(f"{family.symbol} already claims 0x{existing:08X} in the "
                              f"ledger, but this batch would claim 0x{rva:08X}")
        candidates.append((rva, len(body), family, ops))

    # Probe before emitting: compile every candidate once and byte-compare it, so
    # a wrong decorated name (symbol absent from the object) or a wrong body
    # (byte mismatch) is reported here instead of reverting a landed batch.
    GEN_DIR.mkdir(parents=True, exist_ok=True)
    verified, gate_failed = [], []
    if candidates:
        source_path.write_text(
            render_named([(r, f, o) for r, _, f, o in candidates], args.batch),
            encoding="utf-8")
        obj = B.obj_path(source_path)
        B.compile_source(source_path, obj)
        symbol_map = B.load_symbol_map()
        thunks = B.build_call_thunks()
        for rva, size, family, ops in candidates:
            pin = None if family.pin is None else (family.pin[0] % ops, ops[family.pin[1]])
            if pin is not None and pin[0] not in symbol_map:
                symbol_map[pin[0]] = thunks.get(pin[1], []) + [pin[1]]
            row = {"name": family.symbol, "target_rva": f"0x{rva:08X}",
                   "target_size": str(size), "source": source_rel, "notes": ""}
            try:
                patch = B.compile_function(row, symbol_map, obj)
            except ValueError as error:
                gate_failed.append((family.symbol, str(error)))
                continue
            if patch["unresolved"]:
                gate_failed.append((family.symbol,
                                    "unresolved REL32: " + ", ".join(patch["unresolved"])))
            elif patch["bytes"] != patch["target"]:
                gate_failed.append((family.symbol,
                                    f"byte mismatch: retail {patch['target'].hex()} != "
                                    f"generated {patch['bytes'].hex()}"))
            else:
                verified.append((rva, size, family, ops, pin))

    for rva, name, reason in underivable:
        print(f"gen-named: UNDERIVABLE 0x{rva:08X} {name} -> {reason}", file=sys.stderr)
    for symbol, reason in gate_failed:
        print(f"gen-named: GATE-FAILED {symbol} -> {reason}", file=sys.stderr)

    rows, pins = [], []
    for rva, size, family, ops, pin in verified:
        rows.append(format_row(family.symbol, rva, size, source_rel,
                               f"gen-named;family={family.key};ghidra={family.ghidra}"))
        if pin is None:
            continue
        pin_name, address = pin
        if pinned.get(pin_name) not in (None, address):
            raise FormatError(f"{pin_name} is pinned at 0x{pinned[pin_name]:08X} in "
                              f"symbols.csv but names body 0x{address:08X}")
        if pin_name not in pinned:
            pins.append(format_pin(pin_name, address, "gen-named call target"))
            pinned[pin_name] = address

    if verified:
        source_path.write_text(
            render_named([(r, f, o) for r, _, f, o, _ in verified], args.batch),
            encoding="utf-8")
    elif source_path.exists():
        source_path.unlink()
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    pending_path.write_text(json.dumps(
        {"source": source_rel, "rows": rows, "pins": pins}, indent=1) + "\n",
        encoding="utf-8")

    landed = sum(1 for rva, _, _, _, _ in verified if rva in claimed)
    print(f"gen-named: batch {args.batch} -> {source_rel}: scanned {len(scanned)} named "
          f"small function(s) = {len(verified)} derived ({landed} landed) + "
          f"{len(underivable)} derivation-failed + {len(gate_failed)} gate-failed")
    if len(verified) + len(underivable) + len(gate_failed) != len(scanned):
        raise FormatError(
            f"report accounts for {len(verified) + len(underivable) + len(gate_failed)} "
            f"of {len(scanned)} scanned functions")


# --------------------------------------------------------------------------
# SEH funclet sweep
# --------------------------------------------------------------------------
#
# A function compiled with exception handling gets a second COMDAT, `.text$x`,
# holding its unwind funclets and its EH handler stub. Those are ordinary
# defined COFF symbols — the funclets under the compiler's own `$L<n>` labels,
# the stub under `__ehhandler$<parent>` — so a ledger row with an
# `object-symbol=` note byte-verifies one against the retail image with no
# build.py change. Ghidra inventories the retail side as `Unwind@<va>`.
#
# (MSVC 7.1 does NOT emit the `__unwindfunclet$<parent>$<n>` symbols later
# toolchains do: 0 of the 233 cached objects contain one. The parent's identity
# comes from the `__ehhandler$` stub sharing the section, and the row name has
# to be synthesised, because a `$L<n>` label is unique only within its object.)
#
# A funclet body is one or two instructions of destructor call, so the same
# bytes recur across hundreds of parents and cannot attribute anything: picking
# one parent because its bytes fit would be an unfalsifiable row — it
# byte-verifies forever while naming the wrong parent. The retail image states
# ownership outright instead (`funcinfo_ownership`), so the parent comes from
# the FuncInfo tables and the bytes only have to PROVE the pairing the image
# already asserts.

FUNCLET_SECTION = ".text$x"
EHHANDLER_PREFIX = "__ehhandler$"
FUNCLET_PREFIXES = ("Unwind@", "Catch@")


def read_funclet_sections(path):
    """[(parent, [(symbol, size, body, relocs)])] for each .text$x in an object.

    Sizes come from the next symbol in the section (the last runs to the end,
    less any 0xCC pad), which is how a funclet's extent is knowable at all: the
    section holds several back to back with nothing else delimiting them.
    """
    data = path.read_bytes()
    sections, symbols = [], B.read_object_symbols(data)
    for index in range(B.u16(data, 2)):
        offset = 20 + index * 40
        sections.append({
            "name": data[offset:offset + 8].rstrip(b"\0").decode("ascii", "replace"),
            "size": B.u32(data, offset + 16), "raw": B.u32(data, offset + 20),
            "relocs": B.u16(data, offset + 32), "reloc_raw": B.u32(data, offset + 24)})
    grouped = collections.defaultdict(list)
    for symbol in symbols:
        if symbol["section"] > 0 and symbol["name"]:
            grouped[symbol["section"]].append(symbol)

    out = []
    for number, members in sorted(grouped.items()):
        section = sections[number - 1]
        if section["name"] != FUNCLET_SECTION:
            continue
        parents = [s["name"][len(EHHANDLER_PREFIX):] for s in members
                   if s["name"].startswith(EHHANDLER_PREFIX)]
        if len(parents) != 1:
            raise FormatError(
                f"{path.name} section {number} is {FUNCLET_SECTION} with "
                f"{len(parents)} {EHHANDLER_PREFIX} symbol(s) — the funclets in it "
                "cannot be attributed to a parent function")
        body = data[section["raw"]:section["raw"] + section["size"]]
        relocs = [(B.u32(data, section["reloc_raw"] + r * 10),
                   B.u16(data, section["reloc_raw"] + r * 10 + 8),
                   symbols[B.u32(data, section["reloc_raw"] + r * 10 + 4)]["name"])
                  for r in range(section["relocs"])]
        starts = sorted((s["value"], s["name"]) for s in members
                        if s["name"] != section["name"])
        entries = []
        for i, (value, name) in enumerate(starts):
            end = starts[i + 1][0] if i + 1 < len(starts) else section["size"]
            chunk = body[value:end].rstrip(b"\xcc")
            entries.append((name, len(chunk), chunk,
                            [(o - value, t, s) for o, t, s in relocs
                             if value <= o < value + len(chunk)]))
        out.append((parents[0], entries))
    return out


def resolve_relocs(size, relocs, symbol_map):
    """{offset: candidate addresses or None} for the relocs inside `size`, or
    None when one cannot be resolved — a REL32 whose callee is neither matched
    nor pinned leaves four zero bytes that would never match anything, so the
    body is not comparable and must not be claimed on a partial comparison."""
    out = {}
    for offset, rtype, symbol in relocs:
        if offset + 4 > size:
            continue  # reloc belongs to the next funclet in this section
        if rtype == 0x0006:  # DIR32: absolute, masked from the retail bytes
            out[offset] = None
        elif rtype == 0x0014:  # REL32: displacement resolved through symbol_map
            if symbol not in symbol_map:
                return None
            out[offset] = symbol_map[symbol]
        else:
            return None
    return out


def funclet_matches(size, body, resolved, by_size, cache):
    """Every unclaimed retail funclet this body reproduces exactly.

    The non-reloc bytes are compared through an index (a funclet is 8 bytes of
    which 4 are a displacement, so an unindexed scan is 10k comparisons per
    symbol); the REL32 displacements are then checked one candidate at a time,
    exactly as build.compile_function encodes them.
    """
    masked = {p for offset in resolved for p in range(offset, offset + 4)}
    fixed = tuple(p for p in range(size) if p not in masked)
    table = cache.get((size, fixed))
    if table is None:
        table = collections.defaultdict(list)
        for rva, target in by_size.get(size, ()):
            table[bytes(target[p] for p in fixed)].append(rva)
        cache[(size, fixed)] = table
    hits = []
    for rva in table.get(bytes(body[p] for p in fixed), ()):
        target = B.read_target_bytes(rva, size)
        if all(any(struct.pack("<i", address - (rva + offset + 4))
                   == target[offset:offset + 4] for address in candidates)
               for offset, candidates in resolved.items() if candidates is not None):
            hits.append(rva)
    return hits


def funclet_paths(batch):
    return PENDING_DIR / f"funclets_{batch:03d}.json"


# The `__CxxFrameHandler` FuncInfo the compiler emits per EH function. Only the
# first five fields are read: magic, and the two tables holding funclet targets.
FUNCINFO_MAGIC_PREFIX = 0x199305   # 0x19930520/21/22 across VC6..VC7.1
FUNCINFO_MAX_STATE = 4096
FUNCINFO_MAX_TRY = 1024
UNWIND_ENTRY = 8       # {toState, action}
TRYBLOCK_ENTRY = 20    # {tryLow, tryHigh, catchHigh, nCatches, pCatches}
HANDLER_ENTRY = 16     # {adjectives, pType, dispCatchObj, addressOfHandler}


def funcinfo_ownership(entries):
    """({funclet rva: owner function rva}, counts) read out of the retail image.

    Each `eh_` stub is `B8 <FuncInfo VA> E9 <__CxxFrameHandler>`; its FuncInfo
    lists the function's unwind actions and catch handlers, and those addresses
    ARE its funclets. The owning function names its stub in the prologue
    (`6A FF 68 <stub VA>`), so one indexed pass over .text for `push <stub VA>`
    closes the loop and ownership becomes a lookup rather than a guess.

    A stub reached from more than one function, or from none, yields nothing:
    the point of this map is that the parent is known, so an unknown one is
    dropped and counted rather than resolved by preference.
    """
    counts = collections.Counter()
    base = image_base()
    image, sections = B.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    lo, hi = text["rva"], text["rva"] + text["size"]

    stubs = {}
    for row in B.load_function_rows():
        if not row["notes"].startswith(EH_NOTE):
            continue
        rva = int(row["target_rva"], 16)
        body = B.read_target_bytes(rva, 10)
        if body[0] == 0xB8 and body[5] == 0xE9:
            stubs[rva] = B.u32(body, 1)
        else:
            counts["stub-not-B8-E9"] += 1

    # A prologue reference is attributed to the function whose body holds it, so
    # the ghidra inventory and the ledger both contribute boundaries: a matched
    # row is a boundary the inventory may not have, and vice versa.
    spans = sorted({(rva, rva + size) for rva, size, _ in entries}
                   | {(int(r["target_rva"], 16),
                       int(r["target_rva"], 16) + int(r["target_size"]))
                      for r in B.load_function_rows()})
    span_starts = [s for s, _ in spans]

    def enclosing(rva):
        i = bisect.bisect_right(span_starts, rva) - 1
        return spans[i][0] if i >= 0 and spans[i][0] <= rva < spans[i][1] else None

    body = B.read_target_bytes(lo, hi - lo)
    by_va = {rva + base: rva for rva in stubs}
    owners = collections.defaultdict(set)
    pos = body.find(b"\x68")
    while pos >= 0:
        if pos + 5 <= len(body):
            stub = by_va.get(B.u32(body, pos + 1))
            if stub is not None:
                owner = enclosing(lo + pos)
                if owner is None:
                    counts["push-outside-any-function"] += 1
                elif owner != stub:
                    owners[stub].add(owner)
        pos = body.find(b"\x68", pos + 1)

    def in_text(va):
        return lo <= va - base < hi

    ownership = {}
    for stub, funcinfo in sorted(stubs.items()):
        found = owners.get(stub, ())
        if len(found) != 1:
            counts["stub-owner-unknown" if not found else "stub-owner-ambiguous"] += 1
            continue
        offset = funcinfo - base
        if not 0 <= offset < len(image) - 32:
            counts["funcinfo-outside-image"] += 1
            continue
        header = B.read_target_bytes(offset, 32)
        if B.u32(header, 0) >> 8 != FUNCINFO_MAGIC_PREFIX:
            counts["funcinfo-bad-magic"] += 1
            continue
        states, unwind_map = B.u32(header, 4), B.u32(header, 8)
        tries, try_map = B.u32(header, 12), B.u32(header, 16)
        targets = set()
        if unwind_map and 0 < states < FUNCINFO_MAX_STATE:
            table = B.read_target_bytes(unwind_map - base, UNWIND_ENTRY * states)
            targets |= {B.u32(table, UNWIND_ENTRY * i + 4) for i in range(states)}
        if try_map and 0 < tries < FUNCINFO_MAX_TRY:
            table = B.read_target_bytes(try_map - base, TRYBLOCK_ENTRY * tries)
            for i in range(tries):
                catches = B.u32(table, TRYBLOCK_ENTRY * i + 12)
                handlers = B.u32(table, TRYBLOCK_ENTRY * i + 16)
                if handlers and 0 < catches < 256:
                    entry = B.read_target_bytes(handlers - base, HANDLER_ENTRY * catches)
                    targets |= {B.u32(entry, HANDLER_ENTRY * i + 12) for i in range(catches)}
        owner = next(iter(found))
        for target in targets:
            if not target or not in_text(target):
                continue
            if ownership.setdefault(target - base, owner) != owner:
                # Two FuncInfos naming one address means identical funclets were
                # folded; neither owner is then provable, so both lose it.
                counts["funclet-folded-across-owners"] += 1
                ownership[target - base] = None
    counts["stubs"] = len(stubs)
    counts["owned-funclets"] = sum(1 for o in ownership.values() if o is not None)
    return {f: o for f, o in ownership.items() if o is not None}, counts


def sweep_refusal(reason, name, source, funclets, sizes):
    return (reason, name, source, len(funclets),
            sum(sizes[f] for f in funclets), frozenset(funclets))


def claim_funclets(candidates, order, sizes, symbol_map, counts):
    """{funclet rva: (source, object symbol)} for the `candidates` one of the
    objects in `order` reproduces exactly, taking the first that can prove each.

    The image has already said these funclets are the parent's, so the bytes only
    have to pair them up — but anything short of ONE symbol to ONE funclet both
    ways round leaves the individual identities unproven, and those are dropped.
    """
    index_by_size = collections.defaultdict(list)
    for rva in candidates:
        index_by_size[sizes[rva]].append((rva, B.read_target_bytes(rva, sizes[rva])))
    proved = {}
    for source, funclets in order:
        cache, found = {}, []
        for symbol, size, body, relocs in funclets:
            if symbol.startswith(EHHANDLER_PREFIX):
                continue  # the stub itself; retail's copy is an eh_ row already
            counts["symbols"] += 1
            resolved = resolve_relocs(size, relocs, symbol_map)
            if resolved is None:
                counts["unresolvable"] += 1
                continue
            found.append((symbol, funclet_matches(size, body, resolved,
                                                  index_by_size, cache)))
        hits = collections.defaultdict(list)
        for symbol, matched in found:
            for rva in matched:
                hits[rva].append(symbol)
        for symbol, matched in found:
            if len(matched) == 1 and len(hits[matched[0]]) == 1:
                proved.setdefault(matched[0], (source, symbol))
            elif matched:
                counts["ambiguous-inside-parent"] += 1
        if candidates <= set(proved):
            break
    return proved


def cmd_sweep_funclets(args):
    entries = load_ghidra()
    owned, index = foreign_claims("gen-funclet;")
    population = [(rva, size, name) for rva, size, name in entries
                  if name.startswith(FUNCLET_PREFIXES)]
    sizes = {rva: size for rva, size, name in population
             if rva not in owned and find_overlap(index, rva, size) is None}

    ownership, counts = funcinfo_ownership(entries)
    # The owner is a retail address; the parent that can PROVE a funclet is a
    # ledger row STARTING there, because only a row names a source whose object
    # holds the `.text$x` symbols. Containment would be wrong: a partial TU
    # claiming a function's tail, or a MASM dump spanning several functions,
    # contains the address without being that function.
    ledger = collections.defaultdict(set)
    for row in B.load_function_rows():
        ledger[int(row["target_rva"], 16)].add((row["name"], row["source"]))

    by_owner = collections.defaultdict(set)
    for rva in sizes:
        owner = ownership.get(rva)
        if owner is None:
            counts["funclet-no-owner"] += 1
            continue
        rows_here = ledger.get(owner)
        if not rows_here:
            counts["owner-unmatched"] += 1
            continue
        for key in rows_here:
            by_owner[key].add(rva)

    symbol_map = B.load_symbol_map()
    # A funclet is proved by any current object that emits its parent, not only
    # by the object of the row that named the owner: an EH parent is a COMDAT,
    # and the row that claimed the retail body is often a MASM dump or a partial
    # `*Thunk.cpp` that emits no `.text$x` at all while a dozen ordinary TUs
    # instantiating the same header do. The owner still decides the parent —
    # this only widens where its symbols may be read from.
    wanted = collections.defaultdict(set)
    for name, source in by_owner:
        wanted[name].add(source)
    emitters = collections.defaultdict(list)
    for source in sorted({r["source"] for r in B.load_function_rows()}):
        path = ROOT / source
        # Only an object that provably matches its current source may be swept: a
        # stale one describes code the gate no longer compiles, and its rows would
        # die in the land gate after the ledger had already been appended to.
        if not B.compile_is_current(path, B.obj_path(path)):
            counts["stale-object"] += 1
            continue
        counts["current-object"] += 1
        for parent, funclets in read_funclet_sections(B.obj_path(path)):
            if parent in wanted:
                emitters[parent].append((source, funclets))

    claims, refusals = {}, []
    for name in sorted(wanted):
        candidates = set().union(*(by_owner[(name, s)] for s in wanted[name]))
        # The owner's own source first, so a parent that can prove itself is not
        # attributed to somebody else's copy of the same COMDAT.
        order = sorted(emitters.get(name, ()),
                       key=lambda e: (e[0] not in wanted[name], e[0]))
        if not order:
            refusals.append(sweep_refusal("no-emitting-object", name,
                                          sorted(wanted[name])[0], candidates, sizes))
            continue
        for rva, (source, symbol) in claim_funclets(candidates, order, sizes,
                                                    symbol_map, counts).items():
            claims.setdefault(rva, (source, name, symbol))
        if candidates - set(claims):
            refusals.append(sweep_refusal("no-symbol-reproduces", name, order[0][0],
                                          candidates - set(claims), sizes))

    # A landed row whose parent this map disagrees with is never overwritten
    # here: the row already carries a name, so a second attribution has to be
    # reported for a human to retract rather than quietly re-pointed.
    landed = {int(r["target_rva"], 16): (r["source"], r["notes"])
              for r in B.load_all_function_rows() if r["notes"].startswith("gen-funclet;")}
    contested = []
    for rva, (source, notes) in sorted(landed.items()):
        parent = next((p[len("parent="):] for p in notes.split(";")
                       if p.startswith("parent=")), None)
        claim = claims.get(rva)
        if claim is not None and claim[:2] != (source, parent):
            contested.append((rva, source, parent,
                              f"the map gives it to {claim[1]} ({claim[0]})"))
            del claims[rva]
        elif claim is None:
            owner = ownership.get(rva)
            contested.append((rva, source, parent,
                              "no FuncInfo reaches it (its owner's stub is not an eh_ row)"
                              if owner is None else
                              f"the map gives it to the function at 0x{owner:08X}, which no "
                              "matched row starts at"))

    rows = []
    for rva, (source, parent, symbol) in sorted(claims.items()):
        rows.append(format_row(f"uw_{rva:08x}", rva, sizes[rva], source,
                               f"gen-funclet;parent={parent};object-symbol={symbol}"))
    ranges = sorted((rva, rva + sizes[rva]) for rva in claims)
    for (_, end), (start, _) in zip(ranges, ranges[1:]):
        if start < end:
            raise FormatError(f"two claimed funclets overlap at 0x{start:08X}")

    # Batch by whole parent source, never by row: a batch's gate is one
    # ./build.sh over its parents, and build.py takes the host-wide exclusive
    # build lock once a single run has to compile more than eight objects.
    by_source = collections.defaultdict(list)
    for row in rows:
        by_source[row.split(",")[4]].append(row)
    groups = sorted(by_source)
    batches = [groups[i:i + args.limit] for i in range(0, len(groups), args.limit)]
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    for stale in PENDING_DIR.glob("funclets_*.json"):
        stale.unlink()
    for number, batch_sources in enumerate(batches):
        funclet_paths(number).write_text(json.dumps(
            {"sources": batch_sources, "pins": [],
             "rows": [row for source in batch_sources for row in by_source[source]]},
            indent=1) + "\n", encoding="utf-8")

    for rva, source, parent, says in contested:
        print(f"sweep-funclets: CONTESTED-SINCE-LANDED 0x{rva:08X}: landed as "
              f"{parent} ({source}), {says} — the byte-uniqueness sweep that landed "
              "it could not see the owner, so the attribution is unproven",
              file=sys.stderr)
    for reason, name, source, count, size, _ in sorted(refusals):
        print(f"sweep-funclets: REFUSED {reason} {name} ({source}): "
              f"{count} funclet(s) {size} bytes", file=sys.stderr)

    attributed = set().union(*by_owner.values()) if by_owner else set()
    claimed_bytes = sum(sizes[r] for r in claims)
    refused = set().union(*(set(r[5]) for r in refusals)) if refusals else set()
    print(f"sweep-funclets: retail funclet population {len(population)} "
          f"({sum(s for _, s, _ in population)} bytes)")
    print(f"  {len(population) - len(sizes)} already claimed by other ledger rows")
    print(f"  {len(sizes)} unclaimed: {len(attributed)} under {len(wanted)} matched "
          f"owner name(s) ({sum(sizes[f] for f in attributed)} bytes), "
          f"{counts['owner-unmatched']} owned by unmatched functions, "
          f"{counts['funclet-no-owner']} with no FuncInfo owner")
    print(f"  {len(claims)} claimed here ({claimed_bytes} bytes) + "
          f"{len(refused)} refused ({sum(sizes[f] for f in refused)} bytes) over "
          f"{len(refusals)} owner(s): "
          + ", ".join(f"{reason}={sum(r[3] for r in refusals if r[0] == reason)}"
                      for reason in sorted({r[0] for r in refusals})))
    print("  " + ", ".join(f"{kind}={count}" for kind, count in sorted(counts.items())))
    print(f"  {len(rows)} row(s) in {len(batches)} batch(es) -> "
          f"{PENDING_DIR.relative_to(ROOT)}/funclets_NNN.json"
          + (f"; {len(contested)} landed row(s) contested, listed above" if contested else ""))


# --------------------------------------------------------------------------
# STL template grid
# --------------------------------------------------------------------------
#
# The game links STLport 4.5.3, so a container member the retail image holds is
# not lost source: it IS vendor/stlport, instantiated over a payload type. The
# payload's name never reaches the bytes -- only its size, its alignment and
# whether its lifecycle is trivial do -- so instantiating the same template over
# a synthetic payload of the same shape reproduces the retail COMDAT exactly.
#
# Two things decide how a pattern may be claimed:
#
#   (a) A body with no call into the payload's own members is the same code in
#       every instantiation of that shape, so ONE instantiation stands in for
#       every retail site. The rows are `tg_<rva>` with an `object-symbol=` note
#       -- the mangled instantiation name cannot be the row name, because one
#       name may claim only one address.
#   (b) A body that calls the payload's constructor or destructor encodes THAT
#       class's address in a rel32 slot, so each retail site gets its own
#       payload type `Gen_t_<rva>_<shape>` and its own pins. The row name is
#       then the per-site instantiation symbol, unique by construction.
#
# Every callee address is read out of the retail bytes and cross-checked: slots
# naming one symbol inside a body must agree, and a symbol shared across sites
# (operator delete, _M_increment, memmove) is narrowed to the ONE address the
# sites agree on. A site that reaches anything else is refused by name rather
# than resolved through a pin that also answers for something else.

TGRID_NOTE = "gen-tgrid"
TGRID_MIN_SIZE = 17
TGRID_MAX_SIZE = 4096
# Grid TUs are numbered by their position in TGRID_SPECS so that widening the
# grid never renumbers a landed file; instance batches start past them.
TGRID_INSTANCE_BASE = 100
TGRID_PROBE_PREFIX = "tgprobe_"

# tag       payload identifier; the C++ name is Gen_<tag> (or Gen_t_<rva>_<tag>)
# size      sizeof the synthetic payload, which is what the bytes encode
# kind      pod = trivial; cd = extern ctor/copy/dtor/assign; key = cd plus <
# spelling  a builtin type emitted verbatim instead of a struct
TgPayload = collections.namedtuple("TgPayload", "tag size kind spelling")
# key       cell identifier, unique across the whole grid
# payloads  the payload types the cell's lines are written over
# lines     %-format instantiation lines; %(p0)s.. are the payloads, %(pair)s a
#           per-cell typedef name
TgCell = collections.namedtuple("TgCell", "key payloads lines")
TgSpec = collections.namedtuple("TgSpec", "dim key includes cells flags")
# STLport codegen depends on the CRT model and NDEBUG, so a dimension may
# need the flags the retail TUs used; everything else compiles like the
# repo's other exception-handling sources.
TgSpec.__new__.__defaults__ = (("/EHsc",),)
TgPattern = collections.namedtuple("TgPattern", "symbol spec cell size body relocs mode")


def tg_pod(size):
    return TgPayload(f"p{size}pod", size, "pod", None)


def tg_cd(size):
    return TgPayload(f"p{size}cd", size, "cd", None)


TG_INT = TgPayload("int", 4, "raw", "int")
TG_PTR = TgPayload("ptr", 4, "raw", "void *")
TG_KEY = TgPayload("k4", 4, "key", None)


def tg_type(payload, tag):
    """The C++ spelling of `payload` in a generic (tag "") or per-site TU."""
    if payload.spelling is not None:
        return payload.spelling
    return f"Gen_t_{tag}_{payload.tag}" if tag else f"Gen_{payload.tag}"


def tg_payload_lines(payload, tag):
    """The synthetic payload's declaration, or nothing for a builtin.

    Only the layout and the lifecycle reach the bytes: a `cd` payload declares
    its members and never defines them, which is what makes its constructor and
    destructor extern calls whose target the retail body supplies. The
    comparison operators are declared for every payload because list::sort and
    _Rb_tree instantiate members that need them.
    """
    if payload.spelling is not None:
        return []
    name = tg_type(payload, tag)
    field = {1: "char a;", 2: "short a;"}.get(payload.size, f"int a[{payload.size // 4}];")
    if payload.size >= 4 and payload.size % 4:
        raise FormatError(f"payload {payload.tag} is {payload.size} bytes; the grid's "
                          "synthetic payloads are whole ints past 4 bytes")
    decl = f"struct {name} {{ {field}"
    if payload.kind != "pod":
        decl += (f" {name}(); {name}(const {name}&); ~{name}();"
                 f" {name}& operator=(const {name}&);")
    # A `cmp` key orders through an extern member returning int, the way the
    # game's string classes do: `less<K>` then inlines to one thiscall and a
    # signed test, where a free `operator<` would be a cdecl call and a bool.
    if payload.kind == "cmp":
        return [decl + f" int compare(const {name}&) const;"
                       f" bool operator<(const {name}& o) const "
                       f"{{ return compare(o) < 0; }} }};",
                f"bool operator==(const {name}&, const {name}&);"]
    return [decl + " };",
            f"bool operator==(const {name}&, const {name}&);",
            f"bool operator<(const {name}&, const {name}&);"]


def tg_cell_lines(cell, tag):
    """This cell's instantiation lines, over generic or per-site payload names."""
    subs = {f"p{index}": tg_type(payload, tag)
            for index, payload in enumerate(cell.payloads)}
    subs["pair"] = f"TgPair_{cell.key}" + (f"_{tag}" if tag else "")
    return [line % subs for line in cell.lines]


def tg_vector_cell(payload):
    return TgCell(f"vec_{payload.tag}", (payload,),
                  ("template class _STL::vector<%(p0)s >;",))


def tg_list_cell(payload):
    return TgCell(f"list_{payload.tag}", (payload,),
                  ("template class _STL::list<%(p0)s >;",))


def tg_deque_cell(payload):
    return TgCell(f"deque_{payload.tag}", (payload,),
                  ("template class _STL::deque<%(p0)s >;",))


def tg_slist_cell(payload):
    return TgCell(f"slist_{payload.tag}", (payload,),
                  ("template class _STL::slist<%(p0)s >;",))


def tg_tree_cell(key, value):
    return TgCell(f"tree_{key.tag}_{value.tag}", (key, value), (
        "typedef _STL::pair<const %(p0)s, %(p1)s > %(pair)s;",
        "template class _STL::_Rb_tree<%(p0)s, %(pair)s, _STL::_Select1st<%(pair)s >, "
        "_STL::less<%(p0)s >, _STL::allocator<%(pair)s > >;"))


def tg_set_cell(payload):
    return TgCell(f"set_{payload.tag}", (payload,), (
        "template class _STL::_Rb_tree<%(p0)s, %(p0)s, _STL::_Identity<%(p0)s >, "
        "_STL::less<%(p0)s >, _STL::allocator<%(p0)s > >;",))


def tg_hash_cell(key, value):
    return TgCell(f"hash_{key.tag}_{value.tag}", (key, value), (
        "typedef _STL::pair<const %(p0)s, %(p1)s > %(pair)s;",
        "template class _STL::hash_map<%(p0)s, %(p1)s, _STL::hash<%(p0)s >, "
        "_STL::equal_to<%(p0)s >, _STL::allocator<%(pair)s > >;"))


def tg_construct_cell(payload):
    return TgCell(f"ctor_{payload.tag}", (payload,), (
        "template void _STL::_Construct(%(p0)s*, const %(p0)s&);",
        "template void _STL::_Destroy(%(p0)s*);"))


def tg_construct_pair_cell(key, value):
    return TgCell(f"ctorp_{key.tag}_{value.tag}", (key, value), (
        "typedef _STL::pair<const %(p0)s, %(p1)s > %(pair)s;",
        "template void _STL::_Construct(%(pair)s*, const %(pair)s&);",
        "template void _STL::_Destroy(%(pair)s*);"))


def tg_uninit_cell(payload):
    return TgCell(f"uninit_{payload.tag}", (payload,), (
        "template %(p0)s* _STL::uninitialized_copy(const %(p0)s*, const %(p0)s*, %(p0)s*);",
        "template %(p0)s* _STL::uninitialized_fill_n(%(p0)s*, unsigned int, "
        "const %(p0)s&);"))


TG_POD_SIZES = (1, 2, 4, 8, 12, 16, 24, 32)
TG_CD_SIZES = (4, 8, 12, 16, 24, 32)
TG_TREE_VALUES = (tg_pod(4), tg_pod(8), tg_pod(12), tg_pod(16),
                  tg_cd(8), tg_cd(12), tg_cd(16), tg_cd(24))
TG_WIDE_POD = (40, 48, 64, 128)
TG_WIDE_CD = (40, 48, 64)

# Each TgSpec is one committed TU. Widening appends specs; it never edits one,
# so a landed file's content never changes under a later run.
#
# Measured marginal yield, each dimension scanned against the ledger AFTER the
# ones above it landed (2026-08-03): base 131,815B, wide 8,921B, deque 11,350B,
# hash 27,416B, then slist 88B and str 1,207B. The last two are left here
# because a moving ledger may make them worth more later, but at those numbers a
# whole extra TU in the full gate is not repaid, so they are not landed.
# basic_string stays largely unreproduced: 15 of its 323 patterns hit even under
# the flags its matched retail TUs use (/MD /DNDEBUG /D_STLP_USE_STATIC_LIB),
# which buys 1,207B against 840B under plain /EHsc. Its config is still wrong.
TGRID_SPECS = [
    TgSpec("base", "vec", ("vector",),
           [tg_vector_cell(p) for p in (TG_INT, TG_PTR,
                                        *[tg_pod(s) for s in TG_POD_SIZES],
                                        *[tg_cd(s) for s in TG_CD_SIZES])]),
    TgSpec("base", "list", ("list",),
           [tg_list_cell(p) for p in (TG_INT, TG_PTR,
                                      *[tg_pod(s) for s in (4, 8, 12, 16)],
                                      *[tg_cd(s) for s in (4, 8, 12, 16)])]),
    TgSpec("base", "tree", ("map",),
           [tg_tree_cell(k, v) for k in (TG_INT, TG_KEY) for v in TG_TREE_VALUES]),
    TgSpec("base", "help", ("memory", "utility"),
           [tg_construct_cell(p) for p in (tg_cd(4), tg_cd(8), tg_cd(12), tg_cd(16),
                                           tg_cd(24), tg_cd(32))]
           + [tg_construct_pair_cell(k, v) for k in (TG_INT, TG_KEY)
              for v in (tg_pod(4), tg_pod(8), tg_cd(8), tg_cd(12), tg_cd(16))]
           + [tg_uninit_cell(p) for p in (tg_cd(8), tg_cd(12), tg_cd(16), tg_cd(24))]),
    TgSpec("str", "str", ("string",),
           [TgCell("str_char", (), (
               "template class _STL::basic_string<char, _STL::char_traits<char>, "
               "_STL::allocator<char> >;",)),
            TgCell("str_wide", (), (
                "template class _STL::basic_string<unsigned short, "
                "_STL::char_traits<unsigned short>, _STL::allocator<unsigned short> >;",))],
           ("/DNDEBUG", "/DWIN32", "/D_WINDOWS", "/MD", "/EHsc",
            "/D_STLP_USE_STATIC_LIB")),
    TgSpec("wide", "vec2", ("vector",),
           [tg_vector_cell(p) for p in ([tg_pod(s) for s in TG_WIDE_POD]
                                        + [tg_cd(s) for s in TG_WIDE_CD])]),
    TgSpec("wide", "tree2", ("map", "set"),
           [tg_tree_cell(k, v) for k in (TG_INT, TG_KEY)
            for v in (tg_pod(24), tg_pod(32), tg_cd(4), tg_cd(32))]
           + [tg_set_cell(p) for p in (TG_INT, TG_PTR, TG_KEY, tg_cd(8), tg_cd(12))]),
    TgSpec("deque", "deque", ("deque",),
           [tg_deque_cell(p) for p in (TG_INT, TG_PTR, tg_pod(8), tg_pod(12),
                                       tg_pod(16), tg_cd(8), tg_cd(12), tg_cd(16))]),
    TgSpec("slist", "slist", ("slist",),
           [tg_slist_cell(p) for p in (TG_INT, TG_PTR, tg_pod(8), tg_pod(12),
                                       tg_pod(16), tg_cd(8), tg_cd(12), tg_cd(16))]),
    TgSpec("hash", "hash", ("hash_map",),
           [tg_hash_cell(k, v) for k in (TG_INT,)
            for v in (tg_pod(4), tg_pod(8), tg_pod(12), tg_cd(8), tg_cd(12), tg_cd(16))]),
]

TGRID_HEADER = [
    "// Each row this file carries is a retail body that IS this instantiation:",
    "// the game links STLport 4.5.3, so a container member's code is the vendor",
    "// template over a payload of that shape, and the payload's name never",
    "// reaches the bytes. The synthetic payloads below are anonymous by design --",
    "// they reproduce a layout and a lifecycle, never a class identity -- and",
    "// every call target is read out of the retail bytes and pinned in",
    "// reverse/symbols.csv, so the bytes prove the callee.",
]


def tg_render(command, includes, body_lines, flags=("/EHsc",)):
    """One grid or instance TU. `// stlport` and `// cl:` must stay in the first
    lines: build.py reads only the head of a source to decide both."""
    lines = ["// cl: " + " ".join(flags), "// stlport",
             f"// Generated by: python3 tools/gen_small.py {command}",
             "// Do not edit by hand; regenerate instead.", "//", *TGRID_HEADER, ""]
    lines += [f"#include <{name}>" for name in includes]
    lines.append("")
    lines += body_lines
    return "\n".join(lines) + "\n"


def tg_spec_body(spec, tag=""):
    """Payload declarations (deduplicated, in first use order) plus cell lines."""
    seen, payloads, cells = set(), [], []
    for cell in spec.cells:
        for payload in cell.payloads:
            if payload.tag not in seen:
                seen.add(payload.tag)
                payloads += tg_payload_lines(payload, tag)
        cells += tg_cell_lines(cell, tag)
    return payloads + ([""] if payloads else []) + cells


def tg_specs(dims):
    """The grid TUs this run instantiates, with their fixed TU numbers."""
    wanted = None if dims in (None, "all") else set(dims.split(","))
    if wanted is not None:
        unknown = wanted - {spec.dim for spec in TGRID_SPECS}
        if unknown:
            raise SystemExit(f"gen_small: unknown grid dimension(s) {sorted(unknown)}; "
                             f"known: {sorted({s.dim for s in TGRID_SPECS})}")
    keys = collections.Counter(cell.key for spec in TGRID_SPECS for cell in spec.cells)
    duplicated = sorted(key for key, count in keys.items() if count > 1)
    if duplicated:
        raise FormatError(f"grid cell(s) {duplicated} appear in more than one TU; each "
                          "instantiation must live in exactly one translation unit")
    return [(index, spec) for index, spec in enumerate(TGRID_SPECS)
            if wanted is None or spec.dim in wanted]


def tg_source_path(number):
    return GEN_DIR / f"tgrid_{number:03d}.cpp"


def tg_is_payload(symbol):
    """True for a symbol parameterised by one of the grid's payload types."""
    return "Gen_" in symbol


def tg_object_bodies(obj):
    """[(symbol, body)] for the .text COMDATs an instantiation TU defines.

    A COMDAT section can be padded to alignment, so the symbol's extent is the
    section minus its trailing int3 fill; a body that then does not end on a
    whole instruction has no knowable extent and is dropped rather than scanned
    at a size the retail function may not have.
    """
    data = obj.read_bytes()
    out, seen = [], set()
    for symbol in B.read_object_symbols(data):
        name = symbol["name"]
        if symbol["section"] <= 0 or not name.startswith("?") or name in seen:
            continue
        seen.add(name)
        try:
            raw, relocs = B.read_object_symbol_bytes(obj, name)
        except ValueError:
            continue
        body = bytes(raw).rstrip(b"\xcc")
        if not TGRID_MIN_SIZE <= len(body) <= TGRID_MAX_SIZE:
            continue
        if terminator(body) in (None, "int3"):
            continue
        out.append((name, body, tuple((offset, rtype, target)
                                      for offset, rtype, target in relocs
                                      if offset < len(body))))
    return out


def tg_probe(specs):
    """{symbol: TgPattern} for every body the grid emits, by cell.

    One probe TU per cell, compiled into the untracked scratch tree: a pattern's
    cell is what an instance TU has to re-emit under renamed payloads, and it is
    knowable exactly this way instead of parsed back out of a mangled name.
    """
    PENDING_DIR.mkdir(parents=True, exist_ok=True)
    patterns, cells = {}, 0
    for _, spec in specs:
        for cell in spec.cells:
            cells += 1
            source = PENDING_DIR / f"{TGRID_PROBE_PREFIX}{cell.key}.cpp"
            text = tg_render(f"gen-tgrid (probe {cell.key})", spec.includes,
                             [line for payload in cell.payloads
                              for line in tg_payload_lines(payload, "")]
                             + tg_cell_lines(cell, ""), spec.flags)
            if not source.exists() or source.read_text(encoding="utf-8") != text:
                source.write_text(text, encoding="utf-8")
            obj = B.obj_path(source)
            if not B.compile_is_current(source, obj):
                B.compile_source(source, obj)
            for symbol, body, relocs in tg_object_bodies(obj):
                if symbol in patterns:
                    continue
                mode = "b" if any(rtype == 0x0014 and tg_is_payload(target)
                                  for _, rtype, target in relocs) else "a"
                patterns[symbol] = TgPattern(symbol, spec, cell, len(body), body,
                                             relocs, mode)
    print(f"gen-tgrid: probed {cells} cell(s) in {len(specs)} TU(s): {len(patterns)} "
          f"distinct body pattern(s) >= {TGRID_MIN_SIZE}B ("
          + ", ".join(f"mode {mode}={count}" for mode, count in sorted(
              collections.Counter(p.mode for p in patterns.values()).items())) + ")")
    return patterns


def tg_fixed_offsets(pattern):
    """The byte positions a candidate has to reproduce exactly: everything
    outside the relocation slots, which are per-site addresses by construction."""
    masked = {position for offset, _, _ in pattern.relocs
              for position in range(offset, min(offset + 4, pattern.size))}
    return tuple(position for position in range(pattern.size) if position not in masked)


def tg_scan(patterns, entries, blacklist, owned, index, transparent):
    """{rva: (body, [patterns])} over unclaimed inventory space only.

    Start-exact and size-exact against the boundaries in `entries`: a template
    body that happens to appear inside a larger function is not that function.

    `transparent` is dump_boundaries(): a supersedable dump row hides its own
    range from `owned` and from the overlap index, so a candidate over exactly
    that range sees open ground -- and only over exactly that range, which is
    the one shape `validate_rows` accepts at land time.

    A site can match several patterns, and which one it is matters: masking the
    rel32 slots makes `_Rb_tree_iterator::operator++` and `operator--` the same
    template, and they differ only in whether the slot reaches `_M_increment` or
    `_M_decrement`. Every match is returned so the callee addresses decide.
    """
    sizes = {pattern.size for pattern in patterns.values()}
    by_size = collections.defaultdict(list)
    for rva, size, name in entries:
        if size not in sizes or rva in blacklist:
            continue
        dump = transparent.get(rva)
        supersedable = dump is not None and dump[0] == size
        if rva in owned and not supersedable:
            continue
        if find_overlap(index, rva, size,
                        skip=dump[1] if supersedable else None) is not None:
            continue
        by_size[size].append((rva, B.read_target_bytes(rva, size), name))

    tables, hits = {}, {}
    for symbol in sorted(patterns):
        pattern = patterns[symbol]
        fixed = tg_fixed_offsets(pattern)
        table = tables.get((pattern.size, fixed))
        if table is None:
            table = collections.defaultdict(list)
            for rva, body, name in by_size.get(pattern.size, ()):
                table[bytes(body[position] for position in fixed)].append((rva, body, name))
            tables[(pattern.size, fixed)] = table
        for rva, body, name in table.get(
                bytes(pattern.body[position] for position in fixed), ()):
            hits.setdefault(rva, (body, []))[1].append(pattern)
    return hits


def tg_callees(pattern, rva, body, resolved, text_range):
    """({symbol: (offset, addresses)}, None) for one site, or (None, reason).

    Every rel32 slot is read out of the retail bytes and resolved through the
    incremental-link thunk table, because a call to a body and a call to that
    body's thunk are the same call. Two slots naming one symbol must land on one
    address: if they do not, this body is not this instantiation and pinning
    either would be a guess.
    """
    lo, hi = text_range
    slots = collections.defaultdict(list)
    for offset, rtype, symbol in pattern.relocs:
        if rtype != 0x0014:
            continue
        reached = rva + offset + 4 + struct.unpack_from("<i", body, offset)[0]
        if not lo <= reached < hi:
            return None, (f"callee-outside-text: slot +{offset} ({symbol}) reaches "
                          f"0x{reached:08X}")
        slots[symbol].append((offset, reached, {reached} | resolved.get(reached, set())))
    out = {}
    for symbol, occurrences in slots.items():
        agreed = set.intersection(*(candidates for _, _, candidates in occurrences))
        if not agreed:
            return None, ("callee-slot-disagreement: " + ", ".join(
                f"+{offset} reaches 0x{reached:08X}" for offset, reached, _ in occurrences)
                + f" for {symbol} — the slots name different callees")
        out[symbol] = (occurrences[0][0], agreed)
    return out, None


def tg_pick(addresses, resolved):
    """One address to pin from a slot's candidates, preferring the body over its
    incremental-link thunk so the gate can encode whichever a site used."""
    return min(addresses, key=lambda address: (address in resolved, address))


def tg_reachable(address, thunks):
    """Every address a call to `address` may encode: the body and its
    incremental-link thunks, exactly what build.load_symbol_map offers a pin."""
    return {address} | set(thunks.get(address, ()))


def tg_shared_addresses(observed, ledger_names, pinned, thunks, resolved, refusals):
    """({symbol: allowed addresses}, {symbol: new pin address}).

    A symbol every site shares (operator delete, _M_increment, memmove) resolves
    to ONE function: whatever the sites agree on, taken as the body rather than
    the thunk a particular site called through, so every site's spelling of that
    call resolves. Narrowing to it is the point -- symbols.csv already answers
    `??3@YAXPAX@Z` with three addresses and `??2@YAPAXI@Z` with seven, and a slot
    that may resolve to any of them proves nothing about which function ran.
    """
    allowed, new_pins = {}, {}
    for symbol, sightings in sorted(observed.items()):
        counts = collections.Counter(tg_pick(addresses, resolved)
                                     for addresses in sightings)
        best = min(counts, key=lambda address: (-counts[address], address))
        consensus = tg_reachable(best, thunks)
        known = set(pinned.get(symbol, ()))
        if symbol in ledger_names:
            known.add(ledger_names[symbol])
        if not known:
            allowed[symbol], new_pins[symbol] = consensus, best
            continue
        narrowed = consensus.intersection(
            *[set().union(*(tg_reachable(address, thunks) for address in known))])
        if not narrowed:
            refusals.append((0, symbol, "shared-callee-unpinnable: sites reach "
                             f"0x{best:08X}, but {symbol} already resolves to "
                             + ", ".join(f"0x{a:08X}" for a in sorted(known))))
            allowed[symbol] = set()
            continue
        allowed[symbol] = narrowed
    return allowed, new_pins


def tg_instance_symbol(pattern, symbol, tag):
    """`symbol` with every generic payload name replaced by this site's.

    MSVC's back references are positional, so renaming a class name in place
    keeps the rest of the mangling valid; the name is looked up in the compiled
    object afterwards, so a rename this did not get right is a refusal, never a
    silent miss.
    """
    for payload in pattern.cell.payloads:
        if payload.spelling is None:
            symbol = symbol.replace(f"{tg_type(payload, '')}@", f"{tg_type(payload, tag)}@")
    return symbol


def tg_instance_lines(pattern, rva):
    """The payload declarations and instantiation for one per-site claim."""
    tag = f"{rva:08x}"
    lines = [f"// 0x{rva:08X} {pattern.cell.key}"]
    for payload in pattern.cell.payloads:
        lines += tg_payload_lines(payload, tag)
    return lines + tg_cell_lines(pattern.cell, tag)


def tg_verify(source_path, rows, pins, thunks):
    """(verified rows, [(name, reason)]) — compile the batch and prove each row
    exactly the way ./build.sh will, before a single row reaches the ledger.

    The scan proved the retail bytes equal a pattern outside its relocation
    slots; this proves the source about to be committed compiles to that pattern
    and that every slot resolves to the address the row's pins claim. Without it
    a bad rename or a mis-read callee lands as a reverted batch instead of a
    reported refusal.
    """
    obj = B.obj_path(source_path)
    B.compile_source(source_path, obj)
    symbol_map = B.load_symbol_map()
    for pin in pins:
        name, address = pin.split(",")[0], int(pin.split(",")[1], 16)
        candidates = symbol_map.setdefault(name, [])
        for candidate in thunks.get(address, []) + [address]:
            if candidate not in candidates:
                candidates.append(candidate)
    for row in rows:  # rows in one batch resolve each other's recursive calls
        name, _, target_rva, _, _, _, _ = row.split(",")
        address = int(target_rva, 16)
        symbol_map.setdefault(name, thunks.get(address, []) + [address])

    verified, failed = [], []
    for row in rows:
        name, _, target_rva, target_size, source, _, notes = row.split(",")
        record = {"name": name, "target_rva": target_rva, "target_size": target_size,
                  "source": source, "notes": notes}
        try:
            patch = B.compile_function(record, symbol_map, obj)
        except ValueError as error:
            failed.append((name, f"symbol-absent: {error}"))
        else:
            if patch["unresolved"]:
                failed.append((name, "unresolved-callee: "
                               + ", ".join(sorted(set(patch["unresolved"])))))
            elif patch["bytes"] != patch["target"]:
                failed.append((name, f"byte-mismatch: retail {patch['target'].hex()} != "
                                     f"generated {patch['bytes'].hex()}"))
            else:
                verified.append(row)
    return verified, failed


def tg_write_batch(source_path, text, rows, pins, thunks, report, label=TGRID_NOTE):
    """Render, verify and record one batch; returns the rows that survived."""
    source_rel = source_path.relative_to(ROOT).as_posix()
    GEN_DIR.mkdir(parents=True, exist_ok=True)
    source_path.write_text(text, encoding="utf-8")
    verified, failed = tg_verify(source_path, rows, pins, thunks)
    for name, reason in failed:
        print(f"{label}: VERIFY-FAILED {name}: {reason}", file=sys.stderr)
    report["verify-failed"] += len(failed)
    if not verified:
        return []
    pending = PENDING_DIR / (source_path.stem + ".json")
    pending.write_text(json.dumps({"source": source_rel, "rows": verified,
                                   "pins": sorted(set(pins))}, indent=1) + "\n",
                       encoding="utf-8")
    print(f"{label}: {source_rel}: {len(verified)} row(s), "
          f"{sum(int(row.split(',')[3]) for row in verified)} bytes, "
          f"{len(set(pins))} pin(s), {len(failed)} verify-failed")
    return verified


TgResolution = collections.namedtuple(
    "TgResolution", "claimable chosen callees allowed new_pins pinned resolved thunks")


def tg_resolve(hits, label):
    """Which pattern explains each scanned site, and every callee its bytes name.

    Shared by the grid and the family library: the argument is the same in both.
    A site's rel32 slots are read out of the retail bytes, a symbol several sites
    call is narrowed to the one address they agree on, and a site whose slot
    reaches anything else is refused by name. Nothing here is a guess that a
    later gate would have to catch.
    """
    text, lo = text_section()
    text_range = (lo, lo + len(text))
    resolved, thunks = call_targets(), B.build_call_thunks()
    ledger_names = {row["name"]: int(row["target_rva"], 16)
                    for row in B.load_all_function_rows()}
    pinned = load_pin_addresses()

    refusals, resolutions, viable = [], {}, {}
    for rva, (body, candidates) in sorted(hits.items()):
        for pattern in candidates:
            found, reason = tg_callees(pattern, rva, body, resolved, text_range)
            if found is None:
                refusals.append((rva, pattern.symbol, reason))
            else:
                resolutions[(rva, pattern.symbol)] = found
                viable.setdefault(rva, []).append(pattern)

    # The consensus on a shared callee is taken from the sites only one pattern
    # explains; those are the ones that cannot be voting for the wrong template.
    # A symbol no such site uses has nothing else to go on, so its ambiguous
    # sites decide it and the report says how many stood behind it.
    observed, ambiguous_observed = collections.defaultdict(list), collections.defaultdict(list)
    for rva, patterns_here in viable.items():
        for pattern in patterns_here:
            for symbol, (_, addresses) in resolutions[(rva, pattern.symbol)].items():
                if tg_is_payload(symbol):
                    continue
                bucket = observed if len(patterns_here) == 1 else ambiguous_observed
                bucket[symbol].append(addresses)
    for symbol, sightings in ambiguous_observed.items():
        observed.setdefault(symbol, sightings)
    allowed, new_pins = tg_shared_addresses(observed, ledger_names, pinned, thunks,
                                            resolved, refusals)

    def mismatch(rva, pattern):
        """The first shared slot this pattern cannot account for at this site."""
        for symbol, (offset, addresses) in sorted(resolutions[(rva, pattern.symbol)].items()):
            if not tg_is_payload(symbol) and not addresses & allowed.get(symbol, set()):
                return (f"shared-callee-mismatch: slot +{offset} for {symbol} reaches "
                        f"0x{min(addresses):08X}, not the address the other sites agree on")
        return None

    claimable, callees, chosen = [], {}, {}
    for rva in sorted(viable):
        survivors = [(pattern, mismatch(rva, pattern)) for pattern in viable[rva]]
        kept = [pattern for pattern, reason in survivors if reason is None]
        if not kept:
            refusals.append((rva, survivors[0][0].symbol, survivors[0][1]))
            continue
        chosen[rva] = kept[0]  # candidates arrive sorted: first symbol wins
        callees[rva] = resolutions[(rva, kept[0].symbol)]
        claimable.append(rva)

    # A refusal recorded against RVA 0 is about a symbol, not a site: it says a
    # shared callee cannot be pinned at all, and the sites it costs are refused
    # individually below.
    claimed_set = set(claimable)
    refused = {rva for rva, _, _ in refusals if rva and rva not in claimed_set}
    kinds = collections.Counter(reason.split(":")[0] for rva, _, reason in refusals
                                if rva in refused)
    print(f"{label}: {len(hits)} unclaimed site(s) matched a pattern; "
          f"{len(claimable)} claimable + {len(refused)} refused "
          + f"({', '.join(f'{count} {kind}' for kind, count in sorted(kinds.items())) or 'none'})")
    if len(claimable) + len(refused) != len(hits):
        raise FormatError(f"report accounts for {len(claimable) + len(refused)} of "
                          f"{len(hits)} matched site(s)")
    for rva, symbol, reason in refusals[:20]:
        if rva in refused or not rva:
            print(f"{label}: REFUSED 0x{rva:08X} {symbol[:70]}: {reason}", file=sys.stderr)
    return TgResolution(claimable, chosen, callees, allowed, new_pins, pinned,
                        resolved, thunks)


def cmd_gen_tgrid(args):
    specs = tg_specs(args.dims)
    entries = load_ghidra()
    blacklist = load_blacklist()
    patterns = tg_probe(specs)
    # Unlike the other engines here, this one hides its OWN rows from nothing:
    # a landed site is off the table for good. A dimension added later changes
    # which pattern explains a site, and re-selecting a landed one would rewrite
    # the committed TU that already claims it under a different instantiation.
    claimed, claimed_names, index = load_claims()
    boundaries = dump_boundaries()
    hits = tg_scan(patterns, scan_population(entries, boundaries), blacklist,
                   claimed, index, boundaries)

    resolution = tg_resolve(hits, TGRID_NOTE)
    claimable, chosen, callees = resolution.claimable, resolution.chosen, resolution.callees
    allowed, new_pins = resolution.allowed, resolution.new_pins
    pinned, resolved, thunks = resolution.pinned, resolution.resolved, resolution.thunks

    yields = collections.defaultdict(lambda: [0, 0])
    for rva in claimable:
        pattern = chosen[rva]
        yields[pattern.spec.dim][0] += 1
        yields[pattern.spec.dim][1] += pattern.size
    print("gen-tgrid: yield by dimension (whole grid, before batching):")
    for dim, (count, size) in sorted(yields.items(), key=lambda item: -item[1][1]):
        print(f"  {dim:>8}  {count:6d} site(s)  {size:8d} bytes")

    report = collections.Counter()
    grid_rows = collections.defaultdict(list)
    instance_sites = []
    for rva in claimable:
        pattern = chosen[rva]
        if pattern.mode == "a":
            grid_rows[pattern.spec.key].append(rva)
        else:
            instance_sites.append(rva)

    written = []
    for number, spec in specs:
        source_path = tg_source_path(number)
        source_rel = source_path.relative_to(ROOT).as_posix()
        rows, pins = [], []
        for rva in sorted(grid_rows.get(spec.key, ())):
            pattern = chosen[rva]
            rows.append(format_row(f"tg_{rva:08x}", rva, pattern.size, source_rel,
                                   f"{TGRID_NOTE};object-symbol={pattern.symbol}"))
            pins += tg_site_pins(rva, callees[rva], allowed, new_pins, pinned,
                                 resolved, None)
        # A grid TU's content is fixed by its spec, so rewriting one that already
        # carries rows is a no-op -- but only when this run has something to add.
        if not rows:
            continue
        written.append(tg_write_batch(source_path, tg_render(
            "gen-tgrid", spec.includes, tg_spec_body(spec), spec.flags), rows, pins,
            thunks, report))

    # Instance batches take fresh file numbers only: a landed TU is never
    # rewritten, so its rows keep naming the instantiation they were proved on.
    # A TU carries one `// cl:` line, so sites whose dimensions need different
    # flags cannot share one.
    by_flags = collections.defaultdict(list)
    for rva in sorted(instance_sites):
        by_flags[chosen[rva].spec.flags].append(rva)
    batches, number, held = {}, TGRID_INSTANCE_BASE, 0
    for flags, sites in sorted(by_flags.items()):
        while sites and len(batches) < args.batches:
            source_path = tg_source_path(number)
            number += 1
            if source_path.exists():
                continue
            batches[source_path.relative_to(ROOT).as_posix()] = (flags, sites[:args.limit])
            sites = sites[args.limit:]
        held += len(sites)
    if held:
        print(f"gen-tgrid: {held} further site(s) held for the next run "
              f"(--batches {args.batches})")

    for source_rel in sorted(batches):
        flags, sites = batches[source_rel]
        includes, body, rows, pins = [], [], [], []
        for rva in sites:
            pattern = chosen[rva]
            for include in pattern.spec.includes:
                if include not in includes:
                    includes.append(include)
            body += tg_instance_lines(pattern, rva)
            symbol = tg_instance_symbol(pattern, pattern.symbol, f"{rva:08x}")
            rows.append(format_row(symbol, rva, pattern.size, source_rel,
                                   f"{TGRID_NOTE};template={pattern.cell.key}"))
            pins += tg_site_pins(rva, callees[rva], allowed, new_pins, pinned,
                                 resolved, (pattern, symbol))
        written.append(tg_write_batch(ROOT / source_rel, tg_render(
            "gen-tgrid", sorted(includes), body, flags), rows, pins, thunks, report))

    new = sum(len(rows) for rows in written)
    print(f"gen-tgrid: {len(written)} batch(es) pending, {new} verified new row(s) "
          f"({sum(int(row.split(',')[3]) for rows in written for row in rows)} bytes), "
          f"{report['verify-failed']} verify-failed")
    if not new:
        print("gen-tgrid: 0 new — every claimable site is already in the ledger")


# --------------------------------------------------------------------------
# gen-tinst: container instantiations over the REAL element types
# --------------------------------------------------------------------------
#
# gen-tgrid claims what a SHAPE proves: a synthetic payload of some size and
# lifecycle, whose name never reaches the bytes. That is the right instrument
# for an anonymous body, and the wrong one here. ~35 KB of retail container
# members are already NAMED -- reverse/reloc_names.csv and reverse/symbols.csv
# carry their STLport-decorated names, element type and all -- and those names
# are evidence a shape comparison cannot produce. Every four-byte trivially
# assignable element type compiles `_M_fill_insert` to the same 282 bytes, so a
# masked scan over that family names nothing (see the resize family at
# 0x001DC360); the decorated name names it exactly.
#
# So gen-tinst runs the identification backwards from gen-tgrid: it reads the
# element type OUT of the name, instantiates the vendored STLport 4.5.3 template
# over that type, and checks each emitted body against the retail address its own
# name names. Nothing is placed by search, so there is no ambiguity to resolve.

TINST_NOTE = "gen-tinst"
TINST_REF = "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
TINST_INCDIRS = [f"{TINST_REF}/GameEngine/Include", f"{TINST_REF}/GameEngine/Source",
                 f"{TINST_REF}/GameEngineDevice/Include", f"{TINST_REF}/Libraries/Include",
                 f"{TINST_REF}/Libraries/Source", f"{TINST_REF}/Libraries/Source/WWVegas",
                 f"{TINST_REF}/Libraries/Source/WWVegas/WWLib",
                 f"{TINST_REF}/Libraries/Source/WWVegas/WWMath",
                 f"{TINST_REF}/Libraries/Source/WWVegas/WW3D2",
                 f"{TINST_REF}/Libraries/Source/WWVegas/WWDebug",
                 f"{TINST_REF}/Libraries/Source/WWVegas/WWSaveLoad"]
TINST_SHIMS = ["reference/shims/science", "reference/shims/iniexception",
               "reference/shims/ini_noinline", "reference/shims/stlp_nodealloc",
               "reference/shims/sweep"]
# Which allocator a retail body was compiled under is not knowable from its
# name, so both regimes are tried and only an exact byte match decides.
TINST_REGIMES = {"plain": "/DNDEBUG /MD /EHsc",
                 "node": "/DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /MD /EHsc"}
TINST_NS = {"vector": "_STL::vector", "list": "_STL::list",
            "deque": "_STL::deque", "slist": "_STL::slist"}
TINST_PRIM = {"C": "signed char", "D": "char", "E": "unsigned char", "F": "short",
              "G": "unsigned short", "H": "int", "I": "unsigned int", "J": "long",
              "K": "unsigned long", "M": "float", "N": "double", "X": "void",
              "_N": "bool", "_J": "__int64", "_K": "unsigned __int64"}
TINST_BUILTIN = {"_STL", "pair", "vector", "list", "deque", "slist", "const",
                 "unsigned", "int", "char", "float", "double", "bool", "void",
                 "short", "long", "signed"}
TINST_CONTAINER = re.compile(r"\?\$(vector|list|deque|slist)@")


def tinst_demangle(mangled):
    """C++ spelling for one mangled type, or None when this parser cannot.

    Refusing is the point: a guessed spelling would instantiate over the WRONG
    element type and, for the many size classes that compile identically, still
    land on a plausible body. Only shapes this understands exactly get emitted.
    """
    mangled = mangled.strip()
    if mangled in TINST_PRIM:
        return TINST_PRIM[mangled]
    for prefix, wrap in (("PA", "{} *"), ("PB", "const {} *"), ("AA", "{} &")):
        if mangled.startswith(prefix):
            inner = tinst_demangle(mangled[len(prefix):])
            return wrap.format(inner) if inner else None
    # W4Name@@ enum, VName@@ class, UName@@ struct; nested names read outward
    match = re.fullmatch(r"(?:W4|V|U|T)([A-Za-z_0-9]+(?:@[A-Za-z_0-9]+)*)@@", mangled)
    if match:
        return "::".join(reversed(match.group(1).split("@")))
    match = re.fullmatch(r"[VU]\?\$([A-Za-z_0-9]+)@(.*)@(_STL|rts)@@", mangled)
    if match:
        name, args, namespace = match.groups()
        spelled = tinst_arglist(args)
        return f"{namespace}::{name}<{', '.join(spelled)} >" if spelled else None
    return None


def tinst_arglist(mangled):
    """[C++ spellings] for a mangled template argument list, or None."""
    args, position = [], 0
    while position < len(mangled):
        rest = mangled[position:]
        if rest.startswith(("V?$", "U?$")):
            end = tinst_template_end(mangled, position)
            if end is None:
                return None
            piece = tinst_demangle(mangled[position:end])
            position = end
        else:
            match = re.match(r"(?:W4|V|U|T)[A-Za-z_0-9]+(?:@[A-Za-z_0-9]+)*@@"
                             r"|P[AB][A-Za-z_0-9]*(?:@[A-Za-z_0-9]+)*@@|PAX|_N|[CDEFGHIJKMNX]",
                             rest)
            if not match:
                return None
            piece = tinst_demangle(match.group(0))
            position += match.end()
        if piece is None:
            return None
        args.append(piece)
    return args or None


def tinst_template_end(mangled, start):
    """Index just past the `V?$name@...@ns@@` beginning at `start`, or None."""
    depth, position = 0, start
    while position < len(mangled):
        if mangled.startswith("?$", position):
            depth += 1
            position += 2
            continue
        match = re.match(r"@(?:_STL|rts)@@", mangled[position:])
        if match:
            depth -= 1
            position += match.end()
            if not depth:
                return position
            continue
        position += 1
    return None


def tinst_element(name):
    """(container, mangled element) for a one-parameter sequence container."""
    match = TINST_CONTAINER.search(name)
    if not match:
        return None, None
    rest = name[match.end():]
    cut = rest.find("V?$allocator@")
    return (match.group(1), rest[:cut]) if cut >= 0 else (match.group(1), None)


def tinst_resolve(read, rva):
    """Follow the 5-byte incremental-link `jmp rel32` stub to the real body.

    The linker gives every STL member an ILT entry and it is the ILT address the
    name tables record, so a name looked up raw lands on five bytes rather than
    on the function.
    """
    for _ in range(3):
        head = read(rva, 5)
        if len(head) != 5 or head[0] != 0xE9:
            return rva
        rva = (rva + 5 + int.from_bytes(head[1:5], "little", signed=True)) & 0xFFFFFFFF
    return rva


def tinst_named_population():
    """{decorated name: rva} for every STLport-decorated retail name on record."""
    named = {}
    def note(name, rva, size):
        if name not in named or size > named[name][1]:
            named[name] = (rva, size)
    for path, address, size in (("reverse/reloc_names.csv", "target_rva", "target_size"),
                                ("reverse/symbols.csv", "address", None)):
        with open(ROOT / path, newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                if "@_STL@@" not in row["name"]:
                    continue
                try:
                    note(row["name"], int(row[address], 16),
                         int(row[size]) if size else 0)
                except ValueError:
                    continue
    return named


def tinst_header_for(base):
    """The reference-tree header defining `base`, as an #include spelling."""
    if base in TINST_BUILTIN or not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", base):
        return None
    found = subprocess.run(["rg", "-l", rf"^\s*(class|struct)\s+{base}\b", "--glob", "*.h",
                            TINST_REF], cwd=ROOT, capture_output=True, text=True)
    best = None
    for path in found.stdout.split():
        for directory in TINST_INCDIRS:
            if not path.startswith(directory + "/"):
                continue
            spelling = path[len(directory) + 1:]
            # a header named after the type is its definition far more often
            rank = (0 if spelling.rsplit("/", 1)[-1].lower().startswith(base.lower()) else 1,
                    len(spelling))
            if best is None or rank < best[0]:
                best = (rank, spelling)
    return best[1] if best else None


def tinst_render(flags, headers, container, spelling, prerts):
    """One instantiation TU. `// cl:` and `// stlport` must stay in the first
    lines: build.py reads only the head of a source to decide both."""
    lines = ["// cl: " + flags + ("".join(" /I" + d for d in TINST_SHIMS + TINST_INCDIRS)
                                  if headers or prerts else ""),
             "// stlport",
             "// Generated by: python3 tools/gen_small.py gen-tinst",
             "// Do not edit by hand; regenerate instead.",
             "//",
             "// A retail body that IS this instantiation. The element type is read out",
             "// of the body's own STLport-decorated name, not out of its shape -- every",
             "// four-byte trivially assignable element compiles these members to the",
             "// same bytes, so the shape names nothing and the name names it exactly.",
             "//",
             f"// element: {spelling}   container: {container}", ""]
    if prerts:
        lines.append('#include "PreRTS.h"')
    lines += [f'#include "{header}"' for header in headers]
    lines += ["", "#include <cstring>", "",
              "// Retail reaches memmove through the import slot (`ff 15`); the pin",
              "// `_bfme_memmove_ptr` is already in reverse/symbols.csv at that slot.",
              'extern "C" void *(__cdecl *bfme_memmove_ptr)'
              "(void *, const void *, unsigned int);",
              "#define memmove (*bfme_memmove_ptr)",
              f"#include <{container}>",
              "#undef memmove", "",
              f"template class {TINST_NS[container]}<{spelling} >;"]
    return "\n".join(lines) + "\n"


def tinst_cells(read, named):
    """{(container, spelling): bytes at stake} for every unclaimed named body."""
    claimed = {int(row["target_rva"], 16) for row in B.load_all_function_rows()
               if "gen_asm" not in row["source"] and not row["source"].endswith(".asm")}
    dumps = {int(row["target_rva"], 16): int(row["target_size"])
             for row in B.load_all_function_rows()
             if "gen_asm" in row["source"] or row["source"].endswith(".asm")}
    stake = collections.Counter()
    for name, (rva, size) in named.items():
        body = tinst_resolve(read, rva)
        if body in claimed:
            continue
        container, element = tinst_element(name)
        if not container or element is None or "Gen_" in element:
            continue          # a Gen_* payload is gen-tgrid's, by construction
        spelling = tinst_demangle(element)
        if not spelling:
            continue
        stake[(container, spelling)] += dumps.get(body, size)
    return stake


def tinst_probe(read, named, cell, headers, claimed, taken):
    """[(row, size)] for the bodies one cell reproduces exactly, over both
    allocator regimes; the first regime that compiles AND matches wins.

    A body is skipped when its NAME is already in the ledger and, separately,
    when its ADDRESS is -- gen-tgrid reaches many of the same bodies first and
    lands them under a synthetic `tg_*` name, which leaves the address claimed
    while the decorated name is still free.
    """
    container, spelling = cell
    # Keyed on the cell, never on the output batch number: the probe object is
    # the expensive part of a run and the batch number shifts every time an
    # earlier cell lands, which would throw the whole compile cache away.
    key = re.sub(r"[^A-Za-z0-9]+", "_", f"{container}_{spelling}").strip("_")[:58]
    pinned = load_pin_addresses()
    for regime, flags in TINST_REGIMES.items():
        for prerts in ((True, False) if headers else (False,)):
            source = PENDING_DIR / f"tinstprobe_{key}_{regime}.cpp"
            text = tinst_render(flags, headers, container, spelling, prerts)
            if not source.exists() or source.read_text(encoding="utf-8") != text:
                source.write_text(text, encoding="utf-8")
            obj = B.obj_path(source)
            try:
                if not B.compile_is_current(source, obj):
                    B.compile_source(source, obj)
            except BaseException:      # compile_source signals failure with SystemExit
                continue
            hits, pins = [], set()
            for symbol, body, relocs in tg_object_bodies(obj):
                if symbol not in named or symbol in claimed:
                    continue
                rva = tinst_resolve(read, named[symbol][0])
                if rva in taken:
                    continue
                retail = read(rva, len(body))
                if len(retail) != len(body):
                    continue
                masked = {position for offset, _, _ in relocs
                          for position in range(offset, min(offset + 4, len(body)))}
                if any(body[i] != retail[i] for i in range(len(body)) if i not in masked):
                    continue
                hits.append((symbol, rva, len(body)))
                pins.update(tinst_callee_pins(rva, retail, relocs, pinned))
            if hits:
                return hits, text, regime, sorted(pins)
    return [], None, None, []


def tinst_callee_pins(rva, retail, relocs, pinned):
    """The symbols.csv lines a matched body needs, read out of the RETAIL bytes.

    Matching outside the relocation slots proves the code and says nothing about
    where the calls go, which is exactly how a body can be byte-identical and
    still be the wrong instantiation -- `deque<int>::_M_push_back_aux_v` differs
    from its neighbours only in which _M_reallocate_map it reaches. So each
    REL32 target is decoded from retail and pinned under the symbol the object
    relocates against, and the gate then proves the slot rather than masking it.

    A name that already answers to some address is left alone: appending a
    second address to it turns its slot into a wildcard for every other site.
    """
    out = set()
    for offset, rtype, symbol in relocs:
        if rtype != 0x0014 or offset + 4 > len(retail) or symbol in pinned:
            continue
        displacement = int.from_bytes(retail[offset:offset + 4], "little", signed=True)
        out.add(f"{symbol},0x{(rva + offset + 4 + displacement) & 0xFFFFFFFF:08X}")
    return out


def tinst_source_path(number):
    return GEN_DIR / f"tinst_{number:03d}.cpp"


def tinst_next_number(number):
    """The next free batch number. Landed batches are not contiguous once one
    has been retired, and walking past every existing file is what keeps a run
    from writing over a file whose rows are already live."""
    while tinst_source_path(number).exists():
        number += 1
    return number


def cmd_gen_tinst(args):
    read = exe_reader()
    named = tinst_named_population()
    stake = tinst_cells(read, named)
    order = sorted(stake, key=lambda cell: -stake[cell])
    if args.only:
        order = [c for c in order if args.only in c[1]]
    print(f"gen-tinst: {len(order)} element type(s) named in the retail tables, "
          f"{sum(stake[c] for c in order)} unclaimed byte(s) at stake")

    number = tinst_next_number(0)
    thunks, report = B.build_call_thunks(), collections.Counter()
    written, refused = [], collections.Counter()
    claimed = {row["name"] for row in B.load_all_function_rows()}
    taken = {int(row["target_rva"], 16) for row in B.load_all_function_rows()
             if "gen_asm" not in row["source"] and not row["source"].endswith(".asm")}
    for container, spelling in order[:args.batches]:
        headers, missing = [], []
        for base in dict.fromkeys(re.findall(r"[A-Za-z_][A-Za-z_0-9]*", spelling)):
            header = tinst_header_for(base)
            (headers.append(header) if header else
             missing.append(base) if base not in TINST_BUILTIN else None)
        if missing:
            refused[f"no reference header for {missing[0]}"] += 1
            continue
        hits, text, regime, pins = tinst_probe(read, named, (container, spelling),
                                               headers, claimed, taken)
        if not hits:
            refused["no member reproduces the retail bytes"] += 1
            continue
        source = tinst_source_path(number)
        rows = [f"{symbol},,0x{rva:08X},{size},"
                f"{source.relative_to(ROOT).as_posix()},matched,"
                f"{TINST_NOTE};element={spelling};regime={regime}"
                for symbol, rva, size in sorted(hits, key=lambda h: -h[2])]
        verified = tg_write_batch(source, text, rows, pins, thunks, report, TINST_NOTE)
        if verified:
            written.append(verified)
            number = tinst_next_number(number + 1)
        else:
            source.unlink(missing_ok=True)

    new = sum(len(rows) for rows in written)
    print(f"gen-tinst: {len(written)} batch(es) pending, {new} verified new row(s) "
          f"({sum(int(row.split(',')[3]) for rows in written for row in rows)} bytes), "
          f"{report['verify-failed']} verify-failed")
    for reason, count in refused.most_common():
        print(f"gen-tinst: {count} cell(s) refused: {reason}")
    if not new:
        print("gen-tinst: 0 new — every reproducible member is already in the ledger")


def tg_site_pins(rva, found, allowed, new_pins, pinned, resolved, instance,
                 label=TGRID_NOTE):
    """The symbols.csv lines one site needs.

    A payload-owned callee is this site's own class, so it is pinned under the
    per-site symbol the compiled object actually relocates against (`instance`
    supplies the renaming). A shared callee is pinned once, at the address every
    site agreed on, and only when nothing already answers for it -- appending a
    second address to a name that already has one turns its slot into a wildcard.
    """
    pins = []
    for symbol, (_, addresses) in sorted(found.items()):
        if not tg_is_payload(symbol):
            if symbol in new_pins:
                pins.append(format_pin(symbol, new_pins[symbol],
                                       f"{label} shared callee"))
            continue
        name = symbol if instance is None else tg_instance_symbol(
            instance[0], symbol, f"{rva:08x}")
        address = tg_pick(addresses, resolved)
        if instance is not None and name == instance[1]:
            continue  # a recursive call resolves through this site's own row
        if name in pinned and pinned[name] != {address}:
            raise FormatError(f"{name} is pinned at "
                              f"{', '.join(f'0x{a:08X}' for a in sorted(pinned[name]))} "
                              f"but site 0x{rva:08X} calls 0x{address:08X}")
        pins.append(format_pin(name, address, f"{label} payload member"))
    return pins


# --------------------------------------------------------------------------
# shape families
# --------------------------------------------------------------------------
#
# Every engine above knows one recipe. This is the workbench for finding the
# next one: bodies are grouped by their capstone SKELETON -- opcodes and modrm
# bytes kept, displacement and immediate VALUES zeroed, encoded lengths kept --
# which is exactly the equivalence "one C++ template with per-instance constants
# compiles to all of these". A skeleton a matched C++ row already carries is a
# TWIN: that row's source is a worked example of the C++ behind those bytes. A
# skeleton only unclaimed bodies carry is a FAMILY: crack it once, land every
# member. One member is a singleton and belongs to the ordinary queue.

FAMILY_MIN, FAMILY_MAX = 17, 2048
FAMILY_NOTE = "gen-shim;family"
FAMILY_SOURCES = (".cpp", ".cxx", ".cc", ".c")

_DISASSEMBLER = None


def disassembler():
    """One detail-mode 32-bit capstone, built on first use.

    Imported lazily: capstone is needed by this workbench alone, and the landing
    and thunk engines have to keep working on a machine without it.
    """
    global _DISASSEMBLER
    if _DISASSEMBLER is None:
        import capstone
        _DISASSEMBLER = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        _DISASSEMBLER.detail = True
    return _DISASSEMBLER


def shape(body):
    """`body`'s instruction skeleton, or None when it is not whole code.

    Zeroing the operand VALUES while keeping their encoded widths is what makes
    two bodies comparable without making them falsely equal: `mov eax,[ecx+8]`
    and `mov eax,[ecx+0x10]` share a skeleton and one template spells both, but
    `[ecx+8]` and `[ecx+0x100]` do not -- the second encodes four displacement
    bytes, and a template that treats them as one shape would emit the wrong
    length. A body capstone cannot decode to its last byte has no skeleton at
    all: it is data, or it is not a whole function, and no template can claim it.
    """
    out, decoded = bytearray(), 0
    for insn in disassembler().disasm(bytes(body), 0):
        raw = bytearray(insn.bytes)
        if insn.disp_size:
            raw[insn.disp_offset:insn.disp_offset + insn.disp_size] = bytes(insn.disp_size)
        if insn.imm_size:
            raw[insn.imm_offset:insn.imm_offset + insn.imm_size] = bytes(insn.imm_size)
        out += raw
        decoded += insn.size
    return bytes(out) if decoded == len(body) and decoded else None


def family_id(skeleton):
    """`f20_9c1a3b` — a family's name, addressed by its own content.

    Deriving the id from the skeleton instead of from a rank keeps it stable
    while the ledger moves under it: a family cracked today is the same id
    tomorrow, when half the census around it has been claimed and every rank has
    shifted.
    """
    return f"f{len(skeleton)}_{hashlib.sha1(skeleton).hexdigest()[:6]}"


def census_bodies(entries, read, blacklist, claimed, index):
    """[(rva, size, ghidra name, skeleton)] — unclaimed inventory bodies in the
    family window, skipping funclets (they unlock with their parents, not here)."""
    out = []
    for rva, size, name in entries:
        if not FAMILY_MIN <= size <= FAMILY_MAX or rva in blacklist:
            continue
        if name.startswith(FUNCLET_PREFIXES) or rva in claimed:
            continue
        if find_overlap(index, rva, size) is not None:
            continue
        skeleton = shape(read(rva, size))
        if skeleton is not None:
            out.append((rva, size, name, skeleton))
    return out


def census_twins(read):
    """{skeleton: [(name, source, rva)]} for matched rows built from C++.

    A matched row is a statement that this exact byte string came out of a
    compiler over that source file, so a skeleton it shares with an unclaimed
    body is a cheat sheet: the C++ is on disk, and only the constants differ.
    """
    twins = collections.defaultdict(list)
    for row in B.load_all_function_rows():
        if row["status"] != "matched" or not row["source"].endswith(FAMILY_SOURCES):
            continue
        size = int(row["target_size"])
        if not FAMILY_MIN <= size <= FAMILY_MAX:
            continue
        rva = int(row["target_rva"], 16)
        skeleton = shape(read(rva, size))
        if skeleton is not None:
            twins[skeleton].append((row["name"], row["source"], rva))
    return twins


Census = collections.namedtuple("Census", "id skeleton size members bytes tier twins")


def census(entries=None, read=None):
    """[Census] for every unclaimed skeleton, ranked by unclaimed bytes."""
    entries = load_ghidra() if entries is None else entries
    read = exe_reader() if read is None else read
    claimed, _, index = load_claims(skip_dumps=True)
    bodies = census_bodies(entries, read, load_blacklist(), claimed, index)
    twins = census_twins(read)
    groups = collections.defaultdict(list)
    for rva, size, name, skeleton in bodies:
        groups[skeleton].append((rva, size, name))
    out = []
    for skeleton, members in groups.items():
        tier = ("twin" if skeleton in twins
                else "family" if len(members) > 1 else "singleton")
        out.append(Census(family_id(skeleton), skeleton, len(skeleton), sorted(members),
                          sum(size for _, size, _ in members), tier,
                          sorted(twins.get(skeleton, ()))))
    out.sort(key=lambda c: (-c.bytes, c.id))
    return out


def census_find(ranked, wanted):
    """The census entry `wanted` names, by family id or by any member's RVA."""
    for entry in ranked:
        if entry.id == wanted:
            return entry
    address = int(wanted, 16 if wanted.lower().startswith("0x") else 10)
    for entry in ranked:
        if any(rva == address for rva, _, _ in entry.members):
            return entry
    return None


def census_show(entry, read):
    """One family in full: members, twins, and the exemplar's disassembly."""
    print(f"family {entry.id}: {entry.tier} tier, {entry.size}B x "
          f"{len(entry.members)} member(s) = {entry.bytes} bytes")
    for name, source, rva in entry.twins[:6]:
        print(f"  twin  0x{rva:08X}  {source}  {name}")
    if len(entry.twins) > 6:
        print(f"  twin  ... {len(entry.twins) - 6} more")
    print("  members " + " ".join(f"0x{rva:08X}" for rva, _, _ in entry.members[:24])
          + (" ..." if len(entry.members) > 24 else ""))
    rva = entry.members[0][0]
    print(f"  exemplar 0x{rva:08X}:")
    for insn in disassembler().disasm(read(rva, entry.size), rva):
        print(f"    {insn.address:08X}  {insn.bytes.hex(' '):<24}  "
              f"{insn.mnemonic} {insn.op_str}")


def cmd_family_census(args):
    if args.show:
        read = exe_reader()
        ranked = census(read=read)
        for wanted in args.show.split(","):
            entry = census_find(ranked, wanted.strip())
            if entry is None:
                print(f"family-census: {wanted.strip()} names no unclaimed family "
                      "(every body of that shape is claimed)", file=sys.stderr)
            else:
                census_show(entry, read)
        return
    ranked = census()
    if args.json:
        PENDING_DIR.mkdir(parents=True, exist_ok=True)
        Path(args.json).write_text(json.dumps(
            [{"id": e.id, "size": e.size, "tier": e.tier, "bytes": e.bytes,
              "members": [[rva, name] for rva, _, name in e.members],
              "twins": [[name, source, rva] for name, source, rva in e.twins]}
             for e in ranked], indent=1) + "\n", encoding="utf-8")
        print(f"family-census: wrote {args.json}")
    tiers = collections.Counter()
    for entry in ranked:
        tiers[entry.tier] += len(entry.members)
        tiers[entry.tier + " bytes"] += entry.bytes
    print(f"family-census: {sum(len(e.members) for e in ranked)} unclaimed body(s) / "
          f"{sum(e.bytes for e in ranked)} bytes in {FAMILY_MIN}-{FAMILY_MAX}B, "
          f"{len(ranked)} distinct shape(s)")
    for tier in ("twin", "family", "singleton"):
        print(f"  {tier:>9}  {tiers[tier]:6d} fns  {tiers[tier + ' bytes']:9d} bytes")
    crackable = [e for e in ranked if e.tier != "singleton"]
    print(f"family-census: {len(crackable)} crack target(s), "
          f"{sum(e.bytes for e in crackable)} bytes; top {min(args.top, len(crackable))}:")
    print(f"  {'id':>14} {'tier':>6} {'size':>5} {'fns':>5} {'bytes':>7}  "
          f"{'exemplar':>10}  twin / ghidra name")
    for entry in crackable[:args.top]:
        witness = (f"{entry.twins[0][0][:44]} ({entry.twins[0][1]})" if entry.twins
                   else entry.members[0][2])
        print(f"  {entry.id:>14} {entry.tier:>6} {entry.size:5d} {len(entry.members):5d} "
              f"{entry.bytes:7d}  0x{entry.members[0][0]:08X}  {witness}")
    cumulative = 0
    for count in (10, 25, 50, 100, 250):
        cumulative = sum(e.bytes for e in crackable[:count])
        print(f"family-census: top {count:4d} families cumulative {cumulative} bytes")


# --------------------------------------------------------------------------
# family library
# --------------------------------------------------------------------------
#
# A cracked family is a recipe: the C++ whose compiled body IS that shape, the
# flags it needs, and the payload types its per-site instantiations are written
# over. The recipes below are the durable output of `family-spike` -- each one
# was proven by compiling it and comparing it against a live unclaimed exemplar
# on every byte outside its relocation slots -- and `family-emit` lands every
# member of every recipe here.
#
# The recipe is a TgSpec because a family and a grid cell are the same object:
# an instantiation, its flags, and its synthetic payloads. `dim` is the census
# family id the spike proved it against, which is what a row's notes cite.

FAMILY_LABEL = "family-emit"
FAMILY_STEM = "fam"

# The flag set every matched game TU carries (see any source's `// cl:` line):
# the DLL CRT is what makes memmove a call through the import table, and NDEBUG
# is what strips STLport's own checks. A recipe compiled without them is a
# different program, which is how the /MT grid missed these shapes.
FAMILY_RETAIL = ("/DNDEBUG", "/DWIN32", "/D_WINDOWS", "/MD", "/EHsc",
                 "/D_STLP_USE_STATIC_LIB")
# f265's vector bodies carry no assertion, so they were proven without NDEBUG;
# the landed TUs say so and are never rewritten.
FAMILY_MD = ("/EHsc", "/MD", "/D_STLP_USE_STATIC_LIB")


def fam_pod(size):
    return TgPayload(f"m{size}pod", size, "pod", None)


def fam_cd(size):
    return TgPayload(f"m{size}cd", size, "cd", None)


FAM_KEY = TgPayload("mk4", 4, "key", None)
FAM_CMP = TgPayload("mc4", 4, "cmp", None)
FAM_UINT = TgPayload("uint", 4, "raw", "unsigned int")
FAM_USHORT = TgPayload("ushort", 2, "raw", "unsigned short")
FAM_FLOAT = TgPayload("float", 4, "raw", "float")
FAM_UCHAR = TgPayload("uchar", 1, "raw", "unsigned char")

FAMILY_LIBRARY = [
    # Retail links the DLL CRT, so its memmove is a six-byte call through the
    # import table where a /MT build emits a five-byte direct call -- one byte
    # per memmove, which is why the whole memmove-carrying half of the container
    # library missed the /MT grid. /D_STLP_USE_STATIC_LIB keeps STLport's own
    # classes direct-called under _DLL, which is how retail has them.
    TgSpec("f265_b7a8aa", "vecmd", ("vector",),
           [tg_vector_cell(fam_pod(4))], FAMILY_MD),
    # The twins name this one exactly: map<AsciiString, list<AsciiString> > and
    # map<AsciiString, HotKey>, i.e. a four-byte class key with an extern
    # operator< over values whose copy is a call.
    # A tree body's bytes are fixed by its node width and by whether the value's
    # copy is a call, so the value sizes are enumerated rather than guessed: the
    # retail `_M_insert` at 0x8E9C0 allocates 0x38 per node, which is a value
    # this wide and nothing else.
    TgSpec("f629_f3736f", "treemd", ("map",),
           [tg_tree_cell(FAM_CMP, value) for value in
            [fam_cd(s) for s in (4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 48)]
            + [fam_pod(s) for s in (4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 48)]],
           FAMILY_RETAIL),
    TgSpec("listmd", "listmd", ("list",),
           [tg_list_cell(p) for p in (fam_pod(4), fam_pod(8), fam_pod(12),
                                      fam_cd(4), fam_cd(8), fam_cd(12))], FAMILY_RETAIL),
    TgSpec("setmd", "setmd", ("set",),
           [tg_set_cell(p) for p in
            [FAM_CMP, FAM_KEY]
            + [fam_cd(s) for s in (8, 12, 16, 20, 24, 32, 40)]
            + [fam_pod(s) for s in (4, 8, 12, 16, 20, 24, 32, 40)]],
           FAMILY_RETAIL),
    TgSpec("helpmd", "helpmd", ("memory", "utility"),
           [tg_uninit_cell(p) for p in (fam_cd(4), fam_cd(8), fam_cd(12), fam_cd(16))]
           + [tg_construct_pair_cell(FAM_CMP, v) for v in (fam_cd(8), fam_cd(12))],
           FAMILY_RETAIL),
    # Census leaders name their type args in the twin symbols: _Rb_tree@IU (uint
    # key), @GU pair GE (ushort->uchar), PBVThingTemplate (const-ptr key),
    # NameKeyType->float, ??$find@H (int key). All inline less<K> over builtin
    # keys -- the FAM_CMP extern-compare cells can never emit those bodies.
    # Pointer KEYS are omitted: `const %(p0)s` puts const on the pointee for a
    # raw `void *` spelling and _Rb_tree rejects the pair. Pointer VALUES are
    # fine. The one pointer-key census leader (f176, ThingTemplate*) is parked.
    TgSpec("treeraw", "treeraw", ("map",),
           [tg_tree_cell(k, v)
            for k in (TG_INT, FAM_UINT, FAM_USHORT)
            for v in (TG_PTR, TG_INT, FAM_FLOAT, FAM_UCHAR,
                      fam_pod(8), fam_pod(12), fam_cd(4), fam_cd(8))],
           FAMILY_RETAIL),
    TgSpec("hashraw", "hashraw", ("hash_map",),
           [tg_hash_cell(k, v)
            for k in (TG_INT, FAM_UINT)
            for v in (TG_PTR, TG_INT, fam_pod(8), fam_pod(12), fam_cd(4), fam_cd(8))],
           FAMILY_RETAIL),
]


def family_specs(only=None):
    """[(index, TgSpec)] for the recipes `only` names, or all of them."""
    wanted = None if only in (None, "all") else set(only.split(","))
    if wanted is not None:
        unknown = wanted - {spec.dim for spec in FAMILY_LIBRARY}
        if unknown:
            raise SystemExit(f"gen_small: no recipe for {sorted(unknown)}; known: "
                             f"{sorted(spec.dim for spec in FAMILY_LIBRARY)}")
    keys = collections.Counter(cell.key for spec in
                               [s for s in FAMILY_LIBRARY] + TGRID_SPECS
                               for cell in spec.cells)
    duplicated = sorted(key for key, count in keys.items() if count > 1)
    if duplicated:
        raise FormatError(f"cell(s) {duplicated} appear in more than one translation "
                          "unit; a landed TU's content must be fixed by its own spec")
    return [(index, spec) for index, spec in enumerate(FAMILY_LIBRARY)
            if wanted is None or spec.dim in wanted]


def family_prove(spec, exemplar):
    """(the pattern that IS this family, [(pattern, first bad offset, count)]).

    The body is FOUND, not named: every body the recipe emits at the exemplar's
    size is compared against it outside the relocation slots, and the one that
    matches is the family. Naming it instead would let a recipe whose mangled
    symbol I spelled wrong claim a different body and still look green.
    """
    patterns = tg_probe([(0, spec)])
    near = []
    for symbol in sorted(patterns):
        pattern = patterns[symbol]
        if pattern.size != len(exemplar):
            continue
        bad = [offset for offset in tg_fixed_offsets(pattern)
               if pattern.body[offset] != exemplar[offset]]
        if not bad:
            return pattern, []
        near.append((pattern, bad[0], len(bad)))
    return None, sorted(near, key=lambda item: item[2])


def family_explains(patterns, entry, read):
    """The recipe body that reproduces this family's exemplar, or None."""
    exemplar = read(entry.members[0][0], entry.size)
    for symbol in sorted(patterns):
        pattern = patterns[symbol]
        if pattern.size == entry.size and all(
                pattern.body[offset] == exemplar[offset]
                for offset in tg_fixed_offsets(pattern)):
            return pattern
    return None


def cmd_family_recipe(args):
    """Every census family one recipe explains.

    The targeted spike asks "does this recipe crack the family I aimed it at";
    this asks the same question of the whole census at once, which is the honest
    measure of a recipe: an instantiation emits dozens of bodies, and the ones it
    happens to explain are worth exactly as much as the one it was written for.
    """
    read = exe_reader()
    ranked = census(read=read)
    specs = family_specs(args.recipe)
    for _, spec in specs:
        patterns = tg_probe([(0, spec)])
        cracked = [(entry, pattern) for entry, pattern in
                   ((entry, family_explains(patterns, entry, read)) for entry in ranked)
                   if pattern is not None]
        members = sum(len(entry.members) for entry, _ in cracked)
        print(f"family-spike: recipe {spec.dim} explains {len(cracked)} census "
              f"family(s), {members} member(s), "
              f"{sum(entry.bytes for entry, _ in cracked)} bytes")
        for entry, pattern in cracked[:args.top]:
            print(f"  {entry.id:>14} {entry.tier:>6} {entry.size:5d}B x{len(entry.members):4d} "
                  f"{entry.bytes:7d}B  {pattern.symbol[:64]}")


def cmd_family_spike(args):
    read = exe_reader()
    entry = census_find(census(read=read), args.id)
    if entry is None:
        raise SystemExit(f"gen_small: {args.id} names no unclaimed family — either it is "
                         "already claimed or the id is stale; rerun family-census")
    census_show(entry, read)
    spec = next((s for s in FAMILY_LIBRARY if s.dim == entry.id), None)
    if spec is None:
        raise SystemExit(f"family-spike: {entry.id} has no recipe in FAMILY_LIBRARY — "
                         "the spike is the C++; write it there and rerun")
    exemplar = read(entry.members[0][0], entry.size)
    pattern, near = family_prove(spec, exemplar)
    if pattern is None:
        print(f"family-spike: {entry.id} FAIL — no body of the recipe reproduces the "
              f"exemplar ({len(near)} candidate(s) at {entry.size}B)", file=sys.stderr)
        for candidate, offset, count in near[:5]:
            print(f"  {candidate.symbol[:78]}\n    {count} byte(s) differ, first at "
                  f"+{offset}: recipe {candidate.body[offset]:02x} != retail "
                  f"{exemplar[offset]:02x}", file=sys.stderr)
        raise SystemExit(f"family-spike: {entry.id} is not cracked")
    print(f"family-spike: {entry.id} PASS — {pattern.symbol}")
    print(f"  {pattern.size}B, mode {pattern.mode}, {len(pattern.relocs)} slot(s); "
          f"{len(entry.members)} member(s) / {entry.bytes} bytes to land")
    for offset, rtype, symbol in sorted(pattern.relocs):
        kind = "DIR32 (copied from retail)" if rtype == 0x0006 else "REL32 (pinned)"
        owner = "per-site" if tg_is_payload(symbol) else "shared"
        print(f"  +{offset:<4} {kind:<26} {owner:<8} {symbol[:60]}")


def family_source_path(number):
    return GEN_DIR / f"{FAMILY_STEM}_{number:03d}.cpp"


def cmd_family_emit(args):
    specs = family_specs(args.only)
    entries = load_ghidra()
    patterns = tg_probe(specs)
    # Like the grid: a landed site is off the table for good, so this hides
    # nothing from itself and a rerun over a landed batch reports 0 new.
    claimed, claimed_names, index = load_claims()
    boundaries = dump_boundaries()
    hits = tg_scan(patterns, scan_population(entries, boundaries), load_blacklist(),
                   claimed, index, boundaries)
    resolution = tg_resolve(hits, FAMILY_LABEL)

    yields = collections.defaultdict(lambda: [0, 0])
    for rva in resolution.claimable:
        pattern = resolution.chosen[rva]
        yields[pattern.spec.dim][0] += 1
        yields[pattern.spec.dim][1] += pattern.size
    print(f"{FAMILY_LABEL}: yield by family (before batching):")
    for dim, (count, size) in sorted(yields.items(), key=lambda item: -item[1][1]):
        print(f"  {dim:>14}  {count:6d} site(s)  {size:8d} bytes")

    # Fresh file numbers only, and one `// cl:` line per TU, so recipes needing
    # different flags never share one.
    by_flags = collections.defaultdict(list)
    for rva in sorted(resolution.claimable):
        by_flags[resolution.chosen[rva].spec.flags].append(rva)
    batches, number, held = {}, 0, 0
    for flags, sites in sorted(by_flags.items()):
        while sites and len(batches) < args.batches:
            source_path = family_source_path(number)
            number += 1
            if source_path.exists():
                continue
            batches[source_path.relative_to(ROOT).as_posix()] = (flags, sites[:args.limit])
            sites = sites[args.limit:]
        held += len(sites)
    if held:
        print(f"{FAMILY_LABEL}: {held} further site(s) held for the next run "
              f"(--batches {args.batches})")

    report, written = collections.Counter(), []
    for source_rel in sorted(batches):
        flags, sites = batches[source_rel]
        includes, body, rows, pins = [], [], [], []
        for rva in sites:
            pattern = resolution.chosen[rva]
            for include in pattern.spec.includes:
                if include not in includes:
                    includes.append(include)
            body += tg_instance_lines(pattern, rva)
            symbol = tg_instance_symbol(pattern, pattern.symbol, f"{rva:08x}")
            name = f"Gen_{pattern.spec.dim}_{rva:08x}"
            existing = claimed_names.get(name)
            if existing is not None and existing != rva:
                raise FormatError(f"{name} already claims 0x{existing:08X} in the ledger")
            rows.append(format_row(name, rva, pattern.size, source_rel,
                                   f"{FAMILY_NOTE}={pattern.spec.dim};"
                                   f"object-symbol={symbol}"))
            # `None` for the site's own symbol: a family row is named for its
            # family, not for the instantiation, so nothing resolves through the
            # row name and every payload-owned callee needs its own pin --
            # including the recursive one a grid row would have answered itself.
            pins += tg_site_pins(rva, resolution.callees[rva], resolution.allowed,
                                 resolution.new_pins, resolution.pinned,
                                 resolution.resolved, (pattern, None), FAMILY_LABEL)
        written.append(tg_write_batch(ROOT / source_rel, tg_render(
            f"family-emit --only {args.only}", sorted(includes), body, flags),
            rows, pins, resolution.thunks, report, FAMILY_LABEL))

    new = sum(len(rows) for rows in written)
    print(f"{FAMILY_LABEL}: {len(written)} batch(es) pending, {new} verified new row(s) "
          f"({sum(int(row.split(',')[3]) for rows in written for row in rows)} bytes), "
          f"{report['verify-failed']} verify-failed")
    if not new:
        print(f"{FAMILY_LABEL}: 0 new — every claimable member is already in the ledger")


# --------------------------------------------------------------------------
# landing
# --------------------------------------------------------------------------

def overlap_index(ledger_rows):
    """(starts, ranges, widest) for bounded overlap lookups against matched rows."""
    ranges = sorted((r["rva"], r["rva"] + r["size"], r["name"])
                    for r in ledger_rows if r["status"] == "matched")
    return [r[0] for r in ranges], ranges, max((r[1] - r[0] for r in ranges), default=0)


def find_overlap(index, rva, size, skip=None):
    starts, ranges, widest = index
    lo = bisect.bisect_left(starts, rva - widest)
    hi = bisect.bisect_left(starts, rva + size)
    for start, end, name in ranges[lo:hi]:
        if start < rva + size and rva < end and name != skip:
            return name, start, end
    return None


def validate_rows(rows, ledger_rows):
    """Split generated rows into (to_append, already_landed, to_retract), refusing
    anything that would double-claim. Mirrors add_match.py's per-row checks, run once
    over the whole batch instead of once per row.

    A gen-dump row over the EXACT same range is not a double claim: a dump is
    retail's own bytes under a synthetic name, holding a boundary until a real body
    arrives. That body supersedes it, and land_batch retracts and tombstones the dump
    in the same transaction. Any other extent means the boundary itself is in dispute
    — a real conflict, which still raises. Read the note, not the directory: 349
    dumps live in Code/gen_small/, and the path check refused every one of them.
    """
    by_name = {}
    for row in ledger_rows:
        by_name.setdefault(row["name"], []).append(row)
    by_rva = {row["rva"]: row for row in ledger_rows}
    index = overlap_index(ledger_rows)

    to_append, landed, to_retract = [], 0, []
    seen_names, seen_rvas = set(), set()
    for row in rows:
        name, _, target_rva, target_size, source, status, _ = row.split(",")
        rva, size = int(target_rva, 16), int(target_size)
        if name in seen_names or rva in seen_rvas:
            raise FormatError(f"batch claims {name} / 0x{rva:08X} twice")
        seen_names.add(name)
        seen_rvas.add(rva)

        claims = by_name.get(name, [])
        if claims:
            if len(claims) == 1 and claims[0]["rva"] == rva and claims[0]["source"] == source:
                landed += 1
                continue
            where = ", ".join(f"0x{c['rva']:08X} ({c['source']}, {c['status']})" for c in claims)
            raise FormatError(f"{name} is already in the ledger at {where}")
        owner = by_rva.get(rva)
        superseded = None
        if owner is not None:
            if B.is_scaffold_row(owner) and owner["size"] == size:
                superseded = owner
            else:
                raise FormatError(f"{name} [0x{rva:08X}, 0x{rva + size:08X}): target_rva is "
                                  f"already claimed by {owner['name']} [0x{owner['rva']:08X}, "
                                  f"0x{owner['rva'] + owner['size']:08X}) ({owner['source']}, "
                                  f"{owner['status']}, line {owner['line']})")
        hit = find_overlap(index, rva, size,
                           skip=superseded["name"] if superseded is not None else None)
        if hit is not None:
            raise FormatError(f"{name} [0x{rva:08X}, 0x{rva + size:08X}) overlaps matched row "
                              f"{hit[0]} [0x{hit[1]:08X}, 0x{hit[2]:08X})")
        if superseded is not None:
            to_retract.append((superseded, name, source))
        to_append.append(row)
    return to_append, landed, to_retract


def retract_dump_rows(functions_raw, to_retract):
    """Drop each superseded gen-dump row and tombstone it, in one rewrite.

    The tombstone is not bookkeeping: functions.csv merges with git's union
    driver, which cannot express a deletion, so without a row in
    deleted_rows.csv the next rebase from a branch that forked earlier silently
    puts the dump back on top of the real body. Drop by CONTENT through
    ledger_io — the ledger mixes \\r\\r\\n, \\r\\n and bare \\n terminators, and
    every rewrite that split on one of them has lost or duplicated rows.
    """
    keys = {(owner["name"], f"0x{owner['rva']:08X}") for owner, _, _ in to_retract}
    kept, dropped = ledger_io.rewrite(
        functions_raw, lambda f: len(f) < 3 or (f[0], f[2]) not in keys)
    if dropped != len(keys):
        raise SystemExit(f"land: {len(keys)} dump row(s) to retract but {dropped} matched in "
                         "functions.csv — refusing a partial retraction; reconcile by hand")
    B.FUNCTIONS.write_bytes(kept)
    entries = []
    for owner, name, source in to_retract:
        entries.append((
            owner["name"], owner["rva"],
            f"gen-dump placeholder superseded by the real identity of these bytes: {name}, "
            f"byte-verified from {source} over the same {owner['size']}-byte range. The "
            f"{owner['source']} dump reproduces those bytes but carries no identity."))
        print(f"land: superseded dump row {owner['name']} @ 0x{owner['rva']:08X}/"
              f"{owner['size']}B ({owner['source']}) with {name} ({source}) — "
              "retracted and tombstoned")
    write_tombstones(entries)


def write_tombstones(entries):
    """Append (name, rva, reason) rows to reverse/deleted_rows.csv.

    The one place a deletion gets recorded. Every writer that drops a row goes
    through here, gen_uw's rewrite included: functions.csv union-merges, so a row
    removed without a tombstone is put straight back by the next rebase from a
    branch that forked before the removal, and the reason column is the only
    place the next reader learns why it went.
    """
    lines = []
    for name, rva, reason in entries:
        buf = io.StringIO()
        csv.writer(buf, lineterminator="\n").writerow([name, f"0x{rva:08X}", reason])
        lines.append(buf.getvalue())
    with DELETED.open("ab") as handle:
        handle.write("".join(lines).encode("utf-8"))


# land_wave reaches for this as G.line_terminator, and check_csv now refuses the
# commit that mixes symbols.csv in the first place; all three have to be asking
# ledger_io the one question, or the scan/land drift this file already documents
# repeats itself one layer down.
line_terminator = ledger_io.uniform_terminator


def run(command, label):
    print(f"land: {label}")
    return subprocess.run(command, cwd=ROOT).returncode


def git(*args, check=False):
    return subprocess.run(["git", "-C", str(ROOT), *args], check=check,
                          stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


def cmd_land(args):
    source_rel = Path(args.source).as_posix().lstrip("./")
    pending_path = PENDING_DIR / (Path(source_rel).stem + ".json")
    if not pending_path.exists():
        raise SystemExit(f"gen_small: no pending batch at {pending_path.relative_to(ROOT)} — "
                         "run the matching `gen_small.py gen-*` command first")
    batch = json.loads(pending_path.read_text(encoding="utf-8"))
    if batch["source"] != source_rel:
        raise SystemExit(f"gen_small: {pending_path.name} describes {batch['source']}, "
                         f"not {source_rel}")
    sources = batch.get("sources", [source_rel])
    source_paths = [ROOT / source for source in sources]
    missing = [source for source, path in zip(sources, source_paths) if not path.exists()]
    if missing:
        raise SystemExit(f"gen_small: generated source(s) missing: {', '.join(missing)}")
    land_batch(batch["rows"], batch["pins"], sources,
               stage=(sources, source_paths, pending_path))


def cmd_land_funclets(args):
    """Land one funclet batch. Its rows point at parent sources that are already
    tracked, so unlike a generated batch there is no .cpp to stage — the whole
    transaction is rows, and a failed gate reverts the ledger and nothing else."""
    pending_path = funclet_paths(args.batch)
    if not pending_path.exists():
        raise SystemExit(f"gen_small: no pending batch at {pending_path.relative_to(ROOT)} — "
                         "run `gen_small.py sweep-funclets` first")
    batch = json.loads(pending_path.read_text(encoding="utf-8"))
    land_batch(batch["rows"], batch["pins"], batch["sources"])


def land_batch(rows, pins, selectors, stage=None):
    """Append `rows` and `pins`, then prove them with ONE ./build.sh over
    `selectors`; anything short of a green gate reverts every file touched.

    `stage` is (source_rel, source_path, pending_path) for a batch that also
    brings its own generated .cpp: check_csv rejects a row whose source is not
    in git, so the file has to be staged before it can be proved, and un-staged
    again if it is not.
    """
    # One exclusive lock across validate -> append -> verify, the same lock
    # add_match.py takes, so a concurrent single-row append cannot interleave and
    # a revert cannot clobber a row somebody else landed meanwhile.
    lock_handle = LOCK_FILE.open("a")
    lock(lock_handle, exclusive=True,
         wait_notice="land: waiting for ledger lock (another append is running)...")

    functions_raw = B.FUNCTIONS.read_bytes()
    if b"\r\n" not in functions_raw[:200]:
        raise SystemExit("functions.csv has lost its CRLF line endings — restore it from git")
    if not functions_raw.endswith(b"\n"):
        raise SystemExit("functions.csv does not end with a newline (truncated last row?)")
    symbols_raw = B.SYMBOLS.read_bytes()
    symbols_eol = line_terminator(symbols_raw, "symbols.csv")
    deleted_raw = DELETED.read_bytes()

    to_append, landed, to_retract = validate_rows(rows, parse_ledger(functions_raw))
    pinned = load_pins()
    new_pins = []
    for pin in pins:
        name, address = pin.split(",")[0], int(pin.split(",")[1], 16)
        if pinned.get(name) == address:
            continue
        if name in pinned:
            raise FormatError(f"{name} is pinned at 0x{pinned[name]:08X}, batch wants "
                              f"0x{address:08X}")
        new_pins.append(pin)

    if not to_append and not new_pins:
        print(f"land: 0 new rows, 0 new pins ({landed} already landed) — nothing to verify")
        return

    if to_retract:
        retract_dump_rows(functions_raw, to_retract)
    with B.FUNCTIONS.open("ab") as handle:
        handle.write(b"".join(row.encode("utf-8") + b"\r\n" for row in to_append))
    if new_pins:
        with B.SYMBOLS.open("ab") as handle:
            handle.write(b"".join(pin.encode("utf-8") + symbols_eol for pin in new_pins))
    # check_csv rejects a row whose source is not in git — such a row pushes fine
    # here and breaks every other clone — so the batch must be staged before it can
    # be proved. It is this commit unit's own file: a specific path, never `add .`.
    staged = False
    staged_sources = []
    if stage is not None:
        source_rels, source_paths, pending_path = stage
        if isinstance(source_rels, str):
            source_rels, source_paths = [source_rels], [source_paths]
        for source_rel, source_path in zip(source_rels, source_paths):
            if git("ls-files", "--error-unmatch", "--", source_rel).returncode != 0:
                git("add", "--", source_rel, check=True)
                staged_sources.append((source_rel, source_path))
    print(f"land: appended {len(to_append)} row(s) and {len(new_pins)} pin(s) "
          f"({landed} already landed, {len(to_retract)} dump row(s) superseded)")

    def revert(reason):
        B.FUNCTIONS.write_bytes(functions_raw)
        B.SYMBOLS.write_bytes(symbols_raw)
        DELETED.write_bytes(deleted_raw)
        if staged_sources:
            for source_rel, source_path in staged_sources:
                git("rm", "--cached", "--quiet", "--", source_rel)
                source_path.unlink()
            pending_path.unlink()
        print(f"land: {reason} — {len(to_append)} row(s), {len(new_pins)} pin(s), "
              f"{len(to_retract)} retraction(s)"
              + (f" and {len(staged_sources)} generated source(s)" if staged_sources else "") + " REVERTED", file=sys.stderr)

    verify = ([sys.executable, str(ROOT / "tools" / "build.py"), *selectors]
              if sys.platform == "win32" else [str(ROOT / "build.sh"), *selectors])
    try:
        code = run(verify, "./build.sh " + " ".join(selectors))
        if code == 0:
            code = run([sys.executable, str(ROOT / "tools" / "check_csv.py")],
                       "python3 tools/check_csv.py")
    except BaseException:
        revert("interrupted")
        raise
    if code != 0:
        revert(f"verification failed (exit {code})")
        raise SystemExit("land: nothing was changed")
    print(f"land: verified OK — {len(to_append)} row(s) are live")


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("classify", help="write reverse/ghidra_artifacts_blacklist.txt"
                   ).set_defaults(func=cmd_classify)
    gen = sub.add_parser("gen-thunks", help="write one Code/gen_small/thunks_NNN.cpp batch")
    gen.add_argument("--batch", type=int, default=0)
    gen.add_argument("--limit", type=int, default=500)
    gen.set_defaults(func=cmd_gen_thunks)
    gap = sub.add_parser("gen-gap-thunks",
                         help="write one Code/gen_small/gthunks_NNN.cpp batch of the "
                              "thunks the ghidra inventory never covered")
    gap.add_argument("--batch", type=int, default=0)
    gap.add_argument("--limit", type=int, default=500)
    gap.set_defaults(func=cmd_gen_gap_thunks)
    imports = sub.add_parser("gen-imports",
                             help="write one Code/gen_small/imports_NNN.cpp batch")
    imports.add_argument("--batch", type=int, default=0)
    imports.add_argument("--limit", type=int, default=500)
    imports.set_defaults(func=cmd_gen_imports)
    ehstubs = sub.add_parser("gen-ehstubs",
                             help="claim the ten-byte __ehhandler stubs in the gaps against "
                                  "Code/gen_small/eh_anchor.cpp")
    ehstubs.add_argument("--limit", type=int, default=3000)
    ehstubs.set_defaults(func=cmd_gen_ehstubs)
    dtors = sub.add_parser("gen-dtors",
                           help="write one Code/gen_small/dtors_NNN.cpp (or dtorsv_NNN.cpp) "
                                "batch of synthetic classes whose deleting destructors are "
                                "the retail bodies")
    dtors.add_argument("--kind", choices=sorted(DTOR_KINDS), default="scalar")
    dtors.add_argument("--batch", type=int, default=0)
    dtors.add_argument("--limit", type=int, default=200)
    dtors.set_defaults(func=cmd_gen_dtors)
    tgrid = sub.add_parser("gen-tgrid",
                           help="write Code/gen_small/tgrid_NNN.cpp batches of STLport "
                                "instantiations over a synthetic payload grid")
    tgrid.add_argument("--dims", default="all",
                       help="comma-separated grid dimensions to instantiate "
                            f"({', '.join(sorted({s.dim for s in TGRID_SPECS}))}), or all")
    tgrid.add_argument("--limit", type=int, default=100,
                       help="per-site instantiations per emitted TU")
    tgrid.add_argument("--batches", type=int, default=4,
                       help="new per-site TUs to write per run")
    tgrid.set_defaults(func=cmd_gen_tgrid)
    tinst = sub.add_parser("gen-tinst",
                           help="write Code/gen_small/tinst_NNN.cpp batches of STLport "
                                "instantiations over the REAL element types the retail "
                                "name tables carry")
    tinst.add_argument("--batches", type=int, default=8,
                       help="element types to try per run (each is one TU)")
    tinst.add_argument("--only", help="restrict to element types containing this text")
    tinst.set_defaults(func=cmd_gen_tinst)
    sub.add_parser("probe", help="byte-verify one instance of every skeleton"
                   ).set_defaults(func=cmd_probe)
    shims = sub.add_parser("gen-shims", help="write one Code/gen_small/fun_NNN.cpp batch")
    shims.add_argument("--batch", type=int, default=0)
    shims.add_argument("--limit", type=int, default=200)
    shims.set_defaults(func=cmd_gen_shims)
    getters = sub.add_parser(
        "gen-getters",
        help="write one numbered Code/gen_small/getters_NNN.cpp batch of exact B8 imm32 C3 shims")
    getters.add_argument("--batch", type=int, default=0)
    getters.add_argument("--dry-run", action="store_true",
                         help="report the exact population without writing files")
    getters.set_defaults(func=cmd_gen_getters)
    accessors = sub.add_parser(
        "gen-accessors",
        help="write the closed byte-validated accessor/predicate batch")
    accessors.add_argument("--batch", type=int, default=0)
    accessors.set_defaults(func=cmd_gen_accessors)
    sub.add_parser("shim-report", help="account for every anonymous FUN_* body"
                   ).set_defaults(func=cmd_shim_report)
    named = sub.add_parser("gen-named",
                           help="write one Code/gen_small/named_NNN.cpp batch of real identities")
    named.add_argument("--batch", type=int, default=0)
    named.set_defaults(func=cmd_gen_named)
    sweep = sub.add_parser("sweep-funclets",
                           help="match matched parents' SEH funclets to unclaimed retail funclets")
    sweep.add_argument("--limit", type=int, default=8,
                       help="parent sources per batch (each land compiles at most this "
                            "many objects, staying under build.py's full-build lock)")
    sweep.set_defaults(func=cmd_sweep_funclets)
    land = sub.add_parser("land", help="append a generated batch's rows and pins, then verify")
    land.add_argument("source", help="the batch source, e.g. Code/gen_small/thunks_000.cpp")
    land.set_defaults(func=cmd_land)
    fcensus = sub.add_parser("family-census",
                             help="rank the unclaimed shape families in the current ledger")
    fcensus.add_argument("--top", type=int, default=40)
    fcensus.add_argument("--show", help="comma-separated family ids or member RVAs to "
                                        "print in full instead of the ranking")
    fcensus.add_argument("--json", help="also dump the whole ranking here")
    fspike = sub.add_parser("family-spike",
                            help="prove one FAMILY_LIBRARY recipe against a live "
                                 "unclaimed exemplar of its shape")
    fspike.add_argument("id", help="a family id from family-census, or a member RVA")
    fspike.set_defaults(func=cmd_family_spike)
    frecipe = sub.add_parser("family-recipe",
                             help="report every census family a recipe explains")
    frecipe.add_argument("--recipe", default="all", help="comma-separated recipe ids")
    frecipe.add_argument("--top", type=int, default=25)
    frecipe.set_defaults(func=cmd_family_recipe)
    femit = sub.add_parser("family-emit",
                           help="write Code/gen_small/fam_NNN.cpp batches claiming every "
                                "member of every proven family recipe")
    femit.add_argument("--only", default="all", help="comma-separated family ids")
    femit.add_argument("--limit", type=int, default=50,
                       help="per-site instantiations per emitted TU")
    femit.add_argument("--batches", type=int, default=4,
                       help="new TUs to write per run")
    femit.set_defaults(func=cmd_family_emit)
    fcensus.set_defaults(func=cmd_family_census)
    land_funclets = sub.add_parser("land-funclets",
                                   help="append one funclet batch's rows, then verify")
    land_funclets.add_argument("--batch", type=int, default=0)
    land_funclets.set_defaults(func=cmd_land_funclets)
    args = parser.parse_args(argv)
    try:
        args.func(args)
    except FormatError as error:
        raise SystemExit(f"gen_small: {error}")


if __name__ == "__main__":
    main()
