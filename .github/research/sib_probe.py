"""Resume the nine-byte renderer checkpoint. Diagnostic work only, not a landing.
No compiler/output byte patching, no accepted source, ledger, or gate edits.
"""
from pathlib import Path
import hashlib,urllib.request
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
deadline=time.monotonic()+500
mask=[2,7,8,14,17,19,28,36,41]
seed=source_for(mask)
r=evaluate(('resume_baseline',seed,mask));accept(r,seed)
assert r.get('resolved_diffs')==9 and r.get('size')==SIZE and not r.get('masked') and not r.get('unresolved'),r
print('BASELINE_DETAIL',json.dumps(r),flush=True)
import capstone
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
for label,data in [('retail',retail),('candidate',bytes.fromhex(r['raw_hex']))]:
    for ins in md.disasm(data,0):
        if any(abs(ins.address-i)<22 for i in r['offsets']):print('RESIDUE',label,hex(ins.address),ins.bytes.hex(),ins.mnemonic,ins.op_str,flush=True)
for i,m in enumerate(atoms):
    print('ATOM',i,original[max(0,m.start()-75):m.end()+100].replace('\n',' '),flush=True)
for name in ['cl.exe','c1.dll','c1xx.dll','c2.dll']:
    p=build.vc71_root()/'Vc7/bin'/name
    if p.exists():print('COMPILER',name,sha(p.read_bytes()),flush=True)
# Natural inline boundaries for existing array indexing (same type, indices, and accesses).
jobs=[]
for reference in (False,True):
    for swapped in (False,True):
        for force in ('inline','__forceinline'):
            ret='VertexFormatXYZDUV1 &' if reference else 'VertexFormatXYZDUV1 *'
            params='unsigned int index, VertexFormatXYZDUV1 *base' if swapped else 'VertexFormatXYZDUV1 *base, unsigned int index'
            helper='static '+force+' '+ret+' RendererVertexAt('+params+') {return '+('base[index]' if reference else 'base+index')+';}\n'
            def replacement(m):
                args=(m[1]+', vArray') if swapped else ('vArray, '+m[1])
                return 'RendererVertexAt('+args+')'+('.' if reference else '->')
            text=re.sub(r'vArray\[([^\]\n]+)\]\.',replacement,seed)
            text=text.replace('void SegLineRendererClass::Render',helper+'void SegLineRendererClass::Render',1)
            jobs.append(('vertex_helper_'+str(reference)+str(swapped)+force,text,None))
# Group fields into an ordinary vertex reference per existing store group.
pat=r'vArray\[vidx\]\.x = ([^;]+);\nvArray\[vidx\]\.y = ([^;]+);\nvArray\[vidx\]\.z = ([^;]+);'
locations=list(re.finditer(pat,seed))
for chosen in [set(range(len(locations)))]+[{i} for i in range(len(locations))]:
    for form in ('ref','pointer','helper'):
        t=seed
        for i in sorted(chosen,reverse=True):
            m=locations[i];fields=m.groups()
            if form=='ref':new='{ VertexFormatXYZDUV1 &vertex=vArray[vidx]; vertex.x='+fields[0]+'; vertex.y='+fields[1]+'; vertex.z='+fields[2]+'; }'
            elif form=='pointer':new='{ VertexFormatXYZDUV1 *vertex=vArray+vidx; vertex->x='+fields[0]+'; vertex->y='+fields[1]+'; vertex->z='+fields[2]+'; }'
            else:new='StoreRendererPosition(vArray[vidx], '+fields[0].split('.')[0]+');'
            t=t[:m.start()]+new+t[m.end():]
        if form=='helper':t=t.replace('void SegLineRendererClass::Render','static __forceinline void StoreRendererPosition(VertexFormatXYZDUV1& v,const Vector3& p) {v.x=p.X; v.y=p.Y; v.z=p.Z;}\nvoid SegLineRendererClass::Render',1)
        jobs.append(('vertex_group_'+form+'_'+str(min(chosen))+'_'+str(len(chosen)),t,None))
# Move native operator bodies across existing helper boundaries; no added volatile.
helpers=list(re.finditer(r'static (?:WWINLINE|__forceinline) [^{]+\{',seed))
for i,m in enumerate(helpers):
    level=1;j=m.end()
    while level and j<len(seed):
        level+=(seed[j]=='{')-(seed[j]=='}');j+=1
    body=seed[m.start():j]
    for kind in ('plain','inline','force','plain_inline','plain_force'):
        new=body
        if 'plain' in kind:new=re.sub(r'\bvolatile\s+','',new)
        if 'inline' in kind:new=new.replace('__forceinline','inline').replace('WWINLINE','inline')
        if 'force' in kind:new=new.replace('WWINLINE','__forceinline')
        if new!=body:jobs.append(('helper_'+str(i)+'_'+kind,seed[:m.start()]+new+seed[j:],None))
