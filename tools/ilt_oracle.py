#!/usr/bin/env python3
"""Check a thunked function's decorated name against retail's incremental-link thunk table (ILT).

Retail was linked /INCREMENTAL by link.exe 7.10.3077. Every external function defined in a
command-line object got a 5-byte `jmp` thunk at 0x401005+5*slot, and the thunks come out in the
order of the linker's external-symbol hash table: buckets 0..B-1, each chain head to tail. So a
thunk's slot fixes the bucket of its symbol's decorated name to a narrow window between the
buckets of its correctly named neighbours, and any name can be tested against the window
(_audit research 21/24). The rule, from link.exe's code at 0x445330/0x445390/0x445480:

    h = 0; for each signed char c: h = c*0x40001 + h + ((h>>1) ^ h)   (mod 2**32); h %= 0x1ECA9D3B
    bucket = h % maxp, or h % (2*maxp) when that is below the split pointer p (B = maxp + p)
    before every lookup: split bucket p when count*16 // buckets > 48 (at most one split)
    insert at the chain head; a split keeps relative order
    per object, in command-line order: COMDAT-defining externals in section-number order, then
    every other external (definitions and undefs interleaved) in symbol-table order

Retail has B in [38326, 38340] (maxp 32768). The windows come from anchors: slots whose single
real ledger name lies on the longest monotone bucket sequence. A slot's window is bounded by its
nearest anchors on either side, leaving the slot itself out, so an anchor is tested like any
other slot. `generate` freezes them in targets/game/reverse/ilt_windows.tsv; nothing else
writes that file, and the guard (tools/ilt_guard.py) only reads it.

A wrong name fits a window by chance with probability about window/B (2.5e-4 on average). The
measured rate on 39,000 alternative names was 6.2e-4 (research 31), so P_FALSE applies a 2.5x
safety factor. A name that fits is *consistent* with retail, not proven: the hash is cheap to
brute-force, so a free-text name that passes says little. Only a search whose total
expected-false count is small (tool repairs, class triples) counts as *verified*.

    python3 tools/ilt_oracle.py check NAME 0xRVA        CONFIRMED / CONTRADICTED / UNTESTABLE
    python3 tools/ilt_oracle.py audit [--out CSV]       every functions.csv / symbols.csv row
    python3 tools/ilt_oracle.py repair [--out CSV]      access/const and class-dictionary repairs
    python3 tools/ilt_oracle.py generate                rewrite the frozen window file (retail exe + ledger)
"""
import argparse
import bisect
import collections
import csv
import hashlib
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REVERSE = ROOT / "targets/game/reverse"
WINDOWS = REVERSE / "ilt_windows.tsv"
EXE = ROOT / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
ZH = ROOT / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
IMAGE_BASE = 0x400000
MOD = 0x1ECA9D3B
B_LO, B_HI, B_FIT = 38326, 38340, 38333        # research 24: table size range and fitting midpoint
SAFETY = 2.5                                     # measured 6.2e-4 false fits vs 2.5e-4 modelled (research 31)
CONFIRMED, CONTRADICTED, UNTESTABLE = "CONFIRMED", "CONTRADICTED", "UNTESTABLE"

PLACEHOLDER = re.compile(r"(Rva[0-9A-Fa-f]{6,8}|FUN_|sub_|Gen_|^\?[abdj]_[0-9A-Fa-f]+@@|dup_|^\?*tg_|^\$L|^\$S"
                         r"|^\?\?_?[0-9A-Z]?[a-z]?_[0-9a-f]{8}@@)", re.I)
HEXRUN = re.compile(r"[0-9A-Fa-f]{6,}")
INVENTED = re.compile(r"bfme", re.I)


# ---------------------------------------------------------------- the linker's hash table
def vhash(name):
    """link.exe 7.10.3077 external-symbol hash (0x445330) of a decorated name."""
    if isinstance(name, str):
        name = name.encode("latin1", "replace")
    h = 0
    for c in name:
        s = c - 256 if c & 0x80 else c                      # movsx: the chars are signed
        h = (s * 0x40001 + h + ((h >> 1) ^ h)) & 0xFFFFFFFF
    return h % MOD


def bucket(h, buckets):
    """Linear-hashing bucket of hash h in a table of `buckets` buckets (initial maxp 1024)."""
    maxp = 1024
    while buckets >= 2 * maxp:
        maxp *= 2
    b = h % maxp
    return h % (2 * maxp) if b < buckets - maxp else b


