// cl: /O2
// Open-BFME: ParticleSystem::getStartFrame, retail 0x005BD540 (7 bytes).
// ParticleSys.h declares this exact accessor for m_startTimestamp.  In the
// recovered BFME layout that dword is at +0x19C, immediately before the exact
// m_systemLifetimeLeft setter at +0x1A0.

typedef unsigned int UnsignedInt;

class ParticleSystem
{
public:
	UnsignedInt getStartFrame();

private:
	unsigned char m_beforeStartTimestamp[0x19C];
	UnsignedInt m_startTimestamp;
};

UnsignedInt ParticleSystem::getStartFrame()
{
	return m_startTimestamp;
}
