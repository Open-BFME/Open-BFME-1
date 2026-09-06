struct Rva0090C2F0Inner
{
	void go(int first, int second, int third, int fourth, int fifth, int sixth,
		int seventh);

	unsigned char m_bfmeHeadBR[8];
	int m_bfmeFlagBR;
	unsigned char m_bfmeMidBR[0x18];
	int m_bfmeABR;
	int m_bfmeBBR;
	unsigned char m_bfmeMid2BR[8];
	int m_bfmeCBR;
	int m_bfmeDBR;
	int m_bfmeEBR;
	int m_bfmeFBR;
	int m_bfmeGBR;
};

struct BfmeHostBR
{
	unsigned char m_bfmeHeadBR[0x14];
	Rva0090C2F0Inner *m_bfmeInnerBR;
};

class BfmeOwnBR
{
public:
	void bfmeRunBR(void);

	BfmeHostBR *m_bfmeHostBR;
};

void BfmeOwnBR::bfmeRunBR(void)
{
	if (m_bfmeHostBR == 0)
		return;

	if (m_bfmeHostBR->m_bfmeInnerBR == 0)
		return;

	if (m_bfmeHostBR->m_bfmeInnerBR->m_bfmeFlagBR)
		return;

	if (m_bfmeHostBR->m_bfmeInnerBR->m_bfmeFBR)
		return;

	m_bfmeHostBR->m_bfmeInnerBR->go(m_bfmeHostBR->m_bfmeInnerBR->m_bfmeABR,
		m_bfmeHostBR->m_bfmeInnerBR->m_bfmeBBR,
		m_bfmeHostBR->m_bfmeInnerBR->m_bfmeEBR,
		m_bfmeHostBR->m_bfmeInnerBR->m_bfmeCBR,
		m_bfmeHostBR->m_bfmeInnerBR->m_bfmeFBR,
		m_bfmeHostBR->m_bfmeInnerBR->m_bfmeGBR,
		m_bfmeHostBR->m_bfmeInnerBR->m_bfmeDBR);
}
