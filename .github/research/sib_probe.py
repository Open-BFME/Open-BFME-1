"""Zero-code __assume experiments for final-nine renderer output."""
from pathlib import Path
import hashlib,urllib.request,json,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41]);r=evaluate(('baseline9',seed,None));accept(r,seed);assert r.get('cost')==9
jobs=[]
vdecl='VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);'
assumes=[
 '__assume(vArray != 0);',
 '__assume(vidx < vnum);',
 '__assume(vArray != 0); __assume(vidx < vnum);',
 '__assume((((unsigned)vArray)&3)==0);',
 '__assume((((unsigned)vArray)&7)==0);',
 '__assume(vnum > 0);',
]
for i,a in enumerate(assumes):
 jobs.append(('decl_assume_'+str(i),seed.replace(vdecl,vdecl+' '+a,1),None))
# Before each problematic output group, individually and all.
markers=['vArray[vidx].x = top.X;','vArray[vidx].x = bottom.X;']
for marker in markers:
 start=0;n=0
 while True:
  pos=seed.find(marker,start)
  if pos<0:break
  for i,a in enumerate(assumes[:4]):
   jobs.append(('site_'+('t' if 'top.' in marker else 'b')+'_'+str(n)+'_'+str(i),seed[:pos]+a+'\n'+seed[pos:],None))
  start=pos+1;n+=1
# Merge-local assumptions on pointers/edge.
dot='vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);'
pos=seed.find(dot)
for i,a in enumerate([
 '__assume(prev_seg != 0);',
 '__assume(next_seg != 0);',
 '__assume(prev_seg != next_seg);',
 '__assume(edge == TOP_EDGE || edge == BOTTOM_EDGE);',
 '__assume(prev_seg != 0); __assume(next_seg != 0); __assume(prev_seg != next_seg);',
]):
 jobs.append(('merge_assume_'+str(i),seed[:pos]+a+'\n'+seed[pos:],None))
# Projection facts.
proj='top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y'
pos=seed.find(proj)
for i,a in enumerate(['__assume(points != 0);','__assume(pidx < point_cnt);','__assume(points != 0); __assume(pidx < point_cnt);']):
 jobs.append(('proj_assume_'+str(i),seed[:pos]+a+'\n'+seed[pos:],None))

batch(jobs)
print('TOP',json.dumps([{k:x.get(k) for k in ('tag','cost','offsets','code_sha256','error')} for x in sorted(records,key=lambda x:x.get('cost',999))[:30]]),flush=True)
r=evaluate(('final_recheck',best_text,None));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256','verified_exact')}),flush=True)
