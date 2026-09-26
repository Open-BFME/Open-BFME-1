"""Which ledger rows resolve a DIR32 symbol to which base address.

The gate's DIR32 consistency check reports that one symbol resolved to two
different bases without saying who disagreed. This lists the rows, so the
offending translation unit can be found instead of guessed.

Run from the repo root: python3 tools/dir32.py <symbol>
"""
import sys, csv, struct
sys.path.insert(0, 'tools')
import build

want = sys.argv[1]
data = open('inputs/baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe', 'rb').read()

for r in csv.DictReader(open('targets/game/reverse/functions.csv', newline='')):
    if r['status'] != 'matched':
        continue
    src = r['source']
    o = build.obj_path(build.ROOT / src)
    if not o.exists():
        continue
    rva, sz = int(r['target_rva'], 16), int(r['target_size'])
    try:
        body, relocs = build.read_object_symbol_bytes(o, build.ledger_object_symbol(r), sz)
    except Exception:
        continue
    for off, rtype, sym in relocs:
        if rtype != 0x0006 or sym != want or off + 4 > sz or off + 4 > len(body):
            continue
        final = struct.unpack_from('<I', data, rva + off)[0]
        add = struct.unpack_from('<I', bytes(body), off)[0]
        base = (final - add) & 0xFFFFFFFF
        print(f"  base {base:#010x}  <- {r['name'][:58]:60} @{rva:#x}")
        print(f"        {src}")
