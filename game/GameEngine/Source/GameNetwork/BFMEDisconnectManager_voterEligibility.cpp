// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Bool isPlayerConnected(int slot);
	Bool _bfme_slotIsLocalOrLive(int slot);
};

class BFMEDisconnectManager
{
public:
	Bool hasPlayerConnectionTimedOut(int slot, void *connectionManager);
	Int countVoters(void *connectionManager);
};

class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerInGame(Int slot);
};

Bool BFMEDisconnectManager::hasPlayerConnectionTimedOut(int slot, void *connectionManager)
{
	ConnectionManager *manager = (ConnectionManager *)connectionManager;
	if ((unsigned int)slot < 8) {
		if (manager == 0)
			return false;
		if (manager->isPlayerConnected(slot) && manager->_bfme_slotIsLocalOrLive(slot))
			return false;
	}
	return true;
}

// Retail 0x0066BB60, BFMEDisconnectManager::countVoters(void *connectionManager).
//
// Same predicate triple as DisconnectManager::getVotesNeededToKick (0x0066BBC0),
// without skipping the slot under vote. The last predicate is called even when
// the connection-manager pointer is null, matching the retail join point.
Int BFMEDisconnectManager::countVoters(void *connectionManager)
{
	BFMEConnectionManager *manager = (BFMEConnectionManager *)connectionManager;
	Int voters = 0;
	for (Int slot = 0; slot < 8; ++slot)
	{
		if ((unsigned int)slot >= 8)
			continue;
		if (manager && !manager->isPlayerConnected(slot))
			continue;
		if (manager && !manager->_bfme_slotIsLocalOrLive(slot))
			continue;
		if (!manager->isPlayerInGame(slot))
			++voters;
	}
	return voters;
}
