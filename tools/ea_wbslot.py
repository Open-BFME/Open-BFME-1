#!/usr/bin/env python3
"""EA's names for virtual overrides, read from WorldBuilder labels in an aligned vtable slot.

BFME2's and RotWK's WorldBuilder builds keep `__FUNCTION__` labels (`RadarUpgrade::removeUpgrade`)
that the release game lacks. tools/ea_evidence.py pairs functions by alignment and can miss a
labelled override whose body differs between the builds (a WorldBuilder debug report compiled
out of the game). For a virtual family whose slot order is anchored in both builds by one call
sequence, the label's vtable slot names the game body in the aligned slot of the same class's
table. This writes those names to targets/game/reverse/ea_evidence.csv as kind=name,
route=wbslot, basis=strong.

For each family in FAMILIES and each supplied WorldBuilder image (identified by SHA-256 in
WB_IMAGES; an unknown file is refused):

  1. Family tables: in each image, the vtables whose slot `entry_slot` holds the family's
     sequence function (WB: the attemptUpgrade address recorded for that build; game: the body
     reached from GAME_ENTRY), and which a `mov [reg+store], table` in code installs.
  2. Anchors: the virtual-call slots the sequence makes, read from code. The game's
     attemptUpgrade inlines them; WorldBuilder's attemptUpgrade calls giveSelfUpgrade, which
     makes them. They must equal the family's recorded sequences (game 11,13,9,8; WB 12,15,10,9),
     or nothing is written. Each pair (wb slot, game slot) is an anchor.
  3. Labels: every `push imm32` in a WorldBuilder table body that points at a `Class::method`
     string. A label names the body only when Class owns that table: every label in the table's
     own (unshared) bodies names the same class, and no other family table carries that class.
  4. Slot mapping: a label slot equal to an anchor's WB slot maps to its game slot. A label slot
     one below an anchor maps one below that anchor's game slot when that game slot is not itself
     an anchor and the spacing agrees on both sides: the nearest lower anchor is the same distance
     below in both builds, or, with none, the anchor above and the next slot up form a contiguous
     run in both (WB 9,10 = game 8,9 puts WB 8 at game 7). Any other slot is left unnamed: WB 14
     sits between anchors 12 and 15, which are 3 apart in WorldBuilder and 2 apart in the game.
  5. Game body: the class's registered constructor (targets/game/reverse/module_registry.tsv)
     must install exactly one family table at +store. The ILT stub in the mapped slot must
     appear exactly once in the image; its target is the body.

Every supplied WorldBuilder must agree. An address two labels would name differently, or a name
two addresses would take, names nothing. A label row ea_evidence.py already holds at the address must give
the same name: it is kept, with no wbslot row added, and a disagreeing one stops the tool. Evidence:
targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md.

The WorldBuilder executables are not in the repo. Pass them, or set BFME2_WORLDBUILDER /
ROTWK_WORLDBUILDER. tools/ea_evidence.py merges these rows whenever it rewrites the CSV (with its
--wb2-exe). Between its runs:

    python3 tools/ea_wbslot.py --wb EXE [--wb EXE]           # print the rows and their evidence
    python3 tools/ea_wbslot.py --wb EXE [--wb EXE] --write   # replace the CSV's wbslot rows
    python3 tools/ea_wbslot.py --wb EXE [--wb EXE] --check   # exit 1 when they are stale
"""
import argparse
import csv
import hashlib
import os
import re
import struct
import sys
from pathlib import Path

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
REVERSE = ROOT / "targets/game/reverse"
OUT = REVERSE / "ea_evidence.csv"
REGISTRY = REVERSE / "module_registry.tsv"
GAME_EXE = ROOT / "inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe"
ROUTE, BASIS = "wbslot", "strong"
LABEL = re.compile(rb"([A-Za-z_]\w*)::([A-Za-z_]\w*)")
MD = Cs(CS_ARCH_X86, CS_MODE_32)

FAMILIES = {
    "UpgradeMux": dict(
        entry_slot=1,                     # attemptUpgrade
        store=0x10,                       # the UpgradeMux sub-object
        game_entry=0x002D9AD0,            # BFME1 UpgradeMux::attemptUpgrade (inlines giveSelfUpgrade)
        game_sequence=(11, 13, 9, 8),     # performUpgradeFX, processUpgradeRemoval, upgradeImplementation,
        wb_sequence=(12, 15, 10, 9),      # setUpgradeExecuted(true): the same calls, one build each
    ),
}
# sha256 -> (build, {family: WorldBuilder attemptUpgrade RVA})
WB_IMAGES = {
    "af1d464083e45f65331aab2ee1d0b3f4a0b89ac719d875a686a440fe04792f68": ("BFME2", {"UpgradeMux": 0x007E80E0}),
    "3fdae1d2dd3fc2c44cd53e4617acc3b8992b4eec0938b9abb213714c197280d7": ("RotWK", {"UpgradeMux": 0x007EA150}),
}
ENV = ("BFME2_WORLDBUILDER", "ROTWK_WORLDBUILDER")


