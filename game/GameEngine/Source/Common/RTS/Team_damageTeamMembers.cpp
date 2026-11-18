// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/objectdlink
//
// Team::damageTeamMembers at retail RVA 0x000F33F0 (159 bytes).
// The Team source owns this operation: it walks Team+0x0C through the BFME
// Object DLINK PMF, skips the two member status bits, then either calls the
// Object kill entry point or fills the 0x5c-byte BFME DamageInfo and dispatches
// Object::attemptDamage at vtable +0x34.

#include "../../../Include/Common/ScalarTypes.h"

typedef unsigned int ObjectID;

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

#include "../../../Include/Common/Enums/DeathType.h"




struct BFMEDamageInfoInput
{
	unsigned char m_unreconstructed_00[8];
	ObjectID m_sourceID;
	unsigned char m_unreconstructed_0c[4];
	DamageType m_damageType;
	unsigned char m_unreconstructed_14[4];
	DeathType m_deathType;
	Real m_amount;
	Bool m_kill;
};

struct BFMEDamageInfo
{
	BFMEDamageInfo();

	BFMEDamageInfoInput in;
	unsigned char m_unreconstructed_24[0x5c - 0x24];
};

// This is deliberately a vtable-only view.  It declares every slot leading
// to attemptDamage, so the call is the proven BFME +0x34 dispatch and does not
// manufacture a vtable or claim an Object class layout here.
struct BFMEObjectAttemptDamageShim
{
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot0C() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot18() = 0;
	virtual void bfmeSlot1C() = 0;
	virtual void bfmeSlot20() = 0;
	virtual void bfmeSlot24() = 0;
	virtual void bfmeSlot28() = 0;
	virtual void bfmeSlot2C() = 0;
	virtual void bfmeSlot30() = 0;
	virtual void attemptDamage(BFMEDamageInfo *damageInfo) = 0;
};

// Object's two status reads are retained as byte-offset views.  The names are
// intentionally neutral: this body proves the bits used by this retail
// function, not a broader Object flag taxonomy.
struct BfmeObjectDamageStatusView
{
	unsigned char m_unreconstructed_000[0x90];
	unsigned char m_status90;
	unsigned char m_unreconstructed_091[0x344 - 0x91];
	unsigned char m_status344;
};

// This is the proven ObjectDlinkPmf.h layout, kept TU-local so the canonical
// Object::kill declaration can retain its real ABI identity without changing
// the shared shim.  The virtual-base carrier places the BFME vbptr at +0x68;
// the inherited dlink base remains at +0x04 and therefore encodes the PMF
// {pfn=0x00401140, delta=-100, vbindex=0}.
class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	void kill(DamageType damageType, DeathType deathType);
	unsigned char m_tail[0x40];
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const
	{
		return m_cur == 0;
	}

	ObjectType *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNext)();
	}

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

// upstream Team layout: the member-list head is at +0x0c.
class Team
{
public:
	Bool damageTeamMembers(Real amount);
	Bool hasAnyBuildings(Bool bfmeFlag) const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

// ?damageTeamMembers@Team@@QAE_NM@Z
Bool Team::damageTeamMembers(Real amount)
{
	for (BfmeDlinkIterator<Object> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		BfmeObjectDamageStatusView *status =
			reinterpret_cast<BfmeObjectDamageStatusView *>(iter.cur());
		if ((status->m_status344 & 1) != 0)
			continue;
		if ((status->m_status90 & 1) != 0)
			continue;

		if (amount < 0.0)
		{
			iter.cur()->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
		}
		else
		{
			BFMEDamageInfo damageInfo;
			damageInfo.in.m_damageType = DAMAGE_UNRESISTABLE;
			damageInfo.in.m_deathType = DEATH_NORMAL;
			damageInfo.in.m_sourceID = 0;
			damageInfo.in.m_amount = amount;
			reinterpret_cast<BFMEObjectAttemptDamageShim *>(iter.cur())
				->attemptDamage(&damageInfo);
		}
	}
	return false;
}

extern void j_00001140();
extern void j_0002c9d5();

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@@Z=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:??0BFMEDamageInfo@@QAE@XZ=?j_0002c9d5@@YAXXZ")

#define DLINK_ITERATOR BfmeDlinkIterator

// Zero Hour's OVERRIDE<ThingTemplate> with the reference's inline recursive
// Overridable::getFinalOverride (outer level inline, recursive call at ILT
// 0x000022BB); with that typing MSVC aligns hasAnyBuildings' loop head itself,
// which is the retail nop at 0x000F499F.
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

static inline const ThingTemplate *getTemplate(Object *obj)
{
	return ((BfmeObjectTemplateView *)obj)->m_template;
}

Bool Team::hasAnyBuildings(Bool bfmeFlag) const
{
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	if (iter.done())
		return false;
	for (;
		!iter.done(); iter.advance())
	{
		const ThingTemplate *tmpl = getTemplate(iter.cur());
		if ((tmpl->m_kindOf1 & 0x400000) != 0)
			continue;

		if (bfmeFlag)
		{
			tmpl = getTemplate(iter.cur());
			BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
			if ((tmpl->m_kindOf0 & (1u << 7)) != 0 &&
				(obj->m_status118 & 0x0C) != 0)
				continue;
		}

		tmpl = getTemplate(iter.cur());
		if ((tmpl->m_kindOf0 & (1u << 7)) != 0)
			return true;
	}
	return false;
}
