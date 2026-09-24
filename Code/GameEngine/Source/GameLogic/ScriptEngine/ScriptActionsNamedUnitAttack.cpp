// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doNamedAttack@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doNamedAttackArea@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doNamedAttackTeam@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doNamedEnterNamed@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The five actions that send one named unit at something:
//
//   0x003012A0  doNamedAttack               a named unit
//   0x00301330  doNamedAttackArea           a trigger area
//   0x003013B0  doNamedAttackAreaForSeconds the same, then a timer
//   0x00301440  doNamedAttackTeam           a team
//   0x00301990  doNamedEnterNamed           enter a transport
//
// Every one of them is the same four steps: resolve the attacker through
// ScriptEngine slot 26, resolve the target through whichever slot suits its
// kind, take the attacker out of its group, and issue one AICommandInterface
// command. Only the target lookup and the command differ.

#include "StringInline.h"

typedef bool Bool;

class Object;
class PolygonTrigger;
class Team;

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiAttackObject(Object *object, int maxShots, CommandSourceType source);
	// BFME command 0x39: what a giant bird does instead of a normal attack.
	void aiBfmeAttackObject(Object *object, CommandSourceType source);
	void aiAttackTeam(const Team *team, int maxShots, CommandSourceType source);
	void aiAttackArea(const PolygonTrigger *area, CommandSourceType source);
	void aiEnter(Object *object, CommandSourceType source);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

#define OBJECT_TU_MEMBERS \
	void leaveGroup(); \
	Bool bfmeIsGiantBird() const;
#include "../Object/object.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
	virtual void _18()=0; virtual void _19()=0; virtual void _20()=0; virtual void _21()=0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name) = 0;
	virtual void _23()=0; virtual void _24()=0; virtual void _25()=0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
	virtual Object *getUnitNamedByValue(AsciiString name) = 0;

	// Not a slot: the ILT at 0x00044A1C. It is overloaded on the thing being
	// timed -- the Team form is pinned separately at 0x00010DC5.
	void setSequentialTimer(Object *object, int frames);
};

// The three names these bodies cast through to reach a slot the file they lived
// in had not declared. All three are this one vtable.
typedef ScriptEngine ScriptEngineTeamByValue;
typedef ScriptEngine ScriptEngineAreaByValue;
typedef ScriptEngine ScriptEngineByValue;

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedAttack(const AsciiString &, const AsciiString &);
	void doNamedAttackArea(const AsciiString &, const AsciiString &);
	void doNamedAttackAreaForSeconds(const AsciiString &, const AsciiString &, int);
	void doNamedAttackTeam(const AsciiString &, const AsciiString &);
	void doNamedEnterNamed(const AsciiString &, const AsciiString &);
};

// ?doNamedAttack@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doNamedAttack(const AsciiString &attackerName, const AsciiString &victimName)
{
	Object *attacker = TheScriptEngine->getUnitNamed(attackerName);
	Object *victim = TheScriptEngine->getUnitNamed(victimName);
	if (attacker && victim)
	{
		AIUpdateInterface *ai = attacker->m_ai;
		if (ai)
		{
			attacker->leaveGroup();
			if (attacker->bfmeIsGiantBird())
			{
				ai->m_command.aiBfmeAttackObject(victim, CMD_FROM_SCRIPT);
			}
			else
			{
				ai->m_command.aiAttackObject(victim, 0x7fffffff, CMD_FROM_SCRIPT);
			}
		}
	}
}

// ?doNamedAttackArea@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doNamedAttackArea(const AsciiString &unitName, const AsciiString &areaName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
	{
		PolygonTrigger *area = ((ScriptEngineAreaByValue *)TheScriptEngine)->getQualifiedTriggerAreaByName(areaName);
		if (area)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				obj->leaveGroup();
				ai->m_command.aiAttackArea(area, CMD_FROM_SCRIPT);
			}
		}
	}
}

// ?doNamedAttackAreaForSeconds@ScriptActions@@IAEXABVAsciiString@@0H@Z
void ScriptActions::doNamedAttackAreaForSeconds(const AsciiString &unitName, const AsciiString &areaName, int seconds)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
	{
		PolygonTrigger *area = ((ScriptEngineAreaByValue *)TheScriptEngine)->getQualifiedTriggerAreaByName(areaName);
		if (area)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				obj->leaveGroup();
				ai->m_command.aiAttackArea(area, CMD_FROM_SCRIPT);
				TheScriptEngine->setSequentialTimer(obj, seconds * 5);
			}
		}
	}
}

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

// ?doNamedEnterNamed@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doNamedEnterNamed(const AsciiString &unitName, const AsciiString &transportName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
	{
		Object *transport = ((ScriptEngineByValue *)TheScriptEngine)->getUnitNamedByValue(transportName);
		if (transport)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				obj->leaveGroup();
				ai->m_command.aiEnter(transport, CMD_FROM_SCRIPT);
			}
		}
	}
}
