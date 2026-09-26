// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec( dllimport ) unsigned int __stdcall timeGetTime();

class GameSlot
{
public:
	unsigned char getNATBehavior() const
	{
		return *(const unsigned char *)((const char *)this + 0x38);
	}
};

struct NATConnectionNode
{
	int m_slotIndex;
	int m_behavior;
};

enum NATConnectionState
{
	NATCONNECTIONSTATE_NOSTATE = 0,
	NATCONNECTIONSTATE_WAITINGFORRESPONSE = 4,
	NATCONNECTIONSTATE_DONE = 5
};

class NAT
{
protected:
	void doThisConnectionRound();
	void setConnectionState( int nodeNumber, NATConnectionState state );
	void sendMangledSourcePort();

private:
	void *m_vtable;
	void *m_transport;
	GameSlot **m_slotList;
	int m_NATState;
	int m_localNodeNumber;
	int m_targetNodeNumber;
	unsigned int m_localIP;
	unsigned int m_numNodes;
	int m_connectionRound;
	int m_numRetries;
	int m_maxNumRetriesAllowed;
	unsigned short m_packetID;
	unsigned short m_spareSocketPort;
	int m_manglerRetryTime;
	int m_manglerRetries;
	unsigned short m_previousSourcePort;
	unsigned char m_beenProbed;
	unsigned char m_padding3b[ 5 ];
	int m_timeTillNextSend;
	int m_connectionStates[ 9 ];
	NATConnectionNode m_connectionNodes[ 9 ];
	int m_connectionPairIndex;
	unsigned short m_startingPortNumber;
	unsigned short m_paddingb6;
	int m_nextPortSendTime;
	int m_timeoutTime;
	int m_roundTimeout;
	unsigned char m_applyMangledPort;

	static int m_connectionPairs[ 7 ][ 7 ][ 8 ];
	static int m_timeBetweenRetries;
	static int m_timeToWaitForPort;
};

void NAT::doThisConnectionRound()
{
	m_targetNodeNumber = -1;

	for( int i = 0; i < 8; ++i )
	{
		setConnectionState( i, NATCONNECTIONSTATE_NOSTATE );
	}

	m_applyMangledPort = 1;
	m_beenProbed = 0;
	m_numRetries = 0;

	for( int i = 0; i < m_numNodes; ++i )
	{
		int targetNodeNumber = m_connectionPairs[ m_connectionPairIndex ][ m_connectionRound ][ i ];
		if( targetNodeNumber != -1 )
		{
			if( i == m_localNodeNumber )
			{
				m_targetNodeNumber = targetNodeNumber;
				unsigned int targetSlotIndex = m_connectionNodes[
					m_connectionPairs[ m_connectionPairIndex ][ m_connectionRound ][ i ] ].m_slotIndex;
				GameSlot *targetSlot = m_slotList[ targetSlotIndex ];
				GameSlot *localSlot = m_slotList[ m_connectionNodes[ m_localNodeNumber ].m_slotIndex ];

				if( ( targetSlot->getNATBehavior() & 8 ) == 0 &&
					( localSlot->getNATBehavior() & 8 ) != 0 )
				{
					m_timeTillNextSend = -1;
				}

				sendMangledSourcePort();
				m_nextPortSendTime = timeGetTime() + m_timeBetweenRetries;
				m_timeoutTime = timeGetTime() + m_timeToWaitForPort;
			}
			else
			{
				setConnectionState( i, NATCONNECTIONSTATE_WAITINGFORRESPONSE );
			}
		}
		else
		{
			setConnectionState( i, NATCONNECTIONSTATE_DONE );
		}
	}
}
