#!/usr/bin/env python3
"""Read the VC7.1 C++ unwind map behind a retail x86 EH prologue.

Usage: python3 tools/eh_info.py 0x005FFBB0

This reports addresses and cleanup instructions, not guessed C++ identities.
In constructors, receiver adjustments in the cleanup actions can distinguish
a composite base from several independent bases. Try/catch maps expose their
metadata-owned handlers, not proof of source identity or exception equivalence.
Use --prologue-offset only for an independently known prefix before the EH prologue.
Only `push -1; push handler` (optionally preceded by `mov eax,fs:[0]`) and the
`push -1; mov eax,fs:[0]; push handler; push eax; mov fs:[0],esp` form are
accepted; unsupported prologues fail explicitly.
"""
import argparse
from dataclasses import dataclass
import struct

IMAGE_BASE = 0x400000
MAGIC = 0x19930520


def unwind_info(read, rva):
    """Parse supported VC7.1 metadata using an injected read(RVA, size)."""
    lead = read(rva, 8)
    if lead[:6] == b"\x64\xa1\x00\x00\x00\x00":
        prologue = read(rva + 6, 7)
        if len(prologue) != 7 or prologue[:3] != b"\x6a\xff\x68":
            raise ValueError("unsupported EH prologue (expected push -1; push handler)")
        handler_va = struct.unpack_from("<I", prologue, 3)[0]
    elif lead == b"\x6a\xff\x64\xa1\x00\x00\x00\x00":
        prologue = read(rva, 21)
        if (len(prologue) != 21
                or prologue[:9] != b"\x6a\xff\x64\xa1\x00\x00\x00\x00\x68"
                or prologue[13:] != b"\x50\x64\x89\x25\x00\x00\x00\x00"):
            raise ValueError("unsupported EH prologue (expected push -1; push handler)")
        handler_va = struct.unpack_from("<I", prologue, 9)[0]
    else:
        prologue = lead[:7]
        if len(prologue) != 7 or prologue[:3] != b"\x6a\xff\x68":
            raise ValueError("unsupported EH prologue (expected push -1; push handler)")
        handler_va = struct.unpack_from("<I", prologue, 3)[0]
    handler = handler_va - IMAGE_BASE
    stub = read(handler, 10)
    if len(stub) != 10 or stub[0] != 0xB8 or stub[5] != 0xE9:
        raise ValueError("unsupported EH handler (expected mov eax,FuncInfo; jmp)")
    info = struct.unpack_from("<I", stub, 1)[0] - IMAGE_BASE
    header = read(info, 12)
    if len(header) != 12:
        raise ValueError("truncated FuncInfo")
    magic, count, table_va = struct.unpack("<IiI", header)
    if magic != MAGIC or not 0 <= count <= 4096:
        raise ValueError("unsupported FuncInfo magic or invalid unwind-state count")
    states = []
    for state in range(count):
        row = read(table_va - IMAGE_BASE + state * 8, 8)
        if len(row) != 8:
            raise ValueError("truncated unwind map")
        previous, action_va = struct.unpack("<iI", row)
        if not -1 <= previous < state:
            raise ValueError("invalid predecessor in unwind map")
        if action_va and action_va < IMAGE_BASE:
            raise ValueError("invalid cleanup action VA")
        states.append((state, previous, action_va - IMAGE_BASE if action_va else None))
    return handler, info, states


@dataclass(frozen=True)
class CatchHandler:
    adjectives: int
    type_descriptor_rva: int | None
    object_displacement: int
    handler_rva: int


@dataclass(frozen=True)
class TryBlock:
    try_low: int
    try_high: int
    catch_high: int
    handlers: tuple[CatchHandler, ...]


def _read_exact(read, rva, size, context):
    if rva < 0 or rva + size > 0x100000000 - IMAGE_BASE:
        raise ValueError(f"{context}: RVA range 0x{rva:X}+{size} exceeds the 32-bit image address space")
    try:
        data = read(rva, size)
    except (ValueError, OSError, SystemExit) as error:
        raise ValueError(f"{context}: cannot read RVA 0x{rva:08X}: {error}") from error
    if len(data) != size:
        raise ValueError(f"{context}: truncated at RVA 0x{rva:08X} (wanted {size} bytes, got {len(data)})")
    return data


def _pointer_rva(va, context):
    if va < IMAGE_BASE:
        raise ValueError(f"{context}: invalid VA 0x{va:08X} below image base")
    return va - IMAGE_BASE


