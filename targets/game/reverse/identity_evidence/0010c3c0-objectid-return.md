# RVA 0010C3C0 ObjectID transfer return contract

## Correction and bounded source scope

Keep the address-qualified `Rva0010C3C0` identity and its two independently
proved arguments (`MidVirtualSlot90Receiver *`, `void *`). Correct its return
from `void` to `Xfer &`. No semantic name, alternate provider, global resolver
change, or canonical `Xfer` header change is introduced.

Old selected COFF spelling:
`?Rva0010C3C0@@YAXPAVMidVirtualSlot90Receiver@@PAX@Z`

Corrected spelling:
`?Rva0010C3C0@@YAAAVXfer@@PAVMidVirtualSlot90Receiver@@PAX@Z`

This is a coordinated declaration repair. The other 59 slot-90 forwarders
retain their void signatures and ignore the returned value. Their complete
25-byte extents and DIR32 targets must remain exact. Existing typed caller
aliases are migrated to the one selected address-qualified provider; unused
legacy candidate pins are removed rather than kept as competing contracts.

## Independent original-binary evidence

Baseline: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`.
SHA256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Image base is `0x00400000`; every address below explicitly distinguishes RVA
from VA.

Actual read-only Ghidra MCP observations, retained in the StateMachine
serializer evidence packet, establish these native contracts. All 14 saved
MCP byte blocks were independently compared to the original PE for this
repair; all agree.

- At VA `0x0050C3C0` / RVA `0x0010C3C0`, the complete 25-byte body loads
  the second stack argument into EDX and the receiver into ECX; loads its
  vptr; pushes 4, data, and VA `0x0108920C` (the NUL-terminated `ObjectID`
  literal); calls virtual slot `+0x90`; and executes RET without modifying
  EAX. This helper does not synthesize a return or discard the native one.
- At VA `0x00BE7660` / RVA `0x007E7660`, the native Xfer constructor installs
  VA `0x01129258`. The DWORD at vtable `+0x90` is VA `0x00DD67B0` / RVA
  `0x009D67B0`, exported as `?XferEnum@Xfer@@UAEAAV1@PBDPAXI@Z`.
- The native slot implementation saves the receiver in ESI; every successful
  size arm (1 through 4) moves ESI to EAX and returns with RET 12. Invalid
  size throws. Thus the successful return is the same Xfer receiver.
- Native StateMachine serializer RVA `0x000A1510` consumes that returned
  EAX at RVA `0x000A16D8` and `0x000A16F0`, follows its vptr, and continues
  Coord3DBase/Bool transfer chains. This independently demonstrates that the
  helper is used as a returning transfer, not merely that EAX happens to be
  live after a void call.
- Original ILT RVA `0x0000C9B4` is E9 to RVA `0x0010C3C0`. All 146 typed
  call-site relocations found in the 63 emitting audited caller sources
  independently encode that ILT and reach exactly this body. The inventory
  also covers a comment-only source, an unused declaration, and the provider
  TU, totaling 66 files and 339 selected function rows.

The native function remains address-qualified because the ObjectID string and
return contract do not establish an original free-function spelling. The
local receiver view positions the call at +0x90 without touching the existing
separate +0x90/+0x94 issue in the canonical header.

## Legacy candidate reconciliation

The former ILT-only candidates were `friend_xferObjectID`, `bfmeCalcTGC`,
`bfmeHandOver_0000C9B4`, `bfmeThreeCGF`, `bfmeXferObjectID`, and
`xferObjectID0010C3C0`. The first three still had authored callers at this
repair's base; the latter three had no authored C/C++/header uses. None was a
selected real provider. All live calls are migrated coherently; no stale void
declaration or cast-to-void-function-pointer binding remains. Generated
`b_0010c3c0` / `j_0000c9b4` placeholders are not typed identity evidence and are
not edited by this repair. The normal selected-body resolver discovers the
native E9 thunk, so a redundant new pin is unnecessary.

## Verification requirements

Record full family and whole-caller-source verification, all COFF section
payloads and relocation identity changes, before/after pin consistency and
bounded strict link previews. The immutable historical census artifact must
not be rewritten, given fabricated provenance, or described as a fresh global
link result. Existing unrelated link blockers remain visible. No baseline is
expanded.

## MSVC 7.1 incomplete-reference handling

The corrected return is an incomplete `Xfer &` in the provider TU and 20
existing caller TUs. MSVC 7.1 rejects discarding such an lvalue, including an
ordinary `(void)` cast, with C2027. The 59 void macro wrappers therefore bind
an unused local `Xfer &` to the native dispatch result. The 67 genuinely
ignored caller results in those 20 TUs take the returned reference's address
and explicitly discard that pointer, `(void)&Rva0010C3C0(...)`. This performs
an ordinary correctly typed call; it neither casts a function type nor
constructs a return value. Callers with complete Xfer definitions need no
workaround. No empty Xfer definition, extra header, or new helper is used.

`VersionedRecord37A610` had two existing function-pointer return casts. They
are removed only for this provider. Both calls preserve the actual returned
Xfer receiver and view its address through the TU's existing receiver layout;
none substitutes the original input pointer. Four unrelated helper contracts
in that TU retain their existing casts and remain outside this correction.

## Completed byte and COFF checks

- Before and after: 339/339 selected rows pass across all 66 audited TUs,
  with 25 string literals, three empty-string references, 41 float constants,
  and 256 recorded DIR32 references checked by the supported build.
- All 60 provider bodies are exactly 25 bytes, including every independently
  checked DIR32 operand. The 59 unchanged public signatures retain their
  complete native byte sequences.
- The entire emitted COFF section payload, section attributes, relocations,
  and defined/undefined symbols were compared for all 66 objects. Only the
  four proved live callee-name migrations and compiler-local `$L`/`$T`
  ordinal renumberings differ. Each local label is resolved through its
  actual COFF section and offset, including every referencing EH relocation;
  no relocation or data/code byte is ignored. BSS is accounted as zero-fill,
  not mistaken for file bytes at raw pointer zero.
- Pin consistency passes before and after: no new or stale baseline entries,
  all 247 routing rows re-derived, all guarded CRT/DIR32 checks pass. Six
  unused void ILT candidate pins are removed; the corrected selected provider
  needs no symbols.csv pin because the native thunk is discovered normally.

The bounded link-preview receipts retain the unchanged 268232777-byte
historical index, SHA256
`034ebdbd7f13546b5fd7f5f79240e5d75e973fabcc4bad425a0f4ee9dd0d9573`, census
commit `1677ebdc33b984da91173ad45707c94e4fbb7bed`. The 66 current objects are
refreshed using supported `link_check.refresh` at their recorded positions.
Other providers, positions, selected-MAP receipts, and excuses remain
historical. This establishes no new global LINKED total or native link.

Paired preview result: 13 of 66 source objects are clean both before and
after. Exactly 22 old typed-alias unresolved entries disappear, one in each
of 22 caller TUs; no blocker is added or otherwise changed. The other 53
objects retain unrelated blockers, including the provider TU's existing
slot90 data-symbol dependencies. This return-contract prerequisite adds no
new matched-body bytes and establishes no global linked-byte progress.

A supplemental COFF audit also compares every file-header field other than
build timestamp, every complete section header, all primary-symbol metadata
(including type/storage/section/value), and all auxiliary records, including
COMDAT policy/associations/checksums. These all remain equal. Whole-object
hashes can change when the build refreshes intentionally uncacheable TUs;
the full captured section and metadata comparisons, not the timestamped
whole-file hashes alone, establish preservation.
