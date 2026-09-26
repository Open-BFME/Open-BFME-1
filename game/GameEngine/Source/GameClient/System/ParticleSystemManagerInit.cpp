// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ParticleSystemManager::init, retail 0x005BE6C0 (32 bytes).
// The GeneralsMD routine clears the priority lists; BFME then initializes the
// FX module classes instead of loading the legacy ParticleSystem.ini here.

namespace FXParticleSystem
{
	void staticInitModules();
}

class ParticleSystemManager
{
public:
	virtual void init();

private:
	unsigned char m_unmodelled_000[0x08];
	void *m_allParticlesHead[14];
	void *m_allParticlesTail[14];
};

void ParticleSystemManager::init()
{
	for (int i = 0; i < 14; ++i)
	{
		m_allParticlesHead[i] = 0;
		m_allParticlesTail[i] = 0;
	}
	FXParticleSystem::staticInitModules();
}
