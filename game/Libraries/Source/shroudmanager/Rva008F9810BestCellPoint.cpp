// Retail 0x008F9810, 259 bytes, RET12 at +0x100.
// The owner is an address-derived view of the grid used by the forwarder at
// 0x008F7450. No original class or method spelling is asserted.
// Native BFME2 loop structure, adapted to BFME1's two indices, 16-bit mask,
// 0x68-byte cells and three-word channel stride. Keeping the output divisions
// at their stores preserves the retail reloads and register allocation.
// Evidence: targets/game/reverse/identity_evidence/008f9810-native-grid-scan.md.

#include "../../../GameEngine/Include/Common/ScalarTypes.h"

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
	mask &= 0xFFFF;
	const char *bestCell = (const char *)m_bfmeCells;
	const char *finish = (const char *)m_bfmeCells + m_bfmeHeight * m_bfmeWidth * 0x68;
	unsigned int best = 0;
	for (const char *cell = (const char *)m_bfmeCells; cell != finish; cell += 0x68)
	{
		unsigned int total = 0;
		unsigned int m = (unsigned int)mask;
		if (m != 0)
		{
			const unsigned short *words = (const unsigned short *)(cell + index * 2 + 6);
			do
			{
				if ((m & 1) != 0)
					total += *words;
				m >>= 1;
				words += 3;
			} while (m != 0);
		}
		if (total > best)
		{
			bestCell = cell;
			best = total;
		}
	}
	unsigned int row = (unsigned int)((bestCell - (const char *)m_bfmeCells) / 0x68);
	out->x = (Real)(row % (unsigned int)m_bfmeWidth) * m_bfmeScale;
	out->y = (Real)(row / (unsigned int)m_bfmeWidth) * m_bfmeScale;
	out->z = 0.0f;
}
