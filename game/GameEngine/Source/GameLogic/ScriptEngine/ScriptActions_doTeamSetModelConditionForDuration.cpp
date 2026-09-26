// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib
// ScriptActions::doTeamSetModelConditionForDuration, retail RVA 0x002FAD50, 358 bytes.
//
// Identity: the TEAM_SET_MODELCONDITION_FOR_DURATION case of the matched
// ScriptActions::executeAction at 0x00303BF0 calls this body. It is the team
// form of the matched unit sibling at 0x002FABE0: the same 0x130-entry
// condition-name table lookup, then every team member receives the condition
// and the duration in logic frames through the pinned ILT 0x0002852E.
//
// The Zero Hour DLINK_ITERATOR::advance null test and the Zero Hour team-walk
// idiom `Object *obj = iter.cur(); if (!obj) continue;` are both needed: the
// guard is folded away, but without it MSVC 7.1 puts a four-byte alignment
// pad before the member walk that retail does not have.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

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

class BfmeItemRY
{
public:
	void bfmeDoRY(void *condition, void *frames);
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

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
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance(void)
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done(void) const
	{
		return m_cur == 0;
	}

	OBJCLASS *cur(void) const
	{
		return m_cur;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
// Only the TeamMemberList DLINK head at +0x0C is read here.
class Team
{
	void *m_unmodelled00;
	void *m_unmodelled04;
	void *m_unmodelled08;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern "C" const char *bfmeGlobalTable12A6918[];

class ScriptActions
{
protected:
	void doTeamSetModelConditionForDuration(
		const AsciiString &teamName, const AsciiString &conditionName,
		Real duration, Int percent);
};

void ScriptActions::doTeamSetModelConditionForDuration(
	const AsciiString &teamName, const AsciiString &conditionName,
	Real duration, Int percent)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	Int condition;
	condition = 0;
	Int frames;
	for (; condition < 0x130; ++condition)
	{
		AsciiString name(bfmeGlobalTable12A6918[condition]);
		if (conditionName.compare(name) == 0)
		{
			frames = (Int)(duration * (*(const Real *)0x01075344));
			goto matched;
		}
	}
	return;

matched:
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (!obj)
			continue;
		((BfmeItemRY *)obj)->bfmeDoRY((void *)condition, (void *)frames);
	}
}
