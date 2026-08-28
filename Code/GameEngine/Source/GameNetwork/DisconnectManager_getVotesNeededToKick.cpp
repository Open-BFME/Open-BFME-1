// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DisconnectManager::getVotesNeededToKick, retail 0x0066BBC0, 81
// bytes. The body carried only a machine byte-dump row; the symbols.csv pin
// names it, and all three predicates it calls are already ledgered names.
//
// It counts the slots that are not in the game, skipping the one being voted on
// and, when there is a connection manager, any slot that is not connected or
// not live. The last predicate is asked even when there is no connection
// manager -- the null test only guards the first two, and the third call is
// where both paths meet.
//
// The bound test inside the loop is redundant against the loop's own condition
// but it is in the bytes, and it is one unsigned compare. Spelled as
// i < 0 || i >= 8 this compiler emits both halves separately, four bytes more,
// so the cast is written out. The loop's own compare stays signed, which is
// what keeps the counter an Int.

typedef int Int;
typedef bool Bool;

enum { BFME_MAX_SLOTS = 8 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Bool isPlayerConnected(Int slot);			// ILT 0x0001514A
	Bool _bfme_slotIsLocalOrLive(Int slot);			// ILT 0x0001F136
};

class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerInGame(Int slot);				// retail 0x00662BE0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
protected:
	Int getVotesNeededToKick(Int slot, ConnectionManager *conn);
};

// ?getVotesNeededToKick@DisconnectManager@@IAEHHPAVConnectionManager@@@Z
Int DisconnectManager::getVotesNeededToKick(Int slot, ConnectionManager *conn)
{
	Int votes = 0;

	for (Int i = 0; i < BFME_MAX_SLOTS; ++i)
	{
		if (i == slot)
			continue;

		if ((unsigned int)i >= (unsigned int)BFME_MAX_SLOTS)
			continue;

		if (conn)
		{
			if (!conn->isPlayerConnected(i))
				continue;

			if (!conn->_bfme_slotIsLocalOrLive(i))
				continue;
		}

		if (!((BFMEConnectionManager *)conn)->isPlayerInGame(i))
			++votes;
	}

	return votes;
}
