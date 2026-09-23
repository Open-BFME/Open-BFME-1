"""Targeted renderer experiments: vector expansion and per-call helper context.
Source-only mutations. No accepted-source, compiler binary, or gate modifications.
"""
from pathlib import Path
import hashlib,urllib.request
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
deadline=time.monotonic()+520
seed9=source_for([19,41]);seed16=source_for([19,29,35,40,41,53,58])
for tag,text,n in [('baseline9',seed9,9),('baseline16',seed16,16)]:
    r=evaluate((tag,text,None));accept(r,text);assert r.get('cost')==n and not r.get('relocation_drifts'),r
    print('BASELINE',tag,n,flush=True)

def add_helper(text,helper):return text.replace('void SegLineRendererClass::Render',helper+'\nvoid SegLineRendererClass::Render',1)
def helper_span(text,name):
    m=re.search(r'static\s+(?:WWINLINE|__forceinline)\s+[^\n]+?\b'+name+r'\([^\n]*\)\s*\{',text)
    assert m,name
    j=m.end();level=1
    while level:level+=(text[j]=='{')-(text[j]=='}');j+=1
    return m.start(),j

jobs=[]
# Return-value/copy lifetimes for the one remaining block in the 16-byte candidate.
forms=[
('return_by_value','static __forceinline Vector3 ExpandedTop(Vector3 a,const Vector3& d) {a+=d;return a;}','top = ExpandedTop(top,delta);'),
('return_by_value_swapped','static __forceinline Vector3 ExpandedTop(const Vector3& d,Vector3 a) {a+=d;return a;}','top = ExpandedTop(delta,top);'),
('copy_delta','static __forceinline Vector3 ExpandedTop(const Vector3& a,Vector3 d) {d+=a;return d;}','top = ExpandedTop(top,delta);'),
('copy_both','static __forceinline Vector3 ExpandedTop(Vector3 a,Vector3 d) {a+=d;return a;}','top = ExpandedTop(top,delta);'),
('local_copy','static __forceinline Vector3 ExpandedTop(const Vector3& a,const Vector3& d) {Vector3 result=a;result+=d;return result;}','top = ExpandedTop(top,delta);'),
('local_reverse','static __forceinline Vector3 ExpandedTop(const Vector3& a,const Vector3& d) {Vector3 result=d;result+=a;return result;}','top = ExpandedTop(top,delta);'),
('binary_reverse','','top = delta + top;'),
('reuse_delta','','{ Vector3 savedDelta=delta; delta+=top; top=delta; delta=savedDelta; }'),
('copy_then_add','','{ Vector3 originalTop=top; top=delta; top+=originalTop; }'),
('output_copy','static __forceinline void ExpandedTop(Vector3* result,Vector3 a,const Vector3& d) {a+=d;*result=a;}','ExpandedTop(&top,top,delta);'),
('output_const','static __forceinline void ExpandedTop(Vector3* result,const Vector3& a,const Vector3& d) {*result=a+d;}','ExpandedTop(&top,top,delta);')
]
for label,helper,call in forms:
    text=add_helper(seed16,helper).replace('top += delta;',call)
    jobs.append(('top_lifetime_'+label,text,None))
# Identical scalar additions with natural value/reference inputs, confined to expansion.
for lt,rt in itertools.product(['float','const float&','const float*'],repeat=2):
    for reverse in (False,True):
        for axes in [('X',),('X','Y','Z')]:
            le='*a' if '*' in lt else 'a';re_='*b' if '*' in rt else 'b'
            helper='static __forceinline float ExpansionAdd('+lt+' a,'+rt+' b) {return '+(re_+'+'+le if reverse else le+'+'+re_)+';}\n'
            body=''
            for axis in 'XYZ':
                if axis in axes:
                    aa=('&' if '*' in lt else '')+'top.'+axis
                    bb=('&' if '*' in rt else '')+'delta.'+axis
                    body+='top.'+axis+'=ExpansionAdd('+aa+','+bb+');'
                else:body+='top.'+axis+'+=delta.'+axis+';'
            for outer in (False,True):
                h=helper
                if outer:
                    h+='static __forceinline void ExpandTop(Vector3& top,const Vector3& delta) {'+body+'}\n';bodycall='ExpandTop(top,delta);'
                else:bodycall=body
                name='add_'+str(len(jobs))
                jobs.append((name,add_helper(seed16,h).replace('top += delta;',bodycall),None))
# Preserve the delta needed by bottom, but build native vector temporaries differently.
for declaration in [
'Vector3 delta(top.X-bottom.X,top.Y-bottom.Y,top.Z-bottom.Z);',
'Vector3 delta; delta.X=top.X-bottom.X;delta.Y=top.Y-bottom.Y;delta.Z=top.Z-bottom.Z;',
'Vector3 delta(top); delta-=bottom;',
'const Vector3 initialDelta=top-bottom; Vector3 delta(initialDelta);',
'Vector3 delta = top; delta -= bottom;'
]:
    jobs.append(('delta_'+str(len(jobs)),seed16.replace('Vector3 delta = top - bottom;',declaration),None))
