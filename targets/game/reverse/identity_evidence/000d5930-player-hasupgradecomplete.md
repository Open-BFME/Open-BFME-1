# 0x000D5930 Player::hasUpgradeComplete(const UpgradeTemplate *) const (54 B)

Replaces `?hasUpgradeComplete@Player@@QBE_NPBVBfmeThingEL@@@Z`.

BFME 1 target evidence:
- `tools/ilt_oracle.py` CONFIRMS `?hasUpgradeComplete@Player@@QBE_NPBVUpgradeTemplate@@@Z`
  at 0x000D5930 (thunk ILT 0x000235BF) and CONTRADICTS the old row name, the
  non-const `QAE` pin at the ILT and the `PAV` variant.
- Callers pass an upgrade template (RefundDie::onDie, DelayedDeathBody,
  FreeLifeBody, ProductionPrerequisite::isSatisfied, AIPlayer upgrade build,
  PropagandaTowerBehavior::doScan); the body tests bit `template+0x20` of the
  player's completed-upgrade words at +0x8C, returning false for null.

Donor/ZH: Zero Hour declares `Bool hasUpgradeComplete(const UpgradeTemplate*)`
non-const; the BFME 1 const qualifier comes from the ILT confirmation only.
Link queue #90 (census bb53b24f2b): the private-view callers spelled the
non-const name, which the link resolved to Player.cpp's Zero Hour copy.
