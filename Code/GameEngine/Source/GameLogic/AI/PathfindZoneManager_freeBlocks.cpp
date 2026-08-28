// cl: /DNDEBUG /MD /EHsc
// readable body of ?freeBlocks@PathfindZoneManager@@AAEXXZ: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// Open-BFME5: PathfindZoneManager::freeBlocks, retail 0x00403760, 92 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it as
// the BFME-layout cleanup allocateBlocks runs before rebuilding.
//
// Two arrays go and four words are cleared. The first, at +0x23624, has an
// element destructor, so it comes down the long way: the count read from the
// cookie in front of the block, the eh vector destructor iterator over 0x228-
// byte elements, then the block itself freed from four bytes below the array.
// The second, at +0x23628, is freed with a bare operator delete and no null
// test at all, which is what this compiler emits for a delete[] whose element
// has no destructor.
//
// The store clearing the first pointer lands between the push and the call of
// the second free; that is scheduling, not order.

class Rva004029F0
{
public:
	~Rva004029F0();						// ILT 0x00040138

private:
	char m_bfmeBody[0x228];
};

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
