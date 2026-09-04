#!/usr/bin/env python3
"""Group unclaimed retail bodies into families that ONE conversion can pay for.

A family is a set of addresses whose bodies are the same function differing
only in constants. Converting one member proves the shape; the rest land in a
single add_match_batch pass. The whole question is what "the same" means, and
this tool offers four progressively looser normal forms:

  --exact   raw bytes. Finds only families with no relocations and no varying
            field at all.

  --disp    REL32 branch displacements zeroed. A call to a FIXED target encodes
            a DIFFERENT displacement from every address, so exact grouping
            structurally cannot see relocation-bearing families -- every member
            is its own singleton. When this was first measured, on a much
            earlier ledger, masking took the queue from 11 families and 51 rows
            to 161 families and 1,614 rows.

  --operand (default) every immediate AND displacement field zeroed, using
            capstone byte offsets so opcodes, modrm register selection and
            instruction lengths stay intact. `sub ecx,0x58` and `sub ecx,0x08`
            are one shape with one varying axis, but they are not byte-identical
            and --disp leaves each a singleton -- masking displacements does not
            mask IMMEDIATES.

  --mnemonic  the mnemonic sequence alone; operands, REGISTERS and instruction
            lengths all discarded. Merges families that --operand splits purely
            on which register the allocator picked, which is a difference the
            source usually does not contain.

Measured at 31cb443bf over the 7,183 bodies then passing the filters below:

              mode        families    rows    remaining singletons
              --exact          162     348                   6,731
              --disp           384   1,017                   6,062
              --operand        727   3,280                   3,799

and at 35930fea2, once --operand had been worked down to a flat queue whose
largest family held 13 members, --mnemonic restored a workable head (60, 35,
24, 23, 22 ...): 1,481 rows against 869 at --min-members 3.

Looser grouping trades precision for reach and WILL produce false families. An
immediate can be load-bearing in the source -- a 0 and a 1 need different C++ --
and under --mnemonic two members may differ in source outright, since `mov/mov/
ret` says almost nothing. That is acceptable and not a defect, but the looser
the mode the less a proven member says about its siblings: treat a --mnemonic
family as a HYPOTHESIS to look at, never as a claim. This decides only what is
worth LOOKING at; the byte gate still decides every member individually.

FILTERS, each of which exists because omitting it cost a run:
  * only unclaimed Code/gen_asm/ dump rows -- gen_small and gen_uw own theirs;
  * drop rows whose address carries a REAL (not address-derived) symbols.csv
    pin: those are tgrid territory;
  * drop ghidra=Unwind@ rows: compiler unwind residue, not function bodies;
  * require the byte AFTER the row to be 0xCC, so a PREFIX of a longer function
    cannot pass as a whole one;
  * require the body to end in a ret or a jmp, which excludes padding-terminated
    dead code;
  * EXCLUDE PREVIOUSLY-ATTEMPTED ADDRESSES ONLY AFTER GROUPING. Excluding them
    first splits a partially-attempted family into two apparently distinct
    groups -- that is exactly how 0x001EEAE0 and 0x001F35C0 were reported as
    two families of 6 and 7 when they were one family of 7;
  * drop a whole family if any member carries a `refuted` or `blocked` verdict:
    a refutation refutes the SHAPE, so the siblings are dead too;
  * drop bodies that call _atexit -- their source needs a function-local static
    of class type, and MSVC numbers those destructor helpers `_$E<n>` PER
    TRANSLATION UNIT, so the second such TU in the image always collides with
    the first on a name-global consistency check. See
    registers_a_local_static(); it has cost three landings so far.

Usage:
  python3 tools/family_scan.py [--exact|--disp|--operand|--mnemonic]
                              [--min-size 8] [--max-size 160] [--out FILE]
"""
import argparse
import collections
import csv
import io
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import build

ROOT = Path(__file__).resolve().parent.parent
ADDRESS_DERIVED = re.compile(
    r"Gen_?[0-9A-Fa-f]{8}|gen_?[0-9A-Fa-f]{8}|Rva_?[0-9A-Fa-f]{8}|\?[bdj]_", re.I)


def mask_disp(body):
    """Zero the 4-byte displacement of every E8/E9 near branch."""
    out = bytearray(body)
    i = 0
    while i < len(out) - 4:
        if out[i] in (0xE8, 0xE9):
            out[i + 1:i + 5] = b"\0" * 4
            i += 5
        else:
            i += 1
    return bytes(out)


