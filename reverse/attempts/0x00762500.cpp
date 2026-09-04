// ?updateSubObjectsFromShroud@W3DModelDraw@@AAEXXZ
// partial score=0.88 date=2026-09-03
// cl: /DNDEBUG /MD /GX /O2
// Open-BFME5: W3DModelDraw::updateSubObjectsFromShroud, retail 0x00762500.
// Walks the particle-system ID list at +0x48; for each ID looks up a handle,
// stamps ParticleSystem+0x1A7 from (drawable-hidden || fullyObscured), then
// the handle destructor unlinks. Named by setHidden / setFullyObscuredByShroud.

typedef int ParticleSystemID;

class Drawable
{
public:
	bool isDrawableEffectivelyHidden() const;	// ILT 0x00012E3B
};

class ParticleSystem
{
public:
	void clearShroudHidden();	// ILT 0x0000FFD3 -> Rva005BDD90 (+0x1A7 = 0)
	void setShroudHidden();		// ILT 0x00013075 -> Rva005BDDA0 (+0x1A7 = 1)

	unsigned char m_pad00[0x98];
	void *m_firstHandle;
	void *m_lastHandle;
};

// Same handle model as ParticleSystemManager_destroyByID.cpp: copy is
// declare-only (find constructs into the return slot); dtor is defined here
// so this body inlines the unlink the way retail does.
class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that);
	~BfmeParticleSystemHandle();

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id); // ILT 0x0002A216
};

extern ParticleSystemManager *TheParticleSystemManager;

struct BfmeParticleIdNode
{
	BfmeParticleIdNode *m_next;
	BfmeParticleIdNode *m_prev;
	ParticleSystemID m_id;
};

class W3DModelDraw
{
private:
	void updateSubObjectsFromShroud();

	unsigned char m_pad00[8];
	Drawable *m_drawable;					// +0x08
	unsigned char m_pad0c[0x2d - 0x0c];
	unsigned char m_fullyObscuredByShroud;	// +0x2d
	unsigned char m_pad2e[0x48 - 0x2e];
	BfmeParticleIdNode *m_particleIdList;	// +0x48 sentinel
};

BfmeParticleSystemHandle::~BfmeParticleSystemHandle()
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

// ?updateSubObjectsFromShroud@W3DModelDraw@@AAEXXZ
void W3DModelDraw::updateSubObjectsFromShroud()
{
	W3DModelDraw *self = this;
	unsigned char hidden;
	if (self->m_drawable->isDrawableEffectivelyHidden())
		hidden = 1;
	else
	{
		hidden = 0;
		if (self->m_fullyObscuredByShroud)
			hidden = 1;
	}

	BfmeParticleIdNode *sent = self->m_particleIdList;
	for (BfmeParticleIdNode *node = sent->m_next; node != sent; node = node->m_next)
	{
		BfmeParticleSystemHandle handle =
			TheParticleSystemManager->findParticleSystemByID(node->m_id);
		if (handle.m_system)
		{
			if (hidden)
				handle.m_system->setShroudHidden();
			else
				handle.m_system->clearShroudHidden();
		}
	}
}
