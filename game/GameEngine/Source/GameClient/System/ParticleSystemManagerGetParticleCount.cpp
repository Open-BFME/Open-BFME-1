// cl: /O2
// Open-BFME: ParticleSystemManager::getParticleCount, retail 0x00336570
// (7 bytes).  This body sits immediately after ParticleSystem::isSystemForever
// in the ScriptEngine inline-accessor cluster; that source calls both methods.
// Exact manager particle creation/removal code independently fixes the global
// particle-count dword at +0x84.

typedef unsigned int UnsignedInt;

class ParticleSystemManager
{
public:
	UnsignedInt getParticleCount() const;

private:
	unsigned char m_beforeParticleCount[0x84];
	UnsignedInt m_particleCount;
};

UnsignedInt ParticleSystemManager::getParticleCount() const
{
	return m_particleCount;
}
