// Four more: two masked table reads, an assignment that hands the object
// back, and a four-state test.

extern int g_bfmeTableDJa[];					// retail 0x012A9200
extern int g_bfmeTableDJb[];					// retail 0x012A68D8

class Gen_001C3F80
{
public:
	int bfmeLookup(int index) const;

private:
	unsigned int m_bfmeMask;				// +0x00
};

// ?bfmeLookup@Gen_001C3F80@@QBEHH@Z
int Gen_001C3F80::bfmeLookup(int index) const
{
	if (m_bfmeMask & (1 << (index & 31)))
		return g_bfmeTableDJa[index];

	return 0;
}

class Gen_0020EC30
{
public:
	int bfmeLookup(int index) const;

private:
	unsigned int m_bfmeMask;				// +0x00
};

// ?bfmeLookup@Gen_0020EC30@@QBEHH@Z
int Gen_0020EC30::bfmeLookup(int index) const
{
	if (m_bfmeMask & (1 << (index & 31)))
		return g_bfmeTableDJb[index];

	return 0;
}

class BfmeTripleDJ
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

class Gen_00233CC0
{
public:
	Gen_00233CC0 &bfmeAssign(const Gen_00233CC0 &other);

private:
	BfmeTripleDJ m_bfmeTriple;				// +0x00
	int m_bfmeExtra;					// +0x0C
};

// ?bfmeAssign@Gen_00233CC0@@QAEAAV1@ABV1@@Z
Gen_00233CC0 &Gen_00233CC0::bfmeAssign(const Gen_00233CC0 &other)
{
	m_bfmeTriple = other.m_bfmeTriple;

	m_bfmeExtra = other.m_bfmeExtra;

	return *this;
}

class Gen_001F83C0
{
public:
	int bfmeActive(void) const;

private:
	int m_bfmeHead[18];					// +0x00
	bool m_bfmeArmed;					// +0x48
	char m_bfmeGap[0x17];					// +0x49
	int m_bfmeState;					// +0x60
};

// ?bfmeActive@Gen_001F83C0@@QBEHXZ
int Gen_001F83C0::bfmeActive(void) const
{
	if (m_bfmeArmed && (m_bfmeState == 1 || m_bfmeState == 2 || m_bfmeState == 3 || m_bfmeState == 4))
		return 1;

	return 0;
}
