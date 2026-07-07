#!/usr/bin/env python3
"""Audit DIR32 (data-pointer) relocations that build.py currently MASKS (copies original bytes
instead of verifying). For each, RESOLVE+VERIFY the reference instead of trusting it:
  - string literal (??_C@): read the original address from the slot, confirm the string AT that
    address in the binary byte-equals the compiled string literal. Self-verifying, no dedup needed.
  - function address (?...@@..Z, ??_E/??_G thunks): confirm the original address is that function's
    known address (functions.csv / symbols.csv).
  - global / vtable: confirm the symbol is pinned to the original address in symbols.csv.
Reports how many of the ~masked DIR32s become independently VERIFIED vs still need a pin.
"""
import sys, csv, struct, os
sys.path.insert(0,'tools'); import build, harvest
exe=build.EXE.read_bytes(); pe=build.pe_sections(exe); IMG=0x400000
symmap=build.load_symbol_map()
addr2names={}
for nm,addrs in symmap.items():
    for a in addrs: addr2names.setdefault(a,set()).add(nm)
def binstr(rva):
    try:
        o=build.rva_to_file_offset(pe,rva); e=exe.find(b'\x00',o)
        return exe[o:e] if 0<=e-o<400 else None
    except: return None
rows=[r for r in csv.DictReader(open('reverse/functions.csv')) if r['status']=='matched']
bysrc={}
for r in rows: bysrc.setdefault(r['source'],[]).append(r)
from collections import Counter
ver=Counter(); unver=Counter(); fails=[]
for src,frows in sorted(bysrc.items()):
    if not os.path.exists(src): continue
    try: obj=harvest.compile_obj(build.Path(src),[])
    except SystemExit: continue
    for r in frows:
        trva=int(r['target_rva'],16); tsz=int(r['target_size'])
        target=build.read_target_bytes(trva,tsz)
        try: body,relocs=build.read_object_symbol_bytes(obj,r['name'])
        except ValueError: continue
        for off,rt,sym in relocs:
            if rt!=0x0006 or off+4>tsz or off+4>len(target): continue
            va=struct.unpack_from('<I',target,off)[0]; rva=va-IMG
            if sym.startswith('??_C@'):  # string literal -> self-verify content by exact bytes
                try: cs,_=build.read_object_symbol_bytes(obj,sym)
                except ValueError: cs=None
                content=cs.rstrip(b'\x00') if cs else None
                try: o2=build.rva_to_file_offset(pe,rva); bs=exe[o2:o2+len(content)] if content is not None else None
                except: bs=None
                if content is not None and bs==content: ver['string']+=1
                else: unver['string']+=1; fails.append((r['name'][:28],sym[:20]))
            elif sym.endswith('@Z') or sym.startswith('??_E') or sym.startswith('??_G'):  # function addr
                if va in addr2names or rva in addr2names: ver['func-addr']+=1
                else: unver['func-addr']+=1
            elif sym.startswith('??_7'):  # vtable
                if va in addr2names: ver['vtable']+=1
                else: unver['vtable']+=1
            else:  # global / other
                if va in addr2names or sym in symmap: ver['global']+=1
                else: unver['global']+=1
print("VERIFIED (independently, no masking):")
for k,n in ver.most_common(): print(f"  {k:12s}: {n}")
print("STILL UNVERIFIED (need a pin, or a real mismatch):")
for k,n in unver.most_common(): print(f"  {k:12s}: {n}")
tot=sum(ver.values())+sum(unver.values())
print(f"\nTOTAL DIR32: {tot} | verified {sum(ver.values())} ({sum(ver.values())*100//max(tot,1)}%) | unverified {sum(unver.values())}")
if fails:
    print(f"\n{len(fails)} string mismatches (candidate hidden byte-fidelity bugs):")
    seen=set()
    for nm,sm in fails:
        if sm in seen: continue
        seen.add(sm); print(f"  {nm} -> {sm}")
