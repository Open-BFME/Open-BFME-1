// ?rva0029B120@PhysicsBehavior@@QAEX_N@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0029B120/137: compact PhysicsBehavior source shape.
// The constructor and destructor independently prove the +0x20 Coord3D
// vector and 0x60-byte owner layout.  This method name stays address-derived.
// The bitset accessor layers preserve retail's EAX mask for Object model
// condition bit 115, SPLATTED in the shipped table at VA 0x012A6918.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
struct Coord3D { float x, y, z; };
class ModuleData {
public:
    char m_pad[0x59];
    bool m_at59;
};
enum DamageType { DAMAGE_TYPE_8 = 8 };
enum DeathType { DEATH_TYPE_0 = 0 };
class Rva0029B120Conditions {
public:
    bool test(int bit) const { return m_bits.test(bit); }
    void set(int bit) { m_bits.set(bit); }
private:
    _STL::bitset<320> m_bits;
};
class Object {
public:
    void notifyModelConditionChanged();
    void kill(DamageType damage, DeathType death);
    char m_pad[0x110];
    Rva0029B120Conditions m_modelConditionFlags;
};
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };
class UpdateModule {
public:
    char m_vptr[4];
    const ModuleData *m_moduleData;
    Object *m_object;
    char m_rest[0x14];
protected:
    void setWakeFrame(Object *, UpdateSleepTime);
};
class PhysicsBehavior : public UpdateModule {
public:
    void rva0029B120(bool skipWake);
private:
    Coord3D *m_begin;
    Coord3D *m_end;
    Coord3D *m_capacity;
    char m_pad2C[0x24];
    float m_at50;
    float m_at54;
    char m_pad58[7];
    bool m_at5F;
};
extern void j_00014d7b();
static __forceinline void setCondition(Object *obj)
{
    if (!obj->m_modelConditionFlags.test(115)) {
        obj->m_modelConditionFlags.set(115);
        obj->notifyModelConditionChanged();
    }
}
void PhysicsBehavior::rva0029B120(bool skipWake)
{
    Coord3D *begin = m_begin;
    Coord3D *end = m_end;
    Object *obj = m_object;
    m_end = ((Coord3D *(__cdecl *)(Coord3D *, Coord3D *, Coord3D *, void *, int))j_00014d7b)(end, end, begin, &skipWake, 0);
    bool shouldKill = m_at5F;
    m_at50 = 0.0f;
    m_at54 = 0.0f;
    if (shouldKill || m_moduleData->m_at59) {
        setCondition(obj);
        obj->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
    } else if (!skipWake) {
        setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
    }
}
