#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeOwnCD
{
public:
	virtual ~BfmeOwnCD(void);
	// Retail vftable 0x010E7688 holds one slot, the deleting destructor
	// 0x00339FA0 (via ILT 0x1D499); no second virtual.

	AsciiString m_bfmeTextCD;
	AsciiString *m_bfmeTargetCD;
};

BfmeOwnCD::~BfmeOwnCD(void)
{
	AsciiString *target = m_bfmeTargetCD;

	target->set(m_bfmeTextCD);
}
