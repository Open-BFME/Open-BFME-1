// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class ParticleSystem;
ParticleSystem *emptyParticleSystem();
typedef bool Bool;

class ParticleSystemHandle
{
public:
	~ParticleSystemHandle() throw();

	operator Bool() const
	{
		return m_system != 0;
	}

	ParticleSystem *operator->() const
	{
		if( !m_system )
			return emptyParticleSystem();
		return m_system;
	}

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class ParticleSystem
{
public:
	void stop();
	ParticleSystemHandle getSlave();
};

class LivingWorldEyeTowerSecondaryState
{
public:
	void stopParticleSystems();

private:
	unsigned char m_unmodelled00[ 0x14 ];
	ParticleSystemHandle m_particleSystem;
};

// ?stopParticleSystems@LivingWorldEyeTowerSecondaryState@@QAEXXZ
void LivingWorldEyeTowerSecondaryState::stopParticleSystems()
{
	if( m_particleSystem )
	{
		if( m_particleSystem->getSlave() )
			m_particleSystem->getSlave()->stop();
		m_particleSystem->stop();
	}
}
