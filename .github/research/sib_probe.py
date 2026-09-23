"""Scoped compiler research. Production writes occur only in the disposable runner.
No gate bypass, binary patching, remote source update, or progress claim.
"""
from pathlib import Path
import csv, hashlib, itertools, json, re, subprocess, sys, time
ROOT=Path.cwd(); sys.path.insert(0,str(ROOT/'tools'))
import build, probe
OUT=ROOT/'build'/'sib_research_20260923'; OUT.mkdir(parents=True,exist_ok=True)
subprocess.run(['git','sparse-checkout','add','Code/Libraries','Code/GameEngine','Code/GameEngineDevice','reference/shims','reference/CnC_Generals_Zero_Hour/GeneralsMD/Code','vendor/stlport'],cwd=ROOT,check=True,timeout=240)
SPECS={'view':(0x0045C2F0,229,'?getScreenCornerWorldPointsAtZ@View@@UAEXPAUCoord3D@@000M@Z'),'render':(0x00960A30,14081,'?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z')}
records=[]; baselines={}; symbol_map=build.load_symbol_map(); started=time.monotonic()
def sha(data): return hashlib.sha256(data).hexdigest()
def save(): (OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
def evaluate(target,tag,text,strict=False):
    rva,size,symbol=SPECS[target]; retail=build.read_target_bytes(rva,size)
    path=OUT/(tag+'.cpp'); obj=OUT/(tag+'.obj'); path.write_text(text,encoding='utf-8',newline='\n'); obj.unlink(missing_ok=True)
    start=time.monotonic(); ok,output,code=build.try_compile_source(path,obj)
    rec={'target':target,'tag':tag,'returncode':code,'seconds':round(time.monotonic()-start,4),'source_sha256':sha(text.encode())}
    if not ok: rec['error']=output[-2000:]
    else:
        try:
            data,relocs=build.read_object_symbol_bytes(obj,symbol); data=data.rstrip(b'\xcc')
            _,ours,_,_,rb,ob,drifts=probe.diagnostic_streams(retail,data,relocs)
            diffs=[i for i,(a,b) in enumerate(zip(rb,ob)) if a!=b]
            rec.update(size=len(data),diff_count=len(diffs),length_delta=len(data)-size,relocations=len(relocs),relocation_drifts=len(drifts),offsets=diffs,code_sha256=sha(data),retail_sha256=sha(retail),raw_exact=data==retail)
            rec['cost']=len(diffs)+2*abs(len(data)-size)
            if target in baselines:
                bd,br=baselines[target]; rec.update(same_relocations=relocs==br,changed_from_baseline=sum(a!=b for a,b in zip(bd,data))+abs(len(bd)-len(data)))
            else: baselines[target]=(data,relocs)
            if strict or (len(data)==size and rec['cost']<=51 and not drifts):
                row={'name':symbol,'target_rva':hex(rva),'target_size':str(size),'source':path.relative_to(ROOT).as_posix(),'status':'matched','notes':''}
                patch=build.compile_function(row,symbol_map,obj,retain_compiled=True)
                rec.update(resolved_diffs=sum(a!=b for a,b in zip(retail,patch['bytes'])),unresolved=patch['unresolved'],masked=patch['masked'],resolved_sha256=sha(patch['bytes']),boundary_issue=build.claimed_boundary_issue(patch['compiled'],size,patch['relocs']))
                rec['verified_exact']=patch['bytes']==retail and not patch['masked'] and not patch['unresolved'] and len(data)==size and not drifts and rec['boundary_issue'] is None
                if target=='view': rec['raw_hex']=data.hex()
            if strict or rec['cost']<51:
                rec['relocation_tuples']=relocs
                rec['diff_instructions']=[{'offset':hex(x.address),'bytes':bytes(x.bytes).hex(),'instruction':x.mnemonic+' '+x.op_str} for x in ours if any(x.address<=i<x.address+x.size for i in diffs)]
        except (Exception,SystemExit) as exc: rec['error']=type(exc).__name__+': '+str(exc)
    records.append(rec); (OUT/(tag+'.json')).write_text(json.dumps(rec,indent=2),encoding='utf-8'); save()
    print('RESULT',json.dumps({k:v for k,v in rec.items() if k not in ('relocation_tuples','offsets','raw_hex','diff_instructions')}),flush=True)
    return rec

# Integrate the exact witness into its existing canonical owner translation unit.
original=(ROOT/'reverse/attempts/0x0045c2f0.cpp').read_text(encoding='utf-8')
production_path=ROOT/'Code/GameEngine/Source/GameClient/View.cpp'
production=production_path.read_text(encoding='utf-8')
shim=re.search(r'class BFMEViewCornerVTable\s*\{[\s\S]*?\n\};',original).group(0)
start=production.index('void View::getScreenCornerWorldPointsAtZ(')
end=production.index('}  // end getScreenCornerWorldPointsAtZ',start)+len('}  // end getScreenCornerWorldPointsAtZ')
body=production[start:end]
body=body.replace('ICoord2D origin;', 'struct ScreenOrigin : ICoord2D { ScreenOrigin() {} };\n\tScreenOrigin origin;')
for name in ('getWidth','getHeight','getOrigin','screenToWorldAtZ'):
    body=re.sub(r'\b'+name+r'\(', 'reinterpret_cast<BFMEViewCornerVTable *>(this)->'+name+'(',body)
explanation='// Retail View dispatch differs from the vendored Zero Hour declaration.\n// +0x3C width, +0x44 height, +0x4C origin, +0x168 world projection.\n// This is a TU-local ABI view, not a second semantic View definition.\n'
marker='// '+SPECS['view'][2]+' present-unmatched'
repaired=production[:start]+body+production[end:]
repaired=repaired.replace(marker,explanation+shim+'\n\n'+marker,1)
evaluate('view','view_bank',original,True)
view=evaluate('view','view_integrated',repaired,True)
if view.get('verified_exact'):
    obj=OUT/'view_integrated.obj'; checks=[]
    with (ROOT/'reverse/functions.csv').open(encoding='utf-8',newline='') as handle:
        for row in csv.DictReader(handle):
            if row.get('status')!='matched' or row.get('source')!='Code/GameEngine/Source/GameClient/View.cpp': continue
            try:
                got=build.compile_function(row,symbol_map,obj,retain_compiled=True)
                expected=build.read_target_bytes(int(row['target_rva'],16),int(row['target_size']))
                c={'name':row['name'],'rva':row['target_rva'],'size':int(row['target_size']),'exact':got['bytes']==expected and not got['unresolved'] and not got['masked']}
            except (Exception,SystemExit) as exc: c={'name':row['name'],'error':str(exc),'exact':False}
            checks.append(c)
    (OUT/'view_siblings.json').write_text(json.dumps(checks,indent=2),encoding='utf-8')
    print('VIEW_SIBLINGS',json.dumps(checks),flush=True)
    if checks and all(c['exact'] for c in checks):
        # Let the actual repository tool validate source/ledger/relocation/boundary.
        production_path.write_text(repaired,encoding='utf-8',newline='\n')
        cmd=[sys.executable,'tools/add_match.py',SPECS['view'][2],'0x0045C2F0','229',production_path.relative_to(ROOT).as_posix(),'--replace-rva','0x0045C2F0','--notes','View screen-corner world projection; original MSVC71 exact229B no relocations; retail virtual slots 3C/44/4C/168; function-local constructed origin preserves canonical ICoord2D and fixes SIB without added instructions']
        try:
            result=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,errors='replace',timeout=180)
            receipt={'command':cmd,'returncode':result.returncode,'stdout':result.stdout,'stderr':result.stderr}
            print('VIEW_GATE',json.dumps(receipt),flush=True)
            (OUT/'view_gate.json').write_text(json.dumps(receipt,indent=2),encoding='utf-8')
            if result.returncode==0:
                diff=subprocess.run(['git','diff','--','Code/GameEngine/Source/GameClient/View.cpp','reverse/functions.csv','reverse/claims_retired.csv','reverse/attempts/0x0045c2f0.cpp'],cwd=ROOT,capture_output=True,text=True,errors='replace',timeout=30)
                (OUT/'view_integration_patch.json').write_text(json.dumps({'patch':diff.stdout},indent=2),encoding='utf-8')
                print('VIEW_PATCH',json.dumps({'patch':diff.stdout}),flush=True)
        except subprocess.TimeoutExpired:
            print('VIEW_GATE_TIMEOUT',flush=True)

