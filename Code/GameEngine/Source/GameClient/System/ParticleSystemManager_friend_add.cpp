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
	unsigned char m_beforeSystemID[0x58 - 0x44];
	UnsignedInt m_systemID;
	unsigned char m_beforeInSystemList[0x79 - 0x5C];
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
	unsigned char m_beforeUniqueSystemID[0x130 - 0xAC];
	UnsignedInt m_uniqueSystemID;

public:
	void friend_addParticleSystem(ParticleSystem *particleSystemToAdd);
};

void ParticleSystemManager::friend_addParticleSystem(ParticleSystem *particleSystemToAdd)
{
	if (particleSystemToAdd->m_inSystemList)
		return;

	if (m_systemListHead == 0)
		m_systemListHead = particleSystemToAdd;

	if (m_systemListTail != 0) {
		m_systemListTail->m_systemNext = particleSystemToAdd;
		particleSystemToAdd->m_systemPrev = m_systemListTail;
	} else {
		particleSystemToAdd->m_systemPrev = 0;
	}

	m_systemListTail = particleSystemToAdd;
	particleSystemToAdd->m_systemNext = 0;
	particleSystemToAdd->m_inSystemList = true;
	++m_particleSystemCount;
	UnsignedInt id = m_uniqueSystemID;
	UnsignedInt nextID = id + 1;
	m_uniqueSystemID = nextID;
	particleSystemToAdd->m_systemID = id;
}
