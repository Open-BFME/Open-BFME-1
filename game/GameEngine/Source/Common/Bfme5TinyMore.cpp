// Three more tiny ones: a value that reads as zero while a flag is set, a
// masked bit test whose result comes back as an int through the carry, and a
// flag that clears another when it is set.

class Gen_0020FB30
{
public:
	int bfmeValue(void) const;

private:
	int m_bfmeHead[18];					// +0x00
	int m_bfmeStored;					// +0x48
	char m_bfmeGap[0x5A];					// +0x4C
	unsigned char m_bfmeHidden;				// +0xA6
};

// ?bfmeValue@Gen_0020FB30@@QBEHXZ
int Gen_0020FB30::bfmeValue(void) const
{
	if (m_bfmeHidden)
		return 0;

	return m_bfmeStored;
}

class Gen_001EAB50
{
public:
	int bfmeHasOther(int mask) const;

private:
	char m_bfmeHead[0x345];					// +0x000
	unsigned char m_bfmeBits;				// +0x345
};

// ?bfmeHasOther@Gen_001EAB50@@QBEHH@Z
int Gen_001EAB50::bfmeHasOther(int mask) const
{
	return (m_bfmeBits & ~mask) != 0;
}

class Gen_0016A710
{
public:
	void bfmeSetHeld(unsigned char value);

private:
	char m_bfmeHead[0x326];					// +0x000
	unsigned char m_bfmeOther;				// +0x326
	unsigned char m_bfmeGap;				// +0x327
	unsigned char m_bfmeHeld;				// +0x328
};

// ?bfmeSetHeld@Gen_0016A710@@QAEXE@Z
void Gen_0016A710::bfmeSetHeld(unsigned char value)
{
	m_bfmeHeld = value;

	if (value)
		m_bfmeOther = 0;
}
