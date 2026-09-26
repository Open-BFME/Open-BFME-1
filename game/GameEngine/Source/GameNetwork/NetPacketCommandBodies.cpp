// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Eight NetPacket members that work on one command at a time: the four add*
// builders that write a command into the packet, the three isRoomFor* guards
// that decide beforehand whether it will fit, and the static wire-fill helper
// for the router-fallback command.
//
//   addFileCommand                          0x0067F600  668 B  IAE
//   addFileAnnounceCommand                  0x0067F950  651 B  IAE
//   addRequestGameSpyStatsAuthKeyCommand    0x00680350  574 B  IAE
//   addGameSpyStatsAuthKeyCommand           0x00680620  680 B  IAE
//   isRoomForRequestGameSpyStatsAuthKeyMessage 0x0067E1F0 152 B IAE
//   isRoomForWrapperMessage                 0x00677BC0  123 B  IAE
//   isRoomForRouterFallbackMessage       0x00678050  114 B  IAE
//   FillBufferWithRouterFallbackCommand  0x006770B0  106 B  KAX (static)
//
// Every add* opens with its own isRoomFor guard and then writes the same
// 'T'/'R'/'P'/'C' header run before its 'D' payload, and every guard counts
// that same run back up, so the eight bodies are variations on two shapes with
// the payload swapped. Split one per file they were eight copies of the same
// four classes -- and the copies had gone quietly out of step:
//
//   NetCommandMsg was spelled as vptr/timestamp/frame/player/id/type/refcount
//     in six files and as an opaque 12-byte prefix over the first three in the
//     seventh. Same offsets, so one spelling serves.
//   NetCommandRef ended at m_relay (+0x0C) in one file and carried
//     m_timeLastSent (+0x10) in the others, and only two files declared the
//     constructor and destructor the add* bodies actually call.
//   StringBase appeared with str(), without str(), and not at all.
//   NetPacket itself was declared with no data members in the file whose body
//     is static, and with the full 0x1FD-byte layout in the rest.
//
// None of that was a contradiction -- every offset agreed -- but nothing said
// so, and a reader of any one file could not tell which of the partial views
// was the whole. Below is the union, declared once, and each body keeps the
// evidence its own file carried.
//
// The retail layouts drift from the Zero Hour reference in two places that
// matter here, both proven from already-matched bodies: NetPacket keeps m_port
// immediately after m_addr as an embedded ip+port pair, so m_numCommands
// .. m_lastRelay all sit lower than the ZH header puts them (NetPacket_init.cpp
// proves 0x1E0-0x1FC), and NetCommandRef is NOT a MemoryPoolObject and carries
// no vptr (the matched constructor at 0x00676240 and destructor at 0x00676280
// both confirm it).

extern "C" char *__cdecl strcpy(char *dest, const char *src);
#pragma intrinsic(strcpy)

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
	// m_data ? m_data + 1 : "" is retail's test / lea+8 / else-empty-literal.
	const T *str() const { return m_data ? (const T *)(m_data + 1) : (const T *)""; }

private:
	void releaseBuffer();							// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	BfmeStringData *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
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

class NetFileCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getPortableFilename(void);		// ILT thunk 0x00044323
	UnsignedInt getFileLength(void);				// ILT thunk 0x0001E7BD
	UnsignedByte *getFileData(void);				// ILT thunk 0x0003B598
};

class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getPortableFilename(void);		// ILT thunk 0x0003D50F
	UnsignedShort getFileID(void);					// ILT thunk 0x00030909
	UnsignedByte getPlayerMask(void);				// ILT thunk 0x000478F2
};

class BFMENetRequestGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getText1C(void);				// retail 0x006759F0
};

class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	StringBase<char> getText1C(void);				// ILT thunk 0x0002F081
	StringBase<char> getText20(void);				// ILT thunk 0x00019EC5
};

class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	Int m_playerOrder[8];								// this+0x1C
};

