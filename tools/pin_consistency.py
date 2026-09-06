#!/usr/bin/env python3
"""Pin-consistency guard for reverse/symbols.csv.

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
the other way round and are outside it. Neither is a bug in the check; both are
uncovered ground, and saying so here is the point.

1. ONE ADDRESS, MANY NAMES. The 0x14867 incident above is really this shape.
   Three of its four names are flagged only incidentally, because they happen to
   carry other pins too; ?winSetEnabledBorderColor@GameWindow@@QAEHHH@Z pins
   0x14867 and nothing else and is completely invisible here. 70,144 of 70,633
   symbols pin exactly one address and are never compared to anything. A blanket
   check is not the answer -- 6,601 bodies legitimately carry several names, one
   of them 453 folded destructors -- but nothing checks the illegitimate ones.

2. THE OTHER HALF OF THE CANDIDATE LIST. load_symbol_map seeds each name from
   its functions.csv rows and THEN appends its symbols.csv pins, so the additive
   list the resolver actually walks is the union of both. This guard reads only
   the pins. A name with one pin and one ledger row pointing at a different body
   is a two-candidate list -- the exact hazard -- and `len(pins) < 2` skips it.
   `--candidates` applies the same invariant to the real list and currently
   finds 114 violations on top of the gated 410. It reports; it does not gate,
   because gating it would mean baselining 114 new lines and this file is only
   allowed to shrink. Drain them, do not record them.

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

BASELINE, NOT WHITELIST
-----------------------
First run found a backlog of known-bad pins. reverse/pin_consistency_baseline.csv
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
import io
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402  (after the path insert that makes it importable)
import import_pin_guard  # noqa: E402
import progress  # noqa: E402

ROOT = build.ROOT
BASELINE = ROOT / "reverse" / "pin_consistency_baseline.csv"
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


def load_ledger():
    """Per-body extents and identity owners, over every functions.csv row.

    Unmatched rows count for extent because an unmatched row still asserts a
    boundary somebody derived; matched rows are preferred where they disagree,
    and the provenance is reported so a human can see which spoke.
    """
    sizes = collections.defaultdict(dict)
    matched = collections.defaultdict(dict)
    identities = collections.defaultdict(set)
    for row in build.load_all_function_rows():
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
    with (ROOT / "reverse" / "ghidra_functions.csv").open("r", encoding="utf-8",
                                                          newline="") as handle:
        for row in csv.DictReader(handle):
            ghidra.setdefault(int(row["rva"], 16), int(row["size"]))
    with (ROOT / "reverse" / "derived_boundaries.csv").open("r", encoding="utf-8",
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
    def __init__(self):
        self.ledger_sizes, self.ledger_matched, self.identities = load_ledger()
        self.ghidra, self.derived = load_extra_boundaries()
        self.image = Image(self.ledger_sizes)
        self._extents = sorted(
            (rva, size, members[0])
            for rva, entry in self.ledger_matched.items()
            for size, members in entry.items())
        self._starts = [rva for rva, _size, _name in self._extents]
        self._widest = max((size for _rva, size, _name in self._extents), default=0)

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
        multi = 0
        for name in sorted(pins):
            if len(pins[name]) < 2:
                continue
            multi += 1
            found = self.inspect(name, pins[name])
            if found:
                violations.append(found)
        violations.sort(key=lambda v: (v["kind"], v["symbol"]))
        return violations, {"names": len(pins), "multi_pinned": multi}


def candidate_lists():
    """name -> every address build.py's REL32 resolver may try, both sources.

    load_symbol_map seeds each name from its functions.csv rows AND then
    appends its symbols.csv pins, so the additive candidate list the resolver
    walks is the UNION. The guard reads only the symbols.csv half, which means a
    name with one pin and one ledger row at a different body is a two-candidate
    list the invariant never sees. That is the same hazard, one source over.
    """
    lists = collections.defaultdict(list)
    for row in build.load_all_function_rows():
        rva = int(row["target_rva"], 16)
        if rva not in lists[row["name"]]:
            lists[row["name"]].append(rva)
    for name, addresses in load_pins().items():
        for address in addresses:
            if address not in lists[name]:
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
    extra = []
    for name, addresses in candidate_lists().items():
        if len(addresses) < 2 or name in known:
            continue
        found = scanner.inspect(name, addresses)
        if found:
            extra.append(found)
    extra.sort(key=lambda v: (v["kind"], v["symbol"]))
    counts = collections.Counter(v["kind"] for v in extra)
    print(f"{len(pin_violations)} inconsistent on symbols.csv pins alone (the gated surface)")
    print(f"{len(extra)} MORE inconsistent once functions.csv rows join the candidate list "
          "(ungated blind spot)")
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
# reverse/symbols.csv is an ADDITIVE candidate list: build.py's REL32 resolver
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
#   3. Delete the losing pin rows from reverse/symbols.csv -- splice in place,
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
# resolver's candidate list. `--candidates` reports the second (114 more).
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
                "the pin in reverse/symbols.csv instead. New key(s):\n"
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


def verify(path=BASELINE):
    """The gate entry point. Prints its own verdict; raises SystemExit on failure."""
    violations, stats = Scanner().scan()
    new, stale = check(violations, path)
    if new:
        print(f"Pin consistency: FAIL {len(new)} NEW inconsistent symbol(s) "
              "(one name, addresses that are not the same function)")
        for violation in new[:12]:
            print(f"    {violation['symbol']}")
            print(f"        {violation['kind']}: {violation['evidence']}")
        print("    Fix the pin in reverse/symbols.csv. Do NOT add these to "
              f"{shown(path)} to get green.")
        raise SystemExit(1)
    if stale:
        print(f"Pin consistency: FAIL {len(stale)} baseline line(s) no longer describe "
              "a violation — delete them in the commit that fixed the pin")
        for row in stale[:12]:
            print(f"    {row['symbol']} [{row['bodies']}]")
        raise SystemExit(1)
    print(f"Pin consistency: OK ({stats['multi_pinned']} multi-pinned symbols of "
          f"{stats['names']}; {len(violations)} baselined, 0 new, 0 stale)")
    verify_import_pins()


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--check", action="store_true",
                        help="gate mode: fail on any violation not in the baseline")
    parser.add_argument("--write-baseline", action="store_true",
                        help="regenerate reverse/pin_consistency_baseline.csv (may only DROP lines)")
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
    parser.add_argument("--clear-cut", action="store_true",
                        help="candidates a byte-verified ledger row settles — each still needs caller confirmation")
    args = parser.parse_args(argv)

    if args.assert_shrink_only:
        assert_shrink_only(args.assert_shrink_only, args.at)
        return 0

    if args.symbol:
        scanner = Scanner()
        pins = load_pins().get(args.symbol)
        if not pins:
            raise SystemExit(f"pin_consistency: {args.symbol} has no reverse/symbols.csv pin")
        print(f"{args.symbol}: " + " ".join(f"0x{p:08X}" for p in pins))
        for pin in pins:
            body, chain = scanner.image.resolve(pin)
            size, provenance = scanner.extent(body)
            print("    " + " -> ".join(f"0x{x:08X}" for x in chain) +
                  f"  extent={size} ({provenance})  owned-by={scanner.owners(body) or ['unclaimed']}")
        found = scanner.inspect(args.symbol, pins)
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
          f"{len(violations)} inconsistent")
    for kind, count in counts.most_common():
        print(f"    {kind}: {count}")
    for violation in violations:
        print(f"{violation['symbol']}\n    {violation['kind']}: {violation['evidence']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
