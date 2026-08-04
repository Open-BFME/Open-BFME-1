// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the DisconnectManager::processDisconnectVote __emit thunk to clean C++.
//
// Verbatim Zero Hour DisconnectManager.cpp: translate the sender's slot, drop
// the vote if that player is no longer in the game, otherwise apply it. The
// DEBUG_LOG compiles away.
//
// Retail pins getPlayerID to the field read at msg+0x0C, and getSlot returns a
// byte (the movzx before the push). translatedSlotPosition inlines differently
// here than in resetPlayersVotes -- `or esi,-1` plus a jump rather than a branch
// straight to the epilogue -- because the result is passed on instead of being
// tested for an early return.
//
// The applyDisconnectVote it calls is the sibling converted alongside this.

typedef int Int;
typedef unsigned int UnsignedInt;

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID(void);						///< ILT thunk at 0x0004A291
};

class NetCommandMsg
{
public:
	UnsignedInt getVoteFrame(void);							///< ILT thunk at 0x00013F20
	unsigned char getSlot(void);							///< ILT thunk at 0x000058B7

	Int getPlayerID(void) const { return m_playerID; }

private:
	unsigned char m_unreconstructed_00[0x0C];
	Int m_playerID;											///< retail this+0x0C
};

class DisconnectManager
{
protected:
	void processDisconnectVote(NetCommandMsg *, ConnectionManager *);

	bool isPlayerInGame(Int slot, ConnectionManager *conMgr);				///< ILT thunk at 0x0003A648
	void applyDisconnectVote(Int, UnsignedInt, Int, ConnectionManager *);	///< ILT thunk at 0x000215AD

	Int translatedSlotPosition(Int slot, Int localSlot) const
	{
		if (slot < localSlot)
			return slot;
		if (slot == localSlot)
			return -1;
		return slot - 1;
	}
};

// ?processDisconnectVote@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z
void DisconnectManager::processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr)
{
	NetCommandMsg *cmdMsg = msg;
	Int transSlot = translatedSlotPosition(msg->getPlayerID(), conMgr->getLocalPlayerID());

	if (isPlayerInGame(transSlot, conMgr) == false)
	{
		// if they've been timed out, voted out, disconnected, don't count their vote.
		return;
	}

	applyDisconnectVote(cmdMsg->getSlot(), cmdMsg->getVoteFrame(), cmdMsg->getPlayerID(), conMgr);
}
