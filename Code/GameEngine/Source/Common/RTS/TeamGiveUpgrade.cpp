// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
//
// Team::giveUpgrade at retail RVA 0x000ED9D0 (102 bytes). ILT 0x0002DA5B jumps
// here and ScriptActions::doTeamUpgrade (0x002F5B80) is the sole caller.
// The body walks Team+0x0C through the BFME Object DLINK PMF, and for each
// member prefers the contain module's upgrade sink (Object+0x1FC, contain
// vtable +0x68, sink vtable +0xAC) over Object::giveUpgrade (ILT 0x0001A97E ->
// 0x001C9F70).
//
// The ZH Team.cpp member walks open every non-trivial loop body with
// "Object *obj = iter.cur(); if (!obj) continue;". Verified witnesses, both in
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/
// RTS/Team.cpp: Team::deleteTeam (lines 2262-2266) and Team::evacuateTeam
// (lines 2404-2410). Restoring that guard is what removes the five-byte eb03/lea
// loop-alignment pad at +0x1B that sixteen earlier attempts measured: the
// redundant test folds into the loop's own exit test, but it costs the loop
// head its alignment bonus, so MSVC 7.1 stops padding it. The small sibling
// Team::healAllObjects (0x000EDA50) has no such guard and retail pads it,
// which is why the pad is not a toolchain difference.

typedef bool Bool;

class UpgradeTemplate;
class Object;

// Byte-identical to the skeleton in reference/shims/objectdlink/ObjectDlinkPmf.h
// and kept TU-local only because this TU must add a member (the pinned
// Object::giveUpgrade declaration) to Object, which including the header cannot
// do -- not a redeclaration of a covered type. The vbptr carrier is
// inherited at +0x68 and introduces the virtual base at its own +0, so the
// inherited dlink base remains at +0x04 and therefore encodes the PMF
// {pfn=0x00401140, delta=-100, vbindex=0}.
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
	void giveUpgrade(const UpgradeTemplate *upgradeT);
	unsigned char m_tail[0x40];
};

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { m_cur = callMemberFunction(*m_cur, m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS* cur() const { return m_cur; }
};

// The leading slots are spacers, not an identity claim on the contain and
// upgrade-sink interfaces. The two slots the body actually calls are spelled
// slotNN after their vtable INDEX (the Object_containPairDispatch.cpp
// convention for this same contain vtable): the evidence proves the call
// offsets and that slot 26 returns a pointer, and nothing more, so no semantic
// method name is asserted for either. BfmeUpgradeSink is self-labelling.
class BfmeUpgradeSink
{
public:
	virtual void _s00() = 0; virtual void _s01() = 0; virtual void _s02() = 0;
	virtual void _s03() = 0; virtual void _s04() = 0; virtual void _s05() = 0;
	virtual void _s06() = 0; virtual void _s07() = 0; virtual void _s08() = 0;
	virtual void _s09() = 0; virtual void _s10() = 0; virtual void _s11() = 0;
	virtual void _s12() = 0; virtual void _s13() = 0; virtual void _s14() = 0;
	virtual void _s15() = 0; virtual void _s16() = 0; virtual void _s17() = 0;
	virtual void _s18() = 0; virtual void _s19() = 0; virtual void _s20() = 0;
	virtual void _s21() = 0; virtual void _s22() = 0; virtual void _s23() = 0;
	virtual void _s24() = 0; virtual void _s25() = 0; virtual void _s26() = 0;
	virtual void _s27() = 0; virtual void _s28() = 0; virtual void _s29() = 0;
	virtual void _s30() = 0; virtual void _s31() = 0; virtual void _s32() = 0;
	virtual void _s33() = 0; virtual void _s34() = 0; virtual void _s35() = 0;
	virtual void _s36() = 0; virtual void _s37() = 0; virtual void _s38() = 0;
	virtual void _s39() = 0; virtual void _s40() = 0; virtual void _s41() = 0;
	virtual void _s42() = 0;
	// Sink vtable +0xAC == index 43. Takes the caller's UpgradeTemplate*; the
	// sink's own name for it is unknown, so the slot index is the name.
	virtual void slot43(const UpgradeTemplate *upgrade) = 0;
};

// ContainModuleInterface is the real ZH class name and its +0x1FC placement in
// Object is witnessed, but ZH's ContainModuleInterface (see
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/
// GameLogic/Module/ContainModule.h) has NO member at this slot at all -- the
// BFME vtable is longer than ZH's. So the slot keeps its index for a name.
class ContainModuleInterface
{
public:
	virtual void _c00() = 0; virtual void _c01() = 0; virtual void _c02() = 0;
	virtual void _c03() = 0; virtual void _c04() = 0; virtual void _c05() = 0;
	virtual void _c06() = 0; virtual void _c07() = 0; virtual void _c08() = 0;
	virtual void _c09() = 0; virtual void _c10() = 0; virtual void _c11() = 0;
	virtual void _c12() = 0; virtual void _c13() = 0; virtual void _c14() = 0;
	virtual void _c15() = 0; virtual void _c16() = 0; virtual void _c17() = 0;
	virtual void _c18() = 0; virtual void _c19() = 0; virtual void _c20() = 0;
	virtual void _c21() = 0; virtual void _c22() = 0; virtual void _c23() = 0;
	virtual void _c24() = 0; virtual void _c25() = 0;
	// Contain vtable +0x68 == index 26. All the evidence gives is "returns a
	// pointer"; the returned object is used only as the sink below.
	virtual BfmeUpgradeSink *slot26() = 0;
};

// The +0x1FC contain slot witnessed by Object::giveUpgrade at 0x001C9F70.
class BfmeObjectContainView
{
public:
	unsigned char m_head[0x1FC];
	ContainModuleInterface *m_contain;
};

class Team
{
public:
	void giveUpgrade(const UpgradeTemplate *upgrade);
	void *m_vptr; void *m_proto; void *m_id; Object *m_head;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

void Team::giveUpgrade(const UpgradeTemplate *upgrade)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (!obj)
			continue;

		ContainModuleInterface *contain = ((BfmeObjectContainView *)obj)->m_contain;
		if (contain != 0)
		{
			BfmeUpgradeSink *sink = contain->slot26();
			if (sink != 0)
			{
				sink->slot43(upgrade);
				continue;
			}
		}
		obj->giveUpgrade(upgrade);
	}
}
