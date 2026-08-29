// readable body of ?destroy@ParticleSystem@@QAEXXZ: Code/GameEngine/Source/GameClient/System/ParticleSys.cpp
// Tear down the particle-system chain rooted at +0x160.  BFME's pointer
// wrapper supplies the shared lazy-pointer fallback used by the retail body.

class ParticleSystem;

ParticleSystem *Make00001B18(void);

class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_target;
	}

	ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = m_target;
		if (!target)
			target = Make00001B18();
		return target;
	}

private:
	ParticleSystem *m_target;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystem
{
public:
	void destroy(void);

private:
	char m_bfmeState[0x160];
	BfmeParticleSystemPtr m_slaveSystem;			// +0x160
	char m_bfmeGap[0x44];
	unsigned char m_isDestroyed;				// +0x1A8
};

// ?destroy@ParticleSystem@@QAEXXZ
void ParticleSystem::destroy(void)
{
	m_isDestroyed = 1;
	if (m_slaveSystem)
		m_slaveSystem->destroy();
}
