#!/usr/bin/env python3
"""Rank retail vtables by dump bytes still sitting in their slots ("warm classes").

Game classes carry no RTTI, so a vtable is found structurally: a run of .text
pointers in .rdata that starts at an address some .text instruction references
as an imm32 (a `mov [ecx], offset vftable` in a ctor). Splitting runs at every
code-referenced address separates adjacent vtables. Each vtable is scored by
the dump bytes in its slots; the ledger names of its landed slots name the class.

  python tools/fleet/vtable_rank.py        # writes build/rdata_refs.json and
                                            # build/vtable_class_rank.{json,txt}
pick_class.py consumes the json. Read-only against the ledgers."""
import sys, csv, struct, re, collections, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import build
exe = open(build.EXE, 'rb').read(); secs = build.pe_sections(exe); base = 0x400000
S = {s['name']: s for s in secs}
def within(sec, va): return S[sec]['rva'] <= va - base < S[sec]['rva'] + S[sec]['size']
t = S['.text']; rd = S['.rdata']; lo = base + rd['rva']; hi = lo + rd['size']
raw = exe[t['raw_pointer']:t['raw_pointer'] + t['size']]
u = struct.Struct('<I').unpack_from
refs = {u(raw, i)[0] for i in range(len(raw) - 4) if lo <= u(raw, i)[0] < hi}
json.dump(sorted(refs), open(ROOT / 'build/rdata_refs.json', 'w'))
fn = {}
for r in csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')):
    a = (r['target_rva'] or '').lower()
    if a.startswith('0x'): fn[int(a, 16)] = r
pins = collections.defaultdict(list)
for l in open(ROOT / 'reverse/symbols.csv', encoding='utf-8', errors='replace'):
    p = l.split(',')
    if len(p) > 1 and p[1].startswith('0x'):
        try: pins[int(p[1], 16)].append(p[0])
        except ValueError: pass
def klass(n):
    m = re.match(r'\?[^@]+@([A-Za-z_][A-Za-z0-9_]*)@@', n or '')
    return m.group(1) if m else None
rraw = exe[rd['raw_pointer']:rd['raw_pointer'] + rd['size']]
words = struct.unpack_from('<%dI' % (len(rraw) // 4), rraw)
vts = []; i = 0; n = len(words); va0 = lo
while i < n:
    if within('.text', words[i]) and (va0 + i * 4) in refs:
        j = i + 1
        while j < n and within('.text', words[j]) and (va0 + j * 4) not in refs: j += 1
        vts.append((va0 + i * 4, words[i:j])); i = j
    else: i += 1
out = []
SKIP = ('Gen', 'Rva', 'Bfme', 'Q', 'd_', 'dup', 'j_')
for vt, slots in vts:
    dn = db = ln = gn = 0; names = collections.Counter(); drv = []
    for s in slots:
        r = fn.get(s - base)
        if not r: continue
        src = r['source']
        if src.endswith('.asm'): dn += 1; db += int(r['target_size'] or 0); drv.append(s - base)
        elif src.startswith('Code/gen_'): gn += 1
        elif r['status'] == 'matched':
            ln += 1; k = klass(r['name'])
            if k and not k.startswith(SKIP): names[k] += 1
        for pn in pins.get(s - base, []):
            k = klass(pn)
            if k and not k.startswith(SKIP): names[k] += 1
    if db: out.append((db, dn, ln, gn, len(slots), vt, names.most_common(2), drv))
out.sort(reverse=True)
with open(ROOT / 'build/vtable_class_rank.txt', 'w') as h:
    h.write(f"vtables: {len(vts)} | with dump slots: {len(out)} | dump bytes in slots: {sum(o[0] for o in out)}\n")
    h.write(f"{'vtable':10}{'slots':>6}{'dumpN':>6}{'dumpB':>7}{'landed':>7}{'gen':>5}  class guesses\n")
    for db, dn, ln, gn, ns, vt, names, drv in out:
        h.write(f"0x{vt:08x}{ns:6}{dn:6}{db:7}{ln:7}{gn:5}  {names}\n")
json.dump([{'vt': vt, 'slots': ns, 'dump_n': dn, 'dump_b': db, 'landed': ln, 'names': names, 'dump_rvas': drv}
           for db, dn, ln, gn, ns, vt, names, drv in out], open(ROOT / 'build/vtable_class_rank.json', 'w'))
print(open(ROOT / 'build/vtable_class_rank.txt').read().split('\n')[0])
