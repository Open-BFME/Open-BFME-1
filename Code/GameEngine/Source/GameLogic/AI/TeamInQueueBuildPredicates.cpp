// cl: /O2 /Ob0
// Retail BFME1 TeamInQueue work-order checks. Identity evidence:
// reverse/identity_evidence/0x00160f80-team-in-queue-build-predicates.md.
// The retail queue has a vptr at +0, four link pointers at +4..+0x10,
// and the work-order head at +0x14. The native Zero Hour member names
// are retained, while offsets below are witnessed by the retail methods.

struct WorkOrder
{
	char m_unreconstructed_00[8];
	unsigned int m_factoryID;     // +0x08
	WorkOrder *m_next;             // +0x0C
	int m_numCompleted;            // +0x10
	int m_numRequired;             // +0x14
	bool m_required;               // +0x18
};

class TeamInQueue
{
public:
	virtual ~TeamInQueue();
	bool isAllBuilt();
	bool isMinimumBuilt();
	bool areBuildsComplete();

private:
	char m_unreconstructed_04[0x10];
	WorkOrder *m_workOrders;       // +0x14
};

// ?isAllBuilt@TeamInQueue@@QAE_NXZ
bool TeamInQueue::isAllBuilt()
{
	bool stillBuilding = false;
	for (WorkOrder *order = m_workOrders; order; order = order->m_next)
	{
		if (order->m_numRequired > order->m_numCompleted)
			stillBuilding = true;
	}
	return !stillBuilding;
}

// ?isMinimumBuilt@TeamInQueue@@QAE_NXZ
bool TeamInQueue::isMinimumBuilt()
{
	for (WorkOrder *order = m_workOrders; order; order = order->m_next)
	{
		int count = order->m_numCompleted;
		if (order->m_factoryID != 0)
			++count;
		if (order->m_numRequired > count && order->m_required)
			return false;
	}
	return true;
}

// ?areBuildsComplete@TeamInQueue@@QAE_NXZ
bool TeamInQueue::areBuildsComplete()
{
	WorkOrder *order = m_workOrders;
	while (order)
	{
		if (order->m_factoryID != 0)
			return false;
		order = order->m_next;
	}
	return true;
}
