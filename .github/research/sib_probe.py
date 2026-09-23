"""Scoped View and SegLineRenderer compiler tests, diagnostic only.
No ledger, shared header, game source or acceptance-rule modifications.
"""
from pathlib import Path
import hashlib, json, re, subprocess, sys, time
ROOT=Path.cwd(); sys.path.insert(0,str(ROOT/'tools'))
import build, probe
OUT=ROOT/'build'/'sib_research_20260923'; OUT.mkdir(parents=True,exist_ok=True)
subprocess.run(['git','sparse-checkout','add','Code/Libraries','Code/GameEngine','reference/shims','reference/CnC_Generals_Zero_Hour/GeneralsMD/Code','vendor/stlport'],cwd=ROOT,check=True,timeout=240)
SPECS={'view':(0x0045C2F0,229,'?getScreenCornerWorldPointsAtZ@View@@UAEXPAUCoord3D@@000M@Z'),'render':(0x00960A30,14081,'?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z')}
records=[]; baselines={}; symbol_map=build.load_symbol_map()
def sha(data): return hashlib.sha256(data).hexdigest()
def evaluate(target,tag,text,strict=False):
    rva,size,symbol=SPECS[target]; retail=build.read_target_bytes(rva,size)
    path=OUT/(tag+'.cpp'); obj=OUT/(tag+'.obj'); path.write_text(text,encoding='utf-8',newline='\n'); obj.unlink(missing_ok=True)
    start=time.monotonic(); ok,output,code=build.try_compile_source(path,obj)
    rec={'target':target,'tag':tag,'returncode':code,'seconds':round(time.monotonic()-start,4),'source_sha256':sha(text.encode())}
    if not ok: rec['error']=output[-2400:]
    else:
        try:
            data,relocs=build.read_object_symbol_bytes(obj,symbol); data=data.rstrip(b'\xcc')
            _,ours,_,_,rb,ob,drifts=probe.diagnostic_streams(retail,data,relocs)
            diffs=[i for i,(a,b) in enumerate(zip(rb,ob)) if a!=b]
            rec.update(size=len(data),diff_count=len(diffs),length_delta=len(data)-size,relocations=len(relocs),relocation_drifts=len(drifts),offsets=diffs,code_sha256=sha(data),retail_sha256=sha(retail),raw_exact=data==retail)
            rec['cost']=len(diffs)+2*abs(len(data)-size)
            if target in baselines:
                bd,br=baselines[target];rec.update(same_relocations=relocs==br,changed_from_baseline=sum(a!=b for a,b in zip(bd,data))+abs(len(bd)-len(data)))
            else: baselines[target]=(data,relocs)
            if strict or (len(data)==size and not diffs and not drifts):
                row={'name':symbol,'target_rva':hex(rva),'target_size':str(size),'source':path.relative_to(ROOT).as_posix(),'status':'matched','notes':''}
                patch=build.compile_function(row,symbol_map,obj,retain_compiled=True)
                rec.update(resolved_diffs=sum(a!=b for a,b in zip(retail,patch['bytes'])),unresolved=patch['unresolved'],masked=patch['masked'],resolved_sha256=sha(patch['bytes']),boundary_issue=build.claimed_boundary_issue(patch['compiled'],size,patch['relocs']))
                rec['verified_exact']=patch['bytes']==retail and not patch['masked'] and not patch['unresolved'] and len(data)==size and not drifts and rec['boundary_issue'] is None
            if strict or (target=='render' and rec['cost']<51):
                rec['relocation_tuples']=relocs
                (OUT/(tag+'.asm.txt')).write_text('\n'.join(f'{x.address:04x} {bytes(x.bytes).hex()} {x.mnemonic} {x.op_str}' for x in ours),encoding='utf-8')
        except (Exception,SystemExit) as exc:rec['error']=type(exc).__name__+': '+str(exc)
    records.append(rec); (OUT/(tag+'.json')).write_text(json.dumps(rec,indent=2),encoding='utf-8'); (OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
    print('RESULT',json.dumps({k:v for k,v in rec.items() if k not in ('relocation_tuples','offsets')}),flush=True)
    return rec

original=(ROOT/'reverse/attempts/0x0045c2f0.cpp').read_text(encoding='utf-8')
clean=re.sub(r'^\s*volatile char \*viewWidthPointer = .*?;\s*$', '', original,flags=re.M).replace('(Int)(origin.x + (unsigned)viewWidthPointer)','origin.x + viewWidth')
local=clean.replace('ICoord2D origin;','struct ScreenOrigin : ICoord2D { ScreenOrigin() {} };\n\tScreenOrigin origin;')
evaluate('view','view_bank',original,True)
evaluate('view','view_local_origin',local,True)
canonical=re.sub(r'typedef\s+int\s+Int;[\s\S]*?(?=class View)', '#include "Lib/BaseType.h"\n',local,count=1)
canonical=canonical.replace('// cl: /DNDEBUG /MD /EHsc','// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include')
evaluate('view','view_canonical_coordinates',canonical,True)
fullview=re.sub(r'class View\s*\{[\s\S]*?\};','#include "GameClient/View.h"',canonical,count=1)
fullview=fullview.replace('// cl: /DNDEBUG /MD /EHsc','// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas')
evaluate('view','view_canonical_owner',fullview,True)
production=(ROOT/'Code/GameEngine/Source/GameClient/View.cpp').read_text(encoding='utf-8')
evaluate('view','view_native_original',production)
evaluate('view','view_native_constructed_origin',production.replace('ICoord2D origin;','struct ScreenOrigin : ICoord2D { ScreenOrigin() {} };\n\tScreenOrigin origin;'),True)

text=(ROOT/'reverse/attempts/0x00960a30.cpp').read_text(encoding='utf-8').replace('#include "../attempt_support/0x00960a30.inc"','#include "../../reverse/attempt_support/0x00960a30.inc"')
evaluate('render','render_baseline',text,True)
# Native value types and bounded containers, all preserving layout and arithmetic.
edge_pattern=r'enum SegmentEdge\s*\{([\s\S]*?)\};'
for base in ('int','unsigned int'):
    for ctor in ('{}',':value(0) {}'):
        cls='class SegmentEdge { '+base+' value; public: SegmentEdge() '+ctor+' SegmentEdge(int v):value(v) {} operator int() const { return value; } };'
        t=re.sub(edge_pattern,lambda m:'enum {'+m.group(1)+'};\n'+cls,text,count=1)
        evaluate('render','render_typed_edge_'+base.replace(' ','_')+('_zero' if 'value' in ctor else '_empty'),t)
# Edge planes behind a pair with a normal subscript operator.
for arg in ('int','unsigned int'):
    for ctor in ('','EdgePlanePair() {}'):
        decl='struct EdgePlanePair { Vector3 values[NUM_EDGES]; '+ctor+' Vector3& operator[]('+arg+' i) { return values[i]; } const Vector3& operator[]('+arg+' i) const { return values[i]; } };\n'
        t=text.replace('struct LineSegment {',decl+'struct LineSegment {',1)
        t=re.sub(r'Vector3\s+EdgePlane\[NUM_EDGES\];','EdgePlanePair EdgePlane;',t,count=1)
        evaluate('render','render_edge_pair_'+arg.replace(' ','_')+('_ctor' if ctor else '_implicit'),t)
# Constructed scalar buffer: no initialization stores are added.
for variable,length,kind in [('base_tex_v','MAX_SEGLINE_POINT_BUFFER_SIZE','float'),('subdiv_tex_v','MAX_SEGLINE_POINT_BUFFER_SIZE','float'),('u_values','2','float'),('num_intersections','NUM_EDGES','unsigned int')]:
    name='Buffer_'+variable
    definition='struct '+name+' { '+kind+' data['+length+']; '+name+'() {} operator '+kind+'*() {return data;} '+kind+'& operator[](unsigned i) {return data[i];} };\n'+name+' '+variable+';'
    t=re.sub(r'\b'+re.escape(kind)+r'\s+'+variable+r'\['+length+r'\];',definition,text,count=1)
    assert t!=text,variable
    evaluate('render','render_buffer_'+variable,t)
# A typed view of the existing output vertex buffer; storage remains one pointer.
for arg in ('int','unsigned int'):
    definition='struct VertexArrayView { VertexFormatXYZDUV1 *data; VertexArrayView(VertexFormatXYZDUV1 *p):data(p) {} VertexFormatXYZDUV1& operator[]('+arg+' i) {return data[i];} };\nVertexArrayView vArray(getVertexBuffer(vnum));'
    t=text.replace('VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);',definition)
    evaluate('render','render_vertex_view_'+arg.replace(' ','_'),t)
print('SUMMARY',json.dumps({'trials':len(records),'verified_exact':[r['tag'] for r in records if r.get('verified_exact')],'renderer_top':sorted([(r['cost'],r['tag'],r['size'],r['diff_count']) for r in records if r['target']=='render' and 'cost' in r])[:10]}),flush=True)
