// cl: /O2 /Ob1

enum GameDifficulty {};

// retail ILT 0x0001AB54 -> 0x0045B5C0 is the matched AIPlayer::setAIDifficulty
// row and ILT 0x000312A0 -> 0x007423B0 the matched private
// W3DView::setCameraTransform row
class AIPlayer
{
public:
	void setAIDifficulty(GameDifficulty difficulty);
};

class W3DView
{
	friend class Gen_00742DA0;
	void setCameraTransform();
};

class Gen_00742DA0
{
public:
	void bfmeReset(int value);

private:
	unsigned char m_bfmeGap[0x1DC];
	unsigned char m_bfmeD;
	unsigned char m_bfmeGap4[0x204 - 0x1DD];
	unsigned char m_bfmeE;
	unsigned char m_bfmeGap5[0x228 - 0x205];
	unsigned char m_bfmeF;
	unsigned char m_bfmeGap6[0x27C - 0x229];
	unsigned char m_bfmeG;
	unsigned char m_bfmeH;
};

void Gen_00742DA0::bfmeReset(int value)
{
	unsigned char zero;

	((AIPlayer *)this)->setAIDifficulty((GameDifficulty)value);

	zero = 0;
	m_bfmeD = zero;
	m_bfmeE = zero;
	m_bfmeG = zero;
	m_bfmeF = zero;
	m_bfmeH = zero;

	((W3DView *)this)->setCameraTransform();
}
