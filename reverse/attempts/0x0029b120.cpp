// ?rva0029B120@PhysicsBehavior@@QAEX_N@Z
// partial score=0.87 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0029B120/137: compact PhysicsBehavior source shape.
// The constructor and destructor independently prove the +0x20 Coord3D
// vector and 0x60-byte owner layout.  This method name stays address-derived.
// Probe: 137/137 with 18 non-relocation differences at +0x61..+0x75:
// retail materializes 0x80000 in EAX and tests it against the flags in ECX;
// this source ORs in EAX and compares.  Do not land until that tail matches.
struct Coord3D { float x, y, z; };
class ModuleData {
public:
    char m_pad[0x59];
    bool m_at59;
};
enum DamageType { DAMAGE_TYPE_8 = 8 };
enum DeathType { DEATH_TYPE_0 = 0 };
class Object {
public:
    void notifyModelConditionChanged();
    void kill(DamageType damage, DeathType death);
    char m_pad[0x11C];
    unsigned m_modelConditions;
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
        unsigned flags = obj->m_modelConditions;
        unsigned mask = 0x80000;
        if ((flags | mask) != flags) {
            obj->m_modelConditions = flags | mask;
            obj->notifyModelConditionChanged();
        }
        obj->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
    } else if (!skipWake) {
        setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
    }
}
