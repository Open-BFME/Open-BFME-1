#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeOwnCD
{
public:
	virtual ~BfmeOwnCD(void);
	virtual void bfmePureCD(void) = 0;

	AsciiString m_bfmeTextCD;
	AsciiString *m_bfmeTargetCD;
};

BfmeOwnCD::~BfmeOwnCD(void)
{
	AsciiString *target = m_bfmeTargetCD;

	target->set(m_bfmeTextCD);
}
