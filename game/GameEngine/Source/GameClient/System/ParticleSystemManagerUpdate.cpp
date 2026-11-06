// ?update005C37E0@ParticleSystemManager@@UAEXXZ
// cl: /DNDEBUG /MD /EHsc
// ParticleSystemManager::update, retail 0x005C37E0, 467 B (vtable slot 5 of
// ParticleSystemManager 0x0110FDCC and W3DParticleSystemManager 0x0112039C).
// The method name keeps the address: retail's ILT contradicts every
// ?...@ParticleSystemManager@@ decoration (tools/ilt_oracle.py), so the class's
// retail spelling is unknown (same convention as doParticles006FA9B0).
// Zero Hour ParticleSys.cpp:2928 loop (including its `continue` without ++it)
// over BFME's weak BfmeParticleSystemHandle list (layout from the matched
// ParticleSystemManagerReset.cpp), plus QueryPerformanceCounter timing written
// like the matched sibling ParticleSystem::update (ParticleSystemUpdate.cpp,
// 0x005D1140): __int64 counters and `(Real)(end - start) * 1000.0f / (Real)frequency`.
// The handle destructor is an inline definition that VC7.1 keeps out of line
// (its COMDAT reproduces retail 0x001DA440, reached through ILT 0x00013994);
// with its body visible the compiler packs the int64->fild temporary into the
// dead `start` slot exactly as retail does and omits the state -1 store.
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter( __int64 *count );
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency( __int64 *frequency );

class GlobalData
{
public:
	unsigned char m_unmodelled_000[0xA91];
	Bool m_enableFrameTiming;			// +0xA91
};
extern GlobalData *TheWritableGlobalData;

class GameClient
{
public:
	unsigned char m_unmodelled_000[0xC4];
	Bool m_clientFlag;						// +0xC4
};
extern GameClient *TheGameClient;

class GameLogic
{
public:
	unsigned char m_unmodelled_000[0x11D];
	Bool m_gameLogicFlag;						// +0x11D
};
extern GameLogic *TheGameLogic;

struct BfmeParticleSystemHandle;

class ParticleSystem
{
public:
	virtual ~ParticleSystem();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool update(int localPlayerIndex);	// +0x10

	unsigned char m_unmodelled_004[0x94 - 4];
	int m_needsUpdate;					// +0x94
	BfmeParticleSystemHandle *m_handleHead;	// +0x98
	BfmeParticleSystemHandle *m_handleTail;	// +0x9C
};

struct BfmeParticleSystemHandle
{
	BfmeParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) {}
	~BfmeParticleSystemHandle()
	{
		if (m_system)
		{
			if (m_previous)
				m_previous->m_next = m_next;
			else
				m_system->m_handleHead = m_next;
			if (m_next)
				m_next->m_previous = m_previous;
			else
				m_system->m_handleTail = m_previous;
			m_previous = 0;
			m_next = 0;
		}
	}
	__forceinline BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other)
	{
		if (this != &other)
		{
			if (m_system)
			{
				if (m_previous)
					m_previous->m_next = m_next;
				else
					m_system->m_handleHead = m_next;
				if (m_next)
					m_next->m_previous = m_previous;
				else
					m_system->m_handleTail = m_previous;
				m_previous = 0;
				m_next = 0;
			}
			m_system = other.m_system;
			if (m_system)
			{
				m_previous = m_system->m_handleTail;
				m_next = 0;
				m_system->m_handleTail = this;
				if (m_previous)
					m_previous->m_next = this;
				else
					m_system->m_handleHead = this;
			}
		}
		return *this;
	}
	ParticleSystem *operator->() const { return m_system; }

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

struct BfmeParticleSystemNode
{
	BfmeParticleSystemNode *m_next;
	BfmeParticleSystemNode *m_previous;
	BfmeParticleSystemHandle m_value;
};

struct BfmeParticleSystemList
{
	BfmeParticleSystemNode *m_node;
};

class ParticleSystemManager
{
public:
	virtual void update005C37E0();

private:
	unsigned char m_unmodelled_004[0x08];
	ParticleSystem *m_allParticlesHead[14];
	ParticleSystem *m_allParticlesTail[14];
	unsigned int m_uniqueSystemID;
	BfmeParticleSystemList m_allParticleSystemList;	// +0x80
	unsigned int m_particleCount;
	unsigned int m_fieldParticleCount;
	unsigned int m_particleSystemCount;
	int m_onScreenParticleCount;
	Real m_lastUpdateMilliseconds;					// +0x94
	int m_localPlayerIndex;					// +0x98
};

void ParticleSystemManager::update005C37E0()
{
	__int64 frequency;
	__int64 start;
	__int64 end;
	m_lastUpdateMilliseconds = 0;
	if (TheWritableGlobalData->m_enableFrameTiming)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&start);
	}

	BfmeParticleSystemHandle sys;
	Bool skipUpdate = TheGameClient->m_clientFlag && !TheGameLogic->m_gameLogicFlag;

	for (BfmeParticleSystemNode *it = m_allParticleSystemList.m_node->m_next;
		it != m_allParticleSystemList.m_node;)
	{
		sys = it->m_value;
		if (!sys.m_system)
			continue;

		if (sys->m_needsUpdate || skipUpdate)
		{
			if (sys->update(m_localPlayerIndex) == false)
			{
				it = it->m_next;
				delete sys.m_system;
				continue;
			}
		}
		it = it->m_next;
	}

	if (TheWritableGlobalData->m_enableFrameTiming)
	{
		QueryPerformanceCounter(&end);
		m_lastUpdateMilliseconds = (Real)( end - start ) * 1000.0f / (Real)frequency;
	}
}
