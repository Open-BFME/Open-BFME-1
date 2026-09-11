// Open-BFME5: Player::findClosestByKindOf(Object *, ...), retail 0x000CFC30.
// The adjacent matched Coord3D overload and ClosestKindOfData constructor
// establish the search state and Player::iterateObjects callback protocol.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef float Real;
typedef int Int;

template <Int Bits> class BitFlags
{
public:
	unsigned int m_bits[(Bits + 31) / 32];
};

typedef BitFlags<0xC0> KindOfMaskType;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	unsigned char m_head[0x38];
	Coord3D m_position;
};

typedef void (*ObjectIterateFunc)(Object *, void *);

class Player
{
public:
	void iterateObjects(ObjectIterateFunc func, void *userData) const;
	Object *findClosestByKindOf(Object *queryObject,
		KindOfMaskType setMask, KindOfMaskType clearMask);
};

class ClosestKindOfData
{
public:
	ClosestKindOfData();

	KindOfMaskType m_setKindOf;
	KindOfMaskType m_clearKindOf;
	Coord3D m_source;
	Object *m_closest;
	Real m_closestDistSq;
};

class BfmeProbeXM;
struct BfmeStateXM;
int bfmeVisitXM(BfmeProbeXM *probe, BfmeStateXM *state);

Object *Player::findClosestByKindOf(Object *queryObject,
	KindOfMaskType setMask, KindOfMaskType clearMask)
{
	if (queryObject == 0)
		return 0;

	ClosestKindOfData data;
	data.m_setKindOf = setMask;
	data.m_clearKindOf = clearMask;
	data.m_source = queryObject->m_position;

	union
	{
		int (*typed)(BfmeProbeXM *, BfmeStateXM *);
		ObjectIterateFunc iterate;
	} visitor;
	visitor.typed = bfmeVisitXM;
	iterateObjects(visitor.iterate, &data);
	return data.m_closest;
}
