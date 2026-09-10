#!/usr/bin/env python3
"""Claim retail bodies a source we already hold has ALREADY compiled.

Every ledger `.cpp`/`.c` leaves a COMDAT per function in its object. Retail
folded identical COMDATs (`/OPT:ICF`), so one compiled span frequently *is* the
bytes at several addresses — addresses that today carry only a `Code/gen_asm/`
dump or no row at all. Those bodies need no new source: one more row on the TU
that already compiles them, with an `object-symbol=` note, is the whole claim.

What this sweeps, and the three classes it sweeps in
---------------------------------------------------
`build.py:compile_function` copies every DIR32 site straight out of retail and
re-encodes every REL32 from `symbol_map`. So a span verifies at a second address
without resolving a single callee **iff** it carries no REL32: a reloc-free span
compares byte for byte, and a DIR32-only span compares byte for byte outside the
4-byte pointer sites the gate would have copied anyway.

A REL32 site cannot be aliased by COPYING — its displacement is measured from
the address it sits at — but it does not have to be: the gate re-encodes it from
scratch at whatever address the row names. It seeds from `symbol_map[sym][0]`
and stops at the first candidate whose displacement reproduces retail, so at an
alias address it writes retail's own four bytes exactly when the callee retail's
displacement points at, `rva + off + 4 + disp`, is one of that symbol's
candidates — and writes the last candidate's displacement, silently wrong, when
it is not. `rel32` is the class where every site passes that test: the alias
calls the same functions the compiled span calls, the ledger already holds each
of them, and only the displacement differs. Deriving the implied callee here is
that arithmetic run forwards, so a span is only ever offered at an address where
the gate is already going to agree with retail.

Circularity — the one thing that makes this measurement worthless
-----------------------------------------------------------------
A `__declspec(naked)` `__emit` body compiles to retail's bytes BY CONSTRUCTION.
Matching such a span against the dump row it was lifted from proves nothing: it
is the dump recognising itself. The spike that produced this tool reported
928,349 B before those spans were excluded and 138,979 B after — a 6.7x
inflation. Three exclusions kill it, and `--assert-circularity` re-runs the
sweep with them off so the ratio is a printed number rather than a claim:

  1. `(source, symbol)` is itself a naked ledger row (by ledger name AND by its
     `object-symbol=` alias);
  2. `?d_<rva>@...` — the synthetic name a byte-dump row carries;
  3. the span's bytes sit inside a naked body's emitted mass in that source,
     which catches naked bodies that carry no ledger row at all. Reloc-free
     spans only — an `__emit` blob is literal constants, so a span carrying a
     relocation is not a body it could have produced.

Targets
  dump  a not-held ledger row at exactly (rva, size). Only a lone gen-dump row
        is landable: `gen_small.validate_rows` supersedes that and nothing else,
        and any other row or extent at the address is a boundary dispute that
        would abort a whole wave. Dumpness is the note, not the directory.
  uncl  a ghidra start overlapping no matched row; the span has to fit inside
        the unclaimed gap that follows it.

Subcommands
  report                     classify at HEAD and print the byte accounting
  wave --class rf|dir32|rel32
                             write a wave CSV for tools/land_wave.py
  extend                     the reverse direction: held rows whose object
                             symbol is LONGER than target_size and whose retail
                             tail matches, i.e. rows trimmed short at claim time
"""
import argparse
import bisect
import collections
import csv
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import gen_small as G
import locate
import progress

ROOT = B.ROOT
HELD_LANES = ("authored", "vendored", "generated", "library")
DIR32, REL32 = 0x0006, 0x0014
IMAGE_BASE = 0x400000
# A DIR32-only span whose unmasked remainder is this short is not evidence: the
# gate would copy most of it out of retail and "verify" a handful of bytes.
MIN_CONCRETE = 8
# The synthetic name every byte-dump row carries.
DUMP_NAME_RE = re.compile(r"\?d_[0-9a-fA-F]{6,8}@")
# MSVC hashes the absolute source path into anonymous-namespace symbols.
A0X_RE = re.compile(r"\?A0x[0-9A-Fa-f]{8}")
ALIAS_NOTE_PREFIX = "gen-alias;"
ALIAS_NOTE = "C++ alias"
OWNER_PREF = {"code": 0, "vendor": 1, "reference": 2, "gen_small": 3}
CLASSES = ("rf", "dir32", "rel32")
CLASS_RANK = {cls: i for i, cls in enumerate(CLASSES)}
Owner = collections.namedtuple("Owner", "source symbol cls holes sites")


# --------------------------------------------------------------------------
# retail image and the ledger universe
# --------------------------------------------------------------------------

class Image:
    def __init__(self):
        self.data = B.EXE.read_bytes()
        self.sections = B.pe_sections(self.data)

    def body(self, rva, size):
        offset = B.rva_to_file_offset(self.sections, rva)
        out = self.data[offset:offset + size]
        if len(out) != size:
            raise SystemExit(f"obj_sweep: 0x{rva:08X}+{size} runs past the end of "
                             f"{B.EXE.name} — the image and the ledger disagree")
        return out


