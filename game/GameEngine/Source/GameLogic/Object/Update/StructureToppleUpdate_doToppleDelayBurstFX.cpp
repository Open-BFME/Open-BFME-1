// cl: /DNDEBUG /MD /EHsc
// StructureToppleUpdate::doToppleDelayBurstFX, retail 0x002AFB20.

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D;
class ParticleSystemTemplate;

class DamageInfo
{
public:
	unsigned char m_unmodelled_000[0x10];
	Int m_damageType;
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual const DamageInfo *getLastDamageInfo() const;
};

class Drawable
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	Int getPristineBonePositions(const char *, Int, Coord3D *, Matrix3D *, Int, Int) const;
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();

	BodyModuleInterface *getBodyModule() const
	{
		return *reinterpret_cast<BodyModuleInterface *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x200);
	}
};

class FXList
{
public:
	Bool isEmpty() const;
	void doFXPos(const Coord3D *, const Matrix3D *, Real, const Coord3D *) const;
};

struct BfmeParticleSystemHandle;

class ParticleSystem
{
public:
	void setPosition(const Coord3D *);
	void attachToDrawable(const Drawable *);

	unsigned char m_unmodelled_000[0x98];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
};

class StructureToppleParticleSystemAttachShim
{
public:
	void attachToDrawable(const Drawable *);
};

ParticleSystem *Make00001B18();

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw()
	{
		if (m_system)
		{
			if (m_previous)
				m_previous->m_next = m_next;
			else
				m_system->m_firstHandle = m_next;
			if (m_next)
				m_next->m_previous = m_previous;
			else
				m_system->m_lastHandle = m_previous;
			m_previous = 0;
			m_next = 0;
		}
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

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *, Bool) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

struct AsciiString
{
	void *m_data;

	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 :
			reinterpret_cast<const char *>(0x0107388B);
	}
};

struct FXBoneInfo
{
	AsciiString boneName;
	const ParticleSystemTemplate *particleSystemTemplate;
};

struct FXBoneInfoVector
{
	FXBoneInfo *m_begin;
	FXBoneInfo *m_end;
	FXBoneInfo *m_capacity;
};

class StructureToppleUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x48];
	unsigned int m_damageFXTypes;
	FXList *m_toppleStartFXList;
	FXList *m_toppleDelayFXList;
	unsigned char m_unmodelled_054[0x48];
	FXBoneInfoVector fxbones;
};

enum StructureTopplePhaseType
{
	STPHASE_INITIAL = 0,
	STPHASE_DELAY = 1,
	STPHASE_FINAL = 2
};

class StructureToppleModuleBase
{
public:
	virtual void slot00();

protected:
	const void *m_moduleData;
};

class StructureToppleUpdateModuleBase : public StructureToppleModuleBase
{
protected:
	Object *m_object;
};

class StructureToppleUpdate : public StructureToppleUpdateModuleBase
{
public:

	const StructureToppleUpdateModuleData *getStructureToppleUpdateModuleData() const
	{
		return reinterpret_cast<const StructureToppleUpdateModuleData *>(m_moduleData);
	}

	Object *getObject() const
	{
		return m_object;
	}

	protected:
	void doToppleDelayBurstFX();

	unsigned char m_unmodelled_00c[0x3c];
	Coord3D m_delayBurstLocation;

	void doPhaseStuff(StructureTopplePhaseType, const Coord3D *);
};

#pragma comment(linker, "/alternatename:?attachToDrawable@StructureToppleParticleSystemAttachShim@@QBEXPBVDrawable@@@Z=?j_00012319@@YAXXZ")
#pragma comment(linker, "/alternatename:?doPhaseStuff@StructureToppleUpdate@@IAEXW4StructureTopplePhaseType@@PBUCoord3D@@@Z=?j_00022aac@@YAXXZ")

static __forceinline Bool getDamageTypeFlag(unsigned int flags, Int damageType)
{
	return (flags & (1u << (damageType - 1))) != 0;
}

// ?doToppleDelayBurstFX@StructureToppleUpdate@@IAEXXZ
void StructureToppleUpdate::doToppleDelayBurstFX()
{
	void *fx;
	const StructureToppleUpdateModuleData *d = getStructureToppleUpdateModuleData();
	volatile const StructureToppleUpdateModuleData *vd = d;
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

	if (lastDamageInfo)
	{
		if (getDamageTypeFlag(vd->m_damageFXTypes, lastDamageInfo->m_damageType) == false)
			goto afterDelayFX;
	}
	{
		fx = vd->m_toppleDelayFXList;
		if (fx && !reinterpret_cast<FXList *>(fx)->isEmpty())
			reinterpret_cast<FXList *>(fx)->doFXPos(&m_delayBurstLocation, 0, 0.0f, 0);
	}

afterDelayFX:

	Object *building = getObject();
	Drawable *drawable = building->getDrawable();

	fx = 0;
	if (lastDamageInfo == reinterpret_cast<const DamageInfo *>(fx) ||
		getDamageTypeFlag(d->m_damageFXTypes, lastDamageInfo->m_damageType))
	{
		for (FXBoneInfo *it = d->fxbones.m_begin; it != d->fxbones.m_end; ++it)
		{
			BfmeParticleSystemHandle sys =
				TheParticleSystemManager->createParticleSystem(
					it->particleSystemTemplate, true);
			if (sys)
			{
				Coord3D pos;
				if (drawable->getPristineBonePositions(it->boneName.str(), 0,
					&pos, 0, 1, 0) == 1)
				{
					sys->setPosition(&pos);
					reinterpret_cast<StructureToppleParticleSystemAttachShim *>(sys.operator->())->attachToDrawable(drawable);
				}
			}
		}
	}

	doPhaseStuff(STPHASE_DELAY, &m_delayBurstLocation);
}
