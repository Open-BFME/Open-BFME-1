// cl: /DNDEBUG /MD
//
// Retail 0x003DCD80 is the callback used by Pathfinder::snapLine. The
// Rva003D61C0 payload stores the Pathfinder pointer, diameter, and last clear
// cell position. The cell walker at 0x003DE480 calls this body through ILT
// 0x0001EAD3.

extern const float g_rva0107533C;
extern const float g_bfmeDirectionWeight1285;

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot0ABE();
	virtual void bfmeSlot1ABE();
	virtual void bfmeSlot2ABE();
	virtual void bfmeSlot3ABE();
	virtual void bfmeSlot4ABE();
	virtual void bfmeSlot5ABE();
	virtual void bfmeSlot6ABE();
	virtual float bfmeHeightABE(float x, float y, int layer, int normal, int clip);
};

// Retail 0x012EF4CC is EA's singleton; only its type spelling matters for the
// mangled name, so this TU declares it canonically and keeps its own TU-local
// view of the vtable for the members it touches.
class TerrainLogic;

extern TerrainLogic *TheTerrainLogic;

class PathfindCell
{
public:
	unsigned char m_bfmeHeadABE[0xc];
	unsigned int m_bfme0CABE;

	int getLayer() const { return (m_bfme0CABE >> 6) & 0x3f; }
};

// Declared as PathfinderClearCellForDiameter.cpp defines the 0x003DC810 body.
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

class Pathfinder
{
public:
	int clearCellForDiameter(unsigned int crusher, int cellX, int cellY, PathfindLayerEnum layer,
		int pathDiameter, bool stopOnFail);
};

class Rva003D61C0
{
public:
	int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell,
		int currentCellX, int currentCellY);

	Pathfinder *m_pathfinder;
	int m_diameter;
	float m_lastClearCellX;
	float m_lastClearCellY;
	float m_lastClearCellHeight;
};

int Rva003D61C0::cellCallback(PathfindCell *previousCell, PathfindCell *currentCell,
	int currentCellX, int currentCellY)
{
	if (previousCell != 0)
	{
		int currentCellLayer = currentCell->getLayer();

		if (currentCellLayer >= 2 && currentCellLayer <= 0xf)
		{
			if (previousCell->getLayer() == currentCellLayer)
				return 0;
		}
	}

	if (m_pathfinder->clearCellForDiameter(0, currentCellX, currentCellY,
		(PathfindLayerEnum)currentCell->getLayer(), m_diameter, true) == m_diameter)
	{
		int currentCellLayer = currentCell->getLayer();

		float terrainX = ((float)currentCellX + g_rva0107533C) * g_bfmeDirectionWeight1285;

		m_lastClearCellX = terrainX;

		float terrainY = ((float)currentCellY + g_rva0107533C) * g_bfmeDirectionWeight1285;

		m_lastClearCellY = terrainY;
		m_lastClearCellHeight = ((Rva003FD060TerrainLogic *)TheTerrainLogic)->bfmeHeightABE(terrainX, terrainY, currentCellLayer, 0, 1);

		return 0;
	}

	return 1;
}
