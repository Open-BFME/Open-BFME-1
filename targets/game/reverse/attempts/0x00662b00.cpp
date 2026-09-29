// ?isPlayerConnectedForTimeout@BFMEConnectionManager@@QAE_NHI@Z
// partial score=0.9318 date=2026-09-29
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00662A50 (138 bytes) and 0x00662B00 (132 bytes).
//
// Both answer whether a player still counts as connected. The local player is
// always connected, and so is a slot with no connection object. A connection whose
// time stamp at +0x34C is still zero gets the current time and counts as connected.
// Otherwise the elapsed time since that stamp must not exceed a timeout. During the
// first frames of a game (frame below the startup threshold at VA 0x010EAD50) the
// timeout is four times GlobalData+0xCBC (m_networkDisconnectTime), and afterwards
// the DefaultTimeout variant uses m_networkDisconnectTime itself while the ForTimeout
// variant uses its second argument.

extern int (*g_bfmeNowVNH)();
extern unsigned int g_dword010EAD50;

class Connection
{
public:
	char m_before[0x34C];
	volatile unsigned int m_timeStamp34C;
};

class GameLogic
{
public:
	char m_before[0x3C];
	unsigned int m_frame;
};

class GlobalData
{
public:
	char m_before[0xCBC];
	unsigned int m_networkDisconnectTime;
};

extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;

class BFMEConnectionManager
{
public:
	bool isPlayerConnectedDefaultTimeout(int playerID);
	bool isPlayerConnectedForTimeout(int playerID, unsigned int timeout);

private:
	char m_head[4];
	Connection *m_connections[0x4809];
	int m_localPlayerID;
};

// ?isPlayerConnectedDefaultTimeout@BFMEConnectionManager@@QAE_NH@Z
bool BFMEConnectionManager::isPlayerConnectedDefaultTimeout(int playerID)
{
	if (playerID == m_localPlayerID)
		return true;

	Connection *connection = m_connections[playerID];
	if (connection == 0)
		return true;

	unsigned int stamp = connection->m_timeStamp34C;
	if (stamp == 0)
	{
		connection->m_timeStamp34C = g_bfmeNowVNH();
		return true;
	}

	unsigned int now = g_bfmeNowVNH();
	if (TheBfmeGameLogic->m_frame >= g_dword010EAD50)
	{
		unsigned int last = connection->m_timeStamp34C;
		unsigned int limit = TheWritableGlobalData->m_networkDisconnectTime;
		return limit >= now - last ? true : false;
	}

	unsigned int limit = TheWritableGlobalData->m_networkDisconnectTime * 4;
	unsigned int last = connection->m_timeStamp34C;
	return limit >= now - last ? true : false;
}

// ?isPlayerConnectedForTimeout@BFMEConnectionManager@@QAE_NHI@Z
bool BFMEConnectionManager::isPlayerConnectedForTimeout(int playerID, unsigned int timeout)
{
	if (playerID == m_localPlayerID)
		return true;

	Connection *connection = m_connections[playerID];
	if (connection == 0)
		return true;

	unsigned int stamp = connection->m_timeStamp34C;
	if (stamp == 0)
	{
		connection->m_timeStamp34C = g_bfmeNowVNH();
		return true;
	}

	unsigned int now = g_bfmeNowVNH();
	if (TheBfmeGameLogic->m_frame >= g_dword010EAD50)
	{
		unsigned int last = connection->m_timeStamp34C;
		unsigned int limit = timeout;
		return limit >= now - last ? true : false;
	}

	unsigned int last = connection->m_timeStamp34C;
	unsigned int limit = TheWritableGlobalData->m_networkDisconnectTime * 4;
	return limit >= now - last ? true : false;
}