class Universe:
    """Everything derived from the ledger AT HEAD. Never read back from a CSV."""

    def __init__(self):
        matched = progress.matched_at(None)
        notes = progress.notes_at(None)
        naked = progress.naked_cpp_rows_at(matched, None)
        self.text_start, text_size = progress.retail_text()
        self.text_end = self.text_start + text_size

        lanes = collections.defaultdict(set)
        self.rows = collections.defaultdict(list)
        self.sources = set()
        self.naked_symbols = set()
        for key, (size, source) in matched.items():
            if source.lower().endswith((".cpp", ".c", ".cc")):
                self.sources.add(source)
            rva = int(key[1], 16)
            if rva < self.text_start or rva + size > self.text_end:
                continue
            lane = progress.source_lane(source, notes[key], key in naked)
            lanes[(rva, size)].add(lane)
            self.rows[(rva, size)].append({"name": key[0], "rva": rva, "size": size,
                                           "source": source, "notes": notes[key], "lane": lane})
            if key in naked:
                self.naked_symbols.add((source, key[0]))
                self.naked_symbols.add((source, B.ledger_object_symbol(
                    {"name": key[0], "notes": notes[key]})))

        self.held, self.dump = set(), set()
        for key, key_lanes in lanes.items():
            (self.held if self.best_lane(key_lanes) in HELD_LANES else self.dump).add(key)
        self.held_rows = collections.defaultdict(list)
        for key in self.held:
            for row in self.rows[key]:
                if row["lane"] in HELD_LANES:
                    self.held_rows[row["source"]].append(row)

        intervals = sorted((rva, rva + size) for (rva, size) in lanes)
        self._starts = [start for start, _ in intervals]
        self._intervals = intervals
        self._max_end, running = [], 0
        for _, end in intervals:
            running = max(running, end)
            self._max_end.append(running)

        self.unclaimed = self._unclaimed_starts()
        self.tombstoned = self._tombstones()
        # validate_rows refuses a name or an address that ANY ledger row already
        # holds, matched or not, and one such row aborts the whole wave — so the
        # collision sets have to be the full ledger, not just its matched half.
        #
        # `placements` answers the different question of IDENTITY: a row records
        # which compiled symbol is the body at its address in the
        # `object-symbol=` note, not in its name, so a symbol already proven at
        # some address is invisible to `all_names` and its real name gets awarded
        # to a second address. 17 rows shipped that way before this counted the
        # alias spelling too.
        # all_rvas counts rather than collects: `rva in all_rvas` is the same
        # question it always answered, and the count is what tells a dump target
        # its address carries nothing BUT the dump.
        self.all_names, self.all_rvas = set(), collections.Counter()
        self.placements = collections.Counter()
        for row in B.load_all_function_rows():
            self.all_names.add(row["name"])
            self.all_rvas[int(row["target_rva"], 16)] += 1
            self.placements[B.ledger_object_symbol(row)] += 1
        # {name: {address}} — every address a REL32 site is allowed to reach.
        # build.load_symbol_map keeps its candidates as ordered lists because its
        # resolver walks them in order and reports the last one it tried;
        # membership is the only question the rel32 class asks, and one of those
        # lists runs to 9,155 entries.
        self.symbol_addresses = {name: set(addresses)
                                 for name, addresses in B.load_symbol_map().items()}

    @staticmethod
    def best_lane(lanes):
        for lane in progress.SOURCE_LANES:
            if lane in lanes:
                return lane
        raise SystemExit(f"obj_sweep: no known provenance lane in {sorted(lanes)}")

    def overlaps_matched(self, rva, size):
        i = bisect.bisect_right(self._starts, rva + size - 1) - 1
        while i >= 0 and self._max_end[i] > rva:
            if self._intervals[i][1] > rva and self._intervals[i][0] < rva + size:
                return True
            i -= 1
        return False

    def gap_end(self, rva):
        """First matched byte at or after `rva` — how far an unclaimed span may run."""
        i = bisect.bisect_right(self._starts, rva)
        return min(self._intervals[i][0] if i < len(self._intervals) else self.text_end,
                   self.text_end)

    def _unclaimed_starts(self):
        path = ROOT / "reverse" / "ghidra_functions.csv"
        if not path.exists():
            raise SystemExit(f"obj_sweep: {path} is missing — the unclaimed lane cannot be "
                             "measured without the ghidra inventory")
        out = {}
        with path.open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                rva, size = int(row["rva"], 16), int(row["size"])
                if rva < self.text_start or rva + size > self.text_end or size < 3:
                    continue
                if rva in out or self.overlaps_matched(rva, size):
                    continue
                out[rva] = self.gap_end(rva)
        return out

    @staticmethod
    def _tombstones():
        """Names deleted on purpose. Reusing one puts a dead row straight back."""
        path = ROOT / "reverse" / "deleted_rows.csv"
        if not path.exists():
            raise SystemExit(f"obj_sweep: {path} is missing — a wave cannot tell which names "
                             "were retracted on purpose")
        out = set()
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            if not line.strip() or line.startswith("#") or line.startswith("name,"):
                continue
            fields = next(csv.reader([line]))
            if fields and fields[0]:
                out.add(fields[0])
        return out


