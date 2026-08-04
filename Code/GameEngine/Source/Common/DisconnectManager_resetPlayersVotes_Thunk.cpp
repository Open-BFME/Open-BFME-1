// cl: /DNDEBUG /MD /EHs-c-
// Lift the DisconnectManager::resetPlayersVotes __emit thunk to clean C++.
//
// Zero Hour's DisconnectManager.cpp carries the body; its DEBUG_LOG calls
// compile away, leaving the vote sweep and the menu update. Retail pins the
// layout: m_playerVotes is [8][8] of 8-byte entries at this+0x30, indexed
// [i][playerID], which is the `this + playerID*8 + 0x30` base with the 0x40 row
// stride the loop walks. Each entry is a byte vote at +0x00 and a frame at
// +0x04.
//
// Two BFME differences from ZH, both forced by the bytes. countVotesForPlayer
// takes the ConnectionManager as a second argument here (retail pushes both
// before the call), and the menu pointer is null-checked before use.
// translatedSlotPosition is inlined, which is the cmp/jl/je/dec sequence.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

enum { MAX_SLOTS = 8 };

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID(void);						///< ILT thunk at 0x0004A291
};

class DisconnectMenu
{
public:
	void updateVotes(Int slot, Int numVotes);				///< ILT thunk at 0x00031DB8
};

extern DisconnectMenu *TheDisconnectMenu;					///< retail [0x012F4964]

struct PlayerVote
{
	Bool vote;												///< retail this+0x00
	UnsignedInt frame;										///< retail this+0x04
};

class DisconnectManager
{
protected:
	void resetPlayersVotes(Int, UnsignedInt, ConnectionManager *);

	Int countVotesForPlayer(Int playerID, ConnectionManager *conMgr);	///< ILT thunk at 0x00003751

	Int translatedSlotPosition(Int slot, Int localSlot) const
	{
		if (slot < localSlot)
			return slot;
		if (slot == localSlot)
			return -1;
		return slot - 1;
	}

private:
	unsigned char m_unreconstructed_00[0x30];
	PlayerVote m_playerVotes[MAX_SLOTS][MAX_SLOTS];			///< retail this+0x30
};

// ?resetPlayersVotes@DisconnectManager@@IAEXHIPAVConnectionManager@@@Z
void DisconnectManager::resetPlayersVotes(Int playerID, UnsignedInt frame, ConnectionManager *conMgr)
{
	// we need to reset this player's votes that happened before or on the given frame.
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_playerVotes[i][playerID].frame <= frame)
		{
			m_playerVotes[i][playerID].vote = 0;
		}
	}

	Int numVotes = countVotesForPlayer(playerID, conMgr);
	Int transSlot = translatedSlotPosition(playerID, conMgr->getLocalPlayerID());
	if (transSlot != -1 && TheDisconnectMenu)
	{
		TheDisconnectMenu->updateVotes(transSlot, numVotes);
	}
}
