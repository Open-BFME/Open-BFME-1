// Both calls go through ILT 0x00022999 to the matched
// BfmeAptScreenOnlineCustomMatch::applyStagingRoomRefresh (0x0053FC00).
class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyStagingRoomRefresh();
};

class BfmeThingCVB
{
public:
	void bfmeGoCVB(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVB::bfmeGoCVB(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10002)
	{
		m_bfmeState = v ^ 0x10000;
		reinterpret_cast<BfmeAptScreenOnlineCustomMatch *>(this)->applyStagingRoomRefresh();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 2;
	reinterpret_cast<BfmeAptScreenOnlineCustomMatch *>(this)->applyStagingRoomRefresh();
}
