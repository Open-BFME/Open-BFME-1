#!/usr/bin/env python3
"""Differential execution: run a ledger row's retail bytes and its rebuilt code
side by side in an x86 emulator and compare what each one does.

The byte gate proves a row by comparing compiled bytes with retail after
copying every DIR32 operand from retail and resolving each REL32 against a list
of candidate addresses (ledger rows, their thunks, AND every symbols.csv pin).
A row can therefore match while its source names the wrong callee (a pin that
happens to point where retail calls) or the wrong global (any DIR32 at all).
This tool resolves the rebuilt function's relocations the way the linker
would -- by the symbol's own definition -- and then executes both versions on
identical synthetic inputs:

  * retail image (all sections) mapped at its base; IAT slots point at
    per-import stubs; the rebuilt run overwrites only the row's extent with the
    object's bytes, relocated by definition;
  * three input vectors: ecx/edx and eight stack arguments as heap objects,
    as zeros, as small integers; a seeded heap whose words are pointers back
    into the heap or small integers, so pointer chains and vtables resolve;
  * every transfer out of the row's extent is a stubbed callee: the call
    (canonical retail identity: ILT thunks and `jmp [iat]` followed), its
    stack arguments and ecx are recorded, and it returns a value derived from
    the callee identity and its call ordinal;
  * writes outside the stack and reads of image data are recorded.

Relocation binding sources, strongest first: ledger row name, link_cycle map
(--map, code only), data ledger (BFME1 data_rows.csv, BFME2 exports.csv data
rows), `object-symbol=` alias rows, content (a datum defined in the object
whose bytes equal retail's at retail's operand), BFME1 dir32_addresses.csv
consensus, symbols.csv pin, and last `copied` (retail's operand; unverified,
counted per row in `sites`). Names nothing in the tree defines (CRT and library
internals of .lib members) are `copied`, never a divergence. A symbol defined by the ledger is never bound through a pin.

Verdicts (worst over vectors): `logic` (return value, writes or call order
differ), `binding` (first divergence is a different callee identity, global
address or data-pointer argument; `twin` when the two callees have equal
retail bytes), `build_env` (the divergence is a runtime-helper substitution such as
__ftol/__ftol2), `regalloc-only` (behaviour equal,
bytes or stack-local addresses differ), `none`, and `inconclusive` (no object,
unreadable symbol, unsupported relocation).

Dependency: the `unicorn` package (>= 2.0); `capstone` is optional (callee
`ret N` cleanup and --disasm). Install into a venv, e.g.
    python3 -m venv .venv && .venv/bin/pip install unicorn capstone

  python3 tools/diffexec.py --row NAME|0xRVA [--json] [--disasm]
  python3 tools/diffexec.py --all --json [--jobs 8] > diffexec.json
  python3 tools/diffexec.py --sample 2000 --seed 1 [--compile] [--json]
Exit status 1 when any selected row shows `logic` or `binding`.
"""
import argparse
import bisect
import contextlib
import csv
import hashlib
import json
import multiprocessing
import random
import re
import struct
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

try:
    import unicorn
    from unicorn import x86_const as X
except ImportError:  # reported by require_unicorn(); the module stays importable
    unicorn = X = None
try:
    import capstone
except ImportError:
    capstone = None

STACK_LO, STACK_HI = 0x0F000000, 0x0F100000
ESP0 = STACK_HI - 0x2000
HEAP, HEAP_SIZE = 0x30000000, 0x100000
MAGIC = 0x0E000000          # return address of the row under test
IMPORTS = 0x0E100000        # one 16-byte stub per imported name
PHANTOM = 0x0E400000        # data whose content differs from retail's operand
REGION_END = 0x0F000000     # MAGIC..REGION_END is one RWX mapping
MAX_INSNS = 100_000         # deterministic run limits: instructions and recorded
MAX_EVENTS = 4_000          # calls + global writes (a wall-clock cut is not reproducible)
SEVERITY = ["none", "inconclusive", "regalloc-only", "build_env", "binding", "logic"]
# Runtime helpers a toolchain may legitimately swap for one another.
HELPER_EQUIV = [{"__ftol", "__ftol2", "__ftol2_sse"}, {"__chkstk", "__alloca_probe"}]
THISCALL = re.compile(r"@@[ABEFIJMNQRUV][AB]E")


def require_unicorn():
    if unicorn is None:
        raise SystemExit("diffexec needs the `unicorn` package (pip install unicorn capstone)")


