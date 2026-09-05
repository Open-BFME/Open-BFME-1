#!/usr/bin/env python3
"""Size-tolerant twins: dump bodies within +-TOL bytes of a landed real-C++ body
whose masked bytes align at >= RATIO similarity (difflib). Catches "same source,
one extra instruction / different immediate width" siblings the exact-size scans miss.
  python build/fuzzy_twin_scan.py [--tol 24] [--ratio 0.94] [--min 80] [--exclude files...]
"""
import sys, json, csv, collections, difflib
sys.path.insert(0,'tools'); import build
def arg(k,d):
    return type(d)(sys.argv[sys.argv.index(k)+1]) if k in sys.argv else d
tol=arg('--tol',24); ratio=arg('--ratio',0.94); minb=arg('--min',80)
excl=set()
if '--exclude' in sys.argv:
    for f in sys.argv[sys.argv.index('--exclude')+1:]:
        if f.startswith('--'): break
        for l in open(f):
            if l.strip(): excl.add(l.split()[0].lower())
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
rows=list(csv.DictReader(open('reverse/functions.csv',newline='',encoding='utf-8',errors='replace')))
landed=[]; dumps=[]
for r in rows:
    try: rva=int(r['target_rva'],16); size=int(r['target_size'] or 0)
    except ValueError: continue
    if size<minb: continue
    src=r['source']
    if src.endswith('.asm') and 'gen_asm' in src:
        if r['target_rva'].lower() not in excl: dumps.append((rva,size,src))
    elif r.get('status')=='matched' and src.startswith('Code/') and not src.startswith(('Code/gen_','Code/masm_dumps')) and src.endswith(('.cpp','.c')):
        landed.append((size,rva,r['name'],src))
landed.sort()
import bisect
sizes=[x[0] for x in landed]
hits=[]
for rva,size,src in dumps:
    m=mask(body(rva,size)); head=m[:12]
    lo=bisect.bisect_left(sizes,size-tol); hi=bisect.bisect_right(sizes,size+tol)
    best=None
    for s,lrva,lname,lsrc in landed[lo:hi]:
        if s==size: continue
        lm=mask(body(lrva,s))
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
