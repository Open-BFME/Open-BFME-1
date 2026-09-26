// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB
// stlport
// W3DModelDraw::updateSubObjectsFromShroud — retail 0x00762500 (244B).
//
// Zero Hour's doStartOrStopParticleSys: hidden =
// getDrawable()->isDrawableEffectivelyHidden() || m_fullyObscuredByShroud,
// then start/stop every tracked particle system. BFME stores the IDs in a
// STLport list at this+0x48 (pointer-to-sentinel _M_node) and looks each
// one up through ParticleSystemManager::findParticleSystemByID, which
// returns a 12-byte handle by value. The handle destructor unlinks from
// ParticleSystem +0x98/+0x9C (same shape as ParticleSystemHandleListClear).
//
// Callers already matched: setFullyObscuredByShroud @0x007628C0 and
// setHidden @0x00762640. Callees: isDrawableEffectivelyHidden ILT 0x00012E3B,
// findParticleSystemByID ILT 0x0002A216, start ILT 0x0000FFD3 (body
// 0x005BDD90 writes [this+0x1A7]=0), stop ILT 0x00013075 (body 0x005BDDA0
// writes [this+0x1A7]=1). Manager global at 0x00EF64BC.

#define _STLP_USE_NEWALLOC 1
#include <list>

typedef bool Bool;

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

class Drawable
{
public:
	Bool isDrawableEffectivelyHidden() const;	// ILT 0x00012E3B
};

class ParticleSystem
{
public:
	void start(void);							// ILT 0x0000FFD3
	void stop(void);							// ILT 0x00013075

	unsigned char m_pad[0x98];
	class BfmeParticleSystemHandle *m_firstHandle;
	class BfmeParticleSystemHandle *m_lastHandle;
};

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle()
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

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystemManager
{
	friend class W3DModelDraw;
private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);	// ILT 0x0002A216
};

extern ParticleSystemManager *TheParticleSystemManager;

class W3DModelDraw
{
private:
	void updateSubObjectsFromShroud(void);

	unsigned char m_pad00[8];
	Drawable *m_drawable;						// +0x08
	unsigned char m_pad0C[0x2D - 0x0C];
	Bool m_fullyObscuredByShroud;				// +0x2D
	unsigned char m_pad2E[0x48 - 0x2E];
	_STL::list<ParticleSystemID> m_particleSystemIDs;	// +0x48
};

void W3DModelDraw::updateSubObjectsFromShroud()
{
	Bool hidden = m_drawable->isDrawableEffectivelyHidden() || m_fullyObscuredByShroud;

	for (_STL::list<ParticleSystemID>::iterator it = m_particleSystemIDs.begin();
		it != m_particleSystemIDs.end(); ++it)
	{
		BfmeParticleSystemHandle sys = TheParticleSystemManager->findParticleSystemByID(*it);
		if (!sys.m_system)
			continue;
		if (hidden)
			sys.m_system->stop();
		else
			sys.m_system->start();
	}
}
