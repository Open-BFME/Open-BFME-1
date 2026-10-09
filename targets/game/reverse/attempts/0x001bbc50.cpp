// ?d_001bbc50@@YAXXZ
// partial score=0.282 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Include
// Retail 0x001BBC50: complete locomotor query with native GeometryInfo ownership.
// Evidence: targets/game/reverse/identity_evidence/001bbc50-native-lifetime.md.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _OPERATOR_NEW_DEFINED_
#include <bitset>
#include <math.h>
#include "vector3.h"
#include "matrix3d.h"

typedef bool Bool;
#include <Lib/Coord3D.h>
struct ModelConditionFlags {
    __forceinline bool test(int bit) const { return bits.test(bit); }
    __forceinline void set(int bit) { bits.set(bit); }
    __forceinline void clear(int bit) { bits.reset(bit); }
    _STL::bitset<320> bits;
};
#define BFME_HAVE_COORD3D
#define BFME_HAVE_MODELCONDITIONFLAGS
#define THING_TU_MEMBERS \
    float bfmeRelativeAngleTo(const Coord3D *) const; \
    void rva00132200(const Matrix3D *); \
    void setTransformMatrix(const Matrix3D *);
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "object.h"

static __forceinline void setCondition(Object *obj, int bit) {
    if (!obj->m_modelConditionFlags.test(bit)) {
        obj->m_modelConditionFlags.set(bit);
        obj->notifyModelConditionChanged();
    }
}
static __forceinline void clearCondition(Object *obj, int bit) {
    if (obj->m_modelConditionFlags.test(bit)) {
        obj->m_modelConditionFlags.clear(bit);
        obj->notifyModelConditionChanged();
    }
}

template<class T> inline const T &rva001BBC50Max(const T &a, const T &b) {
    return a > b ? a : b;
}

class Overridable {
public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    const Overridable *m_nextOverride;
};
class Rva001BBC50Template : public Overridable {
public:
    char field008[0x14 - 8];
    float field014;
    unsigned char field018;
};
struct Rva001BBC50Bird {
    char field000[0x3f0];
    unsigned field3f0;
    char field3f4[0x470 - 0x3f4];
    float field470;
    float field474;
    char field478[4];
    Coord3D field47c;
    float getCurrentSpeed() const { return field470; }
    void setCurrentSpeed(float value) { field470 = value; }
    float getCurrentAngle() const { return field474; }
    void setCurrentAngle(float value) { field474 = value; }
};
class Rva001BBC50AI {
public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual Rva001BBC50Bird *bird();
};
class Rva002BCB60QueryObject;
class Rva002BCB60AerialPathfinder {
public:
    bool tryQuery(Rva002BCB60QueryObject *, float, Coord3D *);
};
extern Rva002BCB60AerialPathfinder *g_rva012EF1F8;
class TerrainLogic {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual float getGroundHeight(float, float, Coord3D *) const;
};
extern TerrainLogic *TheTerrainLogic;

extern void j_0002b355();
extern void j_000309f4();
class Rva001BBC50GeometryCopy {
public:
    Rva001BBC50GeometryCopy(const void *source) {
        typedef void *(Rva001BBC50GeometryCopy::*Copy)(const void *);
        union { void (*function)(); Copy member; } copy;
        copy.function = j_0002b355;
        (this->*copy.member)(source);
    }
    ~Rva001BBC50GeometryCopy() {
        typedef void (Rva001BBC50GeometryCopy::*Destroy)();
        union { void (*function)(); Destroy member; } destroy;
        destroy.function = j_000309f4;
        (this->*destroy.member)();
    }
    float field014() const { return *(const float *)&words[5]; }
private:
    unsigned words[0x5c / 4];
};
typedef char Rva001BBC50GeometrySize[sizeof(Rva001BBC50GeometryCopy) == 0x5c ? 1 : -1];

struct Rva001B46B0Vec3 { float x, y, z; };
float Rva001B46B0(const Rva001B46B0Vec3 *, const Rva001B46B0Vec3 *);
class Rva001B49E0Owner { public: void setPosition(const Coord3D *); };
class Rva001B4A50 { public: void method(float); };
class Gen_000E5A50 { public: float bfmeDistanceSquared(const class BfmeVec3EJ *) const; };
class Locomotor { public: float getMaxTurnRate(Object *) const; };
class BfmeSub1CC_EC3 { public:
    float effectiveMaxSpeed(void *);
    float queryDivMin40(void *);
    float queryDivMin4C(void *);
};
struct Rva001B59ScaleContext;
class Rva001B59FloatView { public: float getScaledFirst(const Rva001B59ScaleContext *) const; };
class BfmeVec3DG { public:
    BfmeVec3DG() {}
    
    float x, y, z;
};
class Gen_00148990 { public: BfmeVec3DG bfmeDelta(const BfmeVec3DG *) const; };
struct Rva001B3F60Payload;
struct Rva001B3F60Target { void copy(Rva001B3F60Payload *); };
float normalizeAngle(float);

class Rva002C12E0Locomotor {
public:
    unsigned char locoQuery(void *, float, void *, void *);
    void *m_next;
    const Rva001BBC50Template *m_template;
    char field008[0x64 - 8];
    Matrix3D field064;
    const Rva001BBC50Template *getTemplate() const {
        const Rva001BBC50Template *p = m_template;
        if (p && p->m_nextOverride)
            p = (const Rva001BBC50Template *)p->m_nextOverride->getFinalOverride();
        return p;
    }
};