class Table:
    """Exact emulation of the linker's table, for synthetic links: lookup() each external in
    insertion order, then order() is the thunk order of the defined ones."""

    def __init__(self):
        self.maxp, self.p, self.n = 1024, 0, 0
        self.chains = [[] for _ in range(1024)]
        self.hashes = {}

    def _bucket(self, h):
        b = h % self.maxp
        return h % (2 * self.maxp) if b < self.p else b

    def lookup(self, name):
        if self.n * 16 // len(self.chains) > 48:
            self._split()
        if name in self.hashes:
            return
        h = self.hashes[name] = vhash(name)
        self.chains[self._bucket(h)].insert(0, name)
        self.n += 1

    def _split(self):
        old, new = self.p, self.p + self.maxp
        self.p += 1
        if self.p == self.maxp:
            self.maxp, self.p = self.maxp * 2, 0
        self.chains.append([])
        keep, move = [], []
        for x in self.chains[old]:
            (move if self._bucket(self.hashes[x]) == new else keep).append(x)
        self.chains[old], self.chains[new] = keep, move

    def order(self):
        return [x for chain in self.chains for x in chain]


def coff_externals(data):
    """[(name, kind, key)] of one COFF object's externals in the linker's insertion order:
    COMDAT-defining symbols by section number, then the rest in symbol-table order.
    kind: C (COMDAT definition), D (other definition), U (undefined), A (absolute)."""
    _, nsec, _, symptr, nsym, opt, _ = struct.unpack_from("<HHIIIHH", data, 0)
    flags = [struct.unpack_from("<I", data, 20 + opt + 40 * k + 36)[0] for k in range(nsec)]
    strtab = symptr + nsym * 18
    out, i = [], 0
    while i < nsym:
        o = symptr + i * 18
        raw = data[o:o + 8]
        if raw[:4] == b"\0\0\0\0":
            off = strtab + struct.unpack_from("<I", raw, 4)[0]
            name = data[off:data.index(b"\0", off)]
        else:
            name = raw.rstrip(b"\0")
        _, sec, _, sclass, naux = struct.unpack_from("<IhHBB", data, o + 8)
        if sclass in (2, 105):
            kind = "U" if sec == 0 else "A" if sec < 0 else "C" if flags[sec - 1] & 0x1000 else "D"
            out.append((name, kind, (0, sec, i) if kind == "C" else (1, 0, i)))
        i += 1 + naux
    return [(n, k) for n, k, _ in sorted(out, key=lambda x: x[2])]


def predict_thunks(objects, entry=None, linker_symbols=2):
    """Thunk order (decorated names) of an /INCREMENTAL link of these COFF objects (bytes), in
    command-line order, with no libraries. `entry` is looked up first, as the linker does; the
    linker adds `linker_symbols` externals of its own after the objects, then looks up once more
    (research 24: count = externals + 2, with a trailing split)."""
    t, defined = Table(), set()
    if entry:
        t.lookup(entry)
    for data in objects:
        for name, kind in coff_externals(data):
            t.lookup(name)
            if kind in "CD":
                defined.add(name)
    for k in range(linker_symbols):
        t.lookup(b"\0linker%d" % k)
    if t.n * 16 // len(t.chains) > 48:
        t._split()
    return [n for n in t.order() if n in defined]


# ---------------------------------------------------------------- retail ILT and the window file
def retail_ilt(exe=EXE):
    """(first thunk VA, [target RVA per slot]) of the retail image."""
    data = exe.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec, opt = struct.unpack_from("<H", data, pe + 6)[0], struct.unpack_from("<H", data, pe + 20)[0]
    sec = pe + 24 + opt
    va, raw = struct.unpack_from("<I", data, sec + 12)[0], struct.unpack_from("<I", data, sec + 20)[0]
    i = raw
    while data[i] == 0xCC:
        i += 1
    start, targets = IMAGE_BASE + va + (i - raw), []
    while data[i] == 0xE9:
        targets.append(va + (i - raw) + 5 + struct.unpack_from("<i", data, i + 1)[0])
        i += 5
    assert nsec and targets
    return start, targets


def tier(name):
    """placeholder (address-derived/generated), invented (Bfme*), or real."""
    if PLACEHOLDER.search(name) or any(sum(c.isdigit() for c in x) >= 3 for x in HEXRUN.findall(name)):
        return "placeholder"
    return "invented" if INVENTED.search(name) else "real"


