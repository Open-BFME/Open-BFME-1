// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?applyDisconnectVote@DisconnectManager@@IAEXHIHPAVConnectionManager@@@Z: Code/GameEngine/Source/GameNetwork/DisconnectManager.cpp
// Lift the DisconnectManager::applyDisconnectVote __emit thunk to clean C++.
//
// Zero Hour's DisconnectManager.cpp carries the body; the DEBUG_LOG compiles
// away, leaving the vote record and the menu update. Shares its whole tail with
// resetPlayersVotes, so the same layout applies: m_playerVotes is [8][8] of
// 8-byte entries at this+0x30 with a byte vote at +0x00 and a frame at +0x04,
// and the `lea eax,[eax+esi*8]` then `[ecx+eax*8+0x30]` pair is just the
// [slot][fromSlot] index folded into one address.
//
// Same two BFME differences as the sibling: countVotesForPlayer takes the
// ConnectionManager as a second argument, and the menu pointer is null-checked.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

enum { MAX_SLOTS = 8 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID(void);						///< ILT thunk at 0x0004A291
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
protected:
	void applyDisconnectVote(Int, UnsignedInt, Int, ConnectionManager *);

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

// ?applyDisconnectVote@DisconnectManager@@IAEXHIHPAVConnectionManager@@@Z
void DisconnectManager::applyDisconnectVote(Int slot, UnsignedInt frame, Int fromSlot,
											ConnectionManager *conMgr)
{
	m_playerVotes[slot][fromSlot].vote = 1;
	m_playerVotes[slot][fromSlot].frame = frame;

	Int numVotes = countVotesForPlayer(slot, conMgr);
	Int transSlot = translatedSlotPosition(slot, conMgr->getLocalPlayerID());
	if (transSlot != -1 && TheDisconnectMenu)
	{
		TheDisconnectMenu->updateVotes(transSlot, numVotes);
	}
}
