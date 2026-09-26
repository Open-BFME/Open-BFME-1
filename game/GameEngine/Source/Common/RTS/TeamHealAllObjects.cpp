// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink

#include "ObjectDlinkPmf.h"

class Rva001BE790
{
public:
	void run();
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	void healAllObjects();

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// ?healAllObjects@Team@@QAEXXZ
void Team::healAllObjects()
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		((Rva001BE790 *)iter.cur())->run();
	}
}