// ?locoQuery@Rva002C12E0Locomotor@@QAEEPAXM00@Z
unsigned char Rva002C12E0Locomotor::locoQuery(void *object, float desiredSpeed, void *distance, void *path)
{
    Object *obj = (Object *)object;
    if (!obj) return false;
    float radius = *(const float *)((const char *)obj + 0xc0) * 0.5f;
    if (getTemplate()->field014 > 1.0f) radius *= getTemplate()->field014;
    Rva001BBC50AI *ai = (Rva001BBC50AI *)obj->m_ai;
    if (!ai) return false;
    Rva001BBC50Bird *bird = ai->bird();
    if (!bird) return false;
    field064 = obj->m_transform;
    float speed = bird->getCurrentSpeed();
    float range = *(float *)distance + speed;
    *(float *)distance = range;
    Coord3D position;
    if (g_rva012EF1F8->tryQuery((Rva002BCB60QueryObject *)path, range, &position)) {
        ((Rva001B49E0Owner *)this)->setPosition(&position);
        bool flag = (bird->field3f0 >> 7) & 1;
        if (!flag) {
            Coord3D goal;
            goal.x = bird->field47c.x;
            goal.y = bird->field47c.y;
            goal.z = bird->field47c.z;
            flag = ((Gen_000E5A50 *)obj)->bfmeDistanceSquared((const BfmeVec3EJ *)&goal) > 4900.0f;
        }
        if (flag) setCondition(obj, 60);
        else clearCondition(obj, 60);
        float slope = 0.0f;
        float angle = 0.0f;
        float count = 0.0f;
        if (getTemplate()->field018) obj->setTransformMatrix(&field064);
        Coord3D rear, front;
        if (g_rva012EF1F8->tryQuery((Rva002BCB60QueryObject *)path, *(float *)distance - radius, &rear)) {
            slope = Rva001B46B0((Rva001B46B0Vec3 *)&rear, (Rva001B46B0Vec3 *)&position);
            angle = normalizeAngle(obj->bfmeRelativeAngleTo(&rear) + 3.1415927f);
            count = 1.0f;
        }
        if (g_rva012EF1F8->tryQuery((Rva002BCB60QueryObject *)path, radius + *(float *)distance, &front)) {
            slope += Rva001B46B0((Rva001B46B0Vec3 *)&position, (Rva001B46B0Vec3 *)&front);
            angle += obj->bfmeRelativeAngleTo(&front);
            count += 1.0f;
        }
        if (count > 0.0f) { count = 1.0f / count; angle *= count; slope *= count; }
        float oldAngle = bird->getCurrentAngle();
        float rate = ((Locomotor *)this)->getMaxTurnRate(obj);
        bool excessive = fabs(angle) > rate * 3.0f;
        float low = -rate;
        float clamped = (angle > low ? angle : low) < rate ? (angle > low ? angle : low) : rate;
        bird->setCurrentAngle(clamped * 0.2f + oldAngle * 0.8f);
        float newAngle = normalizeAngle(obj->m_cachedAngle + clamped);
        ((Rva001B4A50 *)this)->method(newAngle);
        float remaining;
        {
        BfmeVec3DG delta = ((Gen_00148990 *)obj)->bfmeDelta((const BfmeVec3DG *)((const char *)path + 0x54));
        remaining = (float)sqrt(delta.x * delta.x + delta.z * delta.z + delta.y * delta.y);
        }
        if (remaining < 4.0f * bird->getCurrentSpeed() && slope < 0.0f) slope *= -1.0f;
        else if (excessive) slope += 1.5f;
        if (speed < desiredSpeed) speed += ((BfmeSub1CC_EC3 *)this)->queryDivMin40(obj);
        else if (speed > desiredSpeed) speed -= ((BfmeSub1CC_EC3 *)this)->queryDivMin4C(obj);
        speed *= 1.0f - slope * 0.4f;
        if (((BfmeSub1CC_EC3 *)this)->effectiveMaxSpeed(obj) < speed)
            speed = ((BfmeSub1CC_EC3 *)this)->effectiveMaxSpeed(obj);
        else if (((Rva001B59FloatView *)this)->getScaledFirst((Rva001B59ScaleContext *)obj) > speed)
            speed = ((Rva001B59FloatView *)this)->getScaledFirst((Rva001B59ScaleContext *)obj);
        bird->setCurrentSpeed(speed);
        {
        Vector3 translation = field064.Get_Translation();
        float height = TheTerrainLogic->getGroundHeight(translation.X, translation.Y, 0);
        Rva001BBC50GeometryCopy geometry(obj->m_geometryInfo);
        height += geometry.field014() * 0.25f;
        translation.Z = rva001BBC50Max(translation.Z, height);
        field064.Set_Translation(translation);
        if (slope > 0.3f) {
            if (obj->m_modelConditionFlags.test(71) || !obj->m_modelConditionFlags.test(102)) {
                obj->m_modelConditionFlags.clear(71);
                obj->m_modelConditionFlags.set(102);
                obj->notifyModelConditionChanged();
            }
        } else if (slope < -0.6f) {
            if (obj->m_modelConditionFlags.test(102) || !obj->m_modelConditionFlags.test(71)) {
                obj->m_modelConditionFlags.clear(102);
                obj->m_modelConditionFlags.set(71);
                obj->notifyModelConditionChanged();
            }
        } else { clearCondition(obj, 71); clearCondition(obj, 102); }
        obj->rva00132200(&field064);
        Coord3D next = obj->m_cachedPos;
        if (g_rva012EF1F8->tryQuery((Rva002BCB60QueryObject *)path, bird->getCurrentSpeed() + *(float *)distance, &next))
            ((Rva001B3F60Target *)obj)->copy((Rva001B3F60Payload *)&next);
        return false;
        }
    }
    clearCondition(obj, 60);
    clearCondition(obj, 102);
    clearCondition(obj, 71);
    return true;
}
