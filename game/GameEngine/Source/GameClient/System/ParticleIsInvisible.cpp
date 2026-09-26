// cl: /DNDEBUG /MD /EHsc
// ?isInvisible@Particle@@QAE_NXZ
// Open-BFME: Particle::isInvisible, retail 0x005C31A0, 91 bytes.
// The reference Particle declaration and the retail module dispatch identify this body.

typedef bool Bool;

enum ParticleType
{
	PARTICLE = 1,
	DRAWABLE = 2,
	STREAK = 3,
	VOLUME_PARTICLE = 4,
	SMUDGE = 5,
	TYPE6 = 6,
	TYPE7 = 7
};

class ParticleSystem
{
public:
	ParticleType getParticleType() const { return m_particleType; }

	unsigned char m_unmodelled_000[0x08];
	ParticleType m_particleType;
};

ParticleSystem *Make00001B18();

class ParticleSystemHandle
{
public:
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make00001B18();
	}

private:
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class ParticleVisibilityModule
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual Bool isInvisible(ParticleType type);
};

static __forceinline Bool callParticleInvisible(ParticleVisibilityModule *module,
	ParticleType type)
{
	return module->isInvisible(type);
}

class Particle
{
public:
	Bool isInvisible();

private:
	unsigned char m_unmodelled_000[0x4C];
	ParticleSystemHandle m_system;
	unsigned char m_unmodelled_058[0x18];
	void *m_renderObject;
	unsigned char m_unmodelled_074[0x18];
	ParticleVisibilityModule *m_defaultModule;
	ParticleVisibilityModule *m_specialModule;
};

Bool Particle::isInvisible()
{
	if (m_renderObject)
		return false;

	ParticleType type = m_system.operator->()->m_particleType;
	switch (type)
	{
		case PARTICLE:
		case DRAWABLE:
		case SMUDGE:
		case TYPE6:
			if (m_defaultModule)
				return callParticleInvisible(m_defaultModule, type);
			return false;

		case STREAK:
		case VOLUME_PARTICLE:
		case TYPE7:
			if (m_specialModule)
				return callParticleInvisible(m_specialModule, type);
			return false;
	}

	return true;
}
