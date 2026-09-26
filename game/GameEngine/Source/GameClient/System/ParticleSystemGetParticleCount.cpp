// cl: /O2
// Open-BFME: ParticleSystem::getParticleCount, retail 0x005BD550
// (7 bytes).  The authentic ParticleSys.h accessor returns m_particleCount;
// exact BFME createParticle/addParticle/removeParticle bodies independently
// establish that per-system counter at +0xA8.

typedef unsigned int UnsignedInt;

class ParticleSystem
{
public:
	UnsignedInt getParticleCount() const;

private:
	unsigned char m_beforeParticleCount[0xA8];
	UnsignedInt m_particleCount;
};

UnsignedInt ParticleSystem::getParticleCount() const
{
	return m_particleCount;
}
