// cl: /O2 /EHsc
// Open-BFME: Particle::~Particle, retail 0x005CE990 (216 bytes), and its
// scalar-deleting wrapper at 0x005CF050. Particle vtable 0x0110FE8C slot 0
// routes to the wrapper through ILT 0x0043F558. Slot 1 is Particle's load
// post-process method and slot 2 returns "FXParticle".

class Particle;
class ParticleSystem;
class ParticleSystemManager;

extern ParticleSystem *Make00001B18();
extern ParticleSystemManager *TheParticleSystemManager;

class BfmeBaseVUQ
{
protected:
	virtual ~BfmeBaseVUQ() { }
};

class ParticleSystem
{
public:
	virtual void release();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void detachControlParticle();

	void destroy();
	void removeParticle(Particle *particle);

	int m_refCount;
	unsigned char m_pad08[0x198];
	Particle *m_controlParticle;

	void releaseRef()
	{
		if (--m_refCount == 0)
			release();
	}
};

class ParticleSystemManager
{
public:
	void removeParticle(Particle *particle);
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that);
	~BfmeParticleSystemHandle() throw();

	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make00001B18();
	}

	operator bool() const
	{
		return m_system != 0;
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class Rva005CE920
{
public:
	~Rva005CE920();
};

class Particle : public BfmeBaseVUQ
{
protected:
	__declspec(noinline) virtual ~Particle();

	unsigned char m_pad04[0x48];
	BfmeParticleSystemHandle m_system;
	unsigned char m_pad58[0x18];
	ParticleSystem *m_controlSystem;
	unsigned char m_pad74[0x08];
	BfmeParticleSystemHandle m_destroySystem;
	unsigned int m_destroySystemID;
	Rva005CE920 m_tail;
};

Particle::~Particle()
{
	m_system->removeParticle(this);

	if (m_controlSystem)
	{
		m_controlSystem->detachControlParticle();
		if (m_controlSystem)
		{
			m_controlSystem->releaseRef();
			m_controlSystem = 0;
		}
	}

	if (m_destroySystem)
	{
		m_destroySystem->m_controlParticle = 0;
		m_destroySystem->destroy();
	}

	TheParticleSystemManager->removeParticle(this);
}