# --------------------------------------------------------------------------
# objects
# --------------------------------------------------------------------------

def source_objects(uni, stats):
    """{source: obj path} for every ledger source whose obj the gate would reuse.

    A stale obj is dropped, not used: the gate recompiles from the source on
    disk, so a candidate derived from an older object would be proved against
    bytes this repository no longer produces and would take its whole TU's wave
    down with it.

    "Stale" has to be `compile_is_current` — source, compile command and every
    recorded header byte-identical — and not an mtime comparison, because those
    two disagree in exactly the case this tool is run in. build.py:_portable
    exists so a fresh worktree can be seeded from the main clone's warm cache;
    every obj in it is then OLDER than the checkout that just wrote the sources,
    and mtime throws away thousands of objects the gate has already proved
    current. It read 88 of 4,712 sources that way.
    """
    out = {}
    for source in sorted(uni.sources):
        path = ROOT / source
        if not path.exists():
            stats["source_missing"] += 1
            continue
        obj = B.obj_path(path)
        if not obj.exists():
            stats["obj_missing"] += 1
            continue
        if not B.compile_is_current(path, obj):
            stats["obj_stale"] += 1
            continue
        out[source] = obj
    return out


def owner_class(source):
    if source.startswith("Code/gen_small/"):
        return "gen_small"
    if source.startswith("reference/"):
        return "reference"
    if source.startswith("vendor/"):
        return "vendor"
    return "code"


def masked_equal(span, target, holes):
    if len(span) != len(target):
        return False
    left, right = bytearray(span), bytearray(target)
    for offset in holes:
        left[offset:offset + 4] = right[offset:offset + 4] = b"\0\0\0\0"
    return left == right


# A TU-local label or per-TU EH stub legitimately sits at many addresses; the
# full gate's own dir32 check skips exactly these, so this one must too.
LOCAL_SYMBOL_RE = re.compile(r"\$[A-Za-z]+\d+\Z")


def dir32_sites(body, relocs, image, rva, size):
    """[(symbol, implied base)] for the non-local DIR32 sites of a claim.

    `verify_dir32_consistency` derives base = retail_dword - compiled_addend and
    fails the FULL gate when one symbol resolves to two. A scoped gate never
    runs it, so a masked-DIR32 alias that actually points at a DIFFERENT global
    verifies green here and blows up ten waves later, whole-tree. Deriving the
    same number up front turns that into a rejected candidate.
    """
    out = []
    for offset, rtype, symbol in relocs:
        if rtype != DIR32 or offset + 4 > size or offset + 4 > len(body):
            continue
        if symbol.startswith("??_C@") or symbol.startswith("__ehhandler$"):
            continue
        if LOCAL_SYMBOL_RE.fullmatch(symbol):
            continue
        final = int.from_bytes(image.body(rva + offset, 4), "little")
        addend = int.from_bytes(body[offset:offset + 4], "little")
        out.append((symbol, (final - addend) & 0xFFFFFFFF))
    return out


def string_refs_agree(obj, body, relocs, image, rva, size):
    """True when every `??_C@` site points at the literal the object holds.

    `dir32_sites` exempts string constants from the base-agreement rule on
    purpose — a pooled literal legitimately sits at a different address in every
    TU — so at those sites the masked comparison is the only thing standing
    between a body and the look-alike whose single difference is which string it
    loads. `build.py:verify_string_refs` is what catches that, and it runs AFTER
    the byte comparison: ten such rows passed `Functions: OK 1227/1227` and then
    took the whole wave down at the next stage, naming no source the lander
    could route around. This is that check asked at candidate time instead.
    """
    for offset, rtype, symbol in relocs:
        if rtype != DIR32 or offset + 4 > size or not symbol.startswith("??_C@"):
            continue
        pointer = int.from_bytes(image.body(rva + offset, 4), "little")
        try:
            literal, _ = B.read_object_symbol_bytes(obj, symbol)
            start = B.rva_to_file_offset(image.sections, pointer - IMAGE_BASE)
        except ValueError:
            return False
        content = literal.rstrip(b"\0")
        # A pooled literal is referenced as symbol+addend ("DBGHELP.DLL"+4 is
        # "ELP.DLL"), and the binary holds that tail at the address written here.
        addend = int.from_bytes(body[offset:offset + 4], "little", signed=True)
        if 0 < addend <= len(content):
            content = content[addend:]
        if not content:
            if image.data[start:start + 1] != b"\0":
                return False
        elif image.data[start:start + len(content)] != content:
            return False
    return True


