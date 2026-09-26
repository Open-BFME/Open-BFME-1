// readable body of ??0TAiData@@QAE@XZ: game/GameEngine/Source/GameLogic/AI/ai.cpp
// Open-BFME: TAiData::TAiData, retail 0x0014B150.
//
// BFME's TAiData predates the larger Zero Hour layout exposed by the reference
// header.  Keeping its layout local prevents that later header from changing
// the member offsets and the three one-dword retail strings used here.
// The matched AI::newOverride copy identifies +0xF4 as m_namedLists and
// +0xF8 as m_next (targets/game/reverse/identity_evidence/0x0014ac60-taidata-destructor.md).

typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

class Xfer;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();

protected:
	virtual void crc( Xfer *xfer ) = 0;
	virtual void xfer( Xfer *xfer ) = 0;
	virtual void loadPostProcess() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class TAiData : public Snapshot
{
public:
	TAiData();
	virtual ~TAiData();
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();

private:
	Real m_structureSeconds;
	Real m_teamSeconds;
	UnsignedInt m_resourcesWealthy;
	UnsignedInt m_resourcesPoor;
	UnsignedInt m_forceIdleFramesCount;
	Real m_structuresWealthyMod;
	Real m_teamWealthyMod;
	Real m_structuresPoorMod;
	Real m_teamPoorMod;
	Real m_teamResourcesToBuild;
	Real m_guardInnerModifierAI;
	Real m_guardOuterModifierAI;
	Real m_guardInnerModifierHuman;
	Real m_guardOuterModifierHuman;
	UnsignedInt m_guardChaseUnitFrames;
	UnsignedInt m_guardEnemyScanRate;
	UnsignedInt m_guardEnemyReturnScanRate;
	Real m_wallHeight;
	Real m_alertRangeModifier;
	Real m_aggressiveRangeModifier;
	Real m_attackPriorityDistanceModifier;
	Real m_maxRecruitDistance;
	Real m_skirmishBaseDefenseExtraDistance;
	Real m_repulsedDistance;
	Bool m_enableRepulsors;
	Bool m_forceSkirmishAI;
	Bool m_rotateSkirmishBases;
	Bool m_attackUsesLineOfSight;
	Bool m_attackIgnoreInsignificantBuildings;
	unsigned char m_groupAlignment[3];
	Real m_minDistanceForGroup;
	Real m_distanceRequiresGroup;
	Real m_minClumpDensity;
	UnsignedInt m_infantryPathfindDiameter;
	UnsignedInt m_vehiclePathfindDiameter;
	UnsignedInt m_rebuildDelaySeconds;
	Real m_supplyCenterSafeRadius;
	Real m_aiDozerBoredRadiusModifier;
	Bool m_aiCrushesInfantry;
	unsigned char m_retaliationAlignment[3];
	Real m_meleeApproachTolerance;
	Real m_meleeApproachDist;
	Real m_meleeAcquireLimitDist;
	Real m_wadeWaterDepth;
	Real m_formationColumnWidth;
	Real m_formationRowDepth;
	Real m_formationSquadSpacing;
	Real m_narrowPassageScale;
	UnsignedInt m_formationColumns;
	Bool m_waitForOthers;
	Bool m_hordesWaitForHordes;
	Bool m_attackMoveUsesFormations;
	Bool m_forceHordesToLowLOD;
	Bool m_allowForestFires;
	Bool m_useFormations;
	unsigned char m_bfmeBA[2];
	Real m_altCameraZoomOverride;
	Real m_altCameraPitchOverride;
	Real m_maxRetaliateDistance;
	Real m_retaliateFriendsRadius;
	Real m_chaseFromBehindLimit;
	Real m_castleSiegeStandBackDistance;
	Bool m_useLowLODTrees;
	unsigned char m_bfmeD5[3];
	AsciiString m_lowLodTreeName;
	AsciiString m_lowLodTreeNameNoGrab;
	AsciiString m_lowLodTreeNameNoHarvest;
	Real m_lowLodTreeScale;
	Bool m_disableTrees;
	unsigned char m_bfmeE9[3];
	void *m_sideInfo;
	void *m_sideBuildLists;
	void *m_namedLists;
	TAiData *m_next;
};

