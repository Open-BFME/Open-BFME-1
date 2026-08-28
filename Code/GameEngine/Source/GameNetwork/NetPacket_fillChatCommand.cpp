// cl: /DNDEBUG /MD /EHsc
// readable body of ?FillBufferWithChatCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// Retail 0x0067D620. Zero Hour's FillBufferWithChatCommand field for field, and
// it pairs with GetChatCommandSize at 0x0067D3C0: 'T', 'F' with the execution
// frame, 'R', 'P', 'C', 'D', then the length byte, the wide text and the player
// mask -- fifteen bytes of header plus 1 + 2*len + 4, which is the 2*len + 0x14
// that helper returns.
//
// Worth noting against Zero Hour: its own GetChatCommandSize does not count the
// four-byte player mask this body writes, so the two disagree there. BFME's
// counts it, which is where the four-byte difference between the two size
// functions comes from -- not an extra field.
//
// offset is an UnsignedShort, as in Zero Hour: that is what puts the movzx cx
// in front of the final store.

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
class NetChatCommandMsg
{
public:
	Int getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }
	Int getNetCommandType(void) { return m_commandType; }
	UnsignedInt getExecutionFrame(void) { return m_executionFrame; }

	StringBase<WideChar> getText(void);		// ILT thunk 0x00025338
	Int getPlayerMask(void);			// ILT thunk 0x00002B1C

	unsigned char m_bfmeHead[8];
	UnsignedInt m_executionFrame;			// +0x08
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
	static void FillBufferWithChatCommand(UnsignedByte *buffer, NetCommandRef *msg);
};

// ?FillBufferWithChatCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithChatCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetChatCommandMsg *cmdMsg = (NetChatCommandMsg *)(msg->getCommand());
	UnsignedShort offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'F';
	++offset;
	UnsignedInt newframe = cmdMsg->getExecutionFrame();
	memcpy(buffer + offset, &newframe, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = msg->getRelay();
	memcpy(buffer + offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;
	StringBase<WideChar> unitext = cmdMsg->getText();
	UnsignedByte length = unitext.getLength();
	Int playerMask = cmdMsg->getPlayerMask();
	memcpy(buffer + offset, &length, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	memcpy(buffer + offset, unitext.str(), length * sizeof(UnsignedShort));
	offset += length * sizeof(UnsignedShort);

	memcpy(buffer + offset, &playerMask, sizeof(Int));
	offset += sizeof(Int);
}
