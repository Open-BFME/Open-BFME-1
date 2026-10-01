// cl: /DNDEBUG /MD /Iinputs/reference/shims/pathfind
// Retail RVA0x003E5B80,224B. Matched cell walker003E8440 calls this
// address-derived member on its Rva003E5A50Info payload, with four stack args.
// Starts from banked attempts/0x003e5b80.cpp (0.94); that guessed callback
// name is retired. Distinct zero-byte barriers preserve the two return-one
// epilogues, as in the exact003E5950 sibling. Guard returns reuse the first.
extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

#include "GameLogic/AIPathfind.h"

enum
{
	LAYER_WALL_START = 2,
	LAYER_LAST = 15,
	CELL_CLEAR = 0
};

struct Rva003E5A50InfoAt08
{
	ICoord2D	cell;			// +0x00
	Int			layer;			// +0x08
	Int			m_at0c[8];		// +0x0C .. +0x2B
	Bool		m_at2c;		// +0x2C  (0x34 in the owner)
};

struct Rva003E5A50InfoAt3C
{
	ICoord2D	cell;			// +0x00
};

struct Rva003E5A50InfoAt44
{
	Int			m_at00[3];
};

class Rva003E5A50Info
{
public:
	Int rva003e5b80( PathfindCell *from, PathfindCell *to,
		Int to_x, Int to_y );

	Pathfinder			*m_at00;		// 0x00
	Object		*m_at04;				// 0x04
	Rva003E5A50InfoAt08	m_at08;				// 0x08 (m_at2c at 0x34)
	Int					m_at38;	// 0x38
	Rva003E5A50InfoAt3C	m_at3c;			// 0x3C
	Rva003E5A50InfoAt44	m_at44;			// 0x44
	Int					m_at50;			// 0x50
};

Int Rva003E5A50Info::rva003e5b80( PathfindCell *from,
	PathfindCell *to, Int to_x, Int to_y )
{
	m_at08.cell.x = to_x;
	m_at08.cell.y = to_y;
	m_at08.layer = to->getLayer();

	if (from) {
		if (!m_at00->bfmeStepE0930( m_at04, &m_at08.cell, &m_at3c.cell )) {
			_WriteBarrier();
			return 1;
		}
	} else {
		if (!m_at00->bfmeStepE05B0( m_at04, &m_at08.cell )) {
			_ReadWriteBarrier();
			return 1;
		}
	}

	if (m_at38) {
		_WriteBarrier();
		return 1;
	}

	if (m_at08.m_at2c) {
		m_at50++;
		if (m_at50 > 1) {
			_WriteBarrier();
			return 1;
		}
	}

	m_at3c.cell.x = to_x;
	m_at3c.cell.y = to_y;

	if (from) {
		Int layer = to->getLayer();
		if (layer >= LAYER_WALL_START && layer <= LAYER_LAST &&
				from->getLayer() == layer && to->getType() == CELL_CLEAR) {
			return 0;	// keep going
		}
	}

	return !m_at00->bfmeStepD4F90( &m_at44, to );
}
