"""Read-only complete HRESULT-domain evidence; never changes source or admission rules."""
import argparse, json, pathlib, sys
ROOT = pathlib.Path(__file__).resolve().parents[5]
sys.path.insert(0, str(ROOT / 'tools'))
import build, diffexec
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_REG, X86_OP_IMM, X86_OP_MEM

MOD = 1 << 32
MASK = MOD - 1
IMAGE = diffexec.Image.from_pe(build.EXE)
MD = Cs(CS_ARCH_X86, CS_MODE_32)
MD.detail = True

def signed(n):
    return n if n < MOD // 2 else n - MOD

def ev(expr, x):
    return (expr[0] * x + expr[1]) & MASK

def add(a, b):
    r = (a[0] + b[0], (a[1] + b[1]) & MASK)
    return r

def neg(a):
    return (-a[0], -a[1] & MASK)

def domain_size(domain):
    return sum(hi - lo for lo, hi in domain)

def partition(domain, a, b, jump):
    assert a[0] in (0, 1) and b[0] in (0, 1), (a, b)
    cuts = {0, MOD}
    for expr in (a, b):
        if expr[0]:
            cuts.update({(-expr[1]) & MASK, (MOD // 2 - expr[1]) & MASK})
    if a[0] != b[0]:
        x = (b[1] - a[1]) & MASK if a[0] else (a[1] - b[1]) & MASK
        cuts.update({x, (x + 1) & MASK})
    def predicate(x):
        left, right = ev(a, x), ev(b, x)
        return {'je': left == right, 'jz': left == right,
                'jne': left != right, 'jnz': left != right,
                'jg': signed(left) > signed(right), 'jge': signed(left) >= signed(right),
                'jl': signed(left) < signed(right), 'jle': signed(left) <= signed(right),
                'ja': left > right, 'jae': left >= right, 'jb': left < right, 'jbe': left <= right,
                'jns': signed(left) >= 0, 'js': signed(left) < 0}[jump]
    yes, no = [], []
    for lo, hi in domain:
        points = [lo] + sorted(p for p in cuts if lo < p < hi) + [hi]
        for start, stop in zip(points, points[1:]):
            value = predicate(start)
            assert predicate(stop - 1) == value
            (yes if value else no).append((start, stop))
    return yes, no

def read_mem(address, size):
    assert IMAGE.base <= address < address + size <= IMAGE.base + IMAGE.size
    off = address - IMAGE.base
    return int.from_bytes(IMAGE.flat[off:off + size], 'little')

def string_at(pointer, wide):
    off = pointer - IMAGE.base
    assert 0 <= off < IMAGE.size
    step = 2 if wide else 1
    end = off
    while IMAGE.flat[end:end + step] != bytes(step):
        end += step
        assert end < off + 65536
    return bytes(IMAGE.flat[off:end]).decode('utf-16le' if wide else 'ascii')

def recover(rva, size, wide, default):
    lo, hi = IMAGE.base + rva, IMAGE.base + rva + size
    states = [(lo, {}, [(0, MOD)], None, None)]
    outputs, instructions, edges, domains, tables = [], {}, set(), 0, {}
    table_bytes = set()
    while states:
        pc, regs, domain, flags, origin = states.pop()
        while True:
            assert lo <= pc < hi, hex(pc)
            ins = instructions.get(pc)
            if ins is None:
                ins = next(MD.disasm(bytes(IMAGE.flat[pc-IMAGE.base:pc-IMAGE.base+15]), pc, count=1))
                assert pc + ins.size <= hi
                instructions[pc] = ins
            ops = ins.operands
            def reg(op):
                return ins.reg_name(op.reg)
            def addr(mem):
                result = (0, mem.disp & MASK)
                if mem.base:
                    result = add(result, regs[ins.reg_name(mem.base)])
                if mem.index:
                    idx = regs[ins.reg_name(mem.index)]
                    result = add(result, (idx[0] * mem.scale, idx[1] * mem.scale & MASK))
                return result
            def operand(op):
                if op.type == X86_OP_IMM: return (0, op.imm & MASK)
                if op.type == X86_OP_REG: return regs[reg(op)]
                assert op.type == X86_OP_MEM
                m = op.mem
                if m.base and ins.reg_name(m.base) == 'esp' and not m.index and m.disp == 4:
                    return (1, 0)
                a = addr(m)
                assert a[0] == 0, (hex(pc), ins.mnemonic, ins.op_str, domain_size(domain))
                tables.setdefault(pc, set()).add(a[1])
                table_bytes.update(range(a[1], a[1] + op.size))
                return (0, read_mem(a[1], op.size))
            mn = ins.mnemonic
            nxt = pc + ins.size
            if mn in ('mov', 'movzx'):
                assert ops[0].type == X86_OP_REG
                # A variable table read is bounded by the domain arriving on this CFG edge.
                if ops[1].type == X86_OP_MEM and not (ops[1].mem.base and ins.reg_name(ops[1].mem.base) == 'esp'):
                    address = addr(ops[1].mem)
                    if address[0]:
                        assert domain_size(domain) <= 10000, (hex(pc), domain)
                        for a, b in domain:
                            for x in range(a, b):
                                concrete = {k: (0, ev(v, x)) for k, v in regs.items()}
                                states.append((pc, concrete, [(x, x + 1)], flags, origin))
                        break
                value = operand(ops[1]); regs[reg(ops[0])] = value
                if reg(ops[0]) == 'eax' and not value[0]: origin = pc
            elif mn in ('add', 'sub', 'inc', 'dec'):
                key = reg(ops[0]); right = operand(ops[1]) if len(ops) == 2 else (0, 1)
                value = add(regs[key], neg(right) if mn in ('sub', 'dec') else right)
                regs[key] = value; flags = (value, (0, 0))
            elif mn == 'lea': regs[reg(ops[0])] = addr(ops[1].mem)
            elif mn == 'cmp': flags = (operand(ops[0]), operand(ops[1]))
            elif mn == 'test':
                a, b = operand(ops[0]), operand(ops[1]); assert a == b
                flags = (a, (0, 0))
            elif mn == 'or':
                assert reg(ops[0]) == reg(ops[1])
                flags = (regs[reg(ops[0])], (0, 0))
            elif mn == 'jmp':
                if ops[0].type == X86_OP_MEM:
                    address = addr(ops[0].mem)
                    if address[0]:
                        assert domain_size(domain) <= 10000
                        for a, b in domain:
                            for x in range(a, b):
                                concrete = {k: (0, ev(v, x)) for k, v in regs.items()}
                                states.append((pc, concrete, [(x, x + 1)], flags, origin))
                        break
                target = operand(ops[0]); assert target[0] == 0
                nxt = target[1]
            elif mn.startswith('j'):
                assert flags is not None and ops[0].type == X86_OP_IMM
                yes, no = partition(domain, *flags, mn)
                if yes: states.append((ops[0].imm, dict(regs), yes, flags, origin))
                if not no: break
                domain = no
            elif mn == 'ret':
                assert ops and ops[0].imm == 4
                pointer = regs['eax']; assert pointer[0] == 0 and origin is not None
                outputs.append({'domain': domain, 'value': string_at(pointer[1], wide), 'origin': origin - lo, 'pointer': pointer[1]})
                domains += domain_size(domain)
                break
            else: raise AssertionError((hex(pc), mn, ins.op_str))
            edges.add((pc - lo, nxt - lo));pc = nxt
    assert domains == MOD, domains
    # Disjoint full-domain coverage proves no HRESULT input was omitted or duplicated.
    spans = sorted(span for item in outputs for span in item['domain'])
    end = 0
    for a, b in spans:
        assert a == end, (a, end); end = b
    assert end == MOD
    cases = []
    for item in outputs:
        if item['value'] == default: continue
        assert domain_size(item['domain']) < 10000
        for a, b in item['domain']:
            for x in range(a, b): cases.append({'hr': x, **{k: item[k] for k in ('value', 'origin', 'pointer')}})
    code_bytes = {p + offset for p, ins in instructions.items() for offset in range(ins.size)}
    assert len(code_bytes) == sum(ins.size for ins in instructions.values())
    assert not code_bytes & table_bytes
    assert all(lo <= p < hi for p in table_bytes)
    unclassified = sorted(set(range(lo, hi)) - code_bytes - table_bytes)
    result = {'rva': rva, 'size': size, 'wide': wide, 'default': default,
              'reachable_code_bytes': len(code_bytes), 'read_table_bytes': len(table_bytes),
              'unclassified_offsets': [p - lo for p in unclassified],
              'cases': sorted(cases, key=lambda c: c['hr']),
              'instruction_count': len(instructions), 'edge_count': len(edges),
              'covered_inputs': domains, 'return_paths': len(outputs),
              'table_reads': {hex(k-lo): len(v) for k,v in tables.items()},
              'reachable_instructions': [{'offset': p-lo, 'bytes': i.bytes.hex(), 'mnemonic': i.mnemonic, 'operands': i.op_str} for p,i in sorted(instructions.items())]}
    print(hex(rva), 'cases', len(cases), 'instructions', len(instructions), 'covered inputs', domains, flush=True)
    return result

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out-dir', type=pathlib.Path, required=True)
    args = parser.parse_args()
    args.out_dir.mkdir(parents=True, exist_ok=True)
    functions = [('stringa',0xad548e,70599,False,'Unknown'),('stringw',0xae6855,70612,True,'Unknown'),
                 ('descriptiona',0xaf7c29,10933,False,'n/a'),('descriptionw',0xafa6de,10933,True,'n/a')]
    for name,rva,size,wide,default in functions:
        path = args.out_dir / ('dxerr-'+name+'.json')
        path.write_text(json.dumps(recover(rva,size,wide,default),indent=2)+'\n')