class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	// Declared, not defined: retail calls this out of line through the ILT thunk
	// at 0x0003D839, and that call is what forces the register allocation the
	// rest of the body has -- `this` parked in esi, the running length in edi.
	// An inline accessor compiles the load in place and misses by four bytes.
	UnsignedInt getDataLength();

	UnsignedByte *m_data;							// this+0x1C
	UnsignedInt m_dataLength;						// this+0x20
	UnsignedInt m_dataOffset;						// this+0x24
	UnsignedInt m_totalDataLength;					// this+0x28
	UnsignedInt m_chunkNumber;						// this+0x2C
	UnsignedInt m_numChunks;						// this+0x30
	UnsignedShort m_wrappedCommandID;				// this+0x34
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForFileMessage(NetCommandRef *msg);				// ILT thunk 0x0003B7A5
	Bool isRoomForFileAnnounceMessage(NetCommandRef *msg);			// ILT thunk 0x00035387
	Bool isRoomForGameSpyStatsAuthKeyMessage(NetCommandRef *msg);		// ILT thunk 0x00011A68
	Bool isRoomForRequestGameSpyStatsAuthKeyMessage(NetCommandRef *msg);
	Bool isRoomForWrapperMessage(NetCommandRef *msg);
	Bool isRoomForRouterFallbackMessage(NetCommandRef *msg);

	Bool addFileCommand(NetCommandRef *msg);
	Bool addFileAnnounceCommand(NetCommandRef *msg);
	Bool addGameSpyStatsAuthKeyCommand(NetCommandRef *msg);
	Bool addRequestGameSpyStatsAuthKeyCommand(NetCommandRef *msg);

	static void FillBufferWithRouterFallbackCommand(UnsignedByte *buffer,
		NetCommandRef *msg);

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


