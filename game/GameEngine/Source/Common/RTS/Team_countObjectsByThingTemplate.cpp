// Byte-exact BFME reconstruction of Team::countObjectsByThingTemplate.
// The Object/iterator layout is shared with the proven Team::countObjects
// member-list walk. Keeping template resolution behind BfmeOverride::operator->
// preserves retail's otherwise redundant null guard before iterator advance.
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

// Retail routes these three calls through incremental-link thunks.
extern void j_00001140();
extern void j_000022bb();
extern void j_0003e80b();

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
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
			if (next != 0) {
				typedef const Overridable *(Overridable::*FinalOverrideFn)() const;
				union { void (*fn)(); FinalOverrideFn call; } u = { j_000022bb };
				raw = (Overridable *)(*next.*u.call)();
			}
			value = (const T *)raw;
		}
		return value;
	}

	const T *volatile m_overridable;
};

class BfmeObjectDlinkBase
{
public:
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
		typedef Object *(BfmeObjectDlinkBase::*NextFunc)() const;
		union { void (*fn)(); NextFunc call; } u = { j_00001140 };
		return BfmeDlinkIterator<Object>(m_head, u.call);
	}
};

// ?countObjectsByThingTemplate@Team@@QBEXHPBQBVThingTemplate@@_NPAH1@Z
void Team::countObjectsByThingTemplate(Int count, const ThingTemplate *const *things,
	Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const
{
	for (BfmeDlinkIterator<Object> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance()) {
		const ThingTemplate *tmpl = iter.cur()->getTemplate();
		typedef Bool (ThingTemplate::*IsEquivalentToFn)(const ThingTemplate *) const;
		union { void (*fn)(); IsEquivalentToFn call; } isEquivalentTo = { j_0003e80b };
		for (Int i = 0; i < count; ++i) {
			if (!(tmpl->*isEquivalentTo.call)(things[i]))
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

