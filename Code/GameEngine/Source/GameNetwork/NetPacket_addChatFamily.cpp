// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::addDisconnectChatCommand, retail 0x0067FC80, 532 bytes.
// NetPacket::addChatCommand, retail 0x0067FF20, 703 bytes.
//
// addCommand's jump table pins both addresses; each opens with the isRoomFor
// guard already landed in NetPacket.cpp: isRoomForDisconnectChatMessage
// (0x0067DD40) and isRoomForChatMessage (0x0067DDE0).
//
// Structurally both are NetPacket_addFileCommand.cpp's shape (the same
// 'T'/'R'/'P'/'C' header run, the same 'D', the same command bookkeeping and
// NetCommandRef replacement) with the payload swapped for a UnicodeString:
// addDisconnectChatCommand writes a one-byte length then the wide characters;
// addChatCommand adds the 'F' execution-frame field ahead of the header run
// and a trailing player-mask Int after the text, matching
// NetPacket_commandSizes.cpp's GetChatCommandSize/GetDisconnectChatCommandSize
// accounting (len*2 fields) and the getPlayerMask call already pinned as a
// real out-of-line NetChatCommandMsg method (not header-inlined like the
// other simple getters).
//
// A whole-file copy of these two bodies already exists in NetPacket.cpp
// (present-unmatched), written against the vendored Zero Hour NetCommandRef
// header, which carries a vptr BFME's retail binary does not: that shifts
// every msg->getCommand()/getRelay() load by 4 bytes ([esi+4] vs retail's
// [esi]). This TU keeps the same body text but with the de-pooled
// NetCommandRef layout the landed add*Command siblings already use, matching
// NetPacket_fill.cpp's note about why that class cannot move into the shared
// header without breaking bodies already matched against it.
//
// StringBase is the same eight-byte BFME header the other add*Command
// siblings use, parameterized on UnsignedShort for the wide text.

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#define NULL 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;							// +4
	UnsignedShort m_pad;
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

	Int getLength() const { return m_data ? m_data->m_len : 0; }
	const T *str() const { return m_data ? (const T *)(m_data + 1) : (const T *)L""; }

private:
	void releaseBuffer();							// ?releaseBuffer@?$StringBase@G@@AAEXXZ

	BfmeStringData *m_data;
};

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

class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	StringBase<UnsignedShort> getText(void);		// ILT thunk 0x00015901
};

class NetChatCommandMsg : public NetCommandMsg
{
public:
	StringBase<UnsignedShort> getText(void);		// ILT thunk 0x00025338
	Int getPlayerMask(void);						// ILT thunk 0x00002B1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);				// ILT thunk 0x000079E6
	~NetCommandRef();								// ILT thunk 0x00038960

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

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
	Bool isRoomForDisconnectChatMessage(NetCommandRef *msg);	// 0x0067DD40, landed
	Bool isRoomForChatMessage(NetCommandRef *msg);				// 0x0067DDE0, landed
	Bool addDisconnectChatCommand(NetCommandRef *msg);
	Bool addChatCommand(NetCommandRef *msg);

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


Bool NetPacket::addDisconnectChatCommand(NetCommandRef *msg) {
	if (isRoomForDisconnectChatMessage(msg)) {
		NetDisconnectChatCommandMsg *cmdMsg = (NetDisconnectChatCommandMsg *)(msg->getCommand());

		// If necessary, put the NetCommandType into the packet.
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);

			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		// If necessary, put the relay into the packet.
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);

			m_lastRelay = newRelay;
		}

		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);

			m_lastPlayerID = cmdMsg->getPlayerID();
		}

		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		StringBase<UnsignedShort> unitext = cmdMsg->getText();
		UnsignedByte length = (UnsignedByte)unitext.getLength();
		memcpy(m_packet + m_packetLen, &length, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);

		memcpy(m_packet + m_packetLen, unitext.str(), length * sizeof(UnsignedShort));
		m_packetLen += length * sizeof(UnsignedShort);

		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addChatCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForChatMessage(msg)) {
		NetChatCommandMsg *cmdMsg = (NetChatCommandMsg *)(msg->getCommand());

		// If necessary, put the NetCommandType into the packet.
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);

			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		// If necessary, put the execution frame into the packet.
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);

			m_lastFrame = newframe;
		}

		// If necessary, put the relay into the packet.
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);

			m_lastRelay = newRelay;
		}

		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);

			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}

		// If necessary, specify the command ID of this command.
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		StringBase<UnsignedShort> unitext = cmdMsg->getText();
		UnsignedByte length = (UnsignedByte)unitext.getLength();
		Int playerMask = cmdMsg->getPlayerMask();
		memcpy(m_packet + m_packetLen, &length, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);

		memcpy(m_packet + m_packetLen, unitext.str(), length * sizeof(UnsignedShort));
		m_packetLen += length * sizeof(UnsignedShort);

		memcpy(m_packet + m_packetLen, &playerMask, sizeof(Int));
		m_packetLen += sizeof(Int);

		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}
