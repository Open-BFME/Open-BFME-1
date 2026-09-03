// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystem
{
private:
	unsigned char m_beforeListLinks[0x3C];
	ParticleSystem *m_systemNext;
	ParticleSystem *m_systemPrev;
	unsigned char m_beforeInSystemList[0x79 - 0x44];
	Bool m_inSystemList;

	friend class ParticleSystemManager;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemManager
{
private:
	unsigned char m_beforeSystemList[0xA0];
	ParticleSystem *m_systemListHead;
	ParticleSystem *m_systemListTail;
	UnsignedInt m_particleSystemCount;

public:
	void friend_removeParticleSystem(ParticleSystem *particleSystemToRemove);
};

void ParticleSystemManager::friend_removeParticleSystem(ParticleSystem *particleSystemToRemove)
{
	if (!particleSystemToRemove->m_inSystemList)
		return;

	if (particleSystemToRemove->m_systemNext != 0)
		particleSystemToRemove->m_systemNext->m_systemPrev = particleSystemToRemove->m_systemPrev;
	if (particleSystemToRemove->m_systemPrev != 0)
		particleSystemToRemove->m_systemPrev->m_systemNext = particleSystemToRemove->m_systemNext;

	if (particleSystemToRemove == m_systemListHead)
		m_systemListHead = particleSystemToRemove->m_systemNext;
	if (particleSystemToRemove == m_systemListTail)
		m_systemListTail = particleSystemToRemove->m_systemPrev;

	particleSystemToRemove->m_systemPrev = 0;
	particleSystemToRemove->m_systemNext = 0;
	particleSystemToRemove->m_inSystemList = false;
	--m_particleSystemCount;
}
