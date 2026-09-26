#!/usr/bin/env python3
"""Read BFME's module registry straight out of the retail image.

WHY THIS EXISTS. `game/GameEngine/Source/Common/Thing/ModuleFactory.cpp` is Zero
Hour's file: its `addModule(X)` list names 224 ZH module classes, and the
compiler emits `X::friend_newModuleInstance` / `X::friend_newModuleData` for
every one of them. Those emitted bodies are three-instruction allocate-and-
construct shells, so many of them byte-match SOME retail body whether or not
BFME ever shipped class X -- and `build.py` masks DIR32 operands, which erases
the only bytes that could tell two of them apart. That is how 12 names ended up
green on 0x0011E2D0 and 13 on 0x0024FC20.

THE ORACLE. BFME registers every module it owns by a string literal, from two
functions and nowhere else:

    ?init@ModuleFactory@@UAEXXZ   0x0012C2E0   246 modules
    the W3D draw registrar        0x006BFFE0    16 draw modules

Each registration writes a ModuleTemplate {+0 newModuleInstance, +4
newModuleData, +8 moduleData, +0xC interfaceMask}, in one of two shapes the
compiler chose per call site:

  addModuleInternal  push mask; push &name; push type; push 0; push data;
                     push inst; call ?addModuleInternal@ModuleFactory@@
  mapAssign          call makeDecoratedNameKey; call ModuleTemplateMap::operator[];
                     mov [eax], inst; mov [eax+4], data; mov [eax+0xC], mask

Both are read here. The result is a 262-row bijection name -> newModuleInstance
(no two registered modules share one instance body), so any ledger row spelling
`?friend_newModuleInstance@X@@` at an address this table assigns to Y != X is
provably the wrong name for that body.

CORROBORATION, INDEPENDENT OF THE REGISTRY. Every newModuleData body ends in
`INI::initFromINIMultiProc(data, X::buildFieldParse)`, and that field-parse proc
carries its own class name as a literal. Spot-checked on the four bodies at
0x00114A40/B50/C60/D70: the literal agrees with this table and contradicts the
ledger in all four.

  python3 tools/module_registry.py            # write targets/game/reverse/module_registry.tsv
  python3 tools/module_registry.py --check    # cross-check targets/game/reverse/functions.csv
"""
import bisect, collections, csv, re, struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

OUT = build.ROOT / 'targets/game/reverse/module_registry.tsv'
MODULE_FACTORY_INIT = '?init@ModuleFactory@@UAEXXZ'
DRAW_REGISTRAR_ANCHOR = 'W3DDefaultDraw'   # first literal the W3D registrar pushes
ADD_MODULE_INTERNAL = 0x00129AC0           # ?addModuleInternal@ModuleFactory@@IAEXPBX00HABVAsciiString@@H@Z
MODULE_TEMPLATE_MAP_AT = 0x001296E0        # ??A?$map@HVModuleTemplate@ModuleFactory@@...
OPERATOR_NEW = 0x00881F30                  # ??2@YAPAXI@Z

DATA = build.EXE.read_bytes()
SECS = build.pe_sections(DATA)
TEXT = next(s for s in SECS if s['name'] == '.text')
MD = Cs(CS_ARCH_X86, CS_MODE_32)


def follow(rva, depth=0):
    """Resolve an ILT jmp-thunk chain to the body it lands on."""
    if depth > 8:
        raise SystemExit(f"thunk chain from 0x{rva:08X} does not terminate")
    off = build.rva_to_file_offset(SECS, rva)
    if off is None:
        return rva
    if DATA[off] == 0xE9:
        return follow(rva + 5 + struct.unpack_from('<i', DATA, off + 1)[0], depth + 1)
    if DATA[off] == 0xEB:
        return follow(rva + 2 + struct.unpack_from('<b', DATA, off + 1)[0], depth + 1)
    return rva


def cstring(rva):
    for s in SECS:
        if s['rva'] <= rva < s['rva'] + s['size']:
            o = s['raw_pointer'] + (rva - s['rva'])
            end = DATA.find(b'\0', o, o + 96)
            if end < 0:
                return None
            b = DATA[o:end]
            if 3 <= len(b) <= 64 and all(32 <= c < 127 for c in b):
                return b.decode('ascii')
    return None


def in_text(rva):
    return TEXT['rva'] <= rva < TEXT['rva'] + TEXT['size']


def ledger_rows():
    with open(build.ROOT / 'targets/game/reverse/functions.csv', newline='', encoding='utf-8', errors='replace') as f:
        return list(csv.DictReader(f))


def calls_a_registrar(rva, size):
    off = build.rva_to_file_offset(SECS, rva)
    for x in MD.disasm(DATA[off:off + size], 0x400000 + rva):
        if x.mnemonic == 'call' and x.op_str.startswith('0x'):
            if follow(int(x.op_str, 16) - 0x400000) in (ADD_MODULE_INTERNAL, MODULE_TEMPLATE_MAP_AT):
                return True
    return False


