// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/objectdlink /Ireference/shims/stringinline
// readable body of ?doTeamFaceNamed@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

#include "StringInline.h"

typedef bool Bool;

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0( void ); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	void leaveGroup();
	unsigned char m_tail[0x40];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiFaceObject(Object *object, CommandSourceType source);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void clearWaypointQueue();

private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

class ObjectAI
{
private:
	unsigned char m_pad[0x204];

public:
	AIUpdateInterface *m_ai;
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)( void ) const;

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_unmodelled0;
	void *m_unmodelled1;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0;
	virtual Team *getTeamNamed(AsciiString name, Bool playerOwned) = 0;
};

class ScriptEngineByValue
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0;
	virtual Object *getUnitNamedByValue(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamFaceNamed(const AsciiString &, const AsciiString &);
};

// ?doTeamFaceNamed@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamFaceNamed(const AsciiString &teamName, const AsciiString &faceUnitName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Object *faceObj = ((ScriptEngineByValue *)TheScriptEngine)->getUnitNamedByValue(faceUnitName);
	if (!faceObj)
		return;

	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (obj)
		{
			AIUpdateInterface *ai = *(AIUpdateInterface **)((unsigned char *)obj + 0x204);
			if (ai)
			{
				ai->clearWaypointQueue();
				obj->leaveGroup();
				ai->m_command.aiFaceObject(faceObj, CMD_FROM_SCRIPT);
			}
		}
	}
}
