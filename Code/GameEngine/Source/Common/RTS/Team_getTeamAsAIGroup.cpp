// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::getTeamAsAIGroup, retail 0x000F45A0, 126 bytes.
//
// Named by five byte-true callers including AIPlayer::guardSupplyCenter.
// Same Object DLINK PMF as Team::hasAnyObjects. ZH adds every member; BFME
// skips Object+0x94 bit 0x20 and +0x90 bit 0x04, then if +0x78 is a live
// GameLogic id whose object is kind 0x6C.

#include "ObjectDlinkPmf.h"

typedef bool Bool;

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

enum KindOfType { KINDOF_GETTEAM_SKIP = 0x6C };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

class AIGroup
{
public:
	void add(Object *obj);
};

class BfmeObjectTeamView
{
public:
	unsigned char m_head[0x78];
	int m_lookupId;						// +0x78
	unsigned char m_mid[0x90 - 0x7C];
	unsigned char m_status90;			// +0x90
	unsigned char m_pad91[3];
	unsigned char m_status94;			// +0x94
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *pAIGroup);

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// ?getTeamAsAIGroup@Team@@QAEXPAVAIGroup@@@Z
void Team::getTeamAsAIGroup(AIGroup *pAIGroup)
{
	if (pAIGroup == 0)
		return;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectTeamView *obj = (BfmeObjectTeamView *)iter.cur();
		if ((obj->m_status94 & 0x20) != 0)
			continue;
		if ((obj->m_status90 & 0x04) != 0)
			continue;
		if (obj->m_lookupId != 0)
		{
			Object *found = TheGameLogic->findObjectByID(obj->m_lookupId);
			if (found != 0 && ((Thing *)found)->isKindOf(KINDOF_GETTEAM_SKIP))
				continue;
		}
		pAIGroup->add(iter.cur());
	}
}
