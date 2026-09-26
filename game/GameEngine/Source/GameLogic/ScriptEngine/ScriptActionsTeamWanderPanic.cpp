// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Iinputs/reference/shims/stringinline
// Retail identity evidence names these bodies as TEAM_WANDER at 0x00301ED0 and
// TEAM_PANIC at 0x00302090 in the ScriptEngine action table. Both bodies walk
// the team member list and differ in their locomotor value and AI command.

#include "StringInline.h"

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Waypoint;
class AIUpdateInterface;
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
	unsigned char m_tail[0x194];
	AIUpdateInterface *getAIUpdateInterface(void) const
	{
		return *(AIUpdateInterface **)(
			reinterpret_cast<const unsigned char *>(this) + 0x204);
	}
};

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	Object *m_unmodelled0;
	Object *m_unmodelled1;
	Object *m_unmodelled2;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

#define BFME_SCRIPT_ENGINE_SLOT(index) virtual void _se_##index() = 0;

class ScriptEngine
{
public:
	BFME_SCRIPT_ENGINE_SLOT(0)
	BFME_SCRIPT_ENGINE_SLOT(1)
	BFME_SCRIPT_ENGINE_SLOT(2)
	BFME_SCRIPT_ENGINE_SLOT(3)
	BFME_SCRIPT_ENGINE_SLOT(4)
	BFME_SCRIPT_ENGINE_SLOT(5)
	BFME_SCRIPT_ENGINE_SLOT(6)
	BFME_SCRIPT_ENGINE_SLOT(7)
	BFME_SCRIPT_ENGINE_SLOT(8)
	BFME_SCRIPT_ENGINE_SLOT(9)
	BFME_SCRIPT_ENGINE_SLOT(10)
	BFME_SCRIPT_ENGINE_SLOT(11)
	BFME_SCRIPT_ENGINE_SLOT(12)
	BFME_SCRIPT_ENGINE_SLOT(13)
	BFME_SCRIPT_ENGINE_SLOT(14)
	BFME_SCRIPT_ENGINE_SLOT(15)
	BFME_SCRIPT_ENGINE_SLOT(16)
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
};

#undef BFME_SCRIPT_ENGINE_SLOT

#define BFME_TERRAIN_SLOT(index) virtual void _terrain_##index() = 0;

class TerrainLogic
{
public:
	BFME_TERRAIN_SLOT(0)
	BFME_TERRAIN_SLOT(1)
	BFME_TERRAIN_SLOT(2)
	BFME_TERRAIN_SLOT(3)
	BFME_TERRAIN_SLOT(4)
	BFME_TERRAIN_SLOT(5)
	BFME_TERRAIN_SLOT(6)
	BFME_TERRAIN_SLOT(7)
	BFME_TERRAIN_SLOT(8)
	BFME_TERRAIN_SLOT(9)
	BFME_TERRAIN_SLOT(10)
	BFME_TERRAIN_SLOT(11)
	BFME_TERRAIN_SLOT(12)
	BFME_TERRAIN_SLOT(13)
	BFME_TERRAIN_SLOT(14)
	BFME_TERRAIN_SLOT(15)
	BFME_TERRAIN_SLOT(16)
	BFME_TERRAIN_SLOT(17)
	BFME_TERRAIN_SLOT(18)
	BFME_TERRAIN_SLOT(19)
	BFME_TERRAIN_SLOT(20)
	BFME_TERRAIN_SLOT(21)
	BFME_TERRAIN_SLOT(22)
	BFME_TERRAIN_SLOT(23)
	BFME_TERRAIN_SLOT(24)
	BFME_TERRAIN_SLOT(25)
	BFME_TERRAIN_SLOT(26)
	BFME_TERRAIN_SLOT(27)
	BFME_TERRAIN_SLOT(28)
	BFME_TERRAIN_SLOT(29)
	BFME_TERRAIN_SLOT(30)
	BFME_TERRAIN_SLOT(31)
	BFME_TERRAIN_SLOT(32)
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *,
		AsciiString) = 0;
};

#undef BFME_TERRAIN_SLOT

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
	void aiWander(const Waypoint *, CommandSourceType);
	void aiPanic(const Waypoint *, CommandSourceType);
};

#define BFME_AI_SLOT(index) virtual void _ai_##index() = 0;

