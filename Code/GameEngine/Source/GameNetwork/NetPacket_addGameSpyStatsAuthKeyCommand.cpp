// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::addGameSpyStatsAuthKeyCommand, retail 0x00680620, 680 bytes.
//
// symbols.csv pins addCommand's arm for this address directly (the ILT hop is
// the further indirection); the guard it opens with is
// isRoomForGameSpyStatsAuthKeyMessage at 0x0067E2B0, still a gen-asm dump but
// already a matched, byte-true row so its REL32 resolves normally.
//
// Structurally it is NetPacket_addRequestGameSpyStatsAuthKeyCommand.cpp's
// sibling: same header run, same 'D', same NetCommandRef bookkeeping, and the
// SAME strcpy-intrinsic copy through str()'s null fallback -- retail's own
// disassembly shows two real calls to the getText1C/getText20 getters each
// followed by an inlined byte-copy loop, not the guarded memcpy the
// FillBufferWithGameSpyStatsAuthKeyCommand static helper uses for the same
// fields (that shape belongs to the wire-fill function, not this one; a first
// attempt copying it grew the body by 68 bytes and swapped esi/edi/ebx for
// ebp/edi/ebx). getLength()+1 per field matches
// NetPacket_commandSizesGameSpy.cpp's GetGameSpyStatsAuthKeyCommandSize.
//
// Class layout is NetPacket_fillGameSpyStatsAuthKey.cpp's; StringBase is that
// file's eight-byte BFME header with str() added.

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

class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getText1C(void);				// ILT thunk 0x0002F081
	StringBase<char> getText20(void);				// ILT thunk 0x00019EC5
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
	Bool isRoomForGameSpyStatsAuthKeyMessage(NetCommandRef *msg);	// ILT thunk 0x00011A68
	Bool addGameSpyStatsAuthKeyCommand(NetCommandRef *msg);

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


Bool NetPacket::addGameSpyStatsAuthKeyCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForGameSpyStatsAuthKeyMessage(msg)) {
		BFMENetGameSpyStatsAuthKeyCommandMsg *cmdMsg =
				(BFMENetGameSpyStatsAuthKeyCommandMsg *)(msg->getCommand());

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

		StringBase<char> key = cmdMsg->getText1C();
		strcpy((char *)(m_packet + m_packetLen), key.str());
		m_packetLen += key.getLength() + 1;

		StringBase<char> login = cmdMsg->getText20();
		strcpy((char *)(m_packet + m_packetLen), login.str());
		m_packetLen += login.getLength() + 1;

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
