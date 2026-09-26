// cl: /O2 /Ob2 /G6

// Retail 0x001B1AD0 sweeps every cell of the grid, puts a Coord3D at the cell
// centre on the terrain, and hands it to the 0x001DE2A0 cell body through ILT
// 0x00004D27. The 0x1C-byte grid layout is the one the landed constructor at
// 0x001B1830 proves, and the 0x88-byte cell stride comes from the same row.
// Both callers (0x001DB160, 0x001DC690) are VictorySystem bodies; neither
// names this method, so the address stays in the name.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern const Real g_bfmeK1253;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot0VC();
	virtual void bfmeSlot1VC();
	virtual void bfmeSlot2VC();
	virtual void bfmeSlot3VC();
	virtual void bfmeSlot4VC();
	virtual void bfmeSlot5VC();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

class BfmeCell
{
public:
	void rva001DE2A0(const Coord3D *position, Real cellSize,
		Int index, void *parameters);

private:
	unsigned char m_data[0x88];
};

class BfmeCellGrid
{
public:
	void rva001B1AD0(Int index, void *parameters);

private:
	Int m_width;
	Int m_height;
	UnsignedInt m_cellCount;
	Real m_cellSize;
	Real m_offset;
	BfmeCell *m_cells;
	UnsignedInt *m_cellValues;
};

void BfmeCellGrid::rva001B1AD0(Int index, void *parameters)
{
	Real base = *(volatile Real *)&m_cellSize * g_bfmeK1253 + m_offset;

	for (UnsignedInt y = 0; y < (UnsignedInt)m_height; ++y)
	{
		Coord3D position;
		position.x = base;
		position.y = (Real)y * m_cellSize + base;
		position.z = 0.0f;

		for (UnsignedInt x = 0; x < (UnsignedInt)m_width; ++x)
		{
			UnsignedInt cellIndex = (UnsignedInt)m_height * y + x;
			if (cellIndex < m_cellCount)
			{
				position.x = (Real)x * m_cellSize + base;
				position.z = TheTerrainLogic->getGroundHeight(
					position.x, position.y, 0) + g_bfmeK1253;
				m_cells[cellIndex].rva001DE2A0(&position, m_cellSize,
					index, parameters);
			}
		}
	}
}
