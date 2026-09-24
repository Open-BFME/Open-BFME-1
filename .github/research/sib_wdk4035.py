"""Test the known nine-byte renderer candidate with WDK 3790.1830 compiler 13.10.4035.
Two modes: backend-only c2.dll and full cl/c1xx/c2 toolchain.
Research branch only.
"""
from pathlib import Path
import hashlib,urllib.request,json,shutil,os,sys,subprocess
u='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
b=urllib.request.urlopen(u,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
exec(compile(b.decode().split('seed_masks=',1)[0],'pinned_research_harness','exec'))
seed=source_for([19,41])
base=evaluate(('baseline3077',seed,None));print('BASE',json.dumps({k:base.get(k) for k in ('size','cost','offsets','code_sha256')}),flush=True)
assert base.get('cost')==9
default_root=build.vc71_root()
commit='1ed3987db6e72d1fb9c6298fddf0c080b8f591e1'
files={
'cl.exe':'3b67081112594334862e5a7132f7fc03b1c85b0c',
'c1.dll':'68668253e18aa41b5a00dcaaba80524476903cf7',
'c1xx.dll':'2a0c008bf6699bf6da949743039a27945111582d',
'c2.dll':'50c870e29b487242609658e83beb902080dfb3f6',
'msobj71.dll':'7824c27244272b938b36b2f3bc7f11df1d972979',
'mspdb71.dll':'7560cb07773b51f3560769fe19101895c58e8ce5',
'msvcp71.dll':'766be0e6e57a7b3f17295baeaa7b58c5b23551a4',
'msvcr71.dll':'d710f444fe05e0e47f61c49a9b802f8b1faf47e5',
}
downloaded={}
for name,gitsha in files.items():
    url=f'https://raw.githubusercontent.com/9176324/WinDDK/{commit}/3790.1830/bin/x86/{name}'
    data=urllib.request.urlopen(url,timeout=60).read()
    got=hashlib.sha1(b'blob '+str(len(data)).encode()+b'\0'+data).hexdigest()
    assert got==gitsha,(name,got,gitsha)
    downloaded[name]=data
print('WDK_FILES',json.dumps({k:hashlib.sha256(v).hexdigest() for k,v in downloaded.items()}),flush=True)

def make_root(label,overwrite):
    root=OUT/label
    if root.exists():shutil.rmtree(root)
    # Keep the repo's proven headers/libs/runtime; vary compiler executables only.
    shutil.copytree(default_root,root)
    bindir=root/'Vc7'/'bin'
    for name in overwrite:
        (bindir/name).write_bytes(downloaded[name])
    # DDK cl prints version and finds the compiler DLLs from its bin dir.
    return root

def run_mode(label,names):
    root=make_root(label,names)
    os.environ['VC71_ROOT']=str(root)
    p=subprocess.run([str(root/'Vc7'/'bin'/'cl.exe')],cwd=ROOT,env=build.compiler_environment(root),capture_output=True,text=True,errors='replace',timeout=30)
    print('VERSION',label,(p.stdout+p.stderr)[-1000:],flush=True)
    r=evaluate((label,seed,None))
    print('RESULT',label,json.dumps({k:r.get(k) for k in ('returncode','size','cost','offsets','code_sha256','error')}),flush=True)
    if r.get('returncode')==0:
        path=OUT/(label+'.cpp');path.write_text(seed,encoding='utf-8',newline='\n')
        row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':path.relative_to(ROOT).as_posix(),'status':'matched','notes':''}
        try:
            q=build.compile_function(row,symbols,OUT/(label+'.obj'),retain_compiled=True)
            strict={'resolved_diffs':sum(a!=b for a,b in zip(retail,q['bytes'])),'size':len(q['compiled']),'unresolved':q['unresolved'],'masked':q['masked'],'relocs':len(q['relocs']),'exact':q['bytes']==retail and len(q['compiled'])==SIZE and not q['unresolved'] and not q['masked']}
        except (Exception,SystemExit) as e:strict={'error':str(e),'exact':False}
        print('STRICT',label,json.dumps(strict),flush=True)
        (OUT/(label+'_strict.json')).write_text(json.dumps(strict,indent=2))
    return r

# Current front-end + 13.10.4035 backend only.
hybrid=run_mode('wdk4035_c2only',['c2.dll'])
# Full C++ compiler driver/frontend/backend, with matching PDB/object helpers.
full=run_mode('wdk4035_full',['cl.exe','c1.dll','c1xx.dll','c2.dll','msobj71.dll','mspdb71.dll','msvcp71.dll','msvcr71.dll'])
