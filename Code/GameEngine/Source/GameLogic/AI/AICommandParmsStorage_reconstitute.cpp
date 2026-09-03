// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AICommandParmsStorage::reconstitute, retail 0x00180710, 205 bytes.
//
// BFME stores both team-name keys in the saved command block.  The storage
// damage object starts four bytes later than the live command's object, while
// both use the retail DamageInfo input/output sub-layout.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

class AsciiString
{
	void *m_buffer;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name, const AsciiString &owner);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheBfmeTeamFactory (*(TeamFactory **)0x012ED810)

class DamageInfoInput
{
public:
	DamageInfoInput &operator=(const DamageInfoInput &other);

private:
	char m_body[0x4c];
};

class DamageInfoOutput
{
public:
	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

class DamageInfo
{
public:
	char m_unreconstructed00[4];
	DamageInfoInput m_in;
	DamageInfoOutput m_out;
};

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
	void reconstitute(AICommandParms &parms) const;
};

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
