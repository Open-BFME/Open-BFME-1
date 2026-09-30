#!/usr/bin/env python3
"""The data ledger: targets/game/reverse/data_rows.csv, globals a game/ source owns.

functions.csv owns code. A translation unit that defines only data (ZH's
Common/Language.cpp is one line: `LanguageID OurLanguage = LANGUAGE_ID_US;`)
had no way to own anything, so its honest owner could not exist in game/.
A data row claims one retail address range for one compiled symbol:

  name          the COFF symbol the source's object defines (mangled)
  address       hex, with address_kind `va` or `rva` -- never implied
  size          bytes, PROVEN from the object (below) or refused
  section       the retail section holding the range (.data, .rdata, ...)
  source        the game/ .c/.cpp that defines it
  status        matched
  evidence      why this source is the owner (a verdict, a reference)
  model         who landed it

Integrity (check_csv, no compiler): the header, an explicit address kind, a
size, the section containing the whole range, one owner per address, no two
ranges overlapping, one row per name, a tracked source.

Verification (build.py, per source and in the full gate), per row:
  size      the type's size, proven independently of the allocation: the
            mangled scalar type, the one file-scope definition in the
            preprocessed source (element size x numeric dimensions), or a
            COMMON symbol's own size -- and no larger than the symbol's
            allocation extent (to the next symbol or the section end, padding
            included), which alone proves nothing; otherwise refused.
  bytes     initialised: equal to retail over the extent outside relocation
            fields, and every relocation's target (symbol + in-place addend)
            equal to retail's pointer there, the target's address coming from
            the ledgers (functions.csv object symbols, data_rows, dir32 names,
            symbols.csv pins read as RVA or VA; an ILT stub counts for its body).
            A relocation to a TU-local symbol cannot be placed and fails.
            uninitialised (.bss / COMMON): retail holds zeros over the extent.
            Each symbol is checked alone at its own address: MSVC 7.1 lays a
            TU's zero-filled globals out by name, so no TU-internal order is
            assumed.

  python3 tools/data_rows.py --check            # integrity only
  python3 tools/data_rows.py --verify [SOURCE]  # compile + verify (all rows, or one source's)
"""
import argparse
import csv
import io
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DATA_ROWS = ROOT / "targets" / "game" / "reverse" / "data_rows.csv"
HEADER = "name,address,address_kind,size,section,source,status,evidence,model"
FIELDS = HEADER.split(",")
IMAGE_BASE = 0x400000
DIR32, DIR32NB = 0x0006, 0x0007
EXTERNAL, STATIC = 2, 3
UNINIT = 0x80
SOURCE_SUFFIXES = (".c", ".cpp")


def parse(raw):
    """[(line, dict)] of the ledger's records; raises ValueError on a bad header."""
    text = raw.decode("utf-8", errors="replace")
    records = list(csv.reader(io.StringIO(text)))
    if not records or ",".join(records[0]) != HEADER:
        raise ValueError(f"data_rows.csv: bad header (expected '{HEADER}')")
    out = []
    for line, record in enumerate(records[1:], start=2):
        if not record or record == [""]:
            continue
        out.append((line, dict(zip(FIELDS, record)) if len(record) == len(FIELDS) else {"_fields": len(record)}))
    return out


def va_of(row):
    """The row's VA: its address read the way address_kind says."""
    address = int(row["address"], 16)
    return address if row["address_kind"] == "va" else IMAGE_BASE + address


def retail_sections(exe=None):
    """[(name, va, end)] from retail's PE header (no image load)."""
    if exe is None:
        sys.path.insert(0, str(ROOT / "tools"))
        import build
        exe = build.EXE
    with open(exe, "rb") as handle:
        head = handle.read(4096)
    pe = struct.unpack_from("<I", head, 0x3C)[0]
    count, optional = struct.unpack_from("<H", head, pe + 6)[0], struct.unpack_from("<H", head, pe + 20)[0]
    base = struct.unpack_from("<I", head, pe + 52)[0]
    out = []
    for k in range(count):
        o = pe + 24 + optional + 40 * k
        name = head[o:o + 8].rstrip(b"\0").decode("latin-1").strip()
        vsize, rva, rsize = struct.unpack_from("<III", head, o + 8)
        out.append((name, base + rva, base + rva + max(vsize, rsize)))
    return out


