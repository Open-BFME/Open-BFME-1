#!/usr/bin/env python3
"""EA's names for command-line handlers, read from the CommandLineParam tables in two binaries.

The game and BFME1 WorldBuilder each ship `static CommandLineParam params[]`, an array of
`{const char *flag, FuncPtr handler}` pairs ending in a zero pair, read only by parseCommandLine.
Zero Hour's CommandLine.cpp has the same table with EA's handler names, so a flag Zero Hour pairs
with one handler names the body a BFME table pairs with that flag. This writes those names to
targets/game/reverse/ea_evidence.csv as kind=name, route=flagtable, basis=strong:

  game  lotrbfme.exe's release table (TABLES["game"], 12 entries). Each handler is a 5-byte
        incremental-link E9 thunk; the name goes on the thunk's target.
  wb1   worldbuilder.exe's internal-build table (TABLES["wb1"], 145 entries, debug flags
        included). A WorldBuilder handler names a game body when their effects are identical
        and no other game body or WorldBuilder handler has those effects. Effects are what a
        straight-line pass over the body (to its first ret) writes: each store through the
        GlobalData pointer as (offset, width, value), an OR into another global as its mask,
        and the value returned. Values are constants or an import's result (atoi). The two
        builds allocate registers differently, so bytes are never compared. GlobalData's pointer
        is, in each image, the global its table handlers load most; every flag in both tables
        must give the same effects on both sides or nothing is written.

A flag Zero Hour lacks, or pairs with two handlers in different #if branches, names nothing. An
address two flags would name differently, or a name two addresses would take, is dropped. The
game's own table pairs flags with bodies directly, so it alone names its bodies; a flagtable name
replaces a WorldBuilder-label name at its address. A flag with no Zero Hour handler (BFME's
-scriptDebug2, -Watchdog, -panoramicSlices, ...) keeps its body's address name. Evidence:
targets/game/reverse/identity_evidence/00ea6f40-commandline-params.md.

tools/ea_evidence.py merges these rows whenever it rewrites the CSV; between its runs:

    python3 tools/ea_flagtable.py            # print the rows and the evidence for each
    python3 tools/ea_flagtable.py --write    # replace the CSV's flagtable rows (the rest stay)
    python3 tools/ea_flagtable.py --check    # exit 1 when the CSV's flagtable rows are stale
"""
import argparse
import collections
import csv
import re
import struct
import sys
from pathlib import Path

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
REVERSE = ROOT / "targets/game/reverse"
OUT = REVERSE / "ea_evidence.csv"
IMAGES = {"game": ROOT / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe",
          "wb1": ROOT / "inputs/baselines/bfme1/workshop-vanilla-1.03/files/worldbuilder.exe"}
TABLES = {"game": 0x00EA6F40, "wb1": 0x00FBB788}       # RVAs of params[]
ZH_TABLE = ROOT / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/CommandLine.cpp"
ROUTE, BASIS = "flagtable", "strong"
ENTRY = re.compile(r'\{\s*"(-[^"]+)"\s*,\s*([A-Za-z_]\w*)\s*\}')
MAX_BODY = 512
MD = Cs(CS_ARCH_X86, CS_MODE_32)


def fail(message):
    sys.exit(f"ea_flagtable: {message}")


class Image:
    def __init__(self, path):
        if not path.is_file():
            fail(f"{path} missing")
        pe = pefile.PE(str(path), fast_load=True)
        pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
        self.base, self.mem = pe.OPTIONAL_HEADER.ImageBase, pe.get_memory_mapped_image()
        self.imports = {i.address: i.name.decode("ascii", "replace")
                        for d in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []) for i in d.imports if i.name}
        text = next(s for s in pe.sections if s.Characteristics & 0x20000000)      # executable
        self.text = (text.VirtualAddress, text.VirtualAddress + text.Misc_VirtualSize)

    def u32(self, rva):
        return struct.unpack_from("<I", self.mem, rva)[0]

    def cstr(self, va):
        rva = va - self.base
        if not 0 <= rva < len(self.mem):
            return None
        raw = self.mem[rva:self.mem.index(b"\0", rva)]
        return raw.decode("ascii") if raw and all(32 < c < 127 for c in raw) else None

    def code(self, va):
        return self.text[0] <= va - self.base < self.text[1]


def read_table(img, rva):
    """[(flag, body rva)] of a params[] table; a malformed entry is an error, not a stop."""
    out = []
    while True:
        p, f = img.u32(rva), img.u32(rva + 4)
        if not p and not f:
            return out
        flag = img.cstr(p)
        if not flag or not flag.startswith("-") or not img.code(f):
            fail(f"0x{rva:08X} is not a {{flag, handler}} entry; the table moved or this is the wrong image")
        body = f - img.base
        if img.mem[body] == 0xE9:                     # incremental-link thunk
            body += 5 + struct.unpack_from("<i", img.mem, body + 1)[0]
        out.append((flag, body))
        rva += 8


