// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?doAffectObjectPanelFlagsTeam@ScriptActions@@IAEXABVAsciiString@@0_N@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamStop@ScriptActions@@IAEXABVAsciiString@@_N@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The two actions that walk a team's members through Object's
// virtually-inherited DLINK pointer-to-member {pfn=0x00401140, delta=-100,
// vbindex=0}:
//
//   0x002FC4C0  doAffectObjectPanelFlagsTeam  a command-panel flag per member
//   0x002FDDB0  doTeamStop                    idle the group, optionally disband
//
// doTeamStop's disband arm is the walk: it makes every member recruitable again
// and then merges the team into its player's default team.
#include "ObjectDlinkPmf.h"

typedef bool Bool;

#include "ascii_string.h"

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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
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

class AIGroup;
class Player;
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
	unsigned char m_pad[0x14];
	AsciiString m_name;
public:
	const AsciiString& getName() const { return m_name; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
	void *m_vptr;
	TeamPrototype *m_proto;
	void *m_id;
	Object *m_head;
public:
	Player *getControllingPlayer() const;
	void getTeamAsAIGroup(AIGroup *pAIGroup);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
	const AsciiString& getName() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	unsigned char m_pad[0x230];
	Team *m_defaultTeam;
public:
	Team *getDefaultTeam() { return m_defaultTeam; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
	unsigned char m_pad[0x32C];
	unsigned char m_isRecruitable;
public:
	void setIsRecruitable(Bool recruitable) { m_isRecruitable = recruitable ? 1 : 0; }
};

class ObjectAI
{
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupIdle(int cmdSource);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
extern AI *TheAI;
extern AsciiString TheEmptyString;

// ?getName@Team@@QBEABVAsciiString@@XZ present-unmatched
const AsciiString& Team::getName() const
{
	if (!m_proto)
		return TheEmptyString;
	return m_proto->getName();
}

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void changeObjectPanelFlagForSingleObject(Object *obj, const AsciiString& flagToChange, Bool newVal);
	void doMergeTeamIntoTeam(const AsciiString& teamSrcName, const AsciiString& teamDestName);
	void doAffectObjectPanelFlagsTeam(const AsciiString& teamName, const AsciiString& flagName, Bool enable);
	void doTeamStop(const AsciiString& teamName, Bool shouldDisband);
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

void ScriptActions::doTeamStop(const AsciiString& teamName, Bool shouldDisband)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	theTeam->getTeamAsAIGroup(theGroup);
	theGroup->groupIdle(CMD_FROM_SCRIPT);

	if (shouldDisband) {
		Team *playerDefaultTeam = theTeam->getControllingPlayer()->getDefaultTeam();

		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();

			AIUpdateInterface *ai = ((ObjectAI *)obj)->getAIUpdateInterface();
			if (!ai) {
				continue;
			}

			ai->setIsRecruitable(true);
		}

		doMergeTeamIntoTeam(teamName, playerDefaultTeam->getName());
	}
}
