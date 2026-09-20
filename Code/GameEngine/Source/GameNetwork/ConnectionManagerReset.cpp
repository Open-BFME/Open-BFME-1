// ?reset@ConnectionManager@@QAEXXZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template <class Type>
class StringBase
{
	void releaseBuffer();

public:
	~StringBase()
	{
		releaseBuffer();
	}

	Type *m_buffer;
};

class NetCommandList
{
public:
	NetCommandList();
	virtual ~NetCommandList();
	void reset();

private:
	void *m_first;
	void *m_last;
	void *m_lastMessageInserted;
};

class NetCommandWrapperList
{
public:
	NetCommandWrapperList();
	virtual ~NetCommandWrapperList();
	void init();
	void reset();

private:
	void *m_list;
};

class Transport
{
public:
	~Transport();
	void reset();
};

class Connection
{
public:
	void deleteInstance()
	{
		this->~Connection();
		operator delete(this);
	}

	~Connection()
	{
		if (m_netCommandList != 0)
			delete m_netCommandList;
	}

private:
	unsigned int m_id;
	unsigned int m_openedTime;
	unsigned int m_unknown08;
	unsigned int m_unknown0C;
	unsigned short m_unknown10;
	unsigned short m_unknown12;
	StringBase<unsigned short> m_name;
	NetCommandList *m_netCommandList;
};

class FrameDataManager
{
public:
	virtual ~FrameDataManager();
};

class ConnectionManager
{
public:
	void reset();

private:
	void *m_vptr;
	Connection *m_connections[8];
	unsigned char m_padBeforeTransport[0x12024 - 0x24];
	Transport *m_transport;
	int m_localSlot;
	int m_packetRouterSlot;
	unsigned int m_playerIds[8];
	unsigned int m_pad12050;
	unsigned short m_pad12054;
	unsigned short m_pad12056;
	unsigned int m_pad12058;
	unsigned int m_frameCeiling;
	unsigned int m_playerLatestFrame[8];
	unsigned int m_playerState[8];
	unsigned int m_playerFrameInfoAux[8];
	unsigned int m_playerAux2[8];
	unsigned int m_pad120e0;
	FrameDataManager *m_frameData[8];
	NetCommandList *m_pendingCommands;
	NetCommandList *m_relayedCommands;
	NetCommandWrapperList *m_wrapperList;
	unsigned int m_localLeaveStarted;
	unsigned char m_pad12114;
	unsigned char m_pad12115;
};

void ConnectionManager::reset()
{
	if (m_transport != 0)
	{
		delete m_transport;
		m_transport = 0;
	}

	int i;
	Connection *connection;
	for (i = 0; i < 8; ++i)
	{
		Connection *current = m_connections[i];
		if (current == 0)
			continue;
		connection = current;
		connection->deleteInstance();
		m_connections[i] = 0;
	}

	for (i = 0; i < 8; ++i)
	{
		if (m_frameData[i] != 0)
		{
			delete m_frameData[i];
			m_frameData[i] = 0;
		}
	}

	if (m_pendingCommands == 0)
	{
		m_pendingCommands = new NetCommandList;
		m_pendingCommands->reset();
	}
	_ReadWriteBarrier();
	m_pendingCommands->reset();

	if (m_relayedCommands == 0)
	{
		m_relayedCommands = new NetCommandList;
		m_relayedCommands->reset();
	}
	m_relayedCommands->reset();

	if (m_wrapperList == 0)
	{
		m_wrapperList = new NetCommandWrapperList;
		m_wrapperList->init();
	}
	m_wrapperList->reset();

	m_localSlot = -1;
	m_packetRouterSlot = -1;
	m_frameCeiling = 0;

	for (i = 0; i < 8; ++i)
	{
		m_playerIds[i] = -1;
		m_playerLatestFrame[i] = 0;
		m_playerFrameInfoAux[i] = 0;
		m_playerAux2[i] = 0;
		m_playerState[i] = 0;
	}

	m_localLeaveStarted = 0;
	m_pad12114 = 0;
	m_pad12115 = 1;
}
