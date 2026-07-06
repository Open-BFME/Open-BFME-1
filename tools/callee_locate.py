#!/usr/bin/env python3
"""Place needle-less functions by their matched-callee signature.

locate.py places a function by finding a unique masked-byte needle in .text, then
validates it against known callee starts. Some functions have NO unique needle
(all relocs, or a common byte pattern) yet DO call several already-matched
functions. This finds them the other way round: compute the set of retail
addresses a compiled function calls (via its matched callees), then find the one
unclaimed ghidra function of about the right size whose own e8-call targets are a
superset of that set. A unique hit is emitted as a candidate row; build.py's byte
comparison is the final judge, so a wrong guess simply fails.

    python3 tools/callee_locate.py src/w3d/part_emt.cpp [--emit]

Needs >=2 matched callees to be discriminating; skips functions with fewer. This
complements locate (needle-based) and anchor_by_string (string-based).
"""
import sys, csv, struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build, harvest


def load():
    exe = build.EXE.read_bytes()
    pe = build.pe_sections(exe)
    rows = list(csv.DictReader((ROOT / "reverse" / "functions.csv").open()))
    claimed = {int(r["target_rva"], 16) for r in rows}
    matched_addr = {r["name"]: int(r["target_rva"], 16) for r in rows if r["status"] == "matched"}
    have = {r["name"] for r in rows}
    gh = [(int(r["rva"], 16), int(r["size"]))
          for r in csv.DictReader((ROOT / "reverse" / "ghidra_functions.csv").open())
          if int(r["rva"], 16) not in claimed and int(r["size"]) >= 60]
    return exe, pe, matched_addr, have, gh


def follow_ilt(exe, pe, dest):
    try:
        o = build.rva_to_file_offset(pe, dest)
        if exe[o] == 0xE9:
            return dest + 5 + struct.unpack_from("<i", exe, o + 1)[0]
    except Exception:
        pass
    return dest


def calls_in(exe, pe, rva, size):
    try:
        o = build.rva_to_file_offset(pe, rva)
    except Exception:
        return set()
    buf = exe[o:o + size]
    out = set()
    i = 0
    while i < len(buf) - 4:
        if buf[i] == 0xE8:
            dest = rva + i + 5 + struct.unpack_from("<i", buf, i + 1)[0]
            if 0x1000 <= dest < 0xC00000:
                out.add(follow_ilt(exe, pe, dest))
            i += 5
        else:
            i += 1
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    emit = "--emit" in sys.argv
    src = Path(args[0])
    exe, pe, matched_addr, have, gh = load()
    obj = harvest.compile_obj(src if src.is_absolute() else ROOT / src, [])

    candidates = {}
    for sym in build.read_object_symbols(obj.read_bytes()):
        n = sym["name"]
        if n in have or not n.startswith("?") or sym["section"] <= 0:
            continue
        try:
            body, relocs = build.read_object_symbol_bytes(obj, n)
        except ValueError:
            continue
        mysz = len(body.rstrip(b"\xcc"))
        if mysz < 60:
            continue
        want = {follow_ilt(exe, pe, matched_addr[s]) for off, rt, s in relocs
                if rt == 0x0014 and s in matched_addr}
        if len(want) < 2:
            continue
        hits = [rva for rva, sz in gh if abs(sz - mysz) <= 24 and want.issubset(calls_in(exe, pe, rva, sz))]
        if len(hits) == 1:
            candidates[n] = (hits[0], mysz, len(want))

    if not candidates:
        print(f"{src.name}: no callee-signature placements")
        return
    print(f"{src.name}: {len(candidates)} callee-signature candidate(s)")
    for n, (rva, sz, w) in candidates.items():
        print(f"  0x{rva:06x} ~{sz}B ({w} callees) {n.split('@@')[0][:44]}")
    if emit:
        rows = (ROOT / "reverse" / "functions.csv").read_text().rstrip("\n").split("\n")
        h, b = rows[0], rows[1:]
        for n, (rva, sz, w) in candidates.items():
            b.append(f"{n},,0x{rva:08X},{sz},{src.as_posix()},matched,callee-located")
        b.sort(key=lambda r: r.split(",")[0])
        (ROOT / "reverse" / "functions.csv").write_text(h + "\n" + "\n".join(b) + "\n")
        print(f"emitted {len(candidates)} — run build.py to verify, drop FAILs")


if __name__ == "__main__":
    main()
