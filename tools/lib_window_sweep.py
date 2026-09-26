#!/usr/bin/env python3
"""Needle-place release-library function bodies into retail's library territory.

The linker copied whole COMDATs out of the static libraries this project ships
as build inputs, so 800 KB of retail `.text` is Microsoft's compiled code. The
attached rows prove that per body: `./build.sh` unpacks the archive member a
row's `member=` note names and byte-compares it against retail with every
relocation site masked. This sweep finds the bodies that have not been attached
yet, and it decides where each one went under one explicit standard.

THE COUNT-AGREEMENT STANDARD
----------------------------
A masked body is not a unique fingerprint. A 40-byte prologue-heavy span can
sit at several addresses, and picking one because "it matched" is how a wave
lands 17 wrong addresses. So a placement is only claimed when all three hold:

  in-window        the address lies in the sub-range of [0x9F6C00, 0xB00000)
                   that this library already owns in the ledger. The four
                   libraries occupy four contiguous, non-overlapping runs (see
                   WINDOWS below); a d3dx9 body found inside dxerr9's run is a
                   coincidence, not a placement.
  count-agreement  retail holds no MORE copies of a body than the archive
                   supplies. A class with 3 archive instances and 4 in-window
                   hits is over-subscribed: at least one hit is a collision, we
                   cannot tell which, and the whole class is refused.
  archive-order    with the counts agreeing, the i-th placement by ascending
                   RVA is the i-th instance in archive order. The linker emits
                   COMDATs in the order it pulls members in, so this is the
                   assignment, not a guess among equals.

This is deliberately WEAKER than global uniqueness, which is why the standard
is written down here and in inputs/vendor/d3dx9/PROVENANCE.txt rather than left
implicit in a matcher. Its corroborations and its limits are recorded there.

Four tests keep the ordering premise honest, because ordering is the part of the
standard that can be wrong while every byte still matches:

  ledger anchors   a class containing a body the ledger ALREADY attaches is a
                   class whose ordering has a known answer. If ascending-RVA
                   order disagrees with that answer, the premise failed here
                   and the WHOLE class is refused — not just the bad pair.
  callee targets   two masked-identical bodies differ exactly at their
                   relocation slots, and retail has those slots resolved. Every
                   REL32 in a claimed body is decoded and the archive's own
                   copy of the named callee must be at the far end. This is
                   what separates `??_GCSprite` from `??_GCCodec`: 28 identical
                   bytes, but one calls ??1CCodec and the linker wrote that
                   address down. 53 placements ascending order got wrong were
                   caught this way; they are refused, not repaired, because
                   repairing them means choosing among members that define the
                   same COMDAT and that is a second standard, not this one.
  DIR32 bases      the same idea one step out: a DIR32 slot says where a named
                   global went, and a symbol has one address. A placement that
                   puts an anchored symbol somewhere an already-attached row
                   does not is refused, and so is a pair of this wave's own rows
                   that resolve one symbol two ways. build.py runs the same
                   arithmetic over the whole ledger, but only in the FULL gate —
                   a ledger-only commit gets a SCOPED build from both hooks, and
                   the scoped path skips it. Applying it here is what stops a
                   wave landing rows that check will blame after the push.
  twin naming      the tests above refute; this one measures what is left. For
                   each address, every instance of the class that survives all
                   of them is a candidate. When more than one SYMBOL survives,
                   ascending order was a coin flip, and the row is named
                   `?<lib>_twin_<rva>@@YAXXZ` with `object-symbol=` carrying the
                   COMDAT. The bytes are still proved; only the name stops
                   claiming what the image does not witness.

LEGALITY
--------
Placement says where the bytes are. Legality says whether the ledger will take
the row today:

  pure-unclaimed   overlaps no matched row                    -> plain append
  dump-exact       is exactly one gen-dump row's (rva, size)  -> supersede
  dump-padded      a gen-dump row starts here and is longer than the stripped
                   body but still inside the member's raw span, and the raw
                   span masked-verifies over the row's full extent -> supersede
                   at the DUMP row's size (validate_rows only supersedes an
                   exact range, and the trailing bytes are the member's own
                   0xCC padding, which retail kept)
  dump-mismatch    overlaps gen-dump rows on some other extent -> boundary
                   surgery, not this wave's business
  held-overlap     overlaps a real row                        -> refused

Usage
  python3 tools/lib_window_sweep.py --report
  python3 tools/lib_window_sweep.py --emit wave.csv --legal dump-exact,pure-unclaimed

--emit writes a worklist, not a landing: tools/land_wave.py, which used to
consume it, was retired with the generators, so each row is proved and
appended by hand now.
"""
import argparse
import bisect
import csv
import functools
import io
import re
import struct
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import coffar
import locate

ROOT = B.ROOT
MEMBER_CACHE = ROOT / "build" / "lib_window_sweep" / "members"

VC_LIB = (ROOT / "inputs/toolchains/vs2003/Program Files"
          / "Microsoft Visual Studio .NET 2003/Vc7/lib")
PSDK_LIB = (ROOT / "inputs/toolchains/vs2003/Program Files"
            / "Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Lib")

# The exe links /MD, so the static CRTs cannot be what retail holds; they are
# swept anyway because a handful of statics (RunTmChk, msvcrt's own stubs) do
# get pulled in, and because a body that ALSO exists in libcmt is evidence
# about which archive a CRT-window placement came from.
DEBUG_VARIANTS = {"libcd", "libcmtd", "libcpd", "libcpmtd", "msvcrtd", "msvcprtd",
                  "comsuppd", "comsuppwd", "oledbd"}

# Library territory, and the run each archive owns inside it. Each bound is the
# hull of that archive's ALREADY-ATTACHED rows, rounded out to the next
# library's first attached row.
#
# d3dx9's run starts BELOW its lowest attached row (0xA0009A) and below the
# 0xA00000 inputs/vendor/d3dx9/PROVENANCE.txt states: [0x9F8AC0, 0xA00000) holds
# d3dxmath.obj laid out in object order — ?WithinEpsilon, ?sincosf,
# c_D3DXFloat32To16Array, then thirty init_/c_ pairs in source sequence. Only
# one d3dxmath body had ever been attached, so the region read as unowned. The
# ledger cannot bound this window; the object-order run is what does.
WIN_LO, WIN_HI = 0x9F6C00, 0xB00000
WINDOWS = {
    "crt": (0x9F6C00, 0x9F8AC0),
    "d3dx9": (0x9F8AC0, 0xAD5401),
    "dxerr9": (0xAD5401, 0xAFD550),
    "comsupp": (0xAFD550, 0xB00000),
}

