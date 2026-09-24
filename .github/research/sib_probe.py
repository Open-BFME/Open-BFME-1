"""Alias/provenance experiments for the final-nine SegLineRenderer candidate."""
from pathlib import Path
import hashlib,urllib.request,json,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41]);r=evaluate(('baseline9',seed,None));accept(r,seed);assert r.get('cost')==9
jobs=[]
decl='VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);'
variants=[
 'VertexFormatXYZDUV1 * __restrict vArray = getVertexBuffer(vnum);',
 'VertexFormatXYZDUV1 *__restrict vArray = getVertexBuffer(vnum);',
 'VertexFormatXYZDUV1 * const vArray = getVertexBuffer(vnum);',
 'register VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);',
 'VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum); _ReadWriteBarrier();',
 'VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum); _ReadBarrier();',
]
for i,x in enumerate(variants):jobs.append(('vptr_'+str(i),seed.replace(decl,x,1),None))

# Index lifetime/type hints
for typ in ['register unsigned int','unsigned long','register unsigned long','int','register int']:
 t=seed.replace('unsigned int vidx = 0;',typ+' vidx = 0;',1)
 jobs.append(('vidx_'+typ.replace(' ','_'),t,None))
for typ in ['register unsigned int','unsigned long','register unsigned long','int','register int']:
 t=seed.replace('unsigned int top_int_idx = 1;',typ+' top_int_idx = 1;',1).replace('unsigned int bottom_int_idx = 1;',typ+' bottom_int_idx = 1;',1)
 jobs.append(('iidx_'+typ.replace(' ','_'),t,None))

# Keep vArray in a tiny wrapper object; operator[] remains ordinary C++.
helper_variants=[
 '''struct FinalVertexArray { VertexFormatXYZDUV1 *p; __forceinline VertexFormatXYZDUV1& operator[](unsigned i) const { return p[i]; } };''',
 '''struct FinalVertexArray { VertexFormatXYZDUV1 *p; __forceinline VertexFormatXYZDUV1& at(unsigned i) const { return *(p+i); } };''',
 '''struct FinalVertexArray { VertexFormatXYZDUV1 *p; __forceinline VertexFormatXYZDUV1* at(unsigned i) const { return p+i; } };''',
]
for i,h in enumerate(helper_variants):
 t=seed.replace('void SegLineRendererClass::Render',h+'\nvoid SegLineRendererClass::Render',1)
 if i==0:
  t=t.replace(decl,'FinalVertexArray va = { getVertexBuffer(vnum) }; VertexFormatXYZDUV1 *vArray=va.p;',1)
  # mutate only output phase vArray subscripts, but not getVertexBuffer implementation later
  pos=t.index('FinalVertexArray va')
  end=t.index('SortingRendererClass::Insert_Triangles',pos)
  mid=t[pos:end].replace('vArray[vidx]','va[vidx]')
  t=t[:pos]+mid+t[end:]
 elif i==1:
  t=t.replace(decl,'FinalVertexArray va = { getVertexBuffer(vnum) }; VertexFormatXYZDUV1 *vArray=va.p;',1)
  pos=t.index('FinalVertexArray va');end=t.index('SortingRendererClass::Insert_Triangles',pos)
  mid=t[pos:end].replace('vArray[vidx]','va.at(vidx)')
  t=t[:pos]+mid+t[end:]
 else:
  t=t.replace(decl,'FinalVertexArray va = { getVertexBuffer(vnum) }; VertexFormatXYZDUV1 *vArray=va.p;',1)
  pos=t.index('FinalVertexArray va');end=t.index('SortingRendererClass::Insert_Triangles',pos)
  mid=t[pos:end]
  for field in ['x','y','z','diffuse','u1','v1']:
   mid=mid.replace('vArray[vidx].'+field,'va.at(vidx)->'+field)
  t=t[:pos]+mid+t[end:]
 jobs.append(('wrapper_'+str(i),t,None))

# Alias-contract on member definition. Attribute syntax may be unsupported in VC7;
# failed compiles are useful and isolated.
for spelling in [
 'VertexFormatXYZDUV1 * __declspec(restrict) SegLineRendererClass::getVertexBuffer(unsigned int number)',
 '__declspec(restrict) VertexFormatXYZDUV1 *SegLineRendererClass::getVertexBuffer(unsigned int number)',
 'VertexFormatXYZDUV1 *__restrict SegLineRendererClass::getVertexBuffer(unsigned int number)',
]:
 old='VertexFormatXYZDUV1 *SegLineRendererClass::getVertexBuffer(unsigned int number)'
 if old in seed: jobs.append(('retalias_'+str(len(jobs)),seed.replace(old,spelling,1),None))

# Barrier placement immediately before only the output stores: perturb optimizer IR but
# leave arithmetic source and storage layout unchanged.
markers=['vArray[vidx].x = top.X;','vArray[vidx].x = bottom.X;']
for marker in markers:
 count=seed.count(marker)
 for nth in range(count):
  start=0
  for _ in range(nth+1): pos=seed.find(marker,start);start=pos+1
  for bar in ['_ReadWriteBarrier(); ','_WriteBarrier(); ']:
   t=seed[:pos]+bar+seed[pos:]
   jobs.append(('bar_'+('top' if 'top' in marker else 'bottom')+'_'+str(nth)+'_'+bar[1:5],t,None))

batch(jobs)
print('TOP',json.dumps([{k:x.get(k) for k in ('tag','cost','offsets','code_sha256','error')} for x in sorted(records,key=lambda x:x.get('cost',999))[:20]]),flush=True)
r=evaluate(('final_recheck',best_text,None));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256','verified_exact')}),flush=True)
