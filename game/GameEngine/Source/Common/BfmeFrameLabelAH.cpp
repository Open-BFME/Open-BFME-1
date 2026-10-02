// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the frame label at retail 0x00664680, 153 bytes.  A negative
// frame is wrapped into the positive range before it is printed.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Keep the return type that identifies this body, but use the real BFME string
// implementation so construction and destruction reference StringBase<char>.
class AsciiStringAH : public AsciiString
{
public:
	AsciiStringAH(void) : AsciiString()
	{
	}

	AsciiStringAH(const char *text) : AsciiString(text)
	{
	}

	AsciiStringAH(const AsciiStringAH &other) : AsciiString(other)
	{
	}

	~AsciiStringAH(void)
	{
	}
};

class BfmeFrameAH
{
public:
	AsciiStringAH bfmeLabelAH(void);

	int m_bfmeFrameAH;
	int m_bfmeCountAH;
};

AsciiStringAH BfmeFrameAH::bfmeLabelAH(void)
{
	AsciiStringAH label;

	int frame = m_bfmeFrameAH;

	if (frame < 0)
		frame += 0x10000;

	((AsciiString &)label).format(AsciiString("%d(%d)"), frame, m_bfmeCountAH);

	return label;
}
