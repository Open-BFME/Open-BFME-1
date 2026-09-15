// ?runAt00262570@Rva00262570Secondary@@UAEXI@Z
// partial score=0.25 date=2026-09-15
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmekindof /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
	void *, const void *, unsigned int);
#define memmove BfmeMemMove
#include <vector>
#undef memmove
#include "PreRTS.h"
#include "Common/KindOf.h"

class Object;
class Rva002622D0Subject;
typedef BitFlags<192> Rva00262570KindOfMask;

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

	template <>
	__declspec(noinline)
	_Vector_base<Rva002622D0Subject *,
		allocator<Rva002622D0Subject *> >::_Vector_base(
			size_t, const allocator<Rva002622D0Subject *> &);

	template <>
	__declspec(noinline) allocator<Rva002622D0Subject *>
	vector<Rva002622D0Subject *,
		allocator<Rva002622D0Subject *> >::get_allocator() const;
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
		const Rva00262570KindOfMask &mustBeSet,
		const Rva00262570KindOfMask &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	Rva00262570KindOfMask m_mustBeSet;
	Rva00262570KindOfMask m_mustBeClear;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
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
};

class PartitionManager
{
public:
	BfmeResultA iterateAllAt002622D0(PartitionFilter *filter);
};

extern PartitionManager *ThePartitionManager;

struct Rva002622D0Entry
{
	Object *object;
	std::vector<Rva002622D0Subject *> grouped;
};

typedef std::vector<Rva002622D0Entry> Rva002622D0Entries;

namespace _STL
{
	template <>
	vector<Rva002622D0Entry, allocator<Rva002622D0Entry> >::~vector();
}

class Rva002622D0Owner
{
public:
	Bool collectAt002622D0(Rva002622D0Entries *groups);

	unsigned char m_00_to_08[8];
	Object *m_object;
	unsigned char m_0c_to_10[4];
};

struct Rva00261F40Iterator
{
	Rva002622D0IterData *state;
};

class Rva00261F40Owner
{
public:
	void distribute(void *groups, Rva00261F40Iterator *iterator);
};

struct Rva00260E80Input
{
	Object *object;
	Rva002622D0Subject **begin;
	Rva002622D0Subject **end;
};

class Rva00260E80Owner
{
public:
	void apply(Rva00260E80Input &entry);
};

class Rva00262570Secondary
{
public:
	virtual void runAt00262570(UnsignedInt);
};

void Rva00262570Secondary::runAt00262570(UnsignedInt)
{
	Rva002622D0Entries groups;
	Rva002622D0Owner *primary = reinterpret_cast<Rva002622D0Owner *>(
		reinterpret_cast<unsigned char *>(this) - 0x10);
	if (primary->collectAt002622D0(&groups))
	{
		Object *object = *reinterpret_cast<Object **>(
			reinterpret_cast<unsigned char *>(this) - 8);
		BfmeResultA iterator =
			ThePartitionManager->iterateAllAt002622D0(
				PartitionFilterRelationship(object, 4, false)
					.link(&Rva0025ED50RootFilter())
					->link(Rva0025ED50ObjectFilter(object).link(
						&PartitionFilterAcceptByKindOf(
							Rva00262570KindOfMask(
								Rva00262570KindOfMask::kInit, 108),
							*reinterpret_cast<const Rva00262570KindOfMask *>(
								&KINDOFMASK_NONE)))));

		reinterpret_cast<Rva00261F40Owner *>(primary)->distribute(
			&groups, reinterpret_cast<Rva00261F40Iterator *>(&iterator));
		for (Rva002622D0Entries::iterator it = groups.begin();
			it != groups.end(); ++it)
		{
			Rva002622D0Entry local(*it);
			if (local.grouped.size() > 0)
				reinterpret_cast<Rva00260E80Owner *>(primary)->apply(
					*reinterpret_cast<Rva00260E80Input *>(&local));
		}
	}
}
