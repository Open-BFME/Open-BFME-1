// ?d_008f9810@@YAXXZ
// partial score=0.35 date=2026-09-10
// Open-BFME5 conversions.

// Retail 0x008F9810, 259 bytes. Owner offsets (this-relative) proved by a
// prior blocked attempt: +0x24 width, +0x28 height, +0x2C cell array,
// matching the twin grid-scan family in BfmeConv1563/1565/1574.cpp. Scans
// every BfmeCellFD in the grid (stride 0x68, same layout as
// Gen_008F7CD0::bfmeCellSum), picks the cell with the largest masked word
// sum, then converts that cell's index back to a world-space point.

typedef float Real;

struct BfmePointFD3
{
	Real x;
	Real y;
	Real z;
};

class Rva008F9810Owner
{
public:
	void bfmeBestCellPoint(unsigned int mask, int index, BfmePointFD3 *out) const;

private:
	char m_pad00[0x1C];			// +0x00
	Real m_bfmeScale;			// +0x1C
	char m_pad20[4];			// +0x20
	int m_bfmeWidth;			// +0x24
	int m_bfmeHeight;			// +0x28
	unsigned char *m_bfmeCells;		// +0x2C, stride 0x68 per cell
};

void Rva008F9810Owner::bfmeBestCellPoint(unsigned int mask, int index, BfmePointFD3 *out) const
{
	if (mask == 0)
		return;

	if (index < 0 || index >= 2)
		return;

	mask &= 0xffff;

	unsigned char *cells = m_bfmeCells;
	unsigned char *end = cells + (unsigned int)(m_bfmeWidth * m_bfmeHeight) * 0x68;
	unsigned char *best = cells;
	int bestSum = 0;

	for (unsigned char *cell = cells; cell != end; cell += 0x68)
	{
		int sum = 0;
		if (mask != 0)
		{
			unsigned short *word = (unsigned short *)(cell + index * 2 + 6);
			unsigned int m = mask;
			do
			{
				if ((m & 1) != 0)
					sum += *word;

				m >>= 1;
				word += 3;
			}
			while (m != 0);
		}

		if (sum > bestSum)
		{
			bestSum = sum;
			best = cell;
		}
	}

	int cellIndex = (int)(best - cells) / 0x68;
	int row = cellIndex / m_bfmeWidth;
	int col = cellIndex % m_bfmeWidth;

	out->x = (Real)(unsigned int)col * m_bfmeScale;
	out->y = (Real)(unsigned int)row * m_bfmeScale;
	out->z = 0.0f;
}
