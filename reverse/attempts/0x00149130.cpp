// ?bfmeSampleAirspace@AerialPathfinder@@QAEHPAVObject@@PBUCoord3D@@PAU3@@Z
// partial score=0.86 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc-
//
// BFME AerialPathfind family.  The member below is the 0x00149130 helper
// called by the complete 0x00149470 AerialPathfind body.  Its receiver and
// three stack arguments are established by that caller; the name remains
// address-derived until the original BFME declaration is recovered.

typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Locomotor
{
public:
	unsigned char m_unreconstructed000[0x44];
	Real m_sampleRadius;
};

class AIUpdateInterface
{
public:
	unsigned char m_unreconstructed000[0x1cc];
	Locomotor *m_curLocomotor;
};

class Object
{
public:
	unsigned char m_unreconstructed000[0xc0];
	Real m_heightC0;
	unsigned char m_unreconstructed0c4[0x204 - 0xc4];
	AIUpdateInterface *m_ai;
};

class Rva003FD060TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const = 0;
};

class AerialPathfinder
{
public:
	Real getNoFlyZoneHeight(Real x, Real y);
	void bfmeAerialHeight(Object *object, const Coord3D *from,
		const Real *sample, Coord3D *result);
	Int bfmeSampleAirspace(Object *object, const Coord3D *position,
		Coord3D *result);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

#define Rva001094A50 (*(const Real *)0x01094A50)
#define Rva001094A5C (*(const Real *)0x01094A5C)
#define BfmeZeroRange (*(const Real *)0x01075350)

// ?bfmeSampleAirspace@AerialPathfinder@@QAEHPAVObject@@PBUCoord3D@@PAU3@@Z
Int AerialPathfinder::bfmeSampleAirspace(Object *object,
	const Coord3D *position, Coord3D *result)
{
	AIUpdateInterface *ai = object->m_ai;
	if (ai == 0)
		return 2;
	register AerialPathfinder *self = this;

	result->x = 0.0f;
	result->y = 0.0f;
	result->z = 0.0f;

	Real sampleRadius = ai->m_curLocomotor->m_sampleRadius;
	Real objectRadius = object->m_heightC0;
	Real floorZ = position->z - sampleRadius * Rva001094A50;
	Real best = 0.0f;
	Real x;
	Real y;
	Real terrain;
	Real noFly;
	Real height;

	x = position->x;
	y = position->y;
	terrain = TheTerrainLogic->getGroundHeight(x, y, 0);
	noFly = self->getNoFlyZoneHeight(x, y);
	if (noFly <= terrain)
		noFly = terrain;
	height = noFly - floorZ;
	if (best > height)
		best = height;

	floorZ = position->z - sampleRadius * Rva001094A5C;
	x = position->x - objectRadius;
	y = position->y - sampleRadius;
	terrain = TheTerrainLogic->getGroundHeight(
		x, y, 0);
	noFly = self->getNoFlyZoneHeight(
		x, y);
	if (noFly <= terrain)
		noFly = terrain;
	height = noFly - floorZ;
	if (best > height)
		best = height;

	x = position->x + objectRadius;
	y = position->y - sampleRadius;
	terrain = TheTerrainLogic->getGroundHeight(x, y, 0);
	noFly = self->getNoFlyZoneHeight(
		x, y);
	if (noFly <= terrain)
		noFly = terrain;
	height = noFly - floorZ;
	if (best > height)
		best = height;

	x = position->x + objectRadius;
	y = position->y + sampleRadius;
	terrain = TheTerrainLogic->getGroundHeight(x, y, 0);
	noFly = self->getNoFlyZoneHeight(
		x, y);
	if (noFly <= terrain)
		noFly = terrain;
	height = noFly - floorZ;
	if (best > height)
		best = height;

	x = position->x - objectRadius;
	y = position->y + sampleRadius;
	terrain = TheTerrainLogic->getGroundHeight(x, y, 0);
	noFly = self->getNoFlyZoneHeight(
		x, y);
	if (noFly <= terrain)
		noFly = terrain;
	height = noFly - floorZ;
	if (best > height)
		best = height;

	result->z += best;
	self->bfmeAerialHeight(object, position, &best, result);
	return best > BfmeZeroRange;
}
