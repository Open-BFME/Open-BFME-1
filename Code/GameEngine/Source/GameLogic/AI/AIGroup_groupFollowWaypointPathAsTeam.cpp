// cl: /DNDEBUG /MD /EHsc

// Open-BFME: AIGroup::groupFollowWaypointPathAsTeam, retail 0x00155A80, 85 bytes.
//
// Same member walk as groupHunt / groupGuardPosition. Identity is the matched
// aiFollowWaypointPathAsTeam callee (ILT 0x00003BF2 -> 0x00152F20). BFME adds a
// Bool gate (ILT 0x000104B0) and a group prep (ILT 0x0002E636 -> 0x0015AB50)
// before the walk.

class Waypoint;

enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiFollowWaypointPathAsTeam(const Waypoint *way, CommandSourceType cmdSource);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;			// +0x20
};

class BfmeGroupMember
{
public:
	char m_bfmeHead[0x204];
	BfmeGroupAI *m_bfmeAI;					// +0x204
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;				// +0x00
	BfmeListNodeBase *m_bfmePrev;				// +0x04
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	BfmeGroupMember *m_bfmeValue;				// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupFollowWaypointPathAsTeam(const Waypoint *way, CommandSourceType cmdSource);

	char isReady();								// ILT 0x000104B0
	void prepFollow(CommandSourceType cmdSource, int unused);	// ILT 0x0002E636

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;			// +0x04
};

// ?groupFollowWaypointPathAsTeam@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z
void AIGroup::groupFollowWaypointPathAsTeam(const Waypoint *way, CommandSourceType cmdSource)
{
	if (!isReady())
		return;

	prepFollow(cmdSource, 0);

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

		if (ai)
			ai->m_bfmeCommands.aiFollowWaypointPathAsTeam(way, cmdSource);
	}
}
