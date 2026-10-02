// cl: /DNDEBUG /MD /EHs-c-
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include <new>

class BfmeOtherDRB
{
public:
};

class BfmeThingDRB
{
public:
	BfmeOtherDRB *bfmeGoDRB(BfmeOtherDRB *other, int row, int col);
	unsigned char m_bfmeHead[0xe4];
	int m_bfmeGrid[16][3];
};

BfmeOtherDRB *BfmeThingDRB::bfmeGoDRB(BfmeOtherDRB *other, int row, int col)
{
	volatile int tmp = 0;
	__assume(other != 0);
	new (other) AsciiString(*(const AsciiString *)&m_bfmeGrid[row][col]);
	return other;
}
