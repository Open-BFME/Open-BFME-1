import sys, csv, re
sys.path.insert(0, __import__("os").path.dirname(__file__))
import build
from pathlib import Path

dest = sys.argv[1]
obj = build.obj_path(build.ROOT / dest)
stat = obj.stat()
_d, _s, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
objnames = set(s["name"] for s in symbols)

# every donor file carrying a marker for this destination
donors = {}
for p in Path("Code").rglob("*.cpp"):
    try: t = p.read_text(errors="ignore")
    except Exception: continue
    m = re.search(r"// readable body of ([^:]+): (\S+)", t)
    if m and m.group(2) == dest:
        donors[str(p)] = m.group(1).strip()

rows = {}
for line in Path("reverse/functions.csv").read_bytes().decode("utf-8", "replace").splitlines():
    f = next(csv.reader([line]), [])
    if len(f) >= 5 and f[4] in donors:
        rows.setdefault(f[4], []).append((f[0], int(f[2], 16), int(f[3])))

out = []
for src, rs in rows.items():
    for name, rva, size in rs:
        cand = name if name in objnames else None
        if cand is None:
            hits = [n for n in objnames if n.startswith(name.rstrip("@"))]
            cand = hits[0] if len(hits) == 1 else None
        if cand is None:
            out.append((-1, size, Path(src).name, "no unique object symbol")); continue
        try:
            body, relocs = build.read_object_symbol_bytes(obj, cand, size)
        except Exception as e:
            out.append((-1, size, Path(src).name, str(e)[:48])); continue
        tgt = build.read_target_bytes(rva, size)
        m2, r2 = bytearray(body[:size]), bytearray(tgt)
        for off, _t, _s2 in relocs:
            if off + 4 <= size: m2[off:off+4] = r2[off:off+4] = b"\0\0\0\0"
        same = sum(1 for a, b in zip(m2, r2) if a == b)
        first = next((i for i, (a, b) in enumerate(zip(m2, r2)) if a != b), size)
        out.append((same*100.0/size, size, Path(src).name,
                    "first-diff %d  compiled %d" % (first, len(body))))
for pct, size, nm, note in sorted(out, reverse=True):
    print("%6s  %5dB  %-56s %s" % ("%.1f%%" % pct if pct >= 0 else "  -", size, nm, note))
