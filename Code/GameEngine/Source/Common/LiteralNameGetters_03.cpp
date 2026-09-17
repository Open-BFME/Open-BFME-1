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

BFME_LITERAL_NAME_GETTER( Rva00260640Named, "ManTheWallsSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00262920Named, "OCLSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00263A10Named, "PlayerHealSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00264830Named, "RepairSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00264D00Named, "RousingSpeechUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002658F0Named, "ScavengerSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00265B80Named, "SiegeDeployHordeSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00267630Named, "SpecialDisguiseUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00269060Named, "SpecialPowerModule" )
BFME_LITERAL_NAME_GETTER( Rva0026AFE0Named, "SpecialPowerUpdateModule" )
BFME_LITERAL_NAME_GETTER( Rva0026B070Named, "SplitHordeSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0026B390Named, "StopSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0026C020Named, "ToggleHiddenSpecialAbilityUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0026CCC0Named, "WeaponChangeSpecialPowerModule" )
BFME_LITERAL_NAME_GETTER( Rva0026D3C0Named, "WeaponFireSpecialAbilityUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0026DCA0Named, "WeaponSetSpecialAbilityUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0027F1C0Named, "AIUpdateInterface" )
BFME_LITERAL_NAME_GETTER( Rva0027FC10Named, "AssistedTargetingUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00280E10Named, "AutoDepositUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002814E0Named, "AutoFindHealingUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00281B90Named, "AutoPickUpUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00283390Named, "BannerCarrierUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00285740Named, "BattlePlanUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00287040Named, "BloodthirstyUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00288E30Named, "BoneFXUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002899C0Named, "BroadcastStealthUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028A3B0Named, "CivilianSpawnUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028ABF0Named, "CommandButtonHuntUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028B720Named, "CritterEmitterUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028BD50Named, "DelayedLuaEventUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028C610Named, "DeletionUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028CDF0Named, "DestroyEnvironmentUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028E590Named, "DynamicShroudClearingRangeUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0028FDB0Named, "EmotionTrackerUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00291AE0Named, "EntEnragedUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002922E0Named, "FadeAndDieOrnamentUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00292BF0Named, "FireWeaponUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00293360Named, "FlammableUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00295000Named, "FloatUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002955D0Named, "HeightDieUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00295BA0Named, "HijackerUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00296D40Named, "LargeGroupAudioUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00297730Named, "LargeGroupBonusUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00298200Named, "LifetimeUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00298370Named, "ModelConditionSpecialAbilityUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00298EE0Named, "OneRingPenaltyUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002998C0Named, "PartTheHeavensUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0029A980Named, "PhysicsBehavior" )
BFME_LITERAL_NAME_GETTER( Rva0029CBD0Named, "ProductionUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0029FED0Named, "ProneUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002A0250Named, "RadarUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002A0590Named, "RadiusDecalUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002A0A00Named, "RainOfFireUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002A15F0Named, "RespawnUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002A3720Named, "RubbleRiseUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002A65B0Named, "SpecialAbilityUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002AAFE0Named, "SpecialEnemySenseUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002AB580Named, "StealthDetectorUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002ACD40Named, "StealthUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002AE2E0Named, "StructureCollapseUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002AF2E0Named, "StructureToppleUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B0B90Named, "TemporarilyDefectUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B1150Named, "ToppleUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B2AE0Named, "WeaponModeSpecialPowerUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B2FA0Named, "AnimalAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B4400Named, "AssaultTransportAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B5500Named, "DeployStyleAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B6430Named, "DozerPrimaryStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva002B67E0Named, "DozerAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002B7360Named, "DozerActionPickActionPosState" )
BFME_LITERAL_NAME_GETTER( Rva002B73D0Named, "DozerActionMoveToActionPosState" )
BFME_LITERAL_NAME_GETTER( Rva002B7630Named, "DozerActionStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva002B76E0Named, "DozerPrimaryIdleState" )
BFME_LITERAL_NAME_GETTER( Rva002B77E0Named, "DozerActionState" )
BFME_LITERAL_NAME_GETTER( Rva002B9E00Named, "FoundationAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002BBD10Named, "GiantBirdGuardMachine" )
BFME_LITERAL_NAME_GETTER( Rva002BE050Named, "GiantBirdNormalFlightState" )
BFME_LITERAL_NAME_GETTER( Rva002BE290Named, "AIGiantBirdSwoopState" )
BFME_LITERAL_NAME_GETTER( Rva002BE450Named, "AIGiantBirdAttack" )
BFME_LITERAL_NAME_GETTER( Rva002BEFF0Named, "GiantBirdFollowWaypointPathState" )
BFME_LITERAL_NAME_GETTER( Rva002BF7C0Named, "GiantBirdAttackMoveToState" )
BFME_LITERAL_NAME_GETTER( Rva002C0460Named, "GiantBirdGuardInnerState" )
BFME_LITERAL_NAME_GETTER( Rva002C0540Named, "GiantBirdGuardOuterState" )
BFME_LITERAL_NAME_GETTER( Rva002C05B0Named, "GiantBirdGuardReturnState" )
BFME_LITERAL_NAME_GETTER( Rva002C26D0Named, "GiantBirdAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002C49C0Named, "HordeWorkerAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002C5380Named, "SiegeAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002C59F0Named, "SupplyTruckStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva002C6150Named, "SupplyTruckWantsToPickUpOrDeliverBoxesState" )
BFME_LITERAL_NAME_GETTER( Rva002C61C0Named, "RegroupingState" )
BFME_LITERAL_NAME_GETTER( Rva002C62B0Named, "HarvestingState" )
BFME_LITERAL_NAME_GETTER( Rva002C7070Named, "TransportAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002C7570Named, "WanderAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002C7C60Named, "WorkerAIUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002C8130Named, "WorkerStateMachine" )
BFME_LITERAL_NAME_GETTER( Rva002CE310Named, "RailedTransportDockUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002CED80Named, "RepairDockUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002CF140Named, "SupplyCenterDockUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002CF6E0Named, "SupplyWarehouseDockUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002CFE10Named, "DefaultProductionExitUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002D06C0Named, "QueueProductionExitUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002D1690Named, "SpawnPointProductionExitUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002D23C0Named, "SupplyCenterProductionExitUpdate" )
BFME_LITERAL_NAME_GETTER( Rva002D2B00Named, "ArmorUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D2F00Named, "AttributeModifierUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D3130Named, "AudioLoopUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D3850Named, "BaseUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D41F0Named, "CommandSetUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D45D0Named, "CostModifierUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D4D70Named, "DelayedUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D5020Named, "ExperienceScalarUpgrade" )
