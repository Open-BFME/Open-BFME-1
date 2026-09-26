// 110 of the image's 429 six-byte __thiscall members with one shape:
//
//     mov eax,<offset string literal> / ret
//
// WHAT THE BYTES SHOW.  Six bytes, no use of ecx, no stack cleanup: a member
// function of no arguments whose whole body is a pointer to a NUL-terminated
// byte string in .rdata.  The immediate is the only variable, and following it
// into the image yields a printable string in every case; the build's own
// `verify_string_refs` re-reads the retail bytes at the referenced address and
// fails on any literal that does not match character for character, so each
// literal below is the retail string and not a plausible-looking substitute.
//
// WHAT THE STRINGS ARE.  Almost all of them are BFME class names -- the AI
// state and state-machine hierarchy, module and behaviour classes, the Snapshot
// side of the save system.  The natural reading is a virtual name accessor that
// each class overrides with its own name, which is also how the surrounding
// engine reports states in its debug output; Zero Hour's `State::getName`
// returns an `AsciiString` member rather than a literal, so this is BFME's own
// shape, not a ported one.
//
// IDENTITY IS STILL NOT RECOVERED, AND THE STRING DOES NOT RECOVER IT.  A body
// returning "AIDockState" is evidence that the string is that class's name; it
// is not evidence that this body is that class's member, because nothing here
// witnesses the enclosing class -- no vftable, no `this`, no call site is
// visible from six bytes.  So each row is named for its own address and the
// literal is carried in the source where it belongs.  Promoting these is a
// mechanical repoint once a vftable pins one of them.
//
// The bodies are kept apart rather than folded: they occupy distinct addresses
// and each references its own distinct string.

#define BFME_LITERAL_NAME_GETTER( NAME, TEXT )                                \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		const char *name() const;                                             \
	};                                                                        \
	const char *NAME::name() const                                            \
	{                                                                         \
		return TEXT;                                                           \
	}

