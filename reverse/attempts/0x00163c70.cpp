// ?getPlayerStructureBounds@AIPlayer@@SAXPAURegion2D@@H@Z
// partial score=0.75 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/objectdlink
//
// AIPlayer::getPlayerStructureBounds, retail 0x00163C70, 537 bytes.
// Named by the matched guardSupplyCenter call (two-arg BFME form; ZH's
// conservative third argument is gone). Player team list at +0x288,
// TeamPrototype instances at +0x274, Team members at +0x0C. STRUCTURE
// is the sign bit of ThingTemplate+0xC8. Object DLINK PMF is {0x00401140, -100}.
//
// Probe 525 vs 537. Walk, callees, and the x87 min/max (pos.x in ST0,
// pos.y as integer bits, fcomp st(1) / fcom [edi]) are the retail shape.
// Wall: prologue xor ebx,ebx / sub esp,0x40 vs retail xor esi,esi /
// sub esp,0x44. That colors the whole-function zero as EBX so PMF adj
// spills, every later test is `cmp r,ebx` not `test r,r`, and `it` gets
// its own slot instead of the dead bounds arg. Int z / Object* pObj=0 /
// pointer-bits-as-float-zero did not steal ESI. Load y then x then the
// firstObject flag to match retail's hoist.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;	// ILT 0x000022BB

	void *m_vtable;
	Overridable *m_nextOverride;
};

class BfmeObjectTemplateView
{
public:
	void *m_vptr;
	Overridable *m_template;					// Object+0x04
};

class BfmeObjectPosView
{
public:
	unsigned char m_head[0x38];
	Coord3D m_position;							// +0x38

	const Coord3D *getPosition() const { return &m_position; }
};

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	signed char m_kindOf0;						// +0xC8, STRUCTURE = sign bit
};

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}
	Bool done() const { return m_cur == 0; }
	OBJCLASS* cur() const { return m_cur; }
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	Team *_bfme_nextInInstanceList();			// ILT 0x00022A70

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;								// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_cur(head) {}
	bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}
private:
	Team *m_cur;
};

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

class Player
{
public:
	BfmeTeamListNode *getPlayerTeams() const { return m_playerTeams; }
private:
	unsigned char m_head[0x288];
	BfmeTeamListNode *m_playerTeams;				// +0x288
};

class PlayerList
{
public:
	Player *getNthPlayer(Int ndx);
};

extern PlayerList *ThePlayerList;

class AIPlayer
{
public:
	static void getPlayerStructureBounds(Region2D *bounds, Int playerNdx);
};

static const Overridable *bfmeFinalTemplate(Object *obj)
{
	const Overridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

// ?getPlayerStructureBounds@AIPlayer@@SAXPAURegion2D@@H@Z
void AIPlayer::getPlayerStructureBounds(Region2D *bounds, Int playerNdx)
{
	Object *pObj = 0;
	Bool firstObject = true;
	Bool firstStructure = true;
	bounds->hi.x = bounds->lo.x = bounds->hi.y = bounds->lo.y = 0;
	Region2D objBounds;
	objBounds.hi.x = objBounds.lo.x = objBounds.hi.y = objBounds.lo.y = 0;

	Player *pPlayer = ThePlayerList->getNthPlayer(playerNdx);
	if (pPlayer == 0)
		return;

	BfmeTeamListNode *it = pPlayer->getPlayerTeams()->m_next;
	for (; it != pPlayer->getPlayerTeams(); it = it->m_next)
	{
		TeamPrototype *proto = it->m_proto;
		for (BfmeTeamInstanceIterator iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done(); objIter.advance())
			{
				pObj = objIter.cur();
				if (!pObj)
					continue;
				const ThingTemplate *tmpl = (const ThingTemplate *)bfmeFinalTemplate(pObj);
				signed char kind = tmpl->m_kindOf0;
				if (kind >= 0)
					continue;

				const BfmeObjectPosView *ov = (const BfmeObjectPosView *)pObj;
				Coord3D pos;
				*(Int *)&pos.y = *(const Int *)&ov->m_position.y;
				pos.x = ov->m_position.x;
				if (firstObject)
				{
					objBounds.hi.x = pos.x;
					objBounds.lo.x = pos.x;
					*(Int *)&objBounds.lo.y = *(const Int *)&pos.y;
					firstObject = false;
				}
				else
				{
					if (objBounds.lo.x > pos.x) objBounds.lo.x = pos.x;
					if (objBounds.lo.y > pos.y) objBounds.lo.y = pos.y;
					if (objBounds.hi.x < pos.x) objBounds.hi.x = pos.x;
					if (objBounds.hi.y < pos.y) objBounds.hi.y = pos.y;
				}
				if (firstStructure)
				{
					bounds->hi.x = pos.x;
					bounds->lo.x = pos.x;
					*(Int *)&bounds->lo.y = *(const Int *)&pos.y;
					firstStructure = false;
				}
				else
				{
					if (bounds->lo.x > pos.x) bounds->lo.x = pos.x;
					if (bounds->lo.y > pos.y) bounds->lo.y = pos.y;
					if (bounds->hi.x < pos.x) bounds->hi.x = pos.x;
					if (bounds->hi.y < pos.y) bounds->hi.y = pos.y;
				}
			}
		}
	}
	if (!firstStructure)
		*bounds = objBounds;
}
