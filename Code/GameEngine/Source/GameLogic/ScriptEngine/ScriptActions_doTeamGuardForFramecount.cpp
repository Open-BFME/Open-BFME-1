// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /ICode/Libraries/Source/WWVegas/WWLib
// ScriptActions::doTeamGuardForFramecount, retail RVA 0x00302C70, 202 bytes.
//
// Zero Hour twin: ScriptActions::doTeamGuardForFramecount (team lookup, member
// walk, guard at the current position, sequential timer). BFME adds the same
// seconds flag as the matched unit sibling at 0x00302B40 (framecount * 5).
//
// The guard position is copied inside the `if (ai)` block. Declaring the local
// in a scope that opens after the member pointer is known lets MSVC 7.1 hoist
// the y and z loads above the x and y stores, which is retail's copy schedule;
// a local scoped to the whole loop body keeps each load beside its store.

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, GuardMode guardMode,
		CommandSourceType cmdSource);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	unsigned char m_beforeCommands[0x20];
	AICommandInterface m_commands;
};

static __forceinline AIUpdateInterface *bfmeGetAIUpdateInterface(Object *object)
{
	return *(AIUpdateInterface **)((unsigned char *)object + 0x204);
}

static __forceinline const Coord3D *bfmeGetPosition(const Object *object)
{
	return (const Coord3D *)((const unsigned char *)object + 0x38);
}

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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

	void setSequentialTimer(Team *team, Int frameCount);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	// ?doTeamGuardForFramecount@ScriptActions@@IAEXABVAsciiString@@H_N@Z
	void doTeamGuardForFramecount(const AsciiString &teamName, Int framecount,
		Bool seconds);
};

void ScriptActions::doTeamGuardForFramecount(const AsciiString &teamName,
	Int framecount, Bool seconds)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	// Have all the members of the team guard at their current pos.
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = bfmeGetAIUpdateInterface(obj);
		if (ai)
		{
			const Coord3D *objPos = bfmeGetPosition(obj);
			Coord3D pos;
			pos.x = objPos->x;
			pos.y = objPos->y;
			pos.z = objPos->z;
			ai->m_commands.aiGuardPosition(&pos, GUARDMODE_NORMAL,
				CMD_FROM_SCRIPT);
		}
	}

	if (seconds)
		TheScriptEngine->setSequentialTimer(theTeam, framecount * 5);
	else
		TheScriptEngine->setSequentialTimer(theTeam, framecount);
}
