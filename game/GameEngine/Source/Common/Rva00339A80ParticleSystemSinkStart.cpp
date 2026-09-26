// cl: /Oa
// Retail 0x00339A80 is an exact 107-byte particle-system sink startup helper.
// The vtable at 0x010E75C0 and TheParticleSystemManager global prove the
// subsystem; the callback's public owner/name is not recovered, so the
// function deliberately keeps its retail RVA in its address-derived name.

extern "C" unsigned char g_rva00339a80Vtable[];

class Rva00339A80ParticleNode;
extern Rva00339A80ParticleNode *g_rva00339a80Node;

class Rva00339A80ParticleNode
{
public:
	Rva00339A80ParticleNode()
	{
		m_vtable = g_rva00339a80Vtable;
		m_value = 0;
		m_flag = 0;
	}

	void *m_vtable;
	int m_value;
	char m_flag;
};

class Rva00339A80ParticleSink
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void attach(void *p) = 0;
	virtual void adopt(Rva00339A80ParticleNode *node) = 0;
	virtual void start() = 0;
};

class ParticleSystemManager
{
public:
	unsigned char m_unported[0x84];
	void *m_sinkData;
};

extern Rva00339A80ParticleSink *g_rva00339a80Sink;
extern ParticleSystemManager *TheParticleSystemManager;

void Rva00339A80ParticleSystemSinkStart()
{
	if (g_rva00339a80Sink == 0)
		return;

	if (g_rva00339a80Node == 0)
	{
		g_rva00339a80Node = new Rva00339A80ParticleNode;
		g_rva00339a80Sink->adopt(g_rva00339a80Node);
	}

	g_rva00339a80Sink->attach(TheParticleSystemManager->m_sinkData);
	g_rva00339a80Sink->start();
}
