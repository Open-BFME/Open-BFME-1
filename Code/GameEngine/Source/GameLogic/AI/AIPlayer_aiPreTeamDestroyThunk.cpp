// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// AIPlayer::aiPreTeamDestroy at retail RVA 0x00161430 (223B). Ported from
// Zero Hour's AIPlayer.cpp: two DLINK<TeamInQueue> lists (TeamBuildQueue at
// AIPlayer+4, TeamReadyQueue at AIPlayer+8, matching the destructor's
// removeAll_TeamBuildQueue/removeAll_TeamReadyQueue at 0x001613C0) each
// scanned for a node whose m_team (TeamInQueue+0x1c, per the landed
// TeamInQueue::disband at 0x00161A60) equals the team being destroyed;
// matched nodes are unlinked and deleted.

typedef bool Bool;
class Team;
class TeamInQueue;

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = (m_cur->*m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class TeamInQueue
{
public:
	virtual ~TeamInQueue();

	TeamInQueue *dlink_prev_TeamBuildQueue() const { return m_dlink_TeamBuildQueue_prev; }
	TeamInQueue *dlink_next_TeamBuildQueue() const { return m_dlink_TeamBuildQueue_next; }
	Bool dlink_isInList_TeamBuildQueue(TeamInQueue *const *pListHead) const
	{
		return *pListHead == this || m_dlink_TeamBuildQueue_prev || m_dlink_TeamBuildQueue_next;
	}
	void dlink_removeFrom_TeamBuildQueue(TeamInQueue **pListHead)
	{
		if (m_dlink_TeamBuildQueue_next)
			m_dlink_TeamBuildQueue_next->m_dlink_TeamBuildQueue_prev = m_dlink_TeamBuildQueue_prev;
		if (m_dlink_TeamBuildQueue_prev)
			m_dlink_TeamBuildQueue_prev->m_dlink_TeamBuildQueue_next = m_dlink_TeamBuildQueue_next;
		else
			*pListHead = m_dlink_TeamBuildQueue_next;
		m_dlink_TeamBuildQueue_prev = 0;
		m_dlink_TeamBuildQueue_next = 0;
	}

	TeamInQueue *dlink_prev_TeamReadyQueue() const { return m_dlink_TeamReadyQueue_prev; }
	TeamInQueue *dlink_next_TeamReadyQueue() const { return m_dlink_TeamReadyQueue_next; }
	Bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *pListHead) const
	{
		return *pListHead == this || m_dlink_TeamReadyQueue_prev || m_dlink_TeamReadyQueue_next;
	}
	void dlink_removeFrom_TeamReadyQueue(TeamInQueue **pListHead)
	{
		if (m_dlink_TeamReadyQueue_next)
			m_dlink_TeamReadyQueue_next->m_dlink_TeamReadyQueue_prev = m_dlink_TeamReadyQueue_prev;
		if (m_dlink_TeamReadyQueue_prev)
			m_dlink_TeamReadyQueue_prev->m_dlink_TeamReadyQueue_next = m_dlink_TeamReadyQueue_next;
		else
			*pListHead = m_dlink_TeamReadyQueue_next;
		m_dlink_TeamReadyQueue_prev = 0;
		m_dlink_TeamReadyQueue_next = 0;
	}

	TeamInQueue *m_dlink_TeamBuildQueue_prev;
	TeamInQueue *m_dlink_TeamBuildQueue_next;
	TeamInQueue *m_dlink_TeamReadyQueue_prev;
	TeamInQueue *m_dlink_TeamReadyQueue_next;
	char m_pad_14[8];
	Team *m_team;
};

class PlayerController
{
protected:
	virtual ~PlayerController() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer : public PlayerController
{
public:
	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_dlinkhead_TeamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}
	void removeFrom_TeamBuildQueue(TeamInQueue *o)
	{
		if (o->dlink_isInList_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue))
			o->dlink_removeFrom_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue);
	}

	DLINK_ITERATOR<TeamInQueue> iterate_TeamReadyQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_dlinkhead_TeamReadyQueue, &TeamInQueue::dlink_next_TeamReadyQueue);
	}
	void removeFrom_TeamReadyQueue(TeamInQueue *o)
	{
		if (o->dlink_isInList_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue))
			o->dlink_removeFrom_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue);
	}

	void aiPreTeamDestroy(const Team *deletedTeam);

private:
	TeamInQueue *m_dlinkhead_TeamBuildQueue;
	TeamInQueue *m_dlinkhead_TeamReadyQueue;
};

void AIPlayer::aiPreTeamDestroy(const Team *deletedTeam)
{
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team == deletedTeam)
			{
				removeFrom_TeamBuildQueue(team);
				delete team;
				iter = iterate_TeamBuildQueue();
			}
		}
	}
	{
		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamReadyQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team->m_team == deletedTeam)
			{
				removeFrom_TeamReadyQueue(team);
				delete team;
				iter = iterate_TeamReadyQueue();
			}
		}
	}
}