// NetPacket::addFileCommand, retail 0x0067F600, 668 bytes.
//
// addCommand's jump table pins this address as the arm for command type 4
// (NETCOMMANDTYPE_FILE), and it opens with the isRoomFor guard landed
// alongside it, NetPacket_isRoomForFileAndChat.cpp's isRoomForFileMessage at
// 0x0067DBB0.
//
// Structurally it is addRequestGameSpyStatsAuthKeyCommand's shape below (the
// same 'T'/'R'/'P'/'C' header run, the same 'D', the same command bookkeeping
// and NetCommandRef replacement) with the payload extended: the filename is
// copied with the strcpy intrinsic exactly as that sibling copies its text,
// then the file length and the raw file data follow, matching
// NetPacket_fillFileMessage.cpp's FillBufferWithFileMessage field order and
// NetPacket_commandSizes.cpp's GetFileCommandSize accounting.
Bool NetPacket::addFileCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForFileMessage(msg)) {
		NetFileCommandMsg *cmdMsg = (NetFileCommandMsg *)(msg->getCommand());

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

		UnsignedInt fileLength = cmdMsg->getFileLength();
		memcpy(m_packet + m_packetLen, &fileLength, sizeof(fileLength));
		m_packetLen += sizeof(fileLength);

		memcpy(m_packet + m_packetLen, cmdMsg->getFileData(), fileLength);
		m_packetLen += fileLength;

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


// NetPacket::addFileAnnounceCommand, retail 0x0067F950, 651 bytes.
//
// addCommand's jump table pins this address as the arm for command type 6
// (NETCOMMANDTYPE_FILEANNOUNCE) here (BFME renumbers the GameSpy stats-authkey
// pair ahead of it), and it opens with the isRoomFor guard landed alongside
// it, NetPacket_isRoomForFileAndChat.cpp's isRoomForFileAnnounceMessage at
// 0x0067DC80.
//
// Structurally it is addFileCommand's sibling above with the payload
// swapped: the same filename copy through strcpy, then the two small fields
// NetPacket_commandSizesGameSpy.cpp's neighbour NetPacket_commandSizes.cpp's
// GetFileAnnounceCommandSize counts -- getFileID (UnsignedShort) and
// getPlayerMask (UnsignedByte) -- matching
// NetPacket_fillFileMessage.cpp's field order for the file-data pair, just
// with the shorter announce fields.
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


// NetPacket::addRequestGameSpyStatsAuthKeyCommand, 0x00680350, 574 bytes.
//
// addCommand's jump table pins this address as the arm for command type 5, and
// the guard it opens with is the isRoomFor landed alongside it at 0x0067E1F0.
//
// Structurally it is addFileProgressCommand with one payload swapped: the same
// 'T'/'R'/'P'/'C' header run, the same 'D', the same command bookkeeping and
// NetCommandRef replacement at the end. What differs is the body of the
// message -- a NUL-terminated string copied straight into the packet, then
// getLength() + 1 charged for it, which is exactly the length the isRoomFor
// counts.
//
// Two things the bytes pin about that copy. The store loop is a byte-at-a-time
// run that stops on the terminator, so it is the strcpy intrinsic and not the
// getCharAt loop FillBufferWithFileMessage uses for the same job. And the text
// is a NAMED local, not a temporary: retail destroys it after the new
// NetCommandRef is installed, at the end of the block, rather than at the end
// of the statement that reads its length.
Bool NetPacket::addRequestGameSpyStatsAuthKeyCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForRequestGameSpyStatsAuthKeyMessage(msg)) {
		BFMENetRequestGameSpyStatsAuthKeyCommandMsg *cmdMsg =
				(BFMENetRequestGameSpyStatsAuthKeyCommandMsg *)(msg->getCommand());

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

		StringBase<char> text = cmdMsg->getText1C();
		strcpy((char *)(m_packet + m_packetLen), text.str());
		m_packetLen += text.getLength() + 1;

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


// NetPacket::addGameSpyStatsAuthKeyCommand, retail 0x00680620, 680 bytes.
//
// symbols.csv pins addCommand's arm for this address directly (the ILT hop is
// the further indirection); the guard it opens with is
// isRoomForGameSpyStatsAuthKeyMessage at 0x0067E2B0, still a gen-asm dump but
// already a matched, byte-true row so its REL32 resolves normally.
//
// Structurally it is addRequestGameSpyStatsAuthKeyCommand's
// sibling above: same header run, same 'D', same NetCommandRef bookkeeping, and the
// SAME strcpy-intrinsic copy through str()'s null fallback -- retail's own
// disassembly shows two real calls to the getText1C/getText20 getters each
// followed by an inlined byte-copy loop, not the guarded memcpy the
// FillBufferWithGameSpyStatsAuthKeyCommand static helper uses for the same
// fields (that shape belongs to the wire-fill function, not this one; a first
// attempt copying it grew the body by 68 bytes and swapped esi/edi/ebx for
// ebp/edi/ebx). getLength()+1 per field matches
// NetPacket_commandSizesGameSpy.cpp's GetGameSpyStatsAuthKeyCommandSize.
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


// NetPacket::isRoomForRequestGameSpyStatsAuthKeyMessage, 0x0067E1F0, 152 bytes.
//
// Named the way the rest of the family is: addCommand's jump table pins
// ?addRequestGameSpyStatsAuthKeyCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z at
// 0x00680350 as the arm for command type 5, and that body opens with a call to
// this one -- the same guard-then-write pairing every other add* has with its
// own isRoomFor. Nothing else calls it.
//
// The header accounting is the frame family's, byte for byte: 2 for the command
// type, 2 for the relay, 2 for the player id, 3 for the command id. What is new
// is the payload, and it is the whole reason this message needs its own member:
// the length is not a constant but the text the command carries, so the guard
// has to call ?getText1C@BFMENetRequestGameSpyStatsAuthKeyCommandMsg@@... to
// find out, and the terminator makes it getLength() + 1.
Bool NetPacket::isRoomForRequestGameSpyStatsAuthKeyMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg *cmdMsg =
			(BFMENetRequestGameSpyStatsAuthKeyCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len; // the 'D'
	len += cmdMsg->getText1C().getLength() + 1;

	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}


// NetPacket::isRoomForWrapperMessage, 0x00677BC0, 123 bytes.
//
// Named from the caller, not from a byte-prefix vote: addWrapperCommand's five
// call bytes resolve to the ILT thunk 0x00044FEE, whose body is this one, and
// the pin is already in targets/game/reverse/symbols.csv. The body agrees: it accumulates a
// length from the msg fields, compares against 0x1DC (MAX_PACKET_SIZE) and
// returns through setle.
//
// The body is the reference's, unchanged. What was missing was the ABI, and it
// is supplied here rather than through the shared headers, because BFME drifts
// from the ZH reference on two layouts that other, already-matched rows depend
// on keeping as they are:
//
//   NetPacket    - retail keeps m_port immediately after m_addr as an embedded
//                  ip+port pair, so m_numCommands .. m_lastRelay all sit lower
//                  than the ZH header puts them. NetPacket_init.cpp proves this
//                  ordering across 0x1E0-0x1FC from a matched body.
//   NetCommandRef- retail's is NOT a MemoryPoolObject and carries no vptr:
//                  m_msg at 0, m_next 4, m_prev 8, m_relay 0xC, m_timeLastSent
//                  0x10. The matched ctor at 0x00676240 and the matched dtor at
//                  0x00676280 (NetCommandRef_dtor.cpp) both confirm it.
//
// Only the slice this body touches is declared, at the retail offsets, with the
// correct overall sizes. Editing the shared headers instead would change the
// meaning of three rows that are already matched against the ZH layout, and it
// would run the full gate for no gain -- nothing outside this file needs it.
Bool NetPacket::isRoomForWrapperMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)(msg->getCommand());
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
	len += sizeof(UnsignedShort); // wrapped command ID
	len += sizeof(UnsignedInt); // chunk number
	len += sizeof(UnsignedInt); // number of chunks
	len += sizeof(UnsignedInt); // total data length
	len += sizeof(UnsignedInt); // data length of this chunk
	len += sizeof(UnsignedInt); // offset of this chunk
	len += cmdMsg->getDataLength(); // for the data of this chunk

	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}

	return true;
}