text=(ROOT/'reverse/attempts/0x00960a30.cpp').read_text(encoding='utf-8').replace('#include "../attempt_support/0x00960a30.inc"','#include "../../reverse/attempt_support/0x00960a30.inc"')
evaluate('render','render_baseline',text,True)
# Constructed storage, rather than changing the actual Vector3/LineSegment types.
variants=[]
for arg in ('int','unsigned int'):
    for ctor in ('','SegmentStorage() {}'):
        definition='struct SegmentStorage { LineSegment data[MAX_SEGLINE_POINT_BUFFER_SIZE + 1]; '+ctor+' LineSegment& operator[]('+arg+' i) {return data[i];} };\nSegmentStorage segment;'
        s=text.replace('LineSegment segment[MAX_SEGLINE_POINT_BUFFER_SIZE + 1];',definition)
        assert s!=text
        variants.append(('segment_storage_'+arg.replace(' ','_')+('_ctor' if ctor else '_implicit'),s))
    for ctor in ('','IntersectionStorage() {}'):
        definition='struct IntersectionStorage { typedef LineSegmentIntersection Pair[NUM_EDGES]; Pair data[MAX_SEGLINE_POINT_BUFFER_SIZE + 1]; '+ctor+' Pair& operator[]('+arg+' i) {return data[i];} };\nIntersectionStorage intersection;'
        s=text.replace('LineSegmentIntersection intersection[MAX_SEGLINE_POINT_BUFFER_SIZE + 1][NUM_EDGES];',definition)
        assert s!=text
        variants.append(('intersection_storage_'+arg.replace(' ','_')+('_ctor' if ctor else '_implicit'),s))
