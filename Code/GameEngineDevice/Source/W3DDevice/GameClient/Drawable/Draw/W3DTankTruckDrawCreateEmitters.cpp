// cl: /O2 /Ob2 /GR- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DTankTruckDraw::createEmitters.

typedef bool Bool;
enum { FALSE = 0, TRUE = 1 };

class AsciiString
{
private:
	unsigned char m_storage[4];
};

class Object;
class ParticleSystemTemplate;

class Drawable
{
public:
	Bool isDrawableEffectivelyHidden() const;
	Object *getObject() const
	{
		return m_object;
	}

private:
	unsigned char m_pad[0xfc];
	Object *m_object;
};

class ParticleSystem
{
public:
	void attachToObject(const Object *object);
	void setSaveable(Bool saveable);
};

ParticleSystem *Make00001B18(void);

class U1CachedHolder;

class U1Sub
{
public:
	U1Sub &apply(U1CachedHolder *that) throw();

	ParticleSystem *m_system;
	U1Sub *m_previous;
	U1Sub *m_next;
};

class BfmeParticleSystemHandle : public U1Sub
{
public:
	~BfmeParticleSystemHandle() throw();
	BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &that) throw()
	{
		apply((U1CachedHolder *)&that);
		return *this;
	}
	operator Bool() const
	{
		return m_system != 0;
	}

	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make00001B18();
		return m_system;
	}

};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate,
		Bool createSlaves) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class W3DTankTruckDrawModuleData
{
public:
	unsigned char m_pad[0x15c];
	AsciiString m_dustEffectName;
	AsciiString m_dirtEffectName;
	AsciiString m_powerslideEffectName;
};

class W3DTankTruckPrimaryBase
{
public:
	virtual void sharedSlot();
	W3DTankTruckDrawModuleData *m_moduleData;
	Drawable *m_drawable;
};

class W3DTankTruckSecondaryBase
{
public:
	virtual void sharedSlot();
};

class Gen_w3d_tank_truck : public W3DTankTruckPrimaryBase,
	public W3DTankTruckSecondaryBase
{
public:
	virtual ~Gen_w3d_tank_truck();
	virtual void sharedSlot();

private:
	unsigned char m_pad[0x280 - 0x10];
};

class W3DTankTruckDraw : public Gen_w3d_tank_truck
{
private:
	W3DTankTruckDrawModuleData *getW3DTankTruckDrawModuleData() const
	{
		return m_moduleData;
	}
	Drawable *getDrawable() const
	{
		return m_drawable;
	}

protected:
	BfmeParticleSystemHandle m_dustEffect;
	BfmeParticleSystemHandle m_dirtEffect;
	BfmeParticleSystemHandle m_powerslideEffect;

	void createEmitters(void);
};

void W3DTankTruckDraw::createEmitters(void)
{
	if (getDrawable()->isDrawableEffectivelyHidden())
		return;
	if (getW3DTankTruckDrawModuleData())
	{
		if (!m_dustEffect)
		{
			const ParticleSystemTemplate *sysTemplate =
				TheParticleSystemManager->findTemplate(getW3DTankTruckDrawModuleData()->m_dustEffectName);
			if (sysTemplate)
			{
				m_dustEffect = TheParticleSystemManager->createParticleSystem(sysTemplate, TRUE);
				m_dustEffect->attachToObject(getDrawable()->getObject());
				m_dustEffect->setSaveable(FALSE);
			}
		}
		if (!m_dirtEffect)
		{
			const ParticleSystemTemplate *sysTemplate =
				TheParticleSystemManager->findTemplate(getW3DTankTruckDrawModuleData()->m_dirtEffectName);
			if (sysTemplate)
			{
				m_dirtEffect = TheParticleSystemManager->createParticleSystem(sysTemplate, TRUE);
				m_dirtEffect->attachToObject(getDrawable()->getObject());
				m_dirtEffect->setSaveable(FALSE);
			}
		}
		if (!m_powerslideEffect)
		{
			const ParticleSystemTemplate *sysTemplate =
				TheParticleSystemManager->findTemplate(getW3DTankTruckDrawModuleData()->m_powerslideEffectName);
			if (sysTemplate)
			{
				m_powerslideEffect = TheParticleSystemManager->createParticleSystem(sysTemplate, TRUE);
				m_powerslideEffect->attachToObject(getDrawable()->getObject());
				m_powerslideEffect->setSaveable(FALSE);
			}
		}
	}
}
