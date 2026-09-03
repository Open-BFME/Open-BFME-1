// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::hasAnyUnits, retail 0x000F4C10, 179 bytes.
//
// Named by the already-matched TeamPrototype::hasAnyUnits walk. The member
// list is the Object DLINK PMF {pfn=0x00401140, delta=-100, vbindex=0} from
// ObjectDlinkPmf.h. Dead is bit 0 of Object+0x344; destroyed is bit 0 of
// Object+0x90. Each KindOf test re-walks the template at +0x04 through the
// Overridable final-override ILT at 0x000022BB. STRUCTURE is bit 7 of the
// first kind-of dword (the (1<<7) form is what emits retail's test-cl/js);
// PROJECTILE is 0x2000000 of that same dword; MINE is 0x80000 at +0xD8.

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

class BfmeObjectStatusView
{
public:
	unsigned char m_head[0x90];
	unsigned char m_destroyed;					// +0x90, bit 0
	unsigned char m_mid[0x344 - 0x91];
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyUnits() const;

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

// ?hasAnyUnits@Team@@QBE_NXZ
Bool Team::hasAnyUnits() const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
		if ((obj->m_dead & 1) != 0)
			continue;
		if ((obj->m_destroyed & 1) != 0)
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
