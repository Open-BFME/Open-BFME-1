// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?store@AICommandParmsStorage@@QAEXABUAICommandParms@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// readable body of ?reconstitute@AICommandParmsStorage@@QBEXAAUAICommandParms@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// Open-BFME: the two halves of AICommandParmsStorage, retail
// ::store at 0x001805B0 (270 bytes) and ::reconstitute at 0x00180710 (205 bytes).
// They are inverses of one another over the same field list, so the storage
// layout, the live AICommandParms layout and the DamageInfo sub-layout are
// declared once here instead of once per body.
//
// BFME keeps the team prototype name and owner name in adjacent storage
// strings rather than a team pointer, and its DamageInfo input begins four
// bytes later in storage than in the live command parameters.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	static AsciiString TheEmptyString;

	void set(const AsciiString &source);
	void clear();

private:
	void *m_buffer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_pad00[0x74];
	Int m_id;

public:
	Int getID() const { return m_id; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
private:
	unsigned char m_pad00[0x10];

public:
	AsciiString m_name;
	AsciiString m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
private:
	unsigned char m_pad00[4];

public:
	TeamPrototype *m_proto;

	const AsciiString &getName() const
	{
		return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->m_name;
	}

	const AsciiString &getOwnerName() const
	{
		return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->m_owner;
	}
};

class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name, const AsciiString &owner);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheBfmeTeamFactory (*(TeamFactory **)0x012ED810)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput
{
public:
	DamageInfoInput &operator=(const DamageInfoInput &other);

private:
	char m_body[0x4c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoOutput
{
public:
	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	char m_unreconstructed00[4];
	DamageInfoInput m_in;
	DamageInfoOutput m_out;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
public:
	Int m_cmd;
	Int m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	Team *m_team;
	_STL::vector<Coord3D> m_coords;
	Waypoint *m_waypoint;
	PolygonTrigger *m_polygon;
	Int m_intValue;
	DamageInfo m_damage;
	CommandButton *m_commandButton;
	Path *m_path;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParmsStorage
{
private:
	Int m_cmd;
	Int m_cmdSource;
	Coord3D m_pos;
	Int m_obj;
	Int m_otherObj;
	AsciiString m_teamName;
	AsciiString m_teamOwner;
	_STL::vector<Coord3D> m_coords;
	Waypoint *m_waypoint;
	PolygonTrigger *m_polygon;
	Int m_intValue;
	DamageInfo m_damage;
	CommandButton *m_commandButton;
	Path *m_path;

public:
	void store(const AICommandParms &parms);
	void reconstitute(AICommandParms &parms) const;
};

// ?store@AICommandParmsStorage@@QAEXABUAICommandParms@@@Z
void AICommandParmsStorage::store(const AICommandParms &parms)
{
	m_cmd = parms.m_cmd;
	m_cmdSource = parms.m_cmdSource;
	m_pos = parms.m_pos;
	m_obj = parms.m_obj ? parms.m_obj->getID() : 0;
	m_otherObj = parms.m_otherObj ? parms.m_otherObj->getID() : 0;

	if (parms.m_team)
	{
		m_teamName.set(parms.m_team->getName());
		m_teamOwner.set(parms.m_team->getOwnerName());
	}
	else
	{
		m_teamName.clear();
		m_teamOwner.clear();
	}

	const DamageInfoInput *damageInput = &parms.m_damage.m_in;
	register const _STL::vector<Coord3D> *coords = &parms.m_coords;
	m_coords = *coords;
	m_waypoint = parms.m_waypoint;
	m_polygon = parms.m_polygon;
	m_intValue = parms.m_intValue;
	m_damage.m_in = *damageInput;
	m_damage.m_out.m_actualDamageDealt = parms.m_damage.m_out.m_actualDamageDealt;
	m_damage.m_out.m_actualDamageClipped = parms.m_damage.m_out.m_actualDamageClipped;
	m_damage.m_out.m_noEffect = parms.m_damage.m_out.m_noEffect;
	m_commandButton = parms.m_commandButton;
	m_path = parms.m_path;
}

// ?reconstitute@AICommandParmsStorage@@QBEXAAUAICommandParms@@@Z
void AICommandParmsStorage::reconstitute(AICommandParms &parms) const
{
	parms.m_cmd = m_cmd;
	parms.m_cmdSource = m_cmdSource;
	parms.m_pos = m_pos;
	parms.m_obj = TheBfmeGameLogic->findObjectByID(m_obj);
	parms.m_otherObj = TheBfmeGameLogic->findObjectByID(m_otherObj);
	parms.m_team = TheBfmeTeamFactory->findTeam(m_teamName, m_teamOwner);
	parms.m_coords = m_coords;
	parms.m_waypoint = m_waypoint;
	parms.m_polygon = m_polygon;
	parms.m_intValue = m_intValue;
	parms.m_damage.m_in = m_damage.m_in;
	parms.m_damage.m_out.m_actualDamageDealt = m_damage.m_out.m_actualDamageDealt;
	parms.m_damage.m_out.m_actualDamageClipped = m_damage.m_out.m_actualDamageClipped;
	parms.m_damage.m_out.m_noEffect = m_damage.m_out.m_noEffect;
	parms.m_commandButton = m_commandButton;
	parms.m_path = m_path;
}
