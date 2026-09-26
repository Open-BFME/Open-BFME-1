// Retail RVA 0x0025AEE0..0x0025B1E9 (777 bytes).
// Primary DominateEnemySpecialPower vtable slot 15; incoming this has no args.
// Constructor 0x0025ACF0 and destructor 0x0025AD50 install primary table
// VA 0x010B49F8; slot 15 reaches this body through ILT 0x0001F276.
// The original method name is unknown. The final byte is plain RET.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/BitFlags.h"
#include "Common/KindOf.h"
#include "Common/Overridable.h"
#include "GameLogic/ObjectIter.h"

class Object;
class Player;
class FXList;
enum ObjectID;
typedef BitFlags<86> Rva0025AEE0ObjectStatusMask;
typedef char Rva0025AEE0StatusMaskSizeCheck[
	(sizeof(Rva0025AEE0ObjectStatusMask) == 12) ? 1 : -1];

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

class PartitionFilterRejectByObjectStatus : public PartitionFilter
{
public:
	PartitionFilterRejectByObjectStatus(
		const Rva0025AEE0ObjectStatusMask &mustSet,
		const Rva0025AEE0ObjectStatusMask &mustClear)
		: m_mustSet(mustSet), m_mustClear(mustClear) {}
	virtual ~PartitionFilterRejectByObjectStatus() {}
	virtual Bool allow(Object *);
	Rva0025AEE0ObjectStatusMask m_mustSet;
	Rva0025AEE0ObjectStatusMask m_mustClear;
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
		: m_object(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	Object *m_object;
	Int m_flags;
	Bool m_match;
};

struct Rva0025AEE0IterEntry { Object *object; UnsignedInt word04; };
struct Rva0025AEE0IterData
{
	std::vector<Rva0025AEE0IterEntry> entries;
	Rva0025AEE0IterEntry *current;
	Int references;
};
struct Rva0025AEE0OwningIterator
{
	Rva0025AEE0IterData *value;
	Rva0025AEE0OwningIterator();
	Rva0025AEE0OwningIterator(const Rva0025AEE0OwningIterator &);
	~Rva0025AEE0OwningIterator()
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
	Rva0025AEE0OwningIterator iterateAt0025AEE0(
		const Coord3D *, Real, IterOrderType, PartitionFilter *, Bool);
};
extern PartitionManager *ThePartitionManager;

class BfmeControlBarOverridable
{
public:
	const BfmeControlBarOverridable *getFinalOverride() const;
};
class ThingTemplate : public Overridable {};

class Rva001CF980Result
{
#define RVA0025AEE0_RESULT_SLOT(N) virtual void rvaSlot##N();
	RVA0025AEE0_RESULT_SLOT(000) RVA0025AEE0_RESULT_SLOT(001)
	RVA0025AEE0_RESULT_SLOT(002) RVA0025AEE0_RESULT_SLOT(003)
	RVA0025AEE0_RESULT_SLOT(004) RVA0025AEE0_RESULT_SLOT(005)
	RVA0025AEE0_RESULT_SLOT(006) RVA0025AEE0_RESULT_SLOT(007)
	RVA0025AEE0_RESULT_SLOT(008) RVA0025AEE0_RESULT_SLOT(009)
	RVA0025AEE0_RESULT_SLOT(010) RVA0025AEE0_RESULT_SLOT(011)
	RVA0025AEE0_RESULT_SLOT(012) RVA0025AEE0_RESULT_SLOT(013)
	RVA0025AEE0_RESULT_SLOT(014) RVA0025AEE0_RESULT_SLOT(015)
	RVA0025AEE0_RESULT_SLOT(016) RVA0025AEE0_RESULT_SLOT(017)
	RVA0025AEE0_RESULT_SLOT(018) RVA0025AEE0_RESULT_SLOT(019)
	RVA0025AEE0_RESULT_SLOT(020) RVA0025AEE0_RESULT_SLOT(021)
	RVA0025AEE0_RESULT_SLOT(022) RVA0025AEE0_RESULT_SLOT(023)
	RVA0025AEE0_RESULT_SLOT(024) RVA0025AEE0_RESULT_SLOT(025)
	RVA0025AEE0_RESULT_SLOT(026) RVA0025AEE0_RESULT_SLOT(027)
	RVA0025AEE0_RESULT_SLOT(028) RVA0025AEE0_RESULT_SLOT(029)
	RVA0025AEE0_RESULT_SLOT(030) RVA0025AEE0_RESULT_SLOT(031)
	RVA0025AEE0_RESULT_SLOT(032) RVA0025AEE0_RESULT_SLOT(033)
	RVA0025AEE0_RESULT_SLOT(034) RVA0025AEE0_RESULT_SLOT(035)
	RVA0025AEE0_RESULT_SLOT(036) RVA0025AEE0_RESULT_SLOT(037)
	RVA0025AEE0_RESULT_SLOT(038) RVA0025AEE0_RESULT_SLOT(039)
	RVA0025AEE0_RESULT_SLOT(040) RVA0025AEE0_RESULT_SLOT(041)
	RVA0025AEE0_RESULT_SLOT(042) RVA0025AEE0_RESULT_SLOT(043)
	RVA0025AEE0_RESULT_SLOT(044) RVA0025AEE0_RESULT_SLOT(045)
	RVA0025AEE0_RESULT_SLOT(046) RVA0025AEE0_RESULT_SLOT(047)
	RVA0025AEE0_RESULT_SLOT(048) RVA0025AEE0_RESULT_SLOT(049)
	RVA0025AEE0_RESULT_SLOT(050) RVA0025AEE0_RESULT_SLOT(051)
	RVA0025AEE0_RESULT_SLOT(052) RVA0025AEE0_RESULT_SLOT(053)
	RVA0025AEE0_RESULT_SLOT(054) RVA0025AEE0_RESULT_SLOT(055)
	RVA0025AEE0_RESULT_SLOT(056) RVA0025AEE0_RESULT_SLOT(057)
	RVA0025AEE0_RESULT_SLOT(058) RVA0025AEE0_RESULT_SLOT(059)
	RVA0025AEE0_RESULT_SLOT(060) RVA0025AEE0_RESULT_SLOT(061)
	RVA0025AEE0_RESULT_SLOT(062) RVA0025AEE0_RESULT_SLOT(063)
	RVA0025AEE0_RESULT_SLOT(064) RVA0025AEE0_RESULT_SLOT(065)
	RVA0025AEE0_RESULT_SLOT(066) RVA0025AEE0_RESULT_SLOT(067)
	RVA0025AEE0_RESULT_SLOT(068) RVA0025AEE0_RESULT_SLOT(069)
	RVA0025AEE0_RESULT_SLOT(070) RVA0025AEE0_RESULT_SLOT(071)
	RVA0025AEE0_RESULT_SLOT(072) RVA0025AEE0_RESULT_SLOT(073)
	RVA0025AEE0_RESULT_SLOT(074) RVA0025AEE0_RESULT_SLOT(075)
	RVA0025AEE0_RESULT_SLOT(076) RVA0025AEE0_RESULT_SLOT(077)
	RVA0025AEE0_RESULT_SLOT(078) RVA0025AEE0_RESULT_SLOT(079)
	RVA0025AEE0_RESULT_SLOT(080) RVA0025AEE0_RESULT_SLOT(081)
	RVA0025AEE0_RESULT_SLOT(082) RVA0025AEE0_RESULT_SLOT(083)
	RVA0025AEE0_RESULT_SLOT(084) RVA0025AEE0_RESULT_SLOT(085)
	RVA0025AEE0_RESULT_SLOT(086) RVA0025AEE0_RESULT_SLOT(087)
	RVA0025AEE0_RESULT_SLOT(088) RVA0025AEE0_RESULT_SLOT(089)
	RVA0025AEE0_RESULT_SLOT(090) RVA0025AEE0_RESULT_SLOT(091)
	RVA0025AEE0_RESULT_SLOT(092) RVA0025AEE0_RESULT_SLOT(093)
	RVA0025AEE0_RESULT_SLOT(094) RVA0025AEE0_RESULT_SLOT(095)
	RVA0025AEE0_RESULT_SLOT(096) RVA0025AEE0_RESULT_SLOT(097)
	RVA0025AEE0_RESULT_SLOT(098) RVA0025AEE0_RESULT_SLOT(099)
	RVA0025AEE0_RESULT_SLOT(100) RVA0025AEE0_RESULT_SLOT(101)
	RVA0025AEE0_RESULT_SLOT(102) RVA0025AEE0_RESULT_SLOT(103)
	RVA0025AEE0_RESULT_SLOT(104) RVA0025AEE0_RESULT_SLOT(105)
	RVA0025AEE0_RESULT_SLOT(106) RVA0025AEE0_RESULT_SLOT(107)
	RVA0025AEE0_RESULT_SLOT(108) RVA0025AEE0_RESULT_SLOT(109)
	RVA0025AEE0_RESULT_SLOT(110) RVA0025AEE0_RESULT_SLOT(111)
	RVA0025AEE0_RESULT_SLOT(112)
#undef RVA0025AEE0_RESULT_SLOT
public:
	virtual void applyFXAtSlot01C4(FXList *);
};

class Object
{
#define RVA0025AEE0_OBJECT_SLOT(N) virtual void rvaSlot##N();
	RVA0025AEE0_OBJECT_SLOT(00) RVA0025AEE0_OBJECT_SLOT(01)
	RVA0025AEE0_OBJECT_SLOT(02) RVA0025AEE0_OBJECT_SLOT(03)
	RVA0025AEE0_OBJECT_SLOT(04) RVA0025AEE0_OBJECT_SLOT(05)
	RVA0025AEE0_OBJECT_SLOT(06) RVA0025AEE0_OBJECT_SLOT(07)
	RVA0025AEE0_OBJECT_SLOT(08) RVA0025AEE0_OBJECT_SLOT(09)
	RVA0025AEE0_OBJECT_SLOT(10) RVA0025AEE0_OBJECT_SLOT(11)
	RVA0025AEE0_OBJECT_SLOT(12) RVA0025AEE0_OBJECT_SLOT(13)
	RVA0025AEE0_OBJECT_SLOT(14) RVA0025AEE0_OBJECT_SLOT(15)
	RVA0025AEE0_OBJECT_SLOT(16) RVA0025AEE0_OBJECT_SLOT(17)
	RVA0025AEE0_OBJECT_SLOT(18) RVA0025AEE0_OBJECT_SLOT(19)
	RVA0025AEE0_OBJECT_SLOT(20) RVA0025AEE0_OBJECT_SLOT(21)
	RVA0025AEE0_OBJECT_SLOT(22)
#undef RVA0025AEE0_OBJECT_SLOT
public:
	virtual void callAtSlot005C(Object *);
	Rva001CF980Result *queryAt001CF980();
	ThingTemplate *getTemplate() const { return m_template; }
	ThingTemplate *m_template;
	unsigned char m_08_to_78[0x70];
	ObjectID m_producerID;
	unsigned char m_7c_to_90[0x14];
	UnsignedInt m_status; // First word of the witnessed Object status storage.
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID);
};
extern GameLogic *TheBfmeGameLogic;

