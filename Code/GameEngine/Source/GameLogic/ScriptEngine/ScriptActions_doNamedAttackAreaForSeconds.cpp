// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef bool Bool;

class Object;
class PolygonTrigger;

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiAttackArea(const PolygonTrigger *area, CommandSourceType source);
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
	void setSequentialTimer(Object *object, int frames);
};

class ScriptEngineAreaByValue
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedAttackAreaForSeconds(const AsciiString &, const AsciiString &, int);
};

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
