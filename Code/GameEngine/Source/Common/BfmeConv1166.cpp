// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeA1166
{
public:
	BfmeA1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09, unsigned int a10, unsigned int a11, unsigned int a12);
	unsigned int m_bfme00[10];
};

BfmeA1166::BfmeA1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09, unsigned int a10, unsigned int a11, unsigned int a12)
{
	memset(m_bfme00, 0, 0x28);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
	m_bfme00[a07 >> 5] |= 1u << (a07 & 0x1f);
	m_bfme00[a08 >> 5] |= 1u << (a08 & 0x1f);
	m_bfme00[a09 >> 5] |= 1u << (a09 & 0x1f);
	m_bfme00[a10 >> 5] |= 1u << (a10 & 0x1f);
	m_bfme00[a11 >> 5] |= 1u << (a11 & 0x1f);
	m_bfme00[a12 >> 5] |= 1u << (a12 & 0x1f);
}

class BfmeB1166
{
public:
	BfmeB1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09, unsigned int a10);
	unsigned int m_bfme00[10];
};

BfmeB1166::BfmeB1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09, unsigned int a10)
{
	memset(m_bfme00, 0, 0x28);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
	m_bfme00[a07 >> 5] |= 1u << (a07 & 0x1f);
	m_bfme00[a08 >> 5] |= 1u << (a08 & 0x1f);
	m_bfme00[a09 >> 5] |= 1u << (a09 & 0x1f);
	m_bfme00[a10 >> 5] |= 1u << (a10 & 0x1f);
}

class BfmeC1166
{
public:
	BfmeC1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09);
	unsigned int m_bfme00[10];
};

BfmeC1166::BfmeC1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08, unsigned int a09)
{
	memset(m_bfme00, 0, 0x28);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
	m_bfme00[a07 >> 5] |= 1u << (a07 & 0x1f);
	m_bfme00[a08 >> 5] |= 1u << (a08 & 0x1f);
	m_bfme00[a09 >> 5] |= 1u << (a09 & 0x1f);
}

class BfmeD1166
{
public:
	BfmeD1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08);
	unsigned int m_bfme00[10];
};

BfmeD1166::BfmeD1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06, unsigned int a07, unsigned int a08)
{
	memset(m_bfme00, 0, 0x28);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
	m_bfme00[a07 >> 5] |= 1u << (a07 & 0x1f);
	m_bfme00[a08 >> 5] |= 1u << (a08 & 0x1f);
}

class BfmeE1166
{
public:
	BfmeE1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06);
	unsigned int m_bfme00[10];
};

BfmeE1166::BfmeE1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06)
{
	memset(m_bfme00, 0, 0x28);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
}

class BfmeF1166
{
public:
	BfmeF1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06);
	unsigned int m_bfme00[6];
};

BfmeF1166::BfmeF1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05, unsigned int a06)
{
	memset(m_bfme00, 0, 0x18);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
	m_bfme00[a06 >> 5] |= 1u << (a06 & 0x1f);
}

class BfmeG1166
{
public:
	BfmeG1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05);
	unsigned int m_bfme00[6];
};

BfmeG1166::BfmeG1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04, unsigned int a05)
{
	memset(m_bfme00, 0, 0x18);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
	m_bfme00[a05 >> 5] |= 1u << (a05 & 0x1f);
}

class BfmeH1166
{
public:
	BfmeH1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04);
	unsigned int m_bfme00[6];
};

BfmeH1166::BfmeH1166(int tag, unsigned int a02, unsigned int a03, unsigned int a04)
{
	memset(m_bfme00, 0, 0x18);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
	m_bfme00[a04 >> 5] |= 1u << (a04 & 0x1f);
}

class BfmeI1166
{
public:
	BfmeI1166(int tag, unsigned int a02, unsigned int a03);
	unsigned int m_bfme00[10];
};

BfmeI1166::BfmeI1166(int tag, unsigned int a02, unsigned int a03)
{
	memset(m_bfme00, 0, 0x28);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
}

class BfmeJ1166
{
public:
	BfmeJ1166(int tag, unsigned int a02, unsigned int a03);
	unsigned int m_bfme00[6];
};

BfmeJ1166::BfmeJ1166(int tag, unsigned int a02, unsigned int a03)
{
	memset(m_bfme00, 0, 0x18);
	m_bfme00[a02 >> 5] |= 1u << (a02 & 0x1f);
	m_bfme00[a03 >> 5] |= 1u << (a03 & 0x1f);
}
