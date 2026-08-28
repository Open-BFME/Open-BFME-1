// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
enum { MAX_SLOTS = 8 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Bool isPlayerConnected(int slot);
	Bool _bfme_slotIsLocalOrLive(int slot);
	Bool _bfme_slotStateInRange(int slot);
};

struct PlayerVote
{
	Bool vote;
	unsigned int frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
protected:
	int countVotesForPlayer(int slot, ConnectionManager *connectionManager);

private:
	unsigned char m_unmodelled_00[0x30];
	PlayerVote m_playerVotes[MAX_SLOTS][MAX_SLOTS];
};

int DisconnectManager::countVotesForPlayer(int slot, ConnectionManager *connectionManager)
{
	if (slot < 0 || slot >= MAX_SLOTS)
		return 0;

	int votes = 0;
	for (int voter = 0; voter < MAX_SLOTS; ++voter) {
		if (m_playerVotes[slot][voter].vote == 1 && (unsigned int)voter < MAX_SLOTS) {
			if (connectionManager != 0) {
				if (!connectionManager->isPlayerConnected(voter))
					continue;
				if (!connectionManager->_bfme_slotIsLocalOrLive(voter))
					continue;
			}
			if (!connectionManager->_bfme_slotStateInRange(voter))
				++votes;
		}
	}
	return votes;
}
