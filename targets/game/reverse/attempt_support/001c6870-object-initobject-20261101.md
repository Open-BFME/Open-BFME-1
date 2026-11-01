# 0x001C6870 Object::initObject — bank at 6 non-reloc bytes (933/933 B)

Session 523 (claude-opus-5-5), 2026-11-01. Bank: `targets/game/reverse/attempts/0x001c6870.cpp`.

## Evidence
- Identity: present-unmatched `Object::initObject` in game/.../Object/Object.cpp, ThingFactory caller, ZH
  GeneralsMD twin (earlier verdicts). Boundary 933 B, ret at +0x3A4 (+ tail-duplicated
  getControllingPlayer null arm at +0x391).
- Body written from the retail listing (ZH shared prefix, then BFME work). Every callee resolved to a
  ledger/pin name (callees.py): updateUpgradeModules, GameLogic::sendObjectCreated 0x38B1B0,
  Team::getControllingPlayer 0xEC8F0, Player::friend_applyDifficultyBonusesForObject 0xCE560,
  Player::applyBattlePlanBonusesForObject 0xD5C00, Player::bfmeObjectEnteringInfluence (pin at ILT
  0x29875, as ObjectTeamAndPlayer.cpp), Overridable::getFinalOverride 0x87A80 / friend_getFinalOverride
  0x97880, ScriptEngine::notifyOfObjectCreationOrDestruction, WeaponSet::updateWeaponSet,
  WeaponStore::allocateNewWeapon, Weapon::loadAmmoNow, EmotionSystem::rva0037CFF0,
  GameLogic::_bfme_isInLivingWorldCampaign, StringBase<char>::set (direct 0x887C90),
  Rva00364B10LivingWorldPlayerArmyCollection::scanArmyGroups (TheGameLogic+0x170),
  ExperienceLevelSystem::gainLevel, ExperienceTracker::bfmeResetScalarBaseCount,
  BfmeObjectReferenceStore::updateObjectReference (pin at ILT 0x1F816, receiver 0x012F0FE0),
  ScoreKeeper::addObjectBuilt (Player+0x348). Template-name literal "RohanSamWithFrodoPowers" (0x0109EC04).
- BFME 2 donor Code/.../Object/ObjectInitObject.cpp (45afcff3): only the extra-weapon statement order
  carried (BFME 2's other additions do not exist in BFME 1).

## Levers found
- Real `ascii_string.h` getLength()/str() (TheNullChr) fixed the template-name compare's two separate
  null diamonds (a private view jump-threads them).
- isKindOf form decides two coupled things: Int `(w & m) != 0` keeps retail's `or edi,-1` constant
  CSE (m_lastWeaponCondition store + m_370 == -1) but narrows the bit-88 test to `test byte [eax+0xd3],1`;
  UnsignedInt `w & m` (or bool two-level `!= 0`) gives retail's `test dword [eax+0xd0],0x1000000` but
  drops the -1 CSE (334 diffs from the prologue on). Ablation: removing the bit-88 test in the Int
  version also drops the CSE, so the narrowed site-2 test is what enables it.
- Bank (`(x ? false : true)` at site 2 in the Int version): CSE kept, only site 2 differs
  (`mov al,[eax+0xd3]; not al; test al,1; je` vs `test dword ...; jne`), 6 bytes at +0x171.

## Ruled out (all on the CSE / site-2 coupling)
volatile kind words, explicit masks/shifts, `== 0`, `!!`, if/return, Bool chains (shr form), signed
arrays, `!(a||b)`, nested ifs, Bool/Int locals, enum/unsigned/loop/const-local spellings of the -1,
battle-plan sum orders, inline vs forceinline accessors, /G5 /G6 /G7 /GB /O1 /Os /Ox /Oa /Ow /Ob1.

## Resume
Find a site-2 spelling that keeps `test dword [mem], imm32` while the -1 stays CSE'd, or the
retail-side reason the -1 is CSE'd with a dword test (a third -1 use? different m_lastWeaponCondition
declaration?).

## Later data point
- `(w & 0x1000000) < 1` at site 2 keeps the CSE with an imm32 `and eax,0x1000000; cmp eax,1` (937 B),
  so the 0x1000000 immediate itself is not what blocks the CSE: only the `test dword [mem],imm32`
  form does (also `!= mask`, `> 0`). `(w >> 24) & 1` and `>> 24` forms narrow like the Int version.
