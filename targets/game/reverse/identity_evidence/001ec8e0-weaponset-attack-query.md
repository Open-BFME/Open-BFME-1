# 0x001EC8E0: WeaponSet::getAbleToAttackSpecificObject (BFME four-argument form)

## Identity

The matched `Object::getAbleToAttackSpecificObject`
(`ObjectGetAbleToAttackSpecificObjectBFME.cpp`) makes Zero Hour's
`m_weaponSet.getAbleToAttackSpecificObject(attackType, this, target, commandSource)`
call through ILT 0x000291D6. That ILT is pinned under this name and is
`jmp 0x001EC8E0` in the retail image. The body follows Zero Hour's
WeaponSet.cpp step for step:

- the sanity checks (`isEffectivelyDead` at `+0x344`, `isDestroyed` at `+0x90`,
  `victim == source`);
- sameOwnerForceAttack and allowStealthToPreventAttacks;
- the disguiser exception through `ThePlayerList->getNthPlayer` and
  `Player::getRelationship(otherPlayer->getDefaultTeam())`;
- the relationship gate, testing script status bit 0x10 at `+0x343`;
- the apparent-controller check through `ContainModuleInterface`, slot `+0x3C`;
- the tail call to `getAbleToUseWeaponAgainstTarget` (0x001EBEB0) with
  `victim->getPosition()`.

## Member-name correction at Object+0x110

The banked attempt named the member at `Object+0x110` `m_scriptStatus`.
`tools/name_oracle.py --class Object --offset 0x343` returns `m_scriptStatus`
from the layout witness (confidence 1.00). This body also reads `+0x343` as
the script-status byte, in both of Zero Hour's `testScriptStatusBit(TARGETABLE)`
positions. `+0x110` is a different object: a bit array tested through
`WordBitTest000D2F40::test(0x10C)` (0x000D2F40, reached by ILT 0x0000666D).
The oracle has no name for `+0x110`, so the conversion names it `m_field110`,
after its offset, rather than repeat the contradicted name.
