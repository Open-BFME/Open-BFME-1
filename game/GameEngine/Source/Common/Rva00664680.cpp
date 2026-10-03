// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Retail 0x00664680, 153 bytes. Owner and method identity remain unknown.
// The retail format/copy/release calls establish the canonical AsciiString type.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva00664680
{
public:
	AsciiString method(void);

	int m_bfmeFrameAH;
	int m_bfmeCountAH;
};

AsciiString Rva00664680::method(void)
{
	AsciiString label;

	int frame = m_bfmeFrameAH;

	if (frame < 0)
		frame += 0x10000;

	label.format(AsciiString("%d(%d)"), frame, m_bfmeCountAH);

	return label;
}
