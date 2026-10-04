# Native scalar-StateID lookup and caller contract

Original BFME1 retail1.03-unpacked PE SHA256:
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses below are RVA unless labelled VA. Evidence was read from the original
PE and cross-checked with the saved actual Ghidra MCP read/decompile/disassembly
session for000A1310; no inferred decompiler signature is treated as proof.

## Lookup000A1310, full63 bytes

Entry ECX is the unadjusted machine address. The function forms ECX=this+4,
passes the address of its one four-byte scalar unsigned StateID argument and a
one-word iterator output, then calls ILT0004833D ->000A0E20. It compares the
returned node with the map sentinel; success reads node+14 and returns State*
in EAX. The final instruction is RET4 at+3C, followed by padding. There is no
iterator object passed by the caller and no returning diagnostic operation.

The71-byte tree helper000A0E20 takes ECX=map and two stack words: iterator
output pointer and const unsigned key reference. It returns the output pointer
in EAX and RET8. Keys at node+10 compare using JB/JAE, not signed branches.
The previous provider was `dup_a0e20` in GameClient/System/Image.cpp with
an explicit Image* object-symbol. The corrected State* helper is now selected
from BfmeConv2128.cpp. The already-existing unsigned
State* tree-find candidate pin names this same native body; independently
emitted State* helper code equals all71 original bytes with no relocations.
The original strict selected-identity check rejected that candidate because
its inherited ledger homes were002A1D40,00404A70,004B0530,004D4AF0,00586260,
0094C5E0,009EC290. Independently proved non-State payloads refute those homes.
The companion000a0e20-state-tree-find.md correction retains their byte-only
coverage and selects this TU's natural State* helper once atA0E20; no additional
helper body or pin is introduced.

Missing keys throw the canonical GeneralsMD/Common/Errors.h enum
`ERROR_BAD_ARG` (0xDEAD0003). Native ThrowInfo VA011E0004 points to the single
catchable array VA011DFFFC, record VA011DFFDC, and descriptor VA012A716C named
`.?AW4ErrorCode@@`. Catchable properties=1, size=4, PMD=(0,-1,0), with no copy
or destructor. Natural MSVC7.1 `throw ERROR_BAD_ARG` reproduces all four graph
records after independently checking their pointer targets. The three lookup
relocations are the tree-find ILT, ErrorCode ThrowInfo and _CxxThrowException
at RVA009F6D00. This is not XferException or an iterator diagnostic.

## Caller0016AD90, full185 bytes

Its first entry stack word is passed unchanged to lookup via ILT000124D1. Its
second word is the signed duration. It returns the signed state result in EAX
and RET8; the original extent is185 bytes. The old `void *` first parameter
was a false contract with no other non-generated C++ consumers of its name.
Changing it to unsigned preserves the entire body and removes the old pointer
punning through BfmeIterABB. No caller alias is introduced.

The existing BfmeThingXZ/BfmeSlotXZ views only dispatch at state vtable+10 and
+14 with the returned native State address unchanged. Their localized casts
are partial native layout views, not replacement State identities. In
AIStateMachine_xfer, the existing local State view reads ID at+4. Lookup now
uses one shared declaration with a scalar unsigned input and State* result;
there is no argument or result cast at that call. Neither view constructs a
State or asserts compatibility with the erroneous sweep State header.

## Scope and provider accounting

`Rva000A1310StateMachine` is an explicit address-qualified16-byte partial
prefix: one existing vptr word and the12-byte map at+4. It emits no machine
vtable and is not a new canonical StateMachine. State stays forward-declared
in the header. The complete native class/lifetime migration remains separate.

Retire the false bfmeFrontABB matched row through add_match identity correction
and tombstone; similarly replace bfmeStartXZ's pointer signature with its
scalar signature at the same185-byte extent. Remove unused bfmeAcquireXZ,
bfmeRangeABB, bfmeDiagABB and g_bfmeDescABB pins after the three actual source
consumers are corrected. Do not add lookup aliases. One selected lookup body
remains. The serializer000A1510 research bank is not edited or claimed here.

The three complete selected source rows are63+185+678 bytes. Their scoped byte
and relocation gates must pass, plus pin consistency and identity/tombstone
checks. A shared-header change requires the normal full gate before commit.
The pre-change census preview already reports unrelated AIStateMachine/Squad,
Waypoint and STL blockers; preserving those does not establish native linking.

## Current validation limit

All three selected source rows and their byte-gate relocations pass; canonical
ErrorCode graph and emitted unsigned tree helper pass the independent PE
audit. The first strict preview correctly exposed the inherited tree-helper
identity conflict; the companion family-owned reconciliation repairs that
selected identity instead of hiding it behind a candidate pin. The full header
gate and normal commit remain required. Pre-existing AI/Squad/Waypoint and
broad StateMachine/Image blockers must not be reported as native linkage gains.
No baselines or checkers were changed.
