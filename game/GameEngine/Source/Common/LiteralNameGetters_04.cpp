// 99 of the image's 429 six-byte __thiscall members with one shape:
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

BFME_LITERAL_NAME_GETTER( Rva002D52D0Named, "GarrisonUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D63F0Named, "MaxHealthUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D6720Named, "ModelConditionUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D77C0Named, "ProductionSpeedBonusUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D7AF0Named, "RadarUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D9430Named, "TooltipUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002D97B0Named, "UnpauseSpecialPowerUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002DA370Named, "WeaponBonusUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002DA530Named, "WeaponSetUpgrade" )
BFME_LITERAL_NAME_GETTER( Rva002EB5B0Named, "LuaScriptEngine" )
BFME_LITERAL_NAME_GETTER( Rva00339A70Named, "SequentialScript" )
BFME_LITERAL_NAME_GETTER( Rva00348410Named, "ScriptEngine" )
BFME_LITERAL_NAME_GETTER( Rva0034C660Named, "AttackPriorityInfo" )
BFME_LITERAL_NAME_GETTER( Rva00352C10Named, "Script" )
BFME_LITERAL_NAME_GETTER( Rva0035BC10Named, "ScriptList" )
BFME_LITERAL_NAME_GETTER( Rva00364470Named, "ArmySummarySystem" )
BFME_LITERAL_NAME_GETTER( Rva0036BC40Named, "CastleMemberBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00372B00Named, "CastleBehavior" )
BFME_LITERAL_NAME_GETTER( Rva00378630Named, "CaveSystem" )
BFME_LITERAL_NAME_GETTER( Rva0038F490Named, "GameLogic" )
BFME_LITERAL_NAME_GETTER( Rva003AA7E0Named, "LivingWorldCampaign" )
BFME_LITERAL_NAME_GETTER( Rva003BBC10Named, "DelayedAudioEventModule" )
BFME_LITERAL_NAME_GETTER( Rva003BBE40Named, "DelayedCameraEventModule" )
BFME_LITERAL_NAME_GETTER( Rva003BC020Named, "DelayedRegionFlashModule" )
BFME_LITERAL_NAME_GETTER( Rva003BC160Named, "DelayedWorldTextEventModule" )
BFME_LITERAL_NAME_GETTER( Rva003C31B0Named, "LivingWorldLogic" )
BFME_LITERAL_NAME_GETTER( Rva003C88D0Named, "LivingWorldRegionManager" )
BFME_LITERAL_NAME_GETTER( Rva003CEFF0Named, "LargeGroupAudio" )
BFME_LITERAL_NAME_GETTER( Rva003DC170Named, "Pathfinder" )
BFME_LITERAL_NAME_GETTER( Rva00409540Named, "GlowMaterial" )
BFME_LITERAL_NAME_GETTER( Rva0040AFE0Named, "BuffManager" )
BFME_LITERAL_NAME_GETTER( Rva004121B0Named, "TintEnvelope" )
BFME_LITERAL_NAME_GETTER( Rva004199D0Named, "Drawable" )
BFME_LITERAL_NAME_GETTER( Rva00422510Named, "Eva" )
BFME_LITERAL_NAME_GETTER( Rva004318E0Named, "GameClient" )
BFME_LITERAL_NAME_GETTER( Rva0044B3D0Named, "InGameUI" )
BFME_LITERAL_NAME_GETTER( Rva0045C190Named, "View" )
BFME_LITERAL_NAME_GETTER( Rva005BA660Named, "Anim2D" )
BFME_LITERAL_NAME_GETTER( Rva005BDC50Named, "FXParticleInfo" )
BFME_LITERAL_NAME_GETTER( Rva005CE3A0Named, "FXParticleSystem" )
BFME_LITERAL_NAME_GETTER( Rva005CEAA0Named, "FXParticle" )
BFME_LITERAL_NAME_GETTER( Rva005E2580Named, "StreakDrawModule" )
BFME_LITERAL_NAME_GETTER( Rva005E2680Named, "ButterflyDrawModule" )
BFME_LITERAL_NAME_GETTER( Rva005E2F70Named, "DefaultModule<CAT_COLOR>" )
BFME_LITERAL_NAME_GETTER( Rva005E30C0Named, "DefaultModule<CAT_WIND>" )
BFME_LITERAL_NAME_GETTER( Rva005E3150Named, "LifeEventModule" )
BFME_LITERAL_NAME_GETTER( Rva005E31E0Named, "TerrainCollisionModule" )
BFME_LITERAL_NAME_GETTER( Rva005E5630Named, "ParticleTerrainCollisionModule" )
BFME_LITERAL_NAME_GETTER( Rva005E5E30Named, "DefaultParticleColorModuleInfo" )
BFME_LITERAL_NAME_GETTER( Rva005E5F10Named, "DefaultParticleModule<CAT_COLOR>" )
BFME_LITERAL_NAME_GETTER( Rva005E60C0Named, "DefaultParticlePhysicsModuleInfo" )
BFME_LITERAL_NAME_GETTER( Rva005E61F0Named, "ParticleWindModuleInfo" )
BFME_LITERAL_NAME_GETTER( Rva005E7330Named, "DefaultModule<CAT_ALPHA>" )
BFME_LITERAL_NAME_GETTER( Rva005E73F0Named, "DefaultParticleAlphaModuleInfo" )
BFME_LITERAL_NAME_GETTER( Rva005E74D0Named, "DefaultParticleModule<CAT_ALPHA>" )

class Rva005E74C0Noop
{
public:
	void run();
};

void Rva005E74C0Noop::run()
{
}

BFME_LITERAL_NAME_GETTER( Rva005E75F0Named, "DefaultModule<CAT_UPDATE>" )
BFME_LITERAL_NAME_GETTER( Rva005E76B0Named, "DefaultParticleUpdateModuleInfo" )
BFME_LITERAL_NAME_GETTER( Rva005E77F0Named, "DefaultParticleModule<CAT_UPDATE>" )
BFME_LITERAL_NAME_GETTER( Rva005E7910Named, "RenderObjectUpdateModule" )
BFME_LITERAL_NAME_GETTER( Rva005E7BE0Named, "RenderObjectParticleUpdateModule" )
BFME_LITERAL_NAME_GETTER( Rva005E81F0Named, "DefaultParticleModule<CAT_PHYSICS>" )
BFME_LITERAL_NAME_GETTER( Rva005E8340Named, "DefaultParticleModule<CAT_WIND>" )
BFME_LITERAL_NAME_GETTER( Rva00602D10Named, "TerrainVisual" )
BFME_LITERAL_NAME_GETTER( Rva00602F00Named, "AnimatedParticleSysBoneClientUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00603810Named, "LaserUpdate" )
BFME_LITERAL_NAME_GETTER( Rva00607B00Named, "RandomSoundSelectorClientBehavior" )
BFME_LITERAL_NAME_GETTER( Rva0060CD70Named, "LivingWorldEyeTower" )
BFME_LITERAL_NAME_GETTER( Rva006174B0Named, "LivingWorldManager" )
BFME_LITERAL_NAME_GETTER( Rva00619820Named, "SinglePlayerSkirmishGameInfo" )
BFME_LITERAL_NAME_GETTER( Rva0061A850Named, "LivingWorldRegion" )
BFME_LITERAL_NAME_GETTER( Rva0061BA30Named, "LivingWorldSound" )
BFME_LITERAL_NAME_GETTER( Rva00696360Named, "MilesAudioManager" )
BFME_LITERAL_NAME_GETTER( Rva006BC550Named, "W3DBuffLogic" )
BFME_LITERAL_NAME_GETTER( Rva006BC720Named, "W3DGhostObject" )
BFME_LITERAL_NAME_GETTER( Rva006BC8E0Named, "W3DGhostObjectManager" )
BFME_LITERAL_NAME_GETTER( Rva006BE0B0Named, "W3DTerrainLogic" )
BFME_LITERAL_NAME_GETTER( Rva006DAC30Named, "TBuff" )
BFME_LITERAL_NAME_GETTER( Rva007366E0Named, "W3DTreeBuffer" )
BFME_LITERAL_NAME_GETTER( Rva0074FF70Named, "DrawModule" )
BFME_LITERAL_NAME_GETTER( Rva00750270Named, "W3DBuffDraw" )
BFME_LITERAL_NAME_GETTER( Rva00751190Named, "W3DDefaultDraw" )
BFME_LITERAL_NAME_GETTER( Rva007517E0Named, "W3DFloorDraw" )
BFME_LITERAL_NAME_GETTER( Rva00751E70Named, "W3DHordeModelDraw" )
BFME_LITERAL_NAME_GETTER( Rva00757B40Named, "W3DLaserDraw" )
BFME_LITERAL_NAME_GETTER( Rva00758520Named, "W3DLightDraw" )
BFME_LITERAL_NAME_GETTER( Rva00758E30Named, "W3DPoliceCarDraw" )
BFME_LITERAL_NAME_GETTER( Rva007592F0Named, "W3DPropDraw" )
BFME_LITERAL_NAME_GETTER( Rva00759760Named, "W3DQuadrupedDraw" )
BFME_LITERAL_NAME_GETTER( Rva0075A540Named, "W3DRopeDraw" )
BFME_LITERAL_NAME_GETTER( Rva007739E0Named, "W3DScriptedModelDraw" )
BFME_LITERAL_NAME_GETTER( Rva0077DBC0Named, "W3DSupplyDraw" )
BFME_LITERAL_NAME_GETTER( Rva0077F1F0Named, "W3DTreeDraw" )
BFME_LITERAL_NAME_GETTER( Rva0077FD70Named, "W3DTruckDraw" )
BFME_LITERAL_NAME_GETTER( Rva007A4AC0Named, "WaterRenderObjClass" )
BFME_LITERAL_NAME_GETTER( Rva00880FB0Named, "TaintManager" )
BFME_LITERAL_NAME_GETTER( Rva008F75C0Named, "ShroudManager" )
BFME_LITERAL_NAME_GETTER( Rva009728A0Named, "NULL" )
BFME_LITERAL_NAME_GETTER( Rva009A2670Named, "CollisionManager" )
BFME_LITERAL_NAME_GETTER( Rva009F27F0Named, "PartitionManager" )
