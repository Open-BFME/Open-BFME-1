// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?FillBufferWithAckCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket::FillBufferWithAckCommand, retail 0x00676FB0, 120 bytes.
//
// The three ACK message classes share this body.  Their command ID and source
// player accessors are the authoritative NetCommandMsg declarations used by
// NetPacket_ackCommands.cpp; the dispatch on the concrete command type is
// retained because the retail body calls the matching accessor in each arm.

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

	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	int m_commandType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_msg; }

	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckBothCommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);

	UnsignedByte m_prefix[0x1c];
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	UnsignedByte m_padding;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckStage1CommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);

	UnsignedByte m_prefix[0x1c];
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	UnsignedByte m_padding;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckStage2CommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);

	UnsignedByte m_prefix[0x1c];
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	UnsignedByte m_padding;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static void FillBufferWithAckCommand(UnsignedByte *buffer, NetCommandRef *msg);
};

void NetPacket::FillBufferWithAckCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetCommandMsg *cmdMsg = msg->getCommand();
	UnsignedShort offset = 0;
	UnsignedShort commandID = 0;
	UnsignedByte originalPlayerID = 0;

	if (cmdMsg->getNetCommandType() == 0) {
		NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)msg;
		commandID = ackmsg->getCommandID();
		originalPlayerID = ackmsg->getOriginalPlayerID();
	} else if (cmdMsg->getNetCommandType() == 1) {
		NetAckStage1CommandMsg *ackmsg = (NetAckStage1CommandMsg *)msg;
		commandID = ackmsg->getCommandID();
		originalPlayerID = ackmsg->getOriginalPlayerID();
	} else if (cmdMsg->getNetCommandType() == 2) {
		NetAckStage2CommandMsg *ackmsg = (NetAckStage2CommandMsg *)msg;
		commandID = ackmsg->getCommandID();
		originalPlayerID = ackmsg->getOriginalPlayerID();
	}

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);
	buffer[offset] = 'D';
	++offset;
	memcpy(buffer + offset, &commandID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);
	memcpy(buffer + offset, &originalPlayerID, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);
}
