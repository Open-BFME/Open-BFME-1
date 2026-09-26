# Player::addRadar is at 0x000CBFA0

The 67-byte `RadarUpgrade::upgradeImplementation` body at `0x002D7BD0` calls
`Object::getControllingPlayer` through ILT `0x00020824`, reads the module-data
byte at `+0x70`, pushes that byte as a Boolean, and calls ILT `0x000179FE`.
That ILT jumps to `0x000CBFA0`. The Zero Hour counterpart in
`reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/RadarUpgrade.cpp`
does exactly `player->addRadar(md->m_isDisableProof)` at this point. BFME's
`RadarUpgrade::friend_newModuleData` factory clears byte `+0x70` in its
0x74-byte allocation. The retail call and the upstream source independently
establish the Boolean argument and `Player` owner.

`Code/GameEngine/Source/Common/RTS/PlayerAddRadar.cpp` implements the 215-byte
body at `0x000CBFA0` in clean C++. It updates the radar and disable-proof radar
counts and plays the radar-online sound on the transition. The Zero Hour twin is
`Player::addRadar(Bool)` at `GeneralsMD/.../Common/RTS/Player.cpp:3164`.
`Code/GameEngine/Source/GameLogic/Object/Object_onDisabledEdge_Thunk.cpp`
contains a second typed `Player` call routed through the same ILT.

The old `Player::addRadar(bool)` claim at `0x000FB3F0` is false. Its naked
emitter ends in `ret 8`, whereas the single-Boolean method returns with `ret 4`.
The matched caller `Rva000D9680Player::rva000D9680` at `0x000D9680` passes a
`ThingTemplate *` and a player pointer with `this = Player + 0x684`; its call
goes through ILT `0x00049B1B` to `0x000FB3F0`. The callee's other calls include
the template helper at `0x0013FC80`. Its identity beyond the witnessed
two-argument signature remains unknown, so the already pinned
`Rva000FB3F0::rva000FB3F0` address-derived name is appropriate.

This correction changes the two identities while retaining their already
verified sources and extents. The `0x000FB3F0` naked source still contains
trailing `int3` bytes after its `ret 8`; its extent remains a separate lift
correction for a future clean C++ conversion.
