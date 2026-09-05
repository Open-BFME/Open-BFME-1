#!/usr/bin/env python3
"""Near-twins: dump bodies the same size as a LANDED real-C++ body, differing in
at most --max non-relocation bytes (default 30). Writes build/neartwin_scan.{txt,json}.
Skips RVAs listed in --exclude files (one rva per line, first token)."""
import sys, json, csv, collections
sys.path.insert(0, 'tools'); import build
maxd = int(sys.argv[sys.argv.index('--max')+1]) if '--max' in sys.argv else 30
excl = set()
if '--exclude' in sys.argv:
    for f in sys.argv[sys.argv.index('--exclude')+1:]:
        if f.startswith('--'): break
        for l in open(f): 
            if l.strip(): excl.add(l.split()[0].lower())
data = build.EXE.read_bytes(); secs = build.pe_sections(data)
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
landed=collections.defaultdict(list); dumps=[]
for r in rows:
    try: rva=int(r['target_rva'],16); size=int(r['target_size'] or 0)
    except ValueError: continue
    if size<60: continue
    src=r['source']
    if src.endswith('.asm') and 'gen_asm' in src:
        if r['target_rva'].lower() not in excl: dumps.append((rva,size,src))
    elif r.get('status')=='matched' and src.startswith('Code/') and not src.startswith(('Code/gen_','Code/masm_dumps')) and src.endswith(('.cpp','.c')):
        landed[size].append((rva,r['name'],src,mask(body(rva,size))))
hits=[]
for rva,size,src in dumps:
    if size not in landed: continue
    m=mask(body(rva,size)); best=None
    for lrva,lname,lsrc,lm in landed[size]:
        d=sum(1 for a,b in zip(m,lm) if a!=b)
        if best is None or d<best[0]: best=(d,lrva,lname,lsrc)
    if best and best[0]<=maxd:
        hits.append({'rva':f'0x{rva:08X}','size':size,'dump':src,'diff':best[0],'twin_rva':f'0x{best[1]:08X}','twin':best[2],'twin_src':best[3]})
hits.sort(key=lambda h:(h['diff'],-h['size']))
json.dump(hits,open('build/neartwin_scan.json','w'),indent=0)
with open('build/neartwin_scan.txt','w') as f:
    for h in hits: f.write(f"{h['rva']} {h['size']:5d} diff{h['diff']:2d} {h['dump'].split('/')[-1]:18s} twin {h['twin_rva']} {h['twin'][:55]} @ {h['twin_src']}\n")
print(len(hits),'near-twins', sum(h['size'] for h in hits),'bytes'); print(collections.Counter(h['diff'] for h in hits))
