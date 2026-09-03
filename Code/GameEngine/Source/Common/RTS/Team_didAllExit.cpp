// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::didAllExit, retail 0x000F58B0, 297 bytes (18-byte
// m_enteredOrExited guard at +0x30 plus the 279-byte DLINK walk at 0x000F58C2).
// Named by ScriptConditions::evaluateTeamExitedAreaEntirely. Same Object
// DLINK PMF as Team::noneInside. Two KindOf skips (dword +0xD0 bit 0x01000000
// then byte +0xD8 bit 0x20). didExit / isInside are already-matched Object
// bodies.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

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

class BfmeObjectInsideView
{
public:
	unsigned char m_head[0x204];
	void *m_ai;							// +0x204
	unsigned char m_mid[0x344 - 0x208];
	unsigned char m_dead;						// +0x344, bit 0

	Bool didExit(class PolygonTrigger *pTrigger) const;
	Bool isInside(class PolygonTrigger *pTrigger) const;
};

class BfmeAISurfacesView
{
public:
	unsigned char m_head[0x1B8];
	UnsignedInt m_surfaces;					// AI+0x1B8
};

class ThingTemplate
{
public:
	unsigned char m_head[0xD0];
	UnsignedInt m_kindOf2;						// +0xD0
	UnsignedInt m_kindOf3;						// +0xD4
	unsigned char m_kindOf4;					// +0xD8
};

class PolygonTrigger;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C
	unsigned char m_mid[0x30 - 0x10];
	Bool m_enteredOrExited;					// +0x30

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

// ?didAllExit@Team@@QBE_NPAVPolygonTrigger@@I@Z
Bool Team::didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	if (!m_enteredOrExited)
		return false;

	Bool anyConsidered = false;
	Bool exited = false;
	Bool inside = false;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *cur = iter.cur();
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf4 & 0x20) != 0)
			continue;

		if (((BfmeObjectInsideView *)cur)->didExit(pTrigger))
			exited = true;
		else if (((BfmeObjectInsideView *)cur)->isInside(pTrigger))
			inside = true;
		anyConsidered = true;
	}
	return anyConsidered && exited && !inside;
}
