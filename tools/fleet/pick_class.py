#!/usr/bin/env python3
"""Claim the next WARM CLASS for a class-lane seat and print its brief context.

A warm class is a retail vtable whose slots are mostly landed real C++ with a
few dump slots left. The landed siblings prove the layout and pins; the vtable
slot index maps each dump body to a virtual in declaration order of the ZH twin
header, which is identity evidence no single-body brief has.

  python build/pick_class.py            # claim best unclaimed vtable, print RVAS line + NOTE
  python build/pick_class.py --dry      # no claim
  python build/pick_class.py --vt 0x0113eb94 --dry
Output: first line "RVAS: 0x.. 0x..", then "NOTE: <one paragraph>".
Claims in build/fleet_class_claimed.txt under the fleet claims lock."""
import csv, re, sys, json, subprocess, collections
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
ROOT = Path('.').resolve()
dry = '--dry' in sys.argv
want_vt = None
if '--vt' in sys.argv:
    want_vt = int(sys.argv[sys.argv.index('--vt') + 1], 16)
rank = json.load(open(ROOT / 'build/vtable_class_rank.json'))
claims = ROOT / 'build/fleet_class_claimed.txt'
lf = (ROOT / 'build/.fleet_claims.lock').open('a'); lock(lf, exclusive=True)
taken = {int(l.strip(), 16) for l in claims.read_text().splitlines() if l.strip()} if claims.exists() else set()
fn = {}
for r in csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')):
    a = (r['target_rva'] or '').lower()
    if a.startswith('0x'):
        fn[int(a, 16)] = r
import struct
import build
exe = open(build.EXE, 'rb').read(); secs = build.pe_sections(exe); base = 0x400000
def rd32(va): return struct.unpack_from('<I', exe, build.rva_to_file_offset(secs, va - base))[0]
def klass(n):
    m = re.match(r'\?[^@]+@([A-Za-z_][A-Za-z0-9_]*)@@', n or '')
    return m.group(1) if m else None
chosen = None
for e in rank:
    if want_vt and e['vt'] != want_vt: continue
    if e['vt'] in taken and not want_vt: continue
    live = [a for a in e['dump_rvas'] if fn.get(a, {}).get('source', '').endswith('.asm')]
    if not live: continue
    chosen = (e, live); break
if not chosen:
    sys.exit(0)
e, live = chosen
vt = e['vt']
refs = set(json.load(open(ROOT / 'build/rdata_refs.json')))
slots = []
j = vt
while True:
    f = rd32(j)
    if not (0x401000 <= f < 0x401000 + secs[0]['size']): break
    if j != vt and j in refs: break   # next code-referenced vtable starts here
    slots.append(f - base); j += 4
name = e['names'][0][0] if e['names'] else '?'
zh = subprocess.run(['rg', '-l', '-m1', f'class {name}\b', 'reference/CnC_Generals_Zero_Hour/Generals', '--iglob', '*.h'], capture_output=True, text=True).stdout.strip().split('\n')[0]
virt = []
if zh:
    txt = open(zh, encoding='utf-8', errors='replace').read()
    m = re.search(r'class\s+' + name + r'\b[^{]*\{(.*?)\n\};', txt, re.S)
    if m:
        for v in re.finditer(r'virtual\s+[^;{]*?\b(~?\w+)\s*\(', m.group(1)):
            virt.append(v.group(1))
lines = []
for i, s in enumerate(slots):
    r = fn.get(s)
    tag = 'DUMP' if s in live else ('landed ' + r['name'][:60] + ' @ ' + r['source'].split('/')[-1] if r and r['status'] == 'matched' else 'other')
    zv = virt[i] if i < len(virt) else '?'
    if tag == 'DUMP' or tag.startswith('landed'):
        lines.append(f"slot {i:3} 0x{s:08X} {r['target_size'] if r else '?':>5}B  {tag}  | ZH decl order #{i}: {zv}")
note = (f"WARM CLASS {name}: retail vtable at VA 0x{vt:08X} ({len(slots)} slots, {e['landed']} already landed as real C++, {len(live)} still dumps). "
        f"ZH twin header: {zh or 'not found'} ({len(virt)} virtuals parsed in declaration order; MSVC lays out single-inheritance vtables in declaration order after the base class's slots, so align the ZH list against the LANDED slots first to find the base-slot offset, then read the dump slots' names off it). "
        f"Open the landed sibling sources for this vtable and reuse their class definition, cl: flags and pins verbatim. Slot table:\n" + "\n".join(lines))
if not dry:
    with open(claims, 'a') as h: h.write(f'0x{vt:08x}\n')
print('RVAS: ' + ' '.join(f'0x{a:08X}' for a in live))
print('NOTE: ' + note)
