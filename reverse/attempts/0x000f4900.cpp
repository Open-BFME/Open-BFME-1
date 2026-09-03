// ?countBuildings@Team@@QAEHXZ
// partial score=0.96 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::countBuildings, retail 0x000F4900, 103 bytes.
//
// Named by the already-matched TeamPrototype::countBuildings walk. Same Object
// DLINK PMF as Team::hasAnyObjects. Counts members whose final template has
// STRUCTURE (bit 7 of kind-of dword 0). Null template is skipped.

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
	Overridable *m_template;
};

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindOf0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	int countBuildings();

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

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

// ?countBuildings@Team@@QAEHXZ
int Team::countBuildings()
{
	int retVal = 0;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
		if (tmpl == 0)
			continue;
		if ((tmpl->m_kindOf0 & (1u << 7)) != 0)
			++retVal;
	}
	return retVal;
}
