// cl: /DNDEBUG /MD /EHsc /O2
// BFME TAiData assignment.  The local member order follows the witnessed
// constructor layout; the byte gaps are compiler padding and are not copied.

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();
};

class UnicodeString
{
public:
	void set(const UnicodeString &other);

	void *m_data;
};

class TAiData : public Snapshot
{
public:
	TAiData &operator=(const TAiData &other);

	float m_structureSeconds;
	float m_teamSeconds;
	unsigned int m_resourcesWealthy;
	unsigned int m_resourcesPoor;
	unsigned int m_forceIdleFramesCount;
	float m_structuresWealthyMod;
	float m_teamWealthyMod;
	float m_structuresPoorMod;
	float m_teamPoorMod;
	float m_teamResourcesToBuild;
	float m_guardInnerModifierAI;
	float m_guardOuterModifierAI;
	float m_guardInnerModifierHuman;
	float m_guardOuterModifierHuman;
	unsigned int m_guardChaseUnitFrames;
	unsigned int m_guardEnemyScanRate;
	unsigned int m_guardEnemyReturnScanRate;
	float m_wallHeight;
	float m_alertRangeModifier;
	float m_aggressiveRangeModifier;
	float m_attackPriorityDistanceModifier;
	float m_maxRecruitDistance;
	float m_skirmishBaseDefenseExtraDistance;
	float m_repulsedDistance;
	unsigned char m_enableRepulsors;
	unsigned char m_forceSkirmishAI;
	unsigned char m_rotateSkirmishBases;
	unsigned char m_attackUsesLineOfSight;
	unsigned char m_attackIgnoreInsignificantBuildings;
	unsigned char m_groupPadding[3];
	float m_minDistanceForGroup;
	float m_distanceRequiresGroup;
	float m_minClumpDensity;
	unsigned int m_infantryPathfindDiameter;
	unsigned int m_vehiclePathfindDiameter;
	unsigned int m_rebuildDelaySeconds;
	float m_supplyCenterSafeRadius;
	float m_aiDozerBoredRadiusModifier;
	unsigned char m_aiCrushesInfantry;
	unsigned char m_retaliationPadding[3];
	float m_maxRetaliateDistance;
	float m_retaliateFriendsRadius;
	float m_bfme98;
	float m_bfme9C;
	float m_bfmeA0;
	float m_bfmeA4;
	float m_bfmeA8;
	float m_bfmeAC;
	unsigned int m_bfmeB0;
	unsigned char m_bfmeB4;
	unsigned char m_bfmeB5;
	unsigned char m_bfmeB6;
	unsigned char m_bfmeB7;
	unsigned char m_bfmeB8;
	unsigned char m_bfmeB9;
	unsigned char m_bfmePadding[2];
	float m_bfmeBC;
	float m_bfmeC0;
	float m_bfmeC4;
	float m_bfmeC8;
	float m_bfmeCC;
	float m_bfmeD0;
	unsigned char m_bfmeD4;
	unsigned char m_bfmeD5D7[3];
	UnicodeString m_treeF03;
	UnicodeString m_treeF02;
	UnicodeString m_ptStump02;
	float m_bfmeE4;
	unsigned char m_bfmeE8;
	unsigned char m_bfmeE9EB[3];
	void *m_sideInfo;
	void *m_sideBuildLists;
	TAiData *m_next;
	void *m_bfmeF8;
};

