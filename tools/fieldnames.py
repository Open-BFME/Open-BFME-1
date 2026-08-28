#!/usr/bin/env python3
"""BFME struct member names at binary-proven offsets, joined on the INI key.

Both games parse their INI files through the same table shape --
`{const char* token; INIFieldParseProc parse; const void* userData; Int offset;}`
-- so the retail exe carries, in plain .rdata, the offset of every field an INI
file can set, and upstream carries the C++ member name each key writes. Joining
them on the key recovers names for offsets that are already proven, which is
what `docs/ini_schema.md` used to carry before its generator was deleted in
a4b1dde and left that file unregenerable.

**The offset always comes from the binary and only the name from upstream.**
BFME moved fields (`ScatterRadiusVsInfantry` is +0x514 here, +0x60 upstream), so
an upstream offset would silently corrupt a layout -- and these are shim
declarations, which the byte gate cannot see. The upstream index therefore
stores no offsets at all: there is nothing here to fall back to. An entry whose
offset dword decodes as neither a struct offset nor a pointer aborts its whole
table by name.

What counts as a table: a maximal run of well-formed entries in a
non-executable section, closed by a NULL-token entry. Two independent misreads
are excluded structurally rather than by taste --

  * an entry whose offset dword is a mapped pointer is a 16-byte window over an
    array of 8-byte `{name, proc}` pairs (lua's `getlocal`/`setlocal` table),
    not a field entry, and it ends the run;
  * a lone record closed by a terminator is the shape of every other 16-byte
    `{name, proc, 0, 0}` array in .data -- the INI block keywords, the menu
    callbacks -- so a one-entry run counts only if something in the image points
    at its address. Two or more records sharing a terminator is not a shape
    anything else here has, and stands on its own: ThingTemplate's
    `Draw`/`Geometry` table is reached by arithmetic and no dword in the image
    holds its address.

A key that names one upstream member is that member. A key several upstream
classes define is resolved only when the table's own class vote decides it --
every other key in that table voting `WeaponTemplate` is what makes
`AttackRange` its `m_attackRange` and not `SlavedUpdateModuleData`'s. A tie
decides nothing (margin 0), and a key left unresolved is written with no name
and its candidates in `notes`. It is never guessed.

Usage:
  python3 tools/fieldnames.py [--root DIR]
"""
import argparse
import collections
import csv
import re
import struct
import sys
from pathlib import Path

DEFAULT_ROOT = Path(__file__).resolve().parents[1]
BINARY = "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
UPSTREAM = "reference/CnC_Generals_Zero_Hour"
OUT = "reverse/field_names.csv"
COLUMNS = ["table_rva", "ini_key", "bfme_offset", "upstream_class",
           "upstream_member", "votes", "margin", "notes"]

ENTRY_SIZE = 16
# The largest offset in the retail tables is 5,032; a struct offset that runs
# into five figures is not one, and says the record was misread.
OFFSET_MAX = 0x10000
KEY_MAX = 63
MIN_UNREFERENCED_ENTRIES = 2
SOURCE_EXT = (".cpp", ".c", ".h", ".inl")
IMAGE_SCN_MEM_EXECUTE = 0x20000000

# `{ "Key", <parser>, <userData>, offsetof(Class, m_member) }` on one entry: the
# character class forbids the quote and braces that end an entry, so a key can
# never reach across its own closing `}` to borrow the next entry's offsetof.
UPSTREAM_ENTRY = re.compile(
    r'"([^"\n]+)"\s*,(?:[^"{};]|\n)*?offsetof\s*\(\s*(\w+)\s*,\s*([A-Za-z_]\w*)')

Entry = collections.namedtuple("Entry", "rva key parse offset")
Vote = collections.namedtuple("Vote", "owner votes margin")


def fail(message):
    raise SystemExit(f"fieldnames: {message}")


# ---------------------------------------------------------------------- PE ---

