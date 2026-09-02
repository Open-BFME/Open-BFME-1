#!/usr/bin/env python3
"""Read and write BFME .big archives.

    BIGF
    u32 LE  archive size
    u32 BE  file count
    u32 BE  header size
    per file: u32 BE offset, u32 BE size, NUL-terminated name
    then the payloads, in table order

Two packers wrote the archives this game ships, and they disagree about layout:

  * the APT packages (`apt/*.big`, "Created by AptToBigc") start every payload
    on a **4-byte boundary**, and their header-size field is one less than the
    first payload offset
  * `window.big` is **contiguous** -- no alignment, no gaps -- and its
    header-size field IS the first payload offset

So `write` takes the convention rather than assuming one, and `conventions_of`
recovers it from an existing archive. Run this file on any .big to self-check:
it recovers the convention, repacks the archive from its own contents, and
compares. A correct writer is byte-identical.
"""
import hashlib
import os
import struct
import sys


def read(path):
    """-> [(name, bytes)] in table order."""
    d = open(path, "rb").read()
    if d[:4] not in (b"BIGF", b"BIG4"):
        raise ValueError(f"{path}: not a BIG archive (magic {d[:4]!r})")
    count, _hdr = struct.unpack_from(">II", d, 8)
    off, out = 16, []
    for _ in range(count):
        o, s = struct.unpack_from(">II", d, off)
        off += 8
        end = d.index(b"\0", off)
        out.append((d[off:end].decode("latin1"), d[o:o + s]))
        off = end + 1
    return out


def conventions_of(path):
    """-> (align, gap, header_bias), the layout rules the archive was written with.

    `gap` is the literal bytes between the end of the entry table and the first
    payload -- not padding: the retail packer writes its own marker there
    (`L219` in window.big), and zero-filling it is the difference between a
    byte-identical repack and a wrong one. `header_bias` is
    first_payload_offset - header_size_field."""
    d = open(path, "rb").read()
    count, hdr = struct.unpack_from(">II", d, 8)
    off, offsets = 16, []
    for _ in range(count):
        o, _s = struct.unpack_from(">II", d, off)
        off += 8
        off = d.index(b"\0", off) + 1
        offsets.append(o)
    align = 4 if all(o % 4 == 0 for o in offsets) else 1
    return d[:4], align, d[off:offsets[0]], offsets[0] - hdr


def write(path, files, magic=b"BIGF", align=4, gap=b"\0", header_bias=1):
    """`files` is [(name, bytes)] in the order they should appear."""
    table = 16 + sum(8 + len(n) + 1 for n, _ in files)
    pad = lambda v: (v + align - 1) // align * align
    start = pad(table + len(gap))
    offsets, cur = [], start
    for _n, blob in files:
        cur = pad(cur)
        offsets.append(cur)
        cur += len(blob)

    out = bytearray()
    out += magic
    out += struct.pack("<I", cur)
    out += struct.pack(">II", len(files), start - header_bias)
    for (name, blob), o in zip(files, offsets):
        out += struct.pack(">II", o, len(blob)) + name.encode("latin1") + b"\0"
    out += gap
    for (_n, blob), o in zip(files, offsets):
        out += b"\0" * (o - len(out))
        out += blob
    open(path, "wb").write(bytes(out))
    return len(out)


def main():
    if len(sys.argv) != 2:
        raise SystemExit("usage: bigpack.py <archive.big>    (self-check)")
    src = os.path.expanduser(sys.argv[1])
    files = read(src)
    magic, align, gap, bias = conventions_of(src)
    tmp = "/tmp/bigpack-selfcheck.big"
    n = write(tmp, files, magic=magic, align=align, gap=gap, header_bias=bias)
    a = hashlib.md5(open(src, "rb").read()).hexdigest()
    b = hashlib.md5(open(tmp, "rb").read()).hexdigest()
    print(f"{os.path.basename(src)}: {len(files)} files, {magic.decode()}, "
          f"align {align}, gap {gap!r}, header bias {bias}, {n} bytes")
    print(f"  original {a}")
    print(f"  repacked {b}   {'IDENTICAL' if a == b else 'DIFFERS'}")
    os.unlink(tmp)
    return 0 if a == b else 1


if __name__ == "__main__":
    sys.exit(main())
