// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_GUARD_IN_TUNNEL_NETWORK handler at retail 0x00303400.

#include "StringInline.h"

typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Object;

class AICommandInterface
{
public:
	void aiGuardTunnelNetwork(int guardMode, CommandSourceType source);
};

class AIUpdateInterface
{
private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

class BfmeObjectVirtualTail
{
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x194];
	AIUpdateInterface *m_ai;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }

	void advance()
	{
		if (m_cur) {
			m_cur = (m_cur->*m_getNextFunc)();
		}
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	Object *m_unused0;
	Object *m_unused1;
	Object *m_unused2;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			&Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void _0() = 0; virtual void _1() = 0; virtual void _2() = 0;
	virtual void _3() = 0; virtual void _4() = 0; virtual void _5() = 0;
	virtual void _6() = 0; virtual void _7() = 0; virtual void _8() = 0;
	virtual void _9() = 0; virtual void _10() = 0; virtual void _11() = 0;
	virtual void _12() = 0; virtual void _13() = 0; virtual void _14() = 0;
	virtual void _15() = 0; virtual void _16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamGuardInTunnelNetwork(const AsciiString &);
};

void ScriptActions::doTeamGuardInTunnelNetwork(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->m_ai;
		if (!ai) {
			continue;
		}
		ai->m_command.aiGuardTunnelNetwork(0, CMD_FROM_SCRIPT);
	}
}
