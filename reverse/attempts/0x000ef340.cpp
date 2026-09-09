// ?hasAnyBuildFacility@Team@@QBE_NXZ
// partial score=0.97 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::hasAnyBuildFacility, retail 0x000EF340, 96 bytes.
//
// Named by the already-matched TeamPrototype::hasAnyBuildFacility walk
// (Team.cpp). Same Object DLINK pointer-to-member-function shape as the
// landed TeamMemberQueries.cpp siblings: reference/shims/objectdlink/
// ObjectDlinkPmf.h is what makes MSVC emit retail's virtual-base-adjusted
// indirect call through the DLINK pointer-to-member (ILT 0x00401140,
// delta -0x64, vbindex 0).
//
// Prior attempts (reverse/attempts/0x000ef340.cpp, score 0.96) described the
// missing piece as the `test esi,esi` guard retail keeps right before the PMF
// advance call, which a DLINK_ITERATOR<Object>::advance() helper method lets
// the optimiser prove redundant and delete. Writing the walk as a raw
// while-loop whose own statement re-tests cur right before the call (not
// hidden inside a templated helper) keeps the guard, same fix as
// Team::countBuildings (BfmeConv2160.cpp): closes that gap to 95 of 96 bytes.
//
// Retail's template-override test differs from the countBuildings/
// getEstimateTeamPosition helper shape: when m_template is non-null but its
// m_nextOverride is null, retail does NOT fall back to reading the flag off
// the un-overridden template -- it skips the object outright, same as a null
// m_template. So this body does not reuse bfmeFinalTemplate(); it inlines
// the exact two-test retail shape.
//
// Remaining 1-byte gap and instruction-order diffs are the same register-bank
// reassignment residue as countBuildings (push edi timing vs the two PMF
// constant loads); cur/pfn declaration-order swap tested, no convergence.

#include "ObjectDlinkPmf.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class BfmeObjectTemplateView
{
public:
	void *m_vptr;
	Overridable *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	unsigned char m_head[0x486];
	unsigned char m_isBuildFacility;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	bool hasAnyBuildFacility() const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

typedef Object *(Object::*BfmeGetNextFunc)() const;

// ?hasAnyBuildFacility@Team@@QBE_NXZ
bool Team::hasAnyBuildFacility() const
{
	Object *cur = m_head;
	BfmeGetNextFunc pfn = Object::dlink_next_TeamMemberList;

	while (cur != 0)
	{
		Overridable *tmpl = ((BfmeObjectTemplateView *)cur)->m_template;
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
		{
			ThingTemplate *final = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
			if (final->m_isBuildFacility != 0)
				return true;
		}

		if (cur != 0)
			cur = (cur->*pfn)();
		else
			cur = 0;
	}

	return false;
}
