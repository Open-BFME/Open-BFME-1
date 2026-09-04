// ?tossEmitters@W3DTankDraw@@IAEXXZ
// partial score=0.5 date=2026-09-04
// candidate based on the matched BFME particle-system handle and ILT pins
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS

class Object;

class ParticleSystem
{
public:
	void attachToObject(const Object *object);
	void destroy(void);
};

ParticleSystem *emptyParticleSystem(void);

class ParticleSystemFieldClearShim
{
public:
	void clear(void);

	ParticleSystem *m_system;
	ParticleSystemFieldClearShim *m_previous;
	ParticleSystemFieldClearShim *m_next;
};

class W3DTankDraw
{
private:
	void *m_vtable;
	void *m_moduleData;
	void *m_drawable;
	unsigned char m_unreconstructed00c[0x27c - 0x00c];

protected:
	class ParticleSystemHandle : public ParticleSystemFieldClearShim
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

	ParticleSystemHandle m_treadDebrisLeft;
	ParticleSystemHandle m_treadDebrisRight;

	void tossEmitters(void);
};

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
