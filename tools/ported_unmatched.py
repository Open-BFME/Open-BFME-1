import csv,re,os,collections
rows=list(csv.DictReader(open('reverse/functions.csv',newline='',encoding='utf-8',errors='replace')))
dump={}
for r in rows:
    if 'gen_asm' in r['source'] and r['source'].endswith('.asm'):
        try: dump[int(r['target_rva'],16)]=int(r['target_size'] or 0)
        except: pass
pins=collections.defaultdict(list)
for r in csv.reader(open('reverse/symbols.csv',newline='',encoding='utf-8',errors='replace')):
    if len(r)>1 and r[1].startswith('0x'):
        try: pins[int(r[1],16)].append(r[0])
        except: pass
MARK=re.compile(r"^\s*//\s*(\S+)\s+present-unmatched\b",re.M)
markers={}
for root,_,files in os.walk('Code'):
    if 'gen_asm' in root or 'gen_small' in root or 'masm_dumps' in root: continue
    for f in files:
        if f.endswith('.cpp'):
            p=os.path.join(root,f).replace(os.sep,'/')
            try: t=open(p,encoding='utf-8',errors='replace').read()
            except: continue
            for m in MARK.findall(t): markers.setdefault(m,[]).append(p)
prefix=[m for m in markers if m.endswith('@@')]
claimed={l.strip().lower() for l in open('build/fleet_mid_claimed.txt')}
lat={}
for l in open('reverse/re_attempts.log',encoding='utf-8',errors='replace'):
    p=l.rstrip('\n').split('\t')
    if len(p)>=5 and p[1].startswith('0x'): lat[p[1].lower()]=p[3]
hits=[]
for rva,size in dump.items():
    for n in pins.get(rva,[]):
        src=None
        if n in markers: src=markers[n][0]
        else:
            for m in prefix:
                if n.startswith(m): src=markers[m][0]; break
        if src:
            hits.append((size,rva,n,src)); break
hits.sort(reverse=True)
print(len(hits),'ported-but-unmatched dumps', sum(h[0] for h in hits),'B')
with open('build/ported_unmatched.txt','w') as f:
    for size,rva,n,src in hits:
        k=f'0x{rva:08x}'
        f.write(f"0x{rva:08X} {size:5d} {('claimed' if k in claimed else lat.get(k,'-')):8s} {n[:70]} @ {src}\n")
for h in hits[:12]: print(f"0x{h[1]:08X} {h[0]:5d} {h[2][:55]} @ {h[3]}")
