class BfmeOtherDRA
{
public:
	void bfmeCallDRA(int *cell);
};

class BfmeThingDRA
{
public:
	BfmeOtherDRA *bfmeGoDRA(BfmeOtherDRA *other, int row, int col);
	unsigned char m_bfmeHead[0xa4];
	int m_bfmeGrid[16][3];
};

BfmeOtherDRA *BfmeThingDRA::bfmeGoDRA(BfmeOtherDRA *other, int row, int col)
{
	volatile int tmp = 0;
	other->bfmeCallDRA(&m_bfmeGrid[row][col]);
	return other;
}
