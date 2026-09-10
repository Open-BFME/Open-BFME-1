#!/usr/bin/env python3
"""Byte-true C++ for the MSVC unwind funclets retail left unclaimed.

Six funclet templates carry both a frame reference and a callee that can be
read straight out of the retail bytes, so an anonymous C++ body reproduces them
exactly:

  A  lea ecx,[ebp-D]; jmp <dtor>                       a local object
  B  lea ecx,[ebp+D]; jmp <dtor>                       a by-value class parameter
  C  mov eax,[ebp-D]; push eax; call <op delete>;      the block a throwing
     pop ecx; ret                                      new-expression allocated
  M  mov ecx,[ebp-D]; add ecx,K; jmp <dtor>            a member subobject at
                                                       offset K of the object
                                                       being constructed
  S  push N; mov eax,[ebp-D]; push eax;                the same block, freed
     call <op delete>; add esp,8; ret                  through a class-scoped
                                                       SIZED operator delete
  P  mov eax,[ebp+A]; push eax; mov ecx,[ebp-D];       the block a throwing
     push ecx; call <op delete>; add esp,8; ret        PLACEMENT new-expression
                                                       allocated, with the
                                                       placement argument from A
  K  push <address>; mov eax,[ebp-D]; push eax;        the same placement block,
     call <op delete>; add esp,8; ret                  with the placement
                                                       argument a CONSTANT
                                                       address rather than a
                                                       frame slot

Each takes an int8 displacement while the slot is within 128 bytes of EBP and an
int32 one past that; the C++ is identical either way, so one emitter covers both
encodings. Every frame slot is reached the same way: the object starts at
EBP-0x10 and a leading `char pad[N]` walks it down.

The payloads are anonymous by design: they reproduce a frame slot and a call,
never a class identity, and every callee address comes from the retail bytes.

These funclets have no name of their own, so each ledger row is anchored to the
compiler-local `$L` label its body landed on.  Those numbers are assigned per
translation unit and shift whenever anything ahead of them changes, so this
generator OWNS `Code/gen_small/uw_gen_NNN.cpp` and every ledger row that cites
one: each run rewrites all of them and re-derives every label from a fresh
compile.  Hand-editing a landed file renumbers the labels and breaks rows whose
funclet is byte-for-byte untouched -- regenerate instead of editing, and let the
generator grow into a new file rather than appending to a landed one.

Unlike the 1,366 `gen-funclet` rows that sit on a reconstructed parent's object,
these funclets have no knowable parent: an `Unwind@`/`Catch@` name encodes the
funclet's own virtual address, and being unclaimed is what put them here.  Rows
therefore carry no `parent=` field, and nothing here guesses one from adjacency.

Usage:
  python3 tools/gen_uw.py classify   # measure the population; writes nothing
  python3 tools/gen_uw.py land       # regenerate every owned source and row
"""
import argparse
import bisect
import collections
import csv
import functools
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build      # noqa: E402
import gen_small  # noqa: E402
import harvest    # noqa: E402
import ledger_io  # noqa: E402
from add_match import parse_ledger  # noqa: E402
from portable_lock import lock      # noqa: E402

FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
DELETED = ROOT / "reverse" / "deleted_rows.csv"
GHIDRA = ROOT / "reverse" / "ghidra_functions.csv"
SOURCE_DIR = ROOT / "Code" / "gen_small"
OWNED_SOURCE_DIR = "Code/gen_small/uw_gen_"
# The lock add_match.py and gen_small.land_batch take. land() rewrites rows
# rather than appending them, so a single-row append interleaving with it would
# be erased by the rewrite -- or, worse, by the revert.
LOCK_FILE = ROOT / "reverse" / ".add_match.lock"

# Everything the generator owns is recognised by these two markers alone.
ROW_NOTES = "gen-funclet;object-symbol="
OWNED_ROW_RE = re.compile((r",Code/gen_small/uw_gen_\d{3}\.cpp,matched,"
                           + re.escape(ROW_NOTES)).encode("utf-8"))
PIN_MARKER = "gen-uw-pin"
PIN_NOTE = PIN_MARKER + " dtor target read from the retail funclet bytes"
PIN_NOTE_BYTES = PIN_NOTE.encode("utf-8")

DELETE_NAME = "??3@YAXPAX@Z"
ROWS_PER_FILE = 1200

# The funclet kinds this revision emits. A kind goes in here only once a probe
# compile has reproduced its retail bytes at the extremes of the frame
# displacements and member offsets the pool actually asks for, and the commit
# that adds one lands nothing else -- so a full gate that goes red names the
# shape that did it.
LANDING = ("A", "B", "C", "M", "S", "P", "K")


@functools.lru_cache(maxsize=1)
def image_span():
    """(first, last+1) virtual address the retail image occupies."""
    data, sections = build.exe_image()
    base = build.u32(data, build.u32(data, 0x3C) + 24 + 28)
    return base, base + max(s["rva"] + s["size"] for s in sections)


def in_image(value):
    base, end = image_span()
    return base <= value < end


def delete_kind(pushed):
    """"S" when a two-argument delete's second argument is a class size, "K"
    when it is the address of a retail object.

    Both templates are `push <imm32>; push <block>; call <op delete>;
    add esp,8; ret`, so the immediate is the only thing that tells them apart,
    and reading every immediate as a size published 19 funclets as class-scoped
    sized deletes of classes 19,968,608 bytes and up. They are not sizes: read
    as virtual addresses they land in .data at 104-byte strides, all 19 call one
    address whose body is a lone `ret`, and 253 placement-delete rows already
    name that same address ??3@YAXPAXPAUGen_uwt_0002aaa9@@@Z -- one function
    cannot be the class-scoped operator delete of nineteen different classes.
    An immediate that is a valid address in this image is an address.
    """
    return "K" if in_image(pushed) else "S"


def source_name(index):
    return "Code/gen_small/uw_gen_%03d.cpp" % index


def rel32(body, offset, rva):
    return rva + offset + 5 + struct.unpack_from("<i", body, offset + 1)[0]


def disp8(value):
    return value - 256 if value > 127 else value


