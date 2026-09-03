// cl: /DNDEBUG /MD /EHsc

// Open-BFME: AIGroup::groupHunt, retail 0x00156270, 53 bytes.
//
// Member walk identical to groupGuardPosition: list at +4, object at node+8,
// AI at object+0x204, command interface at AI+0x20. Identity is the matched
// aiHunt callee (ILT 0x0001C882 -> 0x000D88D0).

enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiHunt(CommandSourceType cmdSource);
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
	void groupHunt(CommandSourceType cmdSource);

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;			// +0x04
};

// ?groupHunt@AIGroup@@QAEXW4CommandSourceType@@@Z
void AIGroup::groupHunt(CommandSourceType cmdSource)
{
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_bfmeAI;

		if (ai)
			ai->m_bfmeCommands.aiHunt(cmdSource);
	}
}
