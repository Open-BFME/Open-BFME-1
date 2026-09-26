"""Name anonymous dumps from the call graph instead of from their bytes.

`tools/locate.py` places a function by matching its compiled bytes. When it
reports `unlocated (drifted or not in this binary)` the bytes no longer agree, so
byte-scanning can never find that function and the 5.0 MB sitting in
`?d_xxxxxxxx@@YAXXZ` dumps stays anonymous.

The call graph does not care about drift. A dump called from exactly one named
function is pinned by that caller: open the caller's Zero Hour source, read what it
calls at that point, and the dump has a name. That is how `?d_000efe10@@YAXXZ` was
identified as `TeamFactory::findTeamPrototype` - two named callers agreed.

Usage:
    python3 tools/callers_of.py 0x000efe10        # who calls this address
    python3 tools/callers_of.py --report [N]      # best N naming candidates
    python3 tools/callers_of.py --files [N]       # ...plus the source file each names
    python3 tools/callers_of.py --closure targets/game/reverse/game_end/seeds.json

`--report` lists anonymous dumps that have exactly one distinct named caller,
largest first, which are the ones a single source read can settle.

`--closure` measures how much of a seeded region of the call graph we hold as
source and under a real name. Per seed group it walks callees to `depth` and
callers to `updepth` (both capped per group by `caps`) from the seeds, from the
bodies behind the group's vtables and from the functions that call through the
listed slots of its named globals, over every Ghidra and ledger start. Each
function lands in one group at its shallowest depth. The table counts functions
and bytes per group and tier (min(depth, 2)) by ledger state - UNCLAIMED (no
row), ASM (gen-dump, naked or masm body), SMALL (gen_small), LIB
(game/Libraries), CPP - and by identity: a function is identified when a ledger
row or a symbols.csv pin at its address carries a non-anonymous name.

Direct `E8`/`E9` displacements are followed through link thunk chains, and a
target only counts when it is a known function start, which is what keeps stray
matches inside instruction operands out of the results.
"""
import bisect
import collections
import csv
import json
import re
import struct
import sys
from pathlib import Path

import build
import progress

EXE = 'inputs/baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe'
ANON = re.compile(r'^\?[dj]i?_[0-9a-f]{8}@@YAXXZ$')
IMAGE_BASE = 0x400000
CALL = re.compile(rb'[\xe8\xe9]')
STATES = ('UNCLAIMED', 'ASM', 'SMALL', 'LIB', 'CPP')
COLUMNS = STATES + ('identified', 'anonymous')
SEED_KEYS = {'depth', 'updepth', 'caps', 'groups', 'vtables', 'vcalls',
             'anonymous_prefixes', 'anonymous_substrings'}


def load_image():
    data = open(EXE, 'rb').read()
    pe = data.index(b'PE\0\0')
    nsec = struct.unpack_from('<H', data, pe + 6)[0]
    optsz = struct.unpack_from('<H', data, pe + 20)[0]
    tab = pe + 24 + optsz
    secs = []
    for i in range(nsec):
        s = tab + 40 * i
        va = struct.unpack_from('<I', data, s + 12)[0]
        vsz = struct.unpack_from('<I', data, s + 16)[0]
        raw = struct.unpack_from('<I', data, s + 20)[0]
        secs.append((va, vsz, raw))
    return data, secs


def make_off(secs):
    def off(rva):
        for va, vsz, raw in secs:
            if va <= rva < va + vsz:
                return raw + (rva - va)
        return None
    return off


def load_rows():
    """Return (starts, sized, anon, named) keyed by RVA."""
    starts, sized, anon, named = set(), {}, {}, {}
    for r in csv.DictReader(open('targets/game/reverse/functions.csv', newline='')):
        try:
            rva = int(r['target_rva'], 16)
            size = int(r['target_size'] or 0)
        except (ValueError, KeyError):
            continue
        starts.add(rva)
        sized[rva] = size
        if ANON.match(r['name']):
            anon[rva] = (size, r['name'])
        else:
            named[rva] = r['name']
    return starts, sized, anon, named