def classify(body, inside, stats):
    """(class, mask offsets) for one compiled span, or None if it is not aliasable."""
    if not inside:
        return "rf", []
    types = {t for _, t, _ in inside}
    if types <= {DIR32}:
        cls = "dir32"
    elif types <= {DIR32, REL32}:
        if any(offset + 4 > len(body) for offset, rtype, _ in inside if rtype == REL32):
            # compile_function raises SystemExit on a REL32 site running past the
            # row's end — the whole gate dead, not one failed row — and it is
            # right to: a call displacement cannot end after the body does, so
            # what is wrong there is the boundary. Never offer such a span.
            stats["skip_rel32_straddles_end"] += 1
            return None
        cls = "rel32"
    else:
        stats["skip_other_reloc"] += 1
        return None
    holes = sorted(offset for offset, _, _ in inside)
    if len(body) - min(4 * len(holes), len(body)) < MIN_CONCRETE:
        stats[f"skip_{cls}_thin"] += 1
        return None
    return cls, holes


def rel32_callees(body, relocs, image, rva, symbol_map, stats):
    """[(symbol, callee)] for the REL32 sites of a claim at `rva`, or None.

    None means one site's callee is not one the gate could encode here, and that
    is the whole difference between this class and a masked guess: the four bytes
    are not compared, they are re-derived, and `rva + off + 4 + disp` is the only
    address at which re-deriving them reproduces retail.
    """
    out = []
    for offset, rtype, symbol in relocs:
        if rtype != REL32:
            continue
        candidates = symbol_map.get(symbol)
        if not candidates:
            stats["skip_rel32_callee_unplaced"] += 1
            return None
        displacement = int.from_bytes(image.body(rva + offset, 4), "little", signed=True)
        callee = (rva + offset + 4 + displacement) & 0xFFFFFFFF
        if callee not in candidates:
            stats["skip_rel32_callee_elsewhere"] += 1
            return None
        out.append((symbol, callee))
    return out


class NakedBytes:
    """Is this span the emitted mass of a naked body in its own source?

    The (source, symbol) exclusion misses a naked body that carries no ledger
    row at all, and those are the ones that inflate the measurement worst.

    Only reloc-free spans are asked, and that is the complete case, not a
    narrowing: `__emit` takes literal constants, so the mass a blob contains
    carries no relocation. A span holding even one DIR32 has four bytes the
    emitted mass cannot have produced, so `span in blob` could not match it
    anyway.
    """

    def __init__(self):
        self._cache = {}

    def blobs(self, source):
        if source not in self._cache:
            path = ROOT / source
            bodies = progress.scan_naked_bodies(path.read_text(errors="replace"))
            self._cache[source] = [b["emitted"] for b in bodies if b["emitted"]]
        return self._cache[source]

    def __call__(self, source, span):
        return any(len(blob) >= len(span) and span in blob for blob in self.blobs(source))


# --------------------------------------------------------------------------
# the sweep
# --------------------------------------------------------------------------

