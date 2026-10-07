# 0x0027DEF0 is AIUpdateInterface::setAttitude

## Caller proof

Matched `?setAttitude@AIGroup@@QAEXW4AttitudeType@@@Z` (0x00150FE0, 50 bytes,
game/GameEngine/Source/GameLogic/AI/AIGroupBroadcastOrders.cpp) walks the
group's members, reads the member's AI interface at Object+0x204 and calls
`AIUpdateInterface::setAttitude` through ILT 0x00030553 (callees.py), which
jumps to 0x0027DEF0. Zero Hour's AIGroup::setAttitude is exactly
`ai->setAttitude(tude)` for each member
(inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIGroup.cpp).
symbols.csv already pins `?setAttitude@AIUpdateInterface@@QAEXW4AttitudeType@@@Z`
at 0x00030553.

## Body proof

The 128-byte body starts with Zero Hour's `m_attitude = tude` store (+0x1F8)
and adds a BFME clear path for tude == -3. It is matched byte-exact in
game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_setAttitude.cpp,
previously under the placeholder class AIUpdateSetAttitudeShim. The Zero Hour
13-byte body in AIUpdate.cpp was present-unmatched and is removed.