def mask_operands(body, md):
    """Zero every immediate and displacement field. None if it does not decode
    cleanly end to end -- a body we cannot decode is one we cannot group."""
    out = bytearray(body)
    covered = 0
    for insn in md.disasm(body, 0):
        enc = insn.encoding
        if enc.imm_size:
            lo = insn.address + enc.imm_offset
            out[lo:lo + enc.imm_size] = b"\0" * enc.imm_size
        if enc.disp_size:
            lo = insn.address + enc.disp_offset
            out[lo:lo + enc.disp_size] = b"\0" * enc.disp_size
        covered += insn.size
    return bytes(out) if covered == len(body) else None


def mask_mnemonics(body, md):
    """The MNEMONIC SEQUENCE alone -- operands, registers and lengths discarded.

    One step looser again than --operand. Two bodies share this form iff they
    perform the same operations in the same order, whatever registers the
    allocator happened to pick and whatever the constants were. It merges
    families that --operand splits purely on register choice, which is a
    difference the SOURCE usually does not contain.

    This is the loosest form offered and by far the most false-positive prone:
    `mov/mov/ret` says almost nothing. Treat a family found only here as a
    HYPOTHESIS to look at, never as a claim -- and note that a proven member
    gives less leverage over its siblings than in the tighter modes, because the
    siblings may genuinely differ in source.
    """
    names, covered = [], 0
    for insn in md.disasm(body, 0):
        names.append(insn.mnemonic)
        covered += insn.size
    return ("\n".join(names)).encode("utf-8") if covered == len(body) else None


def ends_in_return_or_jump(body, md):
    """Check the final decoded instruction, not its last operand byte.

    `ret 4` ends in 00, and direct jumps end in their displacement. Conversely,
    an immediate ending in C3 is not a return. Require complete decoding in
    every grouping mode; padding after a truncated instruction is not proof.
    This is a candidate filter, not a replacement for boundary/identity proof.
    """
    last = None
    covered = 0
    for insn in md.disasm(body, 0):
        last = insn
        covered += insn.size
    return (last is not None and covered == len(body)
            and last.mnemonic in ("ret", "jmp"))


def load_real_pins():
    pins = set()
    with io.open(ROOT / "reverse" / "symbols.csv", encoding="utf-8",
                 errors="replace") as fh:
        for i, row in enumerate(csv.reader(fh)):
            if i == 0 or len(row) < 2 or ADDRESS_DERIVED.search(row[0]):
                continue
            try:
                pins.add(int(row[1], 16))
            except ValueError:
                pass
    return pins


DEAD_VERDICTS = ("refuted", "blocked")


def load_attempted():
    """Two sets, because a prior attempt means two different things.

    `seen` is every address the log mentions. Dropping those members but KEEPING
    the family is right after a `converted` verdict: the siblings that did not
    land are still worth doing, and dropping the family instead would hide them.

    `dead` is addresses whose row carried a `refuted` or `blocked` verdict. There
    the whole family is finished, because a family is ONE function and a
    refutation refutes the shape, not the address. Keeping it alive re-queues the
    same shape under a NEW ANCHOR as soon as the logged members are skipped --
    which is exactly what happened: three families totalling 36 rows resurfaced
    at the top of the queue, one of them the local-static guard shape that had
    already been backed out TWICE, and all three were confirmed byte-identical in
    normal form to the shapes they re-anchored from.
    """
    seen, dead = set(), set()
    with io.open(ROOT / "reverse" / "re_attempts.log", encoding="utf-8",
                 errors="replace") as fh:
        for line in fh:
            fields = line.split("\t")
            verdict = fields[3].strip().lower() if len(fields) > 3 else ""
            addresses = {int(m.group(1), 16)
                         for m in re.finditer(r"0x([0-9A-Fa-f]{8})", line)}
            seen |= addresses
            if verdict in DEAD_VERDICTS:
                dead |= addresses
    return seen, dead


ATEXIT_RVA = 0x009F6E26          # _atexit, per reverse/symbols.csv


def registers_a_local_static(body, rva):
    """True if the body calls _atexit -- i.e. its source needs a function-local
    static of class type.

    Such a TU is currently UNCONVERTIBLE, and not for any reason visible in its
    bytes. MSVC names the destructor helper for each function-local static
    `_$E<n>`, numbered sequentially FROM THE START OF THE TRANSLATION UNIT, so
    the second such TU in the image reuses _$E4, _$E6, _$E12 ... and
    verify_dir32_consistency -- which is keyed on symbol NAME across the whole
    image -- reports them as one symbol at several addresses.

    This has now cost three separate landings (19 rows, then 7, then 6), and the
    first two times it was recorded as a property of the SHAPE, which is why the
    refuted-family exclusion above could not catch the third: those were local
    static GUARDS and the third was local static INITIALISERS, a different
    mnemonic sequence and a different normal form. TWO COLLIDING TUs NEED NOT
    SHARE A SINGLE BYTE, so the filter has to key on the CONSTRUCT, and the call
    to _atexit is what makes the construct visible from the outside.

    Remove this filter once verify_dir32_consistency scopes compiler-local
    symbols per-TU, or once the _$E family is whitelisted with that reasoning.
    """
    for i in range(len(body) - 4):
        if body[i] == 0xE8:
            target = rva + i + 5 + int.from_bytes(body[i + 1:i + 5], "little", signed=True)
            if target == ATEXIT_RVA:
                return True
    return False


