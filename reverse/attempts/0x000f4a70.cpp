// ?hasAnyBuildings@Team@@QAE_NV?$BitFlags@$0MA@@@_N@Z
// partial score=0.98 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::hasAnyBuildings(BitFlags<192>, Bool), retail 0x000F4A70, 190 bytes.
//
// Named by the already-matched TeamPrototype::hasAnyBuildings walk at
// 0x000F7020, which forwards the same mask and flag to every instance.
// Same Object DLINK PMF as Team::hasAnyUnits (pfn in ebp, delta in ebx).
// Kind-of dword 1 bit 0x400000 skips. The Bool flag gates a STRUCTURE
// (bit 7 of dword 0) filter that also requires Object+0x118 bits 0x0C.
// Remaining objects OR STRUCTURE (0x80) into the mask and call
// Thing::isKindOfMulti against KINDOFMASK_NONE.

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

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;
typedef BitFlags<126> KindOfMask126;

extern const KindOfMask126 KINDOFMASK_NONE;

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
	unsigned char m_head[0x118];
	unsigned char m_status118;					// +0x118
};

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindOf0;						// +0xC8
	unsigned int m_kindOf1;						// +0xCC
};

class Thing
{
public:
	Bool isKindOfMulti(const KindOfMask126 &mustBeSet, const KindOfMask126 &mustBeClear) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag);

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

// ?hasAnyBuildings@Team@@QAE_NV?$BitFlags@$0MA@@@_N@Z
Bool Team::hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
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
		if (iter.cur())
			continue;
	}
	return false;
}
