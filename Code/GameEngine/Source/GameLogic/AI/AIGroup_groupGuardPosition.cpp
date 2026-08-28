// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AIGroup::groupGuardPosition, retail 0x00156840, 77 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it from
// the ILT guardSupplyCenter calls with the adjusted warehouse position.
//
// A null position drops out at once. Otherwise every member of the list at +4
// is asked for its AI at +0x204 and, when there is one, the command interface
// at +0x20 of that AI is told to guard the position.
//
// The enums are nested in AIGroup here and global on the callee -- the two
// mangled names spell them that way -- so the arguments are cast across.
//
// this is spilled to the frame and reloaded after every call, and the end of
// the list is re-read from it each trip, because the guard order can change the
// membership underneath the walk.

struct Coord3D;

enum GuardMode { BFME_GUARD_MODE_NORMAL };
enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, ::GuardMode mode,
			::CommandSourceType cmdSource);			// ILT 0x0000A033
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
	enum GuardMode { BFME_AIGROUP_GUARD_MODE };
	enum CommandSourceType { BFME_AIGROUP_COMMAND_SOURCE };

	void groupGuardPosition(const Coord3D *pos, GuardMode mode,
			CommandSourceType cmdSource);

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;			// +0x04
};

// ?groupGuardPosition@AIGroup@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z
void AIGroup::groupGuardPosition(const Coord3D *pos, GuardMode mode,
		CommandSourceType cmdSource)
{
	if (!pos)
		return;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

		if (ai)
			ai->m_bfmeCommands.aiGuardPosition(pos, (::GuardMode)mode,
					(::CommandSourceType)cmdSource);
	}
}
