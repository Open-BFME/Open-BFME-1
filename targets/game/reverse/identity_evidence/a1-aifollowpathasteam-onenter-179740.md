# AIFollowPathAsTeamState::onEnter (0x00179740) and AIUpdateInterface::friend_getGoalPathPosition (0x0016FFD0)

BFME 1 target evidence:
- 0x00179740, 670 bytes (ret at +0x29D, int3 after): vtable 0x01099C08 slot 4 of
  AIFollowPathAsTeamState (matched ctor, computePath and onExit siblings);
  `ilt_oracle.py check ?onEnter@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ 0x179740`
  is CONFIRMED. It references the CritterDesync strings 44/45/46 at 0x01099D40,
  0x01099D08 and 0x01099CC4.
- 0x0016FFD0, 62 bytes: bounds-checked lookup `ai->[+0x30]` state machine,
  STLport vector<Coord3D> at +0x44/+0x48, reached only through ILT 0x0000A9D4.
  `ilt_oracle.py check ?friend_getGoalPathPosition@AIUpdateInterface@@QBEPBVCoord3D@@H@Z 0x16FFD0`
  is CONFIRMED (slot 7875); the struct-keyed spelling is CONTRADICTED.
- Compiling Zero Hour's inline AIUpdateInterface::friend_getGoalPathPosition
  (AIUpdate.h) over AIStateMachine::getGoalPathPosition (AIStates.cpp) inside
  onEnter reproduces retail exactly: MSVC 7.1 inlines the first two calls and
  calls the third out of line, and that out-of-line copy is byte-identical to
  0x0016FFD0. The previous name ?getPoint@Rva0016FFD0PathOwner@@... was an
  address-derived placeholder.

Donor evidence (BFME 2, open-bfme-2 45afcff3a6):
Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp,
AIFollowPathAsTeamState::onEnter (BFME 2 0x0034E3A5, matched there), gives the
statement order and log calls. BFME 1 offsets were read from the retail listing.
