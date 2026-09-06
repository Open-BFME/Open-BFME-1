extern int g_s5Head0059DE10;

class BfmeBaseBB
{
public:
	BfmeBaseBB(void);
};

class BfmeOwnBB : public BfmeBaseBB
{
public:
	BfmeOwnBB(void);

	int *m_bfmeVfBB;
	int m_bfmeABB;
	unsigned char m_bfmePadBB;
	char m_bfmeFlagBB;
	unsigned char m_bfmePad2BB[2];
	int m_bfmeCBB;
	int m_bfmeDBB;
	int m_bfmeEBB;
	unsigned char m_bfmeMidBB[0x10];
	int m_bfmeFBB;
	int m_bfmeGBB;
	int m_bfmeHBB;
};

BfmeOwnBB::BfmeOwnBB(void)
{
	m_bfmeVfBB = &g_s5Head0059DE10;
	m_bfmeEBB = 0x1e;
	m_bfmeDBB = 0;
	m_bfmeCBB = 0;
	m_bfmeFBB = 0;
	m_bfmeHBB = 0;
	m_bfmeABB = 0x1e;
	m_bfmeGBB = -1;
	m_bfmeFlagBB = 1;
}
