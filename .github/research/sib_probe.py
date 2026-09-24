"""Targeted final-nine renderer search.
Only source-shape experiments on the isolated research branch.
"""
from pathlib import Path
import hashlib, urllib.request, itertools, re, json, time
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
deadline=time.monotonic()+520
seed=source_for([19,41])
base=evaluate(('baseline9',seed,None)); accept(base,seed)
assert base.get('cost')==9 and not base.get('relocation_drifts'),base
print('BASELINE9',json.dumps({k:base.get(k) for k in ('cost','offsets','code_sha256')}),flush=True)

def add_helper(text,helper):
    return text.replace('void SegLineRendererClass::Render',helper+'\nvoid SegLineRendererClass::Render',1)

jobs=[]
# 1) The two-byte merge-classification X-product residue.
needle='vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);'
for order in [
    '(a.Z*b.Z+a.Y*b.Y)+a.X*b.X',
    '(a.Z*b.Z+a.Y*b.Y)+b.X*a.X',
    '(a.Y*b.Y+a.Z*b.Z)+a.X*b.X',
    'a.Z*b.Z+(a.Y*b.Y+a.X*b.X)',
]:
  for vol in ['none','ax','bx','bothx','ay','by']:
    expr=order
    repl={'ax':'*(const volatile float*)&a.X','bx':'*(const volatile float*)&b.X',
          'ay':'*(const volatile float*)&a.Y','by':'*(const volatile float*)&b.Y'}
    if vol in ('ax','bothx'): expr=expr.replace('a.X',repl['ax'])
    if vol in ('bx','bothx'): expr=expr.replace('b.X',repl['bx'])
    if vol=='ay': expr=expr.replace('a.Y',repl['ay'])
    if vol=='by': expr=expr.replace('b.Y',repl['by'])
    helper='static __forceinline float FinalMergeDot(const Vector3& a,const Vector3& b) { return '+expr+'; }'
    t=add_helper(seed,helper).replace(needle,'vdp = FinalMergeDot(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);')
    jobs.append(('merge_dot_'+str(len(jobs)),t,None))

# 2) The final top-only dot: alter only X operand materialization while retaining Y-Z-X grouping.
old="""top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y
    + points[pidx].Z * top_dir.Z) + points[pidx].X * top_dir.X);"""
for xexpr in [
    'points[pidx].X * top_dir.X',
    'top_dir.X * points[pidx].X',
    '*(const volatile float *)&points[pidx].X * top_dir.X',
    'points[pidx].X * *(const volatile float *)&top_dir.X',
    '*(const volatile float *)&top_dir.X * points[pidx].X',
    'top_dir.X * *(const volatile float *)&points[pidx].X',
]:
  for helper in (False,True):
    expr='((*(const volatile float *)&points[pidx].Y * top_dir.Y + points[pidx].Z * top_dir.Z) + '+xexpr+')'
    if helper:
      h='static __forceinline float FinalTopDotX(const Vector3& p,const Vector3& d) { return ((*(const volatile float *)&p.Y*d.Y+p.Z*d.Z)+'+xexpr.replace('points[pidx]','p').replace('top_dir','d')+'); }'
      t=add_helper(seed,h).replace(old,'top = top_dir * FinalTopDotX(points[pidx], top_dir);')
    else:
      t=seed.replace(old,'top = top_dir * '+expr+';')
    jobs.append(('final_top_'+str(len(jobs)),t,None))

# 3) Address-encoding residues in output writes. Change one block at a time.
blocks=[
"""vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[top_int_idx][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;""",
"""vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[bottom_int_idx][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;""",
]
# same text occurs in multiple control-flow sites; mutate each occurrence separately.
occurrences=[]
for bi,blk in enumerate(blocks):
    start=0
    while True:
        pos=seed.find(blk,start)
        if pos<0: break
        occurrences.append((bi,pos,blk))
        start=pos+1

def replace_nth(text, old, new, nth):
    start=0
    for i in range(nth+1):
        pos=text.find(old,start)
        if pos<0:return text
        if i==nth:return text[:pos]+new+text[pos+len(old):]
        start=pos+1
    return text

for bi,blk in enumerate(blocks):
  count=seed.count(blk)
  for nth in range(count):
    for mode in range(8):
      val='top' if bi==0 else 'bottom'
      idx='0' if bi==0 else '1'
      if mode==0:
        head='VertexFormatXYZDUV1 *out = vArray + vidx;'
      elif mode==1:
        head='VertexFormatXYZDUV1 *out = &vArray[vidx];'
      elif mode==2:
        head='VertexFormatXYZDUV1 &out = vArray[vidx];'
      elif mode==3:
        head='VertexFormatXYZDUV1 *out = (VertexFormatXYZDUV1 *)((char*)vArray + vidx * sizeof(VertexFormatXYZDUV1));'
      elif mode==4:
        head='VertexFormatXYZDUV1 *out = (VertexFormatXYZDUV1 *)((unsigned)vArray + vidx * sizeof(VertexFormatXYZDUV1));'
      elif mode==5:
        head='unsigned outOffset = vidx * sizeof(VertexFormatXYZDUV1); VertexFormatXYZDUV1 *out=(VertexFormatXYZDUV1 *)((unsigned)vArray+outOffset);'
      elif mode==6:
        head='unsigned outBase=(unsigned)vArray; VertexFormatXYZDUV1 *out=(VertexFormatXYZDUV1 *)(outBase+vidx*sizeof(VertexFormatXYZDUV1));'
      else:
        head='VertexFormatXYZDUV1 *out=vArray; out += vidx;'
      arrow='.' if mode==2 else '->'
      repl=head+'\n'+'\n'.join([
        'out'+arrow+'x = '+val+'.X;',
        'out'+arrow+'y = '+val+'.Y;',
        'out'+arrow+'z = '+val+'.Z;',
        'out'+arrow+'diffuse = DX8Wrapper::Convert_Color(intersection['+('top_int_idx' if bi==0 else 'bottom_int_idx')+']['+('TOP_EDGE' if bi==0 else 'BOTTOM_EDGE')+'].RGBA);',
        'out'+arrow+'u1 = u_values['+idx+'] + uv_offset.X;',
        'out'+arrow+'v1 = intersection['+('top_int_idx' if bi==0 else 'bottom_int_idx')+']['+('TOP_EDGE' if bi==0 else 'BOTTOM_EDGE')+'].TexV + uv_offset.Y;'
      ])
      t=replace_nth(seed,blk,repl,nth)
      jobs.append(('out_b'+str(bi)+'_n'+str(nth)+'_m'+str(mode),t,None))

