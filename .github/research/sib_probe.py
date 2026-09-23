"""Bounded ordinary-C++ source search. Never alter emitted bytes or gates.
Every candidate has a distinct object. Final proof uses the strict repo resolver.
"""
from pathlib import Path
import concurrent.futures, hashlib, itertools, json, os, re, subprocess, sys, time
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import build,probe
OUT=ROOT/'build'/'sib_research_20260923';OUT.mkdir(parents=True,exist_ok=True)
(OUT/'driver_source.json').write_text(json.dumps({'source':Path(__file__).read_text()},indent=2),encoding='utf-8')
subprocess.run(['git','sparse-checkout','add','Code/Libraries','Code/GameEngine','Code/GameEngineDevice','reference/shims','reference/CnC_Generals_Zero_Hour/GeneralsMD/Code','vendor/stlport'],cwd=ROOT,check=True,timeout=240)
RVA=0x00960A30;SIZE=14081;SYM='?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z'
original=(ROOT/'reverse/attempts/0x00960a30.cpp').read_text(encoding='utf-8').replace('#include "../attempt_support/0x00960a30.inc"','#include "../../reverse/attempt_support/0x00960a30.inc"')
retail=build.read_target_bytes(RVA,SIZE);symbols=build.load_symbol_map();atoms=list(re.finditer(r'\bvolatile\s+',original));assert len(atoms)==79
(OUT/'support_source.json').write_text(json.dumps({'source':(ROOT/'reverse/attempt_support/0x00960a30.inc').read_text(encoding='utf-8')}),encoding='utf-8')
deadline=time.monotonic()+640; records=[];sources={};cache={};best=None;best_text=None;counter=0

def sha(b):return hashlib.sha256(b).hexdigest()
def source_for(mask):
    s=original
    for i in sorted(mask,reverse=True):m=atoms[i];s=s[:m.start()]+s[m.end():]
    return s

def evaluate(job):
    tag,text,mask=job;path=OUT/(tag+'.cpp');obj=OUT/(tag+'.obj');path.write_text(text,encoding='utf-8',newline='\n');obj.unlink(missing_ok=True)
    rec={'tag':tag,'mask':sorted(mask) if mask is not None else None,'source_sha256':sha(text.encode()),'volatile_tokens':len(re.findall(r'\bvolatile\b',text))}
    t=time.monotonic()
    try:
        cmd,env=build.compiler_command(path,obj)
        p=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True,errors='replace',timeout=45)
        rec.update(returncode=p.returncode,seconds=round(time.monotonic()-t,4))
        if p.returncode or not obj.exists():rec['error']=(p.stdout+p.stderr)[-1500:];return rec
        data,relocs=build.read_object_symbol_bytes(obj,SYM);data=data.rstrip(b'\xcc')
        _,oi,_,_,rb,ob,drifts=probe.diagnostic_streams(retail,data,relocs)
        offsets=[i for i,(a,b) in enumerate(zip(rb,ob)) if a!=b]
        rec.update(size=len(data),diff_count=len(offsets),length_delta=len(data)-SIZE,cost=len(offsets)+2*abs(len(data)-SIZE),relocations=len(relocs),relocation_drifts=len(drifts),code_sha256=sha(data),offsets=offsets)
        if rec['cost']<=9 and not drifts:
            row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':path.relative_to(ROOT).as_posix(),'status':'matched','notes':''}
            patch=build.compile_function(row,symbols,obj,retain_compiled=True)
            rec.update(resolved_diffs=sum(a!=b for a,b in zip(retail,patch['bytes'])),masked=patch['masked'],unresolved=patch['unresolved'],boundary_issue=build.claimed_boundary_issue(patch['compiled'],SIZE,patch['relocs']),resolved_sha256=sha(patch['bytes']))
            rec['verified_exact']=len(data)==SIZE and patch['bytes']==retail and not patch['masked'] and not patch['unresolved'] and not rec['boundary_issue']
            rec['raw_hex']=data.hex();rec['retail_hex']=retail.hex();rec['relocation_tuples']=relocs
            rec['diff_instructions']=[{'offset':hex(x.address),'bytes':bytes(x.bytes).hex(),'instruction':x.mnemonic+' '+x.op_str} for x in oi if any(x.address<=i<x.address+x.size for i in offsets)]
    except (Exception,SystemExit) as exc:rec['error']=type(exc).__name__+': '+str(exc)
    return rec