BFME_LITERAL_NAME_GETTER( Rva000A12A0Named, "StateMachine" )
BFME_LITERAL_NAME_GETTER( Rva000C84E0Named, "MissionStats" )
BFME_LITERAL_NAME_GETTER( Rva000CBA80Named, "Energy" )
BFME_LITERAL_NAME_GETTER( Rva000CBAD0Named, "Money" )
BFME_LITERAL_NAME_GETTER( Rva000CBB30Named, "Command" )
BFME_LITERAL_NAME_GETTER( Rva000D1720Named, "LightPointSystem" )
BFME_LITERAL_NAME_GETTER( Rva000D1970Named, "Squad" )
BFME_LITERAL_NAME_GETTER( Rva000D4020Named, "PlayerRelationMap" )
BFME_LITERAL_NAME_GETTER( Rva000DD970Named, "Player" )
BFME_LITERAL_NAME_GETTER( Rva000E6130Named, "ResourceGatheringManager" )
BFME_LITERAL_NAME_GETTER( Rva000E9B10Named, "ScoreKeeper" )
BFME_LITERAL_NAME_GETTER( Rva000ED490Named, "EventParameter" )
BFME_LITERAL_NAME_GETTER( Rva000F0D60Named, "TeamTemplateInfo" )
BFME_LITERAL_NAME_GETTER( Rva000F2240Named, "TeamRelationMap" )
BFME_LITERAL_NAME_GETTER( Rva000F2300Named, "TeamFactory" )
BFME_LITERAL_NAME_GETTER( Rva000F4020Named, "TeamPrototype" )
BFME_LITERAL_NAME_GETTER( Rva000F44B0Named, "Team" )
BFME_LITERAL_NAME_GETTER( Rva000F8A30Named, "TunnelTracker" )
BFME_LITERAL_NAME_GETTER( Rva000FFE20Named, "GeometryInfo" )
BFME_LITERAL_NAME_GETTER( Rva00106B70Named, "RadarObject" )
BFME_LITERAL_NAME_GETTER( Rva001076D0Named, "Radar" )
BFME_LITERAL_NAME_GETTER( Rva0010A7E0Named, "Upgrade" )
BFME_LITERAL_NAME_GETTER( Rva00111090Named, "GameState" )
BFME_LITERAL_NAME_GETTER( Rva00113AC0Named, "ModuleData" )
BFME_LITERAL_NAME_GETTER( Rva00113D30Named, "ObjectModule" )
BFME_LITERAL_NAME_GETTER( Rva00113E50Named, "DrawableModule" )
BFME_LITERAL_NAME_GETTER( Rva00122030Named, "UpgradeSoundSelectorClientBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00124AE0Named, "ModelConditionSoundSelectorClientBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00128F80Named, "ModuleFactory" )
BFME_LITERAL_NAME_GETTER( Rva0014AD80Named, "TAiData" )
BFME_LITERAL_NAME_GETTER( Rva0014C2A0Named, "AI" )
BFME_LITERAL_NAME_GETTER( Rva0014E650Named, "AIDockMachine" )
BFME_LITERAL_NAME_GETTER( Rva0014F340Named, "AIInternalMoveToState" )
BFME_LITERAL_NAME_GETTER( Rva0014F3D0Named, "AIDockApproachState" )
BFME_LITERAL_NAME_GETTER( Rva0014F480Named, "AIDockWaitForClearanceState" )
BFME_LITERAL_NAME_GETTER( Rva0014F770Named, "AIDockProcessDockState" )
BFME_LITERAL_NAME_GETTER( Rva00151D00Named, "AIGroup" )
BFME_LITERAL_NAME_GETTER( Rva0015B9F0Named, "AIGuardMachine" )
BFME_LITERAL_NAME_GETTER( Rva0015CDC0Named, "AIPickUpCrateState" )
BFME_LITERAL_NAME_GETTER( Rva0015CE70Named, "AIGuardInnerState" )
BFME_LITERAL_NAME_GETTER( Rva0015CEC0Named, "AIGuardIdleState" )
BFME_LITERAL_NAME_GETTER( Rva0015CF40Named, "AIGuardOuterState" )
BFME_LITERAL_NAME_GETTER( Rva0015E740Named, "AIGuardRetaliateMachine" )
BFME_LITERAL_NAME_GETTER( Rva0015F0E0Named, "AIGuardRetaliateAttackAggressorState" )
BFME_LITERAL_NAME_GETTER( Rva0015F740Named, "AIHarvestMachine" )
BFME_LITERAL_NAME_GETTER( Rva0015FD50Named, "AIHarvestApproachSiteState" )
BFME_LITERAL_NAME_GETTER( Rva0015FE10Named, "AIHarvestPrepareSiteState" )
BFME_LITERAL_NAME_GETTER( Rva001611E0Named, "WorkOrder" )
BFME_LITERAL_NAME_GETTER( Rva00168700Named, "AISkirmishPlayer" )
BFME_LITERAL_NAME_GETTER( Rva0016AB10Named, "AttackStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva0016AB60Named, "AttackMeleeStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva0016ABB0Named, "AttackHordeStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva0016AC00Named, "AttackFireWhileMovingMachine" )
BFME_LITERAL_NAME_GETTER( Rva0016AC70Named, "AttackFireWhileChargingMachine" )
BFME_LITERAL_NAME_GETTER( Rva0016ACF0Named, "MoveOntoWallStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva0016B240Named, "AIAttackMOveStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva0016B5B0Named, "BackAwayAndCowerStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva00170E80Named, "FailureState" )
BFME_LITERAL_NAME_GETTER( Rva00170F10Named, "ContinueState" )
BFME_LITERAL_NAME_GETTER( Rva001710B0Named, "AIBackAwayAndCowerState" )
BFME_LITERAL_NAME_GETTER( Rva00171170Named, "AIAttackMeleeHordeWaitPathState" )
BFME_LITERAL_NAME_GETTER( Rva001711E0Named, "AIAttackAimAtTargetState" )
BFME_LITERAL_NAME_GETTER( Rva00171230Named, "AIWaitState" )
BFME_LITERAL_NAME_GETTER( Rva001713B0Named, "AIAttackSquadState" )
BFME_LITERAL_NAME_GETTER( Rva00171400Named, "AIDeadState" )
BFME_LITERAL_NAME_GETTER( Rva00171470Named, "AIDockState" )
BFME_LITERAL_NAME_GETTER( Rva001714D0Named, "AIHarvestState" )
BFME_LITERAL_NAME_GETTER( Rva00171530Named, "AIHordeEnterState" )
BFME_LITERAL_NAME_GETTER( Rva00171590Named, "AIHordeExitState" )
BFME_LITERAL_NAME_GETTER( Rva001717A0Named, "AIGuardRetaliateState" )
BFME_LITERAL_NAME_GETTER( Rva00171810Named, "AITunnelNetworkGuardState" )
BFME_LITERAL_NAME_GETTER( Rva00171910Named, "AIAttackAreaState" )
BFME_LITERAL_NAME_GETTER( Rva00171970Named, "AICowerState" )
BFME_LITERAL_NAME_GETTER( Rva001719E0Named, "AIQuarrelState" )
BFME_LITERAL_NAME_GETTER( Rva00171A40Named, "AIRampageState" )
BFME_LITERAL_NAME_GETTER( Rva00178130Named, "AIAttackMeleeEngageState" )
BFME_LITERAL_NAME_GETTER( Rva0017CA30Named, "AIAttackState" )
BFME_LITERAL_NAME_GETTER( Rva0017F3E0Named, "AIMoveAndTightenState" )
BFME_LITERAL_NAME_GETTER( Rva0017F600Named, "AIAttackApproachTargetState" )
BFME_LITERAL_NAME_GETTER( Rva0017F770Named, "AIAttackPursueTargetState" )
BFME_LITERAL_NAME_GETTER( Rva0017F7E0Named, "AIAttackFireDuringApproachState" )
BFME_LITERAL_NAME_GETTER( Rva0017F8C0Named, "AIAttackMeleeSquishState" )
BFME_LITERAL_NAME_GETTER( Rva0017FD00Named, "AIFollowPathState" )
BFME_LITERAL_NAME_GETTER( Rva0017FD60Named, "AIMoveAndEvacuateState" )
BFME_LITERAL_NAME_GETTER( Rva0017FDB0Named, "AIMoveAndDeleteState" )
BFME_LITERAL_NAME_GETTER( Rva0017FE00Named, "AIMoveToPositionAndDieState" )
BFME_LITERAL_NAME_GETTER( Rva00180040Named, "AIEnterState" )
BFME_LITERAL_NAME_GETTER( Rva00180090Named, "AICombineState" )
BFME_LITERAL_NAME_GETTER( Rva001800F0Named, "AIEnterAndAttackState" )
BFME_LITERAL_NAME_GETTER( Rva00180390Named, "AIFaceState" )
BFME_LITERAL_NAME_GETTER( Rva001805A0Named, "AIChargeTargetState" )
BFME_LITERAL_NAME_GETTER( Rva00181EC0Named, "AIStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva00183C00Named, "AIAttackMoveToState" )
BFME_LITERAL_NAME_GETTER( Rva00183DB0Named, "AIAttackFollowWaypointPathState" )
BFME_LITERAL_NAME_GETTER( Rva00185740Named, "AIMoveToPositionAndEnterState" )
BFME_LITERAL_NAME_GETTER( Rva0018D990Named, "TurretAIIdleState" )
BFME_LITERAL_NAME_GETTER( Rva0018DA00Named, "TurretAIIdleScanState" )
BFME_LITERAL_NAME_GETTER( Rva0018DA60Named, "TurretAIAimTurretState" )
BFME_LITERAL_NAME_GETTER( Rva0018DAD0Named, "TurretAIRecenterTurretState" )
BFME_LITERAL_NAME_GETTER( Rva0018DB50Named, "TurretAIHoldTurretState" )
BFME_LITERAL_NAME_GETTER( Rva00193ED0Named, "BuildListInfo" )
BFME_LITERAL_NAME_GETTER( Rva0019E7E0Named, "SidesList" )
BFME_LITERAL_NAME_GETTER( Rva001ADD40Named, "TerrainLogic" )
BFME_LITERAL_NAME_GETTER( Rva001B0D90Named, "BuffLogic" )
BFME_LITERAL_NAME_GETTER( Rva001B2AF0Named, "BehaviorModule" )
BFME_LITERAL_NAME_GETTER( Rva001B2D40Named, "FiringTracker" )
BFME_LITERAL_NAME_GETTER( Rva001B3010Named, "UpdateModule" )
BFME_LITERAL_NAME_GETTER( Rva001B3AE0Named, "GhostObjectManager" )
BFME_LITERAL_NAME_GETTER( Rva001B3DE0Named, "GhostObject" )
BFME_LITERAL_NAME_GETTER( Rva001B63A0Named, "Locomotor" )
BFME_LITERAL_NAME_GETTER( Rva001B7490Named, "LocomotorSet" )