# tag -> (ledger source path, window key). A tag with no entry is CRT-window
# and has no ledger home yet; it is swept for accounting and refused for
# emission rather than silently attached to the wrong archive.
LEDGER_SOURCE = {
    "d3dx9": ("inputs/vendor/d3dx9/d3dx9.lib", "d3dx9"),
    "dxerr9": ("inputs/vendor/dxerr9/dxerr9.lib", "dxerr9"),
    "vcomsupp": ("inputs/vendor/comsupp/comsupp.lib", "comsupp"),
    "comsupp": ("inputs/vendor/comsupp/comsupp.lib", "comsupp"),
    "comsuppw": ("inputs/vendor/comsupp/comsupp.lib", "comsupp"),
}
for _stem in ("libc", "libcmt", "libcp", "libcpmt", "msvcrt", "msvcprt",
              "oldnames", "RunTmChk"):
    LEDGER_SOURCE.setdefault(
        _stem, (str((VC_LIB / f"{_stem}.lib").relative_to(ROOT)), "crt"))
for _stem in ("strsafe", "bufferoverflow"):
    LEDGER_SOURCE.setdefault(
        _stem, (str((PSDK_LIB / f"{_stem}.lib").relative_to(ROOT)), "crt"))

# A span shorter than this carries too little shape to place by needle at all,
# and build.py refuses a masked comparison with fewer than MIN_LIB_CONCRETE
# bytes outside a relocation site as proving nothing.
MIN_SPAN = 16
MEMBER_NOTE_RE = re.compile(r"(?:^|;)member=([^;]+)")
OBJECT_SYMBOL_RE = re.compile(r"(?:^|;)object-symbol=([^;]+)")


class SweepError(Exception):
    """The sweep found something it must not route around."""


# --------------------------------------------------------------------------
# inputs
# --------------------------------------------------------------------------

def archive_paths():
    """{tag: path} for every release archive and loose object worth sweeping."""
    libs = {}
    if not VC_LIB.is_dir():
        raise SweepError(f"{VC_LIB.relative_to(ROOT)} is not a directory — the VS2003 "
                         "toolchain is a tracked build input; this sweep cannot run without it")
    for path in sorted(VC_LIB.glob("*.lib")):
        if path.stem in DEBUG_VARIANTS:
            continue
        libs[path.stem] = path
    for path in sorted(VC_LIB.glob("*.obj")):
        libs["obj:" + path.stem] = path
    for tag, path in [("d3dx9", ROOT / "inputs/vendor/d3dx9/d3dx9.lib"),
                      ("dxerr9", ROOT / "inputs/vendor/dxerr9/dxerr9.lib"),
                      ("vcomsupp", ROOT / "inputs/vendor/comsupp/comsupp.lib"),
                      ("strsafe", PSDK_LIB / "strsafe.lib"),
                      ("bufferoverflow", PSDK_LIB / "bufferoverflow.lib")]:
        if path.exists():
            libs[tag] = path
    return libs


def tracked_sources():
    """The set of repo-relative paths git holds, so no wave can `git add` a 5 MB lib."""
    out = subprocess.run(["git", "-C", str(ROOT), "ls-files", "-z", "--",
                          "inputs/vendor", "inputs/toolchains"],
                         capture_output=True, text=True, check=True)
    return set(out.stdout.split("\0")) - {""}


class Ledger:
    """The matched rows, indexed the three ways this sweep asks about them."""

    def __init__(self, ref=None):
        self.rows = []
        if ref is None:
            text = (ROOT / "targets/game/reverse" / "functions.csv").read_text(encoding="utf-8")
        else:
            # Re-deriving a wave that has already landed needs the ledger as it
            # was BEFORE it: read against today's rows, every class the wave
            # claimed is `consumed` and the sweep correctly reports nothing.
            text = subprocess.run(
                ["git", "-C", str(ROOT), "show", f"{ref}:targets/game/reverse/functions.csv"],
                capture_output=True, check=True).stdout.decode("utf-8")
        with io.StringIO(text, newline="") as handle:
            for record in csv.DictReader(handle):
                if record["status"] != "matched":
                    continue
                source = record["source"]
                lower = source.lower()
                kind = ("dump" if lower.endswith((".asm", ".s"))
                        else "lib" if lower.endswith(".lib") else "held")
                notes = record["notes"]
                symbol = record["name"]
                match = OBJECT_SYMBOL_RE.search(notes)
                if match:
                    symbol = match.group(1)
                member = MEMBER_NOTE_RE.search(notes)
                self.rows.append({
                    "name": record["name"], "rva": int(record["target_rva"], 16),
                    "size": int(record["target_size"]), "kind": kind, "source": source,
                    "symbol": symbol, "member": member.group(1) if member else None,
                    "is_dump": B.is_scaffold_row({"notes": notes}),
                })
        self.names = {row["name"] for row in self.rows}
        self.by_rva_sorted = sorted(self.rows, key=lambda row: row["rva"])
        self.starts = [row["rva"] for row in self.by_rva_sorted]
        self.dump_at = {row["rva"]: row for row in self.rows if row["is_dump"]}
        self.attached_rvas = {row["rva"] for row in self.rows if row["kind"] == "lib"}
        # Keyed by (source, member, symbol), NOT by address: the question this
        # answers is "has the ledger already consumed this COMDAT?", and asking
        # it by placement lets a body the ledger holds at a size we disagree
        # about be claimed a second time under a second name.
        self.consumed = {}
        for row in self.rows:
            if row["kind"] != "lib" or row["member"] is None:
                continue
            key = (row["source"], row["member"], row["symbol"])
            self.consumed.setdefault(key, []).append(row)
        self.widest = max((row["size"] for row in self.rows), default=0)

    def overlapping(self, rva, size):
        """Every matched row whose range intersects [rva, rva+size).

        Walks back from the first row starting at or after the end. `widest` is
        the real bound: stopping at the first non-overlapping row (what the
        spike did) walks straight past a long row that starts far earlier and
        still covers this address, and reports the ground as free.
        """
        out = []
        index = bisect.bisect_left(self.starts, rva + size) - 1
        while index >= 0:
            row = self.by_rva_sorted[index]
            if rva - row["rva"] > self.widest:
                break
            if row["rva"] + row["size"] > rva:
                out.append(row)
            index -= 1
        return out


