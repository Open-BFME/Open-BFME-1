// cl: /O2
// Open-BFME: ParticleSystem::start, retail 0x005BDD90 (8 bytes).
// Identity: the reviewed ILT at 0x0000FFD3 targets this body, and the visible
// updateSubObjectsFromShroud arm calls it when the system becomes unhidden.

class ParticleSystem
{
public:
	void start();

private:
	unsigned char m_beforeIsStopped[0x1A7];
	bool m_isStopped;
};

void ParticleSystem::start()
{
	m_isStopped = false;
}
