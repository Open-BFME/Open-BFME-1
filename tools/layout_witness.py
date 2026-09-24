"""Witness BFME's class layouts from the code itself.

    python tools/layout_witness.py --compile   # compile every reference GameEngine(Device) TU to build/layout/ref/ (~10 min, resumable)
    python tools/layout_witness.py             # align + aggregate -> reverse/bfme_layouts.json

For every function the ledger or a pin names, whose ZH source compiled, the ZH body
and the retail body are aligned instruction-for-instruction (difflib over opcode
shapes; bodies under 70% alignment are dropped). Each `this`-relative memory
operand whose displacement differs is a witness: ZH offset -> retail offset. The
ZH offset is named through reverse/zh_offsets.json (tools/zh_offsets.py) walking
the primary base chain; witnesses are weighted by alignment quality and summed
per (owner class, member). Read the result with tools/bfme_layout.py.

Known blind spots: `this` inside a non-primary base subobject (offsets come out
subobject-relative), registers that alias `this` after the prologue, and members
of the same ZH offset in a derived class that the dump could not compile."""
import sys,json,re,difflib,collections,csv,struct
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent)); import build as B

ZH=B.ROOT/'reference/CnC_Generals_Zero_Hour/GeneralsMD/Code'


def format_failure_groups(fails, examples=5):
    """Group (rel_path, transcript) pairs by first_cl_error. Return report lines."""
    by = collections.defaultdict(list)
    for rel, text in fails:
        by[B.first_cl_error(text)].append(rel)
    ranked = sorted(by.items(), key=lambda kv: (-len(kv[1]), kv[0]))
    lines = [f'{len(fails)} failing TUs in {len(ranked)} groups:', '']
    for key, rels in ranked:
        lines.append(f'  {len(rels):4d}  {key}')
        for rel in rels[:examples]:
            lines.append(f'         {rel}')
        extra = len(rels) - examples
        if extra > 0:
            lines.append(f'         ... and {extra} more')
        lines.append('')
    return lines, ranked


def compile_reference(prefixes=None):
    """Compile every ZH GameEngine(Device) TU. Failures are grouped, not swallowed."""
    import concurrent.futures as cf
    srcs = [p for r in ('GameEngine/Source', 'GameEngineDevice/Source')
            for p in (ZH / r).rglob('*.cpp')]
    srcs.sort()
    if prefixes:
        srcs = [p for p in srcs if any(pref in p.relative_to(ZH).as_posix() for pref in prefixes)]
    outdir = B.ROOT / 'build/layout/ref'
    outdir.mkdir(parents=True, exist_ok=True)

    def one(p):
        rel = p.relative_to(ZH).as_posix()
        out = outdir / (rel.replace('/', '_')[:-4] + '.obj')
        if out.exists():
            return 'cached', rel, ''
        try:
            ok, text, _code = B.try_compile_source(p, out)
        except SystemExit:
            raise
        except Exception as exc:
            return 'fail', rel, f'{type(exc).__name__}: {exc}'
        if ok and out.exists():
            return 'ok', rel, ''
        return 'fail', rel, text or ''

    with cf.ThreadPoolExecutor(6) as ex:
        rows = list(ex.map(one, srcs))
    n_ok = sum(1 for s, _, _ in rows if s in ('ok', 'cached'))
    n_fail = sum(1 for s, _, _ in rows if s == 'fail')
    n_cached = sum(1 for s, _, _ in rows if s == 'cached')
    extra = f' ({n_cached} cached)' if n_cached else ''
    print(f'reference TUs compiled {n_ok} failed {n_fail}{extra}')
    fails = [(rel, text) for s, rel, text in rows if s == 'fail']
    if not fails:
        return
    lines, ranked = format_failure_groups(fails)
    print()
    print('\n'.join(lines).rstrip())
    log = []
    by = {key: [] for key, _rels in ranked}
    for rel, text in fails:
        by[B.first_cl_error(text)].append((rel, text))
    for key, _rels in ranked:
        for rel, text in by[key]:
            log.append(f'=== {rel} ===\n{key}\n{text.rstrip()}\n')
    log_path = B.ROOT / 'build/layout/ref_failures.txt'
    log_path.write_text('\n'.join(log), encoding='utf-8', errors='replace')
    print(f'\nfull transcripts: {log_path.relative_to(B.ROOT)}')


def member_at(c, off, depth=0, zh=None, bases=None):
    """(class,member) owning ZH offset `off` in class c, walking the primary base chain."""
    if depth>8 or c not in zh and c not in bases: return None
    ms=zh.get(c,{})
    hits=[(m,o) for m,o in ms.items() if isinstance(o,int) and m!='sizeof' and o==off]
    if hits: return (c,hits[0][0])
    # inside a member aggregate? take the nearest member below off
    below=[(o,m) for m,o in ms.items() if isinstance(o,int) and m!='sizeof' and o<off]
    if bases.get(c):
        r=member_at(bases[c][0],off,depth+1,zh,bases)
        if r: return r
    if below:
        o,m=max(below); return (c,f'{m}+0x{off-o:x}')
    return None


