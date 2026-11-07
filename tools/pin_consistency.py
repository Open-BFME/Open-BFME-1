#!/usr/bin/env python3
"""Pin-consistency guard for targets/game/reverse/symbols.csv.

symbols.csv is an ADDITIVE candidate list. build.py's REL32 resolver walks a
name's addresses in file order and keeps the first displacement that reproduces
retail (see load_symbol_map / compile_function). Give one name enough addresses
and something will match, so a green gate proves the BYTES of the caller and
says nothing about WHICH function the callee is. Three misidentifications
reached master through exactly that hole:

  * findNonConstCommandButton was pinned at both 0x36D27 and 0x44EEF, whose
    thunks follow to different 126-byte bodies. A shim had moved two struct
    fields so one class would fit the wrong one; the result byte-matched and was
    written up as an exact match (retracted in a16b62ec9).
  * 0x14867 is currently pinned as winSetDisabledColor, winSetEnabledColor,
    winSetEnabledBorderColor AND winSetHiliteColor at once, which is how sixteen
    GameWindow/GadgetSlider rows came to sit one body early (ba1dbf6f8).

THE INVARIANT: every address pinned to one name must, after following the
incremental-link thunk chain, land on a body byte-equal to every other body the
same name pins. One name, one function.

WHAT THIS DOES NOT CATCH -- read this before trusting a green line
-----------------------------------------------------------------
The invariant is ONE NAME, MANY ADDRESSES. Two neighbouring hazards are shaped
the other way round. The baseline gate (`--check`) does not cover either; the
delta gate (`--delta`, below) refuses NEW instances of both and leaves the
existing ones to be drained. Live counts, never figures typed into this text:
`--check` prints how many names pin a single address, `--candidates` how many
candidate-list violations exist.

1. ONE ADDRESS, MANY NAMES. The 0x14867 incident above is really this shape.
   Three of its four names are flagged only incidentally, because they happen to
   carry other pins too; ?winSetEnabledBorderColor@GameWindow@@QAEHHH@Z pins
   0x14867 and nothing else and is invisible to one-name-one-body. Most symbols
   pin exactly one address and are never compared to anything. A blanket check
   is not the answer -- many bodies legitimately carry several names (folded
   destructors reached through one release body, ILT stubs, routes, views) --
   so `--delta` judges what a diff changes. Policy (project lead 2026-10-16):
   a second spelling on an already-named body is refused; it lands as an
   abi-view= row or with a verified override. Identities are matched rows AND
   real-name pins, keyed by the body their address leads to (through ILT
   slots only). Refused: an added pin or identity row on a body another name
   holds (judged against base and new names together, so demoting the owner
   in the same commit does not help; a row replaced at its own address is a
   rename); an added pin inside a matched body; an existing pin the diff turns
   into a conflict. Admitted by proof: route= and abi-view= rows the image
   admits, a placeholder spelling its own address, and a real name the ILT
   CONFIRMS over rivals that are placeholders or ILT-refuted. An override is a
   `pin-identity-override:` line the same diff adds, citing a verified
   caller=, declared by an `Identity-Override:` trailer.

2. THE OTHER HALF OF THE CANDIDATE LIST. load_symbol_map seeds each name from
   its functions.csv rows and THEN appends its symbols.csv pins, so the additive
   list the resolver actually walks is the union of both. `--check` reads only
   the pins. A name with one pin and one ledger row pointing at a different body
   is a two-candidate list -- the exact hazard -- and `len(pins) < 2` skips it.
   `--candidates` applies the same invariant to the real list and reports. It
   is not baselined (baselines may only shrink); `--delta` refuses any
   violation the base side did not already carry. Drain them, do not record
   them.

HOW TEMPLATES ARE HANDLED (explicitly, not by exclusion)
--------------------------------------------------------
A template instantiated in K translation units leaves up to K byte-identical
COMDATs in retail, and pinning all K is legitimate -- those are the same
function. Two copies of one function at different RVAs differ ONLY in their
rel32 displacement slots, and there by exactly (rva_b - rva_a), because a
displacement is `target - (site + 4)` and the target is shared. So the
comparison rebases instead of excluding: bytes must be equal everywhere except
at rel32 slots anchored to a real branch opcode (E8/E9/0F 8x), where the two
little-endian displacements must differ by exactly the RVA delta.

That is strictly stronger than the blind masking compile_function does for a
lib member: blind masking would let two DIFFERENT call targets pass, the
rebasing test would not. No name pattern is consulted anywhere -- a `??$`
template and a hand-written function are judged by the same rule, and a folded
(ICF) body reached from two pins is one body and trivially consistent.

ROUTING IS NOT IDENTITY (`route=` rows)
---------------------------------------
The invariant above is false for one real case, and denying it made a true fact
unlandable. symbols.csv conflates two claims: "symbol X LIVES at A" and "a call
to X may legitimately ENCODE A". `__CxxThrowException@8` lives at 0x00850600 (a
103-byte static CRT copy this repo has byte-matched) AND at 0x009F6D00 (the
six-byte MSVCR71 import thunk); 128 retail call sites in 82 matched rows encode
the second. Pinning it is what those callers need, and one-name-one-body then
reports a size disagreement -- correctly, by its own rule, about two addresses
that are both true. The gate was demanding the deletion of a fact.

So a row whose notes carry `route=<target>` is a ROUTING pin: it asserts only
that calls encode this address, never that the function lives there, and it is
exempt from one-name-one-body. Nothing else is exempt.

Exempting on an author's say-so would make `route=` a laundering channel for
every identity this guard exists to catch, so admissibility is MACHINE-CHECKED
against the retail image (route_verdict) and a refusal is a hard failure:

  (a) an `FF 25` import thunk whose IAT slot the PE import directory binds to a
      DLL export of this same name, and which functions.csv already carries as a
      matched gen-import row naming that same target; or
  (b) an `E9` jump stub whose target body carries a matched, identity-naming
      functions.csv row for this very symbol.

Both re-derive the answer from the image and compare it to the note, so the note
cannot be wrong and stay. Everything else is refused, including the two nearest
misses: `??3@YAXPAX@Z` at 0x009F6C3A (that slot imports MSVCR71 `free`) and
`??2@YAPAXI@Z` at 0x0082E540 (not a thunk at all -- it is __new_alloc::allocate).

BASELINE, NOT WHITELIST
-----------------------
First run found a backlog of known-bad pins. targets/game/reverse/pin_consistency_baseline.csv
records each one WITH its evidence so the guard fails on anything NEW while the
backlog is drained. It is deliberately not self-seeding: an absent baseline is a
hard failure with instructions, never an auto-written free pass, because
verify_dir32_consistency's self-bootstrap is how 18 whitelist entries (8 of them
provably-wrong placements) got written without a human ever reading them.

The key is (symbol, sorted body RVAs). Adding or removing a pin changes the key,
so a baselined symbol cannot quietly absorb a new bad address, and a FIXED
symbol leaves a stale line that also fails -- the fix and the line removal are
one commit. Shrinking this file is the only direction it is allowed to move.
"""
import argparse
import bisect
import collections
import csv
import functools
import io
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402  (after the path insert that makes it importable)
import import_pin_guard  # noqa: E402
import progress  # noqa: E402

ROOT = build.ROOT
BASELINE = ROOT / "targets/game/reverse" / "pin_consistency_baseline.csv"
BASELINE_FIELDS = ["symbol", "bodies", "kind", "evidence"]

# A chain longer than this is not incremental linking, it is a cycle or a bug.
MAX_THUNK_HOPS = 16

# An incremental-link thunk is `jmp rel32` and nothing else. Following past a
# body the ledger has byte-proven LONGER than that would conflate a real
# one-instruction tail call with its callee, which is a different function.
THUNK_SIZE = 5


class Image:
    """The retail image plus the thunk walk, loaded once."""

    def __init__(self, ledger_sizes):
        self.data = build.EXE.read_bytes()
        self.sections = build.pe_sections(self.data)
        text = next(s for s in self.sections if s["name"] == ".text")
        self.low = text["rva"]
        self.high = text["rva"] + text["size"]
        self.ledger_sizes = ledger_sizes
        self._cache = {}

    def in_text(self, rva):
        return self.low <= rva < self.high

    def resolve(self, rva):
        """(body, chain) -- the body an address ultimately names.

        Follows E9 to a fixpoint rather than one hop: 1,915 pinned addresses
        reach their body through two or more `?j_########` stubs, and stopping
        at the first hop would compare two thunks instead of two functions.
        """
        cached = self._cache.get(rva)
        if cached is not None:
            return cached
        chain = [rva]
        cur = rva
        for _ in range(MAX_THUNK_HOPS):
            if not self.in_text(cur):
                break
            claimed = self.ledger_sizes.get(cur)
            if claimed and max(claimed) > THUNK_SIZE:
                break  # a proven body, not a jump stub
            nxt = build.follow_thunk(self.data, self.sections, cur, self.low, self.high)
            if nxt == cur:
                break
            if nxt in chain:
                raise SystemExit(
                    f"pin_consistency: thunk cycle from 0x{rva:08X}: "
                    + " -> ".join(f"0x{x:08X}" for x in chain + [nxt]))
            chain.append(nxt)
            cur = nxt
        else:
            raise SystemExit(
                f"pin_consistency: thunk chain from 0x{rva:08X} exceeds "
                f"{MAX_THUNK_HOPS} hops: " + " -> ".join(f"0x{x:08X}" for x in chain))
        result = (cur, chain)
        self._cache[rva] = result
        return result


