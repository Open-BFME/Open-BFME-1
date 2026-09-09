// ?getPlayerSuperweaponValue@AIPlayer@@SAHPAUCoord3D@@HM@Z
// partial score=0.98 date=2026-09-09
// Retail 0x00164130/502: BFME's three-argument superweapon target value.
// The player-team traversal, override lookup, kind flags, and retail calls
// identify this as the BFME overload distinct from the four-argument ZH body.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink

#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	Coord3D() {}
};

struct Coord2D
{
	Real x;
	Real y;
};

class Player;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	void *m_vtable;
	BfmeOverridable *m_nextOverride;
};

typedef BfmeOverridable Overridable;

class ThingTemplate : public BfmeOverridable
{
public:
	Int calcCostToBuild(const Player *player, Int playerIndex = -1) const;

	unsigned char m_pad[0xc0];
	unsigned int m_kindOf;
};

__forceinline Int calcCostForTemplate(const ThingTemplate *thingTemplate, const Player *player)
{
	return thingTemplate->calcCostToBuild(player);
}

class TemplateOverride
{
public:
	const ThingTemplate *operator->() const
	{
		const ThingTemplate *tmpl = *(const ThingTemplate **)((const char *)this);
		if (tmpl != 0)
		{
			if (tmpl->m_nextOverride != 0)
				tmpl = (const ThingTemplate *)tmpl->m_nextOverride->friend_getFinalOverride();
		}
		return tmpl;
	}

private:
	const Overridable *m_overridable;
};

class Object;

class BfmeObjectVirtualTail
{
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);

	__forceinline const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = *(const ThingTemplate **)((const char *)this + 4);
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride != 0)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->friend_getFinalOverride();
		return tmpl;
	}
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
	TemplateOverride m_template;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	Bool isKindOf(unsigned int kind) const
	{
		return (getTemplate()->m_kindOf & (1UL << kind)) != 0;
	}

	Bool isSignificantlyAboveTerrain() const;
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	unsigned char m_tail[0x40];
};

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS * (OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
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

	OBJCLASS *cur() const
	{
		return m_cur;
	}

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team;

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_cur(head), m_unused(0) {}
	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }
	void advance();

private:
	Team *m_cur;
	Int m_unused;
};

class TeamPrototype
{
public:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}

	unsigned char m_pad[0x274];
	Team *m_teamInstanceList;
};

class Team
{
public:
	Team *_bfme_nextInInstanceList();

	BfmeTeamInstanceIterator iterate_TeamInstanceList();

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

void BfmeTeamInstanceIterator::advance()
{
	if (m_cur)
		m_cur = m_cur->_bfme_nextInInstanceList();
}

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
	class PlayerTeamList
	{
	public:
		class const_iterator
		{
		public:
			const_iterator() {}
			const_iterator(BfmeTeamListNode *node) : m_node(node) {}
			TeamPrototype *operator*() const { return m_node->m_proto; }
			Bool operator!=(const const_iterator &that) const { return m_node != that.m_node; }
			const_iterator &operator++() { m_node = m_node->m_next; return *this; }

		private:
			BfmeTeamListNode *m_node;
		};

		const_iterator begin() const
		{
			return const_iterator(m_head->m_next);
		}

		const_iterator end() const
		{
			return const_iterator(m_head);
		}

	private:
		BfmeTeamListNode *m_head;
	};

	const PlayerTeamList *getPlayerTeams() const
	{
		return (const PlayerTeamList *)((const char *)this + 0x288);
	}
};

class PlayerList
{
public:
	Player *getNthPlayer(Int index);
};

extern PlayerList *ThePlayerList;
extern Real g_bfmeDefaultBU;

class AIPlayer
{
public:
	static Int getPlayerSuperweaponValue(Coord3D *center, Int playerNdx, Real radius);
};

Int AIPlayer::getPlayerSuperweaponValue(Coord3D *center, Int playerNdx, Real radius)
{
	if (radius < 4 * 10.0f)
		radius = 4 * 10.0f;
	Player::PlayerTeamList::const_iterator it;
	Real cash = 0;
	Real radSqr = radius * radius;

	Player *pPlayer = ThePlayerList->getNthPlayer(playerNdx);
	if (pPlayer == 0)
		return 0;
	for (it = pPlayer->getPlayerTeams()->begin();
		it != pPlayer->getPlayerTeams()->end();
		++it)
	{
		TeamPrototype *proto = *it;
		for (BfmeTeamInstanceIterator iter = proto->iterate_TeamInstanceList();
			!iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList();
				!members.done(); members.advance())
			{
				Object *pObj = members.cur();
				if (!pObj)
					continue;
				if ((pObj->getTemplate()->m_kindOf & 0x1000) != 0)
				{
					if (pObj->isSignificantlyAboveTerrain())
						continue;
				}
				Coord3D pos = *(pObj->getPosition());
				Real dx = center->x - pos.x;
				Real dy = center->y - pos.y;
				if (dx * dx + dy * dy < radSqr)
				{
					const ThingTemplate *templateForCost =
						*(const ThingTemplate **)((const char *)pObj + 4);
					Real dist = sqrt(dx * dx + dy * dy);
					Real factor = 1.0f - (dist / (2 * radius));
					const ThingTemplate *finalTemplateForCost;
					if (templateForCost != 0)
						goto haveTemplateForCost;
					finalTemplateForCost = 0;
					goto templateForCostDone;

				haveTemplateForCost:
					if (templateForCost->m_nextOverride != 0)
						finalTemplateForCost = (const ThingTemplate *)
							templateForCost->m_nextOverride->friend_getFinalOverride();
					else
						finalTemplateForCost = templateForCost;

				templateForCostDone:
					Real value = calcCostForTemplate(finalTemplateForCost, pPlayer);
					if ((pObj->getTemplate()->m_kindOf & 0x20000) != 0)
						value = value / 10;
					if (value > 3000)
						value = value / 10;
					cash += factor * value;
				}
			}
		}
	}
	return cash;
}
