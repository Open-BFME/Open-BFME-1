"""Dump member offsets per class from the ZH (GeneralsMD) headers -- or the few
BFME-patched headers under Code/ -- by compiling `(int)&((C*)0)->m_x` tables with
the project's own cl and reading the constants back out of the object.

    python tools/zh_offsets.py GameEngine/Include/GameLogic/Object.h        # one header, JSON
    python tools/zh_offsets.py --all                                       # every engine header -> reverse/zh_offsets.json

MSVC 7.1 has no /d1reportAllClassLayout, so this is the layout oracle: 728
classes / 6,064 members on 2026-09-10. Members hidden behind #ifdefs are dropped
automatically from the compile errors. `sizeof` is recorded per class."""
import sys,re,subprocess,struct,json
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent)); import build as B
from pathlib import Path
ZH=B.ROOT/'reference/CnC_Generals_Zero_Hour/GeneralsMD/Code'
ROOTS={'zh':ZH,'bfme':B.ROOT/'Code'}
CLFROM={'zh':'Code/GameEngine/Source/GameLogic/Object/Contain/TunnelContain.cpp','bfme':'Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp'}
MEM=re.compile(r'^\s*(?!return|typedef|friend|static|enum|class|struct|union|virtual|using|#)[A-Za-z_][\w:<>,\*&\s]*?\s+\*?\s*(\w+)\s*(\[[^\]]*\])?\s*(?::\s*\d+)?\s*;',re.M)
def classes_in(header):
    """{qualified class name: [members]} for every class/struct in the header;
    nested classes come out as Outer::Inner and their bodies are removed from
    the outer's member scan."""
    txt = header.read_text(encoding='utf-8', errors='replace')
    txt = re.sub(r'//[^\n]*', '', txt)
    txt = re.sub(r'/\*.*?\*/', '', txt, flags=re.S)
    out = {}
    head_re = re.compile(r'(?:^|[;{}\s])(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{')

    def walk(body, prefix):
        pos = 0
        while True:
            m = head_re.search(body, pos)
            if not m:
                break
            name = m.group(1)
            i = m.end()
            depth = 1
            j = i
            while j < len(body) and depth:
                depth += (body[j] == '{') - (body[j] == '}')
                j += 1
            inner = body[i:j - 1]
            q = prefix + name
            walk(inner, q + '::')
            # blank out nested class/struct/enum/union bodies before harvesting members
            flat = inner
            for _ in range(4):
                flat = re.sub(r'(?:class|struct|enum|union)\s*\w*\s*(?::[^{;]*)?\{[^{}]*\}\s*\w*\s*;?', ' ', flat)
            members = [mm.group(1) for mm in MEM.finditer(flat)]
            if members:
                out[q] = members
            pos = j
    walk(txt, '')
    return out
def dump(header_rel, extra_includes=(), cl_from=None, drop=(), root='zh'):
    cl_from=cl_from or CLFROM[root]
    hdr=ROOTS[root]/header_rel; cls=classes_in(hdr)
    for c,m in drop: 
        if c in cls and m in cls[c]: cls[c].remove(m)
    cls={c:ms for c,ms in cls.items() if ms}
    head=Path(B.ROOT/cl_from).read_text(encoding='utf-8',errors='replace').splitlines()[:2]
    if root=='zh':
        ww='reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/'
        head[0]+=' '+' '.join('/I'+ww+d for d in ('WW3D2','WWMath','WWDebug','WWSaveLoad','WWLib'))
    inc=header_rel.split('Include/')[-1] if 'Include/' in header_rel else Path(header_rel).name
    lines=list(head)+['#define private public','#define protected public','#include "PreRTS.h"']+[f'#include "{h}"' for h in extra_includes]+[f'#include "{inc}"']
    items=[]
    for c,ms in cls.items():
        for m in ms:
            items.append((c,m)); lines.append(f'extern const int rva_off_{len(items)-1} = (int)(char*)&((({c}*)0)->{m});')
    lines.append(f'extern const int rva_sizes[{len(cls)}] = {{'+','.join(f'sizeof({c})' for c in cls)+'};')
    (B.ROOT/'build/layout').mkdir(parents=True,exist_ok=True)
    src=B.ROOT/'build/layout'/(root+'_'+Path(header_rel).stem+'_off.cpp'); src.write_text('\n'.join(lines)+'\n',encoding='utf-8')
    out=src.with_suffix('.obj'); cmd,env=B.compiler_command(src,out)
    r=subprocess.run(cmd,env=env,capture_output=True,text=True,errors='replace',cwd=B.ROOT)
    if r.returncode:
        errs=[l for l in (r.stdout+r.stderr).splitlines() if 'error' in l]
        bad=set()
        for e in errs:
            m=re.search(r'_off\.cpp\((\d+)\)',e)
            if m:
                ln=int(m.group(1))-1
                if 0<=ln<len(lines) and lines[ln].startswith('extern const int rva_off_'):
                    k=int(re.search(r'rva_off_(\d+)',lines[ln]).group(1)); bad.add(items[k])
        if bad and len(drop)<400: return dump(header_rel,extra_includes,cl_from,tuple(drop)+tuple(bad),root)
        return None, errs
    res={}
    for i,(c,m) in enumerate(items):
        try: b,_=B.read_object_symbol_bytes(out,f'?rva_off_{i}@@3HB'); res.setdefault(c,{})[m]=struct.unpack_from('<i',b)[0]
        except Exception as e: res.setdefault(c,{})[m]=f'ERR {e}'[:40]
    try:
        b,_=B.read_object_symbol_bytes(out,f'?rva_sizes@@3QBHB')
        for i,c in enumerate(cls): res[c]['sizeof']=struct.unpack_from('<i',b,4*i)[0]
    except Exception as e: pass
    return res, []
def dump_all(root='zh'):
    import concurrent.futures as cf
    base=ROOTS[root]; roots=['GameEngine/Include','GameEngineDevice/Include']+(['Libraries/Source/WWVegas/WWLib','Libraries/Source/WWVegas/WW3D2','Libraries/Source/WWVegas/WWMath'] if root=='zh' else [])
    hdrs=[p.relative_to(base).as_posix() for r in roots for p in (base/r).rglob('*.h')]
    res={}; fails={}
    def one(h):
        r=subprocess.run([sys.executable,__file__,h,root],capture_output=True,text=True,errors='replace',cwd=B.ROOT,timeout=600)
        return h,r.returncode,r.stdout,r.stderr
    with cf.ThreadPoolExecutor(6) as ex:
        for h,rc,out,err in ex.map(one,hdrs):
            if rc==0 and '{' in out: res[h]=json.loads(out[out.index('{'):])
            else: fails[h]=((out+err).strip().splitlines() or ['?'])[-1][:160]
            print(f'{len(res)} ok / {len(fails)} fail  {h}',file=sys.stderr,flush=True)
    outp=B.ROOT/'reverse'/(root+'_offsets.json'); json.dump(res,open(outp,'w'),indent=0)
    json.dump(fails,open(B.ROOT/'build/layout'/(root+'_offsets_fail.json'),'w'),indent=0)
    print('wrote',outp,len(res),'headers;',len(fails),'failed (build/layout/*_fail.json)')
if __name__=='__main__':
    if sys.argv[1]=='--all': dump_all(sys.argv[2] if len(sys.argv)>2 else 'zh'); sys.exit(0)
    res,errs=dump(sys.argv[1],root=(sys.argv[2] if len(sys.argv)>2 else 'zh'))
    if res is None: print('\n'.join(errs[:12])); sys.exit(1)
    print(json.dumps(res))