class Ledger:
    """The ledger rows and pins this generator does not own, plus the lookups
    that decide which funclets are still up for grabs.

    Everything owned is excluded from those lookups: a second run must see the
    same population as the first, and our own rows would otherwise mark their
    own funclets as claimed and their own pins as prior identity.
    """

    def __init__(self):
        self.claimed = {}          # rva -> name, from identity-bearing rows we do not own
        self.dumps = {}            # rva -> size, from gen-dump rows: bytes, no identity
        self.owned = {}            # (name, rva) -> source, the rows this run replaces
        self.named = set()         # (name, address) pairs from rows we do not own
        self.addresses = set()     # byte-proved or explicitly pinned addresses
        self.pinned = set()        # addresses symbols.csv already carries a name for
        self.declined = {}         # rva -> why read_funclets left this funclet behind
        matched = []
        with FUNCTIONS.open(encoding="utf-8", errors="replace", newline="") as handle:
            for row in csv.DictReader(handle):
                try:
                    rva = int(row["target_rva"], 16)
                    size = int(row["target_size"] or 0)
                except ValueError:
                    continue
                if row["source"] and OWNED_SOURCE_DIR in row["source"]:
                    self.owned[(row["name"], rva)] = row["source"]
                    continue
                if row["status"] != "matched":
                    self.claimed[rva] = row["name"]
                    continue
                self.addresses.add(rva)
                self.named.add((row["name"], rva))
                # A gen-dump row is retail's own bytes under a synthetic name: it
                # proves the boundary (so it still answers `addresses`) and claims
                # no identity, so a funclet body over the SAME range supersedes it
                # instead of colliding with it. Anything else on those bytes is an
                # identity and stays untouchable.
                if build.is_scaffold_row(row):
                    self.dumps[rva] = size
                    continue
                self.claimed[rva] = row["name"]
                matched.append((rva, rva + size))
        with SYMBOLS.open(encoding="utf-8", errors="replace", newline="") as handle:
            for row in csv.DictReader(handle):
                if (row.get("notes") or "").startswith(PIN_MARKER):
                    continue
                try:
                    address = int(row["address"], 16)
                except ValueError:
                    continue
                self.addresses.add(address)
                self.pinned.add(address)
                self.named.add((row["name"], address))

        self.tombstoned = {}
        for line in DELETED.read_text(encoding="utf-8").splitlines():
            if line.startswith(("#", "name,")) or not line.strip():
                continue
            row = next(csv.reader([line]))
            if len(row) >= 2:
                self.tombstoned[(row[0], int(row[1], 16))] = row[2] if len(row) > 2 else ""

        self.merged = []
        for start, end in sorted(matched):
            if self.merged and start <= self.merged[-1][1]:
                self.merged[-1] = (self.merged[-1][0], max(self.merged[-1][1], end))
            else:
                self.merged.append((start, end))
        self.starts = [start for start, _ in self.merged]

    def overlaps(self, rva, size):
        """True when [rva, rva+size) touches any byte another matched row owns.

        Full containment is the common case, but a partial overlap would land a
        row check_csv rejects, so the weaker test is not enough.
        """
        index = bisect.bisect_right(self.starts, rva) - 1
        if index >= 0 and self.merged[index][1] > rva:
            return True
        return bisect.bisect_right(self.starts, rva + size - 1) - 1 > index

    def resolves(self, name, address):
        """True when the REL32 resolver would already reach `address` under
        `name` -- which is what a pin has to add, and is not the same question
        as whether the address carries some other name."""
        return (name, address) in self.named


# `extra` is the template's second dimension: the member offset for M, the
# block size for S, the placement argument's frame slot for P, 0 for A/B/C.
Funclet = collections.namedtuple("Funclet", "kind rva size disp target extra")
Unit = collections.namedtuple("Unit", "kind target rows shape")


def disp32(body, offset):
    return struct.unpack_from("<i", body, offset)[0]


def imm32(body, offset):
    """A pushed 32-bit operand, unsigned: it is a size or an address, never a
    displacement, and reading 0x8xxxxxxx as negative would hide both."""
    return struct.unpack_from("<I", body, offset)[0]


ADD8_RET = b"\x83\xc4\x08\xc3"


def classify(rva, body):
    """(kind, disp, target, extra) for the shapes this generator emits.

    Each row is one MSVC unwind template and both encodings of its frame
    reference: an int8 displacement while the slot is within 128 bytes of EBP,
    an int32 one past that.  The disp32 twin is the SAME C++ -- a bigger frame is
    all that separates them -- which is why one emitter covers both.

      A/B  8d 4d D / 8d 8d D32   lea ecx,[ebp+D]; jmp dtor
                                 a local object (D<0) or a by-value parameter (D>0)
      C    8b 45 D / 8b 85 D32   mov eax,[ebp+D]; push eax; call op-delete; pop ecx; ret
                                 the block a throwing new-expression allocated
      M    8b 4d D / 8b 8d D32   mov ecx,[ebp+D]; [add ecx,K;] jmp dtor
                                 a member subobject at offset K of the object
                                 whose `this` the parent spilled at D; K==0 folds
                                 the add away, K<128 takes 83 C1, else 81 C1.
      S    6a N / 68 N32         push sizeof; mov eax,[ebp+D]; push eax;
                                 call op-delete; add esp,8; ret -- the same block
                                 as C, freed through a class-scoped SIZED
                                 operator delete, so the size is in the bytes
      K    68 A32                 the same bytes as S, but the pushed immediate
                                 is an ADDRESS in this image, not a size: a
                                 placement new-expression whose tag argument is
                                 a compile-time constant. delete_kind decides.
      P    8b 45 A ... 8b 4d D   mov eax,[ebp+A]; push eax; mov ecx,[ebp+D];
                                 push ecx; call op-delete; add esp,8; ret -- the
                                 block a throwing PLACEMENT new-expression
                                 allocated, freed through the two-argument
                                 operator delete with the placement argument
                                 from slot A
    """
    size = len(body)
    if size == 8 and body[0] == 0x8D and body[1] == 0x4D and body[3] == 0xE9:
        disp = disp8(body[2])
        return ("A" if disp < 0 else "B"), disp, rel32(body, 3, rva), 0
    if size == 11 and body[0] == 0x8D and body[1] == 0x8D and body[6] == 0xE9:
        disp = disp32(body, 2)
        return ("A" if disp < 0 else "B"), disp, rel32(body, 6, rva), 0
    if (size == 11 and body[0] == 0x8B and body[1] == 0x45 and body[3] == 0x50
            and body[4] == 0xE8 and body[9] == 0x59 and body[10] == 0xC3):
        return "C", disp8(body[2]), rel32(body, 4, rva), 0
    if (size == 14 and body[0] == 0x8B and body[1] == 0x85 and body[6] == 0x50
            and body[7] == 0xE8 and body[12] == 0x59 and body[13] == 0xC3):
        return "C", disp32(body, 2), rel32(body, 7, rva), 0
    if size == 8 and body[0] == 0x8B and body[1] == 0x4D and body[3] == 0xE9:
        return "M", disp8(body[2]), rel32(body, 3, rva), 0
    if size == 11 and body[0] == 0x8B and body[1] == 0x8D and body[6] == 0xE9:
        return "M", disp32(body, 2), rel32(body, 6, rva), 0
    if (size == 11 and body[0] == 0x8B and body[1] == 0x4D and body[3] == 0x83
            and body[4] == 0xC1 and body[6] == 0xE9):
        return "M", disp8(body[2]), rel32(body, 6, rva), disp8(body[5])
    if (size == 14 and body[0] == 0x8B and body[1] == 0x4D and body[3] == 0x81
            and body[4] == 0xC1 and body[9] == 0xE9):
        return "M", disp8(body[2]), rel32(body, 9, rva), disp32(body, 5)
    if (size == 14 and body[0] == 0x8B and body[1] == 0x8D and body[6] == 0x83
            and body[7] == 0xC1 and body[9] == 0xE9):
        return "M", disp32(body, 2), rel32(body, 9, rva), disp8(body[8])
    if (size == 17 and body[0] == 0x8B and body[1] == 0x8D and body[6] == 0x81
            and body[7] == 0xC1 and body[12] == 0xE9):
        return "M", disp32(body, 2), rel32(body, 12, rva), disp32(body, 8)
    # The sized and placement deletes both end `add esp,8; ret` because both push
    # two arguments; what differs is whether the second one is an immediate size
    # or a second frame slot.
    if (size == 15 and body[0] == 0x6A and body[2] == 0x8B and body[3] == 0x45
            and body[5] == 0x50 and body[6] == 0xE8 and body[11:15] == ADD8_RET):
        return "S", disp8(body[4]), rel32(body, 6, rva), body[1]
    if (size == 18 and body[0] == 0x68 and body[5] == 0x8B and body[6] == 0x45
            and body[8] == 0x50 and body[9] == 0xE8 and body[14:18] == ADD8_RET):
        pushed = imm32(body, 1)
        return delete_kind(pushed), disp8(body[7]), rel32(body, 9, rva), pushed
    if (size == 18 and body[0] == 0x6A and body[2] == 0x8B and body[3] == 0x85
            and body[8] == 0x50 and body[9] == 0xE8 and body[14:18] == ADD8_RET):
        return "S", disp32(body, 4), rel32(body, 9, rva), body[1]
    if (size == 21 and body[0] == 0x68 and body[5] == 0x8B and body[6] == 0x85
            and body[11] == 0x50 and body[12] == 0xE8 and body[17:21] == ADD8_RET):
        pushed = imm32(body, 1)
        return delete_kind(pushed), disp32(body, 7), rel32(body, 12, rva), pushed
    if (size == 17 and body[0] == 0x8B and body[1] == 0x45 and body[3] == 0x50
            and body[4] == 0x8B and body[5] == 0x4D and body[7] == 0x51
            and body[8] == 0xE8 and body[13:17] == ADD8_RET):
        return "P", disp8(body[6]), rel32(body, 8, rva), disp8(body[2])
    return None, None, None, None


