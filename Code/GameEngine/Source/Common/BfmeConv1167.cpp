// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1167
{
public:
	BfmeA1167(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5);
	unsigned int m_bitWords[3];
};

BfmeA1167::BfmeA1167(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5)
{
	memset(m_bitWords, 0, 0xc);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
	m_bitWords[bitIndex4 >> 5] |= 1u << (bitIndex4 & 0x1f);
	m_bitWords[bitIndex5 >> 5] |= 1u << (bitIndex5 & 0x1f);
}

class BfmeB1167
{
public:
	BfmeB1167(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3);
	unsigned int m_bitWords[3];
};

BfmeB1167::BfmeB1167(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3)
{
	memset(m_bitWords, 0, 0xc);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
}

class BfmeC1167
{
public:
	BfmeC1167(int tag, unsigned int bitIndex1, unsigned int bitIndex2);
	unsigned int m_bitWords[3];
};

BfmeC1167::BfmeC1167(int tag, unsigned int bitIndex1, unsigned int bitIndex2)
{
	memset(m_bitWords, 0, 0xc);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
}
