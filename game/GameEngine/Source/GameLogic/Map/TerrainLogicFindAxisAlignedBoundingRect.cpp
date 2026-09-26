// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// BFME's ICoord3D has an out-of-line empty constructor; the Zero Hour
// compatibility headers expose plain coordinate aggregates instead.
#define ICoord2D ZeroHourPlainICoord2D
#define ICoord3D ZeroHourPlainICoord3D
#include "PreRTS.h"
#include "GameLogic/TerrainLogic.h"
#include "GameClient/TerrainVisual.h"
#include "GameLogic/PolygonTrigger.h"
#include "WWMath/matrix3d.h"
#undef ICoord2D
#undef ICoord3D
#include "../../../../Libraries/Source/WWVegas/WWMath/icoord.h"

// Retail 0x001A66C0 agrees with the Zero Hour water-extents algorithm.
// The grid identity and virtual water queries also appear in setWaterHeight.
// BFME moved PolygonTrigger's points/count to +0x10/+0x14 and the water
// transform/resolution slots to +0x3c/+0x44 respectively.
struct Rva001A66C0PolygonView
{
    char m_unreconstructed_00[0x10];
    ICoord3D *m_points;
    int m_numPoints;
    const ICoord3D *getPoint(int index) const
    {
        if (index < 0) index = 0;
        if (index >= m_numPoints) index = m_numPoints - 1;
        return m_points + index;
    }
};
class Rva001A66C0TerrainVisualView
{
public:
    virtual void v00() = 0; virtual void v01() = 0;
    virtual void v02() = 0; virtual void v03() = 0;
    virtual void v04() = 0; virtual void v05() = 0;
    virtual void v06() = 0; virtual void v07() = 0;
    virtual void v08() = 0; virtual void v09() = 0;
    virtual void v10() = 0; virtual void v11() = 0;
    virtual void v12() = 0; virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void getWaterTransform(const WaterHandle *, Matrix3D *) = 0;
    virtual void v16() = 0;
    virtual void getWaterGridResolution(const WaterHandle *, Real *, Real *, Real *) = 0;
};

void TerrainLogic::findAxisAlignedBoundingRect( const WaterHandle *water, Region3D *region )
{

	// sanity
	if( water == NULL || region == NULL )
		return;

	// setup the lo and high of the region to the *opposite* side of the map plus some big number
	#define BUFFER 99999.9f  /// just to have extreme regions outside of the map
	Region3D mapExtent;
	getExtent( &mapExtent );
	region->lo.x = mapExtent.hi.x + BUFFER;
	region->lo.y = mapExtent.hi.y + BUFFER;
	region->hi.x = mapExtent.lo.x - BUFFER;
	region->hi.y = mapExtent.lo.y - BUFFER;
	// for water grid we must access the transform
	if( water == &m_gridWaterHandle )
	{
		Int i;
		ICoord3D p[ 4 ];

		// compute the 4 corners of the table according to the grids and grid spacing
		Real gridX, gridY, cellSize;
		((Rva001A66C0TerrainVisualView *)TheTerrainVisual)->getWaterGridResolution( water, &gridX, &gridY, &cellSize );
		p[ 0 ].x = 0;
		p[ 0 ].y = 0;
		p[ 1 ].x = gridX * cellSize;
		p[ 1 ].y = 0;
		p[ 2 ].x = gridX * cellSize;
		p[ 2 ].y = gridY * cellSize;
		p[ 3 ].x = 0;
		p[ 3 ].y = gridY * cellSize;

		// transform the 4 points using the transform matrix of the water
		Vector3 v;
		Matrix3D transform;
		((Rva001A66C0TerrainVisualView *)TheTerrainVisual)->getWaterTransform( water, &transform );
		for( i = 0; i < 4; i++ )
		{

			v.Set( p[ i ].x, p[ i ].y, p[ i ].z );
			transform.Transform_Vector( transform, v, &v );

			// do the region compares
			if( v.X < region->lo.x )
				region->lo.x = v.X;
			if( v.X > region->hi.x )
				region->hi.x = v.X;
			if( v.Y < region->lo.y )
				region->lo.y = v.Y;
			if( v.Y > region->hi.y )
				region->hi.y = v.Y;

		}  // end for i

	}  // end if
	else
	{

		// go through each polygon point and find the extents
		const ICoord3D *p;
		const Rva001A66C0PolygonView *polygon = (const Rva001A66C0PolygonView *)water->m_polygon;
		Int numPoints = polygon->m_numPoints;
		for( Int i = 0; i < numPoints; i++ )
		{
		
			// get this point
			p = ((const Rva001A66C0PolygonView *)water->m_polygon)->getPoint( i );

			// compare to our region
			if( p->x < region->lo.x )
				region->lo.x = p->x;
			if( p->x > region->hi.x )
				region->hi.x = p->x;

			if( p->y < region->lo.y )
				region->lo.y = p->y;
			if( p->y > region->hi.y )
				region->hi.y = p->y;

			if( p->z < region->lo.z )
				region->lo.z = p->z;
			if( p->z > region->hi.z )
				region->hi.z = p->z;

		}  // end for i
				
	}  // end else

}  // end findAxisAlignedBoundingRect
