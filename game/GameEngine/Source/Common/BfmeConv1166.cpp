// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1166
{
public:
	BfmeA1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8, unsigned int bitIndex9, unsigned int bitIndex10, unsigned int bitIndex11);
	unsigned int m_bitWords[10];
};

BfmeA1166::BfmeA1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8, unsigned int bitIndex9, unsigned int bitIndex10, unsigned int bitIndex11)
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
}

class BfmeB1166
{
public:
	BfmeB1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8, unsigned int bitIndex9);
	unsigned int m_bitWords[10];
};

BfmeB1166::BfmeB1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8, unsigned int bitIndex9)
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
}

class BfmeC1166
{
public:
	BfmeC1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8);
	unsigned int m_bitWords[10];
};

BfmeC1166::BfmeC1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8)
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
}

class BfmeD1166
{
public:
	BfmeD1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7);
	unsigned int m_bitWords[10];
};

BfmeD1166::BfmeD1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5, unsigned int bitIndex6, unsigned int bitIndex7)
{
	memset(m_bitWords, 0, 0x28);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
	m_bitWords[bitIndex4 >> 5] |= 1u << (bitIndex4 & 0x1f);
	m_bitWords[bitIndex5 >> 5] |= 1u << (bitIndex5 & 0x1f);
	m_bitWords[bitIndex6 >> 5] |= 1u << (bitIndex6 & 0x1f);
	m_bitWords[bitIndex7 >> 5] |= 1u << (bitIndex7 & 0x1f);
}

class BfmeE1166
{
public:
	BfmeE1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5);
	unsigned int m_bitWords[10];
};

BfmeE1166::BfmeE1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5)
{
	memset(m_bitWords, 0, 0x28);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
	m_bitWords[bitIndex4 >> 5] |= 1u << (bitIndex4 & 0x1f);
	m_bitWords[bitIndex5 >> 5] |= 1u << (bitIndex5 & 0x1f);
}

class BfmeF1166
{
public:
	BfmeF1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5);
	unsigned int m_bitWords[6];
};

BfmeF1166::BfmeF1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5)
{
	memset(m_bitWords, 0, 0x18);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
	m_bitWords[bitIndex4 >> 5] |= 1u << (bitIndex4 & 0x1f);
	m_bitWords[bitIndex5 >> 5] |= 1u << (bitIndex5 & 0x1f);
}

class BfmeG1166
{
public:
	BfmeG1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4);
	unsigned int m_bitWords[6];
};

BfmeG1166::BfmeG1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4)
{
	memset(m_bitWords, 0, 0x18);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
	m_bitWords[bitIndex4 >> 5] |= 1u << (bitIndex4 & 0x1f);
}

class BfmeH1166
{
public:
	BfmeH1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3);
	unsigned int m_bitWords[6];
};

BfmeH1166::BfmeH1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3)
{
	memset(m_bitWords, 0, 0x18);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
	m_bitWords[bitIndex3 >> 5] |= 1u << (bitIndex3 & 0x1f);
}

class BfmeI1166
{
public:
	BfmeI1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2);
	unsigned int m_bitWords[10];
};

BfmeI1166::BfmeI1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2)
{
	memset(m_bitWords, 0, 0x28);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
}

class BfmeJ1166
{
public:
	BfmeJ1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2);
	unsigned int m_bitWords[6];
};

BfmeJ1166::BfmeJ1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2)
{
	memset(m_bitWords, 0, 0x18);
	m_bitWords[bitIndex1 >> 5] |= 1u << (bitIndex1 & 0x1f);
	m_bitWords[bitIndex2 >> 5] |= 1u << (bitIndex2 & 0x1f);
}
