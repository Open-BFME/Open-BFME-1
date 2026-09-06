// ?countKind@Rva000F4830@@QAEHI_N0@Z
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Scratch candidate for retail 0x000F4830.  The caller at 0x00324600
// supplies (kind, false, true) through the 0x0000A957 thunk.

#include "ObjectDlinkPmf.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }

	void advance()
	{
		m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS* cur() const { return m_cur; }

private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ObjectIterator
{
public:
	typedef Object* (Object::*GetNextFunc)() const;
	ObjectIterator(Object *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }
	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
private:
	Object *m_cur;
	GetNextFunc m_getNextFunc;
};

class ObjectTemplateView
{
public:
	void *m_vptr;
	Overridable *m_template;
};

class ObjectStatusView
{
public:
	unsigned char m_prefix[0x90];
	unsigned char m_status90;
	unsigned char m_between[0x344 - 0x91];
	unsigned char m_dead;
};

class ThingTemplate
{
public:
	unsigned char m_prefix[0xC8];
	unsigned int m_kindOf[5];
};

class Rva000F4830
{
public:
	Int countKind(UnsignedInt kind, Bool includeDead, Bool includeContained);

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

static Overridable *bfmeFinalTemplate(Object *object)
{
	Overridable *raw = ((ObjectTemplateView *)object)->m_template;
	if (raw != 0 && raw->m_nextOverride != 0)
		raw = (Overridable *)raw->m_nextOverride->getFinalOverride();
	return raw;
}

Int Rva000F4830::countKind(UnsignedInt kind, Bool includeDead, Bool includeContained)
{
	Int retVal = 0;
	for (ObjectIterator iter(m_head, Object::dlink_next_TeamMemberList);
		!iter.done(); )
	{
		ObjectStatusView *object = (ObjectStatusView *)iter.cur();
		if (includeDead && (object->m_dead & 1) != 0)
			goto next;
		if (includeContained && (object->m_status90 & 4) != 0)
			goto next;

		{
			ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(iter.cur());
			if ((tmpl->m_kindOf[kind >> 5] & (1u << (kind & 31))) != 0)
				++retVal;
		}

	next:
		if (iter.cur() == 0)
			break;
		iter.advance();
	}
	return retVal;
}
