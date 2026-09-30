// ?method@Rva00188E80@@YG_NPAVObject@@0@Z
// partial score=0.3804 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <math.h>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum WeaponSlotType { RvaPrimaryWeaponSlot = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI = 2 };
enum IterOrderType { ITER_FASTEST = 0, ITER_SORTED_NEAR_TO_FAR = 1 };

class Object;
class Weapon;

class AICommandInterface
{
public:
	void bfmeCommand3C(Object *victim, CommandSourceType source);
};

class AIUpdateInterface
{
public:
	void setCurrentVictim(const Object *victim);
	AICommandInterface *getCommandInterface() { return (AICommandInterface *)((char *)this + 0x20); }
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);

	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0xbc - 0x44];
	Real m_boundingCircleRadius;
	unsigned char m_padc0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x214 - 0x208];
	Object *m_containedBy;
};

class Weapon
{
public:
	Real bfmeEstimate(const Object *source, const Object *victim) const;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

// vtable 0x01097154 (dir32 name ??_7Rva0016AA20VptrZeroObject@@6B@); unwind dtor 0x0016AA50.
class Rva00188E80Filter : public PartitionFilter
{
public:
	Rva00188E80Filter(Object *source, Bool flag) : m_source(source), m_flag(flag) {}
	virtual ~Rva00188E80Filter() {}
	virtual Bool allow(Object *);

	Object *m_source;
	Bool m_flag;
};

struct Rva00188E80Entry
{
	Object *m_object;
	UnsignedInt m_distanceBits;
};

struct Rva00188E80Payload
{
	_STL::vector<Rva00188E80Entry> m_entries;
	Rva00188E80Entry *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	Rva00188E80Payload *m_value;

	~BfmeWideResult()
	{
		Rva00188E80Payload *&payload = m_value;
		--payload->m_refCount;
		if (payload->m_refCount == 0)
			delete payload;
	}

	Object *next()
	{
		if (m_value->m_cursor == m_value->m_entries.end())
			return 0;
		return (m_value->m_cursor++)->m_object;
	}
};

class PartitionManager
{
public:
	BfmeWideResult iterate(const Coord3D *pos, Real range, IterOrderType order, PartitionFilter *filter, Bool flag);
};

// Retail pushes the final false as an immediate; this spelling reuses the zero in ebp (one byte short).

extern PartitionManager *ThePartitionManager;
extern const Real BfmeZeroRange;

static inline Real boundingDistanceSquared(const Object *a, const Object *b)
{
	const Coord3D *posA = a->getPosition();
	const Coord3D *posB = b->getPosition();
	Real dx = posA->x - posB->x;
	Real dy = posA->y - posB->y;
	Real dist = (Real)sqrt(dx * dx + dy * dy);
	dist -= a->getBoundingCircleRadius();
	dist -= b->getBoundingCircleRadius();
	if (dist < BfmeZeroRange)
		return BfmeZeroRange;
	return dist * dist;
}

namespace Rva00188E80
{
bool __stdcall method(Object *source, Object *target)
{
	if (source->getContainedBy() != 0)
		return false;

	const Coord3D *targetPos = target->getPosition();
	Real dx = source->getPosition()->x - targetPos->x;
	Real dy = source->getPosition()->y - targetPos->y;
	Real distance = (Real)sqrt(dx * dx + dy * dy);
	Real range = distance;

	Weapon *weapon = source->getCurrentWeapon();
	if (weapon == 0)
		return false;

	Real weaponRange = weapon->bfmeEstimate(source, target);
	if (distance > weaponRange)
		range = weaponRange;

	Rva00188E80Filter filter(source, false);
	BfmeWideResult iter = ThePartitionManager->iterate(targetPos, range, ITER_SORTED_NEAR_TO_FAR, &filter, false);

	Object *best = 0;
	Real bestDistance = 0.0f;
	Object *other;
	while ((other = iter.next()) != 0)
	{
		Real selfDistance = (Real)sqrt(boundingDistanceSquared(source, other));
		Real targetDistance = (Real)sqrt(boundingDistanceSquared(target, other));
		if (selfDistance + other->getBoundingCircleRadius() * 1.5f > distance)
			continue;
		if (targetDistance + selfDistance > distance)
			continue;
		if (best == 0 || bestDistance > selfDistance)
		{
			best = other;
			bestDistance = selfDistance;
		}
	}

	if (best != 0)
	{
		AIUpdateInterface *ai = source->getAI();
		ai->setCurrentVictim(target);
		ai->getCommandInterface()->bfmeCommand3C(best, CMD_FROM_AI);
		return true;
	}
	return false;
}
}
