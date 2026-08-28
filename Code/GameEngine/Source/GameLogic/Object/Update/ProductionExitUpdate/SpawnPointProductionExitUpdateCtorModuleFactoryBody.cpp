// cl: /DNDEBUG /MD /EHsc
// readable body of ??0SpawnPointProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp
// ModuleFactory reaches this constructor body through ILT 0x00023858. The
// explicit retail layout keeps this per-TU copy independent of Zero Hour's
// incompatible UpdateModule layout.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class SPEU_DeepBase
{
public:
    SPEU_DeepBase(Thing *, const ModuleData *);
    virtual ~SPEU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class SPEU_Iface1 { public: virtual void slot(); };
class SPEU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public SPEU_DeepBase, public SPEU_Iface1, public SPEU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : SPEU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class ExitInterface
{
public:
    virtual void exitObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
    Coord3D();
    ~Coord3D();

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h
class SpawnPointProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
    SpawnPointProductionExitUpdate(Thing *, const ModuleData *);

private:
    enum { MAX_SPAWN_POINTS = 10 };

    bool m_bonesInitialized;
    int m_spawnPointCount;
    Coord3D m_worldCoordSpawnPoints[MAX_SPAWN_POINTS];
    float m_worldAngleSpawnPoints[MAX_SPAWN_POINTS];
    unsigned int m_spawnPointOccupier[MAX_SPAWN_POINTS];
};

// ??0SpawnPointProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SpawnPointProductionExitUpdate::SpawnPointProductionExitUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_bonesInitialized = false;
    m_spawnPointCount = 0;
    for (int positionIndex = 0; positionIndex < MAX_SPAWN_POINTS; ++positionIndex)
    {
        m_worldCoordSpawnPoints[positionIndex].zero();
        m_worldAngleSpawnPoints[positionIndex] = 0.0f;
        m_spawnPointOccupier[positionIndex] = 0;
    }
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
