// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Two of NetPacket's isRoomFor family, retail 0x0067DBB0 and 0x0067DC80. Same
// shape as the four already in NetPacket_isRoomForFrameFamily.cpp -- count only
// the headers that would have to be written, add the payload, compare against
// MAX_PACKET_SIZE -- and the payload arithmetic is the same each
// FillBufferWith body writes and each GetXxxCommandSize helper counts.
//
// Named by their getters, both already ledgered:
// getPortableFilename@NetFileCommandMsg and getPortableFilename@NetFileAnnounceCommandMsg.
//
// The two chat twins that used to sit here now live in NetPacket.cpp. These two
// cannot follow: the string they measure is an AsciiString, and the reference
// AsciiString inlines its release as an InterlockedDecrement where retail calls
// one out of line. UnicodeString's release is already out of line in that
// header, which is the whole reason the chat pair compiles to retail's bytes
// inside NetPacket.cpp and this pair does not.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };

// NetCommandMsg's field set is the one NetPacket_addCommand.cpp already pins
// from a matched dispatcher: vptr, timestamp, frame, player, id, type, and the
// reference count that closes it out at 0x1C.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;									// this+0x00
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount;							// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForFileMessage(NetCommandRef *msg);
	Bool isRoomForFileAnnounceMessage(NetCommandRef *msg);

public:

	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;								// this+0x1E0
	NetPacketAddress m_dest;						// this+0x1E4
	Int m_numCommands;								// this+0x1EC
	NetCommandRef *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};


struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;				// +4
	UnsignedShort m_pad;
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

	Int getLength() const { return m_data ? m_data->m_len : 0; }

private:
	void releaseBuffer();

	BfmeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getPortableFilename(void);	// ILT thunk 0x00044323
	UnsignedInt getFileLength(void);		// ILT thunk 0x0001E7BD
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getPortableFilename(void);	// ILT thunk 0x0003D50F
};

Bool NetPacket::isRoomForFileMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetFileCommandMsg *cmdMsg = (NetFileCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}

	++len; // 'D'
	len += cmdMsg->getPortableFilename().getLength() + 1; // PORTABLE filename + the terminating 0
	len += sizeof(UnsignedInt); // filedata length
	len += cmdMsg->getFileLength();

	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}

	return true;
}

Bool NetPacket::isRoomForFileAnnounceMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetFileAnnounceCommandMsg *cmdMsg = (NetFileAnnounceCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedShort);
	}

	++len; // 'D'
	len += cmdMsg->getPortableFilename().getLength() + 1; // PORTABLE filename + the terminating 0
	len += sizeof(UnsignedShort); // m_fileID
	len += sizeof(UnsignedByte); // m_playerMask

	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}

	return true;
}

