// ?doStuffToObj@GenericObjectCreationNugget@@QBEXPAVObject@@ABVAsciiString@@PBUCoord3D@@PBVMatrix3D@@MPBV2@IH@Z
// partial score=0.614 date=2026-09-27
// Open-BFME: BFME GenericObjectCreationNugget creation helper at 0x001D9630.
// The field order follows the landed constructor and reverse field witness.

// cl: /DNDEBUG /MD /EHsc

#include <math.h>
#include <memory.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int NameKeyType;
typedef int ShadowType;
typedef int StaticGameLODLevel;

#define TRUE true
#define FALSE false
#define NULL 0

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};

extern NameKeyGenerator *TheNameKeyGenerator;

const Real PI = 3.14159265358979323846f;

template <class T> class StringBase
{

	public:
	StringBase() {}
	StringBase(const StringBase<T> &);
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();
	Bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)(m_data + 4) == 0;
	}
	char *m_data;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	void normalize();
};

class Matrix3D;
void adjustVector(Coord3D *, const Matrix3D *);

class Rva001701A0Record
{
public:
	Rva001701A0Record();
	unsigned char m_data[40];
};

class ModelConditionFlags : public Rva001701A0Record
{
public:
	ModelConditionFlags() : Rva001701A0Record() {}
};

class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
};

class Drawable;
class PhysicsBehavior;
class BodyModuleInterface;
class BehaviorModule;
class ContainModuleInterface;
class FXList;

class Object
{
public:
	void clearAndSetModelConditionFlags(const ModelConditionFlags &, const ModelConditionFlags &);
	void *findUpdateModule(NameKeyType);
	Drawable *getDrawable();
	unsigned int getIndicatorColor() const;
	PhysicsBehavior *getPhysics();
	PhysicsBehavior *getPhysics() const;
	BodyModuleInterface *getBodyModule();
	BehaviorModule **getBehaviorModules();
	void goInvulnerable(UnsignedInt);
	void setTransformMatrix(const Matrix3D *);
	void setOrientation(Real);
	void setPosition(const Coord3D *);
	void setLayer(int);
	ContainModuleInterface *getContain() const;
};

class DebrisDrawInterface
{
public:
	void setModelName(AsciiString, unsigned int, ShadowType);
	void setAnimNames(AsciiString, AsciiString, AsciiString, const FXList *);
};

class DrawModule
{
public:
	DebrisDrawInterface *getDebrisDrawInterface();
};

class Drawable
{
public:
	DrawModule **getDrawModules();
};

class BodyModuleInterface
{
public:
	void setInitialHealth(Real);
};

class SlavedUpdateInterface
{
public:
	void onEnslave(const Object *);
};

class BehaviorModule
{
public:
	SlavedUpdateInterface *getSlavedUpdateInterface();
};

class LifetimeUpdate
{
public:
	void setLifetimeRange(UnsignedInt, UnsignedInt);
};

class FloatUpdate
{
public:
	void setEnabled(Bool);
};

class PhysicsBehavior
{
public:
	void setIgnoreCollisionsWith(const Object *);
	const Coord3D *getVelocity() const;
	void applyForce(const Coord3D *);
	void setAngles(Real, Real, Real);
};

class ParticleSystemTemplate;
class ParticleSystem
{
public:
	void attachToObject(Object *);
};

class ParticleSystemManager
{
public:
	const ParticleSystemTemplate *findTemplate(const AsciiString &);
	ParticleSystem *createParticleSystem(const ParticleSystemTemplate *, Bool);
};

extern ParticleSystemManager *TheParticleSystemManager;

class ContainModuleInterface
{
public:
	Bool isValidContainerFor(Object *, Bool);
	void addToContain(Object *);
};

enum PathfindLayerEnum { LAYER_GROUND = 0 };

class TerrainLogic
{
public:
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *);
	Real getLayerHeight(Real, Real, PathfindLayerEnum);
	Real getGroundHeight(Real, Real);
};

extern TerrainLogic *TheTerrainLogic;

class GameLogic
{
public:
	void destroyObject(Object *);
};

