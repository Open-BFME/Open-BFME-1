// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1167
{
public:
	BfmeA1167(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06);
	unsigned int m_bfme00[3];
};

BfmeA1167::BfmeA1167(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06)
{
	memset(m_bfme00, 0, 0xc);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
}

class BfmeB1167
{
public:
	BfmeB1167(int tag, unsigned int a02, unsigned int a03, unsigned int a04);
	unsigned int m_bfme00[3];
};

BfmeB1167::BfmeB1167(int tag, unsigned int a02, unsigned int a03, unsigned int a04)
{
	memset(m_bfme00, 0, 0xc);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
}

class BfmeC1167
{
public:
	BfmeC1167(int tag, unsigned int a02, unsigned int a03);
	unsigned int m_bfme00[3];
};

BfmeC1167::BfmeC1167(int tag, unsigned int a02, unsigned int a03)
{
	memset(m_bfme00, 0, 0xc);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
}
