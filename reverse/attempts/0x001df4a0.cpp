// ?_bfme_newMap@VictorySystem@@UAEXXZ
// partial score=0.86 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6
// stlport
//
// Open-BFME: clean C++ reconstruction of VictorySystem::newMap.
// Retail RVA 0x001DF4A0, 747 bytes.  The method is the BFME-only vtable
// slot +0x24 called by GameLogic::startNewGame at 0x003957B7.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" double __cdecl fabs(double value);
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)

// These are the retail constants consumed by the body.  Their values and
// addresses are verified from the baseline image: 0, 1, 0.5, 2.0, and 100.
#define BFME_ZERO (*(const Real *)0x01075350)
#define BFME_ONE (*(const Real *)0x01075334)
#define BFME_HALF (*(const Real *)0x0107533c)
#define BFME_CELL_SIZE_FLOOR (*(const Real *)0x0107fac4)
#define BFME_TWO (*(const double *)0x0107fd90)

class AsciiString;

template <class Character>
class StringBase
{
	friend class AsciiString;

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
	};

	StringBase(const Character *text);
	StringBase(const StringBase &that);
	void releaseBuffer();
	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	int compareNoCase(const char *text) const;
	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

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

extern PlayerList *Rva002EE330ThePlayers;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

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

class BfmeCellGrid
{
public:
	BfmeCellGrid(Int width, Int height, Real cellSize, Real offset);

	char m_opaque[0x1c];
};

class VictorySystem
{
public:
	virtual void _bfme_newMap(void);
	virtual void reset(void);

private:
	UnsignedInt _bfme_findFactionVictoryParametersIndex(
		const AsciiString &name);
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

			++playerIndex;
			++faction;
		}
		while (playerIndex < m_playerCount);
	}

	m_initialized = true;
}
