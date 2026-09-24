// ?groupDoSpecialPowerAtObject@Rva00152110AIGroup@@QAEXIPAVObject@@IW4CommandSourceType@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: special-power-at-object group dispatch, retail RVA 0x00152110,
// reached from GameLogic::logicMessageDispatcher through ILT 0x0002F126.
// Members are ordered by a dominant-axis distance to the target before the
// power is issued; the AIGroup list sits at this+0x04 and Object AI at +0x204.

#define _STLP_NO_EXCEPTIONS 1
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
	const SpecialPowerTemplate *findSpecialPowerTemplateByID(UnsignedInt id);
};

class ActionManager
{
public:
	Bool canDoSpecialPowerAtObject(const Object *source, const Object *target,
		CommandSourceType commandSource, const SpecialPowerTemplate *power,
		UnsignedInt options, Bool forced);
};

extern SpecialPowerStore *TheSpecialPowerStore;
extern ActionManager *TheActionManager;
extern const Real BfmeZeroRange;

class BfmeAIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[0x48];
	CommandSourceType m_lastCommandSource;
};

class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	BfmeAIUpdateInterface *getAI(void)
	{
		return *(BfmeAIUpdateInterface **)((char *)this + 0x204);
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

class Rva00152110AIGroup
{
public:
	void groupDoSpecialPowerAtObject(UnsignedInt specialPowerID,
		Object *target, UnsignedInt commandOptions,
		CommandSourceType commandSource);

private:
	unsigned char m_unmodelled_000[4];
	_STL::list<Object *> m_memberList;
};

void Rva00152110AIGroup::groupDoSpecialPowerAtObject(
	UnsignedInt specialPowerID, Object *target, UnsignedInt commandOptions,
		CommandSourceType commandSource)
{
	_STL::list<BfmeDistanceEntry> sorted;
	_STL::list<Object *>::iterator i;

	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Real distance = BfmeZeroRange;
		Object *object = *i;
		if (target)
		{
			Coord3D targetPosition = *target->getPosition();
			targetPosition.x -= object->getPosition()->x;
			targetPosition.y -= object->getPosition()->y;
			if ((Real)fabs(targetPosition.x) > (Real)fabs(targetPosition.y))
				distance = (Real)fabs(targetPosition.x) + (Real)fabs(targetPosition.y) * 0.25f;
			else
				distance = (Real)fabs(targetPosition.y) + (Real)fabs(targetPosition.x) * 0.25f;
		}

		BfmeDistanceEntry entry;
		entry.m_object = object;
		entry.m_distance = distance;
		Bool inserted = false;
		_STL::list<BfmeDistanceEntry>::iterator at;
		for (at = sorted.begin(); at != sorted.end(); ++at)
		{
			if (entry.m_distance < at->m_distance)
			{
				sorted.insert(at, entry);
				inserted = true;
				break;
			}
		}
		if (!inserted)
			sorted.push_back(entry);
	}

	for (_STL::list<BfmeDistanceEntry>::iterator j = sorted.begin();
		j != sorted.end(); ++j)
	{
		Object *object = j->m_object;
		BfmeAIUpdateInterface *ai = object->getAI();
		if (ai)
			ai->m_lastCommandSource = commandSource;
		const SpecialPowerTemplate *power =
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
