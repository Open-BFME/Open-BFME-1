// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
// stlport
// readable body of ?crc@AI@@UAEXPAVXfer@@@Z: Code/GameEngine/Source/GameLogic/AI/ai.cpp
// Open-BFME5: clean C++ reconstruction of the AI CRC/version serializer.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "xfer.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

template <typename T>
class StringBase
{
protected:
	StringBase() : m_data(0) {}
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	void set(const char *text, int length);
	~AsciiString();
};

// Pathfinder's Snapshot subobject follows its service-interface vptr at +4.
// Only that adjustment is reached by this function.
class PathfinderServices
{
public:
	virtual void unused();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder : private PathfinderServices, public Snapshot
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class TAiData : public Snapshot
{
public:
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
	unsigned char m_pad8d[0xf8 - 0x8d];
	TAiData *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup : public Snapshot
{
};

class CrcVersion
{
public:
	CrcVersion() {}
	unsigned char data[2];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	virtual void crc(Xfer *xfer);

private:
	Pathfinder *m_pathfinder;
	_STL::list<AIGroup *> m_groupList;
	TAiData *m_aiData;
	unsigned int m_nextGroupID;
	unsigned int m_nextFormationID;
};

// ?crc@AI@@UAEXPAVXfer@@@Z
void AI::crc(Xfer *xfer)
{
	register AI *self = this;
	CrcVersion version;
	if (xfer->IsCRC())
	{
		Pathfinder *pathfinder = self->m_pathfinder;
		Pathfinder *nonnullPathfinder = pathfinder ? pathfinder : 0;
		(*xfer) == *static_cast<Snapshot *>(nonnullPathfinder);

		AsciiString marker;
		TAiData *aiData = self->m_aiData;
		while (aiData)
		{
			marker.set("MARKER:TAiData", 14);
			(*xfer) == marker;
			(*xfer) == *aiData;
			aiData = aiData->m_next;
		}

		for (_STL::list<AIGroup *>::iterator groupIt = self->m_groupList.begin();
			groupIt != self->m_groupList.end(); ++groupIt)
		{
			if (*groupIt)
			{
				marker.set("MARKER:AIGroup", 14);
				(*xfer) == marker;
				(*xfer) == **groupIt;
			}
		}
	}
	else
	{
		version.data[0] = 1;
		version.data[1] = 1;
		(*xfer) == *reinterpret_cast<Xfer::Version *>(&version);
		(*xfer) == self->m_nextGroupID;
		xfer->XferRawBytes(&self->m_nextFormationID, 4);
	}
}
