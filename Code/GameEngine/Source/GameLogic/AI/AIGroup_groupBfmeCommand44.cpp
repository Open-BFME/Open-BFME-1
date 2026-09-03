// cl: /DNDEBUG /MD /EHsc

// Open-BFME: AIGroup wrapper for AICMD 0x44, retail 0x001569C0, 85 bytes.
// Same member walk as groupGuardPosition. Null-checks arg1 (the polygon).
// Callee is the matched 0x44 command builder at 0x001549A0.

struct Coord3D;
class PolygonTrigger;

enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };

class AICommandInterface
{
public:
	void aiBfmeCommand44(const PolygonTrigger *poly, int value,
			CommandSourceType cmdSource, const Coord3D *pos);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;
};

class BfmeGroupMember
{
public:
	char m_bfmeHead[0x204];
	BfmeGroupAI *m_bfmeAI;
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	BfmeGroupMember *m_bfmeValue;
};

class AIGroup
{
public:
	void groupBfmeCommand44(const PolygonTrigger *poly, int value,
			CommandSourceType cmdSource, const Coord3D *pos);

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;
};

void AIGroup::groupBfmeCommand44(const PolygonTrigger *poly, int value,
		CommandSourceType cmdSource, const Coord3D *pos)
{
	if (!poly)
		return;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

		if (ai)
			ai->m_bfmeCommands.aiBfmeCommand44(poly, value, cmdSource, pos);
	}
}
