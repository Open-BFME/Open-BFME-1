// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// TerrainLogic::findClosestEdgePoint, retail 0x001A3770 (253 bytes). The
// TerrainLogic vtables installed by its constructors (0x0109C428, 0x0111D090)
// hold it in slot 13, and BFME's getExtent and getGroundHeight sit in slots 8
// and 6. The body is Zero Hour TerrainLogic.cpp as written.
//
// Coord3D carries an inline field-wise copy constructor here, the lever from
// docs/shape_levers.md "A float pair written through an out pointer": the
// returned copy then moves x through the FPU, y through an integer register
// and z straight from the getGroundHeight result, as retail does. With
// BaseType.h's constructor-less Coord3D the copy goes through integer
// registers and the height is spilled first.
#include <math.h>

typedef float Real;
typedef int Int;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

class TerrainLogic
{
public:
	virtual void slot0() const;
	virtual void slot1() const;
	virtual void slot2() const;
	virtual void slot3() const;
	virtual void slot4() const;
	virtual void slot5() const;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual void slot7() const;
	virtual void getExtent(Region3D *extent) const;
	virtual Coord3D findClosestEdgePoint(const Coord3D *closestTo) const;
};

// ?findClosestEdgePoint@TerrainLogic@@UBE?AUCoord3D@@PBU2@@Z
Coord3D TerrainLogic::findClosestEdgePoint( const Coord3D *closestTo ) const
{
	Region3D mapExtent;
	getExtent( &mapExtent );

	Real distances[4];
	distances[0] = fabs( closestTo->y - mapExtent.lo.y );//top
	distances[1] = fabs( closestTo->x - mapExtent.hi.x );//right
	distances[2] = fabs( closestTo->y - mapExtent.hi.y );//bottom
	distances[3] = fabs( closestTo->x - mapExtent.lo.x );//left
	Real bestDistance = distances[0];
	Int bestDistanceIndex = 0;
	for( Int lameIndex = 1; lameIndex < 4; lameIndex++ )
	{
		if( distances[lameIndex] < bestDistance )
		{
			bestDistance = distances[lameIndex];
			bestDistanceIndex = lameIndex;
		}
	}

	Coord3D retVal = *closestTo;
	if( bestDistanceIndex == 0 )
		retVal.y = mapExtent.lo.y;
	else if( bestDistanceIndex == 1 )
		retVal.x = mapExtent.hi.x;
	else if( bestDistanceIndex == 2 )
		retVal.y = mapExtent.hi.y;
	else
		retVal.x = mapExtent.lo.x;

	retVal.z = getGroundHeight( retVal.x, retVal.y );
	return retVal;
}
