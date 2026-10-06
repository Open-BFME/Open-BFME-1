#!/usr/bin/env python3
"""Retail inventories: what the retail image itself says, written only by this tool.

Three files under INVENTORY_DIR, each a pure function of the retail image and
the Ghidra function boundaries committed in the ledger directory. No ledger row,
source file or agent claim feeds them, so a candidate commit cannot create
authority by editing one: the commit gate (tools/hatch_counters.py --staged)
regenerates any staged inventory file and refuses it unless the bytes match.

  data_items.csv   every byte of .rdata and initialised .data, plus referenced
                   .bss starts, partitioned into items keyed by RVA:
                   string, wstring, float, vtable, eh_* (FuncInfo, unwind map,
                   try blocks, handlers, throw info, type descriptors), export,
                   iat, import_dir, safeseh, loadcfg, debug, jumptab,
                   fnptr_table, crt_inittab, scalar_const, global, bss, pad,
                   unknown; with a confidence (high/medium/low).
  fold_list.csv    (Open-BFME-2 only; BFME1 was linked without ICF) retail
                   functions whose bodies are twins: equal bytes AND equal
                   RESOLVED branch targets (rel32 calls/jumps followed through
                   jmp thunks; absolute operands are equal bytes in one image).
                   A masked compare (every address-like dword zeroed) accepts
                   far more; `masked_members` shows how many, and those extra
                   are NOT twins (_audit/research/31_evidence_recheck.md).
                   EH unwind actions and catch handlers (from every FuncInfo),
                   jump thunks and handler stubs (<=16 bytes ending in a jmp)
                   are left out: they belong to their parent body.
  flag_regions.csv contiguous .text regions with the compiler flags their code
                   shape implies (/O1 vs /O2, /arch:SSE vs x87, /G7 vs /G6),
                   with the evidence counts and purity behind each label
                   (_audit/research/25_flag_inference.md).

Ported from the audit prototypes _audit/scratch_r_data/{xrefs,partition}.py,
_audit/scratch_recheck/icf_*.py and _audit/scratch_r_flags/{feat,classify,
regions,regions2}.py; logic kept, inputs moved to the repo's own image and
Ghidra table, output made deterministic.

  python3 tools/retail_inventory.py            regenerate all inventories
  python3 tools/retail_inventory.py --check    regenerate in memory; exit 1 on any drift
  python3 tools/retail_inventory.py data|folds|flags   one inventory
"""
import argparse
import bisect
import collections
import csv
import hashlib
import io
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

if (ROOT / "targets" / "game" / "reverse").is_dir():      # Open-BFME-1
    GAME = "bfme1"
    EXE = ROOT / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
    GHIDRA = ROOT / "targets/game/reverse/ghidra_functions.csv"
    INVENTORY_DIR = "targets/game/reverse/retail_inventory/"
    KINDS = ("data", "flags")
else:                                                       # Open-BFME-2
    GAME = "bfme2"
    EXE = ROOT / "baselines/bfme2/workshop-vanilla-1.06/files/game.dat"
    GHIDRA = ROOT / "reverse/ghidra_functions.csv"
    INVENTORY_DIR = "reverse/retail_inventory/"
    KINDS = ("data", "folds", "flags")

FILES = {"data": "data_items.csv", "folds": "fold_list.csv", "flags": "flag_regions.csv"}


# ---------------------------------------------------------------- image

class Image:
    def __init__(self, path=EXE):
        import pefile
        pe = pefile.PE(str(path), fast_load=True)
        self.pe = pe
        self.base = pe.OPTIONAL_HEADER.ImageBase
        self.img = pe.get_memory_mapped_image()
        self.sha256 = hashlib.sha256(Path(path).read_bytes()).hexdigest()
        self.sec = {}
        for s in pe.sections:
            name = s.Name.rstrip(b"\0").decode(errors="replace")
            self.sec.setdefault(name, (s.VirtualAddress, s.Misc_VirtualSize, s.SizeOfRawData))
        tv, tvs, _ = self.sec[".text"]
        self.text = (self.base + tv, self.base + tv + tvs)

    def d(self, va):
        o = va - self.base
        return struct.unpack_from("<I", self.img, o)[0] if 0 <= o <= len(self.img) - 4 else 0

    def istext(self, va):
        return self.text[0] <= va < self.text[1]

    def sec_of(self, va):
        r = va - self.base
        for n, (v, vs, rs) in self.sec.items():
            if v <= r < v + max(vs, rs):
                return n
        return None


