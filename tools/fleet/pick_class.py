#!/usr/bin/env python3
"""Claim the next WARM CLASS for a class-lane seat and print its brief context.

A warm class is a retail vtable whose slots are mostly landed real C++ with a
few dump slots left. The landed siblings prove the layout and pins; the vtable
slot index maps each dump body to a virtual in declaration order of the ZH twin
header, which is identity evidence no single-body brief has.

  python tools/fleet/pick_class.py            # best servable vtable, print RVAS line + NOTE
  python tools/fleet/pick_class.py --dry      # do not mark the pick in seats.log
  python tools/fleet/pick_class.py --vt 0x0113eb94 --dry
Output: first line "RVAS: 0x.. 0x..", then "NOTE: <one paragraph>".

A slot is served under the same rules as every other lane
(eligibility.servable: leases, the 48 h touched cooldown, the attempt cap,
dead ends, suspect boundaries, unlocked.txt). The old permanent claim file
build/fleet_class_claimed.txt is no longer read or written: a vtable served
once was excluded for ever, whether or not its session landed anything."""
import csv, re, sys, json, subprocess, collections, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
from class_context import find_header
import eligibility
ROOT = Path('.').resolve()
MAX_SLOTS = 8   # seat.sh briefs at most 8 bodies; do not lease what is not briefed
dry = '--dry' in sys.argv
want_vt = None
if '--vt' in sys.argv:
    want_vt = int(sys.argv[sys.argv.index('--vt') + 1], 16)
rank = json.load(open(ROOT / 'build/vtable_class_rank.json'))
# Reuse known context before opening a larger anonymous vtable. This is a
# scheduling hypothesis, not identity evidence; live rows still filter below.
rank.sort(key=lambda e: (bool(e.get('names')), e['landed'] / max(e['slots'], 1), e['dump_b']), reverse=True)
lf = (ROOT / 'build/.fleet_claims.lock').open('a'); lock(lf, exclusive=True)
ok = eligibility.servable(ROOT)
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
    live = [a for a in e['dump_rvas'] if a in fn and eligibility.is_dump_row(fn[a]) and ok(a)][:MAX_SLOTS]
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
zh, virt = find_header(ROOT, name)
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
    # the same in-flight mark the other pickers leave: busy_rvas reads it until
    # the seat logs "done", which covers the gap before fleet_run takes the lease
    with open(ROOT / 'build' / 'fleet_logs' / 'seats.log', 'a') as h:
        h.write(f"{time.strftime('%H:%M')} seat pick -> {' '.join(f'0x{a:08x}' for a in live)}\n")
print('RVAS: ' + ' '.join(f'0x{a:08X}' for a in live))
print('NOTE: ' + note)