def qual(sym):
    m=re.match(r'\?[^@]*@((?:\?\$[^@]+@)?[A-Za-z_0-9]+)@',sym); return m.group(1) if m else None


def shape(i, X86_OP_MEM, X86_OP_IMM):
    ops=[]
    for o in i.operands:
        if o.type==X86_OP_MEM: ops.append(('mem',o.mem.base,o.mem.index,o.mem.scale,o.size))
        elif o.type==X86_OP_IMM: ops.append(('imm',o.size))
        else: ops.append(('reg',o.reg))
    return (i.mnemonic,tuple(ops))


# A body this small that nothing in retail reaches was named by its ZH shape, so an unshifted access in it
# only echoes ZH's layout and cannot witness a member on its own.
SHAPE_ONLY_MAX = 16


def retail_references(data, secs, thunks):
    """RVA -> references that reach it: rel32 call/jmp sites outside `thunks`, references to a thunk (or thunk
    chain) jumping to it, export table entries, and absolute dwords (vtables, push/mov immediates) naming it
    or such a thunk."""
    base = B.u32(data, B.u32(data, 0x3C) + 0x34)
    text = next(s for s in secs if s['name'] == '.text')
    t0, t1 = text['rva'], text['rva'] + text['size']
    blob = data[text['raw_pointer']:text['raw_pointer'] + text['size']]
    direct = collections.Counter(); into = collections.defaultdict(list)
    for m in re.finditer(rb'[\xe8\xe9]', blob):
        i = m.start()
        if i + 5 > len(blob): break
        site = t0 + i; dst = site + 5 + struct.unpack_from('<i', blob, i + 1)[0]
        if not (t0 <= dst < t1): continue
        if blob[i] == 0xE9 and site in thunks: into[dst].append(site)
        else: direct[dst] += 1
    ptr = collections.Counter()
    exp_rva = B.u32(data, B.u32(data, 0x3C) + 0x78)
    if exp_rva:
        e = B.rva_to_file_offset(secs, exp_rva)
        eat = B.rva_to_file_offset(secs, B.u32(data, e + 0x1C))
        for k in range(B.u32(data, e + 0x14)):
            ptr[B.u32(data, eat + 4 * k)] += 1
    for s in secs:
        raw = data[s['raw_pointer']:s['raw_pointer'] + s['size']]
        for align in range(4):
            for (v,) in struct.iter_unpack('<I', raw[align:len(raw) - (len(raw) - align) % 4]):
                if t0 <= v - base < t1: ptr[v - base] += 1
    def count(rva, seen):
        seen.add(rva)
        return direct[rva] + ptr[rva] + sum(count(t, seen) for t in into.get(rva, ()) if t not in seen)
    return collections.Counter({rva: count(rva, set()) for rva in set(direct) | set(into) | set(ptr)})