// NetPacket::isRoomForRouterFallbackMessage, retail 0x00678050, 114 bytes.
//
// Identified from its one caller, retail 0x0067C150 (NetPacket's
// add-RouterFallback path, still an unnamed dump): that body calls this
// function, then writes the T/R/P/C header and a 'D' followed by a loop of
// eight bytes read from the Int array at cmdMsg+0x1C -- the same eight ratio
// slots that the matched FillBufferWithRouterFallbackCommand (0x006770B0)
// and BFMENetRouterFallbackCommandMsg::setPlayerOrder (0x00673A50)
// write.  The wire format carries no frame field, which is why this sibling
// omits the m_lastFrame test the 128-byte members have, and its unconditional
// tail of 9 is the 'D' plus those eight payload bytes.
Bool NetPacket::isRoomForRouterFallbackMessage(NetCommandRef *msg) {
	Int len = 0;
	Bool needNewCommandID = false;
	NetCommandMsg *cmdMsg = (NetCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay()) {
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len; // the 'D'
	// The payload is the eight one-byte player IDs; the retail body folded them
	// into two dword adds, so that shape is kept to reproduce the constant.
	len += sizeof(UnsignedInt);
	len += sizeof(UnsignedInt);
	if ((len + m_packetLen) > MAX_PACKET_SIZE) {
		return false;
	}
	return true;
}


// NetPacket::FillBufferWithRouterFallbackCommand, retail 0x006770B0,
// 106 bytes.  The eight ratio slots are the BFME command's proven Int array;
// the wire format carries one byte from each slot, as readRouterFallback
// does in NetPacket_read.cpp.
void NetPacket::FillBufferWithRouterFallbackCommand(UnsignedByte *buffer,
	NetCommandRef *msg)
{
	BFMENetRouterFallbackCommandMsg *cmdMsg =
		(BFMENetRouterFallbackCommandMsg *)msg->getCommand();
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->getRelay();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	*(UnsignedShort *)(buffer + offset) = newID;
	offset += sizeof(UnsignedShort);
	buffer[offset] = 'D';
	++offset;
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[0];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[1];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[2];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[3];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[4];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[5];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[6];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_playerOrder[7];
}
