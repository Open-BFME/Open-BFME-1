// ?hasAnyBuildFacility@Team@@QBE_NXZ
// partial score=0.96 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::hasAnyBuildFacility, retail 0x000EF340, 99 bytes
// (ghidra 96 was short of the true-path pop/ret).
//
// Named by the already-matched TeamPrototype walk. The member list is the
// Object DLINK PMF {pfn=0x00401140, delta=-100, vbindex=0} from
// ObjectDlinkPmf.h. Each object's template at +0x04 is run through the
// Overridable final-override ILT at 0x000022BB, then the build-facility
// flag at template+0x486 is tested.

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
	Overridable *m_template;					// Object+0x04
};

class ThingTemplate
{
public:
	unsigned char m_head[0x486];
	unsigned char m_isBuildFacility;				// +0x486
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyBuildFacility() const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// ?hasAnyBuildFacility@Team@@QBE_NXZ
Bool Team::hasAnyBuildFacility() const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Overridable *tmpl = ((BfmeObjectTemplateView *)iter.cur())->m_template;
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
			tmpl = (Overridable *)tmpl->m_nextOverride->getFinalOverride();
		if (((ThingTemplate *)tmpl)->m_isBuildFacility != 0)
			return true;
	}
	return false;
}
