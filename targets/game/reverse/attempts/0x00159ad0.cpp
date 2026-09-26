// ?applyPacket@Rva0015A190Owner@@QAEXPAURva0015A190Packet@@H@Z
// partial score=0.22 date=2026-09-22
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB

#include <new>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum IterOrderType
{
	ITER_SORTED_NEAR_TO_FAR = 1
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_AIRCRAFT = 12,
	KINDOF_PRODUCED_AT_HELIPAD = 20,
	KINDOF_CLIFF_JUMPER = 21
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum
{
	DISABLED_HELD = 8,
	OBJECT_STATUS_CAN_STEALTH = 0x00040000,
	OBJECT_STATUS_DETECTED = 0x00020000,
	OBJECT_STATUS_STEALTHED = 0x80000000,
	NO_FORMATION_ID = 0,
	STD_WAYPOINT_CLAMP_MARGIN = 0
};

struct Rva0015A190Packet
{
	void *m_first;
	unsigned char m_flag;
	unsigned char m_pad05[3];
	void *m_objA;
	void *m_objB;
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType kind) const
	{
		return (m_kindOf[(unsigned int)kind >> 5] &
			(1u << ((unsigned int)kind & 31))) != 0;
	}

private:
	unsigned char m_pad08[0xc8 - 8];
	unsigned int m_kindOf[3];
};

class Object;
class StealthUpdate;

extern void ScaleRect2D(Coord2D *min, Coord2D *max, Real factor);
extern Bool Coord3DInsideRect2D(const Coord3D *pos, const Coord2D *min,
	const Coord2D *max);
extern Int GetGameLogicRandomValue(int low, int high, const char *file, int line);

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType source);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType source);
	void aiBfmeCommand42(Object *object, CommandSourceType source);
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateModuleData
{
public:
	unsigned char m_pad00[0x20];
	unsigned int m_autoAcquireEnemiesWhenIdle;
};

class AIUpdateInterface : public BfmeVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const = 0;

	void ignoreObstacle(Object *object);

	Bool canAutoAcquire() const
	{
		return m_moduleData->m_autoAcquireEnemiesWhenIdle != 0;
	}

	Bool canAutoAcquireWhileStealthed() const
	{
		return (m_moduleData->m_autoAcquireEnemiesWhenIdle & 2) != 0;
	}

	void setNextMoodCheckTime(UnsignedInt frame);

private:
	AIUpdateModuleData *m_moduleData;
	unsigned char m_pad08[0x20 - 8];

public:
	AICommandInterface m_commands;
};

class Object
{
public:
	virtual ~Object();

	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *result = m_template;
		if (result && result->m_nextOverride)
			result = (const ThingTemplate *)result->m_nextOverride->getFinalOverride();
		return result;
	}

	bool isKindOf(KindOfType kind) const
	{
		return getTemplate()->isKindOf(kind);
	}

	AIUpdateInterface *getAIUpdateInterface()
	{
		return m_ai;
	}

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	UnsignedInt getStatusBits() const
	{
		return m_statusBits;
	}

	unsigned char getDisabledMask() const
	{
		return m_disabledMask;
	}

	void setFormationID(UnsignedInt id)
	{
		m_formationID = id;
	}

	StealthUpdate *findUpdateModule(NameKeyType key);

private:
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_position;
	unsigned char m_pad44[0x90 - 0x44];
	UnsignedInt m_statusBits;
	unsigned char m_pad94[0x1a4 - 0x94];
	unsigned char m_disabledMask;
	unsigned char m_pad1a5[0x1fc - 0x1a5];
	void *m_contain;
	unsigned char m_pad200[4];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x31c - 0x208];
	UnsignedInt m_formationID;
};

class StealthUpdateModuleData
{
public:
	unsigned char m_pad00[8];
	UnsignedInt m_stealthDelay;
};

class StealthUpdate
{
public:
	unsigned char m_pad00[4];
	StealthUpdateModuleData *m_moduleData;

	UnsignedInt getStealthDelay() const
	{
		return m_moduleData->m_stealthDelay;
	}
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_next;
	BfmeListNodeBase *m_prev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_value;
};

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *object, Real numeric);
	void sort(IterOrderType order);

private:
	unsigned char m_pad04[12];
};

class Coord3DPathfinder
{
public:
	void removeGoal(Object *object);
};

class TAiData
{
public:
	unsigned char m_pad00[0xb9];
	unsigned char m_bfmeB9;
};

class AI
{
public:
	TAiData *getAiData() { return m_aiData; }
	Coord3DPathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_pad00[0x0c];
	Coord3DPathfinder *m_pathfinder;
	unsigned char m_pad10[4];
	TAiData *m_aiData;
};

extern AI *TheAI;

class GlobalData
{
private:
	unsigned char m_pad00[0xbfc];

public:
	Real m_groupMoveClickToGatherFactor;
};

extern GlobalData *TheWritableGlobalData;
extern Real g_bfmeUint32Scale;
extern Real g_bfmeDefaultBU;
extern Real g_bfmeScaleBK;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_0003add7();

static NameKeyType nameKeyViaIlt(const char *name)
{
	typedef NameKeyType (NameKeyGenerator::*NameKeyCall)(const char *);
	union
	{
		void *asVoid;
		NameKeyCall asMember;
	} cast;
	cast.asVoid = (void *)j_0003add7;
	return (TheNameKeyGenerator->*cast.asMember)(name);
}

class BfmeSubjectZZ
{
public:
	unsigned char m_pad00[0x0c];
	void *m_item;
};

class BfmeOwnerZZ
{
public:
	Bool bfmeScanZZ(BfmeSubjectZZ *subject);
};

