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
	void stop();
	ParticleSystemHandle getSlave();
};

// Address-qualified owner: constructor 0x0060BEB0 installs vtable 0x01115E90.
// Slots 8/9 reach 0x0060C140/0x0060C160, which call these methods without
// adjusting ECX. No constructor, RTTI, literal or named caller establishes
// the former LivingWorldEyeTowerSecondaryState label. This view is limited
// to the particle handle at +0x14; the constructor keeps its own ABI view.

class Rva0060BEB0Object
{
public:
	void startParticleSystems();
	void stopParticleSystems();

private:
	unsigned char m_unmodelled00[ 0x14 ];
	ParticleSystemHandle m_particleSystem;
};

// ?startParticleSystems@Rva0060BEB0Object@@QAEXXZ
void Rva0060BEB0Object::startParticleSystems()
{
	if( m_particleSystem )
	{
		m_particleSystem->start();
		if( m_particleSystem->getSlave() )
			m_particleSystem->getSlave()->start();
	}
}

// ?stopParticleSystems@Rva0060BEB0Object@@QAEXXZ
void Rva0060BEB0Object::stopParticleSystems()
{
	if( m_particleSystem )
	{
		if( m_particleSystem->getSlave() )
			m_particleSystem->getSlave()->stop();
		m_particleSystem->stop();
	}
}
