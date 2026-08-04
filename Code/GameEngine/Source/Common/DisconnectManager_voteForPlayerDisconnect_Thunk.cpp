// cl: /DNDEBUG /MD /EHs-c-
// Lift the DisconnectManager::voteForPlayerDisconnect __emit thunk to clean C++.
//
// Zero Hour's DisconnectManager.cpp body, with one BFME difference the bytes
// make plain: ZH runs the slot through untranslatedSlotPosition first, retail
// does not. The `lea ebp,[ebx*8]` hoisted before the first call is just the row
// index of m_playerVotes[slot][localID], reused for both the test and the set,
// which only works because the raw slot is the row.
//
// Same layout as the rest of the family: m_playerVotes is [8][8] of 8-byte
// entries at this+0x30. TheGameLogic->getFrame() inlines to the frame word at
// +0x3C of the global at 0x012F0898.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

enum { MAX_SLOTS = 8 };

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID(void);						///< ILT thunk at 0x0004A291
};

class GameLogic
{
public:
	unsigned char m_unreconstructed_00[0x3C];
	UnsignedInt m_frame;									///< retail this+0x3C

	UnsignedInt getFrame(void) const { return m_frame; }
};

extern GameLogic *TheGameLogic;								///< retail [0x012F0898]

struct PlayerVote
{
	Bool vote;												///< retail this+0x00
	UnsignedInt frame;										///< retail this+0x04
};

class DisconnectManager
{
public:
	void voteForPlayerDisconnect(Int, ConnectionManager *);

protected:
	void sendVoteCommand(Int slot, ConnectionManager *conMgr);				///< ILT thunk at 0x0002EE79
	void applyDisconnectVote(Int, UnsignedInt, Int, ConnectionManager *);	///< ILT thunk at 0x000215AD

private:
	unsigned char m_unreconstructed_00[0x30];
	PlayerVote m_playerVotes[MAX_SLOTS][MAX_SLOTS];			///< retail this+0x30
};

// ?voteForPlayerDisconnect@DisconnectManager@@QAEXHPAVConnectionManager@@@Z
void DisconnectManager::voteForPlayerDisconnect(Int slot, ConnectionManager *conMgr)
{
	if (m_playerVotes[slot][conMgr->getLocalPlayerID()].vote == 0)
	{
		m_playerVotes[slot][conMgr->getLocalPlayerID()].vote = 1;

		sendVoteCommand(slot, conMgr);

		// we use the game logic frame cause we might not have sent out our own disconnect frame yet.
		applyDisconnectVote(slot, TheGameLogic->getFrame(), conMgr->getLocalPlayerID(), conMgr);
	}
}
