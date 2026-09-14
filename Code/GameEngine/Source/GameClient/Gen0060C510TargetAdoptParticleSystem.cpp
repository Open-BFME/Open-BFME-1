// ?adoptParticleSystem@Gen0060C510Target@@QAEXPAVBfmeParticleSystemHandle@@@Z
// The Living World manager passes the newly created BFME particle handle to
// this target method at retail 0x00610D60. The target keeps its handle at
// +0x14 and caches the adopted system ID at +0x20.

typedef unsigned int ParticleSystemID;

class ParticleSystem
{
public:
	unsigned char m_beforeSystemID[0xac];
	ParticleSystemID m_systemID;

};

ParticleSystem *emptyParticleSystem(void);

class ParticleSystemHandle
{
public:
	operator bool() const
	{
		return m_system != 0;
	}

	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();

	ParticleSystem *operator->() const
	{
		if (m_system == 0)
			return emptyParticleSystem();
		return m_system;
	}

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class BfmeParticleSystemHandle : public ParticleSystemHandle
{
};

class Gen0060C510Target
{
public:
	void adoptParticleSystem(BfmeParticleSystemHandle *handle);

private:
	unsigned char m_beforeParticleSystem[0x14];
	ParticleSystemHandle m_particleSystem;
	ParticleSystemID m_particleSystemID;
};

void Gen0060C510Target::adoptParticleSystem(BfmeParticleSystemHandle *handle)
{
	if (*handle)
	{
		m_particleSystem = *handle;
		m_particleSystemID = m_particleSystem->m_systemID;
	}
}
