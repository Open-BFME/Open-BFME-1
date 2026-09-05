// cl: /DNDEBUG /DWIN32 /MD /Ireference/shims/stringinline /Ireference/shims/objectdlink
// Open-BFME: near-twin of ScriptActions::doTeamSetStrictControlEnabled
// (retail 0x002F4780, Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamSetStrictControlEnabled.cpp).
// Same team-walk shape (TheScriptEngine->getTeamNamed then DLINK_ITERATOR<Object>
// over the team member list), but the per-member call differs: retail calls a
// two-explicit-stack-arg helper at 0x002EFB20 (caller cleans up, `add esp,8`)
// instead of the thiscall bfmeSet1026(bit, enabled) the twin uses (callee
// cleans, no `add esp`). That single substitution plus the push-shape it
// requires (push value; push obj; call; add esp,8 -- 3 fewer bytes at the
// call site, 3 more for the cleanup) is the whole 15-byte diff, still 100
// bytes total. The real ZH name is not established, so this lands under an
// address-derived name in ScriptActions, matching the convention the other
// d_002f51xx neighbours in this file already use.

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

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x194];
};

// retail calls this address (0x002EFB20) with two explicit stack args and
// cleans the stack itself afterward (`add esp,8`), unlike the thiscall
// bfmeSet1026 the twin uses -- see FlammableUpdate_getModuleNameKey_Thunk.cpp
// for the same address under its currently-matched (unproven, gen-dump) name.
extern "C" void __cdecl bfmeCall_002efb20(void *obj, Bool flag);

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
	void d_002f5100(const AsciiString &teamName, Bool enabled);
};

void ScriptActions::d_002f5100(
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
			bfmeCall_002efb20(obj, enabled);
		}
	}
}
