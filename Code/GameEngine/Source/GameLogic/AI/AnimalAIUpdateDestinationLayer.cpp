// cl: /DNDEBUG /MD /EHsc

class Object;
struct Coord3D;

enum PathfindLayerEnum
{
	LAYER_GROUND = 0,
	LAYER_WATER = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class AnimalAIUpdateDestinationLayer
{
public:
	unsigned char isReachableLayer(const Coord3D *position) const;

private:
	unsigned char m_beforeObject[8];
	Object *m_object;
};

// @?isReachableLayer@AnimalAIUpdateDestinationLayer@@QBEEPBUCoord3D@@@Z 0x002B3160
unsigned char AnimalAIUpdateDestinationLayer::isReachableLayer(const Coord3D *position) const
{
	if (position == 0)
		return false;

	Object *object = m_object;
	TerrainLogic *terrain = TheTerrainLogic;
	return terrain->getLayerForDestination(object, position) <= LAYER_WATER;
}
