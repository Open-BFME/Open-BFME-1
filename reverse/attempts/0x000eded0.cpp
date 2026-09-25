// ?d_000eded0@@YAXXZ
// partial score=0.93 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Retail RVA 0x000EDED0, 132 bytes through the int3 run at +0x84 (Ghidra split
// it at the null-argument exit, +0x0D).  ScriptActions::doTeamGiveTeamUpgrade
// calls it through ILT 0x00018449 on the destination team with the upgrade:
// it walks the team members as 0x000EDF80 does and answers true when a
// member's contain (Object+0x1FC) yields an object whose slot +0xA4 accepts
// the upgrade, or, without one, when Object::affectedByUpgrade (ILT
// 0x000077B6) does.  The owner, method and contain slots keep the address.

typedef bool Bool;

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class UpgradeTemplate;

#define RVA000EDED0_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();

class Rva000EDED0Rider
{
public:
	RVA000EDED0_SLOTS4(a) RVA000EDED0_SLOTS4(b) RVA000EDED0_SLOTS4(c) RVA000EDED0_SLOTS4(d)
	RVA000EDED0_SLOTS4(e) RVA000EDED0_SLOTS4(f) RVA000EDED0_SLOTS4(g) RVA000EDED0_SLOTS4(h)
	RVA000EDED0_SLOTS4(i) RVA000EDED0_SLOTS4(j)
	virtual void slotA0();
	virtual Bool slotA4(const UpgradeTemplate *upgrade);
};

class Rva000EDED0Contain
{
public:
	RVA000EDED0_SLOTS4(a) RVA000EDED0_SLOTS4(b) RVA000EDED0_SLOTS4(c) RVA000EDED0_SLOTS4(d)
	RVA000EDED0_SLOTS4(e) RVA000EDED0_SLOTS4(f)
	virtual void slot60(); virtual void slot64();
	virtual Rva000EDED0Rider *slot68();
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x1FC - 0x70];
	Rva000EDED0Contain *m_contain;
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
};

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance(void)
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done(void) const
	{
		return m_cur == 0;
	}

	OBJCLASS *cur(void) const
	{
		return m_cur;
	}
};

class Rva000EDED0Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}

	Bool method(const UpgradeTemplate *upgrade) const;
};

Bool Rva000EDED0Team::method(const UpgradeTemplate *upgrade) const
{
	if (!upgrade)
		return false;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		Rva000EDED0Contain *contain = object->m_contain;
		Rva000EDED0Rider *rider = contain ? contain->slot68() : 0;
		if (rider)
		{
			if (rider->slotA4(upgrade))
				return true;
		}
		else if (object->affectedByUpgrade(upgrade) == 1)
			return true;
	}

	return false;
}
