// cl: /DNDEBUG /MD /EHsc
// partial score=0.80 date=2026-09-05
// NetPacket::addAckCommand, 0x0067DEC0, 642 bytes.
//
// BFME's ack message carries the acking player's ID as a fourth argument
// (the reference declaration only has three: msg, commandID,
// originalPlayerID). Retail cleans 0x10 (four stack dwords) on return,
// confirming the fourth arg; NetPacket_ackCommands.cpp's three callers
// (addAckBothCommand/addAckStage1Command/addAckStage2Command) already pass
// ackmsg->getPlayerID() as that fourth argument and declare this exact
// signature as an extern prototype, so this file supplies the body the
// mangled name ?addAckCommand@NetPacket@@IAE_NPAVNetCommandRef@@GEI@Z needs.
//
// isRoomForAckMessage (ZH's separate helper) is fully inlined here: retail
// emits no call between the isAckRepeat() branch and the packet-fill code,
// only the same field comparisons twice (once to size the request, once to
// decide which tag bytes to emit). The BFME-only playerID field is appended
// after 'D'/commandID/originalPlayerID with no tag byte of its own, sized
// straight into the same length check (8 = 'D' + sizeof(UnsignedShort) +
// sizeof(UnsignedByte) + sizeof(UnsignedInt)).
//
// NetCommandRef's BFME layout (m_msg at +0, not +4; m_relay at +0xC, not
// +0x10; no vtable) is the one the already-matched ctor/dtor use in
// NetCommandRef_dtor.cpp -- reproduced here so this TU can call them
// unqualified via `new`/`delete`. NetCommandMsg's layout (m_playerID +0xC,
// m_commandType +0x14) is the one Network_GetCommandsFromCommandList.cpp
// already matched against retail.
//
// NetPacket's own diverging fields (m_packetLen/m_numCommands ahead of
// m_lastCommand, matching the BfmeNetPacketFields view in NetPacket.cpp)
// are declared directly at their retail offsets rather than through a cast
// view, since this TU does not include the vendored NetPacket.h.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Bool;
enum { FALSE = 0, TRUE = 1 };
enum { MAX_PACKET_SIZE = 476 };

#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
// (matched against retail in Network_GetCommandsFromCommandList.cpp)
class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();

	UnsignedInt getPlayerID(void) { return m_playerID; }
	Int getNetCommandType(void) { return m_commandType; }

	UnsignedInt m_timestamp;			// +0x04
	UnsignedInt m_executionFrame;			// +0x08
	UnsignedInt m_playerID;			// +0x0C
	unsigned short m_id;				// +0x10
	Int m_commandType;				// +0x14
	Int m_referenceCount;				// +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
// BFME layout (matches the already-matched ctor/dtor in NetCommandRef_dtor.cpp):
// no vtable, m_msg at +0x00, m_relay at +0x0C.
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();

	NetCommandMsg *getCommand(void) { return m_msg; }
	UnsignedByte getRelay(void) { return m_relay; }
	void setRelay(UnsignedByte v) { m_relay = v; }

private:
	NetCommandMsg *m_msg;				// +0x00
	NetCommandRef *m_next;				// +0x04
	NetCommandRef *m_prev;				// +0x08
	UnsignedByte m_relay;				// +0x0C
	UnsignedInt m_timeLastSent;			// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
// NetPacket : public MemoryPoolObject, so the vtable pointer occupies +0x00
// and m_packet starts at +0x04, ending exactly at +0x1E0 (MAX_PACKET_SIZE).
// isAckRepeat's own identity is not yet recovered (still the raw dump
// FUN_00a7c990/0x0067C990); reach it the way every other not-yet-identified
// callee in this build is reached, through its incremental-link thunk.
extern "C" void j_0000c70c(void);

class NetPacket
{
	// isAckRepeat is reached only through the union/member-pointer trick
	// below; this dummy receiver just gives the member-function-pointer
	// type the right argument shape for the __thiscall the thunk expects.
	class IsAckRepeatReceiver
	{
	public:
		bool isAckRepeat(NetCommandRef *msg);
	};

