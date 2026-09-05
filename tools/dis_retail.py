#!/usr/bin/env python3
"""Disassemble a retail body straight from the baseline EXE, with call/jmp
targets and DIR32 slots resolved to ledger names. Read-only.
  python tools/dis_retail.py 0x0067F600 [SIZE]      (SIZE defaults to the ledger row)
Every worker was writing this by hand; here it is once.
"""
import csv, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
try:
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
except ImportError:
    sys.exit("pip install capstone")
rva = int(sys.argv[1], 16)
size = int(sys.argv[2], 0) if len(sys.argv) > 2 else None
names = {}
for r in csv.DictReader(open(build.ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')):
    try: a = int(r['target_rva'], 16)
    except ValueError: continue
    names[a] = r['name']
    if size is None and a == rva: size = int(r['target_size'] or 0)
if not size: sys.exit("size unknown: pass it")
pins = {}
for r in csv.reader(open(build.ROOT / 'reverse/symbols.csv', newline='', encoding='utf-8', errors='replace')):
    if len(r) > 1 and r[1].startswith('0x'):
        try: pins.setdefault(int(r[1], 16), r[0])
        except ValueError: pass
data = build.EXE.read_bytes(); secs = build.pe_sections(data)
off = build.rva_to_file_offset(secs, rva); body = data[off:off+size]
md = Cs(CS_ARCH_X86, CS_MODE_32); md.detail = False
def label(va):
    r = va - 0x400000
    if r in names: return names[r]
    if va in pins: return pins[va]
    if r in pins: return pins[r]
    return ''
print(f"; {label(rva+0x400000)} rva=0x{rva:08X} size={size}")
for ins in md.disasm(body, 0x400000 + rva):
    note = ''
    if ins.mnemonic in ('call', 'jmp') and ins.op_str.startswith('0x'):
        note = label(int(ins.op_str, 16))
    else:
        for tok in ins.op_str.replace('[', ' ').replace(']', ' ').replace(',', ' ').replace('+', ' ').split():
            if tok.startswith('0x') and 0x400000 <= int(tok, 16) < 0x1500000:
                note = label(int(tok, 16)) or note
    b = ' '.join(f'{x:02x}' for x in ins.bytes)
    print(f"+{ins.address - 0x400000 - rva:04x} {b:24s} {ins.mnemonic:7s} {ins.op_str:40s} {(';' + note) if note else ''}")
