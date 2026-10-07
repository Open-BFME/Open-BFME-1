// Retail calls ILT 0x00022999 -> 0x0053FC00, the matched staging-room refresh.
class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyStagingRoomRefresh();
};

class BfmeThingCVA
{
public:
	void bfmeGoCVA(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVA::bfmeGoCVA(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10001)
	{
		m_bfmeState = v ^ 0x10000;
		((BfmeAptScreenOnlineCustomMatch *)this)->applyStagingRoomRefresh();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 1;
	((BfmeAptScreenOnlineCustomMatch *)this)->applyStagingRoomRefresh();
}
