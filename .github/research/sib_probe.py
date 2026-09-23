"""Isolated compiler experiments. No source ledger or master writes.
All comparisons are diagnostics until normal identity and integration gates pass.
"""
from pathlib import Path
import hashlib, json, re, subprocess, sys, time, itertools
ROOT=Path.cwd()
sys.path.insert(0,str(ROOT/'tools'))
import build, probe
OUT=ROOT/'build'/'sib_research_20260923'
OUT.mkdir(parents=True,exist_ok=True)
records=[]
baselines={}
SPECS={
 'view':(0x0045C2F0,229,'?getScreenCornerWorldPointsAtZ@View@@UAEXPAUCoord3D@@000M@Z'),
 'render':(0x00960A30,14081,'?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z')}

def sha(data): return hashlib.sha256(data).hexdigest()
def evaluate(target,tag,text,details=False):
    rva,size,symbol=SPECS[target]
    retail=build.read_target_bytes(rva,size)
    path=OUT/(tag+'.cpp'); obj=OUT/(tag+'.obj')
    path.write_text(text,encoding='utf-8',newline='\n')
    obj.unlink(missing_ok=True)
    start=time.monotonic()
    ok,output,code=build.try_compile_source(path,obj)
    rec={'target':target,'tag':tag,'returncode':code,'seconds':round(time.monotonic()-start,4),'source_sha256':sha(text.encode())}
    if not ok:
        rec['error']=output[-3500:]
    else:
        try:
            data,relocs=build.read_object_symbol_bytes(obj,symbol)
            data=data.rstrip(b'\xcc')
            ret_raw,our_raw,ret_norm,our_norm,rb,ob,drifts=probe.diagnostic_streams(retail,data,relocs)
            diffs=[i for i,(a,b) in enumerate(zip(rb,ob)) if a!=b]
            rec.update(size=len(data),diff_count=len(diffs),length_delta=len(data)-size,relocations=len(relocs),relocation_drifts=len(drifts),offsets=diffs[:60],code_sha256=sha(data),retail_sha256=sha(retail),raw_exact=data==retail,diagnostic_exact=rb==ob and not drifts)
            if target in baselines:
                base_data,base_rel=baselines[target]
                rec.update(same_relocations=relocs==base_rel,changed_from_baseline=sum(a!=b for a,b in zip(base_data,data))+abs(len(base_data)-len(data)))
            else: baselines[target]=(data,relocs)
            if details or rec['diagnostic_exact'] or (target=='render' and rec['diff_count']<51 and rec['size']==size):
                rec['all_offsets']=diffs
                rec['relocation_tuples']=relocs
                if target=='view': rec['raw_hex']=data.hex()
                (OUT/(tag+'.asm.txt')).write_text('\n'.join(f'{x.address:04x} {bytes(x.bytes).hex()} {x.mnemonic} {x.op_str}' for x in our_raw),encoding='utf-8')
            (OUT/(tag+'.json')).write_text(json.dumps(rec,indent=2),encoding='utf-8')
        except Exception as exc: rec['error']=type(exc).__name__+': '+str(exc)
    records.append(rec)
    print('RESULT',json.dumps({k:v for k,v in rec.items() if k not in ('relocation_tuples','all_offsets','raw_hex')}),flush=True)
    (OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
    return rec

print('PHASE View reproduction and constructor ablation',flush=True)
original=(ROOT/'reverse/attempts/0x0045c2f0.cpp').read_text(encoding='utf-8')
clean=re.sub(r'^\s*volatile char \*viewWidthPointer = .*?;\s*$', '', original,flags=re.M)
clean=clean.replace('(Int)(origin.x + (unsigned)viewWidthPointer)','origin.x + viewWidth')
evaluate('view','view_original',original,True)
constructors={
 'plain':'',
 'default_only':'ICoord2D() {}',
 'default_copy':'ICoord2D() {} ICoord2D(const ICoord2D& o):x(o.x),y(o.y) {}',
 'default_assign':'ICoord2D() {} ICoord2D& operator=(const ICoord2D& o) {x=o.x;y=o.y;return *this;}',
 'default_destructor':'ICoord2D() {} ~ICoord2D() {}',
 'copy_declared':'ICoord2D() {} ICoord2D(const ICoord2D&);',
 'ctor_two_ints':'ICoord2D() {} ICoord2D(Int a,Int b):x(a),y(b) {}',
 'default_outofclass':'ICoord2D();'}
for label,body in constructors.items():
    text=clean.replace('Int y;\n};','Int y;\n '+body+'\n};',1)
    if label=='default_outofclass': text=text.replace('struct Coord3D','inline ICoord2D::ICoord2D() {}\nstruct Coord3D',1)
    for run in range(3 if label in ('plain','default_only','default_copy') else 1):
        evaluate('view','view_'+label+'_'+str(run),text)
# Preserve canonical POD type; give only function-local storage a real constructor.
for use in ('all','corners','origin'):
    text=clean.replace('class View','struct ScreenPoint : ICoord2D { ScreenPoint() {} };\nclass View',1)
    if use in ('all','corners'): text=text.replace('ICoord2D screenTopLeft','ScreenPoint screenTopLeft')
    if use in ('all','origin'): text=text.replace('ICoord2D origin;','ScreenPoint origin;')
    evaluate('view','view_local_storage_'+use,text)

print('PHASE Fetch renderer headers in ephemeral runner',flush=True)
subprocess.run(['git','sparse-checkout','add','Code/Libraries','reference/shims','reference/CnC_Generals_Zero_Hour/GeneralsMD/Code','vendor/stlport'],cwd=ROOT,check=True,timeout=240)
text=(ROOT/'reverse/attempts/0x00960a30.cpp').read_text(encoding='utf-8')
text=text.replace('#include "../attempt_support/0x00960a30.inc"','#include "../../reverse/attempt_support/0x00960a30.inc"')
base=evaluate('render','render_baseline',text,True)
if 'error' in base: raise SystemExit('Renderer baseline must compile before drawing conclusions')
ls={
 'none':'',
 'default':'LineSegment() {}',
 'copy':'LineSegment() {} LineSegment(const LineSegment& o):StartPlane(o.StartPlane) {EdgePlane[0]=o.EdgePlane[0];EdgePlane[1]=o.EdgePlane[1];}',
 'dtor':'~LineSegment() {}'}
li={
 'none':'',
 'default':'LineSegmentIntersection() {}',
 'copy':'LineSegmentIntersection() {} LineSegmentIntersection(const LineSegmentIntersection& o):PointCount(o.PointCount),NextSegmentID(o.NextSegmentID),Direction(o.Direction),Point(o.Point),TexV(o.TexV),RGBA(o.RGBA),Fold(o.Fold),Parallel(o.Parallel) {}',
 'dtor':'~LineSegmentIntersection() {}'}
for an,a in ls.items():
    for bn,b in li.items():
        if an==bn=='none': continue
        candidate=text.replace('struct LineSegment {','struct LineSegment {\n'+a,1).replace('struct LineSegmentIntersection  {','struct LineSegmentIntersection  {\n'+b,1)
        evaluate('render','render_segment_'+an+'_intersection_'+bn,candidate)
# Record whether removing forced volatility alone improves canonical codegen.
no_volatile=re.sub(r'\bvolatile\s+', '', text)
evaluate('render','render_no_volatile',no_volatile)
for typ,ctor in [('LineSegment','LineSegment() {}'),('LineSegmentIntersection','LineSegmentIntersection() {}')]:
    candidate=re.sub(r'(struct '+typ+r'\s*\{)',r'\1\n'+ctor,no_volatile,count=1)
    evaluate('render','render_no_volatile_'+typ,candidate)
print('SUMMARY',json.dumps({'trials':len(records),'raw_exact':[r['tag'] for r in records if r.get('raw_exact')],'renderer_best':sorted([(r['diff_count']+2*abs(r['length_delta']),r['tag'],r['size'],r['diff_count']) for r in records if r['target']=='render' and 'diff_count' in r])[:8]}),flush=True)
