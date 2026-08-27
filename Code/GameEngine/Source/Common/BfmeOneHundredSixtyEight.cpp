// A mark read off a grid of cells by fine position: the position is brought
// down to cell size the way whole-number division rounds toward nothing, and
// anything off the grid answers no. Written twice over, once for each caller.

struct BfmeCellAL
{
	int m_bfmeFirst;			// 0x000
	unsigned char m_bfmeMark;		// 0x004
	unsigned char m_bfmeBody[0x223];	// 0x005
};

class BfmeGridAL
{
public:
	unsigned char bfmeNearAL(int across, int along) const;
	unsigned char bfmeFarAL(int across, int along) const;

private:
	unsigned char m_bfmeHead[0x23628];	// 0x00000
	BfmeCellAL **m_bfmeColumns;		// 0x23628
	int m_bfmeWide;				// 0x2362c
	int m_bfmeHigh;				// 0x23630
};

unsigned char BfmeGridAL::bfmeNearAL(int across, int along) const
{
	if (across < 0 || along < 0)
		return 0;

	int column = across / 16;
	int row = along / 16;

	if (column < m_bfmeWide && row < m_bfmeHigh)
		return m_bfmeColumns[column][row].m_bfmeMark;

	return 0;
}

unsigned char BfmeGridAL::bfmeFarAL(int across, int along) const
{
	if (across < 0 || along < 0)
		return 0;

	int column = across / 16;
	int row = along / 16;

	if (column < m_bfmeWide && row < m_bfmeHigh)
		return m_bfmeColumns[column][row].m_bfmeMark;

	return 0;
}
