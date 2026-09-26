// cl: /O2
// Open-BFME: ParticleSystem::stop, retail 0x005BDDA0 (8 bytes).
// Identity: the reviewed ILT at 0x00013075 targets this body, and the hidden
// updateSubObjectsFromShroud arm calls it when particle emission must stop.

class ParticleSystem
{
public:
	void stop();

private:
	unsigned char m_beforeIsStopped[0x1A7];
	bool m_isStopped;
};

void ParticleSystem::stop()
{
	m_isStopped = true;
}
