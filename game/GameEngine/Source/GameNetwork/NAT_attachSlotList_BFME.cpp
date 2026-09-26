// ?attachSlotList@NAT@@QAEXPAPAVGameSlot@@HI@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

#pragma pack(push, 1)
struct TransportAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};
#pragma pack(pop)

class Transport
{
public:
	Transport();
	bool init(const TransportAddress *address);

private:
	// The allocation immediate in this body and the matched constructor at
	// 0x00683360 independently establish BFME's retail Transport extent.
	unsigned char m_data[0x410e4];
};

class GameSlot
{
public:
	UnsignedShort getPort() const
	{
		return m_port;
	}

private:
	unsigned char m_unreconstructed00[0x34];
	UnsignedShort m_port;
};

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

	void attachSlotList(GameSlot **slotList, int localSlot, UnsignedInt localIP);

protected:
	void generatePortNumbers(GameSlot **slotList, int localSlot);

private:
	int getSlotPort(int slot) const
	{
		if (m_slotList[slot] != 0) {
			return m_slotList[slot]->getPort();
		}
		return 0;
	}

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
typedef char TransportAddressSizeMustBe6[
	sizeof(TransportAddress) == 6 ? 1 : -1];
typedef char TransportObjectSizeMustBe410E4[
	sizeof(Transport) == 0x410e4 ? 1 : -1];

void NAT::attachSlotList(GameSlot **slotList, int localSlot,
	UnsignedInt localIP)
{
	m_slotList = slotList;
	m_localIP = localIP;
	m_transport = new Transport;

	m_startingPortNumber = (UnsignedShort)(8088
		+ ((timeGetTime() / 1000) % 20000));
	generatePortNumbers(slotList, localSlot);

	UnsignedShort port = (UnsignedShort)getSlotPort(localSlot);
	TransportAddress address = { m_localIP, port };
	m_transport->init(&address);
}
