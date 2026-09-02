// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME: ScriptActions::doAffectObjectPanelFlagsTeam, retail 0x002FC4C0, 138 bytes.
//
// Team-member walk via Object's virtually-inherited DLINK PMF
// {pfn=0x00401140, delta=-100, vbindex=0}. Layout from ObjectDlinkPmf.h.

#include "ObjectDlinkPmf.h"

typedef bool Bool;

class AsciiString
{
	char *m_data;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
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
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void changeObjectPanelFlagForSingleObject(Object *obj, const AsciiString& flagToChange, Bool newVal);
	void doAffectObjectPanelFlagsTeam(const AsciiString& teamName, const AsciiString& flagName, Bool enable);
};

void ScriptActions::doAffectObjectPanelFlagsTeam(const AsciiString& teamName, const AsciiString& flagName, Bool enable)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		changeObjectPanelFlagForSingleObject(obj, flagName, enable);
	}
}
