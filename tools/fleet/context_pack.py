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
import sys, csv, json, struct, re, bisect, collections, hashlib, os, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import capstone
from portable_lock import lock

_exe = None; _secs = None; _rows = None; _starts = None; _pins = None; _calls = None; _strings = None; _vt = None
_thunks_of = None
BASE = 0x400000


def call_index(raw, lo, path):
    """Load or build the retail call index with one atomic, image-bound writer.

    Anonymous pickers prepare outside the shared claim lock, so cold readers
    must never see a partially written index from another picker.
    """
    path = Path(path)
    digest = hashlib.sha256(raw).hexdigest()
    with (path.parent / (path.name + '.lock')).open('a+b') as handle:
        lock(handle, exclusive=True)
        try:
            data = json.loads(path.read_text(encoding='utf-8'))
            if (data.get('version') == 1 and data.get('text_sha256') == digest
                    and data.get('text_rva') == lo and isinstance(data.get('calls'), dict)):
                calls = {int(k): v for k, v in data['calls'].items()}
                hi = lo + len(raw)
                if all(lo <= target < hi and isinstance(sites, list)
                       and all(isinstance(site, int) and lo <= site < hi
                               for site in sites)
                       for target, sites in calls.items()):
                    return calls
        except (OSError, ValueError, TypeError, AttributeError):
            pass

        calls = collections.defaultdict(list)
        unpack = struct.Struct('<i').unpack_from
        hi = lo + len(raw)
        i = raw.find(b'\xe8')
        while i != -1 and i + 5 <= len(raw):
            target = lo + i + 5 + unpack(raw, i + 1)[0]
            if lo <= target < hi:
                calls[target].append(lo + i)
            i = raw.find(b'\xe8', i + 1)
        data = {'version': 1, 'text_sha256': digest, 'text_rva': lo,
                'calls': calls}
        temporary = None
        try:
            with tempfile.NamedTemporaryFile('w', encoding='utf-8',
                                             dir=path.parent, prefix=path.name + '.',
                                             suffix='.tmp', delete=False) as out:
                temporary = Path(out.name)
                json.dump(data, out)
            os.replace(temporary, path)
        finally:
            if temporary is not None:
                temporary.unlink(missing_ok=True)
        return dict(calls)


