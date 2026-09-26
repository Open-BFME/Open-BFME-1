// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
// BFME's inner team-member walk.  ObjectDlinkPmf.h carries the recovered
// virtual-inheritance layout that gives Object's DLINK member pointer the
// retail {pfn, -100, 0} representation.
#include "ObjectDlinkPmf.h"

typedef void (__cdecl *ObjectIterateFunc)(Object *, void *);
typedef int (__cdecl *BfmeCheckedObjectIterateFunc)(Object *, void *);

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class BfmeDlinkIterator
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

	BfmeDlinkIterator(OBJCLASS *current, GetNextFunc getNext) :
		m_current(current), m_getNext(getNext)
	{
	}

	void advance(void)
	{
		if (m_current)
			m_current = callMemberFunction(*m_current, m_getNext)();
	}

	bool done(void) const { return m_current == 0; }
	OBJCLASS *current(void) const { return m_current; }

private:
	OBJCLASS *m_current;
	GetNextFunc m_getNext;
};

class BfmeInnerIterable
{
public:
	int bfmeVisit(ObjectIterateFunc func, void *userData);

private:
	unsigned char m_bfmeHead[0x0c];
	Object *m_bfmeFirst;
};

int BfmeInnerIterable::bfmeVisit(ObjectIterateFunc func, void *userData)
{
	BfmeDlinkIterator<Object> iter(m_bfmeFirst,
		Object::dlink_next_TeamMemberList);

	for (; !iter.done(); iter.advance())
	{
		if (!((BfmeCheckedObjectIterateFunc)func)(iter.current(), userData))
			return 0;
	}

	return 1;
}
