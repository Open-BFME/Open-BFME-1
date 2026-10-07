// The refresh both arms call is ILT 0x00022999 -> 0x0053FC00, matched as
// BfmeAptScreenOnlineCustomMatch::applyStagingRoomRefresh (thiscall, void).
class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyStagingRoomRefresh();
};

class BfmeThingCVC
{
public:
	void bfmeGoCVC(void *what);
	unsigned char m_bfmeHead[0x1e8];
	int m_bfmeState;
	int m_bfmePrev;
};

void BfmeThingCVC::bfmeGoCVC(void *what)
{
	int v = m_bfmeState;
	if ((v | 0x10000) == 0x10008)
	{
		m_bfmeState = v ^ 0x10000;
		reinterpret_cast<BfmeAptScreenOnlineCustomMatch *>(this)->applyStagingRoomRefresh();
		return;
	}
	m_bfmePrev = v;
	m_bfmeState = 8;
	reinterpret_cast<BfmeAptScreenOnlineCustomMatch *>(this)->applyStagingRoomRefresh();
}
