# 0x0016CB60 is AIAttackThenIdleStateMachine::~AIAttackThenIdleStateMachine

## Caller proof

`??_GAIAttackThenIdleStateMachine@@MAEPAXI@Z` (0x0016F310, matched,
`game/GameEngine/Source/GameLogic/AI/AttackStateMachineDeletingDestructors.cpp`)
is the scalar-deleting destructor installed in slot 0 of the vtable
0x010976F8 that the exact constructor 0x00184A40 stores. It calls ILT
0x00006BDB, pinned in symbols.csv to `??1AIAttackThenIdleStateMachine@@MAE@XZ`.

## Stub proof

`tools/pin_consistency.py --symbol '??1AIAttackThenIdleStateMachine@@MAE@XZ'`:
0x00006BDB -> 0x0016CB60, extent 11, verdict consistent.

## Body proof

0x0016CB60 (11 bytes) re-seats the vptr and tail-jumps to the matched
StateMachine destructor (ILT 0x00031D5E -> ??1StateMachine@@MAE@XZ), the empty
Zero Hour AIAttackThenIdleStateMachine destructor. The previous name
`??1Rva0016CB60TailDtor@@UAE@XZ` was an address-derived placeholder.
