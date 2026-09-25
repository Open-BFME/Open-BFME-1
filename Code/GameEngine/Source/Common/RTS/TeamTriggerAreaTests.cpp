// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink

// Every Team question that is answered by walking the member list and asking
// each member where it is relative to a trigger area:
//
//   0x000F5580  didAllEnter            265B  evaluateTeamEnteredAreaEntirely
//   0x000F56D0  didPartialEnter        191B  evaluateTeamEnteredAreaPartially
//   0x000F57C0  didPartialExit         191B  evaluateTeamExitedAreaPartially
//   0x000F58B0  didAllExit             297B  evaluateTeamExitedAreaEntirely
//   0x000F5A30  allInside              278B  evaluateTeamInsideAreaEntirely
//   0x000F5B90  noneInside             259B  ZH sibling between the two above
//   0x000F5CE0  someInsideSomeOutside  276B  evaluateTeamInsideAreaPartially
//
// This is the callee side of ScriptConditionsTriggerAreas.cpp: that file holds
// the six conditions, this one holds the six Team bodies they call. All six
// walk the member list through the same Object DLINK pointer-to-member and open
// with the same member filter -- the locomotor-surface test against AI+0x1B8
// (or the GROUND bit alone when Object+0x204 is null), then the dead bit at
// Object+0x344, then a re-walk of the template at Object+0x04 through the
// Overridable final-override ILT.
//
// They sat in four files, each carrying its own DLINK_ITERATOR, Overridable,
// ThingTemplate, object views and bfmeFinalTemplate -- and its own Team.
//
// The Team copies had drifted in the way that matters here: three of the four
// knew the entered-or-exited guard at Team+0x30 and one did not, because the
// three bodies that read it happened to live together and the three that do
// not happened to live apart. One layout states the member list head at +0x0C
// and the guard at +0x30 together.
//
// One thing this file does NOT carry is a locoSetMatches helper. The
// inside-queries donor defined one and nothing ever called it: all six bodies
// inline the surface-flag expression against AI+0x1B8 the way retail does, so
// the helper was a spare description of the expression rather than the
// expression itself. Merged, six bodies sit beside it and none uses it, which
// is how it became visible at all.
//
// The filter is NOT factored into a helper, because it is not one filter. The
// four entirely-bodies apply both KindOf skips -- the dword at +0xD0 bit
// 0x01000000 and then the byte at +0xD8 bit 0x20 -- while the two partial
// bodies apply only the first. Sharing the models is safe; sharing the filter
// would have quietly given two bodies a skip retail does not perform.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

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

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

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
	Overridable *m_template;					// Object+0x04
};

class BfmeObjectInsideView
{
public:
	unsigned char m_head[0x204];
	void *m_ai;							// +0x204
	unsigned char m_mid[0x344 - 0x208];
	unsigned char m_dead;						// +0x344, bit 0

	Bool didEnter(class PolygonTrigger *pTrigger) const;
	Bool didExit(class PolygonTrigger *pTrigger) const;
	Bool isInside(class PolygonTrigger *pTrigger) const;		// ILT 0x0000D6ED
};

class BfmeAISurfacesView
{
public:
	unsigned char m_head[0x1B8];
	UnsignedInt m_surfaces;					// AI+0x1B8
};

class ThingTemplate
{
public:
	unsigned char m_head[0xD0];
	UnsignedInt m_kindOf2;						// +0xD0
	UnsignedInt m_kindOf3;						// +0xD4
	unsigned char m_kindOf4;					// +0xD8
};

class PolygonTrigger;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyObjects(Bool bfmeFlag) const;
	Bool didPartialEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didPartialExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didAllEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool allInside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool noneInside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool someInsideSomeOutside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;							// +0x0C
	unsigned char m_mid[0x30 - 0x10];
	Bool m_enteredOrExited;					// +0x30

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

static Overridable *bfmeFinalTemplate(Object *obj)
{
	Overridable *tmpl = ((BfmeObjectTemplateView *)obj)->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (Overridable *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

// ?didPartialEnter@Team@@QBE_NPAVPolygonTrigger@@I@Z
Bool Team::didPartialEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	if (!m_enteredOrExited)
		return false;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *cur = iter.cur();
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		if (((BfmeObjectInsideView *)cur)->didEnter(pTrigger))
			return true;
	}
	return false;
}

