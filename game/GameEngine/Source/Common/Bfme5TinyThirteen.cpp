// Four more tiny ones: a word in a table tested for zero, a masked byte test
// that answers as an int, another pair handed back and another value taken
// from a source or zeroed.

class BfmeSlotCD
{
public:
	char m_bfmeHead[6];					// +0x00
	short m_bfmeTag;					// +0x06
	char m_bfmeRest[8];					// +0x08
};

class Gen_000EE620
{
public:
	bool bfmeIsFree(int index) const;

private:
	int m_bfmeHead[3];					// +0x00
	BfmeSlotCD *m_bfmeSlots;				// +0x0C
};

// ?bfmeIsFree@Gen_000EE620@@QBE_NH@Z
bool Gen_000EE620::bfmeIsFree(int index) const
{
	BfmeSlotCD *slots = m_bfmeSlots;

	return slots[index].m_bfmeTag == 0;
}

class Gen_000FB880
{
public:
	int bfmeMatches(unsigned char mask) const;

private:
	char m_bfmeHead[0x343];					// +0x000
	unsigned char m_bfmeBits;				// +0x343
};

// ?bfmeMatches@Gen_000FB880@@QBEHE@Z
int Gen_000FB880::bfmeMatches(unsigned char mask) const
{
	return (m_bfmeBits & mask) != 0;
}

class Gen_0014FD90
{
public:
	void bfmeGetPair(int *out) const;

private:
	char m_bfmeHead[0x320];					// +0x000
	int m_bfmeFirst;					// +0x320
	int m_bfmeSecond;					// +0x324
};

class BfmeSourceCD
{
public:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeValue;					// +0x08
};

class Gen_0016A350
{
public:
	void bfmeTake(BfmeSourceCD *source);

private:
	int m_bfmeHead[18];					// +0x00
	int m_bfmeValue;					// +0x48
};

// ?bfmeTake@Gen_0016A350@@QAEXPAVBfmeSourceCD@@@Z
void Gen_0016A350::bfmeTake(BfmeSourceCD *source)
{
	int value;

	if (source)
		value = source->m_bfmeValue;
	else
		value = 0;

	m_bfmeValue = value;
}
