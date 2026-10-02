// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00676290, 190 bytes.
// Here the name comes from a virtual call on the owner the order points at,
// so the struct return slot is passed to an indirect call.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

//
// The format call used to be spelled through a TU-local stand-in pair
// (StringBaseNarrowZT/AsciiStringZT), which named retail's callee
// ?format@StringBaseNarrowZT@@QAAXVAsciiStringZT@@ZZ -- a name retail has no
// body for.  AsciiString::format (0x00888FF0, matched in
// game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp) is the real
// one, so it comes from ascii_string.h and is named through the real class.

class AsciiStringZT : public AsciiString
{
public:
	AsciiStringZT(void)
	{
	}

	AsciiStringZT(const char *text) : AsciiString(text)
	{
	}

	AsciiStringZT(const AsciiStringZT &other) : AsciiString(other)
	{
	}

	~AsciiStringZT(void)
	{
	}

	const char *bfmeTextZT(void) const
	{
		char *buffer = *reinterpret_cast<char *const *>(this);
		return (buffer != 0) ? buffer + 8 : "";
	}
};

class BfmeOwnerZT
{
public:
	virtual void bfmeSlot0ZT(void) = 0;
	virtual void bfmeSlot1ZT(void) = 0;
	virtual void bfmeSlot2ZT(void) = 0;
	virtual AsciiStringZT bfmeNameZT(void) = 0;
};

class BfmeOrderZT
{
public:
	AsciiStringZT bfmeDescribeZT(void);

	BfmeOwnerZT *m_bfmeOwnerZT;
	char m_bfmePadZT[8];
	unsigned char m_bfmeRelayZT;
};

AsciiStringZT BfmeOrderZT::bfmeDescribeZT(void)
{
	AsciiStringZT text;

	((AsciiString &)text).format(AsciiString("%s, relay=0x%X"),
			m_bfmeOwnerZT->bfmeNameZT().bfmeTextZT(), m_bfmeRelayZT);

	return text;
}
