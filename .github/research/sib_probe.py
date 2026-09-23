"""Read-only MSVC 7.1 witness experiments; all output stays under build/.
A byte-equal result is still diagnostic, not an accepted game-source change.
"""
from pathlib import Path
import hashlib, json, os, re, subprocess, sys, time
ROOT=Path.cwd()
sys.path.insert(0,str(ROOT/'tools'))
import build
OUT=ROOT/'build'/'sib_research_20260923'
OUT.mkdir(parents=True,exist_ok=True)
RVA=0x0045C2F0
SYM='?getScreenCornerWorldPointsAtZ@View@@UAEXPAUCoord3D@@000M@Z'
retail=build.read_target_bytes(RVA,229)
print('RETAIL',retail.hex(),flush=True)
original=(ROOT/'reverse/attempts/0x0045c2f0.cpp').read_text(encoding='utf-8')
root=build.vc71_root()
for name in ['cl.exe','c1.dll','c1xx.dll','c2.dll']:
    p=root/'Vc7/bin'/name
    if p.exists():
        print('TOOLCHAIN',name,len(p.read_bytes()),hashlib.sha256(p.read_bytes()).hexdigest(),flush=True)
p=subprocess.run([str(root/'Vc7/bin/cl.exe')],env=build.compiler_environment(root),cwd=ROOT,capture_output=True,text=True,errors='replace',timeout=30)
print(p.stdout,p.stderr,flush=True)
records=[]
seen={}

def evaluate(tag,text,extra=(),details=False):
    path=OUT/'candidate.cpp'
    obj=OUT/'candidate.obj'
    path.write_text(text,encoding='utf-8')
    obj.unlink(missing_ok=True)
    cmd,env=build.compiler_command(path,obj)
    cmd=cmd[:-2]+list(extra)+cmd[-2:]
    start=time.monotonic()
    p=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True,errors='replace',timeout=45)
    rec={'tag':tag,'returncode':p.returncode,'seconds':time.monotonic()-start,'source_sha256':hashlib.sha256(text.encode()).hexdigest(),'extra':list(extra)}
    if p.returncode or not obj.exists():
        rec['error']=(p.stdout+p.stderr)[-2000:]
        records.append(rec)
        print('RESULT',json.dumps(rec),flush=True)
        return None
    data,relocs=build.read_object_symbol_bytes(obj,SYM)
    data=data.rstrip(b'\xcc')
    mismatches=[i for i,(a,b) in enumerate(zip(data,retail)) if a!=b]
    rec.update(size=len(data),relocations=relocs,diff_count=len(mismatches),length_delta=len(data)-len(retail),offsets=mismatches[:24],code_sha256=hashlib.sha256(data).hexdigest(),raw_exact=data==retail)
    if details or len(mismatches)<=1:
        rec['raw_hex']=data.hex()
    digest=rec['code_sha256']
    if digest in seen: rec['same_as']=seen[digest]
    else: seen[digest]=tag
    if rec['raw_exact'] or len(mismatches)<=1 or details:
        (OUT/(tag+'.cpp')).write_text(text,encoding='utf-8')
        (OUT/(tag+'.json')).write_text(json.dumps(rec,indent=2),encoding='utf-8')
    print('RESULT',json.dumps(rec),flush=True)
    if details:
        try:
            import capstone
            md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
            for ins in md.disasm(data,RVA):
                print(f'ASM {ins.address:08x} {ins.bytes.hex()} {ins.mnemonic} {ins.op_str}',flush=True)
        except ImportError: pass
    records.append(rec)
    return rec

baseline=evaluate('original_bank',original,details=True)
assert baseline and baseline['relocations']==[], 'Witness requires zero relocations for raw test'
clean=re.sub(r'^\s*volatile char \*viewWidthPointer = .*?;\s*$', '', original,flags=re.M)
clean=clean.replace('(Int)(origin.x + (unsigned)viewWidthPointer)','origin.x + viewWidth')
evaluate('clean_integer_sum',clean)
# Test source context, not arithmetic respelling: real CRT headers and TU layout.
for header in ['stddef.h','stdlib.h','math.h','float.h','string.h','memory.h','limits.h','stdio.h']:
    evaluate('header_'+header.replace('.','_'), '#include <'+header+'>\n'+clean)
for decl in ['struct ICoord2D','class ICoord2D']:
    text=clean.replace('struct ICoord2D\n{','class ICoord2D\n{\npublic:') if decl.startswith('class') else clean
    variants=[('implicit',text),('copyctor',text.replace('Int y;\n};','Int y;\n ICoord2D() {}\n ICoord2D(const ICoord2D& o): x(o.x),y(o.y) {}\n};',1)),('assign',text.replace('Int y;\n};','Int y;\n ICoord2D& operator=(const ICoord2D& o) {x=o.x;y=o.y;return *this;}\n};',1))]
    for tag,s in variants: evaluate(decl.split()[0]+'_'+tag,s)
# Aggregate corner construction replaces component stores but not call ordering.
for style in ['aggregate','ctor','assignment']:
    t=clean
    t=t.replace('ICoord2D screenTopLeft, screenTopRight, screenBottomLeft, screenBottomRight;','')
    start=t.index('\tscreenTopLeft.x')
    end=t.index('\n\t// project',start)
    if style=='aggregate':
        setup='\tICoord2D screenTopLeft = {origin.x, origin.y};\n\tICoord2D screenTopRight = {origin.x+viewWidth, origin.y};\n\tICoord2D screenBottomLeft = {origin.x+viewWidth, origin.y+viewHeight};\n\tICoord2D screenBottomRight = {origin.x, origin.y+viewHeight};\n'
    elif style=='ctor':
        t=t.replace('Int y;\n};','Int y;\n ICoord2D() {}\n ICoord2D(Int a,Int b):x(a),y(b) {}\n};',1)
        start=t.index('\tscreenTopLeft.x');end=t.index('\n\t// project',start)
        setup='\tICoord2D screenTopLeft(origin.x, origin.y);\n\tICoord2D screenTopRight(origin.x+viewWidth, origin.y);\n\tICoord2D screenBottomLeft(origin.x+viewWidth, origin.y+viewHeight);\n\tICoord2D screenBottomRight(origin.x, origin.y+viewHeight);\n'
    else:
        setup='\tICoord2D screenTopLeft=origin,screenTopRight=origin,screenBottomLeft=origin,screenBottomRight=origin;\n\tscreenTopRight.x+=viewWidth;\n\tscreenBottomLeft.x+=viewWidth;\n\tscreenBottomLeft.y+=viewHeight;\n\tscreenBottomRight.y+=viewHeight;\n'
    t=t[:start]+setup+t[end:]
    evaluate('corners_'+style,t)
(OUT/'results.json').write_text(json.dumps(records,indent=2),encoding='utf-8')
print('SUMMARY',json.dumps({'trials':len(records),'exact':[r['tag'] for r in records if r.get('raw_exact')],'unique_outputs':len(seen)}),flush=True)
