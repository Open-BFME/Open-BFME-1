// ?setControllingPlayer@Team@@QAEXPAVPlayer@@@Z
// partial score=0.97 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: Team::setControllingPlayer, retail 0x000F44C0.



typedef bool Bool;
typedef unsigned int UnsignedInt;

class TeamPrototype;

class Player
{
public:
	void removeTeamFromList(TeamPrototype *team);
	void addTeamToList(TeamPrototype *team);
};

class TeamPrototype
{
public:
	unsigned char m_unmodelled_00[0x08];
	Player *m_owningPlayer;
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xcc];
	UnsignedInt m_kindOf;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && value->m_nextOverride)
			value = (const T *)value->m_nextOverride->getFinalOverride();
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	class BfmeTeamObject *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0() = 0;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeTeamObject : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	void refreshTeamMember();
	void bfmeTransferPowerInfluence(Player *oldPlayer, Player *newPlayer);
};

typedef BfmeTeamObject *(BfmeTeamObject::*BfmeGetNextTeamMemberFunc)() const;

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	BfmeDlinkIterator(ObjectType *cur, BfmeGetNextTeamMemberFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const
	{
		return m_cur == 0;
	}

	ObjectType *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

struct BfmeTeamFields
{
	unsigned char m_unmodelled_00[0x04];
	TeamPrototype *m_proto;
	unsigned char m_unmodelled_008[0x04];
	BfmeTeamObject *m_memberHead;
};

extern void j_00001140();
extern void j_00014b91();
extern void j_00039b5d();

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVBfmeTeamObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeTransferPowerInfluence@BfmeTeamObject@@QAEXPAVPlayer@@0@Z=?j_00014b91@@YAXXZ")
#pragma comment(linker, "/alternatename:?refreshTeamMember@BfmeTeamObject@@QAEXXZ=?j_00039b5d@@YAXXZ")

class Team
{
public:
	void setControllingPlayer(Player *newController);
};

// ?setControllingPlayer@Team@@QAEXPAVPlayer@@@Z
void Team::setControllingPlayer(Player *newController)
{
	BfmeTeamFields *self = (BfmeTeamFields *)this;
	TeamPrototype *proto = self->m_proto;
	if (proto)
	{
		Player *oldPlayer = proto->m_owningPlayer;
		if (newController)
		{
			if (oldPlayer)
				oldPlayer->removeTeamFromList(proto);
			proto->m_owningPlayer = newController;
			newController->addTeamToList(proto);
		}

		BfmeDlinkIterator<BfmeTeamObject> iter(self->m_memberHead,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
		while (!iter.done())
		{
			BfmeTeamObject *object = iter.cur();
			object->refreshTeamMember();
			const ThingTemplate *thing = object->m_template.operator->();
			if ((thing->m_kindOf & 0x1000) != 0
				&& oldPlayer != 0 && oldPlayer != newController)
			{
				object->bfmeTransferPowerInfluence(oldPlayer, newController);
			}
			iter.advance();
		}
	}
}