class FXList
{
public:
	Bool cullAt0042DAA0();
	static void doFXObj(const FXList *, const Object *, const Object *);
	void doFXPos(const Coord3D *, const Matrix3D *, Real, const Coord3D *) const;
};

struct Rva0025AEE0Data
{
	unsigned char m_00_to_254[0x254];
	Real m_radius;
	FXList *m_endFX;
	FXList *m_targetFX;
};

class DominateEnemySpecialPower
{
public:
	virtual void rvaSlot00(); virtual void rvaSlot01();
	virtual void rvaSlot02(); virtual void rvaSlot03();
	virtual void rvaSlot04(); virtual void rvaSlot05();
	virtual void rvaSlot06(); virtual void rvaSlot07();
	virtual void rvaSlot08(); virtual void rvaSlot09();
	virtual void rvaSlot10(); virtual void rvaSlot11();
	virtual void rvaSlot12(); virtual void rvaSlot13();
	virtual void rvaSlot14();
	virtual void actionAt0025AEE0();
	void prepareAt002A9850();

	Rva0025AEE0Data *m_data;
	Object *m_object;
	unsigned char m_0c_to_b0[0xa4];
	Coord3D m_queryPosition;
};

static __forceinline ThingTemplate *Rva0025AEE0FinalTemplate(Object *object)
{
	ThingTemplate *thingTemplate = object->getTemplate();
	if (thingTemplate == 0)
		return 0;
	const Overridable *nextOverride = thingTemplate->getNextOverride();
	return nextOverride != 0
		? const_cast<ThingTemplate *>(
			reinterpret_cast<const ThingTemplate *>(
				reinterpret_cast<const BfmeControlBarOverridable *>(
					nextOverride)->getFinalOverride()))
		: thingTemplate;
}

