// ?countObjectsByThingTemplate@Team@@QBEXHPBQBVThingTemplate@@_NPAH1@Z
// partial score=0.96 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::countObjectsByThingTemplate, retail 0x000F2670, 193 bytes.
//
// Named by the already-matched TeamPrototype::countObjectsByThingTemplate
// walk at 0x000F4030, which forwards the same five arguments to every
// instance. Member list is the Object DLINK PMF {pfn=0x00401140, delta=-100,
// vbindex=0}. Template is Object+0x04 through the Overridable final-override
// ILT at 0x000022BB. isEquivalentTo is the ILT at 0x0003E80B. Dead is bit 0
// of Object+0x344; under-construction is bit 2 of Object+0x90.

#include "ObjectDlinkPmf.h"

typedef int Int;
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

class BfmeObjectStatusView
{
public:
	unsigned char m_head[0x90];
	unsigned char m_status90;					// +0x90, bit 2 = under construction
	unsigned char m_mid[0x344 - 0x91];
	unsigned char m_dead;						// +0x344, bit 0
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *tt) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate *const *things,
		Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// ?countObjectsByThingTemplate@Team@@QBEXHPBQBVThingTemplate@@_NPAH1@Z
void Team::countObjectsByThingTemplate(Int numTmplates, const ThingTemplate *const *things,
	Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Overridable *raw = ((BfmeObjectTemplateView *)iter.cur())->m_template;
		ThingTemplate *tmpl;
		if (raw == 0)
			tmpl = 0;
		else
		{
			Overridable *next = raw->m_nextOverride;
			if (next != 0)
				raw = (Overridable *)next->getFinalOverride();
			tmpl = (ThingTemplate *)raw;
		}
		for (Int i = 0; i < numTmplates; ++i)
		{
			if (!tmpl->isEquivalentTo(things[i]))
				continue;

			BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
			if (ignoreDead && (obj->m_dead & 1) != 0)
				continue;
			if (ignoreUnderConstruction && (obj->m_status90 & 4) != 0)
				continue;

			counts[i] += 1;
			break;
		}
	}
}
