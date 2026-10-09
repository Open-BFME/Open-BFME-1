// Two more: the getter matching an earlier setter, and
// another bounds-checked cell address.

class BfmeEntryFA
{
public:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeD;						// +0x0C
};

extern unsigned int HighlightColorIndex;					// retail 0x012F1400
// Three independently addressed 16-byte entries end at the next datum,
// g_bfmeDefaultCU (retail VA 0x012B4FF8). Each starts with three 0.5f
// bit patterns; the fourth word is zero.
BfmeEntryFA g_bfmeTableFA[3] = {
    {0x3F000000, 0x3F000000, 0x3F000000, 0},
    {0x3F000000, 0x3F000000, 0x3F000000, 0},
    {0x3F000000, 0x3F000000, 0x3F000000, 0}
};

// ?bfmeLoad@@YAXPAH00H@Z
void __cdecl bfmeLoad(int *first, int *second, int *third, int index)
{
	if (index == -1)
		index = HighlightColorIndex;

	*first = g_bfmeTableFA[index].m_bfmeA;
	*second = g_bfmeTableFA[index].m_bfmeB;
	*third = g_bfmeTableFA[index].m_bfmeC;
}

class BfmeCellFD
{
public:
	int m_bfmeData[26];					// 104 bytes
};

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(int x, int y) const;

private:
	int m_bfmeHead[9];					// +0x00
	int m_bfmeWidth;					// +0x24
	int m_bfmeHeight;					// +0x28
	BfmeCellFD *m_bfmeCells;				// +0x2C
};

// ?bfmeAt@Gen_008F7CD0@@QBEPAVBfmeCellFD@@HH@Z
BfmeCellFD *Gen_008F7CD0::bfmeAt(int x, int y) const
{
	if (x >= 0 && x < m_bfmeWidth && y >= 0 && y < m_bfmeHeight)
		return &m_bfmeCells[m_bfmeWidth * y + x];

	return 0;
}
