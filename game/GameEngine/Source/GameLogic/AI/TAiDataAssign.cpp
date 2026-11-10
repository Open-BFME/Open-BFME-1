// cl: /DNDEBUG /MD /EHsc /O2
// BFME TAiData assignment.  The local member order follows the witnessed
// constructor layout; the byte gaps are compiler padding and are not copied.
// AI::newOverride identifies +0xF4 as m_namedLists and +0xF8 as m_next;
// see targets/game/reverse/identity_evidence/0x0014ac60-taidata-destructor.md.

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
	float m_meleeAcquireLimitDist;
	float m_wadeWaterDepth;
	float m_formationColumnWidth;
	float m_formationRowDepth;
	float m_formationSquadSpacing;
	float m_narrowPassageScale;
	unsigned int m_formationColumns;
	unsigned char m_waitForOthers;
	unsigned char m_hordesWaitForHordes;
	unsigned char m_attackMoveUsesFormations;
	unsigned char m_forceHordesToLowLOD;
	unsigned char m_allowForestFires;
	unsigned char m_useFormations;
	unsigned char m_bfmePadding[2];
	float m_altCameraZoomOverride;
	float m_altCameraPitchOverride;
	float m_bfmeC4;
	float m_bfmeC8;
	float m_chaseFromBehindLimit;
	float m_castleSiegeStandBackDistance;
	unsigned char m_useLowLODTrees;
	unsigned char m_bfmeD5D7[3];
	UnicodeString m_lowLodTreeName;
	UnicodeString m_lowLodTreeNameNoGrab;
	UnicodeString m_lowLodTreeNameNoHarvest;
	float m_lowLodTreeScale;
	unsigned char m_disableTrees;
	unsigned char m_bfmeE9EB[3];
	void *m_sideInfo;
	void *m_sideBuildLists;
	void *m_namedLists;
	TAiData *m_next;
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
	m_meleeAcquireLimitDist = other.m_meleeAcquireLimitDist;
	m_wadeWaterDepth = other.m_wadeWaterDepth;
	m_formationColumnWidth = other.m_formationColumnWidth;
	m_formationRowDepth = other.m_formationRowDepth;
	m_formationSquadSpacing = other.m_formationSquadSpacing;
	m_narrowPassageScale = other.m_narrowPassageScale;
	m_formationColumns = other.m_formationColumns;
	m_waitForOthers = other.m_waitForOthers;
	m_hordesWaitForHordes = other.m_hordesWaitForHordes;
	m_attackMoveUsesFormations = other.m_attackMoveUsesFormations;
	m_forceHordesToLowLOD = other.m_forceHordesToLowLOD;
	m_allowForestFires = other.m_allowForestFires;
	m_useFormations = other.m_useFormations;
	m_altCameraZoomOverride = other.m_altCameraZoomOverride;
	m_altCameraPitchOverride = other.m_altCameraPitchOverride;
	m_bfmeC4 = other.m_bfmeC4;
	m_bfmeC8 = other.m_bfmeC8;
	m_chaseFromBehindLimit = other.m_chaseFromBehindLimit;
	m_castleSiegeStandBackDistance = other.m_castleSiegeStandBackDistance;
	m_useLowLODTrees = other.m_useLowLODTrees;
	m_lowLodTreeName.set(other.m_lowLodTreeName);
	m_lowLodTreeNameNoGrab.set(other.m_lowLodTreeNameNoGrab);
	m_lowLodTreeNameNoHarvest.set(other.m_lowLodTreeNameNoHarvest);
	m_lowLodTreeScale = other.m_lowLodTreeScale;
	m_disableTrees = other.m_disableTrees;
	m_sideInfo = other.m_sideInfo;
	m_sideBuildLists = other.m_sideBuildLists;
	m_namedLists = other.m_namedLists;
	m_next = other.m_next;
	return *this;
}
