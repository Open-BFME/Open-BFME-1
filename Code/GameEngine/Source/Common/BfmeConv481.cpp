struct BfmePartBKF
{
	void bfmeOneBKF();
	unsigned char m_bfmeHead[4];
};

class BfmeThingBKF
{
public:
	void bfmeGoBKF();
	unsigned char m_bfmeHead[0x2c];
	BfmePartBKF m_bfmeB;
	BfmePartBKF m_bfmeA;
	unsigned char m_bfmeGap[0x40];
	bool m_bfmeFlag;
};

void BfmeThingBKF::bfmeGoBKF()
{
	m_bfmeFlag = true;
	m_bfmeA.bfmeOneBKF();
	m_bfmeB.bfmeOneBKF();
}
