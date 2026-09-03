// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/objectdlink
// Open-BFME: TEAM_ASSIMILATE_WITH_FIRST_WALK_ON_ARMY at retail RVA 0x002F73D0.

#include "StringInline.h"
#include "ObjectDlinkPmf.h"

typedef bool Bool;

class Team;
class BfmeGlobFEA;
class ScriptActions;

template<class OBJCLASS>
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

class Team
{
private:
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
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
};

class BfmeGlobFEA
{
public:
	void bfmeCallFEA(void *object, int army);
};

extern ScriptEngine *TheScriptEngine;
extern BfmeGlobFEA *TheGameLogic;

extern void j_0001867e();

typedef int (__fastcall *BfmeFirstWalkOnArmyThunk)(BfmeGlobFEA *gameLogic);

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ScriptActions
{
protected:
	void doTeamAssimilateWithFirstWalkOnArmy(Parameter *team);
};

void ScriptActions::doTeamAssimilateWithFirstWalkOnArmy(Parameter *team)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team->m_string, false);
	if (theTeam)
	{
		int army = ((BfmeFirstWalkOnArmyThunk)j_0001867e)(TheGameLogic);
		if (army >= 0)
		{
			for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
				!iter.done(); iter.advance())
			{
				if (iter.cur())
					TheGameLogic->bfmeCallFEA(iter.cur(), army);
			}
		}
	}
}
