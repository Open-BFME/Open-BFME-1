#!/usr/bin/env python3
"""Ask a constructor's own vtable stores which class it constructs.

THE DEFECT THIS EXISTS FOR. `tools/build.py:compile_function` MASKS DIR32
operands before comparing, so a vftable store compares as four zero bytes. Every
constructor of the shape

    call base; mov [this], ??_7X@@6B@; mov [this+c], ...; mov [this+10], ...; ret

therefore byte-matches EVERY other constructor of that shape, whatever class it
belongs to. Fourteen names sat on 0x0024FC20 that way and all fourteen were
green; thirteen were wrong. `tools/multi_name.py` cannot see it -- it compares
the same masked bytes and correctly reports a structural fold, because
structurally they ARE one shape. Only the operands the mask removed tell them
apart, and this reads exactly those.

THE TEST IS DECIDABLE, WHICH IS WHY IT IS WORTH SHIPPING. A constructor writes
the vptr of ITS OWN class last: the base constructor runs first and installs the
base vtable, then the derived body overwrites it. So the LAST store to each
object offset names the most-derived class -- and that class can be read off the
vtable, because a SAGE vtable carries the class's own vector deleting destructor
`??_G<C>@@` and, for pooled classes, `?getClassMemoryPool@<C>@@`. Both are
emitted once per class and carry a class-specific object size or pool pointer,
so they neither fold across classes nor get inherited into a derived vtable.
Resolve those slots through the ledger and the vtable names its owner outright.

FOUR THINGS IT DELIBERATELY DOES NOT DECIDE. Each was a live over-flag before it
was excluded, and the count in the header is what is left after all four:

  * TEMPLATES ARE OUT OF SCOPE (1,749 rows). `VectorClass<int>` and
    `VectorClass<char*>` really do share one constructor at 0x009062F0, because
    their vtables are identical COMDATs the linker folded first, and the
    surviving vtable's slots name several instantiations at once. Every name
    here must have a plain identifier class, so the 20 SimpleVecClass rows on
    one body never reach a verdict.
  * A PLACEHOLDER NAMES NO CLASS (1,239 owners cited before this). `Gen_dtor_`,
    `Rva0024FC60...`, `Bfme...` are the tree's spelling for "not identified
    yet"; reading one as a class indicts a row for disagreeing with a name that
    makes no claim. `rename_addressed_sources.opaque` is the repo's own test for
    that and is what this uses, on the row's class as well as the attester's.
  * A VTABLE ENDS SOMEWHERE. Walking slots until a non-code word runs straight
    through a one-slot vtable into the next one: that is how INIEntry's
    constructor "installed" INISection's destructor. The end is the next address
    anything in .text loads as a vtable, which is one 0.4s scan of .text.
  * AN AMBIGUOUS ATTESTER ATTESTS NOTHING. A destructor address two classes
    claim is this same defect one level down and cannot settle another instance
    of it.

And a row is CLEARED as soon as its class is named ANYWHERE in the vtable it
installs, not only by an owner-grade symbol. A base class's vtable holds that
base's own methods, so `??0SceneClass@@` installing a table full of
`?...@SceneClass@@` is exactly right even when the table's destructor slot has
been given a derived class's name.

So a CONTRADICTED row means: the vtable this body leaves installed is named, by
a row nothing else disputes, for a class this row does not mention. It does not
say WHICH name is wrong -- the attester could be the mistake -- only that the
two cannot both stand.

NO MASS EDIT FOLLOWS FROM A COUNT. The point is to make an invisible class of
defect countable; like every number in targets/game/reverse/identity_baseline.txt it only
goes down.

  python3 tools/ctor_vtable.py            # full report
  python3 tools/ctor_vtable.py --shared   # only addresses several ctors claim
"""
import bisect
import collections
import csv
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402
import rename_addressed_sources as R  # noqa: E402

IMAGE_BASE = 0x400000
MAX_SLOTS = 64

IDENT = r"[A-Za-z_][A-Za-z_0-9]*"
# Only plain identifier classes. `?$` (a template) and any nested qualifier are
# excluded on purpose -- see the docstring on VectorClass.
CTOR = re.compile(r"^\?\?0(%s)@@[A-Z]" % IDENT)
DTOR = re.compile(r"^\?\?_[GE](%s)@@[A-Z]" % IDENT)
POOL = re.compile(r"^\?getClassMemoryPool@(%s)@@[A-Z]" % IDENT)
VFTABLE = re.compile(r"^\?\?_7(%s)@@6B" % IDENT)
# Any symbol that mentions a class at all, used only to CLEAR a row.
MENTIONS = re.compile(r"^\?(?:\?[0-9A-Z]|\?_[A-Z]|%s@)(%s)@@" % (IDENT, IDENT))