def ghidra_functions():
    rows = []
    with open(GHIDRA, newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            try:
                rows.append((int(r["rva"], 16), int(r["size"]), r["name"]))
            except (KeyError, ValueError):
                continue
    rows.sort()
    return rows


_REFS = {}


def code_refs(im):
    """Linear sweep of .text: (site, target, mnemonic, operands) for every absolute operand
    that points into the image outside .text, plus push/mov immediates into .text."""
    if im.sha256 in _REFS:
        return _REFS[im.sha256]
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    hexre = re.compile(r"0x[0-9a-f]+")
    tv, tvs, _ = im.sec[".text"]
    code = bytes(im.img[tv:tv + tvs])
    lo = im.base + min(v for n, (v, _, _) in im.sec.items() if n != ".text" and v > tv)
    hi = im.base + im.pe.OPTIONAL_HEADER.SizeOfImage
    refs, off = [], 0
    while off < len(code):
        last = off
        for a, sz, mn, op in md.disasm_lite(code[off:off + 0x10000], im.base + tv + off):
            for h in hexre.findall(op):
                v = int(h, 16)
                if lo <= v < hi:
                    refs.append((a, v, mn, op))
                elif im.text[0] <= v < im.text[1] and mn in ("push", "mov"):
                    refs.append((a, v, mn, op))
            last = a - im.base - tv + sz
        off = off + 1 if last == off else last
    _REFS[im.sha256] = refs
    return refs


# ---------------------------------------------------------------- data_items

NAMES = ["?", "export", "debug", "loadcfg", "iat", "eh_funcinfo", "eh_unwind", "eh_tryblock",
         "eh_handlers", "eh_throwinfo", "eh_typedesc", "vtable", "fnptr_table", "float", "string",
         "wstring", "crt_inittab", "global", "global_zero", "pad", "unknown", "scalar_const",
         "jumptab", "safeseh", "import_dir", "global_ptrtab", "bss"]
CI = {n: i for i, n in enumerate(NAMES)}
HIGH = {"export", "debug", "loadcfg", "iat", "import_dir", "safeseh", "eh_funcinfo", "eh_unwind",
        "eh_tryblock", "eh_handlers", "eh_throwinfo", "eh_typedesc", "vtable", "float", "string",
        "wstring", "crt_inittab", "jumptab"}
MEDIUM = {"fnptr_table", "scalar_const", "global", "global_zero", "global_ptrtab", "bss"}
OUT_CLASS = {"global_zero": "global", "global_ptrtab": "global"}


def data_items(im):
    B, img, d = im.base, im.img, im.d
    S = im.sec
    rd = (B + S[".rdata"][0], B + S[".rdata"][0] + S[".rdata"][1])
    da = (B + S[".data"][0], B + S[".data"][0] + min(S[".data"][1], S[".data"][2]))
    bss = (da[1], B + S[".data"][0] + S[".data"][1])
    regions = [rd, da]
    if ".idata" in S:
        regions.append((B + S[".idata"][0], B + S[".idata"][0] + S[".idata"][1]))
    offs, n = [], 0
    for lo, hi in regions:
        offs.append(n)
        n += hi - lo
    cls = bytearray(n)

    def idx(va):
        for (lo, hi), o in zip(regions, offs):
            if lo <= va < hi:
                return o + va - lo
        return None

    def indata(v):
        return idx(v) is not None

    def mark(va, size, c, force=False):
        for v in range(va, va + size):
            i = idx(v)
            if i is not None and (force or cls[i] == 0):
                cls[i] = CI[c]

    def ismarked(va):
        i = idx(va)
        return i is not None and cls[i] != 0

    refs = code_refs(im)
    DD = im.pe.OPTIONAL_HEADER.DATA_DIRECTORY
    # linker-generated directories
    mark(B + DD[0].VirtualAddress, DD[0].Size, "export")
    if DD[12].Size:
        mark(B + DD[12].VirtualAddress, DD[12].Size, "iat", True)
    if DD[1].Size:
        mark(B + DD[1].VirtualAddress, DD[1].Size, "import_dir", True)
        for k in range(DD[1].Size // 20):
            o = DD[1].VirtualAddress + 20 * k
            ilt, _, _, name, iat = struct.unpack_from("<5I", img, o)
            if not iat:
                break
            p = ilt or iat
            while d(B + p):
                if not d(B + p) & 0x80000000:
                    hint = d(B + p) & 0x7FFFFFFF
                    nm = img[hint + 2:hint + 258].split(b"\0")[0]
                    mark(B + hint, (2 + len(nm) + 2) & ~1, "import_dir", True)
                p += 4
            if ilt:
                mark(B + ilt, p - ilt + 4, "import_dir", True)
            nm = img[name:name + 256].split(b"\0")[0]
            mark(B + name, len(nm) + 1, "import_dir", True)
    if DD[6].Size:
        mark(B + DD[6].VirtualAddress, DD[6].Size, "debug")
        for k in range(DD[6].Size // 28):
            sz, addr = struct.unpack_from("<II", img, DD[6].VirtualAddress + 28 * k + 16)
            if addr:
                mark(B + addr, sz, "debug")
    if DD[10].Size:
        mark(B + DD[10].VirtualAddress, DD[10].Size, "loadcfg")
        if DD[10].Size >= 0x48:
            tab, cnt = struct.unpack_from("<II", img, DD[10].VirtualAddress + 0x40)
            if tab:
                mark(tab, 4 * cnt, "safeseh", True)
    # IAT by use, when there is no IAT directory: call/jmp [abs] into .rdata holding a non-image value
    if not DD[12].Size:
        def iatslot(w):
            return w == 0 or im.sec_of(B + w) not in (".text", ".rdata", ".data", None)
        iat = sorted({v for a, v, m, o in refs if m in ("call", "jmp") and o.startswith("dword ptr [0x")
                      and rd[0] <= v < rd[1] and d(v) and iatslot(d(v))})
        if iat:
            e = iat[0]
            while e < rd[1] and iatslot(d(e)):
                e += 4
            mark(iat[0], e - iat[0], "iat")
    # exception handling data
    MAG = {0x19930520: 28, 0x19930521: 32, 0x19930522: 36}
    fis = set()
    tv, tvs, _ = S[".text"]
    t = bytes(img[tv:tv + tvs])
    for m in re.finditer(rb"\xb8(....)\xe9", t, re.S):
        v = struct.unpack("<I", m.group(1))[0]
        if indata(v) and d(v) in MAG:
            fis.add(v)
    pat = b"|".join(re.escape(struct.pack("<I", k)) for k in sorted(MAG))
    for m in re.finditer(pat, bytes(img[rd[0] - B:rd[1] - B])):
        if m.start() % 4 == 0:
            v = rd[0] + m.start()
            ms, pu, nt, pt = struct.unpack_from("<IIII", img, v - B + 4)
            if ms < 5000 and nt < 500 and (ms == 0 or indata(pu)):
                fis.add(v)
    typedescs = set()
    for v in sorted(fis):
        mg, ms, pu, nt, pt = struct.unpack_from("<5I", img, v - B)
        mark(v, MAG[mg], "eh_funcinfo", True)
        if ms:
            mark(pu, 8 * ms, "eh_unwind", True)
        if nt and indata(pt):
            mark(pt, 20 * nt, "eh_tryblock", True)
            for k in range(nt):
                _, _, _, nc, ph = struct.unpack_from("<5I", img, pt - B + 20 * k)
                if nc < 100 and indata(ph):
                    mark(ph, 16 * nc, "eh_handlers", True)
                    for j in range(nc):
                        ptype = d(ph + 16 * j + 4)
                        if ptype and indata(ptype):
                            typedescs.add(ptype)
    for a, v, m, o in refs:
        if m == "push" and rd[0] <= v < rd[1] and v % 4 == 0:
            at, pu, pf, pcta = struct.unpack_from("<4I", img, v - B)
            if at < 16 and (pu == 0 or im.istext(pu)) and pf == 0 and indata(pcta):
                n_ = d(pcta)
                if 0 < n_ < 20 and all(indata(d(pcta + 4 + 4 * k)) for k in range(n_)):
                    if cls[idx(v)] == CI["eh_throwinfo"]:
                        continue
                    mark(v, 16, "eh_throwinfo", True)
                    mark(pcta, 4 + 4 * n_, "eh_throwinfo", True)
                    for k in range(n_):
                        ct = d(pcta + 4 + 4 * k)
                        mark(ct, 28, "eh_throwinfo", True)
                        typedescs.add(d(ct + 4))
    for td in sorted(typedescs):
        if indata(td):
            nm = img[td - B + 8:td - B + 264].split(b"\0")[0]
            if nm.startswith(b"."):
                mark(td, (8 + len(nm) + 1 + 3) & ~3, "eh_typedesc", True)
    # CRT initialiser tables: push hi; push lo with all words 0 or .text
    R = sorted(refs)
    for i in range(len(R) - 1):
        a1, v1, m1, _ = R[i]
        a2, v2, m2, _ = R[i + 1]
        if m1 == m2 == "push" and indata(v1) and indata(v2) and v2 < v1 and v1 - v2 < 0x4000 and a2 - a1 <= 6:
            ws = [d(x) for x in range(v2, v1, 4)]
            if ws and all(w == 0 or im.istext(w) for w in ws) and any(ws):
                mark(v2, v1 - v2, "crt_inittab", True)
    # references grouped by target, and data->data pointers
    by = collections.defaultdict(list)
    for a, v, m, o in R:
        if indata(v) or bss[0] <= v < bss[1]:
            by[v].append((m, o))
    dptr = set()
    for lo, hi in (rd, da):
        for x in range(lo, hi - 3, 4):
            w = d(x)
            if indata(w) or bss[0] <= w < bss[1]:
                dptr.add(w)
    starts = sorted(set(by) | dptr)

    def nxt(v):
        i = bisect.bisect_right(starts, v)
        return starts[i] if i < len(starts) else v + 0x1000

    for v in sorted(by):
        L = by[v]
        if not (rd[0] <= v < rd[1]) or ismarked(v):
            continue
        if any(m == "mov" and o.startswith("dword ptr [e") and o.endswith(hex(v)) for m, o in L) and im.istext(d(v)):
            e = v
            while e < rd[1] and im.istext(d(e)) and (e == v or e not in by):
                e += 4
            mark(v, e - v, "vtable")
    for v in sorted(by):
        for m, o in by[v]:
            if m == "jmp" and "*4 +" in o and indata(v):
                e = v
                while im.istext(d(e)) and (e == v or e not in by):
                    e += 4
                mark(v, e - v, "jumptab")
    W = {"dword": 4, "qword": 8, "xword": 10, "tbyte": 10}
    for v in sorted(by):
        L = by[v]
        if ismarked(v) or not (rd[0] <= v < rd[1]):
            continue
        fpu = [o for m, o in L if (m.startswith("f") or m.endswith("ss") or m.endswith("sd") or m.startswith("cvt")
                                   or m.startswith("comis") or m.startswith("ucomis")) and "ptr [0x" in o]
        if fpu and len(fpu) == len(L):
            mark(v, max(W.get(o.split()[0], 4) for o in fpu), "float")

    def strlen_at(v):
        b = img[v - B:v - B + 4096]
        k = 0
        while k < len(b) and (0x20 <= b[k] < 0x7F or b[k] in (9, 10, 13) or b[k] >= 0x80):
            k += 1
        return k if k < len(b) and b[k] == 0 else -1

    def wstrlen_at(v):
        k = 0
        while v - B + 2 * k + 1 < len(img):
            c = struct.unpack_from("<H", img, v - B + 2 * k)[0]
            if c == 0:
                return k
            if not (0x20 <= c < 0x7F or c in (9, 10, 13) or 0xA0 <= c < 0x3000):
                return -1
            k += 1
        return -1

    for v in starts:
        if not indata(v) or ismarked(v):
            continue
        wn, sn = wstrlen_at(v), strlen_at(v)
        if wn >= 2 and sn <= 1:
            mark(v, (2 * wn + 2 + 3) & ~3, "wstring")
        elif sn >= 1 and (sn >= 3 or v in by):
            e = v + sn + 1
            while e % 4 and e < nxt(v) and img[e - B] == 0:
                e += 1
            mark(v, e - v, "string")
    for v in starts:
        if indata(v) and not ismarked(v) and im.istext(d(v)) and im.istext(d(v + 4)):
            e = v
            while im.istext(d(e)) and (e == v or e not in by):
                e += 4
            mark(v, e - v, "fnptr_table")
    for v in sorted(by):
        if ismarked(v) or not (rd[0] <= v < rd[1]):
            continue
        if nxt(v) - v in (4, 8) and all("ptr [0x" in o for m, o in by[v]):
            mark(v, nxt(v) - v, "scalar_const")
    for v in starts:
        if not indata(v) or ismarked(v):
            continue
        hi = next(h for lo, h in regions if lo <= v < h)
        e = min(nxt(v), hi)
        i0 = idx(v)
        k = 0
        while v + k < e and cls[i0 + k] == 0:
            k += 1
        seg = bytes(img[v - B:v - B + k])
        ptrs = sum(1 for x in range(0, len(seg) - 3, 4)
                   if indata(struct.unpack_from("<I", seg, x)[0]) or im.istext(struct.unpack_from("<I", seg, x)[0]))
        c = "global_zero" if not any(seg) else ("global_ptrtab" if ptrs and ptrs * 8 >= len(seg) else "global")
        mark(v, k, c)
    for (lo, hi), o in zip(regions, offs):
        for v in range(lo, hi):
            i = o + v - lo
            if cls[i] == 0:
                cls[i] = CI["pad"] if img[v - B] == 0 else CI["unknown"]
    # items: a new item at every class change and at every referenced start
    startset = set(starts)
    rows = []
    for (lo, hi), o in zip(regions, offs):
        cur = None
        for v in range(lo, hi):
            c = cls[o + v - lo]
            if cur is None or c != cur[1] or (v in startset and NAMES[c] not in ("pad",)):
                if cur:
                    rows.append((cur[0], v - cur[0], cur[1]))
                cur = [v, c]
        if cur:
            rows.append((cur[0], hi - cur[0], cur[1]))
    bss_starts = [v for v in starts if bss[0] <= v < bss[1]]
    for i, v in enumerate(bss_starts):
        e = bss_starts[i + 1] if i + 1 < len(bss_starts) else bss[1]
        rows.append((v, e - v, CI["bss"]))
    out = io.StringIO()
    w = csv.writer(out, lineterminator="\n")
    w.writerow(["rva", "size", "section", "class", "detail", "confidence"])
    for v, size, c in sorted(rows):
        name = NAMES[c]
        conf = "high" if name in HIGH else ("medium" if name in MEDIUM else "low")
        w.writerow(["0x%08X" % (v - B), size, im.sec_of(v) or "?", OUT_CLASS.get(name, name), name, conf])
    return out.getvalue()


# ---------------------------------------------------------------- fold_list

def _relocish(buf, k):
    for s in range(max(0, k - 3), k + 1):
        if s + 4 > len(buf):
            continue
        v = int.from_bytes(buf[s:s + 4], "little")
        if 0x400000 <= v < 0x1000000:
            return True
        if s >= 1 and buf[s - 1] in (0xE8, 0xE9):
            return True
        if s >= 2 and buf[s - 2] == 0x0F and 0x80 <= buf[s - 1] <= 0x8F:
            return True
    return False


def eh_funclets(im):
    """VAs of every unwind action and catch handler named by a FuncInfo in the image."""
    B, img, d = im.base, im.img, im.d
    S = im.sec
    rd = (B + S[".rdata"][0], B + S[".rdata"][0] + S[".rdata"][1])
    MAG = (0x19930520, 0x19930521, 0x19930522)
    tv, tvs, _ = S[".text"]
    fis = set()
    for m in re.finditer(bytes([0xB8]) + b"(....)" + bytes([0xE9]), bytes(img[tv:tv + tvs]), re.S):
        v = struct.unpack("<I", m.group(1))[0]
        if rd[0] <= v < rd[1] and d(v) in MAG:
            fis.add(v)
    out = set()
    for v in sorted(fis):
        _, ms, pu, nt, pt = struct.unpack_from("<5I", img, v - B)
        for k in range(ms if ms < 5000 and im.sec_of(pu) else 0):
            out.add(d(pu + 8 * k + 4))
        for k in range(nt if nt < 500 and im.sec_of(pt) else 0):
            nc, ph = d(pt + 20 * k + 12), d(pt + 20 * k + 16)
            for j in range(nc if nc < 100 and im.sec_of(ph) else 0):
                out.add(d(ph + 16 * j + 12))
    return {x for x in out if im.istext(x)}


def fold_list(im):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    B, img = im.base, im.img
    branch = re.compile(r"^(call|jmp|j[a-z]+|loop\w*)$")

    def follow(t):
        for _ in range(4):
            o = t - B
            if im.istext(t) and img[o] == 0xE9:
                t = (t + 5 + struct.unpack_from("<i", img, o + 1)[0]) & 0xFFFFFFFF
            else:
                break
        return t

    funclets = eh_funclets(im)
    resolved, masked = collections.defaultdict(list), collections.defaultdict(list)
    for rva, size, name in ghidra_functions():
        if size <= 0 or not im.istext(B + rva) or B + rva in funclets:
            continue
        va = B + rva
        body = bytes(img[rva:rva + size])
        parts, pos, last = [], 0, None
        for a, sz, mn, op in md.disasm_lite(body, va):
            pos, last = a - va + sz, (mn, op)
            if branch.match(mn) and op.startswith("0x"):
                tgt = int(op, 16)
                where = ("in:%x" % (tgt - va)) if va <= tgt < va + size else ("ex:%x" % (follow(tgt) - B))
                parts.append(mn.encode() + b" " + where.encode())
            else:
                parts.append(body[a - va:a - va + sz])
        parts.append(body[pos:])
        if last and last[0] == "jmp" and len(parts) <= 4 and size <= 16:
            continue    # a jmp thunk or an EH funclet/handler stub: owned by its parent, never a COMDAT
        rkey = hashlib.sha1(b"\0".join(parts)).hexdigest()
        mkey = hashlib.sha1(bytes(0 if _relocish(body, k) else body[k] for k in range(len(body)))).hexdigest()
        resolved[(size, rkey)].append(rva)
        masked[(size, mkey)].append(rva)
    msize = {}
    for members in masked.values():
        for rva in members:
            msize[rva] = len(members)
    out = io.StringIO()
    w = csv.writer(out, lineterminator="\n")
    w.writerow(["rva", "size", "group_rva", "members", "masked_members", "body_sha1"])
    rows = []
    for (size, rkey), members in resolved.items():
        if len(members) < 2:
            continue
        members = sorted(set(members))
        for rva in members:
            rows.append(("0x%08X" % rva, size, "0x%08X" % members[0], len(members), msize[rva], rkey[:16]))
    for r in sorted(rows):
        w.writerow(r)
    return out.getvalue()


# ---------------------------------------------------------------- flag_regions

R32 = {"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp"}
SSE = re.compile(r"^(movss|addss|subss|mulss|divss|sqrtss|comiss|ucomiss|cvttss2si|cvtss2si|cvtsi2ss|minss|maxss|"
                 r"rcpss|rsqrtss|movaps|movups|mulps|addps|subps|shufps|xorps|andps)$")
X87F = re.compile(r"^(fadd|fsub|fsubr|fmul|fdiv|fdivr|fcom|fcomp)$")
ALIGNNOP = {"ebx, [ebx]", "esp, [esp]", "ecx, [ecx]", "edx, [edx]", "eax, [eax]", "esi, [esi]", "edi, [edi]",
            "esp, [esp + 0]"}


def _features(ins, ehp):
    c = collections.Counter()
    for k, (a, m, o) in enumerate(ins):
        if m in ("inc", "dec") and o in R32: c["incdec"] += 1
        elif m in ("add", "sub") and o.split(", ")[0] in R32 and o.endswith(", 1"): c["add1"] += 1
        elif m == "push" and o.startswith(("0x", "-")) and k + 1 < len(ins) and ins[k + 1][1] == "pop" and ins[k + 1][2] in R32: c["pushpop"] += 1
        elif m == "xor" and o == "eax, eax" and k + 1 < len(ins) and ins[k + 1][1] == "inc" and ins[k + 1][2] == "eax": c["xorinc"] += 1
        elif m == "and" and o.startswith("dword ptr") and o.endswith(", 0"): c["andm0"] += 1
        elif m == "or" and o.startswith("dword ptr") and o.endswith(", 0xffffffff"): c["orm1"] += 1
        elif m == "mov" and o.startswith("dword ptr [") and o.endswith("], 0"): c["movm0"] += 1
        elif m == "leave": c["leave"] += 1
        elif m == "lea" and o in ALIGNNOP: c["alignnop"] += 1
        elif m == "imul" and o in R32 and k > 0 and ins[k - 1][1] == "mov" and re.match(r"e[a-d]x, 0x[0-9a-f]{6,}", ins[k - 1][2]): c["magic"] += 1
        elif m == "idiv" and k > 1 and ins[k - 1][1] in ("pop", "cdq"): c["idiv"] += 1
        elif m == "imul" and o.count(",") == 2 and re.search(r", (3|5|9|0xa|0xc|0x14|0x18|0x24)$", o): c["imulsm"] += 1
        elif SSE.match(m): c["sse"] += 1
        elif X87F.match(m) and "dword ptr" in o: c["x87f"] += 1
        elif m == "call" and o.startswith("0x") and int(o, 16) in ehp and k < 3: c["ehprolog"] += 1
        elif m == "mov" and o == "eax, dword ptr fs:[0]" and k < 8: c["fs0"] += 1
    return c


def _opt(c):
    o1 = c["ehprolog"] * 3 + c["pushpop"] + c["xorinc"] + c["andm0"] + c["orm1"] + c["leave"] + c["idiv"]
    o2 = c["fs0"] * 3 + c["movm0"] + c["alignnop"] + c["magic"] * 2
    if o1 >= 2 * o2 + 1 and o1 >= 1:
        return "O1"
    if o2 >= 2 * o1 + 1 and o2 >= 1:
        return "O2"
    return None


def _tune(c, opt):
    if opt == "O2":
        if c["add1"] >= 1 and c["incdec"] == 0:
            return "G7"
        if c["incdec"] >= 1 and c["add1"] == 0:
            return "G6"
    if opt == "O1" and c["imulsm"] >= 1:
        return "G7"
    return None


def _arch(c):
    if c["sse"] >= 2 and c["sse"] >= 2 * c["x87f"]:
        return "SSE"
    if c["x87f"] >= 2 and c["sse"] == 0:
        return "x87"
    return None


def _mode(window):
    """Most common label; ties go to the label seen first (regions.py's Counter order)."""
    c = collections.Counter(window)
    best = max(c.values())
    return next(x for x in window if c[x] == best)


def _runs(addrs, labels, minrun=3, w=2):
    lab = [_mode(labels[max(0, i - w):i + w + 1]) for i in range(len(labels))]
    runs = []
    for a, l in zip(addrs, lab):
        if runs and runs[-1][2] == l:
            runs[-1][1] = a
            runs[-1][3] += 1
        else:
            runs.append([a, a, l, 1])
    changed = True
    while changed:
        changed = False
        for i in range(1, len(runs) - 1):
            if runs[i][3] < minrun and runs[i - 1][2] == runs[i + 1][2]:
                runs[i - 1][1] = runs[i + 1][1]
                runs[i - 1][3] += runs[i][3] + runs[i + 1][3]
                del runs[i:i + 2]
                changed = True
                break
    return runs


def flag_regions(im):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    B, img = im.base, im.img
    fns = [(B + rva, B + rva + size - 1) for rva, size, name in ghidra_functions()
           if size > 0 and not name.startswith("thunk_") and im.istext(B + rva)]
    raw, ehc = {}, collections.Counter()
    for e, mx in fns:
        ins = [(a, m, o) for a, _, m, o in md.disasm_lite(bytes(img[e - B:mx + 1 - B]), e)]
        raw[e] = (ins, mx + 1 - e)
        if len(ins) >= 2 and ins[0][1] == "mov" and ins[0][2].startswith("eax, 0x") and ins[1][1] == "call" and ins[1][2].startswith("0x"):
            ehc[int(ins[1][2], 16)] += 1
    ehp = {a for a, n in ehc.items() if n > 200}
    lab, size = {}, {}
    for e in sorted(raw):
        ins, nbytes = raw[e]
        c = _features(ins, ehp)
        o = _opt(c)
        lab[e] = (o, _tune(c, o), _arch(c))
        size[e] = nbytes
    tv, tvs, _ = im.sec[".text"]
    text = bytes(img[tv:tv + tvs])
    funclets = []
    for kind, pat in (("G7", rb"\xa1....\x24\xfe\xa3....\xc3"), ("G6", rb"\xa1....\x83\xe0\xfe\xa3....\xc3")):
        funclets += [(B + tv + m.start(), kind) for m in re.finditer(pat, text, re.S)]
    funclets.sort()
    fla = [x for x, _ in funclets]
    E = sorted(lab)
    pts = [(e, lab[e][0]) for e in E if lab[e][0]]
    runs = _runs([p[0] for p in pts], [p[1] for p in pts])
    regs = []
    for i, r in enumerate(runs):
        s = r[0] if i == 0 else regs[-1]["end"] + 1
        end = (runs[i + 1][0] - 1) if i + 1 < len(runs) else E[-1] + size[E[-1]]
        regs.append({"start": s, "end": end, "opt": r[2]})
    for g in regs:
        i0, i1 = bisect.bisect_left(E, g["start"]), bisect.bisect_right(E, g["end"])
        c = collections.Counter()
        for e in E[i0:i1]:
            o, t, a = lab[e]
            c["n"] += 1
            if o:
                c["ov"] += 1
            if a:
                c[a] += 1
            if t and (o == "O2" or t == "G7"):
                c[t] += 1
        j0, j1 = bisect.bisect_left(fla, g["start"]), bisect.bisect_right(fla, g["end"])
        for _, v in funclets[j0:j1]:
            c[v] += 1
            c["fun_" + v] += 1
        g["arch"] = "SSE" if c["SSE"] > c["x87"] else ("x87" if c["x87"] else "?")
        g["tune"] = "G7" if c["G7"] > c["G6"] else ("G6" if c["G6"] else "?")
        g["c"] = c
    merged = []
    for g in regs:
        k = (g["opt"], g["arch"], g["tune"])
        if merged and merged[-1]["k"] == k:
            merged[-1]["end"] = g["end"]
            merged[-1]["c"] += g["c"]
        else:
            merged.append({"k": k, "start": g["start"], "end": g["end"], "c": collections.Counter(g["c"])})
    out = io.StringIO()
    w = csv.writer(out, lineterminator="\n")
    w.writerow(["rva_start", "rva_end", "opt", "arch", "tune", "n_funcs", "n_opt_evidence", "conf_opt",
                "n_arch_evidence", "conf_arch", "n_tune_evidence", "conf_tune", "funclet_al", "funclet_eax"])

    def pur(a, b):
        return "%.2f" % (max(a, b) / (a + b)) if a + b else "0"

    for m in merged:
        c, k = m["c"], m["k"]
        i0, i1 = bisect.bisect_left(E, m["start"]), bisect.bisect_right(E, m["end"])
        agree = sum(1 for e in E[i0:i1] if lab[e][0] == k[0])
        ov = c["ov"]
        w.writerow(["0x%08X" % (m["start"] - B), "0x%08X" % (m["end"] - B), k[0], k[1], k[2], c["n"], ov,
                    "%.2f" % (agree / ov) if ov else "0", c["SSE"] + c["x87"], pur(c["SSE"], c["x87"]),
                    c["G7"] + c["G6"], pur(c["G7"], c["G6"]), c["fun_G7"], c["fun_G6"]])
    return out.getvalue()


# ---------------------------------------------------------------- driver

GENERATORS = {"data": data_items, "folds": fold_list, "flags": flag_regions}


def generate(kinds=KINDS, im=None):
    im = im or Image()
    return {FILES[k]: GENERATORS[k](im) for k in kinds}


def verify_staged(paths):
    """Errors for staged inventory files whose content is not what the tool regenerates."""
    want = {v: k for k, v in FILES.items()}
    kinds, errors = [], []
    for p in paths:
        name = p[len(INVENTORY_DIR):]
        if name not in want or want[name] not in KINDS:
            errors.append("%s is not a file this tool writes; the inventory directory is tool-owned" % p)
        else:
            kinds.append(want[name])
    if not kinds:
        return errors
    fresh = generate(sorted(set(kinds)))
    for p in paths:
        name = p[len(INVENTORY_DIR):]
        if name not in fresh:
            continue
        got = subprocess.run(["git", "show", ":" + p], cwd=ROOT, capture_output=True)
        staged = got.stdout.decode("utf-8", "replace").replace("\r\n", "\n") if got.returncode == 0 else None
        if staged is not None and staged != fresh[name]:
            errors.append("%s differs from `python3 tools/retail_inventory.py` output; it is tool-owned, "
                          "regenerate it instead of editing it" % p)
    return errors


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("kinds", nargs="*", metavar="|".join(KINDS))
    ap.add_argument("--check", action="store_true", help="regenerate in memory and compare")
    args = ap.parse_args(argv)
    kinds = tuple(args.kinds) or KINDS
    if set(kinds) - set(KINDS):
        ap.error("unknown inventory; choose from %s" % ", ".join(KINDS))
    out = generate(kinds)
    drift = 0
    for name, text in out.items():
        path = ROOT / INVENTORY_DIR / name
        if args.check:
            have = path.read_text(encoding="utf-8").replace("\r\n", "\n") if path.exists() else None
            if have != text:
                print("retail_inventory: %s%s is stale or edited" % (INVENTORY_DIR, name), file=sys.stderr)
                drift = 1
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8", newline="\n")
            print("%s%s: %d rows" % (INVENTORY_DIR, name, text.count("\n") - 1))
    return drift


if __name__ == "__main__":
    sys.exit(main())