def thunk_resolver(data, off, starts, sized):
    """Follow `jmp rel32` chains to the body they land on.

    A jump that is not a known start, or a start of at most 5 bytes, is an
    alias of its target rather than a function of its own.
    """
    thunk = {}

    def resolve(rva):
        if rva not in thunk:
            out = rva
            for _ in range(8):
                o = off(out)
                if o is None or o + 5 > len(data) or data[o] != 0xE9 \
                        or (out in starts and sized.get(out, 0) > 5):
                    break
                out = out + 5 + struct.unpack_from('<i', data, o + 1)[0]
            thunk[rva] = out
        return thunk[rva]
    return resolve


def build_edges(data, off, starts, sized, scan, resolve):
    """caller RVA -> set of callee RVAs over the bodies in `scan`."""
    edges = collections.defaultdict(set)
    for rva in scan:
        size = sized.get(rva, 0)
        o = off(rva)
        # A thunk is an alias of its target, not a caller of it.
        if size < 5 or o is None or resolve(rva) != rva:
            continue
        body = data[o:o + size]
        i = 0
        while True:
            hit = CALL.search(body, i, len(body) - 4)
            if hit is None:
                break
            i = hit.start()
            tgt = resolve(rva + i + 5 + struct.unpack_from('<i', body, i + 1)[0])
            if tgt in starts and tgt != rva:
                edges[rva].add(tgt)
            i += 5
    return edges


def file_literal(data, off, rva, size):
    """The basename of any __FILE__ path a body pushes.

    Retail keeps the assert paths, so a body that asserts names the translation
    unit it was compiled in. That survives drift, which is the point.
    """
    o = off(rva)
    if o is None:
        return None
    body = data[o:o + size]
    i = 0
    while i < len(body) - 4:
        if body[i] == 0x68:
            va = struct.unpack_from('<I', body, i + 1)[0]
            fo = off(va - IMAGE_BASE) if va > IMAGE_BASE else None
            if fo is not None:
                s = data[fo:fo + 160].split(b'\0')[0]
                if s[:3].lower() in (b'f:\\', b'c:\\') and (b'.cpp' in s or b'.h' in s):
                    return s.decode('latin1').replace('\\', '/').split('/')[-1]
            i += 5
            continue
        i += 1
    return None


def vtable_bodies(data, off, resolve, starts, text, va):
    """Starts behind a vtable's slots, in slot order.

    The table ends at the first entry that is not a .text pointer: the next
    table's RTTI locator, or padding.
    """
    lo, hi = text
    o = off(va - IMAGE_BASE)
    if o is None:
        sys.exit('vtable 0x%08X lies in no section' % va)
    out = []
    for slot in range(256):
        ptr = struct.unpack_from('<I', data, o + 4 * slot)[0] - IMAGE_BASE
        if not lo <= ptr < hi:
            return out
        body = resolve(ptr)
        if body in starts:
            out.append(body)
        else:
            print('vtable 0x%08X slot 0x%X: body 0x%08X is no known start, skipped'
                  % (va, 4 * slot, body), file=sys.stderr)
    sys.exit('vtable 0x%08X: 256 .text pointers and no end' % va)


def vcall_sites(text, lo, bounds, global_va, slots):
    """Functions that load the global and later call through one of `slots` off
    a register: the virtual calls an E8 scan cannot see.

    The search runs from the load to the end of the function that contains it.
    A byte window instead of that boundary silently under-reports -- 48 bytes
    finds 10 of the 15 `TheNetwork` sites -- and a metric that quietly misses
    callers reads as coverage we do not have.
    """
    hits = set()
    for load in (b'\x8b\x0d', b'\xa1', b'\x8b\x15'):  # mov ecx/eax/edx, [global]
        needle = load + struct.pack('<I', global_va)
        j = text.find(needle)
        while j != -1:
            span = bounds(lo + j)
            if span is None:
                print('load of 0x%08X at 0x%08X lies in no known function, skipped'
                      % (global_va, lo + j), file=sys.stderr)
                j = text.find(needle, j + 1)
                continue
            w = text[j:span[1] - lo]
            for k in range(len(w) - 2):
                if w[k] != 0xFF:
                    continue
                mode = w[k + 1] & 0xF8
                if (mode == 0x50 and w[k + 2] in slots) or (
                        mode == 0x90 and k + 6 <= len(w)
                        and struct.unpack_from('<I', w, k + 2)[0] in slots):
                    hits.add(span[0])
                    break
            j = text.find(needle, j + 1)
    return hits


