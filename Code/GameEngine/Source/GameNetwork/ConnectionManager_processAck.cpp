// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFMEConnectionManager::processAck, 0x006658F0, 150 bytes.
//
// The reference's three-way dispatch: ACKBOTH runs both stages, ACKSTAGE1 the
// first, ACKSTAGE2 the second. Stage two is the ledger's
// ?processAckCommand@BFMEConnectionManager@@QAEXPAX@Z at 0x00665700; stage one
// is inlined here, which is why it appears twice in the body.
//
// BFME's stage one is the reference's minus its latency bookkeeping: the
// reference checks whether the acknowledged command was a FRAMEINFO and feeds
// its frame to m_frameMetrics.processLatencyResponse. Retail does no such thing
// -- it deletes the returned reference and stops. That is one more piece of the
// adaptive-latency layer that FINDINGS already shows is absent.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2
};

enum { NUM_CONNECTIONS = 8 };

void __cdecl operator delete(void *block) throw();

class NetCommandRef;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	Int getNetCommandType() { return m_commandType; }
	UnsignedInt getPlayerID() { return m_playerID; }

	void *m_vptr;
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	~NetCommandRef();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
class Connection
{
public:
	NetCommandRef *processAck(NetCommandMsg *msg);
};

class BFMEConnectionManager
{
public:
	void processAck(NetCommandMsg *msg);
	void processAckCommand(void *msg);

protected:
	void processAckStage1(NetCommandMsg *msg);

	void *m_vptr;
	Connection *m_connections[NUM_CONNECTIONS];		// this+0x04 .. +0x24
};

// Inline in retail: the body below appears once for ACKBOTH and once for
// ACKSTAGE1 rather than as a call.
// ?processAckStage1@BFMEConnectionManager@@IAEXPAVNetCommandMsg@@@Z absent-from-retail
void BFMEConnectionManager::processAckStage1(NetCommandMsg *msg) {
	UnsignedByte playerID = msg->getPlayerID();
	NetCommandRef *ref = 0;

	if (playerID < NUM_CONNECTIONS) {
		if (m_connections[playerID] != 0) {
			ref = m_connections[playerID]->processAck(msg);
		}
	}

	if (ref != 0) {
		delete ref;
	}
}

void BFMEConnectionManager::processAck(NetCommandMsg *msg) {
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		processAckStage1(msg);
		processAckCommand(msg);
	} else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		processAckStage1(msg);
	} else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2) {
		processAckCommand(msg);
	}
}
