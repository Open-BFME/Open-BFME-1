// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?FillBufferWithDisconnectFrameMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?FillBufferWithDisconnectScreenOffMessage@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// The two named BFME one-word frame serializers.  Their distinct retail call
// targets identify the payload accessors: disconnect-frame and screen-off new
// frame.  Both share the proven T/R/P/C/D wire layout.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	Int getNetCommandType(void) { return m_commandType; }
	UnsignedInt getPlayerID(void) { return m_playerID; }
	UnsignedShort getID(void) { return m_id; }

	UnsignedByte m_prefix[0x0c];
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	UnsignedShort m_pad;
	Int m_commandType;
	Int m_referenceCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getDisconnectFrame(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectScreenOffCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getNewFrame(void);
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
	static void FillBufferWithDisconnectFrameMessage(UnsignedByte *buffer, NetCommandRef *msg);
	static void FillBufferWithDisconnectScreenOffMessage(UnsignedByte *buffer, NetCommandRef *msg);
};

void NetPacket::FillBufferWithDisconnectFrameMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetDisconnectFrameCommandMsg *cmdMsg =
		(NetDisconnectFrameCommandMsg *)msg->getCommand();
	UnsignedShort offset = 0;
	buffer[offset] = 'T'; ++offset;
	buffer[offset] = cmdMsg->getNetCommandType(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'R'; ++offset;
	buffer[offset] = msg->getRelay(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'P'; ++offset;
	buffer[offset] = cmdMsg->getPlayerID(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'C'; ++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(newID)); offset += sizeof(newID);
	buffer[offset] = 'D'; ++offset;
	UnsignedInt disconnectFrame = cmdMsg->getDisconnectFrame();
	memcpy(buffer + offset, &disconnectFrame, sizeof(disconnectFrame)); offset += sizeof(disconnectFrame);
}

void NetPacket::FillBufferWithDisconnectScreenOffMessage(UnsignedByte *buffer, NetCommandRef *msg)
{
	NetDisconnectScreenOffCommandMsg *cmdMsg =
		(NetDisconnectScreenOffCommandMsg *)msg->getCommand();
	UnsignedShort offset = 0;
	buffer[offset] = 'T'; ++offset;
	buffer[offset] = cmdMsg->getNetCommandType(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'R'; ++offset;
	buffer[offset] = msg->getRelay(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'P'; ++offset;
	buffer[offset] = cmdMsg->getPlayerID(); offset += sizeof(UnsignedByte);
	buffer[offset] = 'C'; ++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(newID)); offset += sizeof(newID);
	buffer[offset] = 'D'; ++offset;
	UnsignedInt newFrame = cmdMsg->getNewFrame();
	memcpy(buffer + offset, &newFrame, sizeof(newFrame)); offset += sizeof(newFrame);
}
