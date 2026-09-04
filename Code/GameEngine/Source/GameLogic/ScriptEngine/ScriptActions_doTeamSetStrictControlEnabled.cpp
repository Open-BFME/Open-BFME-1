// cl: /DNDEBUG /DWIN32 /MD /Ireference/shims/stringinline /Ireference/shims/objectdlink
// Open-BFME: ScriptActions::doTeamSetStrictControlEnabled, retail 0x002F4780, 100 bytes.
//
// The BFME strict-control action is the team counterpart of the status setter
// at Object::setScriptStatus.  The retail team walk uses Object's virtual-base
// DLINK member-function representation and sets status bit 0x20 on every member.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
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
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_STRICT_CONTROL = 0x20
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x194];
};

class BfmeX1026
{
public:
	void bfmeSet1026(Int bit, char set);
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)(void) const;

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

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS *cur() const
	{
		return m_cur;
	}
};

class Team
{
public:
	Object *m_unmodelled0;
	Object *m_unmodelled1;
	Object *m_unmodelled2;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void _se0() = 0; virtual void _se1() = 0;
	virtual void _se2() = 0; virtual void _se3() = 0;
	virtual void _se4() = 0; virtual void _se5() = 0;
	virtual void _se6() = 0; virtual void _se7() = 0;
	virtual void _se8() = 0; virtual void _se9() = 0;
	virtual void _se10() = 0; virtual void _se11() = 0;
	virtual void _se12() = 0; virtual void _se13() = 0;
	virtual void _se14() = 0; virtual void _se15() = 0;
	virtual void _se16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamSetStrictControlEnabled(const AsciiString &teamName, Bool enabled);
};

void ScriptActions::doTeamSetStrictControlEnabled(
	const AsciiString &teamName, Bool enabled)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theSrcTeam)
	{
		return;
	}

	if (theSrcTeam)
	{
		for (DLINK_ITERATOR<Object> iter = theSrcTeam->iterate_TeamMemberList();
			!iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj)
			{
				continue;
			}
			((BfmeX1026 *)obj)->bfmeSet1026(
				OBJECT_STATUS_SCRIPT_STRICT_CONTROL, enabled);
		}
	}
}