def sweep(uni, image, objects, exclude_circular=True, stats=None):
    """{(kind, rva, size): record} — every dump/unclaimed target a held TU emits.

    `exclude_circular=False` exists for --assert-circularity only: it is the
    measurement this tool is wrong by if the naked exclusions ever stop firing.
    """
    stats = collections.Counter() if stats is None else stats
    is_naked_bytes = NakedBytes()

    # Target indexes. A span is looked up by its first 8 bytes; a span with a
    # relocation inside those 8 has to be looked up by length instead.
    by_prefix = collections.defaultdict(list)
    by_size = collections.defaultdict(list)
    small = collections.defaultdict(list)
    for rva, size in uni.dump:
        target = ("dump", rva, size)
        if size >= 8:
            by_prefix[image.body(rva, 8)].append(target)
        else:
            small[image.body(rva, size)].append(target)
        by_size[size].append(target)
    for rva, end in uni.unclaimed.items():
        if end - rva >= 8:
            by_prefix[image.body(rva, 8)].append(("uncl", rva, end))

    matches = {}
    known_base = collections.defaultdict(set)
    for source, obj in objects.items():
        try:
            spans = list(locate.object_functions(obj))
        except Exception as exc:
            raise SystemExit(f"obj_sweep: cannot parse {obj} for {source}: {exc}")
        by_symbol = {}
        for name, span, relocs in spans:
            by_symbol.setdefault(name, (span, relocs))
        for row in uni.held_rows.get(source, ()):
            entry = by_symbol.get(B.ledger_object_symbol(row))
            if entry is None:
                continue
            for symbol, base in dir32_sites(entry[0], entry[1], image,
                                            row["rva"], row["size"]):
                known_base[symbol].add(base)
        for name, span, relocs in spans:
            if exclude_circular and ((source, name) in uni.naked_symbols
                                     or DUMP_NAME_RE.match(name)):
                stats["skip_naked_symbol"] += 1
                continue
            body = span.rstrip(b"\xcc")
            if not body:
                continue
            stats["spans"] += 1
            inside = [(o, t, s) for (o, t, s) in relocs if o < len(body)]
            classified = classify(body, inside, stats)
            if classified is None:
                continue
            cls, holes = classified

            if len(body) < 8:
                candidates = small.get(body, []) if cls == "rf" else []
            elif any(o < 8 for o in holes):
                candidates = by_size.get(len(body), [])
            else:
                candidates = by_prefix.get(body[:8], [])

            for target in candidates:
                kind, rva = target[0], target[1]
                if kind == "dump":
                    size = target[2]
                    if len(body) != size or not masked_equal(body, image.body(rva, size), holes):
                        continue
                else:
                    if rva + len(body) > target[2]:
                        continue
                    size = len(body)
                    if not masked_equal(body, image.body(rva, size), holes):
                        continue
                if exclude_circular and cls == "rf" and is_naked_bytes(source, body):
                    # Every target this span hits is a dump of this same span.
                    stats["skip_naked_bytes"] += 1
                    break
                if cls == "rel32" and rel32_callees(body, inside, image, rva,
                                                    uni.symbol_addresses, stats) is None:
                    continue
                if cls != "rf" and not string_refs_agree(obj, body, inside, image, rva, size):
                    stats["skip_string_ref_elsewhere"] += 1
                    continue
                record = matches.setdefault((kind, rva, size), {"owners": []})
                sites = dir32_sites(body, inside, image, rva, size) if cls != "rf" else []
                record["owners"].append(Owner(source, name, cls, len(holes), tuple(sites)))

    # A DIR32 site is a hole in the comparison: the gate copies those four bytes
    # out of retail, so a 17-byte boilerplate constructor "matches" every other
    # class's boilerplate constructor and the only byte that told them apart is
    # the one nobody looked at. So the hole has to be closed instead of masked —
    # `verify_dir32_consistency` reads it as base = retail_dword - addend, and an
    # owner is kept ONLY when every one of its sites resolves to a base the
    # ledger's held rows already prove for that symbol. The property that buys is
    # exact: this class can introduce no base the tree did not already contain,
    # so it cannot make the full gate's dir32 check say anything new. Bases below
    # the image base are refused outright — a vtable pointer is never 0 or 2, and
    # both of those turned up as "agreement" the first time this ran.
    for key in sorted(matches):
        record = matches[key]
        keep = [owner for owner in record["owners"]
                if all(base >= IMAGE_BASE and base in known_base.get(symbol, ())
                       for symbol, base in owner.sites)]
        stats["skip_dir32_unproven_base"] += len(record["owners"]) - len(keep)
        if not keep:
            del matches[key]
            continue
        keep.sort(key=lambda owner: rank(owner.cls, owner.source) + (owner.symbol,))
        record["owners"] = keep
        record["cls"], record["holes"] = keep[0].cls, keep[0].holes
    return matches, stats


def rank(cls, source):
    """Best owner first: fewest bytes the gate re-derives, real TU over stub."""
    return (CLASS_RANK[cls], OWNER_PREF[owner_class(source)], source)


def verify_no_circularity(uni, matches):
    """Every accepted owner must be non-naked. A silent regression here is a 7x lie."""
    bad = [(key, owner.source, owner.symbol)
           for key, record in matches.items()
           for owner in record["owners"]
           if (owner.source, owner.symbol) in uni.naked_symbols
           or DUMP_NAME_RE.match(owner.symbol)]
    if bad:
        key, source, symbol = bad[0]
        raise SystemExit(f"obj_sweep: {len(bad)} accepted match(es) are circular — e.g. "
                         f"{key} is owned by {symbol} in {source}, which is itself a naked "
                         "ledger row. The exclusion is broken; the totals are meaningless.")


def totals(matches):
    out = collections.Counter()
    for (kind, _rva, size), record in matches.items():
        out[(kind, record["cls"], "rows")] += 1
        out[(kind, record["cls"], "bytes")] += size
    return out


def load(quiet=False):
    uni = Universe()
    image = Image()
    stats = collections.Counter()
    objects = source_objects(uni, stats)
    if not quiet:
        print(f"obj_sweep: {len(objects)} of {len(uni.sources)} ledger C/C++ sources have a "
              f"current obj ({stats['obj_missing']} missing, {stats['obj_stale']} stale, "
              f"{stats['source_missing']} absent) — run ./build.sh to compile the rest",
              file=sys.stderr)
    return uni, image, objects, stats


# --------------------------------------------------------------------------
# report
# --------------------------------------------------------------------------