def zh_handlers(path=ZH_TABLE):
    """flag -> Zero Hour handler, for flags every #if branch pairs with one handler."""
    seen = collections.defaultdict(set)
    for flag, handler in ENTRY.findall(path.read_text(encoding="latin1")):
        seen[flag].add(handler)
    return {flag: next(iter(h)) for flag, h in seen.items() if len(h) == 1}


REG32 = ("eax", "ecx", "edx", "ebx", "esi", "edi", "ebp")
LOW = {"al": "eax", "cl": "ecx", "dl": "edx", "bl": "ebx", "ax": "eax", "cx": "ecx", "dx": "edx", "bx": "ebx"}
MEM = re.compile(r"(byte|word|dword) ptr \[(?:(e[a-z]{2})(?: ([+-]) (0x[0-9a-f]+|\d+))?|(0x[0-9a-f]+))\]")


def effects(img, rva, gd):
    """The body's writes and return value, or None when the pass meets anything it does not model.

    gd is the GlobalData pointer's VA. Registers and stack slots hold ('const', n), ('gd',),
    ('mem', va), ('args',), ('count',), ('arg', k), ('or', mask) or ('call', import, argument)."""
    regs, stack, out = {}, [], []

    def mem(text):
        """(width, base register or None, displacement or absolute VA) of a memory operand."""
        m = MEM.fullmatch(text)
        if not m:
            return None
        if m.group(5):
            return m.group(1), None, int(m.group(5), 16)
        disp = int(m.group(4), 0) if m.group(4) else 0
        return m.group(1), m.group(2), -disp if m.group(3) == "-" else disp

    def value(text):
        if re.fullmatch(r"0x[0-9a-f]+|\d+", text):
            return ("const", int(text, 0))
        if text in REG32:
            return regs.get(text)
        if text in LOW:
            v = regs.get(LOW[text])
            bits = 8 if text.endswith("l") else 16
            return ("const", v[1] & ((1 << bits) - 1)) if v and v[0] == "const" else None
        m = mem(text)
        if not m or m[0] != "dword":
            return None
        width, base, disp = m
        if base is None:
            return ("gd",) if disp == gd else ("mem", disp)
        if base == "esp":
            return {4: ("args",), 8: ("count",)}.get(disp + 4 * len(stack))
        if regs.get(base) == ("args",) and disp % 4 == 0:
            return ("arg", disp // 4)
        return None

    for i in MD.disasm(bytes(img.mem[rva:rva + MAX_BODY]), img.base + rva):
        mn, ops = i.mnemonic, [o.strip() for o in i.op_str.split(",")] if i.op_str else []
        if mn == "ret":
            return tuple(out) + (("return", regs.get("eax")),)
        if (mn.startswith("j") and mn != "jmp") or mn in ("test", "cmp"):
            continue                                  # guards: the pass follows the fall-through
        dst = mem(ops[0]) if ops else None
        if mn == "xor" and ops[0] == ops[1] and ops[0] in REG32:
            regs[ops[0]] = ("const", 0)
        elif mn == "inc" and ops[0] in REG32 and (regs.get(ops[0]) or ("",))[0] == "const":
            regs[ops[0]] = ("const", regs[ops[0]][1] + 1)
        elif mn == "push":
            stack.append(value(ops[0]))
        elif mn == "pop" and ops[0] in REG32:
            regs[ops[0]] = stack.pop() if stack else None
        elif mn == "add" and ops[0] == "esp" and int(ops[1], 0) % 4 == 0 and int(ops[1], 0) // 4 <= len(stack):
            del stack[len(stack) - int(ops[1], 0) // 4:]
        elif mn == "call" and dst and dst[1] is None and dst[2] in img.imports:
            regs = {"eax": ("call", img.imports[dst[2]], stack[-1] if stack else None)}
        elif mn == "or" and dst and dst[1] is None and dst[2] != gd:
            out.append(("or", dst[0], value(ops[1])))           # a flag word |= bit
        elif mn == "or" and ops[0] in REG32 and (regs.get(ops[0]) or ("",))[0] == "mem":
            regs[ops[0]] = ("or", "dword", value(ops[1]))
        elif mn == "mov" and dst and dst[1] is None and (value(ops[1]) or ("",))[0] == "or":
            out.append(value(ops[1]))
        elif mn == "mov" and dst and dst[1] and regs.get(dst[1]) == ("gd",):
            out.append(("store", dst[2], dst[0], value(ops[1])))
        elif mn == "mov" and ops[0] in REG32:
            regs[ops[0]] = value(ops[1])
        else:
            return None
    return None


def pointer(img, bodies):
    """The global most of these handlers load: GlobalData's pointer."""
    loads = collections.Counter()
    for rva in bodies:
        for i in MD.disasm(bytes(img.mem[rva:rva + 64]), img.base + rva):
            loads.update(int(v, 16) for v in re.findall(r"ptr \[(0x[0-9a-f]+)\]", i.op_str))
            if i.mnemonic == "ret":
                break
    (va, n), *rest = loads.most_common(2) + [(None, 0)]
    if not va or n == rest[0][1]:
        fail("no single global dominates the handlers' loads")
    return va


def game_function_starts():
    starts = set()
    for name in ("functions.csv", "ghidra_functions.csv"):
        with open(REVERSE / name, encoding="utf-8", errors="replace", newline="") as f:
            for r in csv.DictReader(f):
                v = r.get("target_rva") or r.get("rva") or ""
                if v.startswith("0x"):
                    starts.add(int(v, 16))
    return starts


def derive():
    """([(rva, name, evidence)], notes)."""
    game, wb = Image(IMAGES["game"]), Image(IMAGES["wb1"])
    gt, wt = read_table(game, TABLES["game"]), read_table(wb, TABLES["wb1"])
    zh = zh_handlers()
    gd_game = pointer(game, [b for _, b in gt])
    gd_wb = pointer(wb, [b for _, b in wt])
    starts = game_function_starts()
    notes = [f"game table 0x{TABLES['game']:08X}: {len(gt)} entries, GlobalData pointer VA 0x{gd_game:08X}",
             f"wb1 table 0x{TABLES['wb1']:08X}: {len(wt)} entries, GlobalData pointer VA 0x{gd_wb:08X}"]

    wb_by_flag = dict(wt)
    shared = [(f, b, wb_by_flag[f]) for f, b in gt if f in wb_by_flag]
    agree = 0
    for flag, g, w in shared:
        eg, ew = effects(game, g, gd_game), effects(wb, w, gd_wb)
        if eg and ew and eg != ew:
            fail(f"{flag}: game 0x{g:08X} and WorldBuilder 0x{w:08X} disagree ({eg} vs {ew}); the effects model is wrong")
        agree += bool(eg and ew)
    if not agree:
        fail("no flag in both tables has modelled effects on both sides; the effects model cannot be trusted")
    notes.append(f"{agree} of {len(shared)} flags in both tables have identical effects on both sides; none differ")

    claims = collections.defaultdict(set)              # rva -> {(name, evidence)}
    for flag, body in gt:
        if flag in zh:
            if body not in starts:
                fail(f"{flag}: 0x{body:08X} is not a known function start")
            claims[body].add((zh[flag], f"game table '{flag}' -> 0x{body:08X}"))
    direct = set(claims)

    gbytes = struct.pack("<I", gd_game)
    index = collections.defaultdict(set)
    for rva in sorted(starts):
        if gbytes in bytes(game.mem[rva:rva + MAX_BODY]):    # a superset: effects() decides
            e = effects(game, rva, gd_game)
            if e and any(x[0] == "store" for x in e):
                index[e].add(rva)
    wb_effects = {flag: effects(wb, body, gd_wb) for flag, body in wt}
    wb_count = collections.Counter(e for e in wb_effects.values() if e)
    game_flags = {f for f, _ in gt}
    for flag, body in wt:
        e = wb_effects[flag]
        if flag in game_flags or flag not in zh or not e or wb_count[e] != 1 or len(index.get(e, ())) != 1:
            continue
        rva = next(iter(index[e]))
        if rva not in direct:
            claims[rva].add((zh[flag], f"wb1 table '{flag}' -> 0x{body:08X}, the only game body with its effects"))

    by_name = collections.Counter(name for c in claims.values() for name in {n for n, _ in c})
    rows = []
    for rva, c in sorted(claims.items()):
        names = {n for n, _ in c}
        if len(names) != 1 or by_name[next(iter(names))] != 1:
            notes.append(f"0x{rva:08X}: dropped, conflicting claims {sorted(c)}")
            continue
        rows.append((rva, next(iter(names)), "; ".join(sorted(ev for _, ev in c))))
    return rows, notes


def merge(existing, rows):
    """existing CSV rows with every flagtable row replaced by rows; a flagtable name replaces a
    WorldBuilder-label name at its address."""
    named = {rva for rva, _, _ in rows}
    keep = [r for r in existing if r["route"] != ROUTE and not (r["kind"] == "name" and int(r["rva"], 16) in named)]
    keep += [{"rva": f"0x{rva:08X}", "kind": "name", "value": name, "route": ROUTE, "basis": BASIS}
             for rva, name, _ in rows]
    return sorted(keep, key=lambda r: (int(r["rva"], 16), r["kind"]))


def read_csv():
    with open(OUT, encoding="utf-8", newline="") as f:
        return list(csv.DictReader(f))


def write_csv(rows):
    with open(OUT, "w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, ["rva", "kind", "value", "route", "basis"], lineterminator="\n")
        w.writeheader()
        w.writerows(rows)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--write", action="store_true")
    g.add_argument("--check", action="store_true")
    args = ap.parse_args()
    rows, notes = derive()
    existing = read_csv()
    merged = merge(existing, rows)
    if args.check:
        if merged != existing:
            print("ea_flagtable: ea_evidence.csv's flagtable rows are stale: run python3 tools/ea_flagtable.py --write",
                  file=sys.stderr)
            return 1
        return 0
    for n in notes:
        print(n)
    for rva, name, ev in rows:
        print(f"0x{rva:08X}  {name:28} {ev}")
    if args.write:
        write_csv(merged)
        print(f"wrote {len(rows)} flagtable rows to {OUT.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
