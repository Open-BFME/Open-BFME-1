# AIStateMachine constructor, RVA 0x00185A20

The complete native constructor is 4,930 bytes and registers 61 states. The
already-native AIUpdateInterface, AnimalAIUpdate and SupplyTruckAIUpdate factories
call this body through its ILT. The installed machine table VA 0x0109AEF8 has a
name slot routing to 0x00181EC0, which returns AIStateMachine. These are independent
identity witnesses, not names inferred from a byte match.

The original GeneralsMD AIStates.cpp constructor establishes the allocation and
registration algorithm. BFME changes the ID table and adds states: all 61 size,
constructor, state ID, success ID and failure ID tuples were decoded directly from
this complete retail body. Numeric registration IDs in the source deliberately
preserve BFME values rather than borrowing the incompatible ZH enum values.

## Layout and source shape

State has its 0x24-byte prefix proven by native State::State at 0x000A19E0.
AIInternalMoveToState has the 0x50-byte prefix used by its independently matched
constructor at 0x0014F280. StateMachine occupies 0x44 bytes; AIStateMachine's path
vector is +0x44, waypoint +0x50, squad +0x54, temporary state +0x58 and expiry +0x5C.
The already-native AIStateMachine::xfer at 0x00187C50 independently proves object
ID +0x60 and Coord3D +0x64. Native STLport vector::clear and Coord3D::zero reproduce
the exact retail reads and instruction scheduling. The complete size is 0x70.

State-class definitions are local constructor/layout views. Semantic class names
are checked against constructor literals, virtual-name getters and the original
hierarchy. The intermediate movement-prefix type retains its address because this
investigation does not independently establish a distinct semantic identity.
Unknown member names retain their byte offsets. No shared header is changed.

## Virtual-name evidence

Each table below is read from the corresponding vptr store in the retail parent.
Its name getter is slot 2, with the ILT independently followed. A derived class can
inherit a base name getter: those cases use its constructor literal and original
hierarchy as the additional witness. This distinction prevents the getter from
misnaming a derived state.