def cmd_report(args):
    uni, image, objects, stats = load()
    matches, stats = sweep(uni, image, objects, stats=stats)
    verify_no_circularity(uni, matches)
    counts = totals(matches)

    print("newly-claimable bodies (target is a dump row or unclaimed today):")
    grand = 0
    for kind in ("dump", "uncl"):
        for cls in CLASSES:
            rows, size = counts[(kind, cls, "rows")], counts[(kind, cls, "bytes")]
            grand += size
            print(f"  {kind:5s} {cls:6s} {rows:6d} rows {size:10,d} B")
    print(f"  {'TOTAL':12s} {sum(v for k, v in counts.items() if k[2] == 'rows'):6d} rows "
          f"{grand:10,d} B")
    print(f"\nspans: {dict(stats)}")

    if args.assert_circularity:
        loose, _ = sweep(uni, image, objects, exclude_circular=False)
        inflated = sum(size for (_k, _r, size) in loose)
        if inflated <= grand:
            raise SystemExit("obj_sweep: dropping the naked exclusions did NOT inflate the "
                             f"total ({inflated:,d} B vs {grand:,d} B). Either the ledger has "
                             "no naked bodies left or the exclusions never fired — the "
                             "measurement cannot be trusted either way.")
        # No ratio: `grand` is what is LEFT to claim, so it shrinks toward nothing
        # as the waves land and inflated/grand climbs without the exclusions doing
        # one thing more. Quoted as a ratio at the end of a phase this printed
        # 429.6x for a run whose real inflation was 6.7x. The excluded mass is the
        # figure that means the same thing on every run.
        print(f"\ncircularity check: with the naked exclusions OFF this sweep would report "
              f"{inflated:,d} B against {grand:,d} B still claimable — {inflated - grand:,d} B "
              f"of circular claim excluded, by {stats['skip_naked_symbol']} span(s) on ledger "
              f"identity and {stats['skip_naked_bytes']} on emitted bytes.")


# --------------------------------------------------------------------------
# wave emission
# --------------------------------------------------------------------------

def blocked(uni, key, record, args, skipped):
    """True when this match cannot be landed as a plain row; why goes to `skipped`."""
    kind, rva, size = key
    if size < args.min_size:
        skipped[f"smaller than --min-size {args.min_size}"] += 1
        return True
    here = uni.rows.get((rva, size), [])
    if kind == "dump":
        # validate_rows supersedes a lone gen-dump row of this extent, and a dump
        # is that NOTE, never a directory -- 349 of them live in
        # Code/gen_small/dumps_000.cpp. `here` is the matched rows at this exact
        # extent, so all_rvas is asked too: an unmatched row at the address is
        # invisible to the matched-range index and still aborts the whole wave.
        if (len(here) != 1 or not B.is_scaffold_row(here[0])
                or uni.all_rvas[rva] != 1):
            skipped["address does not carry a lone gen-dump row"] += 1
            return True
    elif rva in uni.all_rvas:
        # An unmatched row at this address is invisible to the matched-range
        # index but still makes validate_rows abort the entire wave.
        skipped["unclaimed address already carries a ledger row"] += 1
        return True
    return None


def wave_name(uni, record, rva, folds, taken, skipped):
    """The object's own symbol when that is an identity claim, else a `?dup_` alias.

    A span that matches ONE address is that function: unique byte-identity is
    the same evidence tools/locate.py accepts a placement on. A span that
    matches forty is the representative of an ICF class forty members wide, and
    picking one of them to name an address after is invented identity — those
    land under `?dup_<rva>` with the note still aiming the byte comparison at
    the real COFF symbol. A symbol the ledger already places goes the same way,
    and "places" has to mean BOTH spellings: its own `name` column (check_csv
    refuses one name at two addresses) and any other row's `object-symbol=`
    note, which is where a row that carries a synthetic name records the real
    compiled symbol it is the body of. Tombstoned names go the same way (a
    retracted row must not come back), as do `?A0x`-hashed anonymous-namespace
    names (the hash is this clone's source path, so the name would churn).
    """
    symbol = record["owners"][0].symbol
    if folds[symbol] > 1:
        skipped["ICF class wider than one address — landed as ?dup_<rva>"] += 1
    elif uni.placements[symbol] or symbol in taken:
        skipped["symbol already placed in the ledger — landed as ?dup_<rva>"] += 1
    elif symbol in uni.tombstoned:
        skipped["name was tombstoned — landed as ?dup_<rva>"] += 1
    elif A0X_RE.search(symbol):
        skipped["anonymous-namespace symbol — landed as ?dup_<rva>"] += 1
    else:
        return symbol
    return G.thunk_symbol("dup", rva)


