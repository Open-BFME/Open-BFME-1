"""Renderer experiments on ordinary C++ source. No emitted-byte modifications.
Retain real compiler outputs and strict relocation results; do not change master.
"""
from pathlib import Path
import hashlib, itertools, json, os, re, subprocess, sys, time
ROOT=Path.cwd(); sys.path.insert(0,str(ROOT/'tools'))
import build, probe
OUT=ROOT/'build'/'sib_research_20260923'; OUT.mkdir(parents=True,exist_ok=True)
subprocess.run(['git','sparse-checkout','add','Code/Libraries','Code/GameEngine','Code/GameEngineDevice','reference/shims','reference/CnC_Generals_Zero_Hour/GeneralsMD/Code','vendor/stlport'],cwd=ROOT,check=True,timeout=240)
RVA=0x00960A30; SIZE=14081
SYM='?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z'
retail=build.read_target_bytes(RVA,SIZE); symbols=build.load_symbol_map()
original=(ROOT/'reverse/attempts/0x00960a30.cpp').read_text(encoding='utf-8').replace('#include "../attempt_support/0x00960a30.inc"','#include "../../reverse/attempt_support/0x00960a30.inc"')
rtm=build.vc71_root(); records=[]; best=None; baseline=None; best_source=None; tested={}; deadline=time.monotonic()+610

def sha(data):return hashlib.sha256(data).hexdigest()
def span(text,name):
    m=re.search(r'static\s+(?:WWINLINE|__forceinline)\s+[^\n]+?\b'+re.escape(name)+r'\([^\n]*\)\s*\{',text)
    if not m:raise ValueError(name)
    pos=m.end(); depth=1
    while depth:
        if text[pos]=='{':depth+=1
        elif text[pos]=='}':depth-=1
        pos+=1
    return m.start(),pos

def compiler_receipt(root):
    rec={'root':str(root),'files':{}}
    for rel in ['Vc7/bin/cl.exe','Vc7/bin/c1.dll','Vc7/bin/c1xx.dll','Vc7/bin/c2.dll']:
        p=root/rel
        if p.exists():rec['files'][rel]={'sha256':sha(p.read_bytes()),'size':p.stat().st_size}
    cmd=[str(root/'Vc7/bin/cl.exe')]
    p=subprocess.run(cmd,cwd=ROOT,env=build.compiler_environment(root),capture_output=True,text=True,errors='replace',timeout=30)
    rec['banner']=p.stdout+p.stderr
    print('COMPILER',json.dumps(rec),flush=True);return rec

rtm_receipt=compiler_receipt(rtm)
(OUT/'compiler_rtm.json').write_text(json.dumps(rtm_receipt,indent=2),encoding='utf-8')

