// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the message description at retail 0x00674B30, 197 bytes.
// Same shape as the order descriptions, but the name comes from a static
// lookup on the command type rather than from a member.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "System/message_stream.h"

// Keep the ledger's return-type spelling while using AsciiString's real
// copy constructor and releaseBuffer implementation for its storage.
class AsciiStringZK
{
public:
	AsciiString m_bfmeNarrowZK;
};

class BfmeMessageZK
{
public:
	AsciiStringZK bfmeDescribeZK(void);

	char m_bfmePadAZK[8];
	int m_bfmeFrameZK;
	int m_bfmePlayerZK;
	unsigned short m_bfmeIdZK;
	char m_bfmePadBZK[0x12];
	int m_bfmeTypeZK;
};

AsciiStringZK BfmeMessageZK::bfmeDescribeZK(void)
{
	AsciiStringZK text;

	text.m_bfmeNarrowZK.format(AsciiString("GameMessage:%s, frame=%d, player=%d, id=%d"),
			GameMessage::getCommandTypeAsAsciiString((GameMessage::Type)m_bfmeTypeZK).str(),
			m_bfmeFrameZK, m_bfmePlayerZK,
			m_bfmeIdZK);

	return text;
}
