// ?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBUCoord3D@@@Z
// partial score=0.82 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc
//
// BFME adds this Object-aware overload after the Zero Hour source branch.  The
// TerrainLogic vtable slice below preserves the two retail virtual slots used
// here: getGroundHeight at +0x18 and getFirstBridge at +0x94.

#include <math.h>

typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

class Bridge
{
public:
	bool isPointOnBridge(const Coord3D *position);
	Real getBridgeHeight(const Coord3D *position, Coord3D *normal);

	Bridge *getNext() const { return m_next; }
	PathfindLayerEnum getLayer() const { return m_layer; }

private:
	unsigned char m_pad0[4];
	Bridge *m_next;
	unsigned char m_pad8[0x80];
	PathfindLayerEnum m_layer;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
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
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual Bridge *getFirstBridge();

	PathfindLayerEnum getLayerForDestination(
		Object *object, const Coord3D *position);
};

class Bfme5BridgeList
{
public:
	char bfmeAnyBridgeAt(const Coord3D *position);
};

class Pathfinder : public Bfme5BridgeList
{
public:
	int bfmeLayerForPosition(Object *object, Coord3D position);
};

class AI
{
private:
	unsigned char m_pad0[0x0C];
	Pathfinder *m_pathfinder;

public:
	Pathfinder *pathfinder() { return m_pathfinder; }
};

extern "C" AI *volatile _TheAIParseDefinitionAI;

// ?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBUCoord3D@@@Z
PathfindLayerEnum TerrainLogic::getLayerForDestination(
	Object *object, const Coord3D *position)
{
	Bridge *bridge = getFirstBridge();
	PathfindLayerEnum bestLayer = LAYER_GROUND;
	Real bestDistance = (Real)fabs(position->z -
		getGroundHeight(position->x, position->y, 0));

	while (bridge)
	{
		if (bridge->isPointOnBridge(position))
		{
			Real delta = (Real)fabs(position->z -
				bridge->getBridgeHeight(position, 0));
			if (delta < bestDistance)
			{
				bestLayer = bridge->getLayer();
				bestDistance = delta;
			}
		}
		bridge = bridge->getNext();
	}

	if (bestLayer == LAYER_GROUND)
	{
		AI *ai;

		if (_TheAIParseDefinitionAI->pathfinder()->bfmeAnyBridgeAt(position))
			return (PathfindLayerEnum)16;

		ai = _TheAIParseDefinitionAI;
		if (ai && ai->pathfinder())
			return (PathfindLayerEnum)_TheAIParseDefinitionAI->pathfinder()->
				bfmeLayerForPosition(object, *position);
	}

	return bestLayer;
}
