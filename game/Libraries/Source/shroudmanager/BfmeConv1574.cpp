// Open-BFME5 conversions.

// Bit-weighted word sum over one partition cell, retail 0x008F9920,
// 131 bytes. Converts the point to cell coordinates with the twins
// ?bfmeCellX@Gen_008F7CD0@@QBEHM@Z (0x008F7480) and
// ?bfmeCellY@Gen_008F7CD0@@QBEHM@Z (0x008F74B0), looks the cell up with
// ?bfmeAt@Gen_008F7CD0@@QBEPAVBfmeCellFD@@HH@Z (0x008F7CD0), then sums
// one word per set mask bit, stepping three words per bit. The mask is
// confined to sixteen bits first; the two stack-threaded converter
// results become the lookup arguments in (x, y) order.

typedef float Real;

struct BfmePointFD
{
	Real x;
	Real y;
};

class BfmeCellFD
{
public:
	int m_bfmeData[26];					// 104 bytes
};

class Gen_008F7CD0
{
public:
	int bfmeCellSum(const BfmePointFD *point, int index,
		unsigned int mask) const;
	BfmeCellFD *bfmeAt(int x, int y) const;
	int bfmeCellX(Real value) const;
	int bfmeCellY(Real value) const;

private:
	char m_bfmeHead[4];					// +0x00
	Real m_bfmeOriginX;					// +0x04
	Real m_bfmeOriginY;					// +0x08
	char m_bfmeMid[20];					// +0x0C
	Real m_bfmeScale;					// +0x20
	int m_bfmeWidth;					// +0x24
	int m_bfmeHeight;					// +0x28
	BfmeCellFD *m_bfmeCells;				// +0x2C
};

// ?bfmeCellSum@Gen_008F7CD0@@QBEHPBUBfmePointFD@@HI@Z
int Gen_008F7CD0::bfmeCellSum(const BfmePointFD *point, int index,
	unsigned int mask) const
{
	if (mask == 0)
		return 0;

	if (index < 0 || index >= 2)
		return 0;

	mask &= 0xffff;

	BfmeCellFD *cell = bfmeAt(bfmeCellX(point->x), bfmeCellY(point->y));

	if (cell == 0)
		return 0;

	int total = 0;
	if (mask != 0)
	{
		unsigned short *words = (unsigned short *)((char *)cell
			+ index * 2 + 6);

		do
		{
			if ((mask & 1) != 0)
				total += *words;

			mask >>= 1;
			words += 3;
		}
		while (mask != 0);
	}

	return total;
}
