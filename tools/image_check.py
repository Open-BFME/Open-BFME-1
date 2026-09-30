#!/usr/bin/env python3
"""Whole-image check: follow what the linker SELECTED, verify it against
retail, and prove each function's dependency closure.

Per-file LINKED (link_census.write_status) asks whether one object links on
its own terms. A clean file can still call a function whose selected body is
wrong two hops away (RecordGridScan -> bfmeConsiderEZ ->
Pathfinder::slowDoesPathExist). This check works on the image the census link
built, at COFF level, section by section:

  selection  every section of every census object (link order from
             objects.rsp), kept the way link.exe kept it: ordinary sections
             always, an external COMDAT when the census /MAP (selected.map)
             names its object as the holder, a static COMDAT always, an
             associative COMDAT with its parent. A name binds to the holder's
             definition; a strong duplicate that is not the holder stays in
             the image unreferenced ("shadowed").
  items      a section splits at its named symbols (code: functions and
             externals; data: every named symbol), so a MASM dump's PROCs, a
             TU's .data statics and a vftable's COL slot are items of their
             own. Leading unnamed bytes belong to the first item.
  edges      every relocation of a selected item to the selected definition
             of its target: an external name through the /MAP holder, a
             static inside its own object, a weak external to its definition
             or, when nothing defines it, to its default (flagged
             weak-fallback), a section symbol plus addend to the item holding
             that offset. An edge goes to the item symbol + addend REACHES
             (`_b+16` is whatever starts 16 bytes into _b's section). A rel
             branch the object already resolved between two items of one
             ordinary section is an edge too (DECODED): no relocation is not
             no dependency. A name nothing defines is a leaf: an import or
             CRT name the real link finds (link_census.excused) or
             unresolved.
  retail     an item with a retail address -- the ledger row or symbols.csv
             pin of an external name (RetailTruth: ILT stubs followed, an
             address several names claim only proves "unknown"), the
             object's own ledger row for a static, dir32_addresses.csv for
             data -- gets ONE home: the candidate its bytes equal retail's
             at outside the relocation fields (zero-fill against retail's
             zero-filled virtual bytes); several matching candidates leave it
             unknown. Every relocation must land on the home of the
             definition the link SELECTED, directly or through a proven ILT
             stub (content-named constants by content; imports on retail's
             IAT slot). An item with no address of its own is placed where a
             byte-true item's relocation says retail put it (component_link's
             propagation, to a fixed point); placements that disagree make it
             unknown, and a derived item is then compared like any other.
  movable    the shifted-placement check: relocated fields move with their
             targets by construction, so an item is movable when no field
             WITHOUT a relocation holds an image address or branches out of
             it (dump_relocs.py's operand rules; shift_finding). A dump body
             (MASM db / __emit, no relocations) fails it wherever it reaches
             outside itself.
  verdicts   retail-true, wrong (a byte or a relocation disagrees with
             retail, or an unrelocated address), unknown (no retail address,
             a target with none, disagreeing placements, an ambiguous
             in-image immediate), shadowed. `retail_verdict` is the verdict
             at retail's placement, before the movable check.
  closure    a function is CLOSED when every node reachable through
             relocation edges (itself included) is retail-true at retail's
             placement or an excused leaf; CLOSED STRICT, the acceptance,
             when every one is also movable. A call or jump through a
             register or data (a virtual call, a function pointer) names no
             destination: it is counted per item (`indirect`), and
             closed_strict_direct also requires none anywhere in the closure.
  queue      for every function that is not closed strict, the nearest bad node
             (first bad path) and the set of bad nodes it reaches; a bad node
             that is some function's ONLY one would close that function by
             itself. Ranked by those bytes (authored + vendored, 0xCC out).

Metrics count authored + vendored .text bytes (progress.source_lane of the
selected item's own object) in retail-true, movable, closed and closed-strict
functions, next to the
census's LINKED. Dumps, generated C++, libraries and scaffold are in the graph
and never in the metric.

  python3 tools/image_check.py --census build/wt_link --tree build/wt_census   # full run
  python3 tools/image_check.py --path '?scan@...'           # why a function is not closed
  python3 tools/image_check.py --queue --limit 30           # bad nodes by bytes they would close

The run reads the objects and artefacts of `--census` (the census worktree)
under its lock (<census>.census-lock, as daily_census.sh takes it), and the
ledger and tools of `--tree`, a checkout of the census commit (the census
worktree rebases after it records). It refuses a --tree whose sources or
ledger differ from that commit, and objects rebuilt after the /MAP. Outputs go to
build/image_check/ of this checkout: items.csv, queue.csv, paths.csv,
summary.json and graph.pkl (read by --path and --queue).
"""
import argparse
import bisect
import collections
import csv
import json
import pickle
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "build" / "image_check"
BASE = 0x400000
DIR32, DIR32NB, SECTION, REL32 = 0x0006, 0x0007, 0x000A, 0x0014
DECODED = 0x10000  # not a COFF type: a rel branch the object resolved inside one section
EXTERNAL, STATIC, WEAK_EXTERNAL = 2, 3, 105
COMDAT, CODE, UNINITIALIZED = 0x1000, 0x20, 0x80
SKIP = 0x800 | 0x200  # LNK_REMOVE | LNK_INFO: .drectve, .sxdata
CONSTANT = ("??_C@", "__real@")  # named by content: retail may hold several copies
ABSOLUTE = {"__except_list": 0}  # fs:[0]
DECOMPILED = ("authored", "vendored")
STUB_OBJECT = "selected_stubs.obj"
COMMON = "<common>"  # the /MAP's holder for a C tentative definition link.exe allocated


def normal(name):
    """A name with its anonymous namespace's per-TU hash normalised."""
    return re.sub(r"\?A0x[0-9A-Fa-f]{8}", "?A0xHASH", name)


# ------------------------------------------------------------------ COFF


class Section:
    __slots__ = ("number", "name", "size", "flags", "body", "relocs", "selection", "assoc", "leader", "items",
                 "starts", "kept")

    def __init__(self, number, name, size, flags, body, relocs):
        self.number, self.name, self.size, self.flags, self.body, self.relocs = number, name, size, flags, body, relocs
        self.selection = self.assoc = self.leader = None
        self.items, self.starts, self.kept = [], [], None


class Obj:
    __slots__ = ("name", "position", "sections", "symbols", "exports", "weak", "commons")

    def __init__(self, name, position):
        self.name, self.position = name, position
        self.sections, self.symbols, self.exports, self.weak = [], {}, {}, {}
        self.commons = {}  # C tentative definitions: name -> size (external, section 0, value = size)


def parse_object(name, data, position=0):
    """Obj with its sections (relocations included), symbol records by raw
    index (name, value, section, type, storage, is section symbol), external
    definitions and weak-external defaults. A short import object has none."""
    obj = Obj(name, position)
    if data[:4] == b"\0\0\xff\xff":
        return obj
    count, _, table, nsyms, optional, _ = struct.unpack_from("<HIIIHH", data, 2)
    strings = table + 18 * nsyms

    def long_name(offset):
        start = strings + offset
        return data[start:data.index(b"\0", start)].decode("latin-1")

    for index in range(count):
        at = 20 + optional + 40 * index
        raw = data[at:at + 8].rstrip(b"\0").decode("latin-1")
        if raw.startswith("/") and raw[1:].isdigit():
            raw = long_name(int(raw[1:]))
        size, pointer, relocs, _, nrelocs, _, flags = struct.unpack_from("<IIIIHHI", data, at + 16)
        if flags & SKIP or raw.startswith(".debug"):
            pointer = nrelocs = 0  # never in the image: no bytes, no edges
        body = None if flags & UNINITIALIZED or not pointer else bytes(data[pointer:pointer + size])
        fixups = list(struct.iter_unpack("<IIH", data[relocs:relocs + 10 * nrelocs])) if nrelocs else []
        obj.sections.append(Section(index + 1, raw, size, flags, body, fixups))
    index = 0
    while index < nsyms:
        at = table + 18 * index
        if data[at:at + 4] == b"\0\0\0\0":
            symbol = long_name(struct.unpack_from("<I", data, at + 4)[0])
        else:
            symbol = data[at:at + 8].rstrip(b"\0").decode("latin-1")
        value, section, kind, storage, aux = struct.unpack_from("<IhHBB", data, at + 8)
        is_section = (storage == STATIC and aux and value == 0 and kind == 0 and 0 < section <= count
                      and symbol == obj.sections[section - 1].name)
        obj.symbols[index] = (symbol, value, section, kind, storage, is_section)
        if is_section:
            sec = obj.sections[section - 1]
            if sec.flags & COMDAT and sec.selection is None:
                number, selection = struct.unpack_from("<HB", data, at + 18 + 12)
                sec.selection, sec.assoc = selection, number if selection == 5 else None
        elif 0 < section <= count:
            sec = obj.sections[section - 1]
            if sec.leader is None and storage in (EXTERNAL, STATIC):
                sec.leader = index  # the COMDAT symbol: the first after the section symbol
            if storage == EXTERNAL:
                obj.exports.setdefault(symbol, (section, value))
        if storage == EXTERNAL and section == 0 and value:
            obj.commons[symbol] = max(value, obj.commons.get(symbol, 0))
        if storage == WEAK_EXTERNAL and aux:
            obj.weak[index] = struct.unpack_from("<I", data, at + 18)[0]
        index += 1 + aux
    return obj


