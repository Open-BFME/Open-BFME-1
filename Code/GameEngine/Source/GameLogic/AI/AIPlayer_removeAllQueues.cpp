// cl: /DNDEBUG /MD /EHsc

// AIPlayer::removeAll_TeamBuildQueue and removeAll_TeamReadyQueue, retail
// 0x001607C0 and 0x00160990. The same DLINK macro expanded twice, with the two
// list heads at AIPlayer+0x04 and +0x08. A team in the queues carries TWO link
// pairs, one per list, at node+0x04/+0x08 and node+0x0C/+0x10 - which is what
// the second body's displacements say, and the reason it is not just the first
// with a different head.
//
// Both bodies inline the whole of dlink_removeFrom: unlink from the next, unlink
// from the previous, and ONLY when there is no previous move the list head on to
// the next. That else arm is the jump over the head store, and it is why the
// two functions differ by exactly one displacement.
//
// Zero Hour's removeAll goes through removeFrom, which first asks isInList.
// Retail asks nothing - the node it is unlinking is the head, so the question
// has one answer - and the DLINK node keeps its links at +0x04 and +0x08.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	void dlink_removeFrom_TeamBuildQueue( TeamInQueue **pListHead )
	{
		if( m_dlink_next_build )
			m_dlink_next_build->m_dlink_prev_build = m_dlink_prev_build;

		if( m_dlink_prev_build )
			m_dlink_prev_build->m_dlink_next_build = m_dlink_next_build;
		else
			*pListHead = m_dlink_next_build;

		m_dlink_prev_build = 0;
		m_dlink_next_build = 0;
	}

	void dlink_removeFrom_TeamReadyQueue( TeamInQueue **pListHead )
	{
		if( m_dlink_next_ready )
			m_dlink_next_ready->m_dlink_prev_ready = m_dlink_prev_ready;

		if( m_dlink_prev_ready )
			m_dlink_prev_ready->m_dlink_next_ready = m_dlink_next_ready;
		else
			*pListHead = m_dlink_next_ready;

		m_dlink_prev_ready = 0;
		m_dlink_next_ready = 0;
	}

private:
	unsigned int m_unmodelled_00;
	TeamInQueue *m_dlink_prev_build;			// +0x04
	TeamInQueue *m_dlink_next_build;			// +0x08
	TeamInQueue *m_dlink_prev_ready;			// +0x0C
	TeamInQueue *m_dlink_next_ready;			// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
protected:
	typedef void (*RemoveAllProc)( TeamInQueue *o );

	void removeAll_TeamBuildQueue( RemoveAllProc p );
	void removeAll_TeamReadyQueue( RemoveAllProc p );

private:
	unsigned int m_unmodelled_00;				// +0x00
	TeamInQueue *m_buildQueueHead;				// +0x04
	TeamInQueue *m_readyQueueHead;				// +0x08
};

// ?removeAll_TeamBuildQueue@AIPlayer@@IAEXP6AXPAVTeamInQueue@@@Z@Z
void AIPlayer::removeAll_TeamBuildQueue( RemoveAllProc p )
{
	while( m_buildQueueHead )
	{
		TeamInQueue *tmp = m_buildQueueHead;

		tmp->dlink_removeFrom_TeamBuildQueue( &m_buildQueueHead );

		if( p )
			(*p)( tmp );
	}
}

// ?removeAll_TeamReadyQueue@AIPlayer@@IAEXP6AXPAVTeamInQueue@@@Z@Z
void AIPlayer::removeAll_TeamReadyQueue( RemoveAllProc p )
{
	while( m_readyQueueHead )
	{
		TeamInQueue *tmp = m_readyQueueHead;

		tmp->dlink_removeFrom_TeamReadyQueue( &m_readyQueueHead );

		if( p )
			(*p)( tmp );
	}
}
