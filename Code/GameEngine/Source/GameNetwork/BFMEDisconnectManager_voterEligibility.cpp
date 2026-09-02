// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;

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
