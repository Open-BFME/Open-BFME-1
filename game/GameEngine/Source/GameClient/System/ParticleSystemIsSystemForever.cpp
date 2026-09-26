// cl: /O2
// Open-BFME: ParticleSystem::isSystemForever, retail 0x00336560 (7 bytes).
// ParticleSys.h declares this exact const accessor.  The recovered BFME flag
// cluster places m_isForever at +0x1A6, immediately before the exact stopped
// and destroyed fields at +0x1A7/+0x1A8.  This byte pattern occurs only once
// in the retail image.

typedef bool Bool;

class ParticleSystem
{
public:
	Bool isSystemForever() const;

private:
	unsigned char m_beforeIsForever[0x1A6];
	Bool m_isForever;
};

Bool ParticleSystem::isSystemForever() const
{
	return m_isForever;
}
