// ?bfmeStartYO@@YAXXZ
// partial score=1.0 date=2026-09-10
// cl: /Oa
extern "C" unsigned char bfmeVftYO[];

class BfmeNodeYO;
extern BfmeNodeYO *g_bfmeNodeYO;

class BfmeNodeYO
{
public:
	BfmeNodeYO()
	{
		m_bfmeVfYO = bfmeVftYO;
		m_bfme04YO = 0;
		m_bfme08YO = 0;
	}

	void *m_bfmeVfYO;
	int m_bfme04YO;
	char m_bfme08YO;
};

class BfmeSinkYO
{
public:
	virtual void bfmeV0YO() = 0;
	virtual void bfmeV1YO() = 0;
	virtual void bfmeAttachYO(void *p) = 0;
	virtual void bfmeAdoptYO(BfmeNodeYO *n) = 0;
	virtual void bfmeStartYO() = 0;

};

class ParticleSystemManager
{
public:
	unsigned char m_bfmeHeadYO[0x84];
	void *m_bfme84YO;
};

extern BfmeSinkYO *g_bfmeSinkYO;
extern ParticleSystemManager *TheParticleSystemManager;

void bfmeStartYO()
{
	if (g_bfmeSinkYO == 0)
		return;

	if (g_bfmeNodeYO == 0)
	{
		g_bfmeNodeYO = new BfmeNodeYO;
		g_bfmeSinkYO->bfmeAdoptYO(g_bfmeNodeYO);
	}

	g_bfmeSinkYO->bfmeAttachYO(TheParticleSystemManager->m_bfme84YO);
	g_bfmeSinkYO->bfmeStartYO();
}