# --------------------------------------------------------------------------
# span pool
# --------------------------------------------------------------------------

def canon(span, relocs):
    """The span with every relocation slot zeroed — its identity across instances."""
    out = bytearray(span)
    for offset, rtype, _ in relocs:
        width = coffar.RELOC_WIDTH.get(rtype, 4)
        out[offset:offset + width] = b"\0" * width
    return bytes(out)


class Instance:
    """One function body in one archive member."""

    __slots__ = ("tag", "member", "symbol", "span", "relocs", "raw", "raw_relocs", "order")

    def __init__(self, tag, member, symbol, span, relocs, raw, raw_relocs, order):
        self.tag, self.member, self.symbol = tag, member, symbol
        self.span, self.relocs = span, relocs
        self.raw, self.raw_relocs = raw, raw_relocs
        self.order = order


CALLEE_MIN_SPAN = 8


def collect_instances(libs, warn):
    """(classes, callees) over every release span, in archive order.

    `classes` is {(size, canon): [Instance]} — the placement pool, which needs a
    body long enough to needle-search. `callees` is {(tag, symbol): [Instance]}
    over EVERY span including the short ones, because a 10-byte destructor is a
    perfectly good thing for a claimed body to call, and the call is the
    evidence.
    """
    MEMBER_CACHE.mkdir(parents=True, exist_ok=True)
    classes = defaultdict(list)
    callees = defaultdict(list)
    order = 0
    for tag, path in libs.items():
        if path.suffix.lower() == ".obj":
            members = [(path.name, path.read_bytes())]
        else:
            try:
                members = coffar.read_archive(path)
            except ValueError as exc:
                warn(f"{path.relative_to(ROOT)}: {exc}")
                continue
            names = Counter(name for name, _ in members)
            repeated = {name for name, count in names.items() if count > 1}
            if repeated:
                # extract_lib_members does dict(read_archive(...)), so only the
                # LAST member of a repeated name is ever unpacked. Claiming a
                # body out of the earlier one would name a member the gate
                # resolves to different bytes.
                warn(f"{path.relative_to(ROOT)}: member name(s) repeated in the archive "
                     f"({', '.join(sorted(repeated)[:3])}); every span in them is skipped "
                     "because the gate unpacks one member per name")
                members = [(n, b) for n, b in members if n not in repeated]
        for member_name, body in members:
            # An import library's members are short-import records, not COFF.
            # Handing one to a COFF reader means 65,535 bogus section headers
            # parsed before it throws, so the machine type decides first.
            if len(body) < 20 or body[0:2] != b"\x4c\x01":
                continue
            cached = MEMBER_CACHE / (tag + "_" + re.sub(r"[\\/]", "_", member_name))
            if not cached.exists() or cached.read_bytes() != body:
                cached.write_bytes(body)
            try:
                functions = list(locate.object_functions(cached))
            except Exception as exc:            # a non-COFF or truncated member
                warn(f"{path.name}({member_name}): unreadable as COFF ({exc})")
                continue
            for symbol, raw_span, raw_relocs in functions:
                raw = bytes(raw_span)
                span = raw.rstrip(b"\xcc")
                if len(span) < CALLEE_MIN_SPAN:
                    continue
                relocs = sorted((o, t, s) for o, t, s in raw_relocs if o < len(span))
                order += 1
                instance = Instance(
                    tag, member_name, symbol, span, relocs, raw,
                    sorted((o, t, s) for o, t, s in raw_relocs if o < len(raw)), order)
                callees[(tag, symbol)].append(instance)
                if len(span) >= MIN_SPAN:
                    classes[(len(span), canon(span, relocs))].append(instance)
    return classes, callees


# --------------------------------------------------------------------------
# placement
# --------------------------------------------------------------------------

def holes_of(relocs):
    return [(offset, coffar.RELOC_WIDTH.get(rtype, 4)) for offset, rtype, _ in relocs]


def masked_eq(body, span, relocs, upto=None):
    """True when body matches span everywhere outside a relocation slot."""
    length = len(span) if upto is None else upto
    if len(body) < length:
        return False
    covered = bytearray(length)
    for offset, width in holes_of(relocs):
        if offset >= length:
            continue
        covered[offset:offset + width] = b"\1" * min(width, length - offset)
    for index in range(length):
        if covered[index]:
            continue
        if index >= len(span) or body[index] != span[index]:
            return False
    return True


def concrete_bytes(relocs, size):
    """build.py's `concrete`: bytes of a masked comparison that prove anything."""
    covered = bytearray(size)
    for offset, rtype, _ in relocs:
        if offset >= size:
            continue
        width = min(coffar.RELOC_WIDTH.get(rtype, 4), size - offset)
        covered[offset:offset + width] = b"\1" * width
    return size - sum(covered)


def longest_needle(span, relocs, minimum):
    """The longest run of span with no relocation slot in it — the search key."""
    segments, position = [], 0
    for offset, width in sorted(holes_of(relocs)):
        if offset > position:
            segments.append((position, offset))
        position = max(position, offset + width)
    if position < len(span):
        segments.append((position, len(span)))
    segments = [s for s in segments if s[1] - s[0] >= minimum]
    return max(segments, key=lambda s: s[1] - s[0]) if segments else None


REL32 = 0x0014
JMP_REL32 = 0xE9
IMPORT_THUNK = b"\xff\x25"


