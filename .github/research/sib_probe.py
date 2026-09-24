"""Zero-byte VC7 asm scheduling barriers for the final-nine renderer candidate."""
from pathlib import Path
import hashlib,urllib.request,json,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41]);r=evaluate(('baseline9',seed,None));accept(r,seed);assert r.get('cost')==9
jobs=[]
bar='__asm { }\n'
# Exact region anchors.
anchors=[
 'vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);',
 'VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);',
 'vArray[vidx].x = top.X;',
 'vArray[vidx].x = bottom.X;',
 'top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y',
 'bottom = bottom_dir * DotSegLineBottomOutput(points[pidx], bottom_dir);',
 'top = top_dir * DotSegLineLastTopSequential(top_dir, points[pidx]);',
 'bottom = bottom_dir * DotSegLineLastTopSequential(bottom_dir, points[pidx]);',
]
for ai,a in enumerate(anchors):
 start=0;n=0
 while True:
  pos=seed.find(a,start)
  if pos<0:break
  jobs.append(('bar_before_'+str(ai)+'_'+str(n),seed[:pos]+bar+seed[pos:],None))
  # after complete statement where practical
  semi=seed.find(';',pos)
  if semi>=0:jobs.append(('bar_after_'+str(ai)+'_'+str(n),seed[:semi+1]+'\n'+bar+seed[semi+1:],None))
  start=pos+len(a);n+=1

# Around index increments that establish the values used by the problematic output blocks.
for a in ['vidx++;','pidx++;','top_int_idx++;','bottom_int_idx++;']:
 start=0;n=0
 while True:
  pos=seed.find(a,start)
  if pos<0:break
  jobs.append(('bar_post_'+a.replace('+','p').replace(';','')+'_'+str(n),seed[:pos+len(a)]+'\n'+bar+seed[pos+len(a):],None))
  start=pos+len(a);n+=1

# C/C++ comma-expression sequence points with an empty asm helper cannot exist, so test
# compiler-visible no-op statement forms around the same blocks.
for stmt in ['(void)vidx;','(void)vArray;','(void)pidx;','(void)top_int_idx;','(void)bottom_int_idx;']:
 for marker in ['vArray[vidx].x = top.X;','vArray[vidx].x = bottom.X;']:
  start=0;n=0
  while True:
   pos=seed.find(marker,start)
   if pos<0:break
   jobs.append(('touch_'+stmt[6:10].replace(';','')+'_'+str(n)+'_'+('t' if 'top.' in marker else 'b'),seed[:pos]+stmt+'\n'+seed[pos:],None))
   start=pos+1;n+=1

batch(jobs)
print('TOP',json.dumps([{k:x.get(k) for k in ('tag','cost','offsets','code_sha256','error')} for x in sorted(records,key=lambda x:x.get('cost',999))[:30]]),flush=True)
r=evaluate(('final_recheck',best_text,None));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256','verified_exact')}),flush=True)
