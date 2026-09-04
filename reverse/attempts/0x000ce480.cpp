// ?onUpgradeCompleted@Player@@QAEXPBVUpgradeTemplate@@@Z
// partial score=0.89 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Player::onUpgradeCompleted, retail 0x000CE480, 169 bytes (reloc_names 166
// omitted the ret 4).
//
// Reloc-named from the matched addUpgrade completion call. Player+0x288 is the
// team-prototype circular-list header pointer (same walk as hasAnyObjects).
// Each prototype's instance head is at +0x274 and advances through
// Team::_bfme_nextInInstanceList (ILT 0x00022A70). Members sit at Team+0x0C
// and step through Object's virtually-inherited DLINK PMF
// {pfn=0x00401140, delta=-100, vbindex=0}. Meat is updateUpgradeModules
// (ILT 0x00027FCF). The UpgradeTemplate argument is unused; it still
// produces retail's ret 4.
//
// Best compile: 158B, correct PMF vbptr+0x68 / delta -100 dispatch and both
// callees. Remaining wall is the Team DLINK esi-fold: /O2 LICMs the constant
// PMF to `mov edi, pfn` before `team->m_head`, keeps team in eax, allocates
// sub esp,0x0C not 0x10, and drops the 0x10-aligned `mov edi,edi` /
// `lea ecx,[ecx]` nops. /Og- sinks the PMF after the head load (198B).
// /Oy- emits the 3-byte nop and edx/eax dispatch but introduces a frame
// pointer. Source rewrites and the flag matrix do not flip the esi/eax
// team-cursor swap.

#include "ObjectDlinkPmf.h"

class UpgradeTemplate;

class ObjectUpgradeView
{
public:
	void updateUpgradeModules();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Team *_bfme_nextInInstanceList();				// ILT 0x00022A70

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C
};

class TeamPrototype
{
public:
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;					// +0x274
};

class BfmeTeamListNode
{
public:
	BfmeTeamListNode *m_next;
	BfmeTeamListNode *m_prev;
	TeamPrototype *m_proto;
};

class Player
{
public:
	void onUpgradeCompleted(const UpgradeTemplate *upgradeTemplate);

private:
	unsigned char m_head[0x288];
	BfmeTeamListNode *m_playerTeams;				// +0x288
};

// ?onUpgradeCompleted@Player@@QAEXPBVUpgradeTemplate@@@Z
void Player::onUpgradeCompleted(const UpgradeTemplate *)
{
	BfmeTeamListNode *head = m_playerTeams;
	for (BfmeTeamListNode *node = head->m_next; node != m_playerTeams; node = node->m_next)
	{
		for (Team *team = node->m_proto->m_teamInstanceList; team; team = team->_bfme_nextInInstanceList())
		{
			Object *cur = team->m_head;
			BfmeGetNextTeamMemberFunc getNext = Object::dlink_next_TeamMemberList;
			for (; cur != 0; cur = (cur->*getNext)())
				((ObjectUpgradeView *)cur)->updateUpgradeModules();
		}
	}
}