	union IsAckRepeatCall
	{
		void (*free_function)(void);
		bool (IsAckRepeatReceiver::*member_function)(NetCommandRef *msg);
	};

protected:
	bool addAckCommand(NetCommandRef *msg, UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt playerID);

	unsigned char m_pad000[0x04];			// +0x00 vtable ptr (MemoryPoolObject)
	UnsignedByte m_packet[MAX_PACKET_SIZE];	// +0x04
	Int m_packetLen;				// +0x1E0
	unsigned char m_pad1E4[0x1EC - 0x1E4];		// +0x1E4 fields not touched here
	Int m_numCommands;				// +0x1EC
	NetCommandRef *m_lastCommand;			// +0x1F0
	unsigned char m_pad1F4[0x1FA - 0x1F4];		// +0x1F4 fields not touched here
	UnsignedByte m_lastPlayerID;			// +0x1FA
	UnsignedByte m_lastCommandType;			// +0x1FB
};

// ?addAckCommand@NetPacket@@IAE_NPAVNetCommandRef@@GEI@Z
bool NetPacket::addAckCommand(NetCommandRef *msg, UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt playerID)
{
	IsAckRepeatCall call;
	call.free_function = &j_0000c70c;
	if ((((IsAckRepeatReceiver *)this)->*call.member_function)(msg))
	{
		if (m_packetLen >= MAX_PACKET_SIZE)
			return FALSE;

		m_packet[m_packetLen] = 'Z';
		++m_packetLen;
		++m_numCommands;

		if (m_lastCommand != 0)
		{
			delete m_lastCommand;
			m_lastCommand = 0;
		}

		NetCommandRef *newRef = new NetCommandRef(msg->getCommand());
		newRef->setRelay(msg->getRelay());
		m_lastCommand = newRef;
		return TRUE;
	}

	NetCommandMsg *cmdMsg = msg->getCommand();

	Int len = 0;
	if (m_lastCommandType != cmdMsg->getNetCommandType())
	{
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID())
	{
		++len;
		len += sizeof(UnsignedByte);
	}
	len += sizeof(UnsignedByte);			// 'D'
	len += sizeof(UnsignedShort);			// commandID
	len += sizeof(UnsignedByte);			// originalPlayerID
	len += sizeof(UnsignedInt);			// playerID (BFME only)

	if ((len + m_packetLen) > MAX_PACKET_SIZE)
		return FALSE;

	if (m_lastCommandType != cmdMsg->getNetCommandType())
	{
		m_packet[m_packetLen] = 'T';
		++m_packetLen;
		m_packet[m_packetLen] = (UnsignedByte)cmdMsg->getNetCommandType();
		m_packetLen += sizeof(UnsignedByte);

		m_lastCommandType = (UnsignedByte)cmdMsg->getNetCommandType();
	}

	if (m_lastPlayerID != cmdMsg->getPlayerID())
	{
		m_packet[m_packetLen] = 'P';
		++m_packetLen;
		m_packet[m_packetLen] = (UnsignedByte)cmdMsg->getPlayerID();
		m_packetLen += sizeof(UnsignedByte);

		m_lastPlayerID = (UnsignedByte)cmdMsg->getPlayerID();
	}

	m_packet[m_packetLen] = 'D';
	++m_packetLen;
	memcpy(m_packet + m_packetLen, &commandID, sizeof(UnsignedShort));
	m_packetLen += sizeof(UnsignedShort);
	memcpy(m_packet + m_packetLen, &originalPlayerID, sizeof(UnsignedByte));
	m_packetLen += sizeof(UnsignedByte);
	memcpy(m_packet + m_packetLen, &playerID, sizeof(UnsignedInt));
	m_packetLen += sizeof(UnsignedInt);

	if (m_lastCommand != 0)
	{
		delete m_lastCommand;
		m_lastCommand = 0;
	}
	m_lastCommand = new NetCommandRef(msg->getCommand());
	m_lastCommand->setRelay(msg->getRelay());

	++m_numCommands;
	return TRUE;
}
