#!/usr/bin/env python3
"""Flag ledger rows whose retail stack cleanup contradicts their decorated name.

A callee-cleaned convention (__thiscall, __stdcall, __fastcall) ends in
`ret N`, and N is fixed by the parameter list encoded in the symbol. A parsed
ordinary __cdecl function is caller-cleaned, so its fixed cleanup is `ret 0`;
when either rule disagrees with the bytes the row's identity is wrong --
typically a naked dump parked under a borrowed name, or an ICF alias whose body
belongs to a different function. Those rows still byte-match, so the normal
gate cannot see the problem, but they cannot be converted to clean C++ without
renaming.

Conservative by construction: anything whose return or parameter list this
cannot parse with certainty (templates, by-value classes, hidden return ABIs,
varargs) is skipped rather than guessed at. Exit 0 always; this reports, it
does not gate.
"""
import argparse
import csv
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXE = ROOT / "inputs/baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"

# Calling-convention letter -> who cleans the stack. A parsed __cdecl signature
# is the one caller-cleaned case whose cleanup is still known: it must end in
# `ret 0`, regardless of its fixed ordinary arguments.
CALLEE_CLEANS = {"E": "__thiscall", "G": "__stdcall", "I": "__fastcall"}
CONVENTIONS = {"A": "__cdecl", **CALLEE_CLEANS}

# Access codes for static members: these encode no `this` cv qualifier, so the
# convention letter follows immediately instead of one position later.
STATIC_MEMBER = set("CDKLST")

# Primitive type codes and their stack footprint in bytes.
PRIMITIVE = {
    "C": 4, "D": 4, "E": 4, "F": 4, "G": 4, "H": 4, "I": 4,
    "J": 4, "K": 4, "M": 4, "N": 8, "O": 8, "X": 0, "Z": 0,
}
EXTENDED = {"_N": 4, "_J": 8, "_K": 8, "_W": 4, "_D": 4, "_E": 4, "_F": 4, "_G": 4, "_H": 4, "_I": 4}


def rva_to_offset(data, rva):
    lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    coff = lfanew + 4
    count = struct.unpack_from("<H", data, coff + 2)[0]
    opt = struct.unpack_from("<H", data, coff + 16)[0]
    base = coff + 20 + opt
    for i in range(count):
        o = base + i * 40
        vsize, va, rsize, raw = struct.unpack_from("<IIII", data, o + 8)
        if va <= rva < va + max(vsize, rsize):
            return raw + (rva - va)
    return None


def skip_qualified_name(sym, i):
    """Step over a qualified name: components separated by '@', empty terminates.

    A component is either an identifier or a single digit back-reference, so
    `Coord2DBase@@` and `0@` are both one complete name. Scanning for a literal
    '@@' instead would run straight past a back-reference and swallow the
    parameter list behind it.
    """
    while True:
        if i >= len(sym):
            raise ValueError("unterminated qualified name")
        if sym[i] == "@":                 # empty component ends the name
            return i + 1
        if sym[i] == "?":                 # template / special component
            raise ValueError("templated name component")
        if sym[i].isdigit():              # back-reference component
            i += 1
            continue
        j = sym.find("@", i)
        if j < 0:
            raise ValueError("unterminated name component")
        i = j + 1


def skip_type(sym, i):
    """Step over one encoded type and return the next index.

    Unlike arg_size this accepts records, because a class is perfectly legal as
    the pointee of a pointer even though it cannot be passed by value here.
    """
    if i >= len(sym):
        raise ValueError("truncated type")
    ch = sym[i]
    if ch == "_":
        if sym[i:i + 2] not in EXTENDED:
            raise ValueError(f"unknown extended type {sym[i:i + 2]}")
        return i + 2
    if ch in "PAQR":                     # pointer / reference, plus cv variants
        j = i + 1
        if j < len(sym) and sym[j] in "ABCD":
            j += 1
        return skip_type(sym, j)
    if ch in "VUT":                      # class / struct / union
        return skip_qualified_name(sym, i + 1)
    if ch == "W":                        # enum: W<n><name>@@
        return skip_qualified_name(sym, i + 2)
    if ch in PRIMITIVE:
        return i + 1
    raise ValueError(f"unknown type code {ch!r}")


def arg_size(sym, i):
    """Return (stack_bytes, in_register_eligible, next_index) for a parameter.

    Only integer-like values of exactly one dword can ride in a __fastcall
    register; floating point always goes on the stack regardless of position.
    """
    if i >= len(sym):
        raise ValueError("truncated parameter")
    ch = sym[i]
    if ch in "VUT":
        raise ValueError("by-value record: size unknown")
    if ch == "_":
        size = EXTENDED[sym[i:i + 2]]
        return size, size == 4, skip_type(sym, i)
    if ch in "MNO":                      # float, double, long double
        return PRIMITIVE[ch], False, skip_type(sym, i)
    if ch in PRIMITIVE and ch not in "PAQRW":
        return PRIMITIVE[ch], PRIMITIVE[ch] == 4, skip_type(sym, i)
    return 4, True, skip_type(sym, i)    # pointer, reference or enum


def cdecl_return_is_known(sym, i):
    """Whether a cdecl return has a fixed, non-hidden x86 ABI.

    User-defined by-value returns can use a hidden sret argument, while a
    scalar, pointer, reference, enum, or void return cannot. The caller-cleanup
    result is useful only after this distinction and the complete signature
    have both been proven.
    """
    if i >= len(sym):
        return False
    if sym[i:i + 2] in EXTENDED:
        return True
    ch = sym[i]
    if ch in "VUT":                 # by-value class/struct/union
        return False
    if ch == "Z":                   # parameter-list marker, not a return type
        return False
    return ch in PRIMITIVE or ch in "PAQRW"


