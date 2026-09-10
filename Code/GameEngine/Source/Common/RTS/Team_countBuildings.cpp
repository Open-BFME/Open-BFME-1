// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// ?countBuildings@Team@@QAEHXZ
// BFME Team::countBuildings at retail RVA 0x000F4900, 103 bytes.
//
// The matched TeamPrototype::countBuildings caller at 0x000F6F90 establishes
// this member identity.  The Object DLINK siblings use the same BFME
// virtual-base-adjusted pointer-to-member representation, so this TU keeps
// the object and team views local rather than changing the shared headers.

#include "ObjectDlinkPmf.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate
	: public Overridable
{
public:
	unsigned char m_head[0xC0];
	unsigned int m_kindOf0;
};

template <class TemplateType>
class BfmeOverride
{
public:
	const TemplateType *operator->() const
	{
		const TemplateType *value = m_overridable;
		if (value != 0 && value->m_nextOverride != 0)
			value = (const TemplateType *)value->m_nextOverride->getFinalOverride();
		return value;
	}

	const TemplateType *volatile m_overridable;
};

class BfmeObjectTemplateView
{
public:
	void *m_vptr;
	BfmeOverride<ThingTemplate> m_template;

	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}
};

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

	bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return (ObjectType *)m_cur; }

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

class Team
{
public:
	int countBuildings();

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

int Team::countBuildings()
{
	int retVal = 0;

	for (BfmeDlinkIterator<Object> iter = iterate_TeamMemberList();
			 !iter.done(); iter.advance())
	{
		const ThingTemplate *tmpl =
			((BfmeObjectTemplateView *)iter.cur())->getTemplate();
		if (tmpl == 0)
			continue;
		if ((tmpl->m_kindOf0 & (1u << 7)) != 0)
			++retVal;
	}

	return retVal;
}
