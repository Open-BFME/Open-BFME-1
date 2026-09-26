// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// The three W3DTankDraw bodies that drive its two tread-debris emitters:
//
//   startMoveDebris  0x0077E1F0   start both, unless the drawable is hidden
//   stopMoveDebris               stop both
//   tossEmitters     0x0077EBA0   detach, destroy and clear both
//
// Three files, three handle models for the same two members at +0x27c. The
// difference was not cosmetic and the pins decide it: the handle's clear() is
// pinned as ?clear@ParticleSystemFieldClearShim@@QAEXXZ at the ILT thunk
// 0x00015640, and tossEmitters is the body that calls it, so that is the name
// the base keeps. The other two files put the same storage on a U1Sub base
// whose apply() they only declared and never called -- nothing pins it from
// here, so it goes.
//
// The null-object callee is one function under three pinned spellings, all at
// 0x00001B18: ?emptyParticleSystem@@YAPAVParticleSystem@@XZ,
// ?Make00001B18@@YAPAVParticleSystem@@XZ and ?Make00001B18@@YAPAVGen00001B18@@XZ.
// Since all three resolve to the same address, the merged file can use one --
// and does.

class Object;

class Drawable
{
public:
	bool isDrawableEffectivelyHidden(void) const;
};

class ParticleSystem
{
public:
	void start(void);
	void stop(void);
	void attachToObject(const Object *object);
	void destroy(void);
};

ParticleSystem *emptyParticleSystem(void);

// The tracked handle's storage and its field-clear helper. The class name is
// load-bearing: clear() is pinned under it.
class ParticleSystemFieldClearShim
{
public:
	void clear(void);

	ParticleSystem *m_system;
	ParticleSystemFieldClearShim *m_previous;
	ParticleSystemFieldClearShim *m_next;
};

class TankParticleSystemPtr : public ParticleSystemFieldClearShim
{
public:
	operator bool(void) const
	{
		return m_system != 0;
	}

	ParticleSystem *operator->(void) const
	{
		if (!m_system)
			return emptyParticleSystem();
		return m_system;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTankDraw.h
class W3DTankDraw
{
private:
	void *m_vtable;
	void *m_moduleData;
	Drawable *m_drawable;
	unsigned char m_unreconstructed00c[0x27c - 0x00c];
	TankParticleSystemPtr m_treadDebrisLeft;		// +0x27c
	TankParticleSystemPtr m_treadDebrisRight;

protected:
	void startMoveDebris(void);
	void stopMoveDebris(void);
	void tossEmitters(void);
};

// ?startMoveDebris@W3DTankDraw@@IAEXXZ 0x0077E1F0
void W3DTankDraw::startMoveDebris(void)
{
	if (m_drawable->isDrawableEffectivelyHidden())
		return;
	if (m_treadDebrisLeft)
		m_treadDebrisLeft->start();
	if (m_treadDebrisRight)
		m_treadDebrisRight->start();
}

// ?stopMoveDebris@W3DTankDraw@@IAEXXZ 0x0077E260
void W3DTankDraw::stopMoveDebris(void)
{
	if (m_treadDebrisLeft)
		m_treadDebrisLeft->stop();
	if (m_treadDebrisRight)
		m_treadDebrisRight->stop();
}

// ?tossEmitters@W3DTankDraw@@IAEXXZ 0x0077EBA0
void W3DTankDraw::tossEmitters(void)
{
	if (m_treadDebrisLeft)
	{
		m_treadDebrisLeft->attachToObject(0);
		m_treadDebrisLeft->destroy();
		m_treadDebrisLeft.clear();
	}
	if (m_treadDebrisRight)
	{
		m_treadDebrisRight->attachToObject(0);
		m_treadDebrisRight->destroy();
		m_treadDebrisRight.clear();
	}
}
