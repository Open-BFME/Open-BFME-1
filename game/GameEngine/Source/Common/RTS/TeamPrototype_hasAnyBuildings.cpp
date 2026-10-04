// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
// ?hasAnyBuildings@Team@@QAE_NV?$BitFlags@$0MA@@@_N@Z
// Retail 0x000F4A70, Team::hasAnyBuildings(BitFlags<192>, Bool), 190 bytes.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

extern void j_00001140();
extern void j_000022bb();

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
typedef BitFlags<116> KindOfMask116;

// The one linked KINDOFMASK_NONE is game/GameEngine/Source/Common/System/KindOf.cpp's
// `const BitFlags<192>`, so this reference must carry that spelling or it names a
// symbol nothing defines.  isKindOfMulti uses Thing.cpp's 116-bit signature; the
// local Team mask is still passed by address through that same four-dword view.
extern const BitFlags<192> KINDOFMASK_NONE;

class BfmeOverridable
{
public:
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
	Bool isKindOfMulti(const KindOfMask116 &mustBeSet,
		const KindOfMask116 &mustBeClear) const;
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
		// The retail pfn slot is the ILT thunk 0x1140, reached through the
		// generic PMF dispatch; the member name itself is not a real symbol.
		typedef Object *(BfmeObjectDlinkBase::*GetNextFunc)() const;
		union { void (*fn)(); GetNextFunc call; } u = { j_00001140 };
		return DLINK_ITERATOR<Object>(m_head, u.call);
	}
};

static BfmeOverridable *bfmeFinalTemplate(Object *obj)
{
	typedef const BfmeOverridable *(BfmeOverridable::*FinalOverrideFunc)() const;
	union { void (*fn)(); FinalOverrideFunc call; } u = { j_000022bb };
	BfmeOverridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (BfmeOverridable *)(tmpl->m_nextOverride->*u.call)();
	return tmpl;
}

static BfmeOverridable *bfmeFinalTemplateGuard(Object *obj)
{
	typedef const BfmeOverridable *(BfmeOverridable::*FinalOverrideFunc)() const;
	union { void (*fn)(); FinalOverrideFunc call; } u = { j_000022bb };
	if (!obj) return 0;
	BfmeOverridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (BfmeOverridable *)(tmpl->m_nextOverride->*u.call)();
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
			*reinterpret_cast<const KindOfMask116 *>(&kindOf),
			*reinterpret_cast<const KindOfMask116 *>(&KINDOFMASK_NONE)))
			return true;
	}
	return false;
}
