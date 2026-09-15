// BFME AIUpdateInterface::chooseGoodLocomotorFromCurrentSet, retail 0x00270D40.
// The BFME object and AIUpdate layouts differ from the reference headers.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 0
};

class AIGroup;

class Locomotor
{
};

class LocomotorSet
{
public:
	Locomotor *findLocomotor(Int surfaces);

private:
	char m_unreconstructed[0x24];
};

class Pathfinder
{
public:
	Locomotor *chooseBestLocomotorForPosition(PathfindLayerEnum layer,
		LocomotorSet *locomotorSet, const Coord3D *position);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return *reinterpret_cast<Pathfinder * const *>(
			reinterpret_cast<const char *>(this) + 0x0C);
	}
};

extern AI *TheAI;

class Object
{
public:
	Int getLayer() const;

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}
};

class T_000382c1
{
public:
	void m();
};

class AIUpdateInterface
{
	protected:
	void chooseGoodLocomotorFromCurrentSet();

	char m_unreconstructed_000[0x08];
	Object *m_object;
	char m_unreconstructed_00C[0x1A8 - 0x0C];
	LocomotorSet m_locomotorSet;
	Locomotor *m_curLocomotor;
};

// ?chooseGoodLocomotorFromCurrentSet@AIUpdateInterface@@IAEXXZ
void AIUpdateInterface::chooseGoodLocomotorFromCurrentSet()
{
	Pathfinder *pathfinder = TheAI->pathfinder();
	Locomotor *previous = m_curLocomotor;
	Locomotor *current = pathfinder->chooseBestLocomotorForPosition(
		static_cast<PathfindLayerEnum>(m_object->getLayer()), &m_locomotorSet,
		m_object->getPosition());

	if (current == 0)
	{
		if (previous != 0)
			current = previous;
		else
			current = m_locomotorSet.findLocomotor(1);
	}

	m_curLocomotor = current;

	if (previous != m_curLocomotor)
	{
		typedef AIGroup *(T_000382c1::*GroupCall)();
		union
		{
			void (T_000382c1::*address)();
			GroupCall member;
		} route = { &T_000382c1::m };
		AIGroup *group = (reinterpret_cast<T_000382c1 *>(m_object)->*route.member)();
		if (group)
		{
			group = (reinterpret_cast<T_000382c1 *>(m_object)->*route.member)();
			reinterpret_cast<unsigned char *>(group)[0x10] = 1;
		}

		reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(m_curLocomotor) + 0x40)[0] &= ~8u;
		reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(m_curLocomotor) + 0x40)[0] &= ~0x10u;
		reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(m_curLocomotor) + 0x40)[0] &= ~0x40u;
	}
}
