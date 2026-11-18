// cl: /DNDEBUG /MD /EHsc
// Open-BFME: retail 0x000F9250 (10 B), a dead bool setter storing its argument
// at this+0x24. Its ILT jmp 0x0001764D has no callers and no address
// reference. Retail's ILT order rules out PathNode::setCanOptimize, and BFME's
// matched PathNode users (Path::xfer00401C70, Pathfinder::prependCells) inline
// that setter as a store to +0x1C of a 0x24-byte node, so class and method
// keep the address.

#include "../../../Include/Common/ScalarTypes.h"

class Rva000F9250
{
public:
	void set(Bool value);

private:
	unsigned char m_pad000[0x24];
	Bool m_value;
};

void Rva000F9250::set(Bool value)
{
	m_value = value;
}
