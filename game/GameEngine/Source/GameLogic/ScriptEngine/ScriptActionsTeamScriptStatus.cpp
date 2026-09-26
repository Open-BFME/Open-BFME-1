// cl: /DNDEBUG /DWIN32 /MD /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/objectdlink
// readable body of ?doTeamSetStrictControlEnabled@ScriptActions@@IAEXABVAsciiString@@_N@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The three team walks that set one script-status bit on every member:
//
//   0x002F46F0  doTeamEnableStealth           bit 0x08, inverted
//   0x002F4780  doTeamSetStrictControlEnabled bit 0x20
//   0x002F5100  d_002f5100                    a helper at 0x002EFB20 instead
//
// The first two are the same body with a different bit; the third is the same
// body again with the per-member call swapped from the thiscall setter to a
// two-explicit-stack-arg helper the caller cleans up after (push value; push
// obj; call; add esp,8). That substitution is its whole 15-byte difference,
// and it still lands at 100 bytes. Its real script-action name is unproven, so
// it keeps its address-derived one.

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
	OBJECT_STATUS_SCRIPT_UNSTEALTHED = 8,
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
	virtual void _se0(void) = 0; virtual void _se1(void) = 0;
	virtual void _se2(void) = 0; virtual void _se3(void) = 0;
	virtual void _se4(void) = 0; virtual void _se5(void) = 0;
	virtual void _se6(void) = 0; virtual void _se7(void) = 0;
	virtual void _se8(void) = 0; virtual void _se9(void) = 0;
	virtual void _se10(void) = 0; virtual void _se11(void) = 0;
	virtual void _se12(void) = 0; virtual void _se13(void) = 0;
	virtual void _se14(void) = 0; virtual void _se15(void) = 0;
	virtual void _se16(void) = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;
// Retail calls this address (0x002EFB20) with two explicit stack args and
// cleans the stack itself afterward, unlike the thiscall bfmeSet1026 its two
// siblings use -- see FlammableUpdate_getModuleNameKey_Thunk.cpp for the same
// address under its currently-matched (unproven, gen-dump) name.
extern "C" void __cdecl bfmeCall_002efb20(void *obj, Bool flag);

class ScriptActions
{
protected:
	void doTeamEnableStealth(const AsciiString &teamName, Bool enabled);
	void doTeamSetStrictControlEnabled(const AsciiString &teamName, Bool enabled);
	void d_002f5100(const AsciiString &teamName, Bool enabled);
};

void ScriptActions::doTeamEnableStealth(
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
				OBJECT_STATUS_SCRIPT_UNSTEALTHED, !enabled);
		}
	}
}

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
