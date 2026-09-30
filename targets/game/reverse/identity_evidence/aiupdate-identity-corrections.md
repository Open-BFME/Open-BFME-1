# Six refuted AIUpdate identity claims

These corrections preserve all independently proved retail extents. They do
not infer an owner from a compatible scalar offset. The five distinct unknown
accessor bodies remain represented by address-derived classes; the duplicate
command-source claim is retired while its existing GUI row remains.

The evidence was gathered by GPT-6 Sol from the BFME 1.03 image, matched callers,
and the canonical AI constructor and independently reviewed by the orchestrator.
The reconstructed constructor is additional corroboration; the offset evidence
below also comes from already matched callers and methods.

## Command source: 0x001B49AE, 10 bytes

The body writes receiver+0x3C. It has two ledger names:
`AIUpdateInterface::setLastCommandSource` and `AnimateWindow::setAnimType`.
Matched `AIUpdateInterface::privateDock` at 0x00271760 writes the command source
at AI+0x48, as do seven matched command methods using
`BFMEApproachPathFields::m_lastCommandSource`. The independently reconstructed
AI constructor at 0x0027F4B0 also writes CMD_FROM_AI (2) at +0x48.

The +0x3C body therefore cannot be the claimed AI setter. Retire only that
duplicate name. Retain the existing AnimateWindow row and its ten-byte coverage;
this correction makes no new positive identity claim for the GUI method.

## Attitude setter: 0x0045DC60, 13 bytes

This scalar setter writes +0x1F4. The AI method's existing pin is the ILT at
0x00030553, which routes to 0x0027DEF0, a 128-byte matched body currently named
`AIUpdateSetAttitudeShim::setAttitude`. `AIGroup::setAttitude` and six other named
callers reach that body. It has a -3 clear path and stores the attitude at
+0x1F8. Thus 0x0045DC60 is not the AI setter. Its old pristine-Lua ledger note
does not establish an identity and conflicts with its mangled AI name.

The replacement `Rva0045DC60Owner::set(unsigned int)` preserves the complete
13-byte body and +0x1F4 store. It makes no claim about the receiver's real class.
Keep 0x0027DEF0's separate existing row unchanged.

## Ignored-obstacle setter: 0x007F21F0, 13 bytes

This body writes +0x154. Eight named callers reach the actual AI getter via
ILT0x0001A36B to 0x0026F940, a seven-byte read at +0x164. The adjacent matched
setter at 0x0026F930 also writes +0x164; `AIFollowPathState::update` passes
INVALID_ID when leaving an object. This independently refutes +0x154 as the AI
ignored-obstacle offset.

Retain the complete 13-byte body as `Rva007F21F0Owner::set(unsigned int)`.
Do not rename 0x0026F930 or its conflicting `setCompletedWaypoint` pin as part
of this correction; that name requires a separate audit.

## Anonymous getter aliases: 0x002B1020, 0x004A3AA0 and 0x0047A250

The first two distinct seven-byte bodies read +0x154, but their anonymous ledger
rows borrowed the object symbol `AIUpdateInterface::getIgnoredObstacleID`.
The independently proved AI getter instead reads +0x164. The third seven-byte
body reads +0x1F4 and borrowed `AIUpdateInterface::getAttitude`, whose proven
offset is +0x1F8.

Preserve the existing honest `?dup_` names, sizes and RVAs. Replace only their
source and `object-symbol` mappings with the distinct address-derived getters
`Rva002B1020Owner::get`, `Rva004A3AA0Owner::get`, and
`Rva0047A250Owner::get`. Each scratch body reproduces all seven bytes with no
relocations. Equal instruction shapes are not evidence that they share an owner.

## Verification requirements

All five opaque accessors must pass the production scoped byte gate. The retained
AI rows and GUI row keep their original retail ranges. Record the real-name
corrections using `add_match --correct-identity`, preserve durable tombstones,
and supply exact before/after source snapshots for the name guard. The surplus
identity baseline may shrink only for the single retired duplicate. Any later
AI header/constructor change must independently pass its complete header gate.
