// cl: /DNDEBUG /MD /EHsc
// readable body of ?gotMangledPort@NAT@@IAEXHG@Z: Code/GameEngine/Source/GameNetwork/nat.cpp
// Open-BFME5: recovered BFME NAT mangled-port state machine.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	unsigned int getIP() const { return m_ip; }
	unsigned short getPort() const { return m_port; }
	void setPort(unsigned short port) { m_port = port; }
	unsigned char getNATBehavior() const { return m_natBehavior; }
private:
	unsigned char m_pad[0x30];
	unsigned int m_ip;
	unsigned short m_port;
	unsigned char m_pad2[2];
	unsigned char m_natBehavior;
};

struct NATConnectionNode
{
	int m_slotIndex;
	int m_unused;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NAT.h
class NAT
{
protected:
	void gotMangledPort(int nodeNumber, unsigned short mangledPort);
	void setConnectionStateRetail(int nodeNumber, int state);
	void sendAProbe(unsigned int ip, unsigned short port, int nodeNumber);
	void notifyTargetOfProbe(GameSlot *slot);

private:
	unsigned char m_pad0[8];
	GameSlot **m_slotList;
	unsigned char m_pad1[4];
	int m_localNodeNumber;
	int m_targetNodeNumber;
	unsigned char m_pad2[0x22];
	unsigned char m_beenProbed;
	unsigned char m_pad3[9];
	int m_connectionStates[9];
	NATConnectionNode m_connectionNodes[11];
	unsigned char m_pad4[4];
	unsigned char m_applyMangledPort;
};

void NAT::gotMangledPort(int nodeNumber, unsigned short mangledPort)
{
	if (m_connectionStates[m_localNodeNumber] == 5) return;
	GameSlot *targetSlot = m_slotList[m_connectionNodes[m_targetNodeNumber].m_slotIndex];
	if (!targetSlot) {
		setConnectionStateRetail(m_localNodeNumber, 6);
		return;
	}
	GameSlot *localSlot = m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex];
	if (!localSlot) {
		setConnectionStateRetail(m_localNodeNumber, 6);
		return;
	}
	if (nodeNumber != m_targetNodeNumber) return;
	if (m_applyMangledPort) targetSlot->setPort(mangledPort);
	if (m_connectionStates[m_localNodeNumber] == 2) return;
	if (!(localSlot->getNATBehavior() & 8) || m_beenProbed == 1 ||
		((localSlot->getNATBehavior() & 8) && (targetSlot->getNATBehavior() & 8))) {
		sendAProbe(targetSlot->getIP(), targetSlot->getPort(), m_localNodeNumber);
		notifyTargetOfProbe(targetSlot);
		setConnectionStateRetail(m_localNodeNumber, 4);
	}
}