def ledger_rows(root=ROOT):
    """(source, name, rva, row) for every functions.csv row and symbols.csv pin with an address."""
    rev = root / "targets/game/reverse"
    for src, path, col in (("functions", rev / "functions.csv", "target_rva"), ("pins", rev / "symbols.csv", "address")):
        with open(path, encoding="utf-8", errors="replace", newline="") as f:
            for r in csv.DictReader(f):
                try:
                    yield src, r["name"], int(r[col], 16), r
                except (TypeError, ValueError):
                    continue


def lis(seq):
    """Indices of one longest non-decreasing subsequence."""
    tails, tail_idx, prev = [], [], [-1] * len(seq)
    for i, x in enumerate(seq):
        j = bisect.bisect_right(tails, x)
        if j == len(tails):
            tails.append(x)
            tail_idx.append(i)
        else:
            tails[j], tail_idx[j] = x, i
        prev[i] = tail_idx[j - 1] if j else -1
    out, k = [], tail_idx[-1] if tail_idx else -1
    while k != -1:
        out.append(k)
        k = prev[k]
    return out[::-1]


def generate(exe=EXE, out=WINDOWS, root=ROOT):
    start, targets = retail_ilt(exe)
    names = collections.defaultdict(set)
    slot_rvas = set(targets)
    for _, name, rva, _ in ledger_rows(root):
        if rva in slot_rvas:
            names[rva].add(name)
    fit_i, fit_b = [], []
    for i, t in enumerate(targets):
        real = [n for n in names.get(t, ()) if tier(n) == "real"]
        if len(real) == 1 and not real[0].startswith(("??_G", "??_E")):
            fit_i.append(i)
            fit_b.append(bucket(vhash(real[0]), B_FIT))
    keep = lis(fit_b)
    anc_i, anc_b = [fit_i[k] for k in keep], [fit_b[k] for k in keep]
    anchors = set(anc_i)
    lines = []
    for i, t in enumerate(targets):
        k = bisect.bisect_left(anc_i, i)
        lo = anc_b[k - 1] if k else 0
        k2 = k + 1 if k < len(anc_i) and anc_i[k] == i else k
        hi = anc_b[k2] if k2 < len(anc_i) else B_HI - 1
        lines.append(f"{i}\t0x{t:08X}\t{lo}\t{hi}\t{int(i in anchors)}")
    digest = hashlib.sha256(exe.read_bytes()).hexdigest()
    head = [f"# Generated by: python3 tools/ilt_oracle.py generate. Do not edit; regenerate only with that command.",
            f"# exe_sha256={digest} first_thunk=0x{start:08X} slots={len(targets)} buckets={B_LO}-{B_HI} "
            f"fit_buckets={B_FIT} fit_slots={len(fit_i)} anchors={len(anc_i)}",
            "slot\ttarget_rva\tlo\thi\tanchor"]
    out.write_text("\n".join(head + lines) + "\n", encoding="utf-8", newline="\n")
    return len(targets), len(fit_i), len(anc_i)


