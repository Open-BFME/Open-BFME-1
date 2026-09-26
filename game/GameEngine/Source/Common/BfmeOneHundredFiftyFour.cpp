// A small history that remembers the last two answers before it is closed.

class BfmeHistoryYR
{
public:
	void bfmeSetYR(unsigned char answer);

private:
	unsigned char m_bfmeHead[0x4da1];	// 0x0000
	unsigned char m_bfmeFirst;		// 0x4da1
	unsigned char m_bfmeSecond;		// 0x4da2
	unsigned char m_bfmeThird;		// 0x4da3
	unsigned char m_bfmeFourth;		// 0x4da4
	unsigned char m_bfmeClosed;		// 0x4da5
};

void BfmeHistoryYR::bfmeSetYR(unsigned char answer)
{
	if (m_bfmeClosed != 0)
		return;

	m_bfmeThird = m_bfmeFirst;
	m_bfmeFourth = m_bfmeSecond;
	m_bfmeFirst = answer;
	m_bfmeSecond = answer;
	m_bfmeClosed = 1;
}