class Image:
    """Just enough PE to read .rdata by RVA and ask what points where."""

    def __init__(self, path):
        try:
            self.raw = path.read_bytes()
        except OSError as exc:
            fail(f"cannot read {path}: {exc}")
        if self.raw[:2] != b"MZ":
            fail(f"{path} does not start with MZ; not a PE image")
        head = struct.unpack_from("<I", self.raw, 0x3C)[0]
        if self.raw[head:head + 4] != b"PE\0\0":
            fail(f"{path} has no PE signature at e_lfanew={head:#x}")
        count = struct.unpack_from("<H", self.raw, head + 6)[0]
        optional = struct.unpack_from("<H", self.raw, head + 20)[0]
        self.base = struct.unpack_from("<I", self.raw, head + 24 + 28)[0]
        self.sections = []
        for index in range(count):
            at = head + 24 + optional + index * 40
            size, rva, raw_size, raw_at = struct.unpack_from("<IIII", self.raw, at + 8)
            flags = struct.unpack_from("<I", self.raw, at + 36)[0]
            # A section's tail can be virtual (.data's 0x6a000 of bss), so the
            # readable extent is the raw size, never the virtual one.
            self.sections.append((rva, min(size, raw_size), raw_at, flags))
        self.blobs = [self.raw[at:at + size] for _rva, size, at, _flags in self.sections]

    def at(self, rva):
        for start, size, raw_at, flags in self.sections:
            if start <= rva < start + size:
                return raw_at + rva - start, start + size - rva, flags
        return None

    def read(self, rva, count):
        found = self.at(rva)
        if found is None or found[1] < count:
            return None
        return self.raw[found[0]:found[0] + count]

    def cstring(self, rva):
        found = self.at(rva)
        if found is None:
            return None
        at, room, _flags = found
        end = self.raw.find(b"\0", at, at + min(room, KEY_MAX + 1))
        return None if end < 0 else self.raw[at:end]

    def executable(self, rva):
        found = self.at(rva)
        return found is not None and bool(found[2] & IMAGE_SCN_MEM_EXECUTE)

    def references(self, rva):
        """How many dwords anywhere in the image hold this address."""
        pattern = struct.pack("<I", rva + self.base)
        return sum(blob.count(pattern) for blob in self.blobs)


# ------------------------------------------------------------------ tables ---

def entry(image, rva):
    """One FieldParse record, or None if these 16 bytes are not one."""
    raw = image.read(rva, ENTRY_SIZE)
    if raw is None:
        return None
    token, parse, _user, offset = struct.unpack("<IIII", raw)
    if token < image.base or parse < image.base:
        return None
    key = image.cstring(token - image.base)
    if not key or not all(0x21 <= char <= 0x7E for char in key):
        return None
    if not image.executable(parse - image.base):
        return None
    if offset >= image.base:
        return None
    return Entry(rva, key.decode("ascii"), parse - image.base, offset)


def tables(image):
    """[(table rva, [Entry])] plus the count of runs rejected as too short.

    Runs are grown at four-byte granularity because nothing guarantees a table
    is sixteen-aligned; a run that starts one entry into another is discarded by
    taking only maximal runs."""
    found, rejected = [], 0
    for start, size, _raw_at, flags in image.sections:
        if flags & IMAGE_SCN_MEM_EXECUTE:
            continue
        entries = {}
        for rva in range(start, start + size - ENTRY_SIZE + 1, 4):
            record = entry(image, rva)
            if record is not None:
                entries[rva] = record
        for rva in sorted(entries):
            if rva - ENTRY_SIZE in entries:
                continue
            run, at = [], rva
            while at in entries:
                run.append(entries[at])
                at += ENTRY_SIZE
            head = image.read(at, 4)
            if head is None or struct.unpack("<I", head)[0] != 0:
                continue                      # no NULL terminator: not a table
            if len(run) < MIN_UNREFERENCED_ENTRIES and not image.references(rva):
                rejected += 1
                continue
            found.append((rva, run))
    return found, rejected


def check_offsets(rva, run):
    """Every entry must carry a decodable struct offset, or the table is out.

    Substituting the upstream offset here is the one thing this tool must never
    do: it is a plausible number that would land in a shim declaration, byte
    match, and mis-model the struct for everyone downstream."""
    for record in run:
        if record.offset >= OFFSET_MAX:
            fail(f"table {rva:#010x} entry {record.rva:#010x} '{record.key}' has "
                 f"offset dword {record.offset:#x}, which is no struct offset; "
                 f"aborting that table rather than taking upstream's offset")


# ---------------------------------------------------------------- upstream ---

