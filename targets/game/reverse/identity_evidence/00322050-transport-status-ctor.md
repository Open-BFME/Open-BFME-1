# `TransportStatus::TransportStatus()` at 0x00322050

* **Body.** `mov eax,ecx / xor ecx,ecx / mov [eax],0x010E1F3C`, then it zeroes
  +4, +8, +0xC and +0x10 and does a bare `ret`. It is 23 bytes long.
* **Whose vtable.** `ScriptConditions::evaluateUnitHasEmptied` (0x00323340) is
  Zero Hour's only TransportStatus allocator. It calls `operator new(0x14)` and
  inlines these same five stores with 0x010E1F3C. It then fills +8 with the
  unit's ObjectID, +0xC with the frame and +0x10 with the unit count, and links
  +4 into the list head at 0x012F06AC. That list is `s_transportStatuses`, and
  its search walks +4 and compares +8. The fields and their order are Zero
  Hour's: `m_nextStatus`, `m_objID`, `m_frameNumber`, `m_unitCount`.
  0x010E1F3C has one slot, a destructor.
* **Other installers of 0x010E1F3C.** The 20-byte destructor 0x00322070 and the
  44-byte 0x00324450, both next to this body.
* **The old home.** 0x000D16F0 has the same shape but installs 0x01083E50, a
  four-slot table that `Player::~Player` also installs. Its name slot
  (0x000D1720) returns "LightPointSystem", so it is not TransportStatus.
* **Previous row.** `??0Rva00322050@@QAE@XZ` (R2ZeroingConstructors.cpp) named
  no class.
