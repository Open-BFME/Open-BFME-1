// ?doSpecialPower@ManTheWallsSpecialPower@@EAEXI@Z
// partial score=0.2949 date=2026-11-12
// cl: /DNDEBUG /MD /EHsc
// stlport
// ManTheWallsSpecialPower::doSpecialPower(UnsignedInt), retail 0x00262570,
// full extent 630 B (RET 4 at +0x273; the 624 B dump row cuts ADD ESP).
// Identity: matched ctor 0x00260600 installs table 0x010B5D30 at primary+0x10;
// slot 11 -> ILT 0x000197EA -> this body; ilt_oracle Oracle.check CONFIRMS
// ?doSpecialPower@ManTheWallsSpecialPower@@EAEXI@Z (private virtual) and
// contradicts UAE/MAE/QAE/AAE/IAE and the int-argument spelling.
// Shape: Open BFME 2 donor ManTheWallsSpecialPower.cpp doSpecialPower (76f0baefa6).
// State 2026-11-12: 618/630 B, 428 nonreloc diffs, shape 0.973, frame 0x88 vs 0x8C.
// Levers that worked: real class, override in the secondary interface;
// `extern template` for the _Vector_base<Rva002622D0Subject*> ctor
// (get_allocator-then-size order); a visible __declspec(noinline)
// PartitionFilterAcceptByKindOf ctor so VC7.1 reuses the mask temporary's
// slot for the relationship filter (shape_levers.md, filter construction).
// Residue: retail keeps the primary pointer in EDI with a home at
// [esp+0x38] (the missing 4 frame bytes), reloads it for apply(), pushes EBP
// only at the loop for the iterator, and keeps the copied vector's start in
// EDI across memmove; ours keeps primary in EBP and the iterator in EDI.
// Retail also aligns the loop head (jmp + lea ebx,[ebx]).
// Inert: named primary local before/after entries, members on the class,
// iterator scope/form, loop spellings, visible _Vector_base/get_allocator,
// mask helpers, compiler switches. The novtable mask-wrapper also gives the
// 0x8C frame but loses the ctor's EAX return (393 diffs, shape 0.934).
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Rva002622D0Subject;

namespace _STL
{
	extern template _Vector_base<Rva002622D0Subject *, allocator<Rva002622D0Subject *> >::_Vector_base(
		unsigned int, const allocator<Rva002622D0Subject *> &);
}

template <int N> class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, Int bit)
	{
		for (Int i = 0; i < (N + 31) / 32; ++i)
			m_bits[i] = 0;
		m_bits[bit >> 5] |= 1u << (bit & 31);
	}
	UnsignedInt m_bits[(N + 31) / 32];
};
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

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
	__declspec(noinline) PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
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

struct BfmeResultEntry
{
	Object *m_object;
	UnsignedInt word04;
};

struct BfmeResultData
{
	std::vector<BfmeResultEntry> m_entries;
	BfmeResultEntry *m_current;
	Int m_references;
};

struct BfmeResultA
{
	BfmeResultData *value;
	BfmeResultA();
	BfmeResultA(const BfmeResultA &that);
	~BfmeResultA()
	{
		if (--value->m_references == 0)
			delete value;
	}
};

class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(Int filter);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

struct Gen00261FC0Elem
{
	Object *m_object;
	std::vector<Rva002622D0Subject *> m_members;
};

namespace _STL
{
	template <>
	vector<Gen00261FC0Elem, allocator<Gen00261FC0Elem> >::~vector();
}

struct Rva002622D0Entry;
class Rva002622D0Owner
{
public:
	Bool collectAt002622D0(std::vector<Rva002622D0Entry> *groups);
};

struct Rva00261F40Iterator;
class Rva00261F40Owner
{
public:
	void distribute(void *groups, Rva00261F40Iterator *iterator);
};

struct Rva00260E80Input;
class Rva00260E80Owner
{
public:
	void apply(Rva00260E80Input &entry);
};

template <int N> class ManTheWallsSlots : public ManTheWallsSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};
template <> class ManTheWallsSlots<0> {};

class SpecialPowerModuleInterface : public ManTheWallsSlots<11>
{
private:
	virtual void doSpecialPower(UnsignedInt commandOptions) = 0;	// slot 11
};

class ManTheWallsSpecialPowerPrimary
{
public:
	virtual void primarySlot0();
	void *m_moduleData;
	Object *m_object;
	UnsignedInt m_word0C;
};

class ManTheWallsSpecialPower : public ManTheWallsSpecialPowerPrimary, public SpecialPowerModuleInterface
{
private:
	virtual void doSpecialPower(UnsignedInt commandOptions);
};

void ManTheWallsSpecialPower::doSpecialPower(UnsignedInt commandOptions)
{
	std::vector<Gen00261FC0Elem> entries;
	if (((Rva002622D0Owner *)this)->collectAt002622D0((std::vector<Rva002622D0Entry> *)&entries))
	{
		Object *object = m_object;
		BfmeResultA hits = ((BfmeResultForwardB *)ThePartitionManager)->bfmeForwardResultB((Int)
			PartitionFilterRelationship(object, 4, false).link(&Rva0025ED50RootFilter())->link(
				Rva0025ED50ObjectFilter(object).link(&PartitionFilterAcceptByKindOf(
					KindOfMaskType(KindOfMaskType::kInit, 108), KINDOFMASK_NONE))));
		((Rva00261F40Owner *)this)->distribute(&entries, (Rva00261F40Iterator *)&hits);
		for (Gen00261FC0Elem *it = entries.begin(); it != entries.end(); ++it)
		{
			Gen00261FC0Elem entry(*it);
			if (entry.m_members.size() > 0)
				((Rva00260E80Owner *)this)->apply(*(Rva00260E80Input *)&entry);
		}
	}
}
