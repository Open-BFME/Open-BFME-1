// Probe reconstruction for the BFME GameInfo same-team predicate at 0x0061EB40.
// The body calls the BFME getLocalSlotNum virtual at vtable +0x14 and walks the
// eight slot pointers directly.

typedef bool Bool;

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

class GameSlot
{
public:
	bool isOccupied() const
	{
		return m_state == SLOT_PLAYER || m_state == SLOT_EASY_AI ||
			m_state == SLOT_MED_AI || m_state == SLOT_BRUTAL_AI;
	}

	int getTeamNumber() const { return m_teamNumber; }

private:
	void *_vtable;
	int m_state;
	bool m_isAccepted;
	bool m_hasMap;
	bool m_isMuted;
	char m_pad0b;
	int m_color;
	int m_startPos;
	int m_playerTemplate;
	int m_teamNumber;
};

class GameInfo
{
public:
	virtual int _bfmeSlot0();
	virtual int _bfmeSlot1();
	virtual void reset();
	virtual void startGame(int gameID);
	virtual Bool amIHost() const;
	virtual int getLocalSlotNum() const;

	GameSlot *getSlot(int index) const
	{
		if (index >= 0 && index < 8)
			return m_slots[index];
		return 0;
	}

	Bool allPlayersSameTeam() const;

private:
	int m_preorderMask;
	int m_crcInterval;
	bool m_inGame;
	bool m_inProgress;
	bool m_surrendered;
	char m_pad0f;
	int m_gameID;
	GameSlot *m_slots[8];
};

// ?allPlayersSameTeam@GameInfo@@QBE_NXZ
Bool GameInfo::allPlayersSameTeam() const
{
	int localSlotNum = getLocalSlotNum();
	int localTeam = -1;

	if (localSlotNum < 0)
	{
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *slot = getSlot(i);
			if (slot->isOccupied())
			{
				localTeam = slot->getTeamNumber();
				break;
			}
		}
	}
	else
	{
		GameSlot *slot = getSlot(localSlotNum);
		localTeam = slot->getTeamNumber();
	}

	for (int i = 0; i < 8; ++i)
	{
		if (i == localSlotNum)
			continue;

		GameSlot *slot = getSlot(i);
		if (slot->isOccupied())
		{
			int team = slot->getTeamNumber();
			if (team < 0 || team != localTeam)
				return false;
		}
	}

	return true;
}