def find_registrars(rows):
    """Locate both registration functions by evidence, never by a guessed address."""
    init = [r for r in rows if r['name'] == MODULE_FACTORY_INIT]
    if len(init) != 1:
        raise SystemExit(f"expected exactly one ledger row named {MODULE_FACTORY_INIT}, found {len(init)}")
    spans = sorted((int(r['target_rva'], 16), int(r['target_size'] or 0), r['name'])
                   for r in rows if (r['target_size'] or '').strip())
    starts = [s[0] for s in spans]

    lit = None
    needle = DRAW_REGISTRAR_ANCHOR.encode() + b'\0'
    i = DATA.find(needle)
    while i >= 0:
        if DATA[i - 1] == 0:
            for s in SECS:
                if s['raw_pointer'] <= i < s['raw_pointer'] + s['size']:
                    lit = s['rva'] + (i - s['raw_pointer'])
        i = DATA.find(needle, i + 1)
    if lit is None:
        raise SystemExit(f"literal {DRAW_REGISTRAR_ANCHOR!r} not found in the image")

    owners = set()
    va = struct.pack('<I', 0x400000 + lit)
    j = DATA.find(va)
    while j >= 0:
        for s in SECS:
            if s['name'] == '.text' and s['raw_pointer'] <= j < s['raw_pointer'] + s['size']:
                site = s['rva'] + (j - s['raw_pointer'])
                k = bisect.bisect_right(starts, site) - 1
                if k >= 0 and spans[k][0] <= site < spans[k][0] + spans[k][1]:
                    owners.add((spans[k][0], spans[k][1]))
        j = DATA.find(va, j + 1)
    # Several bodies mention that literal; the registrar is the one that also
    # drives a registration, so keep only owners that call into ModuleFactory.
    registrars = [o for o in sorted(owners) if calls_a_registrar(*o)]
    if len(registrars) != 1:
        raise SystemExit(f"expected exactly one registering owner of the {DRAW_REGISTRAR_ANCHOR!r} "
                         f"reference, found {[(hex(a), n) for a, n in registrars]}")
    draw = registrars[0]
    return [(int(init[0]['target_rva'], 16), int(init[0]['target_size']), 'ModuleFactory::init'),
            (draw[0], draw[1], 'W3D draw registrar')]


def scan(fn_rva, fn_size, origin):
    off = build.rva_to_file_offset(SECS, fn_rva)
    ins = list(MD.disasm(DATA[off:off + fn_size], 0x400000 + fn_rva))
    marks = [i for i, x in enumerate(ins)
             if x.mnemonic == 'push' and x.op_str.startswith('0x')
             and (cstring(int(x.op_str, 16) - 0x400000) or '')[:1].isupper()]
    out = []
    for n, i in enumerate(marks):
        stop = marks[n + 1] if n + 1 < len(marks) else len(ins)
        name = cstring(int(ins[i].op_str, 16) - 0x400000)
        rec = dict(name=name, origin=origin, site=ins[i].address - 0x400000,
                   literal=int(ins[i].op_str, 16) - 0x400000,
                   shape=None, inst=None, data=None, mask=None)
        ptrs, imms = [], []
        for j in range(i + 1, stop):
            x = ins[j]
            if x.mnemonic == 'push' and x.op_str.startswith('0x'):
                raw = int(x.op_str, 16)
                if in_text(raw - 0x400000):
                    ptrs.append(raw - 0x400000)
                else:
                    imms.append(raw)
            elif x.mnemonic == 'push' and x.op_str.isdigit():
                imms.append(int(x.op_str))
            elif x.mnemonic == 'call' and x.op_str.startswith('0x'):
                target = follow(int(x.op_str, 16) - 0x400000)
                if target == ADD_MODULE_INTERNAL:
                    if len(ptrs) < 2:
                        raise SystemExit(f"{name}: addModuleInternal call with {len(ptrs)} function pointers")
                    rec.update(shape='addModuleInternal', inst=follow(ptrs[-1]),
                               data=follow(ptrs[-2]), mask=imms[0] if imms else None)
                    break
                if target == MODULE_TEMPLATE_MAP_AT:
                    for y in ins[j + 1:j + 12]:
                        m = re.match(r'^dword ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\], (0x[0-9a-f]+)$', y.op_str)
                        if y.mnemonic != 'mov' or not m:
                            continue
                        disp = int(m.group(1), 0) if m.group(1) else 0
                        val = int(m.group(2), 16) - 0x400000
                        if disp == 0 and in_text(val):
                            rec['inst'] = follow(val)
                        elif disp == 4 and in_text(val):
                            rec['data'] = follow(val)
                        elif disp == 0xC:
                            rec['mask'] = val + 0x400000
                    rec['shape'] = 'mapAssign'
                    break
        if rec['inst'] is None or rec['data'] is None:
            raise SystemExit(f"{name} at 0x{rec['site']:08X}: no factory pointers recovered")
        out.append(rec)
    return out