class AIUpdateInterface
{
public:
	BFME_AI_SLOT(0)
	BFME_AI_SLOT(1)
	BFME_AI_SLOT(2)
	BFME_AI_SLOT(3)
	BFME_AI_SLOT(4)
	BFME_AI_SLOT(5)
	BFME_AI_SLOT(6)
	BFME_AI_SLOT(7)
	BFME_AI_SLOT(8)
	BFME_AI_SLOT(9)
	BFME_AI_SLOT(10)
	BFME_AI_SLOT(11)
	BFME_AI_SLOT(12)
	BFME_AI_SLOT(13)
	BFME_AI_SLOT(14)
	BFME_AI_SLOT(15)
	BFME_AI_SLOT(16)
	BFME_AI_SLOT(17)
	BFME_AI_SLOT(18)
	BFME_AI_SLOT(19)
	BFME_AI_SLOT(20)
	BFME_AI_SLOT(21)
	BFME_AI_SLOT(22)
	BFME_AI_SLOT(23)
	BFME_AI_SLOT(24)
	BFME_AI_SLOT(25)
	BFME_AI_SLOT(26)
	BFME_AI_SLOT(27)
	BFME_AI_SLOT(28)
	BFME_AI_SLOT(29)
	BFME_AI_SLOT(30)
	BFME_AI_SLOT(31)
	BFME_AI_SLOT(32)
	BFME_AI_SLOT(33)
	BFME_AI_SLOT(34)
	BFME_AI_SLOT(35)
	BFME_AI_SLOT(36)
	BFME_AI_SLOT(37)
	BFME_AI_SLOT(38)
	BFME_AI_SLOT(39)
	BFME_AI_SLOT(40)
	BFME_AI_SLOT(41)
	BFME_AI_SLOT(42)
	BFME_AI_SLOT(43)
	BFME_AI_SLOT(44)
	BFME_AI_SLOT(45)
	BFME_AI_SLOT(46)
	BFME_AI_SLOT(47)
	BFME_AI_SLOT(48)
	BFME_AI_SLOT(49)
	BFME_AI_SLOT(50)
	BFME_AI_SLOT(51)
	BFME_AI_SLOT(52)
	BFME_AI_SLOT(53)
	BFME_AI_SLOT(54)
	BFME_AI_SLOT(55)
	BFME_AI_SLOT(56)
	BFME_AI_SLOT(57)
	BFME_AI_SLOT(58)
	BFME_AI_SLOT(59)
	BFME_AI_SLOT(60)
	BFME_AI_SLOT(61)
	BFME_AI_SLOT(62)
	BFME_AI_SLOT(63)
	BFME_AI_SLOT(64)
	BFME_AI_SLOT(65)
	BFME_AI_SLOT(66)
	BFME_AI_SLOT(67)
	BFME_AI_SLOT(68)
	BFME_AI_SLOT(69)
	BFME_AI_SLOT(70)
	BFME_AI_SLOT(71)
	BFME_AI_SLOT(72)
	BFME_AI_SLOT(73)
	BFME_AI_SLOT(74)
	BFME_AI_SLOT(75)
	BFME_AI_SLOT(76)
	BFME_AI_SLOT(77)
	BFME_AI_SLOT(78)
	BFME_AI_SLOT(79)
	BFME_AI_SLOT(80)
	BFME_AI_SLOT(81)
	BFME_AI_SLOT(82)
	BFME_AI_SLOT(83)
	BFME_AI_SLOT(84)
	BFME_AI_SLOT(85)
	BFME_AI_SLOT(86)
	BFME_AI_SLOT(87)
	BFME_AI_SLOT(88)
	BFME_AI_SLOT(89)
	BFME_AI_SLOT(90)
	BFME_AI_SLOT(91)
	BFME_AI_SLOT(92)
	BFME_AI_SLOT(93)
	BFME_AI_SLOT(94)
	BFME_AI_SLOT(95)
	BFME_AI_SLOT(96)
	BFME_AI_SLOT(97)
	BFME_AI_SLOT(98)
	BFME_AI_SLOT(99)
	BFME_AI_SLOT(100)
	BFME_AI_SLOT(101)
	BFME_AI_SLOT(102)
	BFME_AI_SLOT(103)
	BFME_AI_SLOT(104)
	BFME_AI_SLOT(105)
	BFME_AI_SLOT(106)
	BFME_AI_SLOT(107)
	BFME_AI_SLOT(108)
	BFME_AI_SLOT(109)
	BFME_AI_SLOT(110)
	BFME_AI_SLOT(111)
	BFME_AI_SLOT(112)
	BFME_AI_SLOT(113)
	BFME_AI_SLOT(114)
	BFME_AI_SLOT(115)
	BFME_AI_SLOT(116)
	BFME_AI_SLOT(117)
	BFME_AI_SLOT(118)
	BFME_AI_SLOT(119)
	BFME_AI_SLOT(120)
	BFME_AI_SLOT(121)
	BFME_AI_SLOT(122)
	BFME_AI_SLOT(123)
	BFME_AI_SLOT(124)
	BFME_AI_SLOT(125)
	BFME_AI_SLOT(126)
	virtual Bool chooseLocomotorSet(int);

private:
	unsigned char m_pad[0x1c];

public:
	AICommandInterface m_command;
};

#undef BFME_AI_SLOT

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;

class ScriptActions
{
protected:
	void doTeamWander(const AsciiString &, const AsciiString &);
	void doTeamPanic(const AsciiString &, const AsciiString &);
};

void ScriptActions::doTeamWander(const AsciiString &teamName,
	const AsciiString &waypointPathLabel)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai)
			continue;

		Coord3D pos;
		pos.x = obj->m_position.x;
		pos.y = obj->m_position.y;
		pos.z = obj->m_position.z;
		Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(
			&pos, waypointPathLabel);
		if (!way)
			return;

		ai->chooseLocomotorSet(3);
		ai->m_command.aiWander(way, CMD_FROM_SCRIPT);
	}
}

void ScriptActions::doTeamPanic(const AsciiString &teamName,
	const AsciiString &waypointPathLabel)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai)
			continue;

		Coord3D pos;
		pos.x = obj->m_position.x;
		pos.y = obj->m_position.y;
		pos.z = obj->m_position.z;
		Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(
			&pos, waypointPathLabel);
		if (!way)
			return;

		ai->chooseLocomotorSet(4);
		ai->m_command.aiPanic(way, CMD_FROM_SCRIPT);
	}
}
