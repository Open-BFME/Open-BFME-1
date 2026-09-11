// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Clean C++ recovery of TEAM_WANDER_IN_PLACE.
// Retail RVA 0x00301FE0 (134 bytes).  script_engine.cpp sets
// m_actionTemplates[237].m_internalName to "TEAM_WANDER_IN_PLACE", and the
// executeAction jump table at VA 0x0070D6A0 sends arm 237 to this body.  The
// tail call is ?aiWanderInPlace@AICommandInterface@@QAEXW4CommandSourceType@@@Z
// at retail 0x00300420, reached through ILT 0x000048FE, which names the action
// on its own.  The member walk is the same virtually-inherited Object DLINK
// dispatch that ScriptActionsTeamMemberWalk.cpp already lands.

#include "ObjectDlinkPmf.h"

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
	unsigned char m_pad[0x14];
	AsciiString m_name;
public:
	const AsciiString& getName() const { return m_name; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	unsigned char m_pad[0x230];
	Team *m_defaultTeam;
public:
	Team *getDefaultTeam() { return m_defaultTeam; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupIdle(int cmdSource);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
	void aiWanderInPlace(CommandSourceType source);
};

// The AI update's vtable slot 0x1FC takes the mode constant 3.  Its retail name
// is unresolved, so the slot keeps a positional spelling.
class AIUpdate
{
public:
	virtual void _ai_0() = 0;
	virtual void _ai_1() = 0;
	virtual void _ai_2() = 0;
	virtual void _ai_3() = 0;
	virtual void _ai_4() = 0;
	virtual void _ai_5() = 0;
	virtual void _ai_6() = 0;
	virtual void _ai_7() = 0;
	virtual void _ai_8() = 0;
	virtual void _ai_9() = 0;
	virtual void _ai_10() = 0;
	virtual void _ai_11() = 0;
	virtual void _ai_12() = 0;
	virtual void _ai_13() = 0;
	virtual void _ai_14() = 0;
	virtual void _ai_15() = 0;
	virtual void _ai_16() = 0;
	virtual void _ai_17() = 0;
	virtual void _ai_18() = 0;
	virtual void _ai_19() = 0;
	virtual void _ai_20() = 0;
	virtual void _ai_21() = 0;
	virtual void _ai_22() = 0;
	virtual void _ai_23() = 0;
	virtual void _ai_24() = 0;
	virtual void _ai_25() = 0;
	virtual void _ai_26() = 0;
	virtual void _ai_27() = 0;
	virtual void _ai_28() = 0;
	virtual void _ai_29() = 0;
	virtual void _ai_30() = 0;
	virtual void _ai_31() = 0;
	virtual void _ai_32() = 0;
	virtual void _ai_33() = 0;
	virtual void _ai_34() = 0;
	virtual void _ai_35() = 0;
	virtual void _ai_36() = 0;
	virtual void _ai_37() = 0;
	virtual void _ai_38() = 0;
	virtual void _ai_39() = 0;
	virtual void _ai_40() = 0;
	virtual void _ai_41() = 0;
	virtual void _ai_42() = 0;
	virtual void _ai_43() = 0;
	virtual void _ai_44() = 0;
	virtual void _ai_45() = 0;
	virtual void _ai_46() = 0;
	virtual void _ai_47() = 0;
	virtual void _ai_48() = 0;
	virtual void _ai_49() = 0;
	virtual void _ai_50() = 0;
	virtual void _ai_51() = 0;
	virtual void _ai_52() = 0;
	virtual void _ai_53() = 0;
	virtual void _ai_54() = 0;
	virtual void _ai_55() = 0;
	virtual void _ai_56() = 0;
	virtual void _ai_57() = 0;
	virtual void _ai_58() = 0;
	virtual void _ai_59() = 0;
	virtual void _ai_60() = 0;
	virtual void _ai_61() = 0;
	virtual void _ai_62() = 0;
	virtual void _ai_63() = 0;
	virtual void _ai_64() = 0;
	virtual void _ai_65() = 0;
	virtual void _ai_66() = 0;
	virtual void _ai_67() = 0;
	virtual void _ai_68() = 0;
	virtual void _ai_69() = 0;
	virtual void _ai_70() = 0;
	virtual void _ai_71() = 0;
	virtual void _ai_72() = 0;
	virtual void _ai_73() = 0;
	virtual void _ai_74() = 0;
	virtual void _ai_75() = 0;
	virtual void _ai_76() = 0;
	virtual void _ai_77() = 0;
	virtual void _ai_78() = 0;
	virtual void _ai_79() = 0;
	virtual void _ai_80() = 0;
	virtual void _ai_81() = 0;
	virtual void _ai_82() = 0;
	virtual void _ai_83() = 0;
	virtual void _ai_84() = 0;
	virtual void _ai_85() = 0;
	virtual void _ai_86() = 0;
	virtual void _ai_87() = 0;
	virtual void _ai_88() = 0;
	virtual void _ai_89() = 0;
	virtual void _ai_90() = 0;
	virtual void _ai_91() = 0;
	virtual void _ai_92() = 0;
	virtual void _ai_93() = 0;
	virtual void _ai_94() = 0;
	virtual void _ai_95() = 0;
	virtual void _ai_96() = 0;
	virtual void _ai_97() = 0;
	virtual void _ai_98() = 0;
	virtual void _ai_99() = 0;
	virtual void _ai_100() = 0;
	virtual void _ai_101() = 0;
	virtual void _ai_102() = 0;
	virtual void _ai_103() = 0;
	virtual void _ai_104() = 0;
	virtual void _ai_105() = 0;
	virtual void _ai_106() = 0;
	virtual void _ai_107() = 0;
	virtual void _ai_108() = 0;
	virtual void _ai_109() = 0;
	virtual void _ai_110() = 0;
	virtual void _ai_111() = 0;
	virtual void _ai_112() = 0;
	virtual void _ai_113() = 0;
	virtual void _ai_114() = 0;
	virtual void _ai_115() = 0;
	virtual void _ai_116() = 0;
	virtual void _ai_117() = 0;
	virtual void _ai_118() = 0;
	virtual void _ai_119() = 0;
	virtual void _ai_120() = 0;
	virtual void _ai_121() = 0;
	virtual void _ai_122() = 0;
	virtual void _ai_123() = 0;
	virtual void _ai_124() = 0;
	virtual void _ai_125() = 0;
	virtual void _ai_126() = 0;
	virtual void _ai_127(int mode) = 0;

	AICommandInterface *commands(void)
	{
		return (AICommandInterface *)((char *)this + 0x20);
	}
};

class ObjectAIUpdate
{
	unsigned char m_pad[0x204];
	AIUpdate *m_ai;

public:
	AIUpdate *getAIUpdate(void) { return m_ai; }
};

class ScriptActions
{
protected:
	void doTeamWanderInPlace(const AsciiString &teamName);
};

// ?doTeamWanderInPlace@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamWanderInPlace(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		AIUpdate *ai = ((ObjectAIUpdate *)iter.cur())->getAIUpdate();
		if (ai)
		{
			ai->_ai_127(3);
			ai->commands()->aiWanderInPlace(CMD_FROM_SCRIPT);
		}
	}
}
