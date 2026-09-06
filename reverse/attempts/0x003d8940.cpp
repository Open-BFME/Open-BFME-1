// ?d_003d8940@@YAXXZ
// partial score=0.8 date=2026-09-06
// cl: /DNDEBUG /MD /EHs-c-
// Pathfinder::getLayerHeight, retail 0x003D8940.

typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	int x;
	int y;
};

class PathfindCell
{
public:
	int getLayer(void) const
	{
		return (m_flags >> 6) & 0x3F;
	}

private:
	unsigned char m_pad00[0x0C];
	unsigned int m_flags;
};

class Bridge
{
public:
	Bool isPointOnBridge(const Coord3D *point);
	Real getBridgeHeight(const Coord3D *point, Coord3D *normal);

	unsigned char m_pad00[4];
	Bridge *m_next;
};

class Bfme5BridgeList
{
public:
	char bfmeAnyBridgeAt(const Coord3D *point);

	unsigned char m_pad00[0x858];
	Bridge *m_bridgeList;
};

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
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder : public Bfme5BridgeList
{
public:
	Bool worldToCell(const Coord3D *point, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
	Real getLayerHeight(PathfindLayerEnum layer, const Coord3D *point,
		Coord3D *normal);

	private:
	unsigned char m_pad858[0x243B8 - 0x85C];
	Real m_layerHeights[64];
};

Real Pathfinder::getLayerHeight(PathfindLayerEnum layer,
	const Coord3D *point, Coord3D *normal)
{
	int actualLayer;
	{
		ICoord2D cell;
		if (worldToCell(point, &cell))
		{
			actualLayer = 1;
			goto dispatch_layer;
		}

		PathfindCell *pathCell = getCell(layer, cell.x, cell.y);
		if (pathCell == 0)
		{
			actualLayer = 0;
			goto dispatch_layer;
		}
		if (layer == LAYER_GROUND)
			goto ground_height;

		actualLayer = pathCell->getLayer();
		if (actualLayer == layer)
			goto dispatch_layer;
		if (actualLayer == 0x10)
		{
			if (bfmeAnyBridgeAt(point))
				goto bridge_scan;
			actualLayer = 0;
		}
	}

dispatch_layer:
	layer = (PathfindLayerEnum)actualLayer;
	if (layer == LAYER_GROUND)
		goto ground_height;
	if (layer >= 0x11 && layer <= 0x40)
	{
		Real height = m_layerHeights[layer];
		if (normal != 0)
		{
			normal->x = 0;
			normal->y = 0;
			normal->z = 1;
		}
		return height;
	}
	if (layer != 0x10)
		return point->z;

bridge_scan:
	{
		Bridge *bridge = m_bridgeList;
		while (bridge != 0)
		{
			if (bridge->isPointOnBridge(point))
				return bridge->getBridgeHeight(point, normal);
			bridge = bridge->m_next;
		}

		Coord3D first = *point;
		first.x -= 10.0f;
		Coord3D second = first;
		second.y += 10.0f;
		Coord3D third = second;
		third.x += 10.0f;
		Coord3D fourth = third;
		fourth.y += 10.0f;

		for (bridge = m_bridgeList; bridge != 0; bridge = bridge->m_next)
		{
			if (bridge->isPointOnBridge(&first) ||
				bridge->isPointOnBridge(&second) ||
				bridge->isPointOnBridge(&third) ||
				bridge->isPointOnBridge(&fourth))
				return bridge->getBridgeHeight(point, normal);
		}
	}

	return point->z;

ground_height:
	return TheTerrainLogic->getGroundHeight(point->x, point->y, normal);
}
