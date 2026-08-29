import sys
sys.path.insert(0, __import__("os").path.dirname(__file__))
import build
src, sym, rva, size = sys.argv[1], sys.argv[2], int(sys.argv[3], 16), int(sys.argv[4])
obj = build.obj_path(build.ROOT / src)
body, relocs = build.read_object_symbol_bytes(obj, sym, size)
tgt = build.read_target_bytes(rva, size)
m, r = bytearray(body[:size]), bytearray(tgt)
for off, _t, _s in relocs:
    if off + 4 <= size: m[off:off+4] = r[off:off+4] = b"\0\0\0\0"
same = sum(1 for a, b in zip(m, r) if a == b)
first = next((i for i, (a, b) in enumerate(zip(m, r)) if a != b), size)
print("agreement %d/%d (%.1f%%)  first-diff %d  compiled %d" % (same, size, same*100.0/size, first, len(body)))
