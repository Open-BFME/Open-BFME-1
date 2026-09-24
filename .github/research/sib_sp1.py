"""Compile the known nine-byte SegLineRenderer candidate under VC7.1 SP1.
Research branch only; no accepted source or ledger writes.
"""
from pathlib import Path
import hashlib, urllib.request, tarfile, os, sys, json
ROOT=Path.cwd()
url='https://raw.githubusercontent.com/Open-BFME/Open-BFME-1/010683a09c21c158a15f250bc1cc86fc1a9667cb/.github/research/sib_probe.py'
raw=urllib.request.urlopen(url,timeout=30).read()
assert hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest()=='d021c7de108224c53583b8920ab7ba29e7d090ed'
prefix=raw.decode().split('seed_masks=',1)[0]
exec(compile(prefix,'pinned_research_harness','exec'))
seed=source_for([19,41])
default_root=build.vc71_root()
# Baseline with repository compiler.
r0=evaluate(('rtm_baseline9',seed,None))
print('RTM',json.dumps({k:r0.get(k) for k in ('size','diff_count','cost','offsets','code_sha256')}),flush=True)
# Download the reproducible SP1 bundle used by rebrew-toolchains.
tgz=OUT/'msvc710_sp1.tar.gz'
data=urllib.request.urlopen('https://codeload.github.com/archaic-msvc/msvc710_sp1/tar.gz/refs/heads/master',timeout=60).read()
assert hashlib.sha256(data).hexdigest()=='44246ff2980d715c2d05eaed505344a0b87850a04606482c13ba4832ddf5ec70'
tgz.write_bytes(data)
sp1=OUT/'msvc710_sp1'
sp1.mkdir(exist_ok=True)
with tarfile.open(tgz,'r:gz') as tf:
    root=tf.getmembers()[0].name.split('/')[0]+'/'
    for m in tf.getmembers():
        if not m.name.startswith(root): continue
        m.name=m.name[len(root):]
        if m.name: tf.extract(m,sp1)
# Supply host runtime/support DLLs without replacing SP1 compiler backends.\nimport shutil\nfor srcdir in [default_root/'Vc7'/'bin', default_root/'Common7'/'IDE', default_root.parents[1]]:\n    if not srcdir.exists(): continue\n    for dll in srcdir.glob('*.dll'):\n        if dll.name.lower() in ('c1.dll','c1xx.dll','c2.dll'): continue\n        for dstdir in [sp1/'Vc7'/'bin', sp1/'Common7'/'IDE']:\n            dstdir.mkdir(parents=True,exist_ok=True)\n            dst=dstdir/dll.name\n            if not dst.exists(): shutil.copy2(dll,dst)\n# Bundle root itself contains Vc7.\nos.environ['VC71_ROOT']=str(sp1)
# build.vc71_root reads env at call time; compile unchanged source.
r1=evaluate(('sp1_candidate9',seed,None))
print('SP1',json.dumps({k:r1.get(k) for k in ('returncode','size','diff_count','cost','offsets','code_sha256','raw_exact','error')}),flush=True)
# Strict relocation-resolved verification when shape is promising.
if r1.get('returncode')==0:
    row={'name':SYM,'target_rva':hex(RVA),'target_size':str(SIZE),'source':(OUT/'sp1_candidate9.cpp').relative_to(ROOT).as_posix(),'status':'matched','notes':''}
    (OUT/'sp1_candidate9.cpp').write_text(seed,encoding='utf-8',newline='\n')
    try:
        p=build.compile_function(row,symbols,OUT/'sp1_strict.obj',retain_compiled=True)
        result={'resolved_diffs':sum(a!=b for a,b in zip(retail,p['bytes'])),'size':len(p['compiled']),'unresolved':p['unresolved'],'masked':p['masked'],'relocs':len(p['relocs']),'exact':p['bytes']==retail and len(p['compiled'])==SIZE and not p['unresolved'] and not p['masked']}
    except (Exception,SystemExit) as exc:
        result={'error':str(exc),'exact':False}
    (OUT/'sp1_strict.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
    print('STRICT',json.dumps(result),flush=True)
