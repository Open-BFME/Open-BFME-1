// ?doStuffToObj@GenericObjectCreationNugget@@QBEXPAVObject@@ABVAsciiString@@PBUCoord3D@@PBVMatrix3D@@MPBV2@IH@Z
// partial score=0.8044 date=2026-10-09
// Creation helper with the saved nugget layout and retail branch structure.

// stlport
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Include /Igame/GameEngine/Source/Common /Igame/Libraries/Include/Lib /Igame/GameEngine/Source/GameLogic

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
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

#include "ascii_string.h"
template <typename T> inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

#include "Lib/Coord3D.h"
extern "C" void __fastcall __identifier("?normalize@Coord3D@@QAEXXZ")(Coord3D *);

#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
void adjustVector(Coord3D *, const Matrix3D *);

#include "Rva001701A0Record.h"

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

class AICommandParms;
class AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *) = 0;
};
class AIUpdateInterface
{
public:
    AICommandInterface *commandInterface() { return (AICommandInterface *)((char *)this + 0x20); }
};
struct Rva001D9630ConditionMask
{
    unsigned int m_words[10];
    unsigned int test(Int bit) const { return m_words[bit >> 5] & (1u << (bit & 31)); }
    void set(Int bit) { m_words[bit >> 5] |= (1u << (bit & 31)); }
};
#define OBJECT_TU_MEMBERS \
    void clearAndSetModelConditionFlags(const ModelConditionFlags &, const ModelConditionFlags &); \
    void *findUpdateModule(NameKeyType); \
    unsigned int getIndicatorColor() const; \
    PhysicsBehavior *getPhysics() { return m_physics; } \
    const PhysicsBehavior *getPhysics() const { return m_physics; } \
    BodyModuleInterface *getBodyModule() { return m_body; } \
    BehaviorModule **getBehaviorModules() { return m_behaviors; } \
    AIUpdateInterface *getAIUpdateInterface() { return m_ai; } \
    void goInvulnerable(UnsignedInt); \
    void setTransformMatrix(const Matrix3D *); \
    void setOrientation(Real); \
    void setPosition(const Coord3D *); \
    void setLayer(int); \
    ContainModuleInterface *getContain() const { return m_contain; } \
    void getUnitDirectionVector3D(Coord3D &) const; \
    Real bfmeGetNonnegativePreferredLocomotorHeight() const; \
    void notifyModelConditionChanged(); \
    void setRva001BE220(int, bool); \
    void addRva001D9630Condition() { \
        Rva001D9630ConditionMask &word = *(Rva001D9630ConditionMask *)m_modelConditionFlags; \
        if (!word.test(5)) { word.set(5); notifyModelConditionChanged(); } \
    }
