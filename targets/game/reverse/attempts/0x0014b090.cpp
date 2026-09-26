// ?findClosestRepulsor@AI@@QAEPAVObject@@PBV2@M@Z
// partial score=0.9 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

class Object;
struct Coord3D;

class TAiData
{
public:
	unsigned char m_padding[0x64];
	Bool m_enableRepulsors;
};

class AI
{
public:
	TAiData *getAiData()
	{
		return *(TAiData **)((char *)this + 0x14);
	}

	Object *findClosestRepulsor(const Object *me, Real range);
};

class PartitionFilter
{
public:
	virtual ~PartitionFilter() {}
	PartitionFilter *m_next;
	PartitionFilter *link(PartitionFilter *next);
};

class Rva001DCBB0Filter
	: public PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);

	unsigned char m_storage[8];
};

class PartitionFilterRepulsor
{
public:
	PartitionFilterRepulsor(const Object *object)
	{
		m_next = 0;
		m_vtable = (void *)0x01095704;
		m_self = object;
	}

	void *m_vtable;
	PartitionFilter *m_next;
	const Object *m_self;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real range,
		int distanceCalculation, PartitionFilter *filters);
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

extern PartitionManager *ThePartitionManager;

Object *AI::findClosestRepulsor(const Object *me, Real range)
{
	if (!getAiData()->m_enableRepulsors)
		return 0;

	Rva001DCBB0Filter filterStealth((Object *)me, 0);
	PartitionFilterRepulsor filter(me);
	return ThePartitionManager->getClosestObject(me->getPosition(), range, 1,
		((PartitionFilter *)&filter)->link(&filterStealth));
}
