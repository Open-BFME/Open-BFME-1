"""Direct local-reference experiments on the two remaining x87 operand-order sites."""
from pathlib import Path
import hashlib,urllib.request,json,re
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41]);r=evaluate(('baseline9',seed,None));accept(r,seed);assert r.get('cost')==9
jobs=[]
dot='vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);'
dot_variants=[
'''const Vector3 &prev_plane_ref = prev_seg->EdgePlane[edge]; const Vector3 &next_plane_ref = next_seg->EdgePlane[edge]; vdp = Vector3::Dot_Product(prev_plane_ref, next_plane_ref);''',
'''const Vector3 &next_plane_ref = next_seg->EdgePlane[edge]; const Vector3 &prev_plane_ref = prev_seg->EdgePlane[edge]; vdp = Vector3::Dot_Product(prev_plane_ref, next_plane_ref);''',
'''const Vector3 *prev_plane_ptr = &prev_seg->EdgePlane[edge]; const Vector3 *next_plane_ptr = &next_seg->EdgePlane[edge]; vdp = Vector3::Dot_Product(*prev_plane_ptr, *next_plane_ptr);''',
'''const Vector3 *next_plane_ptr = &next_seg->EdgePlane[edge]; const Vector3 *prev_plane_ptr = &prev_seg->EdgePlane[edge]; vdp = Vector3::Dot_Product(*prev_plane_ptr, *next_plane_ptr);''',
'''const float &px = prev_seg->EdgePlane[edge].X; const float &nx = next_seg->EdgePlane[edge].X; vdp = prev_seg->EdgePlane[edge].Z*next_seg->EdgePlane[edge].Z + prev_seg->EdgePlane[edge].Y*next_seg->EdgePlane[edge].Y + px*nx;''',
'''const float &nx = next_seg->EdgePlane[edge].X; const float &px = prev_seg->EdgePlane[edge].X; vdp = prev_seg->EdgePlane[edge].Z*next_seg->EdgePlane[edge].Z + prev_seg->EdgePlane[edge].Y*next_seg->EdgePlane[edge].Y + px*nx;''',
'''const float *px = &prev_seg->EdgePlane[edge].X; const float *nx = &next_seg->EdgePlane[edge].X; vdp = prev_seg->EdgePlane[edge].Z*next_seg->EdgePlane[edge].Z + prev_seg->EdgePlane[edge].Y*next_seg->EdgePlane[edge].Y + (*px)*(*nx);''',
'''const float *nx = &next_seg->EdgePlane[edge].X; const float *px = &prev_seg->EdgePlane[edge].X; vdp = prev_seg->EdgePlane[edge].Z*next_seg->EdgePlane[edge].Z + prev_seg->EdgePlane[edge].Y*next_seg->EdgePlane[edge].Y + (*px)*(*nx);''',
]
for i,v in enumerate(dot_variants): jobs.append(('dotref_'+str(i),seed.replace(dot,v,1),None))

old='''top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y
    + points[pidx].Z * top_dir.Z) + points[pidx].X * top_dir.X);'''
proj=[
'''const Vector3 &project_point = points[pidx]; top = top_dir * ((*(const volatile float *)&project_point.Y * top_dir.Y + project_point.Z * top_dir.Z) + project_point.X * top_dir.X);''',
'''const Vector3 *project_point = &points[pidx]; top = top_dir * ((*(const volatile float *)&project_point->Y * top_dir.Y + project_point->Z * top_dir.Z) + project_point->X * top_dir.X);''',
'''const float &point_x = points[pidx].X; const float &dir_x = top_dir.X; top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y + points[pidx].Z * top_dir.Z) + point_x * dir_x);''',
'''const float &dir_x = top_dir.X; const float &point_x = points[pidx].X; top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y + points[pidx].Z * top_dir.Z) + point_x * dir_x);''',
'''const float *point_x = &points[pidx].X; const float *dir_x = &top_dir.X; top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y + points[pidx].Z * top_dir.Z) + (*point_x) * (*dir_x));''',
'''const float *dir_x = &top_dir.X; const float *point_x = &points[pidx].X; top = top_dir * ((*(const volatile float *)&points[pidx].Y * top_dir.Y + points[pidx].Z * top_dir.Z) + (*point_x) * (*dir_x));''',
]
for i,v in enumerate(proj): jobs.append(('projref_'+str(i),seed.replace(old,v,1),None))
# combine every dot/projection pair only if both standalone forms compile.
for di,dv in enumerate(dot_variants):
 for pi,pv in enumerate(proj):
  jobs.append(('combo_'+str(di)+'_'+str(pi),seed.replace(dot,dv,1).replace(old,pv,1),None))
batch(jobs)
print('TOP',json.dumps([{k:x.get(k) for k in ('tag','cost','offsets','code_sha256','error')} for x in sorted(records,key=lambda x:x.get('cost',999))[:30]]),flush=True)
r=evaluate(('final_recheck',best_text,None));accept(r,best_text)
print('FINAL',json.dumps({k:r.get(k) for k in ('cost','offsets','code_sha256','verified_exact')}),flush=True)
