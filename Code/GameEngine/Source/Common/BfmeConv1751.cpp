extern int g_s5Head0059D9E0;

class BfmeBaseBE
{
public:
	BfmeBaseBE(void);
};

class BfmeOwnBE : public BfmeBaseBE
{
public:
	BfmeOwnBE(void);

	int *m_bfmeVfBE;
	int m_bfmeABE;
	unsigned char m_bfmePadBE;
	char m_bfmeFlagBE;
	unsigned char m_bfmePad2BE[2];
	int m_bfmeCBE;
	int m_bfmeDBE;
	int m_bfmeEBE;
	unsigned char m_bfmeMidBE[0x10];
	int m_bfmeFBE;
	int m_bfmeGBE;
	int m_bfmeHBE;
	int m_bfmeIBE;
};

BfmeOwnBE::BfmeOwnBE(void)
{
	m_bfmeVfBE = &g_s5Head0059D9E0;
	m_bfmeEBE = 0x1e;
	m_bfmeDBE = 0;
	m_bfmeCBE = 0;
	m_bfmeFBE = 0;
	m_bfmeHBE = 0;
	m_bfmeIBE = 0;
	m_bfmeABE = 0x1e;
	m_bfmeGBE = -1;
	m_bfmeFlagBE = 1;
}
