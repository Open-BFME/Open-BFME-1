// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doNamedAttackTeam@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

#include "StringInline.h"

typedef bool Bool;

class Object;
class Team;

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiAttackTeam(const Team *team, int maxShots, CommandSourceType source);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void leaveGroup();
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

class ScriptEngineTeamByValue
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedAttackTeam(const AsciiString &, const AsciiString &);
};

// ?doNamedAttackTeam@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doNamedAttackTeam(const AsciiString &unitName, const AsciiString &teamName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
	{
		Team *team = ((ScriptEngineTeamByValue *)TheScriptEngine)->getTeamNamed(teamName, false);
		if (team)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				obj->leaveGroup();
				ai->m_command.aiAttackTeam(team, 0x7fffffff, CMD_FROM_SCRIPT);
			}
		}
	}
}
