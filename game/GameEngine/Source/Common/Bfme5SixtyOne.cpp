// Two more: a four-slot setter with an argument to spare and a search over
// sixty-four byte elements.

class BfmePairEH
{
public:
	int m_bfmeValue;					// +0x00
	int m_bfmeSpare;					// +0x04
};

class Gen_0072EA60
{
public:
	void bfmeSet(int first, int second, int third, int fourth, int unused);

private:
	char m_bfmeHead[0x98];					// +0x98
	BfmePairEH m_bfmeSlots[4];				// +0x98
};

// ?bfmeSet@Gen_0072EA60@@QAEXHHHHH@Z
void Gen_0072EA60::bfmeSet(int first, int second, int third, int fourth, int unused)
{
	m_bfmeSlots[0].m_bfmeValue = first;
	m_bfmeSlots[1].m_bfmeValue = second;
	m_bfmeSlots[2].m_bfmeValue = third;
	m_bfmeSlots[3].m_bfmeValue = fourth;
}

class BfmeSlotEH
{
public:
	int m_bfmeHead[2];					// +0x00
	void *m_bfmeKey;					// +0x08
	int m_bfmeTail[13];					// +0x0C
};

class Gen_007F7180
{
public:
	BfmeSlotEH *bfmeFind(void *key) const;

private:
	int m_bfmeHead[18];					// +0x00
	BfmeSlotEH *m_bfmeSlots;				// +0x48
	int m_bfmeCount;					// +0x4C
};

// ?bfmeFind@Gen_007F7180@@QBEPAVBfmeSlotEH@@PAX@Z
BfmeSlotEH *Gen_007F7180::bfmeFind(void *key) const
{
	BfmeSlotEH *first = m_bfmeSlots;
	BfmeSlotEH *last = m_bfmeSlots + m_bfmeCount;

	while (first < last)
	{
		if (first->m_bfmeKey == key)
			return first;

		++first;
	}

	return 0;
}
