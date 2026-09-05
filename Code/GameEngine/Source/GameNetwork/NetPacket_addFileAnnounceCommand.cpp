// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::addFileAnnounceCommand, retail 0x0067F950, 651 bytes.
//
// addCommand's jump table pins this address as the arm for command type 6
// (NETCOMMANDTYPE_FILEANNOUNCE) here (BFME renumbers the GameSpy stats-authkey
// pair ahead of it), and it opens with the isRoomFor guard landed alongside
// it, NetPacket_isRoomForFileAndChat.cpp's isRoomForFileAnnounceMessage at
// 0x0067DC80.
//
// Structurally it is NetPacket_addFileCommand.cpp's sibling with the payload
// swapped: the same filename copy through strcpy, then the two small fields
// NetPacket_commandSizesGameSpy.cpp's neighbour NetPacket_commandSizes.cpp's
// GetFileAnnounceCommandSize counts -- getFileID (UnsignedShort) and
// getPlayerMask (UnsignedByte) -- matching
// NetPacket_fillFileMessage.cpp's field order for the file-data pair, just
// with the shorter announce fields.
//
// Layouts are NetPacket_isRoomForFileAndChat.cpp's; StringBase is that file's
// eight-byte BFME header with str() added, from
// NetPacket_addRequestGameSpyStatsAuthKey.cpp.

extern "C" char *__cdecl strcpy(char *dest, const char *src);
#pragma intrinsic(strcpy)

#define NULL 0

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

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
	const T *str() const { return m_data ? (const T *)(m_data + 1) : (const T *)""; }

private:
	void releaseBuffer();							// ?releaseBuffer@?$StringBase@D@@AAEXXZ

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

class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getPortableFilename(void);	// ILT thunk 0x0003D50F
	UnsignedShort getFileID(void);					// ILT thunk 0x00030909
	UnsignedByte getPlayerMask(void);				// ILT thunk 0x000478F2
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
	Bool isRoomForFileAnnounceMessage(NetCommandRef *msg);		// ILT thunk 0x00035387
	Bool addFileAnnounceCommand(NetCommandRef *msg);

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


Bool NetPacket::addFileAnnounceCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForFileAnnounceMessage(msg)) {
		NetFileAnnounceCommandMsg *cmdMsg = (NetFileAnnounceCommandMsg *)(msg->getCommand());

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
			m_packet[m_packetLen] = newRelay;
			m_packetLen += sizeof(UnsignedByte);

			m_lastRelay = newRelay;
		}

		// If necessary put the player ID into the packet.
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

		StringBase<char> filename = cmdMsg->getPortableFilename();
		strcpy((char *)(m_packet + m_packetLen), filename.str());
		m_packetLen += filename.getLength() + 1;

		UnsignedShort fileID = cmdMsg->getFileID();
		memcpy(m_packet + m_packetLen, &fileID, sizeof(fileID));
		m_packetLen += sizeof(fileID);

		UnsignedByte playerMask = cmdMsg->getPlayerMask();
		memcpy(m_packet + m_packetLen, &playerMask, sizeof(playerMask));
		m_packetLen += sizeof(playerMask);

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
