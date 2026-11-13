import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path
ROOT=Path.cwd()
sys.path.insert(0,str(ROOT/'tools'))
import build
OUT=ROOT/'build/spike3/aicommand-feasibility'
root=build.vc71_root(); env=build.compiler_environment(root)
report=[]
for base in (0x10000000,0x20000000):
    for state in ('before','after'):
        objs=[OUT/('AIStates.obj' if state=='before' else 'AIStates-after-official.obj'),OUT/'AICommandParmsStorageXfer.obj',OUT/'S3VersionBlocks.obj']
        stem=f'official-pair-{state}-{base:08x}'
        command=['wine',str(root/'Vc7/bin/link.exe'),'/NOLOGO','/DLL','/NOENTRY','/NODEFAULTLIB','/INCREMENTAL:NO',
                 '/MACHINE:X86','/OPT:REF','/OPT:NOICF','/INCLUDE:?doXfer@AICommandParmsStorage@@QAEXPAVXfer@@@Z',
                 f'/BASE:{base:#x}',f'/OUT:{OUT.relative_to(ROOT)/(stem+".dll")}',f'/MAP:{OUT.relative_to(ROOT)/(stem+".map")}',
                 *[str(p.relative_to(ROOT)) for p in objs],build.wine_path(root/'Vc7/lib/msvcrt.lib'),build.wine_path(root/'Vc7/lib/kernel32.lib')]
        run=subprocess.run(command,env=env,cwd=ROOT,capture_output=True,text=True,errors='replace')
        text=run.stdout+run.stderr
        (OUT/(stem+'.log')).write_text(text)
        report.append({'state':state,'base':base,'command':command,'exit':run.returncode,
                       'objects':{str(p.relative_to(ROOT)):hashlib.sha256(p.read_bytes()).hexdigest() for p in objs},
                       'duplicates':re.findall(r'^.*error LNK2005:.*$',text,re.M),
                       'unresolved':sorted(set(re.findall(r'error LNK(?:2001|2019): unresolved external symbol (.*?)(?: referenced in function|$)',text,re.M))),
                       'family_closed_delta':None,'selected_provider_proof':False})
(OUT/'official-native-pair.json').write_text(json.dumps(report,indent=2))
for item in report:
    print(item['state'],hex(item['base']),'exit',item['exit'],'duplicates',len(item['duplicates']),'unresolved',len(item['unresolved']))
assert all(len(x['duplicates'])==(1 if x['state']=='before' else 0) for x in report)
assert all(x['exit']!=0 and len(x['unresolved'])==244 for x in report)
assert all(x['unresolved']==report[0]['unresolved'] for x in report)
