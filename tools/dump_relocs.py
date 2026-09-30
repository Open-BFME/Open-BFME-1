#!/usr/bin/env python3
"""Recover relocations for MASM byte dumps and emit relocatable scaffold objects.

A dump PROC (game/gen_asm/, game/masm_dumps/, any ledger .asm whose PROC is
only `db` lines) holds retail's bytes verbatim: every rel32 and absolute
address in it is retail's, so it only works at retail's address. This tool
disassembles each LIVE dump body (a matched ledger row naming the PROC) from
the retail image, types every reference, and writes a MASM file per dump source
under build/dump_relocs/ in which each reference is symbolic. Dump sources are
never edited; the generated objects are build products.

  python3 tools/dump_relocs.py --all                       # every dump source (~90 s)
  python3 tools/dump_relocs.py --all --link-check all      # + link every object (~2 min)
  python3 tools/dump_relocs.py game/gen_asm/d_000d6fb0.asm # one file; reports to build/dump_relocs/subset/

Classification, per instruction reached by recursive descent from the body
start, every Ghidra start inside it, every intra-body branch target and every
switch-table entry:

  REL32  rel32 call/jmp/jcc whose target leaves the body -> the symbol that
         defines the target address (rule `branch`, exact). Intra-body
         branches stay bytes. A rel8 branch leaving the body is a failure.
  DIR32  a disp32 memory operand with no base register (mod=00 rm=101, moffs,
         or SIB with no base) whose value lies in the image (`mem-abs`,
         `mem-sib`, exact); a disp32 after a base register whose value lies in
         the image (`mem-based`: no struct is 4 MB long); every entry of a
         switch table `jmp [reg*4+T]` (`jumptable`). A table past the body's
         end that no row owns is emitted as its own labelled section
         (`jumptable-external`, sized by the entries that point into the body
         and by the `cmp reg, N / ja` bound; a byte-index table by that bound).
  imm32  an in-image immediate is AMBIGUOUS unless the instruction is
         push/mov/cmp AND one of these holds: the value starts a matched ledger
         row, a Ghidra function, a dir32_addresses.csv name (a DIR32 compiled
         code emits), an exports.csv entry, a vtables.tsv vtable or an IAT
         slot; it is this body's start, one of its tables or one of its
         instruction starts (`start:own-insn`), or the address of its own
         instruction (`self-insn`); it points at two function starts in a row
         (`fnptrs`) or at a printable NUL-terminated string in .rdata/.data
         that follows a NUL or starts a dword (4+ chars: either; shorter:
         both) (`string`); or its use says address: `mov reg, imm` whose reg is
         then a memory base (`deref`), `mov ecx, imm` before a call
         (`this-call`), `mov eax, imm; ret` into .text (`catch-continuation`).
         Anything else stays literal and is listed in ambiguous.csv. Values
         such as `cmp eax, 454E44h` ("END") are exactly why.

Target symbol for an address: the defining object symbol of the matched row
that contains it (+addend when interior); for an IAT slot, the one
dir32_addresses.csv `__imp_` spelling of the name the import table gives;
the unique dir32_addresses.csv name at the address; else the address-derived
`g_XXXXXXXX` (VA), with the candidate names recorded when there are several
(never picked) or when a row's symbol is claimed at two addresses.

Failures: rel8 leaving the body, a body ending mid-instruction or falling
through its end (after anything but a call), undecodable or unreached bytes
(int3, nop and MSVC's `mov r,r` / `lea r,[r+0]` fillers are padding), a
table that cannot be bounded, or any verification error.

Verification per body, on the assembled object: the object's relocations are
exactly the recovered ones; (i) resolved with every symbol at its retail
address the bytes equal retail's; (ii) with EVERY symbol, this body included,
moved by its own offset (0x1000 + 16*k), bytes outside relocation fields are
unchanged, each field decodes to its target's moved address, and no operand in
reached code still holds an in-image address except the listed ambiguous ones.
`--link-check` links an object with MSVC 7.1 link.exe at base 0x10000000
against a stub defining each external at its own address, and checks the
image the same way: link.exe reads the relocations as (i) assumes.

Each body and table is its own `_TEXT$...` segment, so a reference between two
dumps of one file is a relocation, never an assembler constant. Names MASM
cannot spell (over 240 chars, odd characters) are assembled as `lnm_NNNNN` and
renamed in the object's string table.

Outputs (build/dump_relocs/): asm/, obj/ (one per source), relocs.csv,
ambiguous.csv, tables.csv, bodies.csv, summary.json.
"""
import argparse
import bisect
import collections
import concurrent.futures
import csv
import json
import os
import re
import struct
import subprocess
import sys
import threading
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

from capstone import CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_JUMP, CS_GRP_RET, Cs  # noqa: E402
from capstone.x86 import (X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_EAX, X86_REG_ECX,  # noqa: E402
                          X86_REG_FS, X86_REG_GS, X86_REG_INVALID)

OUT = ROOT / "build" / "dump_relocs"
REVERSE = ROOT / "targets" / "game" / "reverse"
DIR32, REL32 = 0x0006, 0x0014
PADDING = frozenset(b"\xcc\x90")
JCC = {0x80: "jo", 0x81: "jno", 0x82: "jb", 0x83: "jae", 0x84: "je", 0x85: "jne", 0x86: "jbe",
       0x87: "ja", 0x88: "js", 0x89: "jns", 0x8A: "jp", 0x8B: "jnp", 0x8C: "jl", 0x8D: "jge",
       0x8E: "jle", 0x8F: "jg"}
IMM_ADDRESS_MNEMONICS = frozenset({"push", "mov", "cmp"})
CODE_CLASSES = frozenset({"row", "row-interior", "code-unowned", "row-multiname", "row-name-multibody"})
SAFE_NAME = re.compile(r"^[A-Za-z_?@$][A-Za-z0-9_?@$]*$")
MASM_NAME_LIMIT = 240
SHIFT_BODY = 0x1000

_LOCAL = threading.local()


def disassembler():
    md = getattr(_LOCAL, "md", None)
    if md is None:
        md = _LOCAL.md = Cs(CS_ARCH_X86, CS_MODE_32)
        md.detail = True
    return md


# --------------------------------------------------------------------------- context

