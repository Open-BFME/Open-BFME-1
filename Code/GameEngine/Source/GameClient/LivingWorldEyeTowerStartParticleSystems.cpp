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
	void start();
	ParticleSystemHandle getSlave();
};

class LivingWorldEyeTower
{
public:
	void startParticleSystems();

private:
	unsigned char m_unmodelled00[ 0x14 ];
	ParticleSystemHandle m_particleSystem;
};

// ?startParticleSystems@LivingWorldEyeTower@@QAEXXZ
void LivingWorldEyeTower::startParticleSystems()
{
	if( m_particleSystem )
	{
		m_particleSystem->start();
		if( m_particleSystem->getSlave() )
			m_particleSystem->getSlave()->start();
	}
}
