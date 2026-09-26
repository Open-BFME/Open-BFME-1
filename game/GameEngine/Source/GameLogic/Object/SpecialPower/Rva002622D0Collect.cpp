// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x002622D0..0x002624E4 is a 532-byte thiscall returning Bool with
// one output-vector pointer argument. The body reads its subject at this+8,
// enumerates objects accepted by KindOf 114 and relationship flags 4/false,
// and appends a 16-byte {Object*, vector<Object*>} entry for every non-null
// result. The complete constructor below independently matches the 102-byte
// body at 0x000C3DD0. Keeping that noinline body visible proves the mask
// references do not escape and recovers retail's 0x6C caller frame.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/KindOf.h"

class Object;
class Rva002622D0Subject;
typedef BitFlags<192> Rva002622D0KindOfMask;

__declspec(noinline) void *__cdecl bfmeNodeAllocateAt00061CE0(
	unsigned int bytes)
{
	return _STL::__node_alloc<true, 0>::allocate(bytes);
}

namespace _STL
{
	template <>
	inline Rva002622D0Subject **allocator<Rva002622D0Subject *>::allocate(
		size_type count, const void *) const
	{
		if (count != 0)
			return static_cast<Rva002622D0Subject **>(
				bfmeNodeAllocateAt00061CE0(
					count * sizeof(Rva002622D0Subject *)));
		return 0;
	}
}

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

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const Rva002622D0KindOfMask &mustBeSet,
		const Rva002622D0KindOfMask &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	Rva002622D0KindOfMask m_mustBeSet;
	Rva002622D0KindOfMask m_mustBeClear;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_object(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_object;
	Int m_flags;
	Bool m_match;
};

struct Rva002622D0IterEntry
{
	Object *object;
	UnsignedInt word04;
};

struct Rva002622D0IterData
{
	std::vector<Rva002622D0IterEntry> entries;
	Rva002622D0IterEntry *current;
	Int references;
};

struct BfmeResultA
{
	Rva002622D0IterData *value;

	BfmeResultA();
	BfmeResultA(const BfmeResultA &);
	~BfmeResultA()
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
	// Retail forwards this filter head through the manager's +0x0C source.
	BfmeResultA iterateAllAt002622D0(PartitionFilter *filter);
};

extern PartitionManager *ThePartitionManager;

struct Rva002622D0Entry
{
	Object *object;
	std::vector<Rva002622D0Subject *> grouped;

	__forceinline Rva002622D0Entry() : grouped() {}
	__forceinline Rva002622D0Entry(const Rva002622D0Entry &that)
		: object(that.object), grouped(that.grouped) {}
};

namespace _STL
{
	template <>
	__forceinline void _Construct<Rva002622D0Entry, Rva002622D0Entry>(
		Rva002622D0Entry *dest, const Rva002622D0Entry &source)
	{
		_STLP_PLACEMENT_NEW (dest) Rva002622D0Entry(source);
	}
}

typedef std::vector<Rva002622D0Entry> Rva002622D0Entries;

class Rva002622D0Owner
{
public:
	Bool collectAt002622D0(Rva002622D0Entries *out);

	unsigned char m_00_to_08[8];
	Object *m_object;
};

Bool Rva002622D0Owner::collectAt002622D0(Rva002622D0Entries *out)
{
	BfmeResultA iterator = ThePartitionManager->iterateAllAt002622D0(
			PartitionFilterRelationship(m_object, 4, false).link(
				&PartitionFilterAcceptByKindOf(
					Rva002622D0KindOfMask(
						Rva002622D0KindOfMask::kInit, 114),
					*reinterpret_cast<const Rva002622D0KindOfMask *>(
						&KINDOFMASK_NONE))));

	Object *other;
	while (iterator.next(other))
	{
		if (other != 0)
		{
			Rva002622D0Entry entry;
			entry.object = other;
			out->push_back(entry);
		}
	}

	return out->size() > 0;
}