def run_witness():
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    from capstone.x86 import X86_OP_MEM, X86_OP_IMM
    md=Cs(CS_ARCH_X86,CS_MODE_32); md.detail=True
    data=B.EXE.read_bytes(); secs=B.pe_sections(data)
    def retail(rva,size):
        o=B.rva_to_file_offset(secs,rva); return data[o:o+size]
    # ---- names -> retail address/size
    addr={}; size={}
    for r in csv.DictReader(open(B.ROOT/'reverse/functions.csv',encoding='utf-8',errors='replace')):
        try: a=int(r['target_rva'],16); addr.setdefault(r['name'],a); size.setdefault(a,int(r['target_size']))
        except: pass
    for r in csv.DictReader(open(B.ROOT/'reverse/symbols.csv',encoding='utf-8',errors='replace')):
        try: addr.setdefault(r['name'],int(r['address'],16))
        except: pass
    # ---- ZH offsets and inheritance
    zh={}
    for h,cls in json.load(open(B.ROOT/'reverse/zh_offsets.json')).items():
        for c,ms in cls.items(): zh.setdefault(c,{}).update(ms)
    bases={}
    for h in list((ZH/'GameEngine/Include').rglob('*.h'))+list((ZH/'GameEngineDevice/Include').rglob('*.h'))+list((ZH/'Libraries/Source/WWVegas').rglob('*.h')):
        txt=h.read_text(encoding='utf-8',errors='replace')
        for m in re.finditer(r'^\s*(?:class|struct)\s+(\w+)\s*:\s*([^{;]+)\{',txt,re.M):
            bl=[re.sub(r'\b(public|protected|private|virtual)\b','',x).strip() for x in m.group(2).split(',')]
            bases.setdefault(m.group(1),[re.sub(r'<.*','',b).strip() for b in bl if b.strip()])
    reach=retail_references(data,secs,{a for a,s in size.items() if s==5})
    objs=list((B.ROOT/'build/layout/ref').glob('*.obj'))+list((B.ROOT/'build/match').glob('reference_*.obj'))
    seen=set(); wit=[]; stats=collections.Counter()
    for p in objs:
        try: st=p.stat(); d,ss,syms=B._object_layout(str(p),st.st_mtime_ns,st.st_size)
        except Exception: continue
        for s in syms:
            n=s['name']
            if s['section']<=0 or not n.startswith('?') or n in seen or n not in addr: continue
            rva=addr[n]; sz=size.get(rva)
            if not sz: continue
            dead=sz<=SHAPE_ONLY_MAX and not reach[rva]
            try: comp,relocs=B.read_object_symbol_bytes(p,n)
            except Exception: continue
            ours=len(comp.rstrip(b'\xcc'))
            if not (0.6*sz<=ours<=1.5*sz): stats['size_out']+=1; continue
            seen.add(n); stats['aligned']+=1
            rel={off for off,rt,x in relocs}
            A=list(md.disasm(bytes(comp[:ours]),0)); R=list(md.disasm(bytes(retail(rva,sz)),0))
            sa=[shape(i, X86_OP_MEM, X86_OP_IMM) for i in A]; sr=[shape(i, X86_OP_MEM, X86_OP_IMM) for i in R]
            sm=difflib.SequenceMatcher(None,sa,sr,autojunk=False)
            q=sm.ratio()
            if q<0.7: stats['low_quality']+=1; continue
            isthis=bool(re.search(r'@@[QIUAEMB][AB]E',n)); thisregs={'ecx'}
            for i in A[:12]:
                if i.mnemonic=='mov' and len(i.operands)==2 and i.operands[0].type not in (X86_OP_MEM,) and i.operands[1].type not in (X86_OP_MEM,X86_OP_IMM) and i.reg_name(i.operands[1].reg) in thisregs:
                    thisregs.add(i.reg_name(i.operands[0].reg))
            cls=qual(n)
            for tag,i1,i2,j1,j2 in sm.get_opcodes():
                if tag!='equal': continue
                for a,r in zip(A[i1:i2],R[j1:j2]):
                    if any(a.address<=off<a.address+a.size for off in rel): continue
                    for oa,orr in zip(a.operands,r.operands):
                        if oa.type==X86_OP_MEM and orr.type==X86_OP_MEM and oa.mem.base and oa.mem.index==0:
                            base=a.reg_name(oa.mem.base)
                            if isthis and base in thisregs and oa.mem.disp>=0:
                                echo=dead and oa.mem.disp==orr.mem.disp; stats['shape_only_echo']+=echo
                                wit.append((cls,oa.mem.disp,orr.mem.disp,n,rva,q,echo))
    print(dict(stats),'witness records',len(wit))
    # aggregate: same-offset witnesses also count (confirm ZH offset unchanged)
    # a shape-only echo counts toward the total but never wins, so it can only lower a member's confidence
    votes=collections.defaultdict(collections.Counter); fns=collections.defaultdict(set); fcls=collections.defaultdict(set)
    live=collections.defaultdict(collections.Counter)
    for cls,z,b,n,rva,q,echo in wit:
        key=member_at(cls,z,zh=zh,bases=bases)
        if key: owner,mem=key
        else: owner,mem=cls,f'+0x{z:x}?'
        k=(owner,mem,z)
        votes[k][b]+=q
        if not echo: live[k][b]+=q; fns[k].add(n); fcls[k].add(cls)
    out=[]
    for (owner,mem,z),c in votes.items():
        if not live[(owner,mem,z)]: continue
        bf=live[(owner,mem,z)].most_common(1)[0][0]; nv=c[bf]
        tot=sum(c.values())
        out.append(dict(owner=owner,fn_class=sorted(fcls[(owner,mem,z)])[0],member=mem,zh=z,bfme=bf,votes=round(nv,1),total=round(tot,1),
                        confidence=round(nv/tot,2),alts={f'{k:#x}':round(v,1) for k,v in c.items() if k!=bf},fns=sorted(fns[(owner,mem,z)])[:3]))
    out.sort(key=lambda o:(o['owner'] or '',o['zh']))
    json.dump(out,open(B.ROOT/'reverse/bfme_layouts.json','w'),indent=0)
    changed=[o for o in out if o['bfme']!=o['zh']]
    print('members witnessed',len(out),'changed',len(changed),'classes',len({o['owner'] or o['fn_class'] for o in out}))
    for o in changed[:40]: print(f"  {(o['owner'] or o['fn_class'] or '?'):28s} {o['member']:34s} zh={o['zh']:#6x} bfme={o['bfme']:#6x} votes={o['votes']}/{o['total']}")


if __name__ == '__main__':
    if '--compile' in sys.argv:
        prefixes=[a for a in sys.argv[1:] if a != '--compile']
        compile_reference(prefixes or None); sys.exit(0)
    run_witness()
