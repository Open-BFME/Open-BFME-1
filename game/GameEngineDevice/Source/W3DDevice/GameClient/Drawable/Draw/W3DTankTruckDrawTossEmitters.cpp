// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DTankTruckDraw::tossEmitters.

class Object;

class ParticleSystem
{
public:
	void attachToObject(const Object *object);
	void destroy(void);
};

// The null-system accessor (ILT 0x00001B18 -> 0x005CFF50) is defined only as
// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ; its real name is unproven.
class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();

// The field-clear helper behind ILT 0x00015640 is the matched body 0x005C2240,
// which the ledger defines as BfmeNodeZK::bfmeLeaveZK.
class BfmeNodeZK
{
public:
	void bfmeLeaveZK(void);
};

class ParticleSystemFieldClearShim
{
public:
	ParticleSystem *m_system;
	ParticleSystemFieldClearShim *m_previous;
	ParticleSystemFieldClearShim *m_next;
};

static __forceinline void clearField(ParticleSystemFieldClearShim *field)
{
	((BfmeNodeZK *)field)->bfmeLeaveZK();
}

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
				return (ParticleSystem *)bfmeNullSystemZA();
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
		clearField(&m_dustEffect);
	}
	if (m_dirtEffect)
	{
		m_dirtEffect->attachToObject(0);
		m_dirtEffect->destroy();
		clearField(&m_dirtEffect);
	}
	if (m_powerslideEffect)
	{
		m_powerslideEffect->attachToObject(0);
		m_powerslideEffect->destroy();
		clearField(&m_powerslideEffect);
	}
}
