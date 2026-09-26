// ?bfmeSampleAirspace@AerialPathfinder@@QAEHPAVObject@@PBUCoord3D@@PAU3@@Z
// partial score=0.97 date=2026-09-24
// cl: /O2 /DNDEBUG /MD /EHsc-
//
// Retail 0x00149130, called five times by 0x00149470 with this, Object*,
// const Coord3D*, Coord3D* (ret 0x0C). Samples terrain/no-fly ceiling at the
// centre and four corners offset by Object+0xC0 and returns clearance > 0.

typedef int Int;
typedef float Real;
typedef bool Bool;

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
	// retail 0x00148C70: thiscall, ret 0x10, returns AL, raises *sample
	Bool bfmeAerialHeight(Object *object, const Coord3D *from,
		Real *sample, Coord3D *result);
	Int bfmeSampleAirspace(Object *object, const Coord3D *position,
		Coord3D *result);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

// Height of the higher of terrain and no-fly ceiling above pt.z.
inline Real Rva00149130HeightAbove(AerialPathfinder *self, const Coord3D &pt)
{
	Real terrain = TheTerrainLogic->getGroundHeight(pt.x, pt.y, 0);
	Real noFly = self->getNoFlyZoneHeight(pt.x, pt.y);
	return (noFly > terrain ? noFly : terrain) - pt.z;
}

// ?bfmeSampleAirspace@AerialPathfinder@@QAEHPAVObject@@PBUCoord3D@@PAU3@@Z
Int AerialPathfinder::bfmeSampleAirspace(Object *object,
	const Coord3D *position, Coord3D *result)
{
	AIUpdateInterface *ai = object->m_ai;
	if (ai == 0)
		return 2;

	result->x = 0.0f;
	result->y = 0.0f;
	result->z = 0.0f;

	Real best;
	Real sampleRadius = ai->m_curLocomotor->m_sampleRadius;
	Real halfRadius = sampleRadius * 0.5f;
	Real objectRadius = object->m_heightC0;
	Coord3D pt;
	Real height;
	{
		pt.x = position->x;
		pt.y = position->y;
		pt.z = position->z - halfRadius;
		best = 0.0f;
		height = Rva00149130HeightAbove(this, pt);
		if (0.0f < height)
			best = height;
	}
	{
		pt.x = position->x - objectRadius;
		pt.y = position->y - objectRadius;
		pt.z = position->z - sampleRadius * 0.3885f;
		height = Rva00149130HeightAbove(this, pt);
		if (best < height)
			best = height;
	}
	{
		pt.y = position->y + objectRadius;
		height = Rva00149130HeightAbove(this, pt);
		if (best < height)
			best = height;
	}
	{
		pt.x = position->x + objectRadius;
		height = Rva00149130HeightAbove(this, pt);
		if (best < height)
			best = height;
	}
	{
		Real sampleY = position->y - objectRadius;
		Real terrain = TheTerrainLogic->getGroundHeight(pt.x, sampleY, 0);
		Real noFly = getNoFlyZoneHeight(pt.x, sampleY);
		height = (noFly > terrain ? noFly : terrain) - pt.z;
		if (best < height)
			best = height;
	}
	result->z += best;
	bfmeAerialHeight(object, position, &best, result);
	return best > 0.0f;
}
