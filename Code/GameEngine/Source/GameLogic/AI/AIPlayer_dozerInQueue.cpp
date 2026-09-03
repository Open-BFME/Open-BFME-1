// cl: /DNDEBUG /MD /EHsc
// readable body of ?dozerInQueue@AIPlayer@@IAE_NXZ: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::dozerInQueue — retail 0x00165780 (complete body 76B; dump row
// listed 69B and cut three bytes into xor al,al). TeamInQueue::includesADozer
// is inlined: WorkOrder+4 is the ThingTemplate, +0xC next, +0x19
// m_isResourceGatherer; KINDOF_DOZER is bit 14 (0x4000) at template+0xC8.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	unsigned char m_pad[0xC8];
	unsigned int m_kindOf;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	void *m_vptr;
	ThingTemplate *m_thing;
	int m_factoryID;
	WorkOrder *m_next;
	int m_numCompleted;
	int m_numRequired;
	unsigned char m_required;
	unsigned char m_isResourceGatherer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	TeamInQueue *next();

	unsigned char m_pad[0x14];
	WorkOrder *m_workOrders;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
protected:
	Bool dozerInQueue();

private:
	void *m_vptr;
	TeamInQueue *m_teamBuildQueue;
};

Bool AIPlayer::dozerInQueue()
{
	TeamInQueue *team = m_teamBuildQueue;
	unsigned int mask = 0x4000;
	if (team)
	{
		do
		{
			for (WorkOrder *order = team->m_workOrders; order; order = order->m_next)
			{
				if ((order->m_thing->m_kindOf & mask) && !order->m_isResourceGatherer)
					return true;
			}
			team = team->next();
		} while (team);
	}
	return false;
}
