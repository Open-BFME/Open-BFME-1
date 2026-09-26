// cl: /O2
// Open-BFME: SubsystemInterface::postProcessLoad, retail 0x00067930
// (1 byte).  This inherited no-op occupies slot 3 in the BFME subsystem
// vtables, including ParticleSystemManager and W3DParticleSystemManager.

class SubsystemInterface
{
public:
	virtual void postProcessLoad();
};

void SubsystemInterface::postProcessLoad()
{
}
