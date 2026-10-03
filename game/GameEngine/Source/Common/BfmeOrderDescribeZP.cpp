// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x006757D0, 181 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

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

class BfmeOrderZP
{
public:
	AsciiString bfmeDescribeZP(void);

	char m_bfmePadZP[0x1c];
	int m_bfmeLeavePlayerZP;
};

AsciiString BfmeOrderZP::bfmeDescribeZP(void)
{
	AsciiString text;

	text.format(AsciiString("%s, leavePlayer=%d"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeLeavePlayerZP);

	return text;
}
