#!/usr/bin/env python3
"""Every enum name table in the retail image, and what each one's width implies.

WHY THESE ARE WORTH HAVING AS A FILE. SAGE parses INI by looking an identifier
up in a NUL-terminated array of `const char*`, one array per enum, so a shipped
enum necessarily puts its complete name list into the image in declaration
order. That makes each array a permanent answer to two questions that otherwise
cost a day each: how many enumerators does this enum have, and therefore how
wide is a BitFlags over it, and what is enumerator N called.

Two of these settled width questions that had defeated a merge. The
ModelCondition array at 0x00EA6918 holds 304 names, so a ModelConditionFlags is
ten dwords and the ninety-six-bit local in Object_setSingleModelCondition.cpp
could not have been one. The KindOf array at 0x00EAA068 holds 181, which rounds
to the 192-bit BitFlags a TeamPrototype overload already used. Both were found
by hand, one at a time, which is the part this replaces.

WHAT COUNTS AS A TABLE, AND WHAT THIS REFUSES TO DECIDE. A candidate is a
maximal run of aligned dwords in .data that all point into .rdata and all
resolve to short printable NUL-terminated strings. That shape alone is not an
enum: a run of message strings or file names looks identical to the scan. So a
run is reported NAME_TABLE only when nearly all of its entries are plain C
identifiers, and everything else that has the shape is reported UNCERTAIN rather
than dropped or promoted -- a sweep that silently discards what it cannot
classify is one nobody can trust a negative from.

The run must also be MAXIMAL. Every suffix of a name table is itself a run of
string pointers, so reporting non-maximal runs would bury the real tables under
hundreds of their own tails.

  python3 tools/name_tables.py             # write targets/game/reverse/name_tables.tsv
  python3 tools/name_tables.py --bitflags  # ledger BitFlags widths vs table sizes
"""
import collections
import csv
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402

OUT = B.ROOT / "targets/game/reverse/name_tables.tsv"
IMAGE_BASE = 0x400000
MIN_ENTRIES = 6          # shorter runs are mostly coincidence
MAX_NAME = 64
IDENT_SHARE = 0.9        # below this the run is not an enum, whatever else it is
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
NAME_TABLE, UNCERTAIN = "NAME_TABLE", "UNCERTAIN"


def sections(data):
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count = struct.unpack_from("<H", data, pe + 6)[0]
    opt = struct.unpack_from("<H", data, pe + 20)[0]
    out = {}
    for i in range(count):
        head = pe + 24 + opt + i * 40
        name = data[head:head + 8].rstrip(b"\0").decode(errors="replace")
        vsize, va, rsize, raw = struct.unpack_from("<IIII", data, head + 8)
        out[name] = (va, vsize, raw, rsize)
    return out


class Image:
    """The retail file, with the three questions this sweep asks of it."""

    def __init__(self, path=None):
        self.data = Path(path or B.EXE).read_bytes()
        self.sections = sections(self.data)
        va, vsize, _raw, _rsize = self.sections[".rdata"]
        self.str_lo, self.str_hi = IMAGE_BASE + va, IMAGE_BASE + va + vsize

    def string_at(self, va):
        """The NUL-terminated printable string at this VA, or None."""
        off = va - IMAGE_BASE
        if not 0 <= off < len(self.data):
            return None
        end = self.data.find(b"\0", off, off + MAX_NAME + 1)
        if end <= off:
            return None
        raw = self.data[off:end]
        if not all(32 <= byte < 127 for byte in raw):
            return None
        return raw.decode("ascii")

    def is_string_pointer(self, value):
        return self.str_lo <= value < self.str_hi and self.string_at(value) is not None

    def text_dword_index(self):
        """{dword value: count} over .text, for 'who mentions this address'."""
        va, vsize, raw, rsize = self.sections[".text"]
        lo, hi = raw, raw + min(vsize, rsize)
        seen = collections.Counter()
        for off in range(lo, hi - 4, 4):
            seen[struct.unpack_from("<I", self.data, off)[0]] += 1
        return seen


