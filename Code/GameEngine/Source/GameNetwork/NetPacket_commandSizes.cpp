// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?GetChatCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?GetDisconnectChatCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?GetFileAnnounceCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?GetFileCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket's per-command size helpers, retail 0x0067D370 and neighbours. Each
// one is Zero Hour's body arithmetic for arithmetic; which is which comes from
// the getter it calls, all four of them already ledgered:
//
//   0x0067D370  getText@NetDisconnectChatCommandMsg   2*len + 8
//   0x0067D3C0  getText@NetChatCommandMsg             2*len + 0x14
//   0x0067D410  0x0067D250 + getFileLength            namelen + 0xF + filelen
//   0x0067D460  0x0067D2E0                            namelen + 0xE
//
// The first, third and fourth constants are Zero Hour's exactly. The chat one is
// four larger, and not because BFME added a field: Zero Hour's own
// GetChatCommandSize omits the four-byte player mask that its
// FillBufferWithChatCommand writes, so the two disagree there. BFME's counts it.
// See NetPacket_fillChatCommand.cpp (0x0067D620), which writes that mask at
// 2*len + 0x10 and lands exactly on this 2*len + 0x14.
//
// The strings are StringBase<T> handles returned by value: the length is the
// word at +4, read as a byte because Zero Hour assigns it to an UnsignedByte,
// and the temporary is released through ?releaseBuffer@?$StringBase@T@@AAEXXZ.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

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
	void releaseBuffer();			// ?releaseBuffer@?$StringBase@T@@AAEXXZ

	BfmeStringData *m_data;
};

class NetCommandMsg;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectChatCommandMsg
{
public:
	StringBase<WideChar> getText(void);	// ILT thunk 0x00015901
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetChatCommandMsg
{
public:
	StringBase<WideChar> getText(void);		// ILT thunk 0x00025338
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileCommandMsg
{
public:
	StringBase<char> getPortableFilename(void);	// ILT thunk 0x00044323
	UnsignedInt getFileLength(void);		// ILT thunk 0x0001E7BD
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileAnnounceCommandMsg
{
public:
	StringBase<char> getPortableFilename(void);	// ILT thunk 0x0003D50F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static UnsignedInt GetDisconnectChatCommandSize(NetCommandMsg *msg);
	static UnsignedInt GetChatCommandSize(NetCommandMsg *msg);
	static UnsignedInt GetFileCommandSize(NetCommandMsg *msg);
	static UnsignedInt GetFileAnnounceCommandSize(NetCommandMsg *msg);
};

// ?GetDisconnectChatCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z
UnsignedInt NetPacket::GetDisconnectChatCommandSize(NetCommandMsg *msg)
{
	Int msglen = 0;
	NetDisconnectChatCommandMsg *cmdMsg = (NetDisconnectChatCommandMsg *)(msg);

	++msglen;
	msglen += sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	++msglen;
	msglen += sizeof(UnsignedByte);

	++msglen;				// the 'D'
	msglen += sizeof(UnsignedByte);		// string msglength
	UnsignedByte textmsglen = cmdMsg->getText().getLength();
	msglen += textmsglen * sizeof(UnsignedShort);

	return msglen;
}

// ?GetChatCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z
UnsignedInt NetPacket::GetChatCommandSize(NetCommandMsg *msg)
{
	Int msglen = 0;
	NetChatCommandMsg *cmdMsg = (NetChatCommandMsg *)(msg);

	++msglen;
	msglen += sizeof(UnsignedByte);
	msglen += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	++msglen;
	msglen += sizeof(UnsignedByte);
	msglen += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	msglen += sizeof(UnsignedInt);		// the player mask, which Zero Hour writes but does not count

	++msglen;				// the 'D'
	msglen += sizeof(UnsignedByte);		// string msglength
	UnsignedByte textmsglen = cmdMsg->getText().getLength();
	msglen += textmsglen * sizeof(UnsignedShort);

	return msglen;
}

// ?GetFileCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z
UnsignedInt NetPacket::GetFileCommandSize(NetCommandMsg *msg)
{
	NetFileCommandMsg *filemsg = (NetFileCommandMsg *)msg;
	UnsignedInt msglen = 0;
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'T' and command type
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'P' and player ID
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedShort);		// 'C' and command ID
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'R' and relay

	++msglen;							// 'D'

	msglen += filemsg->getPortableFilename().getLength() + 1;	// filename and its terminator
	msglen += sizeof(UnsignedInt);					// file data length
	msglen += filemsg->getFileLength();				// the file data

	return msglen;
}

// ?GetFileAnnounceCommandSize@NetPacket@@KAIPAVNetCommandMsg@@@Z
UnsignedInt NetPacket::GetFileAnnounceCommandSize(NetCommandMsg *msg)
{
	NetFileAnnounceCommandMsg *filemsg = (NetFileAnnounceCommandMsg *)msg;
	UnsignedInt msglen = 0;
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'T' and command type
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'P' and player ID
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedShort);		// 'C' and command ID
	msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);		// 'R' and relay

	++msglen;							// 'D'

	msglen += filemsg->getPortableFilename().getLength() + 1;	// filename and its terminator
	msglen += sizeof(UnsignedShort);				// m_fileID
	msglen += sizeof(UnsignedByte);					// m_playerMask

	return msglen;
}
