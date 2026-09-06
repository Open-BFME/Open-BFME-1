// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?addDestroyPlayerCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addDisconnectFrameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addDisconnectKeepAliveCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addDisconnectPlayerCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addDisconnectScreenOffCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addDisconnectVoteCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addKeepAliveCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addLoadCompleteMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addPlayerLeaveCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addProgressMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addTimeOutGameStartMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addFileProgressCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?addWrapperCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable twins: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameNetwork/NetPacket.cpp

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#define NULL 0
#define TRUE 1

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;							// this+0x00
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;						// this+0x0C
	UnsignedShort m_id;						// this+0x10
	Int m_commandType;						// this+0x14
	Int m_referenceCount;						// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;						// this+0x00
	NetCommandRef *m_next;						// this+0x04
	NetCommandRef *m_prev;						// this+0x08
	UnsignedByte m_relay;						// this+0x0C
	UnsignedInt m_timeLastSent;					// this+0x10
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForDisconnectKeepAliveMessage(NetCommandRef *msg);
	Bool isRoomForKeepAliveMessage(NetCommandRef *msg);
	Bool isRoomForLoadCompleteMessage(NetCommandRef *msg);
	Bool isRoomForProgressMessage(NetCommandRef *msg);
	Bool isRoomForDisconnectVoteMessage(NetCommandRef *msg);
	Bool isRoomForDisconnectPlayerMessage(NetCommandRef *msg);
	Bool isRoomForPlayerLeaveMessage(NetCommandRef *msg);
	Bool isRoomForDisconnectScreenOffMessage(NetCommandRef *msg);
	Bool isRoomForDisconnectFrameMessage(NetCommandRef *msg);
	Bool isRoomForDestroyPlayerMessage(NetCommandRef *msg);
	Bool addDisconnectKeepAliveCommand(NetCommandRef *msg);
	Bool addKeepAliveCommand(NetCommandRef *msg);
	Bool addTimeOutGameStartMessage(NetCommandRef *msg);
	Bool addLoadCompleteMessage(NetCommandRef *msg);
	Bool addProgressMessage(NetCommandRef *msg);
	Bool addDisconnectVoteCommand(NetCommandRef *msg);
	Bool addDisconnectPlayerCommand(NetCommandRef *msg);
	Bool addPlayerLeaveCommand(NetCommandRef *msg);
	Bool addDisconnectScreenOffCommand(NetCommandRef *msg);
	Bool addDisconnectFrameCommand(NetCommandRef *msg);
	Bool addDestroyPlayerCommand(NetCommandRef *msg);
	Bool isRoomForFileProgressMessage(NetCommandRef *msg);		// ILT thunk 0x0000F6AF
	Bool isRoomForWrapperMessage(NetCommandRef *msg);		// ILT thunk 0x00044FEE
	Bool addFileProgressCommand(NetCommandRef *msg);
	Bool addWrapperCommand(NetCommandRef *msg);

public:
	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;						// this+0x1E0
	NetPacketAddress m_dest;					// this+0x1E4
	Int m_numCommands;						// this+0x1EC
	NetCommandRef *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;					// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;					// this+0x1FC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetProgressCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getPercentage();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectVoteCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getSlot();
	UnsignedInt getVoteFrame();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectPlayerCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getDisconnectSlot();
	UnsignedInt getDisconnectFrame();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getLeavingPlayerID();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectScreenOffCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getNewFrame();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getDisconnectFrame();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getPlayerIndex();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileProgressCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getFileID(void);			// ILT thunk 0x00012C15
	Int getProgress(void);				// ILT thunk 0x00033668
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getWrappedCommandID(void);	// ILT thunk 0x000057C7
	UnsignedInt getChunkNumber(void);		// ILT thunk 0x0003F814
	UnsignedInt getNumChunks(void);			// ILT thunk 0x00018BEC
	UnsignedInt getTotalDataLength(void);		// ILT thunk 0x0000F70E
	UnsignedInt getDataLength(void);		// ILT thunk 0x0003D839
	UnsignedInt getDataOffset(void);		// ILT thunk 0x00027048
	UnsignedByte *getData(void);			// ILT thunk 0x0002D867
};

