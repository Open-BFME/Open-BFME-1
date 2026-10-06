"""Retail-derived evidence for one ledger row: what the retail bytes call, read and switch on.

The gate already proves a landed row's bytes; what bytes with masked relocations
cannot prove is WHICH callee, global, string or case target the relocations
point at, and whether the row's name is supported. So the judge gets retail's
side of exactly that, read from the retail image (never from the author's notes):

  - the disassembly (capped), each call/jump target named from the ledger or
    symbols.csv as of the audited revision, imports as DLL!name;
  - every in-image data reference, shown as the string literal it points at when
    it is one, else the ledger/symbol name;
  - jump tables read out of retail as case index -> target offset.

Names in this evidence come from the ledgers and may themselves be wrong; the
rubric says so.
"""
import functools
import string
import sys

import common

MAX_INSNS = 260
PRINTABLE = set(string.printable.encode()) - set(b"\x0b\x0c")


@functools.lru_cache(maxsize=1)
def image():
    import pefile
    path = common.os.environ.get("AUDIT_RETAIL")
    if not path:
        sys.path.insert(0, str(common.ROOT / "tools"))
        import build  # the repo's own pinned retail image path
        path = str(build.EXE)
    pe = pefile.PE(path, fast_load=True)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    imports = {}
    for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for imp in entry.imports:
            name = imp.name.decode() if imp.name else f"#{imp.ordinal}"
            imports[imp.address - pe.OPTIONAL_HEADER.ImageBase] = f"{entry.dll.decode()}!{name}"
    return pe, pe.OPTIONAL_HEADER.ImageBase, imports


@functools.lru_cache(maxsize=1)
def names():
    """rva -> name from the ledger and symbols.csv of the audited tree."""
    out = {}
    for row in common.read_rows((common.ROOT / common.SYMBOLS).read_text(encoding="utf-8", errors="replace")
                                if (common.ROOT / common.SYMBOLS).exists() else ""):
        rva = common.parse_rva(row.get("address"))
        if rva is not None:
            out.setdefault(rva, row["name"])
    for row in common.ledger_at():
        rva = common.parse_rva(row.get("target_rva"))
        if rva is not None:
            out[rva] = row["name"]
    return out


def read(rva, size):
    pe, _, _ = image()
    try:
        return pe.get_data(rva, size)
    except Exception:
        return b""


def c_string(rva, limit=120):
    data = read(rva, limit + 1)
    end = data.find(b"\0")
    if end >= 4 and all(b in PRINTABLE for b in data[:end]):
        return data[:end].decode("latin-1")
    return None


def describe(rva):
    """How the evidence shows an in-image address."""
    _, _, imports = image()
    if rva in imports:
        return imports[rva]
    text = c_string(rva)
    if text is not None:
        return f'"{text}"' + (" ..." if len(text) >= 120 else "")
    name = names().get(rva)
    return common.short_name(name) if name else f"unnamed@0x{rva:08X}"


def jump_table(rva, start, size, base):
    """Entries of a retail jump table that land inside the function [start, start+size)."""
    out = []
    for i in range(64):
        raw = read(rva + 4 * i, 4)
        if len(raw) < 4:
            break
        target = int.from_bytes(raw, "little") - base
        if not start <= target < start + size:
            break
        out.append(target - start)
    return out


def retail_evidence(rva, size):
    """Text block: the retail function, its references resolved, for the judge packet."""
    import capstone
    pe, base, imports = image()
    code = read(rva, size)
    if not code:
        return f"(retail bytes at 0x{rva:08X} unavailable)"
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    lines, refs, tables = [], {}, []
    span = pe.OPTIONAL_HEADER.SizeOfImage
    count = -1
    for count, insn in enumerate(md.disasm(code, base + rva)):
        note = ""
        for op in insn.operands:
            value = None
            if op.type == capstone.x86.X86_OP_IMM:
                value = op.imm
            elif op.type == capstone.x86.X86_OP_MEM and op.mem.base == 0:
                value = op.mem.disp
                if op.mem.index and op.mem.scale == 4 and insn.mnemonic == "jmp":
                    entries = jump_table(value - base, rva, size, base)
                    if entries:
                        tables.append(f"jump table 0x{value - base:08X}: " + ", ".join(
                            f"case {i}->+0x{off:X}" for i, off in enumerate(entries)))
            if value is None:
                continue
            target = (value & 0xFFFFFFFF) - base
            if 0 < target < span and not rva <= target < rva + size:
                text = describe(target)
                refs[target] = text
                note = f"   ; {text}"
        if count < MAX_INSNS:
            lines.append(f"+0x{insn.address - base - rva:04X}  {insn.mnemonic} {insn.op_str}{note}")
    if count >= MAX_INSNS:
        lines.append(f"... ({count + 1 - MAX_INSNS} more instructions)")
    out = [f"retail function 0x{rva:08X}, {size} bytes", *lines]
    if refs:
        out.append("references (retail address -> ledger name / string / import):")
        out += [f"  0x{t:08X} {refs[t]}" for t in sorted(refs)]
    out += tables
    return "\n".join(out)
