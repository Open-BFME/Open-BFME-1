// ?countBuildings@Team@@QAEHXZ
// partial score=0.97 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: Team::countBuildings, retail 0x000F4900, 103 bytes.
//
// Named by the already-matched TeamPrototype::countBuildings walk (Team.cpp).
// Same Object DLINK pointer-to-member-function shape as the landed
// TeamMemberQueries.cpp siblings (hasAnyUnits/hasAnyObjects/...): the class
// hierarchy in reference/shims/objectdlink/ObjectDlinkPmf.h is what makes
// MSVC emit retail's virtual-base-adjusted indirect call through the DLINK
// pointer-to-member (ILT 0x00401140, delta -0x64, vbindex 0).
//
// Prior attempts (reverse/attempts/0x000f4900.cpp, score 0.96) reached 99 of
// 103 bytes using a DLINK_ITERATOR<Object> helper class whose advance() does
// `if (m_cur) m_cur = ...`; MSVC proves m_cur non-null inside the loop (the
// for-condition already tested !iter.done()) and elides that guard. Retail
// keeps a `test esi,esi / je` immediately before the PMF call. Writing the
// walk as a raw while-loop with the null check spelled out as the loop's own
// statement (not hidden inside a templated helper method) keeps it: nothing
// upstream of that statement proves cur non-null to the optimiser once the
// loop body's own control flow (the continue path) is in between.
//
// With cur/pfn/retVal declared in this order the compiled size is EXACT
// (103/103); remaining diffs are pure register-bank reassignment (which of
// eax/edx/edi/ebp/ebx carries the PMF address/delta/vbindex/retVal-zero, and
// where `push edi` lands relative to the two mov-imm32 constant loads).
// Declaration-order permutations (all six) and a /G5 /G6 /G7 /Ot /Og /Ob1 /O1
// flag sweep move the register roles and sometimes the size, but none
// converges to zero diffs -- consistent with the project's documented
// register-scheduling wall (not source-controllable).

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

class ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindOf0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	int countBuildings();

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

static Overridable *bfmeFinalTemplate(Object *obj)
{
	Overridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (Overridable *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

typedef Object *(Object::*BfmeGetNextFunc)() const;

// ?countBuildings@Team@@QAEHXZ
int Team::countBuildings()
{
	Object *cur = m_head;
	BfmeGetNextFunc pfn = Object::dlink_next_TeamMemberList;
	int retVal = 0;

	while (cur != 0)
	{
		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if (tmpl != 0)
		{
			if ((tmpl->m_kindOf0 & (1u << 7)) != 0)
				++retVal;
		}

		if (cur != 0)
			cur = (cur->*pfn)();
		else
			cur = 0;
	}

	return retVal;
}