def _load():
    global _exe, _secs, _rows, _starts, _pins, _calls, _strings, _vt, _thunks_of
    if _exe is not None:
        return
    _exe = open(build.EXE, 'rb').read(); _secs = build.pe_sections(_exe)
    _rows = {}
    ledger_rows = list(csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')))
    for r in ledger_rows:
        a = (r['target_rva'] or '')
        if a.startswith('0x'):
            _rows[int(a, 16)] = r
    # Carved candidates are pseudo-rows until add_match lands a real source.
    # Keep the current functions.csv ranges authoritative so a stale carved
    # file cannot resurrect an address that landed between regenerations.
    sys.path.insert(0, str(ROOT / 'tools'))
    import eligibility
    for r in eligibility.carved_rows(rows=ledger_rows):
        _rows.setdefault(int(r['target_rva'], 16), r)
    _starts = sorted(_rows)
    _pins = collections.defaultdict(list)
    for l in open(ROOT / 'reverse/symbols.csv', encoding='utf-8', errors='replace'):
        p = l.rstrip('\n').split(',')
        if len(p) > 1 and p[1].startswith('0x'):
            try:
                _pins[int(p[1], 16)].append((p[0], p[2] if len(p) > 2 else ''))
            except ValueError:
                pass
    t = _secs[0]
    raw = _exe[t['raw_pointer']:t['raw_pointer'] + t['size']]
    _calls = call_index(raw, t['rva'], ROOT / 'build/call_index.json')
    # thunk -> body it lands on, so callers of the thunk count for the body
    _thunks_of = collections.defaultdict(list)
    for s0, r0 in _rows.items():
        if int(r0['target_size'] or 0) == 5:
            t0 = thunk_target(s0)
            if t0 is not None:
                _thunks_of[t0].append(s0)
    _strings = collections.defaultdict(list)
    sx = ROOT / 'reverse/string_xrefs.tsv'
    if sx.exists():
        for l in open(sx, encoding='utf-8', errors='replace'):
            p = l.rstrip('\n').split('\t')
            if len(p) >= 2:
                for a in p[1].split(','):
                    try:
                        site = int(a, 16) - BASE
                    except ValueError:
                        continue
                    o = owner(site)
                    key = int(o['target_rva'], 16) if o else site
                    if p[0] not in _strings[key]:
                        _strings[key].append(p[0])
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


def thunk_target(rva, hops=3):
    """Follow a 5-byte `jmp rel32` incremental-link thunk to the body it lands on."""
    t = _secs[0]; tlo = t['rva']; thi = tlo + t['size']
    cur = rva; seen = None
    for _ in range(hops):
        off = build.rva_to_file_offset(_secs, cur)
        if _exe[off] != 0xE9:
            break
        nxt = cur + 5 + int.from_bytes(_exe[off + 1:off + 5], 'little', signed=True)
        if not (tlo <= nxt < thi):
            break
        seen = cur = nxt
    return seen

def eh_signatures(body, size):
    """What the bytes say about this body's exception handling, and which
    documented levers apply. 57% of open dump bytes carry an EH frame and the
    most common blocker tags are EH codegen, so the recipe goes in the brief."""
    has_frame = (b"\x64\xa1\x00\x00\x00\x00" in body          # mov eax, fs:[0]
                 or b"\x64\x89\x0d\x00\x00\x00\x00" in body   # mov fs:[0], ecx
                 or b"\x64\xff\x35\x00\x00\x00\x00" in body)  # push fs:[0]
    if not has_frame:
        return None
    signs, levers = ["SEH/EH registration frame present"], []
    # EH state stores: mov byte/dword ptr [esp+N], imm (C6 44 24 xx / C7 44 24 xx)
    states = len(re.findall(rb"\xc6\x44\x24.|\xc7\x44\x24.....", body))
    if states:
        signs.append(f"~{states} EH state store(s)")
        levers.append("a state store around a call retail makes with NO state change: declare that "
                      "callee `throw()` (getPreferredMap trio); eh_levers tries this per declaration")
    # saved-esp of a by-value temporary: mov ecx,esp (8B CC) shortly before mov [esp+N],esp (89 64 24 xx)
    if re.search(rb"\x8b\xcc[\s\S]{0,24}\x89\x64\x24.", body):
        signs.append("by-value temporary (mov ecx,esp ... mov [esp+N],esp)")
        levers.append("by-value string arg: the string class must be `class AsciiString : private StringBase<char>` "
                      "with INLINE forwarding ctor/dtor (reference/shims/stringinline/StringInline.h)")
        levers.append("saved-esp displacement one slot off: keep the earlier argument LIVE past the temporary "
                      "(reference it in every expression) instead of copying it to a local")
    if b"\xc7\x44\x24" in body and re.search(rb"\xc7\x44\x24.\xff\xff\xff\xff", body):
        signs.append("EH state reset to -1")
        levers.append("extra `mov [esp+N],-1` after array new / vector ctor: declare "
                      "`void __cdecl operator delete[](void *) throw();` before the includes")
    levers.append("destructor of a temporary/RAII local sits LATER in ours: give the local its own nested "
                  "`{ }` block ending where retail's destructor call sits")
    levers.append("STLport helper out of line or an extra try region: `#define _STLP_NO_EXCEPTIONS 1` "
                  "before the first STL include; extra EH states 0/2/4 around atexit: the TU wants /EHsc")
    return {"signs": signs, "levers": levers}


_layouts = None
def layout_lines(rva, vt_entry, limit=10):
    """BFME offsets witnessed for the body's class (reverse/bfme_layouts.json,
    built by tools/layout_witness.py): the members that MOVED from ZH, highest
    confidence first. The class comes from the vtable entry or the pinned name."""
    global _layouts
    if _layouts is None:
        try:
            rows = json.load(open(ROOT / 'reverse/bfme_layouts.json', encoding='utf-8'))
        except OSError:
            rows = []
        _layouts = {}
        for r in rows:
            _layouts.setdefault(r['owner'] or r['fn_class'] or '?', []).append(r)
    classes = []
    if vt_entry and vt_entry.get('names'):
        classes.append(vt_entry['names'][0][0])
    for n, _ in _pins.get(rva, []):
        m = re.match(r'\?[^@]*@((?:\?\$[^@]+@)?[A-Za-z_0-9]+)@', n)
        if m and m.group(1) not in classes:
            classes.append(m.group(1))
    # no vtable, no pin: the class of a strong or plausible ZH fuzzy twin is the
    # best lead an anonymous body has, and layout/offset drift is what 79% of
    # failed anonymous sessions name
    if not classes:
        twin = (_twins or {}).get(rva) if _twins is not None else None
        if twin is None and _twins is None:
            zh_twin_lines(rva); twin = (_twins or {}).get(rva)
        if twin and twin['similarity'] >= 0.7:
            m = re.match(r'\?[^@]*@((?:\?\$[^@]+@)?[A-Za-z_0-9]+)@', twin['symbol'])
            if m:
                classes.append(m.group(1))
    out = []
    for cls in classes[:2]:
        rows = [r for r in _layouts.get(cls, []) if r['bfme'] != r['zh'] and r['votes'] >= 1.5 and r['confidence'] >= 0.6]
        if not rows:
            continue
        rows.sort(key=lambda r: (-r['confidence'], -r['votes']))
        out.append(f"  BFME layout of {cls} (moved from ZH; tools/bfme_layout.py {cls} for all {len(_layouts[cls])} witnessed members):")
        out.append("    " + ', '.join(f"{r['member']} zh+0x{r['zh']:X}->+0x{r['bfme']:X}" for r in rows[:limit]))
    return out

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
    eh = eh_signatures(body, size)
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
            line = f"    0x{tgt:08X} x{len(sites)}  -> {name_of(tgt)}"
            real = thunk_target(tgt)
            if real is not None:
                line += f"  => jmp 0x{real:08X} {name_of(real)}"
            out.append(line)
        if len(callees) > max_items:
            out.append(f"    ... {len(callees) - max_items} more distinct target(s) omitted; "
                       f"full inventory: python3 tools/callees.py 0x{rva:08X} {size}")
    callers = list(_calls.get(rva, []))
    via_thunk = 0
    for th in _thunks_of.get(rva, ()):
        sites = _calls.get(th, [])
        via_thunk += len(sites)
        callers.extend(sites)
    if callers:
        named = collections.Counter()
        for site in callers:
            o = owner(site)
            if o:
                named[(o['name'][:60], o['source'].split('/')[-1])] += 1
        how = f", {via_thunk} via ILT thunk" if via_thunk else ""
        out.append(f"  callers ({len(callers)} sites{how}): " + '; '.join(f"{n} @ {s} x{c}" for (n, s), c in named.most_common(4)))
    else:
        try:
            carved_callers = int(r.get("callers") or 0)
        except (TypeError, ValueError):
            carved_callers = 0
        if carved_callers:
            out.append(f"  callers ({carved_callers} REL32 call/jmp site(s); carved boundary evidence)")
    if eh:
        out.append("  EH FRAME: " + "; ".join(eh["signs"]))
        out.append("    levers (docs/shape_levers.md; mechanical ones via "
                   "`python3 tools/eh_levers.py SRC.cpp > choices.json` + shape_search.py):")
        for line in eh["levers"]:
            out.append("      - " + line)
        out.append("    non-EH shape choices (including loop inversion and branch-length "
                   "polarity): `python3 tools/shape_family_levers.py SRC.cpp "
                   "--families sib,register,bool,test,copy,store,loop,branch,constant,frame > choices.json` + shape_search.py; "
                   "probe and the byte gate still decide whether a choice is useful")
    if vtstore:
        out.append("  installs vtable(s): " + ', '.join(f"0x{v:08X}" for v in vtstore[:4]) + "  (tools/vtable_lookup.py names the class)")
    e = _vt.get(rva)
    if e:
        cls = e['names'][0][0] if e['names'] else '?'
        out.append(f"  vtable slot: member of vtable 0x{e['vt']:08X} ({cls}; {e['landed']} slots landed, {e['dump_n']} still dumps) -> python tools/fleet/pick_class.py --vt 0x{e['vt']:08X} --dry for the slot table")
    if fields:
        out.append("  this-relative fields in the first 0x40 bytes: " + ', '.join(f"+0x{d:X}" for d, _ in sorted(fields.items())[:12]))
    lay = layout_lines(rva, e)
    if lay:
        out.extend(lay)
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
    out += zh_twin_lines(rva)
    return out


_twins = None


def zh_twin_lines(rva):
    """reverse/zh_fuzzy_twins.tsv: the compiled Zero Hour function whose SHAPE is
    closest to this body (tools/zh_fuzzy_twins.py). Exact-byte matching never
    placed it because BFME changed the code; the shape still names a class to
    test and a source to start from. A hypothesis, never identity evidence."""
    global _twins
    if _twins is None:
        try:
            sys.path.insert(0, str(ROOT / 'tools'))
            import zh_fuzzy_twins
            _twins = zh_fuzzy_twins.load_twins()
        except Exception:  # noqa: BLE001  (a missing table must not break a brief)
            _twins = {}
    twin = _twins.get(rva)
    if not twin:
        return []
    # share of top-1 answers that were right on 1,742 bodies whose twin is known (2026-09-21)
    sure = ("strong, right ~95% of the time" if twin['similarity'] >= 0.8 and twin['margin'] >= 0.05
            else "plausible, right ~85% of the time" if twin['similarity'] >= 0.7
            else "weak, right ~70% of the time")
    return [f"  ZH fuzzy twin ({sure}: shape similarity {twin['similarity']:.2f}, {twin['margin']:.2f} over the runner-up): "
            f"{twin['symbol'][:120]}",
            f"      source: {twin['source']}",
            "      HYPOTHESIS ONLY. Start from that source and its class; BFME moved members (tools/bfme_layout.py CLASS) and "
            "added code. Pin the real name only after a caller, vtable slot or literal proves it; otherwise land under an opaque name."]


if __name__ == '__main__':
    for a in sys.argv[1:]:
        print('\n'.join(pack(int(a, 16))))