# ----------------------------------------------------------------- retail image
class Image:
    """A PE image as flat memory: base VA, SizeOfImage, sections and imports."""

    def __init__(self, base, size, sections, imports=None):
        self.base, self.size = base, size
        self.sections = sections            # [(rva, vsize, exec, name)]
        self.flat = bytearray(size)
        self.imports = imports or {}        # iat slot rva -> "dll!name"

    @classmethod
    def from_memory(cls, base, chunks, exec_ranges=()):
        """Tests: {rva: bytes} chunks; rva ranges in exec_ranges are code."""
        size = (max(rva + len(data) for rva, data in chunks.items()) + 0xFFF) & ~0xFFF
        image = cls(base, size, [(lo, hi - lo, True, ".text") for lo, hi in exec_ranges])
        for rva, data in chunks.items():
            image.flat[rva:rva + len(data)] = data
        return image

    @classmethod
    def from_pe(cls, path):
        data = Path(path).read_bytes()
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        count = struct.unpack_from("<H", data, pe + 6)[0]
        opt = pe + 24
        opt_size = struct.unpack_from("<H", data, pe + 20)[0]
        base, = struct.unpack_from("<I", data, opt + 28)
        size, = struct.unpack_from("<I", data, opt + 56)
        imp_rva, = struct.unpack_from("<I", data, opt + 104)
        sections = []
        image = cls(base, (size + 0xFFF) & ~0xFFF, sections)
        for i in range(count):
            at = opt + opt_size + 40 * i
            name = data[at:at + 8].rstrip(b"\0").decode("latin-1")
            vsize, rva, raw_size, raw_ptr = struct.unpack_from("<IIII", data, at + 8)
            flags, = struct.unpack_from("<I", data, at + 36)
            n = min(raw_size, vsize or raw_size)
            image.flat[rva:rva + n] = data[raw_ptr:raw_ptr + n]
            sections.append((rva, max(vsize, raw_size), bool(flags & 0x20000020), name))
        image.imports = image._parse_imports(imp_rva)
        return image

    def _parse_imports(self, rva):
        out = {}
        while rva:
            ilt, _, _, name_rva, iat = struct.unpack_from("<IIIII", self.flat, rva)
            if not iat:
                break
            dll = self.cstr(name_rva).lower()
            slot, src = iat, ilt or iat
            while True:
                entry, = struct.unpack_from("<I", self.flat, src)
                if not entry:
                    break
                name = f"#{entry & 0xFFFF}" if entry & 0x80000000 else self.cstr(entry + 2)
                out[slot] = f"{dll}!{name}"
                slot, src = slot + 4, src + 4
            rva += 20
        return out

    def import_stub(self, name):
        """Stub address of the import a plain external name links to, or None."""
        if not hasattr(self, "_by_name"):
            self.emulation_bytes()
            self._by_name = {}
            for address, full in self.stub_of.items():
                self._by_name.setdefault(full.split("!", 1)[1], address)
        bare = name.lstrip("_").split("@")[0]
        return self._by_name.get(name) or self._by_name.get(bare)

    def cstr(self, rva):
        end = self.flat.index(b"\0", rva)
        return self.flat[rva:end].decode("latin-1")

    def read(self, rva, n):
        return bytes(self.flat[rva:rva + n])

    def u32(self, rva):
        return struct.unpack_from("<I", self.flat, rva)[0]

    def is_code(self, rva):
        return any(lo <= rva < lo + n and ex for lo, n, ex, _ in self.sections)

    def contains_va(self, va):
        return self.base <= va < self.base + self.size

    def emulation_bytes(self):
        """Flat image with every IAT slot pointing at its import stub."""
        if not hasattr(self, "_emu"):
            flat = bytearray(self.flat)
            self.stub_of = {}
            for i, (slot, name) in enumerate(sorted(self.imports.items())):
                struct.pack_into("<I", flat, slot, IMPORTS + 16 * i)
                self.stub_of[IMPORTS + 16 * i] = name
            self._emu = bytes(flat)
        return self._emu


# --------------------------------------------------------------- binding context
class Context:
    """Everything a row's resolution and a run's identities depend on."""

    def __init__(self, image, ledger_rows, pins=(), data_ledger=None, consensus=None,
                 map_publics=None, sizes=None):
        self.image = image
        self.rows = ledger_rows
        self.defs, self.alias, self.names_at = {}, {}, {}
        for row in ledger_rows:
            rva = int(row["target_rva"], 16)
            self.defs.setdefault(row["name"], []).append(rva)
            self.names_at.setdefault(rva, row["name"])
            obj = object_symbol(row)
            if obj != row["name"]:
                self.alias.setdefault(obj, []).append(rva)
        self.pins = {}
        for name, rva in pins:
            self.pins.setdefault(name, []).append(rva)
        self.data = data_ledger or {}
        self.consensus = consensus or {}
        self.map = map_publics or {}
        self.row_starts = set(self.names_at)
        self.sizes = sizes or {int(r["target_rva"], 16): int(r["target_size"]) for r in ledger_rows}
        self._pops, self._extents = {}, {}
        self.phantom_bytes = {}

    def canon(self, va):
        """Retail identity of a code address: thunks and import jumps followed."""
        image = self.image
        if va == MAGIC:
            return "return"
        if va in getattr(image, "stub_of", {}):
            return "import:" + image.stub_of[va]
        if HEAP <= va < HEAP + HEAP_SIZE:
            return f"heap:+0x{va - HEAP:X}"
        if not image.contains_va(va) or va + 6 > image.base + image.size:
            return f"addr:0x{va:08X}"
        rva = va - image.base
        for _ in range(8):
            op = image.flat[rva]
            if op == 0xE9:      # ILT thunk, or a row that is only a tail jump
                nxt = rva + 5 + struct.unpack_from("<i", image.flat, rva + 1)[0]
                if not image.is_code(nxt):
                    break
                rva = nxt
            elif op == 0xFF and image.flat[rva + 1] == 0x25:
                slot = image.u32(rva + 2) - image.base
                if slot in image.imports:
                    return "import:" + image.imports[slot]
                break
            else:
                break
        return f"rva:0x{rva:08X}"

    def name_of(self, ident):
        if ident.startswith("rva:"):
            return self.names_at.get(int(ident[4:], 16), "")
        return ""

    def pop_count(self, ident):
        """Bytes a stubbed callee pops (`ret N`), from its retail body."""
        if ident in self._pops:
            return self._pops[ident]
        pop = 0
        if ident.startswith("rva:") and capstone is not None:
            rva = int(ident[4:], 16)
            size = self.sizes.get(rva, 0x400)
            md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
            for ins in md.disasm(self.image.read(rva, min(size, 0x4000)), rva):
                if ins.mnemonic == "ret":
                    pop = int(ins.op_str, 16) if ins.op_str else 0
                    break
        self._pops[ident] = pop
        return pop

    def twins(self, a, b, depth=3):
        """Equal retail code: same instructions, call/jump targets equal by
        identity or themselves twins (template instances over same-size types)."""
        if a == b:
            return True
        if depth == 0 or not (a.startswith("rva:") and b.startswith("rva:")) or capstone is None:
            return False
        ra, rb = int(a[4:], 16), int(b[4:], 16)
        n = self.sizes.get(ra)
        if not n or n != self.sizes.get(rb, n):
            return False
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        base = self.image.base
        left = list(md.disasm(self.image.read(ra, n), base + ra))
        right = list(md.disasm(self.image.read(rb, n), base + rb))
        if len(left) != len(right) or not left:
            return False
        for x, y in zip(left, right):
            if x.mnemonic != y.mnemonic:
                return False
            if x.bytes == y.bytes:
                continue
            branch = x.mnemonic == "call" or x.mnemonic.startswith("j")
            if not (branch and x.op_str.startswith("0x") and y.op_str.startswith("0x")):
                return False
            tx, ty = int(x.op_str, 16), int(y.op_str, 16)
            inside = base + ra <= tx < base + ra + n
            if inside and tx - (base + ra) != ty - (base + rb):
                return False
            if not inside and not self.twins(self.canon(tx), self.canon(ty), depth - 1):
                return False
        return True