def check(raw, problems, sources_ok=None, sections=None):
    """Integrity problems appended to `problems`; returns the row count."""
    try:
        records = parse(raw)
    except ValueError as exc:
        problems.append(str(exc))
        return 0
    if raw and not raw.endswith(b"\n"):
        problems.append("data_rows.csv: the last row has no line ending")
    sections = retail_sections() if sections is None else sections
    spans, names, starts = [], {}, {}
    for line, row in records:
        where = f"data_rows.csv line {line}"
        if "_fields" in row:
            problems.append(f"{where}: {row['_fields']} fields, expected {len(FIELDS)}")
            continue
        name = row["name"]
        if not name:
            problems.append(f"{where}: empty name")
            continue
        where += f" ({name})"
        if row["address_kind"] not in ("va", "rva"):
            problems.append(f"{where}: address_kind must be `va` or `rva`, not '{row['address_kind']}'")
            continue
        if not re.fullmatch(r"0x[0-9A-Fa-f]{1,8}", row["address"]):
            problems.append(f"{where}: bad address '{row['address']}' (0x + at most 8 hex digits)")
            continue
        if not row["size"].isdigit() or int(row["size"]) <= 0:
            problems.append(f"{where}: size must be a positive integer, not '{row['size']}'")
            continue
        if row["status"] != "matched":
            problems.append(f"{where}: status must be `matched`, not '{row['status']}'")
        if not row["source"].startswith("game/") or not row["source"].endswith(SOURCE_SUFFIXES):
            problems.append(f"{where}: source must be a game/ .c/.cpp file, not '{row['source']}'")
        elif sources_ok is not None and row["source"] not in sources_ok:
            problems.append(f"{where}: source {row['source']} is not tracked")
        if not row["evidence"].strip():
            problems.append(f"{where}: empty evidence")
        if not row["model"].strip():
            problems.append(f"{where}: empty model (who landed it)")
        va, size = va_of(row), int(row["size"])
        home = [s for s in sections if s[1] <= va and va + size <= s[2]]
        if not home:
            problems.append(f"{where}: 0x{va:08X}+{size} lies in no single retail section")
        elif home[0][0] != row["section"]:
            problems.append(f"{where}: 0x{va:08X} is in {home[0][0]}, the row says '{row['section']}'")
        if name in names:
            problems.append(f"{where}: {name} already owned at line {names[name]}; one row per name")
        names.setdefault(name, line)
        if va in starts:
            problems.append(f"{where}: 0x{va:08X} already owned by line {starts[va]}; one owner per address")
        starts.setdefault(va, line)
        spans.append((va, va + size, line, name))
    spans.sort()
    for (a0, a1, l0, n0), (b0, b1, l1, n1) in zip(spans, spans[1:]):
        if b0 < a1 and a0 != b0:
            problems.append(f"data_rows.csv lines {l0} and {l1}: {n0} 0x{a0:08X}+{a1 - a0} overlaps "
                            f"{n1} 0x{b0:08X}+{b1 - b0}")
    return len(records)


def load(path=DATA_ROWS):
    if not Path(path).exists():
        return []
    return [row for _, row in parse(Path(path).read_bytes()) if "_fields" not in row]


# --------------------------------------------------------------------------- verification

def _tools():
    sys.path.insert(0, str(ROOT / "tools"))
    import build
    import reloc_ledger
    return build, reloc_ledger


