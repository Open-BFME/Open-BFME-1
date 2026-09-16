// Byte-exact BFME reconstruction of Team::countObjectsByThingTemplate.
// The Object/iterator layout is shared with the proven Team::countObjects
// member-list walk. Keeping template resolution behind BfmeOverride::operator->
// preserves retail's otherwise redundant null guard before iterator advance.
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo(const ThingTemplate *tt) const;
};

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
	virtual void bfmeObjectSlot0();
};

template <class T>
class BfmeOverride
{
public:
	const T *operator->() const
	{
		Overridable *raw = (Overridable *)m_overridable;
		const T *value;
		if (raw == 0) {
			value = 0;
		} else {
			Overridable *next = raw->m_nextOverride;
			if (next != 0)
				raw = (Overridable *)next->getFinalOverride();
			value = (const T *)raw;
		}
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
	BfmeOverride<ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class T>
class BfmeDlinkIterator
{
public:
	typedef T *(T::*GetNextFunc)() const;

	BfmeDlinkIterator(T *cur, GetNextFunc next) : m_cur(cur), m_next(next) {}
	Bool done() const { return m_cur == 0; }
	T *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_next)();
	}

private:
	T *m_cur;
	GetNextFunc m_next;
};

class BfmeObjectStatusView
{
public:
	unsigned char m_head[0x90];
	unsigned char m_status;
	unsigned char m_mid[0x344 - 0x91];
	unsigned char m_privateStatus;
};

class Team
{
public:
	void countObjectsByThingTemplate(Int count, const ThingTemplate *const *things,
		Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;

private:
	void *m_unmodelled_000;
	void *m_unmodelled_004;
	void *m_unmodelled_008;
	Object *m_head;

public:
	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

// ?countObjectsByThingTemplate@Team@@QBEXHPBQBVThingTemplate@@_NPAH1@Z
void Team::countObjectsByThingTemplate(Int count, const ThingTemplate *const *things,
	Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const
{
	for (BfmeDlinkIterator<Object> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance()) {
		const ThingTemplate *tmpl = iter.cur()->getTemplate();
		for (Int i = 0; i < count; ++i) {
			if (!tmpl->isEquivalentTo(things[i]))
				continue;

			BfmeObjectStatusView *object = (BfmeObjectStatusView *)iter.cur();
			if (ignoreDead && (object->m_privateStatus & 1) != 0)
				continue;
			if (ignoreUnderConstruction && (object->m_status & 4) != 0)
				continue;

			++counts[i];
			break;
		}
	}
}

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z=?j_0003e80b@@YAXXZ")
