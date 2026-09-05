// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::getEstimateTeamPosition(Coord3D *), retail 0x000F2420, 214 bytes.
//
// Named by the already-matched ScriptActions::doRecruitTeam caller. Member
// list is the Object DLINK PMF {pfn=0x00401140, delta=-100, vbindex=0}. Dead
// is bit 0 of Object+0x344; destroyed is bit 0 of Object+0x90. Surviving
// members average Object+0x38/0x3C/0x40. The reciprocal count uses the 1.0f numerator at
// VA 0x01075334 (bytes 00 00 80 3f).

#include "ObjectDlinkPmf.h"

typedef float Real;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmeObjectStatusView
{
public:
	unsigned char m_head[0x38];
	Real m_x;							// +0x38
	Real m_y;							// +0x3C
	Real m_z;							// +0x40
	unsigned char m_mid[0x90 - 0x44];
	unsigned char m_destroyed;					// +0x90, bit 0
	unsigned char m_pad[0x344 - 0x91];
	unsigned char m_dead;						// +0x344, bit 0
};

extern float g_bfmeDefaultBU;					// retail VA 0x01075334 = 1.0f

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *out) const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// ?getEstimateTeamPosition@Team@@QBEPAUCoord3D@@PAU2@@Z
Coord3D *Team::getEstimateTeamPosition(Coord3D *out) const
{
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	int count = 0;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		BfmeObjectStatusView *obj = (BfmeObjectStatusView *)iter.cur();
		if ((obj->m_dead & 1) != 0)
			continue;
		if ((obj->m_destroyed & 1) != 0)
			continue;

		++count;
		pos.x += obj->m_x;
		pos.y += obj->m_y;
		pos.z += obj->m_z;
	}

	if (count > 0)
	{
		Real recip = g_bfmeDefaultBU / (Real)count;
		pos.x *= recip;
		pos.y *= recip;
		pos.z *= recip;
	}

	out->x = pos.x;
	out->y = pos.y;
	out->z = pos.z;
	return out;
}
