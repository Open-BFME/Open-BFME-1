// Retail 0x00540680 calls ILT 0x22999 -> matched 0x0053FC00 on the same this
// (callees.py).
class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyStagingRoomRefresh();
};

class BfmeThingCVD
{
public:
	__forceinline void bfmeApplyCVD()
	{
		((BfmeAptScreenOnlineCustomMatch *)this)->applyStagingRoomRefresh();
	}
	void bfmeGoCVD(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVD::bfmeGoCVD(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10004)
	{
		m_bfmeState = v ^ 0x10000;
		bfmeApplyCVD();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 4;
	bfmeApplyCVD();
}
