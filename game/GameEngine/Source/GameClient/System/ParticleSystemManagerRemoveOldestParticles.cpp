// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ParticleSystemManager::removeOldestParticles, retail
// 0x005BE770 (95 bytes). The public ILT at 0x00008B0C routes here.

typedef int Int;
typedef unsigned int UnsignedInt;

enum ParticlePriorityType
{
	PARTICLE_PRIORITY_NONE = 0,
	PARTICLE_PRIORITY_LOWEST = 1
};

class Particle
{
public:
	virtual ~Particle();
};

class ParticleSystemManager
{
public:
	Int removeOldestParticles(UnsignedInt count, ParticlePriorityType priorityCap);

private:
	unsigned char m_unmodelled_000[0x0C];
	Particle *m_allParticlesHead[14];
	Particle *m_allParticlesTail[14];
	unsigned int m_uniqueSystemID;
	void *m_allParticleSystemList;
	UnsignedInt m_particleCount;
};

Int ParticleSystemManager::removeOldestParticles(
	UnsignedInt count, ParticlePriorityType priorityCap)
{
	Int countToRemove = count;

	while (count-- && m_particleCount)
	{
		for (Int i = PARTICLE_PRIORITY_LOWEST; i < priorityCap; ++i)
		{
			if (m_allParticlesHead[i])
			{
				delete m_allParticlesHead[i];
				break;
			}
		}
	}

	return countToRemove - count;
}
