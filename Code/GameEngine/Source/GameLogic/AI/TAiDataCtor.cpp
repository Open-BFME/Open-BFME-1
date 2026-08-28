// readable body of ??0TAiData@@QAE@XZ: Code/GameEngine/Source/GameLogic/AI/ai.cpp
// Open-BFME: TAiData::TAiData, retail 0x0014B150.
//
// BFME's TAiData predates the larger Zero Hour layout exposed by the reference
// header.  Keeping its layout local prevents that later header from changing
// the member offsets and the three one-dword retail strings used here.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
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
	Real m_maxRetaliateDistance;
	Real m_retaliateFriendsRadius;
	Real m_bfme98;
	Real m_bfme9C;
	Real m_bfmeA0;
	Real m_bfmeA4;
	Real m_bfmeA8;
	Real m_bfmeAC;
	UnsignedInt m_bfmeB0;
	Bool m_bfmeB4;
	Bool m_bfmeB5;
	Bool m_bfmeB6;
	Bool m_bfmeB7;
	Bool m_bfmeB8;
	Bool m_bfmeB9;
	unsigned char m_bfmeBA[2];
	Real m_bfmeBC;
	Real m_bfmeC0;
	Real m_bfmeC4;
	Real m_bfmeC8;
	Real m_bfmeCC;
	Real m_bfmeD0;
	Bool m_bfmeD4;
	unsigned char m_bfmeD5[3];
	AsciiString m_treeF03;
	AsciiString m_treeF02;
	AsciiString m_ptStump02;
	Real m_bfmeE4;
	Bool m_bfmeE8;
	unsigned char m_bfmeE9[3];
	void *m_sideInfo;
	void *m_sideBuildLists;
	TAiData *m_next;
	void *m_bfmeF8;
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
	m_maxRetaliateDistance( 20.0f ),
	m_retaliateFriendsRadius( 60.0f ),
	m_bfme98( 100.0f ),
	m_bfme9C( 5.0f ),
	m_bfmeA0( 65.0f ),
	m_bfmeA4( 65.0f ),
	m_bfmeA8( 30.0f ),
	m_bfmeAC( 1.0f ),
	m_bfmeB0( 2 ),
	m_bfmeB4( 0 ),
	m_bfmeB5( 1 ),
	m_bfmeB6( 1 ),
	m_bfmeB7( 1 ),
	m_bfmeB8( 0 ),
	m_bfmeB9( 1 ),
	m_bfmeBC( 1.4f ),
	m_bfmeC0( 0.5f ),
	m_bfmeC4( 200.0f ),
	m_bfmeC8( 120.0f ),
	m_bfmeCC( 50.0f ),
	m_bfmeD0( 100.0f ),
	m_bfmeD4( 0 ),
	m_treeF03( "TreeF03" ),
	m_treeF02( "TreeF02" ),
	m_ptStump02( "PTStump02" ),
	m_bfmeE8( 0 ),
	m_sideInfo( 0 ),
	m_sideBuildLists( 0 ),
	m_next( 0 ),
	m_bfmeF8( 0 )
{
	m_bfmeE4 = 0.55f;
}
