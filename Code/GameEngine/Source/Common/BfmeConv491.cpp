class BfmeSinkBMD
{
public:
	void *bfmeMakeBMD(void *what);
};

extern BfmeSinkBMD *g_bfmeSinkBMD;

class BfmeThingBMD
{
public:
	void bfmeGoBMD();
	unsigned char m_bfmeHead[4];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x24];
	void *m_bfmeGot;
};

void BfmeThingBMD::bfmeGoBMD()
{
	m_bfmeGot = g_bfmeSinkBMD->bfmeMakeBMD((char *)m_bfmeWhat + 0x18);
}