def upstream_index(root):
    """INI key -> sorted [(class, member)], carrying no offsets by construction.

    Every `.cpp`, `.h` and `.inl` under the reference tree is read, not just the
    files a list would name: the tables live wherever the module that owns them
    does, and a missed file is a key that silently loses its name."""
    tree = root / UPSTREAM
    if not tree.is_dir():
        fail(f"no upstream reference tree at {tree}")
    index = collections.defaultdict(set)
    for path in sorted(tree.rglob("*")):
        if path.suffix not in SOURCE_EXT or not path.is_file():
            continue
        text = path.read_text("utf-8", "replace")
        if "offsetof" not in text:
            continue
        for key, owner, member in UPSTREAM_ENTRY.findall(text):
            index[key].add((owner, member))
    if not index:
        fail(f"{tree} yielded no `offsetof` field-parse entries")
    return {key: sorted(pairs) for key, pairs in index.items()}


def vote(run, index):
    """The table's owning class by key majority, with its margin over second.

    Each key backs every class that defines it, so a key several classes share
    cannot outvote the keys that agree. A margin of zero decided nothing and is
    recorded as such -- no threshold is applied here, and none is hidden."""
    tally = collections.Counter()
    for record in run:
        for owner in {owner for owner, _member in index.get(record.key, ())}:
            tally[owner] += 1
    if not tally:
        return Vote("", 0, 0)
    ranked = sorted(tally.items(), key=lambda item: (-item[1], item[0]))
    runner_up = ranked[1][1] if len(ranked) > 1 else 0
    return Vote(ranked[0][0], ranked[0][1], ranked[0][1] - runner_up)


def resolve(record, index, decided):
    """(class, member, notes) for one key -- named only where nothing is guessed."""
    candidates = index.get(record.key, [])
    members = dict(candidates)
    if decided and decided in members:
        others = "|".join(f"{owner}::{member}" for owner, member in candidates
                          if owner != decided)
        return decided, members[decided], f"vote picked from {others}" if others else ""
    if len(candidates) == 1:
        owner, member = candidates[0]
        note = f"table votes {decided}" if decided else "table vote decided nothing"
        return owner, member, f"sole candidate; {note}"
    if candidates:
        return "", "", "ambiguous: " + "|".join(f"{owner}::{member}"
                                                for owner, member in candidates)
    return "", "", "no upstream key"


# ------------------------------------------------------------------ output ---

def rows(found, index):
    """Every BFME entry, in table then entry order, with the vote it sits under."""
    out, votes = [], {}
    for rva, run in found:
        votes[rva] = decision = vote(run, index)
        decided = decision.owner if decision.margin else ""
        for record in run:
            owner, member, notes = resolve(record, index, decided)
            out.append([f"{rva:#010x}", record.key, f"{record.offset:#x}",
                        owner, member, decision.votes, decision.margin, notes])
    return out, votes


def report(found, rejected, index, out, votes):
    named = sum(1 for row in out if row[4])
    ambiguous = sum(1 for row in out if row[7].startswith("ambiguous"))
    unmatched = sum(1 for row in out if row[7] == "no upstream key")
    lines = [f"{len(found)} FieldParse tables, {len(out)} entries, "
             f"{len({row[1] for row in out})} distinct keys "
             f"({rejected} short unreferenced runs rejected)",
             f"upstream index: {len(index)} keys, "
             f"{sum(len(pairs) for pairs in index.values())} (class, member) pairs",
             f"named {named}, ambiguous {ambiguous}, no upstream key {unmatched}",
             "",
             f"class vote per table (winner/runner-up); "
             f"{sum(1 for d in votes.values() if not d.votes)} tables drew no vote:"]
    for rva, decision in sorted(votes.items(),
                                key=lambda item: (-item[1].votes, item[0])):
        if decision.votes:
            lines.append(f"  {rva:#010x}  {decision.owner} {decision.votes}v/"
                         f"{decision.votes - decision.margin}v "
                         f"(margin {decision.margin})")
    return "\n".join(lines)


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT,
                        help="repository to read and write (default: this repo)")
    args = parser.parse_args(argv)
    root = args.root.resolve()

    image = Image(root / BINARY)
    found, rejected = tables(image)
    if not found:
        fail(f"{root / BINARY} yielded no FieldParse tables")
    for rva, run in found:
        check_offsets(rva, run)
    index = upstream_index(root)
    out, votes = rows(found, index)

    destination = root / OUT
    if not destination.parent.is_dir():
        fail(f"no {destination.parent} to write {OUT} into")
    with open(destination, "w", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(COLUMNS)
        writer.writerows(out)
    print(report(found, rejected, index, out, votes))
    return 0


if __name__ == "__main__":
    sys.exit(main())
