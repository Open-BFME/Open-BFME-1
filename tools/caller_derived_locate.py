#!/usr/bin/env python3
"""Place functions at addresses read from their already-matched CALLERS.

The other locators work from the callee's own bytes (locate=needle, sizepair=size,
callee_locate=matched-callee signature). This works from the CALLER: every matched
function's `e8` call sites point at real addresses; any target that is not yet a
known function start is an unmatched function whose ADDRESS we now know for free.
Collect those, then for a file's compiled functions, keep the one whose bytes match
(reloc-masked, with a substantial run of real opcode bytes) the derived target of
its size. build.py's exact byte compare is the final judge.

    python3 tools/caller_derived_locate.py src/w3d/matrix3.cpp [--emit]

Validated 2026-07-06: placed Matrix3 ctor + ShareBufferClass ctor (needle-less,
called by matched code) that locate/sizepair/callee_locate all missed.

STRICTNESS (learned the hard way): reject data symbols (`@@3`), vtables/thunks
(`??_`), and anything whose reloc-masked bytes leave < max(24, 45%) real bytes —
a fully-relocated function-pointer table masks to nothing and matches any region.
Do NOT run tools/dedup_csv.py after emitting here — it has clobbered sibling rows;
add rows and go straight to ./build.sh.
"""
import sys, csv, struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build, harvest

FUNCTIONS = ROOT / "reverse" / "functions.csv"
GHIDRA = ROOT / "reverse" / "ghidra_functions.csv"


def rvoff(pe, rva):
    try:
        return build.rva_to_file_offset(pe, rva)
    except Exception:
        return None


def follow_ilt(exe, pe, dest):
    o = rvoff(pe, dest)
    if o is not None and exe[o] == 0xE9:
        return dest + 5 + struct.unpack_from("<i", exe, o + 1)[0]
    return dest


def derived_targets(exe, pe):
    rows = list(csv.DictReader(FUNCTIONS.open()))
    claimed = {int(r["target_rva"], 16) for r in rows}
    gh = {int(r["rva"], 16): int(r["size"]) for r in csv.DictReader(GHIDRA.open())}
    derived = {}
    for r in rows:
        if r["status"] != "matched":
            continue
        rva, size = int(r["target_rva"], 16), int(r["target_size"])
        o = rvoff(pe, rva)
        if o is None:
            continue
        buf = exe[o:o + size]
        i = 0
        while i < len(buf) - 4:
            if buf[i] == 0xE8:
                dest = rva + i + 5 + struct.unpack_from("<i", buf, i + 1)[0]
                if 0x1000 <= dest < 0xC00000:
                    dest = follow_ilt(exe, pe, dest)
                    if dest not in claimed and dest in gh:
                        derived[dest] = (gh[dest], derived.get(dest, (0, 0))[1] + 1)
                i += 5
            else:
                i += 1
    return derived


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    emit = "--emit" in sys.argv
    src = Path(args[0])
    exe = build.EXE.read_bytes()
    pe = build.pe_sections(exe)
    targets = derived_targets(exe, pe)
    bysize = {}
    for a, (sz, c) in targets.items():
        bysize.setdefault(sz, []).append((a, c))
    have = {r["name"] for r in csv.DictReader(FUNCTIONS.open())}
    obj = harvest.compile_obj(src if src.is_absolute() else ROOT / src, [])

    hits = []
    seen_addr = set()
    for sym in build.read_object_symbols(obj.read_bytes()):
        n = sym["name"]
        if (n in have or not n.startswith("?") or n.startswith("??_")
                or "@@3" in n or sym["section"] <= 0):
            continue
        try:
            body, relocs = build.read_object_symbol_bytes(obj, n)
        except ValueError:
            continue
        sz = len(body.rstrip(b"\xcc"))
        if sz < 48:
            continue
        mask = bytearray(b"\xff" * sz)
        for roff, rt, s2 in relocs:
            if roff + 4 <= sz:
                for k in range(4):
                    mask[roff + k] = 0
        if sum(mask) // 255 < max(24, sz * 0.45):
            continue
        for a, c in bysize.get(sz, []):
            if a in seen_addr:
                continue
            o = build.rva_to_file_offset(pe, a)
            tgt = exe[o:o + sz]
            if all(tgt[j] == body[j] or mask[j] == 0 for j in range(sz)):
                hits.append((n, a, sz, c))
                seen_addr.add(a)
                break

    if not hits:
        print(f"{src.name}: no caller-derived placements")
        return
    print(f"{src.name}: {len(hits)} caller-derived candidate(s)")
    for n, a, sz, c in hits:
        print(f"  0x{a:06x} {sz}B called_by={c} {n.split('@@')[0][:44]}")
    if emit:
        rows = FUNCTIONS.read_text().rstrip("\n").split("\n")
        h, b = rows[0], rows[1:]
        for n, a, sz, c in hits:
            b.append(f"{n},,0x{a:08X},{sz},{src.as_posix()},matched,caller-derived")
        b.sort(key=lambda r: r.split(",")[0])
        FUNCTIONS.write_text(h + "\n" + "\n".join(b) + "\n")
        print(f"emitted {len(hits)} — run ./build.sh to verify, drop FAILs (do NOT dedup_csv)")


if __name__ == "__main__":
    main()