TAiData::TAiData() :
	m_structureSeconds( 0.0f ),
	m_teamSeconds( 0.0f ),
	m_resourcesWealthy( 0 ),
	m_resourcesPoor( 0 ),
	m_forceIdleFramesCount( 1 ),
	m_structuresWealthyMod( 0.0f ),
	m_teamWealthyMod( 0.0f ),
	m_structuresPoorMod( 0.0f ),
	m_teamPoorMod( 0.0f ),
	m_teamResourcesToBuild( 0.0f ),
	m_guardInnerModifierAI( 0.0f ),
	m_guardOuterModifierAI( 0.0f ),
	m_guardInnerModifierHuman( 0.0f ),
	m_guardOuterModifierHuman( 0.0f ),
	m_guardChaseUnitFrames( 0 ),
	m_guardEnemyScanRate( 2 ),
	m_guardEnemyReturnScanRate( 5 ),
	m_wallHeight( 0.0f ),
	m_alertRangeModifier( 0.0f ),
	m_aggressiveRangeModifier( 0.0f ),
	m_attackPriorityDistanceModifier( 0.0f ),
	m_maxRecruitDistance( 0.0f ),
	m_skirmishBaseDefenseExtraDistance( 0.0f ),
	m_repulsedDistance( 0.0f ),
	m_enableRepulsors( 0 ),
	m_forceSkirmishAI( 0 ),
	m_rotateSkirmishBases( 0 ),
	m_attackUsesLineOfSight( 1 ),
	m_attackIgnoreInsignificantBuildings( 0 ),
	m_minDistanceForGroup( 100.0f ),
	m_distanceRequiresGroup( 600.0f ),
	m_minClumpDensity( 0.5f ),
	m_infantryPathfindDiameter( 6 ),
	m_vehiclePathfindDiameter( 6 ),
	m_rebuildDelaySeconds( 10 ),
	m_supplyCenterSafeRadius( 250.0f ),
	m_aiDozerBoredRadiusModifier( 2.0f ),
	m_aiCrushesInfantry( 1 ),
	m_meleeApproachTolerance( 20.0f ),
	m_meleeApproachDist( 60.0f ),
	m_meleeAcquireLimitDist( 100.0f ),
	m_wadeWaterDepth( 5.0f ),
	m_formationColumnWidth( 65.0f ),
	m_formationRowDepth( 65.0f ),
	m_formationSquadSpacing( 30.0f ),
	m_narrowPassageScale( 1.0f ),
	m_formationColumns( 2 ),
	m_waitForOthers( 0 ),
	m_hordesWaitForHordes( 1 ),
	m_attackMoveUsesFormations( 1 ),
	m_forceHordesToLowLOD( 1 ),
	m_allowForestFires( 0 ),
	m_useFormations( 1 ),
	m_altCameraZoomOverride( 1.4f ),
	m_altCameraPitchOverride( 0.5f ),
	m_maxRetaliateDistance( 200.0f ),
	m_retaliateFriendsRadius( 120.0f ),
	m_chaseFromBehindLimit( 50.0f ),
	m_castleSiegeStandBackDistance( 100.0f ),
	m_useLowLODTrees( 0 ),
	m_lowLodTreeName( "TreeF03" ),
	m_lowLodTreeNameNoGrab( "TreeF02" ),
	m_lowLodTreeNameNoHarvest( "PTStump02" ),
	m_disableTrees( 0 ),
	m_sideInfo( 0 ),
	m_sideBuildLists( 0 ),
	m_namedLists( 0 ),
	m_next( 0 )
{
	m_lowLodTreeScale = 0.55f;
}
