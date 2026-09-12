// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the group attack-move order and the group-special it defers to.
//
//   ?tryGroupSpecial@            0x001599A0, 169 bytes
//   ?groupAttackMoveToPosition@  0x0015A030, 198 bytes
//
// groupAttackMoveToPosition is Zero Hour's per-member isAbleToAttack /
// aiAttackMove / aiMoveToPosition walk with a BFME preamble in front of it:
// when the group has more than one member, the order came from the player, and
// both TAiData+0xB6 and +0xB9 are set, it offers the order to tryGroupSpecial
// first and returns if that consumes it. Named caller is
// GameLogic::logicMessageDispatcher, MSG_DO_ATTACKMOVETO.
//
// tryGroupSpecial is the other half. It walks the same list looking for a member
// whose AI update's Overridable carries field +0x74 after getFinalOverride, and
// only then runs prep / check / prepFollow / send. Its return is inverted from
// what the name suggests: `isReady()` false means TRUE, i.e. the caller must
// treat the order as already handled.
//
// The two files reached the same call through two decorations. Here it is one
// intra-TU call, and it still matches to the byte -- retail's rel32 lands where
// the local definition does, the same way AIGroup::removeAnyObjectsNotOwnedByPlayer
// reaches AIGroup::remove in AIGroupMembership.cpp.
//
// They also declared the member list with two different element types --
// `_STL::list<Object *>` and `_STL::list<BfmeUpdateObject *>` -- for one list of
// one thing. It is Object, and BfmeUpdateObject stays as a cast-through shim
// rather than being folded into it, because ?getAIUpdateInterface@
// BfmeUpdateObject@@QAEPAVBfmeAIUpdateInterface@@XZ is the spelling the ledger
// pins: respelling the class would rename the callee out of existence.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_unmodelled_000[4];
	Overridable *m_nextOverride;			// +0x04
	unsigned char m_unmodelled_008[0x74 - 0x08];
	void *m_field74;						// +0x74
};

class BfmeAIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[4];
	Overridable *m_override;				// +0x04
};

// Shim: this class NAME is what the ledger pins for the accessor, so the member
// object is cast to it rather than the method being moved onto Object.
class BfmeUpdateObject
{
public:
	BfmeAIUpdateInterface *getAIUpdateInterface();		// ILT 0x00021017
};

class TAiData
{
public:
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
	unsigned char m_pad8d[0xB6 - 0x8d];
	unsigned char m_bfmeB6;					// +0xB6
	unsigned char m_bfmeB7;
	unsigned char m_bfmeB8;
	unsigned char m_bfmeB9;					// +0xB9
};

class AI
{
public:
	TAiData *getAiData()
	{
		return m_aiData;
	}

private:
	unsigned char m_unmodelled_000[0x14];
	TAiData *m_aiData;						// +0x14
};

extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire,
		CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class BfmeGroupAI
{
public:
	unsigned char m_unmodelled_000[0x20];
	AICommandInterface m_commands;			// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool isAbleToAttack() const;
	BfmeGroupAI *getAI()
	{
		return m_ai;
	}

private:
	unsigned char m_unmodelled_000[0x204];
	BfmeGroupAI *m_ai;						// +0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	char isReady();
	void prepSpecial();
	bool checkSpecial(const Coord3D *pos, int a);
	void prepFollow(CommandSourceType cmdSource, int flag);
	void sendSpecial(const Coord3D *pos, int a, int b, int d, int zero);

	bool tryGroupSpecial(const Coord3D *pos, int a, int b, int c, int d);
	void groupAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire,
		CommandSourceType cmdSource);

private:
	unsigned char m_unmodelled_000[4];
	_STL::list<Object *> m_memberList;		// +0x04
};

// ?tryGroupSpecial@AIGroup@@QAE_NPBUCoord3D@@HHHH@Z
// Also reached from applyOrFallback (0x0015A190) through the same ILT 0x00046876.
bool AIGroup::tryGroupSpecial(const Coord3D *pos, int a, int b, int c, int d)
{
	if (isReady())
	{
		bool found = false;
		_STL::list<Object *>::iterator i;
		for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
		{
			Object *obj = *i;
			if (obj == 0)
				continue;
			BfmeAIUpdateInterface *ai = ((BfmeUpdateObject *)obj)->getAIUpdateInterface();
			if (ai == 0)
				continue;
			Overridable *ovr = ai->m_override;
			if (ovr)
			{
				if (ovr->m_nextOverride)
					ovr = (Overridable *)ovr->m_nextOverride->getFinalOverride();
			}
			if (ovr->m_field74)
				found = true;
		}

		if (!found)
			return false;

		prepSpecial();
		if (!checkSpecial(pos, a))
			return false;

		prepFollow((CommandSourceType)a, b);
		sendSpecial(pos, a, b, d, 0);
		return true;
	}

	return true;
}

// ?groupAttackMoveToPosition@AIGroup@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z
void AIGroup::groupAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire,
	CommandSourceType cmdSource)
{
	unsigned int count = m_memberList.size();
	float countF = (float)count;
	const Coord3D *dest = pos;
	CommandSourceType src = cmdSource;
	if (countF > 1.0f)
	{
		TAiData *data = TheAI->getAiData();
		if (data->m_bfmeB6 && src == CMD_FROM_PLAYER && data->m_bfmeB9)
		{
			if (tryGroupSpecial(dest, src, 1, src, 1))
				return;
		}
	}

	_STL::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		BfmeGroupAI *ai = obj->getAI();
		if (ai)
		{
			if (obj->isAbleToAttack())
				ai->m_commands.aiAttackMoveToPosition(dest, maxShotsToFire, src);
			else
				ai->m_commands.aiMoveToPosition(dest, src);
		}
	}
}