| Local constructor view | Vtable VA | Name getter RVA | Returned literal |
|---|---|---|---|
| `AIStateMachine` | 0x0109AEF8 | 0x181ec0 | AIStateMachine |
| `AIIdleState` | 0x010985B0 | 0x172140 | AIIdleState |
| `AIMoveToState` | 0x01098F08 | 0x14f340 | AIInternalMoveToState |
| `AIMoveToStateSA` | 0x01098FA8 | 0x173670 | AIMoveToStateSA |
| `AIMoveOutOfTheWayState` | 0x0109A278 | 0x14f340 | AIInternalMoveToState |
| `AIMoveAndTightenState` | 0x0109A2F0 | 0x17f3e0 | AIMoveAndTightenState |
| `AIMoveAwayFromRepulsorsState` | 0x0109A368 | 0x17f3e0 | AIMoveAndTightenState |
| `AIWanderInPlaceState` | 0x0109A910 | 0x17fbd0 | AIWanderInPlaceState |
| `AIFollowWaypointPathExactState` | 0x0109A828 | 0x17faf0 | AIFollowWaypointPathExactState |
| `AIMoveAndEvacuateState` | 0x0109AA60 | 0x17fd60 | AIMoveAndEvacuateState |
| `AIMoveAndDeleteState` | 0x0109AAD8 | 0x17fdb0 | AIMoveAndDeleteState |
| `AIWaitState` | 0x01097CD8 | 0x171230 | AIWaitState |
| `AIStartAttackObjState` | 0x01097A20 | 0x170fa0 | AIBusyState |
| `AIMoveOntoWallState` | 0x01098540 | 0x171da0 | AIMoveOntoWallState |
| `AIAttackSquadState` | 0x01097E30 | 0x1713b0 | AIAttackSquadState |
| `AIMoveAwayPanicState` | 0x0109A3E0 | 0x17f3e0 | AIMoveAndTightenState |
| `AIFearState` | 0x0109A458 | 0x17f3e0 | AIMoveAndTightenState |
| `AICowerState` | 0x01098408 | 0x171970 | AICowerState |
| `AIUncontrollableCower` | 0x010991D0 | 0x174500 | AIUncontrollableCower |
| `AIMoveAwayAndCowerState` | 0x0109AD88 | 0x1804a0 | AIMoveAwayAndCowerState |
| `AIBackAwayAndCowerState` | 0x01097AF8 | 0x1710b0 | AIBackAwayAndCowerState |
| `AIDeadState` | 0x01097EA0 | 0x171400 | AIDeadState |
| `AIDockState` | 0x01097F08 | 0x171470 | AIDockState |
| `AIHarvestState` | 0x01097F70 | 0x1714d0 | AIHarvestState |
| `AIEnterState` | 0x0109ABD0 | 0x180040 | AIEnterState |
| `AICombineState` | 0x0109AC38 | 0x180090 | AICombineState |
| `AIEnterAndAttackState` | 0x0109ACA8 | 0x1800f0 | AIEnterAndAttackState |
| `AIExitState` | 0x01098120 | 0x171660 | AIExitState |
| `AIHordeEnterState` | 0x01097FD8 | 0x171530 | AIHordeEnterState |
| `AIHordeExitState` | 0x01098048 | 0x171590 | AIHordeExitState |
| `AIGuardState` | 0x010981E0 | 0x171740 | AIGuardState |
| `AIGuardRetaliateState` | 0x01098248 | 0x1717a0 | AIGuardRetaliateState |
| `AITunnelNetworkGuardState` | 0x010982B8 | 0x171810 | AITunnelNetworkGuardState |
| `AIHuntState` | 0x01098330 | 0x171890 | AIHuntState |
| `AIAttackAreaState` | 0x01098398 | 0x171910 | AIAttackAreaState |
| `AIFaceState` | 0x0109AD20 | 0x180390 | AIFaceState |
| `AIPickUpCrateState` | 0x010960D0 | 0x15cdc0 | AIPickUpCrateState |
| `AIBusyState` | 0x01097AA0 | 0x171040 | AIBusyState |
| `AIRampageState` | 0x010984D8 | 0x171a40 | AIRampageState |
| `AIMoveToPositionAndDieState` | 0x0109AB50 | 0x17fe00 | AIMoveToPositionAndDieState |
| `AIMoveToPositionAndEnterState` | 0x0109B370 | 0x185740 | AIMoveToPositionAndEnterState |
| `AIQuarrelState` | 0x01098470 | 0x1719e0 | AIQuarrelState |

The ledger's older AIIdleState pin to 0x0109AD20 disagrees with that table's own
AIFaceState getter and its native AIFaceState::update owner at 0x00189660. Likewise,
0x010991D0 returns AIUncontrollableCower, while 0x01098408 returns AICowerState.
This landing uses the independently witnessed identities and adds no vtable pins
or second claims on these existing helper bodies. The older helper names remain
separate correction work; they are not identity evidence for this constructor.

## ABI and verification

All 17 distinct direct targets resolve under strict REL32 verification, with zero
unresolved symbols. The protected StateMachine::defineState spelling and its const
StateConditionInfo pointer agree with the shipped declaration and native 196-byte
owner at 0x000A2030. State, AIInternalMoveToState, AIFollowPathState,
AIFollowPathAsTeamState and attack constructors agree with their independent
owners and hidden by-value AsciiString ABI. A second agent independently reviewed
the direct call inventory and declarations. AIStateMachine's protected virtual
destructor agrees with the proven scalar-deleting wrapper at 0x00187240.

The complete compiled body is exactly 4,930 bytes with 338 relocations; the strict
add_match gate passes 1/1 and verifies all 50 string literals. No new callee pins
are needed. The original naked lift is deleted. The full 61 allocation/EH schedule
is generated by native new expressions, not copied instructions or encoded bytes.
