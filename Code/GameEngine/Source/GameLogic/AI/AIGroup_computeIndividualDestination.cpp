// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIGroup::computeIndividualDestination, retail 0x00154CE0,
// 428 bytes.
//
// The body follows the reference AIGroup implementation. BFME adds an object
// argument to getLayerForDestination and keeps a fast path for non-ground
// template layers. The object offsets come from the retail field accesses.

#include <math.h>

typedef unsigned char Bool;
typedef float Real;

struct Coord2D
{
	Real x;
	Real y;

	Real length(void) const
	{
		return (Real)sqrt(x * x + y * y);
	}

	void normalize(void)
	{
		Real len = length();
		if (len != 0.0f)
		{
			x /= len;
			y /= len;
		}
	}
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class Object;

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	unsigned char m_unreconstructed_000[4];
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xd4 - 0x08];
	unsigned int m_flags;
};

class LocomotorSet
{
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement(void) const = 0;

	LocomotorSet *getLocomotorSet(void)
	{
		return &m_locomotorSet;
	}

private:
	unsigned char m_unreconstructed_004[0x1a8 - 0x04];
	LocomotorSet m_locomotorSet;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip) const;

	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	bool adjustDestination(Object *object, const LocomotorSet &locomotorSet,
		Coord3D *destination, const Coord3D *groupDestination);
	void updateGoal(Object *object, const Coord3D *destination, int layer,
		const char *reason, int flags);
};

class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return m_pathfinder;
	}

private:
	unsigned char m_unreconstructed_000[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class Object
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}

	AIUpdateInterface *getAIUpdateInterface(void)
	{
		return m_ai;
	}

	Real getBoundingCircleRadius(void) const
	{
		return m_boundingCircleRadius;
	}

	void getFormationOffset(Coord2D *offset) const
	{
		*offset = m_formationOffset;
	}

private:
	unsigned char m_unreconstructed_000[0x04];
	ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unreconstructed_044[0xbc - 0x44];
	Real m_boundingCircleRadius;
	unsigned char m_unreconstructed_0c0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
	unsigned char m_unreconstructed_208[0x320 - 0x208];
	Coord2D m_formationOffset;
};

class AIGroup
{
public:
	void computeIndividualDestination(Coord3D *dest, const Coord3D *groupDest,
		Object *obj, const Coord3D *center, Bool isFormation);
};

// ?computeIndividualDestination@AIGroup@@QAEXPAUCoord3D@@PBU2@PAVObject@@1E@Z
void AIGroup::computeIndividualDestination(Coord3D *individualDestination, const Coord3D *groupDestination,
	Object *object, const Coord3D *groupCenter, Bool isFormation)
{
	const unsigned int flags = object->getTemplate()->m_flags;
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(object, groupDestination);
	if ((flags & 0x1000) != 0 && layer != LAYER_GROUND)
	{
		*individualDestination = *groupDestination;
		return;
	}

	Coord2D v;
	const Coord3D *pos = object->getPosition();
	if (isFormation)
	{
		object->getFormationOffset(&v);
	}
	else
	{
		v.x = pos->x - groupCenter->x;
		v.y = pos->y - groupCenter->y;
	}

	Real length = v.length();
	Real maxLength = 6.0f * object->getBoundingCircleRadius();
	if (length > maxLength)
		length = maxLength;
	v.normalize();
	v.x *= length;
	v.y *= length;

	individualDestination->x = groupDestination->x + v.x;
	individualDestination->y = groupDestination->y + v.y;
	individualDestination->z = TheTerrainLogic->getLayerHeight(individualDestination->x, individualDestination->y, layer, 0, true);

	AIUpdateInterface *ai = object->getAIUpdateInterface();
	if (ai && ai->isDoingGroundMovement())
	{
		Bool adjusted;
		if (isFormation)
			adjusted = TheAI->pathfinder()->adjustDestination(object,
				*ai->getLocomotorSet(), individualDestination, 0);
		else
			adjusted = TheAI->pathfinder()->adjustDestination(object,
				*ai->getLocomotorSet(), individualDestination, groupDestination);
		if (!adjusted)
			*individualDestination = *groupDestination;
		TheAI->pathfinder()->updateGoal(object, individualDestination, 1, (const char *)0x1095f44,
			0x233);
	}
}

#pragma comment(linker, "/alternatename:?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z=?j_000294e2@@YAXXZ")
