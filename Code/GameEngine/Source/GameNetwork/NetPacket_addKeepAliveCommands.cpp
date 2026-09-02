// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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

class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

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

public:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	NetPacketAddress m_dest;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_lastFrame;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
};

class NetProgressCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getPercentage();
};

class NetDisconnectVoteCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getSlot();
	UnsignedInt getVoteFrame();
};

class NetDisconnectPlayerCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getDisconnectSlot();
	UnsignedInt getDisconnectFrame();
};

class NetPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	UnsignedByte getLeavingPlayerID();
};

class NetDisconnectScreenOffCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getNewFrame();
};

class NetDisconnectFrameCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getDisconnectFrame();
};

class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getPlayerIndex();
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
