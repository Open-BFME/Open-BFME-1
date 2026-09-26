// cl: /O2
// Open-BFME: ParticleSystemManager::GetSnapshotName, retail 0x005CB570
// (6 bytes).  Both ParticleSystemManager secondary vtables use this slot.

class ParticleSystemManager
{
public:
	virtual const char *GetSnapshotName();
};

const char *ParticleSystemManager::GetSnapshotName()
{
	return "FXParticleSystemManager";
}
