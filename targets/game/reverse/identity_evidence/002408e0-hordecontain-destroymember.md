# RVA 0x002408E0 is HordeContain::destroyMember

The 439-byte body implements `HordeContain::destroyMember(Object*)`, through
the HordeContainInterface subobject at complete HordeContain+0xE4. This is an
identity proof, not a byte conversion. It corrects the earlier attribution to
HordeContainInterface itself and the description of VA 0x010AE230 as the
HordeContain table: that table belongs to AODHordeContain.

All addresses were checked against the retail-1.03-unpacked lotrbfme.exe using
pefile and capstone. GhidraMCP's search for `F6 98 43 00` independently returns
VA 0x010AE264, 0x010AED8C and 0x010B0814. Those are the three slot-13 entries
pointing to ILT RVA 0x000398F6, whose E9 targets VA 0x006408E0.

## Concrete owner and inherited implementations

The matched HordeContain constructor at RVA 0x0023EAF0 first writes the
interface-base table VA 0x010AE8E0 to complete receiver+0xE4 at VA 0x0063EB1F.
The first sixteen entries of that base table all point directly to
VA 0x00C8C500, the matched opaque pure-virtual reporting body. At VA
0x0063EB71 the constructor replaces it with VA 0x010AED58. Slot 13 in that
final table is VA 0x010AED8C and resolves to this body.

The named AODHordeContain constructor at RVA 0x00230580 writes VA 0x010AE230
to +0xE4 at VA 0x006305F9; its slot 13 is the same implementation. The named
HorseHordeContain constructor at RVA 0x0024D220 writes VA 0x010B07E0 to +0xE4
at VA 0x0064D27C and inherits the same slot. Their neighbouring class-specific
slots differ. These derived tables corroborate inheritance; they do not make
the body an AODHordeContain, HorseHordeContain or abstract-interface method.

The retail-run file row in ea_evidence.csv at RVA 0x002408E0 names
GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeContain.cpp.
That EA file evidence corroborates the constructor/table owner independently.

## Matched BFME caller names slot 13

The clean matched `HordeContain::createPayload` at RVA 0x0023C000, in
HordeContainCreatePayload.cpp, obtains the interface at complete this+0xE4,
then calls `horde->destroyMember(member)` followed by
`TheGameLogic->destroyObject(member)` while cleaning up copied payload members.
The native caller computes this+0xE4 at VA 0x0063C036 and calls `[eax+34h]`
at VA 0x0063C10D. Offset 0x34 is slot 13. Its later direct call at VA
0x0063C117 resolves through ILT 0x0001D0DE to GameLogic::destroyObject,
RVA 0x0038B0C0. The matched caller's named slot establishes the spelling;
it is not inferred solely from the behaviour of an anonymous body.

## Extent and receiver contract

The body saves the incoming interface receiver in ESI and computes the
complete owner in EBP by subtracting 0xE4. Its one Object* argument is retained
in EBX. It removes the member from two indexes, conditionally destroys the
owning object, stamps the current frame, issues drawable feedback and restores
selected-member state. RET 4 at RVA 0x00240A94, followed by INT3 at
0x00240A97, proves the 439-byte extent and one-argument thiscall contract.

The earlier 159-byte probe was incomplete and the 414-byte reconstruction
was not exact. No current source is banked or installed by this proof. The
remaining blocker is the complete list/index, virtual-call and register-life
layout, not identity. Do not pin the implementation under the abstract
interface owner merely because callers invoke it through that interface.
