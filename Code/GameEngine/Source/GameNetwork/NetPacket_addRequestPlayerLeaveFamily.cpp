// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Three NetPacket add*Command bodies from d_006675c0.asm, all sitting between
// the already-landed addDisconnectScreenOffCommand (0x00679810) and
// addDisconnectFrameCommand (0x0067A410):
//
//   NetPacket::addRequestPlayerLeaveCommand,      0x00679E10, 591 bytes.
//   NetPacket::addInformPlayerLeaveFrameCommand,  0x00679B00, 625 bytes.
//   NetPacket::addRequestFrameDataCommand,        0x0067A100, 625 bytes.
//
// All three share the T,F,R,P,C,D shape NetPacket_addKeepAliveCommands.cpp's
// DEFINE_FRAME_PAYLOAD_COMMAND macro already proved (T before F before R is
// BFME's own reordering of the Zero Hour T,R,F sequence -- confirmed by the
// already-landed addDisconnectFrameCommand/addDisconnectScreenOffCommand).
//
// addInformPlayerLeaveFrameCommand's identity is direct, not inferred: its
// first call goes to isRoomForInformPlayerLeaveFrameMessage at the exact
// matched address 0x006778B0 (NetPacket_isRoomForDisconnectFamily.cpp), which
// already documents this pairing and the nine-byte trailing payload (two
// dwords, each fetched through its own call). addRequestPlayerLeaveCommand's
// single-dword payload getter call resolves to the exact matched address
// 0x00674250, which is
// ?getRequestedPlayerID@BFMENetRequestPlayerLeaveCommandMsg@@QAEHXZ
// (native_netcommandmsg.cpp) -- BFME command type 7. addRequestFrameDataCommand
// pairs naturally with BFME command type 9 (BFMENetRequestFrameDataCommandMsg,
// NetCommandMsg_ctors.cpp) by the same two-dword shape, though its isRoomFor
// call only reaches that message's ICF-folded twin (isRoomForInformPlayerLeave-
// FrameMessage's own code, per the alias row at 0x006779F0) rather than a
// separately matched isRoomForRequestFrameDataMessage.
//
// The two payload getter calls in addInformPlayerLeaveFrameCommand and
// addRequestFrameDataCommand do NOT reach the already-matched
// BFMENetInformPlayerLeaveFrameCommandMsg::getLeavingPlayerID/getLeaveFrame or
// BFMENetRequestFrameDataCommandMsg::getRequestedPlayerID/getRequestedFrame
// (those sit at 0x006741D0/0x6741E0/0x6742F0/0x674300, all far from this
// body's actual call targets 0x00034612/0x0002DF06/0x0000911F/0x00035EF4).
// Whatever those four callees really are remains unrecovered -- same
// "IDENTITY IS NOT RECOVERED" situation S3WireRecordFills.cpp already
// documented for these exact two address-derived classes and the exact same
// pinned fetchA/fetchB names, reused verbatim here rather than invented twice.

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

	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

// BFME command type 7. Only the payload getter is needed here; its real
// address (0x00674250) is already matched under this exact class/method name.
class BFMENetRequestPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	Int getRequestedPlayerID();
};

// Address-derived placeholder names, reused from
// Code/GameEngine/Source/Common/S3WireRecordFills.cpp: identity of the two
// fetch callees is not recovered, only their addresses (0x00034612/0x0002DF06
// and 0x0000911F/0x00035EF4, pinned in reverse/symbols.csv).
class Rva006774C0Msg : public NetCommandMsg
{
public:
	unsigned int fetchA();
	unsigned int fetchB();
};

class Rva00677590Msg : public NetCommandMsg
{
public:
	unsigned int fetchA();
	unsigned int fetchB();
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForRequestPlayerLeaveMessage(NetCommandRef *msg);
	Bool isRoomForInformPlayerLeaveFrameMessage(NetCommandRef *msg);
	Bool isRoomForRequestFrameDataMessage(NetCommandRef *msg);
	Bool addRequestPlayerLeaveCommand(NetCommandRef *msg);
	Bool addInformPlayerLeaveFrameCommand(NetCommandRef *msg);
	Bool addRequestFrameDataCommand(NetCommandRef *msg);

public:
	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;								// this+0x1E0
	NetPacketAddress m_dest;						// this+0x1E4
	Int m_numCommands;								// this+0x1EC
	NetCommandRef *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};

Bool NetPacket::addRequestPlayerLeaveCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForRequestPlayerLeaveMessage(msg)) {
		BFMENetRequestPlayerLeaveCommandMsg *cmdMsg = (BFMENetRequestPlayerLeaveCommandMsg *)msg->getCommand();

		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType(); m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F'; ++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R'; ++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID(); m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C'; ++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D'; ++m_packetLen;
		UnsignedInt requestedPlayerID = cmdMsg->getRequestedPlayerID();
		memcpy(m_packet + m_packetLen, &requestedPlayerID, sizeof(requestedPlayerID));
		m_packetLen += sizeof(requestedPlayerID);

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

Bool NetPacket::addInformPlayerLeaveFrameCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForInformPlayerLeaveFrameMessage(msg)) {
		Rva006774C0Msg *cmdMsg = (Rva006774C0Msg *)msg->getCommand();

		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType(); m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F'; ++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R'; ++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID(); m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C'; ++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D'; ++m_packetLen;
		UnsignedInt fieldA = cmdMsg->fetchA();
		memcpy(m_packet + m_packetLen, &fieldA, sizeof(fieldA));
		m_packetLen += sizeof(fieldA);
		UnsignedInt fieldB = cmdMsg->fetchB();
		memcpy(m_packet + m_packetLen, &fieldB, sizeof(fieldB));
		m_packetLen += sizeof(fieldB);

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

Bool NetPacket::addRequestFrameDataCommand(NetCommandRef *msg)
{
	Bool needNewCommandID = false;
	if (isRoomForRequestFrameDataMessage(msg)) {
		Rva00677590Msg *cmdMsg = (Rva00677590Msg *)msg->getCommand();

		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType(); m_packetLen += sizeof(UnsignedByte);
			m_lastCommandType = cmdMsg->getNetCommandType();
		}
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F'; ++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);
			m_lastFrame = newframe;
		}
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R'; ++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);
			m_lastRelay = newRelay;
		}
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P'; ++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID(); m_packetLen += sizeof(UnsignedByte);
			m_lastPlayerID = cmdMsg->getPlayerID();
			needNewCommandID = true;
		}
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C'; ++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D'; ++m_packetLen;
		UnsignedInt fieldA = cmdMsg->fetchA();
		memcpy(m_packet + m_packetLen, &fieldA, sizeof(fieldA));
		m_packetLen += sizeof(fieldA);
		UnsignedInt fieldB = cmdMsg->fetchB();
		memcpy(m_packet + m_packetLen, &fieldB, sizeof(fieldB));
		m_packetLen += sizeof(fieldB);

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
