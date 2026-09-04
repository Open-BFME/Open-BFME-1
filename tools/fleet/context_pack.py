#!/usr/bin/env python3
"""Per-body evidence pack for worker briefs.

A seat's first 20-30 minutes on a body go to rediscovering the same facts from
the retail bytes: what it calls, who calls it, which vtable it sits in, which
strings it touches, which fields of `this` it reads, and what its landed
neighbours look like. All of that is mechanical, so this prints it once.

  python tools/fleet/context_pack.py 0xRVA [0xRVA ...]
Library use: pack(rva) -> list of lines. First run builds build/call_index.json
(every REL32 call site in .text keyed by target) in ~20 s; later runs reuse it.
Read-only against the ledgers."""
import sys, csv, json, struct, re, bisect, collections
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import capstone

_exe = None; _secs = None; _rows = None; _starts = None; _pins = None; _calls = None; _strings = None; _vt = None
BASE = 0x400000


def _load():
    global _exe, _secs, _rows, _starts, _pins, _calls, _strings, _vt
    if _exe is not None:
        return
    _exe = open(build.EXE, 'rb').read(); _secs = build.pe_sections(_exe)
    _rows = {}
    for r in csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')):
        a = (r['target_rva'] or '')
        if a.startswith('0x'):
            _rows[int(a, 16)] = r
    _starts = sorted(_rows)
    _pins = collections.defaultdict(list)
    for l in open(ROOT / 'reverse/symbols.csv', encoding='utf-8', errors='replace'):
        p = l.rstrip('\n').split(',')
        if len(p) > 1 and p[1].startswith('0x'):
            try:
                _pins[int(p[1], 16)].append((p[0], p[2] if len(p) > 2 else ''))
            except ValueError:
                pass
    ci = ROOT / 'build/call_index.json'
    if ci.exists():
        _calls = {int(k): v for k, v in json.load(open(ci)).items()}
    else:
        t = _secs[0]; raw = _exe[t['raw_pointer']:t['raw_pointer'] + t['size']]; lo = t['rva']; hi = lo + t['size']
        _calls = collections.defaultdict(list)
        u = struct.Struct('<i').unpack_from
        i = raw.find(b'\xe8')
        while i != -1 and i + 5 <= len(raw):
            tgt = lo + i + 5 + u(raw, i + 1)[0]
            if lo <= tgt < hi:
                _calls[tgt].append(lo + i)
            i = raw.find(b'\xe8', i + 1)
        json.dump(_calls, open(ci, 'w'))
    _strings = collections.defaultdict(list)
    sx = ROOT / 'reverse/string_xrefs.tsv'
    if sx.exists():
        for l in open(sx, encoding='utf-8', errors='replace'):
            p = l.rstrip('\n').split('\t')
            if len(p) >= 2:
                for a in p[1].split(','):
                    try:
                        _strings[int(a, 16) - BASE].append(p[0])
                    except ValueError:
                        pass
    _vt = {}
    vj = ROOT / 'build/vtable_class_rank.json'
    if vj.exists():
        for e in json.load(open(vj)):
            for a in e['dump_rvas']:
                _vt[a] = e


def owner(addr):
    """ledger row containing addr, or None"""
    i = bisect.bisect_right(_starts, addr) - 1
    if i < 0:
        return None
    s = _starts[i]; r = _rows[s]
    return r if addr < s + int(r['target_size'] or 0) else None


def name_of(rva):
    r = _rows.get(rva)
    real = [n for n, _ in _pins.get(rva, []) if not re.match(r'^\?(d_|b_|j_|dup_|gen)', n)]
    if r and not r['source'].endswith('.asm') and not r['source'].startswith('Code/gen_'):
        return f"{r['name'][:70]} @ {r['source'].split('/')[-1]}"
    if real:
        return f"pinned {real[0][:70]} (still a dump)"
    if r:
        return f"{r['name'][:40]} ({'dump' if r['source'].endswith('.asm') else r['source'].split('/')[-1]})"
    return 'not in ledger'


