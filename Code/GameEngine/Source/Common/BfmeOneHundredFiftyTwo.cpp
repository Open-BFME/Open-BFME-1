// A ring searched by key and a run of numbers searched by value.

struct BfmeValueYI
{
	int m_bfmeFirst;			// 0x0
};

struct BfmeNodeYI
{
	BfmeNodeYI *m_bfmeNext;			// 0x0
	int m_bfmeSpare;			// 0x4
	BfmeValueYI m_bfmeValue;		// 0x8
	unsigned short m_bfmeKey;		// 0xc
};

class BfmeMapYI
{
public:
	BfmeValueYI *bfmeFindYI(unsigned short key) const;

private:
	unsigned char m_bfmeHead[0x1ac];	// 0x000
	BfmeNodeYI *m_bfmeRing;			// 0x1ac
};

BfmeValueYI *BfmeMapYI::bfmeFindYI(unsigned short key) const
{
	BfmeNodeYI *ring = m_bfmeRing;
	BfmeNodeYI *at = ring->m_bfmeNext;

	while (at != ring)
	{
		if (at->m_bfmeKey == key)
			return &at->m_bfmeValue;

		at = at->m_bfmeNext;
	}

	return 0;
}

class BfmeSetYK
{
public:
	unsigned char bfmeHasYK(int value) const;

private:
	unsigned char m_bfmeHead[8];		// 0x0
	int *m_bfmeBegin;			// 0x8
	int *m_bfmeEnd;				// 0xc
};

unsigned char BfmeSetYK::bfmeHasYK(int value) const
{
	int *at = m_bfmeBegin;
	int *end = m_bfmeEnd;

	while (at != end)
	{
		if (*at == value)
			return 1;

		++at;
	}

	return 0;
}
