// cl: /O2
// Open-BFME: ParticleSystem::setSystemLifetime, retail 0x005BE2E0
// (13 bytes).  The retail body stores its sole UnsignedInt argument at
// ParticleSystem+0x1A0.  The authentic ParticleSys.h declaration and the
// recovered BFME field layout identify that slot as m_systemLifetimeLeft.

typedef unsigned int UnsignedInt;

class ParticleSystem
{
public:
	void setSystemLifetime(UnsignedInt frames);

private:
	unsigned char m_beforeSystemLifetimeLeft[0x1A0];
	UnsignedInt m_systemLifetimeLeft;
};

void ParticleSystem::setSystemLifetime(UnsignedInt frames)
{
	m_systemLifetimeLeft = frames;
}