#include "Object/object.h"
#undef OBJECT_TU_MEMBERS
class Rva001BE220Receiver
{
public:
    void dispatch(int, unsigned int);
};
class DebrisDrawInterface
{
public:
    virtual void setModelName(AsciiString, unsigned int, ShadowType) = 0;
    virtual void setAnimNames(AsciiString, AsciiString, AsciiString, const FXList *) = 0;
};
class DrawModule
{
public:
	virtual void rva001d9630DrawSlot0() = 0;
	virtual void rva001d9630DrawSlot1() = 0;
	virtual void rva001d9630DrawSlot2() = 0;
	virtual void rva001d9630DrawSlot3() = 0;
	virtual void rva001d9630DrawSlot4() = 0;
	virtual void rva001d9630DrawSlot5() = 0;
	virtual void rva001d9630DrawSlot6() = 0;
	virtual void rva001d9630DrawSlot7() = 0;
	virtual void rva001d9630DrawSlot8() = 0;
	virtual void rva001d9630DrawSlot9() = 0;
	virtual void rva001d9630DrawSlot10() = 0;
	virtual void rva001d9630DrawSlot11() = 0;
	virtual void rva001d9630DrawSlot12() = 0;
	virtual void rva001d9630DrawSlot13() = 0;
	virtual void rva001d9630DrawSlot14() = 0;
	virtual void rva001d9630DrawSlot15() = 0;
	virtual void rva001d9630DrawSlot16() = 0;
	virtual void rva001d9630DrawSlot17() = 0;
	virtual void rva001d9630DrawSlot18() = 0;
	virtual void rva001d9630DrawSlot19() = 0;
	virtual void rva001d9630DrawSlot20() = 0;
	virtual void rva001d9630DrawSlot21() = 0;
	virtual void rva001d9630DrawSlot22() = 0;
	virtual void rva001d9630DrawSlot23() = 0;
	virtual void rva001d9630DrawSlot24() = 0;
	virtual void rva001d9630DrawSlot25() = 0;
	virtual void rva001d9630DrawSlot26() = 0;
	virtual void rva001d9630DrawSlot27() = 0;
	virtual void rva001d9630DrawSlot28() = 0;
	virtual void rva001d9630DrawSlot29() = 0;
	virtual void rva001d9630DrawSlot30() = 0;
	virtual void rva001d9630DrawSlot31() = 0;
	virtual void rva001d9630DrawSlot32() = 0;
	virtual void rva001d9630DrawSlot33() = 0;
	virtual void rva001d9630DrawSlot34() = 0;
	virtual void rva001d9630DrawSlot35() = 0;
	virtual void rva001d9630DrawSlot36() = 0;
	virtual void rva001d9630DrawSlot37() = 0;
	virtual void rva001d9630DrawSlot38() = 0;
	virtual void rva001d9630DrawSlot39() = 0;
	virtual void rva001d9630DrawSlot40() = 0;
    virtual DebrisDrawInterface *getDebrisDrawInterface() = 0;
};
class Drawable
{
public:
    DrawModule **getDrawModules();
    bool rva001D9630IsHidden() const;
    void rva001D9630SetHidden(bool);
};
class BodyModuleInterface
{
public:
	virtual void rva001d9630BodySlot0() = 0;
	virtual void rva001d9630BodySlot1() = 0;
	virtual void rva001d9630BodySlot2() = 0;
	virtual void rva001d9630BodySlot3() = 0;
	virtual void rva001d9630BodySlot4() = 0;
	virtual void rva001d9630BodySlot5() = 0;
	virtual void rva001d9630BodySlot6() = 0;
	virtual void rva001d9630BodySlot7() = 0;
	virtual void rva001d9630BodySlot8() = 0;
	virtual void rva001d9630BodySlot9() = 0;
	virtual void rva001d9630BodySlot10() = 0;
	virtual void rva001d9630BodySlot11() = 0;
	virtual void rva001d9630BodySlot12() = 0;
	virtual void rva001d9630BodySlot13() = 0;
	virtual void rva001d9630BodySlot14() = 0;
	virtual void rva001d9630BodySlot15() = 0;
	virtual void rva001d9630BodySlot16() = 0;
	virtual void rva001d9630BodySlot17() = 0;
	virtual void rva001d9630BodySlot18() = 0;
	virtual void rva001d9630BodySlot19() = 0;
	virtual void rva001d9630BodySlot20() = 0;
    virtual void setInitialHealth(Real, bool) = 0;
};
class SlavedUpdateInterface
{
public:
    virtual void rva001d9630SlavedSlot0() = 0;
    virtual void onEnslave(const Object *) = 0;
};
class Rva001D9630BehaviorInterface
{
public:
	virtual void rva001d9630BehaviorSlot0() = 0;
	virtual void rva001d9630BehaviorSlot1() = 0;
	virtual void rva001d9630BehaviorSlot2() = 0;
	virtual void rva001d9630BehaviorSlot3() = 0;
	virtual void rva001d9630BehaviorSlot4() = 0;
	virtual void rva001d9630BehaviorSlot5() = 0;
	virtual void rva001d9630BehaviorSlot6() = 0;
	virtual void rva001d9630BehaviorSlot7() = 0;
	virtual void rva001d9630BehaviorSlot8() = 0;
	virtual void rva001d9630BehaviorSlot9() = 0;
	virtual void rva001d9630BehaviorSlot10() = 0;
	virtual void rva001d9630BehaviorSlot11() = 0;
	virtual void rva001d9630BehaviorSlot12() = 0;
	virtual void rva001d9630BehaviorSlot13() = 0;
	virtual void rva001d9630BehaviorSlot14() = 0;
	virtual void rva001d9630BehaviorSlot15() = 0;
	virtual void rva001d9630BehaviorSlot16() = 0;
	virtual void rva001d9630BehaviorSlot17() = 0;
	virtual void rva001d9630BehaviorSlot18() = 0;
	virtual void rva001d9630BehaviorSlot19() = 0;
	virtual void rva001d9630BehaviorSlot20() = 0;
	virtual void rva001d9630BehaviorSlot21() = 0;
	virtual void rva001d9630BehaviorSlot22() = 0;
	virtual void rva001d9630BehaviorSlot23() = 0;
	virtual void rva001d9630BehaviorSlot24() = 0;
    virtual SlavedUpdateInterface *getSlavedUpdateInterface() = 0;
};
class BehaviorModule
{
public:
    SlavedUpdateInterface *getSlavedUpdateInterface() {
        return ((Rva001D9630BehaviorInterface *)((char *)this + 0xc))->getSlavedUpdateInterface();
    }
};
class LifetimeUpdate { public: void setLifetimeRange(UnsignedInt, UnsignedInt); };
class FloatUpdate
{
public:
    void setEnabled(Bool value) { *((bool *)this + 0x20) = value; }
};
class PhysicsBehavior
{
public:
    void setIgnoreCollisionsWith(const Object *);
    const Coord3D *getVelocity() const;
    void applyForce(const Coord3D *);
    void setAngles(Real, Real, Real);
    void setAllowBouncing(bool value) { *((bool *)this + 0x5d) = value; }
};
class ParticleSystemTemplate;
class ParticleSystem { public: void attachToObject(const Object *); };
extern "C" void __fastcall __identifier("?j_0002129c@@YAXXZ")(void *);
class ParticleSystemHandle
{
public:
    ~ParticleSystemHandle() { if (m_system) __identifier("?j_0002129c@@YAXXZ")(this); }
    ParticleSystem *get() const;
    ParticleSystem *m_system;
    void *m_next;
    void *m_prev;
};
extern "C" ParticleSystem *__cdecl __identifier("?j_00001b18@@YAXXZ")();
inline ParticleSystem *ParticleSystemHandle::get() const {
    return m_system ? m_system : __identifier("?j_00001b18@@YAXXZ")();
}
class ParticleSystemManager
{
public:
    const ParticleSystemTemplate *findTemplate(const AsciiString &) const;
    ParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *, Bool);
};
extern ParticleSystemManager *TheParticleSystemManager;
class ContainModuleInterface
{
public:
	virtual void rva001d9630ContainSlot0() = 0;
	virtual void rva001d9630ContainSlot1() = 0;
	virtual void rva001d9630ContainSlot2() = 0;
	virtual void rva001d9630ContainSlot3() = 0;
	virtual void rva001d9630ContainSlot4() = 0;
	virtual void rva001d9630ContainSlot5() = 0;
	virtual void rva001d9630ContainSlot6() = 0;
	virtual void rva001d9630ContainSlot7() = 0;
	virtual void rva001d9630ContainSlot8() = 0;
	virtual void rva001d9630ContainSlot9() = 0;
	virtual void rva001d9630ContainSlot10() = 0;
	virtual void rva001d9630ContainSlot11() = 0;
	virtual void rva001d9630ContainSlot12() = 0;
	virtual void rva001d9630ContainSlot13() = 0;
	virtual void rva001d9630ContainSlot14() = 0;
	virtual void rva001d9630ContainSlot15() = 0;
	virtual void rva001d9630ContainSlot16() = 0;
	virtual void rva001d9630ContainSlot17() = 0;
	virtual void rva001d9630ContainSlot18() = 0;
	virtual void rva001d9630ContainSlot19() = 0;
	virtual void rva001d9630ContainSlot20() = 0;
	virtual void rva001d9630ContainSlot21() = 0;
	virtual void rva001d9630ContainSlot22() = 0;
	virtual void rva001d9630ContainSlot23() = 0;
	virtual void rva001d9630ContainSlot24() = 0;
	virtual void rva001d9630ContainSlot25() = 0;
	virtual void rva001d9630ContainSlot26() = 0;
	virtual void rva001d9630ContainSlot27() = 0;
	virtual void rva001d9630ContainSlot28() = 0;
	virtual void rva001d9630ContainSlot29() = 0;
	virtual void rva001d9630ContainSlot30() = 0;
	virtual void rva001d9630ContainSlot31() = 0;
	virtual void rva001d9630ContainSlot32() = 0;
    virtual Bool isValidContainerFor(Object *, Bool) = 0;
    virtual void addToContain(Object *) = 0;
};
enum PathfindLayerEnum { LAYER_GROUND = 1 };
class TerrainLogic
{
public:
	virtual void rva001d9630TerrainSlot0() = 0;
	virtual void rva001d9630TerrainSlot1() = 0;
	virtual void rva001d9630TerrainSlot2() = 0;
	virtual void rva001d9630TerrainSlot3() = 0;
	virtual void rva001d9630TerrainSlot4() = 0;
	virtual void rva001d9630TerrainSlot5() = 0;
    virtual Real getGroundHeight(Real, Real, Coord3D * = 0) const = 0;
    virtual Real getLayerHeight(Real, Real, PathfindLayerEnum, Coord3D * = 0, bool = true) const = 0;
    PathfindLayerEnum getHighestLayerForDestination(const Coord3D *, bool = false);
};
extern TerrainLogic *TheTerrainLogic;
class GameLogic { public: void destroyObject(Object *); };
extern GameLogic *TheGameLogic;
extern Int GetGameLogicRandomValue(Int, Int, char *, Int);
extern Real GetGameLogicRandomValueReal(Real, Real, char *, Int);
inline __declspec(noinline) void calcRandomForce(Real minMag, Real maxMag, Real minPitch, Real maxPitch, Coord3D* force)
{
	Real angle = GetGameLogicRandomValueReal(0, 2*PI, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 568);
	Real pitch = GetGameLogicRandomValueReal(minPitch, maxPitch, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 569);
	Real mag = GetGameLogicRandomValueReal(minMag, maxMag, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 570);

	Matrix3D mtx(1);
	mtx.Scale(mag);
	mtx.Rotate_Z(angle);
	mtx.Rotate_Y(-pitch);

	Vector3 v = mtx.Get_X_Vector();

	force->x = v.X;
	force->y = v.Y;
	force->z = v.Z;
}
class HijackerUpdate { public: void setTargetObject(const Object *); };
template <class T> struct RetailVector
{
	T *m_begin;
	T *m_end;
	T *m_capacity;
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	T &operator[](unsigned int index) const { return m_begin[index]; }
};