// ?didPartialExit@Team@@QBE_NPAVPolygonTrigger@@I@Z
Bool Team::didPartialExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	if (!m_enteredOrExited)
		return false;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *cur = iter.cur();
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		if (((BfmeObjectInsideView *)cur)->didExit(pTrigger))
			return true;
	}
	return false;
}

// ?didAllEnter@Team@@QBE_NPAVPolygonTrigger@@I@Z
// Zero Hour's body as written: any member that entered, and none still
// outside. Like the partial bodies it applies only the first KindOf skip.
Bool Team::didAllEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	if (!m_enteredOrExited)
		return false;

	Bool entered = false;
	Bool outside = false;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *cur = iter.cur();
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		if (((BfmeObjectInsideView *)cur)->didEnter(pTrigger))
			entered = true;
		else if (!((BfmeObjectInsideView *)cur)->isInside(pTrigger))
			outside = true;
	}

	return entered && !outside;
}

// ?didAllExit@Team@@QBE_NPAVPolygonTrigger@@I@Z
Bool Team::didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	if (!m_enteredOrExited)
		return false;

	Bool anyConsidered = false;
	Bool exited = false;
	Bool inside = false;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *cur = iter.cur();
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf4 & 0x20) != 0)
			continue;

		if (((BfmeObjectInsideView *)cur)->didExit(pTrigger))
			exited = true;
		else if (((BfmeObjectInsideView *)cur)->isInside(pTrigger))
			inside = true;
		anyConsidered = true;
	}
	return anyConsidered && exited && !inside;
}

// ?allInside@Team@@QBE_NPAVPolygonTrigger@@I@Z
Bool Team::allInside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	if (!hasAnyObjects(false))
		return false;

	Bool anyConsidered = false;
	Bool anyOutside = false;
	Object *cur = m_head;
	BfmeGetNextTeamMemberFunc getNext = Object::dlink_next_TeamMemberList;
	for (; cur != 0; cur = (cur->*getNext)())
	{
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf4 & 0x20) != 0)
			continue;

		if (!((BfmeObjectInsideView *)cur)->isInside(pTrigger))
			anyOutside = true;
		anyConsidered = true;
	}
	return anyConsidered && !anyOutside;
}

// ?noneInside@Team@@QBE_NPAVPolygonTrigger@@I@Z
Bool Team::noneInside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	Bool anyConsidered = false;
	Bool anyInside = false;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *cur = iter.cur();
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf4 & 0x20) != 0)
			continue;

		if (((BfmeObjectInsideView *)cur)->isInside(pTrigger))
			anyInside = true;
		anyConsidered = true;
	}
	return anyConsidered && !anyInside;
}

// ?someInsideSomeOutside@Team@@QBE_NPAVPolygonTrigger@@I@Z
Bool Team::someInsideSomeOutside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const
{
	Bool anyConsidered = false;
	Bool anyInside = false;
	Bool anyOutside = false;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *cur = iter.cur();
		void *ai = ((BfmeObjectInsideView *)cur)->m_ai;
		if (ai)
		{
			if ((((BfmeAISurfacesView *)ai)->m_surfaces
				& ((whichToConsider & 1) | ((whichToConsider & 2) << 2))) == 0)
				continue;
		}
		else if ((whichToConsider & 1) == 0)
			continue;

		if ((((BfmeObjectInsideView *)cur)->m_dead & 1) != 0)
			continue;

		ThingTemplate *tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf2 & 0x01000000) != 0)
			continue;

		tmpl = (ThingTemplate *)bfmeFinalTemplate(cur);
		if ((tmpl->m_kindOf4 & 0x20) != 0)
			continue;

		if (((BfmeObjectInsideView *)cur)->isInside(pTrigger))
			anyInside = true;
		else
			anyOutside = true;
		anyConsidered = true;
	}
	return anyConsidered && anyInside && anyOutside;
}
