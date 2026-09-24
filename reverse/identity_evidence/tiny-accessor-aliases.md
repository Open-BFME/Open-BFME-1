# Retired aliases on seven tiny accessor bodies

Retail was linked without identical-COMDAT folding, so no two functions
share a body. Grouping the ledger's 48,262 distinct bodies of 4 to 16
bytes (outside the ILT) by their exact retail bytes, 848 byte patterns
are carried by two or more separate bodies: `mov eax,ecx; ret 4` by 953
bodies, `mov eax,[ecx+4]; ret` by 487, `mov eax,[esp+4]; ret 4` by 373.
Template instantiations are always COMDATs, and 16 distinct
`vector<T>::end` / `_Rb_tree::size` bodies of `mov eax,[ecx+4]; ret` and 6
distinct `get_allocator` bodies were not folded either. So each body below
has exactly one identity, and a second real name on it was chosen for the
byte shape alone.

| body | retired rows | kept row | why the kept row is the body |
|---|---|---|---|
| `0x000B2330` | `AnimateWindow::setFinished` | `AudioEventRTS::setIsLogicalAudio` | all 11 named callers are audio and music code; `ScriptActions` music changes call `setIsLogicalAudio` in Zero Hour |
| `0x000B23C0` | `LANGameSlot::setLastHeard` | `AudioEventRTS::setPlayerIndex` | 24 callers set a sound's player; see below for the slot layout |
| `0x00499840` | `Object::friend_setPartitionData` | `WinInstanceData::setVideoBuffer` | all 11 callers are `WindowVideo`, `WindowVideoManager` and the cameo movie |
| `0x00673F30` | `BuildListInfo::setNextBuildList` | `NetWrapperCommandMsg::setNumChunks` | both callers are `NetPacket::readWrapperMessage` and `ConstructBigCommandPacketList`, the two Zero Hour callers of `setNumChunks` |
| `0x00673F70` | `GameSlot::setPort` | `NetWrapperCommandMsg::setWrappedCommandID` | the same two wrapper functions, which call `setWrappedCommandID` in Zero Hour |
| `0x008E21C0` | `AssetIterator::First`, `AABTreeIterator::Reset`, `Money::init` | `CullSystemClass::Reset_Collection` | pinned; both callers are the `GridCullSystemClass` functions that call `Reset_Collection` in `gridcull.cpp` |
| `0x00912040` | `View::setZoomLimited` | `PointGroupClass::Set_Point_Orientation` | pinned from its only caller, `ParticleBufferClass::Render_Particles` |

Independent of folding, five retired names are contradicted by retail
directly:

- `View::setZoomLimited` and `AssetIterator::First` are virtual. A virtual
  function's body is referenced from its class's vtable, but no dword
  anywhere outside `.text` points at `0x00912040` or `0x008E21C0`.
- `Object::friend_setPartitionData` stores `+0x1A4`, which is
  `m_disabledMask` in `docs/object_layout.md` (15 byte-verified copies);
  `m_partitionData` is at `+0x3B0`.
- `BuildListInfo::setNextBuildList` stores `+0x30`. Retail
  `Player::addToBuildList` (0x000CD830) stores `m_nextBuildList` at
  `+0x2C`, and `SidesInfo::addToBuildList` (0x00191510) walks the list
  through `+0x2C`.
- `LANGameSlot::setLastHeard` stores `+0x5C`. Retail
  `LANGameSlot::getUser` (0x0068DE20) copies the slot's `m_lastHeard`
  from `+0x64` into `m_user` (Zero Hour:
  `m_user.setLastHeard(getLastHeard())`).

The retired names keep their definitions in their sources. Where they
really live in retail is not settled here: `Money::init` is probably one
of the `a_000c89b0` / `a_000c8be0` bodies beside `Money::withdraw` and
`Money::deposit`, which compile from its symbol.
