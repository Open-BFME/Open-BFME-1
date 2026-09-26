// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: ParticleSystem::getSlave, retail 0x0060BB60 (78 bytes).
// Identity: the ILT pin at 0x00029208 names this ParticleSystem accessor.
// The returned handle joins the owner's intrusive handle list at +0x98/+0x9C.

class ParticleSystem;

class ParticleSystemHandle
{
public:
	ParticleSystemHandle(const ParticleSystemHandle &other);

private:
	friend class ParticleSystem;
	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class ParticleSystem
{
public:
	ParticleSystemHandle getSlave();

private:
	friend class ParticleSystemHandle;
	unsigned char m_unmodelled_000[0x98];
	ParticleSystemHandle *m_firstHandle;
	ParticleSystemHandle *m_lastHandle;
	unsigned char m_unmodelled_0A0[0xC0];
	ParticleSystemHandle m_slaveSystem;
};

// ??0ParticleSystemHandle@@QAE@ABV0@@Z absent-from-retail
ParticleSystemHandle::ParticleSystemHandle(const ParticleSystemHandle &other)
{
	ParticleSystem *system = other.m_system;
	m_system = system;
	if (system)
	{
		m_previous = system->m_lastHandle;
		m_next = 0;
		system->m_lastHandle = this;
		if (m_previous)
			m_previous->m_next = this;
		else
			m_system->m_firstHandle = this;
	}
	else
	{
		m_next = 0;
		m_previous = 0;
	}
}

ParticleSystemHandle ParticleSystem::getSlave()
{
	volatile unsigned int unused = 0;
	return m_slaveSystem;
}