def callee_verdict(rva, size, instance, callees, image, text_range, follow=True):
    """(corroborated, contradicted) over this placement's outgoing calls.

    The count-agreement standard decides WHICH of several identical bodies sits
    at an address purely by ordering. This decides it by what the body calls.
    Two masked-identical bodies differ exactly at their relocation slots, and
    retail has those slots RESOLVED: decode each REL32, and the archive says
    which function is supposed to be there. If the callee's own library body is
    not at that address, this pair is not the pair — the ordering premise put
    the wrong symbol on these bytes.

    A miss is only ever reported against a callee the archive itself defines,
    so an import, a data reference or a symbol from another library is silent
    rather than guessed at.
    """
    text_lo, text_hi = text_range
    corroborated, contradicted = 0, []
    for offset, rtype, name in instance.relocs:
        if rtype != REL32 or offset + 4 > size:
            continue
        candidates = callees.get((instance.tag, name))
        if not candidates:
            continue
        stored = image(rva + offset, 4)
        if len(stored) < 4:
            contradicted.append((offset, name, None))
            continue
        destination = rva + offset + 4 + int.from_bytes(stored, "little", signed=True)
        if not (text_lo <= destination < text_hi):
            contradicted.append((offset, name, destination))
            continue
        if any(masked_eq(image(destination, len(c.span)), c.span, c.relocs)
               for c in candidates):
            corroborated += 1
            continue
        body = image(destination, 6)
        # A `jmp dword ptr [__imp__x]` stub means the linker satisfied this
        # callee from a DLL and never pulled the archive's copy in. That is
        # evidence about the LINK, not about this placement, so it is silent.
        if len(body) >= 2 and body[0:2] == IMPORT_THUNK:
            continue
        # One hop through a `jmp rel32` veneer before calling it a miss.
        if follow and len(body) >= 5 and body[0] == JMP_REL32:
            hop = destination + 5 + int.from_bytes(body[1:5], "little", signed=True)
            if text_lo <= hop < text_hi and any(
                    masked_eq(image(hop, len(c.span)), c.span, c.relocs) for c in candidates):
                corroborated += 1
                continue
        contradicted.append((offset, name, destination))
    return corroborated, contradicted


DIR32 = 0x0006
COMPILER_LOCAL_RE = re.compile(r"\$[A-Za-z]+\d+\Z")


@functools.lru_cache(maxsize=None)
def static_definitions(path_str):
    """Names this object DEFINES with IMAGE_SYM_CLASS_STATIC.

    A static's name is TU-scoped, so its base is only comparable inside the same
    member. `__NEG_` is static in BOTH d3dxmathsse.obj and d3dxmathsse2.obj: one
    name, two objects, two legitimate addresses. Keyed by name alone that reads
    as a contradiction, and ten byte-verified placements come out for it.
    """
    data = Path(path_str).read_bytes()
    table, count = B.u32(data, 8), B.u32(data, 12)
    strings = data[table + count * 18:]
    out, index = set(), 0
    while index < count:
        offset = table + index * 18
        section = struct.unpack_from("<h", data, offset + 12)[0]
        storage, aux = data[offset + 16], data[offset + 17]
        if section > 0 and storage == 3:
            name = B.coff_name(data, offset, strings)
            if name:
                out.add(name)
        index += 1 + aux
    return frozenset(out)


def statics_of(instance, statics):
    """The static names `instance`'s member defines, however they were supplied.

    `statics` lets a caller inject the map (the tests do); left out, the member
    is read from the sweep's own cache, which is written before any placement.
    """
    key = (instance.tag, instance.member)
    if statics is not None:
        return statics.get(key, frozenset())
    cached = MEMBER_CACHE / (instance.tag + "_" + re.sub(r"[\\/]", "_", instance.member))
    return static_definitions(str(cached)) if cached.exists() else frozenset()


def dir32_assertions(rva, size, instance, image, statics=None):
    """[(key, base, offset, symbol)] this placement asserts through its DIR32s.

    Retail holds the RESOLVED address; the archive holds the addend. Their
    difference is where the named symbol went, so a placement is a statement
    about every global it touches. Same arithmetic as build.py's
    verify_dir32_consistency, and the same exclusions: a string literal is
    per-TU, and `$L1234`/`__ehhandler$` are compiler-local labels an
    object-symbol= row deliberately aliases onto many retail instances.
    """
    local = statics_of(instance, statics)
    limit = min(size, len(instance.span))
    out = []
    for offset, rtype, name in instance.relocs:
        if rtype != DIR32 or offset + 4 > limit:
            continue
        if name.startswith("??_C@") or name.startswith("__ehhandler$"):
            continue
        if COMPILER_LOCAL_RE.fullmatch(name):
            continue
        final = image(rva + offset, 4)
        if len(final) < 4:
            continue
        addend = struct.unpack_from("<I", instance.span, offset)[0]
        base = (struct.unpack("<I", final)[0] - addend) & 0xFFFFFFFF
        out.append(((instance.member, name) if name in local else name,
                    base, offset, name))
    return out


def dir32_verdict(rva, size, instance, image, anchors, statics=None):
    """(corroborated, contradicted) over the globals this placement resolves.

    `anchors` is {key: {base}} witnessed by rows the ledger ALREADY holds. A
    symbol has one address, so a placement whose arithmetic puts an anchored
    symbol somewhere else is a placement archive order got wrong. This is what
    separates ??_GCVSProgram from ??_GCFXLProgram: 34 identical bytes, but one
    loads the vtable base an attached CVSProgram constructor already pins.

    A key with no anchor, or one the ledger itself shows at several bases,
    decides nothing and is silent rather than guessed at.
    """
    corroborated, contradicted = 0, []
    for key, base, offset, name in dir32_assertions(rva, size, instance, image, statics):
        known = anchors.get(key)
        if not known or len(known) != 1:
            continue
        if base == next(iter(known)):
            corroborated += 1
        else:
            contradicted.append((offset, name, base))
    return corroborated, contradicted


def anchor_bases(ledger, classes, callees, image):
    """{key: {base}} from the lib rows attached BEFORE this run.

    Those rows are the trusted baseline: the same rows the ordering test uses
    as anchors, read for what they say about data instead of about order.
    """
    index = {}
    for pool in (classes, callees):
        for instances in pool.values():
            for instance in instances:
                entry = LEDGER_SOURCE.get(instance.tag)
                if entry:
                    index.setdefault((entry[0], instance.member, instance.symbol), instance)
    bases = defaultdict(set)
    for key, rows in ledger.consumed.items():
        instance = index.get(key)
        if instance is None:
            continue
        for row in rows:
            for slot, base, _offset, _name in dir32_assertions(
                    row["rva"], row["size"], instance, image):
                bases[slot].add(base)
    return bases


HIT_CEILING = 64


def placements(window, instance):
    """Every RVA in the window where this body's masked bytes sit."""
    segment = (longest_needle(instance.span, instance.relocs, 8)
               or longest_needle(instance.span, instance.relocs, 4))
    if segment is None:
        return None
    lo, hi = segment
    needle = instance.span[lo:hi]
    size = len(instance.span)
    hits, start = [], 0
    while True:
        position = window.find(needle, start)
        if position < 0:
            break
        first = position - lo
        if 0 <= first <= len(window) - size and \
                masked_eq(window[first:first + size], instance.span, instance.relocs):
            hits.append(WIN_LO + first)
        start = position + 1
        if len(hits) > HIT_CEILING:
            break
    return hits