enum AICommandType { AICMD_RVA001D9630 = 0x31 };
enum CommandSourceType { CMD_RVA001D9630 = 2 };
extern "C" void __fastcall __identifier("?j_0000de68@@YAXXZ")(void *);
struct AICommandParms
{
    AICommandParms(AICommandType, CommandSourceType);
    ~AICommandParms() { __identifier("?j_0000de68@@YAXXZ")(&m_coords); }
    AICommandType m_cmd;
    CommandSourceType m_cmdSource;
    Coord3D m_pos;
    Object *m_obj;
    Object *m_otherObj;
    void *m_team;
    RetailVector<Coord3D> m_coords;
    void *m_waypoint;
    void *m_polygon;
    int m_intValue;
    unsigned char m_remaining[0x64];
};
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

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	void doStuffToObj(Object *, const AsciiString &, const Coord3D *, const Matrix3D *, Real,
		const Object *, UnsignedInt, Int) const;

private:
	_STL::vector<AsciiString> m_names;
	AsciiString m_putInContainer;
	_STL::vector<GenericObjectCreationNuggetAnimSet> m_animSets;
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


typedef char Rva001D9630NuggetSize[sizeof(GenericObjectCreationNugget) == 0x148 ? 1 : -1];
typedef char Rva001D9630CommandSize[sizeof(AICommandParms) == 0x9c ? 1 : -1];
typedef char Rva001D9630AnimSize[sizeof(GenericObjectCreationNuggetAnimSet) == 12 ? 1 : -1];
typedef char Rva001D9630HandleSize[sizeof(ParticleSystemHandle) == 12 ? 1 : -1];

