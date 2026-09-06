// cl: /DNDEBUG /MD /EHsc
//
// readable body of ?areAllQueuesEmpty@ConnectionManager@@: ZH ConnectionManager.cpp
// Open-BFME: ConnectionManager::areAllQueuesEmpty, retail 0x00662DF0. This is
// the near-miss twin of the landed GameResultsQueue::areThreadsRunning
// (0x0063FD10, GameResultsThread.cpp): same loop-and-early-return shape, but
// over 8 connection slots at ConnectionManager+0x04 (per reverse/symbols.csv:
// "conMgr 0x00662DF0 = ZH ConnectionManager::canILeave... loops the 8
// connections at conMgr+0x04 calling isQueueEmpty@Connection"), calling a
// direct (non-virtual) Connection::isQueueEmpty(). Independent TU: does not
// touch the landed native_connection_timing.cpp ConnectionManager class.

typedef bool Bool;
typedef int Int;
#define TRUE 1
#define FALSE 0

class Connection
{
public:
	Bool isQueueEmpty();
};

class ConnectionManager
{
public:
	Bool areAllQueuesEmpty( void );

private:
	char m_unknown00[4];
	Connection *m_connections[8];
};

// ?areAllQueuesEmpty@ConnectionManager@@QAE_NXZ
Bool ConnectionManager::areAllQueuesEmpty( void )
{
	for ( Int i = 0; i < 8; ++i )
	{
		if ( m_connections[i] != 0 )
		{
			if ( m_connections[i]->isQueueEmpty() == FALSE )
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}
