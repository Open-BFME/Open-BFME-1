// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674F00, 182 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Preserve the ledger's return-type spelling while the real AsciiString
// supplies the StringBase<char> copy and release calls.
class AsciiStringZM
{
public:
	AsciiString m_bfmeNarrowZM;
};

// ILT 0x0002D204 reaches the matched NetCommandMsg description at
// 0x006747C0. The qualified call below invokes that base implementation.
class NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
};

class BfmeOrderZM
{
public:
	AsciiStringZM bfmeDescribeZM(void);

	char m_bfmePadZM[0x1c];
	unsigned char m_bfmeLeavingZM;
};

AsciiStringZM BfmeOrderZM::bfmeDescribeZM(void)
{
	AsciiStringZM text;

	text.m_bfmeNarrowZM.format(AsciiString("%s, leavingPlayer=%d"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeLeavingZM);

	return text;
}
