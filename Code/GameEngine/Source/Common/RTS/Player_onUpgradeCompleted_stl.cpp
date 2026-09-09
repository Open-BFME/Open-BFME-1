// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Identity: matched Player::addUpgrade calls ILT 0x0002F856, reaching
// RVA 0x000CE480. BFME PlayerTeamList is at +0x288. The full body is
// 169 bytes through ret 4; the older 166-byte inventory omitted that return.

#include <list>

class TeamPrototype;

class Player
{
public:
	typedef std::list<TeamPrototype *> PlayerTeamList;
	void onUpgradeCompleted(const class UpgradeTemplate *upgradeTemplate);
};

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	void updateUpgradeModules(void);
	unsigned char m_tail[0x40];
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)(void) const;

class Team
{
public:
	Team *_bfme_nextInInstanceList();

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

class TeamPrototype
{
public:
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;
};

class BfmePlayerTeamFields
{
public:
	unsigned char m_unreconstructed_000[0x288];
	Player::PlayerTeamList m_playerTeamPrototypes;
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *cur) : m_cur(cur) {}

	bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
	int m_unmodelled;
};

class BfmeTeamMemberIterator
{
public:
	BfmeTeamMemberIterator(Object *cur, BfmeGetNextTeamMemberFunc getNext)
		: m_cur(cur), m_getNext(getNext) {}

	bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

private:
	Object *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

void Player::onUpgradeCompleted(const UpgradeTemplate *)
{
	BfmePlayerTeamFields *self = (BfmePlayerTeamFields *)this;
	for (PlayerTeamList::iterator it = self->m_playerTeamPrototypes.begin();
		it != self->m_playerTeamPrototypes.end(); ++it)
	{
		BfmeTeamInstanceIterator iter(
			((TeamPrototype *)*it)->m_teamInstanceList);
		for (; !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (team == 0)
				continue;

			BfmeTeamMemberIterator iterObj(
				team->m_head, BfmeObjectDlinkBase::dlink_next_TeamMemberList);
			for (; !iterObj.done(); iterObj.advance())
			{
				Object *obj = iterObj.cur();
				if (obj == 0)
					continue;
				obj->updateUpgradeModules();
			}
		}
	}
}