def walk(frontier, neighbours, limit):
    """Breadth-first depths from `frontier` (rva -> starting depth) to `limit`."""
    depth = dict(frontier)
    for d in range(limit):
        for rva in [r for r, dd in depth.items() if dd == d]:
            for nxt in neighbours.get(rva, ()):
                depth.setdefault(nxt, d + 1)
    return depth


def closure(seeds_path):
    cfg = json.loads(Path(seeds_path).read_text())
    if set(cfg) != SEED_KEYS:
        sys.exit('%s: keys must be exactly %s, got %s'
                 % (seeds_path, sorted(SEED_KEYS), sorted(cfg)))
    groups = list(cfg['groups'])
    for key in ('vtables', 'vcalls', 'caps'):
        stray = set(cfg[key]) - set(groups)
        if stray:
            sys.exit('%s: %s names groups without seeds: %s' % (seeds_path, key, sorted(stray)))

    data, secs = load_image()
    off = make_off(secs)
    sized = {int(r['rva'], 16): int(r['size'])
             for r in csv.DictReader(open('targets/game/reverse/ghidra_functions.csv', newline=''))}
    rows_at = collections.defaultdict(list)
    for row in build.load_function_rows():
        rows_at[int(row['target_rva'], 16)].append(row)
    rows_at = dict(rows_at)
    for rva, rows in rows_at.items():
        sizes = {int(r['target_size']) for r in rows}
        if len(sizes) != 1:
            sys.exit('0x%08X: ledger rows disagree on its size: %s' % (rva, sorted(sizes)))
        sized[rva] = sizes.pop()
    starts = sorted(sized)
    startset = set(starts)
    resolve = thunk_resolver(data, off, startset, sized)
    callees = build_edges(data, off, startset, sized, starts, resolve)
    callers = collections.defaultdict(set)
    for src, tgts in callees.items():
        for tgt in tgts:
            callers[tgt].add(src)

    def bounds(rva):
        """(start, end) of the function containing `rva`, or None."""
        i = bisect.bisect_right(starts, rva) - 1
        if i >= 0 and rva < starts[i] + sized[starts[i]]:
            return starts[i], starts[i] + sized[starts[i]]
        return None

    def contain(rva):
        span = bounds(rva)
        return span[0] if span else None

    lo, size, raw = next(s for s in secs if s[0] <= starts[0] < s[0] + s[1])
    text = data[raw:raw + size]
    frontier = {g: {} for g in groups}
    for g in groups:
        for seed in cfg['groups'][g]:
            rva = contain(int(seed, 16))
            if rva is None:
                sys.exit('%s seed %s lies in no known function' % (g, seed))
            frontier[g].setdefault(resolve(rva), 0)
    for g, tables in cfg['vtables'].items():
        for va in tables:
            for body in vtable_bodies(data, off, resolve, startset, (lo, lo + size), int(va, 16)):
                frontier[g].setdefault(body, 1)
    for g, sites in cfg['vcalls'].items():
        for global_va, slots in sites:
            for fn in vcall_sites(text, lo, bounds, int(global_va, 16), set(slots)):
                frontier[g].setdefault(fn, 1)

    assigned = {}
    for gi, g in enumerate(groups):
        cap = cfg['caps'].get(g, max(cfg['depth'], cfg['updepth']))
        down = walk(frontier[g], callees, min(cfg['depth'], cap))
        up = walk(frontier[g], callers, min(cfg['updepth'], cap))
        for rva in set(down) | set(up):
            d = min(x for x in (down.get(rva), up.get(rva)) if x is not None)
            if rva not in assigned or (d, gi) < assigned[rva]:
                assigned[rva] = (d, gi)

    matched = {(r['name'], r['target_rva']): (int(r['target_size']), r['source'])
               for rows in rows_at.values() for r in rows}
    sources = sorted({r['source'] for rva in assigned for r in rows_at.get(rva, ())
                      if Path(r['source']).suffix.lower() in progress.CPP_SUFFIXES})
    naked = progress.naked_cpp_rows(
        matched, {s: Path(s).read_bytes().decode('utf-8', errors='replace') for s in sources})

    def state(rva):
        if rva not in rows_at:
            return 'UNCLAIMED'
        states = set()
        for row in rows_at[rva]:
            if build.is_scaffold_row(row) or (row['name'], row['target_rva']) in naked \
                    or row['source'].startswith('game/masm_dumps/'):
                states.add('ASM')
            elif row['source'].startswith('game/gen_small/'):
                states.add('SMALL')
            elif row['source'].startswith('game/Libraries/'):
                states.add('LIB')
            else:
                states.add('CPP')
        # ICF alias rows hold one body under several sources; as in progress.py,
        # clean C++ ownership wins over a dump of the same bytes.
        return max(states, key=STATES.index)

    pins = collections.defaultdict(list)
    for r in csv.DictReader(open('targets/game/reverse/symbols.csv', newline='')):
        pins[int(r['address'], 16)].append(r['name'])
    prefixes = tuple(cfg['anonymous_prefixes'])
    substrings = cfg['anonymous_substrings']

    def identified(rva):
        names = [r['name'] for r in rows_at.get(rva, ())] + pins.get(rva, [])
        return any(not (n.startswith(prefixes) or any(s in n for s in substrings))
                   for n in names)

    cells = collections.defaultdict(lambda: {c: [0, 0] for c in COLUMNS})
    for rva, (depth, gi) in assigned.items():
        row = cells[(gi, min(depth, 2))]
        for col in (state(rva), 'identified' if identified(rva) else 'anonymous'):
            row[col][0] += 1
            row[col][1] += sized[rva]

    def summary(row):
        return (sum(row[s][0] for s in STATES), sum(row[s][1] for s in STATES)) \
            + tuple('%d/%d' % tuple(row[c]) for c in COLUMNS)

    fmt = '%-14s %4s %6s %9s  ' + '  '.join(['%-15s'] * len(COLUMNS))
    print(fmt % (('group', 'tier', 'funcs', 'bytes') + COLUMNS))
    total = {c: [0, 0] for c in COLUMNS}
    for gi, tier in sorted(cells):
        row = cells[(gi, tier)]
        for c in COLUMNS:
            total[c][0] += row[c][0]
            total[c][1] += row[c][1]
        print(fmt % ((groups[gi], tier) + summary(row)))
    print(fmt % (('TOTAL', '-') + summary(total)))
    return 0