class Item:
    """One definition in the image: [start, end) of a section of an object."""
    __slots__ = ("id", "obj", "sec", "start", "end", "names", "relocs", "code", "candidates", "home", "derived",
                 "verdict", "reason", "edges", "lane", "bound", "constant", "bytes_ok", "pending", "homes",
                 "retail_verdict", "indirect", "literals", "entries")

    def __init__(self, obj, sec, start, end, names):
        self.obj, self.sec, self.start, self.end, self.names = obj, sec, start, end, names
        self.relocs, self.edges, self.pending = [], [], []
        self.code = bool(sec.flags & CODE)
        self.candidates, self.home, self.derived, self.homes = set(), None, False, set()
        self.retail_verdict, self.indirect, self.literals, self.entries = None, 0, 0, set()
        self.verdict, self.reason, self.lane, self.bound = None, "", None, False
        self.constant = any(name.startswith(CONSTANT) for name, _, _ in names)
        self.bytes_ok = False
        self.id = -1

    @property
    def size(self):
        return self.end - self.start

    def label(self):
        return self.names[0][0] if self.names else f"{self.sec.name}+0x{self.start:X}"

    def body(self):
        return None if self.sec.body is None else self.sec.body[self.start:self.end]


class Leaf:
    """A reference target that is not an item: kind import | crt (excused:
    the real link finds it), unresolved, selection-unknown (several
    definitions and no /MAP holder), discarded (a static in a section the
    link dropped), absolute."""
    __slots__ = ("id", "kind", "name", "good", "reason")

    def __init__(self, kind, name, good, reason=""):
        self.kind, self.name, self.good, self.reason, self.id = kind, name, good, reason, -1

    def label(self):
        return self.name


def split_items(obj, sec):
    """Items of one section: a code section splits at functions and
    externals, a data section at every named symbol."""
    starts = collections.defaultdict(list)
    for symbol, value, section, kind, storage, is_section in obj.symbols.values():
        if section != sec.number or is_section or storage not in (EXTERNAL, STATIC) or symbol.startswith("."):
            continue
        if sec.flags & CODE and storage != EXTERNAL and kind & 0x30 != 0x20:
            continue  # a label inside a function
        starts[value].append((symbol, value, storage))
    offsets = sorted(v for v in starts if v < max(sec.size, 1))
    if not offsets or offsets[0] != 0:
        offsets.insert(0, 0)
    items = []
    for i, start in enumerate(offsets):
        end = offsets[i + 1] if i + 1 < len(offsets) else sec.size
        names = sorted(starts.get(start, []), key=lambda n: (n[2] != EXTERNAL, n[0]))
        items.append(Item(obj, sec, start, end, names))
    for where, target, kind in sec.relocs:
        at = bisect.bisect_right(offsets, where) - 1
        items[max(at, 0)].relocs.append((where, target, kind))
    sec.items, sec.starts = items, offsets
    return items


def item_at(sec, offset):
    """The item of `sec` holding `offset` (one past the end: the last item)."""
    at = bisect.bisect_right(sec.starts, offset) - 1
    return sec.items[min(max(at, 0), len(sec.items) - 1)] if sec.items else None


# ------------------------------------------------------------------ image


