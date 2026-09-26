#!/usr/bin/env python3
"""Size-tolerant twins: dump bodies within +-TOL bytes of a landed real-C++ body
whose masked bytes align at >= RATIO similarity (difflib). Catches "same source,
one extra instruction / different immediate width" siblings the exact-size scans miss.
  python tools/fuzzy_twin_scan.py [--tol 24] [--ratio 0.94] [--min 80] [--exclude files...]
"""
import argparse
import sys, json, csv, collections, difflib
from functools import lru_cache
sys.path.insert(0,'tools'); import build, eligibility, progress

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--tol', type=int, default=24)
parser.add_argument('--ratio', type=float, default=0.94)
parser.add_argument('--min', dest='minb', type=int, default=80)
parser.add_argument('--exclude', nargs='*', default=[], metavar='FILE')
args = parser.parse_args()
if args.tol < 0 or args.minb < 1 or not 0 < args.ratio <= 1:
    parser.error('require --tol >= 0, --min >= 1, and 0 < --ratio <= 1')
tol, ratio, minb = args.tol, args.ratio, args.minb
excl = set(eligibility.busy_rvas())
for filename in args.exclude:
    with open(filename) as handle:
        excl.update(line.split()[0].lower() for line in handle if line.strip())
latest = eligibility.latest_verdicts()
data=build.EXE.read_bytes(); secs=build.pe_sections(data)
def body(rva,size):
    off=build.rva_to_file_offset(secs,rva); return data[off:off+size]
def mask(b):
    out=bytearray(b); i=0; n=len(b)
    while i<n:
        if b[i] in (0xE8,0xE9) and i+5<=n: out[i+1:i+5]=b'\0\0\0\0'; i+=5; continue
        if i+4<=n:
            v=int.from_bytes(b[i:i+4],'little')
            if 0x00400000<=v<0x01500000: out[i:i+4]=b'\0\0\0\0'; i+=4; continue
        i+=1
    return bytes(out)
@lru_cache(maxsize=None)
def masked_body(rva, size):
    return mask(body(rva, size))

landed=[]; dumps=[]; donor_rows={}
with open('targets/game/reverse/functions.csv', newline='', encoding='utf-8', errors='replace') as ledger:
    for r in csv.DictReader(ledger):
        try: rva=int(r['target_rva'],16); size=int(r['target_size'] or 0)
        except (ValueError, TypeError): continue
        src=r['source']
        is_donor = (r.get('status') == 'matched' and src.startswith('game/')
                    and not src.startswith(('game/gen_', 'game/masm_dumps'))
                    and src.endswith(('.cpp', '.c')))
        # Feed the shared classifier every row in a donor TU, including small
        # rows: its single-row fallback must not mistake a mixed TU for a lift.
        if is_donor:
            donor_rows[(r['name'], r['target_rva'])] = (size, src)
        if size<minb: continue
        if src.endswith('.asm') and 'gen_asm' in src:
            if (r['target_rva'].lower() not in excl
                    and eligibility.open_dumps(rows=[r], latest=latest)):
                dumps.append((rva,size,src))
        elif is_donor:
            landed.append((size,rva,r['name'],src))
naked = {(name, int(rva, 16))
         for name, rva in progress.naked_cpp_rows_at(donor_rows, None)}
donor_count = len(landed)
landed = [row for row in landed if (row[2], row[1]) not in naked]
print(donor_count - len(landed), "assembly-backed donor rows excluded")
landed.sort()
import bisect
sizes=[x[0] for x in landed]
hits=[]
for rva,size,src in dumps:
    m=masked_body(rva,size); head=m[:12]
    lo=bisect.bisect_left(sizes,size-tol); hi=bisect.bisect_right(sizes,size+tol)
    best=None
    for s,lrva,lname,lsrc in landed[lo:hi]:
        if s==size: continue
        lm=masked_body(lrva,s)
        if lm[:12]!=head: continue
        q=difflib.SequenceMatcher(None,m,lm,autojunk=False).quick_ratio()
        if q<ratio: continue
        rr=difflib.SequenceMatcher(None,m,lm,autojunk=False).ratio()
        if rr>=ratio and (best is None or rr>best[0]): best=(rr,lrva,lname,lsrc,s)
    if best:
        hits.append({'rva':f'0x{rva:08X}','size':size,'dump':src,'ratio':round(best[0],3),'twin_rva':f'0x{best[1]:08X}','twin':best[2],'twin_src':best[3],'twin_size':best[4]})
hits.sort(key=lambda h:(-h['ratio'],-h['size']))
json.dump(hits,open('build/fuzzy_twin_scan.json','w'),indent=0)
with open('build/fuzzy_twin_scan.txt','w') as f:
    for h in hits: f.write(f"{h['rva']} {h['size']:5d} r{h['ratio']:.3f} {h['dump'].split('/')[-1]:18s} twin {h['twin_rva']} ({h['twin_size']}B) {h['twin'][:50]} @ {h['twin_src']}\n")
print(len(hits),'fuzzy twins',sum(h['size'] for h in hits),'B')
