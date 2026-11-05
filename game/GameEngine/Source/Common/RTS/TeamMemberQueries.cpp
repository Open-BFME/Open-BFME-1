// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink

// The Team questions answered by walking the member list and looking at each
// member itself, rather than at where it stands relative to a trigger area
// (those six are in TeamTriggerAreaTests.cpp):
//
//   0x000F2420  getEstimateTeamPosition  214B  average the surviving members
//   0x000F45A0  getTeamAsAIGroup         126B  add the eligible ones to a group
//   0x000F4B60  hasAnyObjects(filter)    136B  is any member accepted by a filter
//   0x000F4C10  hasAnyUnits              179B  is any member a live unit
//   0x000F4CF0  hasAnyObjects            237B  is any member a live object
//   0x000F4E20  rva000F4E20              214B  is an active team's every horde settled
//
// All six walk the list at Team+0x0C through the same Object DLINK
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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class HordeContainInterface
{
public:
	virtual int slot00() = 0; virtual int slot01() = 0; virtual int slot02() = 0; virtual int slot03() = 0;
	virtual int slot04() = 0; virtual int slot05() = 0; virtual int slot06() = 0; virtual int slot07() = 0;
	virtual int slot08() = 0; virtual int slot09() = 0; virtual int slot10() = 0; virtual int slot11() = 0;
	virtual int slot12() = 0; virtual int slot13() = 0; virtual int slot14() = 0; virtual int slot15() = 0;
	virtual int slot16() = 0; virtual int slot17() = 0; virtual int slot18() = 0; virtual int slot19() = 0;
	virtual int slot20() = 0; virtual int slot21() = 0; virtual int slot22() = 0; virtual int slot23() = 0;
	virtual int slot24() = 0; virtual int slot25() = 0; virtual int slot26() = 0; virtual int slot27() = 0;
	virtual int slot28() = 0; virtual int slot29() = 0; virtual int slot30() = 0; virtual int slot31() = 0;
	virtual int slot32() = 0; virtual int slot33() = 0; virtual int slot34() = 0; virtual int slot35() = 0;
	virtual int slot36() = 0; virtual int slot37() = 0; virtual Bool slot38() = 0; virtual Bool slot39() = 0;
	virtual int slot40() = 0; virtual int slot41() = 0; virtual int slot42() = 0; virtual int slot43() = 0;
	virtual int slot44() = 0; virtual int slot45() = 0; virtual int slot46() = 0; virtual int slot47() = 0;
	virtual int slot48() = 0; virtual int slot49() = 0; virtual int slot50() = 0; virtual int slot51() = 0;
	virtual int slot52() = 0; virtual int slot53() = 0; virtual int slot54() = 0; virtual int slot55() = 0;
	virtual int slot56() = 0; virtual int slot57() = 0; virtual int slot58() = 0; virtual int slot59() = 0;
	virtual int slot60() = 0; virtual int slot61() = 0; virtual int slot62() = 0; virtual int slot63() = 0;
	virtual int slot64() = 0; virtual int slot65() = 0; virtual int slot66() = 0; virtual int slot67() = 0;
	virtual int slot68() = 0; virtual int slot69() = 0; virtual int slot70() = 0; virtual int slot71() = 0;
	virtual int slot72() = 0; virtual int slot73() = 0; virtual int slot74() = 0; virtual int slot75() = 0;
	virtual int slot76() = 0; virtual int slot77() = 0; virtual int slot78() = 0; virtual int slot79() = 0;
	virtual int slot80() = 0; virtual int slot81() = 0; virtual int slot82() = 0; virtual int slot83() = 0;
	virtual int getHordeMemberCount(Bool countRiders) = 0;
};

class ContainModuleInterface
{
public:
	virtual int slot00() = 0; virtual int slot01() = 0; virtual int slot02() = 0; virtual int slot03() = 0;
	virtual int slot04() = 0; virtual int slot05() = 0; virtual int slot06() = 0; virtual int slot07() = 0;
	virtual int slot08() = 0; virtual int slot09() = 0; virtual int slot10() = 0; virtual int slot11() = 0;
	virtual int slot12() = 0; virtual int slot13() = 0; virtual int slot14() = 0; virtual int slot15() = 0;
	virtual int slot16() = 0; virtual int slot17() = 0; virtual int slot18() = 0; virtual int slot19() = 0;
	virtual int slot20() = 0; virtual int slot21() = 0; virtual int slot22() = 0; virtual int slot23() = 0;
	virtual int slot24() = 0; virtual int slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
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
	unsigned char m_mid119[0x1FC - 0x119];
	ContainModuleInterface *m_contain;				// +0x1FC
	unsigned char m_tail[0x344 - 0x200];
	unsigned char m_dead;						// +0x344, bit 0
};

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindOf0;						// +0xC8
	unsigned int m_kindOf1;						// +0xCC
	unsigned int m_kindOf2;						// +0xD0
	unsigned int m_kindOf3;						// +0xD4
	unsigned int m_kindOf4;						// +0xD8
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class AIGroup
{
public:
	void add(Object *obj);
};

extern float g_bfmeDefaultBU;					// retail VA 0x01075334 = 1.0f

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *out) const;
	void getTeamAsAIGroup(AIGroup *pAIGroup);
	Bool hasAnyUnits() const;
	Bool hasAnyObjects(const ObjectFilter *filter, Bool bfmeFlag) const;
	Bool hasAnyObjects(Bool bfmeFlag) const;
	Bool rva000F4E20();

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C
	unsigned char m_pad10[0xE6 - 0x10];
	unsigned char m_isActive;					// +0xE6

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
		if ((tmpl->m_kindOf0 & (1u << 7)) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
		if ((tmpl->m_kindOf0 & 0x2000000) != 0)
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
			if ((tmpl->m_kindOf0 & (1u << 7)) != 0 && (obj->m_status118 & 0x0C) != 0)
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
			if ((tmpl->m_kindOf0 & (1u << 7)) != 0 && (obj->m_status118 & 0x0C) != 0)
				continue;
		}

		{
			ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
			if ((tmpl->m_kindOf0 & 0x2000000) != 0)
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

// ?rva000F4E20@Team@@QAE_NXZ
// Team::updateState (0x000F4F30 +0x5B) asks this through ILT 0x00008A71 before
// running the create script. An inactive team answers true; otherwise a member
// with status bit 0x04 at +0x90 answers false, and so does a member whose final
// template has KindOf word 3 bit 0x1000 and whose contain module's horde
// interface is empty, or reports slot 39 without slot 38. The re-test of the
// member the loop condition just proved non-null keeps VC7.1 from aligning the
// loop head, as retail does not.
Bool Team::rva000F4E20()
{
	if (m_isActive)
	{
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
			if (!obj)
				continue;
			if ((obj->m_status90 & 4) != 0)
				return false;

			if ((((ThingTemplate *)bfmeFinalTemplate(iter.cur()))->m_kindOf3 & 0x1000) == 0)
				continue;

			ContainModuleInterface *contain = obj->m_contain;
			if (contain == 0)
				continue;
			HordeContainInterface *horde = contain->getHordeContainInterface();
			if (horde == 0)
				continue;
			if (horde->getHordeMemberCount(false) == 0)
				return false;
			if (!horde->slot39())
				continue;
			if (!horde->slot38())
				return false;
		}
		return true;
	}
	return true;
}
