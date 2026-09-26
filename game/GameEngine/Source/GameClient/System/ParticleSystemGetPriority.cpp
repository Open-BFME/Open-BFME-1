// cl: /O2
// Open-BFME: ParticleSystem::getPriority, retail 0x005BD580 (4 bytes).
// ParticleSys.h declares this exact const accessor.  The existing exact BFME
// ParticleSystem transfer body independently serializes the priority dword at
// +0x7C, which is the field this previously unclaimed body returns.

enum ParticlePriorityType
{
	PARTICLE_PRIORITY_NONE = 0
};

class ParticleSystem
{
public:
	ParticlePriorityType getPriority() const;

private:
	unsigned char m_beforePriority[0x7C];
	ParticlePriorityType m_priority;
};

ParticlePriorityType ParticleSystem::getPriority() const
{
	return m_priority;
}
