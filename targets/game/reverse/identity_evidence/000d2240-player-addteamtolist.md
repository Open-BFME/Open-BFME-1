# 0x000D2240 is Player::addTeamToList

The 66-byte body at RVA 0x000D2240 (previously the address-derived
`?m@Gen_000d2240@@QAEXPAX@Z`) is `Player::addTeamToList(TeamPrototype*)`.

- Callers: `tools/callees.py` on the matched TeamPrototype constructor
  (0x000F3E40, 367 B) and the matched `Team::setControllingPlayer`
  (0x000F44C0, 171 B) each reports one call `0x2c1ce -> 0xd2240`; the ILT
  0x0002C1CE is the only entry to the body. Both callers' source call
  `m_owningPlayer->addTeamToList(this)` / `newController->addTeamToList(...)`
  at those sites, matching the upstream Team.cpp call sites.
- Field offset: the body scans and appends to a list at this+0x288. The
  matched `Player::removeTeamFromList` and `Player::healAllObjects` in
  Player.cpp walk the same team-prototype list at this+0x288.
- Shape: add-if-absent (early return when `team == *it`, then push_back),
  which is upstream Player::addTeamToList.

Player.cpp's Zero Hour copy (list at +0x1A0) was present-unmatched and never
retail; it is removed so the name has one definition.
