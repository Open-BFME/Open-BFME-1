#!/usr/bin/env python3
"""Read the VC7.1 C++ unwind map behind a retail x86 EH prologue.

Usage: python3 tools/eh_info.py 0x005FFBB0

This reports addresses and cleanup instructions, not guessed C++ identities.
In constructors, receiver adjustments in the cleanup actions can distinguish
a composite base from several independent bases. It does not decode catch
maps or prove that a reconstruction has the correct exception behavior.
Only `push -1; push handler` (optionally preceded by `mov eax,fs:[0]`) and the
`push -1; mov eax,fs:[0]; push handler; push eax; mov fs:[0],esp` form are
accepted; unsupported prologues fail explicitly.
"""
import argparse
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
    args = parser.parse_args()
    import build
    try:
        handler, info, states = unwind_info(build.read_target_bytes, args.rva)
        print(f"handler RVA 0x{handler:08X}; FuncInfo RVA 0x{info:08X}; {len(states)} unwind states")
        for state, previous, action in states:
            print(f"state {state} -> {previous}: " + (f"cleanup RVA 0x{action:08X}" if action is not None else "no cleanup"))
            if action is not None:
                for line in action_instructions(build.read_target_bytes, action):
                    print(line)
        print("Addresses/cleanup adjustments are evidence, not source identities or full callee boundaries.")
    except (ValueError, struct.error) as error:
        parser.exit(1, f"eh_info: {error}\n")


if __name__ == "__main__":
    main()
