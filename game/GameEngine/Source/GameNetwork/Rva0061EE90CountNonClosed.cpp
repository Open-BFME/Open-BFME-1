// cl: /O2 /MD

// The caller at 0x00516850 compares GameInfo::getNumPlayers with this body
// through ILT 0x00032D58. The retail body reads the eight GameInfo slot
// pointers at +0x14 and counts SLOT_OPEN, SLOT_PLAYER, and the three AI states.
// The caller proves that behavior, but it does not prove a source-level method
// name, so the class keeps the retail address in its name.

typedef int Int;

enum Rva0061EE90SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

struct Rva0061EE90Slot
{
	Rva0061EE90SlotState getState() const
	{
		return (Rva0061EE90SlotState)m_state;
	}

	void *m_vptr;
	Int m_state;
};

class Rva0061EE90GameInfo
{
public:
	virtual void reset();

	Rva0061EE90Slot *getSlot(Int slotNum) const
	{
		if (slotNum < 0 || slotNum >= 8)
			return 0;
		return m_slot[slotNum];
	}

	Int countNonClosed() const;

private:
	Int m_preorderMask;
	Int m_crcInterval;
	bool m_inGame;
	bool m_inProgress;
	bool m_surrendered;
	unsigned char m_padding;
	Int m_gameID;
	Rva0061EE90Slot *m_slot[8];
};

Int Rva0061EE90GameInfo::countNonClosed() const
{
	Int count = 0;
	for (Int i = 0; i < 8; ++i)
	{
		Rva0061EE90SlotState state = getSlot(i)->getState();
		if (state == SLOT_OPEN || state == SLOT_PLAYER || state == SLOT_EASY_AI ||
			state == SLOT_MED_AI || state == SLOT_BRUTAL_AI)
			++count;
	}
	return count;
}
