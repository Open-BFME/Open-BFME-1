// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Particle::loadPostProcess, retail 0x005C5030 (161 bytes).
// The BFME save layout stores a 12-byte system handle at this+0x7C and its
// serialized system ID at this+0x88.

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class Particle;
class ParticleSystem;
extern ParticleSystem *Make00001B18();

class ParticleSystemHandle
{
public:
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class BfmeParticleSystemHandle : public ParticleSystemHandle
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
};

class ParticleSystem;

// Retail stores the control particle at system+0x1A0 inline here, while the
// out-of-line ParticleSystem::setControlParticle (0x0021D740) writes +0x330:
// a file-static helper keeps this TU from emitting a competing COMDAT under
// the real member name.
static __forceinline void setControlParticle(ParticleSystem *system, Particle *particle)
{
	*reinterpret_cast<Particle **>(reinterpret_cast<char *>(system) + 0x1A0) = particle;
}

class ParticleSystemManager
{
	friend class Particle;

	private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

struct BfmeFormattedText
{
	char *text;
	int tag;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

class Particle
{
public:
	unsigned char m_pad00[0x78];
	ParticleSystemHandle m_systemUnderControl;
	ParticleSystemID m_systemUnderControlID;

protected:
	virtual void loadPostProcess();
};

void Particle::loadPostProcess()
{
	if (m_systemUnderControlID != INVALID_PARTICLE_SYSTEM_ID)
	{
		BfmeParticleSystemHandle system =
			TheParticleSystemManager->findParticleSystemByID(m_systemUnderControlID);
		setControlParticle(system.operator->(), this);
		m_systemUnderControl = system;
		if (m_systemUnderControlID == INVALID_PARTICLE_SYSTEM_ID)
		{
			throw XferException(5, 0);
		}
	}
}
