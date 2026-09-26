class BfmeStrCG
{
public:
	BfmeStrCG(const char *text);
	~BfmeStrCG();

	int m_bfmeDataCG;
};

class ParticleSystemManager
{
public:
	void bfmeSendCG(const BfmeStrCG &text, void *value);
};

extern ParticleSystemManager *TheParticleSystemManager;

class BfmeOwnCG
{
public:
	void bfmeReportCG(void *first, void *unused);

	unsigned char m_bfmeHeadCG[0xcc];
	char m_bfmeNameCG[1];
};

void BfmeOwnCG::bfmeReportCG(void *first, void *unused)
{
	BfmeStrCG text(m_bfmeNameCG);

	TheParticleSystemManager->bfmeSendCG(text, first);
}
