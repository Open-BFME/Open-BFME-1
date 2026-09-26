// cl: /O2
// Open-BFME: ParticleSystemManager::setOnScreenParticleCount,
// retail 0x005BE6F0 (13 bytes).  The W3D particle-manager vtable slot at
// 0x011203C4 routes through ILT 0x00449D82 to this body.  The exact manager
// constructor/reset layout fixes m_onScreenParticleCount at +0x90.

typedef int Int;

class ParticleSystemManager
{
public:
	virtual void setOnScreenParticleCount(Int count);

private:
	unsigned char m_beforeOnScreenParticleCount[0x90 - sizeof(void *)];
	Int m_onScreenParticleCount;
};

void ParticleSystemManager::setOnScreenParticleCount(Int count)
{
	m_onScreenParticleCount = count;
}
