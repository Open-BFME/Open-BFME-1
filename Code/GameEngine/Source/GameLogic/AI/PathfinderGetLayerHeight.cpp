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
	Bool isPointOnBridge(const Coord3D *worldPosition);
	Real getBridgeHeight(const Coord3D *worldPosition, Coord3D *surfaceNormal);

	unsigned char m_pad00[4];
	Bridge *m_next;
};

class Bfme5BridgeList
{
public:
	char bfmeAnyBridgeAt(const Coord3D *worldPosition);

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
	virtual Real getGroundHeight(Real worldX, Real worldY, Coord3D *surfaceNormal);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder : public Bfme5BridgeList
{
public:
	Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);
	PathfindCell *getCell(PathfindLayerEnum layer, int cellX, int cellY);
	Real getLayerHeight(PathfindLayerEnum layer, const Coord3D *worldPosition,
		Coord3D *surfaceNormal);

private:
	unsigned char m_pad858[0x243B8 - 0x85C];
	Real m_layerHeights[64];
};

Real Pathfinder::getLayerHeight(PathfindLayerEnum layer,
	const Coord3D *worldPosition, Coord3D *surfaceNormal)
{
	{
		ICoord2D cellIndex;
		PathfindCell *pathCell = 0;
		if (!worldToCell(worldPosition, &cellIndex))
			pathCell = getCell(layer, cellIndex.x, cellIndex.y);
		if (pathCell != 0 && layer != LAYER_GROUND)
		{
			int actualLayer = pathCell->getLayer();
			if (actualLayer != layer)
			{
				if (actualLayer == 0x10)
				{
					if (bfmeAnyBridgeAt(worldPosition))
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
		if (surfaceNormal != 0)
		{
			surfaceNormal->x = 0;
			surfaceNormal->y = 0;
			surfaceNormal->z = 1;
		}
		return height;
	}
	if (layer != 0x10)
		return worldPosition->z;

bridge_scan:
	{
		Bridge *bridge = m_bridgeList;
		while (bridge != 0)
		{
			if (bridge->isPointOnBridge(worldPosition))
				return bridge->getBridgeHeight(worldPosition, surfaceNormal);
			bridge = bridge->m_next;
		}

		Coord3D first = *worldPosition;
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
				return bridge->getBridgeHeight(worldPosition, surfaceNormal);
		}
	}

	return worldPosition->z;

ground_height:
	return TheTerrainLogic->getGroundHeight(worldPosition->x, worldPosition->y, surfaceNormal);
}
