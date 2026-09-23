"""Independent floating-point lane seeded from candidates with all SIB bytes exact.
Reuse the pinned preceding research harness, verifying its exact Git blob hash.
All outputs remain scratch; no remote production or ledger changes.
"""
from pathlib import Path
import hashlib,urllib.request
url='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
raw=urllib.request.urlopen(url,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
implementation=raw.decode('utf-8');prefix=implementation.split('seed_masks=',1)[0]
exec(compile(prefix,'pinned_research_harness','exec'))
(OUT/'shared_driver_source.json').write_text(json.dumps({'commit':'010683a09c21c158a15f250bc1cc86fc1a9667cb','source':implementation}),encoding='utf-8')
deadline=time.monotonic()+420
proof=json.loads((ROOT/'reverse/attempt_support/0x00960a30-verification.json').read_text())
address_offsets={int(x,16) for g in proof['remaining_groups'] if 'SIB' in g['name'] for x in g['wrong_offsets']}
assert len(address_offsets)==45
batch([('address_seed_'+str(i),source_for(mask),mask) for i,mask in enumerate([[19,29,40],[19,29,40,41]])])
assert best and best['cost']==20
for generation in range(3):
    if best.get('verified_exact') or time.monotonic()>deadline-60:break
    eligible=sorted((r for r in records if r.get('mask') is not None and 'cost' in r and r.get('relocation_drifts')==0 and not address_offsets.intersection(r['offsets']) and 'error' not in r),key=lambda r:(r['cost'],r['volatile_tokens']))
    beam=[];codes=set()
    for r in eligible:
        if r['code_sha256'] in codes:continue
        codes.add(r['code_sha256']);beam.append(r)
        if len(beam)==3:break
    jobs=[]
    for parent in beam:
        for atom in range(len(atoms)):
            mask=set(parent['mask'])^{atom};counter+=1
            jobs.append(('address_beam_'+str(generation)+'_'+str(counter),source_for(mask),mask))
    result=batch(jobs)
    if not result:break
# Preserve the two lane results even if the byte-distance best lost an address.
address_best=min((r for r in records if 'cost' in r and not r.get('relocation_drifts') and not address_offsets.intersection(r.get('offsets',[])) and 'error' not in r),key=lambda r:(r['cost'],r['volatile_tokens']),default=None)
if address_best:
    seed=sources[address_best['tag']]
    (OUT/'best_address_renderer.cpp').write_text(seed,encoding='utf-8',newline='\n')
    (OUT/'best_address_renderer.json').write_text(json.dumps(address_best,indent=2),encoding='utf-8')
    jobs=[]
    # Same ordinary additions through different natural helper boundaries.
    definitions=[
      'static __forceinline void AddExpandedTop(Vector3& a,const Vector3& b) {a.X+=b.X;a.Y+=b.Y;a.Z+=b.Z;}\n',
      'static __forceinline void AddExpandedTop(Vector3& a,const Vector3& b) {Vector3::Add(a,b,&a);}\n',
      'static __forceinline void AddExpandedTop(Vector3& a,const Vector3& b) {Vector3::Add(b,a,&a);}\n',
      'static __forceinline void AddExpandedTop(Vector3& a,const Vector3& b) {a.Set(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}\n',
      'static __forceinline void AddExpandedTop(Vector3& a,const Vector3& b) {a.X=b.X+a.X;a.Y=b.Y+a.Y;a.Z=b.Z+a.Z;}\n'
    ]
    for i,helper in enumerate(definitions):
        text=seed.replace('void SegLineRendererClass::Render',helper+'void SegLineRendererClass::Render',1).replace('top += delta;','AddExpandedTop(top, delta);')
        if text!=seed:jobs.append(('top_add_helper_'+str(i),text,None))
    # Explicit local construction for the temporary displacement, keeping Vector3.
    for declaration in ['struct ExpansionDelta : Vector3 { ExpansionDelta(const Vector3& a):Vector3(a) {} }; ExpansionDelta delta(top - bottom);','Vector3 delta; delta = top - bottom;']:
        text=seed.replace('Vector3 delta = top - bottom;',declaration)
        if text!=seed:jobs.append(('delta_storage_'+str(len(jobs)),text,None))
    # Per-call-site helper boundaries: clone an existing helper for one use only.
    name='DotSegLineLastTopSequential'
    m=re.search(r'static WWINLINE float '+name+r'\([^\n]*\)\s*\{[^}]*\}',seed)
    if m:
        uses=list(re.finditer(r'\b'+name+r'\(',seed))[1:]
        for i,use in enumerate(uses):
            helper=m.group(0).replace(name,name+'Site')+'\n'
            text=seed[:use.start()]+name+'Site'+seed[use.start()+len(name):]
            text=text.replace('void SegLineRendererClass::Render',helper+'void SegLineRendererClass::Render',1)
            jobs.append(('top_dot_site_'+str(i),text,None))
    if time.monotonic()<deadline-45 and not best.get('verified_exact'):batch(jobs)

if best_text:
    r=evaluate(('final_recheck',best_text,best.get('mask')));accept(r,best_text)
    # Unconditionally run strict resolver even when the lane is still above nine.
    row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':(OUT/'final_recheck.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
    try:
        p=build.compile_function(row,symbols,OUT/'final_recheck.obj',retain_compiled=True)
        r.update(resolved_diffs=sum(a!=b for a,b in zip(retail,p['bytes'])),unresolved=p['unresolved'],masked=p['masked'],resolved_sha256=sha(p['bytes']),raw_hex=p['compiled'].hex(),retail_hex=retail.hex(),relocation_tuples=p['relocs'],boundary_issue=build.claimed_boundary_issue(p['compiled'],SIZE,p['relocs']))
        r['verified_exact']=p['bytes']==retail and r['size']==SIZE and not p['unresolved'] and not p['masked'] and not r['relocation_drifts'] and not r['boundary_issue']
        (OUT/'final_recheck.json').write_text(json.dumps(r,indent=2),encoding='utf-8')
    except (Exception,SystemExit) as exc:print('STRICT_ERROR',str(exc),flush=True)
    checks=[]
    for old in proof['canonical_sibling_checks']:
        row={'name':old['symbol'],'target_rva':old['rva'],'target_size':str(old['size']),'source':(OUT/'final_recheck.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
        try:
            p=build.compile_function(row,symbols,OUT/'final_recheck.obj',retain_compiled=True)
            target=build.read_target_bytes(int(old['rva'],16),old['size'])
            checks.append({'symbol':old['symbol'],'rva':old['rva'],'size':old['size'],'exact':p['bytes']==target and not p['masked'] and not p['unresolved']})
        except (Exception,SystemExit) as exc:checks.append({'symbol':old['symbol'],'error':str(exc),'exact':False})
    (OUT/'renderer_siblings.json').write_text(json.dumps(checks,indent=2),encoding='utf-8')
    print('FINAL',json.dumps({k:v for k,v in r.items() if k not in ('offsets','raw_hex','retail_hex','relocation_tuples','diff_instructions')}),flush=True)
    print('SIBLINGS',json.dumps(checks),flush=True)
(OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
print('SUMMARY',json.dumps({'trials':len(records),'best_cost':best['cost'] if best else None,'exact':[r['tag'] for r in records if r.get('verified_exact')]}),flush=True)
