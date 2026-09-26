// cl: /O2
// Open-BFME: W3DParticleSystemManager::getOnScreenParticleCount,
// retail 0x006FA6D0 (7 bytes).  Retail vtable slot 0x011203C0 routes
// through ILT 0x0041A708 to this body; the adjacent retail source-path
// string names W3DFXParticleSystem.cpp.  The base-manager layout fixes the
// inherited on-screen particle counter at +0x90.

typedef int Int;

class W3DParticleSystemManager
{
public:
	virtual Int getOnScreenParticleCount();

private:
	unsigned char m_beforeOnScreenParticleCount[0x90 - sizeof(void *)];
	Int m_onScreenParticleCount;
};

Int W3DParticleSystemManager::getOnScreenParticleCount()
{
	return m_onScreenParticleCount;
}
