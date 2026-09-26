// cl: /O2
// Open-BFME: ParticleSystem::setSkipParentXfrm, retail 0x005BE120
// (13 bytes).  The sole named caller is W3DModelDraw's exact
// updateBonesForClientParticleSystems body at 0x00762F40, immediately after it
// updates the system's position and local transform.  BFME stores the flag at
// +0x1AC.

class ParticleSystem
{
public:
	void setSkipParentXfrm(bool enable);

private:
	unsigned char m_beforeSkipParentXfrm[0x1AC];
	bool m_skipParentXfrm;
};

void ParticleSystem::setSkipParentXfrm(bool enable)
{
	m_skipParentXfrm = enable;
}
