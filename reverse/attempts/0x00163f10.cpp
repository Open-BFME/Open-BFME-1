// ?isSupplySourceAttacked@AIPlayer@@QAE_NXZ
// partial score=0.94 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// readable body of ?isSupplySourceAttacked@AIPlayer@@QAE_NXZ: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
// Open-BFME: AIPlayer::isSupplySourceAttacked, retail 0x00163F10, 421 bytes.
//
// Named by the already-matched guardSupplyCenter call. Same Object DLINK PMF
// {pfn=0x00401140, delta=-100, vbindex=0} as Team::hasAnyUnits. Each KindOf
// test re-walks Thing+0x04 through Overridable::getFinalOverride (ILT
// 0x000022BB). Team instance list head is TeamPrototype+0x274, advanced
// through Team::_bfme_nextInInstanceList (ILT 0x00022A70). Player team-proto
// list header pointer is at Player+0x288. getFrame inlines to TheGameLogic+0x3c.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class BfmeObjectTemplateView
{
public:
	void *m_vptr;
	Overridable *m_template;					// Object+0x04
};

class BfmeObjectIdView
{
public:
	unsigned char m_head[0x74];
	ObjectID m_id;								// +0x74
};

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindOf0;						// +0xC8
	unsigned int m_kindOf1;						// +0xCC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	unsigned char m_head[0x58];
	unsigned char m_noEffect;					// +0x58
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual const DamageInfo *getLastDamageInfo() const;
	virtual UnsignedInt getLastDamageTimestamp() const;
};

class BfmeObjectBodyView
{
public:
	unsigned char m_head[0x200];
	BodyModuleInterface *m_body;				// +0x200
};

static Overridable *bfmeFinalTemplate(Object *obj)
{
	Overridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (Overridable *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Team *_bfme_nextInInstanceList();

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head)
		: m_cur(head)
	{
	}

	bool done() const
	{
		return m_cur == 0;
	}

	Team *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	UnsignedInt getAttackedFrame() const { return m_attackedFrame; }
	BfmeTeamListNode *getPlayerTeams() const { return m_playerTeams; }

private:
	unsigned char m_head[0x288];
	BfmeTeamListNode *m_playerTeams;			// +0x288
	unsigned char m_mid[0x2c0 - 0x28c];
	UnsignedInt m_attackedFrame;				// +0x2c0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_head[0x3c];
	UnsignedInt m_frame;						// +0x3c
};

extern GameLogic *TheGameLogic;					///< retail 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	Bool isSupplySourceAttacked();

private:
	void *m_vptr;
	unsigned char m_dlink[8];
	Player *m_player;							// +0x0C
	unsigned char m_mid[0x6c - 0x10];
	UnsignedInt m_supplySourceAttackCheckFrame;	// +0x6c
	ObjectID m_attackedSupplyCenter;			// +0x70
};

// ?isSupplySourceAttacked@AIPlayer@@QAE_NXZ
Bool AIPlayer::isSupplySourceAttacked()
{
	const UnsignedInt SCAN_RATE = 10;
	UnsignedInt curFrame = TheGameLogic->getFrame();
	if (curFrame == 0)
	{
		m_supplySourceAttackCheckFrame = curFrame + SCAN_RATE;
		return false;
	}
	m_attackedSupplyCenter = 0;
	if (curFrame < m_supplySourceAttackCheckFrame)
		return false;
	if (m_player->getAttackedFrame() + SCAN_RATE < curFrame)
		return false;
	m_supplySourceAttackCheckFrame = curFrame + SCAN_RATE;

	BfmeTeamListNode *head = m_player->getPlayerTeams();
	for (BfmeTeamListNode *it = head->m_next; it != m_player->getPlayerTeams(); it = it->m_next)
	{
		TeamPrototype *proto = it->m_proto;
		for (BfmeTeamInstanceIterator iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done(); objIter.advance())
			{
				Object *obj = objIter.cur();
				if (!obj)
					continue;
				ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(obj);
				if ((tmpl->m_kindOf1 & 4) == 0)
				{
					tmpl = (ThingTemplate *)bfmeFinalTemplate(obj);
					if ((tmpl->m_kindOf0 & 0x4000) == 0)
					{
						tmpl = (ThingTemplate *)bfmeFinalTemplate(obj);
						if ((tmpl->m_kindOf0 & 0x10000) == 0)
							continue;
					}
				}

				BodyModuleInterface *body = ((BfmeObjectBodyView *)obj)->m_body;
				if (body)
				{
					const DamageInfo *info = body->getLastDamageInfo();
					if (info)
					{
						if (info->m_noEffect)
							continue;
						if (body->getLastDamageTimestamp() + SCAN_RATE > curFrame)
						{
							m_attackedSupplyCenter = ((BfmeObjectIdView *)obj)->m_id;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
