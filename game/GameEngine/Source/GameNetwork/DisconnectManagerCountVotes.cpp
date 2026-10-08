// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
enum { MAX_SLOTS = 8 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Bool isPlayerConnected(int slot);
};

// callees.py 0x66B720: ILT 0x0001F136 -> 0x00662A50 and ILT 0x000486B2 ->
// 0x00662C30, the ledger rows below (native_connection_timing.cpp).  The
// caller tests only the low byte of the int predicate.
class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerConnectedDefaultTimeout(int slot);		// retail 0x00662A50
	int isPlayerSlotActive(int slot);			// retail 0x00662C30
};

struct PlayerVote
{
	Bool vote;
	unsigned int frame;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
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
				if (!((BFMEConnectionManager *)connectionManager)->isPlayerConnectedDefaultTimeout(voter))
					continue;
			}
			if (!(unsigned char)((BFMEConnectionManager *)connectionManager)->isPlayerSlotActive(voter))
				++votes;
		}
	}
	return votes;
}
