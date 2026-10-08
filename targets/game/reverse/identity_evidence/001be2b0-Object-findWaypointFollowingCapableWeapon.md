# 0x001BE2B0 is ?findWaypointFollowingCapableWeapon@Object@@QAEPAVWeapon@@XZ

The 11-byte body at RVA 0x001BE2B0, matched under the address-derived placeholder `?invoke@Rva001BE2B0@@QAEXXZ` (MemberOffsetTailThunks.cpp), is `Object::findWaypointFollowingCapableWeapon`.

Evidence:
- It is `add ecx, 612` then a tail jump to the matched `?findWaypointFollowingCapableWeapon@WeaponSet@@QAEPAVWeapon@@XZ` (0x001EAEF0): the upstream `return m_weaponSet.findWaypointFollowingCapableWeapon();` with Object::m_weaponSet at +0x264.
- The matched ScriptActions::doNamedFireWeaponFollowingWaypointPath (0x00302A80) calls it through ILT 0x00033361, which symbols.csv pins as this name.
- `python3 tools/ilt_oracle.py check '?findWaypointFollowingCapableWeapon@Object@@QAEPAVWeapon@@XZ' 0x001BE2B0` prints CONFIRMED (exact, p_false=4.57e-04).

The correction preserves the start, extent, instructions and relocation targets.
