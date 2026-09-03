// cl: /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?getWaterHandle@TerrainLogic@@UAEPBVWaterHandle@@MM@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "GameLogic/TerrainLogic.h"

class PolygonTrigger;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class WaterHandle
{
public:
	PolygonTrigger *polygon;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	void *vtable;
	PolygonTrigger *next;
	UnsignedByte pad08[8];
	ICoord3D *points;
	Int numPoints;
	UnsignedByte pad18[0x1a];
	Bool waterArea;
	UnsignedByte pad33[9];
	WaterHandle waterHandle;

	PolygonTrigger *getNext() { return next; }
	Bool isWaterArea() const { return waterArea; }
	const ICoord3D *getPoint(Int index) const
	{
		if (index < 0)
			index = 0;
		if (index >= numPoints)
			index = numPoints - 1;
		return points + index;
	}
	Bool pointInTrigger(ICoord3D &point) const;
	const WaterHandle *getWaterHandle() const;
};

struct BfmePolygonTriggerTable
{
	PolygonTrigger *head;
};

class BfmeTerrainVisual
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual Bool getWaterGridHeight(Real x, Real y, Real *height) = 0;
};

extern "C" BfmePolygonTriggerTable *g_bfmePolygonTriggerTable;
extern "C" BfmeTerrainVisual *g_bfmeTerrainVisual;
extern "C" WaterHandle g_bfmeGridWaterHandle;

const WaterHandle *TerrainLogic::getWaterHandle(Real x, Real y)
{
	const WaterHandle *waterHandle = NULL;
	Real waterZ = 0.0f;
	ICoord3D location;

	location.x = (Int)x;
	location.y = (Int)y;
	location.z = 0;

	for (PolygonTrigger *trigger = g_bfmePolygonTriggerTable->head; trigger; trigger = trigger->getNext()) {
		if (trigger->isWaterArea() && trigger->pointInTrigger(location) && trigger->getPoint(0)->z >= waterZ) {
			waterZ = trigger->getPoint(0)->z;
			waterHandle = trigger->getWaterHandle();
		}
	}

	Real meshZ;
	if (g_bfmeTerrainVisual->getWaterGridHeight(x, y, &meshZ) && meshZ >= waterZ) {
		waterHandle = &g_bfmeGridWaterHandle;
	}

	return waterHandle;
}
