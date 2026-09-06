// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
// Open-BFME: Player::findClosestByKindOf(const Coord3D *, KindOfMaskType, KindOfMaskType), retail 0x000CFD20.

#include <float.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];

	void clear()
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
		m_bits[3] = 0;
		m_bits[4] = 0;
		m_bits[5] = 0;
	}
};

typedef BitFlags<192> KindOfMaskType;

class Object
{
public:
	Bool isKindOfMulti(const KindOfMaskType &setMask,
		const KindOfMaskType &clearMask) const;

	char m_pad[0x38];
	Coord3D m_position;
};

typedef void (*ObjectIterateFunc)(Object *object, void *userData);

class Player
{
public:
	Int iterateObjects(ObjectIterateFunc func, void *userData) const;
	Object *findClosestByKindOf(const Coord3D *queryPosition,
		KindOfMaskType setMask, KindOfMaskType clearMask);
};

class ClosestKindOfData
{
public:
	KindOfMaskType m_setKindOf;
	KindOfMaskType m_clearKindOf;
	Coord3D m_source;
	Object *m_closest;
	Real m_closestDistSq;
};

extern void j_00037fe7(void);

static void findClosestKindOf(Object *obj, void *userData)
{
	ClosestKindOfData *closestData = (ClosestKindOfData *)userData;

	if (!obj->isKindOfMulti(closestData->m_setKindOf,
		closestData->m_clearKindOf))
		return;

	Real dx = obj->m_position.x - closestData->m_source.x;
	Real dy = obj->m_position.y - closestData->m_source.y;
	Real distSq = dx * dx + dy * dy;
	if (distSq < closestData->m_closestDistSq)
	{
		closestData->m_closest = obj;
		closestData->m_closestDistSq = distSq;
	}
}

Object *Player::findClosestByKindOf(const Coord3D *queryPosition,
	KindOfMaskType setMask, KindOfMaskType clearMask)
{
	ClosestKindOfData data;
	typedef void (ClosestKindOfData::*Constructor)(void);
	union
	{
		void (*raw)(void);
		Constructor member;
	} constructor;
	constructor.raw = j_00037fe7;
	(data.*constructor.member)();
	register Player *self = this;
	data.m_setKindOf = setMask;
	data.m_clearKindOf = clearMask;
	data.m_source = *queryPosition;
	self->iterateObjects(findClosestKindOf, &data);
	return data.m_closest;
}
