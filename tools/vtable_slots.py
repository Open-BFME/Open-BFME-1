"""Name retail vtable slots from our own compiled objects (build/match/*.obj).

Run after a build. Writes build/vt/candidates.csv (cache: build/vt/vt_index.json,
delete it after a rebuild). Hand the `trusted` rows to a pin batch and run
tools/pin_consistency.py --check before committing.

retail: C7 xx imm32 vptr store -> vtable VA -> owning ledger row (named ctor/dtor)
ours:   that row's compiled object -> ??_7<class>...6B...@ symbol -> slot relocs
match slots; a retail slot whose (thunk-resolved) target is an unnamed dump gets
our mangled slot name as a candidate pin. Vtables are trusted only when slot
counts agree and every already-named retail slot agrees with ours.
"""
import re, csv, collections, sys, struct, bisect, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools')); import build as B

data = B.EXE.read_bytes(); secs = {s['name']: s for s in B.pe_sections(data)}
text, rdata = secs['.text'], secs['.rdata']
base = 0x400000
tlo, thi, toff = text['rva'], text['rva'] + text['size'], text['raw_pointer']
rlo, rhi, roff = rdata['rva'], rdata['rva'] + rdata['size'], rdata['raw_pointer']

rows = list(csv.DictReader(open(ROOT / 'reverse/functions.csv', encoding='utf-8', errors='replace')))
ranges = []; dumps = {}; byrva = collections.defaultdict(list)
for r in rows:
    try: rva = int(r['target_rva'], 16); sz = int(r['target_size'])
    except: continue
    if r['status'] != 'matched': continue
    ranges.append((rva, sz, r['name'], r['source'])); byrva[rva].append(r)
    if r['source'].startswith('Code/gen_asm/'): dumps[rva] = sz
ranges.sort(); starts = [x[0] for x in ranges]
def owner(rva):
    i = bisect.bisect_right(starts, rva) - 1
    if i >= 0 and ranges[i][0] <= rva < ranges[i][0] + ranges[i][1]: return ranges[i]
PH = re.compile(r'\?[dbja]_[0-9a-f]{8}@@|^\$L\d+|^\$CHOKE')
pins = collections.defaultdict(list)
for r in csv.DictReader(open(ROOT / 'reverse/symbols.csv', encoding='utf-8', errors='replace')):
    try: pins[int(r['address'], 16)].append(r['name'])
    except: pass
def real_names(rva):
    ns = {n for n in pins.get(rva, []) if not PH.match(n)}
    ns |= {r['name'] for r in byrva.get(rva, []) if not PH.match(r['name'])}
    return ns

thunk = {}
i = data.find(b'\xe9', toff); end = toff + text['size']
while i != -1 and i < end - 4:
    rva = i - toff + tlo; tgt = rva + 5 + struct.unpack_from('<i', data, i + 1)[0]
    if tlo <= tgt < thi: thunk[rva] = tgt
    i = data.find(b'\xe9', i + 1)
def resolve(t):
    d = 0
    while t in thunk and d < 4: t = thunk[t]; d += 1
    return t

# vtable -> owner rows, in store order per owner
vt_owner = collections.defaultdict(list)
pat = re.compile(rb'\xc7(?:[\x00\x01\x02\x03\x06\x07]|[\x40\x41\x43\x45\x46\x47].|[\x80\x81\x83\x85\x86\x87]....)', re.S)
for m in pat.finditer(data, toff, end):
    imm = struct.unpack_from('<I', data, m.end())[0] - base
    if rlo <= imm < rhi:
        o = owner(m.start() - toff + tlo)
        if o and o not in vt_owner[imm]: vt_owner[imm].append(o)

def retail_slots(vt, limit):
    o = roff + (vt - rlo); out = []
    for k in range(limit + 1):
        if k and (vt + 4 * k) in vt_starts: return out, True
        v = struct.unpack_from('<I', data, o + k * 4)[0] - base
        if not (tlo <= v < thi): return out, True
        out.append(v)
    return out[:limit], False

def qual_of(sym):
    """qualified class name of a ??0/??1 symbol: everything after ??0 up to the
    `@@` that closes the name, honouring template args (?$...@...@@)."""
    s = sym[3:]; depth = 0; i = 0
    while i < len(s):
        if s.startswith('?$', i): depth += 1; i += 2; continue
        if s.startswith('@@', i):
            if depth == 0: return s[:i + 2]
            depth -= 1; i += 2; continue
        i += 1
    return None

