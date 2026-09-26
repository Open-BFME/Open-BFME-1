// cl: /DNDEBUG /MD /EHsc
// Readable conversion of ActiveBody::deleteAllParticleSystems.
// The body owns a singly-linked BodyParticleSystem list at this+0xA8.  Each
// lookup returns BFME's intrusive 12-byte particle-system handle by value;
// the handle is released at the end of every iteration.

typedef unsigned int UnsignedInt;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem
{
public:
	void destroy(void);                         // ILT 0x0000E525

	unsigned char m_pad[0x98];
	class BfmeParticleSystemHandle *m_firstHandle;
	class BfmeParticleSystemHandle *m_lastHandle;
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(ParticleSystem *system = 0) :
		m_system(system), m_previous(0), m_next(0) { }
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that);
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

	operator bool() const { return m_system != 0; }
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

// MemoryPoolObject::deleteInstance ultimately dispatches the virtual
// deleting destructor of the concrete BodyParticleSystem.  Only that ABI
// operation and the two list fields are relevant to this body.
class BodyParticleSystem;

class ActiveBody
{
protected:
	void deleteAllParticleSystems(void);

private:
	unsigned char m_bodyFields[0xA8];
	BodyParticleSystem *m_particleSystems;
};

class ParticleSystemManager
{
	friend void ActiveBody::deleteAllParticleSystems(void);

private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class BodyParticleSystem
{
public:
	virtual ~BodyParticleSystem();

	ParticleSystemID m_particleSystemID;
	BodyParticleSystem *m_next;

	void deleteInstance()
	{
		delete this;
	}
};
void ActiveBody::deleteAllParticleSystems(void)
{
	BodyParticleSystem *nextBodySystem;
	ParticleSystem *particleSystem;

	while (m_particleSystems)
	{
		BfmeParticleSystemHandle system =
			TheParticleSystemManager->findParticleSystemByID(
				m_particleSystems->m_particleSystemID);
		if (system.m_system)
			system.m_system->destroy();

		nextBodySystem = m_particleSystems->m_next;
		m_particleSystems->deleteInstance();
		m_particleSystems = nextBodySystem;
	}
}