class Image:
    """The selected image of `objs` (Obj in link order) and its verdicts.

    `kept` is the /MAP's {name: object name}; `truth` a link_census.RetailTruth
    (ledger, pinned, shared, addresses, _stub, _lands); `statics`
    {(object name, name): {rva}} the ledger rows of TU-local names; `read(rva,
    size)` retail's bytes (virtual image, .bss zero-filled) or None;
    `excused(name)` -> "import" | "crt" | None; `lanes` {object name: {name:
    lane, None: default lane}}; `text` retail .text (start, end)."""

    def __init__(self, objs, kept, truth, statics, read, excused, lanes, text, image_size, unresolved_kinds=None,
                 row_homes=None, scalars=None, map_commons=None):
        # C tentative (common) symbols no section defines: link.exe allocates them in .bss itself (<common> in
        # the /MAP, `map_commons`), sized by the largest declaration; they become items of one synthetic object
        self.map_commons = map_commons
        self.literal_homes = {}  # retail address -> content-named constant retail-true code reads there
        self.common = Obj(COMMON, len(objs))
        # {(retail VA, value)} data words typed evidence proves scalar (workstream B's proven_scalars.csv)
        self.scalars, self.proven_scalars = scalars or set(), 0
        self.image_size, self._md, self._known, self.numbers = image_size, None, None, 0
        self.objs, self.kept, self.truth, self.statics = objs, kept, truth, statics
        self.row_homes = row_homes  # matched ledger addresses: the metric counts only these
        self.read, self.excused, self.lanes, self.text = read, excused, lanes, text
        self.unresolved_kinds = unresolved_kinds or {}
        import inspect  # RetailTruth.addresses took no relocation kind before 2026-09-29
        self._by_kind = len(inspect.signature(truth.addresses).parameters) > 1
        self.by_name = {}
        for obj in objs:
            self.by_name.setdefault(obj.name, obj)
        self.items, self.leaves, self._bind, self.weak_fallbacks = [], {}, {}, []
        self.crossing = {}  # (item id, relocation offset) -> the item the symbol names, when + addend leaves it
        self.unmapped = collections.defaultdict(list)
        for obj in objs:
            for name in obj.exports:
                if name not in kept:
                    self.unmapped[name].append(obj)
        sizes = {}
        for obj in objs:
            for name, size in obj.commons.items():
                if kept.get(name, COMMON) == COMMON and name not in self.unmapped:  # a definition absorbs a common
                    sizes[name] = max(size, sizes.get(name, 0))
        for name, size in sorted(sizes.items()):
            if map_commons is not None and name not in map_commons:
                continue  # the link did not allocate it: leave it to the ordinary rules
            sec = Section(len(self.common.sections) + 1, ".bss$common", size, UNINITIALIZED | 0x40, None, [])
            sec.kept = True
            self.common.sections.append(sec)
            self.common.exports[name] = (sec.number, 0)
        if self.common.sections:
            self.objs = list(objs) + [self.common]
            self.by_name[self.common.name] = self.common

    # -------------------------------------------------------- selection

    def section_kept(self, obj, sec, depth=0):
        if sec.kept is not None:
            return sec.kept
        if not sec.flags & COMDAT:
            result = True
        elif sec.selection == 5 and sec.assoc:
            parent = obj.sections[sec.assoc - 1] if 0 < sec.assoc <= len(obj.sections) else None
            result = bool(parent) and depth < 8 and self.section_kept(obj, parent, depth + 1) is True
        elif sec.leader is None:
            result = True
        else:
            name, _, _, _, storage, _ = obj.symbols[sec.leader]
            if storage != EXTERNAL:
                result = True
            elif name in self.kept:
                result = self.kept[name] == obj.name
            else:
                result = len(self.unmapped.get(name, ())) == 1 or None
        sec.kept = result
        return result

    def bind(self, name):
        """The item or leaf a reference to external `name` resolves to."""
        if name in self._bind:
            return self._bind[name]
        holder = self.kept.get(name)
        found = None
        if holder is not None and holder != STUB_OBJECT:
            obj = self.by_name.get(holder)
            if obj is not None and name in obj.exports:
                section, value = obj.exports[name]
                sec = obj.sections[section - 1]
                found = item_at(sec, value) if sec.kept else None
        elif holder is None and name in self.common.exports:
            section, _ = self.common.exports[name]
            found = self.common.sections[section - 1].items[0]
        elif holder is None and name in self.unmapped:
            owners = self.unmapped[name]
            if len(owners) == 1:
                section, value = owners[0].exports[name]
                sec = owners[0].sections[section - 1]
                found = item_at(sec, value) if sec.kept else None
            else:
                found = self.leaf("selection-unknown", name, False,
                                  f"{len(owners)} definitions and no /MAP holder")
        if found is None:
            if name in ABSOLUTE:
                found = self.leaf("absolute", name, True)
            else:
                excuse = self.excused(name)
                if excuse:
                    found = self.leaf(excuse, name, True)
                else:
                    kind = self.unresolved_kinds.get(name, "")
                    why = f"nothing defines it{' (' + kind + ')' if kind else ''}"
                    found = self.leaf("unresolved", name, False, why)
        self._bind[name] = found
        return found

    def leaf(self, kind, name, good, reason=""):
        key = (kind, name)
        if key not in self.leaves:
            self.leaves[key] = Leaf(kind, name, good, reason)
        return self.leaves[key]

    def select(self):
        """Keep sections, split items, bind names, resolve every edge."""
        for obj in self.objs:
            if obj is self.common:
                for name, (number, _) in self.common.exports.items():
                    sec = obj.sections[number - 1]
                    sec.items, sec.starts = [Item(obj, sec, 0, sec.size, [(name, 0, EXTERNAL)])], [0]
                continue
            for sec in obj.sections:
                if sec.flags & SKIP or sec.name.startswith(".debug") or not sec.size:
                    continue
                if self.section_kept(obj, sec) is True:
                    split_items(obj, sec)
        for obj in self.objs:
            for sec in obj.sections:
                for item in sec.items:
                    item.id = len(self.items)
                    self.items.append(item)
                    item.bound = self._is_bound(item)
                    lanes = self.lanes.get(obj.name, {})
                    item.lane = next((lanes[n] for n, _, _ in item.names if n in lanes), lanes.get(None))
        for item in self.items:
            if item.bound:
                self._edges(item)
        # Interior entry points and decoded branches feed each other: an entry
        # reached through a relocation can reveal a decoded branch to another
        # item, which can enter a third item mid-body. Iterate to a fixed point.
        decodable = [item for item in self.items if item.bound and item.code and len(item.sec.items) > 1
                     and item.sec.body is not None]
        changed = True
        while changed:
            changed = False
            for item in self.items:  # where other items enter a function: every one is a descent root
                for _, _, target, position, _ in item.edges:
                    if isinstance(target, Item) and target is not item and target.code \
                            and target.start < position < target.end \
                            and position - target.start not in target.entries:
                        target.entries.add(position - target.start)
                        changed = True
            for item in decodable:
                changed |= self._decoded_edges(item)
        for index, leaf in enumerate(self.leaves.values()):
            leaf.id = len(self.items) + index

    def _code_literals(self):
        """Relabel an unresolved name whose retail address is where
        retail-true code reads one of the image's content-named constants
        (`__real@3f800000`, the shared 1.0f; self.literal_homes, filled by
        edges_at): the source names a global where retail uses a compiler
        literal. Matching bytes alone prove nothing (every 4 zero bytes
        would be 0.0f). Still unresolved: nothing defines the name."""
        for leaf in self.leaves.values():
            if leaf.kind != "unresolved":
                continue
            homes = self.truth.addresses(leaf.name, DIR32) if self._by_kind else self.truth.addresses(leaf.name)
            literal = next((self.literal_homes[h] for h in sorted(homes or ()) if h in self.literal_homes), None)
            if literal:
                leaf.kind = "code-literal"
                leaf.reason = f"retail code reads the compiler literal {literal} there; nothing defines the name"

    def _is_bound(self, item):
        if not item.names:
            return True  # reached through its section symbol
        for name, _, storage in item.names:
            if storage != EXTERNAL or self.bind(name) is item:
                return True
        return False

    def _edges(self, item):
        obj, body = item.obj, item.sec.body
        for where, index, kind in item.relocs:
            symbol = obj.symbols.get(index)
            addend = struct.unpack_from("<i", body, where)[0] if body and kind in (DIR32, DIR32NB, REL32) \
                and where + 4 <= len(body) else 0
            if symbol is None:
                item.edges.append((where, kind, self.leaf("unresolved", f"<symbol {index}>", False), 0, ""))
                continue
            name, value, section, _, storage, is_section = symbol
            flag = ""
            if storage == WEAK_EXTERNAL:
                target = self.bind(name)
                if isinstance(target, Leaf) and not target.good:
                    default = obj.symbols.get(obj.weak.get(index))
                    if default is not None:
                        flag = f"weak-fallback:{default[0]}"
                        self.weak_fallbacks.append((item, where, name, default[0]))
                        name, value, section, _, storage, is_section = default
                        target = None
                if target is not None:
                    self._add_edge(item, where, kind, target, self._position(target, name, addend), flag)
                    continue
            if storage == EXTERNAL and name not in ABSOLUTE:
                target = self.bind(name)
                self._add_edge(item, where, kind, target, self._position(target, name, addend), flag)
                continue
            if storage == EXTERNAL:
                item.edges.append((where, kind, self.leaf("absolute", name, True), 0, flag))
                continue
            if 0 < section <= len(obj.sections):
                sec = obj.sections[section - 1]
                if not sec.items:
                    item.edges.append((where, kind, self.leaf("discarded", f"{name} ({obj.name})", False,
                                                              "a static in a section the link dropped"), 0, flag))
                    continue
                position = value + addend
                target = item_at(sec, position if is_section else value)
                self._add_edge(item, where, kind, target, position, flag)
                continue
            item.edges.append((where, kind, self.leaf("unresolved", name, False, "no definition"), 0, flag))

    def _add_edge(self, item, where, kind, named, position, flag):
        """An edge to the item `position` (symbol + addend, a section offset)
        actually reaches: link.exe computes symbol + addend, and in this
        image the section is laid out as the object lays it out, so `_b+16`
        executes whatever item starts 16 bytes into _b's section. A data
        pointer just past the named item (an end sentinel) or outside the
        section stays on the named item; a branch has no sentinel. A crossing
        edge keeps the named item (self.crossing) for the retail check."""
        target = named
        end = named.end if kind in (DIR32, DIR32NB) and isinstance(named, Item) else None
        if isinstance(named, Item) and not (named.start <= position < named.end or position == end) \
                and 0 <= position < named.sec.size:
            target = item_at(named.sec, position)
            if target is not named:
                flag = (flag + " " if flag else "") + f"addend-crosses-from:{named.label()}"
                self.crossing[(item.id, where)] = named
        item.edges.append((where, kind, target, position, flag))

    def _decoded_edges(self, item):
        """Transfers the object already resolved: a rel branch with no
        relocation from one item to another of the same ordinary section (a
        MASM file's PROCs, a TU without /Gy). No relocation is not no
        dependency: each becomes an edge of kind DECODED. Returns whether
        an edge was added (select() iterates with interior entry points)."""
        body = item.body()
        known = {(where, target.id) for where, kind, target, _, _ in item.edges if kind == DECODED}
        added = False
        fields = self._fields(item)
        covered = self._covered(fields)
        insns, _ = self._instructions(item, body, fields, covered)
        for off, insn in insns:
            branch = self._branch(insn)
            if branch is None or off + insn.imm_offset in covered:
                continue
            destination = item.start + branch - self._VA
            if 0 <= destination < item.sec.size and not item.start <= destination < item.end:
                target = item_at(item.sec, destination)
                where = item.start + off + insn.imm_offset
                if (where, target.id) not in known:
                    known.add((where, target.id))
                    item.edges.append((where, DECODED, target, destination, "decoded"))
                    added = True
        return added

    @staticmethod
    def _position(target, name, addend):
        """Section offset a reference to `name` + addend means in `target`."""
        if not isinstance(target, Item):
            return 0
        return target.obj.exports.get(name, (None, target.start))[1] + addend

    # -------------------------------------------------------- retail

    def anchor(self):
        """Retail addresses of every bound item from the ledger and pins."""
        truth = self.truth
        for item in self.items:
            if not item.bound or item.constant:
                continue
            for name, value, storage in item.names:
                if storage == EXTERNAL:
                    key = normal(name)
                    homes = truth.ledger.get(key) or truth.pinned.get(key) or ()
                else:
                    homes = self.statics.get((item.obj.name, name)) or (
                        truth.pinned.get(normal(name), ()) if name.startswith("?") else ())
                homes = set(homes)
                if item.code:  # a row or pin on an ILT stub: the stub (a ?j_ thunk) or its target
                    homes |= {truth._stub(address) for address in homes} - {None}
                item.candidates |= {home - (value - item.start) for home in homes}

    def _actual(self, home, where, kind, retail):
        value = struct.unpack_from("<i", retail, where)[0]
        if kind == DIR32:
            return (value - BASE) & 0xFFFFFFFF
        if kind == DIR32NB:
            return value & 0xFFFFFFFF
        return (home + where + 4 + value) & 0xFFFFFFFF

    def bytes_at(self, item, home):
        """None when `item` placed at retail `home` equals retail outside its
        relocation fields, else why not. Zero-fill (.bss) must meet retail
        zeros: retail's virtual bytes there, past raw data or zero in it."""
        if item.sec.body is None:
            if self.text[0] <= home < self.text[1]:
                return f"uninitialized data, but retail's 0x{home:08X} is code"
            chunk = self.read(home, item.size)
            if chunk is None:
                return f"0x{home:08X} is outside retail's image"
            if chunk.count(0) != len(chunk):
                first = next(i for i, b in enumerate(chunk) if b)
                return f"zero-fill, but retail holds 0x{chunk[first]:02X} at +0x{first:X} (0x{home + first:08X})"
            return None
        retail = self.read(home, item.size)
        if retail is None:
            return f"0x{home:08X} is outside retail's image"
        ours, theirs = bytearray(item.body()), bytearray(retail)
        for where, _, kind in item.relocs:
            at, width = where - item.start, 2 if kind == SECTION else 4
            if at + width > len(ours):
                return f"relocation at +0x{at:X} runs past the item"
            ours[at:at + width] = theirs[at:at + width]
        if ours != theirs:
            first = next(i for i in range(len(ours)) if ours[i] != theirs[i])
            return f"bytes differ at +0x{first:X} (0x{home + first:08X})"
        return None

    def judge_at(self, item, home):
        """(status, reason, proposals, pending, bytes_ok) of `item` placed at
        retail `home`: its bytes, then every relocation (edges_at)."""
        reason = self.bytes_at(item, home)
        if reason:
            return "wrong", reason, [], [], False
        return (*self.edges_at(item, home), True)

    def edges_at(self, item, home):
        """(status, reason, proposals, pending) for the relocations of a
        byte-true `item` at `home`. REL32/DIR32 values include the addend, so
        a target's expected address is its home plus the position. An
        anchored target is expected at the ONE home its bytes proved
        (target.homes), or through a proven ILT route to it; an unanchored
        one is proposed where retail's field says it is."""
        truth = self.truth
        retail = self.read(home, item.size)
        status, reason, proposals, pending = "retail", "", [], []
        for where, kind, target, position, _ in item.edges:
            at = where - item.start
            if kind not in (DIR32, DIR32NB, REL32, DECODED):
                if status == "retail":
                    status, reason = "unknown", f"relocation type 0x{kind:X} at +0x{at:X}"
                continue
            # a decoded branch's bytes matched retail: it lands where its displacement says
            actual = home + position - item.start if kind == DECODED else self._actual(home, at, kind, retail)
            if isinstance(target, Leaf):
                if target.kind == "absolute":
                    if kind == DIR32 and target.name in ABSOLUTE:
                        if (actual + BASE) & 0xFFFFFFFF != ABSOLUTE[target.name]:
                            return "wrong", f"+0x{at:X} {target.name} is not absolute 0", [], []
                    continue
                expected = None
                if target.kind in ("import", "crt", "unresolved"):
                    expected = truth.addresses(target.name, kind) if self._by_kind else truth.addresses(target.name)
                if not expected:
                    if status == "retail":
                        status, reason = "unknown", f"+0x{at:X} {target.name}: no retail address"
                    continue
                if not truth._lands(actual, expected):
                    if all(a in truth.shared for a in expected):
                        status, reason = "unknown", f"+0x{at:X} {target.name}: only a shared claim disagrees"
                        continue
                    return "wrong", (f"+0x{at:X} {target.name} lands at 0x{actual:08X}, retail's is "
                                     f"{_hexes(expected)}"), [], []
                continue
            offset = position - target.start
            if target is item:
                if actual != home + offset:
                    return "wrong", f"+0x{at:X} own label lands at 0x{actual:08X}", [], []
                continue
            if target.constant:
                body = target.body()
                if body is None or self.read((actual - offset) & 0xFFFFFFFF, len(body)) != body:
                    return "wrong", f"+0x{at:X} {target.label()} is not at 0x{actual:08X}", [], []
                self.literal_homes.setdefault((actual - offset) & 0xFFFFFFFF, target.label())
                continue
            if target.candidates:
                expected = {h + offset for h in target.homes}
                if actual in expected or (offset == 0 and truth._lands(actual, expected)):
                    continue
                if all(c in truth.shared for c in target.candidates):
                    status, reason = "unknown", f"+0x{at:X} {target.label()}: only a shared claim disagrees"
                    continue
                named = self.crossing.get((item.id, where))
                if named is not None and named.homes and \
                        actual in {h + position - named.start for h in named.homes}:
                    # retail's value is named-relative arithmetic; this image reaches another item there
                    status, reason = "unknown", (f"+0x{at:X} {named.label()}+0x{position - named.start:X} is "
                                                 f"retail's value, but here it reaches {target.label()}")
                    continue
                return "wrong", (f"+0x{at:X} {target.label()} ({target.obj.name}) lands at 0x{actual:08X}, "
                                 f"its retail address is {_hexes(expected)}"), [], []
            base = (actual - offset) & 0xFFFFFFFF
            if target.code and offset == 0:
                stub = truth._stub(base)
                body = target.body()
                if stub is not None and not (body and body[0] == 0xE9):
                    base = stub
            inside = self.text[0] <= base < self.text[1]
            if self.read(base, max(target.size, 1)) is None or inside != target.code:
                # retail's field names no place such an item can be: the relocation is not retail's
                place = ("outside retail's image" if self.read(base, 1) is None else
                         "inside retail's .text" if inside else "outside retail's .text")
                kind_ = "code" if target.code else "data"
                return "wrong", f"+0x{at:X} {target.label()} ({kind_}) would be at 0x{base:08X}, {place}", [], []
            proposals.append((target, base))
            pending.append((at, target))
        return status, reason, proposals, pending

    # -------------------------------------------------------- shifted placement

    def in_image(self, value):
        return BASE <= value < BASE + self.image_size

    def shift_finding(self, item):
        """(status, reason) when `item` would not survive a placement other
        than retail's, else None. Every relocated field moves with its
        target by construction; what does not move is a field with no
        relocation: an operand holding an image address, or a branch out of
        the item. dump_relocs.py's operand rules decide: a rel branch leaving
        the item and a disp32 (absolute, SIB or based) inside the image are
        addresses (wrong); a push/mov imm32 inside the image is ambiguous
        (unknown), and wrong when a ledger row, pin or placed item starts at
        it; any other imm32 (cmp, test, arithmetic) is a number. Data has no
        operand to read: an item holding an unrelocated in-image dword, at
        any offset (a packed struct's pointer need not be aligned), is
        unknown (`literals`, items.csv) until typed evidence says pointer or
        scalar (`--scalars`: a (retail VA, value) pair listed there is a
        number). Retail has no base relocations to say which dwords are
        pointers, and on 2026-09-30 all 16 data dwords that hit the
        ledger-start evidence were byte or short tables (Lua's opcode
        properties 0x01000000, zlib's configuration_table, D3DX shader
        tables): such an item is retail-true at retail's placement (the
        non-strict figures) and blocks only closed strict."""
        body = item.body()
        if body is None or item.constant:
            return None
        fields = self._fields(item)
        covered = self._covered(fields)
        if not item.code:
            first = None
            for off in range(len(body) - 3):  # packed structs put pointers at any offset
                if any(at in covered for at in range(off, off + 4)):
                    continue
                value = struct.unpack_from("<I", body, off)[0]
                if self.in_image(value) and value >= BASE + 0x1000:
                    if (BASE + item.home + off, value) in self.scalars:
                        self.proven_scalars += 1  # typed evidence: a number, not a pointer
                        continue
                    item.literals += 1
                    self.numbers += 1
                    first = first or (off, value)
            if first:
                return "unknown", (f"{item.literals} unrelocated in-image dword(s), first 0x{first[1]:08X} at "
                                   f"+0x{first[0]:X}: pointer or scalar unproven (needs typed evidence)")
            return None
        return self._scan_code(item, body, fields, covered)

    def known_address(self, value):
        """Address evidence for an in-image value: a matched ledger row, a
        symbols.csv pin or dir32 entry, or a placed item starts there."""
        if self._known is None:
            known = set(self.row_homes or ())
            for table in (self.truth.ledger, self.truth.pinned):
                for homes in table.values():
                    known.update(homes)
            known.update(item.home for item in self.items if item.home is not None)
            self._known = known
        return (value - BASE) in self._known

    _VA = 0x10000000  # any base: branch destinations are read item-relative

    @staticmethod
    def _fields(item):
        """Item-relative (start, end) of every relocation field."""
        return sorted((where - item.start, where - item.start + (2 if kind == SECTION else 4))
                      for where, _, kind in item.relocs)

    @staticmethod
    def _covered(fields):
        covered = set()
        for low, high in fields:
            covered.update(range(low, high))
        return covered

    def _instructions(self, item, body, fields, covered):
        """([(offset, instruction)], problem) by recursive descent from the
        item's start and every interior point another item's edge enters
        (item.entries): fall-through, rel branch and call targets inside the
        item, and the entries of its own switch tables (a relocation back
        into the item that is no instruction's operand). A table sits where
        code reaches it only as data, so code after a table is decoded
        whenever a branch reaches it. `problem` says why the code could not
        be fully inspected: an undecodable byte, an instruction overlapping
        a relocation field, a relocation field reached as code, or bytes
        before the first table that nothing reaches (0xCC/NOP padding
        aside)."""
        if self._md is None:
            from capstone import CS_ARCH_X86, CS_MODE_32, Cs
            self._md = Cs(CS_ARCH_X86, CS_MODE_32)
            self._md.detail = True
        from capstone import CS_GRP_JUMP, CS_GRP_RET
        starts = {low for low, _ in fields}
        size = len(body)
        own = {where - item.start: position - item.start
               for where, kind, target, position, _ in item.edges if target is item and kind != DECODED}
        found, operands, problem = {}, set(), None
        pending, seen_entries = [0] + sorted(item.entries), {0} | item.entries
        while True:
            while pending:
                off = pending.pop()
                while 0 <= off < size and off not in found:
                    if off in covered:
                        problem = problem or f"a relocation field at +0x{off:X} is reached as code"
                        break
                    insn = next(self._md.disasm(body[off:off + 16], self._VA + off, 1), None)
                    if insn is None:
                        problem = problem or f"undecodable byte at +0x{off:X}"
                        break
                    end = off + insn.size
                    fields_here = {off + insn.disp_offset if insn.disp_size else None,
                                   off + insn.imm_offset if insn.imm_size else None}
                    if any(off < low < end and low not in fields_here for low in starts):
                        problem = problem or f"the instruction at +0x{off:X} overlaps a relocation field"
                        break
                    found[off] = insn
                    operands |= fields_here
                    groups = set(insn.groups)
                    if CS_GRP_RET in groups or insn.mnemonic in ("int3", "hlt", "ud2"):
                        break
                    branch = self._branch(insn)
                    if branch is not None:
                        destination = branch - self._VA
                        if 0 <= destination < size and destination not in found:
                            pending.append(destination)
                        if insn.mnemonic == "jmp":
                            break
                    elif CS_GRP_JUMP in groups:
                        break  # an indirect jmp: its switch-table entries are followed below
                    off = end
            entries = {target for field, target in own.items() if field not in operands and 0 <= target < size}
            fresh = entries - seen_entries
            if not fresh:
                break
            seen_entries |= fresh
            pending.extend(fresh)
        tables = [field for field in own if field not in operands] + \
            [target for field, target in own.items() if field in operands and target not in found]
        data_start = min(tables, default=size)
        spans = set()
        for off, insn in found.items():
            spans.update(range(off, off + insn.size))
        unreached = [i for i in range(data_start) if i not in spans and i not in covered]
        unreached = self._not_filler(body, unreached)
        if unreached and problem is None:
            problem = (f"{len(unreached)} bytes before any table are reached by no decoded path "
                       f"(first +0x{unreached[0]:X})")
        return sorted(found.items()), problem

    FILLER = re.compile(r"^(?:(?:lea|mov|xchg) (\w+), \[?\1\]?)?$")

    def _not_filler(self, body, offsets):
        """The offsets of `offsets` that are not padding: int3, nop, and
        MSVC's alignment fillers (lea r,[r+0], mov r,r, xchg r,r)."""
        out, runs = [], []
        for off in offsets:
            if runs and runs[-1][1] == off:
                runs[-1][1] = off + 1
            else:
                runs.append([off, off + 1])
        for low, high in runs:
            off = low
            while off < high:
                insn = next(self._md.disasm(body[off:high], self._VA + off, 1), None)
                text = f"{insn.mnemonic} {insn.op_str}".strip() if insn else ""
                if insn is None or not (insn.mnemonic in ("int3", "nop") or self.FILLER.match(text)):
                    out.extend(range(off, high))
                    break
                off += insn.size
        return out

    @staticmethod
    def _branch(insn):
        """The destination (at _VA) of a rel call/jmp/jcc, else None."""
        from capstone import CS_GRP_CALL, CS_GRP_JUMP
        from capstone.x86 import X86_OP_IMM
        ops = insn.operands
        if set(insn.groups) & {CS_GRP_JUMP, CS_GRP_CALL} and len(ops) == 1 and ops[0].type == X86_OP_IMM:
            return ops[0].imm & 0xFFFFFFFF
        return None

    def _scan_code(self, item, body, fields, covered):
        """shift_finding for code. Also counts, in item.indirect, the calls
        and jumps whose destination the code does not state: through a
        register or through memory other than an import slot or the item's
        own switch table (a virtual call, a function pointer). Those are an
        unproven boundary, never an absent dependency."""
        from capstone import CS_GRP_CALL, CS_GRP_JUMP
        from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_FS, X86_REG_GS, X86_REG_INVALID
        targets = {where - item.start: target for where, _, target, _, _ in item.edges}
        unknown, indirect = None, 0
        insns, problem = self._instructions(item, body, fields, covered)
        if problem:  # code this check could not fully inspect proves nothing about moving
            unknown = ("unknown", f"not fully inspected: {problem}")
        for off, insn in insns:
            ops = insn.operands
            branch = self._branch(insn)
            if branch is not None:
                destination = item.start + branch - self._VA
                if off + insn.imm_offset not in covered and not 0 <= destination < item.sec.size:
                    item.indirect = indirect
                    return "wrong", f"unrelocated {insn.mnemonic} at +0x{off:X} leaves its section (not movable)"
                continue
            if set(insn.groups) & {CS_GRP_JUMP, CS_GRP_CALL} and ops:
                target = targets.get(off + insn.disp_offset) if insn.disp_size == 4 else None
                switch = (insn.mnemonic == "jmp" and ops[0].type == X86_OP_MEM and ops[0].mem.base == X86_REG_INVALID
                          and ops[0].mem.index != X86_REG_INVALID and target is item)
                if not (isinstance(target, Leaf) and target.kind == "import") and not switch:
                    indirect += 1
            for op in ops:
                if op.type == X86_OP_MEM and insn.disp_size == 4:
                    if op.mem.segment in (X86_REG_FS, X86_REG_GS):
                        continue
                    value = op.mem.disp & 0xFFFFFFFF
                    if off + insn.disp_offset not in covered and self.in_image(value):
                        item.indirect = indirect
                        return "wrong", (f"unrelocated address 0x{value:08X} in `{insn.mnemonic} {insn.op_str}` "
                                         f"at +0x{off:X} (not movable)")
                elif op.type == X86_OP_IMM and insn.imm_size == 4:
                    value = op.imm & 0xFFFFFFFF
                    if (unknown is None and off + insn.imm_offset not in covered and self.in_image(value)
                            and insn.mnemonic in ("push", "mov")):
                        if self.known_address(value):
                            item.indirect = indirect
                            return "wrong", (f"unrelocated address 0x{value:08X} (a ledger row, pin or placed item "
                                             f"starts there) in `{insn.mnemonic} {insn.op_str}` at +0x{off:X}")
                        unknown = ("unknown", f"unrelocated in-image immediate 0x{value:08X} in "
                                              f"`{insn.mnemonic} {insn.op_str}` at +0x{off:X} (ambiguous, "
                                              "not movable)")
        item.indirect = indirect
        return unknown

    # -------------------------------------------------------- verdicts

    def verify(self):
        """Resolve one home per anchored item (the candidate its bytes
        match), judge its relocations against the homes of what the link
        selected, propagate placements to a fixed point, settle every verdict
        at retail's placement, then check that each retail-true item would
        survive another placement."""
        truth = self.truth
        placements = collections.defaultdict(dict)  # item -> {home: first proposer}
        judged, queue, failed = {}, [], {}

        def preference(home):  # a body before an ILT stub, so a report names the body
            return truth._stub(home) is not None, home
        anchored = [i for i in self.items if i.bound and i.candidates and not i.constant]
        for item in anchored:
            reasons = {home: self.bytes_at(item, home) for home in item.candidates}
            matches = sorted((h for h, r in reasons.items() if r is None), key=preference)
            if matches:
                item.home, item.homes = matches[0], set(matches)
            else:
                item.home = min(item.candidates, key=preference)
                item.homes = set(item.candidates)
                failed[item] = reasons[item.home]
        for item in anchored:
            if item in failed:
                shared = all(home in truth.shared for home in item.candidates)
                judged[item] = ("unknown" if shared else "wrong",
                                ("shared address: " if shared else "") + failed[item], [], [], False)
            elif len(item.homes) > 1:
                judged[item] = ("unknown", "bytes match at several candidate addresses " + _hexes(item.homes),
                                [], [], True)
            else:
                judged[item] = (*self.edges_at(item, item.home), True)
            queue.append(item)
        while queue:
            fresh = []
            for item in queue:
                status, _, proposals, _, bytes_ok = judged[item]
                if not bytes_ok:
                    continue
                for target, base in proposals:
                    if base not in placements[target]:
                        placements[target][base] = item
                    if target.home is None and not target.candidates and target.bound:
                        target.home, target.derived = base, True
                        judged[target] = self.judge_at(target, base)
                        fresh.append(target)
            queue = fresh
        conflicts = {target for target, homes in placements.items() if len(homes) > 1 and not target.candidates}
        for item in self.items:
            if item.constant:
                status, reason = "retail", "content-named constant"
            elif not item.bound:
                status, reason = "shadowed", "another object's definition is the selected one"
            elif item not in judged:
                status, reason = "unknown", "no retail address (no row, pin or placing reference)"
            else:
                status, reason, _, pending, bytes_ok = judged[item]
                item.bytes_ok, item.pending = bytes_ok, pending
                if item in conflicts:
                    homes = placements[item]
                    status, reason = "unknown", "placements disagree: " + ", ".join(
                        f"0x{h:08X} ({p.label()})" for h, p in sorted(homes.items())[:3])
                elif status == "retail":
                    bad = [(at, t) for at, t in pending if t in conflicts]
                    if bad:
                        status, reason = "unknown", f"+0x{bad[0][0]:X} {bad[0][1].label()}: placements disagree"
                if item.derived and status == "wrong" and reason:
                    proposer = placements[item].get(item.home)
                    reason += f" (placed by {proposer.label() if proposer else '?'})"
            item.retail_verdict = status
            if status == "retail":
                found = self.shift_finding(item)
                if found:
                    status, reason = found
            item.verdict, item.reason = status, reason

    # -------------------------------------------------------- closure

    def text_bytes(self, item):
        """Real (0xCC out) retail .text bytes under the item's home."""
        if item.home is None or not item.code:
            return 0
        low, high = max(item.home, self.text[0]), min(item.home + item.size, self.text[1])
        if low >= high:
            return 0
        chunk = self.read(low, high - low) or b""
        return len(chunk) - chunk.count(0xCC)

    def closure(self):
        """Per node, twice: the reachable bad set (up to 2 nodes, None =
        more) with good = retail-true at retail's placement (`badset_retail`)
        and with good = retail-true AND movable (`badset`, the acceptance);
        and for the latter the next hop toward the nearest bad node."""
        nodes = self.items + list(self.leaves.values())
        count = len(nodes)
        succ = [()] * count
        for item in self.items:
            if item.edges:
                succ[item.id] = tuple({t.id for _, _, t, _, _ in item.edges if t.id != item.id})
        good = [False] * count
        good_retail = [False] * count
        for node in nodes:
            if isinstance(node, Leaf):
                good[node.id] = good_retail[node.id] = node.good
            else:
                good[node.id] = node.verdict == "retail"
                good_retail[node.id] = node.retail_verdict == "retail"
        comp = self._scc(succ)
        self.badset = self._badsets(succ, comp, good)
        self.badset_retail = self._badsets(succ, comp, good_retail)
        direct = [good[n] and not (isinstance(node, Item) and node.indirect) for n, node in enumerate(nodes)]
        self.badset_direct = self._badsets(succ, comp, direct)
        pred = [[] for _ in range(count)]
        for node in range(count):
            for nxt in succ[node]:
                pred[nxt].append(node)
        hop = [None] * count
        dist = [None] * count
        frontier = [n for n in range(count) if not good[n]]
        for n in frontier:
            dist[n] = 0
        while frontier:
            fresh = []
            for n in frontier:
                for p in pred[n]:
                    if dist[p] is None:
                        dist[p], hop[p] = dist[n] + 1, n
                        fresh.append(p)
            frontier = fresh
        self.nodes, self.succ, self.good = nodes, succ, good
        self.hop, self.dist = hop, dist

    @staticmethod
    def _badsets(succ, comp, good):
        """Reachable bad nodes per node, up to two (None = more)."""
        members = collections.defaultdict(list)
        for node, c in enumerate(comp):
            members[c].append(node)
        badset = {}
        for c in sorted(members):  # _scc numbers components in reverse topological order
            found, many = set(), False
            for node in members[c]:
                if not good[node]:
                    found.add(node)
                for nxt in succ[node]:
                    d = comp[nxt]
                    if d == c:
                        continue
                    if badset[d] is None:
                        many = True
                    else:
                        found |= badset[d]
                if len(found) > 2:
                    many = True
            badset[c] = None if many else frozenset(found)
        return [badset[comp[n]] for n in range(len(comp))]

    @staticmethod
    def _scc(succ):
        """Tarjan, iterative: component number per node, numbered in the
        order components complete (successors first)."""
        count = len(succ)
        index, low, comp = [None] * count, [0] * count, [None] * count
        stack, on, counter, number = [], [False] * count, 0, 0
        for root in range(count):
            if index[root] is not None:
                continue
            work = [(root, 0)]
            index[root] = low[root] = counter
            counter += 1
            stack.append(root)
            on[root] = True
            while work:
                node, i = work[-1]
                edges = succ[node]
                if i < len(edges):
                    work[-1] = (node, i + 1)
                    nxt = edges[i]
                    if index[nxt] is None:
                        index[nxt] = low[nxt] = counter
                        counter += 1
                        stack.append(nxt)
                        on[nxt] = True
                        work.append((nxt, 0))
                    elif on[nxt]:
                        low[node] = min(low[node], index[nxt])
                    continue
                work.pop()
                if work:
                    parent = work[-1][0]
                    low[parent] = min(low[parent], low[node])
                if low[node] == index[node]:
                    while True:
                        member = stack.pop()
                        on[member] = False
                        comp[member] = number
                        if member == node:
                            break
                    number += 1
        return comp

    def path(self, node):
        """[node ids] from `node` to its nearest bad node (itself when bad)."""
        out = [node]
        while self.hop[out[-1]] is not None and self.good[out[-1]]:
            out.append(self.hop[out[-1]])
        return out

    def functions(self):
        """Bound code items with a retail address in .text."""
        return [item for item in self.items if item.bound and item.code and item.home is not None
                and self.text[0] <= item.home < self.text[1]]

    def run(self):
        self.select()
        self.anchor()
        self.verify()
        self._code_literals()
        self.closure()
        return self


