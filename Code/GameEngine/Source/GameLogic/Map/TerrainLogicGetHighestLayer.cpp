// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?getHighestLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PBUCoord3D@@_N@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// TerrainLogic::getHighestLayerForDestination, retail 0x001A7D60.

#include <math.h>

typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum BodyDamageType
{
	BODY_RUBBLE = 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	Bool isPointOnBridge(const Coord3D *point);
	Real getBridgeHeight(const Coord3D *point, Coord3D *normal);

private:
	unsigned char m_pad00[0x5C];
	int m_damageState;
	unsigned char m_pad60[0x28];
	int m_layer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void preSlot0();
	virtual void preSlot1();
	virtual void preSlot2();
	virtual void preSlot3();
	virtual void preSlot4();
	virtual void preSlot5();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Bridge *getFirstBridge();

	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *point, Bool onlyHealthyBridges);
};

extern Real g_bfmeZero1075350;

PathfindLayerEnum TerrainLogic::getHighestLayerForDestination(const Coord3D *point, Bool onlyHealthyBridges)
{
	PathfindLayerEnum bestLayer = LAYER_GROUND;
	Real bestDistance = point->z - getGroundHeight(point->x, point->y, 0);

	for (Bridge *bridge = getFirstBridge(); bridge != 0; bridge = *(Bridge **)((unsigned char *)bridge + 4))
	{
		if (onlyHealthyBridges && *(int *)((unsigned char *)bridge + 0x5C) == BODY_RUBBLE)
			continue;

		if (bridge->isPointOnBridge(point))
		{
			Real delta = point->z - bridge->getBridgeHeight(point, 0);
			if (delta >= g_bfmeZero1075350 &&
				fabs(delta) < fabs(bestDistance))
			{
				bestLayer = (PathfindLayerEnum)*(int *)((unsigned char *)bridge + 0x88);
				bestDistance = delta;
			}
		}
	}
	return bestLayer;
}
