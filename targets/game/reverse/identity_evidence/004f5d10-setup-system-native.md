# WOL game setup system callback at 0x004F5D10

2026-09-27, GPT-6. Native extent: 2352 bytes, RET at 0x004F663F;
INT3 padding begins at 0x004F6640. No boundary change or helper credit.

## Identity and independent contracts

The retail string at VA 0x010875BC is `WOLGameSetupMenuSystem`.
FunctionLexicon record VA 0x012A9588 pairs it with VA 0x0041E885;
that five-byte ILT thunk jumps to RVA 0x004F5D10. This independently names
this four-argument cdecl callback and is stronger evidence than the old
brief's misleading incidental vtable/string scan. The source twin is
`WOLGameSetupMenu.cpp`; savePlayerInfo, StartPressed and the adjacent matched
setup/update callbacks independently establish the shared menu state.

The complete 34-target retail call inventory was read before reconstruction.
All calls resolve to existing native/pinned targets except two small
callee-contract repairs, carried here after complete target disassembly:

* 0x004F3F20, 560 bytes: the color helper reads its sole stack index into EBP
  at +0x1D and returns with bare RET. It indexes color combo VA 0x012F4470,
  gets selection/data, checks slot+0x0C against the available palette and
  other slots, writes the color and either broadcasts or formats `Color=%d`
  in a `REQ/` peer request. The complete algorithm agrees with the existing
  TU-private `handleColorSelection(int)` definition. The pin names this
  ordinary cdecl helper, not the inaccurate old automatic ABI inference.
* 0x004F44E0, 497 bytes: +0x1D saves ECX as start position in EBX; +0x3B
  reads the sole stack player index. It queries slot+0x10, rejects occupied
  positions, writes that field, broadcasts for the host or sends
  `StartPos=%d` in a `REQ/` peer request. The original TU-private
  `handleStartPositionSelection(player,startPos)` definition reproduces
  MSVC's private optimized convention: ECX carries startPos, player is
  stack-passed and caller-cleaned; RET is bare. The pin is scoped to that
  retained static definition and is not an external two-stack-argument ABI.

Both pins were absent before this change. `pin_consistency.py --symbol`
was run for each before adding it and `--check` passed afterward.
The slash-command call reuses the already matched, address-derived
`Rva004F1FF0HandleSlashCommands(UnicodeString)` cdecl symbol (465 bytes),
without adding a speculative semantic pin. The source name-regression guard
needs a documented call-site correction: the descriptive old helper definition
remains in the TU, while only this caller names the already matched native
owner. No existing ledger identity is renamed or erased. A same-symbol linker
alias was not accepted by the resolver because the old helper is defined in
this TU, so it was discarded rather than adding an unnecessary extra pin.

## Behavior and layout recovered from retail

The old reference body was incomplete despite a coincidental 2352-byte
compiled extent. The real selection-message arm falls through into the
button-message arm; +0x48F is their shared continuation. The unused Zero Hour
starting-cash/superweapon branches are absent from this BFME callback.
Both setState calls pass an eight-byte connection record whose NAT integer
and port halfword are zero. Retail retains distinct full-expression
connection temporaries at stack offsets +0x34 and +0x3C. Native default
construction and temporary arguments reproduce this without manual frame
storage; named locals incorrectly coalesced the records. PeerRequest is the
already independently verified 0x194-byte object and both request paths use
its existing real constructor/destructor.

Info virtual slots +0xB0/+0xC0/+0xC4/+0xCC/+0xF8 and layout slots
+0/+4/+0x10/+0x14/+0x20 are read directly from the complete retail caller,
and agree with the already matched setup initializer/update views. Layout
runInit receives the actual null user-data argument; deleting the virtual
layout emits its real scalar-deleting destructor dispatch. The GameInfo
byte at +0x429 remains address-labelled `value429` because no independent
field-name witness was available. No shared layout header changed.

The visible canonical StringBase<unsigned short>::isEmpty body is the
existing null-or-zero-length implementation. MSVC naturally inlines the
edit-done test while retaining the emote call. Strings remain canonical
AsciiString/UnicodeString, with real copy/destructor behavior.

## Verification

The original 0.38 bank was the starting point. Fresh read-only Ghidra and
complete disassembly exposed the control-flow and temporary-lifetime errors.
Final production-source strict resolver: 2352/2352 bytes, 159 relocations,
87 resolved REL32 candidates, zero unresolved and zero byte differences.
All new data references are the existing menu globals/string literals;
there are no new instantiated vtables, opaque byte emission, inline assembly,
volatile shaping, artificial stack padding or manual exception-state writes.

`eh_info.py` independently reports 13 unwind states: text, request, narrow
and wide temporary string destruction, plus the real local-static initializer
rollback. The native declarations and full-expression lifetimes preserve
these cleanup actions and their observed state chronology. No empty cleanup
substitute was added. Scratch receipts and full callees/disassembly are in
`build/four-hour-setup/` (system-strict-production.txt, system-eh.txt,
system-callees.txt and retail-0x4f*.asm). The scoped full-menu gate passed 16/16 functions and 89 literals plus
28 empty-string references, protecting its previously matched siblings.
