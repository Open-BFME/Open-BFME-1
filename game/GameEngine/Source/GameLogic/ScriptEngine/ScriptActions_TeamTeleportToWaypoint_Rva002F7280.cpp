// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: TEAM_TELEPORT_TO_WAYPOINT handler at retail RVA 0x002F7280, 152 bytes.
//
// executeAction (0x00303BF0) jump-table arm 502 calls this body through ILT
// 0x0002BA9E, and ScriptEngine::init registers m_actionTemplates[502] as
// TEAM_TELEPORT_TO_WAYPOINT (targets/game/reverse/identity_evidence/
// 002f7280-team-teleport-action.md). The arm passes the team parameter itself
// and the waypoint parameter's string. The original method spelling is
// unknown, so the name keeps the address.

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"

typedef bool Bool;

class BfmeAsciiStringArg : public AsciiString
{
public:
	BfmeAsciiStringArg(const AsciiString &that) : AsciiString(that) {}
	~BfmeAsciiStringArg();
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance(void)
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done(void) const
	{
		return m_cur == 0;
	}

	OBJCLASS *cur(void) const
	{
		return m_cur;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
// Only the TeamMemberList DLINK head at +0x0C is read here.
class Team
{
	void *m_unmodelled00;
	void *m_unmodelled04;
	void *m_unmodelled08;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;

};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
	char m_beforePosition[0xc];

public:
	char m_position[0xc];						// Coord3D at +0x0C
};

class TerrainLogic
{
public:
#define TERRAIN_SLOT(N) virtual void slot##N(void) = 0;
	TERRAIN_SLOT(00) TERRAIN_SLOT(01) TERRAIN_SLOT(02) TERRAIN_SLOT(03)
	TERRAIN_SLOT(04) TERRAIN_SLOT(05) TERRAIN_SLOT(06) TERRAIN_SLOT(07)
	TERRAIN_SLOT(08) TERRAIN_SLOT(09) TERRAIN_SLOT(10) TERRAIN_SLOT(11)
	TERRAIN_SLOT(12) TERRAIN_SLOT(13) TERRAIN_SLOT(14) TERRAIN_SLOT(15)
	TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18) TERRAIN_SLOT(19)
	TERRAIN_SLOT(20) TERRAIN_SLOT(21) TERRAIN_SLOT(22) TERRAIN_SLOT(23)
	TERRAIN_SLOT(24) TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27)
	TERRAIN_SLOT(28) TERRAIN_SLOT(29) TERRAIN_SLOT(30)
#undef TERRAIN_SLOT
	virtual Waypoint *getWaypointByName(BfmeAsciiStringArg name) = 0;	// +0x7C
};

extern TerrainLogic *TheTerrainLogic;

class BfmePosTP;

class BfmeHostTP
{
public:
	void bfmeSetPositionTP(const BfmePosTP *position, Bool unknown);	// ILT 0x0001621B
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
	char m_beforeString[0x10];

public:
	AsciiString m_string;						// +0x10
};

class ScriptActions
{
protected:
	void Rva002F7280(Parameter *teamParameter, const AsciiString &waypointName);
};

// ?Rva002F7280@ScriptActions@@IAEXPAVParameter@@ABVAsciiString@@@Z
void ScriptActions::Rva002F7280(Parameter *teamParameter, const AsciiString &waypointName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamParameter->m_string, false);
	if (!theTeam)
		return;

	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (!way)
		return;

	const BfmePosTP *position = (const BfmePosTP *)way->m_position;
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (!obj)
			continue;
		((BfmeHostTP *)obj)->bfmeSetPositionTP(position, false);
	}
}
