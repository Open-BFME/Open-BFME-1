// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: BuddyMessage(const BuddyMessage &) copy constructor.
// Members, in declaration order: UnsignedInt timestamp, GPProfile senderID,
// AsciiString senderNick, GPProfile recipientID, AsciiString recipientNick,
// UnicodeString message. The two AsciiString members and the UnicodeString
// member each forward to their StringBase<T> copy constructor (StringBase<D>
// for the narrow strings, StringBase<G> for the wide one), matching the two
// distinct call targets in the retail thunk.

#include "ascii_string.h"
#include "unicode_string.h"

// Retail copies the wide member through the canonical StringBase helper.
inline UnicodeString::UnicodeString(const UnicodeString &source)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&source);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class BuddyMessage
{
public:
	BuddyMessage(const BuddyMessage &);

private:
	unsigned int m_timestamp;
	unsigned int m_senderID;
	AsciiString m_senderNick;
	unsigned int m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
};

// ??0BuddyMessage@@QAE@ABV0@@Z
BuddyMessage::BuddyMessage(const BuddyMessage &that)
	: m_timestamp(that.m_timestamp),
	  m_senderID(that.m_senderID),
	  m_senderNick(that.m_senderNick),
	  m_recipientID(that.m_recipientID),
	  m_recipientNick(that.m_recipientNick),
	  m_message(that.m_message)
{
}
