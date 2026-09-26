extern int g_s5Head0059FB50;

class BfmeBaseBC
{
public:
	BfmeBaseBC(void);
};

class BfmeOwnBC : public BfmeBaseBC
{
public:
	BfmeOwnBC(void);

	int *m_bfmeVfBC;
	int m_bfmeABC;
	unsigned char m_bfmeHeadBC[8];
	int m_bfmeBBC;
	int m_bfmeCBC;
	int m_bfmeDBC;
	char m_bfmeEBC;
	unsigned char m_bfmePadBC[3];
	float m_bfmeFBC;
	char m_bfmeGBC;
};

BfmeOwnBC::BfmeOwnBC(void)
{
	m_bfmeVfBC = &g_s5Head0059FB50;
	m_bfmeCBC = 0x1e;
	m_bfmeBBC = 0;
	m_bfmeEBC = 0;
	m_bfmeGBC = 0;
	m_bfmeDBC = 7;
	m_bfmeFBC = 1.0f;
	m_bfmeABC = 0x1e;
}
