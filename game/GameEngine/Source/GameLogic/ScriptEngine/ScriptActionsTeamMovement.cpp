// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/objectdlink /Iinputs/reference/shims/stringinline
// readable body of ?doTeamFaceNamed@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doTeamFaceWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The four actions that give a whole team a movement or facing order:
//
//   0x002F3080  doTeamFollowWaypoints       347 bytes, team/formation/plain arms
//   0x002F3240  doTeamFollowWaypointsExact  316 bytes, the exact-path arms
//   0x00303200  doTeamFaceNamed             199 bytes
//   0x00303300  doTeamFaceWaypoint          202 bytes
//
// All four resolve the team through ScriptEngine slot 17 and then walk its
// member list through Object's virtually-inherited DLINK pointer-to-member. The
// two follow actions average the members' positions to find a path start and
// give the order to the group; the two face actions give it to each member's
// own AICommandInterface.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Object;

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
	Coord3D(void) { }
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) { }
	float lengthSqr(void) const { return x * x + y * y + z * z; }
	void normalize(void) { }
};

// The four bases that reproduce Object's retail layout: the vtable pointer, the
// DLINK entry the team list threads through, the 0x64-byte run that carries the
// position at +0x38, and the vbptr carrier whose virtual base sits at the tail.
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_beforePosition[0x34];
	Coord3D m_position;
	unsigned char m_afterPosition[0x24];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	void leaveGroup();
	unsigned char m_tail[0x40];
	const Coord3D *getPosition(void) const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	unsigned char m_pad[0xc];
	Coord3D m_location;
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiFaceObject(Object *object, CommandSourceType source);
	// Spelled with a plain int to match the pin at 0x00040732.
	void aiFacePosition(const Coord3D *position, int source);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void clearWaypointQueue();

private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupFollowWaypointPathAsTeam(const Waypoint *way,
		CommandSourceType cmdSource);
	void groupFollowWaypointPathAsTeamClearFormation(const Waypoint *way,
		CommandSourceType cmdSource);
	void groupFollowWaypointPath(const Waypoint *way,
		CommandSourceType cmdSource);
	void groupFollowWaypointPathAsTeamExact(const Waypoint *way,
		CommandSourceType cmdSource);
	void groupFollowWaypointPathExact(const Waypoint *way,
		CommandSourceType cmdSource);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_unmodelled0;
	void *m_unmodelled1;
	Object *m_head;

	void getTeamAsAIGroup(AIGroup *group);

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0;
	virtual Team *getTeamNamed(AsciiString name, Bool playerOwned) = 0;
	virtual void _18()=0; virtual void _19()=0; virtual void _20()=0; virtual void _21()=0;
	virtual void _22()=0; virtual void _23()=0; virtual void _24()=0; virtual void _25()=0;
	virtual void _26()=0;
	virtual Object *getUnitNamedByValue(AsciiString name) = 0;
};

// The name doTeamFaceNamed casts through to reach slot 27; it is this vtable.
typedef ScriptEngine ScriptEngineByValue;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
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
	virtual void _32()=0;
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos,
		AsciiString label) = 0;
};

// The name doTeamFaceWaypoint casts through to reach slot 31.
typedef TerrainLogic TerrainLogicByValue;

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamFollowWaypoints(const AsciiString &teamName,
		const AsciiString &waypointPathLabel, Bool inFormation, Bool asTeam);
	void doTeamFollowWaypointsExact(const AsciiString &teamName,
		const AsciiString &waypointPathLabel, Bool asTeam);
	void doTeamFaceNamed(const AsciiString &, const AsciiString &);
	void doTeamFaceWaypoint(const AsciiString &, const AsciiString &);
};

void ScriptActions::doTeamFollowWaypoints(
	const AsciiString &teamName, const AsciiString &waypointPathLabel,
	Bool inFormation, Bool asTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;

	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D pos;
	pos.x = pos.y = pos.z = 0;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z;
		count++;
	}

	if (count == 0)
		return;

	pos.x /= count;
	pos.y /= count;
	pos.z /= count;

	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(
		&pos, waypointPathLabel);
	if (!way)
		return;

	if (asTeam)
		theGroup->groupFollowWaypointPathAsTeam(way, CMD_FROM_SCRIPT);
	else if (inFormation)
		theGroup->groupFollowWaypointPathAsTeamClearFormation(
			way, CMD_FROM_SCRIPT);
	else
		theGroup->groupFollowWaypointPath(way, CMD_FROM_SCRIPT);
}

void ScriptActions::doTeamFollowWaypointsExact(
	const AsciiString &teamName, const AsciiString &waypointPathLabel,
	Bool asTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;

	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D pos;
	pos.x = pos.y = pos.z = 0;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z;
		count++;
	}

	if (count == 0)
		return;

	pos.x /= count;
	pos.y /= count;
	pos.z /= count;

	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(
		&pos, waypointPathLabel);
	if (!way)
		return;

	if (asTeam)
		theGroup->groupFollowWaypointPathAsTeamExact(way, CMD_FROM_SCRIPT);
	else
		theGroup->groupFollowWaypointPathExact(way, CMD_FROM_SCRIPT);
}

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
