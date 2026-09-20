// cl: /DNDEBUG /MD /EHsc
// readable body of ?freeBlocks@PathfindZoneManager@@AAEXXZ: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// Open-BFME5: PathfindZoneManager::freeBlocks at retail 0x00403760, 92 bytes.
// The body carried only a machine byte-dump row. The symbols.csv pin names it
// as the BFME-layout cleanup that allocateBlocks runs before rebuilding.
// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[]( void *block );

struct Rva004029F0GridExtent
{
	short width;
	short height;
};

class Rva004029F0
{
public:
	Rva004029F0();						// ILT 0x0004A4E4
	~Rva004029F0();						// ILT 0x00040138

private:
	int m_field00;
	unsigned char m_field04;
	unsigned char m_field05;
	unsigned char m_pad06[2];
	int m_ints[12];
	Rva004029F0GridExtent m_firstGridExtent;	// +0x38
	void *m_firstGrid[12][5];			// +0x3c
	unsigned char m_field12c;
	unsigned char m_pad12d[3];
	Rva004029F0GridExtent m_secondGridExtent;	// +0x130
	void *m_secondGrid[12][5];			// +0x134
	unsigned char m_field224;
	unsigned char m_pad225[3];
};

// ??0Rva004029F0@@QAE@XZ
Rva004029F0::Rva004029F0()
{
	m_field04 = 1;
	m_field00 = 0;
	m_field05 = 0;

	for ( int i = 0; i < 12; ++i )
	{
		m_ints[i] = 0;
	}

	m_secondGridExtent.width = 0;
	m_firstGridExtent.width = 0;
	m_secondGridExtent.height = 0;
	m_firstGridExtent.height = 0;

	for ( int column = 0; column < 5; ++column )
	{
		for ( int row = 0; row < 12; ++row )
		{
			m_secondGrid[row][column] = 0;
			m_firstGrid[row][column] = 0;
		}
	}

	m_field224 = 0;
	m_field12c = 0;
}

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
