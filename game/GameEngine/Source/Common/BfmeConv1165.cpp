// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1165
{
public:
	BfmeA1165(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8, unsigned int bitIndex9, unsigned int bitIndex10, unsigned int bitIndex11, unsigned int bitIndex12, unsigned int bitIndex13, unsigned int bitIndex14, unsigned int bitIndex15);
	unsigned int m_bitWords[10];
};

BfmeA1165::BfmeA1165(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8, unsigned int bitIndex9, unsigned int bitIndex10, unsigned int bitIndex11, unsigned int bitIndex12, unsigned int bitIndex13, unsigned int bitIndex14, unsigned int bitIndex15)
{
	memset(m_bitWords, 0, 0x28);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
	m_bitWords[bitIndex4 >> 5] |= 1u << (bitIndex4 & 0x1f);
	m_bitWords[bitIndex5 >> 5] |= 1u << (bitIndex5 & 0x1f);
	m_bitWords[bitIndex6 >> 5] |= 1u << (bitIndex6 & 0x1f);
	m_bitWords[bitIndex7 >> 5] |= 1u << (bitIndex7 & 0x1f);
	m_bitWords[bitIndex8 >> 5] |= 1u << (bitIndex8 & 0x1f);
	m_bitWords[bitIndex9 >> 5] |= 1u << (bitIndex9 & 0x1f);
	m_bitWords[bitIndex10 >> 5] |= 1u << (bitIndex10 & 0x1f);
	m_bitWords[bitIndex11 >> 5] |= 1u << (bitIndex11 & 0x1f);
	m_bitWords[bitIndex12 >> 5] |= 1u << (bitIndex12 & 0x1f);
	m_bitWords[bitIndex13 >> 5] |= 1u << (bitIndex13 & 0x1f);
	m_bitWords[bitIndex14 >> 5] |= 1u << (bitIndex14 & 0x1f);
	m_bitWords[bitIndex15 >> 5] |= 1u << (bitIndex15 & 0x1f);
}