def pack(rva, max_items=8):
    _load()
    r = _rows.get(rva)
    if not r:
        return [f"0x{rva:08X}: not in ledger"]
    size = int(r['target_size'] or 0)
    body = _exe[build.rva_to_file_offset(_secs, rva):][:size]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
    callees = collections.OrderedDict(); fields = collections.Counter(); globs = collections.OrderedDict(); vtstore = []
    t = _secs[0]; tlo = t['rva']; thi = tlo + t['size']
    for ins in md.disasm(body, rva):
        if ins.mnemonic in ('call', 'jmp') and ins.op_str.startswith('0x'):
            tgt = int(ins.op_str, 16)
            if tlo <= tgt < thi and not (rva <= tgt < rva + size):
                callees.setdefault(tgt, []).append(ins.address - rva)
        for op in ins.operands:
            if op.type == capstone.x86.X86_OP_MEM:
                if op.mem.base == capstone.x86.X86_REG_ECX and op.mem.index == 0 and ins.address - rva < 0x40:
                    fields[op.mem.disp] += 1
                if op.mem.base == 0 and op.mem.index == 0 and op.mem.disp >= BASE:
                    globs.setdefault(op.mem.disp - BASE, ins.mnemonic)
            elif op.type == capstone.x86.X86_OP_IMM and BASE + 0x1000 <= op.imm < BASE + 0x2000000:
                if ins.mnemonic == 'mov' and ins.operands[0].type == capstone.x86.X86_OP_MEM:
                    vtstore.append(op.imm)
    out = [f"EVIDENCE for 0x{rva:08X} ({size} B, dump {r['source'].split('/')[-1]}):"]
    if callees:
        out.append("  callees (retail REL32 targets, in body order):")
        for tgt, sites in list(callees.items())[:max_items]:
            out.append(f"    0x{tgt:08X} x{len(sites)}  -> {name_of(tgt)}")
    callers = _calls.get(rva, [])
    if callers:
        named = collections.Counter()
        for site in callers:
            o = owner(site)
            if o:
                named[(o['name'][:60], o['source'].split('/')[-1])] += 1
        out.append(f"  callers ({len(callers)} sites): " + '; '.join(f"{n} @ {s} x{c}" for (n, s), c in named.most_common(4)))
    if vtstore:
        out.append("  installs vtable(s): " + ', '.join(f"0x{v:08X}" for v in vtstore[:4]) + "  (tools/vtable_lookup.py names the class)")
    e = _vt.get(rva)
    if e:
        cls = e['names'][0][0] if e['names'] else '?'
        out.append(f"  vtable slot: member of vtable 0x{e['vt']:08X} ({cls}; {e['landed']} slots landed, {e['dump_n']} still dumps) -> python build/pick_class.py --vt 0x{e['vt']:08X} --dry for the slot table")
    if fields:
        out.append("  this-relative fields in the first 0x40 bytes: " + ', '.join(f"+0x{d:X}" for d, _ in sorted(fields.items())[:12]))
    strs = _strings.get(rva, [])
    if strs:
        out.append("  strings: " + ' | '.join(s[:50] for s in strs[:5]))
    if globs:
        out.append("  globals: " + ', '.join(f"0x{g + BASE:08X}" for g in list(globs)[:6]) + "  (grep the VA in symbols.csv)")
    i = bisect.bisect_left(_starts, rva)
    nb = []
    for j in (i - 2, i - 1, i + 1, i + 2):
        if 0 <= j < len(_starts):
            n = _rows[_starts[j]]
            if not n['source'].endswith('.asm') and not n['source'].startswith('Code/gen_'):
                nb.append(f"0x{_starts[j]:08X} {n['name'][:50]} @ {n['source'].split('/')[-1]}")
    if nb:
        out.append("  landed neighbours: " + '; '.join(nb))
    return out


if __name__ == '__main__':
    for a in sys.argv[1:]:
        print('\n'.join(pack(int(a, 16))))
