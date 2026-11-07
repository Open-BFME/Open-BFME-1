# Projected-shadow reset calls at 0x007B3E70 and 0x007B3C70

The two callers enter the existing initializer bodies at 0x007AF200 and
0x007AEB70 through ILTs 0x0000AF38 and 0x0000E9A3. The pinned constructor
shape in Rva007B3CE0Ctor.cpp independently calls the same two providers on
the same subobject, with the four stores in between. The two old member
declarations have no bodies. Call the existing providers with the same
this pointer and keep BfmeThingSE as the caller's allocation and list type.

BFME 2 donor review: f6d845ecd4's Rva0010C065AddDecal.cpp and
W3DProjectedShadow.cpp describe the related manager. Their separate
layout and reset paths do not establish the BFME 1 provider ABI.

The scoped build verifies all four source units. The before/after COFF
comparison changes only four REL32 names. Their offsets, addends, code
bytes and retail targets are preserved.