def candidates(min_size, max_size, real_pins):
    with io.open(ROOT / "reverse" / "functions.csv", encoding="utf-8") as fh:
        for i, row in enumerate(csv.reader(fh)):
            if i == 0 or len(row) != 7:
                continue
            name, _, rva_s, size_s, src, _, notes = row
            if not src.startswith("Code/gen_asm/"):
                continue
            size = int(size_s)
            if not (min_size <= size <= max_size) or "Unwind@" in notes:
                continue
            rva = int(rva_s, 16)
            if rva not in real_pins:
                yield name, rva, size


def main():
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--exact", action="store_const", dest="mode", const="exact")
    g.add_argument("--disp", action="store_const", dest="mode", const="disp")
    g.add_argument("--operand", action="store_const", dest="mode", const="operand")
    g.add_argument("--mnemonic", action="store_const", dest="mode", const="mnemonic")
    ap.add_argument("--min-members", type=int, default=2)
    ap.add_argument("--min-size", type=int, default=8)
    ap.add_argument("--max-size", type=int, default=160)
    ap.add_argument("--out", type=Path)
    ap.add_argument("--top", type=int, default=30)
    ap.set_defaults(mode="operand")
    args = ap.parse_args()

    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = args.mode == "operand"

    real_pins = load_real_pins()
    attempted, dead = load_attempted()

    groups = collections.defaultdict(list)
    scanned = undecoded = local_statics = 0
    for name, rva, size in candidates(args.min_size, args.max_size, real_pins):
        try:
            window = build.read_target_bytes(rva, size + 1)
        except Exception:
            continue
        if len(window) != size + 1 or window[size] != 0xCC:
            continue                       # must END at padding
        body = window[:size]
        if not ends_in_return_or_jump(body, md):
            continue                       # must end in a ret or a jmp
        if registers_a_local_static(body, rva):
            local_statics += 1
            continue
        scanned += 1
        if args.mode == "exact":
            key = body
        elif args.mode == "disp":
            key = mask_disp(body)
        elif args.mode == "operand":
            key = mask_operands(body, md)
            if key is None:
                undecoded += 1
                continue
        else:
            key = mask_mnemonics(body, md)
            if key is None:
                undecoded += 1
                continue
        groups[key].append((rva, size, name))

    families = []
    refuted = 0
    for key, members in groups.items():
        if len(members) < args.min_members:
            continue
        # A refutation refutes the SHAPE, so one dead member kills the family.
        if any(m[0] in dead for m in members):
            refuted += 1
            continue
        fresh = [m for m in members if m[0] not in attempted]   # AFTER grouping
        if fresh:
            families.append((len(members), len(fresh), key, members, fresh))
    families.sort(reverse=True, key=lambda f: f[1])
    singletons = sum(1 for m in groups.values()
                     if len(m) == 1 and m[0][0] not in attempted)

    print("mode=%s  bodies scanned: %d%s" % (
        args.mode, scanned,
        "  (undecodable, skipped: %d)" % undecoded if undecoded else ""))
    print("families >= %d with unattempted members: %d"
          % (args.min_members, len(families)))
    print("unattempted rows reachable: %d" % sum(f[1] for f in families))
    print("families dropped as refuted/blocked shapes: %d" % refuted)
    print("bodies skipped as function-local-static TUs: %d" % local_statics)
    print("unattempted singletons (regex-sweep territory): %d" % singletons)

    if args.out:
        with io.open(args.out, "w", encoding="utf-8") as out:
            for total, fresh_n, key, members, fresh in families:
                out.write("=== %d members (%d unattempted), %dB, anchor 0x%08X\n"
                          "normal: %s\nmembers: %s\n\n"
                          % (total, fresh_n, members[0][1], fresh[0][0],
                             key.hex() if args.mode != "mnemonic"
                             else key.decode("utf-8").replace(chr(10), " "),
                             " ".join("0x%08X" % a for a, _, _ in fresh)))
        print("written: %s" % args.out)

    print("\nTOP %d:" % args.top)
    for total, fresh_n, _, members, fresh in families[:args.top]:
        print("  0x%08X  %3dB  %4d fresh / %4d total"
              % (fresh[0][0], members[0][1], fresh_n, total))


if __name__ == "__main__":
    main()