def _hexes(addresses):
    return "/".join(f"0x{a:08X}" for a in sorted(addresses)[:3])


# ------------------------------------------------------------------ results


def describe(image, node_id):
    node = image.nodes[node_id]
    if isinstance(node, Leaf):
        return {"name": node.name, "object": "", "kind": node.kind, "verdict": "good" if node.good else "bad",
                "reason": node.reason, "home": ""}
    return {"name": node.label(), "object": node.obj.name, "kind": "code" if node.code else node.sec.name,
            "verdict": node.verdict, "reason": node.reason,
            "home": f"0x{node.home:08X}" if node.home is not None else "", "lane": node.lane or "",
            "derived": node.derived}


def results(image, linked=None):
    """(summary, queue rows, path rows, item rows) from a run image."""
    functions = image.functions()
    size = {item.id: image.text_bytes(item) for item in functions}
    counted = [item for item in functions if item.lane in DECOMPILED
               and (image.row_homes is None or item.home in image.row_homes)]
    verdicts = collections.Counter(item.verdict for item in image.items)
    bound_verdicts = collections.Counter(item.verdict for item in image.items if item.bound)

    def intervals(items):
        spans = sorted((max(i.home, image.text[0]), min(i.home + i.size, image.text[1])) for i in items)
        total, last = 0, None
        for low, high in spans:  # merged: two items on one address count once
            if last is not None and low < last:
                low = last
            if low < high:
                chunk = image.read(low, high - low) or b""
                total += len(chunk) - chunk.count(0xCC)
                last = high
        return total

    true_items = [i for i in counted if i.retail_verdict == "retail"]
    movable = [i for i in counted if i.verdict == "retail"]
    closed = [i for i in true_items if image.badset_retail[i.id] == frozenset()]
    strict = [i for i in movable if image.badset[i.id] == frozenset()]
    direct = [i for i in strict if image.badset_direct[i.id] == frozenset()]
    summary = {
        "items": len(image.items), "bound_items": sum(1 for i in image.items if i.bound),
        "leaves": len(image.leaves), "edges": sum(len(i.edges) for i in image.items),
        "verdicts_all": dict(verdicts), "verdicts_bound": dict(bound_verdicts),
        "derived_items": sum(1 for i in image.items if i.derived),
        "weak_fallbacks": len(image.weak_fallbacks),
        "unproven_in_image_data_dwords": image.numbers,
        "proven_scalar_data_dwords": image.proven_scalars,
        "data_items_with_unproven_dwords": sum(1 for i in image.items if i.literals),
        "leaf_kinds": dict(collections.Counter(leaf.kind for leaf in image.leaves.values())),
        "functions": len(functions),
        "function_verdicts_retail_placement": dict(collections.Counter(i.retail_verdict for i in functions)),
        "function_verdicts": dict(collections.Counter(i.verdict for i in functions)),
        "decompiled_functions": len(counted),
        "decompiled_bytes": intervals(counted),
        "retail_true_functions": len(true_items), "retail_true_bytes": intervals(true_items),
        "movable_functions": len(movable), "movable_bytes": intervals(movable),
        "closed_functions": len(closed), "closed_bytes": intervals(closed),
        "closed_strict_functions": len(strict), "closed_strict_bytes": intervals(strict),
        "closed_strict_direct_functions": len(direct), "closed_strict_direct_bytes": intervals(direct),
        "functions_with_indirect_transfers": sum(1 for i in functions if i.indirect),
        "decoded_edges": sum(1 for i in image.items for e in i.edges if e[1] == DECODED),
        "crossing_edges": len(image.crossing),
    }
    by_lane = collections.defaultdict(list)
    for item in functions:
        if item.retail_verdict == "retail":
            by_lane[item.lane or "?"].append(item)
    summary["lane_bytes_retail_true"] = {lane: intervals(items) for lane, items in sorted(by_lane.items())}
    if linked:
        summary["census_linked"] = linked
    unlock, unlock_n, first, first_n, example = (collections.Counter(), collections.Counter(), collections.Counter(),
                                                 collections.Counter(), {})
    path_rows = []
    for item in counted:
        bad = image.badset[item.id]
        if bad == frozenset():
            continue
        steps = image.path(item.id)
        end = steps[-1]
        first[end] += size[item.id]
        first_n[end] += 1
        if bad is not None and len(bad) == 1:
            (only,) = bad
            unlock[only] += size[item.id]
            unlock_n[only] += 1
            if size[item.id] > example.get(only, (0, None))[0]:
                example[only] = (size[item.id], item.id)
        example.setdefault(end, (0, item.id))
        path_rows.append({"function": item.label(), "object": item.obj.name, "home": f"0x{item.home:08X}",
                          "bytes": size[item.id], "verdict": item.verdict,
                          "bad_nodes": "many" if bad is None else len(bad),
                          "first_bad": image.nodes[end].label(), "path": " -> ".join(
                              image.nodes[n].label() for n in steps)})
    queue = []
    for node in set(unlock) | set(first):
        info = describe(image, node)
        queue.append({**{k: info[k] for k in ("name", "object", "kind", "verdict", "home", "reason")},
                      "unlock_bytes": unlock[node], "unlock_functions": unlock_n[node],
                      "first_bad_bytes": first[node], "first_bad_functions": first_n[node],
                      "example": " -> ".join(image.nodes[n].label() for n in image.path(example[node][1]))})
    queue.sort(key=lambda r: (-r["unlock_bytes"], -r["first_bad_bytes"], r["name"]))
    summary["queue_nodes"] = len(queue)
    summary["unlockable_bytes"] = sum(unlock.values())
    item_rows = []
    for item in image.items:
        item_rows.append({"id": item.id, "name": item.label(), "object": item.obj.name, "section": item.sec.name,
                          "offset": item.start, "size": item.size,
                          "home": f"0x{item.home:08X}" if item.home is not None else "",
                          "derived": "yes" if item.derived else "", "retail_verdict": item.retail_verdict,
                          "verdict": item.verdict, "lane": item.lane or "",
                          "closed": "" if not item.bound else "yes" if image.badset_retail[item.id] == frozenset()
                          else "no",
                          "closed_strict": "" if not item.bound else "yes" if image.badset[item.id] == frozenset()
                          else "no", "indirect": item.indirect, "data_literals": item.literals,
                          "reason": item.reason})
    return summary, queue, path_rows, item_rows