# 4) Narrow pointer/address alternatives only for xyz stores, leaving color/UV shape intact.
for val in ('top','bottom'):
  for mode in range(5):
    old3='vArray[vidx].x = '+val+'.X;\nvArray[vidx].y = '+val+'.Y;\nvArray[vidx].z = '+val+'.Z;'
    for nth in range(seed.count(old3)):
      if mode==0:
        repl='VertexFormatXYZDUV1 *xyz=&vArray[vidx]; xyz->x='+val+'.X; xyz->y='+val+'.Y; xyz->z='+val+'.Z;'
      elif mode==1:
        repl='VertexFormatXYZDUV1 *xyz=vArray+vidx; xyz->x='+val+'.X; xyz->y='+val+'.Y; xyz->z='+val+'.Z;'
      elif mode==2:
        repl='float *xyz=(float*)&vArray[vidx]; xyz[0]='+val+'.X; xyz[1]='+val+'.Y; xyz[2]='+val+'.Z;'
      elif mode==3:
        repl='float *xyz=(float*)((unsigned)vArray+vidx*sizeof(VertexFormatXYZDUV1)); xyz[0]='+val+'.X; xyz[1]='+val+'.Y; xyz[2]='+val+'.Z;'
      else:
        repl='unsigned xyzaddr=(unsigned)vArray+vidx*sizeof(VertexFormatXYZDUV1); *(float*)(xyzaddr+0)='+val+'.X; *(float*)(xyzaddr+4)='+val+'.Y; *(float*)(xyzaddr+8)='+val+'.Z;'
      t=replace_nth(seed,old3,repl,nth)
      jobs.append(('xyz_'+val+'_'+str(nth)+'_'+str(mode),t,None))

batch(jobs)

# Greedy combine only mutations that improve the nine-byte baseline and keep zero reloc drift.
improved=sorted((r for r in records if r.get('cost',99)<9 and not r.get('relocation_drifts')),key=lambda r:(r['cost'],r.get('volatile_tokens',999)))
print('IMPROVED',json.dumps([{k:r.get(k) for k in ('tag','cost','offsets','code_sha256')} for r in improved[:25]]),flush=True)
if improved:
    best_r=improved[0]; best_src=sources[best_r['tag']]
    # Re-run individual families on top of the best source.
    second=[]
    for tag,text,_ in jobs:
        # derive replacement by line-level delta against seed when practical
        # and skip large multi-region rewrites that cannot be safely composed.
        if tag.startswith(('merge_dot_','final_top_')):
            if tag.startswith('merge_dot_'):
                candidate=text
                # transplant helper+call by extracting the changed merge statement and helper.
                hm=re.search(r'static __forceinline float FinalMergeDot.*?\}',candidate,re.S)
                if hm and 'FinalMergeDot' not in best_src:
                    x=add_helper(best_src,hm.group(0)).replace(needle,re.search(r'vdp = FinalMergeDot[^;]+;',candidate).group(0))
                    second.append(('combine_'+tag,x,None))
            else:
                hm=re.search(r'static __forceinline float FinalTopDotX.*?\}',text,re.S)
                if hm:
                    x=add_helper(best_src,hm.group(0)).replace(old,re.search(r'top = top_dir \* FinalTopDotX[^;]+;',text).group(0))
                else:
                    newstmt=re.search(r'top = top_dir \* \(\(.*?\);',text,re.S)
                    x=best_src.replace(old,newstmt.group(0)) if newstmt else best_src
                second.append(('combine_'+tag,x,None))
    batch(second)

selected=best_text
r=evaluate(('final_recheck',selected,None)); accept(r,selected)
row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':(OUT/'final_recheck.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
p=build.compile_function(row,symbols,OUT/'final_recheck.obj',retain_compiled=True)
r.update(resolved_diffs=sum(a!=b for a,b in zip(retail,p['bytes'])),unresolved=p['unresolved'],masked=p['masked'],resolved_sha256=sha(p['bytes']),boundary_issue=build.claimed_boundary_issue(p['compiled'],SIZE,p['relocs']))
r['verified_exact']=p['bytes']==retail and r['size']==SIZE and not r['unresolved'] and not r['masked'] and not r['boundary_issue']
(OUT/'final_recheck.json').write_text(json.dumps(r,indent=2),encoding='utf-8')
print('FINAL',json.dumps({k:v for k,v in r.items() if k not in ('raw_hex','retail_hex','relocation_tuples')}),flush=True)
print('SUMMARY',json.dumps({'trials':len(records),'best_cost':best['cost'],'exact':r['verified_exact']}),flush=True)
