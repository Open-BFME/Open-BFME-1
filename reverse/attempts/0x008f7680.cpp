// ?doShroudReveal@PartitionManager@@QAEXPBUCoord3D@@MI@Z
// partial score=0.7 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc /QIfist

#include <math.h>

typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmePartitionCells
{
public:
	void doShroudReveal( int cellX, int cellY, int cellRadius, UnsignedInt playerMask );

	unsigned char m_unmodelled_00[4];
	Real m_originX;
	Real m_originY;
	unsigned char m_unmodelled_0C[0x14];
	Real m_cellsPerWorldUnit;
};

class PartitionManager
{
public:
	void doShroudReveal( const Coord3D *position, Real radius, UnsignedInt playerMask );

private:
	unsigned char m_unmodelled_00[0x0C];
	BfmePartitionCells *m_cells;
};

// ?doShroudReveal@PartitionManager@@QAEXPBUCoord3D@@MI@Z
void PartitionManager::doShroudReveal( const Coord3D *position, Real radius,
	UnsignedInt playerMask )
{
	volatile int cellRadius = (int)ceil( radius * m_cells->m_cellsPerWorldUnit );
	volatile int cellY = (int)floor( ( position->y - m_cells->m_originY ) *
		m_cells->m_cellsPerWorldUnit );
	volatile int cellX = (int)floor( ( position->x - m_cells->m_originX ) *
		m_cells->m_cellsPerWorldUnit );

	m_cells->doShroudReveal( cellX, cellY, cellRadius, playerMask );
}
