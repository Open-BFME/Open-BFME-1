// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink
// ?hasAnyBuildFacility@Team@@QBE_NXZ

#include "ObjectDlinkPmf.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_head[0x47e];
	unsigned char m_isBuildFacility;

	bool isBuildFacility() const { return m_isBuildFacility; }
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
	bool hasAnyBuildFacility() const;

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

bool Team::hasAnyBuildFacility() const
{
	for (BfmeDlinkIterator<Object> iter = iterate_TeamMemberList();
				 !iter.done(); iter.advance())
	{
		const ThingTemplate *tmpl = ((BfmeObjectTemplateView *)iter.cur())->getTemplate();
		if (tmpl->isBuildFacility())
			return true;
	}
	return false;
}
