// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?FillBufferWithDestroyPlayerCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?FillBufferWithPlayerLeaveCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// Player-leave and destroy-player serializers.  Their T/R/F/P/C/D layouts
// and distinct payload accessors are established by the BFME dispatcher,
// reader methods, and the authoritative NetCommandMsg declarations.

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

	UnsignedByte m_prefix[8];
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	UnsignedShort m_pad;
	int m_commandType;
	int m_referenceCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getLeavingPlayerID(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getPlayerIndex(void);
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
	static void FillBufferWithPlayerLeaveCommand(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithDestroyPlayerCommand(UnsignedByte *buffer, NetCommandRef *msg);
};

void NetPacket::FillBufferWithPlayerLeaveCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetPlayerLeaveCommandMsg *cmdMsg =
		(NetPlayerLeaveCommandMsg *)msg->getCommand();
	UnsignedShort offset = 0;
	buffer[offset] = 'T'; ++offset;
	buffer[offset] = cmdMsg->getNetCommandType(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'R'; ++offset;
	buffer[offset] = msg->getRelay(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'F'; ++offset;
	memcpy(buffer + offset, &cmdMsg->m_executionFrame, sizeof(UnsignedInt)); offset += sizeof(UnsignedInt);
	buffer[offset] = 'P'; ++offset;
	buffer[offset] = cmdMsg->getPlayerID(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'C'; ++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort)); offset += sizeof(UnsignedShort);
	buffer[offset] = 'D'; ++offset;
	buffer[offset] = cmdMsg->getLeavingPlayerID(); ++offset;
}

void NetPacket::FillBufferWithDestroyPlayerCommand(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetDestroyPlayerCommandMsg *cmdMsg =
		(NetDestroyPlayerCommandMsg *)msg->getCommand();
	UnsignedShort offset = 0;
	buffer[offset] = 'T'; ++offset;
	buffer[offset] = cmdMsg->getNetCommandType(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'R'; ++offset;
	buffer[offset] = msg->getRelay(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'F'; ++offset;
	memcpy(buffer + offset, &cmdMsg->m_executionFrame, sizeof(UnsignedInt)); offset += sizeof(UnsignedInt);
	buffer[offset] = 'P'; ++offset;
	buffer[offset] = cmdMsg->getPlayerID(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'C'; ++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort)); offset += sizeof(UnsignedShort);
	buffer[offset] = 'D'; ++offset;
	UnsignedInt playerIndex = cmdMsg->getPlayerIndex();
	memcpy(buffer + offset, &playerIndex, sizeof(UnsignedInt)); offset += sizeof(UnsignedInt);
}