def expected_ret(sym):
    """Bytes the body must pop, or None when cleanup cannot be decided safely."""
    m = re.search(r"@@([A-Z])", sym)
    if not m:
        return None, None
    lead = m.group(1)
    if lead == "Y" or lead in STATIC_MEMBER:
        # free function (Y<conv>) or static member (<access><conv>): neither has
        # a `this` cv-qualifier letter, so the convention follows immediately.
        pos = m.end() - 1 + 1
    else:
        # non-static member: <access><this-cv><convention>
        pos = m.end() + 1
    if pos >= len(sym):
        return None, None
    convention = CONVENTIONS.get(sym[pos])
    if convention is None:
        return None, None
    # A template name has additional grammar before the calling-convention
    # marker. Do not let the `@@` belonging to one of its encoded components
    # turn an incomplete cdecl parse into a confident cleanup claim. Preserve
    # the established callee-cleaned parser behavior for existing aliases.
    if convention == "__cdecl" and "?$" in sym:
        return None, None
    i = pos + 1
    try:
        # Constructors and destructors encode no return type at all -- the
        # convention letter is followed straight by '@'. Handing that to
        # skip_type drifts the parse, which is why every ??0 and ??1 row was
        # being skipped as unparsable. They are the easiest rows to check, not
        # the hardest: a destructor takes nothing and must pop nothing.
        special_member = re.match(r"\?\?[01]", sym)
        if special_member and convention == "__cdecl":
            return None, None       # no scalar return ABI to prove
        if special_member and i < len(sym) and sym[i] == "@":
            i += 1
        else:
            if convention == "__cdecl" and not cdecl_return_is_known(sym, i):
                return None, None
            i = skip_type(sym, i)         # return type
        total = 0
        registers = 2 if convention == "__fastcall" else 0
        if sym[i:] == "XZ":               # explicit void parameter list
            i += 1
        else:
            while i < len(sym) and sym[i] != "@":
                if sym[i] == "Z":         # varargs: arity is not fixed
                    return None, None
                if convention == "__cdecl" and sym[i] == "X":
                    return None, None     # void is valid only as the full list
                size, in_register, i = arg_size(sym, i)
                if registers and in_register:
                    registers -= 1        # consumed by ecx/edx, never pushed
                    continue
                total += size
    except (ValueError, IndexError, KeyError):
        return None, None

    # Only trust a signature that consumed cleanly to the terminator. Anything
    # else means the parse drifted, and a drifted parse must not accuse a row.
    if sym[i:] not in ("@Z", "Z"):
        return None, None
    if convention == "__cdecl":
        return 0, convention
    return total, convention


def actual_ret(body):
    """Bytes this body pops, or None when it does not end in a `ret` at all.

    A tail-called or non-returning body says nothing about arity, and must not
    be read as `ret 0`.
    """
    if body and body[-1] == 0xC3:
        return 0
    if len(body) >= 3 and body[-3] == 0xC2:
        return struct.unpack_from("<H", body, len(body) - 2)[0]
    return None


def decoded_actual_ret(body):
    """Decode a complete body and read cleanup only from its final instruction.

    This is intentionally separate from ``actual_ret``: the legacy callee-
    cleaned audit keeps its established raw-tail behavior, while caller-cleaned
    cdecl checking must not mistake an immediate or displacement for a return.
    A missing decoder is an error, not an opinion-free result that could report
    a false green queue.
    """
    try:
        import capstone
    except ImportError as exc:
        raise RuntimeError(
            "cdecl cleanup validation requires Capstone; install it in your "
            "Python environment with python3 -m pip install capstone"
        ) from exc

    disassembler = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    instructions = list(disassembler.disasm(bytes(body), 0))
    if not instructions or sum(ins.size for ins in instructions) != len(body):
        return None
    tail = instructions[-1]
    if tail.address + tail.size != len(body) or tail.mnemonic != "ret":
        return None
    if tail.bytes == b"\xc3":
        return 0
    if len(tail.bytes) == 3 and tail.bytes[0] == 0xC2:
        return struct.unpack_from("<H", tail.bytes, 1)[0]
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--csv", default=str(ROOT / "targets/game/reverse" / "functions.csv"))
    args = ap.parse_args()

    data = EXE.read_bytes()
    checked = skipped = 0
    bad = []

    with open(args.csv, newline="", encoding="utf-8", errors="replace") as fh:
        for row in csv.DictReader(fh):
            name, rva_text, size_text = row["name"], row["target_rva"], row["target_size"]
            if not rva_text or not size_text:
                continue
            want, convention = expected_ret(name)
            if want is None:
                skipped += 1
                continue
            size = int(size_text)
            offset = rva_to_offset(data, int(rva_text, 16))
            if offset is None or size < 1:
                continue
            body = data[offset:offset + size]
            got = (decoded_actual_ret(body) if convention == "__cdecl"
                   else actual_ret(body))
            if got is None:
                skipped += 1                 # tail call or non-returning body
                continue
            checked += 1
            if got != want:
                bad.append((name, rva_text, size, want, got, convention, row["source"]))

    print(f"checked {checked} row(s), skipped {skipped} unparsable/tail-call\n")
    print(f"{len(bad)} row(s) whose retail stack cleanup contradicts the decorated name:\n")
    for name, rva, size, want, got, convention, source in bad[:args.limit]:
        print(f"  {rva} {size:>5}B  {convention}  expects ret {want}, retail does ret {got}")
        print(f"      {name[:110]}")
        print(f"      {source}")
    if len(bad) > args.limit:
        print(f"\n  ... {len(bad) - args.limit} more (raise --limit)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