def load_pins(path=None):
    """name -> [address] in symbols.csv file order, deduplicated per name."""
    pins = collections.defaultdict(list)
    with (path or build.SYMBOLS).open("r", encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            address = int(row["address"], 16)
            if address not in pins[row["name"]]:
                pins[row["name"]].append(address)
    return pins


# --------------------------------------------------------------------------
# route= pins -- an address calls ENCODE, not an address the function lives at.
# See "ROUTING IS NOT IDENTITY" above for why this class has to exist.
# --------------------------------------------------------------------------

ROUTE_RE = re.compile(r"(?:^|;)\s*route=([^;]+)")
GEN_IMPORT_TARGET_RE = re.compile(r"(?:^|;)target=([^;]+)")


def load_routes(path=None):
    """(name, address) -> the route target its `route=` note claims.

    build.load_symbol_map reads these rows exactly as it reads any other pin --
    one more REL32 candidate, notes unread -- so the note changes nothing about
    what the resolver does. It changes only what this guard is entitled to
    conclude from two addresses sharing a name.
    """
    routes = {}
    with (path or build.SYMBOLS).open("r", encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            found = ROUTE_RE.search(row.get("notes") or "")
            if not found:
                continue
            key, claim = (row["name"], int(row["address"], 16)), found.group(1).strip()
            # Two route= rows for one (name, address) is union-merge debris or a
            # hand-edit; silently keeping the last one would let a refuted claim
            # be overwritten by an admissible twin and vanish from the report.
            if routes.get(key, claim) != claim:
                raise SystemExit(
                    f"pin_consistency: {key[0]} 0x{key[1]:08X} carries two different "
                    f"route= claims ({routes[key]!r} and {claim!r}); one address routes "
                    "to one place, so one of these rows is wrong")
            routes[key] = claim
    return routes


def _cstring(data, offset):
    return data[offset:data.index(b"\0", offset)].decode("ascii", errors="replace")


@functools.lru_cache(maxsize=1)
def import_table():
    """IAT slot VA -> (dll, exported name), read from the PE import directory.

    Ground truth for what an `FF 25` thunk routes to. Ghidra's name for the
    thunk and the ledger's `target=` note both descend from this table; reading
    it directly means admissibility never rests on a name somebody typed.
    """
    data, sections = build.exe_image()
    optional = struct.unpack_from("<I", data, 0x3C)[0] + 24
    magic = struct.unpack_from("<H", data, optional)[0]
    if magic != 0x10B:
        raise SystemExit(f"pin_consistency: {build.EXE.name} is not PE32 (magic "
                         f"0x{magic:X}); the import reader only understands PE32")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    descriptor = build.rva_to_file_offset(
        sections, struct.unpack_from("<I", data, optional + 96 + 8)[0])
    slots = {}
    while True:
        lookup, _stamp, _fwd, dll_rva, first = struct.unpack_from("<IIIII", data, descriptor)
        if not dll_rva and not first:
            return slots
        dll = _cstring(data, build.rva_to_file_offset(sections, dll_rva))
        # Names come from the LOOKUP table and slot VAs from the address table,
        # walked in step. No fallback to the address table when the lookup is
        # absent: in a bound image those entries are resolved addresses, and
        # reading them as name RVAs would invent export names for real slots.
        if not lookup:
            raise SystemExit(f"pin_consistency: {dll} has no import lookup table, so its "
                             "export names cannot be read; a route= pin cannot be judged "
                             "against this import descriptor")
        entry = build.rva_to_file_offset(sections, lookup)
        slot = first
        while True:
            value = struct.unpack_from("<I", data, entry)[0]
            if not value:
                break
            slots[image_base + slot] = (dll, f"#{value & 0xFFFF}" if value & 0x80000000
                                        else _cstring(data, build.rva_to_file_offset(
                                            sections, value) + 2))
            entry += 4
            slot += 4
        descriptor += 20


@functools.lru_cache(maxsize=1)
def gen_import_targets():
    """RVA -> the function a matched gen-import row says its thunk targets."""
    return gen_import_targets_of(build.load_all_function_rows())


def gen_import_targets_of(rows):
    """gen_import_targets over an explicit set of functions.csv rows."""
    targets = {}
    for row in rows:
        notes = row.get("notes") or ""
        if row["status"] != "matched" or not notes.startswith("gen-import;"):
            continue
        found = GEN_IMPORT_TARGET_RE.search(notes)
        if found:
            targets[int(row["target_rva"], 16)] = found.group(1)
    return targets


def undecorated_forms(name):
    """The import-table spellings a linker may satisfy this object symbol with.

    A C symbol reaches an import table undecorated: the compiler calls the CRT
    throw helper `__CxxThrowException@8` and MSVCR71 exports it as
    `_CxxThrowException` -- one leading underscore and one stdcall `@8` apart,
    which is exactly what an import library reconciles. A C++ mangled name
    (leading `?`) is exported verbatim and is compared as written: stripping a
    trailing `@<n>` off one would invent an equivalence, and inventing
    equivalences is how a route= note would become a laundering channel.
    """
    forms = {name}
    if not name.startswith("?"):
        stem = re.sub(r"@\d+$", "", name)
        forms.add(stem)
        if stem[:1] in ("_", "@"):
            forms.add(stem[1:])
    return forms


def route_verdict(scanner, name, address, claim):
    """None when this `route=` row is admissible, else the reason it is refused.

    ADMISSIBLE IS NARROW ON PURPOSE, and it is decided here rather than by the
    author, because `route=` buys an exemption from one-name-one-body and an
    exemption anyone can write is not a check. Both arms recompute the route
    from the retail image and then require the note to say the same thing, so a
    row cannot carry a claim the image does not support.
    """
    if not scanner.image.in_text(address):
        return f"0x{address:08X} is outside .text, so it is not a call target at all"
    head = build.read_target_bytes(address, 6)
    if len(head) < 6:
        return f"0x{address:08X}: fewer than six bytes remain in the image at that address"
    if head[:2] == b"\xff\x25":
        slot = struct.unpack_from("<I", head, 2)[0]
        entry = import_table().get(slot)
        if entry is None:
            return (f"0x{address:08X} reads IAT slot 0x{slot:08X}, which the PE import "
                    "directory does not describe")
        dll, exported = entry
        forms = undecorated_forms(name)
        if exported not in forms:
            return (f"0x{address:08X} imports {dll}!{exported}, which is not {name} "
                    f"(spellings accepted for it: {', '.join(sorted(forms))})")
        # A Scanner over another ledger state carries its own rows; other
        # callers (link_census) pass a bare namespace and read the working tree.
        targets = (scanner.gen_import_targets() if hasattr(scanner, "gen_import_targets")
                   else gen_import_targets())
        ledger_target = targets.get(address)
        if ledger_target is None:
            return (f"0x{address:08X} has no matched gen-import row in functions.csv, so "
                    "the ledger does not carry this address as an import thunk")
        if ledger_target not in forms:
            return (f"0x{address:08X}: the ledger's gen-import row targets {ledger_target}, "
                    f"not {name}")
        expected = f"{dll}!{exported}"
        return None if claim == expected else \
            f"note says route={claim}; the image says route={expected}"
    if head[:1] == b"\xe9":
        body, _chain = scanner.image.resolve(address)
        if body == address:
            return (f"0x{address:08X} begins E9 but resolves no further; a proven body "
                    "longer than a jump stub is a function, not a route")
        if name not in scanner.identities.get(body, ()):
            owned = sorted(scanner.identities.get(body, ())) or ["nothing"]
            return (f"0x{address:08X} jumps to 0x{body:08X}, which the ledger names "
                    f"{', '.join(owned)} -- not {name}")
        expected = f"0x{body:08X}"
        return None if claim == expected else \
            f"note says route={claim}; the image says route={expected}"
    return (f"0x{address:08X} begins {head[:2].hex()} -- neither an `FF 25` import thunk "
            "nor an `E9` jump stub, so it is a function body and a pin on it is an "
            "identity claim, not a route")


def verify_routes(scanner, routes):
    """Re-derive every `route=` row from the image. Any refusal fails the gate."""
    refused = []
    for (name, address), claim in sorted(routes.items()):
        why = route_verdict(scanner, name, address, claim)
        if why:
            refused.append((name, address, claim, why))
    if refused:
        print(f"Route pins: FAIL {len(refused)} inadmissible route= row(s) in "
              f"{shown(build.SYMBOLS)}")
        for name, address, claim, why in refused[:12]:
            print(f"    {name} 0x{address:08X} (route={claim})")
            print(f"        {why}")
        print("    route= exempts a row from one-name-one-body, so it is accepted only "
              "for an import thunk or a jump stub the retail image itself proves. Fix "
              "the note, or delete the row — do not widen the rule.")
        raise SystemExit(1)
    return len(routes)


def verify_views(pins_path=None):
    """{(name, address)} of the abi-view= rows; any the image refuses fails the gate."""
    import abi_view
    rows = abi_view.view_rows(pins_path)
    if not rows:
        return set()
    refused = abi_view.check(path=pins_path)
    if refused:
        print(f"ABI views: FAIL {len(refused)} inadmissible abi-view= row(s) in {shown(pins_path or build.SYMBOLS)}")
        for name, address, canonical, why in refused[:12]:
            print(f"    {name} 0x{address:08X} (abi-view={canonical})")
            print(f"        {why}")
        print("    abi-view= exempts a pin from identity checks, so it is accepted only when the "
              "retail image proves the call target, the canonical body and the ABI. Fix the "
              "note or the declaration, or delete the row -- do not widen the rule.")
        raise SystemExit(1)
    return {(name, address) for name, address, _canonical in rows}


def names_identity(row):
    """Does this functions.csv row assert WHICH function lives at its address?

    build.py draws the line in the same place (see harvest_reloc_names): a
    generated row pins bytes under a synthetic name, and a ?dup_<rva> row pins
    them under a twin whose identity is explicitly not claimed. Neither can
    settle an argument about identity, so neither counts here. The generated
    test is progress.py's own -- path AND note, so a generator cannot promote
    its rows to identities by omitting its marker.
    """
    return (row["status"] == "matched"
            and not row["source"].startswith(progress.GENERATED_ROOTS)
            and not progress.GEN_NOTE_RE.search(row["notes"])
            and not build.DUP_ALIAS_RE.match(row["name"]))


def load_ledger(rows=None):
    """Per-body extents and identity owners, over every functions.csv row.

    Unmatched rows count for extent because an unmatched row still asserts a
    boundary somebody derived; matched rows are preferred where they disagree,
    and the provenance is reported so a human can see which spoke.
    """
    sizes = collections.defaultdict(dict)
    matched = collections.defaultdict(dict)
    identities = collections.defaultdict(set)
    for row in build.load_all_function_rows() if rows is None else rows:
        rva = int(row["target_rva"], 16)
        size = int(row["target_size"])
        sizes[rva].setdefault(size, []).append(row["name"])
        if row["status"] == "matched":
            matched[rva].setdefault(size, []).append(row["name"])
        if names_identity(row):
            identities[rva].add(row["name"])
    return sizes, matched, identities


def load_extra_boundaries():
    """Fallback extents for a body no functions.csv row claims."""
    ghidra, derived = {}, {}
    with (ROOT / "targets/game/reverse" / "ghidra_functions.csv").open("r", encoding="utf-8",
                                                          newline="") as handle:
        for row in csv.DictReader(handle):
            ghidra.setdefault(int(row["rva"], 16), int(row["size"]))
    with (ROOT / "targets/game/reverse" / "derived_boundaries.csv").open("r", encoding="utf-8",
                                                            newline="") as handle:
        for row in csv.DictReader(handle):
            derived.setdefault(int(row["rva"], 16), int(row["size"]))
    return ghidra, derived


def rebased_equal(left, right, left_rva, right_rva):
    """Are two retail bodies the same function placed at two addresses?

    Returns (verdict, sites, divergence). `sites` are the rel32 offsets whose
    displacements were reconciled by the RVA delta; `divergence` is the offset
    of the first byte difference that is NOT such a site, or None.

    A false PASS here would hide a misidentification, so a difference is only
    forgiven when all three hold at once: the four bytes are a little-endian
    pair differing by exactly (right_rva - left_rva), the preceding byte is a
    rel32 branch opcode, and that opcode byte is itself identical in both.
    """
    if len(left) != len(right):
        raise ValueError("rebased_equal needs equal-length bodies")
    delta = (right_rva - left_rva) & 0xFFFFFFFF
    size = len(left)
    sites = []
    index = 0
    while index < size:
        if left[index] == right[index]:
            index += 1
            continue
        for start in range(max(0, index - 3), index + 1):
            if start + 4 > size:
                break
            pair = struct.unpack_from("<I", left, start)[0] - \
                struct.unpack_from("<I", right, start)[0]
            if pair & 0xFFFFFFFF != delta:
                continue
            if not _branch_anchored(left, right, start):
                continue
            sites.append(start)
            index = start + 4
            break
        else:
            return False, sites, index
    return True, sites, None


def _branch_anchored(left, right, start):
    """Is offset `start` the displacement of a rel32 branch in BOTH bodies?"""
    if start >= 1 and left[start - 1] == right[start - 1] and \
            left[start - 1] in (0xE8, 0xE9):
        return True
    return (start >= 2 and left[start - 2] == right[start - 2] == 0x0F
            and left[start - 1] == right[start - 1]
            and 0x80 <= left[start - 1] <= 0x8F)


class Scanner:
    """The image and one ledger state. ROWS (functions.csv rows) defaults to
    the working tree; the delta gate builds one scanner per side of a diff."""

    def __init__(self, rows=None, extra=None):
        self.rows = rows
        self.ledger_sizes, self.ledger_matched, self.identities = load_ledger(rows)
        self.ghidra, self.derived = extra or load_extra_boundaries()
        self.image = Image(self.ledger_sizes)
        self._extents = sorted(
            (rva, size, members[0])
            for rva, entry in self.ledger_matched.items()
            for size, members in entry.items())
        self._starts = [rva for rva, _size, _name in self._extents]
        self._widest = max((size for _rva, size, _name in self._extents), default=0)

    def gen_import_targets(self):
        if self.rows is None:
            return gen_import_targets()
        if not hasattr(self, "_gen_import_targets"):
            self._gen_import_targets = gen_import_targets_of(self.rows)
        return self._gen_import_targets

    def extent(self, rva):
        """(size, provenance) for a body, or (None, reason)."""
        for table, provenance in ((self.ledger_matched, "matched"),
                                  (self.ledger_sizes, "ledger")):
            entry = table.get(rva)
            if entry:
                if len(entry) > 1:
                    return None, f"{provenance}-rows disagree on extent {sorted(entry)}"
                return next(iter(entry)), provenance
        if rva in self.ghidra:
            return self.ghidra[rva], "ghidra"
        if rva in self.derived:
            return self.derived[rva], "derived"
        return None, "no boundary in any source"

    def interior_of(self, rva):
        """(name, start, size) of the byte-verified body this address is INSIDE.

        A callee pin has to be a function entry. An address strictly inside a
        matched row's extent cannot be one: those bytes are byte-verified as one
        function, and check_csv already forbids two claims overlapping. Both
        no-boundary pins in the first backlog are this -- 0x0012C877 is 1,431
        bytes into ModuleFactory::init and decodes mid-instruction.
        """
        index = bisect.bisect_right(self._starts, rva) - 1
        while index >= 0:
            start, size, name = self._extents[index]
            if start < rva < start + size:
                return name, start, size
            if start + self._widest <= rva:
                break
            index -= 1
        return None

    def owners(self, rva):
        names = set()
        for members in self.ledger_sizes.get(rva, {}).values():
            names.update(members)
        return sorted(names)

    def inspect(self, name, addresses):
        """None when the name's pins agree; a violation dict when they do not."""
        bodies, chains = [], {}
        for address in addresses:
            body, chain = self.image.resolve(address)
            chains.setdefault(body, []).append(chain)
            if body not in bodies:
                bodies.append(body)
        if len(bodies) < 2:
            return None
        bodies.sort()

        outside = [b for b in bodies if not self.image.in_text(b)]
        if outside:
            return self._violation(name, bodies, chains, "non-text-pin",
                                   "; ".join(f"0x{b:08X} is outside .text" for b in outside))

        extents = {b: self.extent(b) for b in bodies}
        unknown = [b for b, (size, _why) in extents.items() if size is None]
        if unknown:
            return self._violation(
                name, bodies, chains, "no-boundary",
                "; ".join(f"0x{b:08X}: {extents[b][1]}" for b in unknown))

        distinct = {size for size, _ in extents.values()}
        if len(distinct) > 1:
            return self._violation(
                name, bodies, chains, "size-disagreement",
                "; ".join(f"0x{b:08X}={extents[b][0]}({extents[b][1]})" for b in bodies))

        size = distinct.pop()
        image = {b: build.read_target_bytes(b, size) for b in bodies}
        classes = []
        for body in bodies:
            for members in classes:
                verdict, _sites, _div = rebased_equal(
                    image[members[0]], image[body], members[0], body)
                if verdict:
                    members.append(body)
                    break
            else:
                classes.append([body])
        if len(classes) == 1:
            return None
        divergence = rebased_equal(image[classes[0][0]], image[classes[1][0]],
                                   classes[0][0], classes[1][0])[2]
        detail = " | ".join(
            "class%d=%s" % (i, ",".join(f"0x{b:08X}" for b in members))
            for i, members in enumerate(classes))
        return self._violation(
            name, bodies, chains, "divergent-bodies",
            f"size={size}; first divergence at +0x{divergence:X}; {detail}")

    def _violation(self, name, bodies, chains, kind, evidence):
        parts = []
        pins = {}
        for body in bodies:
            pins[body] = sorted({chain[0] for chain in chains[body]})
            owned = self.owners(body)
            held = ",".join(n for n in owned if n != name) or "unclaimed"
            inside = self.interior_of(body)
            where = (" INTERIOR-OF:%s+0x%X" % (inside[0], body - inside[1])
                     if inside else "")
            parts.append("0x%08X<-%s owned-by:%s%s" % (
                body, "/".join(f"0x{p:08X}" for p in pins[body]), held, where))
        return {
            "symbol": name,
            "bodies": bodies,
            "pins": pins,
            "kind": kind,
            "evidence": f"{evidence} :: " + " ; ".join(parts),
        }

    def clear_cut(self, violation):
        """CANDIDATE pins a byte-verified ledger row refutes, or None.

        These are candidates, not verdicts. A previous session landed all 47 of
        them and the full gate turned 111 byte-matched rows RED; 110 of those
        failures resolved to a pin it had just dropped. Only 21 of 47 survived
        three gate rounds -- a ~55% false-verdict rate on output once labelled
        "settled by the ledger". The lesson is one rule:

            A BYTE-VERIFIED CALLER OUTRANKS A BYTE-VERIFIED IDENTITY ROW.

        A ledger row says what a body IS. A retail call site says what the
        resolver NEEDS. When they disagree the call site wins, because dropping
        that pin removes the only candidate that reproduces the caller's
        displacement and the gate goes red. The row has to move before the pin
        can follow it.

        THIS FUNCTION CANNOT APPLY THAT RULE, AND THE OBVIOUS FIX IS WRONG.
        Screening out pins retail calls was implemented and measured before
        being removed: 36 of the 39 pins that DID land clean in 0d42eb8f4 are
        themselves retail call targets, so the screen suppresses 92% of the good
        answers while catching 25 of 26 bad ones. It does not separate them, it
        just says "no". Obvious in hindsight -- a callee pin IS an address
        retail calls, so "is it called" is true of nearly all of them.

        Deciding it properly means knowing which SYMBOL each call site
        references, and that lives in the object files' relocations, not in the
        image. This module deliberately reads neither compile output nor cached
        artifacts -- 1.6s on the image and the ledgers is what lets the hooks
        afford it. So the contract is honest instead: these are CANDIDATES.
        Confirm each with a full ./build.sh, and expect about half to be
        refuted.

        Cheap to adjudicate means BOTH ends are already proven: exactly one
        pinned body carries a matched, identity-naming row for this very
        symbol, and every other pinned body carries one for a DIFFERENT
        function. Then the symbol's address is not in dispute and the other
        pins name somebody else's body -- retract them.

        A dropped body must have EXACTLY ONE identity owner, or be interior to a
        byte-verified body and therefore not an entry point at all. Several
        owners on one body is retail ICF: the linker folded functions that
        compiled to the same bytes, so "that address is somebody else" no longer
        argues the symbol is not also there, and the case needs a human.
        0x00887940 carries nine folded destructors and is why this bound exists.

        Anything less (a body only a generated or ?dup_ row covers, two bodies
        both claiming the symbol, no ledger identity anywhere) is a real
        investigation and is deliberately not offered here.
        """
        keep = [b for b in violation["bodies"]
                if violation["symbol"] in self.identities.get(b, ())]
        if len(keep) != 1:
            return None
        drop = []
        for body in violation["bodies"]:
            if body == keep[0]:
                continue
            inside = self.interior_of(body)
            if inside:
                drop.append((body, ["+0x%X inside %s, not an entry point"
                                    % (body - inside[1], inside[0])]))
                continue
            others = sorted(self.identities.get(body, ()))
            if len(others) != 1:
                return None
            drop.append((body, others))
        return {"keep": keep[0], "drop": drop}

    def scan(self, pins_path=None):
        violations = []
        pins = load_pins(pins_path)
        # Admissibility first: a route= row that the image refuses must fail
        # LOUDLY, never quietly buy the exemption it is asking for.
        routes = load_routes(pins_path)
        # An abi-view= row is a compilation view, never an identity (approved by
        # the project lead 2026-10-16; tools/abi_view.py): admitted only when the
        # image proves it. A view's target is named differently by definition, so
        # it is judged by verify_views instead of the route= verdict; it stays in
        # one-name-one-body, because the resolver offers every address a name has.
        views = verify_views(pins_path)
        verify_routes(self, {k: v for k, v in routes.items() if k not in views})
        multi = single = 0
        for name in sorted(pins):
            addresses = [a for a in pins[name] if (name, a) not in routes or (name, a) in views]
            single += len(addresses) == 1
            if len(addresses) < 2:
                continue
            multi += 1
            found = self.inspect(name, addresses)
            if found:
                violations.append(found)
        violations.sort(key=lambda v: (v["kind"], v["symbol"]))
        return violations, {"names": len(pins), "multi_pinned": multi,
                            "single_pinned": single, "routes": len(routes)}


def candidate_lists(rows=None, pins_path=None):
    """name -> every address build.py's REL32 resolver may try, both sources.

    load_symbol_map seeds each name from its functions.csv rows AND then
    appends its symbols.csv pins, so the additive candidate list the resolver
    walks is the UNION. The guard reads only the symbols.csv half, which means a
    name with one pin and one ledger row at a different body is a two-candidate
    list the invariant never sees. That is the same hazard, one source over.
    """
    lists = collections.defaultdict(list)
    routes = load_routes(pins_path)
    import abi_view
    views = {(n, a) for n, a, _c in abi_view.view_rows(pins_path)}  # candidates like any pin
    for row in build.load_all_function_rows() if rows is None else rows:
        rva = int(row["target_rva"], 16)
        if rva not in lists[row["name"]]:
            lists[row["name"]].append(rva)
    for name, addresses in load_pins(pins_path).items():
        for address in addresses:
            # A route is a candidate to the resolver and never an identity, so
            # it is out of this report as it is out of scan(); a view stays in,
            # since the resolver tries it like any pin.
            if address not in lists[name] and ((name, address) not in routes or (name, address) in views):
                lists[name].append(address)
    return lists


def report_candidates(scanner, pin_violations):
    """The invariant over the resolver's real candidate list, as a report.

    Reporting, not gating, and deliberately so: turning this on in the gate
    would need every newly-exposed violation baselined, and growing that file
    is the one move this guard exists to prevent. The next agent extends
    coverage by DRAINING these, not by recording them.
    """
    known = {v["symbol"] for v in pin_violations}
    extra = [v for name, v in candidate_violations(scanner, candidate_lists()).items()
             if name not in known]
    extra.sort(key=lambda v: (v["kind"], v["symbol"]))
    counts = collections.Counter(v["kind"] for v in extra)
    print(f"{len(pin_violations)} inconsistent on symbols.csv pins alone (the gated surface)")
    print(f"{len(extra)} MORE inconsistent once functions.csv rows join the candidate list "
          "(not baselined; `--delta` refuses new ones)")
    for kind, count in counts.most_common():
        print(f"    {kind}: {count}")
    for violation in extra:
        print(f"{violation['symbol']}\n    {violation['kind']}: {violation['evidence']}")
    return extra


def shown(path):
    """A repo-relative path for messages; a test's tmp_path prints in full."""
    return path.relative_to(ROOT) if path.is_relative_to(ROOT) else path


def key_of(symbol, bodies):
    return symbol + "|" + " ".join(f"0x{b:08X}" for b in sorted(bodies))


def format_row(violation):
    return {
        "symbol": violation["symbol"],
        "bodies": " ".join(f"0x{b:08X}" for b in sorted(violation["bodies"])),
        "kind": violation["kind"],
        "evidence": violation["evidence"],
    }


BASELINE_PREAMBLE = """\
# PIN-CONSISTENCY BACKLOG -- a to-do list of known-wrong identities.
# Written by tools/pin_consistency.py; read by the full gate (tools/build.py).
# Generated file: do not reformat it, and see tools/pin_consistency.py for the
# full argument. THE GOAL IS AN EMPTY FILE.
#
# WHAT EACH LINE MEANS
# --------------------
# targets/game/reverse/symbols.csv is an ADDITIVE candidate list: build.py's REL32 resolver
# walks a name's addresses and keeps the first displacement that reproduces
# retail. Give one name enough addresses and something matches, so a green gate
# proves the caller's BYTES and says nothing about WHICH function the callee is.
# Every line here is one name whose pinned addresses follow their thunk chains
# to bodies that are NOT the same function. At most one of them is that name.
# The rest are somebody else's function wearing its label, and each one is a
# misidentification waiting to be written up as an exact match -- which is
# exactly how the ControlBar and GameWindow families got 16 rows placed one body
# early before anyone noticed.
#
# WHY THEY ARE STILL HERE
# -----------------------
# Not because they are acceptable. The guard landed against a pre-existing
# backlog, and failing the gate on all of it would have blocked every agent
# from every unrelated commit. So the backlog is recorded WITH its evidence and
# the gate fails on anything NEW. A line here is a debt, never a permission slip.
#
# HOW TO RESOLVE ONE (this is the work; each line is a self-contained task)
# ------------------------------------------------------------------------
#   1. python3 tools/pin_consistency.py --symbol <name>
#        prints every pin, its thunk chain, each body's proven extent, and which
#        functions.csv rows already claim those bodies.
#   2. Decide WHICH body is the name. Evidence that settles it, strongest first:
#        a byte-verified functions.csv row naming this symbol at that body;
#        a ghidra xref/vtable slot; a decoded store offset (the GameWindow family
#        fell out of `lea eax,[eax+eax*2+d]` alone). Decompiled C is not proof.
#   3. Delete the losing pin rows from targets/game/reverse/symbols.csv -- splice in place,
#        every surviving line byte-identical, terminators unchanged (uniform
#        CRLF), and verify the census before/after. Deleting is a rewrite.
#   4. Delete this line, in the SAME commit. A fixed symbol leaves a stale line
#        that fails too, on purpose: the fix and the removal are one change.
#   5. Run the FULL ./build.sh. Not the scoped one -- see the warning below.
#
# THE TRAP THAT CAUGHT THE LAST TWO SESSIONS
# ------------------------------------------
# A BYTE-VERIFIED CALLER OUTRANKS A BYTE-VERIFIED IDENTITY ROW. A session landed
# all 47 --clear-cut verdicts and the gate turned 111 byte-matched rows RED; 110
# of them resolved to a pin it had just deleted -- retail callers reaching the
# very body the ledger says belongs to somebody else. Only 21 of 47 survived.
# --clear-cut is a CANDIDATE list, not a verdict list: it reads the ledger and
# the image, never the object relocations that say which symbol a call site
# means, so it cannot see this coming. Screening out pins retail calls does NOT
# fix it -- that was measured, and it suppresses 36 of the 39 pins that landed
# clean. Confirm every retraction with a full ./build.sh; expect half to fail.
# When the ledger row and the call site disagree, the row moves first.
#
# THIS FILE IS ONLY ALLOWED TO SHRINK
# -----------------------------------
# Adding a line to make a build green is the exact anti-pattern this guard
# exists to stop -- fix the pin instead. Enforced, not merely requested:
# --write-baseline refuses to emit a key the file does not already carry, and
# `--assert-shrink-only` (run by .githooks/pre-commit) fails on any key added
# vs HEAD, so a hand-edited line is caught too. If you believe a line must be
# added, you have found a NEW misidentification: fix it.
#
# KEY AND COLUMNS
# ---------------
# key = symbol + its sorted body RVAs. A new address on a baselined symbol
# changes the key and FAILS, so a baselined line cannot quietly absorb one more
# bad pin.
#
# kinds:
#   divergent-bodies  same extent, bytes are not the same function even after
#                     rel32 rebasing -- at most one pin names this symbol
#   size-disagreement the pinned bodies have different proven extents. 307 of
#                     these are matched-vs-matched: two byte-verified bodies of
#                     different proven lengths cannot be one function.
#   no-boundary       a pinned body has no proven extent, so nothing can verify it
#   non-text-pin      a pin resolves outside .text and cannot be a code body
#
# evidence: <kind detail> :: <body><-<pins> owned-by:<other functions.csv names>
#           INTERIOR-OF:<fn>+0x<n> means the pin is not even an entry point --
#           it points inside a byte-verified body, so it cannot be any function.
#
# NOT COVERED HERE: single-pinned names, and the functions.csv half of the
# resolver's candidate list. `--candidates` reports the second (live count);
# `--delta` refuses new instances of both.
"""


def write_baseline(violations, path=BASELINE, seed=False):
    """Regenerate the baseline. SHRINK-ONLY unless explicitly seeding.

    "Only allowed to shrink" was prose in the preamble and nothing enforced it,
    which left `--write-baseline` as a one-command way to turn any red green --
    the exact move verify_dir32_consistency's self-bootstrap made, and the
    reason 18 unreviewed whitelist entries exist. So the tool now refuses to
    emit a key the committed file does not already carry: regeneration may drop
    lines and never add one.

    Seeding a baseline for a NEW surface is a real (rare) need, so it gets its
    own flag that only works when there is no file to overwrite. Growth by
    deleting the file and re-running is therefore two loud, separately-named
    acts on a tracked file, not a silent side effect of one.
    """
    ordered = sorted(violations, key=lambda v: (v["kind"], v["symbol"]))
    if seed:
        if path.exists():
            raise SystemExit(
                f"pin_consistency: --seed-baseline refuses to overwrite existing "
                f"{shown(path)}. Seeding is for a surface that has no baseline yet; "
                "to regenerate this one after adjudicating, use --write-baseline "
                "(which may only drop lines).")
    else:
        known = read_baseline(path)
        added = [v for v in ordered if key_of(v["symbol"], v["bodies"]) not in known]
        if added:
            raise SystemExit(
                f"pin_consistency: --write-baseline is SHRINK-ONLY and refuses to add "
                f"{len(added)} line(s) that {shown(path)} does not already carry. A new "
                "violation means a pin got worse, not that the baseline got shorter — fix "
                "the pin in targets/game/reverse/symbols.csv instead. New key(s):\n"
                + "".join(f"    {v['symbol']} [{v['kind']}] "
                          + " ".join(f"0x{b:08X}" for b in sorted(v["bodies"])) + "\n"
                          for v in added[:12]))
    lines = [BASELINE_PREAMBLE, ",".join(BASELINE_FIELDS) + "\n"]
    buffer = []
    for violation in ordered:
        row = format_row(violation)
        buffer.append([row[field] for field in BASELINE_FIELDS])
    out = io.StringIO()
    csv.writer(out, lineterminator="\n").writerows(buffer)
    path.write_text("".join(lines) + out.getvalue(), encoding="utf-8", newline="")


def _blob_at(ref, path):
    import subprocess
    blob = subprocess.run(["git", "show", f"{ref}:{path.relative_to(ROOT).as_posix()}"],
                          capture_output=True, text=True, cwd=ROOT)
    if blob.returncode:
        raise SystemExit(f"pin_consistency: cannot read {shown(path)} at {ref}: "
                         f"{blob.stderr.strip()}")
    return blob.stdout


def assert_shrink_only(ref="HEAD", at=None, path=BASELINE):
    """Fail if the baseline at `at` adds a key the one at `ref` lacks.

    write_baseline's refusal only covers the tool. A hand-edited line is the
    same anti-pattern typed by hand, and the committed file is where it does
    the damage, so the invariant is enforced against git history too — this is
    what the hooks call. Comparing KEYS, not line counts: swapping one
    adjudicated line for one new violation keeps the count flat.

    `at` defaults to the working tree (the commit hook's question, "is what I am
    about to commit bigger?"); the push hook passes the outgoing head so the
    whole range is judged, since --no-verify skips the commit hook entirely.
    """
    previous = set(_baseline_keys(_blob_at(ref, path)))
    current = set(_baseline_keys(_blob_at(at, path) if at
                                 else path.read_text(encoding="utf-8")))
    added = sorted(current - previous)
    if added:
        print(f"Pin baseline: FAIL {len(added)} line(s) ADDED vs {ref} — this file is only "
              "allowed to shrink; a new violation means a pin got worse")
        for key in added[:12]:
            print(f"    {key}")
        raise SystemExit(1)
    print(f"Pin baseline: OK ({len(current)} entries, {len(previous - current)} removed "
          f"vs {ref}, 0 added)")


def _baseline_keys(text):
    body = "".join(line for line in text.splitlines(keepends=True)
                   if not line.startswith("#"))
    for row in csv.DictReader(body.splitlines()):
        yield key_of(row["symbol"], [int(b, 16) for b in row["bodies"].split()])


def read_baseline(path=BASELINE):
    if not path.exists():
        raise SystemExit(
            f"pin_consistency: {shown(path)} is missing. This guard does "
            "NOT seed itself -- an auto-written baseline is an unreviewed whitelist. "
            "Run `python3 tools/pin_consistency.py --write-baseline`, READ the file, "
            "and commit it.")
    entries = {}
    text = path.read_text(encoding="utf-8")
    body = "".join(line for line in text.splitlines(keepends=True)
                   if not line.startswith("#"))
    for row in csv.DictReader(body.splitlines()):
        bodies = [int(b, 16) for b in row["bodies"].split()]
        entries[key_of(row["symbol"], bodies)] = row
    return entries


def check(violations, path=BASELINE):
    """(new, stale) -- violations absent from the baseline, and the reverse."""
    baseline = read_baseline(path)
    current = {key_of(v["symbol"], v["bodies"]): v for v in violations}
    new = [current[k] for k in sorted(current) if k not in baseline]
    stale = [baseline[k] for k in sorted(baseline) if k not in current]
    return new, stale


def verify_import_pins(exe=None, symbols=None):
    """Gate the guarded CRT pins against the retail PE import directory.

    This is intentionally a second, orthogonal check to the one-name/many-
    addresses consistency invariant above.  The latter can accept a single
    wrong pin; this check identifies the import reached by each compiler thunk.
    """
    try:
        image = import_pin_guard.PEImage.from_path(exe or build.EXE)
        pins = import_pin_guard.load_guarded_pins(symbols or build.SYMBOLS)
        results = import_pin_guard.check_pins(image, pins)
    except (OSError, ValueError) as exc:
        print(f"CRT import pins: FAIL unable to inspect baseline: {exc}")
        raise SystemExit(1)

    failures = [result for result in results if not result.ok]
    if failures:
        print(f"CRT import pins: FAIL {len(failures)} of {len(results)} guarded pins")
        for result in failures:
            print(f"    {import_pin_guard._format_result(result)}")
        raise SystemExit(1)
    print(f"CRT import pins: OK ({len(results)} guarded pins)")


def verify_dir32_pins(scanner):
    """A pin must agree with the address byte-verified code gives the same name.

    build.py masks DIR32 operands, so a pin that names the wrong global or vtable
    still reproduces retail; dir32_addresses.csv records where matched references
    put each name. Most pins are RVAs, some are written as VAs, so either reading
    passes, and code addresses are compared after following jump stubs.
    """
    recorded = build.read_dir32_addresses()
    whitelist = build.read_dir32_whitelist()
    wrong, checked = [], 0
    for name, pins in load_pins().items():
        va = recorded.get(name)
        if va is None or name in whitelist:
            continue
        want = scanner.image.resolve(va - 0x400000)[0]
        for pin in pins:
            checked += 1
            readings = [pin] + ([pin - 0x400000] if pin >= 0x400000 else [])
            if not any(scanner.image.resolve(rva)[0] == want for rva in readings):
                wrong.append((name, pin, va))
    if wrong:
        print(f"DIR32 pins: FAIL {len(wrong)} pin(s) put a name somewhere matched code does not")
        for name, pin, va in wrong[:12]:
            print(f"    {name}: pinned 0x{pin:08X}, matched references use 0x{va:08X}")
        print(f"    Fix the pin in {shown(build.SYMBOLS)}, or the code if it is the code that is wrong "
              f"(then correct {shown(build.DIR32_ADDRESSES)} in the same commit).")
        raise SystemExit(1)
    print(f"DIR32 pins: OK ({checked} pin(s) agree with {shown(build.DIR32_ADDRESSES)})")


def verify(path=BASELINE):
    """The gate entry point. Prints its own verdict; raises SystemExit on failure."""
    scanner = Scanner()
    violations, stats = scanner.scan()
    new, stale = check(violations, path)
    if new:
        print(f"Pin consistency: FAIL {len(new)} NEW inconsistent symbol(s) "
              "(one name, addresses that are not the same function)")
        for violation in new[:12]:
            print(f"    {violation['symbol']}")
            print(f"        {violation['kind']}: {violation['evidence']}")
        print("    Fix the pin in targets/game/reverse/symbols.csv. Do NOT add these to "
              f"{shown(path)} to get green.")
        raise SystemExit(1)
    if stale:
        print(f"Pin consistency: FAIL {len(stale)} baseline line(s) no longer describe "
              "a violation — delete them in the commit that fixed the pin")
        for row in stale[:12]:
            print(f"    {row['symbol']} [{row['bodies']}]")
        raise SystemExit(1)
    print(f"Pin consistency: OK ({stats['multi_pinned']} multi-pinned symbols of "
          f"{stats['names']}; {len(violations)} baselined, 0 new, 0 stale; "
          f"{stats['routes']} route= row(s) re-derived from the image)")
    verify_import_pins()
    verify_dir32_pins(scanner)
    # Live counts for what this gate does not cover (the preamble quotes none).
    known = {v["symbol"] for v in violations}
    candidates = sum(name not in known
                     for name in candidate_violations(scanner, candidate_lists()))
    print(f"Pin coverage: {stats['single_pinned']} of {stats['names']} symbols pin a single "
          f"address (one-name-one-body never compares them); {candidates} more "
          "candidate-list violation(s) (`--candidates`; `--delta` refuses new ones)")


# --------------------------------------------------------------------------
# Delta gates: no NEW debt on the two surfaces the baseline does not cover.
# Approved by the project lead 2026-10-16 (pin-candidate decision).
# --------------------------------------------------------------------------
#
# The --candidates violations and one-address-many-names were reported, never
# gated, because gating either the baseline way means recording the existing
# debt, and baselines may only shrink. A DELTA needs no record: judge the
# ledger on both sides of a diff and refuse only what the new side adds.
# Existing debt never blocks a commit; fixing it always passes.
#
# Only the new side is parsed. The base side is the new side with the diff
# undone (git diff -U0 of the two ledgers), applied to the few addresses and
# names the diff touches, which keeps a hook run near one --check.

FUNCTIONS_REL = "targets/game/reverse/functions.csv"
SYMBOLS_REL = "targets/game/reverse/symbols.csv"
EVIDENCE_REL = "targets/game/reverse/identity_evidence"
FUNCTION_FIELDS = ["name", "export_rva", "target_rva", "target_size", "source", "status", "notes"]
PIN_FIELDS = ["name", "address", "notes"]

# A placeholder that spells its own address claims no identity: the compat pin
# a frozen gen caller needs (owner ruling 2026-10-15), an ILT `?j_`, a `?b_`
# call pin, a `?dup_` twin -- only when the spelled address IS the pinned one.
SELF_ADDRESSED = re.compile(r"^\?(?:[abdj]|dup)_([0-9A-Fa-f]{6,8})@@")

# The machine-checkable override for an added pin or row the identity check
# refuses: a line in a committed targets/game/reverse/identity_evidence/ file
# that names the exact (name, address) and gives the proof, e.g.
#   pin-identity-override: ??1Foo@@QAE@XZ 0x0001A2B3 caller=0x00123450 <why>
# Only a line the judged diff ADDS counts, the commit must carry a matching
# `Identity-Override: <name> 0x<address>` trailer (tools/protected_paths.py),
# and the cited caller is verified (verify_override). It never overrides a
# candidate-list violation, an ILT contradiction or a pin inside a body.
OVERRIDE_RE = re.compile(
    r"^[ \t]*pin-identity-override:[ \t]*(\S+)[ \t]+0x([0-9A-Fa-f]{1,8})[ \t]+(\S[^\n]{11,})$",
    re.MULTILINE)


def _git_text(*args, ok=(0,)):
    import subprocess
    done = subprocess.run(["git", *args], capture_output=True, cwd=ROOT)
    if done.returncode not in ok:
        raise SystemExit(f"pin_consistency: git {' '.join(args)} failed: "
                         f"{done.stderr.decode('utf-8', 'replace').strip()}")
    return done.stdout.decode("utf-8")


def _read_side(ref, rel):
    """REL on a delta's new side: None = working tree, ':' = index, else a commit."""
    if ref is None:
        return (ROOT / rel).read_text(encoding="utf-8")
    return _git_text("show", f"{ref}:{rel}" if ref != ":" else f":{rel}")


def _diff_sides(base_ref, new_ref):
    """`git diff` arguments for BASE against the new side, literal: no rename
    pairing, no external diff, no textconv filter."""
    literal = ["-U0", "--no-color", "--no-renames", "--no-ext-diff", "--no-textconv"]
    if new_ref is None:
        return literal + [base_ref]
    if new_ref == ":":
        return literal + ["--cached", base_ref]
    return literal + [base_ref, new_ref]


def diff_rows(base_ref, new_ref, rel, fields):
    """(removed, added) ledger rows between BASE and the new side, as dicts.

    A -U0 diff's -/+ lines are whole rows only while every record is one
    line, so a record that spans lines (a quoted newline) fails closed rather
    than being judged in pieces. --no-renames and --no-ext-diff keep the diff
    literal. Lines split exactly where csv on the full file splits them (a bare
    CR included), so the derived base side parses like a full read would.
    """
    text = _git_text("diff", *_diff_sides(base_ref, new_ref), "--", rel)
    side = {"+": [], "-": []}
    for line in text.splitlines():
        if line[:1] in side and not line.startswith(("+++ ", "--- ")):
            side[line[0]].append(line[1:].rstrip("\r"))
    def parse(lines):
        records = list(csv.reader(io.StringIO("\n".join(lines), newline="")))
        if len(records) != len(lines):
            raise SystemExit(f"pin_consistency: a {rel} record in the diff {base_ref}.."
                             f"{new_ref or 'worktree'} spans lines; the delta cannot judge it")
        return [_norm(dict(zip(fields, rec)) | ({None: rec[len(fields):]}
                                                if len(rec) > len(fields) else {}), fields)
                for rec in records if rec and rec[:1] != [fields[0]]]
    return parse(side["-"]), parse(side["+"])


def _norm(row, fields):
    """ROW as {field: text} plus `_overflow`, the fields an unquoted comma split
    off. `notes` stays the first notes field, as csv.DictReader (build, --check,
    load_routes) reads it; `joined()` is notes plus overflow, as abi_view reads it.
    One parser for both sides of a delta, so a route= past a stray comma is read
    the same way everywhere."""
    out = {field: row.get(field) or "" for field in fields}
    out["_overflow"] = ",".join(row.get(None) or ())
    return out


def joined(row):
    """The notes as tools/abi_view.py reads them: every field after the second."""
    return row["notes"] + ("," + row["_overflow"] if row.get("_overflow") else "")


def pin_exemption(row):
    """'view', 'route' or None for a normalised symbols.csv row, read exactly as
    --check reads it: abi-view= over the joined notes (abi_view.view_rows),
    route= over the first notes field (load_routes)."""
    import abi_view
    if abi_view.is_view(joined(row)):
        return "view"
    if ROUTE_RE.search(row["notes"]):
        return "route"
    return None


def _rva(row, column):
    return int(row[column], 16)


def _multiset_minus(rows, minus, fields):
    """ROWS without one occurrence of each row in MINUS (compared field by field)."""
    key_of_row = lambda row: tuple(_norm(row, fields).values())
    left = collections.Counter(key_of_row(r) for r in minus)
    out = []
    for row in rows:
        key = key_of_row(row)
        if left[key]:
            left[key] -= 1
            continue
        out.append(row)
    return out


class Delta:
    """Both sides of a ledger diff; the new side parsed, the base side derived."""

    def __init__(self, base_ref, new_ref=":"):
        self.base_ref, self.new_ref = base_ref, new_ref
        self.new_rows = list(csv.DictReader(io.StringIO(_read_side(new_ref, FUNCTIONS_REL),
                                                        newline="")))
        import tempfile
        self._tmp = tempfile.TemporaryDirectory(prefix="pin_delta_")
        self.new_symbols = Path(self._tmp.name) / "symbols.csv"
        self.new_symbols.write_text(_read_side(new_ref, SYMBOLS_REL), encoding="utf-8",
                                    newline="")
        self.rows_removed, self.rows_added = diff_rows(base_ref, new_ref, FUNCTIONS_REL,
                                                       FUNCTION_FIELDS)
        self.pins_removed, self.pins_added = diff_rows(base_ref, new_ref, SYMBOLS_REL, PIN_FIELDS)
        self._group()

    def _group(self):
        """Index the diff by address and by name (a mass diff must stay linear)."""
        self.changed = {_rva(r, "target_rva") for r in self.rows_removed + self.rows_added}
        self._by = {}
        for label, rows, key in (("rows+", self.rows_added, "rva"), ("rows-", self.rows_removed, "rva"),
                                 ("rows+n", self.rows_added, "name"),
                                 ("rows-n", self.rows_removed, "name"),
                                 ("pins+", self.pins_added, "name"),
                                 ("pins-", self.pins_removed, "name")):
            table = self._by[label] = collections.defaultdict(list)
            for r in rows:
                table[_rva(r, "target_rva") if key == "rva" else r["name"]].append(r)

    def close(self):
        self._tmp.cleanup()

    # -- the base side, at the addresses and names the diff touches ---------
    def base_rows_at(self, rvas):
        """rva -> the base side's functions.csv rows, for RVAS."""
        out = collections.defaultdict(list)
        for row in self.new_rows:
            rva = _rva(row, "target_rva")
            if rva in rvas:
                out[rva].append(row)
        for rva in set(rvas):
            here = _multiset_minus(out.get(rva, []), self._by["rows+"].get(rva, ()),
                                   FUNCTION_FIELDS)
            out[rva] = here + self._by["rows-"].get(rva, [])
        return out

    def base_scanner(self, new_scanner):
        """new_scanner with the diff's rows undone; the image is shared, not re-read."""
        base = Scanner.__new__(Scanner)
        base.rows = None
        base.ghidra, base.derived = new_scanner.ghidra, new_scanner.derived
        base.ledger_sizes = collections.defaultdict(dict, new_scanner.ledger_sizes)
        base.ledger_matched = collections.defaultdict(dict, new_scanner.ledger_matched)
        base.identities = collections.defaultdict(set, new_scanner.identities)
        for rva, rows in self.base_rows_at(self.changed).items():
            sizes, matched, identities = load_ledger(rows)
            for table, part in ((base.ledger_sizes, sizes), (base.ledger_matched, matched),
                                (base.identities, identities)):
                table.pop(rva, None)
                if part.get(rva):
                    table[rva] = part[rva]
        image = Image.__new__(Image)
        image.__dict__.update(new_scanner.image.__dict__)
        image.ledger_sizes, image._cache = base.ledger_sizes, {}
        base.image = image
        base._extents = sorted((rva, size, members[0])
                               for rva, entry in base.ledger_matched.items()
                               for size, members in entry.items())
        base._starts = [rva for rva, _size, _name in base._extents]
        base._widest = max((size for _rva, size, _name in base._extents), default=0)
        return base

    def touched_names(self):
        return ({r["name"] for r in self.rows_removed + self.rows_added}
                | {r["name"] for r in self.pins_removed + self.pins_added})

    def base_candidates(self, names):
        """name -> the base side's candidate SET, for NAMES (what candidate_lists would give)."""
        rows = collections.defaultdict(list)
        for row in self.new_rows:
            if row["name"] in names:
                rows[row["name"]].append(row)
        pins = collections.defaultdict(list)
        with self.new_symbols.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                if row["name"] in names:
                    pins[row["name"]].append(_norm(row, PIN_FIELDS))
        out = {}
        for name in names:
            here = _multiset_minus(rows.get(name, []), self._by["rows+n"].get(name, ()),
                                   FUNCTION_FIELDS)
            here += self._by["rows-n"].get(name, [])
            pinned = _multiset_minus(pins.get(name, []), self._by["pins+"].get(name, ()),
                                     PIN_FIELDS)
            pinned += self._by["pins-"].get(name, [])
            found = {_rva(r, "target_rva") for r in here}
            for pin in pinned:
                if pin_exemption(pin) != "route":
                    found.add(int(pin["address"], 16))
            out[name] = found
        return out

    def new_pin_rows(self):
        """Every new-side symbols.csv row, normalised (_norm), read once."""
        if not hasattr(self, "_new_pins"):
            with self.new_symbols.open("r", encoding="utf-8", newline="") as handle:
                self._new_pins = [_norm(row, PIN_FIELDS) for row in csv.DictReader(handle)]
        return self._new_pins

    def added_identity_rows(self):
        def ids(rows):
            return {(r["name"], _rva(r, "target_rva")) for r in rows if names_identity(r)}
        return ids(self.rows_added) - ids(self.rows_removed)


def candidate_violations(scanner, lists, names=None):
    """name -> violation over the resolver's candidate lists (all of NAMES, or every name)."""
    out = {}
    for name in sorted(lists if names is None else names):
        addresses = list(lists.get(name, ()))
        if len(addresses) < 2:
            continue
        found = scanner.inspect(name, addresses)
        if found:
            out[name] = found
    return out


def new_candidate_debt(delta_, base_scanner, new_scanner, new_lists):
    """Violations on the new side that the base side did not already carry.

    Inspected: names whose candidate set the diff changed, and names with a
    candidate whose new-side thunk walk touches an address whose ledger claim
    changed (the base walk is identical up to the first such address, so a
    walk that touches none is the same walk on both sides, with the same
    extent at its end). A violation is OLD when the base carried one for the
    same name over a superset of its bodies, so dropping one bad address from
    a three-body violation passes and any new body is new debt.
    """
    touched = delta_.touched_names()
    base_sets = delta_.base_candidates(touched)
    affected = {name for name in touched
                if set(new_lists.get(name, ())) != base_sets[name]}
    for name, addresses in new_lists.items():
        if name in affected or len(addresses) < 2:
            continue
        if any(set(new_scanner.image.resolve(a)[1]) & delta_.changed for a in addresses):
            affected.add(name)
            base_sets.setdefault(name, set(addresses))
    after = candidate_violations(new_scanner, new_lists, affected)
    before = candidate_violations(base_scanner, {n: sorted(base_sets[n]) for n in after}, set(after))
    fresh = [v for name, v in sorted(after.items())
             if not (name in before and set(v["bodies"]) <= set(before[name]["bodies"]))]
    return fresh, len(affected)


def _is_ilt_slot(oracle, rva):
    """Is RVA one of retail's incremental-link thunks (ilt_windows.tsv's table)?"""
    slot, rest = divmod(rva - (oracle.first_thunk - 0x400000), 5)
    return rest == 0 and 0 <= slot < len(oracle.target)


def _self_addressed(row):
    spelled = SELF_ADDRESSED.match(row["name"])
    return bool(spelled) and int(spelled.group(1), 16) == int(row["address"], 16)


@functools.lru_cache(maxsize=None)
def _pin_class(name, address, notes, overflow):
    """'identity', 'alias' or None (route/view/self-addressed) for one pin; both
    sides of a delta share most pins, so each is classified once."""
    row = {"name": name, "address": f"0x{address:08X}", "notes": notes, "_overflow": overflow}
    if _counts_as_identity(row):
        return "identity"
    if not pin_exemption(row) and not _self_addressed(row):
        return "alias"
    return None


def _counts_as_identity(row):
    """Does this normalised pin assert WHICH function lives where it leads?

    A route= or abi-view= row does not (it is a call encoding or a compilation
    view), nor a placeholder spelling its own address (a compat pin), nor any
    other placeholder or invented stand-in (ilt_oracle.tier): those are honest
    "unknown" names. A real decorated name does, row or pin alike.
    """
    if pin_exemption(row):
        return False
    spelled = SELF_ADDRESSED.match(row["name"])
    if spelled and int(spelled.group(1), 16) == int(row["address"], 16):
        return False
    return not alias_spelling(row["name"], int(row["address"], 16))


class Identities:
    """One side's identities, keyed by the body each names.

    A name is an identity of the body its address LEADS to: through ILT slots,
    stopping at the first hop that is not a slot (past it a 5-byte body
    tail-jumps into ANOTHER function, e.g. a pair destructor into the shared
    string release body). Sources: matched, identity-naming functions.csv rows
    (`?j_` thunk rows excluded) and real-name symbols.csv pins (see
    _counts_as_identity) -- a pin-only name is as much a claim as a row.

    Rows and pins with an ALIAS spelling (alias_spelling: placeholder or
    invented, judged on the function's own components) are no identity: a
    real name landing where only aliases stand is an identification, not a
    second spelling. They are kept in `aliases` so the caller can list the
    ones a real name displaces (option (a), pending the project lead's
    approval; the coordinator's decision 2026-10-16).
    """

    def __init__(self, scanner, pin_rows, oracle):
        self.scanner, self.oracle = scanner, oracle
        self._walks = {}
        self.names = collections.defaultdict(lambda: collections.defaultdict(set))
        self.aliases = collections.defaultdict(lambda: collections.defaultdict(set))
        for rva, names in scanner.identities.items():
            for name in names:
                if name.startswith("?j_"):
                    continue
                table = self.aliases if alias_spelling(name, rva) else self.names
                table[self.body_of(rva)][name].add(("row", rva))
        for row in pin_rows:
            address = int(row["address"], 16)
            if not scanner.image.in_text(address):
                continue
            kind = _pin_class(row["name"], address, row["notes"], row.get("_overflow") or "")
            if kind == "identity":
                self.names[self.body_of(address)][row["name"]].add(("pin", address))
            elif kind == "alias":
                self.aliases[self.body_of(address)][row["name"]].add(("pin", address))

    def walk(self, address):
        """The hops from ADDRESS to the body it names (see the class docstring)."""
        found = self._walks.get(address)
        if found is None:
            found = []
            if not _is_ilt_slot(self.oracle, address):
                found = [address]       # not a slot: it names itself
            else:
                for hop in self.scanner.image.resolve(address)[1]:
                    found.append(hop)
                    if not _is_ilt_slot(self.oracle, hop):
                        break
            self._walks[address] = found
        return found

    def body_of(self, address):
        return self.walk(address)[-1]

    def at(self, body, excluding=None):
        """{name} naming BODY, without the one source EXCLUDING=(name, (kind, address))."""
        out = set()
        for name, sources in self.names.get(body, {}).items():
            if excluding and name == excluding[0]:
                sources = sources - {excluding[1]}
            if sources:
                out.add(name)
        return out


def _judge_pin(name, address, here, oracle):
    """(kind, why) when a pin NAME at ADDRESS conflicts with the names HERE
    (the other identities of the body it names), else None."""
    import ilt_oracle
    real = not alias_spelling(name, address)
    if real:
        verdict, _p, why = oracle.check(name, address)
        if verdict == ilt_oracle.CONTRADICTED:
            return "ilt-contradicted", why
    if name in here or not here:
        return None
    if real and verdict == ilt_oracle.CONFIRMED:
        # The ILT window fits ~2.5e-4 of names, so a signature variant of the
        # real owner can be salted to fit. CONFIRMED wins only over names that
        # are no claim (placeholders) or that the same slot refutes.
        rivals = sorted(o for o in here if not alias_spelling(o, address)
                        and oracle.check(o, address)[0] != ilt_oracle.CONTRADICTED)
        if not rivals:
            return None
        return "pin-on-other-identity", ("ILT CONFIRMED, but the body already carries the real "
                                         "name(s) " + ", ".join(rivals))
    return "pin-on-other-identity", "the body already carries " + ", ".join(sorted(here))


def _key(row):
    return row["name"], int(row["address"], 16)


def _show_walk(identities, address):
    return " -> ".join(f"0x{hop:08X}" for hop in identities.walk(address))


# An alias is a placeholder or invented spelling of the function's OWN class
# or method token (the lead's confirmed policy, 2026-10-16): Rva/rva + 6-8 hex
# (Rva8CD130String keeps its six), an address-shaped 0[01]xxxxxx run, the
# ?a_/?b_/?d_/?dup_/?j_ + hex stand-ins, the generator prefixes Gen_/Gen<hex>/
# FUN_/sub_/tg_ at a token start, $L/$S labels, and Bfme* inventions. A bare
# hex-ish run (?InitDecade123Windows) is not one, nor is an anonymous
# namespace scope (?A0x3f2a1b2c).
_BOUNDARY = r"(?:^|(?<=[@?$])|(?<=[@?$][UV])|(?<=W4))"
ALIAS_TOKEN = re.compile(r"[Rr]va[0-9A-Fa-f]{6,8}"
                         r"|(?<![0-9A-Fa-f])0[01][0-9A-Fa-f]{6}|0[01][0-9A-Fa-f]{6}(?![0-9A-Fa-f])"
                         + "|" + _BOUNDARY + r"(?:[abdj]|dup)_[0-9A-Fa-f]{5,8}"
                         + "|" + _BOUNDARY + r"(?:Gen_|Gen[0-9A-Fa-f]{6}|FUN_|sub_|tg_)|^\$[LS]")
INVENTED_TOKEN = re.compile(r"bfme", re.IGNORECASE)
# Every alias rule needs one of these somewhere in the name (a 5+ hex run, a
# generator or Bfme token, a $L/$S label): a cheap screen before the decode.
ALIAS_HINT = re.compile(r"[0-9A-Fa-f]{5,}|bfme|Gen|FUN_|sub_|tg_|^\$[LS]", re.IGNORECASE)
# A 5-8 digit hex run at the end of a token or before a capital letter
# (Open2Rec3A4420, query1A6320, ParsePath8C4DA0, RvaA2160Offset8Getter) is
# address-derived when its value is a known start: a functions.csv row, a
# Ghidra function, an ILT slot, or the row's own RVA.
HEX_TAIL = re.compile(r"[0-9A-Fa-f]{5,}(?=$|[A-Z@?$])")


# The ledger rows the gate judges (set_alias_context), so the known-start set
# and the vendored names follow the --new side, not whatever is checked out.
_ALIAS_CONTEXT = {"row_starts": None, "vendored": frozenset()}
# A D3D surface format spelled in a name (A32B32G32R32F, X8R8G8B8, R5G6B5,
# G16R16): channel letters with bit counts, starting at a non-hex boundary.
D3D_FORMAT = re.compile(r"(?<![0-9A-Fa-f])(?:[ARGBXLPUVWQ][0-9]{1,2}){2,}F?(?![0-9A-Fa-f])")


def set_alias_context(rows, pin_rows=()):
    """Judge alias spellings against these ledger rows (and pins): their starts
    feed known_starts, and their vendored= names keep their real spellings."""
    starts = set()
    vendored = set()
    for row in rows:
        try:
            starts.add(int(row["target_rva"], 16))
        except (KeyError, TypeError, ValueError):
            pass
        if "vendored=" in (row.get("notes") or ""):
            vendored.add(row["name"])
    for row in pin_rows:
        if "vendored=" in joined(row) if "_overflow" in row else "vendored=" in (row.get("notes") or ""):
            vendored.add(row["name"])
    _ALIAS_CONTEXT["row_starts"] = frozenset(starts)
    _ALIAS_CONTEXT["vendored"] = frozenset(vendored)
    _ALIAS_CONTEXT["known"] = None
    alias_spelling.cache_clear()
    _pin_class.cache_clear()


def _fixed_starts():
    """Ghidra function and ILT slot starts: fixed for the baseline, so cached on
    disk keyed on those files' mtime and size."""
    import pickle
    import ilt_oracle
    ghidra = ROOT / "targets/game/reverse/ghidra_functions.csv"
    windows = ilt_oracle.WINDOWS
    key = tuple((str(p), p.stat().st_mtime_ns, p.stat().st_size) for p in (ghidra, windows))
    cache = ROOT / "build" / ".cache" / "pin_known_starts.pickle"
    if _FIXED.get("key") == key:
        return _FIXED["starts"]
    try:
        with cache.open("rb") as handle:
            stored = pickle.load(handle)
        if stored.get("key") == key:
            _FIXED.update(stored)
            return stored["starts"]
    except (OSError, EOFError, pickle.UnpicklingError, AttributeError):
        pass
    starts = set()
    with ghidra.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            try:
                starts.add(int(row["rva"], 16))
            except (KeyError, TypeError, ValueError):
                continue
    oracle = ilt_oracle.oracle()
    first = oracle.first_thunk - 0x400000
    starts.update(first + 5 * slot for slot in range(len(oracle.target)))
    stored = {"key": key, "starts": frozenset(starts)}
    _FIXED.update(stored)
    try:
        cache.parent.mkdir(parents=True, exist_ok=True)
        with cache.open("wb") as handle:
            pickle.dump(stored, handle)
    except OSError:
        pass
    return stored["starts"]


_FIXED = {}


def _row_starts():
    if _ALIAS_CONTEXT["row_starts"] is None:
        set_alias_context(build.load_all_function_rows())
    return _ALIAS_CONTEXT["row_starts"]


def known_starts():
    """{rva} of every ledger row (the judged side's, set_alias_context), Ghidra
    function and ILT slot."""
    if _ALIAS_CONTEXT.get("known") is None:
        _ALIAS_CONTEXT["known"] = _fixed_starts() | _row_starts()
    return _ALIAS_CONTEXT["known"]


def _address_tail(own, address):
    starts = None
    for match in HEX_TAIL.finditer(own):
        # D3D format names (A32B32G32R32F, X8R8G8B8) are hex-shaped words.
        if any(f.start() <= match.end() and match.start() <= f.end()
               for f in D3D_FORMAT.finditer(own)):
            continue
        run = match.group(0)
        for width in range(5, min(8, len(run)) + 1):
            value = int(run[-width:], 16)
            if value == address:
                return True
            if starts is None:
                starts = known_starts()
            if value in starts:
                return True
    return False


def _vendored(name):
    """Fallback outside a delta: is NAME a vendored row in the checkout's ledger?"""
    _row_starts()
    return name in _ALIAS_CONTEXT["vendored"]


def own_components(name):
    """The function's own method token plus its class scopes (a CLASS's template
    arguments included, a member template's own arguments not), as text."""
    import abi_view
    prefix = abi_view.qualified_prefix(name)
    try:
        if name.startswith("??$"):
            end = abi_view.Decode(name).template_name(3)
            method = name[3:name.index("@", 3)]
            scopes = prefix[end:] if prefix else name[end:name.index("@@", end)]
            return method + "@" + scopes
        if name.startswith("??"):
            op = name[:4] if name[2] == "_" else name[:3]
            scopes = prefix[len(op):] if prefix else name[len(op):name.index("@@", len(op))]
            return op + "@" + scopes
        if name.startswith("?"):
            text = prefix or name[:name.index("@@") + 2]
            return text[1:]
    except (ValueError, IndexError):
        pass
    return name


@functools.lru_cache(maxsize=None)
def alias_spelling(name, address=None):
    """Is NAME an alias: does the function's OWN class or method token carry a
    placeholder or invented spelling (ALIAS_TOKEN / INVENTED_TOKEN, applied to
    own_components)? A placeholder PARAMETER type, or a member template's own
    argument, does not make a real Class::method an alias:
    ?calculate@PartitionManagerImpl@@QAEXPAUGen009F5040Node@@PAH11@Z and
    ??$InitializeAppWindows@URva0005F2B0@@@WinMainApp@@QAEXXZ are real claims;
    ??1?$pair@$$CBVAsciiString@@W4Rva001360E0Mapped@@@_STL@@QAE@XZ is an alias
    (its class's own argument is a placeholder)."""
    if not ALIAS_HINT.search(name):
        return False                    # no token any rule below could match: skip the decode
    own = own_components(name)
    if ALIAS_TOKEN.search(own) or INVENTED_TOKEN.search(own):
        return True
    # A vendored library's own name is real however hex-shaped (D3DX's
    # CCodec_A32B32G32R32F); the known-start rule never reads it.
    if name in _ALIAS_CONTEXT["vendored"] or (_ALIAS_CONTEXT["row_starts"] is None and _vendored(name)):
        return False
    return _address_tail(own, address)


def new_identity_conflicts(delta_, new_scanner, base_scanner, oracle, warnings=None):
    """[(kind, name, address, why)]: identity debt the diff ADDS.

    * an added pin that names a body already carrying another identity, judged
      against base and new identities together (deleting or demoting the named
      row in the same commit does not clear the way), except names a row
      REPLACED at its own address (a rename moves the identity, it does not
      add one); an ILT-CONTRADICTED real name is refused outright; CONFIRMED
      wins only over placeholder or ILT-refuted rivals (_judge_pin);
    * an added pin landing strictly inside a matched body (no function starts
      there), unless it is a route= or abi-view= row;
    * an added route= or abi-view= pin the image does not admit;
    * an existing pin with a REAL name the diff turns into a conflict it was
      not on the base side (a renamed or re-pointed row, a pin losing its
      abi-view=). The same for an alias spelling (alias_spelling: placeholder
      or invented) only WARNS, appended to WARNINGS, so landing a real row on
      a body its old stand-in pins still name does not block; those pins go
      to the pin drain (project lead 2026-10-16, option b);
    * an added identity row on a body that already carries another identity.
    """
    import abi_view
    refused = []
    new_pins = delta_.new_pin_rows()
    base_pins = _multiset_minus(new_pins, delta_.pins_added, PIN_FIELDS) + delta_.pins_removed
    new_ids = Identities(new_scanner, new_pins, oracle)
    base_ids = Identities(base_scanner, base_pins, oracle)
    # A row removed at an address where an identity row is added is a rename:
    # its old name leaves the body rather than standing beside the new one.
    renamed = {(r["name"], _rva(r, "target_rva")) for r in delta_.rows_removed
               if any(names_identity(a) for a in delta_._by["rows+"].get(_rva(r, "target_rva"), ()))}

    # A base name that names a DIFFERENT body on the new side has moved (like a
    # rename): the address it vacated is judged against the new state only.
    new_bodies = collections.defaultdict(set)
    for new_body, names in new_ids.names.items():
        for name in names:
            new_bodies[name].add(new_body)

    def union_at(body, excluding):
        out = new_ids.at(body, excluding)
        for name, sources in base_ids.names.get(body, {}).items():
            if excluding and name == excluding[0]:
                sources = sources - {excluding[1]}
            if new_bodies.get(name) and body not in new_bodies[name]:
                continue
            if any(not (kind == "row" and (name, rva) in renamed) for kind, rva in sources):
                out.add(name)
        return out

    def displaced(name, address, body, refusal_kind, here):
        """A real NAME lands where only alias rows/pins stand (no real identity:
        the caller already judged that). Over an alias ROW it needs evidence:
        retail's ILT CONFIRMS the name at ADDRESS, or the commit carries a
        verified Identity-Override (the refusal kind is OVERRIDABLE); over
        alias pins alone it passes, as alias pins never blocked. Every
        alias other than NAME itself is listed for the drain (written only when
        the whole verdict passes). Alias-on-alias passes: an alias name claims
        no identity, so it displaces nothing. Aliases the same diff deleted or
        demoted count as standing (only a row renamed in place has left).

        KNOWN LIMIT: ILT CONFIRMED means the name fits its slot's window; a
        wrong name fits with probability p_false, so a search of ~1/p_false
        (tens of thousands of) spellings finds one that "confirms". The
        CONFIRMED_P_MAX bound keeps out the widest windows only; a brute-forced
        name still passes, and only review and the override's caller proof
        stand against it."""
        import ilt_oracle
        if alias_spelling(name, address) or here:
            return None                 # a real name already stands: nothing is displaced
        aliases = [(alias, kind, at) for alias, sources in sorted(new_ids.aliases.get(body, {}).items())
                   if alias != name for kind, at in sorted(sources)]
        # Aliases the same diff deleted or demoted count too (judged against
        # base and new together, as union_at does for real names): only a row
        # renamed in place at its own address leaves the body.
        gone = [(alias, kind, at) for alias, sources in sorted(base_ids.aliases.get(body, {}).items())
                if alias != name for kind, at in sorted(sources)
                if (alias, kind, at) not in aliases and not (kind == "row" and (alias, at) in renamed)]
        if not aliases and not gone:
            return None
        if warnings is not None:
            for alias, kind, at in aliases:
                warnings.append((f"displaced-alias-{kind}", alias, at,
                                 f"{name} now names body 0x{body:08X}; this alias {kind} still "
                                 "spells it", body, name))
        # Alias PINS never blocked (option b: they warn and go to the drain);
        # evidence is demanded only where option (a) newly lets a real name
        # land, over alias ROWS.
        if not any(kind == "row" for _a, kind, _at in aliases + gone):
            return None
        verdict, p_false, _why = oracle.check(name, address)
        # The window fits a wrong name with probability p_false; a search of
        # ~1/p_false spellings will find one that fits (a known limit: the ILT
        # is consistent with a name, never proof of it). Demanding p < 1e-3
        # keeps the wide windows out; a brute-forced name still passes.
        if verdict == ilt_oracle.CONFIRMED and p_false is not None and p_false < CONFIRMED_P_MAX:
            return None
        aliases = aliases + gone
        return (refusal_kind, name, address,
                f"only alias spellings name body 0x{body:08X} ("
                + ", ".join(sorted({a for a, _k, _at in aliases})[:4])
                + f"); a real name displaces them only when retail's ILT CONFIRMS it there with "
                  f"p_false < {CONFIRMED_P_MAX:g} (here {verdict}"
                + (f", p_false {p_false:.2e}" if p_false is not None else "")
                + ") or with a verified Identity-Override: a `pin-identity-override: <name> "
                  "0x<address> caller=0x<rva> <why>` line added to an identity_evidence/ file and an "
                  "`Identity-Override: <name> 0x<address>` trailer, where the caller's object (built "
                  "in this commit) carries a REL32 naming this exact symbol at its call to the address")

    removed_keys = {_key(r) for r in delta_.pins_removed}
    base_by_key = {_key(r): r for r in delta_.pins_removed}
    added_keys = set()
    ctx = None
    for row in sorted(delta_.pins_added, key=_key):
        name, address = _key(row)
        if (name, address) in removed_keys:
            continue                        # a notes edit, re-judged below
        added_keys.add((name, address))
        exempt = pin_exemption(row)
        if exempt == "view":
            if ctx is None:
                ctx = abi_view.Context(rows=delta_.new_rows,
                                       pins=abi_view.load_pin_addresses(delta_.new_symbols))
            canonical = abi_view.ABI_VIEW_RE.search(joined(row)).group(1).strip()
            why = abi_view.view_verdict(ctx, name, address, canonical, joined(row))
            if why:
                refused.append(("abi-view", name, address, why))
            continue
        if exempt == "route":
            why = route_verdict(new_scanner, name, address,
                                ROUTE_RE.search(row["notes"]).group(1).strip())
            if why:
                refused.append(("route", name, address, why))
            continue
        if not new_scanner.image.in_text(address):
            continue                        # a data pin names no code body
        body = new_ids.body_of(address)
        inside = new_scanner.interior_of(body)
        if inside:
            refused.append(("pin-inside-body", name, address,
                            f"walk {_show_walk(new_ids, address)} lands +0x{body - inside[1]:X} "
                            f"inside {inside[0]} (0x{inside[1]:08X}, {inside[2]} bytes)"))
            continue
        spelled = SELF_ADDRESSED.match(name)
        if spelled and int(spelled.group(1), 16) == address:
            continue
        here = union_at(body, (name, ("pin", address)))
        found = _judge_pin(name, address, here, oracle)
        if found:
            refused.append((found[0], name, address,
                            f"walk {_show_walk(new_ids, address)}: {found[1]}"))
        else:
            refusal = displaced(name, address, body, "pin-on-other-identity", here)
            if refusal:
                refused.append(refusal)

    # Existing pins the diff re-points or re-labels: refuse only a conflict the
    # base side did not already have.
    for row in new_pins:
        key = _key(row)
        name, address = key
        if key in added_keys or not new_scanner.image.in_text(address):
            continue
        edited = key in removed_keys
        if not edited and not (set(new_ids.walk(address)) | set(base_ids.walk(address))) \
                & delta_.changed:
            continue
        if pin_exemption(row):
            continue
        spelled = SELF_ADDRESSED.match(name)
        if spelled and int(spelled.group(1), 16) == address:
            continue
        after = _judge_pin(name, address,
                           new_ids.at(new_ids.body_of(address), (name, ("pin", address))), oracle)
        if not after:
            continue
        before_row = base_by_key.get(key, row)
        before = None if pin_exemption(before_row) else _judge_pin(
            name, address, base_ids.at(base_ids.body_of(address), (name, ("pin", address))), oracle)
        if not before:
            finding = ("existing-pin-now-conflicts", name, address,
                       f"walk {_show_walk(new_ids, address)}: {after[1]}")
            if alias_spelling(name, address) and after[0] == "pin-on-other-identity":
                if warnings is not None:
                    trigger = sorted(new_ids.at(new_ids.body_of(address), (name, ("pin", address))))
                    warnings.append(finding + (new_ids.body_of(address), trigger[0] if trigger else name))
            else:
                refused.append(finding)

    for name, address in sorted(delta_.added_identity_rows()):
        if name.startswith("?j_"):
            continue
        body = new_ids.body_of(address)
        here = union_at(body, (name, ("row", address)))
        if here and name not in here:
            refused.append(("row-on-other-identity", name, address,
                            "the body already carries " + ", ".join(sorted(here))))
        else:
            refusal = displaced(name, address, body, "row-on-other-identity", here)
            if refusal:
                refused.append(refusal)
    return refused


CONFIRMED_P_MAX = 1e-3          # displacing alias rows: the ILT fit must be narrower than this


OVERRIDABLE = ("pin-on-other-identity", "row-on-other-identity", "existing-pin-now-conflicts")
OVERRIDE_CALLER_RE = re.compile(r"\bcaller=0x([0-9A-Fa-f]{1,8})\b")


def added_overrides(base_ref, new_ref):
    """[(name, address, reason)] of override lines the diff ADDS to identity_evidence/.
    A line already committed overrides nothing: an override is spent with the
    commit that cites it."""
    text = _git_text("diff", *_diff_sides(base_ref, new_ref), "--", EVIDENCE_REL)
    added = "\n".join(line[1:] for line in text.replace("\r", "").splitlines()
                      if line.startswith("+") and not line.startswith("+++ "))
    return [(name, int(address, 16), reason.strip())
            for name, address, reason in OVERRIDE_RE.findall(added)]


CALLER_NOT_EVIDENCE = ("game/gen_small/", "game/gen_asm/", "game/masm_dumps/")


def verify_override(scanner, new_ref, name, address, reason):
    """None when an override's cited fact checks out, else why not.

    The reason must cite `caller=0x<rva>`: the start of exactly one matched,
    hand-written C++ row (game/**.cpp, not gen_small/gen_asm/masm_dumps, no
    gen- note) whose retail bytes call or jump to ADDRESS (E8/E9 rel32), and
    whose COMPILED OBJECT, current with its source, carries at that site a
    REL32 relocation naming exactly NAME -- one_identity.caller_names's test.
    A word in the source (a comment, another class's member) proves nothing.
    """
    import delta_sources
    cited = OVERRIDE_CALLER_RE.search(reason)
    if not cited:
        return "the reason cites no caller=0x<rva>"
    caller = int(cited.group(1), 16)
    rows = [r for r in (scanner.rows if scanner.rows is not None else build.load_all_function_rows())
            if r["status"] == "matched" and int(r["target_rva"], 16) == caller
            and r["source"].startswith("game/") and r["source"].endswith(".cpp")
            and not r["source"].startswith(CALLER_NOT_EVIDENCE)
            and not progress.GEN_NOTE_RE.search(r["notes"] or "")]
    if len(rows) != 1:
        return (f"0x{caller:08X} is not the start of exactly one matched hand-written C++ row "
                "(generated, gen- noted and masm_dumps rows name whatever the ledger said)")
    row, size = rows[0], int(rows[0]["target_size"])
    code = build.read_target_bytes(caller, size)
    sites = [i for i in range(len(code) - 4) if code[i] in (0xE8, 0xE9)
             and caller + i + 5 + struct.unpack_from("<i", code, i + 1)[0] == address]
    if not sites:
        return f"{row['name']} (0x{caller:08X}, {size} bytes) has no E8/E9 to 0x{address:08X}"
    obj = build.row_object(row)
    if not obj.exists() or not delta_sources.object_is_current(ROOT / row["source"], obj):
        return f"the caller's object for {row['source']} is missing or stale; build it first"
    defined, rel32 = delta_sources.object_rel32(obj)
    placed = defined.get(build.ledger_object_symbol(row))
    if placed is None:
        return f"{row['name']} is not defined in {obj.name}"
    named = {rel32.get((placed[0], placed[1] + i + 1)) for i in sites}
    if name not in named:
        return (f"{row['name']}'s object names {sorted(n for n in named if n) or ['nothing']} at its "
                f"call site(s) to 0x{address:08X}, not {name}")
    return None


def apply_overrides(conflicts, allowed):
    """(conflicts left, [(conflict, reason) applied]): the identity kinds an
    ALLOWED (name, address) -> reason entry names exactly."""
    left, applied = [], []
    for conflict in conflicts:
        reason = allowed.get((conflict[1], conflict[2])) if conflict[0] in OVERRIDABLE else None
        (applied if reason else left).append((conflict, reason) if reason else conflict)
    return left, applied


ALIAS_LOG_FIELDS = ["name", "address", "body", "kind", "landing", "why"]
# warnings carry (kind, name, address, why, body, trigger): trigger is the name
# that displaced the alias, used to find the commit that introduced it.


def alias_log_path():
    """BFME_PIN_ALIAS_LOG, else build/linkfleet/ds/pin_alias_cleanup.tsv in the
    MAIN checkout (the git common dir's parent), so every worktree feeds the
    one list the pin drain reads."""
    import os
    if os.environ.get("BFME_PIN_ALIAS_LOG"):
        return Path(os.environ["BFME_PIN_ALIAS_LOG"])
    common = Path(_git_text("rev-parse", "--path-format=absolute", "--git-common-dir").strip())
    return common.parent / "build" / "linkfleet" / "ds" / "pin_alias_cleanup.tsv"


def record_alias_cleanup(entries):
    """Append (name, address, body, kind, landing, why) rows to the drain list,
    once per (name, address, body), under an exclusive lock (several worktrees
    push at once). ENTRIES are (kind, name, address, why, body, landing). Any
    line still in the old five-column shape -- anywhere in the file -- gains its
    kind column (unknown); a file without a final newline gets one first."""
    from portable_lock import lock
    path = alias_log_path()
    path.parent.mkdir(parents=True, exist_ok=True)
    header = "\t".join(ALIAS_LOG_FIELDS)
    with path.with_name(path.name + ".lock").open("a+b") as lock_file:
        lock(lock_file, exclusive=True)
        lines = path.read_text(encoding="utf-8").splitlines() if path.exists() else []
        body = lines[1:] if lines and lines[0].startswith("name\t") else lines
        migrated = []
        for line in body:
            parts = line.split("\t")
            migrated.append("\t".join(parts[:3] + ["unknown"] + parts[3:]) if len(parts) == 5 else line)
        wanted = "\n".join([header] + migrated) + "\n"
        if not path.exists() or path.read_text(encoding="utf-8") != wanted:
            temp = path.with_name(path.name + ".tmp")
            temp.write_text(wanted, encoding="utf-8")
            temp.replace(path)
        seen = {tuple(line.split("\t")[:3]) for line in migrated}
        with path.open("a", encoding="utf-8", newline="") as out:
            for kind, name, address, why, body_rva, landing in entries:
                key = (name, f"0x{address:08X}", f"0x{body_rva:08X}")
                if key in seen:
                    continue
                seen.add(key)
                out.write("\t".join(key + (kind, landing, why.replace("\t", " "))) + "\n")
    return path


def pending_alias_path(sha):
    return alias_log_path().parent / "pin_alias_pending" / f"{sha}.json"


def stage_alias_cleanup(warnings, base_ref, new_ref):
    """A passing verdict on a commit range parks its alias rows as PENDING; the
    drain list gets them only from publish_alias_cleanup, which pre-push runs
    after every other check passed, so a refused push lists nothing."""
    import json
    sha = _git_text("rev-parse", new_ref).strip()
    path = pending_alias_path(sha)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps({"base": _git_text("rev-parse", base_ref).strip(), "tip": sha,
                                "warnings": [list(w) for w in warnings]}), encoding="utf-8")
    return path


def introducing_commit(base, tip, trigger):
    """The first commit in BASE..TIP whose ledger diff adds TRIGGER (the name
    that displaced the alias), else TIP: the drain list names who introduced it."""
    found = _git_text("log", "--reverse", "--format=%h", "--abbrev=10", f"-S{trigger}",
                      f"{base}..{tip}", "--", FUNCTIONS_REL, SYMBOLS_REL, ok=(0, 128)).split()
    return found[0] if found else _git_text("rev-parse", "--short=10", tip).strip()


def publish_alias_cleanup(sha):
    """pre-push, last step: move SHA's pending alias rows into the drain list."""
    import json
    sha = _git_text("rev-parse", sha).strip()
    path = pending_alias_path(sha)
    if not path.exists():
        return 0
    staged = json.loads(path.read_text(encoding="utf-8"))
    entries = [(kind, name, address, why, body_rva,
                introducing_commit(staged["base"], staged["tip"], trigger))
               for kind, name, address, why, body_rva, trigger in staged["warnings"]]
    log = record_alias_cleanup(entries)
    path.unlink()
    print(f"Pin delta: {len(entries)} alias row(s)/pin(s) listed in {log}")
    return len(entries)


def delta(base_ref, new_ref=":"):
    """The delta gate. Prints its verdict; raises SystemExit(1) on new debt."""
    import time
    import ilt_oracle
    started = time.monotonic()
    work = Delta(base_ref, new_ref)
    applied, rejected = [], []
    try:
        if not (work.rows_removed or work.rows_added or work.pins_removed or work.pins_added):
            print(f"Pin delta: OK (no functions.csv/symbols.csv change vs {base_ref})")
            return
        set_alias_context(work.new_rows, work.new_pin_rows())
        new_scanner = Scanner(work.new_rows)
        base_scanner = work.base_scanner(new_scanner)
        new_lists = candidate_lists(work.new_rows, work.new_symbols)
        debt, affected = new_candidate_debt(work, base_scanner, new_scanner, new_lists)
        warnings = []
        conflicts = new_identity_conflicts(work, new_scanner, base_scanner, ilt_oracle.oracle(),
                                           warnings)
        if any(kind in OVERRIDABLE for kind, *_rest in conflicts):
            allowed = {}
            for name, address, reason in added_overrides(base_ref, new_ref):
                why = verify_override(new_scanner, new_ref, name, address, reason)
                if why:
                    rejected.append((name, address, why))
                else:
                    allowed[(name, address)] = reason
            conflicts, applied = apply_overrides(conflicts, allowed)
    finally:
        work.close()
    took = time.monotonic() - started
    for kind, name, address, why, _body, _trigger in warnings:
        what = kind.replace("displaced-", "") if kind.startswith("displaced-") else "alias pin"
        print(f"Pin delta: WARNING {what} {name} 0x{address:08X}: {why}; not blocking, "
              "listed for the pin drain")
    if warnings and not (debt or conflicts) and new_ref not in (None, ":"):
        # The drain list records what LANDED: a passing verdict on a commit is
        # parked as pending; pre-push publishes it after its last check
        # (--publish-alias-log), never for a refused verdict, an index, or a
        # push some later check stopped.
        staged = stage_alias_cleanup(warnings, base_ref, new_ref)
        print(f"Pin delta: {len(warnings)} alias row(s)/pin(s) pending in {staged}")
    for (kind, name, address, _why), reason in applied:
        print(f"Pin delta: override applied [{kind}] {name} 0x{address:08X}: {reason}")
    for name, address, why in rejected:
        print(f"Pin delta: override NOT applied for {name} 0x{address:08X}: {why}")
    if debt or conflicts:
        if debt:
            print(f"Pin delta: FAIL {len(debt)} NEW candidate-list violation(s) vs {base_ref} "
                  "(one name, resolver candidates that are not one function)")
            for violation in debt[:12]:
                print(f"    {violation['symbol']}")
                print(f"        {violation['kind']}: {violation['evidence']}")
        if conflicts:
            print(f"Pin delta: FAIL {len(conflicts)} pin(s)/row(s) name a body that already "
                  "carries a different identity, or that retail's ILT contradicts")
            for kind, name, address, why in conflicts[:12]:
                print(f"    [{kind}] {name} 0x{address:08X}")
                print(f"        {why}")
            print("    Pin the body the name really is, keep an address-derived name, or use an "
                  "abi-view=/route= row the image admits (tools/pin_consistency.py, \"WHAT THIS "
                  "DOES NOT CATCH\").")
        print("    Existing debt never blocks; this diff ADDS the lines above. "
              "Do not record them anywhere to go green.")
        raise SystemExit(1)
    print(f"Pin delta: OK (0 new candidate-list violations over {affected} affected name(s), "
          f"0 identity conflicts; {len(work.changed)} changed address(es) vs {base_ref}; "
          f"{took:.1f}s)")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--check", action="store_true",
                        help="gate mode: fail on any violation not in the baseline")
    parser.add_argument("--write-baseline", action="store_true",
                        help="regenerate targets/game/reverse/pin_consistency_baseline.csv (may only DROP lines)")
    parser.add_argument("--seed-baseline", action="store_true",
                        help="create a baseline for a surface that has none (refuses to overwrite)")
    parser.add_argument("--assert-shrink-only", metavar="REF", nargs="?", const="HEAD",
                        help="fail if the baseline adds any key vs REF (default HEAD); the hooks' check")
    parser.add_argument("--at", metavar="REF",
                        help="with --assert-shrink-only: judge the baseline at REF instead of the working tree")
    parser.add_argument("--symbol", help="report one symbol in full and exit")
    parser.add_argument("--candidates", action="store_true",
                        help="apply the invariant to the resolver's REAL candidate list "
                             "(functions.csv rows + symbols.csv pins), not the pins alone")
    parser.add_argument("--publish-alias-log", metavar="SHA",
                        help="pre-push, last step: list SHA's pending alias rows in the drain list")
    parser.add_argument("--delta", metavar="BASE",
                        help="gate the diff BASE -> --new (default: the index): refuse NEW "
                             "candidate-list violations and pins/rows on another identity")
    parser.add_argument("--new", metavar="REF", default=":",
                        help="with --delta: the new side, a commit, ':' (index, default) or 'worktree'")
    parser.add_argument("--routes", action="store_true",
                        help="report every route= row and re-derive it from the retail image")
    parser.add_argument("--clear-cut", action="store_true",
                        help="candidates a byte-verified ledger row settles — each still needs caller confirmation")
    args = parser.parse_args(argv)

    if args.assert_shrink_only:
        assert_shrink_only(args.assert_shrink_only, args.at)
        return 0

    if args.publish_alias_log:
        publish_alias_cleanup(args.publish_alias_log)
        return 0
    if args.delta:
        delta(args.delta, None if args.new == "worktree" else args.new)
        return 0

    if args.routes:
        scanner = Scanner()
        routes = load_routes()
        for (name, address), claim in sorted(routes.items()):
            why = route_verdict(scanner, name, address, claim)
            print(f"{name} 0x{address:08X} route={claim}: " + (why or "admissible"))
        print(f"{verify_routes(scanner, routes)} route= row(s), all admissible")
        return 0

    if args.symbol:
        scanner = Scanner()
        pins = load_pins().get(args.symbol)
        if not pins:
            raise SystemExit(f"pin_consistency: {args.symbol} has no targets/game/reverse/symbols.csv pin")
        routes = load_routes()
        print(f"{args.symbol}: " + " ".join(f"0x{p:08X}" for p in pins))
        for pin in pins:
            body, chain = scanner.image.resolve(pin)
            size, provenance = scanner.extent(body)
            claim = routes.get((args.symbol, pin))
            print("    " + " -> ".join(f"0x{x:08X}" for x in chain) +
                  f"  extent={size} ({provenance})  owned-by={scanner.owners(body) or ['unclaimed']}"
                  + ("" if claim is None else
                     f"  ROUTE={claim} ({route_verdict(scanner, args.symbol, pin, claim) or 'admissible'})"))
        identity = [p for p in pins if (args.symbol, p) not in routes]
        found = scanner.inspect(args.symbol, identity)
        print("    verdict: " + (f"{found['kind']}: {found['evidence']}" if found
                                 else "consistent"))
        return 0

    if args.check:
        verify()
        return 0

    scanner = Scanner()
    violations, stats = scanner.scan()
    if args.clear_cut:
        settled = 0
        for violation in violations:
            verdict = scanner.clear_cut(violation)
            if not verdict:
                continue
            settled += 1
            print(f"{violation['symbol']}")
            print(f"    keep 0x{verdict['keep']:08X} (its own matched row)")
            for body, others in verdict["drop"]:
                for pin in violation["pins"][body]:
                    print(f"    retract pin 0x{pin:08X} -> 0x{body:08X}, "
                          f"which is {others[0]}")
        print(f"{settled} of {len(violations)} violations have a ledger row CONTRADICTING "
              "the extra pins — candidates, not verdicts.")
        print("A byte-verified caller outranks a byte-verified identity row: the last "
              "session landed all 47 of these and 111 byte-matched rows went RED, 110 of "
              "them reaching a pin it had just deleted. Retract in small batches and run a "
              "FULL ./build.sh after each; expect about half to be refuted.")
        return 0
    if args.write_baseline or args.seed_baseline:
        write_baseline(violations, seed=args.seed_baseline)
        print(f"pin_consistency: wrote {shown(BASELINE)} with "
              f"{len(violations)} violation(s) — READ IT before committing")
        return 0
    if args.candidates:
        report_candidates(scanner, violations)
        return 0

    counts = collections.Counter(v["kind"] for v in violations)
    print(f"{stats['multi_pinned']} multi-pinned symbols of {stats['names']}; "
          f"{len(violations)} inconsistent; {stats['routes']} route= row(s)")
    for kind, count in counts.most_common():
        print(f"    {kind}: {count}")
    for violation in violations:
        print(f"{violation['symbol']}\n    {violation['kind']}: {violation['evidence']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
