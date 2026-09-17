// cl: /DNDEBUG /MD /EHsc
// readable body of ?freeBlocks@PathfindZoneManager@@AAEXXZ: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// Open-BFME5: PathfindZoneManager::freeBlocks at retail 0x00403760, 92 bytes.
// The body carried only a machine byte-dump row. The symbols.csv pin names it
// as the BFME-layout cleanup that allocateBlocks runs before rebuilding.
// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[]( void *block );

class Rva004029F0
{
public:
	~Rva004029F0();						// ILT 0x00040138

private:
	char m_beforeGrids[0x3c];
	void *m_firstGrid[12][5];
	char m_betweenGrids[8];
	void *m_secondGrid[12][5];
	char m_tail[4];
};

// ??1Rva004029F0@@QAE@XZ
Rva004029F0::~Rva004029F0()
{
	for ( int column = 0; column < 5; ++column )
	{
		for ( int row = 0; row < 12; ++row )
		{
			delete [] m_firstGrid[row][column];
			m_firstGrid[row][column] = 0;
			delete [] m_secondGrid[row][column];
			m_secondGrid[row][column] = 0;
		}
	}
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	void bfmeAllocateBlocks(void);

private:
	void freeBlocks(void);

	unsigned char m_bfmeHead[0x23624];
	Rva004029F0 *m_bfmeBlocks;				// +0x23624
	short *m_bfmeZones;					// +0x23628
	int m_bfmeZoneCount;					// +0x2362C
	int m_bfmeZoneMax;					// +0x23630
};

// ?freeBlocks@PathfindZoneManager@@AAEXXZ
void PathfindZoneManager::freeBlocks(void)
{
	delete [] m_bfmeBlocks;
	m_bfmeBlocks = 0;

	delete [] m_bfmeZones;
	m_bfmeZones = 0;

	m_bfmeZoneCount = 0;
	m_bfmeZoneMax = 0;
}