def fail(message):
    sys.exit(f"ea_wbslot: {message}")


class Image:
    def __init__(self, path):
        path = Path(path)
        if not path.is_file():
            fail(f"{path} missing")
        raw = path.read_bytes()
        self.sha = hashlib.sha256(raw).hexdigest()
        pe = pefile.PE(data=raw, fast_load=True)
        self.base, self.mem = pe.OPTIONAL_HEADER.ImageBase, pe.get_memory_mapped_image()
        text = next(s for s in pe.sections if s.Characteristics & 0x20000000)
        self.text = (text.VirtualAddress, text.VirtualAddress + text.Misc_VirtualSize)
        self.data = [(s.VirtualAddress, s.VirtualAddress + s.Misc_VirtualSize) for s in pe.sections
                     if not s.Characteristics & 0x20000000]

    def u32(self, rva):
        return struct.unpack_from("<I", self.mem, rva)[0]

    def in_text(self, va):
        return self.text[0] <= va - self.base < self.text[1]

    def find(self, value, lo=0, hi=None):
        pat, out, i = struct.pack("<I", value), [], self.mem.find(struct.pack("<I", value), lo)
        while i != -1 and (hi is None or i < hi):
            out.append(i)
            i = self.mem.find(pat, i + 1)
        return out

    def data_refs(self, va):
        return [r for lo, hi in self.data for r in self.find(va, lo, hi)]

    def resolve(self, va):
        """follow incremental-link E9 thunks to the body (RVA)"""
        rva = va - self.base
        for _ in range(3):
            if not 0 <= rva < len(self.mem) or self.mem[rva] != 0xE9:
                break
            rva = (rva + 5 + struct.unpack_from("<i", self.mem, rva + 1)[0]) & 0xFFFFFFFF
        return rva

    def code(self, rva, n=0x600):
        for i in MD.disasm(bytes(self.mem[rva:rva + n]), rva + self.base):
            yield i
            if i.mnemonic == "ret":
                return

    def slots(self, table_va, limit=64):
        out = []
        for k in range(limit):
            v = self.u32(table_va - self.base + 4 * k)
            if not self.in_text(v):
                break
            out.append(v)
        return out

    def installed(self, table_va, store):
        """code sites `mov dword ptr [reg+store], table_va` (C7 /0 with a disp8)"""
        sites = []
        for off in self.find(table_va, *self.text):
            if self.mem[off - 3] == 0xC7 and self.mem[off - 2] >> 6 == 1 and self.mem[off - 1] == store:
                sites.append(off - 3)
        return sites

    def cstr(self, va):
        rva = va - self.base
        if not any(lo <= rva < hi for lo, hi in self.data):
            return None
        end = self.mem.find(b"\0", rva, rva + 160)
        return bytes(self.mem[rva:end]) if end != -1 else None


