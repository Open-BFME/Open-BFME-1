# 0x003C2E60 mission objective vector transfer

The 91-byte retail body is a thiscall with one `Xfer *` stack argument and
`ret 4`. It calls virtual slot 1 on that argument, clears the two-byte-element
vector at receiver offset `+0x84` when loading, and then calls the ILT at
0x0001E1FF. That ILT jumps to the matched 0x003C2830
`Rva003C2830XferMissionObjectiveStateVector` body. The matched
`LivingWorldLogic::setMissionObjectiveVisible` and
`setMissionObjectiveCompleted` neighbors independently establish the vector
layout and `MissionObjectiveState` element at offset `+0x84`.

The retail body has no named direct caller or proved vtable ownership, so the
exported owner retains its RVA. The source includes the existing `xfer.h` for
virtual slot 1 and uses STLport `vector::clear`; this naturally produces the
retail's dead copy loop before setting the vector end pointer to its begin.
The scratch probe emitted 91/91 bytes with one relocation slot. The strict
scoped build checks the ILT route and body boundary before the claim lands.