def read_funclets(ledger):
    """Every unclaimed named EH funclet, classified, with the ladder split out.

    Returns (on_ladder, off_ladder, tally, tally_bytes); the tallies count the
    whole population per class for the classify report.  A funclet is on the
    ladder when its displacement is a slot this generator can place in a frame.

    `ledger.declined` collects, per address, why every funclet that did not make
    it onto the ladder was left behind.  That is not a report: it is the reason
    column of the tombstone a previously-landed row gets when it drops out.
    """
    data = build.EXE.read_bytes()
    on_ladder, off_ladder = [], []
    tally = collections.Counter()
    tally_bytes = collections.Counter()
    ledger.declined = {}
    with GHIDRA.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if not row["name"].startswith(("Unwind@", "Catch@")):
                continue
            rva, size = int(row["rva"], 16), int(row["size"])
            if ledger.overlaps(rva, size):
                ledger.declined[rva] = ("0x%08X is claimed by another matched row"
                                        % rva)
                continue
            dump = ledger.dumps.get(rva)
            if dump is not None and dump != size:
                ledger.declined[rva] = (
                    "the gen-dump row at 0x%08X is %d bytes and Ghidra calls the "
                    "funclet %d -- the boundary itself is in dispute" % (rva, dump, size))
                continue
            body = data[rva:rva + size]
            kind, disp, target, extra = classify(rva, body)
            if kind is None:
                tally["D other"] += 1
                tally_bytes["D other"] += size
                ledger.declined[rva] = (
                    "the %d retail bytes at 0x%08X (%s...) match no funclet shape this "
                    "generator emits" % (size, rva, body[:6].hex()))
                continue
            label = "%s target-%s" % (kind, "known" if target in ledger.addresses else "UNKNOWN")
            tally[label] += 1
            tally_bytes[label] += size
            if target not in ledger.addresses:
                ledger.declined[rva] = (
                    "the destructor target 0x%08X this funclet jumps to is not a proven "
                    "boundary, so no pin can name it" % target)
                continue
            funclet = Funclet(kind, rva, size, disp, target, extra)
            if on_the_ladder(funclet):
                on_ladder.append(funclet)
            else:
                off_ladder.append(funclet)
                ledger.declined[rva] = unreachable(funclet)
    return on_ladder, off_ladder, tally, tally_bytes


def on_the_ladder(funclet):
    return unreachable(funclet) is None


def unreachable(funclet):
    """Why this generator cannot place the funclet's frame slot, or None.

    Everything reachable is reachable the same way: the frame that holds the
    object starts at EBP-0x10 and a leading `char pad[N]` walks it down four
    bytes at a time, so a slot is placeable exactly when it is 0x10 or more
    below EBP and 4-byte aligned.  A by-value parameter counts up from EBP+4
    instead.  A member offset is a struct field, so it too must be non-negative
    and 4-byte aligned -- `char q[K]` before it is what puts it there.
    """
    if funclet.kind not in LANDING:
        return ("the %s template is recognised but not yet emitted: no probe compile "
                "has reproduced it" % funclet.kind)
    if funclet.kind == "B":
        if funclet.disp < 4 or funclet.disp % 4:
            return ("frame displacement %d is not a by-value parameter slot: they "
                    "start at EBP+4 and step by 4" % funclet.disp)
        return None
    if funclet.disp > -0x10 or (-funclet.disp - 0x10) % 4:
        return ("frame displacement %d is not a local slot: they start at EBP-0x10 "
                "and step down by 4" % funclet.disp)
    if funclet.kind == "M":
        if funclet.extra < 0 or funclet.extra % 4:
            return ("member offset %d is not a 4-byte-aligned field offset a struct "
                    "layout can produce" % funclet.extra)
        return None
    if funclet.kind == "S":
        if funclet.extra < 1:
            return "a sized delete of %d bytes is not a class size" % funclet.extra
    if funclet.kind == "P":
        if funclet.extra < 4 or funclet.extra % 4:
            return ("the placement argument at %d is not a parameter slot: this "
                    "generator can only pass it as a parameter, and those start at "
                    "EBP+4 and step by 4" % funclet.extra)
    if funclet.kind in ("S", "P", "K") and pad_of(funclet) == 4:
        # The one slot no pad reaches: `char pad[4]` fills a gap the frame
        # already had. C escapes it with a second new-expression live at the same
        # time (emit_new), but that second expression is what supplies the
        # callee, and neither delete template survives being given another one.
        return ("EBP-0x14 is the spare slot the frame already has, so no pad "
                "moves the block there")
    return None


def pad_of(funclet):
    """Bytes of leading `char pad[]` that walk EBP-0x10 down to this slot."""
    return -funclet.disp - 0x10