Bool NetPacket::addDisconnectKeepAliveCommand(NetCommandRef *msg)
{
	if (isRoomForDisconnectKeepAliveMessage(msg)) {
		NetCommandMsg *cmdMsg = msg->getCommand();

		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}

		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
		}

		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		++m_numCommands;

		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addKeepAliveCommand(NetCommandRef *msg)
{
	if (isRoomForKeepAliveMessage(msg)) {
		NetCommandMsg *cmdMsg = msg->getCommand();

		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}

		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
		}

		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		++m_numCommands;

		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addTimeOutGameStartMessage(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForLoadCompleteMessage(msg)) {
		NetCommandMsg *cmdMsg = msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen++] = 'T';
			m_packet[m_packetLen++] = cmdMsg->getNetCommandType();
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen++] = 'R';
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(newRelay));
			m_packetLen += sizeof(newRelay);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen++] = 'P';
			m_packet[m_packetLen++] = cmdMsg->getPlayerID();
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen++] = 'C';
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(newID));
			m_packetLen += sizeof(newID);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen++] = 'D';
		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addLoadCompleteMessage(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForLoadCompleteMessage(msg)) {
		NetCommandMsg *cmdMsg = msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen++] = 'T';
			m_packet[m_packetLen++] = cmdMsg->getNetCommandType();
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen++] = 'R';
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(newRelay));
			m_packetLen += sizeof(newRelay);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen++] = 'P';
			m_packet[m_packetLen++] = cmdMsg->getPlayerID();
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen++] = 'C';
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(newID));
			m_packetLen += sizeof(newID);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen++] = 'D';
		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addProgressMessage(NetCommandRef *msg)
{
	if (isRoomForProgressMessage(msg)) {
		NetProgressCommandMsg *cmdMsg = (NetProgressCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen++] = 'T';
			m_packet[m_packetLen++] = cmdMsg->getNetCommandType();
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen++] = 'R';
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(newRelay));
			m_packetLen += sizeof(newRelay);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen++] = 'P';
			m_packet[m_packetLen++] = cmdMsg->getPlayerID();
			m_lastPlayerID = cmdMsg->getPlayerID();
		}
		m_packet[m_packetLen++] = 'D';
		m_packet[m_packetLen++] = cmdMsg->getPercentage();
		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addDisconnectVoteCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForDisconnectVoteMessage(msg)) {
		NetDisconnectVoteCommandMsg *cmdMsg = (NetDisconnectVoteCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte slot = cmdMsg->getSlot();
		memcpy(m_packet + m_packetLen, &slot, sizeof(slot));
		m_packetLen += sizeof(slot);
		UnsignedInt voteFrame = cmdMsg->getVoteFrame();
		memcpy(m_packet + m_packetLen, &voteFrame, sizeof(voteFrame));
		m_packetLen += sizeof(voteFrame);
		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addDisconnectPlayerCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForDisconnectPlayerMessage(msg)) {
		NetDisconnectPlayerCommandMsg *cmdMsg = (NetDisconnectPlayerCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte slot = cmdMsg->getDisconnectSlot();
		memcpy(m_packet + m_packetLen, &slot, sizeof(slot));
		m_packetLen += sizeof(slot);
		UnsignedInt disconnectFrame = cmdMsg->getDisconnectFrame();
		memcpy(m_packet + m_packetLen, &disconnectFrame, sizeof(disconnectFrame));
		m_packetLen += sizeof(disconnectFrame);
		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addPlayerLeaveCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForPlayerLeaveMessage(msg)) {
		NetPlayerLeaveCommandMsg *cmdMsg = (NetPlayerLeaveCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D';
		++m_packetLen;
		UnsignedByte leavingPlayerID = cmdMsg->getLeavingPlayerID();
		memcpy(m_packet + m_packetLen, &leavingPlayerID, sizeof(UnsignedByte));
		m_packetLen += sizeof(UnsignedByte);
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		++m_numCommands;
		return true;
	}
	return false;
}

#define DEFINE_FRAME_PAYLOAD_COMMAND(FUNCTION_NAME, ROOM_NAME, MESSAGE_TYPE, GETTER_NAME) \
Bool NetPacket::FUNCTION_NAME(NetCommandRef *msg) \
{ \
	Bool needNewCommandID = false; \
	if (ROOM_NAME(msg)) { \
		MESSAGE_TYPE *cmdMsg = (MESSAGE_TYPE *)msg->getCommand(); \
		if (m_lastCommandType != cmdMsg->getNetCommandType()) { \
			m_packet[m_packetLen] = 'T'; ++m_packetLen; \
			m_packet[m_packetLen] = cmdMsg->getNetCommandType(); m_packetLen += sizeof(UnsignedByte); \
			m_lastCommandType = cmdMsg->getNetCommandType(); \
		} \
		if (m_lastFrame != cmdMsg->getExecutionFrame()) { \
			m_packet[m_packetLen] = 'F'; ++m_packetLen; \
			UnsignedInt newframe = cmdMsg->getExecutionFrame(); \
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt)); \
			m_packetLen += sizeof(UnsignedInt); m_lastFrame = newframe; \
		} \
		if (m_lastRelay != msg->getRelay()) { \
			m_packet[m_packetLen] = 'R'; ++m_packetLen; \
			UnsignedByte newRelay = msg->getRelay(); \
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte)); \
			m_packetLen += sizeof(UnsignedByte); m_lastRelay = newRelay; \
		} \
		if (m_lastPlayerID != cmdMsg->getPlayerID()) { \
			m_packet[m_packetLen] = 'P'; ++m_packetLen; \
			m_packet[m_packetLen] = cmdMsg->getPlayerID(); m_packetLen += sizeof(UnsignedByte); \
			m_lastPlayerID = cmdMsg->getPlayerID(); needNewCommandID = true; \
		} \
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) { \
			m_packet[m_packetLen] = 'C'; ++m_packetLen; \
			UnsignedShort newID = cmdMsg->getID(); \
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort)); \
			m_packetLen += sizeof(UnsignedShort); \
		} \
		m_lastCommandID = cmdMsg->getID(); \
		m_packet[m_packetLen] = 'D'; ++m_packetLen; \
		UnsignedInt payload = cmdMsg->GETTER_NAME(); \
		memcpy(m_packet + m_packetLen, &payload, sizeof(payload)); \
		m_packetLen += sizeof(payload); ++m_numCommands; \
		if (m_lastCommand != NULL) { delete m_lastCommand; m_lastCommand = NULL; } \
		m_lastCommand = new NetCommandRef(msg->getCommand()); \
		m_lastCommand->setRelay(msg->getRelay()); \
		return true; \
	} \
	return false; \
}

