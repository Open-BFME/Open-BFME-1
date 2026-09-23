// ?rva002850A0@Rva002850A0@@QAEXXZ
// partial score=0.232 date=2026-09-23
// Address-derived method view; caller and receiver ABI are verified, owner is not.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmekindof /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/KindOf.h"

class Object;
class Player;
class FXList;

class Object
{
public:
	Player *getControllingPlayer(void) const;
	void *unidentified_001BFE20(void) const;
	void bfmeRefreshPartitionCells(void);
};

class FXList
{
public:
	static void doFXObj(const FXList *, const Object *, const Object *);
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

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	explicit PartitionFilterPlayerAffiliation(Player *player)
		: m_player(player), m_match(true), m_affiliation(2) {}
	virtual ~PartitionFilterPlayerAffiliation() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Player *m_player;
	Bool m_match;
	Int m_affiliation;
};

typedef BitFlags<192> Rva002850A0KindOfMask;

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const Rva002850A0KindOfMask &mustBeSet,
		const Rva002850A0KindOfMask &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	Rva002850A0KindOfMask m_mustBeSet;
	Rva002850A0KindOfMask m_mustBeClear;
};

struct Rva002850A0Entry
{
	Object *m_object;
	Real m_distance;
};

struct Rva002850A0Payload
{
	std::vector<Rva002850A0Entry> m_entries;
	Rva002850A0Entry *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	Rva002850A0Payload *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	~BfmeWideResult();
	Object *next(Object *&object)
	{
		if (value->m_cursor == value->m_entries.end())
			return 0;
		object = (value->m_cursor++)->m_object;
		return object;
	}
};

class BfmeWideForwardC
{
private:
	unsigned char m_pad[0x0C];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern BfmeWideForwardC *ThePartitionManager;

class Rva002850A0Interface
{
public:
#define RVA850A0_SLOT(n) virtual void slot##n(void) = 0
	RVA850A0_SLOT(00); RVA850A0_SLOT(01); RVA850A0_SLOT(02); RVA850A0_SLOT(03);
	RVA850A0_SLOT(04); RVA850A0_SLOT(05); RVA850A0_SLOT(06); RVA850A0_SLOT(07);
	RVA850A0_SLOT(08); RVA850A0_SLOT(09); RVA850A0_SLOT(10); RVA850A0_SLOT(11);
	RVA850A0_SLOT(12); RVA850A0_SLOT(13); RVA850A0_SLOT(14); RVA850A0_SLOT(15);
	RVA850A0_SLOT(16); RVA850A0_SLOT(17); RVA850A0_SLOT(18); RVA850A0_SLOT(19);
	RVA850A0_SLOT(20); RVA850A0_SLOT(21); RVA850A0_SLOT(22); RVA850A0_SLOT(23);
	RVA850A0_SLOT(24); RVA850A0_SLOT(25); RVA850A0_SLOT(26); RVA850A0_SLOT(27);
	RVA850A0_SLOT(28); RVA850A0_SLOT(29); RVA850A0_SLOT(30); RVA850A0_SLOT(31);
	RVA850A0_SLOT(32); RVA850A0_SLOT(33); RVA850A0_SLOT(34); RVA850A0_SLOT(35);
	RVA850A0_SLOT(36); RVA850A0_SLOT(37); RVA850A0_SLOT(38); RVA850A0_SLOT(39);
	RVA850A0_SLOT(40); RVA850A0_SLOT(41); RVA850A0_SLOT(42); RVA850A0_SLOT(43);
	RVA850A0_SLOT(44); RVA850A0_SLOT(45); RVA850A0_SLOT(46); RVA850A0_SLOT(47);
	RVA850A0_SLOT(48); RVA850A0_SLOT(49); RVA850A0_SLOT(50); RVA850A0_SLOT(51);
	RVA850A0_SLOT(52); RVA850A0_SLOT(53); RVA850A0_SLOT(54); RVA850A0_SLOT(55);
	RVA850A0_SLOT(56); RVA850A0_SLOT(57); RVA850A0_SLOT(58); RVA850A0_SLOT(59);
	RVA850A0_SLOT(60); RVA850A0_SLOT(61); RVA850A0_SLOT(62); RVA850A0_SLOT(63);
	RVA850A0_SLOT(64); RVA850A0_SLOT(65); RVA850A0_SLOT(66); RVA850A0_SLOT(67);
	RVA850A0_SLOT(68); RVA850A0_SLOT(69); RVA850A0_SLOT(70); RVA850A0_SLOT(71);
	RVA850A0_SLOT(72); RVA850A0_SLOT(73); RVA850A0_SLOT(74); RVA850A0_SLOT(75);
	RVA850A0_SLOT(76); RVA850A0_SLOT(77); RVA850A0_SLOT(78); RVA850A0_SLOT(79);
	RVA850A0_SLOT(80);
#undef RVA850A0_SLOT
	virtual void slot144(UnsignedInt) = 0;
	virtual UnsignedInt slot148(void) = 0;
	virtual UnsignedInt slot14c(void) = 0;
	virtual void slot150(void) = 0;
	virtual void slot154(void) = 0;
	virtual UnsignedInt slot158(void) = 0;
	virtual Object *slot15c(Object *) = 0;
};

struct Rva002850A0ModuleData
{
	unsigned char m_00_to34[0x34];
	FXList *m_effect;
	unsigned char m_38;
	Bool m_continue;
	unsigned char m_3a_to3c[2];
	UnsignedInt m_rangeBits;
};

class Rva002850A0
{
public:
	void rva002850A0(void);

private:
	void *m_vtable;
	Rva002850A0ModuleData *m_moduleData;
	Object *m_object;
};

void Rva002850A0::rva002850A0(void)
{
	Player *player = m_object->getControllingPlayer();
	if (player == 0)
		return;

	Rva002850A0ModuleData *moduleData = m_moduleData;
	PartitionFilterPlayerAffiliation playerFilter(player);
	Rva002850A0KindOfMask kindMask;
	kindMask.set(172);
	PartitionFilterAcceptByKindOf kindFilter(kindMask,
		*reinterpret_cast<const Rva002850A0KindOfMask *>(&KINDOFMASK_NONE));

	BfmeWideResult iterator = ((BfmeWideForwardC *)ThePartitionManager)->
		bfmeForwardWideC((int)((unsigned char *)m_object + 0x38),
			(int)moduleData->m_rangeBits, 0,
			(int)kindFilter.link(&playerFilter), 1);
	Object *candidate;
	while (iterator.next(candidate))
	{
		if ((*(const unsigned char *)((const char *)candidate + 0x90) & 4) != 0)
			continue;

		Rva002850A0Interface *interfaceView =
			(Rva002850A0Interface *)candidate->unidentified_001BFE20();
		if (interfaceView == 0)
			continue;

		const UnsignedInt first = interfaceView->slot14c();
		const UnsignedInt second = interfaceView->slot158();
		if (second >= first)
		{
			if (interfaceView->slot148() > 1)
				interfaceView->slot144(1);
			continue;
		}

		Object *updated = interfaceView->slot15c(
			(Object *)((unsigned char *)candidate + 8));
		if (updated != 0)
		{
			updated->bfmeRefreshPartitionCells();
			FXList *effect = moduleData->m_effect;
			if (effect != 0)
				FXList::doFXObj(effect, updated, 0);
		}
		if (!moduleData->m_continue)
			break;
	}
}