def compact(image):
    """What --path and --queue need, without the COFF bodies."""
    nodes = []
    for node in image.nodes:
        if isinstance(node, Leaf):
            nodes.append(("leaf", node.name, node.kind, node.good, node.reason, None, None, None, (), None))
        else:
            nodes.append(("item", node.label(), node.obj.name, node.verdict == "retail", node.reason, node.verdict,
                          node.home, node.lane, tuple(n for n, _, _ in node.names), node.retail_verdict))
    edges = {}
    for item in image.items:
        if item.edges:
            edges[item.id] = [(w - item.start, t.id, flag) for w, _, t, _, flag in item.edges]
    return {"nodes": nodes, "hop": image.hop, "badset": image.badset, "badset_retail": image.badset_retail,
            "edges": edges}


# ------------------------------------------------------------------ the census tree


def load_tree(tree):
    """Import the census tree's own tools (its ledger, objects and retail
    truth), and return the modules."""
    sys.path.insert(0, str(tree / "tools"))
    for name in ("build", "link_census", "progress"):
        sys.modules.pop(name, None)
    import build
    import link_census
    import progress
    if build.ROOT.resolve() != tree.resolve():
        raise SystemExit(f"image_check: imported build.py from {build.ROOT}, not {tree}")
    return build, link_census, progress


