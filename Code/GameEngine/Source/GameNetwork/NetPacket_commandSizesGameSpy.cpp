// cl: /DNDEBUG /MD /EHs-c-

// The two GameSpy stats auth-key size helpers, retail 0x0067D4B0 and
// 0x0067D500. Both are named the way the four in NetPacket_commandSizes.cpp
// are: GetBufferSizeNeededForCommand's jump table at 0x0067F378 indexes by
// command type, and its arms for types 5 and 6 -- REQUEST_GAMESPY_STATS_AUTHKEY
// and GAMESPY_STATS_AUTHKEY, both already pinned by addCommand's own table --
// tail-jump to these two addresses. The getters they call settle which is
// which: 0x0067D4B0 reads the one text field of the request message and
// 0x0067D500 reads both of the reply's.
//
// The arithmetic closes the triangle on the request side. This one returns
// getLength() + 0xB; isRoomForRequestGameSpyStatsAuthKeyMessage (0x0067E1F0)
// charges 2 + 2 + 2 + 3 for the header, 1 for the 'D' and getLength() + 1 for
// the payload, and addRequestGameSpyStatsAuthKeyCommand (0x00680350) writes
// exactly those bytes. Three independent bodies, one number.
//
// No SEH frame in either: /EHs-c-, as NetPacket_commandSizes.cpp uses for the
// same reason. StringBase is that file's eight-byte BFME header, unchanged.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;			// +4
	UnsignedShort m_pad;
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

	Int getLength() const { return m_data ? m_data->m_len : 0; }

private:
	void releaseBuffer();			// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	BfmeStringData *m_data;
};

class NetCommandMsg;

class BFMENetRequestGameSpyStatsAuthKeyCommandMsg
{
public:
	StringBase<char> getText1C(void);	// ILT thunk 0x000204D2
};

class BFMENetGameSpyStatsAuthKeyCommandMsg
{
public:
	StringBase<char> getText1C(void);	// ILT thunk 0x0002F081
	StringBase<char> getText20(void);	// ILT thunk 0x00019EC5
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static UnsignedInt GetRequestGameSpyStatsAuthKeyCommandSize(NetCommandMsg *msg);
	static UnsignedInt GetGameSpyStatsAuthKeyCommandSize(NetCommandMsg *msg);
};

// ?GetRequestGameSpyStatsAuthKeyCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z
UnsignedInt NetPacket::GetRequestGameSpyStatsAuthKeyCommandSize(NetCommandMsg *msg)
{
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg *authMsg = (BFMENetRequestGameSpyStatsAuthKeyCommandMsg *)msg;
	UnsignedInt msglen = 0;
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'T' and command type
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'R' and relay
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'P' and player ID
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedShort);		// 'C' and command ID

	++msglen;							// 'D'

	msglen += authMsg->getText1C().getLength() + 1;			// the key and its terminator

	return msglen;
}

UnsignedInt NetPacket::GetGameSpyStatsAuthKeyCommandSize(NetCommandMsg *msg)
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *authMsg = (BFMENetGameSpyStatsAuthKeyCommandMsg *)msg;
	UnsignedInt msglen = 0;
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'T' and command type
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'R' and relay
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'P' and player ID
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedShort);		// 'C' and command ID

	++msglen;							// 'D'

	msglen += authMsg->getText1C().getLength() + 1;
	msglen += authMsg->getText20().getLength() + 1;

	return msglen;
}