def object_symbol(row):
    match = re.search(r"(?:^|;)object-symbol=([^;]+)", row.get("notes", "") or "")
    return match.group(1) if match else row["name"]


# ------------------------------------------------------------ rebuilt relocation
_STARTS = {}


def symbol_extent(sym_index, symbols, sec_size):
    """Bytes from a symbol to the next symbol of its section (or section end)."""
    sym = symbols[sym_index]
    index = _STARTS.get(id(symbols))
    if index is None or index[0] is not symbols:
        by_section = {}
        for s in symbols:
            if s.get("section", 0) > 0:
                by_section.setdefault(s["section"], set()).add(s["value"])
        index = (symbols, {k: sorted(v) for k, v in by_section.items()})
        if len(_STARTS) > 8:
            _STARTS.clear()
        _STARTS[id(symbols)] = index
    starts = index[1].get(sym["section"], [])
    at = bisect.bisect_right(starts, sym["value"])
    return (starts[at] if at < len(starts) else sec_size) - sym["value"]


def section_relocs(objdata, section):
    out = []
    for r in range(section["reloc_count"]):
        at = section["reloc_pointer"] + r * 10
        off, _, rtype = struct.unpack_from("<IIH", objdata, at)
        out.append((off, rtype))
    return out


def datum_matches(ctx, objdata, sections, symbols, sym_index, retail_rva):
    """True when the object's bytes for this symbol equal retail's at retail_rva
    (relocated words masked). Uninitialized data has no bytes to compare."""
    sym = symbols[sym_index]
    sec = sections[sym["section"] - 1]
    if not sec["raw_pointer"]:
        return None
    n = symbol_extent(sym_index, symbols, sec["raw_size"])
    if n <= 0 or n > 0x10000:
        return None
    mine = bytearray(objdata[sec["raw_pointer"] + sym["value"]:][:n])
    theirs = bytearray(ctx.image.read(retail_rva, n))
    for off, rtype in section_relocs(objdata, sec):
        rel = off - sym["value"]
        if 0 <= rel < n:
            mine[rel:rel + 4] = theirs[rel:rel + 4] = b"\0\0\0\0"
    return mine == theirs


def rebuild(ctx, row, compiled, relocs, info, objdata=None, sections=None):
    """The row's object bytes relocated by definition, plus one record per site."""
    image = ctx.image
    rva = int(row["target_rva"], 16)
    size = int(row["target_size"])
    va = image.base + rva
    out = bytearray(compiled[:size])
    retail = image.read(rva, size)
    symbols = (info or {}).get("symbols")
    reloc_syms = (info or {}).get("reloc_symbols") or [None] * len(relocs)
    if symbols and any(isinstance(s, dict) for s in reloc_syms):
        # BFME1's reader hands back the symbol records, BFME2's their indices
        position = {id(s): i for i, s in enumerate(symbols)}
        reloc_syms = [position.get(id(s)) if isinstance(s, dict) else s for s in reloc_syms]
    sites, phantoms, problems = [], {}, []
    for (off, rtype, name), sym_index in zip(relocs, reloc_syms):
        if off >= size:
            continue
        if rtype not in (0x06, 0x07, 0x14) or off + 4 > size:
            problems.append(f"relocation type 0x{rtype:X} at +0x{off:X}")
            continue
        addend, = struct.unpack_from("<i", out, off)
        want_field, = struct.unpack_from("<I", retail, off)
        if rtype == 0x14:
            retail_target = (va + off + 4 + struct.unpack_from("<i", retail, off)[0] - addend) & 0xFFFFFFFF
        elif rtype == 0x06:
            retail_target = (want_field - addend) & 0xFFFFFFFF
        else:
            retail_target = (want_field + image.base - addend) & 0xFFFFFFFF
        target, source = bind(ctx, row, name, sym_index, symbols, info, objdata, sections,
                              retail_target, phantoms)
        if rtype == 0x14:
            field = target + addend - (va + off + 4)
        elif rtype == 0x06:
            field = target + addend
        else:
            field = target + addend - image.base
        struct.pack_into("<I", out, off, field & 0xFFFFFFFF)
        sites.append({"offset": off, "type": rtype, "symbol": name, "source": source,
                      "target": target, "retail": retail_target})
    return bytes(out), sites, phantoms, problems


