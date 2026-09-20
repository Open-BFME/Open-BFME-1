// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/GameType.h"
#include "Common/KindOf.h"
#include "GameLogic/ObjectIter.h"

// Retail RVA 0x0025E150..0x0025E391 is 577 bytes through the final RET0. This TU keeps
// the owning row address-labelled.  The 355-byte and 468-byte siblings prove
// the BFME filter/result ABI and the temporary lifetime used below.
// The four-filter chain is left-associated; temporary filters die before iteration.
// Keep the producer local distinct from the resolved target and reload module data
// at dispatch. The selected candidate is dispatched, not the owner object.
// Missing producer and kind7 branches still dispatch that candidate; only an
// existing resolved target's excluded status causes enumeration to continue.
// The original module/method names remain unasserted.

class Object;
class Player;
class Rva0025E150ThingTemplate;
struct BfmeNodeND;

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

// Existing BFME object/root filter views from Rva0025ED50ChargeTargets.
class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
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

// Vtable 0x0109689C: dtor 0x00161390, allow 0x001DD140,
// getPlayerMask 0x001DD100.  The third slot is intentionally overridden.
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

// Vtable 0x010B5180: dtor 0x0025DBB0, allow 0x001DCCC0, and the inherited
// BFME default getPlayerMask slot.  The node pointer is at +8.
class Rva0025E150UpgradeFilter : public PartitionFilter
{
public:
	// ??0Rva0025E150UpgradeFilter@@QAE@PAUBfmeNodeND@@@Z
	explicit Rva0025E150UpgradeFilter(BfmeNodeND *node)
		: m_node(node) {}
	virtual ~Rva0025E150UpgradeFilter() {}
	virtual Bool allow(Object *);

	BfmeNodeND *m_node;
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

struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	~Rva0025ED50WideResult()
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
	Rva0025ED50WideResult iterate(const Coord3D *, Real, IterOrderType,
		PartitionFilter *, Bool);
};

extern PartitionManager *ThePartitionManager;

class Object
{
public:
	Player *getControllingPlayer(void) const;
	Object *bfmeResolveMeleeTarget(Int);
	void setStatusBit(Int, Bool);

	void *m_vptr;
	Rva0025E150ThingTemplate *m_template;
	unsigned char m_08_to_38[0x30];
	Coord3D m_position;
	unsigned char m_44_to_74[0x30];
	ObjectID m_id;
	ObjectID m_producerID;
	unsigned char m_7c_to_90[0x14];
	unsigned char m_status[12]; // Read-only byte view of BFME's 86-bit status mask.
	unsigned char m_9c_to_224[0x188];
	UnsignedInt m_upgradeMask[6];
};

typedef Object Rva0025E150Object;

// The existing const out-of-line BFME view is retained so the call is a
// real member call on ThingTemplate+4 rather than an invented free alias.
class BfmeControlBarOverridable
{
public:
	const BfmeControlBarOverridable *getFinalOverride() const;
};

class Rva0025E150ThingTemplate
{
public:
	void *m_vptr;
	BfmeControlBarOverridable *m_overridable;
	unsigned char m_08_to_d8[0xd0];
	UnsignedInt m_flagsD8;
};

class BfmeThingND
{
public:
	BfmeNodeND *bfmeFindND(const UnsignedInt *mask);
};

class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;

class GameLogic
{
public:
	Object *findObjectByID(int);
};

extern GameLogic *TheBfmeGameLogic;

// The +20 member is an embedded BFME interface.  Slot zero receives
// (data+1D8, selected candidate, 0, 0, 0); its semantic owner is not asserted.
class Rva0025E150SecondaryInterface
{
public:
	virtual void dispatch(void *, Object *, Int, Int, Int);
};

struct Rva0025E150Data
{
	unsigned char m_00_to_1d8[0x1d8];
	void *m_dispatchData;
	unsigned char m_1dc_to_270[0x94];
	Bool m_byte270;
};

class Rva0025E150Owner
{
public:
	void callAt0025E150();

	unsigned char m_00_to_04[0x04];
	Rva0025E150Data *m_data;
	Object *m_object;
	unsigned char m_0c_to_20[0x14];
	unsigned char m_secondary[4];
	unsigned char m_24_to_ac[0x88];
	ObjectID m_targetID;
	unsigned char m_b0_to_e9[0x39];
	Bool m_owner_e9;
};

void Rva0025E150Owner::callAt0025E150()
{
	ObjectID pending=m_targetID;
	Rva0025E150Data *data=m_data;
	if (pending == 0 && data->m_byte270)
	{
		Rva0025E150Object *object = m_object;
		m_owner_e9 = true;

		BfmeNodeND *node = reinterpret_cast<BfmeThingND *>(
			TheUpgradeCenter)->bfmeFindND(
			object->m_upgradeMask);

		Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
			&object->m_position, 100000.0f, ITER_FASTEST,
			PartitionFilterPlayerAffiliation(
				object->getControllingPlayer()).link(
					&Rva0025ED50RootFilter())->link(
						&Rva0025E150UpgradeFilter(node))->link(
							&Rva0025ED50ObjectFilter(object)),
			true);

		Rva0025E150Object *candidate;
		while (iterator.next(candidate))
		{
			Rva0025E150ThingTemplate *finalTemplate = candidate->m_template;
			if (finalTemplate == 0)
				finalTemplate = 0;
			else
			{
				if (finalTemplate->m_overridable != 0)
					finalTemplate = const_cast<Rva0025E150ThingTemplate *>(
						reinterpret_cast<const Rva0025E150ThingTemplate *>(finalTemplate->m_overridable->getFinalOverride()));
			}

			// Retail reads +D8 even when the template path left EAX null.
			if ((finalTemplate->m_flagsD8 & 0x200000) != 0)
				continue;
			if ((candidate->m_status[8] & 2) != 0)
				continue;

			Rva0025E150Object *target =
				candidate->bfmeResolveMeleeTarget(0);
			if (target == 0)
			{
				ObjectID producerID = candidate->m_producerID;
				if (producerID == 0)
					goto dispatch_original;
				Object *producer = TheBfmeGameLogic->findObjectByID(producerID);
				if (producer == 0)
					goto dispatch_original;
				if (reinterpret_cast<Thing *>(producer)->isKindOf(
					static_cast<KindOfType>(7)))
					goto dispatch_original;
				target=producer;
			}

			if ((target->m_status[8] & 2) != 0)
				continue;
			if ((target->m_status[0] & 4) != 0)
				continue;
			target->setStatusBit(0x41, true);

		 dispatch_original:
			candidate->setStatusBit(0x41, true);
			reinterpret_cast<Rva0025E150SecondaryInterface *>(m_secondary)->dispatch(m_data->m_dispatchData, candidate, 0, 0, 0);
			break;
		}
	}
}
