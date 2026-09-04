// cl: /DNDEBUG /MD /EHsc

// Open-BFME: AIGroup::groupTightenToPosition, retail 0x00155720, 295 bytes.
//
// Same member walk as groupHunt / groupFollowWaypointPathAsTeam. Identity is
// the matched aiTightenToPosition callee (ILT 0x000438C9 -> 0x001527C0). The
// addWaypoint arm is aiFollowPathAppend (ILT 0x0000BAC8 -> 0x00153480). BFME
// builds a heap SimpleObjectIterator with global operator new, sorts
// NEAR_TO_FAR, and does not hold or delete the iterator.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };
enum IterOrderType { ITER_FASTEST = 0, ITER_SORTED_NEAR_TO_FAR = 1 };
enum KindOfType { KINDOF_IMMOBILE = 2 };

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;	// ILT 0x000022BB

	Overridable *m_nextOverride;						// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(unsigned int)t >> 5] & (1u << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	unsigned int m_kindof[3];							// +0xC8
};

class AICommandInterface
{
public:
	void aiTightenToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType cmdSource);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;					// +0x20
};

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, float numeric);
	void sort(IterOrderType order);

private:
	char m_bfmePad[12];
};

class Object
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	bool isKindOf(KindOfType t) const
	{
		return getTemplate()->isKindOf(t);
	}

	float getPosX(void) const { return m_position.x; }
	float getPosY(void) const { return m_position.y; }
	BfmeGroupAI *getAI(void) { return m_ai; }
	unsigned char getDisabledMask(void) const { return m_disabledMask; }

private:
	virtual ~Object();
	const ThingTemplate *m_template;					// +0x04
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;									// +0x38
	unsigned char m_unreconstructed_44[0x1A4 - 0x44];
	unsigned char m_disabledMask;						// +0x1A4
	unsigned char m_unreconstructed_1A5[0x204 - 0x1A5];
	BfmeGroupAI *m_ai;									// +0x204
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupTightenToPosition(const Coord3D *pos, bool addWaypoint,
			CommandSourceType cmdSource);

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;					// +0x04
};

// ?groupTightenToPosition@AIGroup@@QAEXPBUCoord3D@@_NW4CommandSourceType@@@Z
void AIGroup::groupTightenToPosition(const Coord3D *pos, bool addWaypoint,
		CommandSourceType cmdSource)
{
	SimpleObjectIterator *iter = new SimpleObjectIterator;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		Coord3D unitPos;
		unitPos.x = obj->getPosX();
		unitPos.y = obj->getPosY();

		if (obj->getDisabledMask() & 8)
			continue;
		if (obj->isKindOf(KINDOF_IMMOBILE))
			continue;
		if (obj->getAI() == 0)
			continue;

		float dx = unitPos.x - pos->x;
		float dy = unitPos.y - pos->y;
		iter->insert(obj, dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_NEAR_TO_FAR);

	for (Object *theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		BfmeGroupAI *ai = theUnit->getAI();
		if (!addWaypoint)
			ai->m_bfmeCommands.aiTightenToPosition(pos, cmdSource);
		else
			ai->m_bfmeCommands.aiFollowPathAppend(pos, cmdSource);
	}
}
