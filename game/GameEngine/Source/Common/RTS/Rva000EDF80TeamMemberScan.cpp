// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
// Retail RVA 0x000EDF80: the Team member-list search used by the two
// special-power upgrade actions.  The owner and method remain address-derived;
// the callers prove the Team head and the hasSpecialPower predicate, but not
// the original source spelling.

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

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	Bool hasSpecialPower(SpecialPowerType type) const;
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

class Rva000EDF80
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

	Object *method(SpecialPowerType type) const;
};

// ?method@Rva000EDF80@@QBEPAVObject@@W4SpecialPowerType@@@Z
Object *Rva000EDF80::method(SpecialPowerType type) const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		if (object->hasSpecialPower(type) == 1)
			return object;
	}

	return 0;
}
