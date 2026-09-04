// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DTankDraw::stopMoveDebris.

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
};

ParticleSystem *emptyParticleSystem(void);

class U1CachedHolder;

class U1Sub
{
public:
	U1Sub &apply(U1CachedHolder *that) throw();

	ParticleSystem *m_system;
	U1Sub *m_previous;
	U1Sub *m_next;
};

class TankParticleSystemPtr : public U1Sub
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

class W3DTankDraw
{
private:
	void *m_vtable;
	void *m_moduleData;
	Drawable *m_drawable;
	unsigned char m_unreconstructed00c[0x27c - 0x00c];
	TankParticleSystemPtr m_treadDebrisLeft;
	TankParticleSystemPtr m_treadDebrisRight;

protected:
	void startMoveDebris(void);
	void stopMoveDebris(void);
};

// ?stopMoveDebris@W3DTankDraw@@IAEXXZ 0x0077E260
void W3DTankDraw::stopMoveDebris(void)
{
	if (m_treadDebrisLeft)
		m_treadDebrisLeft->stop();
	if (m_treadDebrisRight)
		m_treadDebrisRight->stop();
}
