// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include/Lib
// stlport

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" double __cdecl fabs(double value);
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)

#define BFME_ZERO 0.0f
#define BFME_ONE 1.0f
#define BFME_HALF 0.5f
#define BFME_CELL_SIZE_FLOOR 100.0f
#define BFME_TWO 2.0

#include "ascii_string.h"
#include "Coord3D.h"

template <>
inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

class Player
{
public:
	char m_beforeSide[0x28];
	AsciiString m_side;
};

class PlayerList
{
public:
	Player *getNthPlayer(Int index);

	char m_beforeCount[0x10];
	UnsignedInt m_playerCount;
};

// Retail 0x012ED748 is ?ThePlayerList@@3PAVPlayerList@@A (data_rows.csv,
// RTS/PlayerList.cpp); Rva002EE330ThePlayers was only a pin.
extern PlayerList *ThePlayerList;
#define Rva002EE330ThePlayers ThePlayerList

struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	Real width() const
	{
		return hi.x - lo.x;
	}

	Real height() const
	{
		return hi.y - lo.y;
	}
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void getExtent(Region3D *extent) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

class CellGrid
{
public:
	CellGrid(Int width, Int height, Real cellSize, Real offset);

	char m_opaque[0x1c];
};

typedef CellGrid BfmeCellGrid;

class VictorySystem
{
public:
	virtual void _bfme_newMap(void);
	virtual void reset(void);

private:
	// The complete finder calls only the C runtime comparison.
	UnsignedInt _bfme_findFactionVictoryParametersIndex(const AsciiString &name) throw();
	char m_beforeCellSize[8];
	Real m_cellSize;
	UnsignedInt m_playerCount;
	char m_beforeCellRadius[8];
	Real m_cellRadius;
	Real m_cellBonusRadius;
	UnsignedInt m_playerFaction[16];
	char m_beforeParameters[0x94];
	BfmeCellGrid *m_cellGrids[2];
	Bool m_initialized;
};

// ?_bfme_newMap@VictorySystem@@UAEXXZ
void VictorySystem::_bfme_newMap(void)
{
	VictorySystem::reset();

	if (m_cellSize > BFME_ZERO)
	{
		m_cellSize = BFME_CELL_SIZE_FLOOR > m_cellSize ?
			BFME_CELL_SIZE_FLOOR : m_cellSize;

		Region3D extent;
		TheTerrainLogic->getExtent(&extent);

		Real width = extent.width();
		if (width > BFME_ZERO)
		{
			Real height = extent.height();
			if (height > BFME_ZERO)
			{
				m_cellSize =
					(width < height ? width : height) < m_cellSize ?
					(width < height ? width : height) : m_cellSize;

				Int cellsX = (Int)ceil(
					(double)(fabs(width) / m_cellSize));
				Int cellsY = (Int)ceil(
					(double)(fabs(extent.height()) / m_cellSize));

				m_cellGrids[0] = new BfmeCellGrid(
					cellsX, cellsY, m_cellSize, 0.0f);
				++cellsX;
				++cellsY;
				m_cellGrids[1] = new BfmeCellGrid(
					cellsX, cellsY, m_cellSize,
					-(m_cellSize * BFME_HALF));
			}
		}

		m_cellBonusRadius = m_cellBonusRadius > BFME_ONE ?
			m_cellBonusRadius : BFME_ONE;

		UnsignedInt playerIndex = 0;
		m_cellRadius = (Real)sqrt(BFME_TWO) *
			(m_cellBonusRadius * m_cellSize * BFME_HALF);

		m_playerCount = Rva002EE330ThePlayers->m_playerCount;
		if (m_playerCount > 0)
		{
			UnsignedInt *faction = m_playerFaction;
			do
			{
				{
					Bool excluded = false;
					Player *player = Rva002EE330ThePlayers->getNthPlayer(playerIndex);
					AsciiString side(player->m_side);
					UnsignedInt index =
						_bfme_findFactionVictoryParametersIndex(side);
					if (side.isEmpty() ||
						side.compareNoCase("Observer") == 0 ||
						side.compareNoCase("Civilian") == 0)
						excluded = true;

					if (index == 0x7fffffff)
					{
						AsciiString defaultSide("Default");
						index = _bfme_findFactionVictoryParametersIndex(defaultSide);
					}

					if (index != 0x7fffffff)
						*faction = index | (excluded ? 0x80000000 : 0);
					else
						*faction = 0;
				}

				++playerIndex;
				++faction;
			}
			while (playerIndex < m_playerCount);
		}

		m_initialized = true;
	}
}
