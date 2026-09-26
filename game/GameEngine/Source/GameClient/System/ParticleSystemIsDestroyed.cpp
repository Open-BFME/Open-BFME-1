// cl: /O2
// Open-BFME: ParticleSystem::isDestroyed, retail 0x005BD500 (7 bytes).
// ParticleSys.h declares this exact const accessor.  The recovered BFME
// ParticleSystem layout places m_isDestroyed at +0x1A8, where the authentic
// destroy() body at 0x005C1FB0 writes it before walking the slave chain.

typedef bool Bool;

class ParticleSystem
{
public:
	Bool isDestroyed() const;

private:
	unsigned char m_beforeIsDestroyed[0x1A8];
	Bool m_isDestroyed;
};

Bool ParticleSystem::isDestroyed() const
{
	return m_isDestroyed;
}
