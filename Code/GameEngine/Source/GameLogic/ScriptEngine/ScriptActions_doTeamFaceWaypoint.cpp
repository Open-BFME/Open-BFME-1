// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/objectdlink /Ireference/shims/stringinline
// readable body of ?doTeamFaceWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

#include "StringInline.h"

typedef bool Bool;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	unsigned char m_pad[0xc];
	Coord3D m_location;
};

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
	void aiFacePosition(const Coord3D *position, int source);
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

class TerrainLogicByValue
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
	virtual void _28()=0; virtual void _29()=0; virtual void _30()=0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamFaceWaypoint(const AsciiString &, const AsciiString &);
};

// ?doTeamFaceWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamFaceWaypoint(const AsciiString &teamName, const AsciiString &waypointName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Waypoint *waypoint = ((TerrainLogicByValue *)TheTerrainLogic)->getWaypointByName(waypointName);
	if (!waypoint)
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
				ai->m_command.aiFacePosition(waypoint->getLocation(), 1);
			}
		}
	}
}
