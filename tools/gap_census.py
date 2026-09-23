"""Census of unclaimed .text (python tools/gap_census.py): every function start we can prove inside the gaps, its
estimated extent, and identity leads (FunctionLexicon name tables, vtable pointers).
Writes build/gap_census.csv and build/lexicon_leads.csv; prints the summary."""
import bisect, csv, re, struct, sys
from collections import Counter
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build

img = open(build.EXE, "rb").read()
secs = {s["name"]: s for s in build.pe_sections(img)}
TEXT = secs[".text"]; RDATA = secs[".rdata"]; DATA = secs[".data"]
T0, T1 = TEXT["rva"], TEXT["rva"] + TEXT["size"]
def off(rva):  # .text/.rdata/.data are file-offset == rva here
    return rva
def in_text(rva): return T0 <= rva < T1
def in_rdata(rva): return RDATA["rva"] <= rva < RDATA["rva"] + RDATA["size"]

# ledger
rows = []
with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace") as fh:
    for r in csv.DictReader(fh):
        if r["status"] != "matched" or not r["target_rva"].lower().startswith("0x"):
            continue
        s = int(r["target_rva"], 16); n = int(r["target_size"] or 0)
        rows.append((s, s + n, r["source"], r["name"]))
rows.sort()
starts = [r[0] for r in rows]
def row_at(rva):
    i = bisect.bisect_right(starts, rva) - 1
    if i >= 0 and rows[i][0] <= rva < rows[i][1]:
        return rows[i]
    return None
def is_dump(row): return row and (row[2].startswith("Code/gen_asm/") or row[2].endswith(".asm"))
merged = []
for s, e, _, _ in rows:
    if merged and s <= merged[-1][1]: merged[-1][1] = max(merged[-1][1], e)
    else: merged.append([s, e])
gaps = []; prev = T0
for s, e in merged:
    if s > prev: gaps.append((prev, s))
    prev = max(prev, e)
if prev < T1: gaps.append((prev, T1))
gstarts = [g[0] for g in gaps]
def gap_of(rva):
    i = bisect.bisect_right(gstarts, rva) - 1
    if i >= 0 and gaps[i][0] <= rva < gaps[i][1]:
        return gaps[i]
    return None

# candidate starts inside gaps
cand = {}  # rva -> set(evidence)
def add(rva, ev):
    if gap_of(rva) is None: return
    cand.setdefault(rva, set()).add(ev)
with open(ROOT / "reverse/ghidra_functions.csv", newline="") as fh:
    gh = {int(r["rva"], 16): int(r["size"] or 0) for r in csv.DictReader(fh)}
for a in gh:
    add(a, "ghidra")
# REL32 call/jmp targets from anywhere in .text
text = img[T0:T1]
for m in re.finditer(rb"[\xE8\xE9]", text):
    p = m.start()
    if p + 5 > len(text): continue
    tgt = T0 + p + 5 + struct.unpack_from("<i", text, p + 1)[0]
    if in_text(tgt) and (img[tgt - 1] == 0xCC or tgt % 16 == 0):
        add(tgt, "call" if text[p] == 0xE8 else "jmp")
# data/rdata pointers into gaps (vtable slots, function tables, lexicon)
for sec, tag in ((RDATA, "rdata_ptr"), (DATA, "data_ptr")):
    base, size = sec["rva"], sec["size"]
    blob = img[base:base + size]
    for p in range(0, size - 3, 4):
        va = struct.unpack_from("<I", blob, p)[0]
        rva = va - 0x400000
        if in_text(rva) and (img[rva - 1] == 0xCC or rva % 16 == 0):
            add(rva, tag)
# aligned-stack / standard prologues right after an int3 run (Ghidra-blind code)
for g0, g1 in gaps:
    i = g0
    while i < g1 - 8:
        if img[i] == 0xCC:
            j = i
            while j < g1 and img[j] == 0xCC: j += 1
            if j < g1 - 8:
                b = img[j:j + 6]
                if b[:2] == b"\x53\x8b" or b[:3] == b"\x55\x8b\xec" or b[:3] == b"\x6a\xff\x68" or b[:2] == b"\x83\xec" or b[:2] == b"\x81\xec" or b[0] in (0x56, 0x57) and b[1] == 0x8b:
                    add(j, "prologue_after_int3")
            i = j
        else:
            i += 1

