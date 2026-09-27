# Integration squash: bank-deletion pairings that are not renames

The integration range carries independent seat commits. Two of them delete a
banked attempt (because its body landed elsewhere) in the same diff that adds an
unrelated new source, and name_regression pairs the deleted bank's local type
name with a placeholder in the unrelated file. Neither is an identity change:

- `targets/game/reverse/attempts/0x00184d50.cpp` was retired because
  `AIAttackSquadState::update` (0x00184D50) landed from the seat commit
  "landed AIAttackSquadState::update 0x00184D50 525B". Its local helper type
  `BfmeAttackStateMachine` was a bank-only scaffold name.
  `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsGarrisonedUnits.cpp`
  is an unrelated ScriptConditions evaluator (0x003252A0) whose opaque
  `Rva003252A0Contain` type is address-derived.
- `targets/game/reverse/attempts/0x007bac10.cpp` was retired because
  `W3DVolumetricShadow::addSilhouetteEdge` (0x007BAC10) landed in
  `W3DVolumetricShadow.cpp`. The bank's `PolygonHolder` was a bank-only local
  name; `Rva007BDB70ArrayOwner` is the pre-existing address-derived type of that
  TU, not a rename of it.
- `targets/game/reverse/attempts/0x00625a00.cpp` was retired because
  `GameSpyInfo::addChat` (0x00625A00) landed; its `parseOnlineChatColorDefinition`
  helper was a bank-local scaffold name. The pairing with the unrelated
  `targets/game/reverse/attempts/0x0078b4f0.cpp` bank (`rva0078B4F0`, a separate
  address-derived near-miss at 0x0078B4F0) is not a rename.
