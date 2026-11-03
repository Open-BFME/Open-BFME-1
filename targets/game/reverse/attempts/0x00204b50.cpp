// ?update@ReplenishUnitsBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.4124 date=2026-11-03
// cl: /DNDEBUG /MD /EHsc
// ?update@ReplenishUnitsBehavior@@UAE?AW4UpdateSleepTime@@XZ  s547 bank: 631/628 B, shape 1.000; residue is frame-slot allocation only
// (frame 0x9C vs retail 0x90: retail packs the kind-of mask temp into the dead group-1
// Rva0025ED50ObjectFilter slot at frame 0; see attempt_support/0x00204b50-replenish-update-s547.md).

#include <string.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Player;

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void *slot26();										// +0x68
};

class Object
{
public:
	Player *getControllingPlayer() const;

	unsigned char m_pad000[0x38];
	Coord3D m_position;											// +0x38
	unsigned char m_pad044[0x1FC - 0x44];
	ContainModuleInterface *m_contain;							// +0x1FC
	unsigned char m_pad200[0x344 - 0x200];
	unsigned char m_privateStatus;								// +0x344
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *);
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class Rva001DCBB0Filter : public PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);
	virtual ~Rva001DCBB0Filter() {}

	Player *m_player;
	unsigned char m_match;
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

	Object *m_object;
	Int m_flags;
	Bool m_match;
};

class Rva00204360VptrZeroObject : public PartitionFilter
{
public:
	Rva00204360VptrZeroObject(void *contain, unsigned char match)
		: m_contain(contain), m_match(match) {}
	virtual ~Rva00204360VptrZeroObject() {}
	virtual Bool allow(Object *);

	void *m_contain;
	unsigned char m_match;
};

class Rva0016A9F0FunctorValueWrapper : public PartitionFilter
{
public:
	explicit Rva0016A9F0FunctorValueWrapper(void *player) : m_player(player) {}
	virtual ~Rva0016A9F0FunctorValueWrapper() {}
	virtual Bool allow(Object *);

	void *m_player;
};

struct VptrZeroBlock12
{
	VptrZeroBlock12() {}
	explicit VptrZeroBlock12(int bit)
	{
		memset(m_bits, 0, sizeof(m_bits));
		m_bits[bit >> 5] |= 1u << (bit & 31);
	}
	unsigned int m_bits[3];
};

class Rva001FC280VptrZeroBlockObject : public PartitionFilter
{
public:
	Rva001FC280VptrZeroBlockObject(const VptrZeroBlock12 &first, const VptrZeroBlock12 &second) throw();
	virtual ~Rva001FC280VptrZeroBlockObject() {}

	VptrZeroBlock12 m_first;
	VptrZeroBlock12 m_second;
};

class BfmeC1050
{
public:
	void *bfmeGo1050D(Int position, Int range, Int distance, Int filters);
};

extern BfmeC1050 *ThePartitionManager;
extern Real g_bfmeDefaultBR;

class BfmeThingEQW;
class BfmeHostEQW
{
public:
	void bfmeGoEQW(BfmeThingEQW *thing);
};

struct ReplenishUnitsBehaviorModuleData
{
	unsigned char m_pad00[0x70];
	Real m_replenishRadius;										// +0x70
	Real m_blockRadius;											// +0x74
	unsigned char m_pad78[4];
	VptrZeroBlock12 m_kindOf;									// +0x7C
	unsigned int m_sleep88;										// +0x88
	unsigned char m_pad8C;
	Bool m_needsContain;										// +0x8D
};

class ReplenishUnitsBehaviorPrimary
{
public:
	virtual void slot00();

	const ReplenishUnitsBehaviorModuleData *m_moduleData;		// +0x04
	Object *m_object;											// +0x08
	void *m_unmodelled0C;
};

class ReplenishUnitsBehaviorUpdateIface
{
public:
	virtual UpdateSleepTime update() = 0;

	unsigned char m_pad04[0xC];
};

class ReplenishUnitsBehaviorSpawnIface
{
public:
	virtual Bool isActive() = 0;
};

class ReplenishUnitsBehavior : public ReplenishUnitsBehaviorPrimary,
	public ReplenishUnitsBehaviorUpdateIface,
	public ReplenishUnitsBehaviorSpawnIface
{
public:
	virtual UpdateSleepTime update();
};

// ?update@ReplenishUnitsBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime ReplenishUnitsBehavior::update()
{
	ReplenishUnitsBehaviorPrimary *self = this;
	const ReplenishUnitsBehaviorModuleData *data = m_moduleData;
	Object *object = m_object;

	if (!static_cast<ReplenishUnitsBehavior *>(self)->isActive() || (object->m_privateStatus & 1))
		return UPDATE_SLEEP_FOREVER;

	void *contain = 0;
	if (data->m_needsContain)
	{
		ContainModuleInterface *c = object->m_contain;
		if (!c || !(contain = c->slot26()))
			return UPDATE_SLEEP_FOREVER;
	}

	Bool clear = data->m_blockRadius == g_bfmeDefaultBR ||
		ThePartitionManager->bfmeGo1050D((Int)&object->m_position,
			*(const Int *)&data->m_blockRadius, 0,
			(Int)PartitionFilterRelationship(object, 1, false).link(
				Rva0025ED50RootFilter().link(
					Rva0025ED50ObjectFilter(object).link(
						&Rva001DCBB0Filter(object, false))))) == 0;
	if (!clear)
		return (UpdateSleepTime)data->m_sleep88;

	void *found = ThePartitionManager->bfmeGo1050D((Int)&object->m_position,
		*(const Int *)&data->m_replenishRadius, 0,
		(Int)Rva0016A9F0FunctorValueWrapper(object->getControllingPlayer()).link(
			Rva001FC280VptrZeroBlockObject(data->m_kindOf, VptrZeroBlock12(49)).link(
				Rva0025ED50RootFilter().link(
					Rva0025ED50ObjectFilter(object).link(
						&Rva00204360VptrZeroObject(contain, true))))));
	if (found)
		((BfmeHostEQW *)self)->bfmeGoEQW((BfmeThingEQW *)found);
	return (UpdateSleepTime)data->m_sleep88;
}