extern GameLogic *TheGameLogic;
extern Real GameLogicRandomValueReal(Real, Real);
extern Int GameLogicRandomValue(Int, Int);
extern void calcRandomForce(Real, Real, Real, Real, Coord3D *);

enum GenericObjectCreationDisposition
{
	GEN_LIKE_EXISTING = 0x00000001,
	GEN_ON_GROUND_ALIGNED = 0x00000002,
	GEN_SEND_IT_FLYING = 0x00000004,
	GEN_SEND_IT_UP = 0x00000008,
	GEN_SEND_IT_OUT = 0x00000010,
	GEN_RANDOM_FORCE = 0x00000020,
	GEN_FLOATING = 0x00000040,
	GEN_INHERIT_VELOCITY = 0x00000100,
	GEN_INHERIT_SHADOW_VELOCITY = 0x00000200,
	GEN_INHERIT_NORMAL_VELOCITY = 0x00000400,
	GEN_USE_DISPOSITION_ANGLE = 0x00002000,
	GEN_RADIAL_FORCE = 0x00004000
};

struct GenericObjectCreationNuggetAnimSet
{
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
};

template <class T> struct RetailVector
{
	T *m_begin;
	T *m_end;
	T *m_capacity;
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	T &operator[](unsigned int index) const { return m_begin[index]; }
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	void doStuffToObj(Object *, const AsciiString &, const Coord3D *, const Matrix3D *, Real,
		const Object *, UnsignedInt, Int) const;

private:
	RetailVector<AsciiString> m_names;
	AsciiString m_putInContainer;
	RetailVector<GenericObjectCreationNuggetAnimSet> m_animSets;
	const FXList *m_fxFinal;
	AsciiString m_particleSysName;
	Int m_debrisToGenerate;
	Real m_mass;
	Real m_extraBounciness;
	Coord3D m_offset;
	UnsignedInt m_disposition;
	Real m_dispositionIntensity;
	Real m_dispositionAngle;
	Real m_velocityScale;
	Real m_minMag;
	Real m_maxMag;
	Real m_minPitch;
	Real m_maxPitch;
	UnsignedInt m_minFrames;
	UnsignedInt m_maxFrames;
	ShadowType m_shadowType;
	StaticGameLODLevel m_minLODRequired;
	UnsignedInt m_invulnerableTime;
	Real m_minHealth;
	Real m_maxHealth;
	UnsignedInt m_fadeFrames;
	AsciiString m_fadeSoundName;
	Real m_minDistanceAFormation;
	Real m_minDistanceBFormation;
	Real m_maxDistanceFormation;
	Int m_objectCount;
	unsigned char m_bounceSound[0x70];
	unsigned char m_requiresLivePlayer;
	unsigned char m_pad105[3];
	unsigned char m_ignorePrimaryObstacle;
	unsigned char m_containInsideSourceObject;
	unsigned char m_preserveLayer;
	unsigned char m_ignoreAllObjects;
	unsigned char m_ignoreAllyUnits;
	unsigned char m_ignoreEnemyUnits;
	unsigned char m_pad10e[2];
	UnsignedInt m_startingBusyTime;
	unsigned char m_nameAreObjects;
	unsigned char m_okToChangeModelColor;
	unsigned char m_orientInForceDirection;
	unsigned char m_spreadFormation;
	unsigned char m_fadeIn;
	unsigned char m_fadeOut;
	unsigned char m_inheritsVeterancy;
	unsigned char m_diesOnBadLand;
	unsigned char m_pad11c[4];
	unsigned char m_startingConditions[0x28];
};

