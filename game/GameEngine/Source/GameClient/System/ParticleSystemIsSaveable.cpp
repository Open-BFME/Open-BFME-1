// cl: /O2
// Open-BFME: ParticleSystem::isSaveable, retail 0x005BD510 (7 bytes).
// ParticleSys.h declares this exact const accessor.  The recovered BFME
// ParticleSystem layout and the exact setSaveable body at 0x005C1F60 agree
// that m_isSaveable is the byte at +0x1AA.

typedef bool Bool;

class ParticleSystem
{
public:
	Bool isSaveable() const;

private:
	unsigned char m_beforeIsSaveable[0x1AA];
	Bool m_isSaveable;
};

Bool ParticleSystem::isSaveable() const
{
	return m_isSaveable;
}
