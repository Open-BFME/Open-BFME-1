# 0x002C38B0 GiantBirdSwoopState::rva002C38B0 (578 B)

BFME 1 target evidence:
- Retail 0x002C38B0..0x002C3AF2: thiscall, two `ret 4` exits (+0x224, +0x23F), INT3 after.
- Its only caller is GiantBirdSwoopState::update 0x002C3550 (vtable 0x010C7868 slot 6), which
  calls ILT 0x000163D3 twice with `this` in ECX and one pushed bool (0 after damping the goal
  range, 1 when the owner is inside half its geometry radius of the goal).
- Callees (all matched rows): Object::notifyModelConditionChanged, GameLogic::findObjectByID,
  AIUpdateInterface::findNearestLabeledContactPointOnTarget, GetGameLogicRandomValue
  (GiantBirdAIUpdate.cpp line 623), Object::getWorldspaceBestContactPoint,
  StateMachine::setGoalPosition, Rva002BC260GoalOwner::run.

Donor evidence (open-bfme-2 b5a7b8290a, Code/GameEngine/Source/GameLogic/Object/Update/
AIUpdate/AIGiantBirdSwoopStateOnEnter.cpp): AIGiantBirdSwoopState::rva0036C438(Bool force), the
same helper of the same state's update, has the same contact-point, distance, model-condition
and goal-retarget control flow; BFME 2 adds a weapon-target path BFME 1 lacks.

Name: no caller, vtable or string names the method, so it keeps an address-derived name.
The first landing of update (b99c489cac) spelled the call `setSwooping`, an unproven guess made
while the callee was still a dump; it described nothing the body does (the body re-acquires
the victim contact point and retargets the goal), so it is replaced by `rva002C38B0`.
