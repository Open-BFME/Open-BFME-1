// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
//
// Retail 0x000EDCD0 (186 bytes, ret 4), reached through ILT 0x000241FE by
// the matched script actions, script conditions and AI guard states that
// declare Team::getEstimateTeamPosition_000EDCD0 and pass a Coord3D to fill.
//
// Shape: walk the TeamMemberList (head at +0x0c, the {0x00401140, -100, 0}
// DLINK pointer-to-member of ObjectDlinkPmf.h), sum each member's position
// (Object +0x38/+0x3c/+0x40) and write the average to the out-parameter.
// The body returns nothing: a Coord3D* return forces MSVC 7.1 to keep the
// out pointer in a second register, while retail stores through EAX, and no
// caller reads EAX after the call.
//
// The `if (!obj) continue;` guard is the upstream DLINK idiom; it lets the
// compiler fold advance()'s null test, as in ScriptConditionsTeamIsLedByUnit.cpp.

typedef bool Bool;
typedef float Real;

#include "ObjectDlinkPmf.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
template<class OBJCLASS>
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

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

// Object +0x38: the position the body sums (address-derived view).
struct Rva000EDCD0ObjectPosition
{
	unsigned char m_before[0x38];
	Coord3D m_position;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}

	void getEstimateTeamPosition_000EDCD0(Coord3D *pos) const;
};

void Team::getEstimateTeamPosition_000EDCD0(Coord3D *pos) const
{
	Coord3D sum;
	sum.x = 0.0f;
	sum.y = 0.0f;
	sum.z = 0.0f;
	int count = 0;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (!obj)
			continue;
		const Coord3D *p = &((const Rva000EDCD0ObjectPosition *)obj)->m_position;
		sum.x += p->x;
		sum.y += p->y;
		sum.z += p->z;
		++count;
	}
	Real scale = 1.0f / count;
	sum.x *= scale;
	sum.y *= scale;
	sum.z *= scale;
	*pos = sum;
}