def bind(ctx, row, name, sym_index, symbols, info, objdata, sections, retail_target, phantoms):
    image = ctx.image
    rva = int(row["target_rva"], 16)
    sym = symbols[sym_index] if symbols and sym_index is not None else None
    own_section = sym is not None and info and sym["section"] == info.get("section")         and sym["section"] > 0
    if own_section and name not in ctx.defs:
        # a label or table of this body; a named function sharing a
        # non-COMDAT .text is placed by its own row instead (below)
        return image.base + rva + sym["value"] - info["value"], "self"

    def pick(cands):   # one definition per name in a link; ICF/dup rows give several
        vas = [image.base + c for c in cands]
        canon_retail = ctx.canon(retail_target)
        for v in vas:
            if v == retail_target or ctx.canon(v) == canon_retail:
                return v
        return vas[0]

    if sym is not None and sym["section"] == -1:
        return sym["value"], "absolute"
    if name in ("__except_list", "___except_list"):
        return 0, "absolute"           # the CRT's absolute 0 (fs:[0])
    if name in ctx.defs:
        return pick(ctx.defs[name]), "ledger"
    if name in ctx.map:
        return image.base + ctx.map[name], "map"
    if name in ctx.data:
        return image.base + ctx.data[name], "data-ledger"
    if name.startswith("__imp_"):
        want = name[6:].split("@")[0].lstrip("_")
        slots = [s for s, n in image.imports.items() if n.split("!")[1] in
                 (want, name[6:], name[7:], name[7:].split("@")[0])]
        if slots:
            slot = min(slots, key=lambda s: s + image.base != retail_target)
            return image.base + slot, "import"
    stub = image.import_stub(name) if sym is not None and sym["section"] == 0 else None
    if stub is not None and image.is_code(retail_target - image.base):
        return stub, "import-thunk"    # `call _wcslen` links to msvcr71's thunk
    if name in ctx.alias:
        return pick(ctx.alias[name]), "alias"
    same = is_code = None
    if sym is not None and sym["section"] > 0 and objdata is not None:
        is_code = bool(sections[sym["section"] - 1]["characteristics"] & 0x20)
        same = image.contains_va(retail_target) and datum_matches(
            ctx, objdata, sections, symbols, sym_index, retail_target - image.base)
        if same:
            return retail_target, "content"
        if same is False and not is_code:
            # A datum this object defines (a literal, a float, a table) whose
            # bytes are not retail's: the linker would emit OUR bytes.
            key = (name, sym_index)
            if key not in phantoms:
                phantoms[key] = PHANTOM + 0x1000 * len(phantoms)
            return phantoms[key], "content-mismatch"
    if name in ctx.consensus:
        return ctx.consensus[name], "consensus"
    if name in ctx.pins:
        # A pin is the weakest identity: used only for names nothing defines.
        # A locally compiled copy that differs from the pinned body is not
        # proof the pin is wrong (the callee may be unmatched), so it is
        # counted as unverified rather than diverged.
        return pick(ctx.pins[name]), "pin" if same is not False else "pin-unmatched-body"
    if same is False:
        return retail_target, "copied-unmatched-body"
    # Nothing in this environment defines the name (CRT/library internals the
    # tree does not link): retail's operand is used and the site is unverified.
    return retail_target, "copied"