# --------------------------------------------------------------------------
# the sweep
# --------------------------------------------------------------------------

LEGAL_ORDER = ["dump-exact", "dump-padded", "pure-unclaimed", "dump-mismatch", "held-overlap"]


def sweep(report, ledger_ref=None):
    ledger = Ledger(ledger_ref)
    libs = archive_paths()
    tracked = tracked_sources()
    data, sections = B.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    base = text["raw_pointer"] - text["rva"]
    window = data[base + WIN_LO:base + WIN_HI]
    text_range = (text["rva"], text["rva"] + text["size"])

    def image(rva, count):
        return data[base + rva:base + rva + count]

    classes, callees = collect_instances(libs, report.warn)
    report.note(f"release spans: {sum(len(v) for v in classes.values()):,} in "
                f"{len(classes):,} masked-identity classes over {len(libs)} archives")
    anchors = anchor_bases(ledger, classes, callees, image)
    report.note(f"DIR32 bases pinned by already-attached rows: {len(anchors):,}")

    # A byte the ledger already holds under a real row can never be re-claimed;
    # a byte a gen-dump holds can be superseded. Tracked as a lane so a class
    # that would claim ground an earlier class in THIS run already took is
    # refused rather than landed into an overlap the gate will reject.
    lane = bytearray(len(window))
    for row in ledger.rows:
        start = max(row["rva"], WIN_LO) - WIN_LO
        end = min(row["rva"] + row["size"], WIN_HI) - WIN_LO
        if start >= end:
            continue
        value = 1 if row["is_dump"] else 2
        for index in range(start, end):
            if lane[index] < value:
                lane[index] = value
    claimed = bytearray(len(window))

    results = []
    for key in sorted(classes, key=lambda k: (-k[0], k[1])):
        size = key[0]
        instances = classes[key]
        tags = {i.tag for i in instances}
        owner = next((t for t in ("d3dx9", "dxerr9", "vcomsupp") if t in tags),
                     sorted(tags)[0])
        source, window_key = LEDGER_SOURCE.get(owner, (None, "crt"))
        wlo, whi = WINDOWS[window_key]
        ordered = sorted((i for i in instances if i.tag == owner), key=lambda i: i.order)
        hits = placements(window, ordered[0])
        if hits is None:
            report.count("no-needle", size)
            continue
        if not hits:
            continue
        in_window = sorted(h for h in hits if wlo <= h < whi)
        if not in_window:
            continue
        # Supply is the OWNER's instance count, not the class's: only this
        # archive's members can have been linked into this archive's run, so
        # counting a libcmt twin as supply for a d3dx9-window hit would license
        # exactly the collision the standard exists to refuse.
        if len(in_window) > len(ordered):
            report.oversubscribed(size, len(in_window), len(ordered))
            continue

        # archive-order assignment over the FULL pairing, then drop the pairs
        # the ledger already owns. Pairing after the drop would slide every
        # later placement onto the wrong member.
        pairs = list(zip(in_window, ordered))

        # Every pair the ledger already holds is a test this class has to pass.
        # A class whose assignment contradicts an attached row is not a class
        # with one bad pair in it — the ordering premise failed there, so every
        # OTHER pair it produced is unevidenced too, and the whole class goes.
        # This is what caught the D3DXQUATERNION operators: inline COMDATs that
        # retail keeps both in their defining object's run and again in the
        # shared inline pool 200 KB later, which ascending-RVA order pairs the
        # wrong way round.
        anchor_hits = 0
        contradicted = False
        for rva, instance in pairs:
            for row in ledger.consumed.get((source, instance.member, instance.symbol), ()):
                if row["rva"] == rva:
                    anchor_hits += 1
                else:
                    contradicted = True
                    report.disagreement(source, instance.member, instance.symbol,
                                        row["rva"], rva)
        if contradicted:
            report.count("assignment-contradicts-ledger", size * len(pairs))
            continue
        report.witness(len(in_window), anchor_hits)

        # What else could be here. Every instance in a class is masked-identical
        # to every other by construction, so an alternative that survives the
        # same three tests is not distinguishable from the one ascending order
        # picked. A row whose survivor set names more than one SYMBOL must not
        # carry any of them: the name column is what every other tool resolves
        # an identity through, and phase 2 put 17 real names on wrong addresses
        # exactly this way.
        feasible = {}
        for rva, _assigned in pairs:
            names = set()
            for candidate in ordered:
                if not masked_eq(image(rva, size), candidate.span, candidate.relocs):
                    continue
                if callee_verdict(rva, size, candidate, callees, image, text_range)[1]:
                    continue
                if dir32_verdict(rva, size, candidate, image, anchors)[1]:
                    continue
                names.add(candidate.symbol)
            feasible[rva] = witnessed_candidates(rva, sorted(names))

        for rva, instance in pairs:
            if (source, instance.member, instance.symbol) in ledger.consumed:
                continue
            if rva in ledger.attached_rvas:
                report.count("rva-held-by-another-member", size)
                continue
            row = classify(rva, size, instance, ledger, lane, claimed, image, source,
                           owner, report, callees, text_range, anchors)
            if row is not None:
                row["placements"] = len(in_window)
                row["instances"] = len(ordered)
                row["anchors"] = anchor_hits
                row["candidates"] = feasible[rva] or [instance.symbol]
                results.append(row)
    return refuse_dir32_conflicts(results, anchors, report), ledger, tracked


GHIDRA_FUNCTIONS = ROOT / "targets/game/reverse" / "ghidra_functions.csv"


@functools.lru_cache(maxsize=1)
def ghidra_names():
    """{rva: name} for the addresses Ghidra names from its own signatures.

    Ghidra has never seen these archives, so a name it recovers independently is
    the one witness that can settle a twin without reading a relocation: it
    names ONE of the candidates, and the rest of the class is not it. Only an
    exact match counts -- a near-miss is a guess, and a guessed identity is
    exactly what this whole file exists to refuse.
    """
    if not GHIDRA_FUNCTIONS.exists():
        return {}
    out = {}
    with GHIDRA_FUNCTIONS.open(newline="", encoding="utf-8") as handle:
        for record in csv.DictReader(handle):
            name = record.get("name") or ""
            if not name or name.startswith("FUN_"):
                continue
            try:
                out[int(record["rva"], 16)] = name
            except ValueError:
                continue
    return out


