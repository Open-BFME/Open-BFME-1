// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME5: AI::newOverride, retail 0x0014E2B0.  This is the BFME form of
// the Generals AI-data override: copy the scalar data, then deep-copy each of
// the three intrusive lists before linking the previous definition.

#include "StringInline.h"

void *operator new(unsigned int size);
void operator delete(void *ptr);

class Xfer;
class BuildListInfo
{
public:
	BuildListInfo *duplicate(void);
};

class AISideInfo;
class AISideBuildList;
class AINamedListNode;

class AINamedListTail
{
public:
	AINamedListTail &operator=(const AINamedListTail &that);

private:
	void *m_data;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class TAiData : public Snapshot
{
public:
	TAiData();
	TAiData &operator=(const TAiData &that);
	void addFactionBuildList(AISideBuildList *buildList);

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
	unsigned char m_pad8d[0xEC - 0x8d];
	AISideInfo *m_sideInfo;
	AISideBuildList *m_sideBuildLists;
	AINamedListNode *m_namedLists;
	TAiData *m_next;
};

class AISideInfo
{
public:
	AISideInfo();
	AISideInfo &operator=(const AISideInfo &that);

	unsigned char m_body[0x1BC];
	AISideInfo *m_next;
};

class AISideBuildList
{
public:
	virtual ~AISideBuildList();
	AISideBuildList(AsciiString side) : m_side(side), m_buildList(0), m_next(0) {}

	AsciiString m_side;
	BuildListInfo *m_buildList;
	AISideBuildList *m_next;
};

class AINamedListNode
{
public:
	AINamedListNode(AsciiString name);

	void *m_vtable;
	AsciiString m_name;
	unsigned int m_value;
	AINamedListTail m_tail;
	AINamedListNode *m_next;
};

class AI
{
protected:
	void newOverride(void);

private:
	unsigned char m_pad[0x14];
	TAiData *m_aiData;
};

void AI::newOverride(void)
{
	AI *self = this;
	TAiData *cur = self->m_aiData;
	const int zero = 0;
	self->m_aiData = new TAiData;
	*self->m_aiData = *cur;

	self->m_aiData->m_sideInfo = (AISideInfo *)zero;
	AISideInfo *info = cur->m_sideInfo;
	while (info)
	{
		AISideInfo *newInfo = new AISideInfo;
		*newInfo = *info;
		newInfo->m_next = (AISideInfo *)zero;
		TAiData *data = self->m_aiData;
		newInfo->m_next = data->m_sideInfo;
		data->m_sideInfo = newInfo;
		info = info->m_next;
	}

	self->m_aiData->m_sideBuildLists = (AISideBuildList *)zero;
	AISideBuildList *build = cur->m_sideBuildLists;
	while (build)
	{
		AISideBuildList *newBuild = new AISideBuildList(build->m_side);
		newBuild->m_next = (AISideBuildList *)zero;
		if (build->m_buildList)
			newBuild->m_buildList = build->m_buildList->duplicate();
		self->m_aiData->addFactionBuildList(newBuild);
		build = build->m_next;
	}

	self->m_aiData->m_namedLists = (AINamedListNode *)zero;
	AINamedListNode *named = cur->m_namedLists;
	while (named)
	{
		AINamedListNode *node = new AINamedListNode(named->m_name);
		node->m_tail = named->m_tail;
		node->m_value = named->m_value;
		TAiData *data = self->m_aiData;
		node->m_next = data->m_namedLists;
		data->m_namedLists = node;
		named = named->m_next;
	}

	self->m_aiData->m_next = cur;
}
