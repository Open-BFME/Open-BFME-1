// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib
// ScriptActions::doTeamGuard, retail RVA 0x00301C10, 160 bytes.
//
// Zero Hour twin: ScriptActions::doTeamGuard, reached from the executeAction
// TEAM_GUARD arm. BFME skips members with object status bit 37 or bit 2 set
// before ordering the rest to guard their current position; the walk and
// the position copy are those of doTeamGuardForFramecount (0x00302C70).
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

#include "../command_source_type.h"

class BfmeAsciiStringArg : public AsciiString
{
public:
	BfmeAsciiStringArg(const AsciiString &that) : AsciiString(that) {}
	~BfmeAsciiStringArg();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, GuardMode guardMode,
		CommandSourceType cmdSource);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
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

// Object status bits live at +0x90.
template<int BIT>
static __forceinline unsigned int bfmeTestStatus(const Object *object)
{
	const unsigned int *status = (const unsigned int *)((const unsigned char *)object + 0x90);
	return status[BIT / 32] & (1u << (BIT % 32));
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
// Only the TeamMemberList DLINK head at +0x0C is read here.
class Team
{
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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

class ScriptActions
{
protected:
	// ?doTeamGuard@ScriptActions@@IAEXABVAsciiString@@@Z
	void doTeamGuard(const AsciiString &teamName);
};

void ScriptActions::doTeamGuard(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	// Have all the members of the team guard at their current pos.
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (bfmeTestStatus<37>(obj))
			continue;
		if (bfmeTestStatus<2>(obj))
			continue;
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
}
