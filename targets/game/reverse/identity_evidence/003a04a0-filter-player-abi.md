# Filter predicate at RVA 0x003A04A0

The matched C++ `Rva2225E0FilteredCountThunk::count` at RVA 0x002225E0
calls `Rva2225E0Filter::accepts(Object *, Player *)` through ILT 0x0001DA34.
This is the existing owner/method spelling, independent of the new byte match.
The complete wrapper is 72 bytes: final RET8 at 0x003A04E5, followed by INT3
at 0x003A04E8 (also independently read through Ghidra).

## The bank's argument split was wrong

Retail at 0x003A04CD loads the incoming Player pointer and pushes it at
0x003A04D1. It then calls ILT 0x00020824 at 0x003A04D4. This is the already
matched `Object::getControllingPlayer() const`, RVA 0x001BE3F0, 18 bytes:
it reads Object+0x23C, tail-jumps through 0x0002369B if non-null, and returns
null with a bare RET otherwise. It takes no stack arguments and returns a
Player pointer, not a Boolean.

The push therefore belongs to the *next* call. At 0x003A04D9 and 0x003A04DA
retail pushes the returned Player and the resolved template, restores the
filter receiver, then calls ILT 0x0001B437 -> RVA 0x0039F0A0. That callee ends
with RET12 at 0x0039F3AA. The matched `BannerThingCounter::add` independently
uses its existing `Rva0039F0A0::accepts(const void *, Player *, Player *)` pin.

The old bank instead declared a one-argument Boolean query and a two-argument
final predicate. Their combined cleanup accidentally agreed with retail,
leaving just four scheduling bytes. Correcting the two calls matches all 72
bytes. The canonical Object header preserves its primary vptr and template
field. The established BfmeOverridable ABI view preserves the existing
ILT 0x000022BB -> matched `Overridable::getFinalOverride` at 0x00087A80;
its const pointer-returning, zero-stack-argument ABI is retained explicitly.

Strict byte and relocation verification passes without new pins. The obsolete
`bfmeQuery@BfmeFilterObject` pin at 0x00020824 has no game-source users and is
removed on reapplication after confirming no game-source or function-ledger users;
it described the disproved one-argument Boolean ABI.

## Name-checker pairing

The removed BfmeFilterObject was the bank's fictitious Object base carrying
the wrong query signature; it is replaced by the canonical Object header.
Rva0039F0A0 is a separate final-callee view already used by the matched
BannerThingCounter caller, not a renamed BfmeFilterObject. The source-rehome
checker pairs these unrelated declarations; the snapshot-specific correction
records that false pairing. The established override-view and link names stay.

## Landing status

The clean wrapper passes strict 72-byte verification. Its production promotion
was reverted before commit because the ledger commit triggers alias_guard on
two unrelated pre-existing aliases (Rva003C8340.cpp and Rva00803080Set.cpp)
that the current origin/master no longer carries. This session may not rebase
or widen the body into unrelated repairs. The corrected source is banked at
1.000; no production row or pin change from this attempt remains.


## Reapplied after upstream guard corrections (2026-10-03)

Upstream f3ef066627 and c86648d2ae removed the unrelated aliases that blocked
the earlier commit. The unchanged exact bank was promoted with add_match,
replacing only the 72-byte generated row. Strict byte/call verification passes
all three relocations without new pins or shared-header edits. The obsolete
BfmeFilterObject pin above is removed using the terminator-preserving ledger
writer; the canonical Object getter pin and existing final-predicate pin remain.

Fresh Ghidra MCP disassembly corroborates the carried stack argument at RVA
0x003A04D1, the zero-argument Object getter call, and the three arguments consumed
by the final predicate. The existing ABI-view names are unchanged. The earlier
private bank remains available in archived history; its preferred copy is now
verified production source.
