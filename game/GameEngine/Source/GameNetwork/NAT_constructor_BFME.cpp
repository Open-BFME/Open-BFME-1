// ??0NAT@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc

// BFME's NAT object is shorter than the Zero Hour layout.  The offsets below
// are corroborated by the matched NAT methods in this directory: the
// connection-state array starts at 0x44, each connection node occupies eight
// bytes at 0x64, and the BFME-only mangled-port flag is at 0xc4.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class GameSlot;
class Transport;

enum NATStateType
{
	NATSTATE_IDLE = 0
};

enum NATConnectionState
{
	NATCONNECTIONSTATE_NOSTATE = 0
};

struct NATConnectionNode
{
	int m_behavior;
	UnsignedInt m_slotIndex;
};

class NAT
{
public:
	NAT();
	virtual ~NAT();

private:
	Transport *m_transport;
	GameSlot **m_slotList;
	NATStateType m_NATState;
	int m_localNodeNumber;
	int m_targetNodeNumber;
	UnsignedInt m_localIP;
	UnsignedInt m_numNodes;
	int m_connectionRound;
	int m_numRetries;
	int m_maxNumRetriesAllowed;
	UnsignedShort m_packetID;
	UnsignedShort m_spareSocketPort;
	int m_manglerRetryTime;
	int m_manglerRetries;
	UnsignedShort m_previousSourcePort;
	bool m_beenProbed;
	UnsignedInt m_manglerAddress;
	int m_timeTillNextSend;
	NATConnectionState m_connectionStates[8];
	NATConnectionNode m_connectionNodes[8];
	bool m_myConnections[8];
	int m_nextKeepaliveTime;
	int m_connectionPairIndex;
	UnsignedShort m_startingPortNumber;
	int m_nextPortSendTime;
	int m_timeoutTime;
	int m_roundTimeout;
	bool m_applyMangledPort;
};

typedef char NATObjectSizeMustBeC8[sizeof(NAT) == 0xc8 ? 1 : -1];

NAT::NAT()
{
	m_transport = 0;
	m_slotList = 0;
	m_NATState = NATSTATE_IDLE;
	m_localNodeNumber = 0;
	m_targetNodeNumber = 0;
	m_localIP = 0;
	m_numNodes = 0;
	m_connectionRound = 0;
	m_numRetries = 0;
	m_maxNumRetriesAllowed = 10;
	m_packetID = 0x7f00;
	m_spareSocketPort = 0;
	m_manglerRetryTime = 0;
	m_manglerRetries = 0;
	m_previousSourcePort = 0;
	m_beenProbed = false;
	m_manglerAddress = 0;
	m_timeTillNextSend = 0;
	m_nextKeepaliveTime = 0;
	m_connectionPairIndex = 0;
	m_startingPortNumber = 0;
	m_nextPortSendTime = 0;
	m_timeoutTime = 0;
	m_roundTimeout = 0;
	m_applyMangledPort = true;

	for (int i = 0; i < 8; ++i) {
		m_connectionStates[i] = NATCONNECTIONSTATE_NOSTATE;
		m_connectionNodes[i].m_slotIndex = 0;
		m_myConnections[i] = false;
	}
}
