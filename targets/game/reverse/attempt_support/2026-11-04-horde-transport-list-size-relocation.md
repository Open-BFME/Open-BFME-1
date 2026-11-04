# Horde transport admission: list-size ownership conflict

Queue #43 (`isValidContainerFor@HordeTransportContain`), BFME 1 c84f680268.
Normal scoped verification of HordeTransportContainIsValidContainerFor.cpp and
HordeSiegeEngineContainIsValidContainerFor.cpp passes both existing rows (2/2).
Census 77a8439ee4 nevertheless judges the only transport provider wrong.

Fresh RetailTruth comparison of its normal verified object isolates exactly
one bad relocation and zero masked-byte differences over the full 112 bytes:
REL32 +0x51 calls ILT 0x0000C176 -> 0x000F88F0 in retail, but C++ names
`_STL::list<int>::size() const`. That name's authoritative matched row now
owns 0x0020AE10 (24B, identity evidence s554-gen-alias-comdat-h.md). Its
separate ILT is 0x00034437. The old candidate pin cannot override the row.
The called body at 0x000F88F0 is currently a tg alias emitted by
SubsystemLegend.cpp as list<SubsystemLegendEntry>::size; this does not prove
that the horde member list contains those entries either.

This is a template identity/ownership problem, not a capacity comparison or
caller scheduling mismatch. Changing the list element spelling to an unrelated
instantiation just to select matching bytes would invent a layout claim.
Establish the actual horde list element type and reconcile its size provider
with the existing alias before changing either caller or ledger.

BFME 2 c8b988aae8f06e96b73717239e0bb8f1e7ec23d4, corresponding
Code/GameEngine/Source/GameLogic/Object/Contain/HordeTransportContainIsValidContainerFor.cpp,
was reviewed from git objects. Its 147-byte, three-argument admission uses
virtual reserved/contained counts and Object::getTransportSlotCount instead of
this BFME 1 list-size call. It supplies no element identity or compatible direct
repair; its +0x98 capacity layout is not BFME 1's +0x168. No donor edit applied.

Before and after source inspection, census-only verdict is 0 linked bytes for
both consumers (historic wrong selected provider). Current linked bytes remain
unknown without a complete current object census. No source, pin, ledger or
bank changed. model=gpt-6.1-sol; t=8min; boundary=0x0024BD70+112B.
