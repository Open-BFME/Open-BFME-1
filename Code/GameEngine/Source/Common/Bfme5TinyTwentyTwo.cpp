// Five more: a planar distance, a search over a global table, a flagged
// three-word copy, and twins of the deadline and the bit test that landed
// earlier at other offsets.
class BfmeSpotCN
{
public:
	int m_bfmeHead[14];					// +0x00
	float m_bfmeX;						// +0x38
	float m_bfmeY;						// +0x3C
};

class Gen_0016E370
{
public:
	float bfmeDistanceSquared(const BfmeSpotCN *other) const;

private:
	int m_bfmeHead[14];					// +0x00
	float m_bfmeX;						// +0x38
	float m_bfmeY;						// +0x3C
};

// ?bfmeDistanceSquared@Gen_0016E370@@QBEMPBVBfmeSpotCN@@@Z
float Gen_0016E370::bfmeDistanceSquared(const BfmeSpotCN *other) const
{
	float dx = m_bfmeX - other->m_bfmeX;
	float dy = m_bfmeY - other->m_bfmeY;

	return dx * dx + dy * dy;
}

class BfmeEntryCN
{
public:
	int m_bfmeHead;						// +0x00
	BfmeEntryCN *m_bfmeNext;				// +0x04
	int m_bfmeGap[1];					// +0x08
	void *m_bfmeKey;					// +0x0C
};

class BfmeTableCN
{
public:
	BfmeEntryCN *m_bfmeHead;				// +0x00
};

extern BfmeTableCN *g_bfmeTableCN;				// retail 0x012ACB50

// ?bfmeLookup@@YAPAVBfmeEntryCN@@PAX@Z
BfmeEntryCN * __cdecl bfmeLookup(void *key)
{
	BfmeEntryCN *entry = g_bfmeTableCN->m_bfmeHead;

	while (entry)
	{
		if (entry->m_bfmeKey == key)
			return entry;

		entry = entry->m_bfmeNext;
	}

	return 0;
}

class BfmeTripleCN
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

extern int g_bfmeDirtyCN;					// retail 0x012EF418

class Gen_0018F290
{
public:
	void bfmeSetTriple(const BfmeTripleCN *value);

private:
	int m_bfmeHead[25];					// +0x00
	BfmeTripleCN m_bfmeTriple;				// +0x64
};

// ?bfmeSetTriple@Gen_0018F290@@QAEXPBVBfmeTripleCN@@@Z
void Gen_0018F290::bfmeSetTriple(const BfmeTripleCN *value)
{
	g_bfmeDirtyCN |= 1;

	m_bfmeTriple = *value;
}

class BfmeClockCJ
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeNow;						// +0x3C
	char m_bfmeGap[0x50];					// +0x40
	unsigned char m_bfmeEnabled;				// +0x90
};

extern BfmeClockCJ *g_bfmeSwitchCJ;				// retail 0x012F0898

class Gen_001BFD40
{
public:
	void bfmeSetDeadline(unsigned int milliseconds);

private:
	int m_bfmeHead[215];					// +0x000
	int m_bfmeDeadline;					// +0x35C
};

// ?bfmeSetDeadline@Gen_001BFD40@@QAEXI@Z
void Gen_001BFD40::bfmeSetDeadline(unsigned int milliseconds)
{
	m_bfmeDeadline = milliseconds / 1000 * 5 + g_bfmeSwitchCJ->m_bfmeNow;
}

class Gen_001C4990
{
public:
	bool bfmeHasBit(int bit) const;

private:
	int m_bfmeHead[167];					// +0x000
	unsigned int m_bfmeMask;				// +0x29C
};

// ?bfmeHasBit@Gen_001C4990@@QBE_NH@Z
bool Gen_001C4990::bfmeHasBit(int bit) const
{
	return (m_bfmeMask & (1 << (bit & 31))) != 0;
}