# Value-returning construction used for scalar local storage and pointer handles.
for variable,kind in [('iidx_r','unsigned int'),('iidx_w','unsigned int'),('pidx','unsigned int'),('sidx','unsigned int'),('iidx','unsigned int'),('view','Matrix4x4'),('modelview','Matrix3D')]:
    name='Storage_'+variable
    if kind.startswith('unsigned'):
        definition='struct '+name+' { '+kind+' value; '+name+'() {} };\n'+name+' local_'+variable+';\n'+kind+'& '+variable+' = local_'+variable+'.value;'
    else:
        definition='struct '+name+' : '+kind+' { '+name+'() {} };\n'+name+' '+variable+';'
    s=text.replace(kind+' '+variable+';',definition,1)
    assert s!=text,variable
    variants.append(('local_storage_'+variable,s))
# Replace only the stack buffer type, with a typed subscript and no pointer conversion.
for variable,length,kind in [('u_values','2','float'),('num_intersections','NUM_EDGES','unsigned int'),('v_index_array','MAX_SEGLINE_POLY_BUFFER_SIZE','TriIndex')]:
    for arg in ('int','unsigned int'):
        name='Buffer_'+variable
        definition='struct '+name+' { '+kind+' data['+length+']; '+name+'() {} '+kind+'& operator[]('+arg+' i) {return data[i];} };\n'+name+' '+variable+';'
        s=re.sub(r'\b'+re.escape(kind)+r'\s+'+variable+r'\['+length+r'\];',definition,text,count=1)
        assert s!=text,variable
        variants.append(('buffer_'+variable+'_'+arg.replace(' ','_'),s))
# Keep the enum induction variable; change only the typed indexed plane accessor.
for arg in ('int','unsigned int','SegmentEdge'):
    for parameter in ('value','reference'):
        at=arg if parameter=='value' else 'const '+arg+'&'
        definition='Vector3& edgePlane('+at+' i) {return EdgePlane[i];}'
        s=text.replace('struct LineSegment {','struct LineSegment {\n'+definition,1)
        s=re.sub(r'((?:next|curr|prev)_seg)->EdgePlane\[edge\]',r'\1->edgePlane(edge)',s)
        variants.append(('plane_accessor_'+arg.replace(' ','_')+'_'+parameter,s))
# Explicit temporaries at the one remaining dot operation; no added volatility.
dot='Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge])'
for style in range(6):
    declarations=[
      'float x = a.X*b.X; float y=a.Y*b.Y; float z=a.Z*b.Z; return (x+y)+z;',
      'float z = a.Z*b.Z; float y=a.Y*b.Y; float x=a.X*b.X; return (x+y)+z;',
      'return (a.X*b.X+a.Y*b.Y)+a.Z*b.Z;',
      'return a.Z*b.Z+(a.Y*b.Y+a.X*b.X);',
      'Vector3 products(a.X*b.X,a.Y*b.Y,a.Z*b.Z); return products.X+products.Y+products.Z;',
      'float dot=a.X*b.X; dot+=a.Y*b.Y; dot+=a.Z*b.Z; return dot;'
    ][style]
    helper='static __forceinline float MergeParallelDot(const Vector3& a,const Vector3& b) {'+declarations+'}\n'
    s=text.replace('void SegLineRendererClass::Render',helper+'void SegLineRendererClass::Render',1).replace(dot,'MergeParallelDot(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge])')
    variants.append(('merge_parallel_dot_'+str(style),s))
# Remove volatility one helper at a time to measure which pieces actually need it.
for match in re.finditer(r'static\s+(?:WWINLINE|__forceinline)\s+[^\n]+?\b([A-Za-z_]\w*)\([^\n]*\)\s*\{',text):
    a=match.start(); brace=text.index('{',match.start()); depth=1; b=brace+1
    while depth and b<len(text):
        if text[b]=='{':depth+=1
        elif text[b]=='}':depth-=1
        b+=1
    fragment=text[a:b]
    if 'volatile' not in fragment:continue
    s=text[:a]+re.sub(r'\bvolatile\s+','',fragment)+text[b:]
    variants.append(('remove_volatile_'+match.group(1),s))
for tag,source in variants:
    if time.monotonic()-started>580:
        print('BUDGET_STOP',tag,flush=True);break
    r=evaluate('render',tag,source)
    if r.get('verified_exact'):
        print('RENDER_EXACT_CANDIDATE',tag,flush=True);break
print('SUMMARY',json.dumps({'trials':len(records),'verified_exact':[r['tag'] for r in records if r.get('verified_exact')],'renderer_top':sorted([(r['cost'],r['tag'],r['size'],r['diff_count']) for r in records if r['target']=='render' and 'cost' in r])[:15]}),flush=True)
