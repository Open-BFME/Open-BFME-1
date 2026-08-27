// A word written into every row of every column, and a flag cleared through a
// whole table of lists.

struct BfmeRowAD
{
	unsigned char m_bfmeHead[0xa];		// 0x00
	unsigned short m_bfmeValue;		// 0x0a
	unsigned char m_bfmeTail[4];		// 0x0c
};

class BfmeTableAD
{
public:
	void bfmeFillAD(int value);

private:
	unsigned char m_bfmeHead[4];		// 0x00
	BfmeRowAD **m_bfmeColumns;		// 0x04
	int m_bfmeColumnCount;			// 0x08
	int m_bfmeRowCount;			// 0x0c
	unsigned char m_bfmeGap[0x20];		// 0x10
	int m_bfmeLast;				// 0x30
};

void BfmeTableAD::bfmeFillAD(int value)
{
	m_bfmeLast = value;

	for (int column = 0; column < m_bfmeColumnCount; ++column)
	{
		for (int row = 0; row < m_bfmeRowCount; ++row)
			m_bfmeColumns[column][row].m_bfmeValue = (unsigned short)value;
	}
}