def main():
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 2
    if args[0] == '--closure':
        if len(args) != 2:
            sys.exit('usage: callers_of.py --closure targets/game/reverse/game_end/seeds.json')
        return closure(args[1])

    data, secs = load_image()
    off = make_off(secs)
    starts, sized, anon, named = load_rows()
    edges = build_edges(data, off, starts, sized, named, thunk_resolver(data, off, starts, sized))

    if args[0] == '--files':
        limit = int(args[1]) if len(args) > 1 else 60
        callers = collections.defaultdict(set)
        for src, tgts in edges.items():
            for t in tgts:
                if t in anon:
                    callers[t].add(src)
        rows = []
        for t, cs in callers.items():
            if len(cs) != 1:
                continue
            src_file = file_literal(data, off, t, anon[t][0])
            if src_file:
                rows.append((anon[t][0], t, next(iter(cs)), src_file))
        rows.sort(reverse=True)
        print('single-caller dumps that name their own source file: %d' % len(rows))
        for size, t, c, f in rows[:limit]:
            print('%7d  0x%08x  %-34s  <- %s' % (size, t, f, named[c][:60]))
        return 0

    if args[0] == '--report':
        limit = int(args[1]) if len(args) > 1 else 40
        callers = collections.defaultdict(set)
        for src, tgts in edges.items():
            for t in tgts:
                if t in anon:
                    callers[t].add(src)
        single = [(anon[t][0], t, next(iter(cs)))
                  for t, cs in callers.items() if len(cs) == 1]
        single.sort(reverse=True)
        print('anonymous dumps with exactly one named caller: %d' % len(single))
        print('%8s  %-10s  %s' % ('size', 'dump', 'sole caller'))
        for size, t, c in single[:limit]:
            print('%8d  0x%08x  %s' % (size, t, named[c][:88]))
        return 0

    target = int(args[0], 16)
    hits = sorted(src for src, tgts in edges.items() if target in tgts)
    label = named.get(target) or (anon[target][1] if target in anon else '?')
    print('0x%08x  %s  (%d bytes)' % (target, label, sized.get(target, 0)))
    if not hits:
        print('  no named caller reaches it directly')
        return 0
    for h in hits:
        print('  <- 0x%08x  %s' % (h, named[h]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
