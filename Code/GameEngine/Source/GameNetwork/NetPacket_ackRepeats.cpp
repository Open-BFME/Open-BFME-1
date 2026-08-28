// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?isAckBothRepeat@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?isAckStage1Repeat@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?isAckStage2Repeat@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// BFME ACK repeat checks use the de-pooled NetCommandRef layout and retain the
// source player in each ACK message at +0x20.  The inherited ZH declarations
// omit that BFME comparison, so this TU keeps the recovered ABI slice local.

typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
#define FALSE false
#define TRUE true

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandType getNetCommandType(void) { return (NetCommandType)m_commandType; }
	UnsignedInt m_prefix[3];
	UnsignedInt m_playerID;
	UnsignedShort m_commandID;
	UnsignedShort m_padding;
	NetCommandType m_commandType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_msg; }
	UnsignedByte getRelay(void) { return m_relay; }
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
	UnsignedByte m_ackPrefix[0x1c];
	UnsignedShort m_ackCommandID;
	UnsignedByte m_originalPlayerID;
	UnsignedByte m_ackPadding;
	UnsignedInt m_ackPlayerID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckStage1CommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);
	UnsignedByte m_ackPrefix[0x1c];
	UnsignedShort m_ackCommandID;
	UnsignedByte m_originalPlayerID;
	UnsignedByte m_ackPadding;
	UnsignedInt m_ackPlayerID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckStage2CommandMsg
{
public:
	UnsignedShort getCommandID(void);
	UnsignedByte getOriginalPlayerID(void);
	UnsignedByte m_ackPrefix[0x1c];
	UnsignedShort m_ackCommandID;
	UnsignedByte m_originalPlayerID;
	UnsignedByte m_ackPadding;
	UnsignedInt m_ackPlayerID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	unsigned char m_packetPrefix[0x1f0];
	NetCommandRef *m_lastCommand;
	Bool isAckBothRepeat(NetCommandRef *msg);
	Bool isAckStage1Repeat(NetCommandRef *msg);
	Bool isAckStage2Repeat(NetCommandRef *msg);
};

Bool NetPacket::isAckBothRepeat(NetCommandRef *msg)
{
	NetAckBothCommandMsg *ack = (NetAckBothCommandMsg *)msg->getCommand();
	NetAckBothCommandMsg *lastAck = (NetAckBothCommandMsg *)(m_lastCommand->getCommand());
	if (lastAck->getCommandID() != (ack->getCommandID() - 1)) {
		return FALSE;
	}
	if (lastAck->getOriginalPlayerID() != ack->getOriginalPlayerID()) {
		return FALSE;
	}
	if (lastAck->m_ackPlayerID != ack->m_ackPlayerID) {
		return FALSE;
	}
	if (msg->getRelay() != m_lastCommand->getRelay()) {
		return FALSE;
	}
	return TRUE;
}

Bool NetPacket::isAckStage1Repeat(NetCommandRef *msg)
{
	NetAckStage2CommandMsg *ack = (NetAckStage2CommandMsg *)msg->getCommand();
	NetAckStage2CommandMsg *lastAck = (NetAckStage2CommandMsg *)(m_lastCommand->getCommand());
	if (lastAck->getCommandID() != (ack->getCommandID() - 1)) {
		return FALSE;
	}
	if (lastAck->getOriginalPlayerID() != ack->getOriginalPlayerID()) {
		return FALSE;
	}
	if (lastAck->m_ackPlayerID != ack->m_ackPlayerID) {
		return FALSE;
	}
	if (msg->getRelay() != m_lastCommand->getRelay()) {
		return FALSE;
	}
	return TRUE;
}

Bool NetPacket::isAckStage2Repeat(NetCommandRef *msg)
{
	NetAckStage2CommandMsg *ack = (NetAckStage2CommandMsg *)msg->getCommand();
	NetAckStage2CommandMsg *lastAck = (NetAckStage2CommandMsg *)(m_lastCommand->getCommand());
	if (lastAck->getCommandID() != (ack->getCommandID() - 1)) {
		return FALSE;
	}
	if (lastAck->getOriginalPlayerID() != ack->getOriginalPlayerID()) {
		return FALSE;
	}
	if (lastAck->m_ackPlayerID != ack->m_ackPlayerID) {
		return FALSE;
	}
	if (msg->getRelay() != m_lastCommand->getRelay()) {
		return FALSE;
	}
	return TRUE;
}
