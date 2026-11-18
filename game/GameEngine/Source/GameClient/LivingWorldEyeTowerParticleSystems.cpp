// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class ParticleSystem;
// The null-system accessor (ILT 0x00001B18 -> 0x005CFF50) is defined only as
// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ; its real name is unproven.
class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();
#include "../../Include/Common/ScalarTypes.h"

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
			return (ParticleSystem *)bfmeNullSystemZA();
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

class LivingWorldEyeTower
{
public:
	void startParticleSystems();
	void stopParticleSystems();

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

// ?stopParticleSystems@LivingWorldEyeTower@@QAEXXZ
void LivingWorldEyeTower::stopParticleSystems()
{
	if( m_particleSystem )
	{
		if( m_particleSystem->getSlave() )
			m_particleSystem->getSlave()->stop();
		m_particleSystem->stop();
	}
}