IDX = ROOT / 'build/vt/vt_index.json'
if IDX.exists(): vindex = json.load(open(IDX))
else:
    vindex = {}
    for p in sorted((ROOT / 'build/match').glob('*.obj')):
        try:
            st = p.stat(); d, sections, symbols = B._object_layout(str(p), st.st_mtime_ns, st.st_size)
        except Exception: continue
        for s in symbols:
            if s['section'] > 0 and s['name'].startswith('??_7') and s['name'] not in vindex:
                try: body, relocs = B.read_object_symbol_bytes(p, s['name'])
                except Exception: continue
                vindex[s['name']] = [len(body) // 4, {str(off // 4): nm for off, rt, nm in relocs if off % 4 == 0}]
    json.dump(vindex, open(IDX, 'w'))
print('vtable index', len(vindex))
vt_starts = set(vt_owner)

SYN = re.compile(r'Gen_[0-9a-f]{8}|Gen_dtor|Rva[0-9A-Fa-f]{8}|Vt[0-9A-F]{7}|[Bb]fme|\?dup_|\?gen0|\?slot|Open2Elem|S4Guarded|\?rva0|Q4New|\?[a-z]_[0-9a-f]{8}@@')
def skeleton(n):
    n = n.replace('??_E', '??_G')
    # drop template arguments: ?$Name@...@ -> ?$Name@
    out = []; i = 0; depth = 0
    while i < len(n):
        if n.startswith('?$', i): depth += 1; j = n.index('@', i); out.append(n[i:j+1]); i = j + 1; continue
        if depth:
            if n.startswith('@@', i): depth -= 1; i += 2; continue
            i += 1; continue
        out.append(n[i]); i += 1
    return ''.join(out)
def agree_names(nm, rn):
    return nm in rn or skeleton(nm) in {skeleton(x) for x in rn}
def evaluate(vt, ours, nslots):
    """Align our slot names to retail's slots allowing insertions on either side
    (BFME adds virtuals ZH headers lack). Returns agree, dis, cand, bounded, dl."""
    rslots, bounded = retail_slots(vt, nslots + 8)
    if not rslots: return None
    ol = [ours.get(k) for k in range(nslots)]
    R = []
    for v in rslots:
        t = resolve(v); rn = {n for n in (real_names(t) | real_names(v)) if not SYN.search(n)}
        R.append((v, t, rn))
    n, m = len(ol), len(R)
    # DP: score +2 match, -1 gap; disagreements are just non-matches
    NEG = -10**9
    S = [[0]*(m+1) for _ in range(n+1)]; P = [[None]*(m+1) for _ in range(n+1)]
    for i in range(1, n+1): S[i][0] = -i; P[i][0] = 'u'
    for j in range(1, m+1): S[0][j] = -j; P[0][j] = 'l'
    for i in range(1, n+1):
        for j in range(1, m+1):
            mt = ol[i-1] is not None and R[j-1][2] and agree_names(ol[i-1], R[j-1][2])
            cand = [(S[i-1][j-1] + (3 if mt else (0 if not R[j-1][2] else -2)), 'd'), (S[i-1][j] - 1, 'u'), (S[i][j-1] - 1, 'l')]
            S[i][j], P[i][j] = max(cand)
    i, j = n, m; pairs = []
    while i or j:
        p = P[i][j]
        if p == 'd': pairs.append((i-1, j-1)); i -= 1; j -= 1
        elif p == 'u': i -= 1
        else: j -= 1
    pairs.reverse()
    agree = dis = 0; dl = []; anchors = []
    for i, j in pairs:
        nm = ol[i]; v, t, rn = R[j]
        if nm is None: continue
        if rn:
            if agree_names(nm, rn): agree += 1; anchors.append((i, j))
            else: dis += 1; dl.append((j, nm, sorted(rn)[:2]))
    cand = []
    for i, j in pairs:
        nm = ol[i]; v, t, rn = R[j]
        if nm is None or rn or t not in dumps or SYN.search(nm): continue
        # bracketed by anchors with the same offset on both sides (or at an end with one)
        before = [a for a in anchors if a[1] < j]; after = [a for a in anchors if a[1] > j]
        ob = (before[-1][1] - before[-1][0]) if before else None; oa = (after[0][1] - after[0][0]) if after else None
        off = j - i
        if (ob == off and oa == off) or (ob == off and not after) or (oa == off and not before) or (i == 0 and j == 0 and (oa == off)):
            cand.append((j, v, t, dumps[t], nm))
    if len(rslots) > nslots: bounded = False
    return agree, dis, cand, bounded, dl

out = []; stats = collections.Counter(); per_vt = {}; DIS = []
for vt, owners in vt_owner.items():
    named = [o for o in owners if not PH.match(o[2]) and re.match(r'\?\?[01]', o[2])]
    if not named: stats['vt_no_named_ctor'] += 1; continue
    best = None; tried = 0
    for o in named:
        q = qual_of(o[2])
        if not q: continue
        for vsym in [s for s in vindex if s.startswith('??_7' + q)]:
            nslots, ours = vindex[vsym]; ours = {int(k): v for k, v in ours.items()}
            r = evaluate(vt, ours, nslots); tried += 1
            if r is None: continue
            agree, dis, cand, bounded, dl = r
            key = (dis == 0, agree, -dis)
            if best is None or key > best[0]: best = (key, o, vsym, agree, dis, cand, bounded, dl)
    if best is None: stats['vt_no_candidate' if tried == 0 else 'slot_count_mismatch'] += 1; continue
    key, o, vsym, agree, dis, cand, bounded, dl = best
    trusted = dis == 0 and agree > 0
    weak = dis == 0 and agree == 0
    aligned = dis > 0 and agree >= 2 and dis <= 3
    per_vt[vt] = ('ok' if trusted else 'weak' if weak else 'untrusted', agree, dis, len(cand))
    DIS += [(vsym,) + d for d in dl]
    for k, v, t, sz, nm in cand:
        out.append({'vtable_va': f'{vt+base:#010x}', 'class_sym': vsym, 'slot': k, 'slot_ptr': f'{v:#010x}',
                    'target': f'{t:#010x}', 'size': sz, 'name': nm, 'trusted': int(trusted), 'weak': int(weak), 'aligned': int(aligned), 'bounded': int(bounded),
                    'agree': agree, 'disagree': dis, 'owner': o[2], 'source': o[3]})
    stats['vt_ok' if trusted else 'vt_weak' if weak else 'vt_aligned' if aligned else 'vt_untrusted'] += 1
with open(ROOT / 'build/vt/candidates.csv', 'w', newline='', encoding='utf-8') as f:
    w = csv.DictWriter(f, fieldnames=list(out[0].keys())); w.writeheader(); w.writerows(out)
print(dict(stats))
tr = [o for o in out if o['trusted']]; ut = [o for o in out if not o['trusted']]
uniq = lambda L: {o['target']: o['size'] for o in L}
print('trusted candidates: rows', len(tr), 'unique bodies', len(uniq(tr)), 'bytes', sum(uniq(tr).values()))
print('untrusted candidates: rows', len(ut), 'unique bodies', len(uniq(ut)), 'bytes', sum(uniq(ut).values()))

al = [o for o in out if o['aligned']]
print('aligned (>=2 anchors, <=3 dis) candidates: unique bodies', len(uniq(al)), 'bytes', sum(uniq(al).values()))
wk = [o for o in out if o['weak']]
print('weak (no named slot to validate) candidates: unique bodies', len(uniq(wk)), 'bytes', sum(uniq(wk).values()))
print('DIS sample'); [print(' ', d) for d in DIS[:15]]

# ---- header-probe pool: named real class, no vtable symbol held anywhere ----
import subprocess
hdr_classes = set()
for p in (ROOT / 'Code').rglob('*.h'):
    try: txt = p.read_text(encoding='utf-8', errors='replace')
    except Exception: continue
    for m in re.finditer(r'^\s*(?:class|struct)\s+([A-Za-z_]\w*)\s*(?::|\{)', txt, re.M): hdr_classes.add(m.group(1))
pool = collections.Counter(); poolb = collections.Counter(); seenT = set(); percls = collections.Counter()
for vt, owners in vt_owner.items():
    named = [o for o in owners if not PH.match(o[2]) and re.match(r'\?\?[01]', o[2]) and not SYN.search(o[2])]
    if not named: continue
    q = qual_of(named[0][2])
    if not q or any(s.startswith('??_7' + q) for s in vindex): continue
    cls = q.split('@')[0]
    has_hdr = cls in hdr_classes
    rs, bounded = retail_slots(vt, 400)
    for v in rs:
        t = resolve(v)
        if t in dumps and not real_names(t) and t not in seenT:
            seenT.add(t); key = 'header' if has_hdr else 'no-header'
            pool[key] += 1; poolb[key] += dumps[t]; percls[(cls, key)] += dumps[t]
print('header-probe pool (unnamed dump slots under real-named classes with no held vtable):')
for k in ('header', 'no-header'): print(f'  {k:10s} bodies={pool[k]} bytes={poolb[k]}')
print('  top classes:', percls.most_common(12))
