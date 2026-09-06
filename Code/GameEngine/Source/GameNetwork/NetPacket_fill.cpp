// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?FillBufferWithKeepAliveCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?FillBufferWithFileAnnounceMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?FillBufferWithFileMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket's FillBufferWith* serialisers.
//
// Each field goes into the packet behind a one-byte tag: 'T' for the command
// type, 'R' for the relay, 'P' for the player id, 'C' for the command id and
// 'D' to open the payload. That tagging is retail's, read off the bodies.
//
// These live in their own TU because they need BFME's de-pooled NetCommandRef --
// no vptr, so m_msg/m_next/m_prev/m_relay sit at +0x00/+0x04/+0x08/+0x0C rather
// than the reference header's +0x04/+0x08/+0x0C/+0x10. NetPacket.cpp itself
// cannot take that declaration without also losing NEW_NETCOMMANDREF and
// deleteInstance, which the rest of that file uses.
//
// The keep-alive serialiser is 0x00677240's body; the file announce one is
// 0x0067D880 and the file one 0x0067D740, each Zero Hour's field for field. The
// two file serialisers pair with GetFileAnnounceCommandSize at 0x0067D460 and
// GetFileCommandSize at 0x0067D410: the same header, the filename with its
// terminator, then the payload, adding up to the namelen + 0xE those helpers
// return. Their command messages are named by their getters, all ledgered:
// ?getPortableFilename@NetFileAnnounceCommandMsg, ?getFileID@... and
// ?getPlayerMask@... for the announce, ?getPortableFilename@NetFileCommandMsg,
// ?getFileLength@... and ?getFileData@... for the file -- each reached in
// exactly Zero Hour's order, including the second getFileLength call Zero Hour
// makes for the dead final offset bump.

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
	UnsignedShort m_len;							// +4
	UnsignedShort m_pad;
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

	Int getLength() const { return m_data ? m_data->m_len : 0; }
	T getCharAt(Int index) const { return m_data ? ((const T *)(m_data + 1))[index] : 0; }

private:
	void releaseBuffer();							// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	BfmeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	Int getNetCommandType() { return m_commandType; }

	char m_padToPlayerID[0x0C];						// vptr + timestamp + execFrame
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
};

// The two file messages share NetCommandMsg's header but are reached by a cast,
// not by inheritance: retail reads the whole player-id dword and narrows it at
// the store, so getPlayerID is Int here where Zero Hour has UnsignedByte.
class NetFileAnnounceCommandMsg
{
public:
	Int getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }
	Int getNetCommandType(void) { return m_commandType; }

	StringBase<char> getPortableFilename(void);		// ILT thunk 0x0003D50F
	UnsignedShort getFileID(void);					// ILT thunk 0x00030909
	UnsignedByte getPlayerMask(void);				// ILT thunk 0x000478F2

	unsigned char m_bfmeHead[0x0C];
	Int m_playerID;									// +0x0C
	UnsignedShort m_id;								// +0x10
	UnsignedShort m_pad;
	Int m_commandType;								// +0x14
};

class NetFileCommandMsg
{
public:
	Int getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }
	Int getNetCommandType(void) { return m_commandType; }

	StringBase<char> getPortableFilename(void);		// ILT thunk 0x00044323
	UnsignedInt getFileLength(void);				// ILT thunk 0x0001E7BD
	UnsignedByte *getFileData(void);				// ILT thunk 0x0003B598

	unsigned char m_bfmeHead[0x0C];
	Int m_playerID;									// +0x0C
	UnsignedShort m_id;								// +0x10
	UnsignedShort m_pad;
	Int m_commandType;								// +0x14
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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static void FillBufferWithKeepAliveCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithFileAnnounceMessage(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithFileMessage(UnsignedByte *buffer, NetCommandRef *msg);
};

void NetPacket::FillBufferWithKeepAliveCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = msg->getCommand();
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = msg->getRelay();
	buffer[offset] = newRelay;
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'D';
	++offset;
}

// ?FillBufferWithFileAnnounceMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithFileAnnounceMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetFileAnnounceCommandMsg *cmdMsg = (NetFileAnnounceCommandMsg *)(msg->getCommand());
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

	StringBase<char> filename = cmdMsg->getPortableFilename();	// PORTABLE
	for (Int i = 0; i < filename.getLength(); ++i) {
		buffer[offset] = filename.getCharAt(i);
		++offset;
	}
	buffer[offset] = 0;
	++offset;

	UnsignedShort fileID = cmdMsg->getFileID();
	memcpy(buffer + offset, &fileID, sizeof(fileID));
	offset += sizeof(fileID);

	UnsignedByte playerMask = cmdMsg->getPlayerMask();
	memcpy(buffer + offset, &playerMask, sizeof(playerMask));
	offset += sizeof(playerMask);
}

// ?FillBufferWithFileMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithFileMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetFileCommandMsg *cmdMsg = (NetFileCommandMsg *)(msg->getCommand());
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

	StringBase<char> filename = cmdMsg->getPortableFilename();	// PORTABLE
	for (Int i = 0; i < filename.getLength(); ++i) {
		buffer[offset] = filename.getCharAt(i);
		++offset;
	}
	buffer[offset] = 0;
	++offset;

	UnsignedInt newInt = cmdMsg->getFileLength();
	memcpy(buffer + offset, &newInt, sizeof(newInt));
	offset += sizeof(newInt);

	memcpy(buffer + offset, cmdMsg->getFileData(), cmdMsg->getFileLength());
	offset += cmdMsg->getFileLength();
}
