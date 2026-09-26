// ?update@ReplenishUnitsBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// ReplenishUnitsBehavior::update, retail 0x00204B50 (628 bytes).
//
// The retail entry is the UpdateModuleInterface subobject at primary +0x10.
// Its constructor-proven slot 0 is the ILT at 0x00017FBC, which jumps here.
// The filter layouts and constants below are recovered from the retail stores;
// the neutral names are kept local because their public class identities are
// not established.

typedef bool Bool;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object;
class Player;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PartitionFilter
{
public:
	PartitionFilter(void) : m_vptr(0x01083b80), m_next(0) {}
	PartitionFilter *link(PartitionFilter *next);

	unsigned int m_vptr;
	PartitionFilter *m_next;
};

class Rva001DCBB0Filter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);

	unsigned int m_vptr;
	unsigned int m_unmodelled_04;
	Player *m_player;
	unsigned char m_match;
};

class SameMapFilter : public PartitionFilter
{
public:
	SameMapFilter(Object *object) : m_object(object)
	{
		m_vptr = 0x01085dd0;
	}

	private:
	Object *m_object;
};

class RelationshipFilter : public PartitionFilter
{
public:
	RelationshipFilter(Object *object, int flags, Bool state)
		: m_object(object), m_flags(flags), m_state(state)
	{
		m_vptr = 0x01085dc0;
	}

private:
	Object *m_object;
	int m_flags;
	Bool m_state;
};

class ContainmentFilter : public PartitionFilter
{
public:
	ContainmentFilter(PartitionFilter *filter)
		: m_filter(filter), m_enabled(true)
	{
		m_vptr = 0x010a5aac;
	}

private:
	PartitionFilter *m_filter;
	Bool m_enabled;
};

class ControllingPlayerFilter : public PartitionFilter
{
public:
	ControllingPlayerFilter(Player *player) : m_player(player)
	{
		m_vptr = 0x01097144;
	}

private:
	Player *m_player;
};

struct VptrZeroBlock12
{
	unsigned int m_dword_00;
	unsigned int m_dword_04;
	unsigned int m_dword_08;
};

class Rva001FC280VptrZeroBlockObject : public PartitionFilter
{
public:
	Rva001FC280VptrZeroBlockObject(const VptrZeroBlock12 &first,
		const VptrZeroBlock12 &second);

	~Rva001FC280VptrZeroBlockObject(void)
	{
		m_vptr = 0x01083b5c;
	}

	VptrZeroBlock12 m_first;
	VptrZeroBlock12 m_second;
};

class SpawnBehaviorBase
{
public:
	virtual Bool slot00() = 0;
};

class ContainModule
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual PartitionFilter *getFilter() = 0;
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		int distanceCalculation, PartitionFilter *filters);
};

class BfmeThingEQW;

class BfmeHostEQW
{
public:
	void bfmeGoEQW(BfmeThingEQW *thing);
};

extern const Real BfmeZeroRange;
extern PartitionManager *ThePartitionManager;

class ReplenishUnitsBehavior
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime ReplenishUnitsBehavior::update()
{
	char *secondaryThis = reinterpret_cast<char *>(this);
	char *primaryThis = secondaryThis - 0x10;
	Object *object = *reinterpret_cast<Object **>(secondaryThis - 0x08);
	char *moduleData = *reinterpret_cast<char **>(secondaryThis - 0x0c);
	SpawnBehaviorBase *spawn =
		reinterpret_cast<SpawnBehaviorBase *>(primaryThis + 0x20);
	BfmeHostEQW *host = reinterpret_cast<BfmeHostEQW *>(primaryThis);
	if (!spawn->slot00())
		return UPDATE_SLEEP_FOREVER;
	if ((*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(object) + 0x344) & 1) != 0)
		return UPDATE_SLEEP_FOREVER;

	PartitionFilter *containment = 0;
	if (*reinterpret_cast<unsigned char *>(moduleData + 0x8d) != 0)
	{
		ContainModule *contain =
			*reinterpret_cast<ContainModule **>(reinterpret_cast<char *>(object) + 0x1fc);
		if (contain == 0)
			return UPDATE_SLEEP_FOREVER;
		containment = contain->getFilter();
		if (containment == 0)
			return UPDATE_SLEEP_FOREVER;
	}

	if (*reinterpret_cast<Real *>(moduleData + 0x74) != BfmeZeroRange)
	{
		Rva001DCBB0Filter playerFilter(object, false);
		SameMapFilter sameMap(object);
		PartitionFilter base;
		RelationshipFilter relationship(object, 1, false);
		PartitionFilter *filters = relationship.link(
			base.link(sameMap.link(reinterpret_cast<PartitionFilter *>(&playerFilter))));
		Object *found = ThePartitionManager->getClosestObject(
			reinterpret_cast<Coord3D *>(reinterpret_cast<char *>(object) + 0x38),
			*reinterpret_cast<Real *>(moduleData + 0x74), 0, filters);
		if (found != 0)
			return UPDATE_SLEEP_FOREVER;
	}

	ContainmentFilter filter(containment);
	SameMapFilter sameMap(object);
	PartitionFilter base;
	VptrZeroBlock12 first = { 0, 0x20000, 0 };
	Rva001FC280VptrZeroBlockObject blockFilter(
		first, *reinterpret_cast<const VptrZeroBlock12 *>(moduleData + 0x7c));
	ControllingPlayerFilter playerFilter(object->getControllingPlayer());
	PartitionFilter *filters = playerFilter.link(
		blockFilter.link(base.link(sameMap.link(&filter))));
	Object *found = ThePartitionManager->getClosestObject(
		reinterpret_cast<Coord3D *>(reinterpret_cast<char *>(object) + 0x38),
		*reinterpret_cast<Real *>(moduleData + 0x70), 0, filters);
	if (found != 0)
		host->bfmeGoEQW(reinterpret_cast<BfmeThingEQW *>(found));
	if (found != 0)
		return *reinterpret_cast<UpdateSleepTime *>(moduleData + 0x88);
	return UPDATE_SLEEP_FOREVER;
}
