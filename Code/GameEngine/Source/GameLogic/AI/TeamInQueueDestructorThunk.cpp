// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift TeamInQueue dtor MASM dump to clean C++.
// Retail @0x00160ED0: protected virtual SEH dtor walking the m_workOrders
// linked list (+0x14) and deleting each node (m_next at +0x0C) via its
// scalar deleting destructor, then inlining m_team->setActive() (flag bytes
// at +0x31/+0x32) and nulling the list head. Unlike ZH, BFME's TeamInQueue
// has a single base (no Snapshot subobject) and uses plain delete.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	virtual ~WorkOrder();
	int m_04;
	int m_08;
	WorkOrder *m_next;	// +0x0c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
	unsigned char m_pad[0x31];
public:
	unsigned char m_b31;	// +0x31
	unsigned char m_b32;	// +0x32
	void setActive() { if (!m_b31) { m_b32 = 1; m_b31 = 1; } }
};

class TeamInQueueBase
{
public:
	virtual ~TeamInQueueBase() {}
	void *m_dlink1a;	// +0x04
	void *m_dlink1b;	// +0x08
	void *m_dlink2a;	// +0x0c
	void *m_dlink2b;	// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue : public TeamInQueueBase
{
protected:
	virtual ~TeamInQueue();

public:
	WorkOrder *m_workOrders;	// +0x14
	unsigned char m_priorityBuild;	// +0x18
	Team *m_team;	// +0x1c
};

// ??1TeamInQueue@@MAE@XZ
TeamInQueue::~TeamInQueue()
{
	WorkOrder *order, *next;

	for (order = m_workOrders; order; order = next)
	{
		next = order->m_next;
		delete order;
	}
	// If we have a team, activate it.  If it is empty, Team.cpp will remove empty active teams.
	if (m_team) m_team->setActive();
	m_workOrders = 0;
}
