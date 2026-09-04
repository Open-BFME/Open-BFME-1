// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DTankTruckDraw::tossEmitters.

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

class W3DTankTruckDraw
{
private:
	void *m_vtable;
	unsigned char m_unreconstructed00c[0x280 - 0x004];

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

	ParticleSystemHandle m_dustEffect;
	ParticleSystemHandle m_dirtEffect;
	ParticleSystemHandle m_powerslideEffect;

	protected:
	void tossEmitters(void);
};

// ?tossEmitters@W3DTankTruckDraw@@IAEXXZ 0x0077FD80
void W3DTankTruckDraw::tossEmitters(void)
{
	if (m_dustEffect)
	{
		m_dustEffect->attachToObject(0);
		m_dustEffect->destroy();
		m_dustEffect.clear();
	}
	if (m_dirtEffect)
	{
		m_dirtEffect->attachToObject(0);
		m_dirtEffect->destroy();
		m_dirtEffect.clear();
	}
	if (m_powerslideEffect)
	{
		m_powerslideEffect->attachToObject(0);
		m_powerslideEffect->destroy();
		m_powerslideEffect.clear();
	}
}
