// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00675D40, 219 bytes.
// Sibling of 0x00675A80 with two string fields rather than one.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ILT 0x0002D204 reaches the base description at 0x006747C0.
class NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
};

// Keep this row's return type while using the canonical string lifecycle.
class AsciiStringZS
{
public:
	AsciiStringZS(void)
	{
	}

	AsciiStringZS(const char *text) : m_bfmeNarrowZS(text)
	{
	}

	AsciiStringZS(const AsciiStringZS &other) : m_bfmeNarrowZS(other.m_bfmeNarrowZS)
	{
	}

	~AsciiStringZS(void)
	{
	}

	const char *bfmeTextZS(void) const
	{
		return m_bfmeNarrowZS.str();
	}

private:
	AsciiString m_bfmeNarrowZS;
};

class BfmeOrderZS
{
public:
	AsciiStringZS bfmeDescribeZS(void);

	char m_bfmePadZS[0x1c];
	AsciiStringZS m_bfmeAuthKeyZS;
	AsciiStringZS m_bfmeAuthTokenZS;
};

AsciiStringZS BfmeOrderZS::bfmeDescribeZS(void)
{
	AsciiStringZS text;

	((AsciiString &)text).format(AsciiString("%s, authToken=%s, authKey=%s"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(),
			m_bfmeAuthTokenZS.bfmeTextZS(),
			m_bfmeAuthKeyZS.bfmeTextZS());

	return text;
}