def plan(on_ladder):
    """Group the funclets into the units a translation unit is built from.

    A unit is one emitted C++ entity and the keys it covers:

      local  (target, pad)          one function whose frame puts a Gen_uw_<t>
                                    local exactly `pad` bytes below EBP-0x10
      param  (target, count)        one function taking `count` by-value
                                    Gen_uw_<t> parameters, covering EBP+4..+4n
      new    (pad)                  one throwing new-expression at that slot
      member (target, pad, offsets) one host struct whose out-of-line constructor
                                    spills `this` at that slot and holds a
                                    Gen_uwm_<t> at each offset
      sized  (target, pad, size)    one new-expression for a class of exactly
                                    that size with a sized operator delete
      place  (target, pad, slot)    one placement new-expression whose tag
                                    argument arrives in that parameter slot
      tag    (target, pad, address) one placement new-expression whose tag
                                    argument is that constant address

    Earlier revisions gave each destructor target ONE function and walked its
    locals down a ladder, which is the same layout arithmetic seen from the other
    end.  It does not survive the disp32 twins: reaching EBP-6276 that way costs
    1,565 live locals in a single frame, and one target in this pool wants
    EBP-65556.  A per-slot pad reaches any of them with one object in the frame.
    """
    locals_of = collections.defaultdict(set)     # target -> {pad}
    params_of = collections.defaultdict(set)     # target -> {slot index}
    new_pads = set()
    members_of = collections.defaultdict(set)    # (target, pad) -> {member offset}
    sized, placed = set(), set()                 # (target, pad, size / arg slot)
    tagged = set()                               # (target, pad, tag address)
    rows = collections.Counter()
    for funclet in on_ladder:
        if funclet.kind == "A":
            unit = ("local", funclet.target, pad_of(funclet))
            locals_of[funclet.target].add(pad_of(funclet))
        elif funclet.kind == "B":
            unit = ("param", funclet.target, None)
            params_of[funclet.target].add(funclet.disp // 4 - 1)
        elif funclet.kind == "C":
            unit = ("new", None, pad_of(funclet))
            new_pads.add(pad_of(funclet))
        elif funclet.kind == "M":
            unit = ("member", funclet.target, pad_of(funclet))
            members_of[(funclet.target, pad_of(funclet))].add(funclet.extra)
        elif funclet.kind == "S":
            unit = ("sized", funclet.target, (pad_of(funclet), funclet.extra))
            sized.add((funclet.target, pad_of(funclet), funclet.extra))
        elif funclet.kind == "K":
            unit = ("tag", funclet.target, (pad_of(funclet), funclet.extra))
            tagged.add((funclet.target, pad_of(funclet), funclet.extra))
        else:
            unit = ("place", funclet.target, (pad_of(funclet), funclet.extra))
            placed.add((funclet.target, pad_of(funclet), funclet.extra))
        rows[unit] += 1

    units = []
    for target in sorted(locals_of):
        for pad in sorted(locals_of[target]):
            units.append(Unit("local", target, rows[("local", target, pad)], (pad,)))
    for target in sorted(params_of):
        units.append(Unit("param", target, rows[("param", target, None)],
                          (max(params_of[target]) + 1,)))
    for pad in sorted(new_pads):
        units.append(Unit("new", None, rows[("new", None, pad)], (pad,)))
    for target, pad in sorted(members_of):
        units.append(Unit("member", target, rows[("member", target, pad)],
                          (pad, tuple(sorted(members_of[(target, pad)])))))
    for target, pad, size in sorted(sized):
        units.append(Unit("sized", target, rows[("sized", target, (pad, size))],
                          (pad, size)))
    for target, pad, slot in sorted(placed):
        units.append(Unit("place", target, rows[("place", target, (pad, slot))],
                          (pad, slot)))
    for target, pad, address in sorted(tagged):
        units.append(Unit("tag", target, rows[("tag", target, (pad, address))],
                          (pad, address)))

    files = [[]]
    count = 0
    for unit in units:
        if files[-1] and count + unit.rows > ROWS_PER_FILE:
            files.append([])
            count = 0
        files[-1].append(unit)
        count += unit.rows
    return files


HEADER = """\
// cl: /DNDEBUG /MD /EHsc
// Generated by: python3 tools/gen_uw.py land
// Do not edit by hand -- regenerate. Every row in this file is anchored to a
// compiler-local $L label, so inserting or removing anything renumbers the
// labels and breaks rows whose funclet bytes never changed.
//
// Each body exists to make MSVC emit one unwind funclet that retail also emits.
// The payloads are anonymous by design -- a frame slot and a destructor call,
// never a class identity -- and every callee address is read out of the retail
// funclet and pinned in reverse/symbols.csv, so the bytes prove the target.

void gen_uw_ext();
void gen_uw_sink(void *);
"""


def unit_keys(unit):
    """Every funclet key one emitted unit is responsible for covering.

    This is the contract the `missing` check enforces: a key claimed here that
    the compiler did not produce stops the run, so no row is ever anchored to a
    label that reproduces something else.
    """
    if unit.kind == "local":
        return [("AB", -(0x10 + unit.shape[0]), unit.target, 0)]
    if unit.kind == "param":
        return [("AB", 4 * (slot + 1), unit.target, 0) for slot in range(unit.shape[0])]
    if unit.kind == "new":
        return [("C", -(0x10 + unit.shape[0]), None, 0)]
    if unit.kind == "sized":
        pad, size = unit.shape
        return [("S", -(0x10 + pad), unit.target, size)]
    if unit.kind == "place":
        pad, slot = unit.shape
        return [("P", -(0x10 + pad), unit.target, slot)]
    if unit.kind == "tag":
        pad, address = unit.shape
        return [("K", -(0x10 + pad), unit.target, address)]
    pad, offsets = unit.shape
    return [("M", -(0x10 + pad), unit.target, offset) for offset in offsets]


NEW_EXPR_TYPES = (
    "// A throwing new-expression leaves its block to be freed from a frame slot,\n"
    "// and padding ahead of it walks that slot down. A 4-byte pad is the\n"
    "// exception: it lands in the spare slot the frame already has and does not\n"
    "// move the temporary, so only a second new-expression that is live at the\n"
    "// same time reaches EBP-0x14.\n"
    "struct Gen_uw_new { int m; Gen_uw_new(int); ~Gen_uw_new(); };\n"
    "struct Gen_uw_new2 { int m; Gen_uw_new2(Gen_uw_new *); ~Gen_uw_new2(); };\n")


def emit_local(target, pad):
    """One frame holding one Gen_uw_<target> at EBP-0x10-pad."""
    if pad == 0:
        body = "\tGen_uw_%08x v; gen_uw_ext();" % target
    elif pad == 4:
        # The same spare slot the new-expressions run into: `char pad[4]` fills a
        # gap the frame already had and leaves the object where it was. A second
        # live object is what actually pushes one down to EBP-0x14.
        body = ("\tGen_uw_%08x v0; gen_uw_ext();\n"
                "\tGen_uw_%08x v1; gen_uw_ext();" % (target, target))
    else:
        body = ("\tchar pad[%d]; gen_uw_sink(pad);\n"
                "\tGen_uw_%08x v; gen_uw_ext();" % (pad, target))
    return "void gen_uw_l%d_%08x()\n{\n%s\n}\n" % (pad, target, body)


def emit_member(target, pad, offsets):
    """One host whose constructor spills `this` at EBP-0x10-pad and holds a
    Gen_uwm_<target> at every offset asked for.

    A member funclet exists only for a member some LATER member's constructor can
    throw past, so the host carries one more Gen_uwm_ after the last offset --
    without it the last offset emits nothing.  `char q[]` fillers put each member
    exactly where retail's `add ecx,K` says it is.

    The constructor is out of line because that is what gives it a frame of its
    own to spill `this` into, and it is the only definition this generator writes
    that no ledger row claims: retail has no such constructor, only the funclets
    it makes MSVC emit.  So it carries the `absent-from-retail` marker
    find_declared_unmatched.py reads -- the honest label, since there is no
    address for a row to point at.
    """
    fields, position = [], 0
    for index, offset in enumerate(offsets):
        if offset > position:
            fields.append("char q%d[%d];" % (index, offset - position))
        fields.append("Gen_uwm_%08x a%d;" % (target, index))
        position = offset + 4
    fields.append("Gen_uwm_%08x z;" % target)
    initialisers = ", ".join("a%d(%d)" % (index, index) for index in range(len(offsets)))
    body = "char pad[%d]; gen_uw_sink(pad);" % pad if pad else ""
    name = "Gen_uwh%d_%08x" % (pad, target)
    return ("struct %s { %s %s(); };\n// ??0%s@@QAE@XZ absent-from-retail\n"
            "%s::%s() : %s, z(0) { %s }\n"
            % (name, " ".join(fields), name, name, name, name, initialisers, body))


def emit_sized(target, pad, size):
    """One new-expression for a class of exactly `size` bytes whose operator
    delete takes the size, so retail's `push sizeof` is `sizeof` and nothing else.

    The class is declared once per (target, size) by emit_source, not here: the
    same pair reaches several frame slots, and a struct definition per slot is a
    redefinition the compiler refuses.
    """
    body = "char p[%d]; gen_uw_sink(p); " % pad if pad else ""
    name = "Gen_uws%d_%08x" % (size, target)
    return ("%s *gen_uw_s%d_%d_%08x() { %sreturn new %s(0); }\n"
            % (name, pad, size, target, body, name))


def emit_place(target, pad, slot):
    """One placement new-expression whose tag argument arrives in parameter
    `slot`, which is what retail's first `mov eax,[ebp+A]` reads.

    The tag type is per target, because the two-argument operator delete is a
    free function and its mangled name is the only thing that distinguishes one
    site's callee from another's.  Earlier parameters exist only to push the tag
    into the right slot; they are handed to gen_uw_sink so nothing folds them
    away.
    """
    count = slot // 4
    args = ", ".join("Gen_uwt_%08x *a%d" % (target, index) for index in range(count))
    unused = "".join("gen_uw_sink(a%d); " % index for index in range(count - 1))
    body = "char p[%d]; gen_uw_sink(p); " % pad if pad else ""
    return ("Gen_uwp_%08x *gen_uw_d%d_%d_%08x(%s)"
            " { %s%sreturn new (a%d) Gen_uwp_%08x(0); }\n"
            % (target, pad, slot, target, args, unused, body, count - 1, target))


def emit_tag(target, pad, address):
    """One placement new-expression whose tag argument is a constant address.

    The same template emit_place writes and the same free two-argument operator
    delete -- only where the tag comes from differs, so the two share one pin
    and one tag type. That is the whole point: reading the pushed address as a
    class size instead minted a Gen_uws<address> class per site and pinned every
    one of them onto the single retail delete they all call.
    """
    body = "char p[%d]; gen_uw_sink(p); " % pad if pad else ""
    return ("Gen_uwp_%08x *gen_uw_k%d_%08x_%08x()"
            " { %sreturn new ((Gen_uwt_%08x *)0x%08X) Gen_uwp_%08x(0); }\n"
            % (target, pad, address, target, body, target, address, target))


def emit_new(pad):
    if pad == 0:
        return "Gen_uw_new *gen_uw_c0() { return new Gen_uw_new(0); }\n"
    if pad == 4:
        return ("Gen_uw_new2 *gen_uw_c4()"
                " { return new Gen_uw_new2(new Gen_uw_new(0)); }\n")
    return ("Gen_uw_new *gen_uw_c%d()"
            " { char p[%d]; gen_uw_sink(p); return new Gen_uw_new(0); }\n" % (pad, pad))


def emit_source(units):
    out = [HEADER]
    ab_targets = sorted({u.target for u in units if u.kind in ("local", "param")})
    m_targets = sorted({u.target for u in units if u.kind == "member"})
    if ab_targets:
        out.append("\n".join("struct Gen_uw_%08x { int m; ~Gen_uw_%08x(); };" % (t, t)
                             for t in ab_targets) + "\n")
    if m_targets:
        # The member type needs a constructor that can throw: a member is only
        # unwound because a later member's constructor threw past it, and a
        # trivially constructed member never produces a funclet at all. That is
        # the whole reason it cannot be the same type the locals use.
        out.append("\n".join(
            "struct Gen_uwm_%08x { int m; Gen_uwm_%08x(int); ~Gen_uwm_%08x(); };"
            % (t, t, t) for t in m_targets) + "\n")
    if any(u.kind == "new" for u in units):
        out.append(NEW_EXPR_TYPES)
    # A sized delete's callee is the class's OWN operator delete, so its mangled
    # name carries the class name and two targets at the same size need two
    # classes to keep their pins apart. One class per (target, size), however
    # many frame slots reach it.
    for target, size in sorted({(u.target, u.shape[1]) for u in units
                                if u.kind == "sized"}):
        out.append("struct Gen_uws%d_%08x { char q[%d]; Gen_uws%d_%08x(int);"
                   " static void operator delete(void *, unsigned int); };\n"
                   % (size, target, size, size, target))
    # A placement site's callee is a FREE two-argument operator delete, so the
    # only thing separating one target's from another's is the tag type in its
    # signature. One tag, one payload and one overload pair per target.
    for target in sorted({u.target for u in units if u.kind in ("place", "tag")}):
        out.append("struct Gen_uwt_%08x;\n"
                   "void *operator new(unsigned int, Gen_uwt_%08x *);\n"
                   "void operator delete(void *, Gen_uwt_%08x *);\n"
                   "struct Gen_uwp_%08x { int m; Gen_uwp_%08x(int); };\n"
                   % (target, target, target, target, target))
    for unit in units:
        if unit.kind == "local":
            out.append(emit_local(unit.target, unit.shape[0]))
        elif unit.kind == "param":
            count = unit.shape[0]
            args = ", ".join("Gen_uw_%08x a%d" % (unit.target, i) for i in range(count))
            out.append("void gen_uw_p%d_%08x(%s) { gen_uw_ext(); }\n"
                       % (count, unit.target, args))
        elif unit.kind == "new":
            out.append(emit_new(unit.shape[0]))
        elif unit.kind == "sized":
            out.append(emit_sized(unit.target, unit.shape[0], unit.shape[1]))
        elif unit.kind == "place":
            out.append(emit_place(unit.target, unit.shape[0], unit.shape[1]))
        elif unit.kind == "tag":
            out.append(emit_tag(unit.target, unit.shape[0], unit.shape[1]))
        else:
            out.append(emit_member(unit.target, unit.shape[0], unit.shape[1]))
    return "\n".join(out)


def compiled_slots(source):
    """Map every funclet the compiler emitted to its $L label.

    Key is what identifies a retail funclet: the shape, its frame displacement,
    and the callee.  The lowest-numbered label wins so the mapping does not move
    when an unrelated unit adds another copy of the same funclet.
    """
    obj = harvest.compile_obj(source, [])
    labels = sorted({s["name"] for s in build.read_object_symbols(obj.read_bytes())
                     if re.fullmatch(r"\$L\d+", s["name"])}, key=lambda n: int(n[2:]))
    slots = {}
    for label in labels:
        body, relocs = build.read_object_symbol_bytes(obj, label)
        calls = {offset: name for offset, rtype, name in relocs if rtype == 0x0014}
        key = emitted_key(body, calls)
        if key is not None:
            slots.setdefault(key, label)
    return slots


# A label's bytes run to the end of its section, so the emitted side is
# recognised by its opcodes alone -- never by its length -- and the callee comes
# from the relocation rather than being guessed from the frame.
#   prefix, opcode offset, opcode, family, callee prefix, callee reloc offset,
#   (member-offset encoding, its offset) or None
EMITTED_SHAPES = (
    (b"\x8d\x4d", 3, 0xE9, "AB", "??1Gen_uw_",   4, None),
    (b"\x8d\x8d", 6, 0xE9, "AB", "??1Gen_uw_",   7, None),
    (b"\x8b\x4d", 3, 0xE9, "M",  "??1Gen_uwm_",  4, None),
    (b"\x8b\x8d", 6, 0xE9, "M",  "??1Gen_uwm_",  7, None),
    (b"\x8b\x4d", 3, 0x83, "M",  "??1Gen_uwm_",  7, ("imm8", 5)),
    (b"\x8b\x4d", 3, 0x81, "M",  "??1Gen_uwm_", 10, ("imm32", 5)),
    (b"\x8b\x8d", 6, 0x83, "M",  "??1Gen_uwm_", 10, ("imm8", 8)),
    (b"\x8b\x8d", 6, 0x81, "M",  "??1Gen_uwm_", 13, ("imm32", 8)),
)
TARGET_IN_NAME = re.compile(r"^\?\?1Gen_uwm?_([0-9a-f]{8})@@QAE@XZ$")
SIZED_DELETE_NAME = re.compile(r"^\?\?3Gen_uws\d+_([0-9a-f]{8})@@SAXPAXI@Z$")
PLACEMENT_DELETE_NAME = re.compile(r"^\?\?3@YAXPAXPAUGen_uwt_([0-9a-f]{8})@@@Z$")


def emitted_target(name, prefix):
    """The retail address encoded in an emitted destructor's own name, or None.

    Gen_uw_new and Gen_uw_new2 share the Gen_uw_ prefix and carry no address, so
    the whole name has to match -- taking eight characters on faith turns those
    two into a ValueError deep inside the label walk.
    """
    match = TARGET_IN_NAME.match(name)
    if match is None or not name.startswith(prefix):
        return None
    return int(match.group(1), 16)


def emitted_key(body, calls):
    """The (family, disp, target, extra) key one emitted funclet covers."""
    if (len(body) >= 11 and body[0] == 0x8B and body[1] == 0x45 and body[3] == 0x50
            and body[4] == 0xE8 and body[9] == 0x59 and body[10] == 0xC3
            and calls.get(5) == DELETE_NAME):
        return ("C", disp8(body[2]), None, 0)
    if (len(body) >= 14 and body[0] == 0x8B and body[1] == 0x85 and body[6] == 0x50
            and body[7] == 0xE8 and body[12] == 0x59 and body[13] == 0xC3
            and calls.get(8) == DELETE_NAME):
        return ("C", disp32(body, 2), None, 0)
    if (len(body) >= 15 and body[0] == 0x6A and body[2] == 0x8B and body[3] == 0x45
            and body[5] == 0x50 and body[6] == 0xE8 and body[11:15] == ADD8_RET):
        match = SIZED_DELETE_NAME.match(calls.get(7, ""))
        if match:
            return ("S", disp8(body[4]), int(match.group(1), 16), body[1])
    if (len(body) >= 18 and body[0] == 0x68 and body[5] == 0x8B and body[6] == 0x45
            and body[8] == 0x50 and body[9] == 0xE8 and body[14:18] == ADD8_RET):
        # Identical bytes to the constant-tag placement delete below; the callee's
        # mangled name is what says which one the compiler emitted.
        match = SIZED_DELETE_NAME.match(calls.get(10, ""))
        if match:
            return ("S", disp8(body[7]), int(match.group(1), 16), imm32(body, 1))
        match = PLACEMENT_DELETE_NAME.match(calls.get(10, ""))
        if match:
            return ("K", disp8(body[7]), int(match.group(1), 16), imm32(body, 1))
    if (len(body) >= 18 and body[0] == 0x6A and body[2] == 0x8B and body[3] == 0x85
            and body[8] == 0x50 and body[9] == 0xE8 and body[14:18] == ADD8_RET):
        match = SIZED_DELETE_NAME.match(calls.get(10, ""))
        if match:
            return ("S", disp32(body, 4), int(match.group(1), 16), body[1])
    if (len(body) >= 21 and body[0] == 0x68 and body[5] == 0x8B and body[6] == 0x85
            and body[11] == 0x50 and body[12] == 0xE8 and body[17:21] == ADD8_RET):
        match = SIZED_DELETE_NAME.match(calls.get(13, ""))
        if match:
            return ("S", disp32(body, 7), int(match.group(1), 16), imm32(body, 1))
        match = PLACEMENT_DELETE_NAME.match(calls.get(13, ""))
        if match:
            return ("K", disp32(body, 7), int(match.group(1), 16), imm32(body, 1))
    if (len(body) >= 17 and body[0] == 0x8B and body[1] == 0x45 and body[3] == 0x50
            and body[4] == 0x8B and body[5] == 0x4D and body[7] == 0x51
            and body[8] == 0xE8 and body[13:17] == ADD8_RET):
        match = PLACEMENT_DELETE_NAME.match(calls.get(9, ""))
        if match:
            return ("P", disp8(body[6]), int(match.group(1), 16), disp8(body[2]))
    for prefix, at, opcode, family, callee, call_at, imm in EMITTED_SHAPES:
        if len(body) <= at or body[:2] != prefix or body[at] != opcode:
            continue
        target = emitted_target(calls.get(call_at, ""), callee)
        if target is None:
            continue
        disp = disp8(body[2]) if prefix[1] in (0x4D, 0x45) else disp32(body, 2)
        offset = 0
        if imm is not None:
            offset = disp8(body[imm[1]]) if imm[0] == "imm8" else disp32(body, imm[1])
        return (family, disp, target, offset)
    return None


def key_of(funclet):
    if funclet.kind == "C":
        # Every emitted new-expression funclet calls ??3@YAXPAX@Z, which is pinned
        # at each operator-delete address the retail funclets reach; the resolver
        # tries the candidates and keeps whichever reproduces retail, so one
        # emitted body serves every target at that slot.
        return ("C", funclet.disp, None, 0)
    if funclet.kind in ("M", "S", "P", "K"):
        return (funclet.kind, funclet.disp, funclet.target, funclet.extra)
    return ("AB", funclet.disp, funclet.target, 0)


def rewrite_lines(path, owned, fresh, newline):
    """Replace the lines this generator owns IN PLACE, leaving every other byte
    alone.

    Splitting on b"\\n" and rejoining reproduces the file exactly, which matters:
    functions.csv carries three shapes of historical line-ending damage that a
    csv round-trip would silently normalise.

    `owned` is asked about the payload with its trailing b"\\r"s removed, never
    the raw split piece.  A predicate that ends in `endswith(note)` matched the
    pins only while they were written LF; the commit that gave symbols.csv its
    real CRLF terminator stopped every one of them being recognised, so each run
    appended 511 pins it believed it had removed.  Nothing caught it because
    land() had no gate -- check_csv says `exact duplicate row` the moment it does.

    The fresh block goes back at the index the old block started at, never at the
    end of the file.  Appending instead relocates every row another session
    appended after the previous land -- 18,689 lines upward, in one hunk that
    changes nothing -- and functions.csv merges with git's UNION driver, which
    keeps both sides' copy of every line that moved.  One re-land plus one
    concurrent append is enough to duplicate those rows on somebody's next
    rebase, and the duplicate reads as a double claim nobody made.  Splicing
    makes a re-land of an unchanged population a byte no-op, which is what makes
    the two-run idempotence check a real regression test.
    """
    lines = path.read_bytes().split(b"\n")
    if lines and lines[-1] == b"":
        lines.pop()
    kept, at = [], None
    for line in lines:
        if owned(line.rstrip(b"\r")):
            if at is None:
                at = len(kept)
            continue
        kept.append(line)
    if at is None:      # first land into this file: the block starts at the end
        at = len(kept)
    kept[at:at] = [text.encode("utf-8") + newline for text in fresh]
    path.write_bytes(b"\n".join(kept) + b"\n")


def owned_sources():
    return sorted(SOURCE_DIR.glob("uw_gen_*.cpp"))


class Snapshot:
    """Byte image of every file land() writes, opened BEFORE the first write.

    A guard that opens at the gate instead of at the first write cannot put back
    what the writes ahead of it did.  deleted_rows.csv is append-only and merges
    by union, so a tombstone stranded against a reverted functions.csv is not a
    cosmetic leftover: it permanently deletes a row that is still landed.
    """

    def __init__(self):
        self.ledgers = {path: path.read_bytes() for path in (FUNCTIONS, SYMBOLS, DELETED)}
        self.sources = {path: path.read_bytes() for path in owned_sources()}
        self.staged = []

    def stage(self, paths):
        """git add the owned sources this run created.

        check_csv rejects a row whose source is not in git -- such a row pushes
        fine from here and breaks every other clone -- so a file the generator
        just wrote has to be in the index before the gate can prove it. Specific
        paths only, never `git add .`.
        """
        for path in paths:
            relative = path.relative_to(ROOT).as_posix()
            if git("ls-files", "--error-unmatch", "--", relative).returncode != 0:
                git("add", "--", relative, check=True)
                self.staged.append(relative)

    def restore(self, reason):
        for path, raw in self.ledgers.items():
            path.write_bytes(raw)
        for path in owned_sources():
            if path not in self.sources:
                path.unlink()
        for path, raw in self.sources.items():
            path.write_bytes(raw)
        for relative in self.staged:
            git("rm", "--cached", "--quiet", "--", relative)
        print("gen_uw: %s -- every ledger row, pin, tombstone and owned source REVERTED"
              % reason, file=sys.stderr)


def git(*args, check=False):
    return subprocess.run(["git", "-C", str(ROOT), *args], check=check,
                          stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


def run(command, label):
    print("gen_uw: %s" % label)
    return subprocess.run(command, cwd=ROOT).returncode


def verify(selectors):
    """The FULL gate, then check_csv. Returns the first non-zero exit code.

    Scoped is not enough here and no argument about runtime changes that.
    build.py's `only` path returns before verify_dir32_consistency and
    verify_noop_patch, and one land() run rewrites 18,689 rows and retracts
    thousands of gen-dump rows -- it changes which sources contribute a DIR32
    placement, which is exactly the question the scoped gate does not ask.  A
    ledger wave proved only by a scoped gate is how origin/master was left red
    with `DIR32 consistency: FAIL 18` and nobody noticed: both hooks run
    './build.sh <sources>' too, so nothing else in the loop asks it either.

    `selectors` is still taken and still names every source this run wrote: a
    red full gate has to be blamed to a file, and that list is the suspect set.
    """
    gate = ([sys.executable, str(ROOT / "tools" / "build.py")]
            if sys.platform == "win32" else [str(ROOT / "build.sh")])
    code = run(gate, "./build.sh (FULL gate; %d owned source(s) written)" % len(selectors))
    if code == 0:
        code = run([sys.executable, str(ROOT / "tools" / "check_csv.py")],
                   "python3 tools/check_csv.py")
    return code


def land():
    # One exclusive lock across derive -> write -> verify, the same lock
    # add_match.py and gen_small.land_batch take. land() REWRITES its rows rather
    # than appending them, so a concurrent single-row append would be erased by
    # the rewrite, or by the revert that follows a red gate.
    lock_handle = LOCK_FILE.open("a")
    lock(lock_handle, exclusive=True,
         wait_notice="gen_uw: waiting for the ledger lock (another append is running)...")

    ledger = Ledger()
    on_ladder, off_ladder, _, _ = read_funclets(ledger)
    for funclet in on_ladder:
        if funclet.rva in ledger.claimed:
            raise SystemExit(
                "0x%08X is already claimed by %s -- a generated row would collide"
                % (funclet.rva, ledger.claimed[funclet.rva]))
    print("on-ladder %d rows / %d B ; off-ladder skipped %d (%s)"
          % (len(on_ladder), sum(f.size for f in on_ladder), len(off_ladder),
             ", ".join("%s=%d" % kv for kv in
                       sorted(collections.Counter(f.kind for f in off_ladder).items()))))

    # Everything from here writes. The snapshot opens first so a failure at any
    # step -- a compile, a mixed symbols.csv, a red gate, a Ctrl-C -- puts all
    # three ledgers and every owned source back byte for byte.
    snapshot = Snapshot()
    try:
        selectors = emit_and_write(ledger, on_ladder, snapshot)
        code = verify(selectors)
    except BaseException:
        snapshot.restore("interrupted")
        raise
    if code != 0:
        snapshot.restore("verification failed (exit %d)" % code)
        raise SystemExit("gen_uw: nothing was changed")
    print("gen_uw: verified OK")


def row_name(rva, tombstoned):
    """This generator's name for the funclet at `rva`, stepped past a tombstone.

    A tombstone retires a NAME at an address for a recorded reason; it does not
    condemn the bytes. 0x00BFD6F0's says a GameState.cpp row anchored to a
    compiler label stopped reproducing after a conversion renumbered the label --
    a verdict on that row, not on this funclet, which the gate byte-proves from a
    generated translation unit either way. Re-using the retired name would leave
    deleted_rows.csv unable to say which row it retired, so the fresh claim takes
    the next name. Resurrecting a tombstoned name is never the answer.
    """
    name = "uw_%08x" % rva
    attempt = 1
    while (name, rva) in tombstoned:
        attempt += 1
        name = "uw_%08x_r%d" % (rva, attempt)
        print("  %s @ 0x%08X is tombstoned, so this claim lands as %s instead. "
              "Recorded reason: %s"
              % ("uw_%08x" % rva, rva, name, tombstoned[("uw_%08x" % rva, rva)]))
    return name


def emit_and_write(ledger, on_ladder, snapshot):
    """Compile the owned sources, then write rows, pins and tombstones.

    Returns the build selectors that prove what was written.
    """
    files = plan(on_ladder)
    by_key = collections.defaultdict(list)
    for funclet in on_ladder:
        by_key[key_of(funclet)].append(funclet)

    rows, written = [], []
    dtor_targets, member_targets = set(), set()
    sized_deletes, placement_targets = set(), set()
    for index, units in enumerate(files):
        path = ROOT / source_name(index)
        path.write_text(emit_source(units), encoding="utf-8", newline="\n")
        slots = compiled_slots(path)
        dtor_targets |= {u.target for u in units if u.kind in ("local", "param")}
        member_targets |= {u.target for u in units if u.kind == "member"}
        sized_deletes |= {(u.target, u.shape[1]) for u in units
                          if u.kind == "sized"}
        placement_targets |= {u.target for u in units if u.kind in ("place", "tag")}
        wanted = sorted(set(k for unit in units for k in unit_keys(unit)) & set(by_key))
        missing = [k for k in wanted if k not in slots]
        if missing:
            raise SystemExit(
                "%s: the compiler emitted no funclet for %d needed slot(s), e.g. %s. "
                "Fix the emitted shape; a row must not be dropped silently."
                % (path.name, len(missing), missing[:8]))
        count = 0
        for key in wanted:
            for funclet in by_key[key]:
                rows.append((row_name(funclet.rva, ledger.tombstoned), "",
                             "0x%08X" % funclet.rva,
                             str(funclet.size), source_name(index), "matched",
                             ROW_NOTES + slots[key]))
                count += 1
        written.append(path)
        print("  %s: %d units, %d rows" % (path.name, len(units), count))

    # A stale file is only unlinked, never `git rm`-ed: it is still tracked, so
    # the deletion stages itself when the commit names the path, and a revert
    # only has to write the bytes back.
    for stale in sorted(SOURCE_DIR.glob("uw_gen_*.cpp")):
        if stale not in written:
            stale.unlink()
            print("  removed stale %s" % stale.name)
    snapshot.stage(written)

    # Every destructor target gets its own pin. The resolver matches a REL32
    # callee by NAME, so an address already pinned under some other name still
    # leaves ??1Gen_uw_* unresolvable -- filtering on the address would drop
    # exactly the pins the build needs. A target reached from both a local and a
    # member subobject is pinned twice, once per type: the two types differ (the
    # member's needs a throwing constructor), so they mangle differently and one
    # pin cannot answer for the other.
    pins = [("??1Gen_uw_%08x@@QAE@XZ" % t, t) for t in sorted(dtor_targets)]
    pins += [("??1Gen_uwm_%08x@@QAE@XZ" % t, t) for t in sorted(member_targets)]
    pins += [(DELETE_NAME, f.target) for f in on_ladder
             if f.kind == "C" and not ledger.resolves(DELETE_NAME, f.target)]
    pins += [("??3Gen_uws%d_%08x@@SAXPAXI@Z" % (size, target), target)
             for target, size in sorted(sized_deletes)]
    pins += [("??3@YAXPAXPAUGen_uwt_%08x@@@Z" % t, t) for t in sorted(placement_targets)]
    pins = sorted(set(pins), key=lambda pin: (pin[1], pin[0]))
    redundant = [pin for pin in pins if ledger.resolves(*pin)]
    if redundant:
        raise SystemExit("pin duplicates a row that already carries it: %s" % redundant[:4])
    # A destructor and its member twin legitimately share an address: they are
    # two invented TYPES whose destructor is the same retail function. An
    # operator delete is not a type -- two delete pins at one address say those
    # same bytes are two different operators, which no reading of them can be.
    # That is exactly what a mis-read immediate did: 19 Gen_uws<address> sized
    # deletes pinned onto the one placement delete they all call.
    crowded = collections.Counter(address for name, address in pins
                                  if name.startswith("??3"))
    clashing = sorted(address for address, count in crowded.items() if count > 1)
    if clashing:
        raise SystemExit(
            "0x%08X would carry %d operator-delete pins (%s) -- one function cannot "
            "be two different operator deletes, so the shape telling them apart is "
            "wrong, not the ledger" % (clashing[0], crowded[clashing[0]],
                                       ", ".join(sorted(n for n, a in pins
                                                        if a == clashing[0])[:3])))

    rows.sort(key=lambda row: row[2])
    formatted = [",".join(row) for row in rows]
    # symbols.csv is asked its terminator BEFORE functions.csv is touched: a
    # mixed file makes that question fatal, and asking it after the first write
    # is what left functions.csv rewritten with no pins behind it.
    symbols_eol = ledger_io.uniform_terminator(SYMBOLS.read_bytes(), "symbols.csv")[:-1]

    # gen_small.validate_rows is the one place a double claim is decided. Run
    # against the ledger MINUS our own rows (Ledger already drops them), so every
    # fresh row is new to it and the two answers it gives -- refuse, or supersede
    # an exact-range gen-dump -- are the only two outcomes.
    functions_raw = FUNCTIONS.read_bytes()
    outside = [row for row in parse_ledger(functions_raw)
               if OWNED_SOURCE_DIR not in row["source"]]
    to_append, already, to_retract = gen_small.validate_rows(formatted, outside)
    if already or len(to_append) != len(formatted):
        raise SystemExit(
            "gen_uw: %d of %d fresh row(s) are already in the ledger under a source this "
            "generator does not own -- the rewrite would leave two rows on those bytes"
            % (len(formatted) - len(to_append), len(formatted)))
    if to_retract:
        gen_small.retract_dump_rows(functions_raw, to_retract)

    # The rewrite un-writes every owned row that is not in the fresh set. Without
    # a tombstone the union merge driver puts each one back on the next rebase
    # from a fork that predates this run, on top of whatever now owns the bytes.
    live = {(row[0], int(row[2], 16)) for row in rows}
    dropped = sorted(key for key in ledger.owned if key not in live)
    if dropped:
        gen_small.write_tombstones([
            (name, rva, "gen_uw re-derived its population and no longer emits this "
                        "funclet: " + ledger.declined.get(
                            rva, "0x%08X is no longer a named EH funclet in "
                                 "reverse/ghidra_functions.csv" % rva))
            for name, rva in dropped])
        print("  tombstoned %d owned row(s) the fresh compile no longer emits" % len(dropped))

    rewrite_lines(FUNCTIONS, OWNED_ROW_RE.search,
                  [",".join(row) for row in rows], b"\r")
    # rewrite_lines rejoins on b"\n", so `newline` is whatever precedes it -- b"\r"
    # for the CRLF file symbols.csv actually is. Hardcoding b"" wrote LF pins into
    # it, which is a NEW line to the union merge driver for a pin that already
    # existed, and gen_small then refuses to append to a mixed file at all.
    # functions.csv below keeps its own b"\r": it legitimately mixes all three
    # terminators, so there is nothing uniform to ask it for.
    rewrite_lines(SYMBOLS, lambda line: line.startswith(b"?") and line.endswith(PIN_NOTE_BYTES),
                  ["%s,0x%08X,%s" % (name, address, PIN_NOTE) for name, address in pins],
                  symbols_eol)
    print("landed %d rows across %d file(s); %d pins, %d of them at an address "
          "symbols.csv already names differently; %d superseded dump row(s)"
          % (len(rows), len(written), len(pins),
             sum(1 for _, address in pins if address in ledger.pinned), len(to_retract)))
    return [path.relative_to(ROOT).as_posix() for path in written]


def census():
    ledger = Ledger()
    on_ladder, off_ladder, tally, tally_bytes = read_funclets(ledger)
    print("=== unclaimed named-EH population by template ===")
    for label in sorted(tally):
        print("  %-22s %6d rows %8d B" % (label, tally[label], tally_bytes[label]))
    print("  %-22s %6d rows %8d B" % ("TOTAL", sum(tally.values()), sum(tally_bytes.values())))
    landed = sum(f.size for f in on_ladder if ("uw_%08x" % f.rva, f.rva) in ledger.owned)
    print("\non-ladder (what land emits): %d rows / %d B ; %d B of that is already landed"
          % (len(on_ladder), sum(f.size for f in on_ladder), landed))
    per_kind = collections.Counter()
    per_kind_bytes = collections.Counter()
    for funclet in on_ladder:
        per_kind[funclet.kind] += 1
        per_kind_bytes[funclet.kind] += funclet.size
    for kind in sorted(per_kind):
        print("    %s %5d rows %8d B" % (kind, per_kind[kind], per_kind_bytes[kind]))
    print("off-ladder (no frame slot this generator can place): %d rows / %d B"
          % (len(off_ladder), sum(f.size for f in off_ladder)))
    reasons = collections.Counter()
    reason_bytes = collections.Counter()
    for funclet in off_ladder:
        reason = unreachable(funclet).split(":")[0]
        reasons[reason] += 1
        reason_bytes[reason] += funclet.size
    for reason in sorted(reason_bytes, key=lambda r: -reason_bytes[r]):
        print("    %5d rows %7d B  %s" % (reasons[reason], reason_bytes[reason], reason))
    targets = {f.target for f in on_ladder if f.kind in "AB"}
    members = {f.target for f in on_ladder if f.kind == "M"}
    print("distinct destructor targets: %d local/parameter + %d member (%d already carry "
          "another name in symbols.csv, which a pin filtered on address would wrongly skip)"
          % (len(targets), len(members),
             sum(1 for t in targets | members if t in ledger.pinned)))
    print("template-C operator delete targets: %s"
          % sorted({hex(f.target) for f in on_ladder if f.kind == "C"}))
    units = [unit for units in plan(on_ladder) for unit in units]
    print("plan: %d unit(s) over %d file(s) at <= %d rows each  %s"
          % (len(units), len(plan(on_ladder)), ROWS_PER_FILE,
             dict(sorted(collections.Counter(u.kind for u in units).items()))))


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("mode", choices=("classify", "land"))
    args = parser.parse_args()
    (census if args.mode == "classify" else land)()


if __name__ == "__main__":
    main()