def symbol_size(sections, symbols, sym, source=None):
    """(proven sizes, what proves them) for a defined or COMMON data symbol.

    The allocation extent (to the next symbol or the section end) includes
    alignment padding, so it only BOUNDS the size. The size itself must be
    proven independently: a COMMON symbol's own size, the size its mangled
    scalar type declares, or the one file-scope definition in its source laid
    out by the compiler's preprocessed unit (element size times numeric array
    dimensions). With none of these, nothing is proven and the row is refused."""
    _, rl = _tools()
    if sym["section"] == 0:  # COMMON: the value is the size
        return {sym["value"]}, "COMMON symbol size"
    sec = sections[sym["section"] - 1]
    later = sorted({s["value"] for s in symbols.values() if s["section"] == sym["section"]
                    and s["storage"] in (EXTERNAL, STATIC) and s["name"] and not s["name"].startswith(".")
                    and s["value"] > sym["value"]})
    extent = (later[0] if later else sec["size"]) - sym["value"]
    scalar = rl.mangled_scalar_size(sym["name"])
    if scalar is not None:
        if scalar <= extent:
            return {scalar}, f"mangled type declares {scalar} (allocation extent {extent})"
        return set(), f"mangled type declares {scalar} but the allocation extent is {extent}"
    cname = rl.c_name(sym["name"])
    declared = rl.declared_size(source, cname) if source is not None and cname else None
    if declared is not None:
        size, text = declared
        if size <= extent:
            return {size}, f"`{text}` declares {size} (allocation extent {extent})"
        return set(), f"`{text}` declares {size} but the allocation extent is {extent}"
    return set(), f"no type size proven (allocation extent {extent} is not a size)"


