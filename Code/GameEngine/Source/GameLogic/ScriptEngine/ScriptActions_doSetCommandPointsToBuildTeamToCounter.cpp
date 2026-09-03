// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/objectdlink
// Open-BFME: SET_COMMAND_POINTS_TO_BUILD_TEAM_TO_COUNTER at retail RVA
// 0x002F6850.

#include "StringInline.h"
#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef int Int;

class ScriptActions;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_beforeCommandPoints[0x4ac];
	Int m_commandPoints;
};

static const ThingTemplate *bfmeObjectTemplate(const Object *object)
{
	return *reinterpret_cast<const ThingTemplate *const *>(
		reinterpret_cast<const char *>(object) + 4);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
private:
	void *m_vptr;
	void *m_prototype;
	void *m_id;

public:
	Object *m_head;
};

template<class OBJCLASS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
protected:
	friend class ScriptActions;
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool unused) = 0;

	struct ScriptCounter *bfmeCounter(AsciiString name);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

struct ScriptCounter
{
	Int m_value;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetCommandPointsToBuildTeamToCounter(Parameter *team,
		Parameter *counter);
};

void ScriptActions::doSetCommandPointsToBuildTeamToCounter(Parameter *team,
	Parameter *counter)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team->m_string, false);
	if (!theTeam)
		return;

	Int value = 0;
	for (DLINK_ITERATOR<Object> iter =
		DLINK_ITERATOR<Object>(theTeam->m_head,
			Object::dlink_next_TeamMemberList);
		!iter.done(); iter.advance())
	{
		const ThingTemplate *thingTemplate = bfmeObjectTemplate(iter.cur());
		if (thingTemplate && thingTemplate->m_nextOverride)
		{
			thingTemplate = reinterpret_cast<const ThingTemplate *>(
				thingTemplate->m_nextOverride->getFinalOverride());
		}
		value += thingTemplate->m_commandPoints;
	}

	ScriptCounter *destination =
		TheScriptEngine->bfmeCounter(counter->m_string);
	destination->m_value = value;
}