def witnessed_candidates(rva, candidates, names=None):
    """`candidates` cut down to the one an independent Ghidra name picks out."""
    name = (ghidra_names() if names is None else names).get(rva)
    return [name] if name in candidates else candidates


DIR32_WHITELIST = ROOT / "targets/game/reverse" / "dir32_consistency_whitelist.txt"


def gate_disagreements(bases, anchors):
    """Keys build.py's verify_dir32_consistency will blame even though we won't.

    That check keys a base by symbol NAME alone, so `__NEG_` -- static in both
    d3dxmathsse.obj and d3dxmathsse2.obj, one name, two objects, two legitimate
    addresses -- reads to it as one symbol at two addresses. Scoping statics by
    member (what dir32_assertions does) is the sharper rule, but the check is
    the gate, and a wave that emits rows the gate blames turns master red for
    everyone. So the sweep refuses what the gate refuses and says why here; the
    fix is a storage-class exclusion in verify_dir32_consistency, not a
    whitelist entry and not a softer sweep.
    """
    whitelist = set()
    if DIR32_WHITELIST.exists():
        whitelist = {line.strip() for line in DIR32_WHITELIST.read_text().splitlines()
                     if line.strip() and not line.startswith("#")}
    by_name = defaultdict(set)
    for source in (bases, anchors):
        for key, seen in source.items():
            by_name[key[1] if isinstance(key, tuple) else key] |= seen
    blamed = {name for name, seen in by_name.items()
              if len(seen) > 1 and name not in whitelist}
    return {key for key in bases
            if (key[1] if isinstance(key, tuple) else key) in blamed}


def refuse_dir32_conflicts(results, anchors, report):
    """Drop every row party to a base two placements disagree about.

    The per-row test above only sees keys the LEDGER anchors. Two rows of the
    same wave can still resolve one symbol two ways with nothing attached to
    say which is right -- `_IID_ID3DXBuffer` landed at 0x0114DA98 through one
    QueryInterface placement and 0x0114DBC8 through the other. One external
    GUID has one address, so at least one is wrong; refusing both is the same
    class-wide rule the ordering test already applies.

    Refusal here leaves the `claimed` lane marked, so a refused row's ground
    stays unclaimed for this run and is re-derived by the next one.
    """
    bases = defaultdict(set)
    for row in results:
        for key, base, _offset, _name in row["dir32"]:
            bases[key].add(base)
    conflicted = {key for key, seen in bases.items()
                  if len(seen) > 1 or (len(anchors.get(key, ())) == 1 and seen != anchors[key])}
    conflicted |= gate_disagreements(bases, anchors)
    if not conflicted:
        return results
    kept = []
    for row in results:
        blamed = sorted({key for key, _b, _o, _n in row["dir32"] if key in conflicted})
        if blamed:
            report.dir32_conflict(row, blamed)
        else:
            kept.append(row)
    return kept


def classify(rva, size, instance, ledger, lane, claimed, image, source, owner, report,
             callees, text_range, anchors):
    offset = rva - WIN_LO
    # The class was placed with its FIRST instance's relocation layout. Two
    # instances can canonicalise the same and still hole differently, so the
    # instance this address was actually assigned re-verifies here — a refusal
    # the sweep can explain beats a drop the gate has to.
    if not masked_eq(image(rva, size), instance.span, instance.relocs):
        report.count("assigned-instance-disagrees", size)
        return None
    corroborated, contradicted = callee_verdict(rva, size, instance, callees, image, text_range)
    if contradicted:
        report.callee_miss(rva, instance, contradicted)
        report.count("callee-target-contradicts", size)
        return None
    based, disputed = dir32_verdict(rva, size, instance, image, anchors)
    if disputed:
        report.dir32_miss(rva, instance, disputed)
        report.count("dir32-base-contradicts", size)
        return None
    overlaps = ledger.overlapping(rva, size)
    dump = ledger.dump_at.get(rva)
    claim_size = size
    relocs = instance.relocs
    if not overlaps:
        legal = "pure-unclaimed"
    elif dump is not None and len(overlaps) == 1 and overlaps[0] is dump:
        if dump["size"] == size:
            legal = "dump-exact"
        elif dump["size"] <= len(instance.raw) and masked_eq(
                image(rva, dump["size"]), instance.raw, instance.raw_relocs, upto=dump["size"]):
            legal = "dump-padded"
            claim_size = dump["size"]
            relocs = instance.raw_relocs
        else:
            legal = "dump-mismatch"
    elif all(row["is_dump"] for row in overlaps):
        legal = "dump-mismatch"
    else:
        legal = "held-overlap"

    if legal in ("held-overlap", "dump-mismatch"):
        report.count(legal, claim_size)
        return None
    # Any overlap with a claim this run already made, not just a total one:
    # land_wave refuses a wave whose own rows straddle each other, and it
    # refuses the WHOLE wave, so a partial overlap emitted here costs every
    # other row in the batch.
    if any(claimed[i] for i in range(offset, offset + claim_size)):
        report.count("overlaps-earlier-claim-this-run", claim_size)
        return None
    new_bytes = sum(1 for i in range(offset, offset + claim_size) if lane[i] != 2)
    if new_bytes == 0:
        report.count("no-new-bytes", claim_size)
        return None
    concrete = concrete_bytes(relocs, claim_size)
    if concrete < B.MIN_LIB_CONCRETE:
        report.thin(rva, instance, claim_size, concrete)
        return None
    for i in range(offset, offset + claim_size):
        claimed[i] = 1
    return {"rva": rva, "size": claim_size, "new": new_bytes, "owner": owner,
            "source": source, "legal": legal, "symbol": instance.symbol,
            "member": instance.member, "tag": instance.tag,
            "dump_row": dump["name"] if dump else "", "concrete": concrete,
            "callees_ok": corroborated, "bases_ok": based,
            "dir32": dir32_assertions(rva, claim_size, instance, image)}


# --------------------------------------------------------------------------
# reporting
# --------------------------------------------------------------------------

