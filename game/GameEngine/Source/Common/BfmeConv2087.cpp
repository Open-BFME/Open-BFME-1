class NetCommandRef;

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef float Real;

enum
{
	CONNECTION_LATENCY_HISTORY_LENGTH = 200
};

class NetCommandMsg;
class NetCommandList;

class Connection
{
public:
	NetCommandRef *processAck(NetCommandMsg *msg);
	NetCommandRef *processAck(UnsignedShort commandID, UnsignedByte originalPlayerID, UnsignedInt originalExecutionFrame);

	char m_beforeCommandList[0x18];
	NetCommandList *m_netCommandList;
	UnsignedInt m_betweenListAndLatency;
	Real m_averageLatency;
	Real m_latencies[CONNECTION_LATENCY_HISTORY_LENGTH];
};

class NetAckStage1CommandMsg
{
public:
	unsigned char getOriginalPlayerID();
	unsigned short getCommandID();

	unsigned char m_bfmeHeadXN[0x20];
	unsigned int m_bfme20XN;
};

class NetAckBothCommandMsg
{
public:
	unsigned char getOriginalPlayerID();
	unsigned short getCommandID();

	unsigned char m_bfmeHeadXN[0x20];
	unsigned int m_bfme20XN;
};

class BfmeConnXN
{
public:
	void bfmeAckXN(NetAckStage1CommandMsg *msg);
	void bfmeAckBothXN(NetAckBothCommandMsg *msg);

};

void BfmeConnXN::bfmeAckXN(NetAckStage1CommandMsg *msg)
{
	((Connection *)this)->processAck(msg->getCommandID(), msg->getOriginalPlayerID(), msg->m_bfme20XN);
}

void BfmeConnXN::bfmeAckBothXN(NetAckBothCommandMsg *msg)
{
	((Connection *)this)->processAck(msg->getCommandID(), msg->getOriginalPlayerID(), msg->m_bfme20XN);
}
