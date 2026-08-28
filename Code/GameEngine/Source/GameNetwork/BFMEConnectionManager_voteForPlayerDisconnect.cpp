// cl: /DNDEBUG /MD /EHsc

// BFME keeps the DisconnectManager pointer in its expanded connection manager
// at +0x120E0.  This forwarding member is the BFME-side hop used by Network's
// voteForPlayerDisconnect virtual call.

typedef int Int;

class ConnectionManager;

class DisconnectManager
{
public:
	void voteForPlayerDisconnect(Int slot, ConnectionManager *connectionManager);
};

class BFMEConnectionManager
{
public:
	void voteForPlayerDisconnect(Int slot);

private:
	char m_retailPrefix[0x120E0];
	DisconnectManager *m_disconnectManager;
};

// ?voteForPlayerDisconnect@BFMEConnectionManager@@QAEXH@Z
void BFMEConnectionManager::voteForPlayerDisconnect(Int slot)
{
	if (m_disconnectManager != 0)
		m_disconnectManager->voteForPlayerDisconnect(
			slot, reinterpret_cast<ConnectionManager *>(this));
}
