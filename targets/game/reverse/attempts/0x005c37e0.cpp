// ?update@ParticleSystemManager@@UAEXXZ
// partial score=0.26 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// ParticleSystemManager::update, retail 0x005C37E0, 467 bytes. Vtable slot 5
// of both installed ParticleSystemManager (0x0110FDCC) and
// W3DParticleSystemManager (0x0112039C) reaches this body, and it follows
// init (0x005BE6C0) and reset (0x005C3740, ParticleSystemManagerReset.cpp,
// whose class layout this reuses) in slot order.
//
// BFME extends the ZH original (GeneralsMD/.../ParticleSys.cpp
// ParticleSystemManager::update) with: an optional QueryPerformanceCounter
// frame-time measurement gated by TheWritableGlobalData's flag at +0xa91,
// stored as a float at this+0x94 (reset() zeroes the same slot as a plain
// int -- BFME dual-purposes it); a "skip update" gate combining
// TheGameClient+0xc4 and TheBfmeGameLogic+0x11d; and, per particle system
// visited, a stack-resident GenNode_006fa270 guard spliced onto the visited
// ParticleSystem's own owner list at +0x98/+0x9c (the exact class already
// landed in Gen_006fa270.cpp) before the update()/delete dispatch, then
// unlinked once at the very end via the same pinned ?unlink thunk. The
// splice's purpose (guarding the *system's own* field-particle owner list
// while update() may delete particles from it) is inferred from the shape,
// not from a comment or symbol, so the guard's field-particle semantics
// stay address-derived even though its class is a proven, already-landed
// type.

struct GenNode_006fa270;

struct GenOwner_006fa270
{
	char m_pad[0x98];
	GenNode_006fa270 *m_head; // owner + 0x98
	GenNode_006fa270 *m_tail; // owner + 0x9C
};

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner; // +0
	GenNode_006fa270 *m_prev;   // +4
	GenNode_006fa270 *m_next;   // +8

	void unlink(void)
	{
		if (m_owner != 0)
		{
			if (m_prev != 0)
				m_prev->m_next = m_next;
			else
				m_owner->m_head = m_next;

			if (m_next != 0)
				m_next->m_prev = m_prev;
			else
				m_owner->m_tail = m_prev;

			m_prev = 0;
			m_next = 0;
		}
	}

	void setOwner(GenOwner_006fa270 *owner)
	{
		m_owner = owner;
		if (owner != 0)
		{
			m_prev = owner->m_tail;
			m_next = 0;
			owner->m_tail = this;
			if (m_prev != 0)
				m_prev->m_next = this;
			else
				m_owner->m_head = this;
		}
	}

	~GenNode_006fa270(void) { unlink(); }
};

typedef int Bool_;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(UnsignedInt *freq);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(UnsignedInt *counter);

extern const float g_bfmeFrameTimeScale; // retail 0x01075C68

struct Rva006C9270GlobalData
{
	unsigned char m_unmodelled[0xa91];
	bool m_enableFrameTiming;
};
extern Rva006C9270GlobalData *TheWritableGlobalData;

struct ClientRoot4120
{
	unsigned char m_unmodelled[0xc4];
	bool m_clientFlag;
};
extern ClientRoot4120 *TheGameClient;

struct Rva00367E30Logic
{
	unsigned char m_unmodelled[0x11d];
	bool m_gameLogicFlag;
};
extern Rva00367E30Logic *TheBfmeGameLogic;

class ParticleSystem
{
public:
	virtual void deletingDtor(int flag);
	unsigned char m_unmodelled00[0x10];
	virtual bool update(int localPlayerIndex);
	unsigned char m_unmodelled04[0x94 - 0x14];
	int m_needsUpdate; // +0x94, this system's own field, unrelated to the manager's
	unsigned char m_unmodelled98[4];
	GenNode_006fa270 *m_fieldParticleHead; // +0x98
	GenNode_006fa270 *m_fieldParticleTail; // +0x9c
};

struct BfmeParticleSystemHandle
{
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
	virtual void update();

private:
	unsigned char m_unmodelled_004[0x08];
	ParticleSystem *m_allParticlesHead[14];
	ParticleSystem *m_allParticlesTail[14];
	unsigned int m_uniqueSystemID;
	BfmeParticleSystemList m_allParticleSystemList;
	unsigned int m_particleCount;
	unsigned int m_fieldParticleCount;
	unsigned int m_particleSystemCount;
	int m_onScreenParticleCount;
	float m_lastUpdateSeconds; // +0x94, dual-purposed vs reset()'s int zero
	int m_localPlayerIndex;
};

// ?update@ParticleSystemManager@@UAEXXZ
void ParticleSystemManager::update()
{
	UnsignedInt startTime[2] = { 0, 0 };
	UnsignedInt endTime[2] = { 0, 0 };
	UnsignedInt freq[2] = { 0, 0 };

	m_lastUpdateSeconds = 0.0f;

	if (TheWritableGlobalData->m_enableFrameTiming)
	{
		QueryPerformanceFrequency(freq);
		QueryPerformanceCounter(startTime);
	}

	Bool_ skipUpdate = 0;
	if (TheGameClient->m_clientFlag)
	{
		skipUpdate = !TheBfmeGameLogic->m_gameLogicFlag;
	}

	for (BfmeParticleSystemNode *node = m_allParticleSystemList.m_node->m_next;
		node != m_allParticleSystemList.m_node; )
	{
		ParticleSystem *sys = node->m_value.m_system;

		GenNode_006fa270 guard;
		if (sys != 0)
			guard.setOwner((GenOwner_006fa270 *)sys);

		if (sys != 0)
		{
			if (sys->m_needsUpdate == 0)
			{
				if (!skipUpdate)
				{
					if (!sys->update(m_localPlayerIndex))
					{
						ParticleSystem *doomed = sys;
						if (doomed != 0)
							doomed->deletingDtor(1);
					}
				}
			}
		}

		node = node->m_next;
	}

	if (TheWritableGlobalData->m_enableFrameTiming)
	{
		QueryPerformanceCounter(endTime);
		__int64 delta = *(__int64 *)endTime - *(__int64 *)startTime;
		m_lastUpdateSeconds =
			(float)((double)delta * g_bfmeFrameTimeScale / (double)*(__int64 *)freq);
	}
}