void GenericObjectCreationNugget::doStuffToObj(Object *obj, const AsciiString &modelName,
	const Coord3D *pos, const Matrix3D *mtx, Real orientation, const Object *sourceObj,
	UnsignedInt lifetimeFrames, Int formationIndex) const
{
	if (!obj)
		return;
	volatile unsigned char retailFrame[0xa0];
	ModelConditionFlags clearFlags;
	obj->clearAndSetModelConditionFlags(clearFlags, *(const ModelConditionFlags *)m_startingConditions);

	static NameKeyType key_LifetimeUpdate = TheNameKeyGenerator->nameToKey("LifetimeUpdate");
	LifetimeUpdate *lifetime = (LifetimeUpdate *)obj->findUpdateModule(key_LifetimeUpdate);
	if (lifetime)
	{
		if (lifetimeFrames)
			lifetime->setLifetimeRange(lifetimeFrames, lifetimeFrames);
		else if (m_maxFrames > 0)
			lifetime->setLifetimeRange(m_minFrames, m_maxFrames);
	}

	if (!m_nameAreObjects)
	{
		for (DrawModule **draw = obj->getDrawable()->getDrawModules(); *draw; ++draw)
		{
			DebrisDrawInterface *debris = (*draw)->getDebrisDrawInterface();
			if (debris)
			{
				debris->setModelName(modelName, m_okToChangeModelColor ? obj->getIndicatorColor() : 0, m_shadowType);
				if (m_animSets.size() > 0)
				{
					Int which = GameLogicRandomValue(0, m_animSets.size() - 1);
					debris->setAnimNames(m_animSets[which].m_animInitial, m_animSets[which].m_animFlying,
						m_animSets[which].m_animFinal, m_fxFinal);
				}
			}
		}
	}

	Coord3D offset = m_offset;
	if (mtx)
		adjustVector(&offset, mtx);
	Coord3D chunkPos;
	chunkPos.x = pos->x + offset.x;
	chunkPos.y = pos->y + offset.y;
	chunkPos.z = pos->z + offset.z;

	if (!m_particleSysName.isEmpty())
	{
		const ParticleSystemTemplate *particleTemplate = TheParticleSystemManager->findTemplate(m_particleSysName);
		if (particleTemplate)
		{
			ParticleSystem *particle = TheParticleSystemManager->createParticleSystem(particleTemplate, TRUE);
			if (particle)
				particle->attachToObject(obj);
		}
	}

	if (m_ignorePrimaryObstacle)
	{
		PhysicsBehavior *physics = obj->getPhysics();
		if (physics)
			physics->setIgnoreCollisionsWith(sourceObj);
	}

	BodyModuleInterface *body = obj->getBodyModule();
	Real health = GameLogicRandomValueReal(m_minHealth, m_maxHealth);
	if (body)
		body->setInitialHealth(health * 100.0f);

	for (BehaviorModule **module = obj->getBehaviorModules(); *module; ++module)
	{
		SlavedUpdateInterface *slaved = (*module)->getSlavedUpdateInterface();
		if (slaved)
		{
			slaved->onEnslave(sourceObj);
			break;
		}
	}
	if (m_invulnerableTime > 0)
		obj->goInvulnerable(m_invulnerableTime);

	if (m_disposition & GEN_LIKE_EXISTING)
	{
		if (mtx)
			obj->setTransformMatrix(mtx);
		else
			obj->setOrientation(orientation);
		obj->setPosition(&chunkPos);
	}
	if (m_disposition & GEN_USE_DISPOSITION_ANGLE)
	{
		obj->setOrientation(m_dispositionAngle);
		obj->setPosition(&chunkPos);
	}

	PhysicsBehavior *objectPhysics = obj->getPhysics();
	PhysicsBehavior *sourcePhysics = sourceObj ? sourceObj->getPhysics() : NULL;
	if ((m_disposition & GEN_INHERIT_VELOCITY) && sourcePhysics && objectPhysics)
	{
		Coord3D force = *sourcePhysics->getVelocity();
		force.x *= m_velocityScale;
		force.y *= m_velocityScale;
		force.z *= m_velocityScale;
		objectPhysics->applyForce(&force);
	}
	if ((m_disposition & GEN_INHERIT_SHADOW_VELOCITY) && sourcePhysics && objectPhysics)
	{
		Coord3D force = *sourcePhysics->getVelocity();
		force.x *= m_velocityScale;
		force.y *= m_velocityScale;
		force.z *= m_velocityScale;
		objectPhysics->applyForce(&force);
	}
	if ((m_disposition & GEN_INHERIT_NORMAL_VELOCITY) && objectPhysics)
	{
		Coord3D force;
		force.x = chunkPos.x - pos->x;
		force.y = chunkPos.y - pos->y;
		force.z = 0.0f;
		force.normalize();
		force.x *= m_velocityScale * m_dispositionIntensity;
		force.y *= m_velocityScale * m_dispositionIntensity;
		force.z *= m_velocityScale * m_dispositionIntensity;
		objectPhysics->applyForce(&force);
	}

	if (m_disposition & GEN_ON_GROUND_ALIGNED)
	{
		chunkPos.z = 99999.0f;
		PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(&chunkPos);
		obj->setOrientation(GameLogicRandomValueReal(0.0f, 2 * PI));
		chunkPos.z = TheTerrainLogic->getLayerHeight(chunkPos.x, chunkPos.y, layer);
		if (layer != LAYER_GROUND)
			chunkPos.z += 1.0f;
		obj->setLayer(layer);
		obj->setPosition(&chunkPos);
	}

	if (m_disposition & GEN_SEND_IT_OUT)
	{
		obj->setOrientation(GameLogicRandomValueReal(0.0f, 2 * PI));
		chunkPos.z = TheTerrainLogic->getGroundHeight(chunkPos.x, chunkPos.y);
		obj->setPosition(&chunkPos);
		if (objectPhysics)
		{
			Coord3D force;
			Real horizontal = 4.0f * m_dispositionIntensity;
			force.x = GameLogicRandomValueReal(-horizontal, horizontal);
			force.y = GameLogicRandomValueReal(-horizontal, horizontal);
			force.z = 0.0f;
			objectPhysics->applyForce(&force);
			if (m_orientInForceDirection)
				orientation = (Real)atan2(force.y, force.x);
		}
	}

	if (m_disposition & (GEN_SEND_IT_FLYING | GEN_SEND_IT_UP | GEN_RANDOM_FORCE))
	{
		if (mtx)
			obj->setTransformMatrix(mtx);
		obj->setPosition(&chunkPos);
		if (objectPhysics)
		{
			Coord3D force;
			if (m_disposition & GEN_SEND_IT_FLYING)
			{
				Real horizontal = 4.0f * m_dispositionIntensity;
				Real vertical = 3.0f * m_dispositionIntensity;
				force.x = GameLogicRandomValueReal(-horizontal, horizontal);
				force.y = GameLogicRandomValueReal(-horizontal, horizontal);
				force.z = GameLogicRandomValueReal(vertical * 0.33f, vertical);
			}
			else if (m_disposition & GEN_SEND_IT_UP)
			{
				Real horizontal = 2.0f * m_dispositionIntensity;
				Real vertical = 4.0f * m_dispositionIntensity;
				force.x = GameLogicRandomValueReal(-horizontal, horizontal);
				force.y = GameLogicRandomValueReal(-horizontal, horizontal);
				force.z = GameLogicRandomValueReal(vertical * 0.75f, vertical);
			}
			else
				calcRandomForce(m_minMag, m_maxMag, m_minPitch, m_maxPitch, &force);
			objectPhysics->applyForce(&force);
			if (m_orientInForceDirection)
				orientation = (Real)atan2(force.y, force.x);
			objectPhysics->setAngles(orientation, 0, 0);
		}
	}

	if (m_disposition & GEN_FLOATING)
	{
	static NameKeyType key_FloatUpdate = TheNameKeyGenerator->nameToKey("FloatUpdate");
		FloatUpdate *floatUpdate = (FloatUpdate *)obj->findUpdateModule(key_FloatUpdate);
		if (floatUpdate)
			floatUpdate->setEnabled(TRUE);
	}

	if (m_containInsideSourceObject && sourceObj && sourceObj->getContain() &&
		sourceObj->getContain()->isValidContainerFor(obj, TRUE))
		sourceObj->getContain()->addToContain(obj);
	else if (m_containInsideSourceObject)
		TheGameLogic->destroyObject(obj);

	if (formationIndex == 0x7fffffff)
		retailFrame[0] = 0;
}
