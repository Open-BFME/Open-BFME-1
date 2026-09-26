// Three more: two byte-wise comparisons and a three-word complement whose
// last word is masked by a trim that takes the word by address -- that is
// what keeps the complement's own store from being folded away.

class BfmeThingCP
{
public:
	char m_bfmeHead[0x344];					// +0x000
	unsigned char m_bfmeBits;				// +0x344
};

class Gen_001DCDB0
{
public:
	int bfmeSameBit(const BfmeThingCP *other) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeThingCP *m_bfmeThing;				// +0x08
};

// ?bfmeSameBit@Gen_001DCDB0@@QBEHPBVBfmeThingCP@@@Z
int Gen_001DCDB0::bfmeSameBit(const BfmeThingCP *other) const
{
	unsigned char bits = m_bfmeThing->m_bfmeBits;

	bits = bits ^ other->m_bfmeBits;
	bits = bits >> 3;
	bits = ~bits;

	return bits & 1;
}

class BfmeMaskCP
{
public:
	int m_bfmeHead[105];					// +0x000
	unsigned int m_bfmeMask;				// +0x1A4
};

class Gen_001DD8C0
{
public:
	int bfmeMatches(const BfmeMaskCP *other) const;

private:
	int m_bfmeHead[2];					// +0x00
	unsigned char m_bfmeWanted;				// +0x08
};

// ?bfmeMatches@Gen_001DD8C0@@QBEHPBVBfmeMaskCP@@@Z
int Gen_001DD8C0::bfmeMatches(const BfmeMaskCP *other) const
{
	unsigned char bit = (unsigned char)(other->m_bfmeMask >> 5);

	bit = bit & 1;

	return bit == m_bfmeWanted;
}

class Gen_00216660
{
public:
	void bfmeInvert(void);

private:
	unsigned int m_bfmeFirst;				// +0x00
	unsigned int m_bfmeSecond;				// +0x04
	unsigned int m_bfmeThird;				// +0x08
};

// The trim takes the word by address, which is what keeps the complement's
// own store alive ahead of the masked one.
inline void bfmeTrim(unsigned int *word)
{
	*word = *word & 0x3FFFFF;
}

// ?bfmeInvert@Gen_00216660@@QAEXXZ
void Gen_00216660::bfmeInvert(void)
{
	m_bfmeFirst = ~m_bfmeFirst;
	m_bfmeSecond = ~m_bfmeSecond;
	m_bfmeThird = ~m_bfmeThird;

	bfmeTrim(&m_bfmeThird);
}
