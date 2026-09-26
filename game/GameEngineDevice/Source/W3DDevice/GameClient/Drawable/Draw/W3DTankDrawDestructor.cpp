// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DTankDraw::~W3DTankDraw.

class ParticleSystem;

class BfmeParticleSystemHandle;

class ParticleSystem
{
public:
	unsigned char m_pad[0x98];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
};

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw()
	{
		if (m_system)
		{
			if (m_previous)
				m_previous->m_next = m_next;
			else
				m_system->m_firstHandle = m_next;
			if (m_next)
				m_next->m_previous = m_previous;
			else
				m_system->m_lastHandle = m_previous;
			m_previous = 0;
			m_next = 0;
		}
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class W3DTankDrawPrimaryBase
{
public:
	virtual void sharedSlot();
	void *m_moduleData;
	void *m_drawable;
};

class W3DTankDrawSecondaryBase
{
public:
	virtual void sharedSlot();
};

class Gen_dtor_0077bf80 : public W3DTankDrawPrimaryBase,
	public W3DTankDrawSecondaryBase
{
public:
	virtual ~Gen_dtor_0077bf80();
	virtual void sharedSlot();

private:
	unsigned char m_pad[0x27c - 0x10];
};

class RenderObjClass
{
public:
	virtual void Release_Ref();
	int m_refCount;
};

struct TreadObjectInfo
{
	RenderObjClass *m_robj;
	unsigned char m_rest[0x10];
};

class W3DTankDraw : public Gen_dtor_0077bf80
{
protected:
	virtual ~W3DTankDraw();

	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;
	void *m_prevRenderObj;
	TreadObjectInfo m_treads[4];
};

W3DTankDraw::~W3DTankDraw()
{
	for (int i = 0; i < 4; ++i)
	{
		RenderObjClass *robj = m_treads[i].m_robj;
		if (robj)
		{
			if (--robj->m_refCount == 0)
				robj->Release_Ref();
			m_treads[i].m_robj = 0;
		}
	}
}