def retail_reader(build):
    """read(rva, size) over retail's virtual image (.bss zero-filled),
    (.text start, end) and SizeOfImage."""
    import pefile
    data = build.EXE.read_bytes()
    pe = pefile.PE(data=data, fast_load=True)
    size = pe.OPTIONAL_HEADER.SizeOfImage
    image = bytearray(size)
    text = None
    for section in pe.sections:
        raw = data[section.PointerToRawData:section.PointerToRawData + min(section.SizeOfRawData,
                                                                          section.Misc_VirtualSize or 1 << 30)]
        image[section.VirtualAddress:section.VirtualAddress + len(raw)] = raw
        if section.Name.rstrip(b"\0") == b".text":
            text = (section.VirtualAddress, section.VirtualAddress + section.Misc_VirtualSize)
    image = bytes(image)

    def read(rva, length):
        if rva < 0 or rva + length > size:
            return None
        return image[rva:rva + length]
    return read, text, size


def census_row(census_tree):
    """The last row of the census tree's link_census_history.csv."""
    with (census_tree / "targets/game/reverse/link_census_history.csv").open(newline="", encoding="utf-8") as handle:
        history = list(csv.DictReader(handle))
    if not history:
        raise SystemExit("image_check: no census in link_census_history.csv")
    return history[-1]


