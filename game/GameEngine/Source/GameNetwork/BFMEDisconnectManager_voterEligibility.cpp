// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Bool isPlayerConnected(int slot);
};

class BFMEDisconnectManager
{
public:
	Bool hasPlayerConnectionTimedOut(int slot, void *connectionManager);
	Int countVoters(void *connectionManager);
};

// callees.py 0x66B6A0 / 0x66BB60: ILT 0x0001F136 -> 0x00662A50 and ILT
// 0x0004A87C -> 0x00662BE0, the ledger rows below
// (native_connection_timing.cpp).  The caller tests only the low byte of
// the int predicate.
class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerConnectedDefaultTimeout(int slot);		// retail 0x00662A50
	Int isPlayerInGame(Int slot);				// retail 0x00662BE0
};

Bool BFMEDisconnectManager::hasPlayerConnectionTimedOut(int slot, void *connectionManager)
{
	BFMEConnectionManager *manager = (BFMEConnectionManager *)connectionManager;
	if ((unsigned int)slot < 8) {
		if (manager == 0)
			return false;
		if (manager->isPlayerConnected(slot) && manager->isPlayerConnectedDefaultTimeout(slot))
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
		if (manager && !manager->isPlayerConnectedDefaultTimeout(slot))
			continue;
		if (!(unsigned char)manager->isPlayerInGame(slot))
			++voters;
	}
	return voters;
}
