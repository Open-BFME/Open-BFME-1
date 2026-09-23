// ?findClosestEdgePoint@TerrainLogic@@UBE?AUCoord3D@@PBU2@@Z
// partial score=0.93 date=2026-09-23
// cl: /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/TerrainLogic.h"

// BFME's getGroundHeight is virtual slot 6; the imported TerrainLogic header
// still puts it at slot 5. Keep this call on the retail slot until the shared
// declaration can be corrected across its other users.
class BfmeTerrainGroundHeightView
{
public:
	virtual void slot0() const = 0;
	virtual void slot1() const = 0;
	virtual void slot2() const = 0;
	virtual void slot3() const = 0;
	virtual void slot4() const = 0;
	virtual void slot5() const = 0;
	virtual Real getGroundHeightBits(UnsignedInt xBits, UnsignedInt yBits,
		Coord3D *normal) const = 0;
};

// ?findClosestEdgePoint@TerrainLogic@@UBE?AUCoord3D@@PBU2@@Z present-unmatched
Coord3D TerrainLogic::findClosestEdgePoint ( const Coord3D *closestTo ) const
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

	Coord3D retVal;
	volatile Coord3D *storedRetVal = &retVal;
	storedRetVal->x = closestTo->x;
	storedRetVal->y = closestTo->y;
	if( bestDistanceIndex == 0 )
	{
		storedRetVal->y = mapExtent.lo.y;
	}
	else if( bestDistanceIndex == 1 )
	{
		storedRetVal->x = mapExtent.hi.x;
	}
	else if( bestDistanceIndex == 2 )
	{
		storedRetVal->y = mapExtent.hi.y;
	}
	else
	{
		storedRetVal->x = mapExtent.lo.x;
	}

	retVal.z = reinterpret_cast<const BfmeTerrainGroundHeightView *>(this)->getGroundHeightBits(
		*reinterpret_cast<const volatile UnsignedInt *>(&retVal.x),
		*reinterpret_cast<const volatile UnsignedInt *>(&retVal.y), NULL);

	return retVal;

}
