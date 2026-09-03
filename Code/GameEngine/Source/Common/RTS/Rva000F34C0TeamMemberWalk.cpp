// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
//
// 0x000F34C0: Team member-list drain via Object DLINK PMF
// {pfn=0x00401140, delta=-100, vbindex=0}. Head at Team+0x0C.
// ret 0x0C -- three stack dwords, unused in the walk.

#include "ObjectDlinkPmf.h"

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

// Layout is the Team member-list slice (head at +0x0C). Method name is not
// recovered -- three unused stack dwords produce retail's ret 0x0C.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Rva000F34C0
{
public:
	void walk(int a, int b, int c);

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// ?walk@Rva000F34C0@@QAEXHHH@Z
void Rva000F34C0::walk(int, int, int)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
		;
}
