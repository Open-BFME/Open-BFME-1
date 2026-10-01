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
        included). A WorldBuilder handler names a game body when their effects are identical,
        no other game body has those effects and no other WorldBuilder handler has them either;
        any such ambiguity names nothing. Effects are a tree over every path through the body
        (effects()): each branch's compared values and condition, each store through the
        GlobalData pointer as (offset, width, value), each write to another global with that
        global's identity, each import call with its arguments, and each path's return value.
        Code it does not model (a loop, an indirect jump, an unknown stored value) leaves a body
        unmodelled. The two builds allocate registers differently, so bytes are never compared.
        GlobalData's pointer is, in each image, the global its table handlers load most; another
        global is identified across the images only where a flag in both tables writes it at the
        same place, and every such flag must give the same effects on both sides or nothing is
        written. Only known function starts that read GlobalData's pointer are candidate bodies.

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
JCC = {"je": "jne", "jb": "jae", "jbe": "ja", "jl": "jge", "jle": "jg", "js": "jns", "jo": "jno", "jp": "jnp"}
NEGATED = {neg: pos for pos, neg in JCC.items()}
MAX_STEPS = 256                                       # instructions over all paths of one body


def effects(img, rva, gd):
    """The body's complete behaviour as a tree, or None when any path meets something it does not model.

    gd is the GlobalData pointer's VA. A tree is the tuple of one path's events up to its end:
    ('store', offset, width, value) through GlobalData, ('set', ('global', va), width, value) into
    another global (`or [g], m` and a load/or/store of g both read ('bitor', ('load', g, w), m)),
    ('call', import, arguments), then ('return', eax, bytes popped) or ('if', condition, taken,
    not taken). A condition is ((compared values), jcc) with jcc in JCC's positive forms: `test r,r`
    is `cmp r,0` (identical flags), and a negated jump swaps the arms, so layout cannot split two
    equal bodies, while different guards or destinations always give different trees. Values are
    ('const', n), ('gd',), ('load', ('global', va), width), ('args',), ('count',), ('arg', k),
    ('bitor', a, b) or ('call', import, arguments). Only forward jumps inside the body are followed."""
    first, limit = img.base + rva, img.base + rva + MAX_BODY
    steps = [0]

    def mem(text):
        """(width, base register or None, displacement or absolute VA) of a memory operand."""
        m = MEM.fullmatch(text)
        if not m:
            return None
        if m.group(5):
            return m.group(1), None, int(m.group(5), 16)
        disp = int(m.group(4), 0) if m.group(4) else 0
        return m.group(1), m.group(2), -disp if m.group(3) == "-" else disp

    def value(text, regs, stack):
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
            return ("gd",) if disp == gd else ("load", ("global", disp), width)
        if base == "esp":
            return {4: ("args",), 8: ("count",)}.get(disp + 4 * len(stack))
        if regs.get(base) == ("args",) and disp % 4 == 0:
            return ("arg", disp // 4)
        return None

    def target(i):
        """A direct jump's destination, when it lies ahead inside the body."""
        if not re.fullmatch(r"0x[0-9a-f]+", i.op_str):
            return None
        to = int(i.op_str, 16)
        return to if i.address < to < limit else None

    def walk(va, regs, stack, flags):
        out = []
        while True:
            steps[0] += 1
            if steps[0] > MAX_STEPS or not first <= va < limit:
                return None
            i = next(MD.disasm(bytes(img.mem[va - img.base:va - img.base + 16]), va, count=1), None)
            if i is None:
                return None
            va = i.address + i.size
            mn, ops = i.mnemonic, [o.strip() for o in i.op_str.split(",")] if i.op_str else []
            dst = mem(ops[0]) if ops else None
            if mn == "ret":
                eax = regs.get("eax")
                return None if eax is None else tuple(out) + (("return", eax, int(ops[0], 0) if ops else 0),)
            if mn in JCC or mn in NEGATED:
                to = target(i)
                if flags is None or to is None:
                    return None
                taken = walk(to, dict(regs), list(stack), flags)
                fall = walk(va, dict(regs), list(stack), flags)
                if taken is None or fall is None:
                    return None
                if mn in NEGATED:
                    mn, taken, fall = NEGATED[mn], fall, taken
                return tuple(out) + (("if", (flags, mn), taken, fall),)
            if mn == "jmp":
                va = target(i)
                if va is None:
                    return None
                continue
            if mn in ("cmp", "test") and len(ops) == 2:
                a, b = value(ops[0], regs, stack), value(ops[1], regs, stack)
                if a is None or b is None:
                    return None
                if mn == "test" and ops[0] == ops[1]:
                    mn, b = "cmp", ("const", 0)       # test r,r sets exactly cmp r,0's flags
                elif mn == "test":
                    a, b = sorted((a, b), key=repr)
                flags = (mn, a, b)
                continue
            if mn in ("mov", "push", "pop"):
                pass                                  # these leave EFLAGS alone
            else:
                flags = None
            if mn == "xor" and ops[0] == ops[1] and ops[0] in REG32:
                regs[ops[0]] = ("const", 0)
            elif mn == "inc" and ops[0] in REG32 and (regs.get(ops[0]) or ("",))[0] == "const":
                regs[ops[0]] = ("const", (regs[ops[0]][1] + 1) & 0xFFFFFFFF)
            elif mn == "push":
                stack.append(value(ops[0], regs, stack))
            elif mn == "pop" and ops[0] in REG32 and stack:
                regs[ops[0]] = stack.pop()
            elif mn == "add" and ops[0] == "esp" and int(ops[1], 0) % 4 == 0 and int(ops[1], 0) // 4 <= len(stack):
                del stack[len(stack) - int(ops[1], 0) // 4:]
            elif mn == "call" and dst and dst[1] is None and dst[2] in img.imports:
                call = ("call", img.imports[dst[2]], tuple(reversed(stack)))
                out.append(call)
                regs = {"eax": call}
            elif mn == "or" and dst and dst[1] is None and dst[2] != gd:
                g, mask = ("global", dst[2]), value(ops[1], regs, stack)
                if mask is None:
                    return None
                out.append(("set", g, dst[0], ("bitor", ("load", g, dst[0]), mask)))
            elif mn == "or" and ops[0] in REG32:
                a, b = regs.get(ops[0]), value(ops[1], regs, stack)
                regs[ops[0]] = ("bitor", a, b) if a is not None and b is not None else None
            elif mn == "mov" and dst and (dst[1] is None or regs.get(dst[1]) == ("gd",)):
                v = value(ops[1], regs, stack)
                if v is None or dst[1] is None and dst[2] == gd:
                    return None                       # an unknown value, or GlobalData's pointer itself
                out.append(("set", ("global", dst[2]), dst[0], v) if dst[1] is None
                           else ("store", dst[2], dst[0], v))
            elif mn == "mov" and ops[0] in REG32:
                regs[ops[0]] = value(ops[1], regs, stack)
            else:
                return None

    return walk(first, {}, [], None)


def events(tree):
    """Every event of every path of an effects() tree."""
    for e in tree:
        if e[0] == "if":
            yield from events(e[2])
            yield from events(e[3])
        else:
            yield e


def unify(game, wb, globals_map):
    """Extend globals_map (WorldBuilder VA -> game VA) with the globals two trees use at the same place."""
    if isinstance(game, tuple) and isinstance(wb, tuple) and len(game) == len(wb):
        if len(game) == 2 and game[0] == wb[0] == "global":
            if globals_map.setdefault(wb[1], game[1]) != game[1]:
                fail(f"WorldBuilder global 0x{wb[1]:08X} is game 0x{globals_map[wb[1]]:08X} and 0x{game[1]:08X}")
            return
        for a, b in zip(game, wb):
            unify(a, b, globals_map)


def rename(tree, globals_map):
    """A WorldBuilder tree in the game's globals; a global no shared flag maps matches nothing."""
    if not isinstance(tree, tuple):
        return tree
    if len(tree) == 2 and tree[0] == "global":
        return ("global", globals_map[tree[1]]) if tree[1] in globals_map else ("global", "wb1", tree[1])
    return tuple(rename(x, globals_map) for x in tree)


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


def pair(trees, candidates, index):
    """({flag: game rva}, notes) for candidate WorldBuilder flags whose effects tree (trees[flag])
    exactly one game body has (index: tree -> {rva}) and no other modelled WorldBuilder handler has.
    A tree two game bodies share, or one body two handlers share, names nothing: ambiguity is no
    evidence. A tree that writes nothing (no store or set) is too weak to name anything."""
    handlers = collections.defaultdict(set)
    for flag, tree in trees.items():
        if tree:
            handlers[tree].add(flag)
    matched, notes = {}, []
    for flag in candidates:
        tree = trees.get(flag)
        if not tree or not any(e[0] in ("store", "set") for e in events(tree)):
            continue
        bodies, rivals = sorted(index.get(tree, ())), sorted(handlers[tree] - {flag})
        if len(bodies) > 1:
            notes.append(f"{flag}: no name, game bodies {', '.join(f'0x{b:08X}' for b in bodies)} all have its effects")
        elif bodies and rivals:
            notes.append(f"{flag}: no name, 0x{bodies[0]:08X}'s effects are also WorldBuilder {', '.join(rivals)}'s")
        elif bodies:
            matched[flag] = bodies[0]
    return matched, notes


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
    trees = [(flag, g, w, effects(game, g, gd_game), effects(wb, w, gd_wb)) for flag, g, w in shared]
    globals_map = {}                                   # the globals shared flags write, WorldBuilder -> game
    for _, _, _, eg, ew in trees:
        if eg and ew:
            unify(eg, ew, globals_map)
    agree = 0
    for flag, g, w, eg, ew in trees:
        if eg and ew and eg != rename(ew, globals_map):
            fail(f"{flag}: game 0x{g:08X} and WorldBuilder 0x{w:08X} disagree ({eg} vs {ew}); the effects model is wrong")
        agree += bool(eg and ew)
    if not agree:
        fail("no flag in both tables has modelled effects on both sides; the effects model cannot be trusted")
    notes.append(f"{agree} of {len(shared)} flags in both tables have identical effects on both sides; none differ")
    notes += [f"WorldBuilder global 0x{w:08X} is game 0x{g:08X} (a shared flag writes both)"
              for w, g in sorted(globals_map.items())]

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
            if e:
                index[e].add(rva)
    wb_trees = {}
    for flag, body in wt:
        e = effects(wb, body, gd_wb)
        wb_trees[flag] = rename(e, globals_map) if e else None
    game_flags = {f for f, _ in gt}
    matched, ambiguous = pair(wb_trees, [f for f, _ in wt if f not in game_flags and f in zh], index)
    notes += ambiguous
    for flag, rva in matched.items():
        if rva not in direct:
            claims[rva].add((zh[flag], f"wb1 table '{flag}' -> 0x{wb_by_flag[flag]:08X}, the only game body with its effects"))

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
