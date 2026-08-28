// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?FillBufferWithFrameCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket::FillBufferWithFrameCommand, retail 0x00677050, 76 bytes.
// The three payload words are the proven NetFrameCommandMsg fields at +1C,
// +20 and +24.  The packet tag order is read directly from this retail body.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	int getNetCommandType(void) { return m_commandType; }
	UnsignedInt getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }

	UnsignedByte m_prefix[0x0c];
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	UnsignedShort m_pad;
	int m_commandType;
	int m_referenceCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt m_frame;
	UnsignedInt m_field20;
	UnsignedInt m_commandCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_msg; }
	UnsignedByte getRelay(void) const { return m_relay; }

	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static void FillBufferWithFrameCommand(UnsignedByte *buffer, NetCommandRef *msg);
};

void NetPacket::FillBufferWithFrameCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetFrameCommandMsg *cmdMsg = (NetFrameCommandMsg *)msg->getCommand();
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
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);
	buffer[offset] = 'D';
	++offset;
	memcpy(buffer + offset, &cmdMsg->m_frame, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);
	memcpy(buffer + offset, &cmdMsg->m_field20, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);
	memcpy(buffer + offset, &cmdMsg->m_commandCount, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);
}
