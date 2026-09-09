// ?addScience@Player@@AAE_NW4ScienceType@@@Z
// partial score=0.55 date=2026-09-09
//
// Apply this diff on top of Code/GameEngine/Source/Common/RTS/Player.cpp's
// existing (present-unmatched) Player::addScience body, retail 0x000D5380,
// 438 bytes:
//
// BLOCKED, not just a near miss: BFME rewrote the setReadyFrame tail. The
// existing scratch body in Player.cpp is a verbatim ZH port with three wrong
// member offsets; fixing those layout offsets gets the compiled body exact
// through retail +0x108 (onSpecialPowerCreation call, slot 0x20) -- i.e. the
// hasScience-inline, m_sciences.push_back, m_playerTeamPrototypes walk,
// TeamPrototype+0x274 instance-list walk, Team+0xC PMF member walk, the
// Object+0x1f0 behavior-module array, and the getSpecialPower/
// getRequiredScience/onSpecialPowerCreation calls (module+0xc adjustor,
// slots 0x1c/0x1c/0x20) ALL match retail once corrected. See the layout
// fixes below, all reusing structs already declared earlier in Player.cpp:
//   - m_sciences.push_back(science) must go through a BfmePlayerAddScienceFields
//     view (this+0x234), matching hasScience's own cast.
//   - m_playerTeamPrototypes iteration must go through BfmePlayerTeamFields
//     (this+0x288), matching countObjectsByThingTemplate.
//   - (*it)->iterate_TeamInstanceList() must go through
//     BfmePlayerTeamPrototypeInstances/BfmePlayerTeamInstanceIterator
//     (TeamPrototype+0x274), matching ungarrisonAllUnits.
//   - team->iterate_TeamMemberList() must go through BfmePlayerTeamView /
//     BfmePlayerDlinkIterator<BfmePlayerObjectDlinkObject>, same as above.
//   - obj->getBehaviorModules() must be replaced by a raw
//     *reinterpret_cast<BehaviorModule***>((char*)obj + 0x1f0) read, matching
//     ActionManager.cpp / Object.cpp's findSpecialPowerModuleInterface.
//
// What does NOT correspond to the ZH reference (Player.cpp:2535 upstream),
// i.e. the real wall: after onSpecialPowerCreation(), ZH calls
// sp->setReadyFrame(TheGameLogic->getFrame()) unconditionally. Retail instead:
//   mov ecx, [TheBfmeGameLogic]                  ; NOT TheGameLogic
//   call j_0001e0ab -> 0x00782c20                ; GameLogicPortraitShim::
//                                                 ; isInMultiplayerOrSkirmishGame()
//   test al, al
//   je <else-branch>
//   ; then-branch: push [TheBfmeGameLogic+0x3c] (a cached frame field, NOT a
//   ;   getFrame() call); call sp-vtable slot 0x24 (setReadyFrame)
//   ; else-branch (no args): call sp-vtable slot 0x40 (a different method
//   ;   entirely -- not present in the BfmeSpecialPowerModuleVtbl_30 shim,
//   ;   which only goes up to slot 0x34/doSpecialPowerAtLocation)
// This two-way branch keyed on isInMultiplayerOrSkirmishGame(), reading a
// cached TheBfmeGameLogic+0x3c frame field on one arm and calling an
// unidentified slot-0x40 method on the other, has no counterpart in the ZH
// source at all -- it is a genuine BFME rewrite of addScience's tail, not a
// register/scheduling residue. Needs slot 0x40's real signature identified
// (0 args per the retail call site) before this can be finished.
//
// t=30min model=sonnet-5.1 score=0.55
