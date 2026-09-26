// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// GiantBirdAIUpdate, retail 0x002C2C10 (435 bytes), non-virtual, ret 0xC.
//
// OWNER. The only caller is GiantBirdAIUpdate::aiDoCommand at 0x002C2E30 --
// slot 0 of the AICommandInterface table 0x010C7E68 that the GiantBird ctor
// 0x002C2430 installs -- which calls this through ILT 0x0000FF33 on its own
// adjusted `this`. Its jump table sends AICMD_FOLLOW_WAYPOINT_PATH 0x06 and
// _EXACT 0x32 here with false, _AS_TEAM 0x07 and 0x33 with true, and passes
// parms->m_waypoint (+0x2C) and parms->m_cmdSource (+0x04); the command ids
// are the ones AICommandInterfaceFollowPathCommands.cpp already names. The
// method name itself is unproven, so it keeps the address.
//
// BODY. Dead or immobile objects are ignored. The current locomotor's +0x44
// is mirrored to +0x478, then the waypoint chain is walked along link 0 into
// a Coord3D vector. Byte +0x488 is set only when the chain closes back on its
// first waypoint; a chain that runs out of links leaves it clear. The state
// machine is cleared, pointed at the last point and handed the path, and the
// bird enters state 0x3F7 (0x3F8 as a team).
//
// SHAPE. Retail copies each location into a stack temporary and re-reads it
// from memory in push_back's placement copy; that only happens when Coord3D
// has a user-declared copy constructor, which BFME's own coord3d.h declares.
// That header cannot be included here: it spells Coord3D as a class, and the
// pinned vector and setGoalPosition names are spelled with the struct.

typedef bool Bool;
typedef int Int;
typedef float Real;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;

	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
};

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// BFME Waypoint: location at +0x0C, links at +0x20, link count at +0x4C
// (AIWaypointPathStates.cpp, getNextWaypoint 0x0016C480).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	Int getNumLinks() const { return m_numLinks; }
	const Waypoint *getLink(Int ndx) const
	{
		if (ndx < 0 || ndx >= 8)
			return 0;
		return m_links[ndx];
	}
	const Coord3D *getLocation() const { return &m_location; }

private:
	void *m_vptr;
	Int m_id;
	void *m_name;
	Coord3D m_location;
	unsigned char m_pad_018[8];
	const Waypoint *m_links[8];
	unsigned char m_pad_040[0xC];
	Int m_numLinks;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isMobile() const;
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	unsigned char m_pad_000[0x344];
	unsigned char m_privateStatus;
};

class Locomotor
{
public:
	unsigned char m_pad_000[0x44];
	Int m_dword44;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(Int id);

	void setGoalPosition(const Coord3D *position);
};

class BfmeSub30_7F0 : public StateMachine
{
public:
	void step2(void *arg);
};

class Rva002BC470StateAction
{
public:
	void finish(void *arg);
};

class GiantBirdAIUpdate
{
public:
	void followWaypointPathRva002C2C10(const Waypoint *way, Bool asTeam,
		CommandSourceType cmdSource);

	BfmeSub30_7F0 *getStateMachine() { return m_stateMachine; }

private:
	unsigned char m_pad_000[8];
	Object *m_object;
	unsigned char m_pad_00C[0x30 - 0x0C];
	BfmeSub30_7F0 *m_stateMachine;
	unsigned char m_pad_034[0x1CC - 0x34];
	Locomotor *m_curLocomotor;
	unsigned char m_pad_1D0[0x478 - 0x1D0];
	Int m_field478;
	unsigned char m_pad_47C[0x488 - 0x47C];
	unsigned char m_field488;
};

void GiantBirdAIUpdate::followWaypointPathRva002C2C10(const Waypoint *way,
	Bool asTeam, CommandSourceType cmdSource)
{
	if (m_object->isEffectivelyDead())
		return;
	if (!m_object->isMobile())
		return;

	if (m_curLocomotor)
		m_field478 = m_curLocomotor->m_dword44;
	m_field488 = 0;

	std::vector<Coord3D> path;
	if (way == 0)
		return;

	const Waypoint *cur = way;
	for (;;)
	{
		Coord3D pos = *cur->getLocation();
		path.push_back(pos);
		if (cur->getNumLinks() == 0)
			break;
		cur = cur->getLink(0);
		if (cur == way)
		{
			m_field488 = 1;
			break;
		}
	}

	getStateMachine()->slot14();
	if (path.size() != 0)
	{
		Coord3D goal = path[path.size() - 1];
		getStateMachine()->setGoalPosition(&goal);
	}
	getStateMachine()->step2(&path);
	// retail 0x0003F42C stores the argument at this+0x48
	reinterpret_cast<Rva002BC470StateAction *>(this)->finish((void *)cmdSource);
	getStateMachine()->setState(asTeam ? 0x3F8 : 0x3F7);
}