# Pure floating expressions in the existing expansion operation. All use native fields.
add_helpers=[
'float x=a.X+b.X; float y=a.Y+b.Y; float z=a.Z+b.Z; a.X=x;a.Y=y;a.Z=z;',
'Vector3 sum(a.X+b.X,a.Y+b.Y,a.Z+b.Z); a=sum;',
'a.X+=b.X;a.Y+=b.Y;a.Z+=b.Z;',
'a.Set(a.X+b.X,a.Y+b.Y,a.Z+b.Z);',
'a+=b;',
'a=a+b;',
'Vector3::Add(a,b,&a);'
]
for i,body in enumerate(add_helpers):
    for swap in (False,True):
        params='const Vector3& b,Vector3& a' if swap else 'Vector3& a,const Vector3& b'
        helper='static __forceinline void RendererExpand('+params+') {'+body+'}\n'
        text=seed.replace('void SegLineRendererClass::Render',helper+'void SegLineRendererClass::Render',1).replace('top += delta;','RendererExpand('+('delta,top' if swap else 'top,delta')+');')
        jobs.append(('expansion_'+str(i)+'_'+str(swap),text,None))
# Plain reads instead of identity pointer casts in different real math helpers.
for i,m in enumerate(helpers):
    level=1;j=m.end()
    while level and j<len(seed):level+=(seed[j]=='{')-(seed[j]=='}');j+=1
    body=seed[m.start():j]
    new=re.sub(r'\*\((?:const )?(?:volatile )?float \*\)&([A-Za-z_]\w*(?:\.[A-Za-z_]\w*)?)',r'\1',body)
    if new!=body:jobs.append(('native_reads_'+str(i),seed[:m.start()]+new+seed[j:],None))
# Preserve all source changes and only retain unique compiled candidates.
batch(jobs)
# Explore interacting helper cleanups from the four closest distinct outputs.
for generation in range(2):
    if best.get('verified_exact') or time.monotonic()>deadline-75:break
    eligible=sorted((x for x in records if 'cost' in x and not x.get('relocation_drifts') and 'error' not in x),key=lambda x:(x['cost'],x['volatile_tokens']))
    beam=[];codes=set()
    for rec in eligible:
        if rec['code_sha256'] in codes:continue
        codes.add(rec['code_sha256']);beam.append(rec)
        if len(beam)==4:break
    more=[]
    for parent in beam:
        text=sources[parent['tag']]
        for i,m in enumerate(re.finditer(r'\bvolatile\s+',text)):
            more.append(('cleanup_'+str(generation)+'_'+parent['tag']+'_'+str(i),text[:m.start()]+text[m.end():],None))
    if not batch(more):break
# Fresh serial compile and strict address-resolved verification.
r=evaluate(('final_recheck',best_text,best.get('mask')))
accept(r,best_text)
row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':(OUT/'final_recheck.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
p=build.compile_function(row,symbols,OUT/'final_recheck.obj',retain_compiled=True)
r.update(resolved_diffs=sum(a!=b for a,b in zip(retail,p['bytes'])),masked=p['masked'],unresolved=p['unresolved'],resolved_sha256=sha(p['bytes']),boundary_issue=build.claimed_boundary_issue(p['compiled'],SIZE,p['relocs']))
r['verified_exact']=p['bytes']==retail and r['size']==SIZE and not r['masked'] and not r['unresolved'] and not r['boundary_issue']
(OUT/'final_recheck.json').write_text(json.dumps(r,indent=2),encoding='utf-8')
checks=[]
for old in json.loads((ROOT/'reverse/attempt_support/0x00960a30-verification.json').read_text())['canonical_sibling_checks']:
    row=dict(row,name=old['symbol'],target_rva=old['rva'],target_size=str(old['size']))
    try:
        p=build.compile_function(row,symbols,OUT/'final_recheck.obj',retain_compiled=True)
        checks.append(dict(old,exact=p['bytes']==build.read_target_bytes(int(old['rva'],16),old['size']) and not p['masked'] and not p['unresolved']))
    except (Exception,SystemExit) as exc:checks.append(dict(old,exact=False,error=str(exc)))
(OUT/'renderer_siblings.json').write_text(json.dumps(checks,indent=2),encoding='utf-8')
print('FINAL',json.dumps({k:v for k,v in r.items() if k not in ('raw_hex','retail_hex','relocation_tuples')}),flush=True)
print('SIBLINGS',json.dumps(checks),flush=True)
print('SUMMARY',json.dumps({'trials':len(records),'best_cost':best['cost'],'exact':r['verified_exact']}),flush=True)
