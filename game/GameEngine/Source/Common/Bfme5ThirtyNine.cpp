// Five more: the same forty-byte checksum through a lookup table in three
// classes, a three-word mask, and a pair returned by value from an indexed
// element.

extern unsigned char g_bfmeTableDH[];				// retail 0x012C7128

class Gen_001C0AA0
{
public:
	int bfmeSum(void) const;

private:
	int m_bfmeBody[10];					// +0x00
};

// ?bfmeSum@Gen_001C0AA0@@QBEHXZ
int Gen_001C0AA0::bfmeSum(void) const
{
	const unsigned char *first = (const unsigned char *)this;
	const unsigned char *last = first + 0x28;

	int total = 0;

	while (first < last)
	{
		total += g_bfmeTableDH[*first];

		++first;
	}

	return total;
}

class Gen_001C2BD0
{
public:
	int bfmeSum(void) const;

private:
	int m_bfmeBody[10];					// +0x00
};

// ?bfmeSum@Gen_001C2BD0@@QBEHXZ
int Gen_001C2BD0::bfmeSum(void) const
{
	const unsigned char *first = (const unsigned char *)this;
	const unsigned char *last = first + 0x28;

	int total = 0;

	while (first < last)
	{
		total += g_bfmeTableDH[*first];

		++first;
	}

	return total;
}

class Gen_001C4060
{
public:
	int bfmeSum(void) const;

private:
	int m_bfmeBody[10];					// +0x00
};

// ?bfmeSum@Gen_001C4060@@QBEHXZ
int Gen_001C4060::bfmeSum(void) const
{
	const unsigned char *first = (const unsigned char *)this;
	const unsigned char *last = first + 0x28;

	int total = 0;

	while (first < last)
	{
		total += g_bfmeTableDH[*first];

		++first;
	}

	return total;
}

class BfmeTripleDH
{
public:
	BfmeTripleDH(void)
	{
	}

	BfmeTripleDH(const BfmeTripleDH &other)
	{
		m_bfmeFirst = other.m_bfmeFirst;
		m_bfmeSecond = other.m_bfmeSecond;
		m_bfmeThird = other.m_bfmeThird;
	}

	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

class Gen_002083D0
{
public:
	void bfmeAnd(const BfmeTripleDH *other);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

// ?bfmeAnd@Gen_002083D0@@QAEXPBVBfmeTripleDH@@@Z
void Gen_002083D0::bfmeAnd(const BfmeTripleDH *other)
{
	m_bfmeFirst = m_bfmeFirst & other->m_bfmeFirst;
	m_bfmeSecond = m_bfmeSecond & other->m_bfmeSecond;
	m_bfmeThird = m_bfmeThird & other->m_bfmeThird;
}

class BfmePairDH
{
public:
	BfmePairDH(void)
	{
	}

	BfmePairDH(const BfmePairDH &other)
	{
		m_bfmeFirst = other.m_bfmeFirst;
		m_bfmeSecond = other.m_bfmeSecond;
	}

	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
};

class BfmeItemDH
{
public:
	int m_bfmeTag;						// +0x00
	BfmePairDH m_bfmePair;					// +0x04
	int m_bfmeTail;						// +0x0C
};

class Gen_002301A0
{
public:
	BfmePairDH bfmeGet(int index) const;

private:
	char m_bfmeHead[0x12C];					// +0x000
	BfmeItemDH *m_bfmeItems;				// +0x12C
};

// ?bfmeGet@Gen_002301A0@@QBE?AVBfmePairDH@@H@Z
BfmePairDH Gen_002301A0::bfmeGet(int index) const
{
	return m_bfmeItems[index].m_bfmePair;
}
