// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Retail 0x00257DB0 (817 bytes, through the final ret at +0x330).  Owner and
// method names are address-derived: the matched 98-byte Rva002581B0Owner::run
// (0x002581B0) empties its +0xE8 list and tail-jumps here through ILT
// 0x0003839D with the same `this`; no named caller or vtable slot is known.
// The body gathers object IDs near this+0xB0 into that list, then tops it up
// to data+0x264 entries by cycling the KINDOF 0x0A subset (or the whole list).
// Filter, result and PartitionManager views follow the matched sibling
// Rva0025ED50ChargeTargets.cpp (same owner layout: data +4, object +8).
// Template reads go through Zero Hour's OVERRIDE<ThingTemplate> with the
// recursive inline Overridable::getFinalOverride (one level inlined, the rest
// at ILT 0x000022BB); that spelling fixed the ebp/edi assignment of the loop.
// KindOf bits are tested raw; their enum names are not asserted.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
enum KindOfType { KINDOF_INVALID = -1 };
enum IterOrderType { ITER_FASTEST, ITER_SORTED_NEAR_TO_FAR, ITER_SORTED_FAR_TO_NEAR, ITER_SORTED_CHEAP_TO_EXPENSIVE, ITER_SORTED_EXPENSIVE_TO_CHEAP };

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(UnsignedInt)t >> 5] & (1 << ((UnsignedInt)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	UnsignedInt m_kindof[5];
};

template <class T> class OVERRIDE
{
public:
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	const T *operator*(void) const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	operator const T *() const
	{
		return operator*();
	}

	const T *m_overridable;
};

class Thing
{
public:
	const ThingTemplate *getTemplate(void) const;
	Bool isKindOf(KindOfType t) const;

private:
	virtual ~Thing();
	OVERRIDE<ThingTemplate> m_template;
};

inline const ThingTemplate *Thing::getTemplate(void) const
{
	return m_template;
}

class Object : public Thing
{
public:
	unsigned char m_08_to_74[0x74 - 0x08];
	ObjectID m_id;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int mode, Bool match)
		: m_obj(object), m_flags(mode), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva0025ED50ResultData *value;

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
public:
	BfmeWideResult iterate(const Coord3D *, Real, IterOrderType,
		PartitionFilter *, Bool);
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern PartitionManager *ThePartitionManager;

struct Rva00257DB0Data
{
	unsigned char m_00_to_258[0x258];
	Real m_range258;
	unsigned char m_25c_to_264[0x264 - 0x25C];
	UnsignedInt m_count264;
};

class Rva002581B0Owner
{
public:
	void callAt00257DB0();

	unsigned char m_00_to_04[0x04];
	Rva00257DB0Data *m_data;
	Object *m_object;
	unsigned char m_0c_to_b0[0xB0 - 0x0C];
	Coord3D m_positionB0;
	unsigned char m_bc_to_e8[0xE8 - 0xBC];
	_STL::list<int> m_ids;
};

void Rva002581B0Owner::callAt00257DB0()
{
	Object *object = m_object;
	Rva00257DB0Data *data = m_data;

	BfmeWideResult iterator = ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
		(int)&m_positionB0, *(int *)&data->m_range258, (int)ITER_FASTEST,
		(int)PartitionFilterRelationship(object, 1, false).link(
			Rva0025ED50RootFilter().link(&Rva0025ED50ObjectFilter(object))), 1);

	_STL::list<int> preferred;
	Object *other;
	while (iterator.next(other))
	{
		if (other->getTemplate()->isKindOf((KindOfType)0x67))
			continue;
		if (other->getTemplate()->isKindOf((KindOfType)0x58))
			continue;
		if (other->getTemplate()->isKindOf((KindOfType)0x2F))
			continue;
		if (other->getTemplate()->isKindOf((KindOfType)0x95))
			continue;
		if (other->getTemplate()->isKindOf((KindOfType)0x35))
			continue;
		if (other->isKindOf((KindOfType)0x85))
			continue;

		ObjectID id = other->m_id;
		m_ids.push_back(id);
		if (other->isKindOf((KindOfType)0x0A))
			preferred.push_back(other->m_id);
	}

	if (m_ids.size() != 0)
	{
		if (m_ids.size() < data->m_count264)
		{
			_STL::list<int> &source = preferred.empty() ? m_ids : preferred;
			_STL::list<int>::iterator it = source.begin();
			while (m_ids.size() < data->m_count264)
			{
				m_ids.push_back(*it);
				++it;
				if (it == source.end())
					it = source.begin();
			}
		}
		preferred.clear();
	}
}
