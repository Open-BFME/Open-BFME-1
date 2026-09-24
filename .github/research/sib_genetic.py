"""Deterministic multi-bit search over compiler-shaping volatile qualifiers.
Research only; no production or ledger changes.
"""
from pathlib import Path
import hashlib,urllib.request,json,random,time,concurrent.futures,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
rng=random.Random(0x960A30)
deadline=time.monotonic()+650
current={19,41}
# First reproduce the nine-byte state.
batch([('seed9',source_for(current),current)])
assert best and best['cost']==9

def candidates_initial():
 out=[]
 remaining=[i for i in range(len(atoms)) if i not in current]
 for k in [1,2,3,5,8,12,20,30,40,55,70]:
  for j in range(5):
   kk=min(k,len(remaining));m=current|set(rng.sample(remaining,kk))
   out.append((f'jump_{k}_{j}',source_for(m),m))
 # Absolute random masks from both sparse and clean ends.
 for k in [0,5,10,20,35,50,65,75,79]:
  for j in range(4):
   m=set(rng.sample(range(len(atoms)),min(k,len(atoms))))
   out.append((f'abs_{k}_{j}',source_for(m),m))
 return out

batch(candidates_initial())
for gen in range(6):
 if best.get('verified_exact') or time.monotonic()>deadline-100:break
 good=sorted((r for r in records if r.get('mask') is not None and 'cost' in r and not r.get('relocation_drifts') and 'error' not in r),key=lambda r:(r['cost'],r['volatile_tokens']))
 # retain diverse machine outputs and removal patterns
 parents=[];codes=set();masks=set()
 for r in good:
  key=tuple(r['mask'])
  if r['code_sha256'] in codes and key in masks:continue
  codes.add(r['code_sha256']);masks.add(key);parents.append(r)
  if len(parents)>=12:break
 jobs=[]
 for pi,p in enumerate(parents):
  pm=set(p['mask'])
  # Small and large mutations.
  for k in [2,3,5,8,13,21]:
   for rep in range(2):
    bits=set(rng.sample(range(len(atoms)),min(k,len(atoms))))
    m=pm^bits
    jobs.append((f'g{gen}_p{pi}_k{k}_{rep}',source_for(m),m))
 # Crossovers among strong parents.
 for i in range(min(8,len(parents))):
  for j in range(i+1,min(8,len(parents))):
   a=set(parents[i]['mask']); bb=set(parents[j]['mask'])
   for mode in range(2):
    if mode==0:m=(a&bb)|{x for x in (a^bb) if rng.random()<0.5}
    else:m=(a|bb)-{x for x in (a^bb) if rng.random()<0.5}
    jobs.append((f'g{gen}_cross_{i}_{j}_{mode}',source_for(m),m))
 batch(jobs)
 print('GEN',gen,'BEST',best['cost'],'VOL',best['volatile_tokens'],'MASK',best.get('mask'),flush=True)

r=evaluate(('final_recheck',best_text,best.get('mask')));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','volatile_tokens','mask','offsets','code_sha256','verified_exact')}),flush=True)
print('SUMMARY',json.dumps({'trials':len(records),'best_cost':best['cost'],'best_volatile':best['volatile_tokens'],'exact':best.get('verified_exact',False)}),flush=True)
