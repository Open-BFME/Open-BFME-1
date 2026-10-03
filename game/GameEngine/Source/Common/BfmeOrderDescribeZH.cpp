// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674C30, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail ILT 0x0002D204 reaches the independently matched 298-byte
// NetCommandMsg::getContentsAsAsciiString at 0x006747C0. The Zero Hour
// header supplies an empty inline body instead, so this TU needs BFME's
// declaration-only call view; no storage or vtable is emitted for it.
class NetCommandMsg
{
public:
    virtual AsciiString getContentsAsAsciiString();
};

class BfmeOrderZH
{
public:

	AsciiString bfmeDescribeZH(void);

	char m_bfmePadZH[0x1c];
	unsigned short m_bfmeCommandZH;
	unsigned char m_bfmePlayerZH;
	int m_bfmeFrameZH;
};

AsciiString BfmeOrderZH::bfmeDescribeZH(void)
{
	AsciiString text;

	text.format(AsciiString("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeCommandZH, m_bfmePlayerZH, m_bfmeFrameZH);

	return text;
}
