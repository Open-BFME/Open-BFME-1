// Five more tiny ones: a bit mask that is complemented unless a flag is set,
// two scans that answer one on the first non-empty slot, a count divided by
// thirty-six and a value stored with a deadline.

class BfmeShiftCE
{
public:
	char m_bfmeHead[0x24];					// +0x00
	unsigned int m_bfmeShift;				// +0x24
};

class Gen_001DD040
{
public:
	unsigned int bfmeMask(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeShiftCE *m_bfmeThing;				// +0x08
	unsigned char m_bfmeKeep;				// +0x0C
};

// ?bfmeMask@Gen_001DD040@@QBEIXZ
unsigned int Gen_001DD040::bfmeMask(void) const
{
	unsigned int mask = 1 << m_bfmeThing->m_bfmeShift;

	if (!m_bfmeKeep)
		mask = ~mask;

	return mask;
}

class Gen_001EAC50
{
public:
	unsigned char bfmeAny(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeSlots[4];					// +0x08
};

// ?bfmeAny@Gen_001EAC50@@QBEEXZ
unsigned char Gen_001EAC50::bfmeAny(void) const
{
	for (int index = 0; index < 4; ++index)
	{
		if (m_bfmeSlots[index] != 0)
			return 1;
	}

	return 0;
}

// ?bfmeAnySix@@YAEPAH@Z
unsigned char __cdecl bfmeAnySix(int *slots)
{
	for (unsigned int index = 0; index < 6; ++index)
	{
		if (slots[index] != 0)
			return 1;
	}

	return 0;
}

class Gen_001C0D80
{
public:
	int bfmeCount(void) const;

private:
	int m_bfmeHead[11];					// +0x00
	char *m_bfmeStart;					// +0x2C
	char *m_bfmeEnd;					// +0x30
};

// ?bfmeCount@Gen_001C0D80@@QBEHXZ
int Gen_001C0D80::bfmeCount(void) const
{
	return (m_bfmeEnd - m_bfmeStart) / 36;
}

class BfmeClockCE
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeStamp;					// +0x3C
};

extern BfmeClockCE *g_bfmeClockCE;				// retail 0x012F0898

class Gen_001B4980
{
public:
	void bfmeArm(int value, int delay);

private:
	int m_bfmeHead[22];					// +0x00
	int m_bfmeValue;					// +0x58
	int m_bfmeDeadline;					// +0x5C
};

