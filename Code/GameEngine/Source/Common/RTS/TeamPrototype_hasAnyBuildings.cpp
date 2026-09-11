// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// ?hasAnyBuildings@Team@@QAE_NV?$BitFlags@$0MA@@@_N@Z
// Retail 0x000F4A70, Team::hasAnyBuildings(BitFlags<192>, Bool), 190 bytes.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

extern void j_00001140();
extern void j_000022bb();

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@BfmeOverridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	 typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) :
		m_cur(cur), m_getNextFunc(getNextFunc)
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

private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
};

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;
typedef BitFlags<126> KindOfMask126;

extern const KindOfMask126 KINDOFMASK_NONE;

class BfmeOverridable
{
public:
	const BfmeOverridable *getFinalOverride() const;

	void *m_vtable;
	BfmeOverridable *m_nextOverride;
};

class BfmeObjectTemplateView
{
public:
	void *m_vptr;
	BfmeOverridable *m_template;
};

class BfmeObjectStatusView
{
public:
	unsigned char m_head[0x118];
	unsigned char m_status118;
};

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindOf0;
	unsigned int m_kindOf1;
};

class Thing
{
public:
	Bool isKindOfMulti(const KindOfMask126 &mustBeSet,
		const KindOfMask126 &mustBeClear) const;
};

class Team
{
public:
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag);

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

static BfmeOverridable *bfmeFinalTemplate(Object *obj)
{
	BfmeOverridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (BfmeOverridable *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

static BfmeOverridable *bfmeFinalTemplateGuard(Object *obj)
{
	if (!obj) return 0;
	BfmeOverridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (BfmeOverridable *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

Bool Team::hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag)
{
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	if (iter.done())
		return false;
	__asm { nop }
	for (; !iter.done(); iter.advance())
	{
		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplateGuard(iter.cur());
		if ((tmpl->m_kindOf1 & 0x400000) != 0)
			continue;

		if (bfmeFlag)
		{
			tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
			BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
			if ((tmpl->m_kindOf0 & (1u << 7)) != 0 && (obj->m_status118 & 0x0C) != 0)
				continue;
		}

		kindOf.m_bits[0] |= 0x80u;
		if (((Thing *)iter.cur())->isKindOfMulti(
			*reinterpret_cast<const KindOfMask126 *>(&kindOf),
			KINDOFMASK_NONE))
			return true;
	}
	return false;
}