class AIGroup
{
public:
	Bool getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center);
	void recompute();
	bool tryGroupSpecial(const Coord3D *pos, int a, int b, int c, int d);
	void groupTightenToPosition(const Coord3D *pos, bool addWaypoint,
		CommandSourceType source);
	void computeIndividualDestination(Coord3D *dest, const Coord3D *groupDest,
		Object *object, const Coord3D *center, Bool formation);

	protected:
	char m_pad00[4];
	BfmeListNodeBase *m_memberList;
	unsigned int m_memberListSize;
	Real m_speed;
	unsigned char m_dirty;
};

class Rva0015A190Owner : public AIGroup
{
public:
	void applyPacket(Rva0015A190Packet *packet, Int command);
};

static Bool scanViaIlt(AIGroup *group, Rva0015A190Packet *packet)
{
	return ((BfmeOwnerZZ *)group)->bfmeScanZZ((BfmeSubjectZZ *)packet);
}

void Rva0015A190Owner::applyPacket(Rva0015A190Packet *packet, Int command)
{
	Bool tightenGroup = false;
	Coord3D center;
	Coord2D min;
	Coord2D max;
	Coord3D dest;

	getMinMaxAndCenter(&min, &max, &center);
	if (m_dirty)
		recompute();

	if (packet->m_objB == 0 && command == 0 &&
		TheWritableGlobalData->m_groupMoveClickToGatherFactor > 0.0f)
	{
		ScaleRect2D(&min, &max,
			TheWritableGlobalData->m_groupMoveClickToGatherFactor);
		if (Coord3DInsideRect2D((const Coord3D *)packet->m_first,
			&min, &max))
			tightenGroup = true;
	}

	unsigned int count = 0;
	for (BfmeListNodeBase *node = m_memberList->m_next;
		node != m_memberList;
		node = node->m_next)
		++count;

	if (count > 1 && !tightenGroup && !packet->m_flag &&
		packet->m_objB == 0 && command == 0 &&
		TheAI->getAiData()->m_bfmeB9)
	{
		if (tryGroupSpecial((const Coord3D *)packet->m_first, 0, 0,
			(int)packet->m_objA, 1))
			return;
		if (!scanViaIlt(this, packet))
			return;
	}

	if (tightenGroup)
	{
		for (BfmeListNodeBase *node = m_memberList->m_next;
			node != m_memberList;
			node = node->m_next)
		{
			Object *object = ((BfmeMemberNode *)node)->m_value;
			AIUpdateInterface *ai = object->getAIUpdateInterface();
			if (ai && ai->isDoingGroundMovement())
				tightenGroup = false;
		}

		if (tightenGroup && !packet->m_flag)
		{
			int dx = (int)((max.x - min.x) * g_bfmeScaleBK);
			if (dx * dx < 2000)
			{
				groupTightenToPosition((const Coord3D *)packet->m_first,
					false, (CommandSourceType)command);
				return;
			}
		}
	}

	SimpleObjectIterator *iter = new SimpleObjectIterator;
	Coord3D goalPos;
	for (BfmeListNodeBase *node = m_memberList->m_next;
		node != m_memberList;
		node = node->m_next)
	{
		Object *object = ((BfmeMemberNode *)node)->m_value;
		if (object->getDisabledMask() & DISABLED_HELD)
			continue;
		if (object->isKindOf(KINDOF_IMMOBILE))
			continue;
		AIUpdateInterface *ai = object->getAIUpdateInterface();
		if (ai == 0)
			continue;

		TheAI->pathfinder()->removeGoal(object);
		Real dx = object->getPosition()->x -
			((const Coord3D *)packet->m_first)->x;
		Real dy = object->getPosition()->y -
			((const Coord3D *)packet->m_first)->y;
		iter->insert(object, dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_NEAR_TO_FAR);
	Bool firstUnit = true;
	for (Object *object = iter->first(); object; object = iter->next())
	{
		AIUpdateInterface *ai = object->getAIUpdateInterface();
		object->setFormationID(NO_FORMATION_ID);
		if (firstUnit)
		{
			center = *object->getPosition();
				goalPos = *(const Coord3D *)packet->m_first;
			firstUnit = false;
		}

		computeIndividualDestination(&dest, &goalPos,
			object, &center, false);

		if (command == 0 &&
			(object->getStatusBits() & OBJECT_STATUS_CAN_STEALTH) &&
			ai->canAutoAcquire() &&
			!(object->getStatusBits() & OBJECT_STATUS_STEALTHED) &&
			!(object->getStatusBits() & OBJECT_STATUS_DETECTED) &&
			!ai->canAutoAcquireWhileStealthed())
		{
			static NameKeyType keyStealthUpdate = nameKeyViaIlt("StealthUpdate");
			StealthUpdate *stealth =
				(StealthUpdate *)object->findUpdateModule(keyStealthUpdate);
			if (stealth)
			{
				UnsignedInt randomFrames = GetGameLogicRandomValue(
					0, 5,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGroup.cpp",
					0x951);
				ai->setNextMoodCheckTime(TheGameLogic->getFrame() +
					stealth->getStealthDelay() + randomFrames);
			}
		}

		if (packet->m_objA)
			ai->ignoreObstacle((Object *)packet->m_objA);
		else if (packet->m_objB)
			ai->m_commands.aiBfmeCommand42((Object *)packet->m_objB,
				(CommandSourceType)command);
		else if (packet->m_flag)
			ai->m_commands.aiFollowPathAppend(&dest,
				(CommandSourceType)command);
		else
			ai->m_commands.aiMoveToPosition(&dest,
				(CommandSourceType)command);
	}

	delete iter;
}
