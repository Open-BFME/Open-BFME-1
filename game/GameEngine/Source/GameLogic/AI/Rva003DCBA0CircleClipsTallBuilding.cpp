// ?circleClipsTallBuilding@Rva003DCBA0@@IAE_NPBUCoord3D@@0MW4ObjectID@@PAU2@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/Common /Igame/GameEngine/Source/GameLogic /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport

#define ASCIISTRING_H
#include "ascii_string.h"
#define __THING_H_
#define __KINDOF_H_
#include "PreRTS.h"
#include "Common/BitFlags.h"

typedef BitFlags<192> KindOfMaskType;
enum KindOfType { Rva003DCBA0KindBit65 = 65 };
#define MAKE_KINDOF_MASK(bit) KindOfMaskType(KindOfMaskType::kInit, (bit))
extern const KindOfMaskType KINDOFMASK_NONE;

class GeometryInfo
{
public:
	Real getBoundingCircleRadius() const
	{
		return *(const Real *)((const char *)this + 0x10);
	}
};

#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS const GeometryInfo &getGeometryInfo() const { return *(const GeometryInfo *)m_geometryInfo; }
#include "object.h"

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual int getPlayerMask();
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

private:
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

__declspec(noinline) PartitionFilterAcceptByKindOf::PartitionFilterAcceptByKindOf(
    const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear)
    : m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_BOUNDINGSPHERE_2D = 1
};

class PartitionManager
{
};

class BfmeC1050
{
public:
	void *bfmeGo1050D(int a, int b, int c, int d);
};

extern PartitionManager *ThePartitionManager;

// ?rva003d60e0RadialOffset@@YAXABUCoord3D@@AAU1@0PAVObject@@M@Z
static __declspec(noinline) void rva003d60e0RadialOffset(const Coord3D &from, Coord3D &insert, const Coord3D &to, Object *obj, Real radius)
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Coord3D objPos;
	objPos.set(obj->getPosition());
	Real objDx = objPos.x - from.x;
	Real objDy = objPos.y - from.y;
	Real cross = dx * objDy - dy * objDx;
	struct { Real x, y; } normal;
	if (cross > 0.0f)
	{
		normal.x = dy;
		normal.y = -dx;
	}
	else
	{
		normal.x = -dy;
		normal.y = dx;
	}
	// Normalize the two-dimensional offset by its reciprocal length.
	Real normalLen = (Real)sqrt(normal.x * normal.x + normal.y * normal.y);
	if (normalLen != 0.0f)
	{
		Real inv = 1.0f / normalLen;
		normal.x *= inv;
		normal.y *= inv;
	}
	insert = *obj->getPosition();
	insert.x += normal.x * radius;
	insert.y += normal.y * radius;
}


// ?computeNormalRadialOffset@@YAXABUCoord3D@@AAU1@0PAVObject@@M@Z absent-from-retail
static __forceinline void computeNormalRadialOffset(const Coord3D &from, Coord3D &insert, const Coord3D &to, Object *obj, Real radius)
{
	rva003d60e0RadialOffset(from, insert, to, obj, radius);
}

class Rva003DCBA0
{
	protected:
	Bool circleClipsTallBuilding(const Coord3D *from, const Coord3D *to,
		Real circleRadius, ObjectID ignoreBuilding, Coord3D *adjustTo);
};

// ?circleClipsTallBuilding@Rva003DCBA0@@IAE_NPBUCoord3D@@0MW4ObjectID@@PAU2@@Z
Bool Rva003DCBA0::circleClipsTallBuilding(const Coord3D *from,
	const Coord3D *to, Real circleRadius, ObjectID ignoreBuilding,
	Coord3D *adjustTo)
{
	Object *tallBuilding = (Object *)((BfmeC1050 *)ThePartitionManager)->bfmeGo1050D(
		(int)to, *(const int *)&circleRadius, FROM_BOUNDINGSPHERE_2D,
		(int)&PartitionFilterAcceptByKindOf(MAKE_KINDOF_MASK(Rva003DCBA0KindBit65), KINDOFMASK_NONE));
	if (tallBuilding) {
		Real radius = tallBuilding->getGeometryInfo().getBoundingCircleRadius()
			+ 20.0f;
		computeNormalRadialOffset(*from, *adjustTo, *to, tallBuilding,
			circleRadius + radius);
		Object *otherTallBuilding = (Object *)((BfmeC1050 *)ThePartitionManager)->bfmeGo1050D(
			(int)adjustTo, *(const int *)&circleRadius, FROM_BOUNDINGSPHERE_2D,
			(int)&PartitionFilterAcceptByKindOf(MAKE_KINDOF_MASK(Rva003DCBA0KindBit65), KINDOFMASK_NONE));
		if (otherTallBuilding && otherTallBuilding != tallBuilding) {
			radius = otherTallBuilding->getGeometryInfo()
				.getBoundingCircleRadius() + 20.0f;
			Coord3D tmpTo = {adjustTo->x, adjustTo->y, adjustTo->z};
			computeNormalRadialOffset(*from, *adjustTo, tmpTo,
				otherTallBuilding, circleRadius + radius);
		}
		return true;
	}
	return false;
}
