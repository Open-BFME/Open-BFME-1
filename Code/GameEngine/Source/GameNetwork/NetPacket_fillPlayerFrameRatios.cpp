// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::FillBufferWithPlayerFrameRatiosCommand, retail 0x006770B0,
// 106 bytes.  The eight ratio slots are the BFME command's proven Int array;
// the wire format carries one byte from each slot, as readPlayerFrameRatios
// does in NetPacket_read.cpp.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

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

class BFMENetPlayerFrameRatiosCommandMsg : public NetCommandMsg
{
public:
	Int m_ratios[8];
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
	static void FillBufferWithPlayerFrameRatiosCommand(UnsignedByte *buffer,
		NetCommandRef *msg);
};

void NetPacket::FillBufferWithPlayerFrameRatiosCommand(UnsignedByte *buffer,
	NetCommandRef *msg)
{
	BFMENetPlayerFrameRatiosCommandMsg *cmdMsg =
		(BFMENetPlayerFrameRatiosCommandMsg *)msg->getCommand();
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
	*(UnsignedShort *)(buffer + offset) = newID;
	offset += sizeof(UnsignedShort);
	buffer[offset] = 'D';
	++offset;
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[0];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[1];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[2];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[3];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[4];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[5];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[6];
	buffer[offset++] = (UnsignedByte)cmdMsg->m_ratios[7];
}
