// ?method@Rva00257DB0Owner@@QAEXXZ
// partial score=0.39 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include <stddef.h>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int ObjectID;
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_RVA00257DB0_A = 0x0a,
	KINDOF_RVA00257DB0_85 = 0x85
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08_to_cc[0xcc - 0x08];
	Int m_kindCC;
	UnsignedInt m_kindD0;
	signed char m_kindD4;
	unsigned char m_padD5_to_d8[3];
	UnsignedInt m_kindD8;
};

class Thing
{
public:
	void *m_vptr;
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	const ThingTemplate *m_template;
	unsigned char m_pad08_to_74[0x74 - 0x08];
	ObjectID m_id;

	const ThingTemplate *resolveTemplate() const
	{
		const ThingTemplate *d = m_template;
		const ThingTemplate *f;
		if (d == 0)
			f = d;
		else
			f = (const ThingTemplate *)(d->m_nextOverride
				? d->m_nextOverride->getFinalOverride()
				: d);
		return f;
	}
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);
	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

struct Rva00257DB0Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva00257DB0ResultData
{
	std::vector<Rva00257DB0Entry> entries;
	Rva00257DB0Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva00257DB0ResultData *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class PartitionManager
{
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern PartitionManager *ThePartitionManager;

struct Rva00257DB0Data
{
	unsigned char m_pad00_to_258[0x258];
	Real m_queryRadius;
	unsigned char m_pad25c_to_264[0x264 - 0x25c];
	UnsignedInt m_maxCount;
};

class Rva00257DB0Owner
{
public:
	void method();
	void *m_vptr;
	Rva00257DB0Data *m_data;
	Object *m_object;
	unsigned char m_pad0c_to_b0[0xb0 - 0x0c];
	Coord3D m_position;
	unsigned char m_padbc_to_e8[0xe8 - 0xbc];
	_STL::list<ObjectID> m_ids;
};

typedef char Rva00257DB0ListSizeCheck[(sizeof(_STL::list<ObjectID>) == 4) ? 1 : -1];

typedef char Rva00257DB0TemplateD0Check[(offsetof(ThingTemplate, m_kindD0) == 0xd0) ? 1 : -1];
typedef char Rva00257DB0TemplateD8Check[(offsetof(ThingTemplate, m_kindD8) == 0xd8) ? 1 : -1];
typedef char Rva00257DB0OwnerListCheck[(offsetof(Rva00257DB0Owner, m_ids) == 0xe8) ? 1 : -1];

void Rva00257DB0Owner::method()
{
	Rva00257DB0Data *data = m_data;
	Object *object = m_object;
	int radiusBits = *(const int *)&data->m_queryRadius;
	BfmeWideResult iterator =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(int)&m_position, radiusBits, 0,
			(int)PartitionFilterRelationship(object, 1, false).link(
				Rva0025ED50RootFilter().link(
					&Rva0025ED50ObjectFilter(object))),
			1);

	_STL::list<int> preferredIds;
	Object *other;
	while (iterator.next(other))
	{
		if ((other->resolveTemplate()->m_kindD4 & 0x80) != 0)
			continue;
		if ((other->resolveTemplate()->m_kindD0 & 0x01000000) != 0)
			continue;
		if (other->resolveTemplate()->m_kindCC < 0)
			continue;
		if ((other->resolveTemplate()->m_kindD8 & 0x00200000) != 0)
			continue;
		if ((other->resolveTemplate()->m_kindCC & 0x00200000) != 0)
			continue;
		if (other->isKindOf(KINDOF_RVA00257DB0_85))
			continue;

		ObjectID id = other->m_id;
		m_ids.push_back(id);
		if (other->isKindOf(KINDOF_RVA00257DB0_A))
			preferredIds.push_back((int)id);
	}

	UnsignedInt count = 0;
	for (_STL::list<ObjectID>::iterator it = m_ids.begin(); it != m_ids.end(); ++it)
		++count;
	if (count < data->m_maxCount)
	{
		for (_STL::list<int>::iterator it = preferredIds.begin();
			it != preferredIds.end() && count < data->m_maxCount; ++it)
		{
			m_ids.push_back(*it);
			++count;
		}
	}
}