CONFIRMED = "the vtable it installs names this class"
CONTRADICTED = "the vtable it installs names a DIFFERENT class"
UNNAMED = "vtable installed but nothing in it is named - no evidence"
NOT_POLYMORPHIC = "installs no vtable - out of scope"
UNDECODED = "a vtable constant reached the body by a form this cannot decode"
UNREADABLE = "body could not be read - NOT a clean result"

Finding = collections.namedtuple(
    "Finding", "rva size name cls verdict owners evidence sharers")


def ctor_class(name):
    match = CTOR.match(name)
    return match.group(1) if match and not R.opaque(match.group(1)) else None


def attester_class(name):
    """The class a symbol attests as its vtable's OWNER, or None.

    An ordinary virtual method attests nothing: `?update@UpdateModule@@` sits in
    the vtable of every class that did not override it, so it names a base. Only
    the per-class generated members count.
    """
    for pattern in (DTOR, POOL, VFTABLE):
        match = pattern.match(name)
        if match and not R.opaque(match.group(1)):
            return match.group(1)
    return None


def mentioned_class(name):
    """The class a symbol mentions at all, for the clearing rule."""
    match = MENTIONS.match(name)
    return match.group(1) if match else None


class Image:
    """The retail bytes, with just the questions this asks of them."""

    def __init__(self, data=None, sections=None, extra_starts=()):
        self.data = B.EXE.read_bytes() if data is None else data
        self.sections = B.pe_sections(self.data) if sections is None else sections
        text = next(s for s in self.sections if s["name"] == ".text")
        self.text = (text["rva"], text["rva"] + text["size"])
        self.rdata = [(s["rva"], s["rva"] + s["size"])
                      for s in self.sections if s["name"] == ".rdata"]
        self.starts = sorted(set(self.scan_vtable_starts()) | set(extra_starts))

    def _dword(self, rva):
        try:
            offset = B.rva_to_file_offset(self.sections, rva)
        except BaseException:      # noqa: BLE001 - an unmapped rva is "not a vtable"
            return None
        if offset + 4 > len(self.data):
            return None
        return struct.unpack_from("<I", self.data, offset)[0]

    def in_text(self, rva):
        return self.text[0] <= rva < self.text[1]

    def body(self, rva, size):
        try:
            offset = B.rva_to_file_offset(self.sections, rva)
        except BaseException:      # noqa: BLE001 - reported as UNREADABLE
            return None
        chunk = self.data[offset:offset + size]
        return chunk if len(chunk) == size else None

    def is_vtable(self, va):
        """A 4-aligned .rdata address whose first slot points into .text.

        Deliberately loose: a false positive contributes a table this cannot
        name, which yields UNNAMED rather than a verdict.
        """
        rva = va - IMAGE_BASE
        if rva % 4 or not any(lo <= rva < hi for lo, hi in self.rdata):
            return False
        slot = self._dword(rva)
        return slot is not None and self.in_text(slot - IMAGE_BASE)

    def scan_vtable_starts(self):
        """Every .rdata table address .text loads as an immediate.

        This is the only thing that bounds a vtable. MSVC lays vtables out
        back to back, so a table of one slot is followed immediately by the next
        class's, and a walk that stops only at a non-code word reads them as one.
        """
        low = B.rva_to_file_offset(self.sections, self.text[0])
        text = self.data[low:low + self.text[1] - self.text[0]]
        found = set()
        for match in re.finditer(rb"[\xc7\x68\xb8-\xbf]", text):
            at = match.start()
            # C7 /0 carries the immediate after a 0, 1 or 4 byte displacement;
            # 68 (push) and B8+r (mov reg) put it straight after the opcode.
            spots = (2, 3, 6) if text[at] == 0xC7 else (1,)
            for skip in spots:
                if at + skip + 4 <= len(text):
                    value = struct.unpack_from("<I", text, at + skip)[0]
                    if self.is_vtable(value):
                        found.add(value)
        return found

    def slots(self, va, cap=MAX_SLOTS):
        """Slot target RVAs, incremental-link thunks followed, stopping at the
        next vtable start or the first non-code word."""
        cap = slot_cap(self.starts, va, cap)
        out = []
        for slot in range(cap):
            word = self._dword(va - IMAGE_BASE + 4 * slot)
            if word is None:
                break
            target = word - IMAGE_BASE
            if not self.in_text(target):
                break
            out.append(B.follow_thunk(self.data, self.sections, target, *self.text))
        return out


