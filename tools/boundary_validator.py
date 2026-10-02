#!/usr/bin/env python3
"""Refuse queue addresses that cannot be a retail function boundary.

The structural queue's addresses come from an alignment vote, so a large share
of them name a spot a few bytes inside a body rather than its start. Nothing in
the queue told a worker that, so the fleet proved it by hand: ~2,300 logged
no-match rows, most of them a 30-60 minute reconstruction against an address
that never had a function at it.

Every check here rejects on positive evidence only -- a byte the image says is
padding, another function's start inside the claimed range, a stack cleanup the
body contradicts. Absence of evidence never rejects: 61% of the bodies already
landed are missing from the Ghidra inventory, so "not in the inventory" is
unknown, not wrong.

Two things deliberately do NOT reject. A range that stops short of the body's
end is a size error, and reconciling size drift is the tier's whole job -- it
warns and is still served. A body that ends in something other than a `ret` is
a tail call as often as it is a boundary error, so it is not consulted at all.

The image reader and the Ghidra inventory are injected rather than imported, so
a replay over a recorded queue is pure.
"""
import bisect

import audit_ret_arity

TEXT_VA, TEXT_SIZE = 0x1000, 0xC72000
# MSVC pads between functions with int3. A single 0xCC is more often an operand
# or displacement byte, so only a run of them is evidence of a boundary.
MIN_PAD_RUN = 3
# The two refusals that name a body: one the address sits inside, one the
# padding it sits in runs up to. `unmapped-gap` and `outside-.text` name none,
# so there is nothing to correct them to -- see `corrected_start`.
CORRECTABLE = {"interior-of-function", "in-int3-padding"}


