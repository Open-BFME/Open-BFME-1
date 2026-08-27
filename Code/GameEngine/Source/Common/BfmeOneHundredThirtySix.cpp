// One more: a constructor whose middle field is four only for the first mode.

class Gen_00920A20
{
public:
	Gen_00920A20(int mode);
private:
	int m_bfmeA;								// +0x00
	int m_bfmeB;								// +0x04
	int m_bfmeC;								// +0x08
	int m_bfmeD;								// +0x0c
	int m_bfmeE;								// +0x10
};

Gen_00920A20::Gen_00920A20(int mode)
{
	m_bfmeD = 0;
	m_bfmeE = 0;

	m_bfmeA = 4;
	m_bfmeB = 4;
	m_bfmeC = (mode != 1) ? 4 : 0;
}