def catch_info(read, info_rva) -> tuple[TryBlock, ...]:
    """Decode VC7.1 try ranges and HandlerType records, without inferring identities."""
    header = _read_exact(read, info_rva, 20, "FuncInfo catch header")
    magic, state_count, _, count, table_va = struct.unpack("<IiIII", header)
    if magic != MAGIC or not 0 <= state_count <= 4096:
        raise ValueError("FuncInfo catch header: unsupported magic or invalid unwind-state count")
    if count > 4096:
        raise ValueError(f"FuncInfo catch header: invalid try-block count {count}")
    if not count:
        return ()
    table = _read_exact(read, _pointer_rva(table_va, "try-block map"), count * 20, "try-block map")
    blocks = []
    for index in range(count):
        context = f"try block {index}"
        low, high, catch_high, handler_count, handlers_va = struct.unpack_from("<iiiiI", table, index * 20)
        if not 0 <= low <= high <= catch_high < state_count:
            raise ValueError(f"{context}: invalid state range {low}..{high}/catch-high {catch_high} for {state_count} states")
        if not 1 <= handler_count <= 4096:
            raise ValueError(f"{context}: invalid handler count {handler_count}")
        records = _read_exact(read, _pointer_rva(handlers_va, context + " handlers"), handler_count * 16, context + " handlers")
        handlers = []
        for handler_index in range(handler_count):
            label = f"{context} handler {handler_index}"
            adjectives, type_va, displacement, handler_va = struct.unpack_from("<IIiI", records, handler_index * 16)
            handler_rva = _pointer_rva(handler_va, label)
            _read_exact(read, handler_rva, 1, label)
            type_rva = _pointer_rva(type_va, label + " TypeDescriptor") if type_va else None
            if type_rva is not None:
                # TypeDescriptor's two pointer words must be followed by at least one name byte.
                _read_exact(read, type_rva, 9, label + " TypeDescriptor")
            handlers.append(CatchHandler(adjectives, type_rva, displacement, handler_rva))
        blocks.append(TryBlock(low, high, catch_high, tuple(handlers)))
    return tuple(blocks)


def action_instructions(read, rva):
    """Show only the cleanup action, stopping at its first transfer/return.

    A terminal direct jump often targets an ILT thunk. Resolve one E9 hop,
    but do not disassemble a whole callee or mistake its first ret for its
    full boundary.
    """
    try:
        from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    except ImportError:
        raise ValueError("eh_info.py requires capstone in the active Python environment")
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    for insn in disassembler.disasm(read(rva, 64), rva + IMAGE_BASE):
        line = f"    RVA 0x{insn.address - IMAGE_BASE:08X}: {insn.mnemonic} {insn.op_str}"
        if insn.size == 5 and insn.bytes[0] == 0xE9:
            target = insn.address + 5 + struct.unpack_from("<i", insn.bytes, 1)[0] - IMAGE_BASE
            thunk = read(target, 5)
            if len(thunk) == 5 and thunk[0] == 0xE9:
                resolved = target + 5 + struct.unpack_from("<i", thunk, 1)[0]
                line += f"  [ILT -> RVA 0x{resolved:08X}]"
        yield line
        if insn.mnemonic.startswith("j") or insn.mnemonic.startswith("ret"):
            return
    raise ValueError("cleanup action exceeds supported 64-byte display window")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("rva", type=lambda text: int(text, 0))
    parser.add_argument("--prologue-offset", type=lambda text: int(text, 0), default=0,
                        help="independently known byte offset to the supported EH prologue; never scans")
    args = parser.parse_args()
    if not 0 <= args.rva <= args.rva + args.prologue_offset < 0x100000000 - IMAGE_BASE:
        parser.error("EH prologue RVA/offset must be within the 32-bit image address space")
    import build
    try:
        handler, info, states = unwind_info(build.read_target_bytes, args.rva + args.prologue_offset)
        blocks = catch_info(build.read_target_bytes, info)
        if args.prologue_offset:
            print(f"EH prologue RVA 0x{args.rva + args.prologue_offset:08X} (input +0x{args.prologue_offset:X})")
        print(f"handler RVA 0x{handler:08X}; FuncInfo RVA 0x{info:08X}; {len(states)} unwind states")
        for state, previous, action in states:
            print(f"state {state} -> {previous}: " + (f"cleanup RVA 0x{action:08X}" if action is not None else "no cleanup"))
            if action is not None:
                for line in action_instructions(build.read_target_bytes, action):
                    print(line)
        print(f"{len(blocks)} try block(s)")
        for index, block in enumerate(blocks):
            print(f"try {index}: states {block.try_low}..{block.try_high}; catch-high {block.catch_high}")
            for handler_index, entry in enumerate(block.handlers):
                kind = ("catch-all" if entry.type_descriptor_rva is None else
                        f"typed (TypeDescriptor RVA 0x{entry.type_descriptor_rva:08X})")
                print(f"  catch {handler_index}: {kind}; handler RVA 0x{entry.handler_rva:08X}; "
                      f"adjectives 0x{entry.adjectives:08X}; object displacement {entry.object_displacement:+#x}")
        print("Metadata topology/cleanup addresses do not prove source identity, boundaries or exception equivalence.")
    except (ValueError, struct.error) as error:
        parser.exit(1, f"eh_info: {error}\n")


if __name__ == "__main__":
    main()
