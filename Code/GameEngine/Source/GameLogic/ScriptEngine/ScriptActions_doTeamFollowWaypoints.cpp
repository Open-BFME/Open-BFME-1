// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /Ireference/shims/stringinline
// Open-BFME: ScriptActions::doTeamFollowWaypoints, retail 0x002F3080, 347 bytes.
//
// This BFME action has separate switches for team movement and formation.
// The center walk and member layout are shared with the exact waypoint action.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
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

class Object;

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

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	const Coord3D *getPosition(void) const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}
};

class PositionObject : public BfmeObjectVtbl
{
public:
	unsigned char m_beforePosition[0x34];
	Coord3D m_position;
	const Coord3D *getPosition(void) const { return &m_position; }
};

class Waypoint
{
public:
	unsigned char m_beforePosition[0x0c];
	Coord3D m_position;
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class AIGroup
{
public:
	void groupFollowWaypointPathAsTeam(const Waypoint *way,
		CommandSourceType cmdSource);
	void groupFollowWaypointPathAsTeamClearFormation(const Waypoint *way,
		CommandSourceType cmdSource);
	void groupFollowWaypointPath(const Waypoint *way,
		CommandSourceType cmdSource);
};

class Team
{
private:
	unsigned char m_beforeMembers[0x0c];
	Object *m_head;

public:
	void getTeamAsAIGroup(AIGroup *group);

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class AI
{
public:
	AIGroup *createGroup();
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16();
	virtual Team *getTeamNamed(AsciiString name, Bool unused);
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos,
		AsciiString label);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamFollowWaypoints(const AsciiString &teamName,
		const AsciiString &waypointPathLabel, Bool inFormation, Bool asTeam);
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