def vcall_slots(img, rva):
    """slots of `call dword ptr [reg+disp]` in order, through the body at rva"""
    out = []
    for i in img.code(rva):
        m = re.fullmatch(r"dword ptr \[e[a-z]{2}(?: \+ (0x[0-9a-f]+|\d+))?\]", i.op_str)
        if i.mnemonic == "call" and m:
            out.append(int(m.group(1) or "0", 0) // 4)
    return out


def direct_calls(img, rva):
    return [int(i.op_str, 16) - img.base for i in img.code(rva)
            if i.mnemonic == "call" and re.fullmatch(r"0x[0-9a-f]+", i.op_str)]


def ilt_stubs(img, target_rva):
    """incremental-link E9 thunks at the start of .text that jump to target_rva (RVAs)"""
    out, rva = [], img.text[0]
    while rva < img.text[1] and img.mem[rva] == 0xCC:
        rva += 1
    while rva + 5 <= img.text[1] and img.mem[rva] == 0xE9:
        if (rva + 5 + struct.unpack_from("<i", img.mem, rva + 1)[0]) & 0xFFFFFFFF == target_rva:
            out.append(rva)
        rva += 5
    return out


def family_tables(img, entry_rva, entry_slot, store):
    """tables whose entry slot holds entry_rva (directly or through its ILT thunk) and that code
    installs at +store"""
    tables = set()
    for target in [entry_rva] + ilt_stubs(img, entry_rva):
        for ref in img.data_refs(target + img.base):
            table = ref - 4 * entry_slot + img.base
            if img.installed(table, store):
                tables.add(table)
    return tables


def labels(img, rva):
    """Class::method strings the body pushes"""
    out = set()
    for i in img.code(rva):
        if i.mnemonic == "push" and re.fullmatch(r"0x[0-9a-f]+", i.op_str):
            s = img.cstr(int(i.op_str, 16))
            m = s and LABEL.fullmatch(s)
            if m:
                out.add((m.group(1).decode(), m.group(2).decode()))
    return out


def map_slot(slot, anchors):
    """WB slot -> game slot through the anchors {wb: game}; None when the rule does not reach it.

    An anchor slot maps directly. A slot one below an anchor maps one below that anchor's game
    slot only when the spacing on both sides agrees: the nearest lower anchor must sit the same
    distance below in both builds, or, with no lower anchor, the anchor above must start a
    contiguous run (it and the next slot up are both anchors, one apart in both builds). A
    build that inserted a virtual between two anchors changes the spacing, and then nothing is
    named."""
    if slot in anchors:
        return anchors[slot]
    above = slot + 1
    if above not in anchors:
        return None
    game = anchors[above] - 1
    if game in anchors.values():
        return None
    lower = [w for w in anchors if w < slot]
    if lower:
        w = max(lower)
        return game if above - w == anchors[above] - anchors[w] else None
    return game if anchors.get(above + 1) == anchors[above] + 1 else None


def wb_labels(wb, family):
    """{class: [(method, wb slot, body rva)]} for the family tables a single class owns"""
    spec = FAMILIES[family]
    entry = WB_IMAGES[wb.sha][1][family]
    tables = sorted(family_tables(wb, entry, spec["entry_slot"], spec["store"]))
    shared = {}
    for t in tables:
        for v in wb.slots(t):
            shared[v] = shared.get(v, 0) + 1
    owners = {}
    for t in tables:
        found = []
        for k, v in enumerate(wb.slots(t)):
            if shared[v] != 1:
                continue                                  # a body several tables share is not the class's own
            for cls, method in labels(wb, v - wb.base):
                found.append((cls, method, k, v - wb.base))
        classes = {c for c, _, _, _ in found}
        if len(classes) == 1:
            owners.setdefault(classes.pop(), []).append((t, found))
    return {c: v[0][1] for c, v in owners.items() if len(v) == 1}       # a class on two tables names nothing


def wb_anchors(wb, family):
    spec = FAMILIES[family]
    entry = WB_IMAGES[wb.sha][1][family]
    calls = direct_calls(wb, entry)
    if len(calls) != 1:
        return None
    seq = tuple(vcall_slots(wb, calls[0]))
    return dict(zip(seq, spec["game_sequence"])) if seq == spec["wb_sequence"] else None


def game_anchors_ok(game, family):
    spec = FAMILIES[family]
    seq = tuple(vcall_slots(game, spec["game_entry"]))
    return seq[1:] == spec["game_sequence"]          # the first call is wouldUpgrade (slot 2)


def registry():
    with open(REGISTRY, encoding="utf-8") as f:
        rows = list(csv.DictReader(f, delimiter="\t"))
    ctors = {}
    for r in rows:
        if r["constructor_rva"]:
            ctors.setdefault(r["module"], set()).add(int(r["constructor_rva"], 16))
    return ctors


def ctor_tables(img, ctor, store):
    """tables the constructor body itself (up to its ret) stores at [reg+store]"""
    out = set()
    for i in img.code(ctor, 0x400):
        m = re.fullmatch(r"dword ptr \[e[a-z]{2} \+ (0x[0-9a-f]+)\], (0x[0-9a-f]+)", i.op_str)
        if i.mnemonic == "mov" and m and int(m.group(1), 16) == store:
            out.add(int(m.group(2), 16))
    return out


def game_body(game, family, cls, slot, ctors, game_tables):
    spec = FAMILIES[family]
    rvas = ctors.get(cls, set())
    if len(rvas) != 1:
        return None, f"{cls}: {len(rvas)} registered constructors"
    ctor = next(iter(rvas))
    mine = ctor_tables(game, ctor, spec["store"]) & game_tables
    if len(mine) != 1:
        return None, f"{cls}: constructor 0x{ctor:08X} installs {len(mine)} family tables"
    mine = sorted(mine)
    entries = game.slots(mine[0])
    if slot >= len(entries):
        return None, f"{cls}: table has no slot {slot}"
    stub = entries[slot]
    if len(game.data_refs(stub)) != 1:
        return None, f"{cls}: slot {slot} entry is shared"
    return game.resolve(stub), f"{cls} table 0x{mine[0]:08X} (ctor 0x{ctor:08X}) slot {slot}"


def derive(wb_paths):
    """rows [(rva, Class::method, evidence)] and notes; refuses ambiguity"""
    game = Image(GAME_EXE)
    wbs = [Image(p) for p in wb_paths]
    for wb, p in zip(wbs, wb_paths):
        if wb.sha not in WB_IMAGES:
            fail(f"{p}: unknown WorldBuilder build (sha256 {wb.sha})")
    ctors, notes, votes = registry(), [], {}
    for family, spec in FAMILIES.items():
        if not game_anchors_ok(game, family):
            fail(f"{family}: the game's call sequence is not {spec['game_sequence']}")
        game_tables = family_tables(game, spec["game_entry"], spec["entry_slot"], spec["store"])
        for wb in wbs:
            build = WB_IMAGES[wb.sha][0]
            anchors = wb_anchors(wb, family)
            if anchors is None:
                fail(f"{family}: {build}'s call sequence is not {spec['wb_sequence']}")
            for cls, found in sorted(wb_labels(wb, family).items()):
                for _, method, wslot, body in found:
                    gslot = map_slot(wslot, anchors)
                    if gslot is None:
                        notes.append(f"{build} {cls}::{method}: WB slot {wslot} has no anchor")
                        continue
                    rva, ev = game_body(game, family, cls, gslot, ctors, game_tables)
                    if rva is None:
                        notes.append(f"{build} {cls}::{method}: {ev}")
                        continue
                    votes.setdefault(rva, {}).setdefault(f"{cls}::{method}", []).append(
                        f"{build} 0x{body:08X} WB slot {wslot} -> {ev}")
    rows, by_name = [], {}
    for rva, names in sorted(votes.items()):
        if len(names) != 1:
            notes.append(f"0x{rva:08X}: labels disagree {sorted(names)}")
            continue
        name, ev = next(iter(names.items()))
        by_name.setdefault(name, []).append((rva, "; ".join(ev)))
    for name, hits in sorted(by_name.items()):
        if len(hits) != 1:
            notes.append(f"{name}: names {len(hits)} addresses")
            continue
        rows.append((hits[0][0], name, hits[0][1]))
    return sorted(rows), notes


def merge(existing, rows):
    """existing CSV rows with every wbslot row replaced by rows. A label name already at the
    address must agree with the slot's name: an agreeing row is kept (its pairing route stays on
    record) and needs no wbslot row; a disagreement stops the tool."""
    named = {rva: name for rva, name, _ in rows}
    keep, covered = [], set()
    for r in existing:
        if r["route"] == ROUTE:
            continue
        rva = int(r["rva"], 16)
        if r["kind"] == "name" and rva in named:
            if r["value"] != named[rva]:
                fail(f"0x{rva:08X}: {r['route']} names {r['value']}, the slot names {named[rva]}")
            covered.add(rva)
        keep.append(r)
    keep += [{"rva": f"0x{rva:08X}", "kind": "name", "value": name, "route": ROUTE, "basis": BASIS}
             for rva, name, _ in rows if rva not in covered]
    return sorted(keep, key=lambda r: (int(r["rva"], 16), r["kind"]))


def read_csv():
    with open(OUT, encoding="utf-8", newline="") as f:
        return list(csv.DictReader(f))


def write_csv(rows):
    with open(OUT, "w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, ["rva", "kind", "value", "route", "basis"], lineterminator="\n")
        w.writeheader()
        w.writerows(rows)


def env_paths(*names):
    return [os.environ[e] for e in names if os.environ.get(e)]


def default_paths():
    return env_paths(*ENV)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--wb", action="append", default=[], help="a known WorldBuilder executable (repeatable)")
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--write", action="store_true")
    g.add_argument("--check", action="store_true")
    args = ap.parse_args()
    paths = args.wb or default_paths()
    if not paths:
        fail("pass --wb EXE (or set BFME2_WORLDBUILDER / ROTWK_WORLDBUILDER)")
    rows, notes = derive(paths)
    existing = read_csv()
    merged = merge(existing, rows)
    if args.check:
        if merged != existing:
            print("ea_wbslot: ea_evidence.csv's wbslot rows are stale: run python3 tools/ea_wbslot.py --write",
                  file=sys.stderr)
            return 1
        return 0
    for n in notes:
        print(n)
    for rva, name, ev in rows:
        print(f"0x{rva:08X}  {name:36} {ev}")
    if args.write:
        write_csv(merged)
        print(f"wrote {len(rows)} wbslot rows to {OUT.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
