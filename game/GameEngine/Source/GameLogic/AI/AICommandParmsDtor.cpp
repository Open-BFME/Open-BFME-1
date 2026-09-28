// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// AICommandParms::~AICommandParms, retail RVA 0x000D7330 (65 bytes).
//
// Identity: the matched DeployStyleAIUpdate::setMyState (0x002B5800) calls
// this body through ILT 0x00017C2E with ECX pointing at its whole local
// AICommandParms, right where Zero Hour's setMyState lets the local die.  The
// body frees only the +0x20 vector (element width 12 = Coord3D, which the
// divide-by-12 magic multiply names), and every other member is trivially
// destructible, so it is the class's implicit destructor.  The layout is the
// one the matched AICommandParmsStorage::store/reconstitute bodies witness.
#include <vector>
#include "../command_source_type.h"

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum AICommandType
{
	AICMD_NO_COMMAND = -1,
	AICMD_MOVE_TO_POSITION = 0x00
};

struct DamageInfo
{
	char m_bfme_body[0x5C];
};

struct AICommandParms
{
public:
	AICommandParms( AICommandType cmd, CommandSourceType commandSource );
	~AICommandParms();

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	const Team *m_team;
	_STL::vector<Coord3D> m_coords;
	const Waypoint *m_waypoint;
	const PolygonTrigger *m_polygon;
	int m_intValue;
	DamageInfo m_damage;
	const CommandButton *m_commandButton;
	Path *m_path;
};

// ??1AICommandParms@@QAE@XZ
AICommandParms::~AICommandParms()
{
}