static __forceinline void rva001D9630Rotate(Coord3D &pos, Real s, Real c)
{
    Real x = pos.x;
    Real y = pos.y;
    pos.x = c * x - s * y;
    pos.y = s * x + c * y;
}
static __forceinline void rva001D9630Rotate(Coord3D &pos, Real angle)
{
    Real s = (Real)sin((double)angle);
    Real c = (Real)cos((double)angle);
    rva001D9630Rotate(pos, s, c);
}

// ?doStuffToObj@GenericObjectCreationNugget@@QBEXPAVObject@@ABVAsciiString@@PBUCoord3D@@PBVMatrix3D@@MPBV2@IH@Z
void GenericObjectCreationNugget::doStuffToObj(Object *obj, const AsciiString &modelName,
    const Coord3D *pos, const Matrix3D *mtx, Real orientation, const Object *sourceObj,
    UnsignedInt lifetimeFrames, Int formationIndex) const
{
    if (!obj) return;
    ModelConditionFlags clearFlags;
    obj->clearAndSetModelConditionFlags(clearFlags, *(const ModelConditionFlags *)m_startingConditions);
    static NameKeyType key_LifetimeUpdate = TheNameKeyGenerator->nameToKey("LifetimeUpdate");
    LifetimeUpdate *lifetime = (LifetimeUpdate *)obj->findUpdateModule(key_LifetimeUpdate);
    if (lifetime) {
        if (lifetimeFrames) lifetime->setLifetimeRange(lifetimeFrames, lifetimeFrames);
        else if (m_maxFrames > 0) lifetime->setLifetimeRange(m_minFrames, m_maxFrames);
    }
    if (!m_nameAreObjects) {
        for (DrawModule **draw = obj->getDrawable()->getDrawModules(); *draw; ++draw) {
            DebrisDrawInterface *debris = (*draw)->getDebrisDrawInterface();
            if (debris) {
                debris->setModelName(modelName, m_okToChangeModelColor ? obj->getIndicatorColor() : 0, m_shadowType);
                if (m_animSets.size() > 0) {
                    Int which = GetGameLogicRandomValue(0, m_animSets.size()-1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1005);
                    debris->setAnimNames(m_animSets[which].m_animInitial, m_animSets[which].m_animFlying, m_animSets[which].m_animFinal, m_fxFinal);
                }
            }
        }
    }
    if (m_ignorePrimaryObstacle) ((Rva001BE220Receiver *)obj)->dispatch(0xcf, 1u);
    if (m_startingBusyTime > 0) {
        UnsignedInt busyTime = m_startingBusyTime;
        AIUpdateInterface *ai = obj->getAIUpdateInterface();
        if (ai) {
            AICommandInterface *receiver = ai->commandInterface();
            AICommandParms parms(AICMD_RVA001D9630, CMD_RVA001D9630);
            parms.m_intValue = busyTime;
            receiver->aiDoCommand(&parms);
        }
    }
    Coord3D offset;
    offset.x = m_offset.x; offset.y = m_offset.y; offset.z = m_offset.z;
    if (mtx) adjustVector(&offset, mtx);
    Coord3D chunkPos;
    chunkPos.x = pos->x + offset.x;
    chunkPos.y = pos->y + offset.y;
    chunkPos.z = pos->z + offset.z;
    if (!m_particleSysName.isEmpty()) {
        const ParticleSystemTemplate *particleTemplate = TheParticleSystemManager->findTemplate(m_particleSysName);
        if (particleTemplate) {
            TheParticleSystemManager->createParticleSystem(particleTemplate, TRUE).get()->attachToObject(obj);
        }
    }
    BodyModuleInterface *body = obj->getBodyModule();
    Real health = GetGameLogicRandomValueReal(m_minHealth, m_maxHealth, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1044);
    if (body) body->setInitialHealth(health * 100.0f, false);
    for (BehaviorModule **module = obj->getBehaviorModules(); *module; ++module) {
        SlavedUpdateInterface *slaved = (*module)->getSlavedUpdateInterface();
        if (slaved) { slaved->onEnslave(sourceObj); break; }
    }
    if (m_invulnerableTime > 0) obj->goInvulnerable(m_invulnerableTime);
    PhysicsBehavior *objectPhysics = obj->getPhysics();
    Coord3D accumulatedForce = {0, 0, 0};
    if (m_disposition & GEN_LIKE_EXISTING) {
        if (mtx) obj->setTransformMatrix(mtx);
        else obj->setOrientation(orientation);
        obj->setPosition(&chunkPos);
    } else if (m_disposition & GEN_USE_DISPOSITION_ANGLE) {
        obj->setOrientation(m_dispositionAngle);
        obj->setPosition(&chunkPos);
    } else if (m_disposition & GEN_RADIAL_FORCE) {
        Coord3D radialPos;
        radialPos.z = chunkPos.z;
        Real angle = formationIndex * m_dispositionAngle;
        radialPos.x = m_dispositionIntensity;
        radialPos.y = 0.0f;
        rva001D9630Rotate(radialPos, angle);
        radialPos.x += chunkPos.x;
        radialPos.y += chunkPos.y;
        obj->setOrientation(angle);
        obj->setPosition(&radialPos);
    }
    if (m_disposition & 0x1000) { obj->addRva001D9630Condition(); return; }
    if ((m_disposition & 0x80) && sourceObj && objectPhysics) {
        Coord3D force;
        sourceObj->getUnitDirectionVector3D(force);
        Real height = sourceObj->bfmeGetNonnegativePreferredLocomotorHeight();
        force.x *= height; force.y *= height; force.z *= height;
        accumulatedForce.x += force.x; accumulatedForce.y += force.y; accumulatedForce.z += force.z;
    }
    if ((m_disposition & GEN_INHERIT_VELOCITY) && sourceObj && sourceObj->getPhysics() && objectPhysics) {
        Coord3D force;
        sourceObj->getUnitDirectionVector3D(force);
        Real height = sourceObj->bfmeGetNonnegativePreferredLocomotorHeight() * m_velocityScale;
        force.x *= height; force.y *= height; force.z *= height;
        objectPhysics->applyForce(&force);
    }
    if ((m_disposition & GEN_INHERIT_SHADOW_VELOCITY) && sourceObj && sourceObj->getPhysics() && objectPhysics) {
        Coord3D force;
        sourceObj->getUnitDirectionVector3D(force);
        Real height = sourceObj->bfmeGetNonnegativePreferredLocomotorHeight() * m_velocityScale * -1.0f;
        force.x *= height; force.y *= height; force.z *= height;
        objectPhysics->applyForce(&force);
    }
    if ((m_disposition & GEN_INHERIT_NORMAL_VELOCITY) && objectPhysics) {
        Coord3D force;
        force.x = offset.x; force.y = offset.y; force.z = 0;
        __identifier("?normalize@Coord3D@@QAEXXZ")(&force);
        Real intensity = m_velocityScale * m_dispositionIntensity;
        force.x *= intensity; force.y *= intensity; force.z *= intensity;
        objectPhysics->applyForce(&force);
    }
    if (m_disposition & 0x800) {
        static NameKeyType key_HijackerUpdate = TheNameKeyGenerator->nameToKey("HijackerUpdate");
        HijackerUpdate *hijacker = (HijackerUpdate *)obj->findUpdateModule(key_HijackerUpdate);
        if (hijacker) hijacker->setTargetObject(sourceObj);
    }
    if (m_disposition & GEN_ON_GROUND_ALIGNED) {
        chunkPos.z = 99999.0f;
        PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(&chunkPos);
        obj->setOrientation(GetGameLogicRandomValueReal(0.0f, 2*PI, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1197));
        chunkPos.z = TheTerrainLogic->getLayerHeight(chunkPos.x, chunkPos.y, layer);
        if (layer != LAYER_GROUND) chunkPos.z += 1.0f;
        obj->setLayer(layer); obj->setPosition(&chunkPos);
    }
    if (m_disposition & GEN_SEND_IT_OUT) {
        obj->setOrientation(GetGameLogicRandomValueReal(0.0f, 2*PI, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1208));
        chunkPos.z = TheTerrainLogic->getGroundHeight(chunkPos.x, chunkPos.y);
        obj->setPosition(&chunkPos);
        {
            Coord3D force;
            Real horizontal = 4.0f * m_dispositionIntensity;
            force.x = GetGameLogicRandomValueReal(-horizontal, horizontal, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1214);
            force.y = GetGameLogicRandomValueReal(-horizontal, horizontal, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1215);
            force.z = 0;
            accumulatedForce.x += force.x; accumulatedForce.y += force.y; accumulatedForce.z += force.z;
        }
    }
    if (m_disposition & (GEN_SEND_IT_FLYING|GEN_SEND_IT_UP|GEN_RANDOM_FORCE)) {
        if (mtx) obj->setTransformMatrix(mtx);
        obj->setPosition(&chunkPos);
        if (objectPhysics) {
            objectPhysics->setAllowBouncing(true);
            Coord3D force;
            if (m_disposition & GEN_SEND_IT_FLYING) {
                Real horizontal = 4.0f * m_dispositionIntensity;
                Real vertical = 3.0f * m_dispositionIntensity;
                force.x = GetGameLogicRandomValueReal(-horizontal,horizontal,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",1242);
                force.y = GetGameLogicRandomValueReal(-horizontal,horizontal,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",1243);
                force.z = GetGameLogicRandomValueReal(vertical*0.33f,vertical,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",1244);
            } else if (m_disposition & GEN_SEND_IT_UP) {
                Real horizontal = 2.0f * m_dispositionIntensity;
                Real vertical = 4.0f * m_dispositionIntensity;
                force.x = GetGameLogicRandomValueReal(-horizontal,horizontal,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",1254);
                force.y = GetGameLogicRandomValueReal(-horizontal,horizontal,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",1255);
                force.z = GetGameLogicRandomValueReal(vertical*0.75f,vertical,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",1256);
            } else calcRandomForce(m_minMag,m_maxMag,m_minPitch,m_maxPitch,&force);
            accumulatedForce.x += force.x; accumulatedForce.y += force.y; accumulatedForce.z += force.z;
        }
    }
    if (m_disposition & GEN_FLOATING) {
        static NameKeyType key_FloatUpdate = TheNameKeyGenerator->nameToKey("FloatUpdate");
        FloatUpdate *floatUpdate = (FloatUpdate *)obj->findUpdateModule(key_FloatUpdate);
        if (floatUpdate) floatUpdate->setEnabled(TRUE);
    }
    if (accumulatedForce.x*accumulatedForce.x + accumulatedForce.y*accumulatedForce.y + accumulatedForce.z*accumulatedForce.z > 0 && objectPhysics)
        objectPhysics->applyForce(&accumulatedForce);
    if (m_containInsideSourceObject) {
        if (sourceObj->getContain() && sourceObj->getContain()->isValidContainerFor(obj, TRUE)) {
            sourceObj->getContain()->addToContain(obj);
            if (sourceObj->getDrawable() && obj->getDrawable() && sourceObj->getDrawable()->rva001D9630IsHidden())
                obj->getDrawable()->rva001D9630SetHidden(true);
        } else TheGameLogic->destroyObject(obj);
    }
}
