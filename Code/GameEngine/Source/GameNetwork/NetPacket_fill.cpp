// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?FillBufferWithKeepAliveCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket's FillBufferWith* serialisers.
//
// Each field goes into the packet behind a one-byte tag: 'T' for the command
// type, 'R' for the relay, 'P' for the player id, 'D' to terminate. That tagging
// is retail's, read off the bodies.
//
// These live in their own TU because they need BFME's de-pooled NetCommandRef --
// no vptr, so m_msg/m_next/m_prev/m_relay sit at +0x00/+0x04/+0x08/+0x0C rather
// than the reference header's +0x04/+0x08/+0x0C/+0x10. NetPacket.cpp itself
// cannot take that declaration without also losing NEW_NETCOMMANDREF and
// deleteInstance, which the rest of that file uses.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

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
