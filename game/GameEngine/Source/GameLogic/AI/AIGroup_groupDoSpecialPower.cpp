// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplateByID(UnsignedInt id);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class AIUpdateInterface
{
public:
	char m_pad00[0x48];
	CommandSourceType m_lastCommandSource;
};

class Object
{
public:
	void doSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		UnsignedInt commandOptions, Bool forced);
	void friend_setUndetectedDefector(Bool status);

	AIUpdateInterface *getAIUpdateInterface()
	{
		return m_ai;
	}

private:
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;
};

class ActionManager
{
public:
	Bool canDoSpecialPower(const Object *object,
		const SpecialPowerTemplate *specialPowerTemplate,
		CommandSourceType commandSource, UnsignedInt commandOptions,
		Bool checkSourceRequirements);
};

extern ActionManager *TheActionManager;

class AIGroup
{
public:
	void groupDoSpecialPower(UnsignedInt specialPowerID,
		UnsignedInt commandOptions, CommandSourceType commandSource);

private:
	char m_pad00[4];
	_STL::list<Object *> m_memberList;
};

void AIGroup::groupDoSpecialPower(UnsignedInt specialPowerID,
	UnsignedInt commandOptions, CommandSourceType commandSource)
{
	for (_STL::list<Object *>::iterator i = m_memberList.begin();
		i != m_memberList.end(); ++i)
	{
		Object *object = *i;
		AIUpdateInterface *ai = object->getAIUpdateInterface();
		if (ai != 0)
			ai->m_lastCommandSource = commandSource;
		const SpecialPowerTemplate *specialPowerTemplate =
			TheSpecialPowerStore->findSpecialPowerTemplateByID(specialPowerID);
		if (specialPowerTemplate != 0)
		{
			if (TheActionManager->canDoSpecialPower(object, specialPowerTemplate,
				CMD_FROM_PLAYER, commandOptions, true))
			{
				object->doSpecialPower(specialPowerTemplate, commandOptions, false);
				object->friend_setUndetectedDefector(false);
			}
		}
	}
}
