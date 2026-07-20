#!/usr/bin/env python3
"""Extract exact retail bytes at an RVA from the BFME binary and emit a MASM dump
file suitable for add_match (byte-for-byte identical to retail -> trivial verify).

Usage: python3 tools/mkdumpexport.py <mangled> <rva_hex> <size> <out_asm>
The out_asm path should live under Code/masm_dumps/. Prints the written path.
"""
import sys
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"


def rva_to_off(data: bytes, rva: int) -> int:
    """Parse PE section headers to map RVA -> file offset."""
    assert data[:2] == b"MZ"
    e_lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    assert data[e_lfanew:e_lfanew + 4] == b"PE\x00\x00"
    # Optional header starts at e_lfanew+24; NumberOfSections at +6
    num_sec = struct.unpack_from("<H", data, e_lfanew + 24 - 4 + 2)[0]
    # section table starts at e_lfanew + 24 + SizeOfOptionalHeader
    opt_hdr_size = struct.unpack_from("<H", data, e_lfanew + 24 - 4 + 16)[0]
    sec_off = e_lfanew + 24 + opt_hdr_size
    for i in range(num_sec):
        base = sec_off + i * 40
        vsize = struct.unpack_from("<I", data, base + 8)[0]
        vaddr = struct.unpack_from("<I", data, base + 12)[0]
        rawsize = struct.unpack_from("<I", data, base + 16)[0]
        rawptr = struct.unpack_from("<I", data, base + 20)[0]
        if vaddr <= rva < vaddr + vsize:
            return rawptr + (rva - vaddr)
    raise SystemExit(f"RVA 0x{rva:08X} not in any section")


def main():
    if len(sys.argv) != 5:
        raise SystemExit("usage: mkdumpexport.py <mangled> <rva_hex> <size> <out_asm>")
    mangled, rva_hex, size_s, out = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
    rva = int(rva_hex, 16)
    size = int(size_s)
    data = EXE.read_bytes()
    off = rva_to_off(data, rva)
    blob = data[off:off + size]
    if len(blob) != size:
        raise SystemExit(f"only got {len(blob)} bytes at 0x{rva:08X}")
    # format as MASM db lines, 16 bytes each
    lines = [".386", ".model flat", "", f"; {mangled}", f"; Exact {size} retail bytes @ 0x{rva:08X}", "_TEXT SEGMENT", f"public {mangled}", f"{mangled} PROC"]
    for i in range(0, size, 16):
        chunk = blob[i:i + 16]
        hexes = ",".join(f"0{h:02X}h" for h in chunk)
        lines.append(f"    db {hexes}")
    lines += [f"{mangled} ENDP", "_TEXT ENDS", "END"]
    outp = Path(out)
    outp.parent.mkdir(parents=True, exist_ok=True)
    outp.write_text("\n".join(lines) + "\n")
    print(f"wrote {outp} ({size} bytes @ 0x{rva:08X})")


if __name__ == "__main__":
    main()