def sweep(image):
    """Maximal runs of string pointers in .data, classified but never dropped."""
    va, vsize, raw, rsize = image.sections[".data"]
    lo, hi = raw, raw + min(vsize, rsize)
    data, found, off = image.data, [], lo
    while off + 4 <= hi:
        value = struct.unpack_from("<I", data, off)[0]
        if not image.is_string_pointer(value):
            off += 4
            continue
        names, cursor = [], off
        while cursor + 4 <= hi:
            word = struct.unpack_from("<I", data, cursor)[0]
            if not image.is_string_pointer(word):
                break
            names.append(image.string_at(word))
            cursor += 4
        terminator = struct.unpack_from("<I", data, cursor)[0] if cursor + 4 <= hi else None
        if len(names) >= MIN_ENTRIES:
            share = sum(bool(IDENT.match(n)) for n in names) / len(names)
            found.append({
                "file_offset": off,
                "va": IMAGE_BASE + va + (off - raw),
                "entries": len(names),
                "verdict": NAME_TABLE if share >= IDENT_SHARE else UNCERTAIN,
                "identifier_share": round(share, 3),
                "nul_terminated": terminator == 0,
                "names": names,
            })
        off = cursor + 4          # maximal runs only: never restart inside one
    return found


def dwords_needed(bits):
    return (bits + 31) // 32


def bitflags_widths(rows=None):
    """{bits: [row name]} for every BitFlags width the ledger decorates."""
    pattern = re.compile(r"BitFlags@\$0([0-9A-P]+)@")
    out = collections.defaultdict(list)
    for row in rows if rows is not None else B.load_all_function_rows():
        for token in set(pattern.findall(row["name"])):
            bits = decode_number(token)
            if bits is not None:
                out[bits].append(row["name"])
    return out


def decode_number(token):
    """MSVC template integer: 0-9 spell 1..10, otherwise hex in A-P."""
    if token.isdigit():
        return int(token) + 1
    value = 0
    for char in token:
        if not "A" <= char <= "P":
            return None
        value = value * 16 + (ord(char) - ord("A"))
    return value


def main(argv):
    image = Image()
    tables = sweep(image)
    if "--bitflags" in argv:
        widths = bitflags_widths()
        sizes = collections.defaultdict(list)
        for table in tables:
            if table["verdict"] == NAME_TABLE:
                sizes[table["entries"]].append(table)
        print(f"{len(widths)} BitFlags width(s) in the ledger against "
              f"{sum(len(v) for v in sizes.values())} name table(s)\n")
        print("  EXACT   the width IS an enum's count, so the decoration names that enum")
        print("  ROUNDED no enum of that size, but the width is a whole number of dwords")
        print("          and an enum fits it -- a storage size rather than a count")
        print("  UNBACKED neither: no enum of this size and not a dword boundary\n")
        unbacked = []
        for bits in sorted(widths):
            exact = sizes.get(bits, [])
            fits = [t for size, ts in sizes.items() if size <= bits for t in ts]
            if exact:
                kind = "EXACT   "
                note = ", ".join(f"{t['names'][0]}.. @{t['file_offset']:#010x} "
                                 f"({t['entries']})" for t in exact[:2])
            elif bits % 32 == 0 and fits:
                kind = "ROUNDED "
                widest = max(fits, key=lambda t: t["entries"])
                note = (f"{dwords_needed(bits)} dwords; largest enum that fits is "
                        f"{widest['names'][0]}.. ({widest['entries']}) @"
                        f"{widest['file_offset']:#010x}")
            else:
                kind = "UNBACKED"
                note = "no enum of this size, and not a dword boundary"
                unbacked.append(bits)
            print(f"  {kind} {bits:>4} bits, {len(widths[bits]):>4} row(s)  {note}")
        if unbacked:
            print(f"\n{len(unbacked)} unbacked width(s): {unbacked}. Each is either a "
                  f"decoration this image does not support or an enum whose table this "
                  f"sweep did not find; neither is settled by counting alone.")
        return 0
    with open(OUT, "w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle, delimiter="\t", lineterminator="\r\n")
        writer.writerow(["file_offset", "va", "entries", "verdict", "identifier_share",
                         "nul_terminated", "dwords_if_bitflags", "first_name",
                         "last_name", "names"])
        for table in sorted(tables, key=lambda t: -t["entries"]):
            writer.writerow([f"{table['file_offset']:#010x}", f"{table['va']:#010x}",
                             table["entries"], table["verdict"], table["identifier_share"],
                             "yes" if table["nul_terminated"] else "no",
                             dwords_needed(table["entries"]),
                             table["names"][0], table["names"][-1],
                             " ".join(table["names"])])
    counts = collections.Counter(t["verdict"] for t in tables)
    print(f"{OUT.relative_to(B.ROOT)}: {counts[NAME_TABLE]} name tables, "
          f"{counts[UNCERTAIN]} uncertain (shape matches, contents are not identifiers)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