class Resolver:
    """Retail VAs a relocation target name may take, from the ledgers only."""

    def __init__(self, data_rows):
        build, rl = _tools()
        self.homes = {}
        for row in build.load_function_rows():
            if row["target_rva"].startswith("0x"):
                va = IMAGE_BASE + int(row["target_rva"], 16)
                for key in {row["name"], build.ledger_object_symbol(row)}:
                    self.homes.setdefault(key, set()).add(va)
        for row in data_rows:
            self.homes.setdefault(row["name"], set()).add(va_of(row))
        for row in rl.read_csv_rows(build.DIR32_ADDRESSES):
            self.homes.setdefault(row["name"], set()).add(int(row["va"], 16))
        with (ROOT / "targets/game/reverse/symbols.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.reader(handle):
                if len(row) >= 2 and row[1].startswith("0x"):
                    value = int(row[1], 16)
                    readings = [value] + ([value - IMAGE_BASE] if value >= IMAGE_BASE else [])
                    self.homes.setdefault(row[0], set()).update(IMAGE_BASE + r for r in readings)

    def __call__(self, name):
        return self.homes.get(name, set())


def verify_row(row, img, resolve, compile=True):
    """(ok, message) for one data row against its source's current object."""
    build, rl = _tools()
    source = ROOT / row["source"]
    if not source.is_file():
        return False, f"source {row['source']} is missing"
    obj = build.obj_path(source)
    if compile and not build.compile_is_current(source, obj):
        ok, text, _ = build.try_compile_source(source, obj)
        if not ok:
            return False, f"{row['source']} does not compile: {(text or '').strip()[-300:]}"
    if not obj.exists():
        return False, f"object {obj.name} missing"
    sections, symbols = rl.parse_coff(obj.read_bytes())
    found = [s for s in symbols.values() if s["name"] == row["name"] and s["storage"] == EXTERNAL
             and (s["section"] > 0 or s["value"] > 0)]
    if len(found) != 1:
        return False, f"{row['name']} is not defined once in {obj.name}"
    sym = found[0]
    size = int(row["size"])
    sizes, why = symbol_size(sections, symbols, sym, source)
    if size not in sizes:
        return False, f"size {size} unproven: {why} gives {sorted(sizes)}"
    va = va_of(row)
    if img.section(va) != row["section"] or img.section(va + size - 1) != row["section"]:
        return False, f"0x{va:08X}+{size} is not inside retail {row['section']}"
    retail = img.read(va, size)
    sec = sections[sym["section"] - 1] if sym["section"] > 0 else None
    if sec is None or sec["body"] is None:
        # zero-filled: this symbol alone, at its own address (no TU order assumed)
        if any(retail):
            return False, f"uninitialised {row['name']} but retail holds non-zero bytes at 0x{va:08X}"
        return True, f"zero-filled {size} B at 0x{va:08X} ({why})"
    lo = sym["value"]
    body = sec["body"][lo:lo + size]
    relocs = [(w, i, k) for w, i, k in sec["relocs"] if lo - 3 <= w < lo + size]
    if any(w < lo or w + 4 > lo + size for w, _, _ in relocs):
        return False, "a relocation field straddles the symbol's extent"
    masked = bytearray(body)
    for w, _, _ in relocs:
        masked[w - lo:w - lo + 4] = retail[w - lo:w - lo + 4]
    if bytes(masked) != retail:
        diff = next(i for i in range(size) if masked[i] != retail[i])
        return False, f"initializer differs from retail at +{diff:#x}"
    for w, index, kind in relocs:
        target = symbols.get(index)
        site = va + w - lo
        value = struct.unpack_from("<I", retail, w - lo)[0]
        if target is None or kind not in (DIR32, DIR32NB):
            return False, f"+{w - lo:#x}: unsupported relocation type {kind:#x}"
        if target["storage"] != EXTERNAL:
            return False, f"+{w - lo:#x}: relocation to TU-local {target['name']} cannot be placed"
        addend = struct.unpack_from("<i", sec["body"], w)[0]
        want = {(home + addend - (IMAGE_BASE if kind == DIR32NB else 0)) & 0xFFFFFFFF
                for home in resolve(target["name"])}
        if not want:
            return False, f"+{w - lo:#x}: {target['name']} has no retail address in the ledgers"
        actual = value if kind == DIR32 else value + IMAGE_BASE
        head = img.read(actual, 5) if img.section(actual) == ".text" else None
        stub = (actual + 5 + struct.unpack_from("<i", head, 1)[0]) & 0xFFFFFFFF if head and head[0] == 0xE9 else None
        if value not in want and stub not in want:
            return False, (f"+{w - lo:#x} (0x{site:08X}): retail points at 0x{value:08X}, "
                           f"{target['name']}+{addend:#x} is " + ", ".join(f"0x{x:08X}" for x in sorted(want)))
    return True, f"{size} B at 0x{va:08X} equal to retail, {len(relocs)} relocation(s) on target ({why})"


def verify(rows=None, sources=None, compile=True, log=print):
    """Verify data rows (all, or those of `sources`); SystemExit(1) on any failure."""
    _, rl = _tools()
    every = load()
    rows = every if rows is None else rows
    if sources is not None:
        wanted = {Path(s).as_posix().removeprefix("source:") for s in sources}
        rows = [r for r in rows if r["source"] in wanted]
    if not rows:
        return 0
    img, resolve = rl.Image(), Resolver(every)
    failed = 0
    for row in rows:
        ok, message = verify_row(row, img, resolve, compile)
        if not ok:
            failed += 1
            log(f"    {row['name']} ({row['source']}): {message}")
    if failed:
        log(f"Data rows: FAIL {failed} of {len(rows)}")
        raise SystemExit(1)
    log(f"Data rows: OK ({len(rows)} row(s) byte-verified)")
    return len(rows)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--check", action="store_true", help="integrity only")
    ap.add_argument("--verify", nargs="*", metavar="SOURCE", help="compile and verify (all rows, or these sources)")
    args = ap.parse_args(argv)
    problems = []
    n = check(DATA_ROWS.read_bytes(), problems) if DATA_ROWS.exists() else 0
    for p in problems:
        print(p)
    if problems:
        return 1
    print(f"data_rows: {n} row(s), integrity OK")
    if args.verify is not None:
        verify(sources=args.verify or None)
    return 0


if __name__ == "__main__":
    sys.exit(main())
