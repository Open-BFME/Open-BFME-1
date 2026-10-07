// A pass writing a value into every row whose mark is set.

// BfmeThingZI::bfmeFindZI (retail 0x007F6A40) lives in
// Rva007F7DA0GameBrowserTicket.cpp: its caller there needs the body visible
// to reproduce retail's register allocation.

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
