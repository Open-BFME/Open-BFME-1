// Open-BFME5 conversion for the fixed-capacity slot allocator at 0x007F9A80.

struct BfmeSlotRecord
{
	void assignId(int newId)
	{
		value1 = 0;
		id = newId;
	}

	int id;
	volatile int value1;
	int value2;
	int value3;
	int value4;
	int value5;
	int value6;
};

class BfmeSlotPool
{
public:
	BfmeSlotRecord *acquireSlot(void);

private:
	char m_pad0[0x0c];
	int m_nextId;
	char m_pad10[0x18];
	BfmeSlotRecord m_slots[32];
};

BfmeSlotRecord *BfmeSlotPool::acquireSlot(void)
{
	for (int index = 0; index < 32; ++index)
	{
		BfmeSlotRecord *slot = &m_slots[index];
		if (slot->id == 0)
		{
			slot->value1 = 0;
			slot->id = 0;
			slot->value2 = 0;
			slot->value3 = 0;
			slot->value4 = 0;
			slot->value5 = 0;
			slot->value6 = 0;
			slot->assignId(++m_nextId);
			return slot;
		}
	}
	return 0;
}