def accept(rec,text):
    global best,best_text
    records.append(rec);sources[rec['tag']]=text;cache[sha(text.encode())]=rec
    (OUT/(rec['tag']+'.json')).write_text(json.dumps(rec,indent=2),encoding='utf-8')
    if 'cost' in rec and rec.get('relocation_drifts')==0 and ('error' not in rec) and (best is None or (rec['cost'],rec['volatile_tokens'])<(best['cost'],best['volatile_tokens'])):
        best=rec;best_text=text
        (OUT/'best_renderer.cpp').write_text(text,encoding='utf-8',newline='\n');(OUT/'best_renderer.json').write_text(json.dumps(rec,indent=2),encoding='utf-8')
        print('NEW_BEST',json.dumps({k:v for k,v in rec.items() if k not in ('offsets','raw_hex','retail_hex','relocation_tuples','diff_instructions')}),flush=True)
    if len(records)%20==0:print('PROGRESS',len(records),'best',best['cost'] if best else None,flush=True)

def batch(jobs):
    unique=[];seen=set()
    for job in jobs:
        digest=sha(job[1].encode())
        if digest in cache or digest in seen:continue
        seen.add(digest);unique.append(job)
    out=[]
    # Four independent compilers; no shared cache/output path and no checkout writes.
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        pending={};iterator=iter(unique)
        while time.monotonic()<deadline-30:
            while len(pending)<4 and not (best and best.get('verified_exact')):
                job=next(iterator,None)
                if job is None:break
                pending[pool.submit(evaluate,job)]=job
            if not pending:break
            done,_=concurrent.futures.wait(pending,return_when=concurrent.futures.FIRST_COMPLETED)
            for f in done:
                job=pending.pop(f);r=f.result();accept(r,job[1]);out.append(r)
        for f,job in list(pending.items()):r=f.result();accept(r,job[1]);out.append(r)
    (OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
    return out

seed_masks=[[2,7,17,19,28,41],[19,41],[2,5,17,19,28,41],[2,11,17,19,28,41],[2,17,19,28,41,67],[2,17,19,28,41,73]]
batch([('seed_'+str(i),source_for(m),m) for i,m in enumerate(seed_masks)])
assert best and best['cost']==9,'Reproduce the nine-byte checkpoint first'
seed=best_text; jobs=[]
# Change only local storage construction while retaining native scalar references.
for variable,value in [('vidx','0'),('tidx','0'),('last_top_vidx','0'),('last_bottom_vidx','1'),('top_int_idx','1'),('bottom_int_idx','1'),('vnum','num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE]')]:
    for ctor in (True,False):
        name='Storage_'+variable
        decl='struct '+name+' { unsigned int value; '+(name+'(unsigned int n):value(n) {}' if ctor else '')+' };\n'
        init=(name+' holder_'+variable+'('+value+');') if ctor else (name+' holder_'+variable+' = {'+value+'};')
        decl+=init+'\nunsigned int &'+variable+' = holder_'+variable+'.value;'
        pattern=r'unsigned int '+variable+r'\s*=\s*'+re.escape(value)+r';'
        text=re.sub(pattern,lambda _:decl,seed,count=1)
        if text!=seed:jobs.append(('storage_'+variable+('_ctor' if ctor else '_aggregate'),text,None))
for reference in (False,True):
    for ctor in (True,False):
        decl='struct VertexBufferStorage { VertexFormatXYZDUV1 *value; '+('VertexBufferStorage(VertexFormatXYZDUV1 *p):value(p) {}' if ctor else '')+' };\n'
        decl+=('VertexBufferStorage vertexStorage(getVertexBuffer(vnum));' if ctor else 'VertexBufferStorage vertexStorage = {getVertexBuffer(vnum)};')
        decl+='\nVertexFormatXYZDUV1 *'+('&' if reference else '')+'vArray = vertexStorage.value;'
        text=seed.replace('VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);',decl)
        jobs.append(('vertex_holder_'+str(int(reference))+str(int(ctor)),text,None))
# Layout-neutral cleanup of identity casts and an unused helper.
clean=re.sub(r'\*\((?:const )?float \*\)&([A-Za-z_]\w*(?:\.[A-Za-z_]\w*)?)',r'\1',seed)
jobs.append(('plain_float_reads',clean,None))
for var in ('vidx','tidx','vnum','edge','iidx_r','iidx_w'):
    for new in ('cursor_'+var,'position_'+var):jobs.append(('rename_'+new,re.sub(r'\b'+var+r'\b',new,seed),None))
for typ in ('int','unsigned long','long'):
    text=seed.replace('unsigned int vidx = 0;',typ+' vidx = 0;')
    jobs.append(('vidx_type_'+typ.replace(' ','_'),text,None))
# Existing indexed element spelling, keeping all stores and calls in order.
jobs.append(('vertex_pointer_add',re.sub(r'vArray\[([^\]\n]+)\]\.',r'(vArray + (\1))->',seed),None))
jobs.append(('vertex_reversed_subscript',re.sub(r'vArray\[([^\]\n]+)\]',r'(\1)[vArray]',seed),None))
for name in ('SegLineEndpointDot',):
    pattern=r'static WWINLINE float '+name+r'\([^\n]*\)\s*\{[^}]*\}'
    jobs.append(('remove_unused_'+name,re.sub(pattern,'',seed,count=1),None))
# Ordinary arithmetic spelling at the parallel-test X product; no new volatile.
dot='Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge])'
expressions=[
'return (a.X*b.X+a.Y*b.Y)+a.Z*b.Z;',
'return (a.Z*b.Z+a.Y*b.Y)+a.X*b.X;',
'float z=a.Z*b.Z; float y=a.Y*b.Y; float x=a.X*b.X; return (z+y)+x;',
'float x=a.X*b.X; float y=a.Y*b.Y; float z=a.Z*b.Z; return (x+y)+z;',
'float x=a.X; float y=a.Y; float z=a.Z; return (z*b.Z+y*b.Y)+x*b.X;',
'const float &x=a.X; const float &y=a.Y; const float &z=a.Z; return (z*b.Z+y*b.Y)+x*b.X;',
'return (a[2]*b[2]+a[1]*b[1])+a[0]*b[0];',
'Vector3 p(a.X*b.X,a.Y*b.Y,a.Z*b.Z); return (p.Z+p.Y)+p.X;'
]
for i,body in enumerate(expressions):
    for swapped in (False,True):
        helper='static __forceinline float ParallelDot(const Vector3& a,const Vector3& b) {'+body+'}\n'
        call='ParallelDot('+('next_seg->EdgePlane[edge], prev_seg->EdgePlane[edge]' if swapped else 'prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]')+')'
        text=seed.replace('void SegLineRendererClass::Render',helper+'void SegLineRendererClass::Render',1).replace(dot,call)
        jobs.append(('dot_'+str(i)+'_'+str(int(swapped)),text,None))
batch(jobs)
# Beam search across original qualifier removals/restorations. This changes only
# C++ source, retaining several distinct instruction outputs to cross plateaus.
for generation in range(4):
    if (best and best.get('verified_exact')) or time.monotonic()>deadline-75:break
    eligible=sorted((r for r in records if r.get('mask') is not None and 'cost' in r and r.get('relocation_drifts')==0 and 'error' not in r),key=lambda r:(r['cost'],r['volatile_tokens']))
    beam=[];codes=set()
    for r in eligible:
        if r['code_sha256'] in codes:continue
        codes.add(r['code_sha256']);beam.append(r)
        if len(beam)==4:break
    jobs=[]
    for parent in beam:
        for atom in range(len(atoms)):
            mask=set(parent['mask'])^{atom}
            counter+=1;jobs.append(('beam_'+str(generation)+'_'+str(counter),source_for(mask),mask))
    if best and best.get('mask') is None:
        # Also explore removing a single remaining qualifier from the best
        # structural candidate, without attempting to encode it as a mask.
        for i,m in enumerate(re.finditer(r'\bvolatile\s+',best_text)):
            jobs.append(('struct_clean_'+str(generation)+'_'+str(i),best_text[:m.start()]+best_text[m.end():],None))
    result=batch(jobs)
    if not result:break

# Final fresh serial compile, plus the existing canonical sibling checks.
if best_text:
    r=evaluate(('final_recheck',best_text,best.get('mask')));accept(r,best_text)
    print('FINAL',json.dumps({k:v for k,v in r.items() if k not in ('offsets','raw_hex','retail_hex','relocation_tuples','diff_instructions')}),flush=True)
    proof=json.loads((ROOT/'reverse/attempt_support/0x00960a30-verification.json').read_text());checks=[]
    for old in proof['canonical_sibling_checks']:
        row={'name':old['symbol'],'target_rva':old['rva'],'target_size':str(old['size']),'source':(OUT/'final_recheck.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
        try:
            p=build.compile_function(row,symbols,OUT/'final_recheck.obj',retain_compiled=True)
            target=build.read_target_bytes(int(old['rva'],16),old['size'])
            checks.append({'symbol':old['symbol'],'rva':old['rva'],'size':old['size'],'exact':p['bytes']==target and not p['masked'] and not p['unresolved']})
        except (Exception,SystemExit) as exc:checks.append({'symbol':old['symbol'],'error':str(exc),'exact':False})
    (OUT/'renderer_siblings.json').write_text(json.dumps(checks,indent=2),encoding='utf-8');print('SIBLINGS',json.dumps(checks),flush=True)
(OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
print('SUMMARY',json.dumps({'trials':len(records),'best_cost':best['cost'] if best else None,'exact':[r['tag'] for r in records if r.get('verified_exact')]}),flush=True)
