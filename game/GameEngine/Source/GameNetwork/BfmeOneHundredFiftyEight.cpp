// Two walks over stored things: a search through four fixed entries, and a pass
// writing a value into every row whose mark is set.

struct BfmeEntryZI
{
	unsigned char m_bfmeHead[8];		// 0x00
	int m_bfmeUsed;				// 0x08
	unsigned char m_bfmeBody[0x18];		// 0x0c
	int m_bfmeOther;			// 0x24
	int m_bfmeKey;				// 0x28
	unsigned char m_bfmeTail[0x68];		// 0x2c
};

class BfmeThingZI
{
public:
	BfmeEntryZI *bfmeFindZI(int key, int other);

private:
	unsigned char m_bfmeHead[0x58];		// 0x000
	BfmeEntryZI m_bfmeEntries[4];		// 0x058
};

BfmeEntryZI *BfmeThingZI::bfmeFindZI(int key, int other)
{
	BfmeEntryZI *at = m_bfmeEntries;
	BfmeEntryZI *end = m_bfmeEntries + 4;

	while (at < end)
	{
		if (at->m_bfmeUsed != 0 && at->m_bfmeKey == key && at->m_bfmeOther == other)
			return at;

		++at;
	}

	return 0;
}

struct BfmeGridZJ
{
	unsigned char m_bfmeHead[0xc];		// 0x0c
	int m_bfmeValue;			// 0x0c
	unsigned char m_bfmeGap[8];		// 0x10
	unsigned char *m_bfmeRows;		// 0x18
	int m_bfmeStride;			// 0x1c
	unsigned char m_bfmeMask;		// 0x20
	unsigned char m_bfmeSpare[3];		// 0x21
	int *m_bfmeOut;				// 0x24
	unsigned char m_bfmeTail[0x64];		// 0x28
	unsigned int m_bfmeCount;		// 0x8c
};

void bfmeFillZJ(BfmeGridZJ *grid)
{
	unsigned int i = 0;
	int value = grid->m_bfmeValue;

	while (i < grid->m_bfmeCount)
	{
		unsigned char mark = grid->m_bfmeRows[grid->m_bfmeStride * i];

		if ((grid->m_bfmeMask & mark) != 0)
			grid->m_bfmeOut[i] = value;

		++i;
	}
}