def instance_body(rva, size):
    """A newModuleInstance body is `new(sizeof(X)); X::X(thing, data)`, so it
    yields the class's object size and its constructor -- the pair the ledger's
    ??0X@@QAE@PAVThing@@PBVModuleData@@@Z rows claim. Reading it here is what
    makes those rows checkable: 262 registered modules resolve to 260 distinct
    constructors, so the map is near-bijective and a constructor row on an
    address it assigns elsewhere is misnamed."""
    off = build.rva_to_file_offset(SECS, rva)
    alloc = ctor = None
    for x in MD.disasm(DATA[off:off + size], 0x400000 + rva):
        if x.mnemonic == 'push' and x.op_str.startswith('0x') and int(x.op_str, 16) < 0x2000 and alloc is None:
            alloc = int(x.op_str, 16)
        elif x.mnemonic == 'call' and x.op_str.startswith('0x') and alloc is not None:
            target = follow(int(x.op_str, 16) - 0x400000)
            if target != OPERATOR_NEW:
                ctor = target
                break
    return alloc, ctor


def build_table():
    rows = ledger_rows()
    recs = []
    for rva, size, origin in find_registrars(rows):
        recs += scan(rva, size, origin)
    sizes = {}
    for r in rows:
        try:
            sizes.setdefault(int(r['target_rva'], 16), int(r['target_size'] or 0))
        except ValueError:
            pass
    for r in recs:
        r['object_size'], r['ctor'] = instance_body(r['inst'], sizes.get(r['inst']) or 96)
    seen = collections.Counter(r['inst'] for r in recs)
    folded = [a for a, n in seen.items() if n > 1]
    if folded:
        print(f"note: {len(folded)} newModuleInstance bodies serve more than one registration", file=sys.stderr)
    return recs


def write_table(recs):
    with open(OUT, 'w', newline='', encoding='utf-8') as f:
        w = csv.writer(f, delimiter='\t', lineterminator='\r\n')
        w.writerow(['module', 'origin', 'shape', 'reg_site_rva', 'name_literal_rva',
                    'new_module_instance_rva', 'new_module_data_rva', 'interface_mask',
                    'object_size', 'constructor_rva'])
        for r in sorted(recs, key=lambda x: x['name']):
            w.writerow([r['name'], r['origin'], r['shape'], f"0x{r['site']:08X}",
                        f"0x{r['literal']:08X}", f"0x{r['inst']:08X}", f"0x{r['data']:08X}",
                        '' if r['mask'] is None else f"0x{r['mask']:X}",
                        '' if r['object_size'] is None else f"0x{r['object_size']:X}",
                        '' if r['ctor'] is None else f"0x{r['ctor']:08X}"])
    print(f"{OUT.relative_to(build.ROOT)}: {len(recs)} registrations, "
          f"{len({r['name'] for r in recs})} distinct module names")


KIND = re.compile(r'^\?(friend_newModuleInstance|friend_newModuleData)@([A-Za-z0-9_]+)@@')
CTOR = re.compile(r'^\?\?0([A-Za-z0-9_]+)@@QAE@PAVThing@@PBVModuleData@@@Z$')


def check(recs):
    owners = {'friend_newModuleInstance': collections.defaultdict(set),
              'friend_newModuleData': collections.defaultdict(set)}
    for r in recs:
        owners['friend_newModuleInstance'][r['inst']].add(r['name'])
        owners['friend_newModuleData'][r['data']].add(r['name'])
    agree, disagree = 0, []
    for r in ledger_rows():
        m = KIND.match(r['name'])
        if not m:
            continue
        try:
            addr = int(r['target_rva'], 16)
        except ValueError:
            continue
        who = owners[m.group(1)].get(addr)
        if not who:
            continue
        if m.group(2) in who:
            agree += 1
        else:
            disagree.append((r['target_rva'], m.group(2), sorted(who), r['source']))
    print(f"friend_new* rows on a registry address: {agree} agree, {len(disagree)} disagree")
    for rva, claimed, real, src in sorted(disagree):
        print(f"  {rva}  ledger says {claimed:38s} registry says {'|'.join(real):38s} {src}")

    by_ctor = collections.defaultdict(set)
    for r in recs:
        if r['ctor']:
            by_ctor[r['ctor']].add(r['name'])
    cagree, cbad = 0, []
    for r in ledger_rows():
        m = CTOR.match(r['name'])
        if not m:
            continue
        try:
            addr = int(r['target_rva'], 16)
        except ValueError:
            continue
        who = by_ctor.get(addr)
        if not who:
            continue
        if m.group(1) in who:
            cagree += 1
        else:
            cbad.append((r['target_rva'], m.group(1), sorted(who), r['source']))
    print(f"module constructor rows on a mapped constructor: {cagree} agree, {len(cbad)} disagree")
    for rva, claimed, real, src in sorted(cbad):
        print(f"  {rva}  ledger says {claimed:38s} registry says {'|'.join(real):38s} {src}")
    return len(disagree) + len(cbad)


if __name__ == '__main__':
    table = build_table()
    if '--check' in sys.argv:
        check(table)
    else:
        write_table(table)