class Report:
    def __init__(self):
        self.warnings, self.notes = [], []
        self.counts, self.bytes = Counter(), Counter()
        self.oversub = Counter()
        self.disagreements, self.thins = [], []
        # How much of the standard's weight each accepted class actually
        # carries: a class with one in-window placement needs no ordering
        # premise at all, and a class an attached row anchors has had it tested.
        self.classes = Counter()
        self.callee_misses = []
        self.dir32_misses, self.dir32_conflicts = [], []

    def warn(self, text):
        self.warnings.append(text)

    def note(self, text):
        self.notes.append(text)
        print(text)

    def count(self, reason, size):
        self.counts[reason] += 1
        self.bytes[reason] += size

    def oversubscribed(self, size, hits, supply):
        self.oversub["classes"] += 1
        self.oversub["bytes"] += size * (hits - supply)
        self.count("oversubscribed", size * hits)

    def witness(self, in_window, anchors):
        if in_window == 1:
            self.classes["single placement (no ordering premise used)"] += 1
        elif anchors:
            self.classes["multi, ordering confirmed by an attached row"] += 1
        else:
            self.classes["multi, ordering unwitnessed"] += 1

    def callee_miss(self, rva, instance, contradicted):
        self.callee_misses.append((rva, instance.member, instance.symbol, contradicted))

    def dir32_miss(self, rva, instance, disputed):
        self.dir32_misses.append((rva, instance.member, instance.symbol, disputed))

    def dir32_conflict(self, row, blamed):
        self.dir32_conflicts.append((row["rva"], row["member"], row["symbol"], blamed))
        self.count("dir32-base-conflicts-within-wave", row["size"])

    def disagreement(self, source, member, symbol, held_rva, assigned_rva):
        self.disagreements.append((source, member, symbol, held_rva, assigned_rva))

    def thin(self, rva, instance, size, concrete):
        self.thins.append((rva, instance.member, instance.symbol, size, concrete))
        self.count("thin-masked-comparison", size)


def print_report(rows, report):
    score, counts = Counter(), Counter()
    for row in rows:
        score[(row["owner"], row["legal"])] += row["new"]
        counts[(row["owner"], row["legal"])] += 1
    print("\n=== claimable placements, count-agreement standard ===")
    for key in sorted(score, key=lambda k: (k[0], LEGAL_ORDER.index(k[1]))):
        print(f"  {key[0]:<14} {key[1]:<15} {score[key]:>9,}B  {counts[key]:>5} rows")
    totals, row_totals = Counter(), Counter()
    for key, value in score.items():
        totals[key[1]] += value
        row_totals[key[1]] += counts[key]
    print()
    for legal in LEGAL_ORDER:
        if legal in totals:
            print(f"  TOTAL {legal:<15} {totals[legal]:>9,}B  {row_totals[legal]:>5} rows")
    print(f"  GRAND TOTAL {sum(totals.values()):,}B over {len(rows):,} rows")
    lone = [r for r in rows if r["placements"] == 1]
    anchored = [r for r in rows if r["placements"] > 1 and r["anchors"]]
    bare = [r for r in rows if r["placements"] > 1 and not r["anchors"]]
    print(f"  of which sole in-window placement of its body: {len(lone):,} rows, "
          f"{sum(r['new'] for r in lone):,}B")
    print(f"           multi-placement, an attached row anchors the order: "
          f"{len(anchored):,} rows, {sum(r['new'] for r in anchored):,}B")
    print(f"           multi-placement, order unwitnessed: {len(bare):,} rows, "
          f"{sum(r['new'] for r in bare):,}B")
    calls = [r for r in rows if r["callees_ok"]]
    print(f"  rows whose own calls land on the callee the archive names: {len(calls):,}, "
          f"{sum(r['new'] for r in calls):,}B")
    based = [r for r in rows if r.get("bases_ok")]
    print(f"  rows resolving a global to the base an attached row pins: {len(based):,}, "
          f"{sum(r['new'] for r in based):,}B")
    twins = [r for r in rows if len(r.get("candidates", ())) > 1]
    print(f"  rows whose SYMBOL another identical body could equally own "
          f"(named ?<lib>_twin_<rva>): {len(twins):,}, {sum(r['new'] for r in twins):,}B")
    if report.classes:
        print("\n=== how much each accepted class leans on archive order ===")
        for label, count in sorted(report.classes.items()):
            print(f"  {label:<48} {count:>5} class(es)")
    if report.counts:
        print("\n=== refused ===")
        for reason, count in sorted(report.counts.items(), key=lambda kv: -kv[1]):
            print(f"  {reason:<28} {count:>6} placement(s)  {report.bytes[reason]:>10,}B")
    if report.oversub["classes"]:
        print(f"  oversubscribed classes: {report.oversub['classes']} "
              f"({report.oversub['bytes']:,}B of surplus retail copies)")
    for text in report.warnings:
        print(f"  WARN {text}")
    if report.disagreements:
        print("\n=== archive-order assignment DISAGREES with the ledger ===")
        for source, member, symbol, held, assigned in report.disagreements[:20]:
            print(f"  {member} {symbol[:60]}: ledger 0x{held:08X}, order-assignment "
                  f"0x{assigned:08X}")
        print(f"  {len(report.disagreements)} disagreement(s) — every one is a placement "
              "this standard would have got wrong, or a row that was.")
    else:
        print("\narchive-order assignment agrees with every attached row it re-derives")
    if report.callee_misses:
        print(f"\n=== {len(report.callee_misses)} placement(s) refused: a call goes somewhere "
              "the named callee is not ===")
        for rva, member, symbol, misses in report.callee_misses[:15]:
            offset, name, destination = misses[0]
            where = f"0x{destination:08X}" if destination is not None else "(truncated)"
            print(f"  0x{rva:08X} {member} {symbol[:46]}: +{offset} calls {where}, "
                  f"which is not {name[:46]}")
    if report.dir32_misses:
        print(f"\n=== {len(report.dir32_misses)} placement(s) refused: a global resolves "
              "somewhere an attached row says it is not ===")
        for rva, member, symbol, disputed in report.dir32_misses[:15]:
            offset, name, base = disputed[0]
            print(f"  0x{rva:08X} {member} {symbol[:46]}: +{offset} puts {name[:46]} "
                  f"at 0x{base:08X}")
    if report.dir32_conflicts:
        print(f"\n=== {len(report.dir32_conflicts)} placement(s) refused: this wave's own "
              "rows resolve one symbol two ways ===")
        for rva, member, symbol, blamed in report.dir32_conflicts[:15]:
            print(f"  0x{rva:08X} {member} {symbol[:46]}: {blamed[0]}")
    if report.thins:
        print(f"\n{len(report.thins)} placement(s) dropped: fewer than "
              f"{B.MIN_LIB_CONCRETE} bytes outside a relocation slot")


# --------------------------------------------------------------------------
# emission
# --------------------------------------------------------------------------

