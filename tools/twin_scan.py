#!/usr/bin/env python3
"""Find dump bodies that are byte-twins of LANDED real-C++ bodies once relocations
are masked. A twin is an instantiation of the same source shape (different
constants/globals/callees): copy the landed TU, rename, land -- minutes each.
Masking: E8/E9 rel32, and any dword in the image VA range (DIR32 slots).
  python build/twin_scan.py [--min N]   -> build/twin_scan.txt / .json (run from the repo root)
"""
import csv, json, re, sys, collections
sys.path.insert(0, 'tools')
import build
min_b = int(sys.argv[sys.argv.index('--min')+1]) if '--min' in sys.argv else 40
data = build.EXE.read_bytes()
secs = build.pe_sections(data)
def body(rva, size):
    off = build.rva_to_file_offset(secs, rva)
    return data[off:off+size]
def mask(b):
    out = bytearray(b); i = 0; n = len(b)
    while i < n:
        if b[i] in (0xE8, 0xE9) and i + 5 <= n:
            out[i+1:i+5] = b'\0\0\0\0'; i += 5; continue
        if i + 4 <= n:
            v = int.from_bytes(b[i:i+4], 'little')
            if 0x00400000 <= v < 0x01500000:
                out[i:i+4] = b'\0\0\0\0'; i += 4; continue
        i += 1
    return bytes(out)
rows = list(csv.DictReader(open('reverse/functions.csv', newline='', encoding='utf-8', errors='replace')))
landed = collections.defaultdict(list); dumps = []
for r in rows:
    try: rva = int(r['target_rva'], 16); size = int(r['target_size'] or 0)
    except ValueError: continue
    if size < min_b: continue
    src = r['source']
    if src.endswith('.asm') and 'gen_asm' in src:
        dumps.append((rva, size, r['name'], src))
    elif r.get('status') == 'matched' and src.startswith('Code/') and not src.startswith(('Code/gen_', 'Code/masm_dumps')) and src.endswith(('.cpp', '.c')):
        landed[size].append((rva, r['name'], src))
hits = []
for rva, size, name, src in dumps:
    if size not in landed: continue
    m = mask(body(rva, size))
    for lrva, lname, lsrc in landed[size]:
        if mask(body(lrva, size)) == m:
            hits.append({'rva': f'0x{rva:08X}', 'size': size, 'dump': src, 'twin_rva': f'0x{lrva:08X}', 'twin': lname, 'twin_src': lsrc})
            break
hits.sort(key=lambda h: -h['size'])
json.dump(hits, open('build/twin_scan.json', 'w'), indent=0)
with open('build/twin_scan.txt', 'w') as f:
    for h in hits:
        f.write(f"{h['rva']} {h['size']:5d} {h['dump'].split('/')[-1]:18s} twin {h['twin_rva']} {h['twin'][:60]} @ {h['twin_src']}\n")
print(len(hits), 'twins,', sum(h['size'] for h in hits), 'bytes')
