// Three more: two sibling loops that stamp the same byte across every row and
// then mark the whole thing dirty, and the generator behind them.

class BfmeRowJA
{
public:
	unsigned char m_bfmeFlag;					// +0x00
	unsigned char m_bfmeGap[0xa3];				// +0x01
};

class Gen_0071C420
{
public:
	void bfmeStampRows(unsigned char value);
private:
	unsigned char m_bfmeGap[0x158c];			// +0x000000
	BfmeRowJA m_bfmeRows[11999];				// +0x00158c
	unsigned char m_bfmeGap2[96];				// +0x1e1c68
	int m_bfmeCount;							// +0x1e1cc8
	unsigned char m_bfmeDirty;					// +0x1e1ccc
};

// The count is a member and the stamp lands in the same object, so the bound
// has to be read again every time round.
void Gen_0071C420::bfmeStampRows(unsigned char value)
{
	for (int index = 0; index < m_bfmeCount; ++index)
		m_bfmeRows[index].m_bfmeFlag = value;

	m_bfmeDirty = 1;
}

class BfmeRowJB
{
public:
	unsigned char m_bfmeFlag;					// +0x00
	unsigned char m_bfmeGap[0xe7];				// +0x01
};

class Gen_00732AB0
{
public:
	void bfmeStampRows(unsigned char value);
private:
	unsigned char m_bfmeGap[0x1f4];				// +0x000000
	BfmeRowJB m_bfmeRows[11999];				// +0x0001f4
	unsigned char m_bfmeGap2[164];				// +0x2a7c0c
	int m_bfmeCount;							// +0x2a7cb0
	unsigned char m_bfmeDirty;					// +0x2a7cb4
};

void Gen_00732AB0::bfmeStampRows(unsigned char value)
{
	for (int index = 0; index < m_bfmeCount; ++index)
		m_bfmeRows[index].m_bfmeFlag = value;

	m_bfmeDirty = 1;
}

extern int g_bfmeSeedJC;
extern int g_bfmeCarryJC;

int bfmeRandom(int range)
{
	int seed = g_bfmeSeedJC;
	int carry = g_bfmeCarryJC;

	int mix = seed * 0x3E322 + carry * 0x8149A;
	int next = mix % 0xF408B;

	g_bfmeCarryJC = seed;
	g_bfmeSeedJC = next;
	return next % range;
}
