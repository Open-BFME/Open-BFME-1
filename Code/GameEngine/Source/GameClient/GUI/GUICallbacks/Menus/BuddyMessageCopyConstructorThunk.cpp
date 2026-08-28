// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BuddyMessage(const BuddyMessage &) copy constructor.
// Members, in declaration order: UnsignedInt timestamp, GPProfile senderID,
// AsciiString senderNick, GPProfile recipientID, AsciiString recipientNick,
// UnicodeString message. The two AsciiString members and the UnicodeString
// member each forward to their StringBase<T> copy constructor (StringBase<D>
// for the narrow strings, StringBase<G> for the wide one), matching the two
// distinct call targets in the retail thunk.

template <class T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase(const StringBase<T> &that);
	T *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that);
	}
	~UnicodeString();

private:
	unsigned short *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
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
