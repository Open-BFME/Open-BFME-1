"""Header-order experiments for the final-nine renderer candidate."""
from pathlib import Path
import hashlib,urllib.request,json,itertools,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41]);r=evaluate(('baseline9',seed,None));accept(r,seed);assert r.get('cost')==9
jobs=[]
support='#include "../attempt_support/0x00960a30.inc"'
matrix='#include "matrix3d.h"'
# Add canonical headers before the ABI prefix, retaining matrix3d first unless explicitly tested.
headers=['vector3.h','vector4.h','vector2.h','dx8fvf.h','seglinerenderer.h','dx8wrapper.h']
for h in headers:
 t=seed.replace(support,'#include "'+h+'"\n'+support,1)
 jobs.append(('pre_'+h.replace('.','_'),t,None))
# Pair combinations in both orders for the most relevant definitions.
for a,bh in itertools.permutations(['vector3.h','vector4.h','dx8fvf.h','seglinerenderer.h'],2):
 block='#include "'+a+'"\n#include "'+bh+'"\n'+support
 jobs.append(('pre_'+a.split('.')[0]+'_'+bh.split('.')[0],seed.replace(support,block,1),None))
# Small three-header permutations: declaration order can move front-end numbering/inline context.
for order in itertools.permutations(['vector3.h','dx8fvf.h','seglinerenderer.h'],3):
 block=''.join('#include "'+x+'"\n' for x in order)+support
 jobs.append(('pre3_'+'_'.join(x.split('.')[0] for x in order),seed.replace(support,block,1),None))
# Move all existing canonical includes before the support prefix while preserving their relative order.
lines=['seglinerenderer.h','ww3d.h','rinfo.h','dx8wrapper.h','sortingrenderer.h','vp.h','vector3i.h','random.h','v3_rnd.h','meshgeometry.h']
for n in [1,2,3,4,6,10]:
 t=seed
 moved=[]
 for h in lines[:n]:
  inc='#include "'+h+'"'
  # random.h has macro before it; don't move it in the broad forms.
  if h=='random.h':continue
  if inc in t:
   t=t.replace(inc,'// moved '+inc,1);moved.append(inc)
 block='\n'.join(moved)+'\n'+support
 t=t.replace(support,block,1)
 jobs.append(('move_first_'+str(n),t,None))
# Support before matrix3d is a negative control; other orderings around matrix.
t=seed.replace(matrix+'\n'+support,support+'\n'+matrix,1);jobs.append(('support_before_matrix',t,None))
for h in ['vector3.h','dx8fvf.h','seglinerenderer.h']:
 t=seed.replace(matrix+'\n'+support,'#include "'+h+'"\n'+matrix+'\n'+support,1)
 jobs.append(('before_matrix_'+h.replace('.','_'),t,None))

batch(jobs)
print('TOP',json.dumps([{k:x.get(k) for k in ('tag','cost','offsets','code_sha256','error')} for x in sorted(records,key=lambda x:x.get('cost',999))[:30]]),flush=True)
r=evaluate(('final_recheck',best_text,None));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256','verified_exact')}),flush=True)