class Context:
    """Everything the classifier asks about an address. Tests build a fake one."""

    def __init__(self):
        data, sections = build.exe_image()
        self.data = data
        pe = build.u32(data, 0x3C)
        self.base = build.u32(data, pe + 24 + 28)
        self.image_end = self.base + build.u32(data, pe + 24 + 56)
        self.sections = [(s["name"] or "?", self.base + s["rva"], self.base + s["rva"] + s["size"],
                          s["raw_pointer"]) for s in sections]
        rows = [r for r in build.load_function_rows() if r["target_rva"].startswith("0x")]
        by_start = collections.defaultdict(list)
        for row in rows:
            by_start[self.base + int(row["target_rva"], 16)].append(row)
        self.rows = rows
        self.row_starts = sorted(by_start)
        self.row_info = {}
        for start in self.row_starts:
            group = by_start[start]
            size = max(int(r["target_size"]) for r in group)
            symbols = sorted({build.ledger_object_symbol(r) for r in group})
            self.row_info[start] = (size, symbols, sorted(r["name"] for r in group))
        # a defined symbol claimed at two addresses cannot name either of them
        homes = collections.defaultdict(set)
        for start, (_, symbols, _) in self.row_info.items():
            for symbol in symbols:
                homes[symbol].add(start)
        self.multibody = {symbol for symbol, starts in homes.items() if len(starts) > 1}
        self.dir32 = collections.defaultdict(set)
        with (REVERSE / "dir32_addresses.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                self.dir32[int(row["va"], 16)].add(row["name"])
        self.iat = {}
        with (REVERSE / "imports.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                self.iat[int(row["iat_va"], 16)] = f"{row['dll']}!{row['name'] or '#' + row['hint']}"
        self.ghidra = set()
        with (REVERSE / "ghidra_functions.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                self.ghidra.add(self.base + int(row["rva"], 16))
        self.exports = set()
        with (REVERSE / "exports.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                if row["rva"].startswith("0x"):
                    self.exports.add(self.base + int(row["rva"], 16))
        self.vtables = set()
        with (REVERSE / "vtables.tsv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle, delimiter="\t"):
                self.vtables.add(self.base + int(row["vtable_rva"], 16))

    # -- raw image
    def section(self, va):
        for name, start, end, _ in self.sections:
            if start <= va < end:
                return name
        return "header" if self.base <= va < self.image_end else None

    def in_image(self, va):
        return self.base <= va < self.image_end

    def read(self, va, size):
        for _, start, end, raw in self.sections:
            if start <= va < end:
                off = raw + va - start
                return self.data[off:off + size]
        return b""

    # -- ownership
    def row_at(self, va):
        """(start, size, defined symbols, row names) of the matched row containing va."""
        i = bisect.bisect_right(self.row_starts, va) - 1
        if i >= 0:
            start = self.row_starts[i]
            size, symbols, names = self.row_info[start]
            if va < start + size:
                return start, size, symbols, names
        return None

    def owner(self, va):
        """(symbol, addend, target_class, note) for a reference to va."""
        row = self.row_at(va)
        if row is not None:
            start, _, symbols, names = row
            if len(symbols) == 1 and symbols[0] not in self.multibody:
                cls = "row" if va == start else "row-interior"
                return symbols[0], va - start, cls, ""
            if len(symbols) == 1:
                return f"g_{start:08X}", va - start, "row-name-multibody", "name=" + symbols[0]
            return f"g_{start:08X}", va - start, "row-multiname", names_note(symbols)
        if va in self.iat:
            names = sorted(n for n in self.dir32.get(va, ()) if n.startswith("__imp_"))
            imported = self.iat[va].split("!", 1)[1]
            # the import table names the slot: keep the one __imp_ spelling of that name
            spelled = [n for n in names if re.sub(r"@\d+$", "", n[len("__imp_"):]).lstrip("_") == imported]
            if len(spelled) == 1:
                return spelled[0], 0, "import", self.iat[va]
            return f"g_{va:08X}", 0, "import-unnamed", self.iat[va] + names_note(names, "; ")
        names = sorted(self.dir32.get(va, ()))
        if len(names) == 1:
            return names[0], 0, "data-named", ""
        section = self.section(va)
        if section == ".text":
            return f"g_{va:08X}", 0, "code-unowned", ("ghidra-start" if va in self.ghidra else "")
        if names:
            return f"g_{va:08X}", 0, "data-multiname", names_note(names)
        return f"g_{va:08X}", 0, "data-anon", section or ""

    # -- imm32 evidence
    def start_evidence(self, va):
        if va in self.row_info:
            return "start:row"
        if va in self.ghidra:
            return "start:ghidra"
        if va in self.vtables:
            return "start:vtable"
        if va in self.dir32:
            return "start:dir32"
        if va in self.exports:
            return "start:export"
        if va in self.iat:
            return "start:iat"
        section = self.section(va)
        if section in (".rdata", ".data"):
            first, second = self.read(va, 8)[:4], self.read(va, 8)[4:]
            if len(second) == 4:
                a, b = struct.unpack("<I", first)[0], struct.unpack("<I", second)[0]
                if all(x in self.row_info or x in self.ghidra for x in (a, b)):
                    return "fnptrs"
            text = self.read(va, 256)
            end = text.find(b"\0")
            if end >= 1 and all(0x20 <= c < 0x7F or c in (9, 10, 13) for c in text[:end]):
                after_nul = self.read(va - 1, 1) == b"\0"
                # 4+ printable bytes after a NUL or on a dword boundary; a shorter string needs both
                if (end >= 4 and (after_nul or va % 4 == 0)) or (after_nul and va % 4 == 0):
                    return "string"
        return None


def names_note(names, sep=""):
    """Candidate names, never picked: the count and the first three."""
    if not names:
        return ""
    shown = "|".join(names[:3]) + ("|..." if len(names) > 3 else "")
    return f"{sep}names={len(names)}:{shown}"


# --------------------------------------------------------------------------- analysis

class Ref:
    __slots__ = ("off", "width", "kind", "value", "form", "insn_off", "text", "mnemonic", "jump_table",
                 "byte_table")

    def __init__(self, off, width, kind, value, form, insn_off, text, mnemonic):
        self.off, self.width, self.kind, self.value = off, width, kind, value
        self.form, self.insn_off, self.text, self.mnemonic = form, insn_off, text, mnemonic
        self.jump_table = self.byte_table = False


def decode(body, off, va):
    for insn in disassembler().disasm(body[off:off + 16], va + off, 1):
        return insn
    return None


def insn_refs(insn, off):
    """Operand fields of one instruction that could hold an address."""
    refs = []
    text = f"{insn.mnemonic} {insn.op_str}".strip()
    groups = set(insn.groups)
    ops = insn.operands
    is_branch = bool(groups & {CS_GRP_JUMP, CS_GRP_CALL})
    if is_branch and len(ops) == 1 and ops[0].type == X86_OP_IMM:
        refs.append(Ref(off + insn.imm_offset, insn.imm_size, "branch", ops[0].imm & 0xFFFFFFFF,
                        "rel", off, text, insn.mnemonic))
        return refs
    for op in ops:
        if op.type == X86_OP_MEM and insn.disp_size == 4:
            mem = op.mem
            if mem.segment in (X86_REG_FS, X86_REG_GS):
                continue
            if mem.base == X86_REG_INVALID and mem.index == X86_REG_INVALID:
                form = "mem-abs"
            elif mem.base == X86_REG_INVALID:
                form = "mem-sib"
            else:
                form = "mem-based"
            ref = Ref(off + insn.disp_offset, 4, "disp", mem.disp & 0xFFFFFFFF, form, off, text, insn.mnemonic)
            ref.jump_table = (insn.mnemonic == "jmp" and mem.base == X86_REG_INVALID
                              and mem.index != X86_REG_INVALID and mem.scale == 4)
            ref.byte_table = op.size == 1 and insn.mnemonic in ("mov", "movzx") and form != "mem-abs"
            refs.append(ref)
        elif op.type == X86_OP_IMM and insn.imm_size == 4:
            refs.append(Ref(off + insn.imm_offset, 4, "imm", op.imm & 0xFFFFFFFF, "imm", off, text,
                            insn.mnemonic))
    return refs


def terminal(insn):
    if CS_GRP_RET in set(insn.groups) or insn.mnemonic in ("hlt", "int3", "ud2", "iretd"):
        return True
    return insn.mnemonic == "jmp"


def descend(body, va, entries, blocked):
    """Recursive descent from `entries`, never decoding inside `blocked` offsets."""
    size = len(body)
    insns, refs, problems = {}, [], []
    owner = bytearray(size)
    work = sorted(entries, reverse=True)
    while work:
        off = work.pop()
        while 0 <= off < size and off not in insns:
            if off in blocked:
                problems.append(("decode-runs-into-table", off, ""))
                break
            insn = decode(body, off, va)
            if insn is None:
                problems.append(("undecodable", off, ""))
                break
            if off + insn.size > size:
                problems.append(("runs-past-end", off, f"{insn.mnemonic} {insn.op_str}"))
                break
            if any(owner[o] for o in range(off, off + insn.size)) or any(
                    o in blocked for o in range(off, off + insn.size)):
                problems.append(("overlapping-decode", off, f"{insn.mnemonic} {insn.op_str}"))
                break
            insns[off] = insn
            owner[off:off + insn.size] = b"\x01" * insn.size
            for ref in insn_refs(insn, off):
                refs.append(ref)
                if ref.kind == "branch" and 0 <= ref.value - va < size:
                    work.append(ref.value - va)
            if terminal(insn):
                break
            off += insn.size
            if off == size:
                problems.append(("falls-off-end", off - insn.size, f"{insn.mnemonic} {insn.op_str}"))
    return insns, refs, problems


def table_extents(body, va, data, stops):
    """{start: (kind, end)}: a jump table runs while its dwords point into the body;
    any other table runs to the next table, the next reached-from-elsewhere code
    offset (`stops`) or the body end."""
    size = len(body)
    out = {}
    starts = sorted(data)
    for i, start in enumerate(starts):
        kind = data[start]
        limit = starts[i + 1] if i + 1 < len(starts) else size
        later = [s for s in stops if s > start]
        if later:
            limit = min(limit, min(later))
        end = start
        if kind == "jumptable":
            while end + 4 <= limit and va <= struct.unpack_from("<I", body, end)[0] < va + size:
                end += 4
        else:
            end = limit
        out[start] = (kind, end)
    return out


def switch_bound(insns, insn_off):
    """N+1 for the `cmp reg, N` / `ja` guarding the switch dispatch at insn_off, else None."""
    order = sorted(o for o in insns if o <= insn_off)
    back = [insns[o] for o in order[-4:]]
    for first, second in zip(back, back[1:]):
        if (first.mnemonic == "cmp" and len(first.operands) == 2 and first.operands[1].type == X86_OP_IMM
                and second.mnemonic == "ja"):
            return (first.operands[1].imm & 0xFFFFFFFF) + 1
    return None


def external_tables(body, va, ctx, insns, refs):
    """Switch tables a body indexes that lie outside it: {va: dict}; jump-table entries
    that point into the body are returned too, as descent entries."""
    size, out, entries = len(body), {}, set()
    for ref in refs:
        if ref.kind != "disp" or va <= ref.value < va + size or ctx is None:
            continue
        if not (ref.jump_table or ref.byte_table) or ctx.section(ref.value) != ".text":
            continue
        bound = switch_bound(insns, ref.insn_off)
        if ref.jump_table:
            targets = []
            while len(targets) < 1024:
                raw = ctx.read(ref.value + 4 * len(targets), 4)
                if len(raw) < 4:
                    break
                target = struct.unpack("<I", raw)[0]
                if not va <= target < va + size:
                    break
                targets.append(target)
            direct = bound is not None and not any(
                r.byte_table and r.insn_off < ref.insn_off for r in refs if r.kind == "disp")
            count = min(len(targets), bound) if direct else len(targets)
            entries.update(t - va for t in targets[:count])
            out[ref.value] = {"kind": "jumptable", "count": count, "bound": bound if direct else None,
                              "insn_off": ref.insn_off}
        else:
            out[ref.value] = {"kind": "bytetable", "count": bound, "bound": bound, "insn_off": ref.insn_off}
    return out, entries


def analyze(body, va, ctx=None, extra_entries=()):
    """Recursive descent to a fixpoint over entries and tables."""
    size = len(body)
    entries = {0} | {e for e in extra_entries if 0 <= e < size}
    data = {}
    stops = set(entries)
    external = {}
    for _ in range(32):
        blocked = set()
        tables = table_extents(body, va, data, stops)
        for start, (_, end) in tables.items():
            blocked.update(range(start, end))
        insns, refs, problems = descend(body, va, entries, blocked)
        new_data = dict(data)
        new_stops = set(entries)
        for ref in refs:
            t = ref.value - va
            if not 0 <= t < size:
                continue
            if ref.kind == "branch":
                new_stops.add(t)
            elif ref.kind == "disp":
                new_data.setdefault(t, "jumptable" if ref.jump_table else
                                    "bytetable" if ref.byte_table else "data")
        new_entries = set(entries)
        for start, (kind, end) in table_extents(body, va, new_data, new_stops).items():
            if kind == "jumptable":
                for o in range(start, end, 4):
                    new_entries.add(struct.unpack_from("<I", body, o)[0] - va)
        external, ext_entries = external_tables(body, va, ctx, insns, refs)
        new_entries |= {e for e in ext_entries if 0 <= e < size}
        new_stops |= new_entries
        if new_data == data and new_entries == entries and new_stops == stops:
            break
        data, entries, stops = new_data, new_entries, new_stops
    else:
        problems.append(("no-fixpoint", 0, ""))
    tables = table_extents(body, va, data, stops)
    for start, (_, end) in tables.items():
        if any(o in insns for o in range(start, end)) or any(
                o < start < o + insns[o].size for o in insns if o < start):
            problems.append(("code-overlaps-table", start, ""))
    result = finish(body, va, insns, refs, problems, tables)
    result["external"] = external
    return result


def is_filler(chunk):
    """int3/nop padding, or MSVC's alignment fillers: `mov r, r` and `lea r, [r+0]`."""
    if all(c in PADDING for c in chunk):
        return True
    off = 0
    while off < len(chunk):
        insn = decode(chunk, off, 0)
        if insn is None or off + insn.size > len(chunk):
            return False
        ops = insn.operands
        if insn.mnemonic in ("nop", "int3"):
            pass
        elif (insn.mnemonic == "mov" and len(ops) == 2 and ops[0].type == ops[1].type == X86_OP_REG
              and ops[0].reg == ops[1].reg):
            pass
        elif (insn.mnemonic == "lea" and len(ops) == 2 and ops[1].type == X86_OP_MEM
              and ops[1].mem.base == ops[0].reg and ops[1].mem.index == X86_REG_INVALID
              and ops[1].mem.disp == 0):
            pass
        else:
            return False
        off += insn.size
    return True


def finish(body, va, insns, refs, problems, tables):
    size = len(body)
    covered = bytearray(size)
    for off, insn in insns.items():
        covered[off:off + insn.size] = b"\1" * insn.size
    for start, (kind, end) in tables.items():
        covered[start:end] = b"\2" * (end - start)
    gaps = []
    off = 0
    while off < size:
        if covered[off]:
            off += 1
            continue
        end = off
        while end < size and not covered[end]:
            end += 1
        if not is_filler(body[off:end]):
            gaps.append((off, end))
        off = end
    return {"insns": insns, "refs": refs, "problems": problems, "tables": tables, "gaps": gaps}


def classify(body, va, ctx, symbol, extra_entries=()):
    """Typed relocations, ambiguous operands and failures for one body.

    relocation: dict(site, kind, symbol, addend, target, cls, rule, evidence, insn, insn_off)
    """
    result = analyze(body, va, ctx, extra_entries)
    size = len(body)
    relocs, ambiguous, failures, info = [], [], [], collections.Counter()
    for kind, off, text in result["problems"]:
        if kind in ("undecodable", "runs-past-end") and size - off < 16:
            whole = decode(ctx.read(va + off, 16), 0, va + off) if ctx is not None else None
            if whole is not None and off + whole.size > size:
                kind, text = "ends-mid-instruction", f"{whole.mnemonic} {whole.op_str}"
        elif kind == "falls-off-end" and text.startswith("call "):
            # a trailing call to a no-return helper (throw, abort) is how MSVC ends such bodies
            info["falls-off-end-after-call"] += 1
            continue
        failures.append((kind, off, text))
    for ref in result["refs"]:
        target = ref.value
        inside = va <= target < va + size
        if ref.kind == "branch":
            if inside:
                info["intra-branch"] += 1
                continue
            if ref.width != 4:
                failures.append(("rel8-leaves-body", ref.insn_off, ref.text))
                continue
            if not ctx.in_image(target) or ctx.section(target) != ".text":
                failures.append(("branch-outside-text", ref.insn_off, ref.text))
                continue
            relocs.append(make_reloc(ctx, ref, REL32, target, "branch", "", va, size, symbol))
            continue
        if not ctx.in_image(target):
            if ref.kind == "disp" and ref.form != "mem-based":
                info["abs-outside-image"] += 1
            continue
        if ref.kind == "disp":
            relocs.append(make_reloc(ctx, ref, DIR32, target, ref.form, "", va, size, symbol))
            continue
        # imm32
        if inside:
            evidence = "start:self" if target == va else (
                "start:table" if target - va in result["tables"] else
                "start:own-insn" if target - va in result["insns"] else None)
        else:
            evidence = ctx.start_evidence(target)
        evidence = evidence or use_evidence(result["insns"], ref, va, ctx)
        if ref.mnemonic not in IMM_ADDRESS_MNEMONICS:
            ambiguous.append((ref.off, target, ctx.section(target), f"imm-{ref.mnemonic}", ref.text,
                              evidence or ""))
        elif evidence is None:
            ambiguous.append((ref.off, target, ctx.section(target), "imm-no-witnessed-start", ref.text, ""))
        else:
            relocs.append(make_reloc(ctx, ref, DIR32, target, "imm", evidence, va, size, symbol))
    for start, (kind, end) in result["tables"].items():
        if kind != "jumptable":
            continue
        for o in range(start, end, 4):
            target = struct.unpack_from("<I", body, o)[0]
            relocs.append({"site": o, "kind": DIR32, "symbol": symbol, "addend": target - va,
                           "target": target, "cls": "self", "rule": "jumptable", "evidence": "",
                           "insn": f"dd table+{o - start:#x}", "insn_off": o})
    tables = []
    for table_va, t in sorted(result["external"].items()):
        if ctx.row_at(table_va) is not None:
            info["external-table-in-other-row"] += 1
            continue
        label, _, cls, _ = ctx.owner(table_va)
        if cls not in ("code-unowned", "data-anon", "data-named"):
            failures.append(("external-table-unlabelled", t["insn_off"], f"{table_va:#x} {cls}"))
            continue
        if not t["count"]:
            failures.append(("external-table-unbounded", t["insn_off"], f"{t['kind']} at {table_va:#x}"))
            continue
        width = 4 if t["kind"] == "jumptable" else 1
        raw = ctx.read(table_va, t["count"] * width)
        trelocs = []
        if t["kind"] == "jumptable":
            if t["bound"] is not None and t["count"] < t["bound"]:
                failures.append(("jumptable-entry-leaves-body", t["insn_off"], f"{table_va:#x}"))
            for i in range(t["count"]):
                target = struct.unpack_from("<I", raw, 4 * i)[0]
                trelocs.append({"site": 4 * i, "kind": DIR32, "symbol": symbol, "addend": target - va,
                                "target": target, "cls": "self", "rule": "jumptable-external",
                                "evidence": f"switch at +{t['insn_off']:#x}", "insn": f"dd case {i}",
                                "insn_off": 4 * i})
        tables.append({"label": label, "va": table_va, "bytes": raw, "relocs": trelocs, "kind": t["kind"]})
    spans = sorted((t["va"], t["va"] + len(t["bytes"])) for t in tables)
    for (a0, a1), (b0, _) in zip(spans, spans[1:]):
        if b0 < a1:
            failures.append(("external-tables-overlap", 0, f"{a0:#x} {b0:#x}"))
    for start, end in result["gaps"]:
        info["unreached-bytes"] += end - start
        failures.append(("unreached", start, f"{end - start} bytes not reached by descent"))
        for o in range(start, end - 3):
            value = struct.unpack_from("<I", body, o)[0]
            if ctx.in_image(value) and value >= ctx.base + 0x1000:
                ambiguous.append((o, value, ctx.section(value), "unreached-dword", "", ""))
    relocs.sort(key=lambda r: r["site"])
    sites = [r["site"] for r in relocs]
    for a, b in zip(sites, sites[1:]):
        if b < a + 4:
            failures.append(("overlapping-relocations", a, ""))
    return {"relocs": relocs, "ambiguous": sorted(ambiguous), "failures": failures, "info": info,
            "analysis": result, "tables": tables}


def use_evidence(insns, ref, va, ctx):
    """Evidence from how an in-image imm32 is used, or None.

    self-insn           the value is the address of the instruction holding it
    catch-continuation  `mov eax, imm32; ret` (an EH catch funclet returns its
                        continuation address) and the value is in .text
    deref               `mov reg, imm32` and a later instruction in the same
                        straight-line run uses reg as a memory base before
                        writing it
    this-call           `mov ecx, imm32` and a call follows before ecx is written
    """
    insn = insns.get(ref.insn_off)
    if insn is None:
        return None
    if ref.value == va + ref.insn_off:
        return "self-insn"
    ops = insn.operands
    if insn.mnemonic != "mov" or len(ops) != 2 or ops[0].type != X86_OP_REG:
        return None
    reg = ops[0].reg
    nxt = insns.get(ref.insn_off + insn.size)
    if reg == X86_REG_EAX and nxt is not None and nxt.mnemonic == "ret" and ctx.section(ref.value) == ".text":
        return "catch-continuation"
    off = ref.insn_off + insn.size
    for _ in range(8):
        cur = insns.get(off)
        if cur is None:
            return None
        for op in cur.operands:
            if op.type == X86_OP_MEM and op.mem.base == reg:
                return "deref"
        if cur.mnemonic == "call" and reg == X86_REG_ECX:
            return "this-call"
        _, written = cur.regs_access()
        if reg in written or terminal(cur) or CS_GRP_JUMP in set(cur.groups):
            return None
        off += cur.size
    return None


def make_reloc(ctx, ref, kind, target, rule, evidence, va, size, symbol):
    if va <= target < va + size:
        sym, addend, cls, note = symbol, target - va, "self", ""
    else:
        sym, addend, cls, note = ctx.owner(target)
    return {"site": ref.off, "kind": kind, "symbol": sym, "addend": addend, "target": target,
            "cls": cls, "rule": rule, "evidence": ";".join(x for x in (evidence, note) if x),
            "insn": ref.text, "insn_off": ref.insn_off}


# --------------------------------------------------------------------------- sources

PROC = re.compile(r"^(\S+)\s+PROC\b")
ENDP = re.compile(r"^(\S+)\s+ENDP\b")
DB_TOKEN = re.compile(r"^(?:0?([0-9A-Fa-f]+)[hH]|(\d+))$")


def parse_source(path):
    """{proc name: bytes or None when the body is not a pure db dump}."""
    procs, current, chunks, pure = {}, None, [], True
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        stripped = line.split(";", 1)[0].strip()
        if not stripped:
            continue
        if current is None:
            m = PROC.match(stripped)
            if m:
                current, chunks, pure = m.group(1), [], True
            continue
        m = ENDP.match(stripped)
        if m and m.group(1) == current:
            procs[current] = bytes(chunks) if pure else None
            current = None
            continue
        if stripped.lower().startswith("db "):
            for token in stripped[3:].split(","):
                t = DB_TOKEN.match(token.strip())
                if not t:
                    pure = False
                    break
                chunks.append(int(t.group(1), 16) if t.group(1) else int(t.group(2)))
        else:
            pure = False
    return procs


def dump_sources(ctx):
    """{source: [rows]} for every matched row whose source is a .asm file."""
    by_source = collections.defaultdict(list)
    for row in ctx.rows:
        if row["source"].lower().endswith(".asm"):
            by_source[row["source"]].append(row)
    return by_source


# --------------------------------------------------------------------------- emission

def masm_name(name, placeholders):
    if SAFE_NAME.match(name) and len(name) <= MASM_NAME_LIMIT:
        return name
    if name not in placeholders:
        placeholders[name] = f"lnm_{len(placeholders):05d}"
    return placeholders[name]


def fmt_addend(addend):
    if addend == 0:
        return ""
    return f" + 0{addend:X}h" if addend > 0 else f" - 0{-addend:X}h"


def hexbytes(chunk):
    return ", ".join(f"0{b:02X}h" for b in chunk)


def emit_asm(source, items):
    """MASM text for one dump source.

    items = [(symbol, va, bytes, relocs, is_table)]: one segment each, so every
    reference between two items is a relocation, never an assembler constant."""
    placeholders = {}
    defined = {item[0] for item in items}
    externs = {}
    for _, _, _, relocs, _ in items:
        for r in relocs:
            if r["symbol"] not in defined:
                code = r["kind"] == REL32 or r["cls"] in CODE_CLASSES
                externs[r["symbol"]] = externs.get(r["symbol"], False) or code
    lines = [".386", ".model flat", f"; generated by tools/dump_relocs.py from {source}; do not edit", ""]
    for name in sorted(externs):
        lines.append(f"EXTERN {masm_name(name, placeholders)}:{'NEAR' if externs[name] else 'BYTE'}")
    for symbol, va, body, relocs, is_table in items:
        seg = f"_TEXT${'t' if is_table else 'd'}{va:08x}"
        msym = masm_name(symbol, placeholders)
        what = "switch table (no ledger row) " if is_table else ""
        lines += ["", f"{seg} SEGMENT BYTE PUBLIC FLAT 'CODE'", f"; {what}retail VA 0x{va:08X} size {len(body)}",
                  f"public {msym}", f"{msym} LABEL BYTE" if is_table else f"{msym} PROC"]
        pos = 0

        def flush(end):
            nonlocal pos
            while pos < end:
                step = min(16, end - pos)
                lines.append(f"    db {hexbytes(body[pos:pos + step])}")
                pos += step

        for r in relocs:
            target = masm_name(r["symbol"], placeholders) + fmt_addend(r["addend"])
            if r["kind"] == DIR32:
                flush(r["site"])
                lines.append(f"    dd {target}")
                pos = r["site"] + 4
            else:
                opcode = body[r["site"] - 1]
                if opcode == 0xE8:
                    mnem, op_start = "call", r["site"] - 1
                elif opcode == 0xE9:
                    mnem, op_start = "jmp", r["site"] - 1
                elif body[r["site"] - 2] == 0x0F and opcode in JCC:
                    mnem, op_start = JCC[opcode], r["site"] - 2
                else:
                    raise ValueError(f"{symbol}+{r['site']:#x}: rel32 without E8/E9/0F8x opcode")
                flush(op_start)
                lines.append(f"    {mnem} {target}")
                pos = r["site"] + 4
        flush(len(body))
        if not is_table:
            lines.append(f"{msym} ENDP")
        lines.append(f"{seg} ENDS")
    lines += ["", "END", ""]
    rename = {v: k for k, v in placeholders.items()}
    if rename:
        lines.insert(3, "; long or unsafe names (renamed in the object after assembly):")
        for i, (ph, name) in enumerate(sorted(rename.items())):
            lines.insert(4 + i, f";   {ph} = {name}")
    return "\n".join(lines), rename


def assemble(asm_path, obj_path, rename):
    root = build.vc71_root()
    env = build.compiler_environment(root, None)
    cmd = [str(root / "Vc7" / "bin" / "ml.exe"), "-nologo", "-c", "-Cp", f"-Fo{obj_path}", str(asm_path)]
    proc = subprocess.run(cmd, capture_output=True, text=True, env=env, cwd=str(asm_path.parent))
    if proc.returncode != 0:
        raise RuntimeError(f"ml failed for {asm_path.name}: {(proc.stdout + proc.stderr).strip()[-2000:]}")
    if rename:
        rename_symbols(obj_path, rename)


def rename_symbols(obj_path, rename):
    """Rewrite placeholder symbol names in a COFF object (MASM caps names at 247 chars)."""
    data = bytearray(obj_path.read_bytes())
    symtab, count = build.u32(data, 8), build.u32(data, 12)
    strings_at = symtab + count * 18
    strings = bytearray(data[strings_at:])
    found = set()
    i = 0
    while i < count:
        off = symtab + i * 18
        name = build.coff_name(data, off, bytes(strings))
        if name in rename:
            found.add(name)
            data[off:off + 8] = struct.pack("<II", 0, len(strings))
            strings += rename[name].encode("latin-1") + b"\0"
        i += 1 + data[off + 17]
    missing = set(rename) - found
    if missing:
        raise RuntimeError(f"{obj_path.name}: placeholders not in object: {sorted(missing)[:3]}")
    struct.pack_into("<I", strings, 0, len(strings))
    obj_path.write_bytes(bytes(data[:strings_at]) + bytes(strings))


# --------------------------------------------------------------------------- verification

def read_object(obj_path):
    """{section name: (bytes, [(offset, type, symbol)])} and {symbol: (section name, value)}."""
    data = obj_path.read_bytes()
    symbols = build.read_object_symbols(data)
    count = build.u16(data, 2)
    strings = data[build.u32(data, 8) + build.u32(data, 12) * 18:]
    sections, names = {}, []
    for i in range(count):
        o = 20 + i * 40
        raw_name = data[o:o + 8]
        if raw_name[:1] == b"/":
            idx = int(raw_name[1:].rstrip(b"\0"))
            name = strings[idx:strings.index(b"\0", idx)].decode("latin-1")
        else:
            name = raw_name.rstrip(b"\0").decode("latin-1")
        raw_size, raw_ptr, rel_ptr = struct.unpack_from("<III", data, o + 16)
        nrel = build.u16(data, o + 32)
        relocs = []
        for r in range(nrel):
            va, si, rtype = struct.unpack_from("<IIH", data, rel_ptr + r * 10)
            relocs.append((va, rtype, symbols[si]["name"]))
        sections[name] = (data[raw_ptr:raw_ptr + raw_size], relocs)
        names.append(name)
    defined = {s["name"]: (names[s["section"] - 1], s["value"]) for s in symbols
               if s["section"] > 0 and s["name"]}
    return sections, defined


def resolve(section_bytes, relocs, place, address_of):
    out = bytearray(section_bytes)
    for off, rtype, sym in relocs:
        inplace = struct.unpack_from("<i", out, off)[0]
        s = address_of(sym)
        if rtype == DIR32:
            value = s + inplace
        elif rtype == REL32:
            value = s + inplace - (place + off + 4)
        else:
            raise ValueError(f"unexpected relocation type {rtype:#x}")
        struct.pack_into("<I", out, off, value & 0xFFFFFFFF)
    return bytes(out)


def shift_of(symbol):
    """Independent, deterministic displacement for every symbol (bodies included):
    0x1000 plus a multiple of 16 below 1 MB, so no two symbols move together."""
    return SHIFT_BODY + (zlib.crc32(symbol.encode("latin-1")) % 0xFF00) * 0x10


def verify_file(obj_path, bodies, symbol_va, in_image):
    """Per body: list of failure strings (empty = verified at both placements)."""
    sections, defined = read_object(obj_path)
    local_va = {symbol: va for symbol, va, _, _, _ in bodies}

    def retail_address(sym):
        return local_va[sym] if sym in local_va else symbol_va[sym]

    def shifted_address(sym):
        return retail_address(sym) + shift_of(sym)

    results = {}
    for symbol, va, body, relocs, analysis in bodies:
        errors = []
        if symbol not in defined:
            results[symbol] = ["symbol missing from object"]
            continue
        section, value = defined[symbol]
        raw, orelocs = sections[section]
        if len(raw) != len(body) or value != 0:
            results[symbol] = [f"section {section} holds {len(raw)} bytes, symbol at +{value}, body {len(body)}"]
            continue
        # the object's relocations must be exactly the recovered ones
        expected = sorted((r["site"], r["kind"], r["symbol"]) for r in relocs)
        if sorted(orelocs) != expected:
            errors.append(f"object relocations {len(orelocs)} != recovered {len(relocs)}")
        # (i) retail placement
        try:
            got = resolve(raw, orelocs, va, retail_address)
        except KeyError as exc:
            results[symbol] = errors + [f"no address for symbol {exc}"]
            continue
        if got != body:
            diff = next(i for i in range(len(body)) if got[i] != body[i])
            errors.append(f"retail placement differs at +{diff:#x}")
        # (ii) every symbol, this body included, at its own shifted address
        place = shifted_address(symbol)
        moved = resolve(raw, orelocs, place, shifted_address)
        fields = set()
        for off, _, _ in orelocs:
            fields.update(range(off, off + 4))
        if any(moved[i] != body[i] for i in range(len(body)) if i not in fields):
            errors.append("shifted placement changed a byte outside relocation fields")
        by_site = {r["site"]: r for r in relocs}
        for off, rtype, sym in orelocs:
            r = by_site.get(off)
            if r is None:
                continue
            want = (shifted_address(sym) + r["addend"]) & 0xFFFFFFFF
            if rtype == DIR32:
                got_target = struct.unpack_from("<I", moved, off)[0]
            else:
                got_target = (place + off + 4 + struct.unpack_from("<i", moved, off)[0]) & 0xFFFFFFFF
            if got_target != want or want == r["target"]:
                errors.append(f"+{off:#x} {sym} decodes to {got_target:#x}, moved target is {want:#x}")
        # no literal retail address left in reached code, except the listed ambiguous ones
        listed = analysis["ambiguous_sites"]
        for off, insn in analysis["insns"].items():
            moved_insn = decode(moved, off, place)
            if moved_insn is None or moved_insn.size != insn.size:
                errors.append(f"+{off:#x} decodes differently after the move")
                continue
            for ref in insn_refs(moved_insn, off):
                if ref.off in fields or ref.off in listed:
                    continue
                if ref.kind == "branch":
                    if not place <= ref.value < place + len(body):
                        errors.append(f"+{off:#x} branch still aims at {ref.value:#x}")
                elif in_image(ref.value):
                    errors.append(f"+{off:#x} literal retail address {ref.value:#x} left ({ref.text})")
        results[symbol] = errors
    return results


# --------------------------------------------------------------------------- driver

def process_source(source, rows, ctx):
    """Analyse, emit and verify one dump source: (relocations, ambiguous, body summaries, tables)."""
    procs = parse_source(ROOT / source)
    items, summaries, all_relocs, all_ambiguous, all_tables = [], [], [], [], []
    for row in sorted(rows, key=lambda r: int(r["target_rva"], 16)):
        symbol = build.ledger_object_symbol(row)
        rva, size = int(row["target_rva"], 16), int(row["target_size"])
        va = ctx.base + rva
        summary = {"source": source, "symbol": symbol, "rva": f"0x{rva:08X}", "size": size,
                   "status": "", "rel32": 0, "dir32": 0, "ambiguous": 0, "unreached": 0, "tables": 0,
                   "reasons": "", "detail": "", "_hard": []}
        summaries.append(summary)
        if symbol not in procs:
            summary.update(status="failed", reasons="proc-missing")
            continue
        text = procs[symbol]
        if text is None:
            summary.update(status="symbolic", reasons="already-symbolic")
            continue
        retail = build.read_target_bytes(rva, size)
        if text != retail:
            summary.update(status="failed", reasons="db-differs-from-retail",
                           detail=f"db {len(text)} bytes, row {size}")
            continue
        extra = [g - va for g in ctx.ghidra_in(va, size)]
        c = classify(retail, va, ctx, symbol, extra)
        c["analysis"]["ambiguous_sites"] = {a[0] for a in c["ambiguous"]}
        summary["rel32"] = sum(r["kind"] == REL32 for r in c["relocs"])
        summary["dir32"] = sum(r["kind"] == DIR32 for r in c["relocs"])
        summary["ambiguous"] = len(c["ambiguous"])
        summary["unreached"] = c["info"]["unreached-bytes"]
        summary["tables"] = len(c["tables"])
        summary["_hard"] = [f for f in c["failures"] if f[0] != "unreached"]
        summary["reasons"] = ";".join(sorted({f[0] for f in c["failures"]}))
        for r in c["relocs"]:
            all_relocs.append({"source": source, "body": symbol, "body_va": va, "site_va": va + r["site"], **r})
        for site, value, section, reason, insn, evidence in c["ambiguous"]:
            all_ambiguous.append({"source": source, "body": symbol, "body_va": f"0x{va:08X}",
                                  "site": f"{site:#x}", "value": f"0x{value:08X}", "section": section or "",
                                  "reason": reason, "evidence": evidence, "insn": insn})
        items.append((symbol, va, retail, c["relocs"], c["analysis"], summary, False))
        for t in c["tables"]:
            for r in t["relocs"]:
                all_relocs.append({"source": source, "body": t["label"], "body_va": t["va"],
                                   "site_va": t["va"] + r["site"], **r})
            all_tables.append({"source": source, "body": symbol, "label": t["label"], "va": f"0x{t['va']:08X}",
                               "kind": t["kind"], "bytes": len(t["bytes"]), "entries": len(t["relocs"])})
            items.append((t["label"], t["va"], t["bytes"], t["relocs"],
                          {"insns": {}, "ambiguous_sites": set()}, summary, True))
    if items:
        finish_source(source, items, ctx)
    return all_relocs, all_ambiguous, summaries, all_tables


def finish_source(source, items, ctx):
    """Emit, assemble and verify; writes each summary's status."""
    def fail_all(reason, detail=""):
        for item in items:
            item[5]["_hard"].append((reason, 0, detail))

    stem = re.sub(r"[^A-Za-z0-9_]+", "_", Path(source).with_suffix("").as_posix())
    asm_path, obj_path = OUT / "asm" / f"{stem}.asm", OUT / "obj" / f"{stem}.obj"
    try:
        text, rename = emit_asm(source, [(s, va, b, r, t) for s, va, b, r, _, _, t in items])
        asm_path.write_text(text, encoding="utf-8", newline="\n")
        assemble(asm_path, obj_path, rename)
    except (ValueError, RuntimeError) as exc:
        fail_all("emit-or-assemble", str(exc)[-300:])
        print(exc, file=sys.stderr)
    else:
        symbol_va, clash = {}, set()
        for _, _, _, relocs, _, _, _ in items:
            for r in relocs:
                address = r["target"] - r["addend"]
                if symbol_va.setdefault(r["symbol"], address) != address:
                    clash.add(r["symbol"])
        results = verify_file(obj_path, [(s, va, b, r, a) for s, va, b, r, a, _, _ in items], symbol_va,
                              lambda v: ctx.in_image(v) and v >= ctx.base + 0x1000)
        for symbol, _, _, relocs, _, summary, _ in items:
            if any(r["symbol"] in clash for r in relocs):
                summary["_hard"].append(("symbol-has-two-addresses", 0, ""))
            for error in results.get(symbol, ["not verified"]):
                summary["_hard"].append(("verify", 0, f"{symbol[:40]}: {error}"))
    for *_, summary, is_table in items:
        if is_table:
            continue
        hard = summary.pop("_hard")
        if hard:
            summary["status"] = "failed"
            summary["reasons"] = ";".join(sorted({h[0] for h in hard} | set(filter(None, summary["reasons"].split(";")))))
            summary["detail"] = "; ".join(f"{k}@+{o:#x} {d}".strip() for k, o, d in hard[:3])
        elif summary["ambiguous"] or summary["unreached"]:
            summary["status"] = "ambiguous"
        else:
            summary["status"] = "exact"


def _ghidra_in(self, va, size):
    return [g for g in self._ghidra_sorted[bisect.bisect_right(self._ghidra_sorted, va):
                                            bisect.bisect_left(self._ghidra_sorted, va + size)]]


Context.ghidra_in = _ghidra_in


def load_context():
    ctx = Context()
    ctx._ghidra_sorted = sorted(ctx.ghidra)
    return ctx


RELOC_FIELDS = ["site_va", "kind", "symbol", "addend", "target", "cls", "rule", "evidence", "body", "site",
                "source", "insn"]


def dump_root(source):
    return "gen_asm" if source.startswith("game/gen_asm/") else         "masm_dumps" if source.startswith("game/masm_dumps/") else "other .asm"


def write_outputs(relocs, ambiguous, summaries, tables, out):
    for s in summaries:
        hard = s.pop("_hard", None)
        if hard and s["status"] != "failed":
            raise AssertionError(f"{s['symbol']}: hard failures {hard} but status {s['status']}")
    out.mkdir(parents=True, exist_ok=True)
    with (out / "relocs.csv").open("w", newline="", encoding="utf-8") as handle:
        w = csv.writer(handle, lineterminator="\n")
        w.writerow(RELOC_FIELDS)
        for r in sorted(relocs, key=lambda r: r["site_va"]):
            w.writerow([f"0x{r['site_va']:08X}", "REL32" if r["kind"] == REL32 else "DIR32", r["symbol"],
                        f"{r['addend']:#x}" if r["addend"] >= 0 else f"-{-r['addend']:#x}",
                        f"0x{r['target']:08X}", r["cls"], r["rule"], r["evidence"], r["body"],
                        f"{r['site']:#x}", r["source"], r["insn"]])
    with (out / "ambiguous.csv").open("w", newline="", encoding="utf-8") as handle:
        fields = ["source", "body", "body_va", "site", "value", "section", "reason", "evidence", "insn"]
        w = csv.DictWriter(handle, fields, lineterminator="\n")
        w.writeheader()
        w.writerows(sorted(ambiguous, key=lambda a: (a["body_va"], int(a["site"], 16))))
    with (out / "tables.csv").open("w", newline="", encoding="utf-8") as handle:
        fields = ["source", "body", "label", "va", "kind", "bytes", "entries"]
        w = csv.DictWriter(handle, fields, lineterminator="\n")
        w.writeheader()
        w.writerows(sorted(tables, key=lambda t: t["va"]))
    with (out / "bodies.csv").open("w", newline="", encoding="utf-8") as handle:
        fields = ["source", "symbol", "rva", "size", "status", "rel32", "dir32", "ambiguous", "unreached",
                  "tables", "reasons", "detail"]
        w = csv.DictWriter(handle, fields, lineterminator="\n")
        w.writeheader()
        w.writerows(sorted(summaries, key=lambda s: s["rva"]))
    status, status_bytes = collections.Counter(), collections.Counter()
    for s in summaries:
        status[s["status"]] += 1
        status_bytes[s["status"]] += s["size"]
    labels = collections.Counter(t["label"] for t in tables)
    summary = {
        "bodies": len(summaries), "bytes": sum(s["size"] for s in summaries),
        "status": dict(status), "status_bytes": dict(status_bytes),
        "relocations": dict(collections.Counter(("REL32" if r["kind"] == REL32 else "DIR32") + ":" + r["rule"]
                                                for r in relocs)),
        "target_classes": dict(collections.Counter(r["cls"] for r in relocs)),
        "imm_evidence": dict(collections.Counter(r["evidence"].split(";")[0] for r in relocs
                                                 if r["rule"] == "imm")),
        "ambiguous": dict(collections.Counter(a["reason"] for a in ambiguous)),
        "ambiguous_sections": dict(collections.Counter(a["section"] for a in ambiguous)),
        "failure_reasons": dict(collections.Counter(reason for s in summaries if s["status"] == "failed"
                                                    for reason in s["reasons"].split(";") if reason)),
        "ambiguous_body_reasons": dict(collections.Counter(reason for s in summaries if s["status"] == "ambiguous"
                                                           for reason in (["unreached"] if s["unreached"] else [])
                                                           + (["operand"] if s["ambiguous"] else []))),
        "unreached_bytes": sum(s["unreached"] for s in summaries),
        "by_root": {root: dict(collections.Counter(s["status"] for s in summaries if dump_root(s["source"]) == root))
                    for root in sorted({dump_root(s["source"]) for s in summaries})},
        "external_tables": {"count": len(tables), "bytes": sum(t["bytes"] for t in tables),
                            "labels_defined_twice": sorted(l for l, n in labels.items() if n > 1)},
    }
    (out / "summary.json").write_text(json.dumps(summary, indent=1, sort_keys=True), encoding="utf-8")
    return summary


LINK_BASE = 0x10000000


def stub_object(names, path):
    """COFF object defining every name at its own 16-byte slot of one .text section."""
    strings, symbols = bytearray(4), bytearray()
    for i, name in enumerate(sorted(names)):
        raw = name.encode("latin-1")
        field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strings))
        if len(raw) > 8:
            strings.extend(raw + b"\0")
        symbols += field + struct.pack("<IhHBB", 16 * i, 1, 0, 2, 0)
    strings[0:4] = struct.pack("<I", len(strings))
    body = b"\xcc" * (16 * max(1, len(names)))
    table = 20 + 40 + len(body)
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, table, len(symbols) // 18, 0, 0)
    section = b".text$zz" + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x60500020)
    path.write_bytes(header + section + body + bytes(symbols) + bytes(strings))


def link_check(source, ctx):
    """Link one source's scaffold object with MSVC 7.1 link.exe at a non-retail base
    (every external a stub at its own address) and check the linked bytes: every
    relocation field holds its symbol's LINKED address (+addend, pc-relative for
    REL32) and every other byte is retail's. Returns the number of failures."""
    import pefile
    stem = re.sub(r"[^A-Za-z0-9_]+", "_", Path(source).with_suffix("").as_posix())
    obj = OUT / "obj" / f"{stem}.obj"
    work = OUT / "link" / stem
    work.mkdir(parents=True, exist_ok=True)
    data = obj.read_bytes()
    symbols = build.read_object_symbols(data)
    externs = sorted({x["name"] for x in symbols if x["section"] == 0 and x["storage"] == 2 and x["name"]})
    stub_object(externs + ["_stub_entry"], work / "stub.obj")
    root = build.vc71_root()
    env = build.compiler_environment(root, None)
    exe, mapfile = work / "scaffold.exe", work / "scaffold.map"
    cmd = [str(root / "Vc7" / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO",
           "/MACHINE:X86", "/SUBSYSTEM:CONSOLE", "/FIXED", f"/BASE:{LINK_BASE:#x}", "/OPT:NOREF",
           "/ENTRY:stub_entry", f"/MAP:{mapfile}", f"/OUT:{exe}", str(obj), str(work / "stub.obj")]
    proc = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=env)
    if proc.returncode != 0:
        print(f"link-check {source}: link.exe exited {proc.returncode}")
        print(proc.stdout[-3000:])
        return 1
    linked = {}
    for line in mapfile.read_text(errors="replace").splitlines():
        parts = line.split()
        if len(parts) >= 3 and re.fullmatch(r"[0-9a-f]{4}:[0-9a-f]{8}", parts[0])                 and re.fullmatch(r"[0-9a-f]{8}", parts[2]):
            linked.setdefault(parts[1], int(parts[2], 16))
    pe = pefile.PE(str(exe))
    image = pe.get_memory_mapped_image()
    sections, defined = read_object(obj)
    failures = checked = moved = 0
    for name, (section, value) in sorted(defined.items()):
        if not section.startswith(".text$") or name not in linked:
            continue
        raw, relocs = sections[section]
        place = linked[name]
        got = image[place - LINK_BASE:place - LINK_BASE + len(raw)]
        retail_va = int(section[7:], 16)
        retail = ctx.read(retail_va, len(raw))
        fields = set()
        bad = []
        for off, rtype, sym in relocs:
            fields.update(range(off, off + 4))
            addend = struct.unpack_from("<i", raw, off)[0]
            want = linked[sym] + addend - (place + off + 4 if rtype == REL32 else 0)
            if struct.unpack_from("<I", got, off)[0] != want & 0xFFFFFFFF:
                bad.append(f"+{off:#x} {sym}")
            if linked[sym] != ctx.base and struct.unpack_from("<I", got, off)[0] != struct.unpack_from(
                    "<I", retail, off)[0]:
                moved += 1
        bad += [f"+{i:#x} byte" for i in range(len(raw)) if i not in fields and got[i] != retail[i]][:3]
        checked += 1
        if bad or place == retail_va:
            failures += 1
            print(f"link-check {name}: linked at {place:#x}: {bad[:4] or 'placed at its retail address'}")
    print(f"link-check {source}: {checked} section(s) linked at base {LINK_BASE:#x}, "
          f"{moved} relocation field(s) changed from retail, {failures} failure(s)")
    return failures


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("sources", nargs="*", help="dump sources (repo-relative .asm paths)")
    ap.add_argument("--all", action="store_true", help="every matched .asm source whose PROCs are db dumps")
    ap.add_argument("--link-check", metavar="SOURCE", action="append", default=[],
                    help="also link SOURCE's object at a non-retail base (repeatable; `all` = every source run)")
    args = ap.parse_args(argv)
    ctx = load_context()
    by_source = dump_sources(ctx)
    sources = sorted(by_source) if args.all else [s.replace("\\", "/") for s in args.sources]
    if not sources:
        ap.error("name a source or pass --all")
    for s in sources:
        if s not in by_source:
            ap.error(f"{s}: no matched ledger row names this source")
    (OUT / "asm").mkdir(parents=True, exist_ok=True)
    (OUT / "obj").mkdir(parents=True, exist_ok=True)
    relocs, ambiguous, summaries, tables = [], [], [], []
    workers = min(int(os.environ.get("BUILD_POOL", "6")), 6)
    with concurrent.futures.ThreadPoolExecutor(workers) as pool:
        for r, a, s, t in pool.map(lambda src: process_source(src, by_source[src], ctx), sources):
            relocs += r
            ambiguous += a
            summaries += s
            tables += t
    # a subset run reports beside, not over, the last full run
    summary = write_outputs(relocs, ambiguous, summaries, tables, OUT if args.all else OUT / "subset")
    print(json.dumps(summary, indent=1, sort_keys=True))
    checks = sources if args.link_check == ["all"] else [src.replace("\\", "/") for src in args.link_check]
    failed = sum(link_check(src, ctx) for src in checks
                 if (OUT / "obj" / (re.sub(r"[^A-Za-z0-9_]+", "_", Path(src).with_suffix("").as_posix()) + ".obj")).exists())
    return 1 if failed or summary["status"].get("failed") else 0


if __name__ == "__main__":
    sys.exit(main())
