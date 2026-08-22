#!/usr/bin/env python3
"""Append a code-cave section to a PE and install jmp-rel32 detours into it.

The strict verifier in build.py/patch.py can only write a function body back
over itself, byte for byte. A mod that grows a body has nowhere to put it.
This adds that place: a new section at the end of the image, plus trampolines
that redirect a target address into it and return.

Nothing here is a fallback. Every case this cannot handle raises.
"""
import struct
import sys
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

SECTION_NAME = ".bfmemod"
CHARACTERISTICS = 0xE0000020  # CODE | EXECUTE | READ | WRITE
JMP_REL32 = 0xE9
NOP = 0x90


class CaveError(RuntimeError):
    pass


class PE:
    def __init__(self, path):
        self.path = Path(path)
        self.data = bytearray(self.path.read_bytes())
        self.pe = struct.unpack_from("<I", self.data, 0x3C)[0]
        if self.data[self.pe:self.pe + 4] != b"PE\0\0":
            raise CaveError(f"{path}: not a PE")
        self.opt = self.pe + 24
        self.n_sections = struct.unpack_from("<H", self.data, self.pe + 6)[0]
        self.opt_size = struct.unpack_from("<H", self.data, self.pe + 20)[0]
        self.image_base = struct.unpack_from("<I", self.data, self.opt + 28)[0]
        self.sect_align = struct.unpack_from("<I", self.data, self.opt + 32)[0]
        self.file_align = struct.unpack_from("<I", self.data, self.opt + 36)[0]
        self.sect_table = self.opt + self.opt_size
        self.size_of_headers = struct.unpack_from("<I", self.data, self.opt + 60)[0]

    # --- section table -------------------------------------------------
    def sections(self):
        out = []
        for i in range(self.n_sections):
            o = self.sect_table + i * 40
            name = self.data[o:o + 8].rstrip(b"\0").decode("ascii", "replace")
            vsize, vaddr, rsize, raddr = struct.unpack_from("<IIII", self.data, o + 8)
            chars = struct.unpack_from("<I", self.data, o + 36)[0]
            out.append(dict(i=i, off=o, name=name, vsize=vsize, vaddr=vaddr,
                            rsize=rsize, raddr=raddr, chars=chars))
        return out

    def rva_to_off(self, rva):
        for s in self.sections():
            if s["vaddr"] <= rva < s["vaddr"] + max(s["vsize"], s["rsize"]):
                off = s["raddr"] + (rva - s["vaddr"])
                if off >= len(self.data):
                    raise CaveError(f"rva 0x{rva:X} maps past end of file")
                return off
        raise CaveError(f"rva 0x{rva:X} is not in any section")

    def read(self, rva, n):
        o = self.rva_to_off(rva)
        return bytes(self.data[o:o + n])

    def write(self, rva, blob):
        o = self.rva_to_off(rva)
        self.data[o:o + len(blob)] = blob

    # --- cave ----------------------------------------------------------
    def add_cave(self, size, name=SECTION_NAME):
        """Append a section. Returns its RVA. Requires header slack and a file
        that ends exactly at its last raw section."""
        if any(s["name"] == name for s in self.sections()):
            raise CaveError(f"section {name} already present")
        used = self.sect_table + self.n_sections * 40
        if used + 40 > self.size_of_headers:
            raise CaveError("no room in the PE header for another section entry")

        last = max(self.sections(), key=lambda s: s["raddr"] + s["rsize"])
        file_end = last["raddr"] + last["rsize"]
        if file_end != len(self.data):
            raise CaveError(
                f"file does not end at its last raw section "
                f"(end 0x{file_end:X}, size 0x{len(self.data):X}); appending is unsafe")

        vsize = self._align(size, self.sect_align)
        rsize = self._align(size, self.file_align)
        vaddr = self._align(max(s["vaddr"] + s["vsize"] for s in self.sections()),
                            self.sect_align)
        raddr = file_end

        o = used
        struct.pack_into("<8s", self.data, o, name.encode())
        struct.pack_into("<IIII", self.data, o + 8, vsize, vaddr, rsize, raddr)
        # +0x18 PointerToRelocations, +0x1C PointerToLinenumbers,
        # +0x20/+0x22 the two counts, +0x24 Characteristics.
        struct.pack_into("<IIHHI", self.data, o + 24, 0, 0, 0, 0, CHARACTERISTICS)
        self.data.extend(b"\0" * rsize)

        self.n_sections += 1
        struct.pack_into("<H", self.data, self.pe + 6, self.n_sections)
        struct.pack_into("<I", self.data, self.opt + 56,
                         self._align(vaddr + vsize, self.sect_align))  # SizeOfImage
        struct.pack_into("<I", self.data, self.opt + 64, 0)            # CheckSum
        self.cave_rva = vaddr
        self.cave_size = vsize
        self.cave_used = 0
        return vaddr

    @staticmethod
    def _align(v, a):
        return (v + a - 1) // a * a

    def next_rva(self, align=16):
        """Where the next aligned allocation will land. Callers that must
        assemble against their own address need this before they have bytes."""
        return self.cave_rva + self._align(self.cave_used, align)

    def alloc(self, blob, align=16):
        """Bump-allocate bytes inside the cave. Returns the RVA written to.

        Alignment is not cosmetic: yasm's bin output pads a section whose org
        is unaligned, which silently shifts the entry point away from the
        address the trampoline was built to jump to.
        """
        if not hasattr(self, "cave_rva"):
            raise CaveError("add_cave() must run before alloc()")
        self.cave_used = self._align(self.cave_used, align)
        if self.cave_used + len(blob) > self.cave_size:
            raise CaveError(f"cave exhausted: need {len(blob)}, "
                            f"have {self.cave_size - self.cave_used}")
        rva = self.cave_rva + self.cave_used
        self.write(rva, blob)
        self.cave_used += len(blob)
        return rva

    # --- detours -------------------------------------------------------
    def _steal(self, rva, need=5):
        """Return (bytes, length) covering whole instructions of >= `need` bytes."""
        md = Cs(CS_ARCH_X86, CS_MODE_32)
        md.detail = True
        blob = self.read(rva, 32)
        taken = 0
        insns = []
        for ins in md.disasm(blob, self.image_base + rva):
            insns.append(ins)
            taken += ins.size
            if taken >= need:
                break
        if taken < need:
            raise CaveError(f"could not decode {need} bytes at rva 0x{rva:X}")
        return bytes(blob[:taken]), taken, insns

    def _relocate(self, insns, src_rva, dst_rva):
        """Re-emit stolen instructions at a new address, fixing rel operands.
        Raises on any relative form this does not explicitly handle."""
        out = bytearray()
        cur_src = src_rva
        for ins in insns:
            raw = bytes(ins.bytes)
            op = raw[0]
            if op == 0xE8 or op == 0xE9:              # call/jmp rel32
                target = cur_src + ins.size + struct.unpack_from("<i", raw, 1)[0]
                new_from = dst_rva + len(out)
                out += bytes([op]) + struct.pack("<i", target - (new_from + 5))
            elif 0x70 <= op <= 0x7F or op in (0xEB, 0xE3):
                raise CaveError(
                    f"short relative branch {ins.mnemonic} at 0x{cur_src:X} in the "
                    f"stolen prologue; pick a different hook address")
            elif op == 0x0F and 0x80 <= raw[1] <= 0x8F:   # jcc rel32
                target = cur_src + ins.size + struct.unpack_from("<i", raw, 2)[0]
                new_from = dst_rva + len(out)
                out += raw[:2] + struct.pack("<i", target - (new_from + 6))
            else:
                for g in ins.groups:
                    if ins.group_name(g) in ("branch_relative", "jump", "call"):
                        raise CaveError(
                            f"unhandled relative instruction {ins.mnemonic} "
                            f"{ins.op_str} at 0x{cur_src:X}")
                out += raw
            cur_src += ins.size
        return bytes(out)

    def detour(self, target_rva, payload=b"", tail=b""):
        """Redirect target_rva into the cave.

        Cave layout: [payload][relocated stolen prologue][tail][jmp back].
        `payload` runs before the original code, `tail` after it. Both must
        preserve every register the original body relies on.
        Returns the cave RVA the target now jumps to.
        """
        stolen, n, insns = self._steal(target_rva, 5)
        # Resolve the landing address before emitting: relocation and the
        # caller's own assembly both have to agree on where this blob starts.
        start = self.next_rva()
        moved = self._relocate(insns, target_rva, start + len(payload))
        back = target_rva + n
        body = bytearray(payload) + moved + tail
        jmp_from = start + len(body)
        body += bytes([JMP_REL32]) + struct.pack("<i", back - (jmp_from + 5))
        self.alloc(bytes(body))

        trampoline = bytes([JMP_REL32]) + struct.pack("<i", start - (target_rva + 5))
        trampoline += bytes([NOP]) * (n - 5)
        self.write(target_rva, trampoline)
        return start

    def save(self, out):
        out = Path(out)
        out.write_bytes(bytes(self.data))
        return out


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("exe")
    ap.add_argument("-o", "--output", required=True)
    ap.add_argument("--size", type=lambda v: int(v, 0), default=0x10000)
    ap.add_argument("--nop-detour", type=lambda v: int(v, 0), action="append",
                    default=[], help="RVA to detour with an empty payload (identity)")
    a = ap.parse_args()

    pe = PE(a.exe)
    rva = pe.add_cave(a.size)
    print(f"cave .bfmemod at RVA 0x{rva:08X} size 0x{pe.cave_size:X}")
    for t in a.nop_detour:
        c = pe.detour(t)
        print(f"  detour 0x{t:08X} -> cave 0x{c:08X} (identity)")
    p = pe.save(a.output)
    print(f"wrote {p} ({len(pe.data):,} bytes)")


if __name__ == "__main__":
    sys.exit(main())
