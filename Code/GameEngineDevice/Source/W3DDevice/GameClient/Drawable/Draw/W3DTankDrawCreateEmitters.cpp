// cl: /O2 /Ob2 /GR- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DTankDraw::createEmitters.

typedef bool Bool;
enum { FALSE = 0, TRUE = 1 };

class AsciiString
{
private:
	unsigned char m_storage[4];
};

class Drawable;
class ParticleSystemTemplate;

class ParticleSystem
{
public:
	void attachToDrawable(const Drawable *drawable);
	void setSaveable(Bool saveable);
	void stop(void);
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
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class W3DTankDrawModuleData
{
public:
	unsigned char m_pad[0x15c];
	AsciiString m_treadDebrisNameLeft;
	AsciiString m_treadDebrisNameRight;
};

class W3DTankDrawPrimaryBase
{
public:
	virtual void sharedSlot();
	W3DTankDrawModuleData *m_moduleData;
	Drawable *m_drawable;
};

class W3DTankDrawSecondaryBase
{
public:
	virtual void sharedSlot();
};

class Gen_w3d_tank_draw : public W3DTankDrawPrimaryBase,
	public W3DTankDrawSecondaryBase
{
public:
	virtual ~Gen_w3d_tank_draw();
	virtual void sharedSlot();

private:
	unsigned char m_pad[0x27c - 0x10];
};

class W3DTankDraw : public Gen_w3d_tank_draw
{
private:
	W3DTankDrawModuleData *getW3DTankDrawModuleData() const
	{
		return m_moduleData;
	}

	Drawable *getDrawable() const
	{
		return m_drawable;
	}

protected:
	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;

	void createEmitters(void);
};

void W3DTankDraw::createEmitters(void)
{
	if (!m_treadDebrisLeft)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(
			getW3DTankDrawModuleData()->m_treadDebrisNameLeft);
		if (sysTemplate)
		{
			m_treadDebrisLeft = TheParticleSystemManager->createParticleSystem(
				sysTemplate, TRUE);
			m_treadDebrisLeft->attachToDrawable(getDrawable());
			m_treadDebrisLeft->setSaveable(FALSE);
			m_treadDebrisLeft->stop();
		}
	}
	if (!m_treadDebrisRight)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(
			getW3DTankDrawModuleData()->m_treadDebrisNameRight);
		if (sysTemplate)
		{
			m_treadDebrisRight = TheParticleSystemManager->createParticleSystem(
				sysTemplate, TRUE);
			m_treadDebrisRight->attachToDrawable(getDrawable());
			m_treadDebrisRight->setSaveable(FALSE);
			m_treadDebrisRight->stop();
		}
	}
}
