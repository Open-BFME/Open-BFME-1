// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
};

class ObjectModuleBase
{
public:
	virtual void objectModuleSlot0() = 0;

protected:
	void *m_moduleData;
	Object *m_object;

	friend class Object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot0() = 0;
	virtual void behaviorSlot1() = 0;
	virtual ContainModuleInterface *getContain() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModuleBase, public BehaviorModuleInterface
{
};

#define OBJECT_TU_MEMBERS \
	void bfmeSwapContainModule(Object *other);
#include "object.h"

void Object::bfmeSwapContainModule(Object *other)
{
	BehaviorModule **mine = m_behaviors;
	while (*mine != 0)
	{
		if ((*mine)->getContain() == m_contain)
			break;
		++mine;
	}

	BehaviorModule **theirs = other->m_behaviors;
	while (*theirs != 0)
	{
		if ((*theirs)->getContain() == other->m_contain)
			break;
		++theirs;
	}

	if (*theirs != 0)
	{
		BehaviorModule *temporary = *mine;
		*mine = *theirs;
		*theirs = temporary;

		ContainModuleInterface *temporaryContain = m_contain;
		m_contain = other->m_contain;
		other->m_contain = temporaryContain;

		(*mine)->m_object = this;
		(*theirs)->m_object = other;
	}
}
