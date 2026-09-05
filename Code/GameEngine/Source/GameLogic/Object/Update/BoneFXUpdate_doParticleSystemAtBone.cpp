// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
// Open-BFME: BoneFXUpdate::doParticleSystemAtBone, retail 0x00289190 / 323B.
// ZH twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// Layout: Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateCtorModuleFactoryBody.cpp
// Handle: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDrawCreateEmitters.cpp

#include <vector>

typedef bool Bool;
typedef int Int;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class ParticleSystemTemplate;
class ModuleData;
class Drawable;

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
	Bool isDrawableEffectivelyHidden() const;
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

class ParticleSystem
{
public:
	ParticleSystemID getSystemID() const
	{
		return m_systemID;
	}

	void setPosition(const Coord3D *pos);
	void attachToObject(const Object *obj);
	void stop();

private:
	unsigned char m_pad[0xAC];
	ParticleSystemID m_systemID;
};

ParticleSystem *Make00001B18(void);

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw();

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
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate,
		bool createSlaves) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class BoneFXUpdateModuleData
{
public:
	unsigned char m_pad[0x910];
	unsigned int m_damageParticleTypes;
};

static __forceinline Bool getDamageTypeFlag(unsigned int flags, Int damageType)
{
	return (flags & (1u << (damageType - 1))) != 0;
}

class BoneFXUpdate
{
public:
	void doParticleSystemAtBone(const ParticleSystemTemplate *particleSystemTemplate,
		const Coord3D *bonePosition);

protected:
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
	virtual void resolveBoneLocations();

	const BoneFXUpdateModuleData *getBoneFXUpdateModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject()
	{
		return m_object;
	}

private:
	const BoneFXUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad014[0x20 - 0x0C];
	_STL::vector<ParticleSystemID> m_particleSystemIDs;
	unsigned char m_pad02C[0x62C - 0x2C];
	Int m_curBodyState;
	bool m_bonesResolved[4];
};

// ?doParticleSystemAtBone@BoneFXUpdate@@QAEXPBVParticleSystemTemplate@@PBUCoord3D@@@Z
void BoneFXUpdate::doParticleSystemAtBone(const ParticleSystemTemplate *particleSystemTemplate,
	const Coord3D *bonePosition)
{
	if (m_bonesResolved[m_curBodyState] == false)
		resolveBoneLocations();

	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();
	if (lastDamageInfo && getDamageTypeFlag(d->m_damageParticleTypes, lastDamageInfo->m_damageType) == false)
		return;

	Object *building = getObject();
	BfmeParticleSystemHandle psys = TheParticleSystemManager->createParticleSystem(particleSystemTemplate, true);
	if (psys)
	{
		m_particleSystemIDs.push_back(psys->getSystemID());
		psys->setPosition(bonePosition);
		psys->attachToObject(building);
		Drawable *drawable = building->getDrawable();
		if (drawable && drawable->isDrawableEffectivelyHidden())
			psys->stop();
	}
}