DEFINE_FRAME_PAYLOAD_COMMAND(addDisconnectScreenOffCommand, isRoomForDisconnectScreenOffMessage,
	NetDisconnectScreenOffCommandMsg, getNewFrame)
DEFINE_FRAME_PAYLOAD_COMMAND(addDisconnectFrameCommand, isRoomForDisconnectFrameMessage,
	NetDisconnectFrameCommandMsg, getDisconnectFrame)

Bool NetPacket::addDestroyPlayerCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForDestroyPlayerMessage(msg)) {
		NetDestroyPlayerCommandMsg *cmdMsg = (NetDestroyPlayerCommandMsg *)msg->getCommand();
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType(); m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R'; ++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte); m_lastRelay = newRelay;
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F'; ++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt); m_lastFrame = newframe;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID(); m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID(); needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C'; ++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();
		m_packet[m_packetLen] = 'D'; ++m_packetLen;
		UnsignedInt playerIndex = cmdMsg->getPlayerIndex();
		memcpy(m_packet + m_packetLen, &playerIndex, sizeof(UnsignedInt));
		m_packetLen += sizeof(UnsignedInt); ++m_numCommands;
		if (m_lastCommand != NULL) { delete m_lastCommand; m_lastCommand = NULL; }
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());
		return true;
	}
	return false;
}

Bool NetPacket::addFileProgressCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForFileProgressMessage(msg)) {
		NetFileProgressCommandMsg *cmdMsg = (NetFileProgressCommandMsg *)(msg->getCommand());

		// If necessary, put the NetCommandType into the packet.
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);

			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		// If necessary, put the relay into the packet.
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);

			m_lastRelay = newRelay;
		}

		// If necessary put the player ID into the packet.
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);

			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}

		// If necessary, specify the command ID of this command.
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D';
		++m_packetLen;

		UnsignedShort fileID = cmdMsg->getFileID();
		memcpy(m_packet + m_packetLen, &fileID, sizeof(fileID));
		m_packetLen += sizeof(fileID);

		Int progress = cmdMsg->getProgress();
		memcpy(m_packet + m_packetLen, &progress, sizeof(progress));
		m_packetLen += sizeof(progress);

		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());

		return true;
	}
	return false;
}

Bool NetPacket::addWrapperCommand(NetCommandRef *msg) {
	Bool needNewCommandID = false;
	if (isRoomForWrapperMessage(msg)) {
		NetWrapperCommandMsg *cmdMsg = (NetWrapperCommandMsg *)(msg->getCommand());

		// If necessary, put the NetCommandType into the packet.
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);

			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		// If necessary, put the relay into the packet.
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);

			m_lastRelay = newRelay;
		}

		// If necessary put the player ID into the packet.
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);

			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}

		// If necessary, specify the command ID of this command.
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == true)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D';
		++m_packetLen;

		// wrapped command ID
		UnsignedShort wrappedCommandID = cmdMsg->getWrappedCommandID();
		memcpy(m_packet + m_packetLen, &wrappedCommandID, sizeof(wrappedCommandID));
		m_packetLen += sizeof(wrappedCommandID);

		// chunk number
		UnsignedInt chunkNumber = cmdMsg->getChunkNumber();
		memcpy(m_packet + m_packetLen, &chunkNumber, sizeof(chunkNumber));
		m_packetLen += sizeof(chunkNumber);

		// number of chunks
		UnsignedInt numChunks = cmdMsg->getNumChunks();
		memcpy(m_packet + m_packetLen, &numChunks, sizeof(numChunks));
		m_packetLen += sizeof(numChunks);

		// total length of data for all chunks
		UnsignedInt totalDataLength = cmdMsg->getTotalDataLength();
		memcpy(m_packet + m_packetLen, &totalDataLength, sizeof(totalDataLength));
		m_packetLen += sizeof(totalDataLength);

		// data length for this chunk
		UnsignedInt dataLength = cmdMsg->getDataLength();
		memcpy(m_packet + m_packetLen, &dataLength, sizeof(dataLength));
		m_packetLen += sizeof(dataLength);

		// the offset into the data of this chunk
		UnsignedInt dataOffset = cmdMsg->getDataOffset();
		memcpy(m_packet + m_packetLen, &dataOffset, sizeof(dataOffset));
		m_packetLen += sizeof(dataOffset);

		// the data for this chunk
		UnsignedByte *data = cmdMsg->getData();
		memcpy(m_packet + m_packetLen, data, dataLength);
		m_packetLen += dataLength;

		++m_numCommands;
		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());

		return true;
	}
	return false;
}