class BoundaryValidator:
    """The three checks, over one address at a time.

    `read_bytes(rva, count) -> bytes` reads the retail image;
    `ghidra_sizes` maps a known function start to its body size.
    """

    def __init__(self, read_bytes, ghidra_sizes):
        self.read = read_bytes
        self.sizes = ghidra_sizes
        self.starts = sorted(ghidra_sizes)

    def containing(self, rva):
        """Start of the known function covering `rva`, or None."""
        index = bisect.bisect_right(self.starts, rva) - 1
        if index < 0:
            return None
        start = self.starts[index]
        return start if rva < start + self.sizes[start] else None

    def starts_inside(self, rva, end):
        """How many known function starts lie strictly inside (rva, end)."""
        low = bisect.bisect_right(self.starts, rva)
        high = bisect.bisect_left(self.starts, end)
        return max(0, high - low)

    def pad_run_inside(self, rva, size):
        """RVA of an int3 run inside the range that still has code after it."""
        body = self.read(rva, size)
        index = 0
        while index < len(body):
            if body[index] != 0xCC:
                index += 1
                continue
            end = index
            while end < len(body) and body[end] == 0xCC:
                end += 1
            if end - index >= MIN_PAD_RUN and end < len(body):
                return rva + index
            index = end
        return None

    def check_start(self, rva):
        """C1: can a function start here? Returns (True|False|None, reason).

        None is "the inventory has no opinion", which is the common case for the
        stubs and generated funclets it never covered.
        """
        if not TEXT_VA <= rva < TEXT_VA + TEXT_SIZE:
            return False, "outside-.text"
        if rva in self.sizes:
            return True, "ghidra-start"
        if self.read(rva, 1)[:1] == b"\xcc":
            return False, "in-int3-padding"
        if self.containing(rva) is not None:
            return False, "interior-of-function"
        return None, "unmapped-gap"

    def corrected_start(self, rva):
        """Where the body at a REFUTED address actually starts, or None.

        An address `check_start` refuses is wrong about one specific body, and
        the inventory names it: an interior address back-snaps to the start
        enclosing it, and one in int3 padding forward-snaps to the start the
        padding runs up to. The two directions are opposite, which is why a size
        formula fitted to either no-ops on the other.

        The gate is here rather than in the caller because the tempting wrong
        rule -- correcting on `containing() is None` -- forward-snaps every
        unmapped address too, and those are unknown, not wrong: each lands past
        its own current end. Absence of evidence still never decides anything.
        """
        if self.check_start(rva)[1] not in CORRECTABLE:
            return None
        inside = self.containing(rva)
        if inside is not None:
            return inside
        index = bisect.bisect_left(self.starts, rva)
        return self.starts[index] if index < len(self.starts) else None

    def check_end(self, rva, size):
        """C2: does [rva, rva+size) walk over a boundary? Returns a reason or None.

        Callers pass the range they will actually serve, not the range a drifted
        source claimed -- see `validate`.
        """
        if not TEXT_VA <= rva + size <= TEXT_VA + TEXT_SIZE:
            return "end-outside-.text"
        crossed = self.starts_inside(rva, rva + size)
        if crossed:
            return f"spans-{min(crossed, 9)}-function-start(s)"
        if self.pad_run_inside(rva, size) is not None:
            return "crosses-int3-run"
        return None

    def check_arity(self, symbol, rva, size):
        """C3: does the body's stack cleanup match the name's parameter list?"""
        want, convention = audit_ret_arity.expected_ret(symbol)
        # This validator's acceptance population contains many byte-verified
        # aliases and naked thunks whose decorated cdecl names are not an
        # identity proof. Keep caller-cleaned names opinion-free here; the
        # naked conversion queue has the body-level check that specifically
        # retires a parsed cdecl name ending in positive `ret N`.
        if convention == "__cdecl":
            return None, "caller-cleaned-not-validated"
        if want is None:
            return None, "name-unparsable-or-unsupported-abi"
        got = audit_ret_arity.actual_ret(self.read(rva, size))
        if got is None:
            return None, "no-ret-tail"
        if got == want:
            return True, "ok"
        return False, f"{convention} must pop {want}B, this body pops {got}B"

    def validate(self, names, rva, size, sizes=None):
        """Verdict for one address and every name claiming it.

        Arity is per name, so a shared address keeps only the names whose
        convention its body can actually satisfy; an address that keeps none is
        not work. C1 and C2 are properties of the address itself and refuse it
        outright.

        `size` is the length to measure the ADDRESS with, which is what C2 and
        the C3 reads need. `sizes` maps a name to the compiled length of its own
        source body, and exists so the size advisory can name a candidate this
        verdict actually keeps: one body carries many drifted names and C3 drops
        the highest-ranked ones, so quoting the caller's single `size` printed
        one candidate's length beside another's (28 of 849 collapsed items, up to
        1,220 B out) and sent the next session reconciling a difference its
        source does not have.
        """
        verdict = {"rva": rva, "size": size, "extent": self.sizes.get(rva),
                   "names": list(names), "refuted": {}, "reject": None,
                   "warnings": []}
        start_ok, reason = self.check_start(rva)
        if start_ok is False:
            verdict["reject"] = f"C1 {reason}"
            return verdict
        # Both remaining checks read the body the queue will hand over: Ghidra's
        # extent where it knows one, the claimed size only where it does not. A
        # drifted size is what this tier reconciles, so measuring against it
        # instead refuses 245 confirmed function starts for their callers' sizes
        # and refutes 24 names where the body refutes 1,278.
        served = verdict["extent"] or size
        reject = self.check_end(rva, served)
        if reject:
            verdict["reject"] = f"C2 {reject}"
            return verdict
        kept = []
        for name in names:
            arity_ok, why = self.check_arity(name, rva, served)
            if arity_ok is False:
                verdict["refuted"][name] = why
            else:
                kept.append(name)
        verdict["names"] = kept
        if not kept:
            verdict["reject"] = "C3 every name's arity is refuted by this body"
            return verdict
        # Emitted last, and about a name this verdict keeps: the advisory is the
        # one number a worker reconciles against retail, so it has to be the
        # length of the source they are actually handed.
        reported = (sizes or {}).get(kept[0], size)
        if verdict["extent"] and verdict["extent"] != reported:
            verdict["warnings"].append(
                f"source claims {reported}B, retail body is {verdict['extent']}B")
        return verdict