# ------------------------------------------------------------------ execution
def heap_bytes(seed):
    out = bytearray(HEAP_SIZE)
    words = HEAP_SIZE // 4
    for i in range(words):
        h = (i * 0x9E3779B1 + seed * 0x85EBCA6B) & 0xFFFFFFFF
        h ^= h >> 15
        value = (h >> 8) % 8 if h % 4 == 0 else HEAP + ((h >> 4) % (words // 4 - 64)) * 16
        struct.pack_into("<I", out, i * 4, value)
    return bytes(out)


_HEAPS = {}


def vectors():
    obj = [HEAP + 0x1000 * k for k in range(1, 12)]
    return [
        {"name": "objects", "ecx": obj[0], "edx": obj[1], "args": obj[2:10], "seed": 1},
        {"name": "zeros", "ecx": obj[0], "edx": 0, "args": [0] * 8, "seed": 2},
        {"name": "ints", "ecx": obj[0], "edx": 1, "args": list(range(1, 9)), "seed": 3},
    ]


def norm(value):
    if STACK_LO <= value < STACK_HI:
        return "stk"
    return value


def run(ctx, start_va, size, code, vector, timeout_us):
    """Execute code (already placed at start_va) and return its observable trace."""
    image = ctx.image
    mu = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    mu.mem_map(image.base, image.size, unicorn.UC_PROT_ALL)
    mu.mem_write(image.base, image.emulation_bytes())
    if code is not None:
        mu.mem_write(start_va, code)
    mu.mem_map(STACK_LO, STACK_HI - STACK_LO)
    mu.mem_map(HEAP, HEAP_SIZE, unicorn.UC_PROT_ALL)
    if vector["seed"] not in _HEAPS:
        _HEAPS[vector["seed"]] = heap_bytes(vector["seed"])
    mu.mem_write(HEAP, _HEAPS[vector["seed"]])
    mu.mem_map(MAGIC, REGION_END - MAGIC, unicorn.UC_PROT_ALL)
    mu.mem_write(PHANTOM, b"\0" * 0x1000 * max(1, len(ctx.phantom_bytes)))
    for address, data in ctx.phantom_bytes.items():
        mu.mem_write(address, data)
    esp = ESP0
    mu.mem_write(esp, struct.pack("<I", MAGIC) + b"".join(
        struct.pack("<I", a) for a in vector["args"]))
    for reg, value in ((X.UC_X86_REG_ESP, esp), (X.UC_X86_REG_ECX, vector["ecx"]),
                       (X.UC_X86_REG_EDX, vector["edx"]), (X.UC_X86_REG_EAX, HEAP + 0xC000),
                       (X.UC_X86_REG_EBX, HEAP + 0xD000), (X.UC_X86_REG_ESI, HEAP + 0xE000),
                       (X.UC_X86_REG_EDI, HEAP + 0xF000), (X.UC_X86_REG_EBP, ESP0 + 0x800)):
        mu.reg_write(reg, value)
    trace = {"calls": [], "writes": {}, "reads": set(), "wild": 0, "end": None, "events": 0}
    ordinal = {}
    lo, hi = start_va, start_va + size

    def on_code(mu, address, _size, _):
        if address == MAGIC:
            trace["end"] = "return"
            mu.emu_stop()
            return
        ident = ctx.canon(address)
        esp = mu.reg_read(X.UC_X86_REG_ESP)
        try:
            ret = struct.unpack("<I", mu.mem_read(esp, 4))[0]
        except unicorn.UcError:
            trace["end"] = ("fault", "stack", ident)
            mu.emu_stop()
            return
        pop = ctx.pop_count(ident)
        follow = b""
        if lo <= ret < hi:
            follow = bytes(mu.mem_read(ret, 6))
        if follow[:2] == b"\x83\xC4":
            nargs = follow[2] // 4
        elif follow[:2] == b"\x81\xC4":
            nargs = min(struct.unpack_from("<I", follow, 2)[0] // 4, 16)
        else:
            nargs = pop // 4
        args = struct.unpack(f"<{nargs}I", mu.mem_read(esp + 4, 4 * nargs)) if nargs else ()
        n = ordinal[ident] = ordinal.get(ident, -1) + 1
        trace["events"] += 1
        if trace["events"] > MAX_EVENTS:
            trace["end"] = ("limit", "events")
            mu.emu_stop()
        thiscall = THISCALL.search(ctx.name_of(ident) or "") is not None
        trace["calls"].append((ident, tuple(norm(a) for a in args),
                               norm(mu.reg_read(X.UC_X86_REG_ECX)) if thiscall else None))
        h = int.from_bytes(hashlib.sha1(f"{ident}#{n}".encode()).digest()[:4], "little")
        value = (h >> 8) % 4 if h % 4 == 0 else HEAP + ((h >> 4) % (HEAP_SIZE // 16 - 64)) * 16
        mu.reg_write(X.UC_X86_REG_EAX, value)
        mu.reg_write(X.UC_X86_REG_EDX, 0)
        mu.reg_write(X.UC_X86_REG_ESP, esp + 4 + pop)
        mu.reg_write(X.UC_X86_REG_EIP, ret)

    def on_write(mu, _access, address, size, value, _):
        if size == 4 and STACK_LO <= value < STACK_HI:
            data = b"SSSS"
        else:
            data = (value & ((1 << (8 * size)) - 1)).to_bytes(size, "little")
        for i in range(size):
            trace["writes"][address + i] = data[i]
        trace["events"] += 1
        if trace["events"] > MAX_EVENTS:
            trace["end"] = ("limit", "events")
            mu.emu_stop()

    def on_read(mu, _access, address, size, _value, _):
        if not lo <= address < hi:
            trace["reads"].add(address)

    def on_unmapped(mu, access, address, size, value, _):
        page = address & ~0xFFF
        try:
            mu.mem_map(page, 0x1000, unicorn.UC_PROT_ALL)
        except unicorn.UcError:
            return False
        trace["wild"] += 1
        return True

    mu.hook_add(unicorn.UC_HOOK_CODE, on_code, None, 0, lo - 1)
    mu.hook_add(unicorn.UC_HOOK_CODE, on_code, None, hi, 0xFFFFFFFF)
    mu.hook_add(unicorn.UC_HOOK_MEM_WRITE, on_write, None, 0, STACK_LO - 1)
    mu.hook_add(unicorn.UC_HOOK_MEM_WRITE, on_write, None, STACK_HI, 0xFFFFFFFF)
    mu.hook_add(unicorn.UC_HOOK_MEM_READ, on_read, None, image.base, image.base + image.size - 1)
    mu.hook_add(unicorn.UC_HOOK_MEM_UNMAPPED, on_unmapped)
    began = time.perf_counter()
    try:
        mu.emu_start(start_va, MAGIC, timeout=timeout_us, count=MAX_INSNS)
    except unicorn.UcError as error:
        trace["end"] = ("fault", norm(mu.reg_read(X.UC_X86_REG_EIP)), str(error))
    if trace["end"] is None:
        eip = mu.reg_read(X.UC_X86_REG_EIP)
        if eip == MAGIC:
            trace["end"] = "return"
        elif (time.perf_counter() - began) * 1e6 >= timeout_us:
            trace["end"] = ("timeout",)    # wall-clock cut: not comparable
        else:
            trace["end"] = ("limit", "instructions")
    if trace["end"] == "return":
        trace["ret"] = (norm(mu.reg_read(X.UC_X86_REG_EAX)), norm(mu.reg_read(X.UC_X86_REG_EDX)),
                        mu.reg_read(X.UC_X86_REG_ESP) - (ESP0 + 4))
    return trace


# ------------------------------------------------------------------ comparison
def addressish(ctx, value):
    """A global/data address: the retail image or a phantom datum."""
    return isinstance(value, int) and (PHANTOM <= value < REGION_END or ctx.image.contains_va(value))


def classify(ctx, a, b, row_name):
    """(verdict, reason) for retail trace a against rebuilt trace b."""
    if (a["calls"], a["writes"], a["reads"], a["end"], a.get("ret")) == \
            (b["calls"], b["writes"], b["reads"], b["end"], b.get("ret")):
        return "none", ""
    for i, (ca, cb) in enumerate(zip(a["calls"], b["calls"])):
        if ca == cb:
            continue
        if ca[0] != cb[0]:
            names = {ca[0].split("!")[-1].lstrip("_"), cb[0].split("!")[-1].lstrip("_")}
            names |= {ctx.name_of(ca[0]).lstrip("_"), ctx.name_of(cb[0]).lstrip("_")}
            if any(len({n.lstrip("_") for n in group} & names) >= 2 for group in HELPER_EQUIV):
                return "build_env", f"call #{i}: runtime helper {ca[0]} vs {cb[0]}"
            twin = " (twin bodies)" if ctx.twins(ca[0], cb[0]) else ""
            return "binding", (f"call #{i}: retail {describe(ctx, ca[0])} rebuilt "
                               f"{describe(ctx, cb[0])}{twin}")
        diffs = [(x, y) for x, y in zip(ca[1], cb[1]) if x != y]
        if ca[2] != cb[2]:
            diffs.append((ca[2], cb[2]))
        if diffs and all(addressish(ctx, x) or addressish(ctx, y) for x, y in diffs):
            return "binding", f"call #{i} {describe(ctx, ca[0])}: data-pointer args " + ", ".join(
                f"0x{x:X}/0x{y:X}" if isinstance(x, int) and isinstance(y, int) else f"{x}/{y}"
                for x, y in diffs[:3])
        if all("stk" in (x, y) for x, y in diffs):
            continue
        return "logic", f"call #{i} {describe(ctx, ca[0])}: args differ {diffs[:3]}"
    image_reads = lambda t: {r for r in t["reads"] if not ctx.image.is_code(r - ctx.image.base)}
    ra, rb = image_reads(a), image_reads(b)
    if ra != rb and (rb - ra):
        only = sorted(rb - ra)[:2] + sorted(ra - rb)[:2]
        return "binding", "global reads differ: " + ", ".join(f"0x{x:X}" for x in only)
    if len(a["calls"]) != len(b["calls"]):
        return "logic", f"{len(a['calls'])} calls in retail, {len(b['calls'])} rebuilt"
    if a["writes"] != b["writes"]:
        keys = sorted(set(a["writes"]) ^ set(b["writes"]))
        if keys and all(addressish(ctx, k) for k in keys):
            return "binding", "global writes differ at " + ", ".join(f"0x{k:X}" for k in keys[:3])
        diff = sorted(k for k in set(a["writes"]) | set(b["writes"])
                      if a["writes"].get(k) != b["writes"].get(k))
        return "logic", f"{len(diff)} written byte(s) differ, first 0x{diff[0]:X}"
    if a["end"] != b["end"] or a.get("ret") != b.get("ret"):
        ra_, rb_ = a.get("ret"), b.get("ret")
        if ra_ and rb_ and ra_[0] != rb_[0] and addressish(ctx, ra_[0]) and addressish(ctx, rb_[0]):
            return "binding", f"returns 0x{ra_[0]:X} vs 0x{rb_[0]:X}"
        return "logic", f"end {a['end']} {ra_} vs {b['end']} {rb_}"
    if ra != rb:
        return "binding", "global reads differ"
    return "regalloc-only", "only stack-local addresses differ"


def describe(ctx, ident):
    name = ctx.name_of(ident)
    return f"{ident}({name})" if name else ident


def worst(verdicts):
    return max(verdicts, key=SEVERITY.index)


def diff_row(ctx, row, compiled, relocs, info=None, objdata=None, sections=None,
             budget_ms=2000):
    """Run retail and rebuilt for one row; returns the result record."""
    require_unicorn()
    began = time.perf_counter()
    rva, size = int(row["target_rva"], 16), int(row["target_size"])
    record = {"name": row["name"], "rva": f"0x{rva:08X}", "size": size,
              "source": row.get("source", "")}
    if len(compiled) < size:
        record.update(verdict="inconclusive", reason="object body shorter than the row")
        return record
    code, sites, phantoms, problems = rebuild(ctx, row, compiled, relocs, info, objdata, sections)
    counts = {}
    for site in sites:
        counts[site["source"]] = counts.get(site["source"], 0) + 1
    record["sites"] = counts
    if problems:
        record.update(verdict="inconclusive", reason="; ".join(problems[:3]))
        return record
    ctx.phantom_bytes = {}
    for (name, index), address in phantoms.items():
        sym = info["symbols"][index]
        sec = sections[sym["section"] - 1]
        n = symbol_extent(index, info["symbols"], sec["raw_size"])
        ctx.phantom_bytes[address] = bytes(objdata[sec["raw_pointer"] + sym["value"]:][:min(n, 0x1000)])
    retail = ctx.image.read(rva, size)
    record["bytes_equal"] = code == retail
    in_site = set()
    for site in sites:
        in_site.update(range(site["offset"], site["offset"] + 4))
    # differing only inside relocation fields = the same code linked differently
    same_code = all(x == y for i, (x, y) in enumerate(zip(code, retail)) if i not in in_site)
    va = ctx.image.base + rva
    timeout = max(1_000_000, budget_ms * 1000)   # safety net only; limits are counts
    verdicts, reasons = [], []
    for vector in vectors():
        a = run(ctx, va, size, None, vector, timeout)
        b = run(ctx, va, size, code, vector, timeout)
        if ("timeout",) in (a["end"], b["end"]):
            verdicts.append("inconclusive")
            reasons.append(f"{vector['name']}: wall-clock safety timeout")
            continue
        verdict, reason = classify(ctx, a, b, row["name"])
        if verdict == "none" and not same_code:
            verdict = "regalloc-only"
        verdicts.append(verdict)
        if reason:
            reasons.append(f"{vector['name']}: {reason}")
        record.setdefault("ends", []).append(str(a["end"])[:40])
    record["verdict"] = worst(verdicts)
    record["reason"] = " | ".join(reasons[:3])
    record["divergent_sites"] = [
        {k: (f"0x{v:08X}" if k in ("target", "retail") else v) for k, v in s.items()}
        for s in sites if s["target"] != s["retail"]][:8]
    record["ms"] = round((time.perf_counter() - began) * 1000, 1)
    if record["ms"] > budget_ms:
        record["over_budget"] = True
    return record


# ------------------------------------------------------------------ repo adapter
def load_context(map_path=None):
    import build
    image = Image.from_pe(build.EXE)
    rows = build.load_all_function_rows()
    reverse = Path(build.FUNCTIONS).parent
    pins = []
    if Path(build.SYMBOLS).exists():
        with open(build.SYMBOLS, encoding="utf-8", newline="") as handle:
            for pin in csv.DictReader(handle):
                try:
                    pins.append((pin["name"], int(pin["address"], 16)))
                except ValueError:
                    continue
    data, consensus = {}, {}
    if (reverse / "data_rows.csv").exists():          # BFME1 data ledger
        with open(reverse / "data_rows.csv", encoding="utf-8", newline="") as handle:
            for d in csv.DictReader(handle):
                address = int(d["address"], 16)
                data[d["name"]] = address - image.base if d.get("address_kind") == "va" else address
    if (reverse / "exports.csv").exists():            # BFME2 named data
        with open(reverse / "exports.csv", encoding="utf-8", newline="") as handle:
            for d in csv.DictReader(handle):
                if d.get("kind") == "data" and d.get("rva"):
                    data.setdefault(d["name"], int(d["rva"], 16))
    if (reverse / "dir32_addresses.csv").exists():
        with open(reverse / "dir32_addresses.csv", encoding="utf-8", newline="") as handle:
            for d in csv.DictReader(handle):
                consensus[d["name"]] = int(d["va"], 16)
    publics = {}
    path = Path(map_path) if map_path else Path(build.ROOT) / "build" / "link_cycle" / "base.map"
    if path.exists():
        starts = {int(r["target_rva"], 16) for r in rows}
        for line in path.read_text(encoding="latin-1").splitlines():
            if "Static symbols" in line:
                break
            m = re.match(r"\s*[0-9a-fA-F]{4}:[0-9a-fA-F]{8}\s+(\S+)\s+([0-9a-fA-F]{8})\s", line)
            if m and int(m.group(2), 16) - image.base in starts:
                publics[m.group(1)] = int(m.group(2), 16) - image.base
    return Context(image, rows, pins, data, consensus, publics)


def object_body(row):
    """(compiled, relocs, info, objdata, sections) from the row's built object."""
    import build
    obj = Path(build.row_object(row))
    if not obj.exists():
        raise LookupError(f"object {obj.name} not built (run with --compile or ./build.sh)")
    symbol = build.ledger_object_symbol(row)
    size = int(row["target_size"])
    if build.is_funclet_row(row, symbol):
        target = build.read_target_bytes(int(row["target_rva"], 16), size)
        compiled, relocs, _ = build.read_funclet(row, symbol, obj, target)
        return compiled, relocs, None, None, None
    try:
        compiled, relocs, info = build.read_object_symbol_bytes(obj, symbol, size, detail=True)
    except (ValueError, SystemExit) as error:
        raise LookupError(str(error)) from None
    stat = obj.stat()
    objdata, sections, _ = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    return compiled, relocs, info, objdata, sections


def diff_ledger_row(ctx, row, budget_ms):
    try:
        body = object_body(row)
    except LookupError as error:
        return {"name": row["name"], "rva": row["target_rva"], "size": int(row["target_size"]),
                "source": row["source"], "verdict": "inconclusive", "reason": str(error)[:200]}
    try:
        return diff_row(ctx, row, *body, budget_ms=budget_ms)
    except Exception as error:   # one row's harness failure must not end a sweep
        return {"name": row["name"], "rva": row["target_rva"], "size": int(row["target_size"]),
                "source": row["source"], "verdict": "inconclusive",
                "reason": f"harness: {type(error).__name__}: {error}"[:200]}


def stratum(row):
    size = int(row["target_size"])
    band = next(i for i, edge in enumerate((16, 64, 256, 1024, 1 << 40)) if size <= edge)
    source = row["source"].replace("\\", "/")
    kind = ("lib" if source.lower().endswith(".lib") else "asm" if source.endswith(".asm")
            else "generated" if "/gen_" in source else "authored")
    return f"{kind}/{band}"


def stratified_sample(rows, n, seed):
    rng = random.Random(seed)
    groups = {}
    for row in rows:
        groups.setdefault(stratum(row), []).append(row)
    picked = []
    for key in sorted(groups):
        group = groups[key]
        take = min(len(group), max(10, round(n * len(group) / len(rows))))
        picked += rng.sample(group, take)
    return picked


_CTX = None


def _init(map_path):
    global _CTX
    _CTX = load_context(map_path)


def _work(args):
    row, budget = args
    return diff_ledger_row(_CTX, row, budget)


def disasm(ctx, record, row):
    if capstone is None:
        return "(capstone not installed)"
    body = object_body(row)
    code, *_ = rebuild(ctx, row, *body[:3], body[3], body[4])
    rva = int(row["target_rva"], 16)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    lines = []
    for label, data in (("retail", ctx.image.read(rva, len(code))), ("rebuilt", code)):
        lines.append(f"--- {label}")
        for ins in md.disasm(data, ctx.image.base + rva):
            mark = " " if data[ins.address - ctx.image.base - rva:][:ins.size] == \
                ctx.image.read(ins.address - ctx.image.base, ins.size) else "*"
            lines.append(f"{mark} {ins.address:08X}  {ins.mnemonic} {ins.op_str}")
    return "\n".join(lines)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    pick = ap.add_mutually_exclusive_group(required=True)
    pick.add_argument("--row", action="append", help="row name or 0xRVA (repeatable)")
    pick.add_argument("--all", action="store_true", help="every matched row")
    pick.add_argument("--sample", type=int, help="stratified sample of N matched rows")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--source", help="only rows whose source contains this text")
    ap.add_argument("--map", help="link_cycle base.map (default build/link_cycle/base.map)")
    ap.add_argument("--compile", action="store_true", help="compile stale objects first")
    ap.add_argument("--jobs", type=int, default=1)
    ap.add_argument("--budget-ms", type=int, default=2000, help="per-row wall budget")
    ap.add_argument("--json", action="store_true", help="one JSON record per row")
    ap.add_argument("--disasm", action="store_true", help="with --row: retail/rebuilt listing")
    args = ap.parse_args(argv)
    require_unicorn()
    import build
    rows = [r for r in build.load_all_function_rows() if r["status"] == "matched"]
    if args.source:
        rows = [r for r in rows if args.source in r["source"]]
    if args.row:
        names = set(args.row)
        rvas = {int(w, 16) for w in args.row if w.lower().startswith("0x")}
        rows = [r for r in rows if r["name"] in names or int(r["target_rva"], 16) in rvas]
        if not rows:
            raise SystemExit("no matched row: " + ", ".join(args.row))
    elif args.sample:
        rows = stratified_sample(rows, args.sample, args.seed)
    if args.compile:
        sources = sorted({Path(build.ROOT) / r["source"] for r in rows})
        with contextlib.redirect_stdout(sys.stderr):   # keep --json output clean
            build.compile_rows(rows, sources)
    if args.jobs > 1 and len(rows) > 1:
        with multiprocessing.Pool(args.jobs, _init, (args.map,)) as pool:
            results = pool.map(_work, [(r, args.budget_ms) for r in rows], chunksize=8)
        ctx = None
    else:
        ctx = load_context(args.map)
        results = [diff_ledger_row(ctx, r, args.budget_ms) for r in rows]
    bad = 0
    for row, record in zip(rows, results):
        bad += record["verdict"] in ("logic", "binding")
        if args.json:
            print(json.dumps(record, sort_keys=True))
        else:
            print(f"{record['verdict']:13} {record['rva']} {record['name']} "
                  f"{record.get('ms', '')}ms {record.get('reason', '')}")
        if args.disasm and ctx is not None and record["verdict"] != "inconclusive":
            print(disasm(ctx, record, row))
    if not args.json:
        tally = {}
        for record in results:
            tally[record["verdict"]] = tally.get(record["verdict"], 0) + 1
        print("diffexec:", ", ".join(f"{k} {v}" for k, v in sorted(tally.items())),
              f"(seed {args.seed})" if args.sample else "")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
