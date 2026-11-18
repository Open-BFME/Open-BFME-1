// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
// ?hasAnyBuildings@Team@@QAE_NV?$BitFlags@$0MA@@@_N@Z
// Retail 0x000F4A70, Team::hasAnyBuildings(BitFlags<192>, Bool), 190 bytes.
// The template reads are Zero Hour's OVERRIDE<ThingTemplate> with the reference's
// inline recursive Overridable::getFinalOverride (outer level inline, recursive
// call at ILT 0x000022BB); with that typing MSVC aligns the loop head itself,
// which is the retail nop at +0x1F.

#include "ObjectDlinkPmf.h"

#include "../../../Include/Common/ScalarTypes.h"


extern void j_00001140();

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

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	const T *operator*() const
	{
		if (!m_overridable) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }

	const T *m_overridable;
};

class ThingTemplate;

class BfmeObjectTemplateView
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }

	void *m_vptr;
	OVERRIDE<ThingTemplate> m_template;
};

class BfmeObjectStatusView
{
public:
	unsigned char m_head[0x118];
	unsigned char m_status118;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_head[0xC8 - 8];
	unsigned int m_kindOf0;
	unsigned int m_kindOf1;
};

#define THING_TU_MEMBERS \
public: Bool isKindOfMulti(const KindOfMask116 &mustBeSet, \
		const KindOfMask116 &mustBeClear) const;
#include "../Thing/thing.h"
#undef THING_TU_MEMBERS

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

static inline const ThingTemplate *getTemplate(Object *obj)
{
	return ((BfmeObjectTemplateView *)obj)->getTemplate();
}

Bool Team::hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag)
{
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	if (iter.done())
		return false;
	for (; !iter.done(); iter.advance())
	{
		const ThingTemplate *tmpl = getTemplate(iter.cur());
		if ((tmpl->m_kindOf1 & 0x400000) != 0)
			continue;

		if (bfmeFlag)
		{
			tmpl = getTemplate(iter.cur());
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
