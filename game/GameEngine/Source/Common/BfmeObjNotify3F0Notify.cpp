// ?notify@BfmeObjNotify3F0@@QAEXPAXH@Z
// Both byte-matched callers in BfmeConv830.cpp pass this method a name and flags 0 or 1.
// The pin at ILT 0x259FA and its consistent route to 0xD22A0 confirm the method identity and extent.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs- /EHc- /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source
// stlport

#include <list>
#include "ascii_string.h"
typedef bool Bool;
enum ObjectScriptStatusBit { OBJECT_STATUS_SCRIPT_DISABLED = 0x01 };
#define OBJECT_TU_MEMBERS void setScriptStatus(ObjectScriptStatusBit status, Bool value);
#include "GameLogic/Object/object.h"

typedef int Int;
typedef bool Bool;

#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ=?j_00022a70@@YAXXZ")

class BfmeObjNotify3F0
{
public:
	void notify(void *param, int flag);
};

class Rva000D22A0TeamPrototypeView;

typedef std::list<Rva000D22A0TeamPrototypeView *> Rva000D22A0TeamPrototypeList;

struct Rva000D22A0OwnerView
{
	unsigned char m_unreconstructed_000[0x288];
	Rva000D22A0TeamPrototypeList m_playerTeamPrototypes;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class Rva000D22A0ObjectView;

typedef Rva000D22A0ObjectView *(__fastcall *Rva000D22A0ObjectDlinkNext)(Rva000D22A0ObjectView *);

struct Rva000D22A0ObjectDlinkPmf
{
	Rva000D22A0ObjectDlinkNext pfn;
	int delta;
	int vbindex;
};

extern void j_00001140(void);

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class Rva000D22A0ThingTemplateView : public Overridable
{
public:
	unsigned char m_unmodelled_008[0x20 - 0x08];
	AsciiString m_name;

	const AsciiString &getName() const { return m_name; }
};

template <class T>
class Rva000D22A0OverrideView
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}

	const T *m_overridable;
};

class Rva000D22A0ObjectView : public Object
{
public:
	const Rva000D22A0ThingTemplateView *getTemplate() const
	{
		return ((Rva000D22A0OverrideView<Rva000D22A0ThingTemplateView> *)&m_template)->operator->();
	}
};

class Rva000D22A0TeamView
{
public:
	unsigned char m_unmodelled_000[0x0c];
	Rva000D22A0ObjectView *m_head;
};

struct Rva000D22A0TeamPrototypeView
{
	unsigned char m_unmodelled_000[0x274];
	Rva000D22A0TeamView *m_teamInstanceList;
};

class Rva000D22A0TeamInstanceIterator
{
public:
	Rva000D22A0TeamInstanceIterator(Rva000D22A0TeamView *cur) : m_cur(cur) {}

	Bool done() const { return m_cur == NULL; }
	Rva000D22A0TeamView *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (Rva000D22A0TeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	Rva000D22A0TeamView *m_cur;
	Int m_unmodelled;
};

template <class ObjectType> class Rva000D22A0ObjectDlinkIterator
{
public:
	Rva000D22A0ObjectDlinkIterator(ObjectType *cur, Rva000D22A0ObjectDlinkPmf getNext)
		: m_cur(cur), m_getNext(getNext) {}

	Bool done() const { return m_cur == NULL; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		ObjectType *object = m_cur;
		if (!object)
			return;
		int vbindex = m_getNext.vbindex;
		char *vbptr = *(char **)((char *)object + 0x68);
		char *adjusted = (char *)object + 0x68;
		adjusted += *(int *)(vbptr + vbindex);
		adjusted += m_getNext.delta;
		m_cur = m_getNext.pfn((ObjectType *)adjusted);
	}

private:
	ObjectType *m_cur;
	int m_padding;
	Rva000D22A0ObjectDlinkPmf m_getNext;
	int m_tailPadding;
};

void BfmeObjNotify3F0::notify(void *param, int flag)
{
	Rva000D22A0OwnerView *self = (Rva000D22A0OwnerView *)this;
	for (Rva000D22A0TeamPrototypeList::iterator it = self->m_playerTeamPrototypes.begin();
			it != self->m_playerTeamPrototypes.end(); ++it)
	{
		Rva000D22A0TeamPrototypeView *prototype =
			(Rva000D22A0TeamPrototypeView *)*it;
		for (Rva000D22A0TeamInstanceIterator iter(prototype->m_teamInstanceList);
				!iter.done(); iter.advance())
		{
			Rva000D22A0TeamView *team = iter.cur();
			if (!team)
				continue;

			Rva000D22A0ObjectDlinkPmf pmf = {(Rva000D22A0ObjectDlinkNext)j_00001140, -100, 0};
			Rva000D22A0ObjectDlinkIterator<Rva000D22A0ObjectView> iterObj(team->m_head, pmf);
			for (; !iterObj.done(); iterObj.advance())
			{
				Rva000D22A0ObjectView *obj = iterObj.cur();
				if (!obj)
					continue;

				const Rva000D22A0ThingTemplateView *thingTemplate = obj->getTemplate();

				if (thingTemplate->getName().compare(*(AsciiString *)param) == 0)
					obj->setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, (Bool)(*(unsigned char *)&flag == 0));
			}
		}
	}
}
