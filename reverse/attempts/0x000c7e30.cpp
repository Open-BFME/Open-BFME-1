// ?bfmeAddFG@BfmeAccumFG@@QAEXH@Z (identity unknown)
// partial score=0.85 date=2026-09-06
// 44/39. Retail tail-jumps to the member callee with ecx already holding the sink
// and the flag written into the caller own argument slot; MSVC spills the sink to
// esi, which forces a restore and therefore a real call.
// Twin at 0x000C7E60 differs only in the member offsets and the compare direction.
// Pin: ?bfmeNotifyFG@BfmeSinkFG@@QAEXH@Z,0x0004326B
class BfmeSinkFG
{
public:
	void bfmeNotifyFG(int flag);
};

class BfmeAccumFG
{
public:
	void bfmeAddFG(int amount);

	unsigned char m_bfmeHeadFG[4];
	int m_bfmeTotalFG;
	int m_bfmeLimitFG;
	BfmeSinkFG *m_bfmeSinkFG;
};

void BfmeAccumFG::bfmeAddFG(int amount)
{
	int total = m_bfmeTotalFG + amount;
	m_bfmeTotalFG = total;

	BfmeSinkFG *sink = m_bfmeSinkFG;
	if (sink != 0)
		return sink->bfmeNotifyFG(total < m_bfmeLimitFG);
}
