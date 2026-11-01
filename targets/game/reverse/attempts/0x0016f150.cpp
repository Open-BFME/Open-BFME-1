// ?method@Rva0016F150@@QAE_NPAUCoord3D@@PAVObject@@PAX@Z
// partial score=0.7358 date=2026-11-01
// cl: /DNDEBUG /MD /Igame/Libraries/Include
//
// Retail 0x0016F150: 352 bytes, ret 0x0C (this unused).  Reached through
// ILT 0x0002255C from 0x00182F70 (+0x2DC/+0x33C).  Walks a destination
// back toward the object in 10-unit steps (count from the 2D distance
// times -0.05) until Pathfinder::lineClear accepts the segment from the
// candidate to itself on the object's layer, then stores the accepted
// candidate.  No retail name evidence: the method keeps the address name.

#include <math.h>
#include "Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class AIUpdateInterface
{
public:
	char m_unreconstructed000[0x1b8];
	Int m_1b8;
};

class Object
{
public:
	Int getLayer() const;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	char m_unreconstructed000[0x38];
	Coord3D m_position;
	char m_unreconstructed044[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class Pathfinder
{
public:
	Int lineClear(Object *obj, Int locomotorSet, PathfindLayerEnum layer,
		const Coord3D *from, const Coord3D *to);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

	char m_unreconstructed00[0x0c];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

inline Real coordLength(const Coord3D &c)
{
	return (Real)sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
}

inline Real coordLength2D(const Coord3D &c)
{
	return (Real)sqrt(c.x * c.x + c.y * c.y);
}

inline void coordNormalize(Coord3D &c)
{
	Real inv = 1.0f / coordLength(c);
	c.x *= inv;
	c.y *= inv;
	c.z *= inv;
}

inline void coordScale(Coord3D &c, Real s)
{
	c.x *= s;
	c.y *= s;
	c.z *= s;
}

class Rva0016F150
{
public:
	Bool method(Coord3D *destination, Object *obj, void *unused);
};

// ?method@Rva0016F150@@QAE_NPAUCoord3D@@PAVObject@@PAX@Z
Bool Rva0016F150::method(Coord3D *destination, Object *obj, void *unused)
{
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return false;

	Coord3D candidate;
	candidate.x = destination->x;
	candidate.y = destination->y;
	candidate.z = destination->z;
	Coord3D dir;
	dir.x = destination->x;
	dir.y = destination->y;
	dir.z = 0.0f;
	dir.x -= obj->getPosition()->x;
	dir.y -= obj->getPosition()->y;
	Int count = -(Int)(coordLength2D(dir) * -0.05f) - 1;
	coordNormalize(dir);
	coordScale(dir, 10.0f);

	for (Int i = 0; i < count; i++)
	{
		Int loco = ai->m_1b8;
		if ((unsigned char)TheAI->pathfinder()->lineClear(obj, loco,
				(PathfindLayerEnum)obj->getLayer(), &candidate, &candidate))
		{
			*destination = candidate;
			return true;
		}
		candidate.x -= dir.x;
		candidate.y -= dir.y;
		candidate.z -= dir.z;
	}
	return false;
}
