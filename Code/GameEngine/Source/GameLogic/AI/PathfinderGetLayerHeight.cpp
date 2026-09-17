// cl: /DNDEBUG /MD /EHs-c-
// BFME retail RVA 0x003D8940, 511 bytes.
// Identity is established by the matched W3DTerrainLogic::getLayerHeight
// caller at 0x006BE2A0 through ILT 0x00029F3C.

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
	{
		ICoord2D cell;
		PathfindCell *pathCell = 0;
		if (!worldToCell(point, &cell))
			pathCell = getCell(layer, cell.x, cell.y);
		if (pathCell != 0 && layer != LAYER_GROUND)
		{
			int actualLayer = pathCell->getLayer();
			if (actualLayer != layer)
			{
				if (actualLayer == 0x10)
				{
					if (bfmeAnyBridgeAt(point))
						goto bridge_scan;
				}
				else
				{
					layer = (PathfindLayerEnum)actualLayer;
				}
			}
		}
	}

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
		first.y -= 10.0f;
		Coord3D second = first;
		second.x += 20.0f;
		Coord3D third = second;
		third.y += 20.0f;
		Coord3D fourth = first;
		fourth.y += 20.0f;

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