class Oracle:
    def __init__(self, path=WINDOWS):
        self.slots = collections.defaultdict(list)       # target rva -> [slot]
        self.window, self.target, self.meta = [], [], {}
        with open(path, encoding="utf-8") as f:
            for line in f:
                if line.startswith("#"):
                    self.meta.update(kv.split("=", 1) for kv in line[1:].split() if "=" in kv)
                    continue
                parts = line.split("\t")
                if parts[0] == "slot":
                    continue
                t = int(parts[1], 16)
                self.slots[t].append(int(parts[0]))
                self.target.append(t)
                self.window.append((int(parts[2]), int(parts[3])))
        self.first_thunk = int(self.meta.get("first_thunk", "0x401005"), 16)
        self._bk = {}

    def buckets(self, name):
        r = self._bk.get(name)
        if r is None:
            h = vhash(name)
            r = self._bk[name] = (bucket(h, B_LO), bucket(h, B_HI))
        return r

    def fits_slot(self, name, slot):
        lo, hi = self.window[slot]
        return any(lo <= b <= hi for b in self.buckets(name))

    def fit_slots(self, name, rva):
        return [s for s in self.slots_of(rva) if self.fits_slot(name, s)]

    def p_slot(self, slot):
        lo, hi = self.window[slot]
        return min(1.0, SAFETY * (hi - lo + 1) / B_LO)

    def p_target(self, rva):
        """Chance that one wrong name fits some slot of this target."""
        return min(1.0, sum(self.p_slot(s) for s in self.slots_of(rva)))

    def slots_of(self, rva):
        """Slots a name at this RVA must fit: the thunks jumping to it, or the thunk itself when
        the RVA is a slot address inside the ILT (a pin naming the thunk)."""
        first = self.first_thunk - IMAGE_BASE
        k, r = divmod(rva - first, 5)
        if r == 0 and 0 <= k < len(self.target):
            return [k]
        return self.slots.get(rva, [])

    def check(self, name, rva):
        """(verdict, p_false, why). p_false: chance a wrong name would have got this verdict's fit."""
        if not self.slots_of(rva):
            return UNTESTABLE, None, "not a thunk target (lib region, static, label, data)"
        tries = [(name, "exact")]
        if name.startswith(("??_G", "??_E")):
            tries.append((("??_E" if name.startswith("??_G") else "??_G") + name[4:], "G/E alias twin"))
        if not name.startswith(("?", "_", "@", "$")):
            tries.append(("_" + name, "C prefix"))
        p = min(1.0, len(tries) * self.p_target(rva))
        for n, why in tries:
            if self.fit_slots(n, rva):
                return CONFIRMED, p, why
        return CONTRADICTED, p, "outside every window of the target's slots " + ",".join(
            f"{s}:{self.window[s][0]}-{self.window[s][1]}" for s in self.slots_of(rva))


_ORACLE = None


def oracle():
    global _ORACLE
    if _ORACLE is None:
        _ORACLE = Oracle()
    return _ORACLE


def check(decorated_name, rva):
    """Public API: (CONFIRMED | CONTRADICTED | UNTESTABLE, false-positive probability or None)."""
    v, p, _ = oracle().check(decorated_name, rva)
    return v, p


# ---------------------------------------------------------------- audit
def audit(o, root=ROOT):
    rows, counts = [], collections.Counter()
    for src, name, rva, r in ledger_rows(root):
        v, p, why = o.check(name, rva)
        t = tier(name)
        counts[(src, t, v)] += 1
        rows.append(dict(src=src, rva=f"0x{rva:08X}", name=name, tier=t, verdict=v, why=why,
                         p_false="" if p is None else f"{p:.2e}", status=r.get("status", ""),
                         source=r.get("source", "")))
    return rows, counts


# ---------------------------------------------------------------- repair
NONSTATIC_GROUPS = {"A": "AIQ", "I": "AIQ", "Q": "AIQ", "E": "EMU", "M": "EMU", "U": "EMU",
                    "C": "CKS", "K": "CKS", "S": "CKS"}
STRUCTOR_CODES = ["UAE", "MAE", "EAE", "QAE", "IAE", "AAE"]


def split_member(name):
    """(prefix, access code, cv, rest) of a simple `?name@Class@@<code>...` member symbol."""
    if not name.startswith("?"):
        return None
    i = name.find("@@")
    if i < 0 or "?$" in name[1:i] or "@?" in name[:i]:
        return None
    rest = name[i + 2:]
    if len(rest) < 3:
        return None
    k = rest[0]
    if k in "AEIMQU":
        return name[:i], k, rest[1], rest[2:]
    if k in "CKS":
        return name[:i], k, "", rest[1:]
    return None


def access_variants(name):
    """T1: the same member with another access level of its kind, and for instance members
    also the other const qualifier (QAE->QBE, MAE->UAE...)."""
    s = split_member(name)
    if not s:
        return []
    pre, k, cv, tail = s
    out = set()
    for k2 in NONSTATIC_GROUPS[k]:
        for cv2 in ("AB" if cv else ("",)):
            out.add(f"{pre}@@{k2}{cv2}{tail}")
    out.discard(name)
    return sorted(out)


def dtor_callee_slot(o, text, text_rva, rva):
    """Slot of the destructor a scalar deleting destructor calls first (push esi; mov esi,ecx; call)."""
    off = rva - text_rva
    if 0 <= off and text[off:off + 4] == b"\x56\x8b\xf1\xe8":
        callee = IMAGE_BASE + rva + 8 + struct.unpack_from("<i", text, off + 4)[0]
        k, r = divmod(callee - o.first_thunk, 5)
        if r == 0 and 0 <= k < len(o.target):
            return k
    return None


