// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/objectdlink

#include "ObjectDlinkPmf.h"

// Retail ILT thunks these bodies route their calls through.
extern void j_00001140();
extern void j_000022bb();

class Rva000F4640Overridable
{
public:
	void *m_vtable;
	Rva000F4640Overridable *m_nextOverride;
};

class Rva000F4640ThingTemplate
{
public:
	unsigned char m_head[0xC8];
	unsigned int m_kindOf0;
};

class Rva000F4640ObjectTemplateView
{
public:
	void *m_vptr;
	Rva000F4640Overridable *m_template;
};

class Rva000F4640ObjectAiView
{
public:
	unsigned char m_head[0x204];
	void *m_ai;
};

class Rva000F4640ObjectDeadView
{
public:
	unsigned char m_head[0x344];
	unsigned char m_dead;
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class ObjectType>
class Rva000F4640DlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	Rva000F4640DlinkIterator(ObjectType *current, GetNextFunc getNext)
		: m_current(current), m_getNext(getNext) { }

	bool done() const { return m_current == 0; }
	ObjectType *current() const { return m_current; }

	void advance()
	{
		if (m_current)
			m_current = callMemberFunction(*m_current, m_getNext)();
	}

private:
	ObjectType *m_current;
	GetNextFunc m_getNext;
};

class Rva000F4640Team
{
public:
	int getTargetableCount() const;

private:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	Rva000F4640DlinkIterator<Object> iterateTeamMemberList() const
	{
		// Retail passes the {pfn, -100, 0} PMF of
		// Object::dlink_next_TeamMemberList, and calls it through the ILT
		// thunk at 0x00401140 (?j_00001140@@YAXXZ). The linker is the only
		// thing that can turn &BfmeObjectDlinkBase::dlink_next_TeamMemberList
		// into that thunk address: MSVC 7.1 folds the PMF to immediates only
		// for a compile-time `&Class::member` constant, so the stand-in name
		// has to stay mapped onto the thunk.
		return Rva000F4640DlinkIterator<Object>(m_head,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

// ?getTargetableCount@Rva000F4640Team@@QBEHXZ
int Rva000F4640Team::getTargetableCount() const
{
	int retVal = 0;
	for (Rva000F4640DlinkIterator<Object> iter = iterateTeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.current();
		if ((((Rva000F4640ObjectDeadView *)obj)->m_dead & 1) != 0)
			continue;

		if (((Rva000F4640ObjectAiView *)obj)->m_ai == 0)
		{
			Rva000F4640Overridable *raw =
				((Rva000F4640ObjectTemplateView *)obj)->m_template;
			if (raw != 0)
			{
				Rva000F4640Overridable *next = raw->m_nextOverride;
				if (next != 0)
				{
					// Retail walks the override chain through the ILT thunk at
					// 0x004022BB (?j_000022bb@@YAXXZ).
					typedef const Rva000F4640Overridable *(
						Rva000F4640Overridable::*GetFinal)() const;
					union { void (*fn)(); GetFinal call; } u = { j_000022bb };
					raw = (Rva000F4640Overridable *)(next->*u.call)();
				}
			}
			Rva000F4640ThingTemplate *tmpl =
				(Rva000F4640ThingTemplate *)raw;
			if ((tmpl->m_kindOf0 & 0x80) == 0)
				continue;
		}

		++retVal;
	}
	return retVal;
}

// Stand-in PMF name for the retail ILT thunk; see iterateTeamMemberList().
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
