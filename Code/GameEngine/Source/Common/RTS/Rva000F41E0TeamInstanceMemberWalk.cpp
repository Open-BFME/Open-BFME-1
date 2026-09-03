// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
//
// 0x000F41E0: TeamPrototype instance-list walk at this+0x274 via ILT
// 0x00022A70, draining each team's member list (Team+0x0C) through the
// Object DLINK PMF {pfn=0x00401140, delta=-100, vbindex=0}. Same PMF as
// Rva000F34C0. Method name is not recovered -- three unused stack dwords
// produce retail's ret 0x0C.

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

class Team
{
public:
	Team *_bfme_nextInInstanceList();				// ILT 0x00022A70

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head)
		: m_cur(head)
	{
	}

	bool done() const
	{
		return m_cur == 0;
	}

	Team *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

// Layout is the TeamPrototype instance-list slice (head at +0x274).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Rva000F41E0
{
public:
	void walk(int a, int b, int c);

	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}

	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;					// +0x274
};

// ?walk@Rva000F41E0@@QAEXHHH@Z
void Rva000F41E0::walk(int, int, int)
{
	for (BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		for (DLINK_ITERATOR<Object> members = iter.cur()->iterate_TeamMemberList();
			 !members.done();
			 members.advance())
			;
	}
}
