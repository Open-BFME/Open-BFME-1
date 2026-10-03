# C3C146: exact native cleanup awaiting the STLport owner

Addresses are RVAs unless explicitly marked VA. No source or pin is changed.

Retail action C3C146 is 14 bytes: load ECX from EBP-EC, subtract6C, tail-jump
via ILT2E40B to5BFA20. The next instruction at C3C154 is the separate handler.
Parent5EEF50 pushes handlerC3C154, which selects FuncInfoE2BBC8 and mapE2BBB0.
State2/predecessor-1 points to this action.

The unchanged native parent is
`game/GameEngine/Source/GameClient/System/FXParticleSystem/DefaultModuleTemplate00WriteINIThunk.cpp`.
Its handler selects `$T771`, whose map is `$T780`; relocation at map+20 selects
`$L746`. The 14-byte action has ten concrete bytes in executable COFF section
0x60501020. Its sole relocation at+10 names
`??1?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ`.
The complete parent passes its gate, two literals, and five DIR32 references.
The cleanup gate fails only because that destructor has no canonical pin.
`add_match` reverted its proposed row after the failure.

## Independent native identity evidence

The complete15-byte body5BFA20 loads the virtual-base adjustment through
[ECX-4] and writes VA0112F304, then RET at5BFA2E followed by INT3.
The vtable at D2F304 has COL VA011DE67C at D2F300. The COL type descriptor
is VA012C7C70, whose in-exe name at EC7C78 is
`.?AV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@`.
Thus the char stream identity is independently anchored by RTTI, not inferred
from the existing writer source. The adjacent wide-stream RTTI is distinct
(VA012C7CAC, char_traits<G>), so this is not a char/wchar alias.

The vtable slotD2F304 contains ILT VA0042986B, which routes to5C23D0.
That scalar deleting destructor repeats the same vptr store, destroys the
virtual base via ILT414BB, tests its low deletion flag, optionally calls
881EB0, and returns4 at5C23FC. This independently supports destructor role
and the virtual-base-adjusted ECX contract used by the cleanup.
The ledger currently retains5BFA20 as opaque `Rva005BFA20::run` in
R2IndirectSlotWrites.cpp; this note does not retire or alias that body.

`pin_consistency.py --symbol` confirms no canonical stream-destructor pin.
`link_check.py next --family stlport --no-claim` reports the family held by
`sol1843-stl-resource`, with the instruction to leave its names alone.
Canonical binding/identity reconciliation belongs to that owner. No competing
pin, source definition, guessed helper name, or nonmatching source is added.