for parameter in ['float factor','const float& factor']:
    for body in ['value*=factor;return value;','value.X*=factor;value.Y*=factor;value.Z*=factor;return value;','value = value*factor;return value;']:
        helper='static __forceinline Vector3& ScaleSegLineExpansion(Vector3& value,'+parameter+') {'+body+'}'
        a,z=helper_span(seed16,'ScaleSegLineExpansion')
        jobs.append(('scale_'+str(len(jobs)),seed16[:a]+helper+seed16[z:],None))
batch(jobs)
# Distinct inline copies for actual call sites: never add a new volatile read.
# The helpers are shared by different endpoint/interior contexts in the saved bank.
jobs=[]
for lane,seed in [('nine',seed9),('sixteen',seed16)]:
    for name in ['SegLineStartSignXZ','DotSegLineTopPlaneYXZ','DotSegLineLastTopSequential','SegLineTopSignSequential']:
        a,z=helper_span(seed,name);definition=seed[a:z]
        uses=[m for m in re.finditer(r'\b'+name+r'\(',seed) if m.start()>z]
        vpos=list(re.finditer(r'\bvolatile\s+',definition))
        for use_index,use in enumerate(uses):
            for removal in range(1<<len(vpos)):
                clone=definition
                for i in reversed(range(len(vpos))):
                    if removal&(1<<i):clone=clone[:vpos[i].start()]+clone[vpos[i].end():]
                newname=name+'AtSite'+str(use_index)
                clone=clone.replace(name,newname,1)
                for inline_kind in ('keep','force'):
                    d=clone.replace('WWINLINE','__forceinline') if inline_kind=='force' else clone
                    t=seed[:use.start()]+newname+seed[use.start()+len(name):]
                    t=add_helper(t,d)
                    jobs.append(('site_'+lane+'_'+name+'_'+str(use_index)+'_'+str(removal)+'_'+inline_kind,t,None))
# Parallel-test dot input lifetimes, leaving the other native dot sites untouched.
dot='Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge])'
for left,right in itertools.product(['const Vector3&','const Vector3'],repeat=2):
    for reverse in (False,True):
        body=left+' a=prev_seg->EdgePlane[edge];'+right+' b=next_seg->EdgePlane[edge]; vdp=Vector3::Dot_Product('+('b,a' if reverse else 'a,b')+');'
        jobs.append(('dot_lifetime_'+str(len(jobs)),seed9.replace('vdp = '+dot+';','{'+body+'}'),None))
batch(jobs)
# Recheck the best candidate with all relocation operands resolved, plus sibling checks.
selected=best_text
r=evaluate(('final_recheck',selected,None));accept(r,selected)
row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':(OUT/'final_recheck.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
p=build.compile_function(row,symbols,OUT/'final_recheck.obj',retain_compiled=True)
r.update(resolved_diffs=sum(a!=b for a,b in zip(retail,p['bytes'])),unresolved=p['unresolved'],masked=p['masked'],resolved_sha256=sha(p['bytes']),boundary_issue=build.claimed_boundary_issue(p['compiled'],SIZE,p['relocs']))
r['verified_exact']=p['bytes']==retail and r['size']==SIZE and not r['unresolved'] and not r['masked'] and not r['boundary_issue']
(OUT/'final_recheck.json').write_text(json.dumps(r,indent=2),encoding='utf-8')
checks=[]
for old in json.loads((ROOT/'reverse/attempt_support/0x00960a30-verification.json').read_text())['canonical_sibling_checks']:
    sr=dict(row,name=old['symbol'],target_rva=old['rva'],target_size=str(old['size']))
    try:
        q=build.compile_function(sr,symbols,OUT/'final_recheck.obj',retain_compiled=True)
        checks.append(dict(old,exact=q['bytes']==build.read_target_bytes(int(old['rva'],16),old['size']) and not q['masked'] and not q['unresolved']))
    except (Exception,SystemExit) as exc:checks.append(dict(old,exact=False,error=str(exc)))
(OUT/'renderer_siblings.json').write_text(json.dumps(checks,indent=2),encoding='utf-8')
print('FINAL',json.dumps({k:v for k,v in r.items() if k not in ('raw_hex','retail_hex','relocation_tuples')}),flush=True)
print('SIBLINGS',json.dumps(checks),flush=True)
print('CLOSEST',json.dumps([{k:x.get(k) for k in ('tag','cost','volatile_tokens','offsets','code_sha256')} for x in sorted((x for x in records if 'cost' in x and not x.get('relocation_drifts')),key=lambda x:x['cost'])[:30]]),flush=True)
print('SUMMARY',json.dumps({'trials':len(records),'best_cost':best['cost'],'exact':r['verified_exact']}),flush=True)
