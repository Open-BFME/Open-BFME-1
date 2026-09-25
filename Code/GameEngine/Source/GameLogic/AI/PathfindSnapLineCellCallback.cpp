// cl: /DNDEBUG /MD
//
// Retail 0x003DCD80 is the callback used by Pathfinder::snapLine. The
// Rva003D61C0 payload stores the Pathfinder pointer, diameter, and last clear
// cell position. The cell walker at 0x003DE480 calls this body through ILT
// 0x0001EAD3.

extern const float g_bfmeK1253;
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

extern Rva003FD060TerrainLogic *TheTerrainLogic;

class PathfindCell
{
public:
	unsigned char m_bfmeHeadABE[0xc];
	unsigned int m_bfme0CABE;

	int getLayer() const { return (m_bfme0CABE >> 6) & 0x3f; }
};

class Pathfinder
{
public:
	int clearCellForDiameter(int crusher, int cellX, int cellY, int layer,
		int diameter, int attackerOnWall);
};

class Rva003D61C0
{
public:
	int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell,
		int currentCellX, int currentCellY);

	Pathfinder *m_bfme00ABE;
	int m_bfme04ABE;
	float m_bfme08ABE;
	float m_bfme0CABE;
	float m_bfme10ABE;
};

int Rva003D61C0::cellCallback(PathfindCell *previousCell, PathfindCell *currentCell,
	int currentCellX, int currentCellY)
{
	if (previousCell != 0)
	{
		int f1 = currentCell->getLayer();

		if (f1 >= 2 && f1 <= 0xf)
		{
			if (previousCell->getLayer() == f1)
				return 0;
		}
	}

	if (m_bfme00ABE->clearCellForDiameter(0, currentCellX, currentCellY, currentCell->getLayer(),
		m_bfme04ABE, 1) == m_bfme04ABE)
	{
		int f = currentCell->getLayer();

		float x = ((float)currentCellX + g_bfmeK1253) * g_bfmeDirectionWeight1285;

		m_bfme08ABE = x;

		float y = ((float)currentCellY + g_bfmeK1253) * g_bfmeDirectionWeight1285;

		m_bfme0CABE = y;
		m_bfme10ABE = TheTerrainLogic->bfmeHeightABE(x, y, f, 0, 1);

		return 0;
	}

	return 1;
}
