# 0027FED0: AssistedTargetingUpdate::assistAttack

The 105-byte body at 0x0027FED0 was matched as the placeholder
?bfmeRun@Gen_0027FED0@@QAEXPAXPAVObject@@@Z. Evidence for the ZH identity
AssistedTargetingUpdate::assistAttack(const Object *, Object *):
- The matched makeAssistanceRequest (0x001E4AA0) finds the
  "AssistedTargetingUpdate" update module, tests isFreeToAssist, and calls
  this body with (requestingObject, victimObject), exactly as ZH Weapon.cpp
  makeAssistanceRequest calls assistAttack.
- The body calls Object::setWeaponLock (ILT 0x3EEBE), then
  AICommandInterface::aiAttackObject(victim, clipSize, CMD_FROM_AI), then twice
  the private ILT 0x21EE5 -> 0x0027FD70, matched as
  AssistedTargetingUpdate::makeFeedbackLaser, with (laserFromAssisted,
  requester, me) and (laserToTarget, me, victim): the ZH body.
- tools/ilt_oracle.py check
  ?assistAttack@AssistedTargetingUpdate@@QAEXPBVObject@@PAV2@@Z 0x0027FED0:
  CONFIRMED (exact).

Bytes unchanged; makeAssistanceRequest is respelled to call it by name.
