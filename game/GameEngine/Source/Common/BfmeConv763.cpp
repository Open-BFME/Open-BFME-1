// cl: /DNDEBUG /MD /EHs-c-
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include <new>

class BfmeOtherDRA
{
public:
};

class BfmeThingDRA
{
public:
	BfmeOtherDRA *bfmeGoDRA(BfmeOtherDRA *other, int row, int col);
	unsigned char m_bfmeHead[0xa4];
	int m_bfmeGrid[16][3];
};

BfmeOtherDRA *BfmeThingDRA::bfmeGoDRA(BfmeOtherDRA *other, int row, int col)
{
	volatile int tmp = 0;
	__assume(other != 0);
	new (other) AsciiString(*(const AsciiString *)&m_bfmeGrid[row][col]);
	return other;
}
