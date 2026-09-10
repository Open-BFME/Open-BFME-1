// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[ 4 ];
};

// The retail Team-member walk uses the inherited virtual-base pointer at
// Object+0x68.  This is the same layout as the matched Team::countObjects
// sibling at 0x000F2770, including the -100 PMF delta.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[ 4 ];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		const T *value = m_overridable;
		if (value && value->m_nextOverride)
			value = (const T *)value->m_nextOverride->getFinalOverride();
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
	BfmeOverride<class ThingTemplate> m_template;
};

// The typed Base method is the retail body at 0x000C8980.  Its receiver is
// the Object DLINK base subobject, and the next-link field is at +0x260.
Object *BfmeObjectDlinkBase::dlink_next_TeamMemberList() const
{
	return *(Object **)((const char *)this + 0x260);
}

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[ 0x60 ];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const class ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}

	unsigned char m_tail[ 0x40 ];
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)() const;

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	BfmeDlinkIterator(ObjectType *cur, BfmeGetNextTeamMemberFunc getNext)
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
			m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[ 0xc0 ];
	UnsignedInt m_kindOf[ 6 ]; // matched Team kind-mask ABI is BitFlags<192>.

	Bool hasKind(UnsignedInt kind) const
	{
		return (m_kindOf[kind >> 5] & (1u << (kind & 31))) != 0;
	}
};

class BfmeObjectStatusView
{
public:
	unsigned char m_prefix[ 0x90 ];
	unsigned char m_status90;
	unsigned char m_between[ 0x344 - 0x91 ];
	unsigned char m_status344;
};

class Rva000F4830
{
public:
	Int countKind(UnsignedInt kind, Bool excludeFlag344, Bool excludeFlag90);

private:
	unsigned char m_unmodelled_000[ 0x0c ];
	Object *m_head;

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

// The matched ScriptConditions::evaluateTeamCountCompare caller reaches this
// body through ILT 0x0000A957 and supplies (kind, false, true).  The two Bool
// parameters are exclusion flags in the retail stack order: [esp+0x1c] is
// excludeFlag344 and [esp+0x20] is excludeFlag90.
Int Rva000F4830::countKind(UnsignedInt kind, Bool excludeFlag344, Bool excludeFlag90)
{
	Int retVal = 0;
	for (BfmeDlinkIterator<Object> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		BfmeObjectStatusView *object = (BfmeObjectStatusView *)iter.cur();
		if (excludeFlag344 && (object->m_status344 & 1) != 0)
			continue;
		if (excludeFlag90 && (object->m_status90 & 4) != 0)
			continue;

		const ThingTemplate *tmpl = iter.cur()->getTemplate();
		if (tmpl->hasKind(kind))
			++retVal;
	}
	return retVal;
}
