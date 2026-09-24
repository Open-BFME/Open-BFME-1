"""Constructor/lifetime perturbations for the final-nine renderer candidate."""
from pathlib import Path
import hashlib,urllib.request,itertools,json,time,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41])
r=evaluate(('baseline9',seed,None));accept(r,seed);assert r.get('cost')==9
print('BASE',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256')}),flush=True)

jobs=[]
# Explicit default constructors on the large stack record arrays.
repls=[
 ('LineSegment','struct LineSegment {','struct LineSegment { LineSegment() {}'),
 ('LineSegmentIntersection','struct LineSegmentIntersection  {','struct LineSegmentIntersection { LineSegmentIntersection() {}'),
]
for mask in range(1,4):
 t=seed; names=[]
 for i,(name,a,b) in enumerate(repls):
  if mask&(1<<i):
   t=t.replace(a,b,1);names.append(name)
 jobs.append(('ctor_'+'_'.join(names),t,None))

# Forceinline/noinline constructor forms to probe front-end lifetime boundaries.
for name,a,b in repls:
 for spec in ['__forceinline ','__declspec(noinline) ','']:
  ctor=(('struct '+name+' {') if name=='LineSegment' else 'struct LineSegmentIntersection {')+' '+spec+name+'() {}'
  old=a
  t=seed.replace(old,ctor,1)
  jobs.append(('ctorform_'+name+'_'+(spec.strip().replace(' ','_') or 'inline'),t,None))

# Add explicit copy constructors/assignments to records (not necessarily exercised)
# to see whether type traits change optimizer treatment.
for name,a,b in repls:
 base=('struct LineSegment {' if name=='LineSegment' else 'struct LineSegmentIntersection  {')
 for kind in ['copy','assign','both']:
  extra=name+'() {} '
  if kind in ('copy','both'): extra+=name+'(const '+name+'& o) { *this=o; } '
  if kind in ('assign','both'): extra+=name+'& operator=(const '+name+'& o) { memcpy(this,&o,sizeof(*this)); return *this; } '
  t=seed.replace(base,('struct '+name+' { '+extra),1)
  jobs.append(('traits_'+name+'_'+kind,t,None))

# TriIndex stack array: shadow with a wrapper only if its declaration is available by name.
# No field changes; constructor is intentionally empty.
for spec in ['','__forceinline ']:
 marker='TriIndex v_index_array[MAX_SEGLINE_POLY_BUFFER_SIZE];'
 replacement='struct LocalTriIndex : TriIndex { '+spec+'LocalTriIndex() {} }; LocalTriIndex v_index_array[MAX_SEGLINE_POLY_BUFFER_SIZE];'
 jobs.append(('tri_ctor_'+(spec.strip() or 'inline'),seed.replace(marker,replacement),None))

# Lifetime scopes around the output phase can change allocator interference without
# changing any expression. Test nested block boundaries.
start='unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];'
end='SortingRendererClass::Insert_Triangles('
if start in seed and end in seed:
 pos=seed.index(start); ep=seed.index(end,pos)
 for mode in range(3):
  if mode==0:
   t=seed[:pos]+'{\n'+seed[pos:ep]+'}\n'+seed[ep:]
  elif mode==1:
   # block only vertex pointer and index array declarations plus use region
   t=seed[:pos]+'{\n'+seed[pos:ep]+seed[ep:]
   # close before function's following state restore by searching after insert statement later
   close=t.find(';',t.index(end,pos))+1;t=t[:close]+'\n}\n'+t[close:]
  else:
   t=seed.replace('VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);','VertexFormatXYZDUV1 *vArray; { vArray = getVertexBuffer(vnum); }',1)
  jobs.append(('scope_'+str(mode),t,None))

batch(jobs)
print('BESTS',json.dumps([{k:x.get(k) for k in ('tag','cost','offsets','code_sha256','error')} for x in sorted(records,key=lambda x:x.get('cost',999))[:20]]),flush=True)
r=evaluate(('final_recheck',best_text,None));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256','verified_exact')}),flush=True)
