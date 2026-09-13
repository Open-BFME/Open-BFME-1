// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
// readable body of ??0PhysicsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/PhysicsUpdate.cpp
// ModuleFactory reaches this constructor through ILT 0x0003C3BC. Its 0x60-byte
// allocation proves the compact BFME layout, which predates Zero Hour fields.

#include <vector>

class Thing;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
    unsigned char m_pad[0x58];
    bool m_allowBouncing;
};

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }
    const ModuleData *getModuleData() const { return m_moduleData; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
    void zero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

private:
    float x;
    float y;
    float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PhysicsUpdate.h
class PhysicsBehavior : public UpdateModule
{
public:
    PhysicsBehavior(Thing *, const ModuleData *);
    virtual ~PhysicsBehavior();

private:
    std::vector<Coord3D> m_overlapForces;
    Coord3D m_accel;
    Coord3D m_vel;
    float m_velMag;
    float m_yawRate;
    float m_rollRate;
    float m_pitchRate;
    float m_mass;
    unsigned int m_motiveForceExpires;
    bool m_flag5c;
    bool m_allowBouncing;
    bool m_flag5e;
    bool m_flag5f;
};

// ??0PhysicsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
PhysicsBehavior::PhysicsBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_velMag = 0.0f;
    m_yawRate = 0.0f;
    m_rollRate = 0.0f;
    m_pitchRate = 0.0f;
    m_mass = 0.0f;
    m_motiveForceExpires = 0;
    m_flag5c = false;
    m_flag5e = false;
    m_flag5f = false;
    m_accel.zero();
    m_vel.zero();
    m_allowBouncing = getModuleData()->m_allowBouncing;
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
