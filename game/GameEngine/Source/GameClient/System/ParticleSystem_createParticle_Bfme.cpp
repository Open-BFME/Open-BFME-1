// cl: /O2 /Ob2 /EHsc
// Open-BFME: ParticleSystem::createParticle, retail 0x005D0040 (344 bytes).

#include <new>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ParticlePriorityType
{
	AREA_EFFECT = 0xB,
	ALWAYS_RENDER = 0xD
};

class GlobalData;
class GameLODManager;
class ParticleSystemManager;
class ParticleSystem;
class ParticleInfo;
class Particle;

extern GlobalData *TheWritableGlobalData;
extern GameLODManager *TheGameLODManager;
extern ParticleSystemManager *TheParticleSystemManager;

struct BfmeCreateParticleGlobalData
{
	unsigned char m_pad00[0xA7F];
	Bool m_useFX;
	unsigned char m_padA80[0xB8C - 0xA80];
	UnsignedInt m_maxParticleCount;
	UnsignedInt m_maxFieldParticleCount;
};

struct BfmeCreateParticleLODManager
{
	unsigned char m_pad00[0x16D0];
	Int m_numParticleGenerations;
	Int m_dynamicParticleSkipMask;
	unsigned char m_padD8[0xC];
	ParticlePriorityType m_minDynamicParticlePriority;
	ParticlePriorityType m_minDynamicParticleSkipPriority;

	inline Bool isParticleSkipped(void)
	{
		return (++m_numParticleGenerations & m_dynamicParticleSkipMask) != m_dynamicParticleSkipMask;
	}

	inline ParticlePriorityType getMinDynamicParticlePriority(void)
	{
		return m_minDynamicParticlePriority;
	}
};

struct BfmeCreateParticleManager
{
	unsigned char m_pad00[0x84];
	UnsignedInt m_particleCount;
	UnsignedInt m_fieldParticleCount;
};

struct BfmeCreateParticleSystem
{
	unsigned char m_pad00[0x80];
	Bool m_isGroundAligned;
	unsigned char m_pad81[0x27];
	UnsignedInt m_particleCount;
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(ParticleSystem *system);
	~BfmeParticleSystemHandle() throw();

private:
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class Particle
{
public:
	Particle(const BfmeParticleSystemHandle &system, const ParticleInfo *info);

private:
	unsigned char m_data[0xB8];
};

class ParticleSystemManager
{
public:
	Int removeOldestParticles(UnsignedInt count, ParticlePriorityType priorityCap);
	inline UnsignedInt getParticleCount(void)
	{
		return reinterpret_cast<BfmeCreateParticleManager *>(this)->m_particleCount;
	}
};

class ParticleSystem
{
protected:
	virtual Particle *createParticle(const ParticleInfo *info,
		ParticlePriorityType priority, Bool forceCreate = false);
};

Particle *ParticleSystem::createParticle(const ParticleInfo *info,
	ParticlePriorityType priority, Bool forceCreate)
{
	if (forceCreate == false)
	{
		if (reinterpret_cast<BfmeCreateParticleGlobalData *>(TheWritableGlobalData)->m_useFX == false)
			return 0;

		if (priority < reinterpret_cast<BfmeCreateParticleLODManager *>(TheGameLODManager)->getMinDynamicParticlePriority() ||
			(priority < reinterpret_cast<BfmeCreateParticleLODManager *>(TheGameLODManager)->m_minDynamicParticleSkipPriority &&
				reinterpret_cast<BfmeCreateParticleLODManager *>(TheGameLODManager)->isParticleSkipped()))
			return 0;

		BfmeCreateParticleSystem *particleSystem =
			reinterpret_cast<BfmeCreateParticleSystem *>(this);
		if (particleSystem->m_particleCount > 0 && priority == AREA_EFFECT &&
			particleSystem->m_isGroundAligned &&
			reinterpret_cast<BfmeCreateParticleManager *>(TheParticleSystemManager)->m_fieldParticleCount >
				reinterpret_cast<BfmeCreateParticleGlobalData *>(TheWritableGlobalData)->m_maxFieldParticleCount)
			return 0;

		if (priority != ALWAYS_RENDER)
		{
			Int numInExcess =
				reinterpret_cast<ParticleSystemManager *>(TheParticleSystemManager)->getParticleCount() -
				reinterpret_cast<BfmeCreateParticleGlobalData *>(TheWritableGlobalData)->m_maxParticleCount;
			if (numInExcess > 0)
			{
				if (TheParticleSystemManager->removeOldestParticles(
					(UnsignedInt)numInExcess, priority) != numInExcess)
					return 0;
			}

			if (reinterpret_cast<BfmeCreateParticleGlobalData *>(TheWritableGlobalData)->m_maxParticleCount == 0)
				return 0;
		}
	}

	return new Particle(BfmeParticleSystemHandle(this), info);
}