def text_section(exe=EXE):
    data = exe.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    sec = pe + 24 + struct.unpack_from("<H", data, pe + 20)[0]
    va, size, raw = struct.unpack_from("<III", data, sec + 12)
    return data[raw:raw + size], va


IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]{2,60}")


def class_dictionary(root=ROOT, extra=()):
    """Candidate class identifiers: ledger names, Zero Hour declarations, retail strings, extra files."""
    words = set()
    for _, name, _, _ in ledger_rows(root):
        words.update(re.findall(r"[?@]([A-Za-z_]\w{2,60})@@", name))
        words.update(re.findall(r"@([A-Za-z_]\w{2,60})@", name))
    zh = root / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
    if zh.is_dir():
        for p in zh.rglob("*.h"):
            words.update(re.findall(r"\b(?:class|struct)\s+([A-Za-z_]\w{2,60})", p.read_text("latin1")))
    exe = root / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
    if exe.exists():
        words.update(m.decode() for m in re.findall(rb"[A-Za-z_][A-Za-z0-9_]{2,60}", exe.read_bytes()))
    for path in extra:
        words.update(re.findall(r"[?@]([A-Za-z_]\w{2,60})@@", Path(path).read_text("utf-8", "replace")))
    return sorted(w for w in words if tier(f"?x@{w}@@QAEXXZ") == "real" and IDENT.fullmatch(w))


def repair(o, rows, root=ROOT, extra=(), exe=EXE):
    """Candidate renames for CONTRADICTED rows. Returns (repairs, stats).

    T1: access/const variant of a real member name, unique fit. Class triples: a body with a
    ??_G thunk (and ??_E when it has two) whose dtor callee is also thunked: ??_G<X>, ??_E<X>
    and ??1<X> must each fit their slot. Expected false = sum of tests x p_false over every
    searched row, so it bounds the false repairs among those applied."""
    by_rva = collections.defaultdict(list)
    for r in rows:
        if r["verdict"] != UNTESTABLE:
            by_rva[int(r["rva"], 16)].append(r)
    confirmed_real = {rva for rva, rs in by_rva.items()
                      if any(r["verdict"] == CONFIRMED and r["tier"] == "real" for r in rs)}
    out, stats = [], collections.Counter()
    efp = collections.Counter()
    for rva, rs in sorted(by_rva.items()):
        if rva in confirmed_real:
            continue
        for r in rs:
            if r["verdict"] != CONTRADICTED or r["tier"] != "real":
                continue
            cands = access_variants(r["name"])
            if not cands:
                continue
            p = o.p_target(rva)
            stats["T1 tests"] += len(cands)
            efp["T1"] += p * len(cands)
            hits = [c for c in cands if o.fit_slots(c, rva)]
            if len(hits) == 1:
                out.append(dict(src=r["src"], rva=r["rva"], old=r["name"], new=hits[0], method="T1-access",
                                expected_false=f"{p * len(cands):.2e}", evidence=f"slot {o.fit_slots(hits[0], rva)}"))
            elif hits:
                stats["T1 ambiguous"] += 1
    # class triples
    text, text_rva = text_section(exe)
    words = class_dictionary(root, extra)
    stats["dictionary"] = len(words)
    index = collections.defaultdict(list)
    for w in words:
        for c in STRUCTOR_CODES:
            for b in set(o.buckets(f"??_G{w}@@{c}PAXI@Z")):
                index[b].append((w, c))
    n_cand = len(words) * len(STRUCTOR_CODES)
    for rva, slots in sorted(o.slots.items()):
        if len(slots) != 2:      # one slot (??_G + dtor only) expects ~64 false classes: research 24
            continue
        ds = dtor_callee_slot(o, text, text_rva, rva)
        if ds is None:
            continue
        stats["class bodies"] += 1
        p = 2 * n_cand * min(1.0, len(STRUCTOR_CODES) * o.p_slot(ds))     # 2: either slot can be ??_G
        for s in slots:
            p *= o.p_slot(s)
        efp["class"] += p
        hits = set()
        for s in slots:
            lo, hi = o.window[s]
            for b in range(lo, hi + 1):
                for w, c in index.get(b, ()):
                    g, e = f"??_G{w}@@{c}PAXI@Z", f"??_E{w}@@{c}PAXI@Z"
                    if not o.fits_slot(g, s):
                        continue
                    if not o.fits_slot(e, [x for x in slots if x != s][0]):
                        continue
                    d = [f"??1{w}@@{c2}@XZ" for c2 in STRUCTOR_CODES if o.fits_slot(f"??1{w}@@{c2}@XZ", ds)]
                    if d:
                        hits.add((w, c, s, d[0]))
        if len({h[0] for h in hits}) != 1:
            stats["class ambiguous" if hits else "class no hit"] += 1
            continue
        w, c, gslot, dname = sorted(hits)[0]
        g = f"??_G{w}@@{c}PAXI@Z"
        e = f"??_E{w}@@{c}PAXI@Z"
        dtor = o.target[ds]
        for r in by_rva.get(rva, ()):
            if r["verdict"] == CONTRADICTED and (r["tier"] != "real" or r["name"].startswith(("??_G", "??_E"))):
                new = e if r["name"].startswith("??_E") else g
                out.append(dict(src=r["src"], rva=r["rva"], old=r["name"], new=new, method="class-GED",
                                expected_false=f"{p:.2e}", evidence=f"G/E slots {slots}, dtor slot {ds}"))
        for r in by_rva.get(dtor, ()):
            if dtor in confirmed_real and r["tier"] == "real":
                continue
            if r["verdict"] == CONTRADICTED and (r["tier"] != "real" or r["name"].startswith("??1")):
                out.append(dict(src=r["src"], rva=r["rva"], old=r["name"], new=dname, method="class-GED-dtor",
                                expected_false=f"{p:.2e}", evidence=f"dtor of 0x{rva:08X}"))
        # rows naming the thunks themselves (pins at slot addresses inside the ILT)
        first = o.first_thunk - IMAGE_BASE
        for s, new, method in [(s, g if s == gslot else e, "class-GED") for s in slots] + [(ds, dname, "class-GED-dtor")]:
            for r in by_rva.get(first + 5 * s, ()):
                if r["verdict"] == CONTRADICTED and (r["tier"] != "real" or r["name"][:4] in ("??_G", "??_E", "??1" + w[:1])):
                    out.append(dict(src=r["src"], rva=r["rva"], old=r["name"], new=new, method=method,
                                    expected_false=f"{p:.2e}", evidence=f"thunk slot {s} of 0x{rva:08X}"))
    seen, uniq = set(), []
    for x in out:
        k = (x["src"], x["rva"], x["old"])
        if k not in seen:
            seen.add(k)
            uniq.append(x)
    stats["expected false T1"] = round(efp["T1"], 2)
    stats["expected false class"] = round(efp["class"], 4)
    return uniq, stats


