// cl: /O2
// Open-BFME: ParticleSystemManager::LoadPostProcess, retail 0x005CB560
// (1 byte).  This no-op occupies the first Snapshot method slot in both the
// ParticleSystemManager and W3DParticleSystemManager secondary vtables.

class ParticleSystemManager
{
public:
	virtual void LoadPostProcess();
};

void ParticleSystemManager::LoadPostProcess()
{
}
