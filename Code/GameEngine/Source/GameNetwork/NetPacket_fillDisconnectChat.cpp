// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?FillBufferWithDisconnectChatCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// Retail 0x0067D580. Zero Hour's FillBufferWithDisconnectChatCommand, and it
// pairs with GetDisconnectChatCommandSize at 0x0067D370: 'T', 'R', 'P', 'D',
// then the length byte and the wide text -- eight bytes of header plus 2*len,
// which is that helper's 2*len + 8 exactly. No 'C' and no execution frame, which
// is what makes it shorter than the chat command beside it.
//
// Two differences from the chat body worth keeping straight. This message's type
// and player id are byte-sized -- retail reads them with mov dl, where
// NetChatCommandMsg's are dwords read with mov ecx -- and there is no unwind
// record at all despite the UnicodeString temporary, so the TU is /EHs-c-.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

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
	const T *str() const { return m_data ? (const T *)(m_data + 1) : (const T *)L""; }

private:
	void releaseBuffer();			// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	BfmeStringData *m_data;
};

class NetCommandMsg;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectChatCommandMsg
{
public:
	UnsignedByte getPlayerID(void) { return m_playerID; }
	UnsignedByte getNetCommandType(void) { return m_commandType; }

	StringBase<WideChar> getText(void);		// ILT thunk 0x00015901

	unsigned char m_bfmeHeadA[0x0C];
	UnsignedByte m_playerID;			// +0x0C
	unsigned char m_bfmeHeadB[0x14 - 0x0D];
	UnsignedByte m_commandType;			// +0x14
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
	static void FillBufferWithDisconnectChatCommand(UnsignedByte *buffer, NetCommandRef *msg);
};

// ?FillBufferWithDisconnectChatCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithDisconnectChatCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetDisconnectChatCommandMsg *cmdMsg = (NetDisconnectChatCommandMsg *)(msg->getCommand());
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = msg->getRelay();
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'D';
	++offset;
	StringBase<WideChar> unitext = cmdMsg->getText();
	UnsignedByte length = unitext.getLength();
	memcpy(buffer + offset, &length, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	memcpy(buffer + offset, unitext.str(), length * sizeof(UnsignedShort));
	offset += length * sizeof(UnsignedShort);
}
