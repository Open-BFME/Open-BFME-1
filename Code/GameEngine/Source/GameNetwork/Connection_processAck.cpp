// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Connection::processAck(NetCommandMsg *), 0x00662270, 91 bytes.
//
// The reference's shape: dispatch on the ack stage, cast, and forward. What
// BFME adds is a third argument -- the original execution frame the ack carries
// at +0x20, which the reference's ack classes do not have at all. It is read
// straight off the field; there is no getter for it anywhere in the image.
//
// The reference routes each stage through a one-line overload taking the
// concrete ack class; retail inlines those, so only the three-argument form
// survives as a call.  That form is the second body below, 0x00661CC0/166.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1
};

typedef float Real;

// The three-argument processAck's own view of the list.  All offsets are read
// straight off the retail body at 0x00661CC0.
class NetCommandMsg;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	NetCommandRef *getNext() { return m_next; }
	UnsignedInt getTimeLastSent() { return m_timeLastSent; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedInt m_retryCount;						// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandList.h
class NetCommandList
{
public:
	NetCommandRef *getFirstMessage() { return m_first; }
	// Out of line in retail: the ack path reaches it through a plain call.
	void removeMessage(NetCommandRef *msg);

	void *m_vptr;									// this+0x00
	NetCommandRef *m_first;							// this+0x04
};

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

enum { CONNECTION_LATENCY_HISTORY_LENGTH = 200 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount;							// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
class Connection
{
public:
	NetCommandRef *processAck(NetCommandMsg *msg);
	NetCommandRef *processAck(UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt originalExecutionFrame);

	char m_beforeCommandList[0x18];					// this+0x00
	NetCommandList *m_netCommandList;				// this+0x18
	UnsignedInt m_betweenListAndLatency;			// this+0x1C
	Real m_averageLatency;							// this+0x20
	Real m_latencies[CONNECTION_LATENCY_HISTORY_LENGTH];	// this+0x24
};

NetCommandRef *Connection::processAck(NetCommandMsg *msg) {
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		NetAckStage1CommandMsg *ackmsg = (NetAckStage1CommandMsg *)msg;
		return processAck(ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), ackmsg->m_originalExecutionFrame);
	}

	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)msg;
		UnsignedInt originalExecutionFrame = ackmsg->m_originalExecutionFrame;
		return processAck(ackmsg->getCommandID(), ackmsg->getOriginalPlayerID(), originalExecutionFrame);
	}

	return 0;
}

// ?processAck@Connection@@QAEPAVNetCommandRef@@GEI@Z
NetCommandRef *Connection::processAck(UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt originalExecutionFrame) {
	NetCommandRef *temp = m_netCommandList->getFirstMessage();
	while ((temp != 0) && ((temp->getCommand()->m_id != commandID) ||
		(temp->getCommand()->m_playerID != originalPlayerID) ||
		(temp->getCommand()->m_executionFrame != originalExecutionFrame))) {

		// cycle through the commands till we find the one we need to remove.
		temp = temp->getNext();
	}
	if (temp == 0) {
		return 0;
	}

	Int index = temp->getCommand()->m_id % CONNECTION_LATENCY_HISTORY_LENGTH;
	m_averageLatency -= ((Real)(m_latencies[index])) / CONNECTION_LATENCY_HISTORY_LENGTH;
	Real lat = (Real)(timeGetTime() - temp->getTimeLastSent());
	m_averageLatency += lat / CONNECTION_LATENCY_HISTORY_LENGTH;
	m_latencies[index] = lat;

	m_netCommandList->removeMessage(temp);
	return temp;
}
