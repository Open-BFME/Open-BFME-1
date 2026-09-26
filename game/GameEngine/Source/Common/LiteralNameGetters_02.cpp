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

BFME_LITERAL_NAME_GETTER( Rva001C0E60Named, "ObjectHelper" )
BFME_LITERAL_NAME_GETTER( Rva001C0F80Named, "ObjectDefectionHelper" )
BFME_LITERAL_NAME_GETTER( Rva001C1160Named, "ObjectRecoveryHelper" )
BFME_LITERAL_NAME_GETTER( Rva001C12A0Named, "ObjectRepulsorHelper" )
BFME_LITERAL_NAME_GETTER( Rva001C1460Named, "ObjectWeaponStatusHelper" )
BFME_LITERAL_NAME_GETTER( Rva001D3E60Named, "Object" )
BFME_LITERAL_NAME_GETTER( Rva001DC250Named, "ObjectTypes" )
BFME_LITERAL_NAME_GETTER( Rva001DFFC0Named, "VictorySystem" )
BFME_LITERAL_NAME_GETTER( Rva001E53B0Named, "Weapon" )
BFME_LITERAL_NAME_GETTER( Rva001EB0C0Named, "WeaponSet" )
BFME_LITERAL_NAME_GETTER( Rva001ED780Named, "AutoAbilityBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001EEAB0Named, "AutoHealBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F0340Named, "BezierProjectileBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F3570Named, "BridgeBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F5AA0Named, "BridgeScaffoldBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F6080Named, "BridgeTowerBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F6830Named, "BuildingBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F6F80Named, "ClearanceTestingSlowDeathBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F7920Named, "ClickReactionBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F7F10Named, "DualWeaponBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001F8A20Named, "UpgradeModule" )
BFME_LITERAL_NAME_GETTER( Rva001F8C10Named, "DynamicPortalBehaviour" )
BFME_LITERAL_NAME_GETTER( Rva001FACB0Named, "EnragedBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001FB1E0Named, "FireWeaponWhenDamagedBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001FBE60Named, "FireWeaponWhenDeadBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001FC380Named, "GateOpenAndCloseBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001FE470Named, "GettingBuiltBehavior" )
BFME_LITERAL_NAME_GETTER( Rva001FFC00Named, "GiantBirdSlowDeathBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00200B30Named, "DieModule" )
BFME_LITERAL_NAME_GETTER( Rva00200BF0Named, "InstantDeathBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00201C20Named, "OathbreakersFadeAwayBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00202210Named, "PassiveAreaEffectBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00202AC0Named, "PoisonedBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00203000Named, "PropagandaTowerBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00203CE0Named, "RampageBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00204620Named, "ReplenishUnitsBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00205800Named, "ShareExperienceBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00206390Named, "SiegeDockingBehavior" )
BFME_LITERAL_NAME_GETTER( Rva002073B0Named, "SlaveWatcherBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00207D00Named, "SlowDeathBehavior" )
BFME_LITERAL_NAME_GETTER( Rva0020CCD0Named, "SpawnTownsmenBehavior" )
BFME_LITERAL_NAME_GETTER( Rva0020D680Named, "SupplyWarehouseCripplingBehavior" )
BFME_LITERAL_NAME_GETTER( Rva0020D9C0Named, "WargBehavior" )
BFME_LITERAL_NAME_GETTER( Rva0020E530Named, "BodyModule" )
BFME_LITERAL_NAME_GETTER( Rva0020FA50Named, "ActiveBody" )
BFME_LITERAL_NAME_GETTER( Rva00212860Named, "DelayedDeathBody" )
BFME_LITERAL_NAME_GETTER( Rva00212D60Named, "DetachableRiderBody" )
BFME_LITERAL_NAME_GETTER( Rva002132D0Named, "FreeLifeBody" )
BFME_LITERAL_NAME_GETTER( Rva002137F0Named, "HighlanderBody" )
BFME_LITERAL_NAME_GETTER( Rva002139D0Named, "ImmortalBody" )
BFME_LITERAL_NAME_GETTER( Rva00213C90Named, "InactiveBody" )
BFME_LITERAL_NAME_GETTER( Rva00213F70Named, "OathbreakerBody" )
BFME_LITERAL_NAME_GETTER( Rva002141B0Named, "PorcupineFormationBodyModule" )
BFME_LITERAL_NAME_GETTER( Rva00214690Named, "RespawnBody" )
BFME_LITERAL_NAME_GETTER( Rva00214B40Named, "StructureBody" )
BFME_LITERAL_NAME_GETTER( Rva00214CE0Named, "SymbioticStructuresBody" )
BFME_LITERAL_NAME_GETTER( Rva00215CD0Named, "AODCrushCollide" )
BFME_LITERAL_NAME_GETTER( Rva002162E0Named, "FireWeaponCollide" )
BFME_LITERAL_NAME_GETTER( Rva00216350Named, "CollideModule" )
BFME_LITERAL_NAME_GETTER( Rva002167F0Named, "HordeMemberCollide" )
BFME_LITERAL_NAME_GETTER( Rva00216BF0Named, "SquishCollide" )
BFME_LITERAL_NAME_GETTER( Rva002176B0Named, "CrateCollide" )
BFME_LITERAL_NAME_GETTER( Rva00218070Named, "SalvageCrateCollide" )
BFME_LITERAL_NAME_GETTER( Rva00218660Named, "ShroudCrateCollide" )
BFME_LITERAL_NAME_GETTER( Rva002188B0Named, "UnitCrateCollide" )
BFME_LITERAL_NAME_GETTER( Rva00218C20Named, "VeterancyCrateCollide" )
BFME_LITERAL_NAME_GETTER( Rva00219740Named, "CaveContain" )
BFME_LITERAL_NAME_GETTER( Rva0021B8A0Named, "ContestableContain" )
BFME_LITERAL_NAME_GETTER( Rva00220220Named, "HealContain" )
BFME_LITERAL_NAME_GETTER( Rva0022A090Named, "RiderChangeContain" )
BFME_LITERAL_NAME_GETTER( Rva0022B970Named, "SiegeEngineContain" )
BFME_LITERAL_NAME_GETTER( Rva0022CCE0Named, "TransportContain" )
BFME_LITERAL_NAME_GETTER( Rva0022EEF0Named, "TunnelContain" )
BFME_LITERAL_NAME_GETTER( Rva00230860Named, "AODHordeContain" )
BFME_LITERAL_NAME_GETTER( Rva0023EEF0Named, "HordeContain" )
BFME_LITERAL_NAME_GETTER( Rva0024A280Named, "HordeSiegeEngineContain" )
BFME_LITERAL_NAME_GETTER( Rva0024B780Named, "HordeTransportContain" )
BFME_LITERAL_NAME_GETTER( Rva0024D2B0Named, "HorseHordeContain" )
BFME_LITERAL_NAME_GETTER( Rva0024E820Named, "SlaughterHordeContain" )
BFME_LITERAL_NAME_GETTER( Rva0024F4A0Named, "CreateModule" )
BFME_LITERAL_NAME_GETTER( Rva0024F8A0Named, "GrantUpgradeCreate" )
BFME_LITERAL_NAME_GETTER( Rva0024FC60Named, "LockWeaponCreate" )
BFME_LITERAL_NAME_GETTER( Rva002502A0Named, "SupplyCenterCreate" )
BFME_LITERAL_NAME_GETTER( Rva002506E0Named, "DamageModule" )
BFME_LITERAL_NAME_GETTER( Rva00250790Named, "BoneFXDamage" )
BFME_LITERAL_NAME_GETTER( Rva00251140Named, "EvacuateDamage" )
BFME_LITERAL_NAME_GETTER( Rva00251740Named, "ReflectDamage" )
BFME_LITERAL_NAME_GETTER( Rva00252FD0Named, "TransitionDamageFX" )
BFME_LITERAL_NAME_GETTER( Rva00253C80Named, "DestroyModule" )
BFME_LITERAL_NAME_GETTER( Rva00254BE0Named, "CrushDie" )
BFME_LITERAL_NAME_GETTER( Rva00254FD0Named, "DestroyDie" )
BFME_LITERAL_NAME_GETTER( Rva002553B0Named, "FXListDie" )
BFME_LITERAL_NAME_GETTER( Rva00255AD0Named, "RefundDie" )
BFME_LITERAL_NAME_GETTER( Rva00255E90Named, "SpecialPowerCompletionDie" )
BFME_LITERAL_NAME_GETTER( Rva00256130Named, "UpgradeDie" )
BFME_LITERAL_NAME_GETTER( Rva00257870Named, "ArrowStormUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00259050Named, "CloudBreakSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00259730Named, "CombineHordeSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva00259BC0Named, "DarknessSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0025A2F0Named, "DeflectSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0025A800Named, "DevastateSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0025AD40Named, "DominateEnemySpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0025B2F0Named, "ElvenWoodSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0025CF90Named, "FellBeastSwoopPower" )
BFME_LITERAL_NAME_GETTER( Rva0025D5D0Named, "FreezingRainSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0025DA00Named, "GiveUpgradeUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0025E9A0Named, "GloriousChargeUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0025F120Named, "GrabPassengerSpecialPower" )
BFME_LITERAL_NAME_GETTER( Rva0025F8F0Named, "HeroModeSpecialAbilityUpdate" )
BFME_LITERAL_NAME_GETTER( Rva0025FD70Named, "LevelGrantSpecialPower" )
