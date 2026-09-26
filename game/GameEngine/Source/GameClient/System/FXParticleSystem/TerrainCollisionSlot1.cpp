// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The final TerrainCollisionModule family is installed by factory 0x005E8D30.
// Its slot 1 is distinct from ParticleTerrainCollisionModule at 0x005FD380;
// retain the address-qualified owner until the template class layers are known.
// The one-pointer tracking view supplies a shared null singleton on dereference.
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class ParticleSystem
{
public:
	void getPosition(Coord3D *pos);

	private:
		unsigned char m_pad[0x12c];

	public:
	unsigned int m_field12c;
};

ParticleSystem *Make00001B18();

class Rva005FCF70LazyParticleSystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_target;
	}

	// Retail dereference supplies the shared null singleton but does not
	// store it back into the wrapper field.
	ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = m_target;
		if (!target)
			target = Make00001B18();
		return target;
	}

private:
	ParticleSystem *m_target;
};

class Matrix3D;

class FXList
{
public:
	bool bfmeIsBlocked();
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary) const;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;
};

extern TerrainLogic *TheTerrainLogic;

class Rva005FCF70TerrainCollisionFamily
{
public:
	virtual void slot00();
	virtual void slot1();

private:
	Rva005FCF70LazyParticleSystemPtr m_system;
	unsigned char m_pad08[0x15];
	bool m_deactivate;
	unsigned char m_pad1e[0x1a];
	FXList * m_eventFX;
	unsigned char m_pad3c[4];
	bool m_active;
	unsigned char m_pad41[3];
};

void Rva005FCF70TerrainCollisionFamily::slot1()
{
	ParticleSystem *system = m_system.operator->();
	Coord3D position;
	system->getPosition(&position);
	if (!m_active)
		return;

	if (!m_eventFX)
		return;
	if (position.z <= TheTerrainLogic->getGroundHeight(position.x, position.y, 0))
	{
		FXList *eventFX = m_eventFX;
		if (eventFX != 0 && !eventFX->bfmeIsBlocked())
			eventFX->doFXPos(&position, 0, 0.0f, 0);

		bool deactivate = m_deactivate;
		m_active = false;
		if (deactivate)
		{
			ParticleSystem *finished;
			if (!m_system)
				finished = Make00001B18();
			else
				finished = m_system;
			finished->m_field12c = 1;
		}
	}
}
