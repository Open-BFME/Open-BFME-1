// cl: /DNDEBUG /MD /EHsc

// The two GameSpy stats auth-key packet writers, retail 0x0067D990 and
// 0x0067DA50 -- the last two bodies of the FillBufferWith* run that starts at
// 0x0067D580 and whose first four are already ledgered. Which is which comes
// from the getters, as it does for the other four: 0x0067D990 writes the one
// text field of BFMENetRequestGameSpyStatsAuthKeyCommandMsg and 0x0067DA50
// writes both of BFMENetGameSpyStatsAuthKeyCommandMsg's.
//
// Each closes its own triangle against NetPacket_commandSizesGameSpy.cpp: ten
// header bytes then the text plus a terminator, so getLength() + 0xB for the
// request and l1 + l2 + 0xC for the reply, which is exactly what those helpers
// return. Nothing here is conditional, so MSVC folds the running offset to
// constants for the whole header run.
//
// The two differ in one thing that is genuinely in the source and not a
// scheduling accident: the request writer copies unguarded, through str() and
// its empty-string fallback, while the reply writer guards each copy with a
// non-zero length test. Under that test the compiler already knows the handle
// is non-null, so str() folds to m_data + 1 and the literal never appears --
// which is how the bytes tell the two shapes apart.
//
// StringBase is NetPacket_commandSizes.cpp's eight-byte BFME header with str()
// added; the message and NetCommandRef slices are
// NetPacket_fillFileMessage.cpp's, unchanged.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

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
	const T *str() const { return m_data ? (const T *)(m_data + 1) : (const T *)""; }

private:
	void releaseBuffer();			// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	BfmeStringData *m_data;
};

class NetCommandMsg;

class BFMENetRequestGameSpyStatsAuthKeyCommandMsg
{
public:
	Int getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }
	Int getNetCommandType(void) { return m_commandType; }

	StringBase<char> getText1C(void);		// ILT thunk 0x000204D2

	unsigned char m_bfmeHead[0x0C];
	Int m_playerID;					// +0x0C
	UnsignedShort m_id;				// +0x10
	UnsignedShort m_pad;
	Int m_commandType;				// +0x14
};

class BFMENetGameSpyStatsAuthKeyCommandMsg
{
public:
	Int getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }
	Int getNetCommandType(void) { return m_commandType; }

	StringBase<char> getText1C(void);		// ILT thunk 0x0002F081
	StringBase<char> getText20(void);		// ILT thunk 0x00019EC5

	unsigned char m_bfmeHead[0x0C];
	Int m_playerID;					// +0x0C
	UnsignedShort m_id;				// +0x10
	UnsignedShort m_pad;
	Int m_commandType;				// +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_command; }
	UnsignedByte getRelay(void) { return m_relay; }

	NetCommandMsg *m_command;			// +0x00
	unsigned char m_bfmeMiddle[0x0C - 4];
	UnsignedByte m_relay;				// +0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static void FillBufferWithRequestGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg);
};

// ?FillBufferWithRequestGameSpyStatsAuthKeyCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithRequestGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg *cmdMsg =
			(BFMENetRequestGameSpyStatsAuthKeyCommandMsg *)(msg->getCommand());
	UnsignedInt offset = 0;

	// command type
	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	// relay
	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->getRelay();
	offset += sizeof(UnsignedByte);

	// player ID
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	// command ID
	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(newID));
	offset += sizeof(newID);

	// data
	buffer[offset] = 'D';
	++offset;

	StringBase<char> text = cmdMsg->getText1C();
	memcpy(buffer + offset, text.str(), text.getLength());
	offset += text.getLength();
	buffer[offset] = 0;
}

void NetPacket::FillBufferWithGameSpyStatsAuthKeyCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *cmdMsg =
			(BFMENetGameSpyStatsAuthKeyCommandMsg *)(msg->getCommand());
	UnsignedInt offset = 0;

	// command type
	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	// relay
	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->getRelay();
	offset += sizeof(UnsignedByte);

	// player ID
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	// command ID
	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(newID));
	offset += sizeof(newID);

	// data
	buffer[offset] = 'D';
	++offset;

	StringBase<char> key = cmdMsg->getText1C();
	if (key.getLength() != 0) {
		memcpy(buffer + offset, key.str(), key.getLength());
	}
	offset += key.getLength();
	buffer[offset] = 0;
	++offset;

	StringBase<char> login = cmdMsg->getText20();
	if (login.getLength() != 0) {
		memcpy(buffer + offset, login.str(), login.getLength());
	}
	offset += login.getLength();
	buffer[offset] = 0;
}
