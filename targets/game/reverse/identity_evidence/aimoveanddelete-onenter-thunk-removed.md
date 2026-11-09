# AIMoveAndDeleteState_onEnter_Thunk.cpp removal

The removed file held a stale second lift of AIMoveAndDeleteState::onEnter with
local placeholder layout views (`m_unreconstructed_*`). The verified owner of
retail 0x0017A430 is AIMoveAndDeleteState_onEnter.cpp, which uses its own
`m_pad*` views of the same retail offsets (AIInternalMoveToState +0x04 pad 0x18,
+0x20 pad 4, +0x30 pad 0x1C). The name checker pairs the deleted file with that
owner; no name was lost, the placeholder views simply disappeared with the file.
The two rows it still owned (StateMachine::lock 0x0014E5E0 and
AIInternalMoveToState::setAdjustsDestination 0x00360700) are emitted with
retail-equal bytes by the owners they were rehomed to (build.sh: Functions OK 5/5).
