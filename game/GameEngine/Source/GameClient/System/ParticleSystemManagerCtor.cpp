// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ParticleSystemManager constructor, retail 0x005CBF60 (224 bytes).
// The retail vtable string at 0x0110FE14 names FXParticleSystemManager.

#include <hash_map>
#include <list>
#include <vector>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void postProcessLoad() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() {}

private:
	void *m_name;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(void *) = 0;
	virtual void xfer(void *) = 0;
	virtual void loadPostProcess() = 0;
};

class ParticleSystem;
class ParticleSystemTemplate;

struct BfmeParticleSystemHandle
{
	void *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

namespace rts
{
	template <class T> struct hash {};
}

#include "ascii_string.h"

typedef std::hash_map<AsciiString, ParticleSystemTemplate *, rts::hash<AsciiString>,
	std::equal_to<AsciiString> > ParticleTemplateMap;
typedef std::list<BfmeParticleSystemHandle> ParticleSystemList;

class ParticleSystemManager : public SubsystemInterface, public Snapshot
{
public:
	ParticleSystemManager();
	virtual ~ParticleSystemManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual int getOnScreenParticleCount() = 0;
	virtual void setOnScreenParticleCount(int count);
	virtual void doParticles(void *) = 0;
	virtual void queueParticleRender() = 0;
	virtual void preloadAssets(int timeOfDay);

protected:
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();

	void *m_allParticlesHead[14];
	void *m_allParticlesTail[14];
	unsigned int m_uniqueSystemID;
	ParticleSystemList m_allParticleSystemList;
	unsigned int m_particleCount;
	unsigned int m_fieldParticleCount;
	unsigned int m_particleSystemCount;
	int m_onScreenParticleCount;
	unsigned int m_lastLogicFrameUpdate;
	int m_localPlayerIndex;
	ParticleTemplateMap m_templateMap;
	std::vector<void *> m_bfmeTemplateList;
};

ParticleSystemManager::ParticleSystemManager()
{
	m_uniqueSystemID = 0;
	m_onScreenParticleCount = 0;
	m_localPlayerIndex = 0;
	m_particleCount = 0;
	m_fieldParticleCount = 0;
	m_particleSystemCount = 0;
	m_lastLogicFrameUpdate = 0;

	for (int i = 0; i < 14; ++i)
	{
		m_allParticlesHead[i] = 0;
		m_allParticlesTail[i] = 0;
	}
}