def row_names(rows, ledger, tracked, report):
    """Assign each row a name unique in the wave AND in functions.csv.

    A symbol shared by two members is the common case here (the jpeg decoders
    d3dx9 links twice, the SSE float16 pair). The ledger cannot hold one name at
    two RVAs, so a twin gets `<symbol>$<member stem>` and an `object-symbol=`
    note pointing the gate back at the real COFF symbol — the shape the eight
    twins already in the ledger use. That name still says something true: both
    candidates ARE that function, compiled into two objects.

    A row whose `candidates` name more than one SYMBOL is the other case, and it
    gets no mangled name at all. Ascending order chose among masked-identical
    bodies that survive every test the standard applies, so a real name here
    asserts an identity the image does not witness — the phase-2 failure mode,
    where a name index built off the name column resolved 17 symbols to wrong
    addresses. `object-symbol=` still names the COMDAT whose bytes these are, so
    the gate verifies exactly as before and the byte claim is untouched.
    """
    occurrences = Counter(row["symbol"] for row in rows)
    used, named, refused = set(ledger.names), [], []
    for row in rows:
        if row["source"] is None or row["source"] not in tracked:
            refused.append((row, f"no tracked ledger source for archive tag {row['tag']}"))
            continue
        symbol = row["symbol"]
        candidates = row.get("candidates") or [symbol]
        if len(candidates) > 1:
            name = twin_name(row)
        else:
            alias = occurrences[symbol] > 1 or symbol in used
            name = symbol
            if alias:
                stem = re.sub(r"\.obj$", "", row["member"], flags=re.I)
                name = f"{symbol}${stem}"
            suffix = 1
            while name in used:
                suffix += 1
                stem = re.sub(r"\.obj$", "", row["member"], flags=re.I)
                name = f"{symbol}${stem}#{suffix}"
        if any(char in name for char in ',"\r\n'):
            refused.append((row, f"symbol carries a CSV-hostile character: {symbol!r}"))
            continue
        used.add(name)
        notes = f"vendored={vendor_tag(row['source'])};member={row['member']}"
        if name != symbol:
            notes += f";object-symbol={symbol}"
        if len(candidates) > 1:
            notes += (f";lib-twin={len(candidates)} masked-identical archive bodies could sit "
                      "at this address and nothing in the image separates them, so this name "
                      "asserts none of them")
        named.append(dict(row, name=name, notes=notes))
    for row, reason in refused:
        report.warn(f"0x{row['rva']:08X} {row['symbol'][:60]}: {reason}")
    return named, refused


def twin_name(row):
    """A ledger name for bytes whose SYMBOL the evidence does not pin.

    Mangled-looking so it reads as a symbol and sorts with them, address-keyed
    so it is unique by construction, and carrying no `gen-` marker: these rows
    are real library bodies byte-verified against a real archive member, not
    generated placeholders, and progress.py routes anything with a `gen-` note
    into the generated lane.
    """
    return f"?{row['owner']}_twin_{row['rva']:08x}@@YAXXZ"


def vendor_tag(source):
    """The `vendored=` value a row on this archive carries."""
    stem = Path(source).stem
    return {"d3dx9": "d3dx9-summer2003", "dxerr9": "dxerr9-summer2003",
            "comsupp": "comsupp-vs2003"}.get(stem, f"{stem}-vs2003")


def write_wave(path, rows):
    with Path(path).open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["name", "rva", "size", "source", "notes"],
                                lineterminator="\n")
        writer.writeheader()
        for row in rows:
            writer.writerow({"name": row["name"], "rva": f"0x{row['rva']:08X}",
                             "size": row["size"], "source": row["source"],
                             "notes": row["notes"]})


def write_detail(path, rows):
    columns = ["rva", "size", "new", "owner", "legal", "tag", "member", "symbol",
               "dump_row", "concrete", "callees_ok", "bases_ok", "placements", "instances",
               "anchors", "candidates", "name", "notes", "source"]
    with Path(path).open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, columns, lineterminator="\n", extrasaction="ignore")
        writer.writeheader()
        for row in rows:
            writer.writerow(dict(row, rva=f"0x{row['rva']:08X}",
                                 candidates="|".join(row.get("candidates", ()))))


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--report", action="store_true", help="print the score table")
    parser.add_argument("--ledger-ref", help="read functions.csv from this git ref instead of "
                        "the worktree, to re-derive a wave that has already landed")
    parser.add_argument("--emit",
                        help="write the wave CSV here (a worklist only: the lander "
                             "that consumed it was retired with the generators)")
    parser.add_argument("--detail", help="write the full per-placement CSV here")
    parser.add_argument("--legal", default="dump-exact,dump-padded,pure-unclaimed",
                        help="comma-separated legality classes to emit")
    parser.add_argument("--owner", help="restrict emission to one archive tag")
    parser.add_argument("--limit", type=int, help="emit at most this many rows")
    parser.add_argument("--offset", type=int, default=0, help="skip this many emittable rows")
    args = parser.parse_args(argv)

    report = Report()
    try:
        rows, ledger, tracked = sweep(report, args.ledger_ref)
    except SweepError as exc:
        raise SystemExit(f"lib_window_sweep: {exc}")
    rows.sort(key=lambda row: row["rva"])
    named, refused = row_names(rows, ledger, tracked, report)
    if args.report or not (args.emit or args.detail):
        print_report(named, report)
    if args.detail:
        write_detail(args.detail, named)
        print(f"wrote {args.detail} ({len(named)} placement(s))")
    if args.emit:
        wanted = {c.strip() for c in args.legal.split(",") if c.strip()}
        unknown = wanted - set(LEGAL_ORDER)
        if unknown:
            raise SystemExit(f"lib_window_sweep: unknown legality class(es) "
                             f"{', '.join(sorted(unknown))}; known: {', '.join(LEGAL_ORDER)}")
        emit = [r for r in named if r["legal"] in wanted
                and (args.owner is None or r["owner"] == args.owner)]
        emit = emit[args.offset:]
        if args.limit is not None:
            emit = emit[:args.limit]
        if not emit:
            raise SystemExit("lib_window_sweep: no rows to emit under those filters — "
                             "nothing was written")
        write_wave(args.emit, emit)
        print(f"wrote {args.emit}: {len(emit)} row(s), {sum(r['size'] for r in emit):,}B "
              f"({Counter(r['legal'] for r in emit).most_common()})")
    if refused:
        print(f"\n{len(refused)} placement(s) refused emission — see WARN lines above",
              file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
