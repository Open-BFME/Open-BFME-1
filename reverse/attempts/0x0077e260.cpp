// ?stopMoveDebris@W3DTankDraw@@IAEXXZ
// partial score=0.5 date=2026-09-04
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS

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

class TankParticleSystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_testTarget;
	}

	ParticleSystem *operator->(void) const
	{
		ParticleSystem *volatile target = m_target;
		if (!target)
			target = emptyParticleSystem();
		return target;
	}

private:
	union
	{
		ParticleSystem *m_testTarget;
		ParticleSystem *m_target;
	};
};

class W3DTankDraw
{
private:
	void *m_vtable;
	void *m_moduleData;
	Drawable *m_drawable;
	unsigned char m_unreconstructed00c[0x27c - 0x00c];
	TankParticleSystemPtr m_treadDebrisLeft;
	unsigned char m_unreconstructed280[0x288 - 0x280];
	TankParticleSystemPtr m_treadDebrisRight;

protected:
	void startMoveDebris(void);
	void stopMoveDebris(void);
};

void W3DTankDraw::startMoveDebris(void)
{
	if (m_drawable->isDrawableEffectivelyHidden())
		return;
	if (m_treadDebrisLeft)
		m_treadDebrisLeft->start();
	if (m_treadDebrisRight)
		m_treadDebrisRight->start();
}

void W3DTankDraw::stopMoveDebris(void)
{
	if (m_treadDebrisLeft)
		m_treadDebrisLeft->stop();
	if (m_treadDebrisRight)
		m_treadDebrisRight->stop();
}