# extents: to next candidate or gap end, trimmed of trailing 0xCC
cs = sorted(cand)
funcs = []
for k, a in enumerate(cs):
    g = gap_of(a)
    nxt = cs[k + 1] if k + 1 < len(cs) and cs[k + 1] < g[1] else g[1]
    e = nxt
    while e > a and img[e - 1] == 0xCC: e -= 1
    funcs.append((a, e - a, sorted(cand[a])))

# FunctionLexicon-style tables: (name ptr, func ptr) adjacent dwords in .data or .rdata
ident = re.compile(rb"[A-Za-z_][A-Za-z0-9_:]{2,80}\0")
leads = []
for sec in (DATA, RDATA):
    base, size = sec["rva"], sec["size"]
    blob = img[base:base + size]
    for p in range(0, size - 7, 4):
        nva, fva = struct.unpack_from("<II", blob, p)
        nrva, frva = nva - 0x400000, fva - 0x400000
        if not in_rdata(nrva) or not in_text(frva): continue
        m = ident.match(img, nrva)
        if not m or m.start() != nrva: continue
        name = m.group(0)[:-1].decode()
        row = row_at(frva)
        status = "gap" if row is None else ("dump" if is_dump(row) else "landed")
        leads.append((name, frva, status, row[3] if row else "", row[1] - row[0] if row else 0))
# a real lexicon entry: the target is a function start (aligned or after int3) and the name is not a type/string blob
leads = [l for l in leads if img[l[1] - 1] == 0xCC or l[1] % 16 == 0]
seen = set(); uniq = []
for l in leads:
    if (l[0], l[1]) in seen: continue
    seen.add((l[0], l[1])); uniq.append(l)
leads = uniq

with open(ROOT / "build/gap_census.csv", "w", newline="") as fh:
    w = csv.writer(fh); w.writerow(["rva", "size", "evidence", "ghidra_size"])
    for a, n, ev in funcs:
        w.writerow([f"0x{a:08X}", n, "|".join(ev), gh.get(a, "")])
with open(ROOT / "build/lexicon_leads.csv", "w", newline="") as fh:
    w = csv.writer(fh); w.writerow(["name", "rva", "status", "ledger_name", "ledger_size"])
    for l in sorted(leads, key=lambda x: (x[2], -x[4])):
        w.writerow([l[0], f"0x{l[1]:08X}", l[2], l[3], l[4]])

real_gap = sum(len(img[a:b]) - img[a:b].count(0xCC) for a, b in gaps)
print(f"gaps {len(gaps)}  real unclaimed bytes {real_gap:,}")
print(f"function starts proved inside gaps: {len(funcs)}  covering {sum(n for _, n, _ in funcs):,} bytes")
band = Counter(); cnt = Counter()
for a, n, ev in funcs:
    b = "<100" if n < 100 else "<300" if n < 300 else "<600" if n < 600 else "<1200" if n < 1200 else "<2500" if n < 2500 else "<5000" if n < 5000 else ">=5000"
    band[b] += n; cnt[b] += 1
for k in ["<100", "<300", "<600", "<1200", "<2500", "<5000", ">=5000"]:
    print(f"  {k:>6}: {cnt[k]:5} funcs {band[k]:9,} B")
ev = Counter(e for _, _, evs in funcs for e in evs)
print("evidence:", dict(ev))
st = Counter(l[2] for l in leads)
print(f"lexicon-style (name, function) pairs: {len(leads)}  by target status: {dict(st)}")
gapleads = [l for l in leads if l[2] == "gap"]
lead_bytes = 0
fmap = {a: n for a, n, _ in funcs}
for l in gapleads: lead_bytes += fmap.get(l[1], 0)
print(f"named unclaimed functions (identity from a name table): {len(gapleads)}  ~{lead_bytes:,} B")
for l in sorted(gapleads, key=lambda x: -fmap.get(x[1], 0))[:25]:
    print(f"  0x{l[1]:08X} {fmap.get(l[1], 0):6} B  {l[0]}")
dumpleads = [l for l in leads if l[2] == "dump"]
print(f"named DUMP bodies (identity for existing anonymous rows): {len(dumpleads)}  {sum(l[4] for l in dumpleads):,} B")
for l in sorted(dumpleads, key=lambda x: -x[4])[:15]:
    print(f"  0x{l[1]:08X} {l[4]:6} B  {l[0]}  (row {l[3]})")