def evaluate(tag,text,strict=False,toolchain='rtm',keep_rtm_headers=False):
    global best,best_source,baseline
    digest=sha(text.encode()); key=(toolchain,keep_rtm_headers,digest)
    if key in tested:return tested[key]
    path=OUT/(tag+'.cpp'); obj=OUT/(tag+'.obj'); path.write_text(text,encoding='utf-8',newline='\n'); obj.unlink(missing_ok=True)
    command,env=build.compiler_command(path,obj)
    if keep_rtm_headers:env['INCLUDE']=env['INCLUDE'].replace(str(build.vc71_root()/'Vc7/include'),str(rtm/'Vc7/include'))
    begin=time.monotonic()
    try:run=subprocess.run(command,cwd=ROOT,env=env,capture_output=True,text=True,errors='replace',timeout=45)
    except subprocess.TimeoutExpired:
        rec={'tag':tag,'toolchain':toolchain,'error':'compiler timeout'};records.append(rec);return rec
    rec={'tag':tag,'toolchain':toolchain,'rtm_headers':keep_rtm_headers,'source_sha256':digest,'seconds':round(time.monotonic()-begin,3),'returncode':run.returncode,'volatile_tokens':len(re.findall(r'\bvolatile\b',text))}
    if run.returncode or not obj.exists():rec['error']=(run.stdout+run.stderr)[-1800:]
    else:
        try:
            data,relocs=build.read_object_symbol_bytes(obj,SYM);data=data.rstrip(b'\xcc')
            _,ours,_,_,rb,ob,drifts=probe.diagnostic_streams(retail,data,relocs)
            offsets=[i for i,(a,b) in enumerate(zip(rb,ob)) if a!=b]
            rec.update(size=len(data),diff_count=len(offsets),length_delta=len(data)-SIZE,relocations=len(relocs),relocation_drifts=len(drifts),cost=len(offsets)+2*abs(len(data)-SIZE),code_sha256=sha(data),retail_sha256=sha(retail),offsets=offsets)
            if baseline is None:baseline=(data,relocs)
            rec['same_relocations']=relocs==baseline[1]
            promising=best is None or rec['cost']<best.get('cost',10**9)
            if strict or promising or rec['cost']<=10:
                row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':path.relative_to(ROOT).as_posix(),'status':'matched','notes':''}
                patch=build.compile_function(row,symbols,obj,retain_compiled=True)
                rec.update(resolved_diffs=sum(a!=b for a,b in zip(retail,patch['bytes'])),unresolved=patch['unresolved'],masked=patch['masked'],resolved_sha256=sha(patch['bytes']),boundary_issue=build.claimed_boundary_issue(patch['compiled'],SIZE,patch['relocs']))
                rec['verified_exact']=patch['bytes']==retail and len(data)==SIZE and not patch['unresolved'] and not patch['masked'] and not drifts and rec['boundary_issue'] is None
                rec['relocation_tuples']=relocs
                rec['diff_instructions']=[{'offset':hex(x.address),'bytes':bytes(x.bytes).hex(),'instruction':x.mnemonic+' '+x.op_str} for x in ours if any(x.address<=i<x.address+x.size for i in offsets)]
                rec['raw_hex']=data.hex();rec['retail_hex']=retail.hex()
            if toolchain=='rtm' and (best is None or (rec['cost'],rec['volatile_tokens'])<(best['cost'],best['volatile_tokens'])):
                best=rec;best_source=text
                (OUT/'best_renderer.cpp').write_text(text,encoding='utf-8',newline='\n')
                (OUT/'best_renderer.json').write_text(json.dumps(rec,indent=2),encoding='utf-8')
                print('NEW_BEST',json.dumps({k:v for k,v in rec.items() if k not in ('offsets','relocation_tuples','diff_instructions','raw_hex','retail_hex')}),flush=True)
        except (Exception,SystemExit) as exc:rec['error']=type(exc).__name__+': '+str(exc)
    tested[key]=rec;records.append(rec)
    (OUT/(tag+'.json')).write_text(json.dumps(rec,indent=2),encoding='utf-8')
    (OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
    print('RESULT',json.dumps({k:v for k,v in rec.items() if k not in ('offsets','relocation_tuples','diff_instructions','raw_hex','retail_hex')}),flush=True)
    return rec

evaluate('baseline',original,True)
# Seven individual qualifiers in the three helpers that independently improved
# the previous measured baseline. Enumerate by number removed, not lexicographic
# Cartesian order. These only remove existing coercions; no new ones are added.
names=['SegLineStartSignXZ','DotSegLineLastTopSequential','DotSegLineTopPlaneYXZ']
positions=[]
for name in names:
    a,b=span(original,name)
    positions.extend((m.start(),m.end()) for m in re.finditer(r'\bvolatile\s+',original) if a<=m.start()<b)
assert len(positions)==7
print('ATOMS',json.dumps({'names':names,'positions':positions}),flush=True)
for n in range(1,8):
    for indices in itertools.combinations(range(7),n):
        if time.monotonic()>deadline-150:break
        candidate=original
        for a,b in sorted([positions[i] for i in indices],reverse=True):candidate=candidate[:a]+candidate[b:]
        r=evaluate('remove_'+''.join(map(str,indices)),candidate)
        if r.get('verified_exact'):break
    if (best and best.get('verified_exact')) or time.monotonic()>deadline-150:break
# Now remove one remaining qualifier from the best source, accepting lower cost
# or equal cost with fewer qualifiers. A second pass tests interactions.
for generation in range(2):
    if not best_source or best.get('verified_exact'):break
    seed=best_source
    atoms=list(re.finditer(r'\bvolatile\s+',seed))
    for i,m in enumerate(atoms):
        if time.monotonic()>deadline-95:break
        s=seed[:m.start()]+seed[m.end():]
        r=evaluate('clean_g'+str(generation)+'_'+str(i),s)
        if r.get('verified_exact'):break
    if best_source==seed or time.monotonic()>deadline-95:break

# Pinned complete SP1 distribution, kept separate from the repo's toolchain.
# No installers or repository-supplied setup scripts are executed.
try:
    sp1=OUT/'msvc710_sp1';sp1.mkdir(exist_ok=True)
    for cmd in [['git','init',str(sp1)],['git','-C',str(sp1),'remote','add','origin','https://github.com/archaic-msvc/msvc710_sp1.git'],['git','-C',str(sp1),'fetch','--depth=1','origin','cf62606064633dd8441aa2feffe34792099cc366'],['git','-C',str(sp1),'checkout','--detach','FETCH_HEAD']]:
        subprocess.run(cmd,cwd=ROOT,check=True,capture_output=True,timeout=90)
    actual=subprocess.check_output(['git','-C',str(sp1),'rev-parse','HEAD'],text=True).strip()
    assert actual=='cf62606064633dd8441aa2feffe34792099cc366'
    # Runtime DLL fallback from the already available original installation.
    os.environ['PATH']=str(rtm.parents[1])+os.pathsep+str(rtm/'Common7/IDE')+os.pathsep+os.environ.get('PATH','')
    os.environ['VC71_ROOT']=str(sp1)
    receipt=compiler_receipt(sp1);receipt['commit']=actual
    (OUT/'compiler_sp1.json').write_text(json.dumps(receipt,indent=2),encoding='utf-8')
    evaluate('sp1_original',original,True,'sp1')
    evaluate('sp1_original_rtm_headers',original,True,'sp1',True)
    if best_source:evaluate('sp1_best_rtm_source',best_source,True,'sp1',True)
except (Exception,SystemExit) as exc:
    (OUT/'sp1_error.json').write_text(json.dumps({'error':str(exc)}),encoding='utf-8')
    print('SP1_ERROR',str(exc),flush=True)
finally:os.environ['VC71_ROOT']=str(rtm)

# Fresh recompile of the selected RTM source, followed by all 17 renderer checks.
if best_source:
    selected=best_source
    # Different filename and object prevents reuse of a previously scored object.
    tested.pop(('rtm',False,sha(selected.encode())),None)
    verification=evaluate('final_recheck',selected,True)
    checks=[];obj=OUT/'final_recheck.obj'
    proof=json.loads((ROOT/'reverse/attempt_support/0x00960a30-verification.json').read_text())
    for old in proof['canonical_sibling_checks']:
        row={'name':old['symbol'],'target_rva':old['rva'],'target_size':str(old['size']),'source':(OUT/'final_recheck.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
        try:
            p=build.compile_function(row,symbols,obj,retain_compiled=True)
            target=build.read_target_bytes(int(old['rva'],16),old['size'])
            checks.append({'symbol':old['symbol'],'rva':old['rva'],'size':old['size'],'exact':p['bytes']==target and not p['masked'] and not p['unresolved']})
        except (Exception,SystemExit) as exc:checks.append({'symbol':old['symbol'],'error':str(exc),'exact':False})
    (OUT/'renderer_siblings.json').write_text(json.dumps(checks,indent=2),encoding='utf-8')
    print('RENDER_SIBLINGS',json.dumps(checks),flush=True)
print('SUMMARY',json.dumps({'trials':len(records),'rtm_best':{k:v for k,v in (best or {}).items() if k not in ('offsets','relocation_tuples','diff_instructions','raw_hex','retail_hex')},'exact':[r['tag'] for r in records if r.get('verified_exact')]}),flush=True)