def cmd_wave(args):
    uni, image, objects, stats = load()
    if args.klass != "rf" and (stats["obj_missing"] or stats["obj_stale"]):
        # Not fatal — the base rule below only ever ACCEPTS on proven agreement,
        # so an unreadable source costs candidates, never correctness. It is worth
        # saying out loud because it is the whole difference in this class's yield.
        print(f"obj_sweep: {stats['obj_missing']} ledger source(s) have no object and "
              f"{stats['obj_stale']} are older than their source; the symbol bases they "
              "prove are invisible here, so DIR32 candidates that depend on them are "
              "dropped. ./build.sh (no arguments) recovers them.", file=sys.stderr)
    matches, stats = sweep(uni, image, objects, stats=stats)
    verify_no_circularity(uni, matches)

    wanted = {"dump"} | ({"uncl"} if args.include_unclaimed else set())
    # How many retail addresses each compiled span turned out to be. Counted over
    # EVERY match, not just this class's, so the width of an ICF class does not
    # change with the filters a wave happens to run under — and over the ledger's
    # existing placements too, because a wave that lands three of a four-address
    # class leaves the fourth looking unique to the NEXT wave, which re-derives
    # folds from the not-held population alone. Splitting a wave must not erode
    # the guard that keeps an ICF representative from naming an address.
    folds = collections.Counter(record["owners"][0].symbol for record in matches.values())
    folds.update(uni.placements)
    skipped = collections.Counter()
    picked, taken, claimed = [], set(), []
    for key in sorted(matches):
        kind, rva, size = key
        record = matches[key]
        if kind not in wanted:
            skipped[f"kind {kind} not requested"] += 1
            continue
        if record["cls"] != args.klass:
            skipped[f"class {record['cls']} not requested"] += 1
            continue
        if blocked(uni, key, record, args, skipped):
            continue
        if kind == "uncl" and claimed and rva < claimed[-1]:
            # Two ghidra starts in one gap: the second span would overlap the
            # first, and check_csv refuses overlapping matched ranges.
            skipped["unclaimed span overlaps an earlier pick"] += 1
            continue
        name = wave_name(uni, record, rva, folds, taken, skipped)
        if name in taken or name in uni.all_names or name in uni.tombstoned:
            skipped["synthetic name already taken"] += 1
            continue
        taken.add(name)
        owners = []
        for owner in record["owners"]:
            entry = (owner.source,
                     f"{ALIAS_NOTE_PREFIX}object-symbol={owner.symbol};{ALIAS_NOTE}")
            if entry not in owners:
                owners.append(entry)
            if len(owners) > args.alternates:
                break
        picked.append({"name": name, "rva": rva, "size": size, "owners": owners})
        if kind == "uncl":
            claimed.append(rva + size)

    # The gate re-verifies every row of every TU a wave touches, so a wave spread
    # over 200 TUs pays 200 full-TU verifies for the same bytes. Concentrate.
    by_source = collections.defaultdict(list)
    for row in picked:
        by_source[row["owners"][0][0]].append(row)
    order = sorted(by_source, key=lambda s: (-sum(r["size"] for r in by_source[s]), s))
    if args.skip_sources:
        order = order[args.skip_sources:]
    if args.max_sources:
        order = order[:args.max_sources]
    wave = []
    for source in order:
        for row in sorted(by_source[source], key=lambda r: r["rva"]):
            if args.limit and len(wave) >= args.limit:
                break
            wave.append(row)
        if args.limit and len(wave) >= args.limit:
            break

    if not wave:
        raise SystemExit(f"obj_sweep: class {args.klass} produced no landable row under these "
                         f"filters ({len(matches)} match(es) at HEAD; skipped: "
                         + ", ".join(f"{n} {why}" for why, n in skipped.most_common()) + ")")

    columns = ["name", "rva", "size", "source", "notes"]
    for i in range(1, max(len(row["owners"]) for row in wave)):
        columns += [f"alt{i}_source", f"alt{i}_notes"]
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, columns, lineterminator="\n")
        writer.writeheader()
        for row in wave:
            record = {"name": row["name"], "rva": f"0x{row['rva']:08X}", "size": row["size"],
                      "source": row["owners"][0][0], "notes": row["owners"][0][1]}
            for i, (source, notes) in enumerate(row["owners"][1:], start=1):
                record[f"alt{i}_source"], record[f"alt{i}_notes"] = source, notes
            writer.writerow(record)
    print(f"obj_sweep: {len(wave)} row(s), {sum(r['size'] for r in wave):,d} byte(s) over "
          f"{len(order)} TU(s) -> {out}")
    print(f"  class {args.klass}: {len(picked)} landable row(s), "
          f"{sum(r['size'] for r in picked):,d} B total across {len(by_source)} TU(s)")
    for why, count in skipped.most_common():
        print(f"  skipped {count}: {why}")


# --------------------------------------------------------------------------
# row extension
# --------------------------------------------------------------------------

