// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class BfmeStrNVSR
{
public:
	~BfmeStrNVSR() { ((StringBase<char> *)this)->clear(); }
	char *m_bfme00;
};

class BfmeStrWVSR
{
public:
	~BfmeStrWVSR() { ((StringBase<unsigned short> *)this)->clear(); }
	unsigned short *m_bfme00;
};

class BfmeHolderVSR
{
public:
	~BfmeHolderVSR();
	BfmeStrNVSR m_bfme00;
	int m_bfme04;
	BfmeStrWVSR m_bfme08;
};

BfmeHolderVSR::~BfmeHolderVSR()
{
	m_bfme04 = 0;
}