def census_guard(tree, census_tree):
    """Refuse a ledger checkout that is not the census's commit. The census
    worktree commits its history row and rebases after linking, so its own
    HEAD is usually a later commit: then `--tree` names a checkout of the
    census commit, and objects and artefacts still come from `--census`."""
    row = census_row(census_tree)
    changed = subprocess.run(["git", "diff", "--quiet", row["commit"], "--", "game",
                              "targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv",
                              "targets/game/reverse/dir32_addresses.csv"], cwd=tree).returncode
    if changed:
        raise SystemExit(f"image_check: {tree} differs from the census commit {row['commit']}; check that commit "
                         f"out (git worktree add --detach build/wt_census {row['commit']}) and pass it as --tree")
    census = census_tree / "build" / "link_census"
    for name in ("objects.rsp", "selected.map", "census.log"):
        if not (census / name).exists():
            raise SystemExit(f"image_check: {census / name} is missing (run link_census.py --selected)")
    return row


def read_scalars(path):
    """{(va, value)} from a proven-scalar CSV; None without one."""
    if path is None:
        return None
    with path.open(newline="", encoding="utf-8") as handle:
        return {(int(row["va"], 16), int(row["value"], 16)) for row in csv.DictReader(handle)}


def load(tree, census_tree, scalars_path=None):
    build, link_census, progress = load_tree(tree)
    history = census_guard(tree, census_tree)
    commit = history["commit"]
    census = census_tree / "build" / "link_census"
    started = time.time()
    rows = link_census.ledger()
    paths = [census_tree / line.strip().strip('"') for line in (census / "objects.rsp").read_text().splitlines()
             if line.strip()]
    map_time = (census / "selected.map").stat().st_mtime
    newer = [p.name for p in paths if p.stat().st_mtime > map_time]
    if newer:
        raise SystemExit(f"image_check: {len(newer)} objects were rebuilt after selected.map, e.g. {newer[0]}; "
                         "rerun link_census.py --selected")
    wanted = {build.row_object(row).name for row in rows}
    names = {p.name for p in paths}
    if wanted - names:
        raise SystemExit(f"image_check: {len(wanted - names)} ledger objects are not in objects.rsp")
    objs = [parse_object(p.name, p.read_bytes(), i) for i, p in enumerate(paths)]
    print(f"image_check: parsed {len(objs):,} objects ({time.time() - started:.0f}s)", flush=True)
    map_text = (census / "selected.map").read_text(encoding="latin-1")
    kept = link_census.selected_definitions(map_text)
    map_commons = {line.split()[1] for line in map_text.splitlines() if line.rstrip().endswith("<common>")}
    truth = link_census.RetailTruth(rows)
    statics = collections.defaultdict(set)
    lanes = collections.defaultdict(dict)
    matched, notes = progress.matched_at(None), progress.notes_at(None)
    naked = set(progress.naked_cpp_rows_at(matched, None))
    for row in rows:
        obj = build.row_object(row).name
        address = int(row["target_rva"], 16)
        key = (row["name"], row["target_rva"])
        lane = progress.source_lane(row["source"], notes.get(key, row.get("notes") or ""), key in naked)
        for name in {row["name"], build.ledger_object_symbol(row)}:
            if "icf-owner=" not in (row.get("notes") or ""):
                statics[(obj, name)].add(address)
            lanes[obj].setdefault(name, lane)
        lanes[obj].setdefault(None, lane)
    crt = build.vc71_root() / "Vc7" / "lib" / "msvcrt.lib"
    runtime, imported, stubs = (link_census.library_symbols(crt), link_census.retail_imports(),
                                link_census.import_stubs())

    def excused(name):
        if not link_census.excused(name, runtime, imported, stubs):
            return None
        return "import" if name.startswith("__imp_") or name in stubs else "crt"
    kinds = {}
    census_json = census / "census.json"
    if census_json.exists():
        kinds = {name: entry.get("kind", "") for name, entry in
                 json.loads(census_json.read_text(encoding="utf-8")).get("unresolved", {}).items()}
    read, text, size = retail_reader(build)
    image = Image(objs, kept, truth, statics, read, excused, lanes, text, size, kinds,
                  {int(row["target_rva"], 16) for row in rows}, read_scalars(scalars_path), map_commons)
    image.paths = {path.name: path for path in paths}  # image_compose seals the selected objects
    image.baseline = build.EXE
    linked = {"commit": commit, "date": history.get("date"), "linked_bytes": int(history.get("linked_bytes") or 0),
              "linked_authored": int(history.get("linked_authored") or 0)}
    return image, linked


