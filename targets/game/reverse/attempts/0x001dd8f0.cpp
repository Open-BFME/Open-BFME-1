// ?bfmeRunEQT@BfmeObjEQT@@QAEDPAX@Z
// partial score=0.6932 date=2026-10-04
struct Coord3D
{
	float x;
	float y;
	float z;

	void set(const Coord3D *sourcePosition)
	{
		x = sourcePosition->x;
		y = sourcePosition->y;
		z = sourcePosition->z;
	}
};

#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS const Coord3D *getPosition() const;
#include "../../../../game/GameEngine/Source/GameLogic/Object/object.h"

inline const Coord3D *Thing::getPosition() const
{
	return &m_cachedPos;
}

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition(void) const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class TerrainLogic
{
public:
#define BFME_TERRAIN_SLOT(n) virtual void terrainSlot##n(void) = 0
	BFME_TERRAIN_SLOT(00); BFME_TERRAIN_SLOT(01); BFME_TERRAIN_SLOT(02); BFME_TERRAIN_SLOT(03);
	BFME_TERRAIN_SLOT(04); BFME_TERRAIN_SLOT(05); BFME_TERRAIN_SLOT(06); BFME_TERRAIN_SLOT(07);
	BFME_TERRAIN_SLOT(08); BFME_TERRAIN_SLOT(09); BFME_TERRAIN_SLOT(10); BFME_TERRAIN_SLOT(11);
	BFME_TERRAIN_SLOT(12); BFME_TERRAIN_SLOT(13); BFME_TERRAIN_SLOT(14);
#undef BFME_TERRAIN_SLOT
	virtual bool isClearLineOfSight(const Coord3D &pos, const Coord3D &posOther) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

class BfmeSubEQT
{
public:
	char bfmeAEQT();
	char bfmeBEQT();
};

class BfmeHoldEQT
{
public:
	unsigned char m_bfmeHeadEQT[4];
	BfmeSubEQT *m_bfmeSubEQT;
};

class BfmeThingEQT
{
public:
	char bfmeCEQT(int what);
};

class BfmeBaseEQT
{
public:
	BfmeBaseEQT() { m_bfmeZeroEQT = 0; }

	int m_bfmeZeroEQT;
};

class BfmeObjEQT : public BfmeBaseEQT
{
public:
	BfmeObjEQT(BfmeThingEQT *owner) { m_bfmeOwnerEQT = owner; }
	virtual ~BfmeObjEQT() {}

	char bfmeRunEQT(void *arg);

	BfmeThingEQT *m_bfmeOwnerEQT;
};

char bfmeCheckEQT(BfmeThingEQT *thing, void *arg, BfmeHoldEQT *hold)
{
	if (hold != 0 && arg != 0 &&
		!hold->m_bfmeSubEQT->bfmeAEQT() &&
		!hold->m_bfmeSubEQT->bfmeBEQT() &&
		thing->bfmeCEQT(0x3a))
	{
		BfmeObjEQT obj(thing);

		if (!obj.bfmeRunEQT(arg))
			return 0;
	}

	return 1;
}

class Pathfinder
{
public:
	void bfmeAdjustLOSPoints(Coord3D *victimPos, Coord3D *origin);
	bool isAttackViewBlockedByObstacle(const Object *source, const Object *target);
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AI;
extern AI *TheAI;

char BfmeObjEQT::bfmeRunEQT(void *arg)
{
	Object *object;
	const Coord3D *ownerPosition = ((Object *)m_bfmeOwnerEQT)->getPosition();
	Coord3D origin;
	origin.x = ownerPosition->x;
	origin.y = ownerPosition->y;
	unsigned int originZ = *(const unsigned int *)((const unsigned char *)ownerPosition + 8);
	_ReadWriteBarrier();
	object = (Object *)arg;
	const Coord3D *objectPosition = object->getPosition();
	Coord3D victimPos;
	victimPos.set(objectPosition);
	*(unsigned int *)((unsigned char *)&origin + 8) = originZ;

	Overridable *objectTemplate = (Overridable *)object->m_template;
	if (objectTemplate != 0)
	{
		Overridable *nextOverride = *(Overridable **)((unsigned char *)objectTemplate + 4);
		if (nextOverride != 0)
			objectTemplate = (Overridable *)nextOverride->getFinalOverride();
		if (*(const unsigned int *)((const unsigned char *)objectTemplate + 0xCC) & 0x08000000)
		{
			AI *ai = TheAI;
			Pathfinder *pathfinder = ai != 0 ? *(Pathfinder **)((unsigned char *)ai + 0x0C) : 0;
			if (pathfinder != 0)
				pathfinder->bfmeAdjustLOSPoints(&victimPos, &origin);
		}
	}

	Object *owner = (Object *)m_bfmeOwnerEQT;
	Overridable *ownerTemplate = (Overridable *)owner->m_template;
	if (ownerTemplate != 0)
	{
		Overridable *nextOverride = *(Overridable **)((unsigned char *)ownerTemplate + 4);
		if (nextOverride != 0)
			ownerTemplate = (Overridable *)nextOverride->getFinalOverride();
	}
	if ((*(const unsigned char *)((const unsigned char *)ownerTemplate + 0xC8) & 0x80) != 0)
		goto skipGeometryHeight;
	origin.z += ((GeometryInfo *)((unsigned char *)owner + 0xAC))->getMaxHeightAbovePosition();
	victimPos.z += ((GeometryInfo *)((unsigned char *)object + 0xAC))->getMaxHeightAbovePosition();
skipGeometryHeight:

	if (!TheTerrainLogic->isClearLineOfSight(*(const Coord3D *)&origin,
		*(const Coord3D *)&victimPos))
		return 0;

	AI *ai = TheAI;
	Pathfinder *pathfinder = ai != 0 ? *(Pathfinder **)((unsigned char *)ai + 0x0C) : 0;
	if (pathfinder != 0 &&
		pathfinder->isAttackViewBlockedByObstacle((const Object *)m_bfmeOwnerEQT, (const Object *)object))
		return 0;

	return 1;
}
