// ?circleClipsTallBuilding@Rva003DCBA0@@IAE_NPBUCoord3D@@0MW4ObjectID@@PAU2@@Z
// partial score=0.38 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/Common /Igame/GameEngine/Source/GameLogic /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// stlport
// Retail 0x003DCBA0: aircraft path circle adjustment around tall buildings.

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

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	const GeometryInfo &getGeometryInfo() const
	{
		return *(const GeometryInfo *)((const char *)this + 0xac);
	}
};

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
	Object *bfmeGo1050D(int a, int b, int c, int d);
};

extern const Real BfmeZeroRange;
extern PartitionManager *ThePartitionManager;

static __declspec(noinline) void computeNormalRadialOffset(
	const Coord3D &from, Coord3D &insert, const Coord3D &to,
	Object *obj, Real radius)
{
	Real crossProduct;
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	const Coord3D *objPos = obj->getPosition();
	Real objDx = objPos->x - from.x;
	Real objDy = objPos->y - from.y;

	crossProduct = dx * objDy - dy * objDx;

	Coord3D fromToNormal;
	fromToNormal.z = 0;
	if (crossProduct > 0) {
		fromToNormal.x = dy;
		fromToNormal.y = -dx;
	} else {
		fromToNormal.x = -dy;
		fromToNormal.y = dx;
	}
	fromToNormal.normalize();
	Real length = radius;
	insert = *objPos;
	insert.x += fromToNormal.x * length;
	insert.y += fromToNormal.y * length;
}

class Rva003DCBA0
{
	protected:
	Bool circleClipsTallBuilding(const Coord3D *from, const Coord3D *to,
		Real circleRadius, ObjectID ignoreBuilding, Coord3D *adjustTo);
};

Bool Rva003DCBA0::circleClipsTallBuilding(const Coord3D *from,
	const Coord3D *to, Real circleRadius, ObjectID ignoreBuilding,
	Coord3D *adjustTo)
{
	Object *tallBuilding;
	{
		PartitionFilterAcceptByKindOf filterKindof(
			MAKE_KINDOF_MASK(Rva003DCBA0KindBit65), KINDOFMASK_NONE);
		tallBuilding = ((BfmeC1050 *)ThePartitionManager)->bfmeGo1050D(
			(int)to, *(const int *)&circleRadius, FROM_BOUNDINGSPHERE_2D,
			(int)&filterKindof);
	}
	if (tallBuilding) {
		Real radius = tallBuilding->getGeometryInfo().getBoundingCircleRadius()
			+ *(const Real *)0x010977E0;
		computeNormalRadialOffset(*from, *adjustTo, *to, tallBuilding,
			circleRadius + radius);
		Object *otherTallBuilding;
		{
			PartitionFilterAcceptByKindOf filterKindof(
				MAKE_KINDOF_MASK(Rva003DCBA0KindBit65), KINDOFMASK_NONE);
			otherTallBuilding = ((BfmeC1050 *)ThePartitionManager)
				->bfmeGo1050D((int)adjustTo, *(const int *)&circleRadius,
					FROM_BOUNDINGSPHERE_2D, (int)&filterKindof);
		}
		if (otherTallBuilding && otherTallBuilding != tallBuilding) {
			radius = otherTallBuilding->getGeometryInfo()
				.getBoundingCircleRadius() + *(const Real *)0x010977E0;
			Coord3D tmpTo = *adjustTo;
			computeNormalRadialOffset(*from, *adjustTo, tmpTo,
				otherTallBuilding, circleRadius + radius);
		}
		return true;
	}
	return false;
}
