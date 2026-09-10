// ?groupDoSpecialPowerAtObject@AIGroup@@QAEXIPAVObject@@IW4CommandSourceType@@@Z
// partial score=0.45 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: AIGroup special-power-at-object dispatch, retail RVA 0x00152110.
//
// The named GameLogic dispatcher calls this body for MSG_DO_SPECIAL_POWER_AT_OBJECT.
// BFME orders the members by the target-distance key before asking the action
// manager whether each member may execute the selected power.
// stlport
#include <list>
#include <math.h>

typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

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

class Object;
class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	SpecialPowerTemplate *findSpecialPowerTemplateByID(UnsignedInt id);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class BFMEActionManager
{
public:
	Bool canDoSpecialPowerAtObject(Object *source, Object *target,
		CommandSourceType cmdSource, SpecialPowerTemplate *power,
		UnsignedInt options, Bool forced);
};

extern BFMEActionManager *TheActionManager;

class AIUpdateInterface
{
public:
	unsigned char m_bfmePad[0x48];
	CommandSourceType m_lastCommandSource;
};

class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	AIUpdateInterface *getAI(void)
	{
		return *(AIUpdateInterface **)((char *)this + 0x204);
	}

	void doSpecialPowerAtObject(const SpecialPowerTemplate *power,
		Object *target, UnsignedInt options, Bool forced);
	void friend_setUndetectedDefector(Bool undetected);
};

struct BfmeDistanceEntry
{
	Object *m_object;
	Real m_distance;
};

class AIGroup
{
public:
	void groupDoSpecialPowerAtObject(UnsignedInt specialPowerID,
		Object *target, UnsignedInt commandOptions,
		CommandSourceType cmdSource);

private:
	virtual ~AIGroup();
	_STL::list<Object *> m_memberList;
};

static Real distanceKey(const Coord3D *from, const Coord3D *to)
{
	Real dx = (Real)fabs(from->x - to->x);
	Real dy = (Real)fabs(from->y - to->y);
	return dx + dy;
}

// ?groupDoSpecialPowerAtObject@AIGroup@@QAEXIPAVObject@@IW4CommandSourceType@@@Z
void AIGroup::groupDoSpecialPowerAtObject(UnsignedInt specialPowerID,
	Object *target, UnsignedInt commandOptions, CommandSourceType cmdSource)
{
	_STL::list<BfmeDistanceEntry> sorted;
	for (_STL::list<Object *>::iterator i = m_memberList.begin();
		i != m_memberList.end(); ++i)
	{
		Object *object = *i;
		if (!target)
			continue;

		BfmeDistanceEntry entry;
		entry.m_object = object;
		entry.m_distance = distanceKey(object->getPosition(), target->getPosition());
		_STL::list<BfmeDistanceEntry>::iterator at = sorted.begin();
		while (at != sorted.end() && at->m_distance <= entry.m_distance)
			++at;
		sorted.insert(at, entry);
	}

	for (_STL::list<BfmeDistanceEntry>::iterator i = sorted.begin();
		i != sorted.end(); ++i)
	{
		Object *object = i->m_object;
		AIUpdateInterface *ai = object->getAI();
		if (!ai)
			continue;

		ai->m_lastCommandSource = cmdSource;
		SpecialPowerTemplate *power =
			TheSpecialPowerStore->findSpecialPowerTemplateByID(specialPowerID);
		if (!power)
			continue;
		if (TheActionManager->canDoSpecialPowerAtObject(object, target,
			CMD_FROM_PLAYER, power, commandOptions, false))
		{
			object->doSpecialPowerAtObject(power, target, commandOptions, false);
			object->friend_setUndetectedDefector(false);
		}
	}
}