def cmd_extend(args):
    """Held rows the claim trimmed short: the object symbol runs past target_size.

    A jump table or the constant island after the `ret` belongs to the function
    but was not in the boundary the row was claimed with. If the object's tail
    equals retail's, masked at its own relocation sites, and no other row claims
    those bytes, the row's target_size is simply short.
    """
    uni, image, objects, _load_stats = load()
    stats = collections.Counter()
    with (ROOT / "reverse" / "ghidra_functions.csv").open(newline="", encoding="utf-8") as handle:
        ghidra_starts = {int(row["rva"], 16) for row in csv.DictReader(handle)}
    rows_by_source = collections.defaultdict(list)
    for key, rows in uni.rows.items():
        for row in rows:
            if row["lane"] in HELD_LANES and row["source"] in objects:
                rows_by_source[row["source"]].append(row)

    out_rows = []
    for source, rows in sorted(rows_by_source.items()):
        spans, normalized = {}, collections.defaultdict(list)
        for name, span, relocs in locate.object_functions(objects[source]):
            spans.setdefault(name, (span, relocs))
            normalized[A0X_RE.sub("?A0xHASH", name)].append(name)
        for row in rows:
            symbol = B.ledger_object_symbol(row)
            if re.fullmatch(r"\$L\d+", symbol):
                stats["funclet_label"] += 1
                continue
            entry = spans.get(symbol)
            if entry is None:
                # build.py:read_object_symbol_bytes resolves an anonymous-namespace
                # name the same way (the ?A0x token is this clone's source path),
                # so the gate would size the row off the same span. Counted, not
                # silent: the extended size then comes from a symbol the ledger
                # does NOT name, and a self-consistent wrong size is the one
                # failure this whole subcommand could produce.
                candidates = normalized.get(A0X_RE.sub("?A0xHASH", symbol), [])
                if len(candidates) == 1:
                    entry = spans[candidates[0]]
                    symbol = candidates[0]
                    stats["symbol_rehashed"] += 1
            if entry is None:
                stats["symbol_missing"] += 1
                continue
            span, relocs = entry
            body = span.rstrip(b"\xcc")
            stats["resolved"] += 1
            if len(body) < row["size"]:
                stats["object_shorter"] += 1
                continue
            if len(body) == row["size"]:
                stats["exact"] += 1
                continue
            stats["longer"] += 1
            tail, tail_rva = body[row["size"]:], row["rva"] + row["size"]
            if tail_rva + len(tail) > uni.text_end or uni.overlaps_matched(tail_rva, len(tail)):
                stats["tail_already_claimed"] += 1
                continue
            if any(tail_rva <= start < tail_rva + len(tail) for start in ghidra_starts):
                # A boundary inside the tail says those bytes are another
                # function's, however well they compare — the row was not
                # trimmed short, the object simply laid two bodies out in the
                # order retail happens to hold them.
                stats["tail_holds_a_ghidra_start"] += 1
                continue
            holes = [o - row["size"] for o, t, _ in relocs
                     if row["size"] <= o < len(body) and t in (DIR32, REL32)]
            if not masked_equal(tail, image.body(tail_rva, len(tail)), holes):
                stats["tail_mismatch"] += 1
                stats["tail_mismatch_bytes"] += len(tail)
                continue
            stats["extendable"] += 1
            stats["extendable_bytes"] += len(tail)
            out_rows.append({"name": row["name"], "rva": f"0x{row['rva']:08X}",
                             "old_size": row["size"], "new_size": len(body),
                             "tail": len(tail), "source": source,
                             "symbol": symbol, "notes": row["notes"]})

    print(f"obj_sweep extend: {dict(stats)}")
    if not out_rows:
        raise SystemExit("obj_sweep extend: no held row's object symbol runs past its "
                         f"target_size with a matching retail tail ({stats['longer']} ran "
                         f"long, {stats['tail_mismatch']} tails differed, "
                         f"{stats['tail_already_claimed']} were already claimed). Writing a "
                         "one-column CSV here would look like a wave with nothing in it.")
    out_rows.sort(key=lambda r: -r["tail"])
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, list(out_rows[0]), lineterminator="\n")
        writer.writeheader()
        writer.writerows(out_rows)
    print(f"obj_sweep extend: {len(out_rows)} row(s), "
          f"{sum(r['tail'] for r in out_rows):,d} byte(s) -> {out}")


# --------------------------------------------------------------------------

def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)

    report = sub.add_parser("report", help="classify at HEAD and print the byte accounting")
    report.add_argument("--assert-circularity", action="store_true",
                        help="re-run with the naked exclusions off and print the inflation "
                             "ratio; fails if they are not doing anything")
    report.set_defaults(func=cmd_report)

    wave = sub.add_parser("wave", help="write a wave CSV for tools/land_wave.py")
    wave.add_argument("--class", dest="klass", required=True, choices=CLASSES)
    wave.add_argument("--out", required=True)
    wave.add_argument("--limit", type=int, default=0, help="stop after this many rows")
    wave.add_argument("--min-size", type=int, default=1)
    wave.add_argument("--max-sources", type=int, default=0,
                      help="draw from at most this many owner TUs (byte-heaviest first)")
    wave.add_argument("--skip-sources", type=int, default=0,
                      help="skip this many owner TUs first — the next wave's cursor")
    wave.add_argument("--alternates", type=int, default=2,
                      help="alternate owner TUs per row for land_wave's retry path")
    wave.add_argument("--include-unclaimed", action="store_true",
                      help="also claim ghidra starts no ledger row covers")
    wave.set_defaults(func=cmd_wave)

    extend = sub.add_parser("extend", help="held rows whose object symbol runs past target_size")
    extend.add_argument("--out", required=True)
    extend.set_defaults(func=cmd_extend)

    args = parser.parse_args(argv)
    args.func(args)


if __name__ == "__main__":
    main()
