// ??0Rva003DB640Info@@QAE@PAVPathfinder@@PAVObject@@H@Z
// partial score=0.7345 date=2026-11-01
// cl: /DNDEBUG /MD
typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;

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
	unsigned char m_pad08[0x444 - 0x08];
	Int m_field444;
	unsigned char m_pad448[0x4CC - 0x448];
	char m_field4CC;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (m_template == 0)
			return 0;
		if (m_template->m_nextOverride)
			return (const ThingTemplate *)m_template->m_nextOverride->getFinalOverride();
		return m_template;
	}
	Bool bfmeIsComputerControlled() const;

	void *m_vtable;
	const ThingTemplate *m_template;
};

class Pathfinder;

struct Rva003DB640Query
{
	unsigned int m_surfaces;
	unsigned char m_flag0;
	unsigned char m_flag1;
	unsigned char m_pad06[2];
	Int m_radius;

	void set(unsigned int surfaces, char flag, Bool computer, Int maxLayer)
	{
		m_surfaces = surfaces;
		m_flag0 = flag == 0;
		m_flag1 = computer;
		m_radius = maxLayer - 1;
	}
};

class Rva003DB640Info
{
public:
	Rva003DB640Info(Pathfinder *pathfinder, Object *object, Int validSurfaces);

	Pathfinder *m_pathfinder;
	Object *m_object;
	Int m_at08;
	Int m_at0C;
	Int m_at10;
	Int m_at14;
	Bool m_at18;
	Bool m_at19;
	Int m_at1C;
	Int m_at20;
	Rva003DB640Query m_current;
	Int m_at30;
	Bool m_at34;
	Bool m_at35;
	Bool m_at36;
	Int m_at38;
	Rva003DB640Query m_query;
	Int m_at48;
	Int m_at4C;
};

Rva003DB640Info::Rva003DB640Info(Pathfinder *pathfinder, Object *object, Int validSurfaces)
{
	m_pathfinder = pathfinder;
	m_object = object;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
	m_at14 = 0;
	m_at18 = false;
	m_at19 = false;
	m_at1C = 0;
	m_at20 = 0;
	m_current.m_surfaces = 0;
	m_current.m_flag0 = false;
	m_current.m_flag1 = false;
	m_current.m_radius = -1;
	m_at30 = 0;
	m_at35 = false;
	m_at36 = false;
	m_at34 = false;
	m_at38 = 0;
	Int radius = object->getTemplate()->m_field444;
	char flag = object->getTemplate()->m_field4CC;
	m_query.set(validSurfaces, flag, object->bfmeIsComputerControlled(), radius);
	m_at48 = 0;
	m_at4C = 0;
	const Rva003DB640Query &q = m_query;
	Rva003DB640Query &c = m_current;
	c = q;
	m_at19 = false;
	m_at20 = 0;
	m_at14 = 0;
	m_at1C = 12;
	m_at18 = true;
}
