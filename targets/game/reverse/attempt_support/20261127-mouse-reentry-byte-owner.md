# Existing Mouse reentry byte: one physical owner

One data-owner task, not a new C++ function: the existing accepted
`extern bool Glo012F4C62;` in Mouse.cpp becomes
`bool Glo012F4C62 = false;`. Exactly one newly emitted BSS byte and one
newly admitted 1-byte data row. No method, type, layout, include, source flag,
header, pin, alias, DIR32 record or existing function row changes.

## Independent BFME1 identity and access chain

Existing symbol and DIR32 ledgers both name the same cell at VA012F4C62.
The original writable .data byte reads00. The complete114-byte original
Mouse::updateMouseData at RVA005A42E0 loads that byte at+0, writes1 at+16,
then writes0 at+64 after its event-drain loop. The matched emitted body has
exactly the same three named DIR32 operands (+1,+18,+66). Its bool width,
condition, loop and event-source ABI remain unchanged. A fresh whole-.text
literal-address scan finds exactly those three bound operands; this does not
exclude indirect or derived accesses. No matched datum overlaps the byte.

The existing TheMouse pointer owns VA012F4C5C..60 and TheLookAtTranslator
starts at012F4C64. Neither owns the intervening bool. Narrow actual
game/shim/vendor searches find only the existing declaration and three uses.
The native refreshed before population has22997 current objects, missing0,
stale0 and no strong, COMMON or COMDAT provider of this exact accepted name.

## Donor scope and rejected adaptations

Official archived BFME2 upstream was freshly fetched and remains clean at
e2e99959950e6eebfe1ced5663aa05de320afc52. Existing
Code/GameEngine/Source/GameClient/Input/Mouse.cpp:608ff uses local
`static Bool busy=false` around the corresponding drain. Zero Hour's
GeneralsMD Mouse.cpp has the same role. This corroborates purpose, not the
original BFME1 spelling/linkage. No donor class/layout or local-static name
is imported; adding a second busy cell would leave the accepted reference
unresolved. The donor's later MouseProcessEvents.cpp comment is stale: that
path is absent and provides no proof. No donor or BFME1 build inputs change.

Current linking-first rank/near were consulted first. The highest open
aiMoveToPosition repair still requires its banked EH/ScriptActions COMDAT
selection prerequisite. Sole near-serve Rva008B4630 has the recorded
base-constructor/identity ownership conflict. Neither unchanged blocked
family was retried. This banked, independently supported physical owner was
selected instead; its earlier private pass alone was not treated as admission.

## Ordinary verification and complete emitted-object delta

Fresh normal build.cmd control and candidate each pass24/24 rows, retaining
1876 row bytes, plus the existing2 data rows and16 DIR32 checks. Candidate
has3 verified data rows. Normal add_data_match admits the real named bool:
native sizeof1, allocation extent1, loader-zero00, no relocation in the byte.
Whole runtime graphs have189 nodes each.188 old nodes are exactly preserved.
The sole replaced BSS node grows4->5 bytes: TheMouse remains+0/4B and the
new actual bool is+4/1B. One external definition replaces its former
undefined symbol; no function, dependency, weak route or directive is added.
All29 compiler locals and all old code, data, EH, CRT, RTC, FPO, SafeSEH,
COMDAT flags/associations and runtime relocation edges remain exact. Only
CodeView .debug$S/.debug$T are excluded from the runtime comparison; FPO and
unwind sections are retained. Whole-object equality is explicitly false.

## Evidence boundaries

This relocatable BSS layout is not final retail placement: TheMouse-to-bool
offset is4 in COFF, while original VA distance is6. The normal scalar data
gate resolves each symbol independently and proves this one-byte owner;
no padding/absolute-address/alias workaround is introduced. No final image
placement, complete executable link, startup, crash, memory or speed result
is claimed. Existing function/exact/unique text coverage stays unchanged.

The before preview and frozen object/provider receipt use historical census
42237e2367 (21Nov), refreshed against current objects. Daily tracked queue
01575795f1 is a separate generation. Current posthook native after-provider
and preview receipts are recorded under the diagnostic directory below;
they are required before publication, and are not a new /MAP census.

Diagnostics: W:/OpenBFME/diagnostics/one-per-project-20261127-1848/bfme1.
Tracked receipt JSON binds original image/accesses, native admission,
normal builds and complete precommit object proof. Final frozen manifest
binds the exact committed source, normal hooks, posthook current provider,
whole object and both progress checks. No extra task credit for these checks.

Sicher: original initializer/accesses, admitted1B owner and scoped byte/object
facts. No new gameplay or full-image/runtime effect is established.