// ??4TAiData@@QAEAAV0@ABV0@@Z
TAiData &TAiData::operator=(const TAiData &other)
{
	m_structureSeconds = other.m_structureSeconds;
	m_teamSeconds = other.m_teamSeconds;
	m_resourcesWealthy = other.m_resourcesWealthy;
	m_resourcesPoor = other.m_resourcesPoor;
	m_forceIdleFramesCount = other.m_forceIdleFramesCount;
	m_structuresWealthyMod = other.m_structuresWealthyMod;
	m_teamWealthyMod = other.m_teamWealthyMod;
	m_structuresPoorMod = other.m_structuresPoorMod;
	m_teamPoorMod = other.m_teamPoorMod;
	m_teamResourcesToBuild = other.m_teamResourcesToBuild;
	m_guardInnerModifierAI = other.m_guardInnerModifierAI;
	m_guardOuterModifierAI = other.m_guardOuterModifierAI;
	m_guardInnerModifierHuman = other.m_guardInnerModifierHuman;
	m_guardOuterModifierHuman = other.m_guardOuterModifierHuman;
	m_guardChaseUnitFrames = other.m_guardChaseUnitFrames;
	m_guardEnemyScanRate = other.m_guardEnemyScanRate;
	m_guardEnemyReturnScanRate = other.m_guardEnemyReturnScanRate;
	m_wallHeight = other.m_wallHeight;
	m_alertRangeModifier = other.m_alertRangeModifier;
	m_aggressiveRangeModifier = other.m_aggressiveRangeModifier;
	m_attackPriorityDistanceModifier = other.m_attackPriorityDistanceModifier;
	m_maxRecruitDistance = other.m_maxRecruitDistance;
	m_skirmishBaseDefenseExtraDistance = other.m_skirmishBaseDefenseExtraDistance;
	m_repulsedDistance = other.m_repulsedDistance;
	m_enableRepulsors = other.m_enableRepulsors;
	m_forceSkirmishAI = other.m_forceSkirmishAI;
	m_rotateSkirmishBases = other.m_rotateSkirmishBases;
	m_attackUsesLineOfSight = other.m_attackUsesLineOfSight;
	m_attackIgnoreInsignificantBuildings = other.m_attackIgnoreInsignificantBuildings;
	m_minDistanceForGroup = other.m_minDistanceForGroup;
	m_distanceRequiresGroup = other.m_distanceRequiresGroup;
	m_minClumpDensity = other.m_minClumpDensity;
	m_infantryPathfindDiameter = other.m_infantryPathfindDiameter;
	m_vehiclePathfindDiameter = other.m_vehiclePathfindDiameter;
	m_rebuildDelaySeconds = other.m_rebuildDelaySeconds;
	m_supplyCenterSafeRadius = other.m_supplyCenterSafeRadius;
	m_aiDozerBoredRadiusModifier = other.m_aiDozerBoredRadiusModifier;
	m_aiCrushesInfantry = other.m_aiCrushesInfantry;
	m_maxRetaliateDistance = other.m_maxRetaliateDistance;
	m_retaliateFriendsRadius = other.m_retaliateFriendsRadius;
	m_bfme98 = other.m_bfme98;
	m_bfme9C = other.m_bfme9C;
	m_bfmeA0 = other.m_bfmeA0;
	m_bfmeA4 = other.m_bfmeA4;
	m_bfmeA8 = other.m_bfmeA8;
	m_bfmeAC = other.m_bfmeAC;
	m_bfmeB0 = other.m_bfmeB0;
	m_bfmeB4 = other.m_bfmeB4;
	m_bfmeB5 = other.m_bfmeB5;
	m_bfmeB6 = other.m_bfmeB6;
	m_bfmeB7 = other.m_bfmeB7;
	m_bfmeB8 = other.m_bfmeB8;
	m_bfmeB9 = other.m_bfmeB9;
	m_bfmeBC = other.m_bfmeBC;
	m_bfmeC0 = other.m_bfmeC0;
	m_bfmeC4 = other.m_bfmeC4;
	m_bfmeC8 = other.m_bfmeC8;
	m_bfmeCC = other.m_bfmeCC;
	m_bfmeD0 = other.m_bfmeD0;
	m_bfmeD4 = other.m_bfmeD4;
	m_treeF03.set(other.m_treeF03);
	m_treeF02.set(other.m_treeF02);
	m_ptStump02.set(other.m_ptStump02);
	m_bfmeE4 = other.m_bfmeE4;
	m_bfmeE8 = other.m_bfmeE8;
	m_sideInfo = other.m_sideInfo;
	m_sideBuildLists = other.m_sideBuildLists;
	m_next = other.m_next;
	m_bfmeF8 = other.m_bfmeF8;
	return *this;
}
