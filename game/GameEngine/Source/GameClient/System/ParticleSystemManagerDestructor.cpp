// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stlp_nodealloc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ParticleSystemManager destructor, retail 0x005CB360 (402 bytes).
// The vtable group at 0x0110FDCC and the FXParticleSystemManager string identify the class.

#include <hash_map>
#include <list>
#include <vector>

#include "Common/AsciiString.h"

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
	AsciiString m_name;
};

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

struct BfmeParticleSystemHandle;

class ParticleSystem
{
public:
	unsigned char m_reserved[0x98];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
};

struct BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(ParticleSystem *system = 0) :
		m_system(system), m_previous(0), m_next(0) {}
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that);
	~BfmeParticleSystemHandle() throw();

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

#define BFME_PARTICLE_SYSTEM_HANDLE_DESTRUCTOR BfmeParticleSystemHandle::~BfmeParticleSystemHandle
inline BFME_PARTICLE_SYSTEM_HANDLE_DESTRUCTOR()
{
	if (m_system)
	{
		if (m_previous)
			m_previous->m_next = m_next;
		else
			m_system->m_firstHandle = m_next;
		if (m_next)
			m_next->m_previous = m_previous;
		else
			m_system->m_lastHandle = m_previous;
		m_previous = 0;
		m_next = 0;
	}
}
#undef BFME_PARTICLE_SYSTEM_HANDLE_DESTRUCTOR

class ParticleSystemTemplate
{
public:
	virtual ~ParticleSystemTemplate() {}

	void deleteInstance()
	{
		delete this;
	}
};

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(const T &) const;
	};
	template <> struct hash<AsciiString>
	{
		size_t operator()(AsciiString string) const
		{
			std::hash<const char *> hashString;
			return hashString(string.str());
		}
	};
	template <class T> struct equal_to
	{
		bool operator()(const T &, const T &) const;
	};
}

typedef std::hash_map<AsciiString, ParticleSystemTemplate *, rts::hash<AsciiString>,
	rts::equal_to<AsciiString> > TemplateMap;
typedef std::list<BfmeParticleSystemHandle> ParticleSystemList;

class ParticleSystemManager : public SubsystemInterface, public Snapshot
{
public:
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
	TemplateMap m_templateMap;
	std::vector<void *> m_bfmeTemplateList;
};

ParticleSystemManager::~ParticleSystemManager()
{
	reset();

	TemplateMap::iterator begin(m_templateMap.begin());
	TemplateMap::iterator end(m_templateMap.end());
	for (; begin != end; ++begin) {
		(*begin).second->deleteInstance();
	}
}
