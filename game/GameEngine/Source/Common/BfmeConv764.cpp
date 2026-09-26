class BfmeOtherDRB
{
public:
	void bfmeCallDRB(int *cell);
};

class BfmeThingDRB
{
public:
	BfmeOtherDRB *bfmeGoDRB(BfmeOtherDRB *other, int row, int col);
	unsigned char m_bfmeHead[0xe4];
	int m_bfmeGrid[16][3];
};

BfmeOtherDRB *BfmeThingDRB::bfmeGoDRB(BfmeOtherDRB *other, int row, int col)
{
	volatile int tmp = 0;
	other->bfmeCallDRB(&m_bfmeGrid[row][col]);
	return other;
}
