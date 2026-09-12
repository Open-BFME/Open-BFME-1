// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink

// The Team questions answered by walking the member list and looking at each
// member itself, rather than at where it stands relative to a trigger area
// (those six are in TeamTriggerAreaTests.cpp):
//
//   0x000F2420  getEstimateTeamPosition  214B  average the surviving members
//   0x000F45A0  getTeamAsAIGroup         126B  add the eligible ones to a group
//   0x000F4B60  hasAnyObjects(filter)    136B  is any member accepted by a filter
//   0x000F4C10  hasAnyUnits              179B  is any member a live unit
//   0x000F4CF0  hasAnyObjects            237B  is any member a live object
//
// All five walk the list at Team+0x0C through the same Object DLINK
// pointer-to-member, and all five sat in files carrying their own copy of the
// iterator and of Team.
//
// What they really shared, and what no one file could show, is the object they
// look at. Each declared a private view naming only the fields its own body
// touched, and the four views are four disjoint pictures of one Object:
//
//   +0x38/+0x3C/+0x40  the position    (getEstimateTeamPosition)
//   +0x78              a lookup id     (getTeamAsAIGroup)
//   +0x90              a status byte   (all four)
//   +0x94              a status byte   (getTeamAsAIGroup)
//   +0x118             a status byte   (hasAnyObjects)
//   +0x344             the dead bit    (three of the four)
//
// The byte at +0x90 is the one worth pointing at. Three files called it the
// destroyed flag and tested bit 0; the fourth called it a status byte and
// tested bit 0x04. It is one byte holding several flags, and naming it for the
// single bit each body happened to read was three files generalising from
// their own use. It is now named for its offset, with the meaning of bit 0
// recorded beside it.
//
// KindOfType is the same story in miniature: two files declared an enum of
// that name holding only their own constants -- 0x19 and 0x93 in one, 0x6C in
// the other -- so the same enum existed twice with disjoint contents.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef float Real;

class ObjectFilter;
class Player;

// The predicate at ILT 0x0001DA34 is still carried under this existing
// address-derived facade.  The exact caller chain proves that its receiver is
// the ObjectFilter argument, but does not by itself prove the predicate's
// original source-level name.  Keep that uncertainty local instead of minting
// a speculative ObjectFilter method identity.
class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
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

enum KindOfType
{
	KINDOF_GETTEAM_SKIP = 0x6C,
	KINDOF_HASANYOBJECTS_SKIP_A = 0x19,
	KINDOF_HASANYOBJECTS_SKIP_B = 0x93
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

// The four views the four files carried, stated once. Reached by casting the
// Object pointer, which is what retail does; the offsets are the claim, the
// class is only somewhere to write them.
class BfmeObjectStatusView
{
public:
	unsigned char m_head[0x38];
	Real m_x;							// +0x38
	Real m_y;							// +0x3C
	Real m_z;							// +0x40
	unsigned char m_mid44[0x78 - 0x44];
	int m_lookupId;							// +0x78
	unsigned char m_mid7C[0x90 - 0x7C];
	unsigned char m_status90;					// +0x90, bit 0 = destroyed
	unsigned char m_pad91[3];
	unsigned char m_status94;					// +0x94
	unsigned char m_mid95[0x118 - 0x95];
	unsigned char m_status118;					// +0x118
	unsigned char m_tail[0x344 - 0x119];
	unsigned char m_dead;						// +0x344, bit 0
};

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindof;						// +0xC8
	unsigned int m_shadowOffsetY;						// +0xCC
	unsigned int m_kindOf2;						// +0xD0
	unsigned int m_kindOf3;						// +0xD4
	unsigned int m_kindOf4;						// +0xD8
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

extern float g_bfmeDefaultBU;					// retail VA 0x01075334 = 1.0f

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *out) const;
	void getTeamAsAIGroup(AIGroup *pAIGroup);
	Bool hasAnyUnits() const;
	Bool hasAnyObjects(const ObjectFilter *filter, Bool bfmeFlag) const;
	Bool hasAnyObjects(Bool bfmeFlag) const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

static Overridable *bfmeFinalTemplate(Object *obj)
{
	Overridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (Overridable *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

// ?getEstimateTeamPosition@Team@@QBEPAUCoord3D@@PAU2@@Z
Coord3D *Team::getEstimateTeamPosition(Coord3D *out) const
{
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	int count = 0;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
		if ((obj->m_dead & 1) != 0)
			continue;
		if ((obj->m_status90 & 1) != 0)
			continue;

		++count;
		pos.x += obj->m_x;
		pos.y += obj->m_y;
		pos.z += obj->m_z;
	}

	if (count > 0)
	{
		Real recip = g_bfmeDefaultBU / (Real)count;
		pos.x *= recip;
		pos.y *= recip;
		pos.z *= recip;
	}

	out->x = pos.x;
	out->y = pos.y;
	out->z = pos.z;
	return out;
}

// ?getTeamAsAIGroup@Team@@QAEXPAVAIGroup@@@Z
void Team::getTeamAsAIGroup(AIGroup *pAIGroup)
{
	if (pAIGroup == 0)
		return;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
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

// ?hasAnyUnits@Team@@QBE_NXZ
Bool Team::hasAnyUnits() const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
		if ((obj->m_dead & 1) != 0)
			continue;
		if ((obj->m_status90 & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
		if ((tmpl->m_kindof & (1u << 7)) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
		if ((tmpl->m_kindof & 0x2000000) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
		if ((tmpl->m_kindOf4 & 0x80000) != 0)
			continue;

		return true;
	}
	return false;
}

// ?hasAnyObjects@Team@@QBE_NPBVObjectFilter@@_N@Z
// The exact TeamPrototype caller at 0x000F70C0 forwards ObjectFilter const *
// and Bool here through ILT 0x0003CCD1.  The body uses the first as the receiver
// for the existing filter predicate and the second as the same BFME-only
// dead/building gate used by the unfiltered sibling below.
Bool Team::hasAnyObjects(const ObjectFilter *filter, Bool bfmeFlag) const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
		if (bfmeFlag)
		{
			ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
			if ((tmpl->m_kindof & (1u << 7)) != 0 && (obj->m_status118 & 0x0C) != 0)
				continue;
		}

		if (((Rva2225E0Filter *)filter)->accepts(iter.cur(), 0))
			return true;
	}
	return false;
}

// ?hasAnyObjects@Team@@QBE_N_N@Z
Bool Team::hasAnyObjects(Bool bfmeFlag) const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
		if ((obj->m_dead & 1) != 0)
			continue;
		if ((obj->m_status90 & 1) != 0)
			continue;

		if (bfmeFlag)
		{
			ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
			if ((tmpl->m_kindof & (1u << 7)) != 0 && (obj->m_status118 & 0x0C) != 0)
				continue;
		}

		{
			ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
			if ((tmpl->m_kindof & 0x2000000) != 0)
				continue;
		}

		{
			ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
			if ((tmpl->m_kindOf2 & 0x1000000) != 0)
				continue;
		}

		if (((Thing *)obj)->isKindOf(KINDOF_HASANYOBJECTS_SKIP_A))
			continue;
		if (!((Thing *)obj)->isKindOf(KINDOF_HASANYOBJECTS_SKIP_B))
			return true;
	}
	return false;
}