def census_lock(tree):
    """mkdir <tree>.census-lock, as daily_census.sh does; None when held."""
    lock = Path(str(tree.resolve()) + ".census-lock")
    try:
        lock.mkdir()
    except FileExistsError:
        return None
    return lock


def write_csv(path, rows, fields=None):
    fields = fields or (list(rows[0]) if rows else ["empty"])
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fields, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def print_summary(summary):
    linked = summary.get("census_linked", {})
    print(f"image_check: {summary['items']:,} items ({summary['bound_items']:,} bound), {summary['edges']:,} "
          f"relocation edges, {summary['leaves']:,} leaves {summary['leaf_kinds']}")
    print(f"  bound item verdicts: {summary['verdicts_bound']}; placed by propagation: {summary['derived_items']:,}; "
          f"weak-external fallbacks: {summary['weak_fallbacks']:,}; decoded in-section transfers: "
          f"{summary['decoded_edges']:,}; addends crossing into another item: {summary['crossing_edges']:,}; "
          f"unrelocated in-image data dwords (unproven, per item in items.csv): "
          f"{summary['unproven_in_image_data_dwords']:,} in {summary['data_items_with_unproven_dwords']:,} items")
    print(f"  functions with a retail .text address: {summary['functions']:,}; at retail's placement "
          f"{summary['function_verdicts_retail_placement']}, movable {summary['function_verdicts']}")
    print(f"  authored + vendored bytes: {summary['decompiled_bytes']:,} in {summary['decompiled_functions']:,} "
          f"functions")
    print(f"    retail-true   {summary['retail_true_bytes']:>10,} ({summary['retail_true_functions']:,} functions, "
          "at retail's placement)")
    print(f"    movable       {summary['movable_bytes']:>10,} ({summary['movable_functions']:,}; retail-true and no "
          "unrelocated image address or outward branch)")
    print(f"    closed        {summary['closed_bytes']:>10,} ({summary['closed_functions']:,}; everything reached is "
          "retail-true at retail's placement)")
    print(f"    closed strict {summary['closed_strict_bytes']:>10,} ({summary['closed_strict_functions']:,}; "
          "everything reached is retail-true and movable: the acceptance)")
    print(f"      no indirect {summary['closed_strict_direct_bytes']:>10,} "
          f"({summary['closed_strict_direct_functions']:,}; and nothing reached calls or jumps through a register "
          "or data: virtual calls are an unproven boundary)")
    if linked:
        print(f"    census LINKED {linked.get('linked_bytes', 0):>10,} (per file, {linked.get('commit')} "
              f"{linked.get('date')})")
    print(f"  bad nodes on some function's path: {summary['queue_nodes']:,}; bytes a single repair would close: "
          f"{summary['unlockable_bytes']:,}")


def print_queue(queue, limit):
    print(f"  {'unlock':>8} {'fns':>4} {'first':>8} {'fns':>4}  verdict  kind        name (object): reason")
    for row in queue[:limit]:
        print(f"  {row['unlock_bytes']:>8,} {row['unlock_functions']:>4} {row['first_bad_bytes']:>8,} "
              f"{row['first_bad_functions']:>4}  {row['verdict'][:7]:<7}  {row['kind'][:10]:<10}  {row['name']}"
              f"{' (' + row['object'] + ')' if row['object'] else ''}: {row['reason']}")


def print_path(graph, symbol):
    nodes = graph["nodes"]
    found = [i for i, n in enumerate(nodes) if n[0] == "item" and (n[1] == symbol or symbol in n[8])]
    if not found:
        found = [i for i, n in enumerate(nodes) if n[0] == "item" and symbol in n[1]][:10]
        if not found:
            print(f"image_check: no selected item named {symbol}")
            return 1
    for node in found:
        kind, label, obj, good, reason, verdict, home, lane, _, retail_verdict = nodes[node]
        bad = graph["badset"][node]
        state = "CLOSED STRICT" if bad == frozenset() else "not closed strict"
        at_retail = "closed" if graph["badset_retail"][node] == frozenset() else "not closed"
        print(f"{label} ({obj}) at {'0x%08X' % home if home is not None else 'no address'}: {verdict}, {state} "
              f"(at retail's placement {retail_verdict}, {at_retail}){'; ' + reason if reason else ''}")
        if bad == frozenset():
            continue
        print(f"  bad nodes reached: {'more than two' if bad is None else len(bad)}")
        step = node
        while True:
            entry = nodes[step]
            desc = (f"{entry[1]} [{entry[2]}{' ' + entry[4] if entry[4] else ''}]" if entry[0] == "leaf" else
                    f"{entry[1]} ({entry[2]}) {entry[5]}{': ' + entry[4] if entry[4] else ''}")
            print(f"    {desc}")
            nxt = graph["hop"][step]
            if nxt is None or not entry[3]:
                break
            via = next((f"+0x{off:X}{' ' + flag if flag else ''}" for off, t, flag in graph["edges"].get(step, ())
                        if t == nxt), "")
            print(f"      -> via {via}")
            step = nxt
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--tree", type=Path, default=ROOT,
                    help="checkout of the census commit: ledger, pins and tools (default: this one)")
    ap.add_argument("--scalars", type=Path,
                    help="CSV (va,value,...) of data words typed evidence proves scalar (workstream B's "
                         "build/reloc_ledger/proven_scalars.csv)")
    ap.add_argument("--census", type=Path,
                    help="checkout holding the census's build/link_census artefacts and objects (default: --tree)")
    ap.add_argument("--path", metavar="SYMBOL", help="why a function is not closed (from the last run's graph)")
    ap.add_argument("--queue", action="store_true", help="bad nodes ranked by the closed bytes they would unlock")
    ap.add_argument("--limit", type=int, default=30)
    args = ap.parse_args(argv)
    graph_path = OUT / "graph.pkl"
    if args.path or (args.queue and graph_path.exists()):
        if args.queue:
            with (OUT / "queue.csv").open(newline="", encoding="utf-8") as handle:
                rows = list(csv.DictReader(handle))
            for row in rows:
                for key in ("unlock_bytes", "unlock_functions", "first_bad_bytes", "first_bad_functions"):
                    row[key] = int(row[key])
            print_summary(json.loads((OUT / "summary.json").read_text(encoding="utf-8")))
            print_queue(rows, args.limit)
        if args.path:
            if not graph_path.exists():
                raise SystemExit("image_check: no graph yet; run the full check first")
            with graph_path.open("rb") as handle:
                return print_path(pickle.load(handle), args.path)
        return 0
    census_tree = (args.census or args.tree).resolve()
    tree = args.tree.resolve()
    lock = census_lock(census_tree) if census_tree != ROOT.resolve() else None
    if census_tree != ROOT.resolve() and lock is None:
        raise SystemExit(f"image_check: {census_tree}.census-lock is held (a census is running); try later")
    try:
        started = time.time()
        image, linked = load(tree, census_tree, args.scalars)
        image.run()
        print(f"image_check: verified and closed ({time.time() - started:.0f}s)", flush=True)
    finally:
        if lock is not None:
            lock.rmdir()
    summary, queue, paths, items = results(image, linked)
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / "summary.json").write_text(json.dumps(summary, indent=1), encoding="utf-8")
    write_csv(OUT / "queue.csv", queue, ["name", "object", "kind", "verdict", "home", "reason", "unlock_bytes",
                                         "unlock_functions", "first_bad_bytes", "first_bad_functions", "example"])
    write_csv(OUT / "paths.csv", sorted(paths, key=lambda r: -r["bytes"]))
    write_csv(OUT / "items.csv", items)
    with (OUT / "graph.pkl").open("wb") as handle:
        pickle.dump(compact(image), handle, protocol=pickle.HIGHEST_PROTOCOL)
    print_summary(summary)
    print_queue(queue, args.limit)
    return 0


if __name__ == "__main__":
    sys.exit(main())
