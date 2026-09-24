"""TU-local member-boundary experiments for final-nine renderer bytes."""
from pathlib import Path
import hashlib,urllib.request,json,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41]);r=evaluate(('baseline9',seed,None));accept(r,seed);assert r.get('cost')==9
jobs=[]

# Member-style vertex writers: same field stores, no out-of-line calls.
helpers=[
'''struct FinalVertexWriter { VertexFormatXYZDUV1 *p; __forceinline void xyz(unsigned i,float x,float y,float z) { p[i].x=x; p[i].y=y; p[i].z=z; } };''',
'''struct FinalVertexWriter { VertexFormatXYZDUV1 *p; __forceinline void xyz(unsigned i,const Vector3& v) { p[i].x=v.X; p[i].y=v.Y; p[i].z=v.Z; } };''',
'''struct FinalVertexWriter { VertexFormatXYZDUV1 *p; __forceinline void x(unsigned i,float v){p[i].x=v;} __forceinline void y(unsigned i,float v){p[i].y=v;} __forceinline void z(unsigned i,float v){p[i].z=v;} };''',
'''struct FinalVertexWriter { VertexFormatXYZDUV1 *p; __forceinline VertexFormatXYZDUV1* at(unsigned i){return &p[i];} __forceinline void xyz(unsigned i,const Vector3& v){VertexFormatXYZDUV1 *q=at(i);q->x=v.X;q->y=v.Y;q->z=v.Z;} };''',
]
triples=[('top','vArray[vidx].x = top.X;\nvArray[vidx].y = top.Y;\nvArray[vidx].z = top.Z;'),('bottom','vArray[vidx].x = bottom.X;\nvArray[vidx].y = bottom.Y;\nvArray[vidx].z = bottom.Z;')]
for hi,h in enumerate(helpers):
 base=seed.replace('void SegLineRendererClass::Render',h+'\nvoid SegLineRendererClass::Render',1)
 base=base.replace('VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);','VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum); FinalVertexWriter writer = { vArray };',1)
 for target,old in triples:
  count=base.count(old)
  for nth in range(count):
   if hi in (0,3): new='writer.xyz(vidx, '+target+'.X, '+target+'.Y, '+target+'.Z);' if hi==0 else 'writer.xyz(vidx, '+target+');'
   elif hi==1:new='writer.xyz(vidx, '+target+');'
   else:new='writer.x(vidx,'+target+'.X); writer.y(vidx,'+target+'.Y); writer.z(vidx,'+target+'.Z);'
   # replace nth occurrence only
   pos=-1;start=0
   for _ in range(nth+1):pos=base.find(old,start);start=pos+1
   t=base[:pos]+new+base[pos+len(old):]
   jobs.append(('writer_h'+str(hi)+'_'+target+'_'+str(nth),t,None))

# Replace every xyz triplet together; sometimes allocator only moves if all uses share provenance.
for hi,h in enumerate(helpers):
 t=seed.replace('void SegLineRendererClass::Render',h+'\nvoid SegLineRendererClass::Render',1)
 t=t.replace('VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);','VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum); FinalVertexWriter writer = { vArray };',1)
 for target,old in triples:
  if hi in (0,):new='writer.xyz(vidx, '+target+'.X, '+target+'.Y, '+target+'.Z);'
  elif hi in (1,3):new='writer.xyz(vidx, '+target+');'
  else:new='writer.x(vidx,'+target+'.X); writer.y(vidx,'+target+'.Y); writer.z(vidx,'+target+'.Z);'
  t=t.replace(old,new)
 jobs.append(('writer_all_h'+str(hi),t,None))

# Member-style dot receiver wrappers. Preserve the exact arithmetic association.
dot='Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge])'
dh=[
'''struct FinalDot { const Vector3 *a; __forceinline float run(const Vector3& b) const { return a->X*b.X + a->Y*b.Y + a->Z*b.Z; } };''',
'''struct FinalDot { const Vector3 *a; __forceinline float run(const Vector3& b) const { return (a->Z*b.Z + a->Y*b.Y) + a->X*b.X; } };''',
'''struct FinalDot { const Vector3 *a; __forceinline float run(const Vector3& b) const { float zy=a->Z*b.Z+a->Y*b.Y; return zy+a->X*b.X; } };''',
'''struct FinalDot { const Vector3 *a; __forceinline float run(const Vector3& b) const { float x=a->X*b.X; float y=a->Y*b.Y; float z=a->Z*b.Z; return (z+y)+x; } };''',
]
for i,h in enumerate(dh):
 for rev in (False,True):
  call=('FinalDot{&prev_seg->EdgePlane[edge]}.run(next_seg->EdgePlane[edge])' if not rev else 'FinalDot{&next_seg->EdgePlane[edge]}.run(prev_seg->EdgePlane[edge])')
  # VC7 has no brace temporary initialization; use local helper factory via constructor.
  h2=h.replace('const Vector3 *a;','const Vector3 *a; FinalDot(const Vector3* p):a(p){}')
  call=('FinalDot(&prev_seg->EdgePlane[edge]).run(next_seg->EdgePlane[edge])' if not rev else 'FinalDot(&next_seg->EdgePlane[edge]).run(prev_seg->EdgePlane[edge])')
  t=seed.replace('void SegLineRendererClass::Render',h2+'\nvoid SegLineRendererClass::Render',1).replace(dot,call)
  jobs.append(('dotmember_'+str(i)+'_'+str(int(rev)),t,None))

# Final top projection as a receiver wrapper, point-receiver vs direction-receiver.
old='''top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y
    + points[pidx].Z * top_dir.Z) + points[pidx].X * top_dir.X);'''
ph=[
'''struct FinalProjection { const Vector3 *p; FinalProjection(const Vector3* q):p(q){} __forceinline float on(const Vector3& d) const { return ((*(const volatile float *)&p->Y*d.Y+p->Z*d.Z)+p->X*d.X); } };''',
'''struct FinalProjection { const Vector3 *d; FinalProjection(const Vector3* q):d(q){} __forceinline float of(const Vector3& p) const { return ((*(const volatile float *)&p.Y*d->Y+p.Z*d->Z)+p.X*d->X); } };''',
'''struct FinalProjection { const Vector3 *p; FinalProjection(const Vector3* q):p(q){} __forceinline float on(const Vector3& d) const { float yz=*(const volatile float *)&p->Y*d.Y+p->Z*d.Z; return yz+p->X*d.X; } };''',
]
for i,h in enumerate(ph):
 call=('FinalProjection(&points[pidx]).on(top_dir)' if '.on(' in h else 'FinalProjection(&top_dir).of(points[pidx])')
 t=seed.replace('void SegLineRendererClass::Render',h+'\nvoid SegLineRendererClass::Render',1).replace(old,'top = top_dir * '+call+';')
 jobs.append(('projection_member_'+str(i),t,None))

batch(jobs)
print('TOP',json.dumps([{k:x.get(k) for k in ('tag','cost','offsets','code_sha256','error')} for x in sorted(records,key=lambda x:x.get('cost',999))[:25]]),flush=True)
r=evaluate(('final_recheck',best_text,None));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256','verified_exact')}),flush=True)
