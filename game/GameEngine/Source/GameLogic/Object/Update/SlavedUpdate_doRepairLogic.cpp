// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// SlavedUpdate repair logic; ZH control flow with BFME field offsets.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)


typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord3D
{
    Real x, y, z;
    void set(const Coord3D *other) { x = other->x; y = other->y; z = other->z; }
    void addZ(Real amount) { z += amount; }
};

class Object;
class GameLogic
{
public:
    Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;
extern Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

class Locomotor
{
private:
    unsigned char m_pad00[0x40];
public:
    unsigned int m_flags;
    void setUsePreciseZPos(Bool enabled)
    {
        if (enabled) m_flags |= 8;
        else m_flags &= ~8u;
    }
};

enum CommandSourceType { COMMAND_SOURCE_AI = 2 };

class AICommandInterface
{
public:
    void aiMoveToPosition(const Coord3D *pos, CommandSourceType commandSource);
};

class AIUpdateInterface
{
private:
    unsigned char m_pad00[0x20];
public:
    AICommandInterface m_commands;
    unsigned char m_pad24[0x1cc - 0x24];
    Locomotor *m_locomotor;
};

class BodyModuleInterface
{
public:
    virtual void slot0();
    virtual void attemptHealing(const class DamageInfo *info);
};

class Object
{
private:
    unsigned char m_pad00[0x38];
public:
    Coord3D m_position;
    unsigned char m_pad44[0xc0-0x44];
    Real m_radius;
    unsigned char m_padC4[0x200-0xc4];
    BodyModuleInterface *m_body;
    AIUpdateInterface *m_ai;
    Real getDistanceSquared(const Object *other) const;
    const Coord3D *getPosition() const { return &m_position; }
    AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
};

// DamageInfo::in begins after its Snapshot vtable; input's damage and death
// kinds and amount are +0x10, +0x18, and +0x1c from the whole object.
class DamageInfo
{
public:
    DamageInfo();
    unsigned char m_pad00[0x10];
    Int m_damageType;
    Int m_status;
    Int m_deathType;
    Real m_amount;
    unsigned char m_unused[0x5c-0x20];
};

class SlavedUpdateModuleData
{
private:
    unsigned char m_pad00[0x24];
public:
    Int m_repairRange;
    Real m_repairMinAltitude;
    Real m_repairMaxAltitude;
    Real m_repairRatePerSecond;
};

static __forceinline Real getRepairAltitude(const SlavedUpdateModuleData *data)
{
    Real value = GetGameLogicRandomValueReal(data->m_repairMinAltitude,
        data->m_repairMaxAltitude,
        "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp", 0x1f8);
    _ReadWriteBarrier();
    return value;
}

enum RepairStates { REPAIRSTATE_NONE, REPAIRSTATE_UNPACKING, REPAIRSTATE_PACKING,
    REPAIRSTATE_READY, REPAIRSTATE_EXTENDING, REPAIRSTATE_RETRACTING,
    REPAIRSTATE_WELDING };

class SlavedUpdate
{
public:
    void doRepairLogic();
    void setRepairState(RepairStates state);
    SlavedUpdateModuleData *getSlavedUpdateModuleData() const { return m_data; }
    Object *getObject() const { return m_object; }
private:
    unsigned char m_pad00[4];
    SlavedUpdateModuleData *m_data;
    Object *m_object;
    unsigned char m_pad0c[0x24-0x0c];
    Int m_slaver;
    unsigned char m_pad28[0x34-0x28];
    Int m_framesToWait;
    RepairStates m_repairState;
    Bool m_repairing;
};

#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:??0DamageInfo@@QAE@XZ=?j_0002c9d5@@YAXXZ")
#pragma comment(linker, "/alternatename:?getDistanceSquared@Object@@QBEMPBV1@@Z=?j_00043ced@@YAXXZ")

void SlavedUpdate::doRepairLogic()
{
    Object *me = getObject();
    Object *master = TheGameLogic->findObjectByID(m_slaver);
    const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
    AIUpdateInterface *ai = me->getAIUpdateInterface();
    if (!ai) return;

    // The decoded 0x000ED3B0 callee subtracts the two objects' XY positions
    // and their bounding radii before squaring the resulting distance.
    Real distanceSq = me->getDistanceSquared(master);
    Bool closeEnough = distanceSq < *(const Real *)0x010C2D30;
    if (closeEnough)
    {
        switch (m_repairState)
        {
        case REPAIRSTATE_NONE: setRepairState(REPAIRSTATE_READY); break;
        case REPAIRSTATE_READY: case REPAIRSTATE_EXTENDING:
            if (!m_framesToWait) setRepairState(REPAIRSTATE_WELDING);
            break;
        case REPAIRSTATE_UNPACKING: case REPAIRSTATE_RETRACTING:
        case REPAIRSTATE_WELDING:
            if (!m_framesToWait) setRepairState(REPAIRSTATE_READY);
            break;
        }
    }
    else
    {
        m_repairing = false;
        Bool preciseZ = distanceSq < (master->m_radius * 2) * (master->m_radius * 2);
        Locomotor *locomotor = ai->m_locomotor;
        if (locomotor) locomotor->setUsePreciseZPos(preciseZ);
        Coord3D pos;
        pos.set(master->getPosition());
        pos.z += getRepairAltitude(data);
        ai->m_commands.aiMoveToPosition(&pos, COMMAND_SOURCE_AI);
        if (!m_framesToWait) setRepairState(REPAIRSTATE_READY);
    }
    if (closeEnough && m_repairing)
    {
        BodyModuleInterface *body = master->m_body;
        if (body)
        {
            Real amount = data->m_repairRatePerSecond / 30.0f;
            DamageInfo healing;
            healing.m_amount = amount;
            healing.m_damageType = 7;
            healing.m_deathType = 1;
            body->attemptHealing(&healing);
        }
    }
}
