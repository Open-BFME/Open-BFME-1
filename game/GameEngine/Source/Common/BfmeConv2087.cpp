class NetCommandRef;

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

	NetCommandRef *processAck(unsigned short cmd, unsigned char player, unsigned int n);
};

void BfmeConnXN::bfmeAckXN(NetAckStage1CommandMsg *msg)
{
	processAck(msg->getCommandID(), msg->getOriginalPlayerID(), msg->m_bfme20XN);
}

void BfmeConnXN::bfmeAckBothXN(NetAckBothCommandMsg *msg)
{
	processAck(msg->getCommandID(), msg->getOriginalPlayerID(), msg->m_bfme20XN);
}
