// ?groupDoSpecialPowerAtObject@AIGroup@@QAEXIPAVObject@@IW4CommandSourceType@@@Z
// partial score=0.65 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: BFME's ordered special-power-at-object group dispatch,
// retail RVA 0x00152110.
//
// The BFME body copies the target position and orders members by the
// dominant horizontal axis before checking the selected power.  The local
// mirror keeps the witnessed AIGroup list at this+0x04 and the Object AI
// pointer at this+0x204.

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
		CommandSourceType cmdSource, const SpecialPowerTemplate *power,
		UnsignedInt options, Bool forced);
};

extern SpecialPowerStore *TheSpecialPowerStore;
extern ActionManager *TheActionManager;

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
		CommandSourceType cmdSource);

private:
	unsigned char m_unmodelled_000[4];
	_STL::list<Object *> m_memberList;
};

// ?groupDoSpecialPowerAtObject@AIGroup@@QAEXIPAVObject@@IW4CommandSourceType@@@Z
void Rva00152110AIGroup::groupDoSpecialPowerAtObject(
	UnsignedInt specialPowerID, Object *target, UnsignedInt commandOptions,
	CommandSourceType cmdSource)
{
	_STL::list<BfmeDistanceEntry> sorted;
	_STL::list<Object *>::iterator i;

	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Real distance = *(const Real *)0x01075350;
		Object *object = *i;
		if (target)
		{
			Coord3D targetPosition = *target->getPosition();
			targetPosition.x -= object->getPosition()->x;
			targetPosition.y -= object->getPosition()->y;
			if ((Real)fabs(targetPosition.x) > (Real)fabs(targetPosition.y))
				distance = (Real)fabs(targetPosition.x) + (Real)fabs(targetPosition.y) * *(const Real *)0x01083B6C;
			else
				distance = (Real)fabs(targetPosition.y) + (Real)fabs(targetPosition.x) * *(const Real *)0x01083B6C;
		}

		BfmeDistanceEntry entry;
		entry.m_object = object;
		entry.m_distance = distance;
		_STL::list<BfmeDistanceEntry>::iterator at = sorted.begin();
		for (; at != sorted.end(); ++at)
		{
			if (at->m_distance > entry.m_distance)
				break;
		}
		if (at == sorted.end())
			sorted.push_back(entry);
		else
			sorted.insert(at, entry);
	}

	for (_STL::list<BfmeDistanceEntry>::iterator j = sorted.begin();
		j != sorted.end(); ++j)
	{
		Object *object = j->m_object;
		BfmeAIUpdateInterface *ai = object->getAI();
		if (!ai)
			continue;

		ai->m_lastCommandSource = cmdSource;
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
