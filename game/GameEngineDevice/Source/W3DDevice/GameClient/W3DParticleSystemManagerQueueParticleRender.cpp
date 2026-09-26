// cl: /O2
// Open-BFME: W3DParticleSystemManager::queueParticleRender,
// retail 0x006FA030 (8 bytes).  Retail vtable slot 0x011203D0 routes
// through ILT 0x00409D22 to this body.  The adjacent doParticles body at
// 0x006FA9B0 tests and clears the same ready-to-render byte at +0xBC.

typedef bool Bool;

class W3DParticleSystemManager
{
public:
	virtual void queueParticleRender();

private:
	unsigned char m_beforeReadyToRender[0xBC - sizeof(void *)];
	Bool m_readyToRender;
};

void W3DParticleSystemManager::queueParticleRender()
{
	m_readyToRender = true;
}