void DominateEnemySpecialPower::actionAt0025AEE0()
{
	prepareAt002A9850();
	Object *owner = m_object;
	static NameKeyType temporarilyDefectKey =
		TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");
	Rva0025AEE0Data *data = m_data;

	Rva0025AEE0OwningIterator iterator =
		ThePartitionManager->iterateAt0025AEE0(
			&m_queryPosition, data->m_radius, ITER_FASTEST,
			PartitionFilterRelationship(owner, 1, false)
				.link(&Rva0025ED50RootFilter())
				->link(&Rva0025ED50ObjectFilter(owner))
				->link(&PartitionFilterRejectByObjectStatus(
					Rva0025AEE0ObjectStatusMask(
						Rva0025AEE0ObjectStatusMask::kInit, 37),
					Rva0025AEE0ObjectStatusMask())),
			true);

	Object *other;
	while (iterator.next(other))
	{
		if (other == 0 || other == owner)
			continue;
		if ((*reinterpret_cast<UnsignedInt *>(
				reinterpret_cast<unsigned char *>(
					(Rva0025AEE0FinalTemplate(other))) + 0xd0)
			& 0x02000000u) != 0)
			continue;
		if ((*reinterpret_cast<signed char *>(
				reinterpret_cast<unsigned char *>(
					(Rva0025AEE0FinalTemplate(other))) + 0xc8) & 0x80) != 0)
			continue;
		if ((*reinterpret_cast<unsigned char *>(
				reinterpret_cast<unsigned char *>(
					(Rva0025AEE0FinalTemplate(other))) + 0xd8)
			& 0x20u) != 0)
			continue;
		if ((*reinterpret_cast<UnsignedInt *>(
				reinterpret_cast<unsigned char *>(
					(Rva0025AEE0FinalTemplate(other))) + 0xd8)
			& 0x00400000u) != 0)
			continue;

		UnsignedInt status = other->m_status;
		if ((status & 0x0cu) != 0)
			continue;
		Object *producer = TheBfmeGameLogic->findObjectByID(other->m_producerID);
		if (producer != 0 && reinterpret_cast<Thing *>(producer)->isKindOf(
				static_cast<KindOfType>(0x6c)))
			continue;
		if ((status & 0x40u) != 0)
			continue;

		other->callAtSlot005C(owner);
		Rva001CF980Result *result = other->queryAt001CF980();
		if (result != 0)
			result->applyFXAtSlot01C4(data->m_targetFX);
		else
			FXList::doFXObj(data->m_targetFX, other, 0);
	}

	FXList *endFX = data->m_endFX;
	if (endFX != 0 && !endFX->cullAt0042DAA0())
		endFX->doFXPos(&m_queryPosition, 0, 0.0f, 0);
}