def write_csv(path, rows):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]) if rows else ["empty"])
        w.writeheader()
        w.writerows(rows)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("check")
    c.add_argument("name")
    c.add_argument("rva")
    a = sub.add_parser("audit")
    a.add_argument("--out", default=str(ROOT / "build/ilt/audit.csv"))
    r = sub.add_parser("repair")
    r.add_argument("--out", default=str(ROOT / "build/ilt/repairs.csv"))
    r.add_argument("--dict-extra", nargs="*", default=[], help="more ledgers whose class names join the dictionary")
    sub.add_parser("generate")
    args = ap.parse_args(argv)
    if args.cmd == "generate":
        n, f, k = generate()
        print(f"{WINDOWS.relative_to(ROOT)}: {n} slots, {f} single-real-name slots, {k} anchors")
        return 0
    o = oracle()
    if args.cmd == "check":
        rva = int(args.rva, 16)
        rva -= IMAGE_BASE if rva >= IMAGE_BASE + 0x1000 and rva - IMAGE_BASE in o.slots else 0
        v, p, why = o.check(args.name, rva)
        print(f"{v}  p_false={p if p is None else f'{p:.2e}'}  ({why})")
        return 0 if v != CONTRADICTED else 1
    rows, counts = audit(o)
    if args.cmd == "audit":
        write_csv(args.out, rows)
        for k in sorted(counts):
            print(*k, counts[k], sep="\t")
        print(f"wrote {args.out}")
        return 0
    reps, stats = repair(o, rows, extra=args.dict_extra)
    write_csv(args.out, reps)
    for k, v in sorted(stats.items()):
        print(f"{k}: {v}")
    print(f"{len(reps)} repairs: {dict(collections.Counter((x['method'], x['src']) for x in reps))}\nwrote {args.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
