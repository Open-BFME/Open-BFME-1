// cl: /DNDEBUG /MD /EHsc
// Open-BFME: TAiData::addFactionBuildList at retail 0x0014BE10.
// AI::newOverride and Rva0014C090::parseDefinition call its retail ILT.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

extern const char Rva006A16B0Empty[];

struct BfmeAsciiStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class BfmeRetailAsciiString
{
public:
	int compare(const BfmeRetailAsciiString &other) const
	{
		int rightLength = other.m_data ? other.m_data->m_length : 0;
		const char *right = other.m_data ? other.m_data->m_text : Rva006A16B0Empty;
		int leftLength = m_data ? m_data->m_length : 0;
		const char *left = m_data ? m_data->m_text : Rva006A16B0Empty;
		int length = leftLength < rightLength ? leftLength : rightLength;
		int result = memcmp(left, right, length);
		if (result != 0)
			return result;
		return leftLength - rightLength;
	}

	bool operator==(const BfmeRetailAsciiString &other) const
	{
		return compare(other) == 0;
	}

private:
	BfmeAsciiStringData *m_data;
};

class BuildListInfo
{
public:
	virtual ~BuildListInfo();

	void deleteInstance()
	{
		delete this;
	}
};

class AISideBuildList
{
public:
	virtual ~AISideBuildList();

	void deleteInstance()
	{
		delete this;
	}

	BfmeRetailAsciiString m_side;
	BuildListInfo *m_buildList;
	AISideBuildList *m_next;
};

class TAiData
{
public:
	void addFactionBuildList(AISideBuildList *buildList);

private:
	unsigned char m_pad00[4];
	float m_structureSeconds;
	float m_teamSeconds;
	int m_resourcesWealthy;
	int m_resourcesPoor;
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
	float m_skirmishGroupFudgeValue;
	float m_maxRecruitDistance;
	float m_repulsedDistance;
	unsigned char m_enableRepulsors;
	unsigned char m_forceSkirmishAI;
	unsigned char m_rotateSkirmishBases;
	unsigned char m_attackUsesLineOfSight;
	unsigned char m_attackIgnoreInsignificantBuildings;
	unsigned char m_pad69[3];
	float m_minDistanceForGroup;
	unsigned char m_pad70[4];
	float m_minClumpDensity;
	int m_infantryPathfindDiameter;
	int m_vehiclePathfindDiameter;
	int m_rebuildDelaySeconds;
	float m_supplyCenterSafeRadius;
	float m_aiDozerBoredRadiusModifier;
	unsigned char m_aiCrushesInfantry;
	unsigned char m_pad8d[0xf0 - 0x8d];
	AISideBuildList *m_sideBuildLists;
};

void TAiData::addFactionBuildList(AISideBuildList *buildList)
{
	AISideBuildList *info = m_sideBuildLists;
	while (info)
	{
		if (buildList->m_side == info->m_side)
		{
			if (info->m_buildList)
				info->m_buildList->deleteInstance();
			info->m_buildList = buildList->m_buildList;
			buildList->m_buildList = 0;
			buildList->m_next = 0;
			buildList->deleteInstance();
			return;
		}
		info = info->m_next;
	}
	buildList->m_next = m_sideBuildLists;
	m_sideBuildLists = buildList;
}
