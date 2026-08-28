// cl: /DNDEBUG /MD /GX

enum PlayerLeaveCode
{
	PLAYER_LEAVE_CODE_CLIENT
};

class ConnectionManager
{
public:
	PlayerLeaveCode disconnectPlayer(int slot);
	__declspec(noinline) void disconnectLocalPlayer(void);

private:
	unsigned char m_unmodelled_00000[0x12028];
	int m_localSlot;
};

class BFMEConnectionManager
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void update(bool isInGame, bool phase) = 0;
};

class GameMessage;

class MessageStream
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual GameMessage *appendMessage(unsigned int type) = 0;
};

extern MessageStream *TheMessageStream;

void ConnectionManager::disconnectLocalPlayer(void)
{
	for (int slot = 0; slot < 8; ++slot)
	{
		if (slot != m_localSlot)
			disconnectPlayer(slot);
	}
}

class Network
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void liteupdate(bool phase) = 0;
	virtual void update(bool phase);

protected:
	void GetCommandsFromCommandList(void);
	void RelayCommandsToCommandList(void);

private:
	void *m_subsystemName;
	ConnectionManager *m_conMgr;
	int m_localStatus;
	unsigned char m_gap10[0x24];
	bool m_frameDataReady;
};

void Network::liteupdate(bool phase)
{
	if (m_conMgr != 0)
	{
		BFMEConnectionManager *conMgr = (BFMEConnectionManager *)m_conMgr;
		conMgr->update(m_localStatus == 1, phase);
	}
}

void Network::update(bool phase)
{
	m_frameDataReady = false;
	if (m_localStatus == 0)
		m_localStatus = 1;

	GetCommandsFromCommandList();
	liteupdate(phase);

	if (m_localStatus == 2)
	{
		m_conMgr->disconnectLocalPlayer();
		TheMessageStream->appendMessage(0x1D);
		m_localStatus = 3;
	}

	RelayCommandsToCommandList();
}
