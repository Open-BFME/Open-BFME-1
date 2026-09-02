// ?countVoters@BFMEDisconnectManager@@QAEHPAX@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;

class ConnectionManager
{
public:
	Bool isPlayerConnected(int slot);
	Bool _bfme_slotIsLocalOrLive(int slot);
};

class BFMEConnectionManager
{
public:
	Bool isPlayerInGame(int slot);
};

class BFMEDisconnectManager
{
public:
	int countVoters(void *connectionManager);
};

int BFMEDisconnectManager::countVoters(void *connectionManager)
{
	int slot = 0;
	ConnectionManager *manager = (ConnectionManager *)connectionManager;
	BFMEConnectionManager *bfmeManager = (BFMEConnectionManager *)connectionManager;
	int count = 0;
	for (; slot < 8; ++slot) {
		if (manager != 0) {
			if (!manager->isPlayerConnected(slot))
				continue;
			if (!manager->_bfme_slotIsLocalOrLive(slot))
				continue;
		}
		if (!bfmeManager->isPlayerInGame(slot))
			++count;
	}
	return count;
}