def slot_cap(starts, va, cap=MAX_SLOTS):
    """How many slots a table at `va` may have before the next table begins.

    MSVC lays vtables out back to back, so a one-slot table is followed
    immediately by the next class's. Without this bound INIEntry's constructor
    "installed" INISection's destructor -- read out of the table next door.
    """
    index = bisect.bisect_right(starts, va)
    if index < len(starts):
        cap = min(cap, (starts[index] - va) // 4)
    return max(cap, 0)


def vptr_stores(body, is_vtable):
    """([(offset, (base_reg, disp), va)], [va reached by an undecoded form]).

    Decoded without a disassembler on purpose: this is cheap enough for the
    commit hook and a hook that dies when capstone is missing blocks every
    lane's commit. The anchor is the OPERAND -- a 4-aligned .rdata word whose
    first slot is code -- so only `C7 /0` (`mov dword ptr [reg+disp], imm32`)
    has to be recognised, matched backwards from an immediate already known to
    be a vtable. Verified instruction for instruction against capstone on the
    bodies at 0x0024FC20, 0x001ECF40, 0x0020D5C0, 0x001F8B80 and 0x006CFAE0.
    """
    recognised, loose = [], []
    for at in range(0, max(0, len(body) - 3)):
        va = struct.unpack_from("<I", body, at)[0]
        if not is_vtable(va):
            continue
        where = None
        if at >= 2 and body[at - 2] == 0xC7:
            modrm = body[at - 1]
            if modrm >> 6 == 0 and (modrm >> 3) & 7 == 0 and modrm & 7 not in (4, 5):
                where = (modrm & 7, 0)
        if where is None and at >= 3 and body[at - 3] == 0xC7:
            modrm = body[at - 2]
            if modrm >> 6 == 1 and (modrm >> 3) & 7 == 0 and modrm & 7 != 4:
                where = (modrm & 7, struct.unpack_from("<b", body, at - 1)[0])
        if where is None and at >= 6 and body[at - 6] == 0xC7:
            modrm = body[at - 5]
            if modrm >> 6 == 2 and (modrm >> 3) & 7 == 0 and modrm & 7 != 4:
                where = (modrm & 7, struct.unpack_from("<i", body, at - 4)[0])
        (recognised if where else loose).append((at, where, va))
    return ([(at, where, va) for at, where, va in recognised],
            [va for _, _, va in loose])


def most_derived(body, is_vtable):
    """The vtables still installed when the constructor returns, or None.

    None means "cannot tell": a vtable constant reached this body by a form the
    decoder does not read, so which store lands last is unknown and no verdict
    may rest on it.  A direct store at a nonzero displacement is a base/member
    subobject and cannot name a non-polymorphic enclosing class: PlayerTemplate's
    copy constructor, for example, installs Money's vtable at this+0x1c.  The
    detector is about the constructor's primary object, so only the final
    offset-zero store may attest or contradict its class.
    """
    recognised, loose = vptr_stores(body, is_vtable)
    if loose:
        return None
    last = {}
    for at, where, va in recognised:
        last[where] = (at, va)
    # If the body installs a primary vptr, retain secondary-base stores too:
    # one of their tables may be the only one whose slots still name the
    # derived class.  With no offset-zero store, every recognised table is a
    # member/subobject and none can identify the enclosing constructor.
    if not any(displacement == 0 for _, displacement in last):
        return set()
    return {va for _, va in last.values()}


def attest(va, image, names_at, pinned):
    """(owners, mentions, evidence) for one vtable."""
    owners, mentions, evidence = set(), set(), []
    pin = pinned.get(va)
    if pin is not None:
        owners.add(pin)
        mentions.add(pin)
        evidence.append((-1, va - IMAGE_BASE, pin))
    for index, target in enumerate(image.slots(va)):
        names = names_at.get(target, ())
        for name in names:
            mentioned = mentioned_class(name)
            if mentioned:
                mentions.add(mentioned)
        claims = {attester_class(name) for name in names}
        claims.discard(None)
        # Two classes claiming one destructor is this defect one level down.
        if len(claims) != 1:
            continue
        owner = claims.pop()
        owners.add(owner)
        evidence.append((index, target, owner))
    return owners, mentions, evidence


def classify(rows, image, names_at, pinned=None, read=None):
    """Yield a Finding for every matched constructor row with a plain class."""
    pinned = pinned or {}
    read = read or (lambda row, rva, size: image.body(rva, size))
    sharers = collections.defaultdict(set)
    for row in rows:
        sharers[row["target_rva"].lower()].add(row["name"])
    cache = {}
    for row in rows:
        cls = ctor_class(row["name"])
        if cls is None:
            continue
        try:
            rva, size = int(row["target_rva"], 16), int(row["target_size"])
        except ValueError:
            continue
        peers = sorted(sharers[row["target_rva"].lower()] - {row["name"]})
        body = read(row, rva, size)
        if body is None:
            yield Finding(rva, size, row["name"], cls, UNREADABLE, (), (), peers)
            continue
        installed = most_derived(body, image.is_vtable)
        if installed is None:
            yield Finding(rva, size, row["name"], cls, UNDECODED, (), (), peers)
            continue
        if not installed:
            yield Finding(rva, size, row["name"], cls, NOT_POLYMORPHIC, (), (), peers)
            continue
        owners, mentions, evidence = set(), set(), []
        for va in sorted(installed):
            if va not in cache:
                cache[va] = attest(va, image, names_at, pinned)
            found, said, why = cache[va]
            owners |= found
            mentions |= said
            evidence += [(va,) + item for item in why]
        if cls in mentions:
            verdict = CONFIRMED
        elif not owners:
            verdict = UNNAMED
        else:
            verdict = CONTRADICTED
        yield Finding(rva, size, row["name"], cls, verdict,
                      tuple(sorted(owners)), tuple(evidence), peers)


def pinned_vtables(records=None):
    """{vtable VA: class} from the targets/game/reverse/symbols.csv ??_7 pins.

    A pin is the one place a vtable is named directly rather than through a
    slot. It is also the least trustworthy evidence here -- symbols.csv is an
    ADDITIVE CANDIDATE LIST, so a pin naming the wrong vtable still byte-matches
    -- which is why an address carrying pins for two different classes attests
    NOTHING. 0x01073744 has three (BfmeBaseVUQ, DockUpdateModuleData,
    HordeContainModuleDataBase); taking the first non-placeholder one indicted
    both Snapshot constructors on the strength of a coin flip.

    Both address spellings occur in that file -- most pins are VAs, a few are
    RVAs -- so each is registered under both readings and the one that never
    matches a real vtable simply goes unused.
    """
    if records is None:
        path = B.ROOT / "targets/game/reverse" / "symbols.csv"
        with open(path, newline="", encoding="utf-8", errors="replace") as handle:
            records = list(csv.reader(handle))
    claims = collections.defaultdict(set)
    for record in records:
        if len(record) < 2 or not record[0].startswith("??_7"):
            continue
        cls = attester_class(record[0])
        if cls is None:
            continue
        try:
            address = int(record[1], 16)
        except ValueError:
            continue
        claims[address].add(cls)
        claims[address + IMAGE_BASE].add(cls)
    return {address: next(iter(named)) for address, named in claims.items()
            if len(named) == 1}


def load(image=None):
    rows = [r for r in B.load_function_rows() if r["status"] == "matched"]
    pinned = pinned_vtables()
    image = image or Image(extra_starts=[a for a in pinned if a >= IMAGE_BASE])
    names_at = collections.defaultdict(set)
    for row in rows:
        try:
            names_at[int(row["target_rva"], 16)].add(row["name"])
        except ValueError:
            pass
    return rows, image, names_at, pinned


def scan(image=None):
    rows, image, names_at, pinned = load(image)
    return list(classify(rows, image, names_at, pinned))


def main(argv):
    only_shared = "--shared" in argv
    findings = scan()
    tally = collections.Counter(f.verdict for f in findings)
    print("matched constructor rows with a plain class name: %d" % len(findings))
    for verdict, count in tally.most_common():
        print("  %5d  %s" % (count, verdict))
    flagged = [f for f in findings if f.verdict == CONTRADICTED]
    shared = [f for f in flagged if f.sharers]
    print("\nof the %d contradicted, %d share their address with another name"
          % (len(flagged), len(shared)))
    for f in sorted(shared if only_shared else flagged,
                    key=lambda f: (f.rva, f.name)):
        print("\n0x%08X %4dB  %s" % (f.rva, f.size, f.name[:88]))
        print("      claims %s; the vtable it leaves installed belongs to %s"
              % (f.cls, ", ".join(f.owners)))
        for va, index, target, owner in f.evidence:
            where = "pin" if index < 0 else "slot %d" % index
            print("      vtable %#x %-8s -> 0x%08X  %s" % (va, where, target, owner))
        for peer in f.sharers:
            print("      also claimed here: %s" % peer[:88])
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
