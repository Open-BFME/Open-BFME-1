// cl: /O2
//
// NetPacket::FillBufferWithRequestPlayerLeaveCommand, retail 0x00677530,
// 66 bytes.
//
// Named from FillBufferWithCommand's jump table (dispatcher 0x0067F430, table
// 0x0067F52C): case 7 -- NETCOMMANDTYPE_REQUESTPLAYERLEAVE, per the enum
// NetPacket_addCommand.cpp pins -- reaches arm 0x0067F4FD, ILT 0x00038E6F,
// here.  Every other entry in that table lands on an already-matched
// FillBufferWith* of the matching type, so the mapping is checked twenty times
// over.  The fourteen bytes it writes are what GetRequestPlayerLeaveCommandSize
// returns (0xE), and the payload getter it calls is the type-7 one at
// 0x00674250, already the ICF owner under this class and method name.
#include <string.h>

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	UnsignedByte m_prefix[0xc];
	UnsignedByte m_playerID;		// +0xC
	UnsignedByte m_pad0[3];
	UnsignedShort m_id;			// +0x10
	UnsignedByte m_pad1[2];
	UnsignedByte m_commandType;		// +0x14
};

// BFME command type 7. Its one payload field is reached through the getter,
// which is matched at 0x00674250 under exactly this name.
class BFMENetRequestPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	Int getRequestedPlayerID();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *m_msg;			// +0x0
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;			// +0xC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static void FillBufferWithRequestPlayerLeaveCommand(UnsignedByte *buffer,
		NetCommandRef *msg);
};

void NetPacket::FillBufferWithRequestPlayerLeaveCommand(UnsignedByte *buffer,
	NetCommandRef *msg)
{
	BFMENetRequestPlayerLeaveCommandMsg *cmdMsg =
		(BFMENetRequestPlayerLeaveCommandMsg *)msg->m_msg;
	UnsignedInt offset = 0;

	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->m_commandType;
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'R';
	++offset;
	buffer[offset] = msg->m_relay;
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->m_playerID;
	offset += sizeof(UnsignedByte);

	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->m_id;
	memcpy(buffer + offset, &newID, sizeof(newID));
	offset += sizeof(newID);

	buffer[offset] = 'D';
	++offset;

	Int requestedPlayerID = cmdMsg->getRequestedPlayerID();
	memcpy(buffer + offset, &requestedPlayerID, sizeof(requestedPlayerID));
	offset += sizeof(requestedPlayerID);
}
