class BfmeOtherDRC
{
public:
	void bfmeCallDRC(int *cell);
};

class BfmeThingDRC
{
public:
	BfmeOtherDRC *bfmeGoDRC(BfmeOtherDRC *other, int row, int col);
	unsigned char m_bfmeHead[0x114];
	int m_bfmeGrid[16][3];
};

BfmeOtherDRC *BfmeThingDRC::bfmeGoDRC(BfmeOtherDRC *other, int row, int col)
{
	volatile int tmp = 0;
	other->bfmeCallDRC(&m_bfmeGrid[row][col]);
	return other;
}
