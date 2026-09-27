# ProductionUpdate::update: complete reconstruction bank

Retail RVA `0029E330` has a complete contiguous extent of **4,685 bytes**,
ending at `0029F57D` after the countdown tail jumps back to the common return.
This is an incomplete byte match, not accepted game code or headline progress.
The executable SHA256 is `c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9`.

The independently native 396-byte constructor `0029C9E0`, 200-byte destructor
`0029D460`, deleting destructor `0029E300`, existing named update pin, and the
Zero Hour ProductionUpdate source establish the module identity. The update
entry receives the secondary UpdateModuleInterface subobject at full object
`+10`; module data and Object therefore occur at receiver `-C/-8`. Calls to
primary ProductionUpdate helpers adjust the receiver back by `10`. The prior
bank emitted only 943 bytes and omitted most factory, upgrade, UI and audio
behavior. Fresh read-only Ghidra and raw disassembly supplied the full BFME
flow; decompiler types and instruction counts were not treated as byte proof.

## Independently checked contracts and BFME details

- Entry helper `0029C380` /111 is zero-argument thiscall, returning the entry
  pointer in EAX. Helper `0029C340` /42 is thiscall(Object*), RET4; it skips a
  null argument or null owner and propagates owner Object+370 when not -1.
- `0029C410` /32 returns AsciiString by value through the hidden result
  buffer, copying receiver+24 and using RET4. The existing Win32BIGFile name
  is wrong-owner legacy evidence. `0029C440` /37 returns AsciiString by value
  with an integer index, copying receiver+38+4*index, RET8. Independent agent
  B decoded both complete bodies. The bank keeps address-derived declarations
  instead of importing those incorrect semantic views or adding pins.
- Move ILT `0003436A` reaches native219-byte AICommandInterface::aiMoveToPosition
  at `000D86C0`, thiscall(const Coord3D*,CommandSourceType), RET8. Retail loads
  the AIUpdate pointer at Object+204 and adjusts it by20 before this call.
  Independently authored ScriptActionsNamedUnitMovement, Rva0024F280 callback,
  PathfindMoveAlliesCellCallbackEc070 and AIPlayerSelectTeamToReinforce agree.
- UI virtual slot34 is `message(UnicodeString,...)`: retail pushes the receiver
  and caller-cleans8 bytes. The original InGameUI header independently declares
  the varargs overload. Modeling it as ordinary thiscall is wrong.
- Door tables at VA010C0D54/64/74 contain `{21,25,29,33}`, `{22,26,30,34}` and
  `{23,27,31,35}`. These differ from the Zero Hour flags and were read directly
  from the image. The 320-bit clear/set fields are ten words each.
- The update includes ordinary units, respawn, upgrades, door maintenance,
  controlled audio lifetime, five addon-name checks, addon object creation,
  two unit-voice list operations, and the final pending countdown. Radar event
  operand is2. Completion comparisons preserve retail unordered behavior.
- Final template resolution calls the override receiver at template+4. The
  addon timed condition call at0029F1FC uses the main created Object, not the
  addon Object. Those details are preserved even when they seem surprising.
- Player+684 is retained as an address-derived receiver: the calls establish
  its layout and ABI, not a new semantic member name. GlobalData defaults are
  not asserted as gameplay configuration.

## Measurement and bounded residue

Final formatted source emits **4,698 /4,685 bytes**, frame **F8 /F4**, with171
relocations and **3,697 differing masked positions**. Positional agreement is
**988 /4,685 =0.210885805763**; the extra13 bytes remain a size failure.
The separate normalized instruction similarity is **0.918**, with123 structural
alignment differences. It is not a 91.8% byte match. The bank score uses the
positional fraction, superseding the old incomplete body's author estimate0.2.

Retail contains141 direct call sites over84 targets. The compiled source has
138 resolved call relocations and three unresolved hidden-string-return sites:
C410 twice and C440 once. Because relocation sites drift, existing additive
resolver candidates can also select the wrong alternative for AudioEventRTS
cleanup, UnicodeString construction and BitFlags construction. The required
physical targets are respectively000B31F0,00065410 and001C5450; a future exact
pass must verify the selected routes, not merely count unresolved names.
No callee pin, shared header, function ledger row or baseline was changed.

The bounded pass corrected full BFME control flow, hidden return ABI, actual
virtual receiver adjustment, varargs UI and value tables; it tried natural
switch/nested-exit structure, exact string scopes, progress temporaries and
native list handling. The residue is broad live-register/stack allocation and
block placement, not one missing instruction. A generic PMF returning an
AsciiString emitted out of line despite force-inline and was rejected. Future
work should begin from this complete source and seek a new authenticated type
or lifetime lever, rather than recreating the incomplete943-byte prefix.

Session GPT-6, approximately30 minutes; model=gpt-6. Source/probes remained
under build until banking. New rebuildable native bytes: **zero**.

## Exact source-diff naming corrections

The guard pairs17 old `slot00`..`slot16` dummy virtual declarations with the
new unrelated ILT extern declarations because both are void no-argument
signatures. They do not represent renamed methods; reserved virtual slots
remain explicitly declared in the new address-derived interface views. The
old `setFlags` parameter of a removed raw call adapter likewise aligns with
an unrelated ILT declaration. Its clear/set behavior remains in the real
clearAndSet call, with the original receiver-relative+6C/+94 buffers.
Finally the old `voiceEntry` named a ProductionEntry pointer passed as audio
construction data in the incomplete prefix. Retail instead constructs from
module-data AudioEventInfoRef+44 plus ObjectID. It is not renamed to ILT04F1B:
that is a separate later notification call. Each correction is hash-locked
to this exact full-source replacement and makes no reusable exception.
