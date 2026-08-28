// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift ScriptActions::doTeamAttackNamed to clean C++.

typedef int Int;
typedef bool Bool;

class AsciiString;
class AIGroup;
class Object;
class Team;

template <class T> class StringBase
{
	friend class AsciiString;

public:
	int compare(const char *) const;

private:
	StringBase(const StringBase &);
	~StringBase();
	struct Header;
	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	~AsciiString();
	int compare(const char *str) const
	{
		return ((const StringBase<char> *)this)->compare(str);
	}

private:
	char *m_text;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool);
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
private:
	void groupAttackObjectPrivate(Bool, Object *, Int, CommandSourceType);

public:
	void groupAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource)
	{
		groupAttackObjectPrivate(false, victim, maxShotsToFire, cmdSource);
	}
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamAttackNamed(const AsciiString &, const AsciiString &);
};

// ?doTeamAttackNamed@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamAttackNamed(const AsciiString &teamName, const AsciiString &unitName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam) {
		return;
	}

	Object *theVictim = TheScriptEngine->getUnitNamed(unitName);
	if (!theVictim) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	theTeam->getTeamAsAIGroup(theGroup);
	if (teamName.compare("Aragorn 2") == 0) {
		theGroup->groupAttackObject(theVictim, 0x7fffffff, CMD_FROM_PLAYER);
	}
	theGroup->groupAttackObject(theVictim, 0x7fffffff, CMD_FROM_SCRIPT);
}
